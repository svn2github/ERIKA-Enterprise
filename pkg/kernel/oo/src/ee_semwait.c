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
 * CVS: $Id: ee_semwait.c,v 1.2 2006/12/03 22:07:50 pj Exp $
 */

#include "ee_internal.h"

/* WaitSem:
   - can be called from an extended task only
   - the task state is put to wait until a call to PostSem wakes it up
   - if the task blocks -> reschedulig + internal resource released
   - returns (only extended status)
       E_OS_RESOURCE task occupies a resource
       E_OS_ACCESS   if the task is not an extended task
       E_OS_CALLEVEL called at interrupt level
*/


#if defined(__OO_ECC1__) || defined(__OO_ECC2__)
#ifndef __PRIVATE_WAITSEM__

#ifdef __OO_EXTENDED_STATUS__
StatusType EE_oo_WaitSem(SemRefType Sem)
#else
void EE_oo_WaitSem(SemRefType Sem)
#endif
{
  TaskType current, tmp;
  register EE_FREG np_flags;

#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_WAITSEM+1U;
#endif

  current = EE_stk_queryfirst();

#ifdef __OO_EXTENDED_STATUS__    

  /* check for a call at interrupt level:
   * Note: this must be the FIRST error check!!!
   */
  if (EE_hal_get_IRQ_nesting_level() || current==EE_NIL) {
#ifdef __OO_ORTI_LASTERROR__
    EE_ORTI_lasterror = E_OS_CALLEVEL;
#endif

#ifdef __OO_HAS_ERRORHOOK__
    np_flags = EE_hal_begin_nested_primitive();
    if (!EE_ErrorHook_nested_flag) {
#ifndef __OO_ERRORHOOK_NOMACROS__
      EE_oo_ErrorHook_ServiceID = OSServiceId_WaitSem;
      EE_oo_ErrorHook_data.WaitSem_prm.Sem = Sem;
#endif
      EE_ErrorHook_nested_flag = 1;
      ErrorHook(E_OS_CALLEVEL);
      EE_ErrorHook_nested_flag = 0;
    }
    EE_hal_end_nested_primitive(np_flags);
#endif

#ifdef __OO_ORTI_SERVICETRACE__
    EE_ORTI_servicetrace = EE_SERVICETRACE_WAITSEM;
#endif

    return E_OS_CALLEVEL;
  }

#ifndef __OO_NO_RESOURCES__
  /* check for busy resources */ 
  if (EE_th_resource_last[current] != EE_UREG_MINUS1) {
#ifdef __OO_ORTI_LASTERROR__
    EE_ORTI_lasterror = E_OS_RESOURCE;
#endif

#ifdef __OO_HAS_ERRORHOOK__
    np_flags = EE_hal_begin_nested_primitive();
    if (!EE_ErrorHook_nested_flag) {  
#ifndef __OO_ERRORHOOK_NOMACROS__
      EE_oo_ErrorHook_ServiceID = OSServiceId_WaitSem;
      EE_oo_ErrorHook_data.WaitSem_prm.Sem = Sem;
#endif
      EE_ErrorHook_nested_flag = 1;
      ErrorHook(E_OS_RESOURCE);
      EE_ErrorHook_nested_flag = 0;
    }
    EE_hal_end_nested_primitive(np_flags);
#endif

#ifdef __OO_ORTI_SERVICETRACE__
    EE_ORTI_servicetrace = EE_SERVICETRACE_WAITSEM;
#endif

    return E_OS_RESOURCE;
  }
#endif

  /* check if the task is an extended task */
  if (!EE_th_is_extended[current]) {
#ifdef __OO_ORTI_LASTERROR__
    EE_ORTI_lasterror = E_OS_ACCESS;
#endif

#ifdef __OO_HAS_ERRORHOOK__
    np_flags = EE_hal_begin_nested_primitive();
    if (!EE_ErrorHook_nested_flag) {
#ifndef __OO_ERRORHOOK_NOMACROS__
      EE_oo_ErrorHook_ServiceID = OSServiceId_WaitSem;
      EE_oo_ErrorHook_data.WaitSem_prm.Sem = Sem;
#endif
      EE_ErrorHook_nested_flag = 1;
      ErrorHook(E_OS_ACCESS);
      EE_ErrorHook_nested_flag = 0;
    }
    EE_hal_end_nested_primitive(np_flags);
#endif

#ifdef __OO_ORTI_SERVICETRACE__
    EE_ORTI_servicetrace = EE_SERVICETRACE_WAITSEM;
#endif

    return E_OS_ACCESS;
  }
#endif

  np_flags = EE_hal_begin_nested_primitive();

  /* handle a local semaphore queue */
  /* check if we have to wait */
  if (Sem->count) {
    Sem->count--;
  }
  else {
#ifdef __OO_HAS_POSTTASKHOOK__
    PostTaskHook();
#endif 

    /* extract the task from the stk data structure
     * current was filled at the beginning of the function
     */
    EE_stk_getfirst();

    /* the task must go into the WAITING state */
    EE_th_status[current] = WAITING;

    /* reset the thread priority bit in the system_ceiling */
    EE_sys_ceiling &= ~EE_th_dispatch_prio[current];
    /* the ready priority is not touched, it is not the same as Schedule! */

#ifdef __OO_ORTI_PRIORITY__
    EE_ORTI_th_priority[current] = 0;
#endif

    /* queue the task inside the semaphore queue */
    if (Sem->first != EE_NIL)
      // the semaphore queue is not empty
      EE_th_next[Sem->last] = current;
    else
      // the semaphore queue is empty
      Sem->first = current;
    Sem->last = current;
    EE_th_next[current] = EE_NIL;
	

    /* since the task blocks, it has to be woken up by another
       EE_hal_stkchange */
    EE_th_waswaiting[current] = 1;

    /* then, the task will be woken up by a PostSem using a EE_hal_stkchange... */

    /* check if there is to schedule a ready thread or pop a preempted
     * thread 
     */
    tmp = EE_rq_queryfirst();

    if (tmp == EE_NIL ||
        EE_sys_ceiling >= EE_th_ready_prio[tmp])
    {
        /* we have to schedule an interrupted thread that is on the top 
         * of its stack; the state is already STACKED! */
        tmp = EE_stk_queryfirst();
	if (tmp != EE_NIL)
	  EE_th_status[tmp] = RUNNING;
        EE_hal_stkchange(tmp);
    }
    else { 
        /* we have to schedule a ready thread that is not yet on the stack */
        EE_th_status[tmp] = RUNNING;
        EE_sys_ceiling |= EE_th_dispatch_prio[tmp];

#ifdef __OO_ORTI_PRIORITY__
	EE_ORTI_th_priority[tmp] = EE_th_dispatch_prio[tmp];
#endif

	tmp = EE_rq2stk_exchange();
	if (EE_th_waswaiting[tmp]) {
	  EE_th_waswaiting[tmp] = 0;
	  EE_hal_stkchange(tmp);
	}
	else
	  EE_hal_ready2stacked(tmp);
    }

    /* We do not have to set the thread priority bit in the
       system_ceiling, it will be set by the primitives that put the
       task in the RUNNING state */

#ifdef __OO_HAS_PRETASKHOOK__
    PreTaskHook();
#endif	
  }
  EE_hal_end_nested_primitive(np_flags);
  
#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_WAITSEM;
#endif

#ifdef __OO_EXTENDED_STATUS__
  return E_OK;
#endif
}

#endif
#endif

