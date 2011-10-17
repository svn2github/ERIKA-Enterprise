/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
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
 * Derived from the mico32 code.
 * Author: 2010 Fabio Checconi
 */

#ifndef __INCLUDE_E200ZX_IRQ_INTERNAL_H__
#define __INCLUDE_E200ZX_IRQ_INTERNAL_H__

#include "ee_internal.h"
#include "cpu/common/inc/ee_irqstub.h"

#ifdef __ALLOW_NESTED_IRQ__
#define EE_std_enableIRQ_nested()
#define EE_std_disableIRQ_nested()
#endif

/*
 * Call an ISR.  If the ISR is to be called on a new stack we need to
 * resort to the black magic of assembly programming, and here we're
 * left with just a declaration.  If the ISR doesn't need a new stack
 * we only need to enable the external interrupts and call it.
 *
 * The pseudocode for the full-fledged ISR call is the following:
 *
 * void EE_e200z7_call_ISR_new_stack(EE_e200z7_ISR_handler fun)
 * {
 *	if (EE_IRQ_nesting_level == 1)
 *		change_stacks();
 *	EE_std_enableIRQ_nested();	// Enable IRQs if nesting is allowed.
 *	fun();
 *	EE_std_disableIRQ_nested();	// Disable IRQs if nesting is allowed.
 *	if (EE_IRQ_nesting_level == 1)
 * 		change_stacks_back();
 */
#if defined(__IRQ_STACK_NEEDED__) && ! defined(__AS_SC4__)
extern struct EE_TOS EE_e200z7_IRQ_tos;

/* For SC4 the stack is changed within the prestub and the postub */
void EE_e200z7_call_ISR_new_stack(EE_SREG level, EE_e200z7_ISR_handler fun,
							EE_UREG nesting);
#else /* if __IRQ_STACK_NEEDED__ && ! _AS_SC4__ */
__INLINE__ void __ALWAYS_INLINE__ EE_e200z7_call_ISR_new_stack(EE_SREG level,
			EE_e200z7_ISR_handler fun, EE_UREG nesting)
{
	EE_std_enableIRQ_nested();
	if (fun != NULL) {
		fun();
	}
	EE_std_disableIRQ_nested();
}
#endif /* else if __IRQ_STACK_NEEDED__ && ! _AS_SC4__ */

/* IRQ handler */
void EE_e200z7_irq(EE_SREG level);

#if defined(__AS_SC4__)
/*
 * In SC4 ISR2 are somehow tricky: we need to execute them in trusted/
 * untrusted mode according to the OS application they belong to, and we
 * must be able to terminate them if necessary.  We use one ISR2 stack
 * per application and we maintain a stack of ISR2 descriptors to track
 * the active ISR2s.  A complete implementation would use two stacks per
 * application: one for trusted and one for untrusted mode.
 */
/*
 * Pseudocode:
 * void ISR2_N_handler(void)
 * {
 *	EE_as_Application_RAM_type *from, *to;
 *	EE_as_ISR_RAM_type *tos;
 *	ApplicationType toid = N, fromid;
 *	EE_ADDR sp = get_sp();
 *
 *	fromid = EE_e200zx_get_application();
 *	to = &EE_as_Application_RAM[ISR_N_appid];
 *
 *	tos = &EE_as_ISR_stack[EE_IRQ_nesting_level++];
 *	tos->ISR = N;
 *
 *	if (EE_IRQ_nesting_level == 1) {
 *		EE_e200zx_ISR_stksave.sp = sp;
 *		EE_e200zx_ISR_stksave.appl = fromid;
 *		load_sp(to->ISRTOS);
 *	} else if (fromid != ISR2_N_appid) {
 *		from = &EE_as_Application_RAM[fromid];
 *		from->ISRTOS = sp;
 *		load_sp(to->ISRTOS);
 *	}
 *
 *	tos->TerminationTOS = sp;
 *
 *	EE_std_enableIRQ_nested();
 *	load_appid(ISR2_N_appid);
 *	load_mode(ISR2_N_appmode);
 *	call_handler();
 *	TerminateISR2();
 * }
 */

#define DeclareIsr(f) void f(void)


__asm void EE_ISR2_prestub(int toid, int isrid)
{

% reg toid, isrid;
! "r6", "r7", "r8", "r9", "r10", "r11"

	.set noreorder
	addis	r6, 0, EE_as_Application_RAM@ha
	ori	r6, r6, EE_as_Application_RAM@l	# r6 <= EE_as_Application_RAM
	mr	r7, toid
	slwi	r7, r7, 4
	add	r8, r6, r7			# r8 <= to

	addis	r9, 0, EE_IRQ_nesting_level@ha
	ori	r9, r9, EE_IRQ_nesting_level@l
	lwz	r7, 0(r9)
	mr	r10, r7				# r10 <= EE_IRQ_nesting_level
	addi	r7, r7, 1
	stw	r7, 0(r9)

	addis	r11, 0, EE_as_ISR_stack@ha
	ori	r11, r11, EE_as_ISR_stack@l
	slwi	r7, r10, 3			# r7 <= r10 << 3
	add	r9, r11, r7			# r9 <= tos

	stw	isrid, 4(r9)			# tos->ISR_Terminated = 0 | ID

	mfpid0	r7				# r7 <= fromid

	cmpli	cr0, 0, r10, 0
	bne	1f

	addis	r11, 0, EE_e200zx_ISR_stksave@ha
	ori	r11, r11, EE_e200zx_ISR_stksave@l
	stw	sp, (r11)
	stw	r7, 4(r11)

	lwz	sp, (r8)			# sp <= to->ISRTOS
	b	2f
1:
	cmpl	cr0, r7, toid
	beq	2f

	slwi	r7, r7, 4
	stwx	sp, r6, r7			# from->ISRTOS <= sp

	lwz	sp, (r8)			# sp <= to->ISRTOS
2:
#if 0 /* Arbitrary TerminateIsr() not supported */
	stw	sp, (r9)			# tos->TerminationTOS <= sp
#endif
	mtpid0	toid				# switch app

	lwz	r0, 4(r8)			# r0 <= to->Mode
	mtmsr	r0				# switch appmode
	.set reorder
}

__asm void EE_ISR2_poststub(void)
{
! "r0"
	li	r0, EE_ID_TerminateISR2
	sc
}

#define ISR2(f)								\
static void EE_PREPROC_JOIN(ISR2_,f)(void);				\
void f(void)								\
{									\
	EE_ISR2_prestub(EE_PREPROC_JOIN(ISR2_APP_,f),			\
		EE_PREPROC_JOIN(ISR2_ID_,f));				\
	EE_PREPROC_JOIN(ISR2_,f)();					\
	EE_ISR2_poststub();						\
}									\
static void EE_PREPROC_JOIN(ISR2_,f)(void)
#endif /* __AS_SC4__ */


/*
 * ORTI ISR2 support
 */

typedef EE_e200z7_ISR_handler EE_ORTI_ISR2_magic_type;

#ifdef __OO_ORTI_ISR2__
extern volatile EE_ORTI_ISR2_magic_type EE_ORTI_ISR2_magic;

__INLINE__ EE_ORTI_ISR2_magic_type EE_ORTI_get_ISR2_magic(void)
{
	return EE_ORTI_ISR2_magic;
}

__INLINE__ void EE_ORTI_set_ISR2_magic(EE_ORTI_ISR2_magic_type isr2)
{
	EE_ORTI_ISR2_magic = isr2;
}

#else /* if __OO_ORTI_ISR2__ */

__INLINE__ EE_ORTI_ISR2_magic_type EE_ORTI_get_ISR2_magic(void)
{
	return NULL;
}

__INLINE__ void EE_ORTI_set_ISR2_magic(EE_ORTI_ISR2_magic_type isr2)
{
}

#endif /* else __OO_ORTI_ISR2__ */

#endif /* __INCLUDE_E200ZX_IRQ_INTERNAL_H__ */
