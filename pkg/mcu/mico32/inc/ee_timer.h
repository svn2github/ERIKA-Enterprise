/** 
* ee_timer.h
*/

#ifndef __INCLUDE_EEMCUMICO32_TIMER_H__
#define __INCLUDE_EEMCUMICO32_TIMER_H__

#include "ee.h"			// to refer Erika Enterprise.
#include "cpu/mico32/inc/ee_irq.h"
#include <system_conf.h>
#include "MicoTimer.h"	// to use LATTICE data structures.


//#include "MicoTimerService.h"
//#include "MicoMacros.h"
//#include "MicoInterrupts.h"

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
//#define MICO32_TIMER_STATUS_REG_OFFSET             	  (0x00)
//#define MICO32_TIMER_CONTROL_REG_OFFSET                 (0x04)
//#define MICO32_TIMER_PERIOD_REG_OFFSET                  (0x08)
//#define MICO32_TIMER_SNAPSHOT_REG_OFFSET                (0x0c)
//#define MICO32_TIMER_STATUS_TO_BIT_MASK                 (0x1)
//#define MICO32_TIMER_CONTROL_INT_BIT_MASK               (0x1)
//#define MICO32_TIMER_CONTROL_CONT_BIT_MASK              (0x2)
//#define MICO32_TIMER_CONTROL_START_BIT_MASK             (0x4)
//#define MICO32_TIMER_CONTROL_STOP_BIT_MASK              (0x8)

#define EE_TIMER_OK		(0x00)

#define EE_timer_init(name, per, set) 			EE_timer_init_base((name##_BASE_ADDRESS), (per), (set))
#define EE_timer_set_ISR_callback(name, isrcbk) 	EE_timer_set_ISR_callback_base((name##_BASE_ADDRESS), (name##_IRQ),(isrcbk))
#define EE_timer_start(name) 					EE_timer_start_base((name##_BASE_ADDRESS))
#define EE_timer_stop(name) 					EE_timer_stop_base((name##_BASE_ADDRESS))
#define EE_timer_get_val(name, addval) 			EE_timer_get_val_base((name##_BASE_ADDRESS), (addval))


/*************************************************** 
* Functions declarations
****************************************************/
EE_UINT8 EE_timer_init_base(EE_UINT32 base, EE_UINT32 period, EE_UINT32 settings); 
EE_UINT8 EE_timer_start_base(EE_UINT32 base);
EE_UINT8 EE_timer_stop_base(EE_UINT32 base);
EE_UINT32 EE_timer_get_val_base(EE_UINT32 base, EE_UINT32 *val);
EE_UINT8 EE_timer_set_ISR_callback_base(EE_UINT32 base, EE_UINT32 irq_flag, EE_mico32_ISR_handler isr_callback);


#endif // __INCLUDE_EEMCUMICO32_TIMER_H__
