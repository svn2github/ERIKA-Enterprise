/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
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
 * Author: 2001-2002 Alessandro Colantonio, 2002- Paolo Gai
 * CVS: $Id: ee_board.h,v 1.4 2006/04/08 21:07:19 pj Exp $
 */

#ifndef __INCLUDE_UNIBO_MPARM_BOARD_H__
#define __INCLUDE_UNIBO_MPARM_BOARD_H__

#include "mcu/unibo_mparm/inc/ee_mcu.h"


// TODO: Change According to MPARM!!!

/*************************************************************************
 Button
 *************************************************************************/

/* the button is connected to EXT0 */

#ifdef __BUTTON_USED__

/* Initialize the EXT0 interrupt source (button)  */
__INLINE__ void __ALWAYS_INLINE__ EE_button_init(void)
{
    *IOPCON |= IO_ENABLE_EXT0;
    *IOPCON |= IO_ACTIVE_HIGH_EXT0;
    *IOPCON |= IO_RISING_EDGE_EXT0;
}

#endif


/*************************************************************************
 LEDs
 *************************************************************************/

#ifdef __LEDS_USED__

/* On Evaluator7T, the LEDs are connected through IO Port 
 * LED1 is Green, LED2 is Red, LED3 is Yellow, LED4 is Green */

__INLINE__ void __ALWAYS_INLINE__ EE_led_4_on(void) {*IOPDATA |= 16;}
__INLINE__ void __ALWAYS_INLINE__ EE_led_3_on(void) {*IOPDATA |= 32;}
__INLINE__ void __ALWAYS_INLINE__ EE_led_2_on(void) {*IOPDATA |= 64;}
__INLINE__ void __ALWAYS_INLINE__ EE_led_1_on(void) {*IOPDATA |= 128;}

__INLINE__ void __ALWAYS_INLINE__ EE_led_4_off(void) {*IOPDATA &= ~16;}
__INLINE__ void __ALWAYS_INLINE__ EE_led_3_off(void) {*IOPDATA &= ~32;}
__INLINE__ void __ALWAYS_INLINE__ EE_led_2_off(void) {*IOPDATA &= ~64;}
__INLINE__ void __ALWAYS_INLINE__ EE_led_1_off(void) {*IOPDATA &= ~128;}

__INLINE__ void __ALWAYS_INLINE__ EE_leds_init(void) {*IOPDATA &= ~(128+64+32+16);}

#endif /* __LEDS_USED__ */


#endif
