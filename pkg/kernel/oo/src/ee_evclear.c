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
 * CVS: $Id: ee_evclear.c,v 1.1 2005/07/16 12:23:42 pj Exp $
 */

#include "ee_internal.h"
#include "../inc/ee_kernel.h"

/* ClearEvent:
   - can be called from an extended task
   - clear the events for the task
   - returns (only extended state)
       E_OS_CALLEVEL call at interrupt level
       E_OS_ACCESS   if the task is not an extended task
*/


#if defined(__OO_ECC1__) || defined(__OO_ECC2__)
#ifndef __PRIVATE_CLEAREVENT__

#ifdef __OO_EXTENDED_STATUS__
StatusType EE_oo_ClearEvent(EventMaskType Mask)
#else
void EE_oo_ClearEvent(EventMaskType Mask)
#endif
{
  EE_TID current;

#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_CLEAREVENT+1;
#endif

  current = EE_stk_queryfirst();



#ifdef __OO_EXTENDED_STATUS__

  /* check for a call at interrupt level; This must be the FIRST check! */
  if (EE_hal_get_IRQ_nesting_level()) {
#ifdef __OO_ORTI_LASTERROR__
    EE_ORTI_lasterror = E_OS_CALLEVEL;
#endif

#ifdef __OO_HAS_ERRORHOOK__
    EE_hal_begin_primitive();
    if (!EE_ErrorHook_nested_flag) {  
#ifndef __OO_ERRORHOOK_NOMACROS__
      EE_oo_ErrorHook_ServiceID = OSServiceId_ClearEvent;
      EE_oo_ErrorHook_data.ClearEvent_prm.Mask = Mask;
#endif
      EE_ErrorHook_nested_flag = 1U;
      ErrorHook(E_OS_CALLEVEL);
      EE_ErrorHook_nested_flag = 0U;
    }
    EE_hal_end_primitive();
#endif

#ifdef __OO_ORTI_SERVICETRACE__
    EE_ORTI_servicetrace = EE_SERVICETRACE_CLEAREVENT;
#endif

    return E_OS_CALLEVEL;
  }
  
  /* check if the task Id is valid */
  if (!EE_th_is_extended[current]) {
#ifdef __OO_ORTI_LASTERROR__
    EE_ORTI_lasterror = E_OS_ACCESS;
#endif

#ifdef __OO_HAS_ERRORHOOK__
    EE_hal_begin_primitive();
    if (!EE_ErrorHook_nested_flag) {  
#ifndef __OO_ERRORHOOK_NOMACROS__
      EE_oo_ErrorHook_ServiceID = OSServiceId_ClearEvent;
      EE_oo_ErrorHook_data.ClearEvent_prm.Mask = Mask;
#endif
      EE_ErrorHook_nested_flag = 1U;
      ErrorHook(E_OS_ACCESS);
      EE_ErrorHook_nested_flag = 0U;
    }
    EE_hal_end_primitive();
#endif

#ifdef __OO_ORTI_SERVICETRACE__
    EE_ORTI_servicetrace = EE_SERVICETRACE_CLEAREVENT;
#endif

    return E_OS_ACCESS;
  }
#endif


  EE_hal_begin_primitive();

  /* clear the event */
  EE_th_event_active[current] &= ~Mask;

  EE_hal_end_primitive();

#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_CLEAREVENT;
#endif

#ifdef __OO_EXTENDED_STATUS__
  return E_OK;
#endif
}

#endif
#endif
