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
 * IRQ low-level code, based on the mico32 version.
 * Author: 2010 Fabio Checconi
 */

#include <cpu/e200z7/inc/ee_regs.h>

#ifdef __ALLOW_NESTED_IRQ__
jmp_if_nested_reg: .macro reg, label
	cmpi	cr0, reg, 1
	bne	label
	.endm

jmp_if_nested: .macro label
	addis	r5, 0, EE_IRQ_nesting_level@ha
	lwz	r0, EE_IRQ_nesting_level@l(r5)
	cmpi	cr0, r0, 1
	bne	label
	.endm

enable_irq_nested: .macro
	wrteei	1
	.endm

disable_irq_nested: .macro
	wrteei	0
	.endm
#else
jmp_if_nested_reg: .macro reg, label
	.endm

jmp_if_nested: .macro label
	.endm

enable_irq_nested: .macro
	.endm

disable_irq_nested: .macro
	.endm
#endif

        .section .bss

	.global	EE_e200z7_tmp_tos
	.type	EE_e200z7_tmp_tos, @object
	.balign	4
EE_e200z7_tmp_tos:
        .space  4
	.size	EE_e200z7_tmp_tos, .-EE_e200z7_tmp_tos

	.text

	.global EE_e200z7_call_ISR_new_stack

	.type EE_e200z7_call_ISR_new_stack, @function

EE_e200z7_call_ISR_new_stack:
	/*
	 * r3 == irq_level
	 * r4 == fun
	 * r5 == nesting_level
	 */

	stwu	sp, -16(sp)
	mfspr	r0, SPRG_LR
	stw	r0, 20(sp)

	/* if (nesting_level == 1) */
	jmp_if_nested_reg r5, skip_change

        /*	change_stacks(); */
	addis	r3, 0, EE_e200z7_tmp_tos@ha
	stw	sp, EE_e200z7_tmp_tos@l(r3)

	addis	r3, 0, EE_e200z7_IRQ_tos@ha
	lwz	sp, EE_e200z7_IRQ_tos@l(r3)

skip_change:
	/* EE_std_enableIRQ_nested(); */
	enable_irq_nested

	/* fun(); */
	mtspr	SPRG_LR, r4
	blrl

	/* EE_std_disableIRQ_nested(); */
	disable_irq_nested

	/* if (nesting_level == 1) */
	jmp_if_nested skip_change_back

	/*     change_stacks_back(); */
	addis	r3, 0, EE_e200z7_tmp_tos@ha
	lwz	sp, EE_e200z7_tmp_tos@l(r3)

skip_change_back:
	lwz	r0, 20(sp)
	addi	sp, sp, 16
	mtspr	SPRG_LR, r0

	blr

	.size	EE_e200z7_call_ISR_new_stack, .-EE_e200z7_call_ISR_new_stack
