#include "mcu/microchip_pic32/inc/ee_timer.h"
#ifdef __PIC32_INCLUDE_REGS__
#include "ee_pic32regs.h"
#endif

/******************************************************************************/
/*                             Utility Macros                                 */
/******************************************************************************/

/******************************************************************************/
/*                       Private Local Variables                              */
/******************************************************************************/
#ifdef __USE_EE_TIMER_1__
static void (* volatile timer1_callback)(void) = NULL;
#endif
#ifdef __USE_EE_TIMER_2__
static void (* volatile timer2_callback)(void) = NULL;
#endif
#ifdef __USE_EE_TIMER_3__
static void (* volatile timer3_callback)(void) = NULL;
#endif
#ifdef __USE_EE_TIMER_4__
static void (* volatile timer4_callback)(void) = NULL;
#endif
#ifdef __USE_EE_TIMER_5__
static void (* volatile timer5_callback)(void) = NULL;
#endif

/******************************************************************************/
/*                       Private Local Functions                              */
/******************************************************************************/
#ifdef __USE_EE_TIMER_1__
__INLINE__ void __ALWAYS_INLINE__ timer1_init(EE_UREG pr, EE_UINT8 tckps)
{
	IEC0CLR = _IEC0_T1IE_MASK;	// Disable Timer IRQ
	IFS0CLR = _IFS0_T1IF_MASK;	// Clean Timer IRQ Flag
	IPC1CLR = _IPC1_T1IP_MASK;	// Clean IRQ Priority
	IPC1SET = (2 << _IPC1_T1IP_POSITION); //TODO:change hardcoding Irq Prio?
	IPC1CLR = _IPC1_T1IS_MASK; //TODO:change hardcoding Irq Sub-Prio?
	PR1 = pr;
	TMR1 = 0;
	T1CON = ((tckps & 0x03) << _T1CON_TCKPS_POSITION);
}

__INLINE__ void __ALWAYS_INLINE__ timer1_start(void) 
{
	IFS0CLR = _IFS0_T1IF_MASK;	// Clean Timer IRQ Flag
	IEC0SET = _IEC0_T1IE_MASK;	// Enable Timer IRQ
	T1CONSET = _T1CON_ON_MASK;	// Start Timer
}

__INLINE__ void __ALWAYS_INLINE__ timer1_stop(void) 
{
	T1CONCLR = _T1CON_ON_MASK;	// Stop Timer
	IEC0CLR = _IEC0_T1IE_MASK;	// Disable Timer IRQ
	IFS0CLR = _IFS0_T1IF_MASK;	// Clean Timer IRQ Flag
}
#endif /* __USE_EE_TIMER_1__ */

#ifdef __USE_EE_TIMER_2__
#endif /* __USE_EE_TIMER_2__ */

#ifdef __USE_EE_TIMER_3__
#endif /* __USE_EE_TIMER_3__ */

#ifdef __USE_EE_TIMER_4__
#endif /* __USE_EE_TIMER_4__ */

#ifdef __USE_EE_TIMER_5__
#endif /* __USE_EE_TIMER_5__ */

/******************************************************************************/
/*                              TIMER ISRs                                    */
/******************************************************************************/
#ifdef __USE_EE_TIMER_1__
ISR2(_TIMER_1_VECTOR)
{
	IFS0CLR = _IFS0_T1IF_MASK;
	#ifdef __COUNTER_TICK_ON_TIMER_1__
	CounterTick(__COUNTER_TICK_ON_TIMER_1__);
	#endif
	if (timer1_callback)
		timer1_callback();
}
#endif /* __USE_EE_TIMER_1__ */

#ifdef __USE_EE_TIMER_2__
#endif /* __USE_EE_TIMER_2__ */

#ifdef __USE_EE_TIMER_3__
#endif /* __USE_EE_TIMER_3__ */

#ifdef __USE_EE_TIMER_4__
#endif /* __USE_EE_TIMER_4__ */

#ifdef __USE_EE_TIMER_5__
#endif /* __USE_EE_TIMER_5__ */

/******************************************************************************/
/*                       Public Global Functions                              */
/******************************************************************************/
EE_INT8 EE_timer_hard_init(EE_UINT8 id, EE_UINT16 period, EE_UINT8 prescale)
{
	switch (id) {
	#ifdef __USE_EE_TIMER_1__
	case EE_TIMER_1 :
		timer1_init((EE_UREG) period, prescale);
		break;
	#endif 
	#ifdef __USE_EE_TIMER_2__
	case EE_TIMER_2 :
		return -EE_TIMER_ERR_UNIMPLEMENTED;
	#endif 
	#ifdef __USE_EE_TIMER_3__
	case EE_TIMER_3 :
		return -EE_TIMER_ERR_UNIMPLEMENTED;
	#endif 
	#ifdef __USE_EE_TIMER_4__
	case EE_TIMER_4 :
		return -EE_TIMER_ERR_UNIMPLEMENTED;
	#endif 
	#ifdef __USE_EE_TIMER_5__
	case EE_TIMER_5 :
		return -EE_TIMER_ERR_UNIMPLEMENTED;
	#endif 
	default:
		return -EE_TIMER_ERR_BAD_TIMER_ID;
	}
	return EE_TIMER_NO_ERRORS;
} 

EE_INT8 EE_timer_soft_init(EE_UINT8 id, EE_UINT32 period_us, EE_UINT32 f_tick) 
{	
	EE_UREG pr, ps;

	/* TODO: Auto calculate proper values for period and prescaler, not
		 the following fake code
	 */
	if (period_us != 1000 && f_tick != 80000)
		return -EE_TIMER_ERR_UNIMPLEMENTED;
	pr = 0x9C40;
	ps = 0;
	switch (id) {
	#ifdef __USE_EE_TIMER_1__
	case EE_TIMER_1 :
		timer1_init(pr, ps);
		break;
	#endif 
	#ifdef __USE_EE_TIMER_2__
	case EE_TIMER_2 :
		return -EE_TIMER_ERR_UNIMPLEMENTED;
	#endif 
	#ifdef __USE_EE_TIMER_3__
	case EE_TIMER_3 :
		return -EE_TIMER_ERR_UNIMPLEMENTED;
	#endif 
	#ifdef __USE_EE_TIMER_4__
	case EE_TIMER_4 :
		return -EE_TIMER_ERR_UNIMPLEMENTED;
	#endif 
	#ifdef __USE_EE_TIMER_5__
	case EE_TIMER_5 :
		return -EE_TIMER_ERR_UNIMPLEMENTED;
	#endif 
	default:
		return -EE_TIMER_ERR_BAD_TIMER_ID;
	}
	return EE_TIMER_NO_ERRORS;
} 

EE_INT8 EE_timer_set_callback(EE_UINT8 id, void (*f)(void))
{
	switch (id) {
	#ifdef __USE_EE_TIMER_1__
	case EE_TIMER_1 :
		timer1_callback = f;
		break;
	#endif 
	#ifdef __USE_EE_TIMER_2__
	case EE_TIMER_2 :
		timer2_callback = f;
		break;
	#endif 
	#ifdef __USE_EE_TIMER_3__
	case EE_TIMER_3 :
		timer3_callback = f;
		break;
	#endif 
	#ifdef __USE_EE_TIMER_4__
	case EE_TIMER_4 :
		timer4_callback = f;
		break;
	#endif 
	#ifdef __USE_EE_TIMER_5__
	case EE_TIMER_5 :
		timer5_callback = f;
		break;
	#endif 
	default:
		return -EE_TIMER_ERR_BAD_TIMER_ID;
	}
	return EE_TIMER_NO_ERRORS;
} 

EE_INT8 EE_timer_start(EE_UINT8 id)
{
	switch (id) {
	#ifdef __USE_EE_TIMER_1__
	case EE_TIMER_1 :
		timer1_start();
		break;
	#endif 
	#ifdef __USE_EE_TIMER_2__
	case EE_TIMER_2 :
		return -EE_TIMER_ERR_UNIMPLEMENTED;
	#endif 
	#ifdef __USE_EE_TIMER_3__
	case EE_TIMER_3 :
		return -EE_TIMER_ERR_UNIMPLEMENTED;
	#endif 
	#ifdef __USE_EE_TIMER_4__
	case EE_TIMER_4 :
		return -EE_TIMER_ERR_UNIMPLEMENTED;
	#endif 
	#ifdef __USE_EE_TIMER_5__
	case EE_TIMER_5 :
		return -EE_TIMER_ERR_UNIMPLEMENTED;
	#endif 
	default:
		return -EE_TIMER_ERR_BAD_TIMER_ID;
	}
	return EE_TIMER_NO_ERRORS;
}

EE_INT8 EE_timer_stop(EE_UINT8 id)
{
	switch (id) {
	#ifdef __USE_EE_TIMER_1__
	case EE_TIMER_1 :
		timer1_stop();
		break;
	#endif 
	#ifdef __USE_EE_TIMER_2__
	case EE_TIMER_2 :
		return -EE_TIMER_ERR_UNIMPLEMENTED;
	#endif 
	#ifdef __USE_EE_TIMER_3__
	case EE_TIMER_3 :
		return -EE_TIMER_ERR_UNIMPLEMENTED;
	#endif 
	#ifdef __USE_EE_TIMER_4__
	case EE_TIMER_4 :
		return -EE_TIMER_ERR_UNIMPLEMENTED;
	#endif 
	#ifdef __USE_EE_TIMER_5__
	case EE_TIMER_5 :
		return -EE_TIMER_ERR_UNIMPLEMENTED;
	#endif 
	default:
		return -EE_TIMER_ERR_BAD_TIMER_ID;
	}
	return EE_TIMER_NO_ERRORS;
}

EE_INT8 EE_timer_get_val(EE_UINT8 id, EE_UINT16 *v)
{
	switch (id) {
	#ifdef __USE_EE_TIMER_1__
	case EE_TIMER_1 :
		*v = TMR1;
		break;
	#endif 
	#ifdef __USE_EE_TIMER_2__
	case EE_TIMER_2 :
		return -EE_TIMER_ERR_UNIMPLEMENTED;
	#endif 
	#ifdef __USE_EE_TIMER_3__
	case EE_TIMER_3 :
		return -EE_TIMER_ERR_UNIMPLEMENTED;
	#endif 
	#ifdef __USE_EE_TIMER_4__
	case EE_TIMER_4 :
		return -EE_TIMER_ERR_UNIMPLEMENTED;
	#endif 
	#ifdef __USE_EE_TIMER_5__
	case EE_TIMER_5 :
		return -EE_TIMER_ERR_UNIMPLEMENTED;
	#endif 
	default:
		return -EE_TIMER_ERR_BAD_TIMER_ID;
	}
	return EE_TIMER_NO_ERRORS;
}
