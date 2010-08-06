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
 * CVS: $Id: ee_alsetabs.c,v 1.1 2005/07/16 12:23:42 pj Exp $
 */

#include "ee_internal.h"
#include "../inc/ee_kernel.h"

/* SetAbsAlarm
   - This function occupies the AlarmID setting an alarm when the counter 
     will reach the absolute value passed as parameter.
   - the Alarm must not be already in use

   returns the relative value in ticks before the alarm expires
   - it returns E_OK if all OK
     E_OS_STATE if the Alarm is already used
     E_OS_ID if the alarm is invalid (only Extended status)
     E_OS_VALUE if the parameters are incorrect
*/

void EE_oo_alarm_insert(AlarmType AlarmID, TickType increment);

#ifndef __PRIVATE_SETABSALARM__
StatusType EE_oo_SetAbsAlarm(AlarmType AlarmID, 
				  TickType start, 
				  TickType cycle)
{
  register EE_FREG flag;

#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_SETABSALARM+1;
#endif

#ifdef __OO_EXTENDED_STATUS__
  if (AlarmID < 0 || AlarmID >= EE_MAX_ALARM) {
#ifdef __OO_ORTI_LASTERROR__
    EE_ORTI_lasterror = E_OS_ID;
#endif

#ifdef __OO_HAS_ERRORHOOK__
    flag = EE_hal_begin_nested_primitive();
    if (!EE_ErrorHook_nested_flag) {
#ifndef __OO_ERRORHOOK_NOMACROS__
      EE_oo_ErrorHook_ServiceID = OSServiceId_SetAbsAlarm;
      EE_oo_ErrorHook_data.SetAbsAlarm_prm.AlarmID = AlarmID;
      EE_oo_ErrorHook_data.SetAbsAlarm_prm.start = start;
      EE_oo_ErrorHook_data.SetAbsAlarm_prm.cycle = cycle;
#endif
      EE_ErrorHook_nested_flag = 1U;
      ErrorHook(E_OS_ID);
      EE_ErrorHook_nested_flag = 0U;
    }
    EE_hal_end_nested_primitive(flag);
#endif

#ifdef __OO_ORTI_SERVICETRACE__
    EE_ORTI_servicetrace = EE_SERVICETRACE_SETABSALARM;
#endif

    return E_OS_ID;
  }
#endif

  /* let the system still work if the start parameter is 0 note that 0
   * is still an invalid value, so I decided arbitrarily to let it
   * fire the next tick.
   */
  if (start==0U) {
    start = 1U;
  }

#ifdef __OO_EXTENDED_STATUS__
  if (start > EE_counter_ROM[EE_alarm_ROM[AlarmID].c].maxallowedvalue
      || 
      (cycle && 
       (cycle < EE_counter_ROM[EE_alarm_ROM[AlarmID].c].mincycle ||
	cycle > EE_counter_ROM[EE_alarm_ROM[AlarmID].c].maxallowedvalue))
      ) {
#ifdef __OO_ORTI_LASTERROR__
    EE_ORTI_lasterror = E_OS_VALUE;
#endif

#ifdef __OO_HAS_ERRORHOOK__
    flag = EE_hal_begin_nested_primitive();
    if (!EE_ErrorHook_nested_flag) {
#ifndef __OO_ERRORHOOK_NOMACROS__
      EE_oo_ErrorHook_ServiceID = OSServiceId_SetAbsAlarm;
      EE_oo_ErrorHook_data.SetAbsAlarm_prm.AlarmID = AlarmID;
      EE_oo_ErrorHook_data.SetAbsAlarm_prm.start = start;
      EE_oo_ErrorHook_data.SetAbsAlarm_prm.cycle = cycle;
#endif
      EE_ErrorHook_nested_flag = 1U;
      ErrorHook(E_OS_VALUE);
      EE_ErrorHook_nested_flag = 0U;
    }
    EE_hal_end_nested_primitive(flag);
#endif

#ifdef __OO_ORTI_SERVICETRACE__
    EE_ORTI_servicetrace = EE_SERVICETRACE_SETABSALARM;
#endif

    return E_OS_VALUE;
  }
#endif



  flag = EE_hal_begin_nested_primitive();

  if (EE_alarm_RAM[AlarmID].used) {
#ifdef __OO_ORTI_LASTERROR__
    EE_ORTI_lasterror = E_OS_STATE;
#endif

#ifdef __OO_HAS_ERRORHOOK__
    if (!EE_ErrorHook_nested_flag) {
#ifndef __OO_ERRORHOOK_NOMACROS__
      EE_oo_ErrorHook_ServiceID = OSServiceId_SetAbsAlarm;
      EE_oo_ErrorHook_data.SetAbsAlarm_prm.AlarmID = AlarmID;
      EE_oo_ErrorHook_data.SetAbsAlarm_prm.start = start;
      EE_oo_ErrorHook_data.SetAbsAlarm_prm.cycle = cycle;
#endif
      EE_ErrorHook_nested_flag = 1U;
      ErrorHook(E_OS_STATE);
      EE_ErrorHook_nested_flag = 0U;
    }
#endif

    EE_hal_end_nested_primitive(flag);

#ifdef __OO_ORTI_SERVICETRACE__
    EE_ORTI_servicetrace = EE_SERVICETRACE_SETABSALARM;
#endif

    return E_OS_STATE;
  }

  /* first, use the alarm and set the cycle */
  EE_alarm_RAM[AlarmID].used = 1U;
  EE_alarm_RAM[AlarmID].cycle = cycle;

  EE_oo_alarm_insert(AlarmID, start - 
			  EE_counter_RAM[EE_alarm_ROM[AlarmID].c].value);
  
  EE_hal_end_nested_primitive(flag);

#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_SETABSALARM;
#endif

  return E_OK;
}
#endif
