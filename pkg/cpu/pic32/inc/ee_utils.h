#ifndef __INCLUDE_PIC32_EE_UTILS_H__
#define __INCLUDE_PIC32_EE_UTILS_H__

#include "cpu/pic32/inc/ee_compiler.h"
#include "ee_pic32regs.h"

void EE_system_init(void);
EE_UINT32 EE_get_system_clock(void);
EE_UINT32 EE_get_peripheral_clock(void);
void EE_nop_delay_us_80mips(EE_UINT32 delay);
void EE_delay_ticks(EE_UINT32 ticks);
void EE_delay_us(EE_UINT32 delay);

#ifdef __USE_EE_CORETIMER_ALARM__
void EE_coretimer_hard_alarm(EE_UINT32 hw_ticks, void (*f)(void));
void EE_coretimer_soft_alarm(EE_UINT32 period_us, void (*f)(void));
#endif

#endif  /* __INCLUDE_PIC32_EE_UTILS_H__ */
