#include <mac/ozb_mac_internal.h>
#include <hal/ozb_radio.h>
#include <kal/ozb_kal.h>
#include <util/ozb_debug.h>

#define NEXT_TSLOT(idx) (((idx) + 1) % 16)
#define TIME32_SUBTRACT(t1, t2) ((t1)>(t2) ? (t1)-(t2) : 0xFFFFFFFF-(t2)+(t1))

OZB_KAL_TASK(MAC_TIMESLOT, 10);
OZB_KAL_TASK(MAC_BEFORE_TIMESLOT, 10); 
OZB_KAL_TASK(MAC_BACKOFF_PERIOD, 10);
OZB_KAL_TASK(MAC_GTS_SEND, 10);

/******************************************************************************/
/*                          MAC Tasks Private Data                            */
/******************************************************************************/
static uint8_t current_tslot = OZB_MAC_SUPERFRAME_LAST_SLOT;
static struct {
	unsigned has_idle : 1;
	unsigned wait_sf_end : 1;
	unsigned gts_sending : 1;
} sf_flags = {OZB_FALSE, OZB_FALSE, OZB_FALSE};
static uint32_t time_reference = 0;
static uint32_t gts_available_bytes = 0;
static uint16_t gts_lifs_bytes = 0;
static uint16_t gts_sifs_bytes = 0;
static uint32_t test_time = 0;
/******************************************************************************/
/*                      MAC Tasks Private Functions                           */
/******************************************************************************/
COMPILER_INLINE void stop_activations(void) 
{
	/* FIXME: now I'm ignoring the return values! */
	ozb_kal_cancel_activation(MAC_TIMESLOT);
	ozb_kal_cancel_activation(MAC_BEFORE_TIMESLOT);
	ozb_kal_cancel_activation(MAC_BACKOFF_PERIOD);
}

COMPILER_INLINE void start_activations(uint32_t offset) 
{
	uint32_t t;

	if (offset == 0)
		offset = OZB_MAC_TICKS_BEFORE_TIMESLOT;
		//offset = OZB_MAC_TICKS_BEFORE_TIMESLOT + 1;
	t = OZB_MAC_GET_TS(ozb_mac_pib.macSuperframeOrder);
	/* FIXME: now I'm ignoring the return values! */
	ozb_kal_set_activation(MAC_BEFORE_TIMESLOT, 
				offset - OZB_MAC_TICKS_BEFORE_TIMESLOT, t); 
	ozb_kal_set_activation(MAC_TIMESLOT, offset, t);
	ozb_kal_set_activation(MAC_BACKOFF_PERIOD, offset, 1);
} 

COMPILER_INLINE void restart_activations(uint32_t offset) 
{
	stop_activations();
	start_activations(offset);
} 

COMPILER_INLINE uint32_t btick_to_bytes(uint32_t bt)
{
	/* TODO: change this hard-coding (320 microsecond) ? */
	bt *= 32; /* bt1 = bt0 x 320us x 10^-1 */
	bt *= ozb_radio_phy_get_bitrate() / 80; /* bt2 = bt1 x Bps x 10^-1 */
	bt /= 10000; /* bt3 = bt2 x 10^-4 [us x Bps x 10^-6] */
	return bt;
}

COMPILER_INLINE uint8_t is_in_tx_gts(void) 
{
	return (ozb_mac_status.sf_context != OZB_MAC_SF_IDLE && 
		current_tslot >= ozb_mac_gts_stat.tx_start_tslot && 
		current_tslot < ozb_mac_gts_stat.tx_start_tslot + 
		ozb_mac_gts_stat.tx_length);
}


COMPILER_INLINE void resync_activations(void) 
{
	uint32_t t;

	stop_activations();
	t = OZB_MAC_GET_TS(ozb_mac_pib.macSuperframeOrder);
	current_tslot = OZB_MAC_SUPERFRAME_LAST_SLOT;
	ozb_kal_set_activation(MAC_BEFORE_TIMESLOT, 
			       t - OZB_MAC_TICKS_BEFORE_TIMESLOT, t);
	ozb_kal_set_activation(MAC_TIMESLOT, 0, t);
	ozb_kal_set_activation(MAC_BACKOFF_PERIOD, 0, 1);
}

COMPILER_INLINE void start_beacon_interval(void) 
{
	char s[100];
	uint32_t mmm = ozb_debug_time_get_us(OZB_DEBUG_TIME_CLOCK_DEVEL);

	ozb_debug_time_get(OZB_DEBUG_TIME_CLOCK_BI);
	if (ozb_mac_status.is_pan_coordinator || ozb_mac_status.is_coordinator){
		ozb_radio_mac_send_beacon(); /* TODO: parse ret value*/
	} else if (ozb_mac_status.count_beacon_lost++ > OZB_aMaxLostBeacons) {
		stop_activations();
		return;
	}
	if (ozb_mac_pib.macSuperframeOrder < ozb_mac_pib.macBeaconOrder) {
		sf_flags.has_idle = OZB_TRUE;
		sf_flags.wait_sf_end = OZB_TRUE;
	}
	if (ozb_mac_gts_stat.tx_length != 0) {
		/* TODO: calculate gts_available_bytes */
		gts_available_bytes = 
			btick_to_bytes((uint32_t) ozb_mac_gts_stat.tx_length *
			       OZB_MAC_GET_TS( ozb_mac_pib.macSuperframeOrder));
		gts_available_bytes -= gts_lifs_bytes;
		
	}
	ozb_mac_status.sf_context = OZB_MAC_SF_CAP;
	/*
	sprintf(s, "DEVICE: Start BI - %lu: B0=%u S0=%u TX=%u LTX=%u ", 
		mmm,ozb_mac_pib.macBeaconOrder, ozb_mac_pib.macSuperframeOrder, 
		ozb_mac_gts_stat.tx_start_tslot, ozb_mac_gts_stat.tx_length);
	ozb_debug_print(s);
	*/
	ozb_debug_print("DEVICE: start BI");
}

COMPILER_INLINE void stop_superframe(void) 
{
	uint32_t t;

	ozb_mac_status.sf_context = OZB_MAC_SF_IDLE;
	sf_flags.wait_sf_end = OZB_FALSE;
	t = OZB_MAC_GET_BI(ozb_mac_pib.macBeaconOrder) - 
	    OZB_MAC_GET_SD(ozb_mac_pib.macSuperframeOrder);
	restart_activations(t);
	current_tslot = OZB_MAC_SUPERFRAME_LAST_SLOT;
	sf_flags.wait_sf_end = OZB_FALSE;
	sf_flags.has_idle = OZB_FALSE;
	ozb_debug_print("DEVICE: End Of SF");
}

COMPILER_INLINE void before_beacon_interval(void)
{
	uint8_t str[OZB_DEBUG_STAT_STRLEN];

	if (ozb_mac_status.is_pan_coordinator || ozb_mac_status.is_coordinator)
		ozb_radio_mac_create_beacon(); /* TODO: parse error! */
	ozb_debug_stat2str(str);
	ozb_debug_write(str, OZB_DEBUG_STAT_STRLEN);
	ozb_debug_print("DEVICE: before Start BI");
}

/******************************************************************************/
/*                             MAC Layer TASKs                                */
/******************************************************************************/
static void on_timeslot_start(void) 
{
	uint32_t t, tmin;
	/*
	char s[100];
	uint32_t mmm = ozb_debug_time_get_us(OZB_DEBUG_TIME_CLOCK_DEVEL);
	*/
	/* TODO: Implement an efficient version:
		 In case of a device that is not coordinator we can do:
			- if in CAP do whatever 
			- if in CFP, since I already know when to Tx/Rx I can
			  suspend until that time (manage this!) 
	*/
	current_tslot = NEXT_TSLOT(current_tslot);
	if (current_tslot == OZB_MAC_SUPERFRAME_FIRST_SLOT) {
		if (sf_flags.has_idle) { 	/* Has to go in IDLE? */
			stop_superframe(); 
			return;
		}
		if (ozb_mac_superframe_has_tx_gts()) {
			sf_flags.gts_sending = 0;
			gts_available_bytes = 0;
			cqueue_clear(&ozb_mac_queue_gts);
			/* TODO: has effect? */
			ozb_kal_cancel_activation(MAC_GTS_SEND);
		}
		time_reference = ozb_kal_get_time(); 
		start_beacon_interval();
	} else if (current_tslot == OZB_MAC_SUPERFRAME_FIRST_SLOT + 1) {
		t = ozb_kal_get_time();
		t = TIME32_SUBTRACT(t, time_reference);
		tmin = OZB_MAC_GET_TS(ozb_mac_pib.macSuperframeOrder);
		tmin -= OZB_MAC_GET_TS(ozb_mac_pib.macSuperframeOrder) >> 2;
		if (t < tmin) { /* t=<TS_1-TS_0>,  tmin=3/4<TS_size> */
			current_tslot = OZB_MAC_SUPERFRAME_FIRST_SLOT;
			return;
		}
	}
	if (ozb_mac_pib.macGTSPermit == 0)
		return;
	if (current_tslot == ozb_mac_gts_stat.first_cfp_tslot) {
		ozb_mac_status.sf_context = OZB_MAC_SF_CFP;
		if (ozb_mac_status.is_pan_coordinator || 
		    ozb_mac_status.is_coordinator) {
			/* TODO: simplified version: 
				 coordinator can only receive in CFP -> RX ON 				*/
			ozb_radio_phy_set_rx_on(); /* TODO:Raise error if < 0 */
		} 
	}
	if (ozb_mac_superframe_has_tx_gts() && 
            current_tslot == ozb_mac_gts_stat.tx_start_tslot) {
		sf_flags.gts_sending = 1;
		time_reference = (ozb_mac_gts_stat.tx_length *
			       OZB_MAC_GET_TS(ozb_mac_pib.macSuperframeOrder)) +
			       ozb_kal_get_time();
		ozb_kal_set_activation(MAC_GTS_SEND, OZB_MAC_LIFS_PERIOD, 0);
	} else if (ozb_mac_superframe_has_tx_gts() && 
		   current_tslot >= ozb_mac_gts_stat.tx_start_tslot + 
		   ozb_mac_gts_stat.tx_length) {
		sf_flags.gts_sending = 0;
		gts_available_bytes = 0;
		cqueue_clear(&ozb_mac_queue_gts);
		ozb_kal_cancel_activation(MAC_GTS_SEND);/* TODO: has effect? */
	}
	/*
	sprintf(s, "DEVICE: slot=%u  Dck=%lu  ck=%lu ref_ck=%lu  t=%lu", 
		current_tslot, mmm-test_time, mmm, time_reference, t); 
	ozb_debug_print(s);
	*/
}

static void before_timeslot_start(void) 
{
	/*
	char s[100];
	uint32_t mmm = ozb_debug_time_get_us(OZB_DEBUG_TIME_CLOCK_DEVEL);
	*/
	if (NEXT_TSLOT(current_tslot) == OZB_MAC_SUPERFRAME_FIRST_SLOT) { 
		/* Is before the BI? */
		if (sf_flags.wait_sf_end == OZB_FALSE)
			before_beacon_interval();
			/* TODO: if something must be done before first slot,
				 that is the place!! */
		return;
	}
	/*
	sprintf(s, "DEVICE: before slot = %u, Dck%lu, ck=%lu", 
		NEXT_TSLOT(current_tslot), mmm-test_time, mmm);
	ozb_debug_print(s);
	test_time = mmm;
	*/
}

static void on_backoff_period_start(void) 
{
	/* TODO: this task can be stopped after the CAP! */
	/*
	if (ozb_mac_status.sf_context != OZB_MAC_SF_CAP)
		return; 
	*/
}

static void on_gts_send(void)
{
	struct ozb_mac_frame_t *frame;
	uint32_t t;

	char s[100];
	if (!sf_flags.gts_sending) {
/*
		sprintf(s,"DEVICE: On GTS SEND -- STOP -- @ %d",current_tslot);
		ozb_debug_print(s);
*/
		return;
	}
/*
	uint32_t mmm = ozb_debug_time_get_us(OZB_DEBUG_TIME_CLOCK_DEVEL);
	sprintf(s, "DEVICE: On GTS SEND  @ %u, %lu", current_tslot, mmm);
	ozb_debug_print(s);
*/
	if (cqueue_is_empty(&ozb_mac_queue_gts)) {
		sf_flags.gts_sending = 0; /* Nothing more to send by now. */
		return;
	}
	frame = (struct ozb_mac_frame_t*) cqueue_pop(&ozb_mac_queue_gts);
	if (frame == 0) 
		return; 
	/* TODO: send data with phy! */
	if (!is_in_tx_gts()) /* Check if meanwhile the GTS is no longer valid */
		return; /* TODO: notify somehow the packet drop */
LATEbits.LATE0 = 1;
	if (ozb_radio_phy_send_now(frame->mpdu, frame->mpdu_size) == 
	    						OZB_RADIO_ERR_NONE)
		ozb_MCPS_DATA_confirm(frame->msdu_handle, OZB_MAC_SUCCESS, 0);
	/*
	else 
		TODO: how to notify in case of error? if exists!
	*/
	/* TODO: Add extra "protection" tick (4) */
	//tmin = OZB_MAC_GET_TS(ozb_mac_pib.macSuperframeOrder);
	//tmin -= OZB_MAC_GET_TS(ozb_mac_pib.macSuperframeOrder) >> 2;
	//if (t < tmin) { /* t=<TS_1-TS_0>,  tmin=3/4<TS_size> */
	//	current_tslot = OZB_MAC_SUPERFRAME_FIRST_SLOT;
	//	return;
	//}
	if (frame->mpdu_size > OZB_aMaxSIFSFrameSize) /* TODO: check!!!! */
		ozb_kal_set_activation(MAC_GTS_SEND, OZB_MAC_LIFS_PERIOD, 0);
	else
		ozb_kal_set_activation(MAC_GTS_SEND, OZB_MAC_SIFS_PERIOD, 0);
LATEbits.LATE0 = 0;
}

/******************************************************************************/
/*                      MAC Tasks General Functions                           */
/******************************************************************************/
int8_t ozb_mac_superframe_init(void)
{
	int8_t retv = 1;

	if (ozb_mac_status.sf_initialized)
		return 1;
	retv = ozb_kal_init(320); /* TODO: this comes from the PHY, because
	it's just the duration of the aUnitBackoffPeriod = 20 symbols so...
	backoff_period = aUnitBackoffPeriod x bit_per_symbols / bandwidth  
		       = 20 x 4bits / 250000 bps = 320 microseconds .
	How can we make this general? Where can this change? When? */
	if (retv < 0)
		return retv;
	retv = ozb_kal_set_body(MAC_TIMESLOT, on_timeslot_start);
	if (retv < 0)
		return retv;
	retv = ozb_kal_set_body(MAC_BEFORE_TIMESLOT, before_timeslot_start);
	if (retv < 0)
		return retv;
	retv = ozb_kal_set_body(MAC_BACKOFF_PERIOD, on_backoff_period_start);
	if (retv < 0)
		return retv;
	retv = ozb_kal_set_body(MAC_GTS_SEND, on_gts_send);
	if (retv < 0)
		return retv;
	ozb_mac_status.sf_initialized = OZB_TRUE;
	gts_lifs_bytes = btick_to_bytes(OZB_MAC_LIFS_PERIOD);
	gts_sifs_bytes = btick_to_bytes(OZB_MAC_SIFS_PERIOD);
TRISEbits.TRISE0 = 0;
LATEbits.LATE0 = 0;
	return 1;
} 

void ozb_mac_superframe_start(uint32_t offset)
{
	/* TODO: check this behaviour*/
	if (ozb_mac_status.track_beacon) {
		ozb_radio_phy_set_rx_on(); /* TODO: Raise error if < 0 */
		ozb_debug_time_start(OZB_DEBUG_TIME_CLOCK_BI);
		return;
	}	
	ozb_debug_time_start(OZB_DEBUG_TIME_CLOCK_DEVEL);
	ozb_debug_time_start(OZB_DEBUG_TIME_CLOCK_BI);
	current_tslot = OZB_MAC_SUPERFRAME_LAST_SLOT;
	sf_flags.wait_sf_end = OZB_FALSE;
	sf_flags.has_idle = OZB_FALSE;
	if (ozb_mac_status.is_pan_coordinator || ozb_mac_status.is_coordinator)
		start_activations(offset);
	/* TODO: do I need this (a before_BI before the first BCN) in device? 
	else
		ozb_kal_set_activation(MAC_BEFORE_TIMESLOT, 0, 0);
	*/
} 

void ozb_mac_superframe_stop(void) 
{
	stop_activations();
}

void ozb_mac_superframe_resync(void)
{
	/*
	char s[100];
	uint32_t mmm = ozb_debug_time_get_us(OZB_DEBUG_TIME_CLOCK_DEVEL);
	*/
	ozb_mac_status.count_beacon_lost = 0;
	if (!ozb_mac_status.track_beacon)
		return;
	resync_activations();
	/*
	sprintf(s, "BCN -> SF Resync: Dck=%lu, ck=%lu, %u, %u", 
		mmm - test_time, mmm,
		(uint16_t) ozb_mac_pib.macBeaconOrder,
		(uint16_t) ozb_mac_pib.macSuperframeOrder);
	ozb_debug_print(s);
	test_time = mmm;
	*/
}


void ozb_mac_superframe_gts_wakeup(void) 
{
	if (!sf_flags.gts_sending && ozb_mac_gts_stat.tx_length != 0 &&
	    current_tslot == ozb_mac_gts_stat.tx_start_tslot) {
		sf_flags.gts_sending = 1;
		ozb_kal_set_activation(MAC_GTS_SEND, 0, 0);
	}
}

uint8_t ozb_mac_superframe_check_gts(uint8_t length)
{
	uint32_t x = gts_available_bytes;
/*
char s[100];
*/
	/* TODO: use the extra bytes for protection??? in this case 10 */

	if (gts_available_bytes < length + 10)
		return 0; 
	if (is_in_tx_gts()) {
		/* x = remaining btick in GTS */
		x = ozb_kal_get_time();
		x = TIME32_SUBTRACT(time_reference, x);
		/* x = remaining bytes in GTS */
		x = btick_to_bytes(x);
/*
sprintf(s,"DEVICE: ####--->>> Remaining Byte =  %lu", x);
ozb_debug_print(s);
*/
		if (x < length + 10) {
			gts_available_bytes = 0;
			return 0;
		}
	}
	gts_available_bytes = x - (length + 10);
	/* x = LISF or SIFS in bytes */
	x = length < OZB_aMaxSIFSFrameSize ? 
	    gts_sifs_bytes : gts_lifs_bytes;
	gts_available_bytes = gts_available_bytes >= x ?
			      gts_available_bytes - x : 0;
	return 1;

/* TODO Remove following lines if previous are ok! */	
//	if (gts_available_bytes >= length + 10) {
//		gts_available_bytes -= length + 10;
//		/* x = LISF or SIFS in bytes */
//		x = length < OZB_aMaxSIFSFrameSize ? 
//		    gts_sifs_bytes : gts_lifs_bytes;
//		gts_available_bytes = gts_available_bytes >= x ?
//				      gts_available_bytes - x : 0;
//		if (!is_in_tx_gts()) 
//			return 1;
//		/* x = remaining btick in GTS */
//		x = ozb_kal_get_time();
//		x = TIME32_SUBTRACT(time_reference, x);
//		/* x = remaining bytes in GTS */
//		x = btick_to_bytes(x);
//sprintf(s,"DEVICE: ####--->>> Remaining Byte =  %lu", x);
//ozb_debug_print(s);
//		if (x >= length + 10) {
//			gts_available_bytes = x - (length + 10);
//			return 1;
//		} else {
//			gts_available_bytes = 0
//		}
//	}
//	return 0;
}

