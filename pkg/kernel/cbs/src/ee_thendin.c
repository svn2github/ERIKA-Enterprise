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
 * Author: 2003 Paolo Gai
 * CVS: $Id: ee_thendin.c,v 1.6 2007/06/14 10:27:12 pj Exp $
 */

#include "ee_internal.h"

#ifndef __PRIVATE_THREAD_END_INSTANCE__
// this function MUST NOT BE CALLED BY THE USER!!!
// maybe it is better to write this function in assembler,
// a RET can be saved!
void EE_thread_end_instance(void)
{
  register EE_TIME tmp_time;
  register EE_TID current;

  current = EE_exec;

  tmp_time = EE_hal_gettime();

  /* decrease the pending activations... ready or stacked => (nact>0) */
  EE_th_nact[current]--;

  /* The task state switch from STACKED TO READY because it end its
   * instance. Note that status=READY and nact=0 ==>> the task is
   * suspended!!! */
  EE_th_status[current] = EE_READY;

  /* account the capacity to the task that is currently executing */
  EE_th_budget_avail[current] -= tmp_time - EE_last_time;
  EE_last_time = tmp_time;

  if (EE_th_nact[current] > 0) {
    EE_cbs_updatecapacity(current, tmp_time);

    /* there are pending activations... we have to reinsert the task
       into the ready queue before rescheduling!!! */
    EE_rq_insert(current);
  }

#ifdef DEBUG
  if (EE_th_lockedcounter[current])
    for(;;);
#endif

  /* the task is pointed by EE_exec. It has not been inserted in
     the stk data structure, so there is no need to remove it from
     that structure as we did in FP/EDF */

  /* since the task pointed by exec has just ended, we have now to
     choose between the tasks pointed by stkfirst and by rqfirst */
  // th_absdline[stk_queryfirst()] <= th_absdline[rq_queryfirst()] 
  if (EE_rq_queryfirst() == EE_NIL ||  // note that this test work also for the main task!
      (EE_stk_queryfirst() != EE_NIL && 
       (
	(EE_STIME)(EE_th_absdline[EE_stk_queryfirst()] - 
		   EE_th_absdline[EE_rq_queryfirst()]) <= 0
	|| EE_sys_ceiling >= EE_th_prlevel[EE_rq_queryfirst()]
	) 
       )
      )  {
    /* if I m here I am scheduling a stacked task or the main
       thread. Note: in both cases the task has the WASSTACKED flag */

    /* first, remove the task from stacked */
    EE_exec = EE_stk_queryfirst();

    if (EE_exec != EE_NIL) {
      EE_stk_getfirst();
      EE_hal_capacityIRQ(EE_th_budget_avail[EE_exec]); 
      EE_th_status[EE_exec] = EE_READY;
    }
    
    /* schedule the interrupted thread (already on the stack!!!) */
    EE_hal_endcycle_stacked(EE_exec);
  }
  else {
    /* we will schedule a ready thread */
    register int flag;
    
    /* first, remove the task from the ready queue */
    EE_exec = EE_rq_queryfirst();

    /* remove the first task from the ready queue, and set the new
       exec task as READY */
    flag = EE_th_status[EE_exec] & EE_WASSTACKED;
    EE_th_status[EE_exec] = EE_READY;
    EE_rq_getfirst();
 
    /* program the capacity interrupt */
    EE_hal_capacityIRQ(EE_th_budget_avail[EE_exec]);
    
    if (flag)
      EE_hal_endcycle_stacked(EE_exec);
    else
      EE_hal_endcycle_ready(EE_exec);
  }
}  
#endif
