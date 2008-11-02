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
 * CVS: $Id: ee_spost.c,v 1.2 2008/07/16 09:46:12 francesco Exp $
 */

#include "ee_internal.h"

#ifndef __PRIVATE_SEM_POST__
void EE_sem_PostSem(SemRefType s)
{
  register EE_FREG flag;
  register EE_TIME tmp_time;
  EE_TID tmp_rq;

  flag = EE_hal_begin_nested_primitive();
  tmp_time = EE_hal_gettime();

  if (s->first != EE_NIL) {
    EE_th_timedout[s->first]=0;
    
    // Search in the recharging queue
    {
      EE_TID p,q;
    
      p = EE_NIL;
      q = EE_rcg_queryfirst();
    
      while ( (q != EE_NIL) && (q != s->first) ) {
        p = q;
        q = EE_th_next[q];
      }
      if( q != EE_NIL ) {
        if( p == EE_NIL )
        {
          EE_rcg_getfirst();
          // Program the recharging timer
          if(EE_rcg_queryfirst() != EE_NIL){
            if(EE_th_status[EE_rcg_queryfirst()] & EE_BLOCKED)
              EE_hal_rechargingIRQ(EE_th_timeouts[EE_rcg_queryfirst()] - tmp_time);
            else
              EE_hal_rechargingIRQ(EE_th_absdline[EE_rcg_queryfirst()] - tmp_time);
          }
        }
        else 
        {
          EE_th_next[p] = EE_th_next[q];
        }
      }
      else
        for(;;);
    }
  
    tmp_rq = s->first;

    // wake up blocked thread
    if ((s->first = EE_th_nextsem[tmp_rq]) == EE_NIL)
      s->last = EE_NIL;
      
   	EE_th_status[tmp_rq] = EE_READY | EE_WASSTACKED;
  	EE_rq_insert(tmp_rq);
    
      /* check if there is a preemption; that is, I have to check if the
      deadline of the task pointed by exec is later than that of the
      first task in the ready queue; moreover, I have to check if the
      preemption level of the first task in the ready queue is high
      enough */
  
    tmp_rq=EE_rq_queryfirst();
    if (!EE_hal_get_IRQ_nesting_level()) {
      if (EE_exec == EE_NIL || 	/* main task! */
  	(tmp_rq != EE_NIL
  	 && (EE_STIME)(EE_th_absdline[EE_exec] - EE_th_absdline[tmp_rq]) > 0
  	 && EE_sys_ceiling < EE_th_prlevel[tmp_rq])) {
  
     /* we have to schedule a ready thread (that maybe is different
  	 from the thread we have just activated, due to ) */
        register EE_TID old_exec;
        register int wasstacked;
    
        old_exec = EE_exec;
        EE_exec = tmp_rq;
    
        /* remove the first task from the ready queue, and set the new
         exec task as READY */
        wasstacked = EE_th_status[tmp_rq] & EE_WASSTACKED;
        EE_th_status[tmp_rq] = EE_READY;
        EE_rq_getfirst();
    
        /* manage the current exec task */
        if (old_exec != EE_NIL) {
    	
        	/* account the capacity to the task that is currently executing */
        	EE_th_budget_avail[old_exec] -= tmp_time - EE_last_time;
    	
        	if (EE_th_budget_avail[old_exec] < EE_TIMER_MINCAPACITY) {
            /* if the badget is exhausted then recharge*/
            EE_th_status[old_exec] = EE_RECHARGING; //Inutile forse
            EE_rcg_insert(old_exec);
          }else if (EE_th_lockedcounter[old_exec])
    	      EE_stk_insertfirst(old_exec);
        	else
        	  EE_rq_insert(old_exec);
      
          EE_th_status[old_exec] |= EE_WASSTACKED;
        }
       
        /* this has to be done in any case */
        EE_last_time = tmp_time;
    
        /* program the capacity interrupt 
        *  if the deadline of the task is in the past
        *  recharge budget and assign the deadline
        */                    
        if((EE_STIME)(EE_th_absdline[tmp_rq]- tmp_time)<=100){
          EE_th_absdline[tmp_rq]=tmp_time+EE_th_period[tmp_rq];
          EE_th_budget_avail[tmp_rq] = EE_th_budget[tmp_rq];
        }
        EE_hal_capacityIRQ(EE_th_budget_avail[tmp_rq]);
        EE_sys_ceiling |= EE_th_prlevel[tmp_rq];
        
        if (wasstacked)
          EE_hal_stkchange(tmp_rq);
        else
          EE_hal_ready2stacked(tmp_rq);

      }
    }
  }
  else
    s->count++;

  EE_hal_end_nested_primitive(flag);
}
#endif
