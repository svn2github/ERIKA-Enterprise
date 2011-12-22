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

/** 
	@file ee_cpu.h
	@brief CPU-dependent part of HAL. Derived from pkg/cpu/pic30/inc/ee_cpu.h
	@author Gianluca Franchino
	@author Giuseppe Serano
	@date 2011
*/ 

#ifndef __INCLUDE_CORTEX_MX_EE_CPU_H__
#define __INCLUDE_CORTEX_MX_EE_CPU_H__

#include "eecfg.h"

#ifdef __IAR__
#include "cpu/common/inc/ee_compiler_iar.h"
#else
#ifdef __CCS__
#include "cpu/common/inc/ee_compiler_ccs.h"
#else
#error Unsupported compiler
#endif
#endif

/* Initial stack offset (in words) */
#ifndef CORTEX_MX_INIT_TOS_OFFSET
#define CORTEX_MX_INIT_TOS_OFFSET 9
#endif

/*************************************************************************
 HAL Types and structures
 *************************************************************************/

/* Primitive data types */
#include "cpu/common/inc/ee_types.h"

typedef EE_UINT32 EE_UREG;
typedef EE_INT32  EE_SREG;
typedef EE_UINT32 EE_FREG;
#define EE_UREG_SIZE 4

/* Thread IDs */
typedef EE_INT32 EE_TID;
/* Used by the common layer to decide whether to start a new thread */
#define TID_IS_STACKED_MARK 0x80000000

/* EE_TYPEIRQ is currently unused */

/* XXX: define EE_TIME? */

/* Use the "standard" implementation */
#include "cpu/common/inc/ee_hal_structs.h"

/******************************************************************************
 Application dependent data types
 ******************************************************************************/

#ifdef	__HAS_TYPES_H__
#include	"types.h"
#endif

/******************************************************************************
 HAL Variables
 ******************************************************************************/

#ifdef __MULTI__

/* Top-of-stack of each private stack */
extern struct EE_TOS EE_cortex_mx_system_tos[];
//#define	EE_std_system_tos EE_cortex_mx_system_tos

/* Index of the current stack */
extern EE_UREG EE_cortex_mx_active_tos;
#define	EE_hal_active_tos EE_cortex_mx_active_tos

/*extern	EE_UREG EE_pic30_thread_tos[];
#define	EE_std_thread_tos EE_pic30_thread_tos */
#endif /* __MULTI__ */

/*********************************************************************
 Cortex M0 interrupt disabling/enabling
 *********************************************************************/

/* Used to check the value returned by EE_cortex_mx_disableIRQ */
#define EE_cortex_mx_are_IRQs_enabled(ie) ((ie) ^ 1)

/**
 * Enable interrupts
 */
__INLINE__ void __ALWAYS_INLINE__ EE_cortex_mx_enableIRQ(void)
{
#ifdef __IAR__
	__ASM ("cpsie i");
#else
#ifndef __CCS__
	 __ASM volatile("cpsie i");
#else
	__ASM ("    cpsie    i\n");
#endif
#endif
}

/**
 * Disable interrupts
 */
__INLINE__ void __ALWAYS_INLINE__ EE_cortex_mx_disableIRQ(void)
{
#ifdef __IAR__
	__ASM ("cpsid i");
#else
#ifndef __CCS__
	 __ASM volatile("cpsid i");
#else
	__ASM ("    cpsid    i\n");
#endif
#endif
}

/**
 * Resume interrupts
 */
__INLINE__ void __ALWAYS_INLINE__ EE_cortex_mx_resumeIRQ(EE_FREG f)
{
#ifdef __IAR__
	__set_PRIMASK(f);
#else
#ifndef __CCS__
	 __ASM volatile("msr primask, %0" :: "r" (f));
#else
	__ASM ("    msr    primask, r0\n");
#endif
#endif
}

/**
 * Suspend interrupts
 */
__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_cortex_mx_suspendIRQ(void)
{
#ifndef __CCS__
	EE_FREG istat;
#endif
#ifdef __IAR__
	 istat = __get_PRIMASK();
	__ASM ("cpsid i");
#else
#ifndef __CCS__
	__ASM volatile ("mrs %0, primask" : "=r" (istat) );
	__ASM volatile ("cpsid i");
#else
	__ASM ("    mrs     r0, primask\n"
	       "    cpsid   i\n"
	       "    bx      lr\n");
#endif
#endif
#ifdef __CCS__
	return 0;
#else
	return istat;
#endif
}

/**
 * Return true (not 0) if IRQs are enabled, 0 (false) if IRQ are disabled.
 */
__INLINE__ EE_UINT32 __ALWAYS_INLINE__ EE_cortex_mx_get_IRQ_enabled(void)
{
#ifndef __CCS__
	 EE_UREG ie;
#endif
#ifdef __IAR__
	ie = __get_PRIMASK();
#else
#ifndef __CCS__
	__ASM volatile ("MRS %0, primask" : "=r" (ie) );
#else
	__ASM ("    MRS     r0, PRIMASK\n"
	       "    EOR     r0, #1n"
	       "    bx      lr\n");
#endif
#endif
#ifdef __CCS__
	return 0;
#else
	return EE_cortex_mx_are_IRQs_enabled(ie);
#endif
}

/*************************************************************************
 Functions exported by the HAL to the kernel
 *************************************************************************/

/* 
 * Interrupt Handling
 */

/** Hal Enable Interrupts */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_enableIRQ(void)
{
    EE_cortex_mx_enableIRQ();
}

/** Hal Disable Interrupts */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_disableIRQ(void)
{
    EE_cortex_mx_disableIRQ();
}

/** Hal Resume Interrupts */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_resumeIRQ(EE_FREG f)
{
    EE_cortex_mx_resumeIRQ(f);
}

/** Hal Suspend Interrupts */
__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_hal_suspendIRQ(void)
{
    return EE_cortex_mx_suspendIRQ();
}

/**************************************************************************
 System Initialization
***************************************************************************/

void EE_system_init(void);

#endif /* __INCLUDE_CORTEX_MX_EE_CPU_H__ */