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
#define EE_STACK_ATTRIB_NAME(n)	EE_COMPILER_ALIGN(EE_STACK_ALIGN)	\
	EE_COMPILER_SECTION(EE_STACK_SEC "_" EE_PREPROC_STRING(n))

/* Word used to build user stacks */
typedef EE_UINT32 EE_STACK_T;
/* Stack length in words */
#define EE_STACK_WLEN(bl) (((((EE_UREG)(bl) +				\
			(EE_UREG)EE_STACK_ALIGN) - 1U)			\
		/ (EE_UREG)EE_STACK_ALIGN)				\
	* ((EE_UREG)EE_STACK_ALIGN / sizeof(EE_STACK_T)))
/* Initial pointer (word offset) in user stacks */
#define EE_STACK_INITP(bl) (EE_STACK_WLEN(bl) -	\
	((EE_UREG)EE_STACK_ALIGN / sizeof(EE_STACK_T)))

extern EE_STACK_T EE_STACK_ATTRIB EE_e200zx_sys_stack[EE_STACK_WLEN(EE_SYS_STACK_SIZE)];

/* ORTI types */
#ifdef __OO_ORTI_RUNNINGISR2__
typedef EE_e200z7_ISR_handler EE_ORTI_runningisr2_type;
#define EE_ORTI_build_isr2id(l,f) (f)
#else /* __OO_ORTI_RUNNINGISR2__ */
/* In this case EE_ORTI_runningisr2_type is defined inside the OO kernel */
#define EE_ORTI_build_isr2id(l,f) ((EE_ORTI_runningisr2_type)0)
#endif /* else __OO_ORTI_RUNNINGISR2__ */

#ifdef __MULTI__

/* Top of each private stack. */
extern struct EE_TOS EE_e200z7_system_tos[];

/* Index of the current stack. */
extern EE_UREG EE_e200z7_active_tos;

#endif /* __MULTI__ */


/*************************************************************************
 System startup
 *************************************************************************/

#define __OO_CPU_HAS_STARTOS_ROUTINE__

#if defined(__MSRP__) || (defined(__EE_MEMORY_PROTECTION__) \
	&& (defined(__OO_BCC1__) || defined(__OO_BCC2__)    \
		|| defined(__OO_ECC1__) || defined(__OO_ECC2__)))
/* On multi-core this is used also as a synchronization point */
int EE_cpu_startos(void);

#else /* if __MSRP__ || __EE_MEMORY_PROTECTION__ ... */
/* Nothing to do */
__INLINE__ int __ALWAYS_INLINE__ EE_cpu_startos(void)
{
	return 0;
}

#endif /* else if __MSRP__ || __EE_MEMORY_PROTECTION__ ... */


/*********************************************************************
 Multicore and multiprocessor support
 *********************************************************************/

#ifdef __MSRP__

/* the MSB in a MUTEX type indicates if a resource is global (1) or
   local (0) to a processor */
#define EE_GLOBAL_MUTEX ((ResourceType)0x80000000U)

/* Type for spinlocks: an ID */
typedef EE_UINT32 EE_TYPESPIN;

/* For compatibilty with old code */
#define EE_SHARED_DATA(x) x

/* Shared data use separate sections; potentially, three different sections
 * could be used for constant, unitialized, and initialized data */
#define EE_SHARED_CDATA  EE_COMPILER_SECTION(".mcglobalc") EE_COMPILER_KEEP
#define EE_SHARED_UDATA  EE_COMPILER_SECTION(".mcglobald") EE_COMPILER_KEEP
#define EE_SHARED_IDATA  EE_COMPILER_SECTION(".mcglobald") EE_COMPILER_KEEP

#if 0  /* Shared code, resources and mutex not working yet */
#define EE_SHARED_CODE(x) EE_SHARED_CODE_##x
#define EE_SHARED_RES(name,var) EE_SHARED_RES_##name(var)
#endif

#endif /* __MSRP__ */


/*********************************************************************
 E200Z7 interrupt disabling/enabling
 *********************************************************************/

#define MSR_EE	((EE_FREG)1U << 15)

__INLINE__ EE_FREG EE_e200z7_are_IRQs_enabled(EE_FREG ie)
{
	return ie & MSR_EE;
}

__INLINE__ void __ALWAYS_INLINE__ EE_e200z7_enableIRQ(void)
{
	asm volatile ("wrteei 1\n");
}

#ifdef __DCC__
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

#ifdef __EE_MEMORY_PROTECTION__

#define EE_HAL_IRQSTATE_INVALID ((EE_FREG)0U)
#define EE_hal_set_irq_valid_flag(f) ((f) | (MSR_EE << 1))
#define EE_hal_clear_irq_flag(f) ((f) & ~MSR_EE)
#define EE_hal_copy_irq_flag(from, to) (((to) & ~MSR_EE) | ((from) & MSR_EE))

#endif /* __EE_MEMORY_PROTECTION__ */

/*************************************************************************
 Access to CPU registers
 *************************************************************************/

#ifdef __DCC__
__asm EE_UREG EE_e200zx_get_tcr(void)
{
! "r3"
	mfspr	r3, tcr
}

__asm void EE_e200zx_set_tcr(EE_UREG val)
{
% reg val
!
	mtspr	tcr, val
}

__asm EE_UREG EE_e200zx_get_tsr(void)
{
! "r3"
	mfspr	r3, tsr
}

__asm void EE_e200zx_set_tsr(EE_UREG val)
{
% reg val
!
	mtspr	tsr, val
}

__asm void EE_e200zx_set_dec(EE_UREG val)
{
% reg val
!
	mtspr	dec, val
}

__asm void EE_e200zx_set_decar(EE_UREG val)
{
% reg val
!
	mtspr	decar, val
}

__asm EE_UINT32 EE_e200zx_get_tbl(void)
{
! "r3"
	mfspr	r3, tbl
}

#else /* if __DCC__ */
__INLINE__ EE_UREG EE_e200zx_get_tcr(void)
{
	EE_UREG tcr;
	asm volatile ("mfspr %0, tcr" : "=r"(tcr));
	return tcr;
}

__INLINE__ void EE_e200zx_set_tcr(EE_UREG val)
{
	asm volatile ("mtspr tcr, %0" :: "r"(val) );
}

__INLINE__ EE_UREG EE_e200zx_get_tsr(void)
{
	EE_UREG tsr;
	asm volatile ("mfspr %0, tsr" : "=r"(tsr));
	return tsr;
}

__INLINE__ void EE_e200zx_set_tsr(EE_UREG val)
{
	asm volatile ("mtspr tsr, %0" :: "r"(val) );
}

__INLINE__ void EE_e200zx_set_dec(EE_UREG val)
{
	asm volatile ("mtspr dec, %0" :: "r"(val) );
}

__INLINE__ void EE_e200zx_set_decar(EE_UREG val)
{
	asm volatile ("mtspr decar, %0" :: "r"(val) );
}

__INLINE__ EE_UINT32 EE_e200zx_get_tbl(void)
{
	EE_UINT32 tbl;
	asm volatile ("mfspr %0, tbl" : "=r"(tbl));
	return tbl;
}
#endif /* else __DCC__ */


/*************************************************************************
 Functions
 *************************************************************************/

__INLINE__ void __ALWAYS_INLINE__ EE_e200zx_isync(void)
{
	asm volatile ("isync");
}


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
	(void)EE_e200z7_disableIRQ();
}

#ifndef __PPCE200Z0__
/* e200z0 has no internal timer, so the functions below are not defined */

/* Enable the fixed-interval interrupt.  bitpos (0-63) is the bit of the time
 * base register that triggers the interrupt; 0 is the most significant bit of
 * the register.  See the Book E manual for details on this interrupt.  */
void EE_e200zx_setup_fixed_intv(EE_UREG bitpos);
/* Disable the fixed-interval interrupt */
void EE_e200zx_stop_fixed_intv(void);

/* Configure the decrementer to raise an interrupt every `delay' cycles */
void EE_e200z7_setup_decrementer(EE_UINT32 value);
/* Configure the decrementer to raise an interrupt once after `delay' cycles */
void EE_e200z7_setup_decrementer_oneshot(EE_UINT32 value);
/* Stop the decrementer from generating interrupts */
void EE_e200z7_stop_decrementer(void);

/* Wait a number of ticks as counted by the CPU time base */
void EE_e200zx_delay(EE_UINT32 ticks);

#endif /* ! __PPCE200Z0__ */


/*************************************************************************
 MMU
 *************************************************************************/

/* TLB entry specification.  Values to be loaded in the MAS1, MAS2, and MAS3
 * registers.  You can use the constants below to build such values.  Please
 * refer to the Book E or Freescale manuals for details.  */
typedef struct {
	EE_UREG mas1;
	EE_UREG mas2;
	EE_UREG mas3;
} EE_MMU_ENTRY_T;

/* Masks used for MAS0 */
#define EE_E200ZX_MMU_TLBSEL1	((EE_UREG)0x10000000U)	/* Use TLB1 */

/* Masks used for MAS1 */
#define EE_E200ZX_MMU_VALID	0x80000000U	/* TLB entry is valid */
#define EE_E200ZX_MMU_IPROT	0x40000000U	/* TLB entry is protected */

/* Page sizes (MAS1) */
#define EE_E200ZX_MMU_SIZE_256M	0x00000900U
#define EE_E200ZX_MMU_SIZE_64M	0x00000800U
#define EE_E200ZX_MMU_SIZE_16M	0x00000700U
#define EE_E200ZX_MMU_SIZE_4M	0x00000600U
#define EE_E200ZX_MMU_SIZE_1M	0x00000500U
#define EE_E200ZX_MMU_SIZE_256K	0x00000400U
#define EE_E200ZX_MMU_SIZE_64K	0x00000300U
#define EE_E200ZX_MMU_SIZE_16K	0x00000200U
#define EE_E200ZX_MMU_SIZE_4K	0x00000100U

/* Masks used for MAS2 */
#define EE_E200ZX_MMU_FLAG_GUARD 0x00000002U	/* Guarded access */
#define EE_E200ZX_MMU_FLAG_CE	0x00000000U	/* Cache enabled */
#define EE_E200ZX_MMU_FLAG_CD	0x00000008U	/* Cache disabled */
#define EE_E200ZX_MMU_FLAG_FLE	0x00000000U	/* Fixed-length encoding */
#define EE_E200ZX_MMU_FLAG_VLE	0x00000020U	/* Variable-length encoding */

/* Masks used for MAS3 */
#define EE_E200ZX_MMU_PROT_UR	0x02U		/* User read access */
#define EE_E200ZX_MMU_PROT_UW	0x08U		/* User write access */
#define EE_E200ZX_MMU_PROT_UX	0x20U		/* User execute access */
#define EE_E200ZX_MMU_PROT_SR	0x01U		/* Supervisor read access */
#define EE_E200ZX_MMU_PROT_SW	0x04U		/* Supervisor write access */
#define EE_E200ZX_MMU_PROT_SX	0x10U		/* Supervisor execute access */
#define EE_E200ZX_MMU_PROT_SRWX	0x15U		/* All supervisor access */
#define EE_E200ZX_MMU_PROT_URWX	0x2aU		/* All user access */
/* Permission for code: read + execute in both modes */
#define EE_E200ZX_MMU_PROT_CODE	(EE_E200ZX_MMU_PROT_SX | EE_E200ZX_MMU_PROT_UX \
	| EE_E200ZX_MMU_PROT_SR | EE_E200ZX_MMU_PROT_UR)

/* MMU initialization.  Load `count' entries specified in `entries' in the first
 * `count' entries of the TLB.  This is a C function, so RAM and stack must be
 * initialized already before calling this function. */
void EE_e200zx_mmu_setup(const EE_MMU_ENTRY_T *entries, EE_UREG count);

#ifdef __EE_CRT0_INIT_MMU__
/* Entries to be loaded by the crt0 */
extern const EE_MMU_ENTRY_T EE_e200zx_mmu_entries[];
/* Number of entries to be loaded by the crt0 */
extern const unsigned EE_e200zx_mmu_num_entries;
#endif /* __EE_CRT0_INIT_MMU__ */


/*************************************************************************
 Memory Protection
 *************************************************************************/

#if defined(__EE_MEMORY_PROTECTION__)
typedef EE_MMU_ENTRY_T EE_MEMPROT_ENTRY_T;

#define EE_MEMPROT_USR_DATA	(EE_E200ZX_MMU_PROT_SW | EE_E200ZX_MMU_PROT_SR \
	| EE_E200ZX_MMU_PROT_UW | EE_E200ZX_MMU_PROT_UR)
#define EE_MEMPROT_SYS_DATA	(EE_E200ZX_MMU_PROT_SW | EE_E200ZX_MMU_PROT_SR)
#define EE_MEMPROT_TRUST_DATA	(EE_E200ZX_MMU_PROT_SW | EE_E200ZX_MMU_PROT_SR)
#define EE_MEMPROT_ROM_CODE	(EE_E200ZX_MMU_PROT_SX | EE_E200ZX_MMU_PROT_UX \
	| EE_E200ZX_MMU_PROT_SR | EE_E200ZX_MMU_PROT_UR)
#define EE_MEMPROT_RAM_CODE	(EE_E200ZX_MMU_PROT_SX | EE_E200ZX_MMU_PROT_UX \
	| EE_E200ZX_MMU_PROT_SR | EE_E200ZX_MMU_PROT_UR | EE_E200ZX_MMU_PROT_SW)
#define EE_MEMPROT_HW_REG	(EE_E200ZX_MMU_PROT_SW | EE_E200ZX_MMU_PROT_SR \
	| ((EE_E200ZX_MMU_FLAG_CD | EE_E200ZX_MMU_FLAG_GUARD) << 16))

#ifdef __VLE__
#define EE_MEMPROT_USE_VLE EE_E200ZX_MMU_FLAG_VLE
#else
#define EE_MEMPROT_USE_VLE 0U
#endif

#define EE_MEMPROT_USER_ENTRY(appid, base, size, log2size, type)	\
	{ 0xc0000000U | ((EE_UREG)(appid) << 16)			\
		  | ((((EE_UREG)(log2size) - 10U) / 2U) << 8),		\
		(base) | EE_MEMPROT_USE_VLE				\
		  | ((EE_UREG)(((type) & 0xffff0000U) >> 16) & 0xffffU), \
		(base) | ((EE_UREG)(type) & 0xffffU) }

#define EE_MEMPROT_SYSTEM_ENTRY	\
	{ EE_E200ZX_MMU_VALID | EE_E200ZX_MMU_IPROT | EE_E200ZX_MMU_SIZE_1M,	\
		0xfff00000U | EE_E200ZX_MMU_FLAG_CD | EE_E200ZX_MMU_FLAG_GUARD, \
		0xfff00000U | EE_E200ZX_MMU_PROT_SRWX },		\
	{ EE_E200ZX_MMU_VALID | EE_E200ZX_MMU_IPROT | EE_E200ZX_MMU_SIZE_16M,	\
		/*0x00000000U |*/ EE_E200ZX_MMU_FLAG_CE | EE_MEMPROT_USE_VLE,	\
		/*0x00000000U |*/ EE_E200ZX_MMU_PROT_SR | EE_E200ZX_MMU_PROT_SX \
		| EE_E200ZX_MMU_PROT_UR | EE_E200ZX_MMU_PROT_UX },	\
	{ EE_E200ZX_MMU_VALID | EE_E200ZX_MMU_IPROT | EE_E200ZX_MMU_SIZE_1M,	\
		0xc3f00000U | EE_E200ZX_MMU_FLAG_CD | EE_E200ZX_MMU_FLAG_GUARD, \
		0xc3f00000U | EE_E200ZX_MMU_PROT_SR | EE_E200ZX_MMU_PROT_SW },	\
	{ EE_E200ZX_MMU_VALID | EE_E200ZX_MMU_IPROT | EE_E200ZX_MMU_SIZE_64K,	\
		0x40000000U | EE_E200ZX_MMU_FLAG_CE,			\
		0x40000000U | EE_E200ZX_MMU_PROT_SR | EE_E200ZX_MMU_PROT_SW \
		| EE_E200ZX_MMU_PROT_UR }

#define EE_HAL_MEMPROT_ENTRIES(numapps)	((numapps) + 4U)

extern const EE_MEMPROT_ENTRY_T EE_hal_memprot_entries[EE_HAL_MEMPROT_ENTRIES(EE_MAX_APP)];

/* SR value for trusted and unstrusted code */
#define EE_MEMPROT_TRUST_MODE 0x8000U
#define EE_MEMPROT_USR_MODE 0xc000U

/* Information about sections of each application */
typedef struct {
	/* Inizialized data section, Flash address */
	const void *data_flash;
#if defined(RTDRUID_CONFIGURATOR_NUMBER) \
 && RTDRUID_CONFIGURATOR_NUMBER >= RTDRUID_CONFNUM_STACK_IN_APP_SEC_INFO
	/* Stack section.  Its end coincides with data start */
	void *stack_start;
#endif /* RTDRUID_CONFNUM_STACK_IN_APP_SEC_INFO */
	/* Inizialized data section, RAM address.  Its end coincides with BSS
	 * start. */
	void *data_ram;
	/* BSS section start */
	void *bss_start;
	/* BSS section end (address of the byte after the section) */
	void *bss_end;
} EE_APP_SEC_INFO_T;

/* Initialize the memory sections (initialized data and BSS) of an application */
void EE_hal_app_init(const EE_APP_SEC_INFO_T *app_info);

#endif /* __EE_MEMORY_PROTECTION__ */

/*
 * Markers for application private areas
 */
/* Application private constant data (read-only) */
#define EE_APPLICATION_CDATA(app)  EE_COMPILER_SECTION(".rodata")
/* Application private uninitialized data (BSS) */
#define EE_APPLICATION_UDATA(app)  \
	EE_COMPILER_SECTION(".bss_" EE_PREPROC_STRING(app))
/* Application private initialized data */
#define EE_APPLICATION_IDATA(app)  \
	EE_COMPILER_SECTION(".data_" EE_PREPROC_STRING(app))

#ifdef __DCC__
__asm EE_UINT8 EE_as_raw_call_trusted_func(EE_UINT32 FunctionIndex,
	void *FunctionParams)
{
% reg FunctionIndex, FunctionParams
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	mr	r3, FunctionParams
	mr	r0, FunctionIndex
	sc
}
#else
__INLINE__ EE_UINT8 EE_as_raw_call_trusted_func(EE_UINT32 FunctionIndex,
	void *FunctionParams)
{
	asm volatile ("mr r3, %0" :: "r"(FunctionParams) );
	asm volatile ("mr r0, %0" :: "r"(FunctionIndex) );
	asm volatile ("sc");
}
#endif

/*************************************************************************
 CPU-dependent ORT support (mainly OTM)
 *************************************************************************/

/* Probably, some parts of the OTM code below does not depend on the
 * architecture.  They should be moved somewhere into pkg/cpu/common if this
 * turns out to be the case. */

#define EE_ORTI_OTM_ID_RUNNINGISR2 1
#define EE_ORTI_OTM_ID_SERVICETRACE 2

#ifdef __OO_ORTI_USE_OTM__
void EE_e200zx_send_otm8(EE_UINT8 id, EE_UINT8 data);
void EE_e200zx_send_otm32(EE_UINT8 id, EE_UINT32 data);

#else /* if __OO_ORTI_USE_OTM__ */
__INLINE__ void EE_e200zx_send_otm8(EE_UINT8 id, EE_UINT8 data)
{
	/* OTM disabled */
}

__INLINE__ void EE_e200zx_send_otm32(EE_UINT8 id, EE_UINT32 data)
{
	/* OTM disabled */
}
#endif /* else __OO_ORTI_USE_OTM__ */

#ifdef __OO_ORTI_RUNNINGISR2__
__INLINE__ void EE_ORTI_send_otm_runningisr2(EE_ORTI_runningisr2_type isr2)
{
	EE_e200zx_send_otm32(EE_ORTI_OTM_ID_RUNNINGISR2, (EE_UINT32)isr2);
}
#endif /* __OO_ORTI_RUNNINGISR2__ */

#ifdef __OO_ORTI_SERVICETRACE__
__INLINE__ void EE_ORTI_send_otm_servicetrace(EE_UINT8 srv)
{
	EE_e200zx_send_otm8(EE_ORTI_OTM_ID_SERVICETRACE, srv);
}

#if defined(__EE_MEMORY_PROTECTION__)
#if defined(RTDRUID_CONFIGURATOR_NUMBER) \
 && RTDRUID_CONFIGURATOR_NUMBER >= RTDRUID_CONFNUM_ORTI_SERVICE_API
#if defined __DCC__
__asm void EE_ORTI_ext_set_service(EE_UINT8 srv)
{
% reg srv
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	mr	r3, srv
	li	r0, EE_ID_ORTI_ext_set_service
	sc
}
#endif /* __DCC__ */
#else /* RTDRUID_CONFNUM_ORTI_SERVICE_API */
__INLINE__ void EE_ORTI_ext_set_service(EE_UINT8 srv)
{
}
#endif /* else RTDRUID_CONFNUM_ORTI_SERVICE_API */
#endif /* __EE_MEMORY_PROTECTION__ */

#endif /* __OO_ORTI_SERVICETRACE__ */

#endif /* __INCLUDE_E200ZX_EE_CPU_H__ */
