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
 * Dual-core interfacing code for MPC5668
 * Author: 2011 Bernardo  Dal Seno
 */

#ifndef EE_MCU_MPC5668_DUAL_H
#define EE_MCU_MPC5668_DUAL_H

#include "mpc5668.h"

/* First software IRQ used for interprocessor communication  */
#define EE_MPC5668_INTER_IRQ_BASE 6
/* Position in VBA of the first interprocessor IRQ */
#define EE_MPC5668_INTER_IRQ_VBA_BASE EE_MPC5668_INTER_IRQ_BASE
/* Interprocessor IRQ vector number, from CPU id */
#define EE_MPC5668_INTER_IRQ_LEVEL(cpu) \
	((cpu) + EE_MPC5668_INTER_IRQ_VBA_BASE + 16)


/* Enable the Z0 CPU, which starts executing the code pointed by `f' */
__INLINE__ void EE_mpc5668_start_z0(void (*f)(void))
{
	CRP.Z0VEC.R = (uint32_t)f;
}

/* Setup the intercore IRQs used by ERIKA for multicore support */
__INLINE__ void EE_mpc5668_setup_inter_irqs(void)
{
	INTC.PSR[EE_MPC5668_INTER_IRQ_BASE + 0].R = 0;
	INTC.PSR[EE_MPC5668_INTER_IRQ_BASE + 1].R = 0xc0;
}

/* Signal the core `cpu' (0/1) by sending an IIRQ */
__INLINE__ void EE_mpc5668_signal_cpu(int cpu)
{
	INTC.SSCIR[EE_MPC5668_INTER_IRQ_BASE + cpu].R = 2;
}

/* Acknowledge the signal riceved by the core `cpu' (0/1) */
__INLINE__ void EE_mpc5668_ack_signal(int cpu)
{
	INTC.SSCIR[EE_MPC5668_INTER_IRQ_BASE + cpu].R = 1;
}

/* Acquire the spin lock `spin_id' */
__INLINE__ void EE_mpc5668_spin_in(EE_TYPESPIN spin_id)
{
	/* The same value as EE_CURRENTCPU can be obtained at run-time by
	 * reading from special register PIR (286) */
	int locked_val = EE_CURRENTCPU + 1;
	do {
		SEMA4.GATE[spin_id].R = locked_val;
	} while (SEMA4.GATE[spin_id].R != locked_val);
}

/* Release the spin lock `spin_id' */
__INLINE__ void EE_mpc5668_spin_out(EE_TYPESPIN spin_id)
{
	SEMA4.GATE[spin_id].R = 0;
}


#endif /* EE_MCU_MPC5668_DUAL_H */
