/** 
* @file ee_timer.c
*/

#include "mcu/mico32/inc/ee_timer.h"
#include <cpu/mico32/inc/ee_irq.h>		// to use ISR functions.

/******************************************************************************/
/*                             Utility Macros                                 */
/******************************************************************************/
// ...

/******************************************************************************/
/*                       Private Local Variables                              */
/******************************************************************************/

/******************************************************************************/
/*                       Private Local Functions                              */
/******************************************************************************/
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


/******************************************************************************/
/*                              ISRs                                          */
/******************************************************************************/
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


/******************************************************************************/
/*                       Public Global Functions                              */
/******************************************************************************/

int EE_hal_timer_init(EE_timer_st* tst, int period, int settings)
{
	MicoTimer_t *timerc = tst->base;
	
	/* Register the handler */
	EE_mico32_register_ISR(tst->irqf, EE_timer_common_handler);
	
	if(EE_timer_need_enable_int(settings))
		mico32_enable_irq(tst->irqf);
	else
		mico32_disable_irq(tst->irqf);
	
	/* Stop the timer */
	timerc->Control = MICO32_TIMER_CONTROL_STOP_BIT_MASK;
	
	/* Set the period */
	timerc->Period = period;	// timer period
	
	/* Set the control register */
	timerc->Control = settings;
	
	/* ISR management */
	return EE_TIMER_OK;

}

