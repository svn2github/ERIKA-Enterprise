#ifndef __ozb_mac_h__
#define __ozb_mac_h__

#include <mac/ozb_mac_const.h>
#include <mac/ozb_mac_types.h>	
#include <mac/ozb_mac_mcps.h>
#include <mac/ozb_mac_mlme.h>

#define OZB_SET_MAC_EXTD_ADDR(address, high, low) 	\
do {							\
	(address)[0] = (low);				\
	(address)[1] = (high);				\
} while (0)						\


#define OZB_GET_MAC_EXTD_ADDR(address, high, low) 	\
do {							\
	(low) = (address)[0];				\
	(high) = (address)[1];				\
} while (0)						\


#define OZB_MAC_MPDU_FRAME_CONTROL(mpdu) 		(mpdu)
#define OZB_MAC_MPDU_SEQ_NUMBER(mpdu) 			((mpdu) + 2)
#define OZB_MAC_MPDU_ADDRESSING_FIELDS(mpdu) 		((mpdu) + 3)
#define OZB_MAC_MPDU_AUX_SECURITY_HEADER(mpdu, offset) 	((mpdu) + 3 + (offset))
#define OZB_MAC_MPDU_MAC_PAYLOAD(mpdu, offset) 		((mpdu) + 3 + (offset))
#define OZB_MAC_MPDU_MAC_FCS(mpdu, offset) 		((mpdu) + 3 + (offset))

#define OZB_MAC_MPDU_FRAME_CONTROL_GET_FRAME_TYPE(fcf) 	((*(fcf)) & 0x07)

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


#define OZB_MAC_PENDING_ADDR_SPEC_SET_EMPTY(pend_spec)			\
	(*(pend_spec) = 0)						\

#define OZB_MAC_PENDING_ADDR_SPEC_SET_SHORTS(pend_spec, cnt) 		\
	(*(pend_spec) = (*(pend_spec) & 0xF8) | ((cnt) & 0x07))		\

#define OZB_MAC_PENDING_ADDR_SPEC_SET_EXTDS(pend_spec, cnt) 		\
	(*(pend_spec) = (*(pend_spec) & 0x8F) | (((cnt) & 0x07) << 4))	\


int8_t ozb_mac_init(void); 

#endif /* Header Protection */
