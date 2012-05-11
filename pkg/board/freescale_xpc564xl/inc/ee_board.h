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
 * MPC564XL register mappings
 * Author: 2012 Francesco Esposito
 */

#ifndef INCLUDE_EE_FREESCALE_MPC564XL_BOARD_H
#define INCLUDE_EE_FREESCALE_MPC564XL_BOARD_H

#define SIU_BASE	0xc3f90000

#define SIU_PCRS	((volatile EE_UINT16 *)(SIU_BASE+0x0040))

/* Leds */
#define SIU_PCR52	SIU_PCRS[52]
#define SIU_PCR53	SIU_PCRS[53]
#define SIU_PCR54	SIU_PCRS[54]
#define SIU_PCR55	SIU_PCRS[55]

/* Button */
#define SIU_PCR0	SIU_PCRS[0]
#define SIU_PCR8	SIU_PCRS[8]
#define SIU_PCR17	SIU_PCRS[17]
#define SIU_PCR38	SIU_PCRS[38]

#define SIU_GPIO	((volatile EE_UINT8 *)(SIU_BASE + 0x0600))

#define SIU_IREER	(*(volatile EE_UINT32 *)(SIU_BASE + 0x0028))
#define SIU_IFEER	(*(volatile EE_UINT32 *)(SIU_BASE + 0x002c))

#define SIU_ISR		(*(volatile EE_UINT32 *)(SIU_BASE + 0x0014))

#define SIU_IRER	(*(volatile EE_UINT32 *)(SIU_BASE + 0x0018))

#define SIU_IFER	(*(volatile EE_UINT32 *)(SIU_BASE + 0x0030))

#ifdef __USE_LEDS__

#define LED_0	1
#define LED_1	2
#define LED_2	4
#define LED_3	8

/* Leds initialization */
__INLINE__ void __ALWAYS_INLINE__ EE_leds_init(void)
{
	SIU_PCR52 = 0x4200;
	SIU_PCR53 = 0x4200;
	SIU_PCR54 = 0x4200;
	SIU_PCR55 = 0x4200;

	/* Turn leds off after initialization */
	SIU_GPIO[52] = 1;
	SIU_GPIO[53] = 1;
	SIU_GPIO[54] = 1;
	SIU_GPIO[55] = 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_leds(EE_UREG led)
{
	SIU_GPIO[52] = led & 1;
	SIU_GPIO[53] = (led >> 1) & 1;
	SIU_GPIO[54] = (led >> 2) & 1;
	SIU_GPIO[55] = (led >> 3) & 1;
}

/* Turn ALL leds on */
__INLINE__ void __ALWAYS_INLINE__ EE_leds_on(void)
{
	SIU_GPIO[52] = 0;
	SIU_GPIO[53] = 0;
	SIU_GPIO[54] = 0;
	SIU_GPIO[55] = 0; /* fourth led not working (bug in the PD7) */
}

/* Turn ALL leds off */
__INLINE__ void __ALWAYS_INLINE__ EE_leds_off(void)
{
	SIU_GPIO[52] = 1;
	SIU_GPIO[53] = 1;
	SIU_GPIO[54] = 1;
	SIU_GPIO[55] = 1;
}

/* turn specific led on/off: val=1 off, val=0 on */
__INLINE__ void __ALWAYS_INLINE__ EE_led_set(EE_UREG idx, EE_UREG val)
{
	SIU_GPIO[52 + idx] = val;
}

/* Active Low */
#define EE_led_0_on()	EE_led_set(0, 0);
#define EE_led_0_off()	EE_led_set(0, 1);
#define EE_led_1_on()	EE_led_set(1, 0);
#define EE_led_1_off()	EE_led_set(1, 1);
#define EE_led_2_on()	EE_led_set(2, 0);
#define EE_led_2_off()	EE_led_set(2, 1);
#define EE_led_3_on()	EE_led_set(3, 0);
#define EE_led_3_off()	EE_led_set(3, 1);

#endif

#ifdef __USE_BUTTONS__

#define BUTTON_0	0U
#define BUTTON_1	1U
#define BUTTON_2	2U
#define BUTTON_3	3U

/* input parameter necessary to guarantee backward compatibility of demos */
__INLINE__ void __ALWAYS_INLINE__ EE_buttons_disable_interrupts(EE_UREG btn)
{
	EE_UINT32 val;

	val = SIU_IRER;

	/* Disable  IRQ_0 IRQ_1 IRQ_2 IRQ_3 */
	SIU_IRER = val & ~0x01010101;
}

/* input parameter necessary to guarantee backward compatibility of demos */
__INLINE__ void __ALWAYS_INLINE__ EE_buttons_enable_interrupts(EE_UREG btn)
{
	EE_UINT32 val;

	val = SIU_IRER;

	/* Eneble IRQ_0 IRQ_1 IRQ_2 IRQ_3 */
	SIU_IRER = val | 0x01010101;
}

/* Clear specific ISR flag associated to a specific button */
__INLINE__ void __ALWAYS_INLINE__ EE_buttons_clear_ISRflag(EE_UREG btn)
{
	EE_UINT32 val;

	/* Save old ISR value */
	val = SIU_ISR;

	if (btn == 0U) {
		SIU_ISR = val | 0x1U;
	}
	else if(btn == 1U) {
		SIU_ISR = val | 0x100U;
	}
	else if(btn == 2U) {
		SIU_ISR = val | 0x10000U;
	}
	else if(btn == 3U) {
		SIU_ISR = val | 0x1000000U;
	}
	else {
		/* button not supported */
	} 
}

/* Get button 0 status */
__INLINE__ EE_UINT32 __ALWAYS_INLINE__ EE_button_get_B0(void)
{
	return !((*(volatile EE_UINT32 *)(SIU_BASE + 0x0800))&0x01000000);
}

/* Get button 1 status */
__INLINE__ EE_UINT32 __ALWAYS_INLINE__ EE_button_get_B1(void)
{
	return !((*(volatile EE_UINT32 *)(SIU_BASE + 0x0808))&0x01000000);
}

/* Get button 2 status */
__INLINE__ EE_UINT32 __ALWAYS_INLINE__ EE_button_get_B2(void)
{
	return !((*(volatile EE_UINT32 *)(SIU_BASE + 0x0810))&0x00010000);
}

/* Get button 3 status */
__INLINE__ EE_UINT32 __ALWAYS_INLINE__ EE_button_get_B3(void)
{
	return !((*(volatile EE_UINT32 *)(SIU_BASE + 0x0824))&0x00000100);
}

/* Buttons initialization */
__INLINE__ void __ALWAYS_INLINE__ EE_buttons_init(void)
{
	EE_UINT32 val;

	/* Enable PRC0/8/17/93 as inputs */
	SIU_PCR0 = 0x100;
	SIU_PCR8 = 0x100;
	SIU_PCR17 = 0x100;
	SIU_PCR38 = 0x100;

	/* Eneble IRQ_0 IRQ_1 IRQ_2 IRQ_3 */
	SIU_IRER = 0x01010101;

	/* Eneble external irqs (0,8,16,24) on falling edge */
	SIU_IREER = 0x01010101;
}

#endif

#endif
