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
 * CVS: $Id: ee_recharge.c,v 1.2 2008/07/21 16:46:40 francesco Exp $
 */

#include "ee_internal.h"

/* try to recharge task
 * RET value:
 * - 1 if recharged one or more task
 * - 0 otherwise
 */

int recharge(EE_TIME tmp_time)
{
  /* if there are not tasks in the ready and in the stacked queue,
   * check if there are task in recharging queue and if so, immediately
   * recharge one or more of them.
   */
  register EE_TIME delta;
  EE_TID t;
  
  /* Check for negative budget and in case re-insert in the rcg queue */
  for(;;){
    EE_TID p;
  
    p = EE_NIL;
    t = EE_rcg_queryfirst();
  
    while ( (t != EE_NIL) && (EE_th_status[t] & EE_RECHARGING) != EE_RECHARGING ) {
      p = t;
      t = EE_th_next[t];
    }
    if(t == EE_NIL){
      /* next thread is main */
//      EE_exec=EE_NIL;
      /* turn off budget timer */
//      EE_hal_stop_budget_timer();
//      EE_hal_endcycle_stacked(EE_exec);
      return 0;
    }
    if( p == EE_NIL ){
      EE_rcg_getfirst();
    }
    else{
      EE_th_next[p] = EE_th_next[t];
    }
    if( (EE_th_budget_avail[t] += EE_th_budget[t]) > EE_TIMER_MINCAPACITY )
      break;
    EE_th_absdline[t]+=EE_th_period[t];
    EE_rcg_insert(t);
  }
  
  /* t is the recharged task: it is now set to ready */
  EE_rq_insert(t);
  EE_th_status[t] = EE_READY | EE_WASSTACKED;
  delta=EE_th_absdline[t]-tmp_time; 
  EE_th_absdline[t]=tmp_time+EE_th_period[t];

  t=EE_rcg_queryfirst();

  EE_TID prev=EE_NIL;

  /* update recharging times */
  while(t!=EE_NIL){
    if(EE_th_status[t] & EE_RECHARGING){
      EE_th_absdline[t]-=delta;

	  /* if the deadline is (almost) 0 */
      if((EE_STIME)(EE_th_absdline[t]-tmp_time)<=100){
        EE_TID t_tmp=t;
        if(prev != EE_NIL)
          EE_th_next[prev]=EE_th_next[t];
        else
          EE_rcg_getfirst();
        EE_th_absdline[t_tmp]=tmp_time+EE_th_period[t_tmp];
        EE_th_budget_avail[t_tmp] = EE_th_budget[t_tmp];
        EE_rq_insert(t_tmp);
        prev=t;
        t=EE_th_next[t];
      }
      else{
        prev=t;
        t=EE_th_next[t];
      }
    }
    else{
      prev=t;
      t=EE_th_next[t];
    }
  }
  
  if(EE_rcg_queryfirst() != EE_NIL){
#ifdef __SEM_FRSH__
    if(EE_th_status[EE_rcg_queryfirst()] & EE_BLOCKED) {
      EE_hal_rechargingIRQ(EE_th_timeouts[EE_rcg_queryfirst()] - tmp_time);
    }
    else
#endif
      EE_hal_rechargingIRQ(EE_th_absdline[EE_rcg_queryfirst()] - tmp_time);
  }
  else
    EE_hal_stop_recharging_timer();
  
  return 1;
}
