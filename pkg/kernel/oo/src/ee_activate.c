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
 * CVS: $Id: ee_activate.c,v 1.5 2006/01/05 14:37:22 pj Exp $
 */

#include "ee_internal.h"

/* ActivateTask:
   - The task is moved from the suspended state to the ready state
   - called from interrupts, from tasks, from StartupHook
   - returns E_OS_LIMIT if too many activations are issued
	     E_OK otherwise
             E_OS_ID if the taskID is invalid (Extended status)
   - clears the events of a task (extended task)

   NOTE: part of this source code is copied into altick.c!
*/

#ifndef __PRIVATE_ACTIVATETASK__
StatusType EE_oo_ActivateTask(TaskType TaskID)
{
  register TaskType tmp,current;
  register EE_FREG flag;
  
#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_ACTIVATETASK+1;
#endif

#ifdef __RN_TASK__
  if (TaskID & EE_REMOTE_TID) {
    EE_TYPERN_PARAM par;
    par.pending = 1;
    /* forward the request to another CPU */
    EE_rn_send(TaskID & ~EE_REMOTE_TID, EE_RN_TASK, par );

#ifdef __OO_ORTI_SERVICETRACE__
    EE_ORTI_servicetrace = EE_SERVICETRACE_ACTIVATETASK;
#endif
    return E_OK;
  }
#endif
  
#ifdef __OO_EXTENDED_STATUS__    
  /* check if the task Id is valid */
  if (TaskID < 0 || TaskID >= EE_MAX_TASK) {
#ifdef __OO_ORTI_LASTERROR__
    EE_ORTI_lasterror = E_OS_ID;
#endif

#ifdef __OO_HAS_ERRORHOOK__
    flag = EE_hal_begin_nested_primitive();
    if (!EE_ErrorHook_nested_flag) {
#ifndef __OO_ERRORHOOK_NOMACROS__
      EE_oo_ErrorHook_ServiceID = OSServiceId_ActivateTask;
      EE_oo_ErrorHook_data.ActivateTask_prm.TaskID = TaskID;
#endif
      EE_ErrorHook_nested_flag = 1;
      ErrorHook(E_OS_ID);
      EE_ErrorHook_nested_flag = 0;
    }
    EE_hal_end_nested_primitive(flag);
#endif

#ifdef __OO_ORTI_SERVICETRACE__
    EE_ORTI_servicetrace = EE_SERVICETRACE_ACTIVATETASK;
#endif

    return E_OS_ID;
  }
#endif

  flag = EE_hal_begin_nested_primitive();
  
  /* check for pending activations */
  if (EE_th_rnact[TaskID] == 0) {
#ifdef __OO_ORTI_LASTERROR__
    EE_ORTI_lasterror = E_OS_LIMIT;
#endif

#ifdef __OO_HAS_ERRORHOOK__
    if (!EE_ErrorHook_nested_flag) {
#ifndef __OO_ERRORHOOK_NOMACROS__
      EE_oo_ErrorHook_ServiceID = OSServiceId_ActivateTask;
      EE_oo_ErrorHook_data.ActivateTask_prm.TaskID = TaskID;
#endif
      EE_ErrorHook_nested_flag = 1;
      ErrorHook(E_OS_LIMIT);
      EE_ErrorHook_nested_flag = 0;
    }
#endif

    EE_hal_end_nested_primitive(flag);

#ifdef __OO_ORTI_SERVICETRACE__
    EE_ORTI_servicetrace = EE_SERVICETRACE_ACTIVATETASK;
#endif

    return E_OS_LIMIT;
  } 
  EE_th_rnact[TaskID]--;
  
  /* see also thendin.c
     put the task in the ready state:
     - if the task is basic/BCC1 or extended it can be here only because
     it had rnact=1 before the call, and so it is in suspended state
     - if the task is basic/BCC2 it can be that it is ready or 
     running. in that case we have to check and queue it anyway
  */
#if defined(__OO_BCC2__) || defined(__OO_ECC2__)
  if (EE_th_status[TaskID] == SUSPENDED) {
    EE_th_status[TaskID] = READY;
#ifdef __OO_ECC2__
    /* When an extended task is transferred from suspended state
       into ready state all its events are cleared*/
    EE_th_event_active[TaskID] = 0;
#endif
  }
#else
  EE_th_status[TaskID] = READY;
#ifdef __OO_ECC1__
  /* When an extended task is transferred from suspended state
     into ready state all its events are cleared*/
  EE_th_event_active[TaskID] = 0;
#endif
#endif
  
  /* insert the task in the ready queue */
  EE_rq_insert(TaskID);
  
  /* check for preemption: 
     this test has to be done only if we are inside a task */ 
  if (!EE_hal_get_IRQ_nesting_level()
#if defined(__OO_HAS_STARTUPHOOK__) || defined(__OO_AUTOSTART_TASK__)
      && !EE_oo_no_preemption
#endif
      ) {
    /* we are inside a task */
    tmp = EE_rq_queryfirst();
    if (tmp != EE_NIL) {
      if (EE_sys_ceiling < EE_th_ready_prio[tmp]) {
	/* we have to schedule a ready thread */
	
	current = EE_stk_queryfirst();
	if (current != EE_NIL) { 
	  /* the if is needed because this function can be called from
	     the main task */
#ifdef __OO_HAS_POSTTASKHOOK__
	  PostTaskHook();
#endif	
	  /* the running task is now suspended */
	  EE_th_status[current] = READY;
	}

	/* and another task is put into the running state */
	EE_th_status[tmp] = RUNNING;
	
	EE_sys_ceiling |= EE_th_dispatch_prio[tmp];

#ifdef __OO_ORTI_PRIORITY__
	EE_ORTI_th_priority[tmp] = EE_th_dispatch_prio[tmp];
#endif

#if defined(__OO_ECC1__) || defined(__OO_ECC2__)
	tmp = EE_rq2stk_exchange();
	if (EE_th_waswaiting[tmp]) {
	  EE_th_waswaiting[tmp] = 0;
	  EE_hal_stkchange(tmp);
	}
	else
	  EE_hal_ready2stacked(tmp);
#else
	EE_hal_ready2stacked(EE_rq2stk_exchange());
#endif

#ifdef __OO_HAS_PRETASKHOOK__
	/* the if is needed because this function can be called from
	   the main task */
	if (current != EE_NIL) {
	  PreTaskHook();
	}
#endif	
      }
    }
  }
  
  EE_hal_end_nested_primitive(flag);
  
#ifdef __OO_ORTI_SERVICETRACE__
    EE_ORTI_servicetrace = EE_SERVICETRACE_ACTIVATETASK;
#endif

  return E_OK;
}

#endif
