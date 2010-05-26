/*
  Name: ee_timer.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.28
  Description: Timer library header file. 
*/

#ifndef __INCLUDE_EEMCUMICO32_TIMER_H__
#define __INCLUDE_EEMCUMICO32_TIMER_H__

#include "cpu/mico32/inc/ee_internal.h"
#include "mcu/mico32/inc/ee_internal.h"
#include "mcu/mico32/inc/ee_buffer.h"
#include <cpu/mico32/inc/ee_irq.h>
#include "MicoTimer.h"					// to use LATTICE data structures.
 
/* mico-timer register structure (defined in MicoTimer.h) */
// typedef struct st_MicoTimer{
	// volatile unsigned int Status;
	// volatile unsigned int Control;
	// volatile unsigned int Period;
	// volatile unsigned int Snapshot;
// }MicoTimer_t; 
 
/* Symbols and macros */
#define EE_TIMER_OK			(0x00)
#define EE_timer_need_enable_int(mode)  ( (mode) & MICO32_TIMER_CONTROL_INT_BIT_MASK )

/*
	__INLINE__ int __ALWAYS_INLINE__  EE_hal_timer_start(MicoTimer_t* base)
	Function to start the timer.
*/
__INLINE__ int __ALWAYS_INLINE__  EE_hal_timer_start(MicoTimer_t* base)
{
	base->Control |= MICO32_TIMER_CONTROL_START_BIT_MASK; 
	return EE_TIMER_OK;
}

/*
	__INLINE__ int __ALWAYS_INLINE__  EE_hal_timer_stop(MicoTimer_t* base)
	Function to stop the timer.
*/
__INLINE__ int __ALWAYS_INLINE__  EE_hal_timer_stop(MicoTimer_t* base)
{
	base->Control |= MICO32_TIMER_CONTROL_STOP_BIT_MASK; 
	base->Status = 0;
	return EE_TIMER_OK;
}

/*
	__INLINE__ int __ALWAYS_INLINE__  EE_hal_timer_get_val(MicoTimer_t* base, EE_UINT32 *val)
	Function to get the timer value.
*/
__INLINE__ int __ALWAYS_INLINE__  EE_hal_timer_get_val(MicoTimer_t* base, EE_UINT32 *val)
{
	*val = base->Snapshot;
	return EE_TIMER_OK;
}

/*
	__INLINE__ int __ALWAYS_INLINE__  EE_hal_timer_enable_IRQ(MicoTimer_t* base)
	Function to enable IRQ.
*/
__INLINE__ int __ALWAYS_INLINE__  EE_hal_timer_enable_IRQ(MicoTimer_t* base)
{
	base->Control |= MICO32_TIMER_CONTROL_INT_BIT_MASK;
	return EE_TIMER_OK;
}

/*
	__INLINE__ int __ALWAYS_INLINE__  EE_hal_timer_disable_IRQ(MicoTimer_t* base)
	Function to disable IRQ.
*/
__INLINE__ int __ALWAYS_INLINE__  EE_hal_timer_disable_IRQ(MicoTimer_t* base)
{
	base->Control &= ~MICO32_TIMER_CONTROL_INT_BIT_MASK;
	return EE_TIMER_OK;
}

#ifdef __USE_TIMER_IRQ__

/* Macro for Structure declaration */
#define DECLARE_STRUCT_TIMER(uc, lc) \
	extern EE_timer_st EE_ST_NAME(lc);
/* Macro for structure definition */
#define DEFINE_STRUCT_TIMER(uc, lc) \
EE_timer_st cat3(ee_, lc, _st) = { \
	.base= (MicoTimer_t*)cat2(uc, _BASE_ADDRESS),\
	.irqf= cat2(uc, _IRQ),\
	.cbk= EE_NULL_CBK };
	
/* Timer structure */
typedef struct {
    MicoTimer_t* base;
    int irqf;							// irq flag to register the handler
    EE_ISR_callback cbk;
} EE_timer_st;

/*
		int EE_hal_timer_init(EE_timer_st* tst, int period, int settings);
		Function to init the timer.
*/
int EE_hal_timer_init(EE_timer_st* tst, int period, int settings);

/*
	__INLINE__ int __ALWAYS_INLINE__  EE_hal_timer_set_callback(EE_timer_st* tst, EE_ISR_callback cbk)
	Function to record the isr callback user function to be called at the end of the interrupt handler.
*/
__INLINE__ int __ALWAYS_INLINE__  EE_hal_timer_set_callback(EE_timer_st* tst, EE_ISR_callback cbk)
{
	tst->cbk = cbk;
	return EE_TIMER_OK;
}

/*
	void EE_timer_common_handler(int level);
	IRQ handler.
*/
void EE_timer_common_handler(int level);

#ifndef __STATIC_ISR_TABLE__
__INLINE__ void __ALWAYS_INLINE__ EE_hal_timer_handler_setup(EE_timer_st* tst)
{
	/* Register IRQ handler */
    EE_mico32_register_ISR(tst->irqf, EE_timer_common_handler);	
}
#else // __STATIC_ISR_TABLE__
#define EE_hal_timer_handler_setup(tst)
#endif // __STATIC_ISR_TABLE__

/* 
	Macros for TIMER driver API generation (irq mode)
*/ 
#define DECLARE_FUNC_TIMER(uc, lc) \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _init)(int period, int settings){ \
	return EE_hal_timer_init(& EE_ST_NAME(lc), period, settings); } \
__INLINE__ int __ALWAYS_INLINE__  cat3(EE_, lc, _on)(void){ \
	return EE_hal_timer_start((MicoTimer_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__  cat3(EE_, lc, _off)(void){ \
	return EE_hal_timer_stop((MicoTimer_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__  cat3(EE_, lc, _set_ISR_callback)(EE_ISR_callback cbk){ \
	return EE_hal_timer_set_callback(& EE_ST_NAME(lc), cbk); } \
__INLINE__ int __ALWAYS_INLINE__  cat3(EE_, lc, _get_value)(EE_UINT32 *val){ \
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

__INLINE__ EE_timer_st * __ALWAYS_INLINE__ EE_get_timer_st_from_level(int level)
{
	#ifdef EE_TIMER1_NAME_UC
	if (level == EE_IRQ_NAME(EE_TIMER1_NAME_UC))
        return & EE_ST_NAME(EE_TIMER1_NAME_LC);
	#endif
	#ifdef EE_TIMER2_NAME_UC
	if (level == EE_IRQ_NAME(EE_TIMER2_NAME_UC))
        return & EE_ST_NAME(EE_TIMER2_NAME_LC);
	#endif
	#ifdef EE_TIMER3_NAME_UC
	if (level == EE_IRQ_NAME(EE_TIMER3_NAME_UC))
        return & EE_ST_NAME(EE_TIMER3_NAME_LC);
	#endif
	#ifdef EE_TIMER4_NAME_UC
	if (level == EE_IRQ_NAME(EE_TIMER4_NAME_UC))
        return & EE_ST_NAME(EE_TIMER4_NAME_LC);
	#endif
	return (EE_timer_st *)0;
}

// #ifndef EE_TIMER2_NAME_UC
// /* If there is only one component of this kind, no test is done */
// __INLINE__ EE_timer_st * __ALWAYS_INLINE__ EE_get_timer_st_from_level(int level)
// {
    // return & EE_ST_NAME(EE_TIMER1_NAME_LC);
// }
// #else /* #ifndef EE_TIMER_NAME2_UC */
// __INLINE__ EE_timer_st * __ALWAYS_INLINE__ EE_get_timer_st_from_level(int level)
// {
    // switch (level) {
    // default:
        // return & EE_ST_NAME(EE_TIMER1_NAME_LC);
// #ifdef EE_TIMER2_NAME_UC
    // case EE_IRQ_NAME(EE_TIMER2_NAME_UC):
        // return & EE_ST_NAME(EE_TIMER2_NAME_LC);
// #endif
// #ifdef EE_TIMER3_NAME_UC
    // case EE_IRQ_NAME(EE_TIMER3_NAME_UC):
        // return & EE_ST_NAME(EE_TIMER3_NAME_LC);
// #endif
// #ifdef EE_TIMER4_NAME_UC
    // case EE_IRQ_NAME(EE_TIMER4_NAME_UC):
        // return & EE_ST_NAME(EE_TIMER4_NAME_LC);
// #endif
    // }
// }
// #endif /* #ifndef EE_TIMER_NAME2_UC */

#else // #ifdef __USE_TIMER_IRQ__ --------------------------------------------------------------------------------

/*
	int EE_hal_timer_init(MicoTimer_t* timerc, int irqf, int period, int settings);
	Function to init the timer.
*/
int EE_hal_timer_init(MicoTimer_t* timerc, int irqf, int period, int settings);

/* 
	Macros for TIMER driver API generation (polling mode)
*/ 
#define DECLARE_FUNC_TIMER(uc, lc) \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _init)(int period, int settings){ \
	return EE_hal_timer_init((MicoTimer_t*)EE_BASE_ADD(uc), (int)EE_IRQ_NAME(uc), period, settings); } \
__INLINE__ int __ALWAYS_INLINE__  cat3(EE_, lc, _on)(void){ \
	return EE_hal_timer_start((MicoTimer_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__  cat3(EE_, lc, _off)(void){ \
	return EE_hal_timer_stop((MicoTimer_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__  cat3(EE_, lc, _get_value)(EE_UINT32 *val){ \
	return EE_hal_timer_get_val((MicoTimer_t*)EE_BASE_ADD(uc), val); } \
__INLINE__ int __ALWAYS_INLINE__  cat3(EE_, lc, _enable_IRQ)(void){ \
	return EE_hal_timer_enable_IRQ((MicoTimer_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__  cat3(EE_, lc, _disable_IRQ)(void){ \
	return EE_hal_timer_disable_IRQ((MicoTimer_t*)EE_BASE_ADD(uc)); }

#endif	// #ifdef __USE_TIMER_IRQ__

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

#ifdef __USE_MICO_PIC32LIKE_API__
#include "mcu/mico32/inc/ee_timer_pic32like_api.h"
#endif // #ifdef __USE_MICO_PIC32LIKE_API__

#endif // __INCLUDE_EEMCUMICO32_TIMER_H__

