/** 
* @file phy_types.h
* @brief PHY types
* @author Christian Nastasi
* @date 2009-03-22
*/
#ifndef __ozb_phy_types_h__
#define __ozb_phy_types_h__

#include <hal/ozb_compiler.h>
#include <phy/ozb_phy_const.h>

/** 
* @brief IEEE 802.15.4 PHY PAN Information Base
*
* \todo Some member can be optimized due to their representation. Check the
* 	standard at the section and table PHY PIB attributes.
* \todo Some value (from CURRENT_PAGE_INIT to 
*	SYMBOLS_PER_OCTET_INIT) cannot change at runtime unless there 
*	is a change in the transceiver (is this correct?). Can we optimize
*	the code making some of the elements as either const (flash) or define?
*/
struct ozb_phy_pib_t {
	uint8_t 	phyCurrentChannel;
	uint32_t	phyChannelsSupported[OZB_PHY_CHANNEL_PAGES];
	uint8_t 	phyTransmitPower;
	uint8_t		phyCCAMode;
	uint8_t 	phyCurrentPage;
	uint16_t	phyMaxFrameDuration;
	uint8_t		phySHRDuration;
	float 		phySymbolsPerOctet;
};

/** 
* @brief PHY PIB Attributes IDs.
*
* \todo Make a reference to the std where is defined the PHY PIB attribute list.
*/
enum ozb_phy_pib_id_t {
	OZB_PHY_CURRENT_CHANNEL		= 0x00,
	OZB_PHY_CHANNEL_SUPPORTED	= 0x01,
	OZB_PHY_TRANSMIT_POWER		= 0x02,
	OZB_PHY_CCA_MODE		= 0x03,
	OZB_PHY_CURRENT_PAGE		= 0x04,
	OZB_PHY_MAX_FRAME_DURATION	= 0x05,
	OZB_PHY_SHR_DURATION		= 0x06,
	OZB_PHY_SYMBOLS_PER_OCTET	= 0x07,
};

/** 
* @brief PHY status and state code.
*
* \todo Make a reference to the std where is defined the PHY enumeration list.
*/
enum ozb_phy_code_t {
	OZB_PHY_BUSY 			= 0x00,
	OZB_PHY_BUSY_RX 		= 0x01,
	OZB_PHY_BUSY_TX 		= 0x02,
	OZB_PHY_FORCE_TRX_OFF 		= 0x03,
	OZB_PHY_IDLE 			= 0x04,
	OZB_PHY_INVALID_PARAMETER 	= 0x05,
	OZB_PHY_RX_ON 			= 0x06,
	OZB_PHY_SUCCESS 		= 0x07,
	OZB_PHY_TRX_OFF 		= 0x08,
	OZB_PHY_TX_ON 			= 0x09,
	OZB_PHY_UNSUPPORTED_ATTRIBUTE 	= 0x0A,
	OZB_PHY_READ_ONLY 		= 0x0B
};


#endif /* Header Protection */
