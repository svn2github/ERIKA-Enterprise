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
 * CVS: $Id: ee_evwait.c,v 1.3 2006/05/03 05:59:55 pj Exp $
 */

#include "ee_internal.h"

/* WaitEvent:
   - can be called from an extended task only
   - the task state is put to wait until an event in the mask has been set
   - if the task blocks -> reschedulig + internal resource released
   - returns (only extended state)
       E_OS_RESOURCE task occupies a resource
       E_OS_ACCESS   if the task is not an extended task
       E_OS_CALLEVEL called at interrupt level
*/


#if defined(__OO_ECC1__) || defined(__OO_ECC2__)
#ifndef __PRIVATE_WAITEVENT__

#ifdef __OO_EXTENDED_STATUS__
StatusType EE_oo_WaitEvent(EventMaskType Mask)
#else
void EE_oo_WaitEvent(EventMaskType Mask)
#endif
{
  TaskType current, tmp;

#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_WAITEVENT+1;
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
    EE_hal_begin_primitive();
    if (!EE_ErrorHook_nested_flag) {
#ifndef __OO_ERRORHOOK_NOMACROS__
      EE_oo_ErrorHook_ServiceID = OSServiceId_WaitEvent;
      EE_oo_ErrorHook_data.WaitEvent_prm.Mask = Mask;
#endif
      EE_ErrorHook_nested_flag = 1;
      ErrorHook(E_OS_CALLEVEL);
      EE_ErrorHook_nested_flag = 0;
    }
    EE_hal_end_primitive();
#endif

#ifdef __OO_ORTI_SERVICETRACE__
    EE_ORTI_servicetrace = EE_SERVICETRACE_WAITEVENT;
#endif

    return E_OS_CALLEVEL;
  }

#ifndef __OO_NO_RESOURCES__
  /* check for busy resources */ 
  if (EE_th_resource_last[current] != -1) {
#ifdef __OO_ORTI_LASTERROR__
    EE_ORTI_lasterror = E_OS_RESOURCE;
#endif

#ifdef __OO_HAS_ERRORHOOK__
    EE_hal_begin_primitive();
    if (!EE_ErrorHook_nested_flag) {  
#ifndef __OO_ERRORHOOK_NOMACROS__
      EE_oo_ErrorHook_ServiceID = OSServiceId_WaitEvent;
      EE_oo_ErrorHook_data.WaitEvent_prm.Mask = Mask;
#endif
      EE_ErrorHook_nested_flag = 1;
      ErrorHook(E_OS_RESOURCE);
      EE_ErrorHook_nested_flag = 0;
    }
    EE_hal_end_primitive();
#endif

#ifdef __OO_ORTI_SERVICETRACE__
    EE_ORTI_servicetrace = EE_SERVICETRACE_WAITEVENT;
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
    EE_hal_begin_primitive();
    if (!EE_ErrorHook_nested_flag) {
#ifndef __OO_ERRORHOOK_NOMACROS__
      EE_oo_ErrorHook_ServiceID = OSServiceId_WaitEvent;
      EE_oo_ErrorHook_data.WaitEvent_prm.Mask = Mask;
#endif
      EE_ErrorHook_nested_flag = 1;
      ErrorHook(E_OS_ACCESS);
      EE_ErrorHook_nested_flag = 0;
    }
    EE_hal_end_primitive();
#endif

#ifdef __OO_ORTI_SERVICETRACE__
    EE_ORTI_servicetrace = EE_SERVICETRACE_WAITEVENT;
#endif

    return E_OS_ACCESS;
  }
#endif

  EE_hal_begin_primitive();

  /* check if we have to wait */
  if (!(EE_th_event_active[current] & Mask)) {
#ifdef __OO_HAS_POSTTASKHOOK__
    PostTaskHook();
#endif	

    /* set the waiting mask */
    EE_th_event_waitmask[current] = Mask;

    /* the task must go into the WAITING state */
    EE_th_status[current] = WAITING;

    /* extract the task from the stk data structure */
    EE_stk_getfirst();

    /* reset the thread priority bit in the system_ceiling */
    EE_sys_ceiling &= ~EE_th_dispatch_prio[current];
    /* the ready priority is not touched, it is not the same as Schedule! */

#ifdef __OO_ORTI_PRIORITY__
    EE_ORTI_th_priority[current] = 0;
#endif

    /* since the task blocks, it has to be woken up by another
       EE_hal_stkchange */
    EE_th_waswaiting[current] = 1;

    /* then, the task is not inserted in any queue! it will be woken
       up by a SetEvent using a EE_hal_stkchange... */


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

    /* reset the waiting mask */
    EE_th_event_waitmask[current] = 0;

    /* We do not have to set the thread priority bit in the
       system_ceiling, it will be set by the primitives that put the
       task in the RUNNING state */

#ifdef __OO_HAS_PRETASKHOOK__
    PreTaskHook();
#endif	
  }
  EE_hal_end_primitive();
  
#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_WAITEVENT;
#endif

#ifdef __OO_EXTENDED_STATUS__
  return E_OK;
#endif
}

#endif
#endif
