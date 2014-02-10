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

 /** @file      ee_as_internal.h
  *  @brief     Internals for Autosar layer
  *  @author    Errico Guidieri
  *  @date      2012
  */

#ifndef INCLUDE_EE_KERNEL_AS_INTERNAL__
#define INCLUDE_EE_KERNEL_AS_INTERNAL__

#ifndef __AS_SC4__

#include "kernel/as/inc/ee_as_kernel.h"

#ifdef EE_AS_USER_SPINLOCKS__
/*******************************************************************************
 *          Spinlock internal Data Structures an Internal Clean-Up
 ******************************************************************************/

/** @brief Hold which core is locking the spinlock */
extern CoreIdType     volatile  EE_as_spinlocks_locker_core[];
/** @brief Spinlock Stack head */
extern SpinlockIdType volatile  EE_as_spinlocks_last[];
/** @brief Spinlock Stack */
extern SpinlockIdType volatile  EE_as_spinlocks_stack[];
/** @brief Hold which task is locking the spinlock */
extern TaskType  EE_as_spinlocks_locker_task_or_isr2[];

/* Internal Clean-up function */
SpinlockIdType EE_as_release_all_spinlocks( EE_TID tid );

#else  /* EE_AS_USER_SPINLOCKS__ */
#define EE_as_release_all_spinlocks(tid) ((void)0U)
#endif /* EE_AS_USER_SPINLOCKS__ */

#ifdef EE_AS_RPC__
/*******************************************************************************
 *                   Synchronous Remote Procedure Calls
 ******************************************************************************/

/** @brief used to map global ids on local ids */
extern EE_TYPEASREMOTEIDCONSTREF const EE_as_rpc_services_table[];

/** @brief Mask used in shutdown all cores procedure for synchronization */
extern EE_UREG volatile EE_SHARED_IDATA EE_as_shutdown_mask;

/** @brief Data structures to pass RPC parameters */
extern EE_TYPEASRPC volatile EE_as_rpc_RAM[];

/** @brief Flag used to signal that ShutdownAllCores have been called */
extern EE_BIT volatile EE_as_shutdown_all_cores_flag;

/** @brief Used to pass ShutdownAllCores error parameter to other cores */
extern StatusType volatile EE_as_shutdown_all_cores_error;

/** @brief Macro used to check if an id is a remote id */
#define EE_AS_ID_REMOTE(id)         ((((EE_UINT32)(id)) & \
    (EE_UINT32)EE_REMOTE_TID) != 0U)
/** @brief Macro used to unmark a remote id */
#define EE_AS_UNMARK_REMOTE_ID(id)  (((EE_UINT32)(id)) & (~EE_REMOTE_TID))

/** @brief define that identify an invalid ServiceId */
#define INVALID_SERVICE_ID      ((OSServiceIdType)-1)
#define INVALID_ERROR           ((StatusType)-1)

/** @brief RPC Handler to be called inside IIRQ handler */
extern void  EE_as_rpc_handler( void );

__INLINE__ StatusType __ALWAYS_INLINE__ EE_as_rpc_from_us( OSServiceIdType
  ServiceId, EE_os_param param1, EE_os_param param2, EE_os_param param3 )
{
  StatusType ev;
  register EE_FREG const flag = EE_hal_begin_nested_primitive();
  ev = EE_as_rpc(ServiceId, param1, param2, param3);
  EE_hal_end_nested_primitive(flag);
  return ev;
}

#endif /* EE_AS_RPC__ */

#ifdef EE_AS_IOC__
/*******************************************************************************
 *                  Inter OSApplication Communication (IOC)
 ******************************************************************************/

/* If MemMap.h support is enabled (i.e. because memory protection): use it */
#ifdef EE_SUPPORT_MEMMAP_H
/* The following variables belong to ERIKA API section: ee_kernel_bss */
#define OS_START_SEC_VAR_NOINIT
#include "MemMap.h"
#endif /* EE_SUPPORT_MEMMAP_H */

/** @brief Flag used to signal a IOC request */
extern EE_BIT EE_as_rpc_IOC[];

/* If MemMap.h support is enabled (i.e. because memory protection): use it */
#ifdef EE_SUPPORT_MEMMAP_H
#define OS_STOP_SEC_VAR_NOINIT
#include "MemMap.h"
#endif /* EE_SUPPORT_MEMMAP_H */
#endif /* EE_AS_IOC__ */

#endif /* !__AS_SC4__ */

#endif /* INCLUDE_EE_KERNEL_AS_INTERNAL__ */
