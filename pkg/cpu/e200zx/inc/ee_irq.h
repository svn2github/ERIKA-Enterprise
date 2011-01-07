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

#ifndef __INCLUDE_E200ZX_IRQ_H__
#define __INCLUDE_E200ZX_IRQ_H__

#include "ee_internal.h"
#include "cpu/common/inc/ee_irqstub.h"
#include "cpu/e200zx/inc/ee_irq.h"
#include "cpu/e200zx/inc/ee_internal.h"

typedef void (*EE_e200z7_ISR_handler)(void);
extern EE_e200z7_ISR_handler EE_e200z7_ISR_table[];

/*
 * Alternate ISR implementation, to be used when the user defines his own
 * entry points for ISRs.
 */

__asm static void EE_ISR1_prestub(void)
{
	wrteei	1
}

#define ISR1(f)								\
void ISR1_ ## f(void);							\
void f(void)								\
{									\
	EE_ISR1_prestub();						\
	ISR1_ ## f();							\
}									\
void ISR1_ ## f(void)

/*
 * NOTE: The ISR2 stubs are independent from the architecture, we should
 * move them to common/
 */
static inline void EE_ISR2_prestub(void)
{
	EE_increment_IRQ_nesting_level();
}

static inline void EE_ISR2_poststub(void)
{
	EE_decrement_IRQ_nesting_level();
	if (!EE_is_inside_ISR_call()) {
		EE_std_after_IRQ_schedule();
	}
}

#define ISR2(f)								\
void ISR2_ ## f(void);							\
void f(void)								\
{									\
	EE_ISR2_prestub();						\
	ISR2_ ## f();							\
	EE_ISR2_poststub();						\
}									\
void ISR2_ ## f(void)

#endif /*  __INCLUDE_E200ZX_IRQ_H__ */
