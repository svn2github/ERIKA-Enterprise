/*
* ee_timer_internal.h
*/

#ifndef __INCLUDE_EEMCUMICO32_TIMER_INTERNAL_H__
#define __INCLUDE_EEMCUMICO32_TIMER_INTERNAL_H__

#ifdef __USE_TIMER__

#include "cpu/mico32/inc/ee_internal.h"
#include "mcu/mico32/inc/ee_internal.h"
#include "mcu/mico32/inc/ee_buffer.h"
#include "MicoTimer.h"					// to use LATTICE data structures.


/*************************************************************************
 Timers
 *************************************************************************/

/* Timer structure */
typedef struct {
    MicoTimer_t* base;
    int irqf;							// irq flag to register the handler
    EE_ISR_callback cbk;
} EE_timer_st;

/* Symbols and macros */
#define EE_TIMER_OK			(0x00)
#define EE_timer_need_enable_int(mode)  ( (mode) & MICO32_TIMER_CONTROL_INT_BIT_MASK )

/* Macro for Structure declaration */
#define DECLARE_STRUCT_TIMER(uc, lc) \
  extern EE_timer_st EE_ST_NAME(lc);
/* Macro for structure definition */
#define DEFINE_STRUCT_TIMER(uc, lc) \
EE_timer_st cat3(ee_, lc, _st) = { \
	.base= (MicoTimer_t*)cat2(uc, _BASE_ADDRESS),\
	.irqf= cat2(uc, _IRQ),\
	.cbk= EE_NULL_CBK };

int EE_hal_timer_init(EE_timer_st* tst, int period, int settings);

__INLINE__ int __ALWAYS_INLINE__  EE_hal_timer_start(MicoTimer_t* base)
{
	base->Control |= MICO32_TIMER_CONTROL_START_BIT_MASK; 
	return EE_TIMER_OK;
}

__INLINE__ int __ALWAYS_INLINE__  EE_hal_timer_stop(MicoTimer_t* base)
{
	base->Control |= MICO32_TIMER_CONTROL_STOP_BIT_MASK; 
	return EE_TIMER_OK;
}

__INLINE__ int __ALWAYS_INLINE__  EE_hal_timer_get_val(MicoTimer_t* base, unsigned int *val)
{
	*val = base->Snapshot;
	return EE_TIMER_OK;
}

__INLINE__ int __ALWAYS_INLINE__  EE_hal_timer_set_callback(EE_timer_st* tst, EE_ISR_callback cbk)
{
	tst->cbk = cbk;
	return EE_TIMER_OK;
}

__INLINE__ int __ALWAYS_INLINE__  EE_hal_timer_enable_IRQ(MicoTimer_t* base)
{
	base->Control |= MICO32_TIMER_CONTROL_INT_BIT_MASK;
	return EE_TIMER_OK;
}

__INLINE__ int __ALWAYS_INLINE__  EE_hal_timer_disable_IRQ(MicoTimer_t* base)
{
	base->Control &= ~MICO32_TIMER_CONTROL_INT_BIT_MASK;
	return EE_TIMER_OK;
}

#define DECLARE_FUNC_TIMER(uc, lc) \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _init)(int period, int settings){ \
	return EE_hal_timer_init(& EE_ST_NAME(lc), period, settings); } \
__INLINE__ int __ALWAYS_INLINE__  cat3(EE_, lc, _on)(void){ \
	return EE_hal_timer_start((MicoTimer_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__  cat3(EE_, lc, _off)(void){ \
	return EE_hal_timer_stop((MicoTimer_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__  cat3(EE_, lc, _set_ISR_callback)(EE_ISR_callback cbk){ \
	return EE_hal_timer_set_callback(& EE_ST_NAME(lc), cbk); } \
__INLINE__ int __ALWAYS_INLINE__  cat3(EE_, lc, _get_value)(unsigned int *val){ \
	return EE_hal_timer_get_val((MicoTimer_t*)EE_BASE_ADD(uc), val); } \
__INLINE__ int __ALWAYS_INLINE__  cat3(EE_, lc, _enable_IRQ)(void){ \
	return EE_hal_timer_enable_IRQ((MicoTimer_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__  cat3(EE_, lc, _disable_IRQ)(void){ \
	return EE_hal_timer_disable_IRQ((MicoTimer_t*)EE_BASE_ADD(uc)); }
	
 
#ifdef EE_TIMER1_NAME_UC
DECLARE_STRUCT_TIMER(EE_TIMER1_NAME_UC, EE_TIMER1_NAME_LC)
#endif	//#ifdef EE_TIMER1_NAME_UC

#ifdef EE_TIMER2_NAME_UC
DECLARE_STRUCT_TIMER(EE_TIMER2_NAME_UC, EE_TIMER2_NAME_LC)
#endif	//#ifdef EE_TIMER2_NAME_UC
	
#ifdef EE_TIMER3_NAME_UC
DECLARE_STRUCT_TIMER(EE_TIMER3_NAME_UC, EE_TIMER3_NAME_LC)
#endif	//#ifdef EE_TIMER3_NAME_UC	
	
#ifdef EE_TIMER4_NAME_UC
DECLARE_STRUCT_TIMER(EE_TIMER4_NAME_UC, EE_TIMER4_NAME_LC)
#endif	//#ifdef EE_TIMER4_NAME_UC
	
/* Return the Timer structure for the componente associated with the given IRQ
 * level */
__DECLARE_INLINE__ EE_timer_st *EE_get_timer_st_from_level(int level);

#ifndef EE_TIMER2_NAME_UC
/* If there is only one component of this kind, no test is done */
__INLINE__ EE_timer_st * __ALWAYS_INLINE__ EE_get_timer_st_from_level(int level)
{
    return & EE_ST_NAME(EE_TIMER1_NAME_LC);
}
#else /* #ifndef EE_TIMER_NAME2_UC */
__INLINE__ EE_timer_st * __ALWAYS_INLINE__ EE_get_timer_st_from_level(int level)
{
    switch (level) {
    default:
        return & EE_ST_NAME(EE_TIMER1_NAME_LC);
#ifdef EE_TIMER2_NAME_UC
    case EE_IRQ_NAME(EE_TIMER2_NAME_UC):
        return & EE_ST_NAME(EE_TIMER2_NAME_LC);
#endif
#ifdef EE_TIMER3_NAME_UC
    case EE_IRQ_NAME(EE_TIMER3_NAME_UC):
        return & EE_ST_NAME(EE_TIMER3_NAME_LC);
#endif
#ifdef EE_TIMER4_NAME_UC
    case EE_IRQ_NAME(EE_TIMER4_NAME_UC):
        return & EE_ST_NAME(EE_TIMER4_NAME_LC);
#endif
    }
}
#endif /* #ifndef EE_TIMER_NAME2_UC */


/* User functions (API) declaration: */  
#ifdef EE_TIMER1_NAME_UC
DECLARE_FUNC_TIMER(EE_TIMER1_NAME_UC, EE_TIMER1_NAME_LC)
#endif	//#ifdef EE_TIMER1_NAME_UC

#ifdef EE_TIMER2_NAME_UC
DECLARE_FUNC_TIMER(EE_TIMER2_NAME_UC, EE_TIMER2_NAME_LC)
#endif	//#ifdef EE_TIMER2_NAME_UC

#ifdef EE_TIMER3_NAME_UC
DECLARE_FUNC_TIMER(EE_TIMER3_NAME_UC, EE_TIMER3_NAME_LC)
#endif	//#ifdef EE_TIMER_NAME_UC

#ifdef EE_TIMER4_NAME_UC
DECLARE_FUNC_TIMER(EE_TIMER4_NAME_UC, EE_TIMER4_NAME_LC)
#endif	//#ifdef EE_TIMER4_NAME_UC

/* Macros for compatibility with pic32 timer driver */
#ifdef __USE_MICO_PIC_API__
#define EE_TIMER_DEFAULT_SETTINGS (MICO32_TIMER_CONTROL_INT_BIT_MASK | MICO32_TIMER_CONTROL_CONT_BIT_MASK | MICO32_TIMER_CONTROL_START_BIT_MASK)
#define EE_mchp_timer_init(lc, period, prescale) EE_hal_timer_init(& EE_ST_NAME(lc), period, EE_TIMER_DEFAULT_SETTINGS)
#define EE_mchp_timer_start(uc) EE_hal_timer_start((MicoTimer_t*)EE_BASE_ADD(uc))
#define EE_mchp_timer_stop(uc) EE_hal_timer_stop((MicoTimer_t*)EE_BASE_ADD(uc))
#define EE_mchp_timer_set_callback(lc, cbk) EE_hal_timer_set_callback(& EE_ST_NAME(lc), cbk)
#define EE_mchp_timer_get_val(uc, va) EE_hal_timer_get_val((MicoTimer_t*)EE_BASE_ADD(uc), va)
#define EE_timer_soft_init(a, b, c) EE_timer_hard_init(a, b, c)

__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_timer_hard_init(EE_UINT8 id, EE_UINT16 period, EE_UINT8 prescale)
{
	EE_INT8 ret;
	
	#if defined(EE_TIMER1_NAME_LC) && defined(EE_TIMER2_NAME_LC)
	if(id==1)
		ret = EE_mchp_timer_init(EE_TIMER1_NAME_LC, period, prescale);
	else 
		ret = EE_mchp_timer_init(EE_TIMER2_NAME_LC, period, prescale);
	#else
		#if defined(EE_UART1_NAME_LC)
		ret = EE_mchp_timer_init(EE_TIMER1_NAME_LC, period, prescale);
		#else	
		ret = EE_mchp_timer_init(EE_TIMER2_NAME_LC, period, prescale);
		#endif
	#endif
	
	return ret;
}

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
#endif // #ifdef __USE_MICO_PIC_API__

#endif //#ifdef __USE_TIMER__

#endif //__INCLUDE_EEMCUMICO32_TIMER_INTERNAL_H__
