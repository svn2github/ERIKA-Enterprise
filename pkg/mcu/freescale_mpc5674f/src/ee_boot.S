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
 * Boot code for the MPC5674F board.
 * Author: 2010 Fabio Checconi
 */

#include <mcu/freescale_mpc5674f/inc/ee_regs.h>

	.section ".boot"

	.extern	_load_ram, _sdata, _sbss, _ebss
	.globl __start

	.long	0			/* leave room for the BAM data */
	.long	0

__start:
	lis	r8, _stack0@ha		/* setup the stack pointer */
	addi	sp, r8, _stack0@l

	lis	r8, _load_ram@ha	/* load _load_ram into r8 */
	addi	r8, r8, _load_ram@l
	lis	r9, _sbss@ha		/* load _sbss into r9 */
	addi	r9, r9, _sbss@l
	lis	r10, _sdata@ha		/* load _sdata into r10 */
	addi	r10, r10, _sdata@l

	cmplw	cr0, r8, r10		/* check if we have to move data */
	beq	2f

	/* NOTE: the loops below assume that .data and .bss are not empty */
1:
	lwz	r11, 0(r8)		/* copy .data where it belongs */
	addi	r8, r8, 4
	stw	r11, 0(r10)
	addi	r10, r10, 4
	cmplw	cr0, r10, r9
	blt	1b

2:
	lis	r8, _ebss@ha		/* load _ebss into r8 (r9 is _sbss) */
	addi	r8, r8, _ebss@l
	li	r11, 0			/* load 0 in r11 */

1:
	stw	r11, 0(r9)		/* zero out the BSS */
	addi	r9, r9, 4
	cmplw	cr0, r9, r8
	blt	1b

	lis	r8, _estack@ha		/* load _estack into r8 */
	addi	r8, r8, _estack@l
	lis	r9, _sstack@ha		/* load _sstack into r9 */
	addi	r9, r9, _sstack@l
	lis	r11, 0xa5a5a5a5@ha	/* load the fill pattern in r11 */
	addi	r11, r11, 0xa5a5a5a5@l

1:
	stw	r11, 0(r9)		/* fill the stacks */
	addi	r9, r9, 4
	cmplw	cr0, r9, r8
	blt	1b

	lis	r13, _SDA_BASE_@ha	/* load .sdata base into r13 */
	addi	r13, r13, _SDA_BASE_@l
	lis	r2, _SDA2_BASE_@ha	/* load .sdata2 base into r2 */
	addi	r2, r2, _SDA_BASE_@l

	bl	cpu_setup		/* cpu-specific initialization */
	bl	mcu_setup		/* mcu-specific initialization */
	bl	main			/* jump to application code */

	wrteei	0
1:
	b	1b

	.section ".stack"
	.align 4

	.space	504

	.global _stack0
_stack0:
	.space	8

/*
 * external interrupt handlers (the first 16 entries are for cpu vectors)
 * to use the full hw support we should let the INTC handle the multiplexing,
 * since we have a common entry point, by now use it.
 */
/* #define VTBA		(16 * 4 + EE_e200z7_ISR_table) */
#define VTBA	0

	.text
mcu_setup:
	/* MCR = 0: VTES=0 (4 byte entries) HVEN=0 (SW vector mode) */
	li	r0, 0
	lis	r3, INTC_MCR@ha
	stw	r0, INTC_MCR@l(r3)

	/* init current priority */
	stw	r0, INTC_CPR@l(r3)

	/* init vector table base address */
	lis	r4, VTBA@ha
	addi	r4, r4, VTBA@l
	stw	r4, INTC_IACKR@l(r3)

	blr
