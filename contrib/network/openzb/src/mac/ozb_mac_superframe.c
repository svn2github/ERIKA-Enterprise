#include <mac/ozb_mac_internal.h>
#include <hal/ozb_radio.h>
#include <osal/ozb_osal.h>
#include <util/ozb_debug.h>
#ifdef OZB_DEBUG_LOG
#include <stdio.h> //TODO: REMOVE together with the sprintf() !!!!!
#endif

/* TODO: remove all the debug parts or put them under ifdef!!! */

/* */
#define OZB_MAC_SF_FIRST_SLOT 0
#define OZB_MAC_SF_LAST_SLOT 15

//#define SPRINTF sprintf

/******************************************************************************/
/*                          MAC Tasks Private Data                            */
/******************************************************************************/
static uint8_t current_timeslot_id = 0;
static struct {
	unsigned  has_idle : 1;
	unsigned  wait_sf_end : 1;
} sf_flags = {0, 0};

/******************************************************************************/
/*                      MAC Tasks Private Functions                           */
/******************************************************************************/

/******************************************************************************/
/*                             MAC Layer TASKs                                */
/******************************************************************************/
//OZB_OSAL_TASK(MAC_BEACON_INTERVAL, 10);
//OZB_OSAL_TASK(MAC_BEFORE_BEACON_INTERVAL, 10);
//OZB_OSAL_TASK(MAC_SUPERFRAME_END, 10);
OZB_OSAL_TASK(MAC_TIMESLOT, 10);
OZB_OSAL_TASK(MAC_BEFORE_TIMESLOT, 10); // FIXME: manage this is a problem!!
OZB_OSAL_TASK(MAC_BACKOFF_PERIOD, 10);

static void on_beacon_start(void) 
{
	char s[100];
	uint32_t ticks =  ozb_debug_time_get_us(OZB_DEBUG_TIME_CLOCK_BI);
	ozb_debug_time_get(OZB_DEBUG_TIME_CLOCK_BI);
	/* TODO: parse ret value*/
	ozb_radio_send_beacon();
	if (ozb_mac_pib.macSuperframeOrder < ozb_mac_pib.macBeaconOrder) {
		sf_flags.has_idle = 1;
		sf_flags.wait_sf_end = 1;
	}

	ozb_mac_status.sf_context = OZB_MAC_SF_CAP;
	ozb_debug_print("OZB_TASK: BI Start!");
	sprintf(s, "    CLOCK=%lu", ticks); 
	ozb_debug_print(s);
}

static void on_superframe_end(void) 
{
	char s[100];
	uint32_t t;
	uint32_t ticks =  ozb_debug_time_get_us(OZB_DEBUG_TIME_CLOCK_DEVEL);

	ozb_mac_status.sf_context = OZB_MAC_SF_IDLE;
	sf_flags.wait_sf_end = 0;
	ozb_osal_cancel_activation(MAC_TIMESLOT);
	ozb_osal_cancel_activation(MAC_BEFORE_TIMESLOT);
	ozb_osal_cancel_activation(MAC_BACKOFF_PERIOD);
	t = OZB_MAC_GET_BI(ozb_mac_pib.macBeaconOrder) - 
	    OZB_MAC_GET_SD(ozb_mac_pib.macSuperframeOrder);
	ozb_mac_sf_start(t);
	ozb_debug_print("OZB_TASK: SF End!");
	/* chris: TODO: in future stop the tasks: 
			on_ts_start, before_ts_start, on_backoff_period_start 
		  	NOTE: the backoff_period can be stopped on CAP end!! */
	sprintf(s, "    TS=%u  CLOCK=%lu", current_timeslot_id, ticks);
	ozb_debug_print(s);
}

static void on_timeslot_start(void) 
{
	char s[100];
	uint32_t ticks =  ozb_debug_time_get_us(OZB_DEBUG_TIME_CLOCK_DEVEL);

	if (current_timeslot_id == 0) {
		if (sf_flags.has_idle) { 
			on_superframe_end(); 
			return;
		}
		on_beacon_start();
	}
	ozb_debug_print("OZB_TASK: TS Start!");
	if (ozb_mac_status.sf_context == OZB_MAC_SF_IDLE)
		return; /* TODO: in future stop the activations on_sf_end */
	sprintf(s, "    TS=%u  CLOCK=%lu", current_timeslot_id, ticks);
	ozb_debug_print(s);
	current_timeslot_id = (current_timeslot_id + 1) % 16;
}

static void before_beacon_start(void)
{
	ozb_mpdu_t bcn;
	uint8_t bcn_size;
	uint8_t str[OZB_DEBUG_STAT_STRLEN];

	bcn_size = ozb_mac_create_beacon(bcn);
	if (bcn_size != 0) {
		/* TODO: parse error! */
		ozb_radio_store_beacon(bcn, bcn_size);
		ozb_debug_print("OZB_TASK: Before BI... bcn saved");
	}

	ozb_debug_stat2str(str);
	ozb_debug_write(str, OZB_DEBUG_STAT_STRLEN);
	ozb_debug_print("OZB_TASK: Before BI");
}

static void before_timeslot_start(void) 
{
	char s[100];
	uint32_t ticks =  ozb_debug_time_get_us(OZB_DEBUG_TIME_CLOCK_DEVEL);
	
	//if (ozb_mac_status.sf_context == OZB_MAC_SF_IDLE)
	//	return; /* TODO: in future stop the activations on_sf_end */
	if (current_timeslot_id == 0) {
		if (/*sf_flags.has_idle && */sf_flags.wait_sf_end) {
			ozb_debug_print("OZB_TASK: TS _LOCK");
			return;
		}
		before_beacon_start();
		return;
	}
	ozb_debug_print("OZB_TASK: Before TS Start!");
	sprintf(s, "    TS=%u  CLOCK=%lu", current_timeslot_id, ticks);
	ozb_debug_print(s);
}

static void on_backoff_period_start(void) 
{
	//uint32_t ticks =  ozb_debug_time_get_us();
	//ozb_debug_print("OZB_TASK: Backoff Period Start!");
	if (ozb_mac_status.sf_context != OZB_MAC_SF_CAP)
		return; /* TODO: in future stop the activations on_sf_end */
}

/******************************************************************************/
/*                      MAC Tasks General Functions                           */
/******************************************************************************/
int8_t ozb_mac_sf_init(void)
{
	int8_t retv = 1;

	if (ozb_mac_status.sf_initialized)
		return 1;
	retv = ozb_osal_init(320); /* TODO: this comes from the PHY, because
	it's just the duration of the aUnitBackoffPeriod = 20 symbols so...
	backoff_period = aUnitBackoffPeriod x bit_per_symbols / bandwidth  
		       = 20 x 4bits / 250000 bps = 320 microseconds .
	How can we make this general? Where can this change? When? */
	if (retv < 0)
		return retv;
//	retv = ozb_osal_set_body(MAC_BEACON_INTERVAL, on_beacon_start);
//	if (retv < 0)
//		return retv;
//	retv=ozb_osal_set_body(MAC_BEFORE_BEACON_INTERVAL, before_beacon_start);
//	if (retv < 0)
//		return retv;
//	retv = ozb_osal_set_body(MAC_SUPERFRAME_END, on_superframe_end);
//	if (retv < 0)
//		return retv;
	retv = ozb_osal_set_body(MAC_TIMESLOT, on_timeslot_start);
	if (retv < 0)
		return retv;
	retv = ozb_osal_set_body(MAC_BEFORE_TIMESLOT, before_timeslot_start);
	if (retv < 0)
		return retv;
	retv = ozb_osal_set_body(MAC_BACKOFF_PERIOD, on_backoff_period_start);
	if (retv < 0)
		return retv;
	ozb_mac_status.sf_initialized = 1;
	return 1;
} 

void ozb_mac_sf_start(uint32_t offset)
{
	uint32_t t;
	char s[100];

	ozb_debug_print("ozb_mac_sf_start: ");
	ozb_debug_time_start(OZB_DEBUG_TIME_CLOCK_DEVEL);
	ozb_debug_time_start(OZB_DEBUG_TIME_CLOCK_BI);

	current_timeslot_id = 0;
	sf_flags.wait_sf_end = 0;
	sf_flags.has_idle = 0;
	sprintf(s, "    OFFSET=%lu", offset);
	ozb_debug_print(s);
	if (offset == 0)
		offset = OZB_MAC_TICKS_BEFORE_TIMESLOT;
	//t = OZB_MAC_GET_BI(ozb_mac_pib.macBeaconOrder);
	//ozb_osal_set_activation(MAC_BEACON_INTERVAL, offset, t);
	t = OZB_MAC_GET_TS(ozb_mac_pib.macSuperframeOrder);
	ozb_osal_set_activation(MAC_BEFORE_TIMESLOT, 
				offset - OZB_MAC_TICKS_BEFORE_TIMESLOT, t); 
	ozb_osal_set_activation(MAC_TIMESLOT, offset, t);
	ozb_osal_set_activation(MAC_BACKOFF_PERIOD, offset, 1);
} 

void ozb_mac_sf_stop(void) 
{
	/* FIXME: now I'm ignoring the return values! */
//	ozb_osal_cancel_activation(MAC_BEACON_INTERVAL);
//	ozb_osal_cancel_activation(MAC_BEFORE_BEACON_INTERVAL);
//	ozb_osal_cancel_activation(MAC_SUPERFRAME_END);
	ozb_osal_cancel_activation(MAC_TIMESLOT);
	ozb_osal_cancel_activation(MAC_BEFORE_TIMESLOT);
	ozb_osal_cancel_activation(MAC_BACKOFF_PERIOD);
}

void ozb_mac_sf_resync(void)
{
}
