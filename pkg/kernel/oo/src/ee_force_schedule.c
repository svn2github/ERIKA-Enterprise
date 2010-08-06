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
 * CVS: $Id: ee_force_schedule.c,v 1.2 2006/06/08 20:40:42 pj Exp $
 */

#include "ee_internal.h"
#include "../inc/ee_kernel.h"

/* Force Scheduling: 

    - This is an internal function that has been inserted in the OO
      implementation because it is also needed because counters relies
      on such a rescheduling point when the counter increment is
      called inside a task (a call to this function is not needed when
      calling the counter increment inside an interrupt handler.

    - no checks are done at all; it is the user responsibility to take
      care that this function is called in the proper place.

    - the typical behavior of this function is -nothing-. It will just
      implement a preemption point for the functions that need it and
      that have not a preemption point hardwired in their code.

    - return values:
      Standard status: nothing
      Extended status: E_OS_CALLEVEL, if it was called at interrupt level

*/

#ifndef __PRIVATE_FORCESCHEDULE__

#ifdef __OO_EXTENDED_STATUS__
StatusType EE_oo_ForceSchedule(void)
#else
void EE_oo_ForceSchedule(void)
#endif
{
  EE_TID current, rq;

#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_FORCESCHEDULE+1;
#endif

#ifdef __OO_EXTENDED_STATUS__
  /* check for a call at interrupt level: This must be the FIRST check!*/
  if (EE_hal_get_IRQ_nesting_level()) {
#ifdef __OO_ORTI_LASTERROR__
    EE_ORTI_lasterror = E_OS_CALLEVEL;
#endif

#ifdef __OO_HAS_ERRORHOOK__
    EE_hal_begin_primitive();
    if (!EE_ErrorHook_nested_flag) {  
#ifndef __OO_ERRORHOOK_NOMACROS__
      EE_oo_ErrorHook_ServiceID = OSServiceId_ForceSchedule;
#endif
      EE_ErrorHook_nested_flag = 1U;
      ErrorHook(E_OS_CALLEVEL);
      EE_ErrorHook_nested_flag = 0U;
    }
    EE_hal_end_primitive();
#endif

#ifdef __OO_ORTI_SERVICETRACE__
    EE_ORTI_servicetrace = EE_SERVICETRACE_FORCESCHEDULE;
#endif

    return E_OS_CALLEVEL;
  }
#endif


  EE_hal_begin_primitive();
  
  current = EE_stk_queryfirst();

  /* check if there is a preemption */
  rq = EE_rq_queryfirst();
  if (rq != EE_NIL) {
    /* We check if the system ceiling is greater or not the first task
       in the ready queue */
    if (EE_sys_ceiling < EE_th_ready_prio[rq]) {
      if (current != EE_NIL) { 
#ifdef __OO_HAS_POSTTASKHOOK__
	PostTaskHook();
#endif	
	/* we have to put the task in the ready status */
	EE_th_status[current] = READY;
	/* but not in the ready queue!!! 
	   the task remains into the stacked queue!
	*/
      }
      
      /* get the new internal resource */
      EE_sys_ceiling |= EE_th_dispatch_prio[rq];
      /* put the task in running state */
      EE_th_status[rq] = RUNNING;

#ifdef __OO_ORTI_PRIORITY__
      EE_ORTI_th_priority[rq] = EE_th_dispatch_prio[rq];
#endif
      
#if defined(__OO_ECC1__) || defined(__OO_ECC2__)
      rq = EE_rq2stk_exchange();
      if (EE_th_waswaiting[rq]) {
	EE_th_waswaiting[rq] = 0U;
	EE_hal_stkchange(rq); 
      } else {
	EE_hal_ready2stacked(rq);
      }
#else
      EE_hal_ready2stacked(EE_rq2stk_exchange());
#endif
      
#ifdef __OO_HAS_PRETASKHOOK__
      PreTaskHook();
#endif	

    }
  }
  
  EE_hal_end_primitive();

#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_FORCESCHEDULE;
#endif
  
#ifdef __OO_EXTENDED_STATUS__
  return E_OK;
#endif
}

#endif

