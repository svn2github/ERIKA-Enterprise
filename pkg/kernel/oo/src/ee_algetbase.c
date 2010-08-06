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
 * CVS: $Id: ee_algetbase.c,v 1.1 2005/07/16 12:23:42 pj Exp $
 */

#include "ee_internal.h"
#include "../inc/ee_kernel.h"

/* GetAlarmBase
   - This function returns the base characteristics of a counter
   - in Extended Status it returns E_OK or E_OS_ID if the alarm_id is invalid
*/

#ifndef __PRIVATE_GETALARMBASE__
#ifdef __OO_EXTENDED_STATUS__
StatusType EE_oo_GetAlarmBase(AlarmType AlarmID, AlarmBaseRefType Info)
#else
void EE_oo_GetAlarmBase(AlarmType AlarmID, AlarmBaseRefType Info)
#endif
{
  register const EE_oo_counter_ROM_type *c;

#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_GETALARMBASE+1;
#endif


#ifdef __OO_EXTENDED_STATUS__
  if (AlarmID < 0 || AlarmID >= EE_MAX_ALARM) {
#ifdef __OO_ORTI_LASTERROR__
    EE_ORTI_lasterror = E_OS_ID;
#endif

    /* Kernel mutual exclusion needed only here */
#ifdef __OO_HAS_ERRORHOOK__
    EE_hal_begin_primitive();
    if (!EE_ErrorHook_nested_flag) {
#ifndef __OO_ERRORHOOK_NOMACROS__
      EE_oo_ErrorHook_ServiceID = OSServiceId_GetAlarmBase;
      EE_oo_ErrorHook_data.GetAlarmBase_prm.AlarmID = AlarmID;
      EE_oo_ErrorHook_data.GetAlarmBase_prm.Info = Info;
#endif
      EE_ErrorHook_nested_flag = 1U;
      ErrorHook(E_OS_ID);
      EE_ErrorHook_nested_flag = 0U;
    }
    EE_hal_end_primitive();
#endif

#ifdef __OO_ORTI_SERVICETRACE__
    EE_ORTI_servicetrace = EE_SERVICETRACE_GETALARMBASE;
#endif

    return E_OS_ID;
  }
#endif

  /* Fill the informations required */
  c = &EE_counter_ROM[EE_alarm_ROM[AlarmID].c];
  Info->maxallowedvalue = c->maxallowedvalue;
  Info->ticksperbase = c->ticksperbase;
#ifdef __OO_EXTENDED_STATUS__
  Info->mincycle = c->mincycle;
#endif

#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_GETALARMBASE;
#endif

#ifdef __OO_EXTENDED_STATUS__
  return E_OK;
#endif
}
#endif
