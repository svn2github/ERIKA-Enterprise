/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2012  Evidence Srl
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

 /** @file      ee_as_kernel.h
  *  @brief     Types and macros for Autosar layer
  *  @author    Errico Guidieri
  *  @date      2012
  */

#ifndef INCLUDE_EE_KERNEL_AS_KERNEL__
#define INCLUDE_EE_KERNEL_AS_KERNEL__

#ifndef __AS_SC4__

#define OSId_AS_Sevices_Begin                   OSId_OO_Services_End

#define OSServiceId_GetNumberOfActivatedCores   OSId_AS_Sevices_Begin
#define OSServiceId_GetCoreID                   (OSId_AS_Sevices_Begin + 1U)
#define OSServiceId_StartCore                   (OSId_AS_Sevices_Begin + 2U)
#define OSServiceId_StartNonAutosarCore         (OSId_AS_Sevices_Begin + 3U)
#define OSServiceId_GetSpinlock                 (OSId_AS_Sevices_Begin + 4U)
#define OSServiceId_ReleaseSpinlock             (OSId_AS_Sevices_Begin + 5U)
#define OSServiceId_TryToGetSpinlock            (OSId_AS_Sevices_Begin + 6U)
#define OSServiceId_ShutdownAllCores            (OSId_AS_Sevices_Begin + 7U)
/*                  Inter OSApplication Communication (IOC)                   */
#define OSServiceId_IOCService                  (OSId_AS_Sevices_Begin + 8U)
/*                          OS-Applications Services                          */
#define OSServiceId_GetApplicationState         (OSId_AS_Sevices_Begin + 9U)
#define OSServiceId_TerminateApplication        (OSId_AS_Sevices_Begin + 10U)
#define OSServiceId_AllowAccess                 (OSId_AS_Sevices_Begin + 11U)
/*                             Trusted Function                               */
#define OSServiceId_CallTrustedFunction         (OSId_AS_Sevices_Begin + 12U)
/*                              Schedule Table                                */
#define OSServiceId_StartScheduleTableRel       (OSId_AS_Sevices_Begin + 13U)
#define OSServiceId_StartScheduleTableAbs       (OSId_AS_Sevices_Begin + 14U)
#define OSServiceId_StopScheduleTable           (OSId_AS_Sevices_Begin + 15U)
#define OSServiceId_NextScheduleTable           (OSId_AS_Sevices_Begin + 16U)
#define OSServiceId_GetScheduleTableStatus      (OSId_AS_Sevices_Begin + 17U)
#define OSServiceId_SyncScheduleTable           (OSId_AS_Sevices_Begin + 18U)
/*                       Service Protection Check API                         */
#define OSServiceId_CheckObjectOwnership        (OSId_AS_Sevices_Begin + 19U)
#define OSServiceId_CheckObjectAccess           (OSId_AS_Sevices_Begin + 20U)
/*                        Memory Protection Check API                         */
#define OSServiceId_CheckTaskMemoryAccess       (OSId_AS_Sevices_Begin + 21U)
#define OSServiceId_CheckISRMemoryAccess        (OSId_AS_Sevices_Begin + 22U)
/*                        GetApplicationID & GetISRID
          (put here because forgotten and RT-Druid support already ORTI)      */
#define OSServiceId_GetApplicationID            (OSId_AS_Sevices_Begin + 22U)
#define OSServiceId_GetISRID                    (OSId_AS_Sevices_Begin + 23U)

/*******************************************************************************
 *                            Standard Defines
 ******************************************************************************/

/* 8.1 Constants */
/* Application Mode do not Care */
#define DONOTCARE ((AppModeType)-1)

/*******************************************************************************
 *                              ORTI support
 ******************************************************************************/

/*  The last OO service called by the application. SERVICETRACE IDs
    are even numbers. The LSBit is used as a flag and it is set to 1
    when the servce is entered, to 0 at exit.
    (Needed here, not in intenal, for services inline implementation). */
#ifdef __OO_ORTI_SERVICETRACE__

#define EE_SERVICETRACE_AS_BEGIN                    EE_SERVICETRACE_OO_LAST

#define EE_SERVICETRACE_GETNUMBEROFACTIVATEDCORES   EE_SERVICETRACE_AS_BEGIN
#define EE_SERVICETRACE_GETCOREID             (EE_SERVICETRACE_AS_BEGIN + 2U)
#define EE_SERVICETRACE_STARTCORE             (EE_SERVICETRACE_AS_BEGIN + 4U)
#define EE_SERVICETRACE_STARTNONAUTOSARCORE   (EE_SERVICETRACE_AS_BEGIN + 6U)
#define EE_SERVICETRACE_GETSPINLOCK           (EE_SERVICETRACE_AS_BEGIN + 8U)
#define EE_SERVICETRACE_RELEASESPINLOCK       (EE_SERVICETRACE_AS_BEGIN + 10U)
#define EE_SERVICETRACE_TRYTOGETSPINLOCK      (EE_SERVICETRACE_AS_BEGIN + 12U)
#define EE_SERVICETRACE_SHUTDOWNALLCORES      (EE_SERVICETRACE_AS_BEGIN + 14U)
#define EE_SERVICETRACE_CHECKTASKMEMORYACCESS (EE_SERVICETRACE_AS_BEGIN + 16U)
#define EE_SERVICETRACE_CHECKISRMEMORYACCESS  (EE_SERVICETRACE_AS_BEGIN + 18U)
#define EE_SERVICETRACE_GETAPPLICATIONID      (EE_SERVICETRACE_AS_BEGIN + 20U)
#define EE_SERVICETRACE_GETISRID              (EE_SERVICETRACE_AS_BEGIN + 22U)
#define EE_SERVICETRACE_GETAPPLICATIONSTATE   (EE_SERVICETRACE_AS_BEGIN + 24U)
#define EE_SERVICETRACE_TERMINATEAPPLICATION  (EE_SERVICETRACE_AS_BEGIN + 26U)
#define EE_SERVICETRACE_ALLOWACCESS           (EE_SERVICETRACE_AS_BEGIN + 28U)
#define EE_SERVICETRACE_CHECKOBJECTACCESS     (EE_SERVICETRACE_AS_BEGIN + 30U)
#define EE_SERVICETRACE_CHECKOBJECTOWNERSHIP  (EE_SERVICETRACE_AS_BEGIN + 32U)
#define EE_SERVICETRACE_CALLTRUSTEDFUNCTION   (EE_SERVICETRACE_AS_BEGIN + 34U)
#define EE_SERVICETRACE_STARTSCHEDULETABLEREL (EE_SERVICETRACE_AS_BEGIN + 36U)
#define EE_SERVICETRACE_STARTSCHEDULETABLEABS (EE_SERVICETRACE_AS_BEGIN + 38U)
#define EE_SERVICETRACE_STOPSCHEDULETABLE     (EE_SERVICETRACE_AS_BEGIN + 40U)
#define EE_SERVICETRACE_NEXTSCHEDULETABLE     (EE_SERVICETRACE_AS_BEGIN + 42U)
#define EE_SERVICETRACE_GETSCHEDULETABLESTATUS  \
  (EE_SERVICETRACE_AS_BEGIN + 44U)
#define EE_SERVICETRACE_SYNCSCHEDULETABLE     (EE_SERVICETRACE_AS_BEGIN + 46U)
#endif /* __OO_ORTI_SERVICETRACE__ */

#ifdef __MSRP__
/*******************************************************************************
 *               System Services Implemented Inline inclusion
 ******************************************************************************/
#include "kernel/as/inc/ee_as_inline.h"

/* Fololwing types and services declaration have reason only in multicore
   environment */
#ifndef __PRIVATE_STARTOS__
void EE_as_StartCore( CoreIdType CoreID, StatusType *Status );
void EE_as_StartNonAutosarCore( CoreIdType CoreID, StatusType *Status );
#endif /* !__PRIVATE_STARTOS__ */


#if defined(EE_AS_USER_SPINLOCKS__)  && (!defined(EE_PRIVATE_SPINLOCK__))
StatusType EE_as_GetSpinlock( SpinlockIdType SpinlockId );
StatusType EE_as_ReleaseSpinlock( SpinlockIdType SpinlockId );
StatusType EE_as_TryToGetSpinlock( SpinlockIdType SpinlockId,
  TryToGetSpinlockType* Success );

#endif /* EE_AS_USER_SPINLOCKS__ && !EE_PRIVATE_SPINLOCK__ */

#if (!defined(__PRIVATE_SHUTDOWNOS__)) && defined(EE_AS_RPC__)
void EE_as_ShutdownAllCores( StatusType Error );
#endif /* !__PRIVATE_SHUTDOWNOS__ && EE_AS_RPC__ */

#endif /* __MSRP__ */

/*******************************************************************************
 *                          Errors Handling API
 ******************************************************************************/

/* [OS439]: The Operating System module shall provide the OSEK error macros
    (OSError...()) to all configured error hooks AND there shall be two
    (like in OIL) global configuration parameters to switch these macros on
    or off. */
#if defined(__OO_HAS_ERRORHOOK__) && (!defined(__OO_ERRORHOOK_NOMACROS__))
#ifdef EE_AS_USER_SPINLOCKS__
__INLINE__ SpinlockIdType __ALWAYS_INLINE__
  OSError_GetSpinlock_SpinlockId( void )
{
  return EE_oo_get_errorhook_data()->param1.value_param;
}

__INLINE__ SpinlockIdType __ALWAYS_INLINE__
  OSError_ReleaseSpinlock_SpinlockId( void )
{
  return EE_oo_get_errorhook_data()->param1.value_param;
}

__INLINE__ SpinlockIdType __ALWAYS_INLINE__
  OSError_TryToGetSpinlock_SpinlockId( void )
{
  return EE_oo_get_errorhook_data()->param1.value_param;
}

__INLINE__ TryToGetSpinlockType * __ALWAYS_INLINE__
  OSError_TryToGetSpinlock_Success( void )
{
  return EE_oo_get_errorhook_data()->param2.try_to_get_spinlock_ref;
}
#endif /* EE_AS_USER_SPINLOCKS__ */
#endif /* __OO_HAS_ERRORHOOK__ && !__OO_ERRORHOOK_NOMACROS__ */

#ifdef EE_AS_RPC__
/*******************************************************************************
 *                   Synchronous Remote Procedure Calls
 ******************************************************************************/

/** @brief type tha hold params and retur value for a RPC */
typedef struct
{
  CoreIdType      serving_core;
  OSServiceIdType remote_procedure;
  EE_os_param     param1;
  EE_os_param     param2;
  EE_os_param     param3;
  StatusType      error;
} EE_TYPEASRPC;

typedef struct {
  CoreIdType      core_id;
  EE_os_param_id  param_id;
#ifdef  EE_SERVICE_PROTECTION__
  EE_UREG         core0_index;
#endif /*  EE_SERVICE_PROTECTION__ */
} EE_TYPEASREMOTEID;

typedef EE_TYPEASREMOTEID const * EE_TYPEASREMOTEIDCONSTREF;

/* The following are moved in interface because used by inline generated code
   for IOC */

/** @brief Map the core id with his corresponding spinlock */
extern EE_TYPESPIN const EE_as_core_spinlocks[];
/** @brief Flag that a core is serving a RPCs */
extern EE_BIT volatile EE_SHARED_IDATA EE_as_rpc_serving[EE_MAX_CPU];

/** @brief The following implement a synchronous RPC kernel primitive. */
/* This is put here because have to be seen in eecfg.c in case of
   __EE_MEMORY_PROTECTION__ */
extern StatusType EE_as_rpc( OSServiceIdType ServiceId, EE_os_param param1,
  EE_os_param param2, EE_os_param param3 );
#endif /* EE_AS_RPC__ */

#endif /* !__AS_SC4__ */

#endif /* INCLUDE_EE_KERNEL_AS_KERNEL__ */
