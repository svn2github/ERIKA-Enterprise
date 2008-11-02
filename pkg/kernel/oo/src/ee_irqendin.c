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
 * Author: 2002-2004 Paolo Gai
 * CVS: $Id: ee_irqendin.c,v 1.2 2006/01/24 10:21:14 pj Exp $
 */

#include "ee_internal.h"


#ifndef __PRIVATE_IRQ_END_INSTANCE__
/* This primitive shall be atomic.
   This primitive shall be inserted as the last function in an IRQ handler.
   If the HAL allow IRQ nesting the C_end_instance should work as follows:
   - it must implement the preemption test only if it is the last IRQ on the stack
   - if there are other interrupts on the stack the IRQ end_instance should do nothing
*/
void EE_IRQ_end_instance(void)
{
  register EE_TID tmp;
  register EE_TID tmp_stacked;
  
  tmp = EE_rq_queryfirst();
  tmp_stacked = EE_stk_queryfirst();

  if (tmp != EE_NIL && EE_sys_ceiling < EE_th_ready_prio[tmp]) {
      /* we have to schedule a ready thread */

      if (tmp_stacked != EE_NIL) {
#ifdef __OO_HAS_POSTTASKHOOK__
	/* there is a post task hook only if there is a task that is running */
	PostTaskHook();
#endif	
	/* the running task is now suspended */
	EE_th_status[tmp_stacked] = READY;
      }

      /* and another task is put into the running state */
      EE_th_status[tmp] = RUNNING;
      
      EE_sys_ceiling |= EE_th_dispatch_prio[tmp];

#ifdef __OO_ORTI_PRIORITY__
      EE_ORTI_th_priority[tmp] = EE_th_dispatch_prio[tmp];
#endif
      
#if defined(__OO_ECC1__) || defined(__OO_ECC2__)
      tmp = EE_rq2stk_exchange();
      if (EE_th_waswaiting[tmp]) {
	EE_th_waswaiting[tmp] = 0;
#ifdef __OO_HAS_PRETASKHOOK__
	PreTaskHook();
#endif	
	EE_hal_IRQ_stacked(tmp);
      }
      else
	EE_hal_IRQ_ready(tmp);
#else
      EE_hal_IRQ_ready(EE_rq2stk_exchange());
#endif
  }
  else
    EE_hal_IRQ_stacked(EE_stk_queryfirst());
}

#endif /* __PRIVATE_IRQ_END_INSTANCE__ */
