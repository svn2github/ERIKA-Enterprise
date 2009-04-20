#ifndef __ozb_mac_const_h__
#define __ozb_mac_const_h__

#ifndef OZB_TRUE
#define OZB_TRUE	1
#endif
#ifndef OZB_FALSE	
#define OZB_FALSE	0
#endif

#define OZB_MAC_TICKS_BEFORE_BI		5
#define OZB_MAC_TICKS_BEFORE_TIMESLOT	5
#define OZB_MAC_TICKS_ON_SO_EQUAL_BO	1

/* chris: TODO: could we have a better choice for a default 64bits address? */
#ifndef OZB_MAC_DEVICE_EXTD_ADDRESS
#define OZB_MAC_DEVICE_EXTD_ADDRESS_HIGH	0x00000000
#define OZB_MAC_DEVICE_EXTD_ADDRESS_LOW		0x00000001
#endif

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
