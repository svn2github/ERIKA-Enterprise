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
 * Multicore support
 * Author: 2011 Bernardo  Dal Seno
 */

#include <ee_internal.h>
#include <cpu/e200zx/inc/ee_irq.h>

#if EE_CURRENTCPU == 0
EE_TYPEBARRIER EE_SHARED_UDATA EE_e200zx_start_barrier;
#endif


void EE_e200zx_sync_barrier(EE_TYPEBARRIER *bar)
{
	EE_UINT32 all = (1U << EE_MAX_CPU) - 1U;
	EE_hal_spin_in(0);
	bar->value |= (1U << EE_CURRENTCPU);
	EE_hal_spin_out(0);
	while (bar->value != all) {
		/* Wait for all other cores/CPUs */
	}
}


static void EE_e200zx_setup_inter_irqs(void)
{
	EE_e200z7_register_ISR(EE_E200ZX_INTER_IRQ_LEVEL(EE_CURRENTCPU),
		EE_rn_handler, 1);
}


static void EE_e200zx_iirq_handler(void)
{
	EE_rn_handler();
}


int EE_cpu_startos(void)
{
	EE_e200zx_setup_inter_irqs();
	EE_e200zx_sync_barrier(&EE_e200zx_start_barrier);
	return 0;
}