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
 * IRQ functions used in test cases for PPC e200zX
 * Author: 2011 Bernardo  Dal Seno
 */


#include "../test_common.h"
#include <cpu/e200zx/inc/ee_mcu_regs.h>
#include <cpu/e200zx/inc/ee_irq.h>

#define E200ZX_TEST_IRQ0 0

static void test_isr(void)
{
	INTC.SSCIR[E200ZX_TEST_IRQ0].R = 1; /* Ack the IRQ */
	isr_callback();
}

void test_setup_irq(void)
{
	INTC.PSR[E200ZX_TEST_IRQ0].R = 0;
	EE_e200z7_register_ISR(16 + E200ZX_TEST_IRQ0, test_isr, 1);
}

void test_fire_irq(void)
{
	INTC.SSCIR[E200ZX_TEST_IRQ0].R = 2;
	EE_e200zx_isync();
}
