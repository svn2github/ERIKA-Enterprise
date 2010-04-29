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
 * Driver for the parallel/serial IO components of the FPGA+Camera board
 * Author: 2010,  Bernardo  Dal Seno
 */


#ifndef __INCLUDE_FPGA_CAMERA_BOARD_SERIO_H__
#define __INCLUDE_FPGA_CAMERA_BOARD_SERIO_H__

#include <ee.h>
#include <MicoGPIO.h>
#include <system_conf.h>

/* Common stuff */
#ifdef SERPARIO_BASE_ADDRESS

/* Public common stuff */

#define EE_LED_COUNT 10

#define EE_TRANSISTOR_SRAM      0
#define EE_TRANSISTOR_LCD       1
#define EE_TRANSISTOR_FLASH     2
#define EE_TRANSISTOR_DRAM      3
#define EE_TRANSISTOR_CAMERA    4
#define EE_TRANSISTOR_SWITCHES  5
#define EE_TRANSISTOR_EXT_SPI   6

/* Private common stuff */

typedef struct
{
    /* Register to read state of switches and button (RO) */
    volatile EE_UINT32 data_in;
    /* Register to control leds & transistors (R/W) */
    volatile EE_UINT32 data_out;
    /* Status register (R/W) */
    volatile EE_UINT32 status;
} SerParIO_t;

static SerParIO_t * const serpario = (SerParIO_t *)SERPARIO_BASE_ADDRESS;


__INLINE__ EE_UINT32 __ALWAYS_INLINE__ EE_serio_read(void)
{
    return serpario->data_in;
}


__INLINE__ void __ALWAYS_INLINE__ EE_serio_write(EE_UINT32 data)
{
    serpario->data_out = data;
}


__INLINE__ EE_UINT32 __ALWAYS_INLINE__ EE_serio_get_data_out(void)
{
    return serpario->data_out;
}

#define EE_SERIO_SYSTEM_LED 9
#define EE_SERIO_LED_COUNT (EE_LED_COUNT - 1)
#define EE_SERIO_ALL_LEDS ((1 << EE_SERIO_LED_COUNT) - 1)
#define EE_SERIO_LED_MASK(n) (1 << (n))

#define EE_SERIO_SWITCH_MASK(n) (1 << (n))

#define EE_SERIO_TRANSISTOR_MASK(n) (1 << ((n) + EE_SERIO_LED_COUNT))
#define EE_SERIO_ALL_TRANSISTORS (0x7f << EE_SERIO_LED_COUNT)
#else
#error Unsopported platform: no parallel/serial component found
#endif /* SERPARIO_BASE_ADDRESS */


/* Leds */

#ifdef __USE_LEDS__

__DECLARE_INLINE__ void EE_serio_system_led_on(void);
__DECLARE_INLINE__ void EE_serio_system_led_off(void);
__DECLARE_INLINE__ void EE_serio_system_led_toggle(void);
__DECLARE_INLINE__ void EE_serio_system_led_set(EE_UREG s);

__INLINE__ void __ALWAYS_INLINE__ EE_led_on(EE_UREG n)
{
    if (n == EE_SERIO_SYSTEM_LED)
        EE_serio_system_led_on();
    else
        EE_serio_write(EE_serio_get_data_out() | EE_SERIO_LED_MASK(n));
}

__INLINE__ void __ALWAYS_INLINE__ EE_led_off(EE_UREG n)
{
    if (n == EE_SERIO_SYSTEM_LED)
        EE_serio_system_led_off();
    else
        EE_serio_write(EE_serio_get_data_out() & ~EE_SERIO_LED_MASK(n));
}

__INLINE__ void __ALWAYS_INLINE__ EE_led_toggle(EE_UREG n)
{
    if (n == EE_SERIO_SYSTEM_LED)
        EE_serio_system_led_toggle();
    else
        EE_serio_write(EE_serio_get_data_out() ^ EE_SERIO_LED_MASK(n));
}

__INLINE__ void __ALWAYS_INLINE__ EE_led_set_all(EE_INT32 state)
{
    EE_INT32 old = EE_serio_get_data_out();
    EE_serio_write((old & ~EE_SERIO_ALL_LEDS) | (state & EE_SERIO_ALL_LEDS));
    EE_serio_system_led_set(state & (1 << EE_SERIO_SYSTEM_LED));
}


__INLINE__ void __ALWAYS_INLINE__ EE_led_all_off(void)
{
    EE_led_set_all(0);
    EE_serio_system_led_off();
}


__INLINE__ void __ALWAYS_INLINE__ EE_led_all_on(void)
{
    EE_led_set_all(EE_SERIO_ALL_LEDS);
    EE_serio_system_led_on();
}


__INLINE__ void __ALWAYS_INLINE__ EE_led_all_toggle(void)
{
    EE_serio_write(EE_serio_get_data_out() ^ EE_SERIO_ALL_LEDS);
    EE_serio_system_led_toggle();
}

/* Private LED stuff */

EE_UREG EE_serio_system_led_status; /* Gcc merges all these definitions */

#define EE_SERIO_GPIO_LED_MASK 1
__INLINE__ void __ALWAYS_INLINE__ EE_serio_system_led_set(EE_UREG s)
{
    MicoGPIO_t * const led_io = (MicoGPIO_t *)MISC_GPIO_BASE_ADDRESS;
    EE_serio_system_led_status = s;
    led_io->data = s ? EE_SERIO_GPIO_LED_MASK : 0;
    #warning The current LED driver interferes with networking pins
}
__INLINE__ void __ALWAYS_INLINE__ EE_serio_system_led_on(void)
{
    EE_serio_system_led_set(1);
}
__INLINE__ void __ALWAYS_INLINE__ EE_serio_system_led_off(void)
{
    EE_serio_system_led_set(0);
}

__INLINE__ void __ALWAYS_INLINE__ EE_serio_system_led_toggle(void)
{
    EE_serio_system_led_set (! EE_serio_system_led_status);
}


#endif /* __USE_LEDS__ */


/* Switches & button */

#ifdef __USE_SWITCHES__

__INLINE__ EE_UINT32 __ALWAYS_INLINE__ EE_switch_read_all(void)
{
    return EE_serio_read();
}

__INLINE__ EE_UINT32 __ALWAYS_INLINE__ EE_switch_read(EE_UREG n)
{
    return (EE_serio_read() & EE_SERIO_SWITCH_MASK(n)) != 0;
}

#endif /* __USE_SWITCHES__ */


/* Transistors */

#ifdef __USE_TRANSISTORS__

/* Transistors are controlled with negative logic, with the exception of the
 * one powering the switch array. */

__INLINE__ void __ALWAYS_INLINE__ EE_transistor_on(EE_UREG n)
{
    if (n != EE_TRANSISTOR_SWITCHES)
        EE_serio_write(EE_serio_get_data_out() & ~EE_SERIO_TRANSISTOR_MASK(n));
    else
        EE_serio_write(EE_serio_get_data_out() | EE_SERIO_TRANSISTOR_MASK(n));
}

__INLINE__ void __ALWAYS_INLINE__ EE_transistor_off(EE_UREG n)
{
    if (n != EE_TRANSISTOR_SWITCHES)
        EE_serio_write(EE_serio_get_data_out() | EE_SERIO_TRANSISTOR_MASK(n));
    else
        EE_serio_write(EE_serio_get_data_out() & ~EE_SERIO_TRANSISTOR_MASK(n));
}

__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_transistor_read(EE_UREG n)
{
    unsigned sw;
    sw = EE_serio_get_data_out() & EE_SERIO_TRANSISTOR_MASK(n);
    if (n != EE_TRANSISTOR_SWITCHES)
        return sw == 0;
    else
        return sw == 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_transistor_all_on(void)
{
    EE_serio_write((EE_serio_get_data_out() & ~EE_SERIO_ALL_TRANSISTORS)
        | EE_SERIO_TRANSISTOR_MASK(EE_TRANSISTOR_SWITCHES));
}

__INLINE__ void __ALWAYS_INLINE__ EE_transistor_all_off(void)
{
    EE_serio_write((EE_serio_get_data_out() | EE_SERIO_ALL_TRANSISTORS)
        & ~EE_SERIO_TRANSISTOR_MASK(EE_TRANSISTOR_SWITCHES));
}

#endif /* __USE_TRANSISTORS__ */

#endif /* __INCLUDE_FPGA_CAMERA_BOARD_SERIO_H__ */
