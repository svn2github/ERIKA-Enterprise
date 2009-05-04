#ifndef __ozb_mac_types_h__
#define __ozb_mac_types_h__

#include <hal/ozb_compiler.h>
#include <mac/ozb_mac_const.h>

typedef uint32_t ozb_mac_dev_addr_extd_t[2]; 
typedef uint16_t ozb_mac_dev_addr_short_t; 
#ifdef OZB_DEVICE_ADDRESS_16_ONLY /* TODO: check this in the varius call!*/
typedef ozb_mac_dev_addr_short_t ozb_mac_dev_addr_t; 
#else
typedef ozb_mac_dev_addr_extd_t ozb_mac_dev_addr_t; 
/*TODO: simplify writing the address with some macro? */
#endif

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

/* TODO complete this struc!!!! */
enum ozb_mac_pib_id_t {
	OZB_MAC_TODO,
	OZB_MAC_SHORT_ADDRESS 		= 0x53,
};

/* TODO: optimization on the types!! (make use of bit fields!!) */
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

/** 
* @brief IEEE 802.15.4 MAC PAN Information Base
*
* \todo Write comments!
*/

/*TODO: reorder the fields to have chance for compact representation (packing)*/
struct ozb_mac_pib_t {
	uint8_t macAckWaitDuration;	/*TODO: check representation! */
	unsigned macAssociatedPANCoord : 1;
	#ifndef OZB_RFD_DISABLE_OPTIONAL
	unsigned macAssociationPermit : 1;
	#endif /* OZB_RFD_DISABLE_OPTIONAL */
	unsigned macAutoRequest : 1;
	unsigned macBattLifeExt : 1;
	uint8_t macBattLifeExtPeriods; /* TODO: reduce representation! */
	#ifndef OZB_RFD_DISABLE_OPTIONAL
	//uint8_t macBeaconPayload[aMaxBeaconPayloadLength];
	uint8_t *macBeaconPayload; /* TODO: use this?? */
	uint8_t macBeaconPayloadLenght; /* TODO: reduce representation! */
	uint8_t macBeaconOrder;		/* TODO: reduce representation! */
	uint32_t macBeaconTxTime;	/* TODO: reduce representation?? */
	uint8_t macBSN;
	#endif /* OZB_RFD_DISABLE_OPTIONAL */
	//EE_UINT32 macCoordExtendedAddress0;	// TODO: REMOVE
	//EE_UINT32 macCoordExtendedAddress1;	// TODO: REMOVE
	ozb_mac_dev_addr_extd_t macCoordExtendedAddress;
	ozb_mac_dev_addr_short_t macCoordShortAddress;
	uint8_t macDSN;
	#ifndef OZB_DEVICE_DISABLE_OPTIONAL
	uint8_t macGTSPermit;
	#endif /* OZB_DEVICE_DISABLE_OPTIONAL */
	uint8_t macMaxBE;		/* TODO: reduce representation! */
	uint8_t macMaxCSMABackoffs;	/* TODO: reduce representation! */
	uint32_t macMaxFrameTotalWaitTime; /*TODO: check representation! */
	uint8_t macMaxFrameRetries; 	/* TODO: reduce representation! */
	uint8_t macMinBE;		/* TODO: reduce representation! */
	uint8_t macMinLIFSPeriod;	/* TODO: check representation! */
	uint8_t macMinSIFSPeriod;	/* TODO: check representation! */
	uint16_t macPANId;
	#ifndef OZB_RFD_DISABLE_OPTIONAL
	unsigned macPromiscuousMode : 1;
	#endif /* OZB_RFD_DISABLE_OPTIONAL */
	uint8_t macResponseWaitTime;	/* TODO: reduce representation! */
	unsigned macRxOnWhenIdle : 1;
	unsigned macSecurityEnabled : 1;
	ozb_mac_dev_addr_short_t macShortAddress;
	#ifndef OZB_RFD_DISABLE_OPTIONAL
	uint8_t macSuperframeOrder;	/* TODO: reduce representation! */
	#endif /* OZB_RFD_DISABLE_OPTIONAL */
	uint16_t macSyncSymbolOffset;	/* TODO: reduce representation! */
	unsigned macTimestampSupported : 1;	
	uint32_t macTransactionPersistenceTime; /*TODO: check representation!*/
};


typedef uint8_t ozb_mpdu_t[OZB_MAC_MPDU_SIZE]; 
typedef uint8_t *ozb_mpdu_ptr_t; 

enum ozb_mac_frame_type_t {
	OZB_MAC_TYPE_BEACON 	= 0x0,
	OZB_MAC_TYPE_DATA	= 0x1,
	OZB_MAC_TYPE_ACK	= 0x2,
	OZB_MAC_TYPE_COMMAND	= 0x3,
};

enum ozb_mac_addr_mode_t {
	OZB_MAC_ADDRESS_NONE 	= 0x0,
	OZB_MAC_ADDRESS_SHORT 	= 0x2,
	OZB_MAC_ADDRESS_EXTD 	= 0x3,
};


#endif /* Header Protection */
