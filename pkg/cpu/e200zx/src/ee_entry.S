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
 * Entry points for the Z7 cpu.
 * Author: 2010 Fabio Checconi
 */

	.text

	.set noreorder

#include <cpu/e200zx/inc/ee_regs.h>

set_ivor: .macro n,label
	li	r0, 0
	addi	r0, 0, label@l
	mtspr	SPRG_IVOR_BASE + n, r0
	.endm

save_all: .macro
	addi	sp, sp, -80
	stw	r0, 8(sp)
	mfspr	r0, lr
	stw	r0, 12(sp)
	bl	save_registers
	.endm

restore_all: .macro
	bl	restore_registers
	lwz	r0, 12(sp)
	mtspr	lr, r0
	lwz	r0, 8(sp)
	addi	sp, sp, 80
	.endm

vector: .macro label,handler
	.align 5
	.type	label, @function
label:
	save_all
	b	handler
	.size	label, .-label
	.endm

vector_epilogue: .macro
	restore_all
	rfi
	.endm


	.type	save_registers, @function
save_registers:
	stw	r3, 20(sp)
	stw	r4, 24(sp)
	stw	r5, 28(sp)
	stw	r6, 32(sp)
	stw	r7, 36(sp)
	stw	r8, 40(sp)
	stw	r9, 44(sp)
	stw	r10, 48(sp)
	stw	r11, 52(sp)
	stw	r12, 56(sp)

	mfspr	r0, srr0
	stw	r0, 60(sp)
	mfspr	r0, srr1
	stw	r0, 64(sp)
	mfcr	r0
	stw	r0, 68(sp)
	mfspr	r0, ctr
	stw	r0, 72(sp)
	mfspr	r0, xer
	stw	r0, 76(sp)

	blr
	.size	save_registers, .-save_registers


	.type	restore_registers, @function
restore_registers:
	lwz	r0, 76(sp)
	mtspr	xer, r0
	lwz	r0, 72(sp)
	mtspr	ctr, r0
	lwz	r0, 68(sp)
	mtcr	r0
	lwz	r0, 64(sp)
	mtspr	srr1, r0
	lwz	r0, 60(sp)
	mtspr	srr0, r0

	lwz	r12, 56(sp)
	lwz	r11, 52(sp)
	lwz	r10, 48(sp)
	lwz	r9, 44(sp)
	lwz	r8, 40(sp)
	lwz	r7, 36(sp)
	lwz	r6, 32(sp)
	lwz	r5, 28(sp)
	lwz	r4, 24(sp)
	lwz	r3, 20(sp)

	blr
	.size	restore_registers, .-restore_registers


/*
 * this belongs to the mcu code; we'd need a way to let the mcu code
 * define a couple of macros for us...
 */
#include <mcu/freescale_mpc5674f/inc/ee_regs.h>

	.type	external_input_handler, @function
external_input_handler:
	addis	r3, 0, INTC_IACKR@ha	/* ack the interrupt */
	lwz	r0, INTC_IACKR@l(r3)

	srawi	r3, r0, 2		/* calculate the irq number */
	addi	r3, r3, 16

	bl	EE_e200z7_irq		/* handle the interrupt */

	addis	r3, 0, INTC_EOIR@ha	/* send the EOI */
	stw	r0, INTC_EOIR@l(r3)

	vector_epilogue
	.size	external_input_handler, .-external_input_handler


	.type	decrementer_handler, @function
decrementer_handler:
	addis	r0, 0, (1 << TSR_DIS)@h
	mtspr	tsr, r0
	li	r3, 10
	bl	EE_e200z7_irq
	vector_epilogue
	.size	decrementer_handler, .-decrementer_handler


	.type	__empty_handler, @function
__empty_handler:
	b	__empty_handler
	.size	__empty_handler, .-__empty_handler


vector_base:
vector critical_input, __empty_handler
vector machine_check, __empty_handler
vector data_storage, __empty_handler
vector instruction_storage, __empty_handler
vector external_input, external_input_handler
vector alignment, __empty_handler
vector program, __empty_handler
vector float_unavailable, __empty_handler
vector system_call, __empty_handler
vector auxiliary_unavailable, __empty_handler
vector decrementer, decrementer_handler
vector interval_timer, __empty_handler
vector watchdog_timer, __empty_handler
vector data_tlb_error, __empty_handler
vector instruction_tlb_error, __empty_handler
vector debug_critical, __empty_handler


	.global	EE_e200z7_setup_decrementer
	.type	EE_e200z7_setup_decrementer, @function
EE_e200z7_setup_decrementer:
	mtspr	decar, r3
	mtspr	dec, r3

	mfspr	r3, tcr
	oris	r3, r3, (1 << TCR_DIE)@ha
	oris	r3, r3, (1 << TCR_ARE)@ha
	mtspr	tcr, r3

	blr
	.size	EE_e200z7_setup_decrementer, .-EE_e200z7_setup_decrementer


	.global	EE_e200z7_setup_decrementer_oneshot
	.type	EE_e200z7_setup_decrementer_oneshot, @function
EE_e200z7_setup_decrementer_oneshot:
	mtspr	dec, r3

	mfspr	r3, tcr
	oris	r3, r3, (1 << TCR_DIE)@ha
	andis.	r3, r3, ~(1 << TCR_ARE)@ha
	mtspr	tcr, r3

	blr
	.size	EE_e200z7_setup_decrementer_oneshot, .-EE_e200z7_setup_decrementer_oneshot


	.global	EE_e200z7_stop_decrementer
	.type	EE_e200z7_stop_decrementer, @function
EE_e200z7_stop_decrementer:
	li	r0, 0

	mfspr	r3, tcr
	andis.	r3, r3, ~(1 << TCR_ARE)@ha
	mtspr	tcr, r3

	mtspr	decar, r0
	mtspr	dec, r0

	mfspr	r3, tcr
	andis.	r3, r3, ~(1 << TCR_DIE)@ha
	mtspr	tcr, r3

	addis	r3, 0, (1 << TSR_DIS)@h
	mtspr	tsr, r3

	blr
	.size	EE_e200z7_stop_decrementer, .-EE_e200z7_stop_decrementer


	.global	cpu_setup
	.type	cpu_setup, @function
cpu_setup:
	set_ivor 0, critical_input
	set_ivor 1, machine_check
	set_ivor 2, data_storage
	set_ivor 3, instruction_storage
	set_ivor 4, external_input
	set_ivor 5, alignment
	set_ivor 6, program
	set_ivor 7, float_unavailable
	set_ivor 8, system_call
	set_ivor 9, auxiliary_unavailable
	set_ivor 10, decrementer
	set_ivor 11, interval_timer
	set_ivor 12, watchdog_timer
	set_ivor 13, data_tlb_error
	set_ivor 14, instruction_tlb_error
	set_ivor 15, debug_critical
	msync

	addis	r0, 0, vector_base@h
	mtspr	ivpr, r0

	li	r0, 0
	mtspr	SPRG_TBL_W, r0
	mtspr	SPRG_TBH_W, r0
	mtspr	SPRG_TBL_W, r0

	mfspr	r3, SPRG_HID0
	ori	r3, r3, 1 << HID0_TBEN
	mtspr	SPRG_HID0, r3

	blr
	.size	cpu_setup, .-cpu_setup



	.section ".boot"

	.set TLB_0_MAS_0, 0x10050000
	.set TLB_0_MAS_1, 0xc0000700
	.set TLB_0_MAS_2, 0x00000000
	.set TLB_0_MAS_3, 0x0000003f

	.set TLB_1_MAS_0, 0x10010000
	.set TLB_1_MAS_1, 0xc0000500
	.set TLB_1_MAS_2, 0xfff0000a
	.set TLB_1_MAS_3, 0xfff0003f

	.set TLB_2_MAS_0, 0x10020000
	.set TLB_2_MAS_1, 0xc0000700
	.set TLB_2_MAS_2, 0x20000000
	.set TLB_2_MAS_3, 0x2000003f

	.set TLB_3_MAS_0, 0x10030000
	.set TLB_3_MAS_1, 0xc0000400
	.set TLB_3_MAS_2, 0x40000008
	.set TLB_3_MAS_3, 0x4000003f

	.set TLB_4_MAS_0, 0x10040000
	.set TLB_4_MAS_1, 0xc0000500
	.set TLB_4_MAS_2, 0xc3f00008
	.set TLB_4_MAS_3, 0xc3f0003f

#define TLB_VAL(num, mas)	TLB_&& ## num ## &&_MAS_ ## mas

set_tlb: .macro entry
	addis	r3, 0, TLB_VAL(entry, 0)@ha
	addi	r3, r3, TLB_VAL(entry, 0)@l
	mtspr	mas0, r3

	addis	r3, 0, TLB_VAL(entry, 1)@ha
	addi	r3, r3, TLB_VAL(entry, 1)@l
	mtspr	mas1, r3

	addis	r3, 0, TLB_VAL(entry, 2)@ha
	addi	r3, r3, TLB_VAL(entry, 2)@l
	mtspr	mas2, r3

	addis	r3, 0, TLB_VAL(entry, 3)@ha
	addi	r3, r3, TLB_VAL(entry, 3)@l
	mtspr	mas3, r3

	tlbwe
	.endm


	.global	mmu_setup
	.type	mmu_setup, @function
mmu_setup:
#ifndef __E200ZX_EXECUTE_FROM_RAM__
	set_tlb	0
	set_tlb	1
	set_tlb	2
	set_tlb	3
	set_tlb	4
	msync
#endif

	blr
	.size	mmu_setup, .-mmu_setup
