/** 
* ee_timer.h
*/

#ifdef __USE_TIMER__

#ifndef __INCLUDE_EEMCUMICO32_TIMER_H__
#define __INCLUDE_EEMCUMICO32_TIMER_H__

#include "mcu/mico32/inc/ee_timer_internal.h"

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
// ATT!!! One timer should be reserved because it is used by the EE kernel for counters and alarms (periodic tasks).

/*************************************************** 
* Functions declarations
****************************************************/

#endif // __INCLUDE_EEMCUMICO32_TIMER_H__

#endif //#ifdef __USE_TIMER__
