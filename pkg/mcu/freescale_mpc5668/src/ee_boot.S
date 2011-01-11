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
 * Boot code for the MPC5668 board.
 * Author: 2010 Fabio Checconi
 */

#include <mcu/freescale_mpc5668/inc/ee_regs_asm.h>

	.section ".boot"

	.extern	_load_ram, _sdata, _sbss, _ebss

	.long	0			/* leave room for the BAM data */
	.long	0

	.global	__start
	.type	__start, @function
__start:
	bl	mmu_setup
	/* bl	sram_setup */
	/* bl	pll_setup */

	addis	r8, 0, _stack0@ha	/* setup the stack pointer */
	addi	sp, r8, _stack0@l

	addis	r8, 0, _load_ram@ha	/* load _load_ram into r8 */
	addi	r8, r8, _load_ram@l
	addis	r9, 0, _sbss@ha		/* load _sbss into r9 */
	addi	r9, r9, _sbss@l
	addis	r10, 0, _sdata@ha	/* load _sdata into r10 */
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
	addis	r8, 0, _ebss@ha		/* load _ebss into r8 (r9 is _sbss) */
	addi	r8, r8, _ebss@l
	li	r11, 0			/* load 0 in r11 */

1:
	stw	r11, 0(r9)		/* zero out the BSS */
	addi	r9, r9, 4
	cmplw	cr0, r9, r8
	blt	1b

	addis	r8, 0, _estack@ha	/* load _estack into r8 */
	addi	r8, r8, _estack@l
	addis	r9, 0, _sstack@ha	/* load _sstack into r9 */
	addi	r9, r9, _sstack@l
	addis	r11, 0, 0xa5a5a5a5@ha	/* load the fill pattern in r11 */
	addi	r11, r11, 0xa5a5a5a5@l

1:
	stw	r11, 0(r9)		/* fill the stacks */
	addi	r9, r9, 4
	cmplw	cr0, r9, r8
	blt	1b

	addis	r13, 0, _SDA_BASE_@ha	/* load .sdata base into r13 */
	addi	r13, r13, _SDA_BASE_@l
	addis	r2, 0, _SDA2_BASE_@ha	/* load .sdata2 base into r2 */
	addi	r2, r2, _SDA_BASE_@l

	bl	flash_setup		/* reduce flash wait states */

	bl	cpu_setup		/* cpu-specific initialization */
	bl	intc_setup		/* mcu-specific initialization */
	bl	main			/* jump to application code */

	wrteei	0
1:
	b	1b
	.size	__start, .-__start

#define RAM_BASE	0x40000000
#define RAM_WORDS	0x00010000

	.type	sram_setup, @function
sram_setup:
#ifndef __E200ZX_EXECUTE_FROM_RAM__
	addis	r8, 0, RAM_BASE@ha
	addi	r8, r8, RAM_BASE@l
	addis	r9, 0, RAM_WORDS@ha
	addi	r9, r9, RAM_WORDS@l
	mtctr	r9

1:
	stw	r0, (r8)
	addi	r8, r8,  4
	bdnz	1b
#endif

	blr
	.size	sram_setup, .-sram_setup

#define FMPLL_BASE		0xc3f80000
#define FMPLL_ESYNSR		0xc3f80004
#define FMPLL_ESYNCR1		0xc3f80008
#define FMPLL_ESYNCR2		0xc3f8000c

#ifdef F200MHZ
#define FMPLL_ESYNCR1_VAL0	0x00050022
#define FMPLL_ESYNCR2_VAL0	0x00000003
#define FMPLL_ESYNCR1_VAL1	0x70050022
#define FMPLL_ESYNCR2_VAL1	0x00000001
#else
#define FMPLL_ESYNCR1_VAL0	0x00050022
#define FMPLL_ESYNCR2_VAL0	0x00000003
#define FMPLL_ESYNCR1_VAL1	0x70050022
#define FMPLL_ESYNCR2_VAL1	0x00000003
#endif

	.type	pll_setup, @function
pll_setup:
	addis	r8, 0, FMPLL_BASE@ha

	/* setup PLL to 200Mhz */

	addis	r9, 0, FMPLL_ESYNCR2_VAL0@h
	addi	r9, r9, FMPLL_ESYNCR2_VAL0@l
	stw	r9, FMPLL_ESYNCR2@l(r8)
	msync

	addis   r9,0, FMPLL_ESYNCR1_VAL0@h
	addi	r9, r9, FMPLL_ESYNCR1_VAL0@l
	stw	r9, FMPLL_ESYNCR1@l(r8)
	msync

	addis	r9, 0, FMPLL_ESYNCR1_VAL1@h
	addi	r9, r9, FMPLL_ESYNCR1_VAL1@l
	stw	r9, FMPLL_ESYNCR1@l(r8)
	msync

1:
	/* wait for PLL to lock */
	addis   r9, 0, 0
	addi	r9, r9, 48000
	mtctr	r9

	/* load the lock bitmask in r9 */
	addis   r9, 0, 0
	addi	r9, r9, 8

2:
	bdnz	3f

	/* timed out: should reset or do something smarter... */
	b	1b

3:
	lwz	r10, FMPLL_ESYNSR@l(r8)
	and.	r11, r9, r10
	bne	2b

	/* locked: return */
	addis   r9, 0, FMPLL_ESYNCR2_VAL1@h
	addi	r9, r9, FMPLL_ESYNCR2_VAL1@l
	stw	r9, FMPLL_ESYNCR2@l(r8)
	msync

	blr
	.size	pll_setup, .-pll_setup


#define	FLASH_BIUCR	0
#define FLASH_CFG	0

	.type	flash_setup, @function
flash_setup:
#ifndef __E200ZX_EXECUTE_FROM_RAM__
	mfspr	r10, lr
#ifdef notyet
	bl	sram_code
#endif
	mtspr	lr, r10
#endif /* __E200ZX_EXECUTE_FROM_RAM__ */
	blr
	.size	flash_setup, .-flash_setup

#ifndef __E200ZX_EXECUTE_FROM_RAM__
	.section ".sram_text"
	.type	sram_code, @function
sram_code:
	addis	r8, 0, FLASH_BIUCR@ha
	addis	r9, 0, FLASH_CFG@ha
	addi	r9, r9, FLASH_CFG@l

	stw	r9, FLASH_BIUCR@l(r8)

	isync
	blr
	.size	sram_code, .-sram_code
#endif /* __E200ZX_EXECUTE_FROM_RAM__ */	

	
	.section ".stack"
	.align 4

	.space	496

	.global _stack0
_stack0:
	.space	16

/*
 * external interrupt handlers (the first 16 entries are for cpu vectors)
 * to use the full hw support we should let the INTC handle the multiplexing,
 * since we have a common entry point, by now use it.
 */
/* #define VTBA		(16 * 4 + EE_e200z7_ISR_table) */
/* VTBA = 0 -> Only offsets are read from INTC_IACKR_PRC */
#define VTBA	0

	.text
	.type	intc_setup, @function
intc_setup:
	/* MCR = 0: VTES=0 (4 byte entries) HVEN=0 (SW vector mode) */
	li	r0, 0
	addis	r3, 0, INTC_MCR@ha
	stw	r0, INTC_MCR@l(r3)

	/* init current priority */
	stw	r0, INTC_CPR@l(r3)

	/* init vector table base address */
	addis	r4, 0, VTBA@ha
	addi	r4, r4, VTBA@l
	stw	r4, INTC_IACKR@l(r3)

	blr
	.size	intc_setup, .-intc_setup
