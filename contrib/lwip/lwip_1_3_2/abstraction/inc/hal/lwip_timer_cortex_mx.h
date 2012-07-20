/*
  Name: lwip_timer_mico32.h
  Copyright: Evidence Srl
  Author: Andrea Azzarà, Marco Ghibaudi
  Date: 29/03/10 18.23
  Description: Mico32 Timer functions for LWIP.
*/

#ifndef __lwip_timer_cortex_mx_h__
#define __lwip_timer_cortex_mx_h__

#if !defined(__AUTOSAR_R4_0__) || !defined(__AS_GPT_DRIVER__)
#error lwip for cortex need Autosar GPT MCAL driver!
#endif /* !defined(__AUTOSAR_R4_0__) || !defined(__AS_GPT_DRIVER__) */

#ifndef MILLISECONDS_TO_TICKS
#error lwip for cortex need MILLISECONDS_TO_TICKS macro!
#endif

#include <hal/lwip_compiler.h>

#define EE_get_peripheral_clock() EE_CPU_CLOCK
 
#define EE_hal_lwip_maybe_call_link_tmr() ((void)0)
 
__INLINE__ u32_t __ALWAYS_INLINE__ EE_lwip_get_core_timer_value(void)
{
	return EE_systick_get_value();
}
/* Function used for timer configuration */
void EE_hal_lwip_timers_configuration(void);

#ifdef __LWIP_TIME_DEBUG__
__INLINE__ u32_t __ALWAYS_INLINE__ EE_hal_lwip_read_timer(void)
{
    return EE_lwip_get_core_timer_value();
}
#endif

#endif /* Header Protection */
