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
 * CVS: $Id: ee_evset.c,v 1.4 2005/11/03 09:39:48 pj Exp $
 */

#include "ee_internal.h"

/* SetEvent:
   - can be called from ISR and from task level
   - if the task was waiting for one of the events -> wake up it!
   - returns (only extended state)
       E_OS_ID     if task id is invalid
       E_OS_ACCESS if the referenced task is not an extended task
       E_OS_STATE  events cannot be set because the task is in the
                   suspended state

   Note: The implementation of this function can be a little bit
   optimized.  That is, we should check in which queue the task really
   goes, then eventually inserting it into the ready queue...

   Note: part of this code is present also in altick.c!
*/


#if defined(__OO_ECC1__) || defined(__OO_ECC2__)
#ifndef __PRIVATE_SETEVENT__

#ifdef __OO_EXTENDED_STATUS__
StatusType EE_oo_SetEvent(TaskType TaskID, EventMaskType Mask)
#else
void EE_oo_SetEvent(TaskType TaskID, EventMaskType Mask)
#endif
{
  register TaskType tmp;
  register TaskType tmp_stacked;
  register EE_FREG flag;


#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_SETEVENT+1;
#endif

#ifdef __RN_EVENT__
  if (TaskID & EE_REMOTE_TID) {
    /* forward the request to another CPU whether the thread do
       not become to the current CPU */
    register EE_TYPERN_PARAM par;
    par.ev = Mask;
    EE_rn_send(TaskID & ~EE_REMOTE_TID, EE_RN_EVENT, par );
    
#ifdef __OO_ORTI_SERVICETRACE__
    EE_ORTI_servicetrace = EE_SERVICETRACE_SETEVENT;
#endif

#ifdef __OO_EXTENDED_STATUS__
    return E_OK;
#else
    return;
#endif
  }
#endif

#ifdef __OO_EXTENDED_STATUS__    
  /* check if the task Id is valid */
  //if (TaskID < 0 || TaskID >= EE_MAX_TASK) {
	if (TaskID >= EE_MAX_TASK) {
#ifdef __OO_ORTI_LASTERROR__
    EE_ORTI_lasterror = E_OS_ID;
#endif

#ifdef __OO_HAS_ERRORHOOK__
    flag = EE_hal_begin_nested_primitive();
    if (!EE_ErrorHook_nested_flag) {  
#ifndef __OO_ERRORHOOK_NOMACROS__
      EE_oo_ErrorHook_ServiceID = OSServiceId_SetEvent;
      EE_oo_ErrorHook_data.SetEvent_prm.TaskID = TaskID;
      EE_oo_ErrorHook_data.SetEvent_prm.Mask = Mask;
#endif
      EE_ErrorHook_nested_flag = 1;
      ErrorHook(E_OS_ID);
      EE_ErrorHook_nested_flag = 0;
    }
    EE_hal_end_nested_primitive(flag);
#endif

#ifdef __OO_ORTI_SERVICETRACE__
    EE_ORTI_servicetrace = EE_SERVICETRACE_SETEVENT;
#endif

    return E_OS_ID;
  }

  if (!EE_th_is_extended[TaskID]) {
#ifdef __OO_ORTI_LASTERROR__
    EE_ORTI_lasterror = E_OS_ACCESS;
#endif

#ifdef __OO_HAS_ERRORHOOK__
    flag = EE_hal_begin_nested_primitive();
    if (!EE_ErrorHook_nested_flag) {
#ifndef __OO_ERRORHOOK_NOMACROS__
      EE_oo_ErrorHook_ServiceID = OSServiceId_SetEvent;
      EE_oo_ErrorHook_data.SetEvent_prm.TaskID = TaskID;
      EE_oo_ErrorHook_data.SetEvent_prm.Mask = Mask;
#endif
      EE_ErrorHook_nested_flag = 1;
      ErrorHook(E_OS_ACCESS);
      EE_ErrorHook_nested_flag = 0;
    }
    EE_hal_end_nested_primitive(flag);
#endif

#ifdef __OO_ORTI_SERVICETRACE__
    EE_ORTI_servicetrace = EE_SERVICETRACE_SETEVENT;
#endif

    return E_OS_ACCESS;
  }
#endif

  flag = EE_hal_begin_nested_primitive();

#ifdef __OO_EXTENDED_STATUS__    
  if (EE_th_status[TaskID] == SUSPENDED) {
#ifdef __OO_ORTI_LASTERROR__
    EE_ORTI_lasterror = E_OS_STATE;
#endif

#ifdef __OO_HAS_ERRORHOOK__
    if (!EE_ErrorHook_nested_flag) {
#ifndef __OO_ERRORHOOK_NOMACROS__
      EE_oo_ErrorHook_ServiceID = OSServiceId_SetEvent;
      EE_oo_ErrorHook_data.SetEvent_prm.TaskID = TaskID;
      EE_oo_ErrorHook_data.SetEvent_prm.Mask = Mask;
#endif
      EE_ErrorHook_nested_flag = 1;
      ErrorHook(E_OS_STATE);
      EE_ErrorHook_nested_flag = 0;
    }
#endif

    EE_hal_end_nested_primitive(flag);

#ifdef __OO_ORTI_SERVICETRACE__
    EE_ORTI_servicetrace = EE_SERVICETRACE_SETEVENT;
#endif

    return E_OS_STATE;
  }
#endif

  /* set the event mask */
  EE_th_event_active[TaskID] |= Mask;
  
  /* check if the task was waiting for an event we just set 
   *
   * WARNING:
   * the test with status==WAITING is FUNDAMENTAL to avoid double
   * insertion of the task in the ready queue!!! Example, when I call
   * two times the same setevent... the first time the task must go in
   * the ready queue, the second time NOT!!!
   */
  if (EE_th_event_waitmask[TaskID] & Mask &&
      EE_th_status[TaskID] == WAITING) {
    /* if yes, the task must go back into the READY state */
    EE_th_status[TaskID] = READY;
    /* insert the task in the ready queue */
    EE_rq_insert(TaskID);
  
    /* and if I am at task level, check for preemption... */
    if (!EE_hal_get_IRQ_nesting_level()) {
      /* we are inside a task */
      tmp = EE_rq_queryfirst();
      if (tmp != EE_NIL) {
	if (EE_sys_ceiling < EE_th_ready_prio[tmp]) {
	  /* we have to schedule a ready thread */

	  tmp_stacked = EE_stk_queryfirst();
	  if (tmp_stacked != EE_NIL) {
#ifdef __OO_HAS_POSTTASKHOOK__
	    PostTaskHook();
#endif	
	    /* the running task is now suspended */
	    EE_th_status[tmp_stacked] = READY;
	  }

	  /* and another task is put into the running state */
	  EE_th_status[tmp] = RUNNING;
	  
	  EE_sys_ceiling |= EE_th_dispatch_prio[tmp];

#ifdef __OO_ORTI_PRIORITY__
	  EE_ORTI_th_priority[tmp] = EE_th_dispatch_prio[tmp];
#endif

	  /* this code is valid either for ECC1 and ECC2 ;-) */
	  tmp = EE_rq2stk_exchange();
	  if (EE_th_waswaiting[tmp]) {
	    EE_th_waswaiting[tmp] = 0;
	    EE_hal_stkchange(tmp);
	  }
	  else
	    EE_hal_ready2stacked(tmp);

#ifdef __OO_HAS_PRETASKHOOK__
	  if (tmp_stacked != EE_NIL) {
	    PreTaskHook();
	  }
#endif	
	}
      }
    }
  }  

  EE_hal_end_nested_primitive(flag);

#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_SETEVENT;
#endif

#ifdef __OO_EXTENDED_STATUS__
  return E_OK;
#endif
}

#endif
#endif
