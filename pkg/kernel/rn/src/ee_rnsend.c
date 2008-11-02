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
 * Author: 2001, 2002 Paolo Gai
 * CVS: $Id: ee_rnsend.c,v 1.9 2006/06/08 20:40:42 pj Exp $
 */

#include "ee_internal.h"

#ifdef __RN__

/* This function can be used to send a remote notification.
   Parameters: the remote notification. MUST BE >0
   Returned values:  None
*/

#ifndef __PRIVATE_RN_SEND__
void EE_rn_send(EE_TYPERN rn, EE_TYPERN_PARAM p, EE_TYPEEVENTMASK ev)
{
  register EE_UINT8 cpu;
  register EE_TYPERN_SWITCH sw;
  register int newIRQ;
  register EE_FREG flag;
  
  flag = EE_hal_begin_nested_primitive();

  /* here we suppose that inter-processor interrupts can not preempt
     this function. For that reason, it is not necessary to lock the
     spin lock here. That is, only one entity for each processor can
     use the notification data structure at a time, and the
     interprocessor interrupt always find the spin lock used by a task
     on another CPU or it find it free. */

  cpu = EE_rn_cpu[rn];

  if (cpu == EE_CURRENTCPU) {
    /* THIS SHOULD NEVER HAPPEN!!!
       Local notification not allowed 
       CHECK YOUR CONFIGURATION FOR THE REMOTE NOTIFICATIONS!!!
       should we return an error?
    */
    EE_hal_end_nested_primitive(flag);
    return;
  } else {
    /* Remote notification */

    /* Spin Lock acquisition */
    EE_hal_spin_in(EE_rn_spin[cpu]);

    /* Note: sw must be read inside the spin-lock because its value
       can be changed by the other CPU! */
    sw = EE_rn_switch[cpu] & EE_RN_SWITCH_COPY;

    /* Check if we should raise a new Interprocessor Interrupt 
     *
     * That is, noone is inside the IIRQ interrupt handler, and noone
     * is already queued on the current data structure
     */
    newIRQ = !(EE_rn_switch[cpu] & EE_RN_SWITCH_INSIDEIRQ) && 
      EE_rn_first[cpu][sw] == -1;

    /* the interrupt handler have to do the cycle again */
    if (EE_rn_switch[cpu] & EE_RN_SWITCH_INSIDEIRQ)
      EE_rn_switch[cpu] |= EE_RN_SWITCH_NEWRN;

    /* Queuing request */
    if (!EE_rn_pending[rn][sw]) {
      /* request was not queued before */

      /* insert it into the pending requests */
      EE_rn_next[rn][sw] = EE_rn_first[cpu][sw];
      EE_rn_first[cpu][sw] = rn;
    }

#ifdef __RN_EVENT__
    EE_rn_event[rn][sw] |= ev; 
#endif

#ifdef __OO_SEM__
    if (p==EE_TYPERN_PARAM_SEM_UNLOCK)
      /* the task has been unlocked! */
      EE_rn_sem[rn][sw] = 1;
    else
#endif
      /* increase the pending counter */
      EE_rn_pending[rn][sw] += p;
    
    /* Spin Lock release */
    EE_hal_spin_out(EE_rn_spin[cpu]);

    /* Inter-processor interrupt 
       
    We raise an interprocessor interrupt only if there is not a
    similar interrupt pending Note that the irq is raised before
    releasing the spin lock, anyway the instructions that are
    still to execute are only a little. In reality, the
    interprocessor interrupt is needed only when rn_first[cpu] !=
    -1. anyway, it's not worth to add this test on the Janus
    architecture.
    */
    if (newIRQ)
      EE_hal_IRQ_interprocessor(cpu);
  }
  
  EE_hal_end_nested_primitive(flag);
}
#endif

#endif
