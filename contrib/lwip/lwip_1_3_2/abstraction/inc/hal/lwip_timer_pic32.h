/*
  Name: lwip_timer_mico32.h
  Copyright: Evidence Srl
  Author: Andrea Azzarà, Marco Ghibaudi
  Date: 29/03/10 18.23
  Description: Mico32 Timer functions for LWIP.
*/

#ifndef __lwip_timer_pic32_h__
#define __lwip_timer_pic32_h__

#include <hal/lwip_compiler.h>
#include "mcu/microchip_pic32/inc/ee_timer.h"

#ifndef EE_LWIP_TIMER_IN_USE	
#define EE_LWIP_TIMER_IN_USE	EE_TIMER_2
#endif

/* Function used for timer configuration */
void EE_hal_lwip_timers_configuration(void);

#ifdef __LWIP_TIME_DEBUG__
__INLINE__ u32_t __ALWAYS_INLINE__ EE_hal_lwip_read_timer(void)
{
	u32_t time_val;
	EE_timer_get_val32(EE_LWIP_TIMER_IN_USE, &time_val);
	return time_val;
}
#endif

#endif /* Header Protection */
