/** 
* @file ee_timer.c
*/

#include "mcu/mico32/inc/ee_timer.h"
//#include "ee_internal.h"

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
// ...

/******************************************************************************/
/*                              ISRs                                          */
/******************************************************************************/
//void MicoTimerISRCallback(void)
//{
//    MicoTimer_t *timerc = (MicoTimer_t *)TIMER_BASE_ADDRESS; 
//
//    /* acknowledge the interrupt */
//    timerc->Status = 0;
//
//    // body of the ISR callback...
//
//    return;
//}

/******************************************************************************/
/*                       Public Global Functions                              */
/******************************************************************************/

EE_UINT8 EE_timer_init_base(EE_UINT32 base, EE_UINT32 period, EE_UINT32 settings)
{
	// START_STOP_CONTROL must be controllable!!!
	MicoTimer_t *timerc = (MicoTimer_t *)base;
	
	/* check period value */
	if( period==0 )
        return(MICO_STATUS_E_INVALID_PARAM);
        
	/* Stop the timer */
	timerc->Control = MICO32_TIMER_CONTROL_STOP_BIT_MASK;
	
	/* Set the period */
	timerc->Period = period;	// timer period
	
	/* Set the control register */
	timerc->Control = settings;
	
	// All done!!!
	return EE_TIMER_OK;
}

EE_UINT8 EE_timer_set_ISR_callback_base(EE_UINT32 base, EE_UINT32 irq_flag, EE_mico32_ISR_handler isr_callback)
{
	// START_STOP_CONTROL must be controllable!!!
	MicoTimer_t *timerc = (MicoTimer_t *)base;
	
	/* ISR configuration  */
	if(isr_callback != NULL)
	{
    	/* Register handler and enable the interrupt */
    	EE_mico32_register_ISR(irq_flag, isr_callback);
    	timerc->Control |= MICO32_TIMER_CONTROL_INT_BIT_MASK; // flags: ex. MICO32_TIMER_CONTROL_INT_BIT_MASK | MICO32_TIMER_CONTROL_CONT_BIT_MASK | MICO32_TIMER_CONTROL_START_BIT_MASK;
	}
	else
		timerc->Control &= (~(unsigned int)(MICO32_TIMER_CONTROL_INT_BIT_MASK));
	
	// All done!!!
	return EE_TIMER_OK;
}

EE_UINT8 EE_timer_start_base(EE_UINT32 base) 
{
	// START_STOP_CONTROL must be controllable!!!
	MicoTimer_t *timerc = (MicoTimer_t *)base;
	timerc->Control |= MICO32_TIMER_CONTROL_START_BIT_MASK; 
	
	// All done!!!
	return EE_TIMER_OK;
}

EE_UINT8 EE_timer_stop_base(EE_UINT32 base) 
{
	// START_STOP_CONTROL must be controllable!!!
	MicoTimer_t *timerc = (MicoTimer_t *)base;
	timerc->Control |= MICO32_TIMER_CONTROL_STOP_BIT_MASK; 
	
	// All done!!!
	return EE_TIMER_OK;
}

EE_UINT32 EE_timer_get_val_base(EE_UINT32 base, EE_UINT32 *val)
{
	// START_STOP_CONTROL must be controllable!!!
	MicoTimer_t *timerc = (MicoTimer_t *)base;
	
	// All done!!! return the snapshot value... 
	return timerc->Snapshot; 
}


