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
 * CVS: $Id: ee_thact.c,v 1.4 2007/06/14 10:27:12 pj Exp $
 */

#include "ee_internal.h"

#ifndef __PRIVATE_THREAD_ACTIVATE__

void EE_cbs_thread_activate(EE_TID t)
{
  register EE_TID tmp_rq;
  register EE_TIME tmp_time;
  register EE_FREG flag;
  
  flag = EE_hal_begin_nested_primitive();

  /* read the current time; this will be used later to compute task's
     deadlines */
  tmp_time = EE_hal_gettime();

  if (EE_th_nact[t] == 0) {
    /* since nact==0, the task has not been stacked before, and so it
       is safe to put it in the READY state */

    EE_cbs_updatecapacity(t, tmp_time);

    EE_th_status[t] = EE_READY;
    EE_rq_insert(t);
  }

  EE_th_nact[t]++;

  tmp_rq = EE_rq_queryfirst();
      
  /* check if there is a preemption; that is, I have to check if the
     deadline of the task pointed by exec is later than that of the
     first task in the ready queue; moreover, I have to check if the
     preemption level of the first task in the ready queue is high
     enough */
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
	EE_th_status[old_exec] |= EE_WASSTACKED;
	/* account the capacity to the task that is currently executing */
	EE_th_budget_avail[old_exec] -= tmp_time - EE_last_time;
	
	EE_cbs_updatecapacity(old_exec, tmp_time);
	
	if (EE_th_lockedcounter[old_exec])
	  EE_stk_insertfirst(old_exec);
	else
	  EE_rq_insert(old_exec);
      }
      
      /* this has to be done in any case */
      EE_last_time = tmp_time;
      
      /* program the capacity interrupt */
      EE_hal_capacityIRQ(EE_th_budget_avail[tmp_rq]);
      
      if (wasstacked)
	EE_hal_stkchange(tmp_rq);
      else
	EE_hal_ready2stacked(tmp_rq);
    }
  }

  EE_hal_end_nested_primitive(flag);
}

#endif
