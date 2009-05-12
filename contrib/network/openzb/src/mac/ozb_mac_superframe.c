#include <mac/ozb_mac_internal.h>
#include <hal/ozb_radio.h>
#include <kal/ozb_kal.h>
#include <util/ozb_debug.h>

OZB_KAL_TASK(MAC_TIMESLOT, 10);
OZB_KAL_TASK(MAC_BEFORE_TIMESLOT, 10); 
OZB_KAL_TASK(MAC_BACKOFF_PERIOD, 10);
OZB_KAL_TASK(MAC_GTS_SEND, 10);

/******************************************************************************/
/*                          MAC Tasks Private Data                            */
/******************************************************************************/
static uint8_t current_tslot = OZB_MAC_SUPERFRAME_FIRST_SLOT;
static struct {
	unsigned  has_idle : 1;
	unsigned  wait_sf_end : 1;
} sf_flags = {OZB_FALSE, OZB_FALSE};
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
		offset = OZB_MAC_TICKS_BEFORE_TIMESLOT + 1;
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

COMPILER_INLINE void resync_activations(void) 
{
	uint32_t t;

	stop_activations();
	t = OZB_MAC_GET_TS(ozb_mac_pib.macSuperframeOrder);
	ozb_kal_set_activation(MAC_BEFORE_TIMESLOT, 
			       t - OZB_MAC_TICKS_BEFORE_TIMESLOT, t);
	ozb_kal_set_activation(MAC_TIMESLOT, 1, t);
	ozb_kal_set_activation(MAC_BACKOFF_PERIOD, 1, 1);
}

COMPILER_INLINE void start_beacon_interval(void) 
{
	ozb_debug_time_get(OZB_DEBUG_TIME_CLOCK_BI);
	if (ozb_mac_status.is_pan_coordinator || ozb_mac_status.is_coordinator)
		ozb_radio_mac_send_beacon(); /* TODO: parse ret value*/
	if (ozb_mac_pib.macSuperframeOrder < ozb_mac_pib.macBeaconOrder) {
		sf_flags.has_idle = OZB_TRUE;
		sf_flags.wait_sf_end = OZB_TRUE;
	}
	ozb_mac_status.sf_context = OZB_MAC_SF_CAP;
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
	current_tslot = OZB_MAC_SUPERFRAME_FIRST_SLOT;
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
	char s[100];
	uint32_t mmm = ozb_debug_time_get_us(OZB_DEBUG_TIME_CLOCK_DEVEL);
	/* TODO: perform GTS send/receive with appropriate IFS */
	/* TODO: Implement an efficient version:
		 In case of a device that is not coordinator we can do:
			- if in CAP do whatever 
			- if in CFP, since I already know when to Tx/Rx I can
			  suspend until that time (manage this!) 
	*/
	if (current_tslot == OZB_MAC_SUPERFRAME_FIRST_SLOT) {
		if (sf_flags.has_idle) { 	/* Has to go in IDLE? */
			stop_superframe(); 
			return;
		}
		start_beacon_interval();
	}
	if (ozb_mac_pib.macGTSPermit == 0)
		goto on_timeslot_start_exit;
goto on_timeslot_start_exit; /* TODO: temporary!! */
	if (current_tslot == ozb_mac_gts_stat.tx_start_tslot)
		ozb_kal_set_activation(MAC_GTS_SEND, 0, 0);
	else if (current_tslot >= ozb_mac_gts_stat.tx_start_tslot + 
						ozb_mac_gts_stat.tx_length)
		ozb_kal_cancel_activation(MAC_GTS_SEND);
	//	perform_cap_send();
	//if (current_tslot >= ozb_mac_gts_stat.tx_tslot && current_tslot < 
	//    ozb_mac_gts_stat.tx_tslot + ozb_mac_gts_stat.tx_length)
	//	perform_cap_send();
	//else if (current_tslot >= ozb_mac_gts_stat.rx_tslot && current_tslot < 
	//	 ozb_mac_gts_stat.rx_tslot + ozb_mac_gts_stat.rx_length)
	//	perform_cap_receive();
on_timeslot_start_exit:
	sprintf(s, "DEVICE: slot=%u  Dck=%lu  ck=%lu "
		"tx_s=%u tx_s=%u rx_s=%u rx_s=%u", 
		current_tslot, mmm-test_time, mmm, 
		(uint16_t) ozb_mac_gts_stat.tx_start_tslot,
		(uint16_t) ozb_mac_gts_stat.tx_length,
		(uint16_t) ozb_mac_gts_stat.rx_start_tslot,
		(uint16_t) ozb_mac_gts_stat.rx_length);
	ozb_debug_print(s);
	current_tslot = (current_tslot + 1) % 16;
}

static void before_timeslot_start(void) 
{
	uint32_t mmm = ozb_debug_time_get_us(OZB_DEBUG_TIME_CLOCK_DEVEL);
	if (current_tslot == OZB_MAC_SUPERFRAME_FIRST_SLOT) { 
		/* Is before the BI? */
		if (sf_flags.wait_sf_end == 0)
			before_beacon_interval();
			/* TODO: if something must be done before first slot,
				 that is the place!! */
		return;
	}
	char s[100];
	sprintf(s, "DEVICE: before slot = %u, Dck%lu, ck=%lu", current_tslot, 
		mmm-test_time, mmm);
	ozb_debug_print(s);
	test_time = mmm;
}

static void on_backoff_period_start(void) 
{
	/*
	if (ozb_mac_status.sf_context != OZB_MAC_SF_CAP)
		return; 
	*/
}

static void on_gts_send(void)
{
	/* Send with sifs or lifs !! */
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
	if (!(ozb_mac_status.is_pan_coordinator || 
	      ozb_mac_status.is_coordinator))
		return;
	ozb_debug_time_start(OZB_DEBUG_TIME_CLOCK_DEVEL);
	ozb_debug_time_start(OZB_DEBUG_TIME_CLOCK_BI);
	current_tslot = OZB_MAC_SUPERFRAME_FIRST_SLOT;
	sf_flags.wait_sf_end = OZB_FALSE;
	sf_flags.has_idle = OZB_FALSE;
	start_activations(offset);
} 

void ozb_mac_superframe_stop(void) 
{
	stop_activations();
}

void ozb_mac_superframe_resync(void)
{
	uint32_t mmm = ozb_debug_time_get_us(OZB_DEBUG_TIME_CLOCK_DEVEL);
	if (!ozb_mac_status.track_beacon)
		return;
	resync_activations();
	/* TODO: realign the task activation for the superframe! */
	char s[100];
	sprintf(s, "BCN -> SF Resync: Dck=%lu, ck=%lu, %u, %u", 
		mmm - test_time, mmm,
		(uint16_t) ozb_mac_pib.macBeaconOrder,
		(uint16_t) ozb_mac_pib.macSuperframeOrder);
	ozb_debug_print(s);
	test_time = mmm;
}







#ifdef compila_merda_di_ricardo

void start_gts_send()
{
	
	if(!GTS_TRANSMITING && current_time_slot >= s_GTSss && current_time_slot <= s_GTSss + s_GTS_length && gts_send_buffer_count > 0 && on_sync == 1){
		GTS_TRANSMITING=1;
		//send_gts_after_interframearrival();
		SetRelAlarm(interframespace_firedAlarm, 1, 15);			
	}	
	return;	
}

//void send_gts_after_interframearrival(){
TASK(send_gts_after_interframearrivalTask){
	
	//if(current_time_slot >= s_GTSss && current_time_slot <= s_GTSss + s_GTS_length && gts_send_buffer_count > 0 && on_sync == 1)
		//if (gts_send_buffer_count && check_gts_send_conditions(gts_send_buffer[gts_send_buffer_msg_out].length) == 1 )			
		//while(gts_send_buffer_count)
		//if (gts_send_buffer_count)
		if(current_time_slot >= s_GTSss && current_time_slot < s_GTSss + s_GTS_length && gts_send_buffer_count > 0)
		{
			
			
			//ee_console_out_str("\nbuf\n");
			//ee_console_out16_radix(gts_send_buffer_count,16);
			//PD_DATA_request	
			//gts_send_buffer[gts_send_buffer_msg_out].data[11+8]=current_time_slot;
			//gts_send_buffer[gts_send_buffer_msg_out].data[12+8]=gts_send_buffer_count;
			//gts_send_buffer[gts_send_buffer_msg_out].data[13+8]=gts_send_buffer_msg_out;
			//gts_send_buffer[gts_send_buffer_msg_out].data[14+8]=mac_PIB.macShortAddress;
			//gts_send_buffer[gts_send_buffer_msg_out].data[15+8]=(EE_UINT8)beaconnumber>>8;
			//gts_send_buffer[gts_send_buffer_msg_out].data[16+8]=(EE_UINT8)beaconnumber;
			
			PD_DATA_request(gts_send_buffer[gts_send_buffer_msg_out].length,(EE_UINT8 *)&gts_send_buffer[gts_send_buffer_msg_out]);
		
			//ee_console_out16_radix(gts_send_buffer[gts_send_buffer_msg_out].length,16);
			//ee_console_out16_radix(gts_send_buffer[gts_send_buffer_msg_out].data[6],16);
			
			gts_send_buffer_count --;
			gts_send_buffer_msg_out++;

			if (gts_send_buffer_msg_out == GTS_SEND_BUFFER_SIZE)
				gts_send_buffer_msg_out=0;

			
			
//				if (gts_send_buffer_count > 0)
//					gts_send_pending_data = 1;	
//					
//				if(gts_send_buffer_count == 0){
//					GTS_TRANSMITING=0;
//					break;					
//				}else{
//						//SetRelAlarm(interframespace_firedAlarm, 15, 0);
//					EE_UINT16 k = 0;
//					for(k = 0; k < 60000; k++);
//					//gts_send_buffer_count --;
//					//gts_send_buffer_msg_out++;
//				}
		}
		
		if(gts_send_buffer_count <= 0){
			CancelAlarm(interframespace_firedAlarm);
			GTS_TRANSMITING=0;
		}/*else{
			SetRelAlarm(interframespace_firedAlarm, 300, 0);
			//gts_send_buffer_count --;
			//gts_send_buffer_msg_out++;
		}*/		
}

#endif
