#ifndef __ozb_mac_internal_h__
#define __ozb_mac_internal_h__

#include <mac/ozb_mac.h>
#include <hal/ozb_radio.h>
#include <phy/ozb_phy.h>

#define OZB_aBaseSlotDuration_btick	  3  /**< OZB_aBaseSlotDuration / 
						  OZB_aUnitBackoffPeriod */ 
#define OZB_aBaseSuperframeDuration_btick 48 /**< OZB_aBaseSuperframeDuration / 
						  OZB_aUnitBackoffPeriod */

#define OZB_MAC_GET_BI(bo) ((1UL << (bo)) * OZB_aBaseSuperframeDuration_btick)
#define OZB_MAC_GET_SD(so) ((1UL << (so)) * OZB_aBaseSuperframeDuration_btick)
#define OZB_MAC_GET_TS(so) ((1UL << (so)) * OZB_aBaseSlotDuration_btick)

enum ozb_mac_state_id_t {
	OZB_MAC_SF_OFF 	= 0,	/**< Superframe is not present. */
	OZB_MAC_SF_CAP 	= 1,	/**< Stack in Contention Access Period. */
	OZB_MAC_SF_CFP	= 2,	/**< Stack in Collision Free Period. */
	OZB_MAC_SF_IDLE	= 3, 	/**< Stack in Idle Period. */
};

struct ozb_mac_flags_t {
	unsigned mac_initialized : 1;
	unsigned is_pan_coordinator : 1;
	unsigned is_coordinator : 1;
	unsigned is_associated : 1;
	unsigned beacon_enabled : 1;
	unsigned track_beacon : 1;
	unsigned sf_initialized : 1;
	unsigned sf_context : 2;
};

struct ozb_mac_gts_stat_t {
	unsigned descriptor_count : 3; // TODO: maybe is useless!!!
	unsigned first_cfp_tslot : 4;
	unsigned tx_start_tslot : 4;
	unsigned tx_length : 4;
	unsigned rx_start_tslot : 4;
	unsigned rx_length : 4;
};

extern struct ozb_mac_pib_t ozb_mac_pib;
extern struct ozb_mac_flags_t ozb_mac_status;
extern struct ozb_mac_gts_stat_t ozb_mac_gts_stat;

uint8_t ozb_mac_create_beacon(ozb_mpdu_ptr_t beacon);
void ozb_mac_parse_received_mpdu(uint8_t *psdu, uint8_t len);

int8_t ozb_mac_gts_init(void); 
uint8_t ozb_mac_gts_set_gts_fields(uint8_t *gf);
uint8_t ozb_mac_gts_get_gts_fields(uint8_t *gf);
COMPILER_INLINE void ozb_mac_gts_set_cap_end(uint8_t last_cap_tslot) 
{
	ozb_mac_gts_stat.first_cfp_tslot = last_cap_tslot + 1;
}
COMPILER_INLINE uint8_t ozb_mac_gts_get_cap_end(void) 
{
	return ozb_mac_gts_stat.first_cfp_tslot - 1;
}

int8_t ozb_mac_superframe_init(void);
void ozb_mac_superframe_start(uint32_t offset);
void ozb_mac_superframe_stop(void); 
void ozb_mac_superframe_resync(void);

#endif /* Header Protection */
