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

#ifndef __PRIVATE_IRQ_END_BUDGET__
/* This primitive shall be atomic.
 * This primitive shall be inserted as the last function in an IRQ handler.
 * If the HAL allow IRQ nesting the C_end_instance should work as follows:
 * - it must implement the preemption test only if it is the last IRQ
 *   on the stack
 * - if there are other interrupts on the stack the IRQ scheduler
 *   should do nothing
*/

/*
 * This routine shall be called when the budget timer expires.
 * the task interrupted is switched to recharging.
 * Anyway, if there are no more ready task, one or more recharging
 * task are immediately recharged.
 */

int recharge(EE_TIME);

void EE_IRQ_end_budget(void)
{
  EE_served=1;
  register EE_TIME tmp_time;
  register EE_TID t_rq,t_stk;

  if (EE_th_lockedcounter[EE_exec]){
    EE_hal_IRQ_stacked(EE_exec);
    return;
  }
  
  //update the task status to recharging
  EE_th_status[EE_exec] = EE_RECHARGING | EE_WASSTACKED;
  EE_rcg_insert(EE_exec);
  tmp_time = EE_hal_gettime();

  // this has to be done in any case
  EE_last_time = tmp_time;
 
  if(EE_rcg_queryfirst() == EE_exec){
    if((EE_STIME)(EE_th_absdline[EE_exec]- tmp_time)<0){
      /* immedialtely recharge */
      EE_rcg_getfirst();
      EE_th_absdline[EE_exec]=tmp_time+EE_th_period[EE_exec];
      EE_th_budget_avail[EE_exec] = EE_th_budget[EE_exec];
      EE_th_status[EE_exec] = EE_READY | EE_WASSTACKED;
      EE_rq_insert(EE_exec);
    }else
      EE_hal_rechargingIRQ( EE_th_absdline[EE_rcg_queryfirst()] - tmp_time );
  }
 
  t_rq=EE_rq_queryfirst();
  t_stk=EE_stk_queryfirst();
  
  if(t_rq == EE_NIL && t_stk == EE_NIL){
  // if there are not tasks in the ready and in the stacked queue, 
  // immediately recharge one or more task.
    recharge(tmp_time);
  }
  
  t_rq = EE_rq_queryfirst();

#ifdef DEBUG 
  if(t_rq == EE_NIL) for(;;);
#endif

  if(t_rq == EE_NIL ||  // note that this test work also for the main task!
      ( t_stk != EE_NIL && ( (EE_STIME)(EE_th_absdline[t_stk] - 
		   EE_th_absdline[t_rq]) <= 0
	|| EE_sys_ceiling >= EE_th_prlevel[t_rq]) )) {
  
    // The task in the stacked queue has to be executed
    EE_exec = t_stk;
    EE_stk_getfirst();
    EE_hal_capacityIRQ(EE_th_budget_avail[EE_exec]); 
    EE_th_status[EE_exec] = EE_READY;
    EE_hal_IRQ_stacked(t_stk);
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
      EE_hal_IRQ_stacked(t_rq);
    else
      EE_hal_IRQ_ready(t_rq);
  }

}
#endif
