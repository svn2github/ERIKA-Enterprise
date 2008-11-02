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
 * CVS: $Id: ee_swait.c,v 1.1 2008/04/23 11:46:32 francesco Exp $
 */

#include "ee_internal.h"

#ifndef __PRIVATE_SEM_WAIT__
void EE_sem_WaitSem(SemRefType s)
{
  register EE_TID t_rq,t_stk;
  register EE_TIME tmp_time;
  EE_TID current;

  EE_hal_begin_primitive();

  if (s->count)
    s->count--;
  else {
    /* The running task blocks: 
       - it must be removed from the stacked queue
       - and then it must be inserted into the blocked queue */

    /* get the running task */	
    tmp_time = EE_hal_gettime();
    EE_th_budget_avail[EE_exec] -= tmp_time - EE_last_time;
    EE_last_time = tmp_time;
    current = EE_exec;

    /* The task state switch from STACKED TO BLOCKED */
    EE_th_status[current] = EE_BLOCKED | EE_WASSTACKED;

    /* reset the thread priority bit in the system_ceiling */
    EE_sys_ceiling &= ~EE_th_prlevel[current];

    if (s->first != EE_NIL)
      // the semaphore queue is not empty
      EE_th_next[s->last] = current;
    else
      // the semaphore queue is empty
      s->first = current;

    s->last = current;
    EE_th_next[current] = EE_NIL;
    
    t_rq=EE_rq_queryfirst();
    t_stk=EE_stk_queryfirst();

    if( ( t_stk != EE_NIL && t_rq == EE_NIL) ||  // note that this test work also for the main task!
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
    else if(t_rq != EE_NIL) {
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
    else{
      // next thread is main
      EE_exec=EE_NIL;
      // turn off budget timer
      EE_hal_stop_budget_timer();
      EE_hal_stkchange(EE_exec);
    }
  }

  EE_hal_end_primitive();

}
#endif
