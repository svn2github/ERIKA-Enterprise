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

#define OZB_RADIO_SUCCESS 0
#define OZB_RADIO_ERROR_TODO 1

#ifdef USE_CC2420		/* Texas Instruments CC2420 */
#include <hal/ozb_radio_cc2420.h>

#elif defined USE_MRF24J40 	/* Microchip MRF24J40. */
#include <hal/ozb_radio_mrf24j40.h>

#else			/* No radio */
#error "OZB_HAL ERROR: radio type not specified!"

#endif	/* End Radio Selection */

#endif /* Header Protection */
