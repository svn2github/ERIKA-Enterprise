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
 * CVS: $Id: ee_irq_sc.c,v 1.3 2008/07/18 09:53:55 tiberipa Exp $
 */

#include "ee_internal.h"

#ifndef __PRIVATE_IRQ_END_INSTANCE__
/* This function is called at the end of any IRQ Handler.
 * If the interrupt was not generated by budget timer or 
 * recharging timer (flag EE_served), check whether there is
 * preemption
 */
void EE_IRQ_end_instance(void)
{
  register EE_TIME tmp_time;
  register int wasstacked;

  tmp_time = EE_hal_gettime();
  
  /* check_slice: checks the elapsed time on the exec task, putting it into the right
     queue (recharging or ready). at the end EE_exec is EE_NIL */
  EE_frsh_check_slice(tmp_time);
  /* --- */
    
  /* check_recharging: if ready and stacked queue are empty pulls from the recharging queue */
  EE_frsh_check_recharging(tmp_time);
  /* --- */

  /* at this point, exec is for sure EE_NIL (it is set by check_slice) */
  /* select the first task from the ready or stacked queue */
  /* the function set the EE_exec value, removing the task from the queue
     the status is untouched */
  EE_frsh_select_exec();
  /* --- */

  if (EE_exec != EE_NIL) {
    wasstacked = EE_th[EE_exec].status & EE_TASK_WASSTACKED;
    EE_th[EE_exec].status = EE_TASK_READY;  

    /* reprogram the capacity timer for the new task */
    EE_hal_set_budget_timer(EE_vres[EE_th[EE_exec].contract].budget_avail);
    
    if (wasstacked)
      EE_hal_IRQ_stacked(EE_exec);
    else
      EE_hal_IRQ_ready(EE_exec);
  } else {
    /* no task to execute. stop the capacity IRQ */
    EE_hal_stop_budget_timer();
    EE_hal_IRQ_stacked(EE_exec);
  }
}
#endif
