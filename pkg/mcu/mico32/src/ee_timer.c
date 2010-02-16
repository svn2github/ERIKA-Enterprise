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
void EE_timer_handler(EE_timer_st* tsp)
{
	MicoTimer_t *timerc = (MicoTimer_t *)(tsp->base); 
	
	/* acknowledge the interrupt */
	timerc->Status = 0;
	
	/* body of the ISR callback... */
	tsp->cbk();
	
	// All done!!!
	return;	
}


/******************************************************************************/
/*                       Public Global Functions                              */
/******************************************************************************/
// START_STOP_CONTROL must be controllable!!!
EE_UINT8 EE_timer_init_base(EE_UINT32 base, EE_UINT32 period, EE_UINT32 settings)
{
	// START_STOP_CONTROL must be controllable!!!
	MicoTimer_t *timerc = (MicoTimer_t *)base;
	
	/* check period value */
	if( period==0 )
        return(MICO_STATUS_E_INVALID_PARAM);
        
    switch(base)
	{
		case TIMER1_BASE_ADDRESS:
			ee_timer_st_1.base = base;
			break;
		case TIMER2_BASE_ADDRESS:
			ee_timer_st_2.base = base;
			break;
		default:
			return(MICO_STATUS_E_INVALID_PARAM);
	}    
	    
	/* Stop the timer */
	timerc->Control = MICO32_TIMER_CONTROL_STOP_BIT_MASK;
	
	/* Set the period */
	timerc->Period = period;	// timer period
	
	/* Set the control register */
	timerc->Control = settings;
	
	// All done!!!
	return EE_TIMER_OK;
}

EE_UINT8 EE_timer_set_ISR_callback_base(EE_UINT32 base, EE_UINT32 irq_flag, EE_mico32_ISR_callback isr_callback)
{
	// START_STOP_CONTROL must be controllable!!!
	MicoTimer_t *timerc = (MicoTimer_t *)base;
	
    switch(base)
	{
		case TIMER1_BASE_ADDRESS:
			ee_timer_st_1.cbk = isr_callback;
			if(isr_callback != NULL)
			{
				EE_mico32_register_ISR(irq_flag, EE_timer1_handler);
				timerc->Control |= MICO32_TIMER_CONTROL_INT_BIT_MASK; // flags: ex. MICO32_TIMER_CONTROL_INT_BIT_MASK | MICO32_TIMER_CONTROL_CONT_BIT_MASK | MICO32_TIMER_CONTROL_START_BIT_MASK;	
			}
			else
				timerc->Control &= (~(unsigned int)(MICO32_TIMER_CONTROL_INT_BIT_MASK));
			break;
		case TIMER2_BASE_ADDRESS:
			ee_timer_st_2.cbk = isr_callback;
			if(isr_callback != NULL)
			{
				EE_mico32_register_ISR(irq_flag, EE_timer2_handler);
				timerc->Control |= MICO32_TIMER_CONTROL_INT_BIT_MASK; // flags: ex. MICO32_TIMER_CONTROL_INT_BIT_MASK | MICO32_TIMER_CONTROL_CONT_BIT_MASK | MICO32_TIMER_CONTROL_START_BIT_MASK;	
			}
			else
				timerc->Control &= (~(unsigned int)(MICO32_TIMER_CONTROL_INT_BIT_MASK));
			break;
		default:
			return(MICO_STATUS_E_INVALID_PARAM);
	}   
	
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


