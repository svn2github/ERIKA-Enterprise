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
 * Author: 2004 Paolo Gai
 * CVS: $Id: ee_inline.h,v 1.3 2006/04/08 21:15:23 pj Exp $
 */

/* This file is ONLY included when we are NOT compiling a library that
   will be used in BINARY DISTRIBUTIONS */

#ifndef __INCLUDE_OO_INLINE_H__
#define __INCLUDE_OO_INLINE_H__


/***************************************************************************
 * Internal data structures and functions
 ***************************************************************************/

#include "kernel/oo/inc/ee_intfunc.h"

/***************************************************************************
 * 13.2 Task management 
 ***************************************************************************/

/* 13.2.3.5: BCC1, BCC2, ECC1, ECC2 */
#ifndef __PRIVATE_GETTASKID__
#if 0 && defined __OO_EXTENDED_STATUS__ /* Disabled! */
StatusType EE_oo_GetTaskID(TaskRefType TaskID);
#else
__INLINE__ void __ALWAYS_INLINE__ EE_oo_GetTaskID(TaskRefType TaskID)
{
#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_GETTASKID+1U;
#endif

  if (TaskID != NULL) {
    *TaskID = EE_stk_queryfirst();
  }

#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_GETTASKID;
#endif
}
#endif /* __OO_EXTENDED_STATUS__ */
#endif

/* 13.2.3.6: BCC1, BCC2, ECC1, ECC2 */
#ifndef __PRIVATE_GETTASKSTATE__
#ifdef __OO_EXTENDED_STATUS__
__INLINE__ StatusType __ALWAYS_INLINE__ EE_oo_GetTaskState(TaskType TaskID, TaskStateRefType State)
{
#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_GETTASKSTATE+1U;
#endif

  if (TaskID < 0 || TaskID >= EE_MAX_TASK) {
#ifdef __OO_ORTI_SERVICETRACE__
    EE_ORTI_servicetrace = EE_SERVICETRACE_GETTASKSTATE;
#endif
    return E_OS_ID;
  }

  if (State != NULL) {
    *State = EE_th_status[TaskID];
  }

#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_GETTASKSTATE;
#endif
  return E_OK;
}
#else
__INLINE__ void __ALWAYS_INLINE__ EE_oo_GetTaskState(TaskType TaskID, TaskStateRefType State)
{
#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_GETTASKSTATE+1U;
#endif

  *State = EE_th_status[TaskID];

#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_GETTASKSTATE;
#endif
}
#endif
#endif


/***************************************************************************
 * 13.3 Interrupt handling 
 ***************************************************************************/


/* 13.3.2.1: BCC1, BCC2, ECC1, ECC2 */
#if ! defined(__PRIVATE_ENABLEALLINTERRUPTS__) \
 && ! defined(__EE_MEMORY_PROTECTION__)
__INLINE__ void __ALWAYS_INLINE__ EE_oo_EnableAllInterrupts(void)
{
#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_ENABLEALLINTERRUPTS+1U;
#endif

  EE_hal_enableIRQ();

#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_ENABLEALLINTERRUPTS;
#endif
}
#endif

/* 13.3.2.2: BCC1, BCC2, ECC1, ECC2 */
#if ! defined(__PRIVATE_DISABLEALLINTERRUPTS__) \
 && ! defined(__EE_MEMORY_PROTECTION__)
__INLINE__ void __ALWAYS_INLINE__ EE_oo_DisableAllInterrupts(void)
{
#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_DISABLEALLINTERRUPTS+1U;
#endif

  EE_hal_disableIRQ();

#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_DISABLEALLINTERRUPTS;
#endif
}
#endif /* ! __PRIVATE_DISABLEALLINTERRUPTS__) && ! __EE_MEMORY_PROTECTION__ */

/* 13.3.2.3: BCC1, BCC2, ECC1, ECC2 */
#if ! defined(__PRIVATE_RESUMEALLINTERRUPTS__) \
 && ! defined(__EE_MEMORY_PROTECTION__)
__INLINE__ void __ALWAYS_INLINE__ EE_oo_ResumeAllInterrupts(void)
{
#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_RESUMEALLINTERRUPTS+1U;
#endif

  EE_oo_IRQ_disable_count--;
  if (!EE_oo_IRQ_disable_count) {
    EE_hal_enableIRQ();
  }

#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_RESUMEALLINTERRUPTS;
#endif
}
#endif /* ! __PRIVATE_RESUMEALLINTERRUPTS__ && ! __EE_MEMORY_PROTECTION__ */

/* 13.3.2.4: BCC1, BCC2, ECC1, ECC2 */
#if ! defined(__PRIVATE_SUSPENDALLINTERRUPTS__) \
 && ! defined(__EE_MEMORY_PROTECTION__)
__INLINE__ void __ALWAYS_INLINE__ EE_oo_SuspendAllInterrupts(void)
{
#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_SUSPENDALLINTERRUPTS+1U;
#endif

  if (!EE_oo_IRQ_disable_count) {
    EE_hal_disableIRQ();
  }
  EE_oo_IRQ_disable_count++;

#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_SUSPENDALLINTERRUPTS;
#endif
}
#endif /* ! __PRIVATE_SUSPENDALLINTERRUPTS__ && ! __EE_MEMORY_PROTECTION__ */

/* 13.3.2.5: BCC1, BCC2, ECC1, ECC2 */
#if ! defined(__PRIVATE_RESUMEOSINTERRUPTS__) \
 && ! defined(__EE_MEMORY_PROTECTION__)
__INLINE__ void __ALWAYS_INLINE__ EE_oo_ResumeOSInterrupts(void)
{
#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_RESUMEOSINTERRUPTS+1U;
#endif

  EE_oo_IRQ_disable_count--;
  if (!EE_oo_IRQ_disable_count) {
    EE_hal_enableIRQ();
  }

#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_RESUMEOSINTERRUPTS;
#endif
}
#endif /* ! __PRIVATE_RESUMEOSINTERRUPTS__ && ! __EE_MEMORY_PROTECTION__ */

/* 13.3.2.6: BCC1, BCC2, ECC1, ECC2 */
#if ! defined(__PRIVATE_SUSPENDOSINTERRUPTS__) \
 && ! defined(__EE_MEMORY_PROTECTION__)
__INLINE__ void __ALWAYS_INLINE__ EE_oo_SuspendOSInterrupts(void)
{
#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_SUSPENDOSINTERRUPTS+1U;
#endif

  if (!EE_oo_IRQ_disable_count) {
    EE_hal_disableIRQ();
  }
  EE_oo_IRQ_disable_count++;

#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_SUSPENDOSINTERRUPTS;
#endif
}
#endif /* ! __PRIVATE_SUSPENDOSINTERRUPTS__ && ! __EE_MEMORY_PROTECTION__ */


/***************************************************************************
 * 13.7 Operating system execution control 
 ***************************************************************************/

/* 13.7.2 System services                                                  */
/* ----------------------------------------------------------------------- */

/* 13.7.2.1: BCC1, BCC2, ECC1, ECC2 */
#ifndef __PRIVATE_GETACTIVEAPPLICATIONMODE__
/* by default there is only 6the default application mode defined!... */
__INLINE__ AppModeType __ALWAYS_INLINE__ EE_oo_GetActiveApplicationMode(void) 
{ 
#ifdef __OO_ORTI_SERVICETRACE__
  /* both assignment to enable smart debuggers to notice the entry and
     exit from getactiveapplicationmode.
     Note that the variable is volatile, so both the writings succeeds
  */
  EE_ORTI_servicetrace = EE_SERVICETRACE_GETACTIVEAPPLICATIONMODE+1U;
  EE_ORTI_servicetrace = EE_SERVICETRACE_GETACTIVEAPPLICATIONMODE;
#endif

  return EE_ApplicationMode; 
}
#endif




#endif
