/*
  Name: ee_timer_pic32like_api.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.28
  Description: Timer driver functions for compatibility with pic32 projects. 
*/

#ifndef __INCLUDE_EEMCUMICO32_TIMER_PIC32LIKE_H__
#define __INCLUDE_EEMCUMICO32_TIMER_PIC32LIKE_H__

/* ------------------------------------------------ */
/* Macros for compatibility with pic32 timer driver */
/* ------------------------------------------------ */

#define EE_TIMER_DEFAULT_SETTINGS (MICO32_TIMER_CONTROL_INT_BIT_MASK | MICO32_TIMER_CONTROL_CONT_BIT_MASK | MICO32_TIMER_CONTROL_START_BIT_MASK)
#ifdef __USE_TIMER_IRQ__
#define EE_mchp_timer_set_callback(lc, cbk) EE_hal_timer_set_callback(& EE_ST_NAME(lc), cbk)
#define EE_mchp_timer_init(uc, lc, period, prescale) EE_hal_timer_init(& EE_ST_NAME(lc), period, EE_TIMER_DEFAULT_SETTINGS)
#else
#define EE_mchp_timer_init(uc, lc, period, prescale) EE_hal_timer_init((MicoTimer_t*)EE_BASE_ADD(uc), (int)EE_IRQ_NAME(uc), period, MICO32_TIMER_CONTROL_CONT_BIT_MASK | MICO32_TIMER_CONTROL_START_BIT_MASK)
#endif // #ifdef __USE_TIMER_IRQ__
#define EE_mchp_timer_start(uc) EE_hal_timer_start((MicoTimer_t*)EE_BASE_ADD(uc))
#define EE_mchp_timer_stop(uc) EE_hal_timer_stop((MicoTimer_t*)EE_BASE_ADD(uc))
#define EE_mchp_timer_get_val(uc, va) EE_hal_timer_get_val((MicoTimer_t*)EE_BASE_ADD(uc), va)

__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_timer_hard_init(EE_UINT8 id, EE_UINT16 period, EE_UINT8 prescale)
{
	EE_INT8 ret;
	
	#if defined(EE_TIMER1_NAME_LC) && defined(EE_TIMER2_NAME_LC)
	if(id==1)
		ret = EE_mchp_timer_init(EE_TIMER1_NAME_UC, EE_TIMER1_NAME_LC, period, prescale);
	else 
		ret = EE_mchp_timer_init(EE_TIMER2_NAME_UC, EE_TIMER2_NAME_LC, period, prescale);
	#else
		#if defined(EE_UART1_NAME_LC)
		ret = EE_mchp_timer_init(EE_TIMER1_NAME_UC, EE_TIMER1_NAME_LC, period, prescale);
		#else	
		ret = EE_mchp_timer_init(EE_TIMER2_NAME_UC, EE_TIMER2_NAME_LC, period, prescale);
		#endif
	#endif
	
	return ret;
}

__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_timer_soft_init(EE_UINT8 id, EE_UINT32 period_us, EE_UINT32 f_tick)
{
	EE_INT8 ret;
	
	#if defined(EE_TIMER1_NAME_LC) && defined(EE_TIMER2_NAME_LC)
	if(id==1)
		ret = EE_mchp_timer_init(EE_TIMER1_NAME_UC, EE_TIMER1_NAME_LC, period_us, f_tick);
	else 
		ret = EE_mchp_timer_init(EE_TIMER2_NAME_UC, EE_TIMER2_NAME_LC, period_us, f_tick);
	#else
		#if defined(EE_UART1_NAME_LC)
		ret = EE_mchp_timer_init(EE_TIMER1_NAME_UC, EE_TIMER1_NAME_LC, period_us, f_tick);
		#else	
		ret = EE_mchp_timer_init(EE_TIMER2_NAME_UC, EE_TIMER2_NAME_LC, period_us, f_tick);
		#endif
	#endif
	
	return ret;
}

#ifdef __USE_TIMER_IRQ__
__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_timer_set_callback(EE_UINT8 id, void (*f)(void))
{
	EE_INT8 ret;
	
	#if defined(EE_TIMER1_NAME_LC) && defined(EE_TIMER2_NAME_LC)
	if(id==1)
		ret = EE_mchp_timer_set_callback(EE_TIMER1_NAME_LC, f);
	else 
		ret = EE_mchp_timer_set_callback(EE_TIMER2_NAME_LC, f);
	#else
		#if defined(EE_UART1_NAME_LC)
		ret = EE_mchp_timer_set_callback(EE_TIMER1_NAME_LC, f);
		#else	
		ret = EE_mchp_timer_set_callback(EE_TIMER2_NAME_LC, f);
		#endif
	#endif
	
	return ret;
}
#endif // #ifdef __USE_TIMER_IRQ__

__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_timer_start(EE_UINT8 id)
{
	EE_INT8 ret;
	
	#if defined(EE_TIMER1_NAME_LC) && defined(EE_TIMER2_NAME_LC)
	if(id==1)
		ret = EE_mchp_timer_start(EE_TIMER1_NAME_UC);
	else 
		ret = EE_mchp_timer_start(EE_TIMER2_NAME_UC);
	#else
		#if defined(EE_UART1_NAME_LC)
		ret = EE_mchp_timer_start(EE_TIMER1_NAME_UC);
		#else	
		ret = EE_mchp_timer_start(EE_TIMER2_NAME_UC);
		#endif
	#endif
	
	return ret;
}


__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_timer_stop(EE_UINT8 id)
{
	EE_INT8 ret;
	
	#if defined(EE_TIMER1_NAME_LC) && defined(EE_TIMER2_NAME_LC)
	if(id==1)
		ret = EE_mchp_timer_stop(EE_TIMER1_NAME_UC);
	else 
		ret = EE_mchp_timer_stop(EE_TIMER2_NAME_UC);
	#else
		#if defined(EE_UART1_NAME_LC)
		ret = EE_mchp_timer_stop(EE_TIMER1_NAME_UC);
		#else	
		ret = EE_mchp_timer_stop(EE_TIMER2_NAME_UC);
		#endif
	#endif
	
	return ret;
}

__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_timer_get_val(EE_UINT8 id, EE_UINT16 *v)
{
	EE_INT8 ret;
	
	#if defined(EE_TIMER1_NAME_LC) && defined(EE_TIMER2_NAME_LC)
	if(id==1)
		ret = EE_mchp_timer_get_val(EE_TIMER1_NAME_UC, (unsigned int *) v);
	else 
		ret = EE_mchp_timer_get_val(EE_TIMER2_NAME_UC, (unsigned int *) v);
	#else
		#if defined(EE_UART1_NAME_LC)
		ret = EE_mchp_timer_get_val(EE_TIMER1_NAME_UC, (unsigned int *) v);
		#else	
		ret = EE_mchp_timer_get_val(EE_TIMER2_NAME_UC, (unsigned int *) v);
		#endif
	#endif
	
	return ret;
}

#endif // __INCLUDE_EEMCUMICO32_TIMER_PIC32LIKE_H__
