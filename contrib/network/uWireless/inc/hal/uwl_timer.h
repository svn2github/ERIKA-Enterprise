#ifndef __uwl_timer_h__
#define __uwl_timer_h__

#ifndef UWL_HAL_EXTERNAL_TIMER		/* Check if no external HAL timer */

#include <hal/uwl_compiler.h>

#if defined __MICROCHIP_DSPIC30__

#include <hal/uwl_timer_dspic30.h>

#elif defined __AVR5__
/* TODO*/

#else			/* No timer */
#error "UWL_HAL ERROR: timer hw interface not specified"

#endif	/* End Selection */

#endif /* UWL_HAL_EXTERNAL_TIMER */

#endif /* Header Protection */
