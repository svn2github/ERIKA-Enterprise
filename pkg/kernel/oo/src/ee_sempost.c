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
 * CVS: $Id: ee_sempost.c,v 1.3 2006/12/03 22:07:50 pj Exp $
 */

#include "ee_internal.h"

/* PostSem:
  - This primitive can be called from ISRs, Tasks, and from the background (main) task.
  - for BCC1 and BCC2, a smaller reduced version is provided.
  - The primitive implements the traditional counting Semaphore post operation.
  - If there are tasks blocked on the Semaphore, then one of these tasks is awaken. In that case, the call enforces rescheduling.
    If there are no tasks blocked on the Semaphore, the semaphore counter is incremented.
  - Error value returned
    Standard:  No error, E_OK 
    E_OS_VALUE Semaphore counter has the maximum value

    Conformance: 
    - BCC1, BCC2 (without wakeup)
    - ECC1, ECC2 (with wakeup)
*/

#if defined(__OO_ECC1__) || defined(__OO_ECC2__)
#ifndef __PRIVATE_POSTSEM__

StatusType EE_oo_PostSem(SemRefType Sem)
{
  register TaskType tmp, unlocked_tmp;
  register TaskType tmp_stacked;
  register EE_FREG flag;


#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_POSTSEM+1;
#endif

  flag = EE_hal_begin_nested_primitive();

  /* check if the post on the semaphore wakes up someone */
  if (Sem->first != EE_NIL) {

    // update the semaphore queue
    unlocked_tmp = Sem->first;
    if ((Sem->first = EE_th_next[unlocked_tmp]) == EE_NIL)
      Sem->last = EE_NIL;

    /* if yes, the task must go back into the READY state */
    EE_th_status[unlocked_tmp] = READY;
    /* insert the task in the ready queue */
    EE_rq_insert(unlocked_tmp);
  
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
  else {
    if (Sem->count == EE_MAX_SEM_COUNTER) {
#ifdef __OO_ORTI_LASTERROR__
      EE_ORTI_lasterror = E_OS_VALUE;
#endif

#ifdef __OO_HAS_ERRORHOOK__
      if (!EE_ErrorHook_nested_flag) {
#ifndef __OO_ERRORHOOK_NOMACROS__
	EE_oo_ErrorHook_ServiceID = OSServiceId_PostSem;
	EE_oo_ErrorHook_data.PostSem_prm.Sem = Sem;
#endif
	EE_ErrorHook_nested_flag = 1;
	ErrorHook(E_OS_VALUE);
	EE_ErrorHook_nested_flag = 0;
      }
#endif
      
      EE_hal_end_nested_primitive(flag);
      
#ifdef __OO_ORTI_SERVICETRACE__
      EE_ORTI_servicetrace = EE_SERVICETRACE_POSTSEM;
#endif
      
      return E_OS_VALUE;
    }

    Sem->count++;
  }

  EE_hal_end_nested_primitive(flag);

#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_POSTSEM;
#endif

  return E_OK;
}

#endif
#endif // ECC1/ECC2


/* This is a simplified version of PostSem */

#if defined(__OO_BCC1__) || defined(__OO_BCC2__)
#ifndef __PRIVATE_POSTSEM__

StatusType EE_oo_PostSem(SemRefType Sem)
{
  register EE_FREG flag;


#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_POSTSEM+1;
#endif

  flag = EE_hal_begin_nested_primitive();

  /* the wake up check is removed because there is no blocking wait! */
  if (Sem->count == EE_MAX_SEM_COUNTER) {
#ifdef __OO_ORTI_LASTERROR__
    EE_ORTI_lasterror = E_OS_VALUE;
#endif

#ifdef __OO_HAS_ERRORHOOK__
    if (!EE_ErrorHook_nested_flag) {
#ifndef __OO_ERRORHOOK_NOMACROS__
      EE_oo_ErrorHook_ServiceID = OSServiceId_PostSem;
      EE_oo_ErrorHook_data.PostSem_prm.Sem = Sem;
#endif
      EE_ErrorHook_nested_flag = 1;
      ErrorHook(E_OS_VALUE);
      EE_ErrorHook_nested_flag = 0;
    }
#endif
    
    EE_hal_end_nested_primitive(flag);
    
#ifdef __OO_ORTI_SERVICETRACE__
    EE_ORTI_servicetrace = EE_SERVICETRACE_POSTSEM;
#endif
    
    return E_OS_VALUE;
  }
  
  Sem->count++;

  EE_hal_end_nested_primitive(flag);

#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_POSTSEM;
#endif

  return E_OK;
}

#endif
#endif // BCC1/BCC2
