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
 * Exception entry points and hardware setup for the e200zX CPUs.
 * Author: 2010 Fabio Checconi
 *         2011 Bernardo  Dal Seno
 */

#include <cpu/e200zx/inc/ee_regs.h>

	text_section(.text)

	ASM_REORDER_OFF

set_ivor: .macro n,label
#ifdef __VLE__
	se_li	r0, 0
	e_add16i r0, r0, label@l
	mtspr	SPRG_IVOR_BASE + n, r0
#else
	li	r0, 0
	addi	r0, 0, label@l
	mtspr	SPRG_IVOR_BASE + n, r0
#endif
	.endm


vector: .macro label,handler
	.balign	E200ZX_IRQ_ENTRY_ALIGN
	.type	label, @function
label:
#ifdef __VLE__
	e_add16i sp, sp, -80
	e_stw	r0, 8(sp)
	se_mflr	r0
	e_b	handler
#else
	addi	sp, sp, -80
	stw	r0, 8(sp)
	mfspr	r0, lr
	b	handler
#endif
	.size	label, .-label
	.endm


	.type	__empty_handler, @function
__empty_handler:
#ifdef __VLE__
	se_b	__empty_handler
#else
	b	__empty_handler
#endif
	.size	__empty_handler, .-__empty_handler


	.balign	E200ZX_IRQ_VECTOR_BASE_ALIGN
vector_base:
vector EE_e200zx_critical_input, __empty_handler
vector EE_e200zx_machine_check, __empty_handler
vector EE_e200zx_data_storage, __empty_handler
vector EE_e200zx_instruction_storage, __empty_handler
vector EE_e200zx_external_input, EE_e200zx_external_input_handler
vector EE_e200zx_alignment, __empty_handler
vector EE_e200zx_program, __empty_handler
vector EE_e200zx_float_unavailable, __empty_handler
vector EE_e200zx_system_call, __empty_handler
vector EE_e200zx_auxiliary_unavailable, __empty_handler
vector EE_e200zx_decrementer, EE_e200zx_decrementer_handler
vector EE_e200zx_interval_timer, __empty_handler
vector EE_e200zx_watchdog_timer, __empty_handler
vector EE_e200zx_data_tlb_error, __empty_handler
vector EE_e200zx_instruction_tlb_error, __empty_handler
vector EE_e200zx_debug_critical, __empty_handler


	.global	ivor_setup
	.type	ivor_setup, @function
ivor_setup:
	set_ivor 0, EE_e200zx_critical_input
	set_ivor 1, EE_e200zx_machine_check
	set_ivor 2, EE_e200zx_data_storage
	set_ivor 3, EE_e200zx_instruction_storage
	set_ivor 4, EE_e200zx_external_input
	set_ivor 5, EE_e200zx_alignment
	set_ivor 6, EE_e200zx_program
	set_ivor 7, EE_e200zx_float_unavailable
	set_ivor 8, EE_e200zx_system_call
	set_ivor 9, EE_e200zx_auxiliary_unavailable
	set_ivor 10, EE_e200zx_decrementer
	set_ivor 11, EE_e200zx_interval_timer
	set_ivor 12, EE_e200zx_watchdog_timer
	set_ivor 13, EE_e200zx_data_tlb_error
	set_ivor 14, EE_e200zx_instruction_tlb_error
	set_ivor 15, EE_e200zx_debug_critical
	msync

#ifdef __VLE__
	e_add2is r0, vector_base@h
	mtspr	ivpr, r0
	se_blr
#else
	addis	r0, 0, vector_base@h
	mtspr	ivpr, r0
	blr
#endif
	.size	ivor_setup, .-ivor_setup
