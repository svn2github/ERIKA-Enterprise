#ifndef __ozb_mac_internal_h__
#define __ozb_mac_internal_h__

#include <mac/ozb_mac.h>
#include <phy/ozb_phy.h>

#define OZB_aBaseSuperframeDuration_ticks 48 /**< OZB_aBaseSuperframeDuration / 
						  OZB_aUnitBackoffPeriod */

enum ozb_mac_state_id_t {
	OZB_MAC_SF_OFF 	= 0,	/**< Superframe is not present. */
	OZB_MAC_SF_CAP 	= 1,	/**< Stack in Contention Access Period. */
	OZB_MAC_SF_CFP	= 2,	/**< Stack in Collision Free Period. */
	OZB_MAC_SF_IDLE	= 3, 	/**< Stack in Idle Period. */
};

struct ozb_mac_flags_t {
	unsigned mac_initialized : 1;
	unsigned is_coordinator : 1;
	unsigned beacon_enabled : 1;
	unsigned sf_initialized : 1;
	unsigned sf_context : 2;
};

extern struct ozb_mac_pib_t ozb_mac_pib;
extern struct ozb_mac_flags_t ozb_mac_status;



int8_t ozb_mac_sf_init(void);
void ozb_mac_sf_start(uint32_t offset);
void ozb_mac_sf_stop(void); 
void ozb_mac_sf_resync(void);

#endif /* Header Protection */
