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
 * CVS: $Id: ee_cap.c,v 1.6 2008/07/18 09:53:55 tiberipa Exp $
 */

#include "ee_internal.h"


/* tasks are put into the recharging queue with the following status:
   - the budget is always greater then the minimum capacity

   - the period is:

     - if the budget was >0 when the task was interrupted, it is the
       former theadline of the task when it was interrupted

     - if the budget was <0 then the deadline is postponed and the
       budget incremented until it is greater than 0

   - a problem may occur if the budget is -really- <0 due to shared
     resource usage. in that case the task deadline can drift in the
     future way over the lifetime of the timer. This is a limitation
     we do not address here, because we assume taht the task
     parameters and the resource usages are compatible, in other words
     the critical sections must be short in order the system to work
     fine.
*/

/* This function recharges a task budget up to a point that it can be
   inserted into the recharging queue safely. */
#ifndef __PRIVATE_RECHARGEBUDGET__
void EE_frsh_rechargebudget(EE_TID t) {
  for(;;){
    // recharge the task.
    if (EE_th_budget_avail[t] > 0) {
      // the budget is positive, and we recharge to the maximum and we exit.
      EE_th_budget_avail[t] = EE_th_budget[t];
      break;
    } else {
      // the budget is negative. we sum it and we check if the new budget is enough
      EE_th_budget_avail[t] += EE_th_budget[t];
      if ( EE_th_budget_avail[t] > EE_TIMER_MINCAPACITY )
	break;
    }

    // we have to do another round! we update the period and we put the task back
    EE_th_absdline[t] += EE_th_period[t];
  }
}
#endif


#ifndef __PRIVATE_UPDATECAPACITY__

/* this function is called every time a thread is activated 
 * to update his budget available and to check if it should go
 * recharging
 */
ActionType EE_frsh_updatecapacity(EE_TID t, EE_TIME tmp_time)
{
  /* if the thread is not active or the current deadline is in the past */
  if (!EE_th_active[t] || (EE_STIME)(EE_th_absdline[t] - tmp_time) < 0) {
    /* task deadline is in the past, reset it to the default */
    EE_th_absdline[t] = tmp_time + EE_th_period[t];

    /* In this case, we decided to put it equal to the budget because
       since the deadline is in the past or the task is not active it
       is not worth to check and use a += instead of = . also, using
       += does not guarantees that after the sum the capacity is
       greater than 0, and so we are not sure we can put the task into
       the ready queue! */
    EE_th_budget_avail[t] = EE_th_budget[t];

    EE_th_active[t] = 1;
    return InsertRDQueue;
  } 
  else{
    // task deadline is in the future 
    if (EE_th_budget_avail[t] < EE_TIMER_MINCAPACITY) {
      EE_frsh_rechargebudget(t);

      return InsertRCGQueue;
    }
    /* This is the test of CBS, saying that if the bandwith of the
       task considered as the remaining capacity divided buy the time
       left to the deadline is greater than the nominal bandwidth of
       the task we have to reassign the deadlines to avoid that the
       task executes too much. This situation typically happens when
       the task stays idle for a while, or if the task has been
       blocked for a while. */

    if((EE_STIME)(EE_th_absdline[t] - EE_th_budget_avail[t]*EE_inv_proc_util[t] -
                   tmp_time) <= 0 ) {
      EE_th_budget_avail[t] = EE_th_budget[t];
      EE_th_absdline[t] = tmp_time + EE_th_period[t];          
    }
    return InsertRDQueue;     
  }
}

#endif


#ifndef __PRIVATE_SELECTEXEC__

/* 
 * input status: EE_exec is EE_NIL, ready or stacked queue may be full or empty
 * result:
 * EE_exec is set to the next task to schedule.
 * the status is untouched
 * if EE_exec is different from EE_NIL, then the task has been removed from its queue
 */
void EE_frsh_select_exec(void)
{
  register EE_TID tmp_rq;
  register EE_TID tmp_stk;

  tmp_rq = EE_rq_queryfirst();
  tmp_stk = EE_stk_queryfirst();
  
  if (tmp_rq == EE_NIL) {
    /* either the first on the stacked queue or nil */
    EE_exec = tmp_stk;
    if (tmp_stk != EE_NIL) { 
      EE_stk_getfirst();
    }
  } else {
    /* the ready queue is not empty */
    if (tmp_stk == EE_NIL ||
	((EE_STIME)(EE_th_absdline[tmp_stk] - EE_th_absdline[tmp_rq]) > 0
	 && EE_sys_ceiling < EE_th_prlevel[tmp_rq])) {
      EE_exec = tmp_rq;
      EE_rq_getfirst();
    } else {
      /* note that if the previous exec task ahs some locked
	 resources, then it was put into the stacked queue */
      EE_exec = tmp_stk;
      if (tmp_stk != EE_NIL) { 
	EE_stk_getfirst();
      }
    }
  }
}
#endif


/* 
   check_slice

   first considers the exec task, and accounts the elapsed time.

   updates the last timer read

   put the exec task in the right queue:
   - stacked if the task has locked resources, independently from the budget
   - ready if the task has still budget
   - recharging if it has no more budget

   puts exec to -1
*/

#ifndef __PRIVATE_CHECKSLICE__
void EE_frsh_check_slice(EE_TIME tmp_time)
{
  if (EE_exec != EE_NIL) {
    /* account the capacity to the task that is currently executing */
    EE_th_budget_avail[EE_exec] -= tmp_time - EE_last_time;

    if (EE_th_lockedcounter[EE_exec]) {
      /* The task is holding a resource, put it into the stacked queue 
	 regardless of the budget it has.
       */
      EE_stk_insertfirst(EE_exec);
    } else if ( (EE_STIME)EE_th_budget_avail[EE_exec] < EE_TIMER_MINCAPACITY) {
      /* if the budget is exhausted then insert in the recharging queue */
      EE_frsh_rechargebudget(EE_exec);
      EE_th_status[EE_exec] = EE_RECHARGING;
      EE_rcg_insert(EE_exec);

      /* update the recharging IRQ if the activated task becomes the first */
      if(EE_rcg_queryfirst() == EE_exec)
        EE_hal_set_recharging_timer(EE_th_absdline[EE_exec] - tmp_time);

    } else {
      EE_rq_insert(EE_exec);
    }
    
    EE_th_status[EE_exec] |= EE_WASSTACKED;

    /* EE_exec has been inserted into a queue */
    EE_exec = EE_NIL;
  }

  /* update the last timer read */
  EE_last_time = tmp_time;
}
#endif



/* 
   end_slice

   This is similar to check-slice, but it is different because it is
   executed at the end of a task.

   first considers the exec task, and accounts the elapsed time.

   updates the last timer read

   put the exec task in the right queue:
   if nact >1 and budget>0
     the task is put back into the ready queue
   if nact =0 and budget >0
     the task is suspended waiting for the next activation
   if nact >1 and budget <0
     the ending task has consumed all its budget.
     I put the task in recharging
   if nact =0 and budget <0
     I cannot put this task in the recharging queue because it is no more active
     but it will go in the recharging queue when it will be activated again
     so in this case I do nothing

   puts exec to -1
*/

#ifndef __PRIVATE_ENDSLICE__
void EE_frsh_end_slice(EE_TIME tmp_time)
{
  register int time_check;
  register int nact_check;
  
  /* account the capacity to the task that is currently executing */
  EE_th_budget_avail[EE_exec] -= tmp_time - EE_last_time;
  
  time_check = (EE_STIME)EE_th_budget_avail[EE_exec] < EE_TIMER_MINCAPACITY;
  nact_check = EE_th_nact[EE_exec];
  
  if (time_check) {
    // no budget left
    if (nact_check) {
      // nact > 1
      // the ending task has consumed all its budget.
      // It has still pending activations, I put the task in recharging
      EE_frsh_rechargebudget(EE_exec);
      EE_th_status[EE_exec] = EE_RECHARGING;
      EE_rcg_insert(EE_exec);

      /* update the recharging IRQ if the activated task becomes the first */
      if(EE_rcg_queryfirst() == EE_exec)
        EE_hal_set_recharging_timer(EE_th_absdline[EE_exec] - tmp_time);

      // WASSTACKED is not set, because the task just ended
    } else {
      // nact = 0
      // do nothing. 
      // the task is currently in any queue
      // the task will be inserted in the recharging queue when activated again
      EE_th_status[EE_exec] = EE_SUSPENDED;
    }
  } else {
    // there is still budget
    if (nact_check) {
      // nact > 1
      // the task is put back into the ready queue, no need to update the budget
      EE_rq_insert(EE_exec);
      EE_th_status[EE_exec] = EE_READY;
      // WASSTACKED is not set, because the task just ended
    } else {
      // nact = 0
      // the task is suspended waiting for the next activation. 
      // the budget is left as it was
      EE_th_status[EE_exec] = EE_SUSPENDED;
    }
  }
  
  /* EE_exec has been inserted into a queue or is terminated */
  EE_exec = EE_NIL;
  
  /* update the last timer read */
  EE_last_time = tmp_time;
}
#endif






/* 
   check-recharging

   if ready and stacked queue are empty pulls from the recharging queue 

   it reprograms the recharging IRQ
*/
#ifndef __PRIVATE_CHECKRECHARGING__
void EE_frsh_check_recharging(EE_TIME tmp_time)
{
  register EE_TIME delta;
  register EE_TID t;
  
  /* if there are not tasks in the ready and in the stacked queue,
   * check if there are task in recharging queue and if so, immediately
   * recharge one or more of them.
   */

  /* check if the ready and stacked queue are empty */
  if (EE_stk_queryfirst() != EE_NIL || EE_rq_queryfirst() != EE_NIL)
    return;

  /* we take the first task in the recharging queue.
     the tasks has been inserted into the queue with a reasonable budget
     (see EE_frsh_rechargebudget) */
  t = EE_rcg_queryfirst();

  /* exit if the recharging queue is empty */
  if (t == EE_NIL) {
    EE_hal_stop_recharging_timer();
    return;
  }

  /* remove the task from the recharging queue */
  EE_rcg_getfirst();

  /* delta is the amount of time we have to shift all the recharging deadlines */
  delta = EE_th_absdline[t] - tmp_time; 

  /* at this point t is the head of the recharging queue
     t has a budget which is > EE_TIMER_MINCAPACITY
     t has the deadline which was the one which it was inserted (or postponed) into the recharging queue
     t is no more inside the recharging queue
     delta is the shift to be applied to all the tasks remaining in the recharging queue
  */
     
  /* we update the deadline of the task and we set it to ready */
  EE_th_absdline[t] = tmp_time + EE_th_period[t];
  EE_rq_insert(t);

  /* if a task is in the recharging queue it means it is active and it
     has finished the budget. it means it is on the stack! */
  EE_th_status[t] = EE_READY | EE_WASSTACKED;


  /* we have to shift all the recharging times by delta */
  t = EE_rcg_queryfirst();
  EE_TID prev = EE_NIL;

  while (t != EE_NIL) {
    EE_th_absdline[t] -= delta;
    
    /* if the deadline is (almost) 0, it means that the task's recharge IRQ once put in the ready queue
       will fire in a few microseconds */
    if ((EE_STIME)(EE_th_absdline[t] - tmp_time) <= EE_TIMER_MINCAPACITY) {
      // we have to reassign deadline and budget
      // to avoid the recharging interrupt to arrive
      
      // remove from the recharging queue
      EE_TID t_tmp = t;

      // handle t and prev.  Note: we have to update t because when
      // inserting t_tmp in the ready queue it will change th_next
      // (that's why the main if has the else: t and prev have to be
      // updated here!
      if (prev != EE_NIL) {
	t = EE_th_next[t];
	EE_th_next[prev] = t;
      }
      else {
	EE_rcg_getfirst();
	t = EE_rcg_queryfirst();
      }
      
      // update the deadline. Note the deadline has been shifted by delta already
      // The budget has already been set when inserting into the recharging queue
      EE_th_absdline[t_tmp] += EE_th_period[t_tmp];
      
      // insert in the ready queue
      EE_rq_insert(t_tmp);
      EE_th_status[t_tmp] = EE_READY | EE_WASSTACKED;
    } else {
      // go to the next task
      prev = t;
      t = EE_th_next[t];
    }
  }
  
  t = EE_rcg_queryfirst();

  // at the end of the update, we have to reprogram the recharging IRQ
  if (t != EE_NIL) {
      EE_hal_set_recharging_timer(EE_th_absdline[t] - tmp_time);
  }
  else
    EE_hal_stop_recharging_timer();
}
#endif

/* #ifdef __SEM_FRSH__ */
/*     // PJ: da rivedere quando farò i semafori */
/*     // note: both recharging times and semaphore timeouts timers are on the same queue */
/*     // PJ: potremmo usare un vettore per gli accodamenti nel recharging evitando gli if... */
/*     if (EE_th_status[EE_rcg_queryfirst()] & EE_BLOCKED) { */
/*       EE_hal_set_recharging_timer(EE_th_timeouts[EE_rcg_queryfirst()] - tmp_time); */
/*     }  */
/*     else */
/* #endif */

