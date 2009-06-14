#ifndef __ozb_mac_const_h__
#define __ozb_mac_const_h__

#ifdef OZB_TRUE
#undef OZB_TRUE
#endif
#define OZB_TRUE	1

#ifdef OZB_FALSE	
#undef OZB_FALSE	
#endif
#define OZB_FALSE	0

#define OZB_DEVICE_FFD		1
#define OZB_DEVICE_RFD		0

#ifndef OZB_MAC_GTS_QUEUE_SIZE	
//#define OZB_MAC_GTS_QUEUE_SIZE	5
#define OZB_MAC_GTS_QUEUE_SIZE	20
#endif

#ifndef OZB_MAC_CAP_QUEUE_SIZE	
//#define OZB_MAC_CAP_QUEUE_SIZE	5
#define OZB_MAC_CAP_QUEUE_SIZE	20
#endif

#define OZB_MAC_ERR_NONE 			1 /* Returned as positive! */
#define OZB_MAC_ERR_NOT_INITIALIZED		1
#define OZB_MAC_ERR_SF_NOT_INITIALIZED		2
#define OZB_MAC_ERR_INVALID_PARAM		3
#define OZB_MAC_ERR_PHY_FAILURE			4 /**< PHY bad reply. */
#define OZB_MAC_ERR_INVALID_LENGTH	5
#define OZB_MAC_ERR_STANDARD_UNSUPPORTED	10
#define OZB_MAC_ERR_DEBUG_INIT			11
#define OZB_MAC_ERR_GTS_MANIPULATION_DISABLED	20
#define OZB_MAC_ERR_GTS_CFP_TOO_LARGE		21
#define OZB_MAC_ERR_SUPERFRAME_CALLBACKS_DISABLED   22


/* TODO: these should depend on the current SO and BO settings!! */
#define OZB_MAC_TICKS_BEFORE_BI			2
#define OZB_MAC_TICKS_BEFORE_TIMESLOT		2

/* chris: TODO: could we have a better choice for a default 64bits address? */
#ifndef OZB_MAC_DEVICE_EXTD_ADDRESS
#define OZB_MAC_DEVICE_EXTD_ADDRESS_HIGH	0x00000000
#define OZB_MAC_DEVICE_EXTD_ADDRESS_LOW		0x00000001
#endif

#define OZB_MAC_PANID_BROADCAST			0xFFFF
#define OZB_MAC_SHORT_ADDRESS_BROADCAST		0xFFFF
#define OZB_MAC_SHORT_ADDRESS_ASSOC_INVALID	0xFFFF
#define OZB_MAC_SHORT_ADDRESS_INVALID		0xFFFF
#define OZB_MAC_SHORT_ADDRESS_USE_EXTD		0xFFFE

#define OZB_MAC_NULL_SECURITY_PARAMS_LIST	0, 0, NULL, 0

/**
* @name IEEE 802.15.4 MAC Layer Constants
* 
* \see Table 85: Mac Sublayer Constants
* @{ */
#define OZB_aBaseSlotDuration		60 /**< Base Time slot duration 
						in symbols. */
#define OZB_aBaseSuperframeDuration	960/**< OZB_aBaseSlotDuration x 
						OZB_aNumSuperframeSlots. */
#define OZB_aExtendedAddress_high	OZB_MAC_DEVICE_EXTD_ADDRESS_HIGH
#define OZB_aExtendedAddress_low	OZB_MAC_DEVICE_EXTD_ADDRESS_LOW
#define OZB_aGTSDescPersistenceTime	4  /**< Duration in number of SFs. */
#define OZB_aMaxBeaconOverhead		75 /**< Overhead in bytes */
#define OZB_aMaxBeaconPayloadLength	52 /**< OZB_aMaxPHYPacketSize - 
						OZB_aMaxBeaconOverhead */
#define OZB_aMaxLostBeacons		4  /**< Number of consecutive losts. */
#define OZB_aMaxMACSafePayloadSize	102/**< OZB_aMaxPHYPacketSize -
						OZB_aMaxMPDUUnsecuredOverhead.*/
#define OZB_aMaxMACPayloadSize		118/**< OZB_aMaxPHYPacketSize -
						OZB_aMinMPDUOverhead. */
#define OZB_aMaxMPDUUnsecuredOverhead	25 /**< In bytes.*/
#define OZB_aMaxSIFSFrameSize		18 /**< In bytes. */
#define OZB_aMinCAPLength		440/**< In symbols. */
#define OZB_aMinMPDUOverhead		9  /**< In bytes.*/
#define OZB_aNumSuperframeSlots 	16 /**< Number of slots in a SF. */
#define OZB_aUnitBackoffPeriod		20 /**< In symbols. */
/**  @} */

#define OZB_MAC_ACK_MPDU_SIZE			4
#define OZB_MAC_MPDU_SIZE			127 /* TODO: WHY NOT 127 ???? */
#define OZB_MAC_MAX_MSDU_SIZE			OZB_aMaxMACPayloadSize 
//#define OZB_MAC_MPDU_SIZE			125 /* TODO: WHY NOT 127 ???? */
#define OZB_MAC_MPDU_FRAME_CONTROL_SIZE		2
#define OZB_MAC_MPDU_SEQ_NUMBER_SIZE		1
#define OZB_MAC_MPDU_PANID_SIZE			2
#define OZB_MAC_MPDU_ADDRESS_SHORT_SIZE		2
#define OZB_MAC_MPDU_ADDRESS_EXTD_SIZE		8
#define OZB_MAC_MPDU_MHR_BASE_SIZE		3
#define OZB_MAC_MPDU_MFR_SIZE			2
#define OZB_MAC_MPDU_SUPERFRAME_SPEC_SIZE	2
#define OZB_MAC_MPDU_GTS_SPEC_SIZE		1
#define OZB_MAC_MPDU_GTS_DIRECTIONS_SIZE	1
#define OZB_MAC_MPDU_GTS_DESCRIPTOR_SIZE	3

#define OZB_MAC_SUPERFRAME_FIRST_SLOT 		0
#define OZB_MAC_SUPERFRAME_LAST_SLOT 		15

#define OZB_MAC_GTS_MAX_NUMBER 			7
#define OZB_MAC_GTS_DIRECTION_IN 		1
#define OZB_MAC_GTS_DIRECTION_OUT 		0







/* chris: TODO: What are these supposed to be???? ------> */
#define OZB_aMaxBE	5 
#define OZB_aMaxFrameOverhead          25
#define OZB_aMaxFrameResponseTime      1220
#define OZB_aMaxFrameRetries           1
//(SYNC)number of beacons lost before sending a Beacon-Lost indication
#define OZB_aMaxMACFrameSize           aMaxPHYPacketSize-aMaxFrameOverhead
#define OZB_aMinLIFSPeriod             40
#define OZB_aMinSIFSPeriod             12
#define OZB_aResponseWaitTime          32*aBaseSuperframeDuration
/* <-------------- TODO: see prev. comment!*/

#endif /* Header Protection */
