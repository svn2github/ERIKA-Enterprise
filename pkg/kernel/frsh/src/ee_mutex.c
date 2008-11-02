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
 * Author: 2008 Paolo Tiberi & Francesco Focacci
 * CVS: $Id: ee_mutex.c,v 1.6 2008/07/18 09:53:55 tiberipa Exp $
 */

#include "ee_internal.h"

#ifndef __PRIVATE_MUTEX_LOCK__
void EE_frsh_mutex_lock(EE_MUTEX m)
{
    EE_hal_begin_primitive();
    
    EE_mutex_oldceiling[m] = EE_sys_ceiling;
    EE_sys_ceiling |= EE_mutex_ceiling[m];
    EE_th_lockedcounter[EE_exec]++;
    
    EE_hal_end_primitive();
}
#endif /* __PRIVATE_MUTEX_LOCK__ */




#ifndef __PRIVATE_MUTEX_UNLOCK__

void EE_recharging_release_mutex(EE_TIME tmp_time)
{
  register EE_TIME delta;
  register EE_TID t_rq,t_stk;
  
  EE_th_status[EE_exec] = EE_RECHARGING | EE_WASSTACKED;
  EE_rcg_insert(EE_exec);
  t_rq=EE_rq_queryfirst();
  t_stk=EE_stk_queryfirst();
  
  if(EE_rcg_queryfirst() == EE_exec)
    EE_hal_rechargingIRQ( EE_th_absdline[EE_rcg_queryfirst()] - tmp_time );
  
  if(t_rq == EE_NIL && t_stk == EE_NIL){
  // if there are not tasks in the ready and in the stacked queue
    EE_TID t;
    
    // Control for negative budget and in case re-insert in the rcg queue
    for(;;){
      t = EE_rcg_queryfirst();
      EE_rcg_getfirst();
      if( (EE_th_budget_avail[t] += EE_th_budget[t]) > EE_TIMER_MINCAPACITY )
        break;
      EE_th_absdline[t]+=EE_th_period[t];
      EE_rcg_insert(t);
    }
    
    EE_rq_insert(t);
    EE_th_status[t] = EE_READY | EE_WASSTACKED;
    delta=EE_th_absdline[t]-tmp_time; 
    EE_th_absdline[t]=tmp_time+EE_th_period[t];
    
    t=EE_rcg_queryfirst();
    
    //update recharging times
    while(t!=EE_NIL){
      EE_th_absdline[t]-=delta;
      if((EE_STIME)(EE_th_absdline[t]- tmp_time)<=100){
        EE_TID t_tmp=t;
        t=EE_th_next[t];
        EE_rcg_getfirst();
        EE_th_absdline[t_tmp]=tmp_time+EE_th_period[t_tmp];
        EE_th_budget_avail[t_tmp] = EE_th_budget[t_tmp];
        EE_rq_insert(t_tmp);
      }
      else
        t=EE_th_next[t];
    }
    
    if(EE_rcg_queryfirst() != EE_NIL)
      EE_hal_rechargingIRQ(EE_th_absdline[EE_rcg_queryfirst()] - tmp_time);
  }
    
  t_rq = EE_rq_queryfirst();
  
  if(t_rq == EE_NIL ||  // note that this test work also for the main task!
      ( t_stk != EE_NIL && ( (EE_STIME)(EE_th_absdline[t_stk] - 
		   EE_th_absdline[t_rq]) <= 0
	|| EE_sys_ceiling >= EE_th_prlevel[t_rq]) )) {
  
    // The task in the stacked queue has to be executed
    EE_exec = t_stk;
    EE_stk_getfirst();
    EE_hal_capacityIRQ(EE_th_budget_avail[EE_exec]); 
    EE_th_status[EE_exec] = EE_READY;
    EE_hal_stkchange(EE_exec);
  }
  else {
    /* we will schedule a ready thread */
    register int flag;
    
    /* first, remove the task from the ready queue */
    EE_exec = t_rq;

    /* remove the first task from the ready queue, and set the new
       exec task as READY */
    flag = EE_th_status[EE_exec] & EE_WASSTACKED;
    EE_th_status[EE_exec] = EE_READY;
    EE_rq_getfirst();
 
    /* program the capacity interrupt */
    EE_hal_capacityIRQ(EE_th_budget_avail[EE_exec]);
    
    if (flag)
      EE_hal_stkchange(EE_exec);
    else
      EE_hal_ready2stacked(EE_exec);
  }
}

void EE_frsh_mutex_unlock(EE_MUTEX m)
{
  register EE_TID old_exec;
  register EE_TID t;
  register int test_ready;
  register int test_stacked;
  register EE_TIME tmp_time;

  EE_hal_begin_primitive();
  
  old_exec = EE_exec;

  EE_sys_ceiling = EE_mutex_oldceiling[m];
  EE_th_lockedcounter[old_exec]--;

  /* account the capacity to the running task */
  tmp_time = EE_hal_gettime();
  
  EE_th_budget_avail[old_exec] -= tmp_time - EE_last_time;
  
  if (!EE_th_active[EE_exec] || (EE_STIME)(EE_th_absdline[EE_exec] - tmp_time) < 100) {
    /* task deadline is in the past, reset it to the default */
    EE_th_absdline[EE_exec] = tmp_time + EE_th_period[EE_exec];
    EE_th_budget_avail[EE_exec] = EE_th_budget[EE_exec];
    EE_th_active[EE_exec] = 1;
  }
  else if (EE_th_budget_avail[EE_exec] < EE_TIMER_MINCAPACITY && !EE_th_lockedcounter[EE_exec]) {
    EE_recharging_release_mutex(tmp_time);
    EE_last_time = tmp_time;
    EE_hal_end_primitive();
    return;
  }
  
  EE_last_time = tmp_time;

  /* this code is similar to the EE_iris_sys_scheduler()!!! */
  t = EE_rq_queryfirst();

  test_ready = 
    t != EE_NIL &&
    (EE_STIME)(EE_th_absdline[old_exec] - EE_th_absdline[t]) > 0
    && EE_sys_ceiling < EE_th_prlevel[t];

  test_stacked =
    EE_stk_queryfirst() != EE_NIL &&
    EE_th_lockedcounter[old_exec] == 0 ;

  /* check if there is a preemption */
  if (test_ready && 
      (!test_stacked || 
       (test_stacked &&
	(EE_STIME)(EE_th_absdline[EE_stk_queryfirst()] - 
		   EE_th_absdline[t]) > 0)
      )){
    /* we have to schedule a ready thread */

    register int flag;

    EE_exec = t;

    /* remove the first task from the ready queue, and set the new
       exec task as READY */
    flag = EE_th_status[t] & EE_WASSTACKED;
    EE_th_status[t] = EE_READY;
    EE_rq_getfirst();
    
    /* set the stacked flag to the old running task */
    EE_th_status[old_exec] |= EE_WASSTACKED;

    if (EE_th_lockedcounter[old_exec])
      EE_stk_insertfirst(old_exec);
    else
      EE_rq_insert(old_exec);

    /* program the capacity interrupt */
    EE_hal_capacityIRQ(EE_th_budget_avail[EE_exec]);

    if (flag)
      EE_hal_stkchange(EE_exec);
    else
      EE_hal_ready2stacked(EE_exec);
  }

  else if (test_stacked &&     
	   (EE_STIME)(EE_th_absdline[old_exec] - 
		      EE_th_absdline[EE_stk_queryfirst()]) > 0) {
    /* we have to schedule a stacked thread */

    EE_exec = t = EE_stk_queryfirst();

    /* NOTE: t has been reassigned! */

    /* remove the first task from the stacked queue. the task has the
       WASSTACKED flag set. */
    EE_stk_getfirst();
    
    /* set the stacked flag to the old running task */
    EE_th_status[old_exec] |= EE_WASSTACKED;

    EE_rq_insert(old_exec);

    /* program the capacity interrupt */
    EE_hal_capacityIRQ(EE_th_budget_avail[EE_exec]);

    EE_hal_stkchange(EE_exec);
  }
  else {
    if(EE_exec != EE_NIL)
      EE_hal_capacityIRQ(EE_th_budget_avail[EE_exec]);
  }
  
  EE_hal_end_primitive();
}			   

#endif /* __PRIVATE_MUTEX_UNLOCK__ */
