/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation, 
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/*
 * Author: 2002 Paolo Gai
 * CVS: $Id: ee_internal.h,v 1.6 2006/12/03 22:07:50 pj Exp $
 */

#include "kernel/oo/inc/ee_common.h"
#include "kernel/oo/inc/ee_intfunc.h"

#ifndef __INCLUDE_OO_INTERNAL_H__
#define __INCLUDE_OO_INTERNAL_H__

/*************************************************************************
 HAL extensions
 *************************************************************************/

 /* these are the functions that have been inserted to support tha OO layer
    under the EE HAL.
    
    - all the functions for interrupt handling (13.3)
    - EE_hal_begin_nested_primitive
      EE_hal_end_nested_primitive 
      (for primitives that can be called both into a task and into an ISR2
    - EE_hal_terminate_task(EE_TID t)
    - EE_hal_terminate_savestk(EE_TID t)
    - EE_oo_shutdown() if not redefined it does for(;;);
    - All the alarm constants listed in 13.6.4
 */


/***************************************************************************
 * Internal data structures and functions
 ***************************************************************************/

#ifdef __OO_HAS_ERRORHOOK__
extern EE_TYPEBOOL EE_ErrorHook_nested_flag;
#endif

/* a flag that says if we are inside the startupHook/autostart rutines or not */
#if defined(__OO_HAS_STARTUPHOOK__) || defined(__OO_AUTOSTART_TASK__) || defined(__OO_AUTOSTART_ALARM__)
/* this variable is defined into lookup.c! */
extern EE_TYPEBOOL EE_oo_no_preemption;
#endif

#if defined(__OO_BCC2__) || defined(__OO_ECC2__)
/* a lookup table to speedup ready queue handling */
extern const EE_INT8 EE_rq_lookup[];
#endif

/* Internal Queue management functions */

/* return the first ready task without extracting it */
#ifndef __PRIVATE_RQ_QUERYFIRST__
#if defined(__OO_BCC1__) || defined(__OO_ECC1__)
__INLINE__ EE_TID __ALWAYS_INLINE__ EE_rq_queryfirst(void)
{ return EE_rq_first; }
#endif

#if defined(__OO_BCC2__) || defined(__OO_ECC2__)
EE_TID EE_rq_queryfirst(void);
#endif
#endif

/* __INLINE__ EE_TID __ALWAYS_INLINE__ EE_stk_queryfirst(void) in intfunc.h */

/* extract the running task from the stack */
#ifndef __PRIVATE_STK_GETFIRST__
__INLINE__ void __ALWAYS_INLINE__ EE_stk_getfirst(void)
{
    EE_stkfirst = EE_th_next[EE_stkfirst];
}
#endif

/* insert a task into the stack  data structures */
#ifndef __PRIVATE_STK_INSERTFIRST__
__INLINE__ void __ALWAYS_INLINE__ EE_stk_insertfirst(EE_TID t)
{
    EE_th_next[t] = EE_stkfirst;
    EE_stkfirst = t;
}
#endif

/* insert a task into the ready queue */
#ifndef __PRIVATE_RQ_INSERT__
void EE_rq_insert(EE_TID t);
#endif

/* put the first ready task into the stack */
#ifndef __PRIVATE_RQ2STK_EXCHANGE__
EE_TID EE_rq2stk_exchange(void);
#endif

#ifndef __PRIVATE_SHUTDOWN__
__INLINE__ void __ALWAYS_INLINE__ EE_oo_shutdown(void) { for(;;); }
#endif

/* This call terminates a thread instance. It must be called as the
   LAST function call BEFORE the `}' that ends a thread. If the
   primitive is not inserted at the end of */
#ifndef __PRIVATE_THREAD_END_INSTANCE__
void EE_thread_end_instance(void);
#endif

#ifndef __PRIVATE_IRQ_END_INSTANCE__
/* This primitive shall be atomic.
   This primitive shall be inserted as the last function in an IRQ handler.
   If the HAL allow IRQ nesting the C_end_instance should work as follows:
   - it must implement the preemption test only if it is the last IRQ on the stack
   - if there are other interrupts on the stack the IRQ end_instance should do nothing
*/
void EE_IRQ_end_instance(void);
#endif



/* 13.2.3 System services                                                  */
/* ----------------------------------------------------------------------- */

/* used by Startos */
/* 13.2.3.1: BCC1, BCC2, ECC1, ECC2 */
#ifndef __PRIVATE_ACTIVATETASK__
StatusType EE_oo_ActivateTask(TaskType TaskID);
#endif


/***************************************************************************
 * 13.5 Event control 
 ***************************************************************************/

/* 13.5.3 System services                                                  */
/* ----------------------------------------------------------------------- */

/* see ee_kernel.h - this function is here because used by the rn */
/* 13.5.3.1: ECC1, ECC2 */
#if defined(__OO_ECC1__) || defined(__OO_ECC2__)
#ifndef __PRIVATE_SETEVENT__
#ifdef __OO_EXTENDED_STATUS__
StatusType EE_oo_SetEvent(TaskType TaskID, EventMaskType Mask);
#else
void EE_oo_SetEvent(TaskType TaskID, EventMaskType Mask);
#endif
#endif
#endif


/***************************************************************************
 * 13.6 Alarms 
 ***************************************************************************/

#ifndef __OO_NO_ALARMS__

/*
  This function is used by Remote Notifications
  see ee_kernel.h
*/
#ifndef __PRIVATE_COUNTER_TICK__
void EE_oo_counter_tick(EE_TYPECOUNTER c);
#endif


/* 13.6.3 System services                                                  */
/* ----------------------------------------------------------------------- */

/* used by Startos */
/* 13.6.3.3 BCC1, BCC2, ECC1, ECC2; Events only ECC1, ECC2 */
#ifndef __PRIVATE_SETRELALARM__
StatusType EE_oo_SetRelAlarm(AlarmType AlarmID, TickType increment, TickType cycle);
#endif

#endif



/* 13.8.2 System services                                                  */
/* ----------------------------------------------------------------------- */

/* These declarations are duplicated into ee_kernel.h */

/* 13.8.2.1: BCC1, BCC2, ECC1, ECC2 */
#ifdef __OO_HAS_ERRORHOOK__
void ErrorHook(StatusType Error);
#endif

/* 13.8.2.2: BCC1, BCC2, ECC1, ECC2 */
#ifdef __OO_HAS_PRETASKHOOK__
void PreTaskHook(void);
#endif

/* 13.8.2.3: BCC1, BCC2, ECC1, ECC2 */
#ifdef __OO_HAS_POSTTASKHOOK__
void PostTaskHook(void);
#endif

/* 13.8.2.4: BCC1, BCC2, ECC1, ECC2 */
#ifdef __OO_HAS_STARTUPHOOK__
void StartupHook(void);
#endif

/* 13.8.2.5: BCC1, BCC2, ECC1, ECC2 */
#ifdef __OO_HAS_SHUTDOWNHOOK__
void ShutdownHook(StatusType Error);
#endif


#endif
