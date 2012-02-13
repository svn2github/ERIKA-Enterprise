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
/*
#if 0 && defined __OO_EXTENDED_STATUS__  Disabled! 
StatusType EE_oo_GetTaskID(TaskRefType TaskID);
#else
*/
__INLINE__ void __ALWAYS_INLINE__ EE_oo_GetTaskID(TaskRefType TaskID)
{
  EE_ORTI_set_service_in(EE_SERVICETRACE_GETTASKID);

  if (TaskID != (TaskRefType)NULL) {
    *TaskID = EE_stk_queryfirst();
  }

  EE_ORTI_set_service_out(EE_SERVICETRACE_GETTASKID);
}
/*#endif*/ /* __OO_EXTENDED_STATUS__ */
#endif

/***************************************************************************
 * 13.3 Interrupt handling 
 ***************************************************************************/

/* 13.3.2.1: BCC1, BCC2, ECC1, ECC2 */
#if (! defined(__PRIVATE_ENABLEALLINTERRUPTS__)) \
 && (! defined(__EE_MEMORY_PROTECTION__))
__INLINE__ void __ALWAYS_INLINE__ EE_oo_EnableAllInterrupts(void)
{
  EE_ORTI_set_service_in(EE_SERVICETRACE_ENABLEALLINTERRUPTS);

  EE_hal_enableIRQ();

  EE_ORTI_set_service_out(EE_SERVICETRACE_ENABLEALLINTERRUPTS);
}
#endif

/* 13.3.2.2: BCC1, BCC2, ECC1, ECC2 */
#if (! defined(__PRIVATE_DISABLEALLINTERRUPTS__)) \
 && (! defined(__EE_MEMORY_PROTECTION__))
__INLINE__ void __ALWAYS_INLINE__ EE_oo_DisableAllInterrupts(void)
{
  EE_ORTI_set_service_in(EE_SERVICETRACE_DISABLEALLINTERRUPTS);

  EE_hal_disableIRQ();

  EE_ORTI_set_service_out(EE_SERVICETRACE_DISABLEALLINTERRUPTS);
}
#endif /* ! __PRIVATE_DISABLEALLINTERRUPTS__) && ! __EE_MEMORY_PROTECTION__ */

/* 13.3.2.3: BCC1, BCC2, ECC1, ECC2 */
#if (! defined(__PRIVATE_RESUMEALLINTERRUPTS__)) \
 && (! defined(__EE_MEMORY_PROTECTION__))
__INLINE__ void __ALWAYS_INLINE__ EE_oo_ResumeAllInterrupts(void)
{
  EE_ORTI_set_service_in(EE_SERVICETRACE_RESUMEALLINTERRUPTS);

  EE_oo_IRQ_disable_count--;
  if (EE_oo_IRQ_disable_count == 0U) {
    EE_hal_enableIRQ();
  }

  EE_ORTI_set_service_out(EE_SERVICETRACE_RESUMEALLINTERRUPTS);
}
#endif /* ! __PRIVATE_RESUMEALLINTERRUPTS__ && ! __EE_MEMORY_PROTECTION__ */

/* 13.3.2.4: BCC1, BCC2, ECC1, ECC2 */
#if (! defined(__PRIVATE_SUSPENDALLINTERRUPTS__)) \
 && (! defined(__EE_MEMORY_PROTECTION__))
__INLINE__ void __ALWAYS_INLINE__ EE_oo_SuspendAllInterrupts(void)
{
  EE_ORTI_set_service_in(EE_SERVICETRACE_SUSPENDALLINTERRUPTS);

  if (EE_oo_IRQ_disable_count == 0U) {
    EE_hal_disableIRQ();
  }
  EE_oo_IRQ_disable_count++;

  EE_ORTI_set_service_out(EE_SERVICETRACE_SUSPENDALLINTERRUPTS);
}
#endif /* ! __PRIVATE_SUSPENDALLINTERRUPTS__ && ! __EE_MEMORY_PROTECTION__ */

/* 13.3.2.5: BCC1, BCC2, ECC1, ECC2 */
#if (! defined(__PRIVATE_RESUMEOSINTERRUPTS__)) \
 && (! defined(__EE_MEMORY_PROTECTION__))
__INLINE__ void __ALWAYS_INLINE__ EE_oo_ResumeOSInterrupts(void)
{
  EE_ORTI_set_service_in(EE_SERVICETRACE_RESUMEOSINTERRUPTS);

  EE_oo_IRQ_disable_count--;
  if (EE_oo_IRQ_disable_count == 0U) {
    EE_hal_enableIRQ();
  }

  EE_ORTI_set_service_out(EE_SERVICETRACE_RESUMEOSINTERRUPTS);
}
#endif /* ! __PRIVATE_RESUMEOSINTERRUPTS__ && ! __EE_MEMORY_PROTECTION__ */

/* 13.3.2.6: BCC1, BCC2, ECC1, ECC2 */
#if (! defined(__PRIVATE_SUSPENDOSINTERRUPTS__)) \
 && (! defined(__EE_MEMORY_PROTECTION__))
__INLINE__ void __ALWAYS_INLINE__ EE_oo_SuspendOSInterrupts(void)
{
  EE_ORTI_set_service_in(EE_SERVICETRACE_SUSPENDOSINTERRUPTS);

  if (EE_oo_IRQ_disable_count == 0U) {
    EE_hal_disableIRQ();
  }
  EE_oo_IRQ_disable_count++;

  EE_ORTI_set_service_out(EE_SERVICETRACE_SUSPENDOSINTERRUPTS);
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
  /* both assignment to enable smart debuggers to notice the entry and
     exit from getactiveapplicationmode.
     Note that the variable is volatile, so both the writings succeeds
  */
  EE_ORTI_set_service_in(EE_SERVICETRACE_GETACTIVEAPPLICATIONMODE);
  EE_ORTI_set_service_out(EE_SERVICETRACE_GETACTIVEAPPLICATIONMODE);

  return EE_ApplicationMode; 
}
#endif

#ifdef __MSRP__
__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_oo_isGlobal(ResourceType ResID)
{
  register EE_UREG isGlobal, ureg_tmp1, ureg_tmp2;
  EE_SREG sreg_tmp;
/* mask off the MSB, that indicates whether this is a global or a
     local resource */

  /*
   * This is the compact expression
   * isGlobal = ((ResID & EE_GLOBAL_MUTEX) != (ResourceType)0U);
   *
   * The following is the extended version introduced to
   * meet MISRA requirements
   */
  ureg_tmp1 = (ResID & EE_GLOBAL_MUTEX);
  ureg_tmp2 = (ResourceType)0U;
  sreg_tmp = (EE_SREG)(ureg_tmp1 != ureg_tmp2);
  isGlobal = (EE_UREG)sreg_tmp;

  return isGlobal;
}
#endif

#endif /* __INCLUDE_OO_INLINE_H__ */
