/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2009-2011  Evidence Srl
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

#include "ee.h"
#include "ee_irq.h"
#include "test/assert/inc/ee_assert.h"

#include "cpu/cortex_ax/inc/ee_private_timer.h"
#include "mcu/freescale_imx6/inc/serial.h"

#include "cpu/cortex_ax/inc/ee_buffer_io.h"

#ifndef TRUE
#define TRUE 1
#endif

/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[10];

/* Final result */
EE_TYPEASSERTVALUE result;

#define __EE_OO_XEN_PV__
#ifdef __EE_OO_XEN_PV__

#include "xendebug.h"
#include "xenincludes.h"

extern int HYPERVISOR_memory_op(int what, struct xen_add_to_physmap *xatp);

void *dtb_global;
extern char _end;
shared_info_t *HYPERVISOR_shared_info;

void EE_oo_Xen_map_shared(void)
{
	struct xen_add_to_physmap xatp;
	/* Map shared info page */
	xatp.domid = DOMID_SELF;
	xatp.idx = 0;
	xatp.space = XENMAPSPACE_shared_info;
	xatp.gpfn = virt_to_pfn(&shared_info);
	if (HYPERVISOR_memory_op(XENMEM_add_to_physmap, &xatp) != 0)
		BUG();
	HYPERVISOR_shared_info = (struct shared_info *)&shared_info;
	printk("EE: shared info page mapped\n");
}

#define PAGE_SHIFT		12
#define PAGE_SIZE		(1 << PAGE_SHIFT)
#define PHYS_SIZE		(40*1024*1024)
unsigned long start_pfn_p, max_pfn_p;

void EE_oo_Xen_init_mm(void)
{
        // FIXME Get from dt!
        start_pfn_p = (((unsigned long)&_end) >> PAGE_SHIFT) + 1000;
        max_pfn_p = ((unsigned long)&_end + PHYS_SIZE) >> PAGE_SHIFT;
	printk("EE: init mm\n");
}

#include "gic.c"
#include "xenstore.c"

struct xenstore_domain_interface xenstore_buf;
uint32_t store_evtchn;

void EE_oo_Xen_init_xenbus(void)
{
	struct xenstore_domain_interface *xsb = &xenstore_buf;
	arch_init_xenbus(&xsb, &store_evtchn);
	// XXX: create xenstore task
	//      bind xenstore evtchn
	//      unmask xenstore evtchn
	printk("EE: xenbus init\n");
}

void EE_oo_Xen_Start(void)
{
	printk("EE: Xen start\n");
	EE_oo_Xen_map_shared();
	EE_oo_Xen_init_mm();
	gic_init();
	printk("EE: gic init\n");
	//EE_oo_Xen_init_xenbus();
}
#endif /*__EE_OO_XEN_PV__*/

#include "gpio.h"

unsigned int SUNXI_PIO_BASE = 0;

void gpio_init(void)
{
	unsigned int PageSize, PageMask,
		     addr_start, addr_offset;

	PageSize = 4096;
	PageMask = (~(PageSize-1));
	addr_start = SW_PORTC_IO_BASE & PageMask;
	addr_offset = SW_PORTC_IO_BASE & ~PageMask;

	SUNXI_PIO_BASE = addr_start + addr_offset;
}

int gpio_cfg_pin(unsigned int pin, unsigned int val)
{
	unsigned int cfg;
	unsigned int bank = GPIO_BANK(pin);
	unsigned int index = GPIO_CFG_INDEX(pin);
	unsigned int offset = GPIO_CFG_OFFSET(pin);

	if (!SUNXI_PIO_BASE)
		return -1;

	struct sunxi_gpio *pio =
		&((struct sunxi_gpio_reg *)SUNXI_PIO_BASE)->gpio_bank[bank];

	cfg = *(&pio->cfg[0] + index);
	cfg &= ~(0xf << offset);
	cfg |= val << offset;

	*(&pio->cfg[0] + index) = cfg;

	return 0;
}

int gpio_output(unsigned int pin, unsigned int val)
{
	unsigned int bank = GPIO_BANK(pin);
	unsigned int num = GPIO_NUM(pin);

	if (!SUNXI_PIO_BASE)
		return -1;

	struct sunxi_gpio *pio =&((struct sunxi_gpio_reg *)SUNXI_PIO_BASE)->gpio_bank[bank];

	if (val)
		*(&pio->dat) |= 1 << num;
	else
		*(&pio->dat) &= ~(1 << num);

	return 0;
}

TASK(Hello_world_task)
{
#ifdef __EE_OO_XEN_PV__
	printk("EE: task\n");
	gpio_cfg_pin(PD1, OUTPUT);
	printk("EE: task: GPIO configured\n");
	gpio_output(PD1, HIGH);
	printk("EE: task: GPIO pin high\n");
#endif /*__EE_OO_XEN_PV__*/
}

/*
 * MAIN TASK
*/

/* The loop is OK */


void ErrorHook(StatusType Error)
{
    /*TODO*/
    return;
}

int main(void)
{
//    EE_serial_init();
#ifdef __EE_OO_XEN_PV__
    printk("ERIKA Enterprise\n");
    EE_oo_Xen_Start();
#endif /* __EE_OO_XEN_PV__ */
    EnableAllInterrupts();
#ifdef __EE_OO_XEN_PV__
    printk("EE: interrupts enabled\n");
#endif /* __EE_OO_XEN_PV__ */
    gpio_init();
#ifdef __EE_OO_XEN_PV__
    printk("EE: GPIO initialized\n");
#endif /* __EE_OO_XEN_PV__ */
    EE_assert(1, TRUE, EE_ASSERT_NIL);

    StartOS(OSDEFAULTAPPMODE);

    ActivateTask(Hello_world_task);

    // Forever loop: background activities (if any) should go here
    for (;;) ;

    return 0;
}
