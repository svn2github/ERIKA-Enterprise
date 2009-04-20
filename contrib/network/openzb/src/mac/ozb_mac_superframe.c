#include <mac/ozb_mac_internal.h>
#include <osal/ozb_osal.h>
#include <util/ozb_debug.h>
#ifdef OZB_DEBUG_LOG
#include <stdio.h> //TODO: REMOVE together with the sprintf() !!!!!
#endif

/* TODO: remove all the debug parts or put them under ifdef!!! */

/******************************************************************************/
/*                          MAC Tasks Private Data                            */
/******************************************************************************/

/******************************************************************************/
/*                      MAC Tasks Private Functions                           */
/******************************************************************************/
static uint8_t timeslot_id = 0;

/******************************************************************************/
/*                             MAC Layer TASKs                                */
/******************************************************************************/
OZB_OSAL_TASK(MAC_BEACON_INTERVAL, 10);
OZB_OSAL_TASK(MAC_BEFORE_BEACON_INTERVAL, 10);
OZB_OSAL_TASK(MAC_SUPERFRAME_END, 10);
OZB_OSAL_TASK(MAC_TIMESLOT, 10);
OZB_OSAL_TASK(MAC_BEFORE_TIMESLOT, 10);
OZB_OSAL_TASK(MAC_BACKOFF_PERIOD, 10);

static void on_beacon_start(void) 
{
	uint32_t t;
	char s[100];
	uint32_t ticks =  ozb_debug_time_tick2us(ozb_debug_time_tock());

	ozb_debug_print("OZB_TASK: BI Start!");
	timeslot_id = 0;
	/* Calculate BI */
	t = (1UL << ozb_mac_pib.macBeaconOrder) * 
	    OZB_aBaseSuperframeDuration_ticks;
	ozb_osal_set_activation(MAC_BEFORE_BEACON_INTERVAL, 
				t - OZB_MAC_TICKS_BEFORE_BI, 0);
	sprintf(s, "    BI_ticks=%lu  CLOCK=%lu", t, ticks); 
	ozb_debug_print(s);
	if (ozb_mac_pib.macSuperframeOrder < ozb_mac_pib.macBeaconOrder) {
		/* Calculate SD, if required */
		t =  (1UL << ozb_mac_pib.macSuperframeOrder) * 
		     OZB_aBaseSuperframeDuration_ticks;
		ozb_osal_set_activation(MAC_SUPERFRAME_END, t, 0);
		sprintf(s, "    on SO < BO: SD_ticks=%lu", t);
		ozb_debug_print(s);
	}
	/* Calculate TS 
	TODO: in the future when having the superframe task, it is worth to
	      shutdown in this case the following tasks and reactivate them
	      here, at the beginning of the next superframe.

	t = t / OZB_aNumSuperframeSlots;
	ozb_osal_set_activation(MAC_TIMESLOT, offset, t);
	ozb_osal_set_activation(MAC_BEFORE_TIMESLOT, offset, 
				t - OZB_MAC_TICKS_BEFORE_TIMESLOT);
	ozb_osal_set_activation(MAC_BACKOFF_PERIOD, offset, 1);
	*/
	ozb_mac_status.sf_context = OZB_MAC_SF_CAP;
}

static void before_beacon_start(void) 
{
	char s[100];
	uint32_t ticks =  ozb_debug_time_tick2us(ozb_debug_time_tock());

	ozb_debug_print("OZB_TASK: Before BI Start!");
	sprintf(s, "    CLOCK=%lu", ticks);
	ozb_debug_print(s);
}

static void on_superframe_end(void) 
{
	char s[100];
	uint32_t ticks =  ozb_debug_time_tick2us(ozb_debug_time_tock());

	ozb_debug_print("OZB_TASK: SF End!");
	/* chris: TODO: in future stop the tasks: 
			on_ts_start, before_ts_start, on_backoff_period_start 
		  	NOTE: the backoff_period can be stopped on CAP end!! */
	ozb_mac_status.sf_context = OZB_MAC_SF_IDLE;
	sprintf(s, "    TS=%u  CLOCK=%lu", timeslot_id, ticks);
	ozb_debug_print(s);
}

static void on_timeslot_start(void) 
{
	char s[100];
	uint32_t ticks =  ozb_debug_time_tick2us(ozb_debug_time_tock());
	
	ozb_debug_print("OZB_TASK: TS Start!");
	if (ozb_mac_status.sf_context == OZB_MAC_SF_IDLE)
		return; /* TODO: in future stop the activations on_sf_end */
	sprintf(s, "    TS=%u  CLOCK=%lu", timeslot_id, ticks);
	ozb_debug_print(s);
	timeslot_id++;
}

static void before_timeslot_start(void) 
{
	char s[100];
	uint32_t ticks =  ozb_debug_time_tick2us(ozb_debug_time_tock());
	
	ozb_debug_print("OZB_TASK: Before TS Start!");
	if (ozb_mac_status.sf_context == OZB_MAC_SF_IDLE)
		return; /* TODO: in future stop the activations on_sf_end */
	sprintf(s, "    TS=%u  CLOCK=%lu", timeslot_id, ticks);
	ozb_debug_print(s);
}

static void on_backoff_period_start(void) 
{
	//uint32_t ticks =  ozb_debug_time_tick2us(ozb_debug_time_tock());
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
	retv = ozb_osal_set_body(MAC_BEACON_INTERVAL, on_beacon_start);
	if (retv < 0)
		return retv;
	retv=ozb_osal_set_body(MAC_BEFORE_BEACON_INTERVAL, before_beacon_start);
	if (retv < 0)
		return retv;
	retv = ozb_osal_set_body(MAC_SUPERFRAME_END, on_superframe_end);
	if (retv < 0)
		return retv;
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

	ozb_debug_time_tick();
	ozb_debug_print("ozb_mac_sf_start: ");

	if (offset == 0)
		offset = OZB_MAC_TICKS_BEFORE_TIMESLOT;
	/* FIXME: now I'm ignoring the return values! */
	t = (1UL << ozb_mac_pib.macBeaconOrder) * 
	    OZB_aBaseSuperframeDuration_ticks;
	ozb_osal_set_activation(MAC_BEACON_INTERVAL, offset, t);
	sprintf(s, "    BI_ticks=%lu", t);
	ozb_debug_print(s);
	t = ozb_mac_pib.macSuperframeOrder;
	sprintf(s, "    SO=%lu", t);
	ozb_debug_print(s);
	t = (1UL << ozb_mac_pib.macSuperframeOrder) * 
	    OZB_aBaseSuperframeDuration_ticks;
	sprintf(s, "    SF_ticks=%lu", t);
	ozb_debug_print(s);
	t = t / OZB_aNumSuperframeSlots;
	sprintf(s, "    TS_ticks=%lu", t);
	ozb_debug_print(s);
	ozb_osal_set_activation(MAC_BEFORE_TIMESLOT, 
				offset - OZB_MAC_TICKS_BEFORE_TIMESLOT, t); 
	ozb_osal_set_activation(MAC_TIMESLOT, offset, t);
	ozb_osal_set_activation(MAC_BACKOFF_PERIOD, offset, 1);
} 

void ozb_mac_sf_stop(void) 
{
	/* FIXME: now I'm ignoring the return values! */
	ozb_osal_cancel_activation(MAC_BEACON_INTERVAL);
	ozb_osal_cancel_activation(MAC_BEFORE_BEACON_INTERVAL);
	ozb_osal_cancel_activation(MAC_SUPERFRAME_END);
	ozb_osal_cancel_activation(MAC_TIMESLOT);
	ozb_osal_cancel_activation(MAC_BEFORE_TIMESLOT);
	ozb_osal_cancel_activation(MAC_BACKOFF_PERIOD);
}

void ozb_mac_sf_resync(void)
{
}
