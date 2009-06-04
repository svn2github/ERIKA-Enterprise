#ifndef __ozb_mac_internal_h__
#define __ozb_mac_internal_h__

#include <mac/ozb_mac.h>
#include <hal/ozb_radio.h>
#include <phy/ozb_phy.h>
#include <util/ozb_memory.h>

#define OZB_aBaseSlotDuration_btick	  3  /**< OZB_aBaseSlotDuration / 
						  OZB_aUnitBackoffPeriod */ 
#define OZB_aBaseSuperframeDuration_btick 48 /**< OZB_aBaseSuperframeDuration / 
						  OZB_aUnitBackoffPeriod */
#define OZB_aTurnaroundTime_btick	1 /**< ceiling( OZB_aTurnaroundTime / 
						OZB_aUnitBackoffPeriod ) */

#define OZB_MAC_LIFS_PERIOD		2 /**< 	macMinLIFSPeriod / 
						OZB_aUnitBackoffPeriod */
#define OZB_MAC_SIFS_PERIOD		1 /**<  Greater than macMinSIFSPeriod / 
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
	unsigned count_beacon_lost : 4;
	unsigned sf_initialized : 1;
	unsigned sf_context : 2;
};

struct ozb_mac_gts_stat_t {
	unsigned descriptor_count : 3; // TODO: maybe is useless!!!
	unsigned first_cfp_tslot : 5;
	unsigned tx_start_tslot : 4;
	unsigned tx_length : 4;
	unsigned rx_start_tslot : 4;
	unsigned rx_length : 4;
};


extern struct ozb_mac_pib_t ozb_mac_pib;
extern struct ozb_mac_flags_t ozb_mac_status;
extern struct ozb_mac_gts_stat_t ozb_mac_gts_stat;
extern cqueue_t ozb_mac_queue_cap;
extern cqueue_t ozb_mac_queue_gts;


uint8_t ozb_mac_create_beacon(ozb_mpdu_ptr_t beacon);
void ozb_mac_parse_received_mpdu(uint8_t *psdu, uint8_t len);
void ozb_mac_perform_data_request(uint8_t src_mode, uint8_t dst_mode,
				  uint16_t dst_panid, void *dst_addr,
				  uint8_t len, uint8_t *payload,
				  uint8_t handle, uint8_t tx_opt /*,
				  uint8_t sec_lev, uint8_t key_id_mode,
				  uint8_t *key_src, uint8_t key_idx */);

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

COMPILER_INLINE uint8_t ozb_mac_gts_get_cap_size(void)
{
	return ozb_mac_gts_stat.first_cfp_tslot;
}

COMPILER_INLINE uint8_t ozb_mac_superframe_has_tx_gts(void) 
{
	return (ozb_mac_gts_stat.tx_length != 0);
}


int8_t ozb_mac_superframe_init(void);
void ozb_mac_superframe_start(uint32_t offset);
void ozb_mac_superframe_stop(void); 
void ozb_mac_superframe_resync(void);
void ozb_mac_superframe_gts_wakeup(void); 
uint8_t ozb_mac_superframe_check_gts(uint8_t lenght); 

#endif /* Header Protection */
