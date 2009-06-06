#include <mac/ozb_mac_internal.h>
#include <hal/ozb_radio.h>
#include <util/ozb_memory.h>
#include <util/ozb_debug.h>

/******************************************************************************/
/*                            MAC GTS Private Data                            */
/******************************************************************************/
LIST_DEFINE_STATIC(gts_list, struct ozb_gts_info_t , OZB_MAC_GTS_MAX_NUMBER);

/******************************************************************************/
/*                        MAC GTS Private Functions                           */
/******************************************************************************/
static int8_t gts_db_add_entry(ozb_mac_dev_addr_short_t dev_addr, uint8_t len, 
			       uint8_t dir) 
{
	struct ozb_gts_info_t *entry;

	if (len > OZB_MAC_SUPERFRAME_LAST_SLOT || dir > 1) 
		return -OZB_MAC_ERR_INVALID_PARAM; /* invalid params values */
	/*TODO: check aMinCAPLength, calculate the minCAP in slot and use it
		instead of 1
	*/
	if (list_is_full(&gts_list) || ozb_mac_gts_stat.first_cfp_tslot < len+1)
		return -OZB_MAC_ERR_GTS_CFP_TOO_LARGE;
	for (entry = (struct ozb_gts_info_t *) list_iterator_head(&gts_list); 
	     entry != 0;
             entry = (struct ozb_gts_info_t *) list_iterate(&gts_list)) 
		if (entry->dev_address == dev_addr && entry->direction == dir)
			return 0; /*TODO: check. already added, make sense? */
	ozb_mac_gts_stat.first_cfp_tslot -= len;
	entry = list_add(&gts_list); /* NOTE: already checked if full! */
	entry->starting_tslot = ozb_mac_gts_stat.first_cfp_tslot;
	entry->length = len;
	entry->direction = dir;
	entry->dev_address = dev_addr;
	entry->expiration = 0x00; /* TODO: un-hardcode!!! */
	//ozb_mac_gts_stat.descriptor_count++;
	return OZB_MAC_ERR_NONE;
}

COMPILER_INLINE void gts_db_delete_all(void) 
{
	list_clear(&gts_list);
	ozb_mac_gts_stat.first_cfp_tslot = OZB_MAC_SUPERFRAME_LAST_SLOT + 1;
	ozb_mac_gts_stat.tx_start_tslot = 0;
	ozb_mac_gts_stat.tx_length = 0;
	ozb_mac_gts_stat.rx_start_tslot = 0;
	ozb_mac_gts_stat.rx_length = 0;
}

COMPILER_INLINE void set_gts_descriptor(uint8_t *des, 
					ozb_mac_dev_addr_short_t addr, 
					uint8_t tslot, uint8_t len)
{
	//memcpy(des, &addr, sizeof(ozb_mac_dev_addr_short_t));
	des[0] = addr & 0x00FF;
	des[1] = addr >> 8;
	des[2] = (len << 4) | (tslot & 0x0F);
}

/******************************************************************************/
/*                MAC GTS General Exportable Functions                        */
/******************************************************************************/
/* TODO: add more low-level manipulation functions! 
         (e.g allowing GTS allocation with 'holes') 
*/
int8_t ozb_mac_gts_db_clean(void) 
{
	#ifdef OZB_GTS_MANIPULATION
	gts_db_delete_all();
	return 1;
	#else
	return -OZB_MAC_ERR_GTS_MANIPULATION_DISABLED;
	#endif
}

int8_t ozb_mac_gts_db_add(ozb_mac_dev_addr_short_t dev_addr, 
			  uint8_t len, uint8_t dir) 
{
	#ifdef OZB_GTS_MANIPULATION
	return gts_db_add_entry(dev_addr, len, dir);
	#else
	return -OZB_MAC_ERR_GTS_MANIPULATION_DISABLED;
	#endif
}

/******************************************************************************/
/*                        MAC GTS General Functions                           */
/******************************************************************************/
int8_t ozb_mac_gts_init(void) 
{
	gts_db_delete_all();
	/* TODO: parse return values! */
	#ifndef OZB_GTS_MANIPULATION
	gts_db_add_entry(0x0002, 1, OZB_MAC_GTS_DIRECTION_OUT);
	gts_db_add_entry(0x0003, 3, OZB_MAC_GTS_DIRECTION_OUT);
	gts_db_add_entry(0x0004, 2, OZB_MAC_GTS_DIRECTION_OUT);
	#endif
	return 1;
}

uint8_t ozb_mac_gts_set_gts_fields(uint8_t *gf) 
{
	struct ozb_gts_info_t *entry;
	uint8_t *tmp;
	uint8_t i = 0;
	uint8_t s = OZB_MAC_MPDU_GTS_SPEC_SIZE;

	if (ozb_mac_pib.macGTSPermit == 0) {
		OZB_MAC_GTS_SPEC_SET_EMPTY(gf);
		return s;
	}
	OZB_MAC_GTS_SPEC_SET_DESCRIPTOR_COUNT(gf, list_get_size(&gts_list));
	OZB_MAC_GTS_SPEC_SET_PERMIT(gf, ozb_mac_pib.macGTSPermit);
	if (list_is_empty(&gts_list))
		return s;
	tmp = gf + s;
	s += OZB_MAC_MPDU_GTS_DIRECTIONS_SIZE;
	for (entry = (struct ozb_gts_info_t *) list_iterator_head(&gts_list); 
	     entry != 0;
             entry = (struct ozb_gts_info_t *) list_iterate(&gts_list)) {
		OZB_MAC_GTS_DIRECTION_SET(tmp, i, entry->direction);
		set_gts_descriptor(gf + s, entry->dev_address,  
				   entry->starting_tslot, entry->length); 
		s += OZB_MAC_MPDU_GTS_DESCRIPTOR_SIZE;
		i++;
	}
	/* TODO: remove this! DEBUG TEST!!! ---------- >>>>> */
	/*
	static uint16_t aaa = 0x0005;
	//static char bbb = 1;
	if (gts_db_add_entry(aaa++, 1, OZB_MAC_GTS_DIRECTION_OUT) == -1) {
		gts_db_delete_all();
		gts_db_add_entry(0x0002, 1, OZB_MAC_GTS_DIRECTION_OUT);
		gts_db_add_entry(0x0003, 3, OZB_MAC_GTS_DIRECTION_OUT);
		gts_db_add_entry(0x0004, 2, OZB_MAC_GTS_DIRECTION_OUT);
		//if (bbb) {
		//	ozb_mac_pib.macBeaconOrder++;
		//	bbb = 0;
		//} else {
		//	ozb_mac_pib.macBeaconOrder--;
		//	bbb = 1;
		//}
	}
	*/
	/* <<<<<<<<<<<<-----------------  TODO REMOVE BLOCK!!! */
	return s;
}

uint8_t ozb_mac_gts_get_gts_fields(uint8_t *gf) 
{
	uint8_t *tmp;
	uint8_t cnt;
	uint8_t i = 0;
	uint8_t s = OZB_MAC_MPDU_GTS_SPEC_SIZE;

	ozb_mac_pib.macGTSPermit = OZB_MAC_GTS_SPEC_GET_PERMIT(gf);
	if (ozb_mac_pib.macGTSPermit == 0) 
		return s;
	cnt = OZB_MAC_GTS_SPEC_GET_DESCRIPTOR_COUNT(gf);
	tmp = gf + s;
	s += OZB_MAC_MPDU_GTS_DIRECTIONS_SIZE;
	/* NOTE: if the GTS descriptor list is malformed (more than one GTS
		 in tx or more than one in rx) this shall take the last one! */
	for (i = 0; i < cnt; i++) {
		if (OZB_MAC_GTS_DES_GET_ADDRESS(gf + s) == 
		    ozb_mac_pib.macShortAddress) {
			if (OZB_MAC_GTS_DIRECTION_GET(tmp, i) == 
			    OZB_MAC_GTS_DIRECTION_OUT) {
				ozb_mac_gts_stat.tx_start_tslot =
					OZB_MAC_GTS_DES_GET_START_SLOT(gf + s);
				ozb_mac_gts_stat.tx_length =
					OZB_MAC_GTS_DES_GET_LENGTH(gf + s);
			} else {
				ozb_mac_gts_stat.rx_start_tslot =
					OZB_MAC_GTS_DES_GET_START_SLOT(gf + s);
				ozb_mac_gts_stat.rx_length =
					OZB_MAC_GTS_DES_GET_LENGTH(gf + s);
			}
		}
		s += OZB_MAC_MPDU_GTS_DESCRIPTOR_SIZE;
	}
	return s;
}

