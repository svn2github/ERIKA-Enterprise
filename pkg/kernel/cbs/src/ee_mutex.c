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
 * CVS: $Id: ee_mutex.c,v 1.2 2007/06/14 10:27:12 pj Exp $
 */

#include "ee_internal.h"

#ifndef __PRIVATE_MUTEX_LOCK__
void EE_cbs_mutex_lock(EE_MUTEX m)
{
    EE_hal_begin_primitive();
    
    EE_mutex_oldceiling[m] = EE_sys_ceiling;
    EE_sys_ceiling |= EE_mutex_ceiling[m];
    EE_th_lockedcounter[EE_exec]++;
    
    EE_hal_end_primitive();
}
#endif /* __PRIVATE_MUTEX_LOCK__ */




#ifndef __PRIVATE_MUTEX_UNLOCK__
void EE_cbs_mutex_unlock(EE_MUTEX m)
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
  EE_cbs_updatecapacity(old_exec, tmp_time);
  EE_last_time = tmp_time;

  /* this code is similar to the EE_cbs_sys_scheduler()!!! */
  t = EE_rq_queryfirst();

  test_ready = 
    t != EE_NIL &&
    (EE_STIME)(EE_th_absdline[old_exec] - EE_th_absdline[t]) > 0
    && EE_sys_ceiling < EE_th_prlevel[t];

  test_stacked =
    EE_stk_queryfirst() != EE_NIL &&
    EE_th_lockedcounter[old_exec] == 0;

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
    EE_hal_capacityIRQ(EE_th_budget_avail[t]);

    if (flag)
      EE_hal_stkchange(t);
    else
      EE_hal_ready2stacked(t);
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
    EE_hal_capacityIRQ(EE_th_budget_avail[t]);

    EE_hal_stkchange(t);
  }


  EE_hal_end_primitive();
}			   

#endif /* __PRIVATE_MUTEX_UNLOCK__ */
