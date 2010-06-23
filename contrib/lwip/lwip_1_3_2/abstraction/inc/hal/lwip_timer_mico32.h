/*
  Name: lwip_timer_mico32.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: Mico32 Timer functions for LWIP.
*/

#ifndef __lwip_timer_mico32_h__
#define __lwip_timer_mico32_h__

#include <hal/lwip_compiler.h>

__INLINE__ u32_t __ALWAYS_INLINE__ EE_hal_lwip_read_timer(void)
{
	u32_t time_val;
	EE_freetimer_get_value(&time_val);
	return time_val;
}


#endif /* Header Protection */
