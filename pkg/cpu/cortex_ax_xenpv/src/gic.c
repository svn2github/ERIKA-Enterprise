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
 */

#include "cpu/common/inc/ee_types.h"
#include "cpu/cortex_ax_xenpv/inc/ee_gic_maps.h"
#include "cpu/cortex_ax_xenpv/inc/ee_cax_utils.h"

#include "eecfg.h"
#include "cpu/cortex_ax_xenpv/inc/ee_cax_irq.h"
#include "cpu/cortex_ax_xenpv/src/ee_gic_prio_table.h"

#if 0
void gic_dist_init()
{
	unsigned int max_irq;
	unsigned int i;

	EE_UINT32 cpu_mask = 1 << cortex_ax_smp_cpu_id();
	cpu_mask |= cpu_mask << 8;
	cpu_mask |= cpu_mask << 16;

	/* disable gic */
	writel(0, EE_IC_DISTRIBUTOR_BASE_ADDR + EE_GIC_DIST_CTRL);

	max_irq = readl(EE_IC_DISTRIBUTOR_BASE_ADDR + EE_GIC_DIST_CTR) & 0x1f;
	max_irq = (max_irq + 1) * 32;
	max_irq = (max_irq > 1020) ? 1020 : max_irq;

	/* Set all global interrupts to be level triggered, active low */
	for (i = 32; i < max_irq; i += 16)
		writel(0, EE_IC_DISTRIBUTOR_BASE_ADDR + EE_GIC_DIST_CONFIG
			  + i * 4 /16);

	/* Set all global interrupts to this CPU only */
	for (i = 32; i < max_irq; i += 4)
		writel(cpu_mask, EE_IC_DISTRIBUTOR_BASE_ADDR + EE_GIC_DIST_TARGET
				 + i * 4 / 4);

	/* Set priority on all global interrupts */
	for (i = 32; i < max_irq; i += 4)
		writel(0xa0a0a0a0, EE_IC_DISTRIBUTOR_BASE_ADDR + EE_GIC_DIST_PRI +
				   + i * 4 / 4);

	for (i = 32; i < max_irq; i += 32)
		writel(0xffffffff, EE_IC_DISTRIBUTOR_BASE_ADDR
				   + EE_GIC_DIST_ENABLE_CLEAR + i * 4 / 32);

	/* enable gic */
	writel(1, EE_IC_DISTRIBUTOR_BASE_ADDR + EE_GIC_DIST_CTRL);
}
#endif


void EE_gic_dist_init(void)
{
	unsigned int max_irq;
	unsigned int i;
	unsigned int intID;
	unsigned int prio;
	EE_UINT32 cpu_int_en = 0;
	EE_UINT32 reg_off;
	EE_UINT32 byte_off;
	EE_UINT32 tmp;
	EE_UINT32 cpu_mask = 1 << cortex_ax_smp_cpu_id();

#if 0
	cpu_mask |= cpu_mask << 8;
	cpu_mask |= cpu_mask << 16;
#endif
	/* disable gic dist */
	writel(0, EE_IC_DISTRIBUTOR_BASE_ADDR + EE_GIC_DIST_CTRL);

	printk("EE: here\n");
	max_irq = readl(EE_IC_DISTRIBUTOR_BASE_ADDR + EE_GIC_DIST_CTR) & 0x1f;
	max_irq = (max_irq + 1) * 32;
	max_irq = (max_irq > 1020) ? 1020 : max_irq;

	writel(0xffffffff, EE_IC_DISTRIBUTOR_BASE_ADDR + EE_GIC_DIST_ENABLE_CLEAR);

	for (i = 0; i < IP_TABLE_SIZE; ++i) {
		if (intID != 31 && intID != 27)
			continue;
		intID = ip_table[i].intID;
		prio = ip_table[i].prio;
		if (intID < 32) {
			reg_off = (intID / 4) * 4; /*  (* 4 means word) */
			byte_off = (intID % 4) * 8;
			tmp = readl(EE_IC_DISTRIBUTOR_BASE_ADDR
				    + EE_GIC_DIST_PRI + reg_off);
			tmp = (tmp & ~(0xff << byte_off))
			      | ((prio & 0xff) << byte_off);
			writel(tmp, EE_IC_DISTRIBUTOR_BASE_ADDR + EE_GIC_DIST_PRI +
				    + reg_off);
			cpu_int_en |= (1 << intID);
		} else {
		/* Set global interrupts to be level triggered, active low */
			reg_off = (intID / 16) * 4; /* (* 4 means word) */
			byte_off = (intID % 16) * 2;
			tmp = readl(EE_IC_DISTRIBUTOR_BASE_ADDR
				    + EE_GIC_DIST_CONFIG + reg_off);
			tmp = tmp & ~(0x3 << byte_off);
			writel(tmp, EE_IC_DISTRIBUTOR_BASE_ADDR
				    + EE_GIC_DIST_CONFIG + reg_off);

		/* Set global interrupts to this CPU */
			reg_off = (intID / 4) * 4; /* (* 4 means word) */
			byte_off = (intID % 4) * 8;
			tmp = readl(EE_IC_DISTRIBUTOR_BASE_ADDR
				    + EE_GIC_DIST_TARGET + reg_off);
			tmp = (tmp & ~(0xff << byte_off))
			      | ((cpu_mask & 0xff) << byte_off);
			writel(tmp, EE_IC_DISTRIBUTOR_BASE_ADDR
				    + EE_GIC_DIST_TARGET + reg_off);
		/* Set priority on global interrupts */
			tmp = readl(EE_IC_DISTRIBUTOR_BASE_ADDR
				    + EE_GIC_DIST_PRI + reg_off);
			tmp = (tmp & ~(0xff << byte_off))
			      | ((prio & 0xff) << byte_off);
			writel(tmp, EE_IC_DISTRIBUTOR_BASE_ADDR
				    + EE_GIC_DIST_PRI + reg_off);
		/* Enable global interrupt forwarding from distributor to cpu interface */
			reg_off = (intID / 32) * 4; /* (* 4 measn word) */
			byte_off = (intID % 32) * 1;
			tmp = 1 << byte_off;
			writel(tmp, EE_IC_DISTRIBUTOR_BASE_ADDR
				    + EE_GIC_DIST_ENABLE_SET + reg_off);
		}
	}

	writel(cpu_int_en, EE_IC_DISTRIBUTOR_BASE_ADDR + EE_GIC_DIST_ENABLE_SET);

	/* enable gic dist */
	writel(1, EE_IC_DISTRIBUTOR_BASE_ADDR + EE_GIC_DIST_CTRL);

	/* enable gic cpu */
	writel(EE_GIC_MIN_PRIO, EE_IC_INTERFACES_BASE_ADDR + EE_GIC_CPU_PRIMASK);
	writel(1, EE_IC_INTERFACES_BASE_ADDR + EE_GIC_CPU_CTRL);
}

void gic_cpu_init(void)
{
	int i;
	//unsigned int val = 0x0000ffff; /* all the private sgi */
	unsigned int val = 0x00000000; /* all the private sgi */

	/* SGI & PPI stuffs */
	writel(0xffffffff, EE_IC_DISTRIBUTOR_BASE_ADDR + EE_GIC_DIST_ENABLE_CLEAR);
//	writel(0x0000ffff, EE_IC_DISTRIBUTOR_BASE_ADDR + EE_GIC_DIST_ENABLE_SET);
//	val |= (1 << 29); /* private local timer interrupt */
	writel(val, EE_IC_DISTRIBUTOR_BASE_ADDR + EE_GIC_DIST_ENABLE_SET);

	for (i = 0; i < 32; i += 4)
		writel(0xf0f0f0f0, EE_IC_DISTRIBUTOR_BASE_ADDR + EE_GIC_DIST_PRI +
				   + i * 4 / 4);

	writel(0xf0, EE_IC_INTERFACES_BASE_ADDR + EE_GIC_CPU_PRIMASK);
	writel(1, EE_IC_INTERFACES_BASE_ADDR + EE_GIC_CPU_CTRL);

}

void EE_gic_send_sgi(EE_UINT32 id, EE_UINT32 target_list, EE_UINT32 filter_list)
{
	EE_UINT32 reg = 0;
	/* NSATT = 0 --> only to group 0 */
	reg = ((filter_list & 0x3) << 24)
	      | ((target_list & 0xff)) << 16
	      | (id & 0x0f);

	writel(reg, EE_IC_DISTRIBUTOR_BASE_ADDR + EE_GIC_DIST_SOFTINT);
}
