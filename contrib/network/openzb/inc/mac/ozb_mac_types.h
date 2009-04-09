#ifndef __ozb_mac_types_h__
#define __ozb_mac_types_h__

#include <hal/ozb_compiler.h>
//#include <mac/ozb_mac_const.h>
typedef uint8_t ozb_mac_dev_addr_extd_t[4]; 
typedef uint16_t ozb_mac_dev_addr_short_t; 
#ifdef OZB_DEVICE_ADDRESS_16_ONLY /* TODO: check this in the varius call!*/
typedef ozb_mac_dev_addr_short_t ozb_mac_dev_addr_t; 
#else
typedef ozb_mac_dev_addr_extd_t ozb_mac_dev_addr_t; 
/*TODO: simplify writing the address with some macro? */
#endif

/* TODO: optimization on the types!! (make use of bit fields!!) */
enum ozb_mac_code_t {
	//OZB_MAC_ASSOCIATION_SUCCESS	= 0x00,
	OZB_MAC_SUCCESS			= 0x00,
	OZB_MAC_PAN_AT_CAPACITY		= 0x01,
	OZB_MAC_PAN_ACCESS_DENIED	= 0x02,
	OZB_MAC_COUNTER_ERROR		= 0xDB,
	OZB_MAC_IMPROPER_KEY_TYPE	= 0xDC,
	OZB_MAC_IMPROPER_SECURITY_LEVEL	= 0xDD,
	OZB_MAC_UNSUPPORTED_LEGACY	= 0xDE,
	OZB_MAC_UNSUPPORTED_SECURITY	= 0xDF,
	OZB_MAC_BEACON_LOSS		= 0xE0,
	OZB_MAC_CHANNEL_ACCESS_FAILURE	= 0xE1,
	OZB_MAC_DEFINED			= 0xE2,
	OZB_MAC_DISABLE_TRX_FAIULURE	= 0xE3,
	OZB_MAC_FRAME_TOO_LONG		= 0xE5,
	OZB_MAC_SECURITY_ERROR		= 0xE4,
	OZB_MAC_INVALID_GTS		= 0xE6, 
	OZB_MAC_INVALID_HANDLE		= 0xE7,
	OZB_MAC_INVALID_PARAMETER	= 0xE8,
	OZB_MAC_NO_ACK			= 0xE9,
	OZB_MAC_NO_BEACON		= 0xEA,
	OZB_MAC_NO_DATA			= 0xEB,
	OZB_MAC_NO_SHORT_ADDRESS	= 0xEC,
	OZB_MAC_OUT_OF_CAP		= 0xED,
	OZB_MAC_PAN_ID_CONFLICT		= 0xEE,
	OZB_MAC_REALIGNMENT		= 0xEF,
	OZB_MAC_TRANSACTION_EXPIRED	= 0xF0,
	OZB_MAC_TRANSACTION_OVERFLOW	= 0xF1,
	OZB_MAC_TX_ACTIVE		= 0xF2,
	OZB_MAC_UNAVAILABLE_KEY		= 0xF3,
	OZB_MAC_UNSUPPORTED_ATTRIBUTE	= 0xF4,
	OZB_MAC_INVALID_ADDRESS		= 0xF5,
	OZB_MAC_ON_TIME_TOO_LONG	= 0xF6,
	OZB_MAC_PAST_TIME		= 0xF7,
	OZB_MAC_TRACKING_OFF		= 0xF8,
	OZB_MAC_INVALID_INDEX		= 0xF9,
	OZB_MAC_LIMIT_REACHED		= 0xFA,
	OZB_MAC_READ_ONLY		= 0xFB,
	OZB_MAC_SCAN_IN_PROGRESS	= 0xFC,
	OZB_MAC_SUPERFRAME_OVERLAP	= 0xFD,
	OZB_MAC_BEACON_LOST // TODO: is this an error? should be LOSS??? 
};

enum ozb_mac_pib_id_t {
	OZB_MAC_TODO
};

struct ozb_pan_des_t {
	uint8_t CoordAddrMode;
	uint16_t CoordPANId;
	ozb_mac_dev_addr_t CoordAddress;
	uint8_t LogicalChannel;
	uint8_t ChannelPage;
	uint16_t SuperframeSpec;
	uint8_t GTSPermit;
	uint8_t LinkQuality;
	uint32_t TimeStamp;
	enum ozb_mac_code_t SecurityFailure;
	uint8_t SecurityLevel;
	uint8_t KeyIdMode;
	uint8_t KeySource[8];
	uint8_t KeyIndex;
};



#endif /* Header Protection */
