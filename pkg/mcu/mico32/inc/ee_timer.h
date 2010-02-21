/** 
* ee_timer.h
*/

#ifndef __INCLUDE_EEMCUMICO32_TIMER_H__
#define __INCLUDE_EEMCUMICO32_TIMER_H__

#include "ee.h"							// to use Erika Enterprise data types.
#include "cpu/mico32/inc/ee_irq.h"		// to use ISR functions.
#include <system_conf.h>				// to use mico32 symbols and names.
#include "MicoTimer.h"					// to use LATTICE data structures.
#include "mcu/mico32/inc/ee_timer2.h"	// to use Timer0 functions.
#include "mcu/mico32/inc/ee_timer1.h"	// to use Timer1 functions.

/*********************************************************************
     *                                                    
     * Timer Device Register-map                         
     *                                                    
**********************************************************************/
//	typedef struct st_MicoTimer
//	{
//        volatile unsigned int Status;
//        volatile unsigned int Control;
//        volatile unsigned int Period;
//        volatile unsigned int Snapshot;
//	}MicoTimer_t;


/*************************************************** 
* Symbols and macros definition
****************************************************/
// ATT!!! timer0 is reserved because it is used by the EE kernel for counters and alarms (periodic tasks).

#ifndef EE_MICO32_CBK_DEFINED
#define EE_MICO32_CBK_DEFINED
typedef void (*EE_mico32_ISR_callback)(void);
#endif

typedef struct {
    EE_UINT32 base;
    EE_mico32_ISR_callback cbk;
} EE_timer_st;

extern EE_timer_st ee_timer_st_2;
extern EE_timer_st ee_timer_st_1;

#define EE_TIMER_OK								(0x00)
#define EE_timer_init(name, per, set, isrcbk) 	EE_timer_init_base((name##_BASE_ADDRESS), (name##_IRQ), (per), (set), (isrcbk))
//#define EE_timer_init(name, per, set) 		EE_timer_init_base((name##_BASE_ADDRESS), (per), (set))
//#define EE_timer_set_ISR_callback(name, isrcbk) EE_timer_set_ISR_callback_base((name##_BASE_ADDRESS), (name##_IRQ), (isrcbk))
#define EE_timer_start(name) 					EE_timer_start_base((name##_BASE_ADDRESS))
#define EE_timer_stop(name) 					EE_timer_stop_base((name##_BASE_ADDRESS))
#define EE_timer_get_val(name, addval) 			EE_timer_get_val_base((name##_BASE_ADDRESS), (addval))


/*************************************************** 
* Functions declarations
****************************************************/
//EE_UINT8 EE_timer_init_base(EE_UINT32 base, EE_UINT32 period, EE_UINT32 settings); 
EE_UINT8 EE_timer_init_base(EE_UINT32 base, EE_UINT32 irq_flag, EE_UINT32 period, EE_UINT32 settings, EE_mico32_ISR_callback isr_callback); 
EE_UINT8 EE_timer_start_base(EE_UINT32 base);
EE_UINT8 EE_timer_stop_base(EE_UINT32 base);
EE_UINT32 EE_timer_get_val_base(EE_UINT32 base, EE_UINT32 *val);
EE_UINT8 EE_timer_set_ISR_callback_base(EE_UINT32 base, EE_UINT32 irq_flag, EE_mico32_ISR_callback isr_callback);
void EE_timer_handler(int level);

#endif // __INCLUDE_EEMCUMICO32_TIMER_H__
