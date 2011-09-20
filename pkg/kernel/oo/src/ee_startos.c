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
 * CVS: $Id: ee_startos.c,v 1.5 2006/12/03 22:07:50 pj Exp $
 */

#include "ee_internal.h"

/* StartOS

  - called to start the operating system in a specific Application
    mode
  - it does not need to return to the caller
*/


#ifndef __PRIVATE_STARTOS__
#ifdef __OO_EXTENDED_STATUS__
StatusType EE_oo_StartOS(AppModeType Mode)
#else
void EE_oo_StartOS(AppModeType Mode)
#endif
{ 
  EE_TID rq;
#if defined(__OO_AUTOSTART_TASK__) || defined(__OO_AUTOSTART_ALARM__)
  register EE_UINT8 t, n;
#endif

#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_STARTOS+1U;
#endif

#ifdef __OO_CPU_HAS_STARTOS_ROUTINE__
  /* the CPU initialization can return an error; 0 if all ok */
#ifdef __OO_EXTENDED_STATUS__
  if (EE_cpu_startos()) {
#ifdef __OO_ORTI_LASTERROR__
    EE_ORTI_lasterror = E_OS_SYS_INIT;
#endif /* __OO_ORTI_LASTERROR__ */

#ifdef __OO_HAS_ERRORHOOK__
    EE_hal_begin_primitive();
    if (!EE_ErrorHook_nested_flag) {
#ifndef __OO_ERRORHOOK_NOMACROS__
      EE_oo_ErrorHook_ServiceID = OSServiceId_StartOS;
      EE_oo_ErrorHook_data.StartOS_prm.Mode = Mode;
#endif /* __OO_ERRORHOOK_NOMACROS__ */
      EE_ErrorHook_nested_flag = 1U;
      ErrorHook(E_OS_SYS_INIT);
      EE_ErrorHook_nested_flag = 0U;
    }
    EE_hal_end_primitive();
#endif /* __OO_HAS_ERRORHOOK__ */

#ifdef __OO_ORTI_SERVICETRACE__
    EE_ORTI_servicetrace = EE_SERVICETRACE_STARTOS;
#endif

    return E_OS_SYS_INIT;
  }

#else /* __OO_EXTENDED_STATUS__ */
  /* in this case, there is no error or the error is ignored */
  EE_cpu_startos();
#endif /* __OO_EXTENDED_STATUS__ */
#endif /* __OO_CPU_HAS_STARTOS_ROUTINE__ */

  EE_hal_begin_primitive();

  EE_ApplicationMode = Mode;
  
#if defined(__OO_HAS_STARTUPHOOK__) || defined(__OO_AUTOSTART_TASK__) || defined(__OO_AUTOSTART_ALARM__)
  EE_oo_no_preemption = 1U;

#ifdef __OO_HAS_STARTUPHOOK__
  StartupHook();
#endif

#if defined(__OO_AUTOSTART_TASK__) || defined(__OO_AUTOSTART_ALARM__)
	if (Mode < EE_MAX_APPMODE) {
#ifdef __OO_AUTOSTART_TASK__
    n = (EE_UINT8)(EE_oo_autostart_task_data[Mode].n);
    for (t = 0U; t<n; t++) {
      (void)EE_oo_ActivateTask(EE_oo_autostart_task_data[Mode].task[t]);
    }
#endif

#ifdef __OO_AUTOSTART_ALARM__
    n = (EE_UINT8)(EE_oo_autostart_alarm_data[Mode].n);
    for (t = 0U; t<n; t++) {
      EE_TYPEALARM alarm_temp = EE_oo_autostart_alarm_data[Mode].alarm[t];
      (void)EE_oo_SetRelAlarm(alarm_temp,
			EE_oo_autostart_alarm_increment[alarm_temp],
			EE_oo_autostart_alarm_cycle[alarm_temp]);
    }
#endif
  }
#endif

  EE_oo_no_preemption = 0U;
#endif

  /* check if there is a preemption */
  rq = EE_rq_queryfirst();
  if (rq != EE_NIL) {
      /* get the internal resource */
      EE_sys_ceiling |= EE_th_dispatch_prio[rq];
      /* put the task in running state */
      EE_th_status[rq] = RUNNING;

#ifdef __OO_ORTI_PRIORITY__
      EE_ORTI_th_priority[rq] = EE_th_dispatch_prio[rq];
#endif
      
#if defined(__OO_ECC1__) || defined(__OO_ECC2__)
      /* Since we are into the StartOS, the task was NOT previously on
	 the stack... (we do not have to check the wasstacked field */
      EE_hal_ready2stacked(EE_rq2stk_exchange());
#else
      EE_hal_ready2stacked(EE_rq2stk_exchange());
#endif
  }
  EE_hal_end_primitive();

#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_STARTOS;
#endif

#ifdef __OO_EXTENDED_STATUS__
  return E_OK;
#endif
}

#endif
