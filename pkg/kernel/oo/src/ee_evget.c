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
 * CVS: $Id: ee_evget.c,v 1.1 2005/07/16 12:23:42 pj Exp $
 */

#include "ee_internal.h"

/* GetEvent:
   - can be called from a task, from ISR, from error, pre e post taskhook
   - clear the events for the task
   - returns (only extended state)
       E_OS_ID       task id invalid
       E_OS_ACCESS   if the task is not an extended task
       E_OS_STATE    the task id is in the suspended state
*/


#if defined(__OO_ECC1__) || defined(__OO_ECC2__)
#ifndef __PRIVATE_GETEVENT__

#ifdef __OO_EXTENDED_STATUS__
StatusType EE_oo_GetEvent(TaskType TaskID, EventMaskRefType Event)
#else
void EE_oo_GetEvent(TaskType TaskID, EventMaskRefType Event)
#endif
{
  register EE_FREG flag;
  
#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_GETEVENT+1;
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
      EE_oo_ErrorHook_ServiceID = OSServiceId_GetEvent;
      EE_oo_ErrorHook_data.GetEvent_prm.TaskID = TaskID;
      EE_oo_ErrorHook_data.GetEvent_prm.Event = Event;
#endif
      EE_ErrorHook_nested_flag = 1U;
      ErrorHook(E_OS_ID);
      EE_ErrorHook_nested_flag = 0U;
    }
    EE_hal_end_nested_primitive(flag);
#endif

#ifdef __OO_ORTI_SERVICETRACE__
    EE_ORTI_servicetrace = EE_SERVICETRACE_GETEVENT;
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
      EE_oo_ErrorHook_ServiceID = OSServiceId_GetEvent;
      EE_oo_ErrorHook_data.GetEvent_prm.TaskID = TaskID;
      EE_oo_ErrorHook_data.GetEvent_prm.Event = Event;
#endif
      EE_ErrorHook_nested_flag = 1U;
      ErrorHook(E_OS_ACCESS);
      EE_ErrorHook_nested_flag = 0U;
    }
    EE_hal_end_nested_primitive(flag);
#endif

#ifdef __OO_ORTI_SERVICETRACE__
    EE_ORTI_servicetrace = EE_SERVICETRACE_GETEVENT;
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
      EE_oo_ErrorHook_ServiceID = OSServiceId_GetEvent;
      EE_oo_ErrorHook_data.GetEvent_prm.TaskID = TaskID;
      EE_oo_ErrorHook_data.GetEvent_prm.Event = Event;
#endif
      EE_ErrorHook_nested_flag = 1U;
      ErrorHook(E_OS_STATE);
      EE_ErrorHook_nested_flag = 0U;
    }
#endif

    EE_hal_end_nested_primitive(flag);

#ifdef __OO_ORTI_SERVICETRACE__
    EE_ORTI_servicetrace = EE_SERVICETRACE_GETEVENT;
#endif

    return E_OS_STATE;
  }
#endif

  *Event = EE_th_event_active[TaskID];

  EE_hal_end_nested_primitive(flag);

#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_GETEVENT;
#endif

#ifdef __OO_EXTENDED_STATUS__
  return E_OK;
#endif
}

#endif
#endif
