/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
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
 * APIs for Autosar with memory protection
 * Author: 2010 Fabio Checconi
 *         2011 Bernardo  Dal Seno
 */


#ifndef __INCLUDE_KERNEL_AS_EE_API__
#define __INCLUDE_KERNEL_AS_EE_API__

#ifdef __EE_MEMORY_PROTECTION__

#define ActivateTask(TaskID)	EE_SysCall1((TaskID), EE_ID_ActivateTask)
#define TerminateTask()		EE_SysCall0(EE_ID_TerminateTask)
#define ChainTask(TaskID)	EE_SysCall1((TaskID), EE_ID_ChainTask)
#define Schedule()		EE_SysCall0(EE_ID_Schedule)
#define ForceSchedule()		EE_SysCall0(EE_ID_ForceSchedule)
#define GetTaskID(TaskID)	EE_SysCall1((TaskID), EE_ID_GetTaskID)
#define GetTaskState(TaskID, State)					\
	EE_SysCall2((TaskID), (State), EE_ID_GetTaskState)

/* ----- */

#define EnableAllInterrupts()	EE_SysCall0(EE_ID_EnableAllInterrupts)
#define DisableAllInterrupts()	EE_SysCall0(EE_ID_DisableAllInterrupts)
#define ResumeAllInterrupts()	EE_SysCall0(EE_ID_ResumeAllInterrupts)
#define SuspendAllInterrupts()	EE_SysCall0(EE_ID_SuspendAllInterrupts)
#define ResumeOSInterrupts()	EE_SysCall0(EE_ID_ResumeOSInterrupts)
#define SuspendOSInterrupts()	EE_SysCall0(EE_ID_SuspendOSInterrupts)

/* ----- */

#ifndef __OO_NO_RESOURCES__

#define GetResource(ResID)	EE_SysCall1((ResID), EE_ID_GetResource)
#define ReleaseResource(ResID)	EE_SysCall1((ResID), EE_ID_ReleaseResource)

#endif /* ! __OO_NO_RESOURCES__ */

/* ----- */

#ifndef __OO_NO_EVENTS__

#define SetEvent(TaskID, Mask)	EE_SysCall2((TaskID), (Mask), EE_ID_SetEvent)
#define ClearEvent(Mask)	EE_SysCall1((Mask), EE_ID_ClearEvent)
#define GetEvent(TaskID, Event)	EE_SysCall2((TaskID), (EE_UREG)(Event), \
	EE_ID_GetEvent)
#define WaitEvent(Mask)		EE_SysCall1((Mask), EE_ID_WaitEvent)

#endif /* ! __OO_NO_EVENTS__ */

/* ----- */

#ifndef __OO_NO_ALARMS__

/* Legacy API, not part of Autosar nor OSEK */
#define CounterTick(c)          EE_SysCall1((c), EE_ID_counter_tick)

#define GetAlarmBase(AlarmID, info)					\
	EE_SysCall2((AlarmID), (EE_UREG)(info), EE_ID_GetAlarmBase)
#define GetAlarm(AlarmID, Tick)	EE_SysCall2((AlarmID), (EE_UREG)(Tick), \
	EE_ID_GetAlarm)
#define SetRelAlarm(AlarmID, incr, cycle)				\
	EE_SysCall3((AlarmID), (incr), (cycle), EE_ID_SetRelAlarm)
#define SetAbsAlarm(AlarmID, sta, cycle)				\
	EE_SysCall3((AlarmID), (sta), (cycle), EE_ID_SetAbsAlarm)
#define CancelAlarm(AlarmID)	EE_SysCall1((AlarmID), EE_ID_CancelAlarm)

#endif /* ! __OO_NO_ALARMS__ */

/* ----- */

#define GetActiveApplicationMode()					\
	EE_SysCall0(EE_ID_GetActiveApplicationMode)
#define StartOS(Mode)		EE_SysCall1((Mode), EE_ID_StartOS)
#define ShutdownOS(Error)	EE_SysCall1((Error), EE_ID_ShutdownOS)

/* ----- */

#ifdef __OO_SEM__

#define InitSem(sem, value)	EE_SysCall2((sem), (value), EE_ID_InitSem)
#define WaitSem(sem)		EE_SysCall1((sem), EE_ID_WaitSem)
#define TryWaitSem(sem)		EE_SysCall1((sem), EE_ID_TryWaitSem)
#define PostSem(sem)		EE_SysCall1((sem), EE_ID_PostSem)
#define GetValueSem(sem)	EE_SysCall1((sem), EE_ID_GetValueSem)

#endif /* __OO_SEM__ */

/* EE_ORTI_ext_set_service() is defined in ee_os_internal.h */

#endif /* __EE_MEMORY_PROTECTION__ */

#endif /* __INCLUDE_KERNEL_AS_EE_API__ */
