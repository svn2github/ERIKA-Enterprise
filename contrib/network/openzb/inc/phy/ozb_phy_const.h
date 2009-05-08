/**
* @file phy_const.h
* @brief PHY Constants
* @author Christian Nastasi
* @date 2009-03-22
*/
#ifndef __ozb_phy_const_h__
#define __ozb_phy_const_h__

/**
*  @brief Number of Channel Pages
*
*  According to this value the \ref OZB_PHY_CHANNEL_SUPPORTED_INIT must be
*  properly defined as an array of \c OZB_PHY_CHANNEL_PAGES elements.
*/
#define OZB_PHY_CHANNEL_PAGES 1



#define OZB_PHY_CHANNEL_PAGE_FIRST 	0
#define OZB_PHY_CHANNEL_PAGE_LAST 	31

#define OZB_PHY_ERR_NONE		1 /* Returned as positive! */
#define OZB_PHY_ERR_INVALID_PARAM	2
#define OZB_PHY_ERR_HW_FAILURE		3
#define OZB_PHY_ERR_NOT_INITIALIZED	4
#define OZB_PHY_ERR_OSAL_ERROR		5



/**
* @name IEEE 802.15.4 PHY Layer Constants
* @{ */
#define OZB_aMaxPHYPacketSize 	127
#define OZB_aTurnaroundTime 	12
/**  @} */

#endif /* Header Protection */
