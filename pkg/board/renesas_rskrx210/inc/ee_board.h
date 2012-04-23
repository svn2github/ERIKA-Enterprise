/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2012  Evidence Srl
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

 /**
    @file   ee_board.h
    @brief  stellaris board header file.

    Header file that contains board's API declaration, and defines
    for remap mcu drivers on board layout.

    @author Gianluca Franchino
    @date   2012
  */

#ifndef __INCLUDE_RENESAS_RSKRX210_BOARD_H__
#define __INCLUDE_RENESAS_RSKRX210_BOARD_H__

#include "mcu/renesas_r5f5210x/inc/ee_mcu.h"

/*
 * User Led
 */

#ifdef __USE_RSKRX120_USER_LED__
#ifdef __CCRX__
#pragma inline (EE_rskrx210_leds_init)
#endif
/** @brief Initialize board leds defined by mask */
__INLINE__  void EE_rskrx210_leds_init(EE_UINT8 mask)
{
	if (mask & 0x1)
		PORT1.PDR.BIT.B4 = 1;
	if (mask & 0x2)
		PORT1.PDR.BIT.B5 = 1;
	if (mask & 0x4)
		PORT1.PDR.BIT.B6 = 1;
	if (mask & 0x8)
		PORT1.PDR.BIT.B7 = 1;
}
#ifdef __CCRX__
#pragma inline (EE_rskrx210_leds_on)
#endif
/** @brief User leds on **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_leds_on(void)
{
	PORT1.PODR.BIT.B4 = 0;
	PORT1.PODR.BIT.B5 = 0;
	PORT1.PODR.BIT.B6 = 0;
	PORT1.PODR.BIT.B7 = 0;	
}

#ifdef __CCRX__
#pragma inline (EE_rskrx210_leds_off)
#endif
/** @brief User leds off **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_leds_off(void)
{
	PORT1.PODR.BIT.B4 = 1;
	PORT1.PODR.BIT.B5 = 1;
	PORT1.PODR.BIT.B6 = 1;
	PORT1.PODR.BIT.B7 = 1;	
}

#ifdef __CCRX__
#pragma inline (EE_rskrx210_leds_toggle)
#endif
/** @brief User leds toggle **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_leds_toggle(void)
{
	PORT1.PODR.BIT.B4 = PORT1.PODR.BIT.B4 ^ 1;
	PORT1.PODR.BIT.B5 = PORT1.PODR.BIT.B5 ^ 1;
	PORT1.PODR.BIT.B6 = PORT1.PODR.BIT.B6 ^ 1;
	PORT1.PODR.BIT.B7 = PORT1.PODR.BIT.B7 ^ 1;
}

#ifdef __CCRX__
#pragma inline (EE_rskrx210_led0_on)
#endif
/** @brief User led0 on **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_led0_on(void)
{
	PORT1.PODR.BIT.B4 = 0;
}
#ifdef __CCRX__
#pragma inline (EE_rskrx210_led0_off)
#endif
/** @brief User led0 off **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_led0_off(void)
{
	PORT1.PODR.BIT.B4 = 1;
}
#ifdef __CCRX__
#pragma inline (EE_rskrx210_led0_toggle)
#endif
/** @brief User led0 toggle **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_led0_toggle(void)
{
	PORT1.PODR.BIT.B4 =  PORT1.PODR.BIT.B4 ^ 1;
}

#ifdef __CCRX__
#pragma inline (EE_rskrx210_led1_on)
#endif
/** @brief User led1 on **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_led1_on(void)
{
	PORT1.PODR.BIT.B5 = 0;
}
#ifdef __CCRX__
#pragma inline (EE_rskrx210_led1_off)
#endif
/** @brief User led1 off **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_led1_off(void)
{
	PORT1.PODR.BIT.B5 = 1;
}

#ifdef __CCRX__
#pragma inline (EE_rskrx210_led1_toggle)
#endif
/** @brief User led1 toggle **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_led1_toggle(void)
{
	PORT1.PODR.BIT.B5 =  PORT1.PODR.BIT.B5 ^ 1;
}

#ifdef __CCRX__
#pragma inline (EE_rskrx210_led2_on)
#endif
/** @brief User led2 on **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_led2_on(void)
{
	PORT1.PODR.BIT.B6 = 0;
}

#ifdef __CCRX__
#pragma inline (EE_rskrx210_led2_off)
#endif
/** @brief User led2 off **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_led2_off(void)
{
	PORT1.PODR.BIT.B6 = 1;
}

#ifdef __CCRX__
#pragma inline (EE_rskrx210_led2_toggle)
#endif
/** @brief User led2 toggle **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_led2_toggle(void)
{
	PORT1.PODR.BIT.B6 =  PORT1.PODR.BIT.B6 ^ 1;
}
#ifdef __CCRX__
#pragma inline (EE_rskrx210_led3_on)
#endif
/** @brief User led3 on **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_led3_on(void)
{
	PORT1.PODR.BIT.B7 = 0;
}
#ifdef __CCRX__
#pragma inline (EE_rskrx210_led3_off)
#endif
/** @brief User led3 off **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_led3_off(void)
{
	PORT1.PODR.BIT.B7 = 1;
}
#ifdef __CCRX__
#pragma inline (EE_rskrx210_led3_toggle)
#endif
/** @brief User led3 toggle **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_led3_toggle(void)
{
	PORT1.PODR.BIT.B7 =  PORT1.PODR.BIT.B7 ^ 1;
}

#endif /* __USE_RSKRX120_USER_LED__ */

#ifdef __USE_RSKRX120_BUTTONS__
#ifdef __CCRX__
#pragma inline (EE_rskrx210_buttons_pins_init)
#endif

/** @brief Buttons initialization **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_buttons_pins_init(EE_UINT8 mask)
{
	if (mask & 0x1)
		PORT3.PDR.BIT.B1 = 0;
	if (mask & 0x2)
		PORT3.PDR.BIT.B3 = 0;
	if (mask & 0x4)
		PORT3.PDR.BIT.B4 = 0;
}

#ifdef __CCRX__
#pragma inline (EE_rskrx210_buttons_IRQ_init)
#endif
/** @brief Initialize board buttons ISRs as defined by mask */	
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_buttons_IRQ_init(EE_UINT8 mask)
{
	if (mask & 0x1) {
		
		MPC.PWPR.BIT.B0WI = 0;
		MPC.PWPR.BIT.PFSWE = 1;
		/*Set IRQ1 enabled on Multi-function Pin Controller*/
		MPC.P31PFS.BIT.ISEL = 1;
		MPC.PWPR.BIT.PFSWE = 0;
		MPC.PWPR.BIT.B0WI = 1;
		/*Set IRQ1 interrupt priority to level 1 */
		ICU.IPR[IR_ICU_IRQ1].BIT.IPR = 0x1;
		/*Enable IRQ1 interrupt in ICU*/
		ICU.IER[IER_ICU_IRQ1].BIT.IEN_ICU_IRQ1 = 1;
	}
	if (mask & 0x2) {
		MPC.PWPR.BIT.B0WI = 0;
		MPC.PWPR.BIT.PFSWE = 1;
		/*Set IRQ1 enabled on Multi-function Pin Controller*/
		MPC.P33PFS.BIT.ISEL = 1;
		MPC.PWPR.BIT.PFSWE = 0;
		MPC.PWPR.BIT.B0WI = 1;
		/*Set IRQ3 interrupt priority to level 1 */
		ICU.IPR[IR_ICU_IRQ3].BIT.IPR = 0x1;
		/*Enable IRQ3 interrupt in ICU*/
		ICU.IER[IER_ICU_IRQ3].BIT.IEN_ICU_IRQ3 = 1;
	}
	if (mask & 0x4) {
		MPC.PWPR.BIT.B0WI = 0;
		MPC.PWPR.BIT.PFSWE = 1;	
		MPC.P34PFS.BIT.ISEL = 1;
		MPC.PWPR.BIT.PFSWE = 0;
		MPC.PWPR.BIT.B0WI = 1;		
		/*Set IRQ4 interrupt priority to level 1 */
		ICU.IPR[IR_ICU_IRQ4].BIT.IPR = 0x1;
		/*Enable IRQ interrupt in ICU*/
		ICU.IER[IER_ICU_IRQ4].BIT.IEN_ICU_IRQ4 = 1;
	}
}

#ifdef __CCRX__
#pragma inline (EE_b1_not_pressed)
#endif
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_b1_not_pressed(void)
{
	 return PORT3.PIDR.BIT.B1;
}

#ifdef __CCRX__
#pragma inline (EE_b2_not_pressed)
#endif
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_b2_not_pressed(void)
{
	 return PORT3.PIDR.BIT.B3;
}

#ifdef __CCRX__
#pragma inline (EE_b3_not_pressed)
#endif
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_b3_not_pressed(void)
{
	 return PORT3.PIDR.BIT.B4;
}

#ifdef __CCRX__
#pragma inline (EE_b1_disable_IRQ)
#endif
__INLINE__ void __ALWAYS_INLINE__ EE_b1_disable_IRQ(void)
{
	 	ICU.IER[IER_ICU_IRQ1].BIT.IEN_ICU_IRQ1 = 0;
}

#ifdef __CCRX__
#pragma inline (EE_b1_enable_IRQ)
#endif
__INLINE__ void __ALWAYS_INLINE__ EE_b1_enable_IRQ(void)
{
	 	ICU.IER[IER_ICU_IRQ1].BIT.IEN_ICU_IRQ1 = 1;
}

#ifdef __CCRX__
#pragma inline (EE_b2_disable_IRQ)
#endif
__INLINE__ void __ALWAYS_INLINE__ EE_b2_disable_IRQ(void)
{
	ICU.IER[IER_ICU_IRQ3].BIT.IEN_ICU_IRQ3 = 0;
}

#ifdef __CCRX__
#pragma inline (EE_b2_enable_IRQ)
#endif
__INLINE__ void __ALWAYS_INLINE__ EE_b2_enable_IRQ(void)
{
	ICU.IER[IER_ICU_IRQ3].BIT.IEN_ICU_IRQ3 = 1;
}

#ifdef __CCRX__
#pragma inline (EE_b3_disable_IRQ)
#endif
__INLINE__ void __ALWAYS_INLINE__ EE_b3_disable_IRQ(void)
{
	ICU.IER[IER_ICU_IRQ4].BIT.IEN_ICU_IRQ4 = 0;
}

#ifdef __CCRX__
#pragma inline (EE_b3_enable_IRQ)
#endif
__INLINE__ void __ALWAYS_INLINE__ EE_b3_enable_IRQ(void)
{
	ICU.IER[IER_ICU_IRQ4].BIT.IEN_ICU_IRQ4 = 1;
}


#endif /* __USE_RSKRX120_BUTTONS__ */

#endif /*__INCLUDE_RENESAS_RSKRX210_BOARD_H__ */
