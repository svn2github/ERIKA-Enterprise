/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2013  Evidence Srl
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
 * Author: 2013 Bruno Morelli
 * Contribution: 2014 Karim Allah (hints from his Mini-OS ARM port)
 */
#define PHYS_START (0x80008000)
#define TTB_COHERENT            0x00014c06
#define TTB_STRONGREORDER       0x00014c02
#define TTB_STRONGREORDER_NS    0x00004c02
#define TTB_NONCOHERENT         0x00000c1e
/*#define TTB_DEVICE            0x00000c06*/
#define TTB_DEVICE              0x00000c02

#include "cpu/cortex_ax/inc/ee_cax_defs.h"

.section .text

.globl _start
.extern dtb_global
_start:
	@ zImage header
.rept   8
        mov     r0, r0
.endr
        b       1f
        .word   0x016f2818      @ Magic numbers to help the loader
        .word   _start		@ absolute load/run zImage address
        .word   _end - _start   @ zImage size
	@ end of zImage header

1:
@ core processor specific initialization
	@ Set the CPU to SVC32 mode
	mrs     r0, cpsr
        bic     r0, r0, #0x1f
        orr     r0, r0, #0xd3
        msr     cpsr, r0
@ clear branch prediction array
	mov     r0, #0
	mcr     p15, 0, r0, c7, c5, 6   @ BPIALL invalidate entire branch
					@ predictor array
@ invalidate TLBs
        mov     r0, #0
        mcr     p15, 0, r0, c8, c7, 0   @ TLBIALL Invalidate entire
                                        @ Unifed TLB

	@ save dtb pointer before we clobber r2
        ldr     r1, =dtb_global
	str     r2, [r1]

@ Build pagetables
	bl	build_pagetables

	ldr	r2, =page_dir
	MCR	p15, 0, r2, c2, c0, 0	@ set ttbr0

	@ Set access permission for domains
	mov	r0, #0x3
	MCR	p15, 0, r0, c3, c0, 0
	isb

	ldr	r0, =mmu_switched

	@ enable mmu / sctlr
	mrc	p15, 0, r1, c1, c0, 0	@ read sctlr
	orr	r1, r1, #0x1		@ enable mmu
	@orr	r1, r1, #0x4		@ enable cache
	orr	r1, r1, #0x02		@ enable barrier enable
	@mcr	p15, 0, r1, c1, c0, 0	@ write sctlr
	isb

	@ jump to the virtual address now
	mov	pc, r0

@ If we're here, then we're very lucky
mmu_switched:

        /* enable branch prediction */
        mrc     p15, 0, r0, c1, c0, 0   /* get SCTLR */
        orr     r0, r0, #(1 << 11)      /* set Z bit */
        mcr     p15, 0, r0, c1, c0, 0   /* write SCTLR */

        /* AMP/SMP config */
        mrc     p15, 0, r0, c1, c0, 1   /* read aux ctrl reg (ACTLR) */
        bic     r0, r0, #(1 << 6)       /* reset bit 6 (SMP) */
        mcr     p15, 0, r0, c1, c0, 1   /* write aux ctrl reg (ACTLR) */

@ load stack
	@ Interrupt stack (IRQ)
        mov     r1, #I_bit | F_bit | Mode_IRQ
        msr     cpsr_c, r1
        ldr	sp, =EE_irq_stack_start
	add	sp, sp, #(4*1024)

	@ Abort stack (ABT)
        mov     r1, #I_bit | F_bit | Mode_ABT
        msr     cpsr_c, r1
        ldr     sp, =EE_abt_stack_start
	add	sp, sp, #(1024)

	@ Fast interrupt stack (FIQ)
	mov     r1, #I_bit | F_bit | Mode_FIQ
	msr     cpsr_c, r1
	ldr     sp, =EE_fiq_stack_start
	add	sp, sp, #(1024)

        @ Supervisor stack (SWI)
        mov     r1, #I_bit | F_bit | Mode_SVC
        msr     cpsr_c, r1
        ldr     sp, =EE_svc_stack_start
	add	sp, sp, #(1024)

        @ System stack (default running mode)
	mov     r1, #I_bit | F_bit | Mode_SYS
        msr     cpsr_c, r1
        ldr     sp, =EE_stack_start
	add	sp, sp, #(4*2*1024)

#ifdef __OO_ORTI_STACK__
        ldr     r0, =EE_stack_start
        ldr     r1, =EE_stack_end
        ldr     r2, =0xa5a5a5a5
_orti_stack_fill:
        str     r2, [r1], #4
        cmp     r1, r0;
        bcc     _orti_stack_fill
#endif

        ldr     r0, =__bss_start__
        ldr     r1, =__bss_end__
        mov     r2, #0
bss_loop:
        str     r2, [r0]
        cmp     r0, r1
        add     r0, r0, #4
        bne     bss_loop

#if 0
	@ GPIO configuration
	ldr	r1, =0x01C20800		@ PIO base address: 0x01c20800
	ldr	r2, [r1, #0x6c]		@ PD_CFG0 offset  : 0x6c
	@ Set bit 6:4 to 001 (output)
	@ Default value for PD_CFG0 is 0, so all we have to do is
	@ set bit 4 to 1
	orr	r2, r2, #4
	str	r2, [r1]
	ldr	r1, =0x01C2087C		@ PD_DAT offset   : 0x7c
	orr	r1, r1, #0
#endif

	b	main

@ Populate the whole pagedir with 1MB section descriptors for now (1-1 mapping)
build_pagetables:
	ldr	r0, =(0x2 + (1 << 16) + (1<<19)) @ First section entry (sharable + NS ).
	ldr	r1, =page_dir
	add	r2, r1, #(4*4*1024) @ Limit

1:
	str	r0, [r1] @ write the section entry

	add	r0, r0, #(1 << 20) @ next physical page.
	add	r1, r1, #4 @ next pagedir entry
	cmp	r1, r2
	bne	1b

	mov	pc, lr

.pushsection .data
.align 13
.globl EE_stack_start
EE_stack_start:
	.fill (2048), 4, 0x0
.align 13
.globl EE_irq_stack_start
EE_irq_stack_start:
	.fill (1024), 4, 0x0
.align 13
.globl EE_fiq_stack_start
EE_fiq_stack_start:
        .fill (1024), 1, 0x0
.align 13
.globl EE_svc_stack_start
EE_svc_stack_start:
        .fill (1024), 1, 0x0
.align 13
.globl EE_abt_stack_start
EE_abt_stack_start:
        .fill (1024), 1, 0x0
.globl shared_info
.align 13
shared_info:
	.fill (1024), 4, 0x0
.align	14
page_dir:
	.fill (4*1024), 4, 0x0

.popsection
.end
