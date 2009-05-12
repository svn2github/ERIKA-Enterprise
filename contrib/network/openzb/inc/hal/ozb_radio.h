/**
* @file ozb_radio.h
* @brief Abstract Radio Definition
* @author Christian Nastasi
* @date 2009-03-22
*
* This file contains the declarations of the abstract radio used by the OpenZB
* modules.
*
*/
#ifndef __ozb_radio_h__
#define __ozb_radio_h__

#include <hal/ozb_compiler.h>

#define OZB_RADIO_ERR_NONE 		0
#define OZB_RADIO_ERR_PHY_FAILURE 	1/**< The PHY layer issued a primitive 						      with a failure status. */

#ifdef USE_CC2420		/* Texas Instruments CC2420 */
#include <hal/ozb_radio_cc2420.h>

#elif defined USE_MRF24J40 	/* Microchip MRF24J40. */
#include <hal/ozb_radio_mrf24j40.h>

#else			/* No radio */
#error "OZB_HAL ERROR: radio type not specified!"

#endif	/* End Radio Selection */

enum ozb_phy_code_t ozb_radio_phy_get_status(void);
int8_t ozb_radio_phy_set_channel(uint8_t ch);
int8_t ozb_radio_phy_set_rx_on(void);

#endif /* Header Protection */
