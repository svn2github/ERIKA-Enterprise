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

 /**
    @file   ee_board.h
    @brief  stellaris board header file.

    Header file taht contains board's API declaration, and defines
    for remap mcu drivers on board layout.

    @author Giuseppe Serano
    @date   2011
  */

#ifndef __INCLUDE_STELLARIS_LM4F232XXXX_BOARD_H__
#define __INCLUDE_STELLARIS_LM4F232XXXX_BOARD_H__

#include "mcu/ti_stellaris_lm4f232xxxx/inc/ee_mcu.h"

/*
 * User Led
 */

#ifdef __USE_USER_LED__

/** @brief User led initialization **/
__INLINE__ void __ALWAYS_INLINE__ EE_user_led_init(void)
{
    volatile register EE_UREG tmp;

    //
    // Enable the GPIO port that is used for the on-board LED.
    //
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOG;

    //
    // Do a dummy read to insert a few cycles after enabling the peripheral.
    //
    tmp = SYSCTL_RCGC2_R;

    //
    // Enable the GPIO pin for the LED (PG2).  Set the direction as output, and
    // enable the GPIO pin for digital function.
    //
    GPIO_PORTG_DIR_R = 0x04;
    GPIO_PORTG_DEN_R = 0x04;

}

/** @brief User led on **/
__INLINE__ void __ALWAYS_INLINE__ EE_user_led_on(void)
{
    GPIO_PORTG_DATA_R |= 0x04;
}

/** @brief User_led_off **/
__INLINE__ void __ALWAYS_INLINE__ EE_user_led_off(void)
{
    GPIO_PORTG_DATA_R &= ~(0x04);
}

/** @brief User led toggle **/
__INLINE__ void __ALWAYS_INLINE__ EE_user_led_toggle(void)
{
    GPIO_PORTG_DATA_R ^= 0x04;
}

#endif /* __USE_USER_LED__ */

#endif /*__INCLUDE_STELLARIS_LM4F232XXXX_BOARD_H__ */
