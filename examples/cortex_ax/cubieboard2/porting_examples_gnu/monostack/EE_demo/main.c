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

volatile int counter_task1 = 0;
volatile int counter_task2 = 0;
volatile int led_timer = 0;
volatile int led_active = 0;

ISR2(Timer_isr2)
{
    ActivateTask(Blinking_led_task);
    ActivateTask(Saw_tooth_task);
}

#define TICKS_IN_SEC 20
//extern EE_IO_BUFFER clk_buffer;
static void EE_timer_init()
{
#if 0
  /* help to find clock mismatch */
  unsigned int clk;
  clk = (unsigned int)EE_imx6_get_arm_clock();
  buffer_out_write(&clk_buffer, (char*)&clk,
                   sizeof(clk));
#endif
/*
 *     (pre + 1) * (load + 1)
 * T = ----------------------
 *            per_clk
 *
 * per_clk = arm_clk / N
 * for imx6, N = 2 ???
 *
 */
    /* pre value */
    EE_private_timer_set_prescaler(249);
    /* load value */
//  EE_private_timer_set_load(5279);    // T = 0.004s (1/250)
//  EE_private_timer_set_load(2639);    // T = 0.002s (1/500)
    EE_private_timer_set_load(65999);   // T = 0.05s
//  EE_private_timer_set_load(13199);   // T = 0.01s
//  EE_private_timer_set_load(131999);  // T = 0.1s
//  EE_private_timer_set_load(1320000); // T = 1.0s
//  EE_private_timer_set_load(659999);  // T = 0.5s
    EE_private_timer_enable(EE_PRIVATE_TIMER_INT | EE_PRIVATE_TIMER_AUTORELOAD);
}

#define LED_ON_TIME (1)
extern EE_IO_BUFFER led_status;
TASK(Blinking_led_task)
{
    int led = 1;

    if (!led_active) {
        return;
    }

    if (led_timer == 0) {
        led = 0;
        buffer_out_write(&led_status, (char*)&led, sizeof(led));
    }

    ++led_timer;

    if (led_timer > LED_ON_TIME * TICKS_IN_SEC) {
        led = 1;
        led_timer = 0;
        buffer_out_write(&led_status, (char*)&led, sizeof(led));
        led_active = 0;
    }
}

TASK(Activate_led_task)
{
    if (led_active == 0)
        led_active = 1;
}

extern EE_IO_BUFFER saw_tooth_data;
extern EE_IO_BUFFER saw_tooth_data_max;
static unsigned int saw_tooth_min = 100;
static unsigned int saw_tooth_max = 150;
static unsigned int saw_tooth = 100;
TASK(Saw_tooth_task)
{
    /* 99:59 -- mins:secs */
    static char timer[7] = "00:00\r";
    static int cpu_time = TICKS_IN_SEC;
    unsigned int tmp;

    ++counter_task2;
    if (buffer_out_read(&saw_tooth_data_max, (char*)&tmp,
                        sizeof(tmp)) == sizeof(tmp)) {
        if (tmp > saw_tooth_min)
            saw_tooth_max = tmp;
    }

    ++saw_tooth;

    if (saw_tooth > saw_tooth_max)
        saw_tooth = saw_tooth_min;

    buffer_out_write(&saw_tooth_data, (char*)&saw_tooth,
                     sizeof(saw_tooth));


    ++cpu_time;
    if (cpu_time < TICKS_IN_SEC) {
        return;
    }

    cpu_time = 0;

//    EE_serial_puts(timer);

    ++timer[4];
    if (timer[4] > '9') {
        timer[4] = '0';
        ++timer[3];
        if (timer[3] > '5') {
            timer[3] = '0';
            ++timer[1];
            if (timer[1] > '9') {
                timer[1] = '0';
                ++timer[0];
                if (timer[0] > '9')
                    timer[0] = '0';
            }
        }
    }
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
    EnableAllInterrupts();
    EE_assert(1, TRUE, EE_ASSERT_NIL);

    StartOS(OSDEFAULTAPPMODE);

//    EE_serial_puts("GO!\n\n");
    EE_timer_init();
    //ActivateTask(Task1);

    EE_assert(6, counter_task1==1 && counter_task2==1, 5);

    EE_assert_range(0,1,6);
    result = EE_assert_last();

    // Forever loop: background activities (if any) should go here
    for (;;) ;

    return 0;
}
