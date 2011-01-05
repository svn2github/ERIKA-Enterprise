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

#ifndef __INCLUDE_E200Z7_IRQ_INTERNAL_H__
#define __INCLUDE_E200Z7_IRQ_INTERNAL_H__

#include "ee_internal.h"
#include "cpu/common/inc/ee_irqstub.h"
#include "cpu/e200zx/inc/ee_irq.h"
#include "cpu/e200zx/inc/ee_internal.h"

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
#ifdef __IRQ_STACK_NEEDED__
void EE_e200z7_call_ISR_new_stack(int level, EE_e200z7_ISR_handler fun,
							unsigned nesting);
#else
__INLINE__ void __ALWAYS_INLINE__ EE_e200z7_call_ISR_new_stack(int level,
			EE_e200z7_ISR_handler fun, unsigned nesting)
{
	EE_std_enableIRQ_nested();
	if (fun != NULL) {
		fun();
	}
	EE_std_disableIRQ_nested();
}
#endif

/* IRQ handler */
void EE_e200z7_irq(int level);

#endif
