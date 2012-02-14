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
 * Types and macros for Autosar layer
 * Author: 2010 Fabio Checconi
 *         2011 Bernardo  Dal Seno
 */

#ifndef __INCLUDE_KERNEL_AS_EE_OS__
#define __INCLUDE_KERNEL_AS_EE_OS__

#if defined(__AS_SC4__)

/*
 * 7.11 Error classification
 * NOTE: the values start from EE_OS_SYS_INIT in oo/inc/ee_common.h
 */

#define EE_AUTOSAR_E_BASE		E_OS_SYS_INIT

#define E_OS_SERVICEID              (EE_AUTOSAR_E_BASE + 1U)
#define E_OS_ILLEGAL_ADDRESS        (EE_AUTOSAR_E_BASE + 2U)
#define E_OS_MISSINGEND             (EE_AUTOSAR_E_BASE + 3U)
#define E_OS_DISABLEDINT            (EE_AUTOSAR_E_BASE + 4U)
#define E_OS_STACKFAULT             (EE_AUTOSAR_E_BASE + 5U)
#define E_OS_PARAMETER_POINTER      (EE_AUTOSAR_E_BASE + 6U)
#define E_OS_PROTECTION_MEMORY      (EE_AUTOSAR_E_BASE + 7U)
#define E_OS_PROTECTION_TIME        (EE_AUTOSAR_E_BASE + 8U)
#define E_OS_PROTECTION_ARRIVAL     (EE_AUTOSAR_E_BASE + 9U)
#define E_OS_PROTECTION_LOCKED      (EE_AUTOSAR_E_BASE + 10U)
#define E_OS_PROTECTION_EXCEPTION   (EE_AUTOSAR_E_BASE + 11U)

/*
 * 8.2 Macros
 */
#define OSMEMORY_IS_READABLE(acc) (((acc) & EE_ACCESS_READ) != (AccessType)0)
#define OSMEMORY_IS_WRITEABLE(acc) (((acc) & EE_ACCESS_WRITE) != (AccessType)0)
#define OSMEMORY_IS_EXECUTABLE(acc) (((acc) & EE_ACCESS_EXEC) != (AccessType)0)
#define OSMEMORY_IS_STACKSPACE(acc) (((acc) & EE_ACCESS_STACK) != (AccessType)0)

/*
 * 8.3 Type definitions
 */

/* This data type identifies the OS-Application. */
typedef	EE_TID	ApplicationType;
#define INVALID_OSAPPLICATION	((ApplicationType)0)

/* This data type identifies the state of an OS-Application. */
typedef enum {
	APPLICATION_ACCESSIBLE,
	APPLICATION_RESTARTING,
	APPLICATION_TERMINATED
} ApplicationStateType;

/* This data type points to location where a ApplicationStateType
 * can be stored. */
typedef ApplicationStateType	*ApplicationStateRefType;

/* This data type identifies a trusted function. */
typedef EE_UINT32 TrustedFunctionIndexType;

/* This data type points to a structure which holds the arguments
 * for a call to a trusted function. */
typedef void *TrustedFunctionParameterRefType;

/* This type holds information how a specific memory region can be accessed. */
typedef EE_UREG	AccessType;
/* AccessType is a mask made by ORing together a subset of these bits: */
#define EE_ACCESS_READ ((AccessType)0x1)
#define EE_ACCESS_WRITE ((AccessType)0x2)
#define EE_ACCESS_EXEC ((AccessType)0x4)
#define EE_ACCESS_STACK ((AccessType)0x8)

/* This data type identifies if an OS-Application has access to an object. */
typedef EE_INT8	ObjectAccessType;
#define ACCESS		((ObjectAccessType)0)
#define NO_ACCESS	((ObjectAccessType)1)

/* This data type identifies an object. */
typedef EE_INT8	ObjectTypeType;
#define OBJECT_TASK		((ObjectTypeType)0)
#define OBJECT_ISR		((ObjectTypeType)1)
#define OBJECT_ALARM		((ObjectTypeType)2)
#define OBJECT_RESOURCE		((ObjectTypeType)3)
#define OBJECT_COUNTER		((ObjectTypeType)4)
#define OBJECT_SCHEDULETABLE	((ObjectTypeType)5)

/* This data type is a pointer which is able to point to any location
 * in the MCU. */
typedef EE_ADDR	MemoryStartAddressType;

/* This data type holds the size (in bytes) of a memory region. */
typedef EE_UREG	MemorySizeType;

/* This data type identifies an interrupt service routine (ISR). */
typedef EE_UREG	ISRType;
#define INVALID_ISR		((ISRType)~(ISRType)0)

/* This data type identifies a schedule table. */
typedef EE_TID	ScheduleTableType;

/* This type describes the status of a schedule. */
typedef EE_INT8	ScheduleTableStatusType;
#define SCHEDULETABLE_STOPPED			((ScheduleTableStatusType)0)
#define SCHEDULETABLE_NEXT			((ScheduleTableStatusType)1)
#define SCHEDULETABLE_WAITING			((ScheduleTableStatusType)2)
#define SCHEDULETABLE_RUNNING			((ScheduleTableStatusType)3)
#define SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS	((ScheduleTableStatusType)4)

/* This data type points to a variable of the data type
 * ScheduleTableStatusType. */
typedef ScheduleTableStatusType *ScheduleTableStatusRefType;

/* This data type identifies a counter. */
typedef EE_TID	CounterType;

/* This data type identifies a value which controls further actions
 * of the OS on return from the protection hook. */
typedef EE_INT8	ProtectionReturnType;
#define PRO_IGNORE			((ProtectionReturnType)0)
#define PRO_TERMINATETASKISR		((ProtectionReturnType)1)
#define PRO_TERMINATEAPPL		((ProtectionReturnType)2)
#define PRO_TERMINATEAPPL_RESTART	((ProtectionReturnType)3)
#define PRO_SHUTDOWN			((ProtectionReturnType)4)

/* This data type defines the use of a Restart Task after
 * terminating an OS-Application. */
typedef EE_INT8	RestartType;
#define RESTART		((RestartType)0)
#define NO_RESTART	((RestartType)1)

/*
 * 8.4 Function definitions
 */
ApplicationType	GetApplicationID(void);
ISRType		GetISRID(void);
AccessType	CheckISRMemoryAccess(ISRType ISRID, MemoryStartAddressType
			Address, MemorySizeType Size);
AccessType	CheckTaskMemoryAccess(TaskType TaskID,
			MemoryStartAddressType Address,
			MemorySizeType Size);
StatusType	CallTrustedFunction(TrustedFunctionIndexType FunctionIndex,
			 TrustedFunctionParameterRefType FunctionParams);

ObjectAccessType
CheckObjectAccess(ApplicationType ApplID, ObjectTypeType ObjectType,
		  EE_TID ObjectID);
ApplicationType CheckObjectOwnership(ObjectTypeType ObjectType,
				EE_TID Object);
StatusType TerminateApplication(ApplicationType Application,
				RestartType RestartOption);
StatusType AllowAccess(void);
StatusType GetApplicationState(const ApplicationType Application,
			       const ApplicationStateRefType Value);

#if 0	/* Defined as macros */
ObjectAccessType CheckObjectAccess(ApplicationType ApplID, ObjectTypeType
			ObjectType, EE_TID ObjectID);
ApplicationType CheckObjectOwnership(ObjectTypeType ObjectType, EE_TID Object);
StatusType	StartScheduleTableRel(ScheduleTableType ScheduleTableID,
			TickType Offset);
StatusType	StartScheduleTableAbs(ScheduleTableType ScheduleTableID,
			TickType Start);
StatusType	StopScheduleTable(ScheduleTableType ScheduleTableID);
StatusType	NextScheduleTable(ScheduleTableType ScheduleTableID_From,
			ScheduleTableType ScheduleTableID_To);
StatusType	StartScheduleTableSynchron(ScheduleTableType ScheduleTableID);
StatusType	SyncScheduleTable(ScheduleTableType ScheduleTableID,
			TickType Value);
StatusType	SetScheduleTableAsync(ScheduleTableType ScheduleTableID);
StatusType	GetScheduleTableStatus(ScheduleTableType ScheduleTableID,
			ScheduleTableStatusRefType ScheduleStatus);
StatusType	IncrementCounter(CounterType CounterID);
StatusType	GetCounterValue(CounterType CounterID, TickRefType Value);
StatusType	GetElapsedTime(CounterType CounterID, TickRefType Value,
			TickRefType ElapsedValue);
StatusType	TerminateApplication(ApplicationType Application,
			RestartType RestartOption);
StatusType	AllowAccess(void);
StatusType	GetApplicationState(ApplicationType Application,
			ApplicationStateRefType Value);
#endif

/* The APIs below should modify the state of interrupts, but they cannot
 * manipulate the state register directly when a syscall is used.  So they take
 * the value of the state register before the syscall and return the value to be
 * set after the syscall.  The syscall handler code takes care of updating the
 * state register.  The HAL is free to use only the IRQ-enable flag or
 * the whole state register as a parameter to the functions below. */

/* DisableAllInterrupts() body */
EE_FREG EE_as_DisableAllInterrupts(EE_FREG prev);
/* EnableAllInterrupts() body */
EE_FREG EE_as_EnableAllInterrupts(EE_FREG prev);
/* SuspendAllInterrupts() body */
EE_FREG EE_as_SuspendAllInterrupts(EE_FREG prev);
/* ResumeAllInterrupts() body */
EE_FREG EE_as_ResumeAllInterrupts(EE_FREG prev);
/* SuspendOSInterrupts() body */
EE_FREG EE_as_SuspendOSInterrupts(EE_FREG prev);
/* ResumeOSInterrupts() body */
EE_FREG EE_as_ResumeOSInterrupts(EE_FREG prev);

#define TerminateISR2 EE_as_TerminateISR2
StatusType TerminateISR2(void);

/* Used to set the ORTI service inside APIs that are normally executed in user
 * mode */
#ifdef __OO_ORTI_SERVICETRACE__
void EE_as_ORTI_set_service(EE_UINT8 srv);
#endif

#endif /* defined(__AS_SC4__) */

#endif /* __INCLUDE_KERNEL_AS_EE_OS__ */
