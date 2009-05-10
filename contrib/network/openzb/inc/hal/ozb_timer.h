#ifndef __ozb_timer_h__
#define __ozb_timer_h__

#ifndef OZB_HAL_EXTERNAL_TIMER		/* Check if no HAL timer inref*/

#include <hal/ozb_compiler.h>

#if defined __MICROCHIP_DSPIC30__

#include <hal/ozb_timer_dspic30.h>

#elif defined __AVR5__
/* TODO*/

#else			/* No timer */
#error "OZB_HAL ERROR: timer hw interface not specified"

#endif	/* End Selection */

#endif /* OZB_HAL_EXTERNAL_TIMER */

#endif /* Header Protection */
