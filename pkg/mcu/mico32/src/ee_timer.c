/*
  Name: ee_timer.c
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.28
  Description: Timer library source file. 
*/

#include "mcu/mico32/inc/ee_timer.h"

/******************************************************************************/
/*                              Global Functions                              */
/******************************************************************************/
#ifdef __USE_TIMER_IRQ__
/* Vectors and uart structures definitions */
#ifdef EE_TIMER1_NAME_UC
DEFINE_STRUCT_TIMER(EE_TIMER1_NAME_UC, EE_TIMER1_NAME_LC)
#endif

#ifdef EE_TIMER2_NAME_UC
DEFINE_STRUCT_TIMER(EE_TIMER2_NAME_UC, EE_TIMER2_NAME_LC)
#endif

#ifdef EE_TIMER3_NAME_UC
DEFINE_STRUCT_TIMER(EE_TIMER3_NAME_UC, EE_TIMER3_NAME_LC)
#endif

#ifdef EE_TIMER4_NAME_UC
DEFINE_STRUCT_TIMER(EE_TIMER4_NAME_UC, EE_TIMER4_NAME_LC)
#endif
#endif /* #ifdef __USE_TIMER_IRQ__ */

/******************************************************************************/
/*                              ISRs                                          */
/******************************************************************************/
#ifdef __USE_TIMER_IRQ__
void EE_timer_common_handler(int level)
{
    EE_timer_st *tstp = EE_get_timer_st_from_level(level);
    MicoTimer_t *timerc = tstp->base;
    
	/* acknowledge the interrupt */
	timerc->Status = 0;
	
	/* body of the ISR callback... */
	if(tstp->cbk != EE_NULL_CBK)
        tstp->cbk();

	// All done!!!
	return;	
}
#endif /* #ifdef __USE_TIMER_IRQ__ */

/******************************************************************************/
/*                       Public Global Functions                              */
/******************************************************************************/

#ifdef __USE_TIMER_IRQ__

int EE_hal_timer_init(EE_timer_st* tst, int period, int settings)
{
	MicoTimer_t *timerc = tst->base;
	
	/* Stop the timer */
	timerc->Control = MICO32_TIMER_CONTROL_STOP_BIT_MASK;
	
	/* acknowledge the interrupt */
	timerc->Status = 0;
	
	/* Register the handler */
	EE_hal_timer_handler_setup(tst);
	if(EE_timer_need_enable_int(settings))
		mico32_enable_irq(tst->irqf);
	else
		mico32_disable_irq(tst->irqf);
	
	/* Set the period */
	timerc->Period = period;	// timer period
	
	/* Set the control register */
	timerc->Control = settings;
	
	/* ISR management */
	return EE_TIMER_OK;

}

#else

int EE_hal_timer_init(MicoTimer_t* timerc, int irqf, int period, int settings)
{
	/* Stop the timer */
	timerc->Control = MICO32_TIMER_CONTROL_STOP_BIT_MASK;
	
	/* acknowledge the interrupt */
	timerc->Status = 0;
	
	mico32_disable_irq(irqf);
	
	/* Set the period */
	timerc->Period = period;	// timer period
	
	/* Set the control register */
	timerc->Control = settings;
	
	/* ISR management */
	return EE_TIMER_OK;

}

#endif /* #ifdef __USE_TIMER_IRQ__ */
