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
 * CVS: $Id: ee_ulockres.c,v 1.3 2006/12/03 22:07:50 pj Exp $
 */

#include "ee_internal.h"

/* ReleaseResource:
   - release a resource
   - lock/unlock on the same function level
   - no point of rescheduling inside critical sections!!!
   - returns (only extended state)
       E_OS_ID     if resource number is invalid
       E_OS_ACCESS if resource already locked or interrupt routine 
                   greater than the ceiling priority

   Extended Status: Count for locked resources!!!!
*/

#ifndef __PRIVATE_RELEASERESOURCE__

#ifdef __OO_EXTENDED_STATUS__
StatusType EE_oo_ReleaseResource(ResourceType ResID)
#else
void EE_oo_ReleaseResource(ResourceType ResID)
#endif
{
  register EE_TID current;
#ifdef __MSRP__
  register EE_UREG isGlobal;
#endif
  register EE_FREG flag;

  EE_ORTI_set_service_in(EE_SERVICETRACE_RELEASERESOURCE);

#ifdef __MSRP__
  isGlobal = EE_oo_isGlobal(ResID);
  ResID = ResID & ~EE_GLOBAL_MUTEX;
#endif

#ifdef __OO_EXTENDED_STATUS__
  /* no comparison for ResID < 0, the type is unsigned! */
  if (ResID >= EE_MAX_RESOURCE) {
    EE_ORTI_set_lasterror(E_OS_ID);

    flag = EE_hal_begin_nested_primitive();
    EE_oo_notify_error_ReleaseResource(ResID, E_OS_ID);
    EE_hal_end_nested_primitive(flag);

    EE_ORTI_set_service_out(EE_SERVICETRACE_RELEASERESOURCE);

    return E_OS_ID;
  }
#endif /* __OO_EXTENDED_STATUS__ */

  current = EE_stk_queryfirst();

#ifdef __OO_EXTENDED_STATUS__
  if (EE_th_ready_prio[current] > EE_resource_ceiling[ResID]) {
    EE_ORTI_set_lasterror(E_OS_ACCESS);

    flag = EE_hal_begin_nested_primitive();
    EE_oo_notify_error_ReleaseResource(ResID, E_OS_ACCESS);
    EE_hal_end_nested_primitive(flag);

    EE_ORTI_set_service_out(EE_SERVICETRACE_RELEASERESOURCE);

    return E_OS_ACCESS;
  }
#endif /* __OO_EXTENDED_STATUS__ */

  flag = EE_hal_begin_nested_primitive();

#ifdef __OO_EXTENDED_STATUS__
  if ((EE_resource_locked[ResID] == 0U) ||
      (EE_th_resource_last[current] != ResID)) {
    EE_ORTI_set_lasterror(E_OS_NOFUNC);

    EE_oo_notify_error_ReleaseResource(ResID, E_OS_NOFUNC);

    EE_hal_end_nested_primitive(flag);
    EE_ORTI_set_service_out(EE_SERVICETRACE_RELEASERESOURCE);

    return E_OS_NOFUNC;
  }

  /* remove the last entry from the data structure */
  EE_th_resource_last[current] = 
    EE_resource_stack[EE_th_resource_last[current]];
#endif /* __OO_EXTENDED_STATUS__ */

#if defined(__OO_EXTENDED_STATUS__) || defined(__OO_ORTI_RES_ISLOCKED__)
  /* ok, we have to free that resource! */
  EE_resource_locked[ResID] = 0U;
#endif

#ifdef __MSRP__
  /* if this is a global resource, unlock the others CPUs */
  if (isGlobal) {
    EE_hal_spin_out((EE_TYPESPIN)ResID);
  }
#endif

  /* there is no need to store that the resource has no more lockers,
     because we inserted an if expression into the ORTI File */
  /* #ifdef __OO_ORTI_RES_LOCKER_TASK__ */
  /*  EE_ORTI_res_locker[ResID] = EE_NIL; */
  /* #endif */

  EE_sys_ceiling = EE_resource_oldceiling[ResID];

#ifdef __OO_ORTI_PRIORITY__
  EE_ORTI_th_priority[current] = EE_ORTI_resource_oldpriority[ResID];
#endif

  /* check if there is a preemption */
  EE_oo_preemption_point();

  EE_hal_end_nested_primitive(flag); 
  EE_ORTI_set_service_out(EE_SERVICETRACE_RELEASERESOURCE);

#ifdef __OO_EXTENDED_STATUS__
  return E_OK;
#endif
}

#endif /* __PRIVATE_RELEASERESOURCE__ */
