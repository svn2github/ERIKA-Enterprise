#ifndef __ozb_timer_dspic30_h__
#define __ozb_timer_dspic30_h__

#include <hal/ozb_timer.h>

#ifndef OZB_TIMER_REG_CON
#define OZB_TIMER_REG_CON		T5CON
#endif

#ifndef OZB_TIMER_REG_CONbits
#define OZB_TIMER_REG_CONbits		T5CONbits
#endif

#ifndef OZB_TIMER_REG_TMR
#define OZB_TIMER_REG_TMR		TMR5
#endif

#ifndef OZB_TIMER_REG_PERIOD
#define OZB_TIMER_REG_PERIOD		PR5
#endif

#ifndef OZB_TIMER_INTERRUPT_NAME
#define OZB_TIMER_INTERRUPT_NAME	_T5Interrupt
#endif

#ifndef OZB_TIMER_INTERRUPT_FLAG	
#define OZB_TIMER_INTERRUPT_FLAG	IFS1bits.T5IF	
#endif

#ifndef OZB_TIMER_INTERRUPT_ENABLE
#define OZB_TIMER_INTERRUPT_ENABLE 	IEC1bits.T5IE
#endif

#ifndef OZB_TIMER_INTERRUPT_PRIORITY
#define OZB_TIMER_INTERRUPT_PRIORITY 	IPC7bits.T5IP
#endif

int8_t ozb_timer_init(uint32_t period, uint32_t fcy);

void ozb_timer_set_isr_callback(void (*func)(void));

COMPILER_INLINE void ozb_timer_start(void)
{
	OZB_TIMER_INTERRUPT_FLAG = 0;
	OZB_TIMER_INTERRUPT_ENABLE = 1;
	OZB_TIMER_REG_CONbits.TON = 1;
}

COMPILER_INLINE void ozb_timer_stop(void)
{
	OZB_TIMER_INTERRUPT_ENABLE = 0;
	OZB_TIMER_REG_CONbits.TON = 0;
	OZB_TIMER_INTERRUPT_FLAG = 0;
}

#endif /* Header Protection */
