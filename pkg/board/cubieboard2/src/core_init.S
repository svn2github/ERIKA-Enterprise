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

        /*
         * Set up Domain Access Control Reg
         * ----------------------------------
         * b00 - No Access (abort)
         * b01 - Client (respect table entry)
         * b10 - RESERVED
         * b11 - Manager (ignore access permissions)
         * Setting D0 to client, all others to No Access
         */
        mov     r0, #0x01
        mcr     p15, 0, r0, c3, c0, 0

        ldr     r0, =__mmu_tbl_start
        mov     r2, #1024
        mov     r1, r0
        mov     r3, #0
        mov     r4, #0
        mov     r5, #0
        mov     r6, #0
l1_pg_table_zero_loop:
        stmia   r1!, {r3-r6}
        subs    r2, r2, #1
        bne     l1_pg_table_zero_loop
/* r4 -> mmu table */
        ldr     r0, =__mmu_tbl_start
        mov     r4, r0
        mov     r1, #0
@       mov     r3, #4096               /* 4gb address */
        mov     r3, #384                /* first 384MB: 128MB +
                                           256MB peripherals + romboot */
        ldr     r2, =TTB_COHERENT
        orr     r1, r1, r2
l1_pg_table_loop:
        str     r1, [r0]
        add     r0, r0, #4
        add     r1, r1, #0x100000
        subs    r3, r3, #1
        bne     l1_pg_table_loop

        mrc     p15, 4, r1, c15, c0, 0  /* periph base */
        lsr     r1, r1, #20
        lsl     r2, r1, #2
        lsl     r1, r1, #20
        ldr     r3, =TTB_DEVICE
        orr     r1, r1, r3
        str     r1, [r4, r2]
        /*UART2*/
        ldr     r1,=0x021E8000
        lsr     r1, r1, #20
        lsl     r2, r1, #2
        lsl     r1, r1, #20
        ldr     r3, =TTB_DEVICE
        orr     r1, r1, r3
        str     r1, [r4, r2]
        /* remap phy addr of __vector_start to va 0x00000000 & 0xffff0000 */
        ldr     r1, =_vector_table
        lsr     r1, r1, #20
        lsl     r1, r1, #20
        mov     r2, #0
        ldr     r3, =TTB_COHERENT
        orr     r1, r1, r3
        str     r1, [r4, r2]
        ldr     r2, =0xffff0000
        lsr     r2, #20
        lsl     r2, #2
        str     r1, [r4, r2]
        ldr     r6, =__ee_mcglobal_end
        lsr     r6, r6, #20
        ldr     r1, =__ee_mcglobal_start
        lsr     r1, r1, #20
        ldr     r3, =TTB_STRONGREORDER_NS
ee_mcglobal_loop:
        mov     r2, r1
        lsl     r2, #2
        lsl     r5, r1, #20
        orr     r5, r5, r3
        str     r5, [r4, r2]
        cmp     r1, r6
        addlt   r1, r1, #1
        blt     ee_mcglobal_loop

        mov     r7, #0                  /* dsb cp15 emulation (deprecated) */
        mcr     p15, 0, r7, c7, c10, 4  /* dsb instruction on non armv7 cpu */
        /* set phy address of l1 page table */
        mcr     p15, 0, r4, c2, c0, 0

#if 0
        /* enable MMU */
        mrc     p15, 0, r0, c1, c0, 0   /* current control register */
        orr     r0, r0, #0x01           /* set M bit */
        mcr     p15, 0, r0, c1, c0, 0   /* current control register */
#endif

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
	b	main

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
