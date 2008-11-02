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

#include "ee_internal.h"

#ifndef __PRIVATE_IRQ_END_RECHARGING__
/* This primitive shall be atomic.
   This primitive shall be inserted as the last function in an IRQ handler.
   If the HAL allow IRQ nesting the C_end_instance should work as follows:
   - it must implement the preemption test only if it is the last IRQ
     on the stack
   - if there are other interrupts on the stack the IRQ scheduler
     should do nothing
*/

/*
  In general, this routine is called as the last thing before the end
  of an interrupt. The interrupt could have interrupted a task, or the
  main task (EE_exec=NIL).

  Moreover, this routine is called by the (empty) capacity interrupt,
  that is used to postpone the deadline of the running task.

  In general, we have to verify that a task has enough capacity. if it
  ended the available capacity, its deadline have to be postponed n
  times, until the available capacity goes over a threahold.

  Please note the following race condition:
  - the capacity interrupt is posted
  - the running task enters in a primitive disabling the interrupt
  - the capacity interrupt fires but it remains pending due to
    interrupt disabling
  - the primitive (i.e, thread activation) notice that the capacity is
    exausted and it postpones the deadline
  - the primitive ends activating another task and posting another
    capacity interrupt
  - the capacity interrupt that was pending may again fire (depending
    on the architectures). in that case the capacity interrupt has to
    work anyway on the current running task, eventually doing nothing.
 */

void EE_IRQ_end_recharging(void)
{
  register EE_TIME tmp_time;
  register EE_TID t,tmp_rq;

  // Control for negative budget and in case re-insert in the rcg queue
  tmp_time = EE_hal_gettime();
  
  /* this has to be done in any case */
  EE_last_time = tmp_time;
  
  do{
    t = EE_rcg_queryfirst();
    EE_rcg_getfirst();
    if( (EE_th_budget_avail[t] += EE_th_budget[t]) > EE_TIMER_MINCAPACITY ) {
      EE_rq_insert(t);
      EE_th_absdline[t]=tmp_time+EE_th_period[t];
    }
    else {
      EE_th_absdline[t]+=EE_th_period[t];
      EE_rcg_insert(t);
    }
  }while((EE_STIME)(EE_th_absdline[EE_rcg_queryfirst()]-tmp_time) <= 100);
  
  tmp_rq = EE_rq_queryfirst();
  /* check if there is a preemption */
  if (EE_exec == EE_NIL ||	/* main task! */
    ((tmp_rq != EE_NIL) && (EE_STIME)(EE_th_absdline[EE_exec] - EE_th_absdline[tmp_rq]) > 0
     && EE_sys_ceiling < EE_th_prlevel[tmp_rq])) {
         /* we have to schedule a ready thread */

    register int flag;
    register EE_TID old_exec;

    old_exec = EE_exec;
    EE_exec = tmp_rq;

    /* remove the first task from the ready queue, and set the new
       exec task as READY */
    flag = EE_th_status[tmp_rq] & EE_WASSTACKED;
    EE_th_status[tmp_rq] = EE_READY;
    EE_rq_getfirst();
    
    /* manage the old exec task */
    if (old_exec != EE_NIL) {
      EE_th_status[old_exec] |= EE_WASSTACKED;

      if (EE_th_lockedcounter[old_exec])
	      EE_stk_insertfirst(old_exec);
      else
        EE_rq_insert(old_exec);
    }
    /* program the capacity interrupt */
    EE_hal_capacityIRQ(EE_th_budget_avail[EE_exec]);
    
    if (flag)
      EE_hal_IRQ_stacked(EE_exec);
    else
      EE_hal_IRQ_ready(EE_exec);
  }

  // Program the recharging timer
  if(EE_rcg_queryfirst() != EE_NIL){
    EE_hal_rechargingIRQ(EE_th_absdline[EE_rcg_queryfirst()] - tmp_time);
  }
}

#endif

