#include <mac/ozb_mac_internal.h>
#include <hal/ozb_radio.h>
#include <kal/ozb_kal.h>
#include <util/ozb_debug.h>

/******************************************************************************/
/*                          MAC Tasks Private Data                            */
/******************************************************************************/
static uint8_t current_timeslot_id = OZB_MAC_SUPERFRAME_FIRST_SLOT;
static struct {
	unsigned  has_idle : 1;
	unsigned  wait_sf_end : 1;
} sf_flags = {OZB_FALSE, OZB_FALSE};

/******************************************************************************/
/*                      MAC Tasks Private Functions                           */
/******************************************************************************/
static void start_beacon_interval(void) 
{
	ozb_debug_time_get(OZB_DEBUG_TIME_CLOCK_BI);
	ozb_radio_mac_send_beacon(); /* TODO: parse ret value*/
	if (ozb_mac_pib.macSuperframeOrder < ozb_mac_pib.macBeaconOrder) {
		sf_flags.has_idle = OZB_TRUE;
		sf_flags.wait_sf_end = OZB_TRUE;
	}
	ozb_mac_status.sf_context = OZB_MAC_SF_CAP;
}

static void stop_superframe(void) 
{
	uint32_t t;

	ozb_mac_status.sf_context = OZB_MAC_SF_IDLE;
	sf_flags.wait_sf_end = OZB_FALSE;
	ozb_kal_cancel_activation(MAC_TIMESLOT);
	ozb_kal_cancel_activation(MAC_BEFORE_TIMESLOT);
	ozb_kal_cancel_activation(MAC_BACKOFF_PERIOD);
	t = OZB_MAC_GET_BI(ozb_mac_pib.macBeaconOrder) - 
	    OZB_MAC_GET_SD(ozb_mac_pib.macSuperframeOrder);
	ozb_mac_superframe_start(t);
}

static void before_beacon_interval(void)
{
	uint8_t str[OZB_DEBUG_STAT_STRLEN];

	ozb_radio_mac_create_beacon(); /* TODO: parse error! */
	ozb_debug_stat2str(str);
	ozb_debug_write(str, OZB_DEBUG_STAT_STRLEN);
}

/******************************************************************************/
/*                             MAC Layer TASKs                                */
/******************************************************************************/
OZB_KAL_TASK(MAC_TIMESLOT, 10);
OZB_KAL_TASK(MAC_BEFORE_TIMESLOT, 10); 
OZB_KAL_TASK(MAC_BACKOFF_PERIOD, 10);

static void on_timeslot_start(void) 
{
	/* TODO: perform GTS send/receive with appropriate IFS */
	if (current_timeslot_id == OZB_MAC_SUPERFRAME_FIRST_SLOT) {
		if (sf_flags.has_idle) { 	/* Has to go in IDLE? */
			stop_superframe(); 
			return;
		}
		start_beacon_interval();
	}
	current_timeslot_id = (current_timeslot_id + 1) % 16;
}

static void before_timeslot_start(void) 
{
	if (current_timeslot_id == OZB_MAC_SUPERFRAME_FIRST_SLOT) { 
		/* Is before the BI? */
		if (sf_flags.wait_sf_end == OZB_MAC_SUPERFRAME_FIRST_SLOT)
			before_beacon_interval();
		return;
	}
}

static void on_backoff_period_start(void) 
{
	/*
	if (ozb_mac_status.sf_context != OZB_MAC_SF_CAP)
		return; 
	*/
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
	ozb_mac_status.sf_initialized = OZB_TRUE;
	return 1;
} 

void ozb_mac_superframe_start(uint32_t offset)
{
	uint32_t t;

	ozb_debug_time_start(OZB_DEBUG_TIME_CLOCK_DEVEL);
	ozb_debug_time_start(OZB_DEBUG_TIME_CLOCK_BI);

	if (offset == 0)
		offset = OZB_MAC_TICKS_BEFORE_TIMESLOT;
	current_timeslot_id = OZB_MAC_SUPERFRAME_FIRST_SLOT;
	sf_flags.wait_sf_end = OZB_FALSE;
	sf_flags.has_idle = OZB_FALSE;
	t = OZB_MAC_GET_TS(ozb_mac_pib.macSuperframeOrder);
	ozb_kal_set_activation(MAC_BEFORE_TIMESLOT, 
				offset - OZB_MAC_TICKS_BEFORE_TIMESLOT, t); 
	ozb_kal_set_activation(MAC_TIMESLOT, offset, t);
	ozb_kal_set_activation(MAC_BACKOFF_PERIOD, offset, 1);
} 

void ozb_mac_superframe_stop(void) 
{
	/* FIXME: now I'm ignoring the return values! */
	ozb_kal_cancel_activation(MAC_TIMESLOT);
	ozb_kal_cancel_activation(MAC_BEFORE_TIMESLOT);
	ozb_kal_cancel_activation(MAC_BACKOFF_PERIOD);
}

void ozb_mac_superframe_resync(void)
{
}
