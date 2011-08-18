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
 * CPU-dependent part of HAL
 * Derived from pkg/cpu/mico32/inc/ee_cpu.h
 * Author: 2010 Fabio Checconi
 *         2011 Bernardo  Dal Seno
 */


#ifndef __INCLUDE_E200ZX_EE_CPU_H__
#define __INCLUDE_E200ZX_EE_CPU_H__

#include "eecfg.h"
#ifdef __GNUC__
#include "cpu/common/inc/ee_compiler_gcc.h"
#elif defined (__DCC__)
#include "cpu/common/inc/ee_compiler_diab.h"
#elif defined (__CWCC__)
#include "cpu/common/inc/ee_compiler_codewarrior.h"
#else
#error Unsupported compiler
#endif


/* This instruction should cause a trap when executed.  Handy to mark invalid
 * functions */
/* XXX */
#define INVALID_ASM_INSTR  asm volatile ( ".word 0xcccc" )


/*************************************************************************
 HAL Types and structures
 *************************************************************************/

/* Primitive data types */
#include "cpu/common/inc/ee_types.h"

#include "ee_cpu_asm.h"

typedef EE_UINT32 EE_UREG;
typedef EE_INT32  EE_SREG;
typedef EE_UINT32 EE_FREG;

/* Thread IDs */
typedef EE_INT32 EE_TID;

/* Flag (OR'ed to an EE_TID) to mark a task as stacked. */
#define TID_IS_STACKED_MARK	0x80000000

/* EE_TYPEIRQ is defined inside the MCU */

/* XXX: define EE_TIME? */

/* Use the "standard" implementation */
#include "cpu/common/inc/ee_hal_structs.h"

/* Type pointing to an ISR */
typedef void (*EE_e200z7_ISR_handler)(void);

/* Alignment and section for program stacks */
#define EE_STACK_SEC ".stack"
#define EE_STACK_ATTRIB		EE_COMPILER_ALIGN(EE_STACK_ALIGN)	\
	EE_COMPILER_SECTION(EE_STACK_SEC)

/* Word used to build user stacks */
typedef EE_UINT32 EE_STACK_T;
/* Stack length in words */
#define EE_STACK_WLEN(bl) (((bl) + EE_STACK_ALIGN - 1) / EE_STACK_ALIGN * \
	(EE_STACK_ALIGN / sizeof(EE_STACK_T)))
/* Initial pointer (word offset) in user stacks */
#define EE_STACK_INITP(bl) (EE_STACK_WLEN(bl) - \
	EE_STACK_ALIGN / sizeof(EE_STACK_T))

extern EE_STACK_T EE_STACK_ATTRIB EE_e200zx_sys_stack[EE_STACK_WLEN(EE_SYS_STACK_SIZE)];

#ifdef __MULTI__

/* Top of each private stack. */
extern struct EE_TOS EE_e200z7_system_tos[];

/* Index of the current stack. */
extern EE_UREG EE_e200z7_active_tos;

#endif /* __MULTI__ */


/*********************************************************************
 Multicore and multiprocessor support
 *********************************************************************/

#ifdef __MSRP__

/* the MSB in a MUTEX type indicates if a resource is global (1) or
   local (0) to a processor */
#define EE_GLOBAL_MUTEX 0x80000000U

/* Type for spinlocks: an ID */
typedef EE_UINT32 EE_TYPESPIN;

/* For compatibilty with old code */
#define EE_SHARED_DATA(x) x

/* Shared data use separate sections; potentially, three different sections
 * could be used for constant, unitialized, and initialized data */
#define EE_SHARED_CDATA  EE_COMPILER_SECTION(".mcglobalc")
#define EE_SHARED_UDATA  EE_COMPILER_SECTION(".mcglobald")
#define EE_SHARED_IDATA  EE_COMPILER_SECTION(".mcglobald")

#if 0  /* Shared code, resources and mutex not working yet */
#define EE_SHARED_CODE(x) EE_SHARED_CODE_##x
#define EE_SHARED_RES(name,var) EE_SHARED_RES_##name(var)
#endif

#endif /* __MSRP__ */


/*********************************************************************
 E200Z7 interrupt disabling/enabling
 *********************************************************************/

#define EE_E200ZX_MAX_CPU_EXCP 16

#define MSR_EE	(1U << 15)

__INLINE__ EE_FREG EE_e200z7_are_IRQs_enabled(EE_FREG ie)
{
	return ie & MSR_EE;
}

__INLINE__ void __ALWAYS_INLINE__ EE_e200z7_enableIRQ(void)
{
	asm volatile ("wrteei 1\n");
}

#ifdef __DCC__
EE_FREG EE_e200z7_disableIRQ(void); /* Prototype required by Misra */

__asm EE_FREG EE_e200z7_disableIRQ(void)
{
! "r3"
	mfmsr	r3
	wrteei	0
}
#else
__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_e200z7_disableIRQ(void)
{
	EE_FREG msr;

	asm volatile ("mfmsr %0		\n"
		      "wrteei 0		\n"
			: "=r"(msr));
	return msr;
}
#endif


/*************************************************************************
 Functions
 *************************************************************************/

/*
 * Interrupt Handling
 */

/* Disable/Enable Interrupts */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_enableIRQ(void)
{
	EE_e200z7_enableIRQ();
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_disableIRQ(void)
{
	EE_e200z7_disableIRQ();
}

void EE_e200z7_setup_decrementer(unsigned long value);
void EE_e200z7_setup_decrementer_oneshot(unsigned long value);
void EE_e200z7_stop_decrementer(void);

/* Assembly functions */
void __start(void);
void intc_setup(void);
void cpu_setup(void);
void sram_setup(void);
void mmu_setup(void);
/* Symbols provided by the linker script */
extern int _load_ram;
extern int _sbss;
extern int _sdata;
extern int _ebss;
extern int _SDA_BASE_;
extern int _SDA2_BASE_;
extern int _sstack, _estack;

#endif /* __INCLUDE_E200ZX_EE_CPU_H__ */
