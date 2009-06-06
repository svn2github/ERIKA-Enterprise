#ifndef __ozb_mac_h__
#define __ozb_mac_h__

#include <mac/ozb_mac_const.h>
#include <mac/ozb_mac_types.h>	
#include <mac/ozb_mac_mcps.h>
#include <mac/ozb_mac_mlme.h>

#define OZB_MAC_EXTD_ADDR_SET(address, high, low) 	\
do {							\
	(address)[0] = (low);				\
	(address)[1] = (high);				\
} while (0)						\


#define OZB_MAC_EXTD_ADDR_GET(address, high, low) 	\
do {							\
	(low) = (address)[0];				\
	(high) = (address)[1];				\
} while (0)						\


#define OZB_MAC_EXTD_ADDR_COMPARE(address1, address2) 	\
	(((address1)[0] == (address2)[0]) && ((address1)[1] == (address2)[1]))

#define OZB_MAC_EXTD_ADDR_COMPARE_IMM(address, high, low) 	\
	(((address)[0] == (low) && ((address)[1] == (high))))


#define OZB_MAC_MPDU_FRAME_CONTROL(mpdu) 		(mpdu)
#define OZB_MAC_MPDU_SEQ_NUMBER(mpdu) 			((mpdu) + 2)
#define OZB_MAC_MPDU_ADDRESSING_FIELDS(mpdu) 		((mpdu) + 3)
#define OZB_MAC_MPDU_AUX_SECURITY_HEADER(mpdu, offset) 	((mpdu) + 3 + (offset))
#define OZB_MAC_MPDU_MAC_PAYLOAD(mpdu, offset) 		((mpdu) + 3 + (offset))
#define OZB_MAC_MPDU_MAC_FCS(mpdu, offset) 		((mpdu) + 3 + (offset))

#define OZB_MAC_FCTL_GET_FRAME_TYPE(fcf) 	((*(fcf)) & 0x07)
#define OZB_MAC_FCTL_GET_SECURITY(fcf) 		(((*(fcf)) >> 3) & 0x01)
#define OZB_MAC_FCTL_GET_FRAME_PENDING(fcf) 	(((*(fcf)) >> 4) & 0x01)
#define OZB_MAC_FCTL_GET_ACK_REQUEST(fcf) 	(((*(fcf)) >> 5) & 0x01)
#define OZB_MAC_FCTL_GET_PANID_COMPRESS(fcf) 	(((*(fcf)) >> 6) & 0x01)
#define OZB_MAC_FCTL_GET_DST_ADDR_MODE(fcf)	((((fcf)[1]) >> 2) & 0x03)
#define OZB_MAC_FCTL_GET_FRAME_VERSION(fcf)	((((fcf)[1]) >> 4) & 0x03)
#define OZB_MAC_FCTL_GET_SRC_ADDR_MODE(fcf)	((((fcf)[1]) >> 6) & 0x03)

#define OZB_MAC_SF_SPEC_GET_BO(ss)		((*(ss)) & 0x0F)
#define OZB_MAC_SF_SPEC_GET_SO(ss)		((*(ss)) >> 4)
#define OZB_MAC_SF_SPEC_GET_LAST_CAP_TSLOT(ss)	(((ss)[1]) & 0x0F)
#define OZB_MAC_SF_SPEC_GET_BLE(ss)		((((ss)[1]) >> 4) & 0x03)
#define OZB_MAC_SF_SPEC_GET_PAN_COORD(ss)	((((ss)[1]) >> 6) & 0x01)
#define OZB_MAC_SF_SPEC_GET_ASSOC_PERMIT(ss)	((((ss)[1]) >> 7) & 0x01)

/*
#define OZB_MAC_MPDU_SF_SPECIFICATION(mpdu, offset) 	((mpdu) + 3 + (offset))
#define OZB_MAC_MPDU_GTS_FIELDS(mpdu, offset) 		((mpdu) + 5 + (offset))
#define OZB_MAC_MPDU_PENDING_ADDRESSES(mpdu, offset) 	((mpdu) + 6 + (offset))
#define OZB_MAC_MPDU_BEACON_PAYLOAD(mpdu, offset) 	((mpdu) + 7 + (offset))
*/

#define OZB_MAC_GTS_SPEC_SET_EMPTY(gts_spec) 				\
	(*(gts_spec) = 0)						\

#define OZB_MAC_GTS_SPEC_SET_DESCRIPTOR_COUNT(gts_spec, cnt) 		\
	(*(gts_spec) = (*(gts_spec) & 0xF8) | ((cnt) & 0x07))		\

#define OZB_MAC_GTS_SPEC_SET_PERMIT(gts_spec, permit) 			\
	(*(gts_spec) = (*(gts_spec) & 0x7F) | ((permit)) << 7)		\

#define OZB_MAC_GTS_DIRECTION_SET(gts_dirs, id, val) 			   \
	(*(gts_dirs) = (*(gts_dirs) & (~(0x1 << (id))))	| ((val)) << (id)) \


#define OZB_MAC_GTS_SPEC_GET_DESCRIPTOR_COUNT(gts_spec) \
	(*(gts_spec) & 0x07)				\

#define OZB_MAC_GTS_SPEC_GET_PERMIT(gts_spec) 		\
	((*(gts_spec)) >> 7)				\

#define OZB_MAC_GTS_DIRECTION_GET(gts_dirs, id) 	\
	((*(gts_dirs) >> (id)) & 0x1) 			\

#define OZB_MAC_GTS_DES_GET_ADDRESS(gts_des) 		\
	(((uint8_t *)(gts_des))[0] + 			\
	(((uint16_t)((uint8_t *)(gts_des))[1]) << 8))	\


#define OZB_MAC_GTS_DES_GET_LENGTH(gts_des) 		\
	(((gts_des)[2]) >> 4)				\

#define OZB_MAC_GTS_DES_GET_START_SLOT(gts_des) 	\
	(((gts_des)[2]) & 0x0F)				\



#define OZB_MAC_PENDING_ADDR_SPEC_SET_EMPTY(pend_spec)			\
	(*(pend_spec) = 0)						\

#define OZB_MAC_PENDING_ADDR_SPEC_SET_SHORTS(pend_spec, cnt) 		\
	(*(pend_spec) = (*(pend_spec) & 0xF8) | ((cnt) & 0x07))		\

#define OZB_MAC_PENDING_ADDR_SPEC_SET_EXTDS(pend_spec, cnt) 		\
	(*(pend_spec) = (*(pend_spec) & 0x8F) | (((cnt) & 0x07) << 4))	\


int8_t ozb_mac_init(void); 

int8_t ozb_mac_gts_db_clean(void);

int8_t ozb_mac_gts_db_add(ozb_mac_dev_addr_short_t dev_addr, 
			  uint8_t len, uint8_t dir);

#endif /* Header Protection */
