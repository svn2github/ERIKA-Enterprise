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
 * Author: 2003- Paolo Gai
 * CVS: $Id: ee_rn_internal.h,v 1.5 2007/06/01 09:00:21 pj Exp $
 */


#ifndef __KERNEL_RN_RN_INTERNAL_H__
#define __KERNEL_RN_RN_INTERNAL_H__

#ifdef  __RN__

#include "kernel/rn/inc/ee_rn.h"

/* For each CPU: an index that says informations about the queuing data
   structure should be used by the rn_send function. Init value=0 
   Flags: 
   - bit 0 which copy of the data structures
   - bit 1 inside or not an interrupt handler
   - bit 2 a new remote notification arrived while inside an interrupt handler
*/

#define EE_RN_SWITCH_COPY      1
#define EE_RN_SWITCH_INSIDEIRQ 2
#define EE_RN_SWITCH_NEWRN     4
extern EE_TYPERN_SWITCH EE_rn_switch[];



/*
  this is used as parameter for EE_rn_send.
  from 0 to n, it stores the pending activations.
  if equal 0xf...f then it means "semaphore unlock"
  
*/
typedef EE_UREG EE_TYPERN_PARAM;

#ifdef __OO_SEM__
#define EE_TYPERN_PARAM_SEM_UNLOCK ((EE_TYPERN_PARAM)~0)
#endif

/*
 * EE_TYPEEVENTMASK is defined only in OO
 */
#if defined(__FP__) || defined(__EDF__) || defined(__CBS__)
#define EE_TYPEEVENTMASK EE_UREG
#endif


/* This function can be used to send a remote notification
   Parameters: the remote notification (MUST BE >0)
   Returned values: none 
*/
#ifndef __PRIVATE_RN_SEND__
extern void EE_rn_send(EE_TYPERN rn, EE_TYPERN_PARAM p, EE_TYPEEVENTMASK ev);
#endif

/* this function can be used into an interrupt handler to handle
   pending notifications. It will execute all the pending
   notification. Execution order may not respect the original
   notification order. */
#ifndef __PRIVATE_RN_HANDLER__
extern void EE_rn_handler(void);
#endif

#endif // __RN__
#endif
