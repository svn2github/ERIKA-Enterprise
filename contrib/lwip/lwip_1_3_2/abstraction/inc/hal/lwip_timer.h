/*
  Name: lwip_timer.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: Timer configurations functions for LWIP.
*/

#ifndef __lwip_timer_h__
#define __lwip_timer_h__

#ifndef LWIP_HAL_EXTERNAL_TIMER		/* Check if no external HAL timer */
#include <hal/lwip_compiler.h>
#if defined __LM32__
#include <hal/lwip_timer_mico32.h>
#else			/* No timer */
#error "LWIP_HAL ERROR: timer hw interface not specified"
#endif	/* End Selection */
#endif /* lwip_HAL_EXTERNAL_TIMER */

#endif /* Header Protection */
