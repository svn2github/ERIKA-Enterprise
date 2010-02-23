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
 * Simple project to test the all the context changes; it measure the time
 * used for different types of context changes.  Multistack, FP kernel.
 * Author: 2010,  Bernardo  Dal Seno
 */


#include <ee.h>
/* Platform description */
#include <system_conf.h>
/* Lattice Timer component */
#include <MicoTimer.h>
/* Erika Mico32 interrupts */
#include <cpu/mico32/inc/ee_irq.h>
/* Assertions */
#include "test/assert/inc/ee_assert.h"

/* For time measurements */
#include "timing.h"

/* started: Set to 1 at the beginning of main() */
int started;


/* Assertions */
EE_TYPEASSERTVALUE EE_assertions[16];
/* Final result */
EE_TYPEASSERTVALUE result;


/* Event time instants */
volatile timer_t t2_before_irq1, th_caught_irq, th_end_irq, t2_before_irq2,
t3_start_finish, t2_finish, t1_before_t5, t5_finish, t4_finish;

/* Context change timing */
timer_t irq_call1, irq_call2, irq_return, irq_new_task, end_task_after_irq,
end_task_new_task1, activate_new_task1, end_task1, activate_new_task2,
end_task_new_task2, end_task2;
/* The last three are for context changes that do not involve stack switching */

/*
 * Event sequence:
 
 T2 starts
 IRQ fires; ISR activates T1
 IRQ fires; ISR activates T3
 T3 starts and terminates
 T2 terminates
 T1 starts
 T1 activates T3
 T3 starts and terminates
 T1 activates T5
 T5 starts
 T5 activates T4
 T5 terminates
 T4 starts and terminates
 T1 terminates
 
 */


/* Not an Osek kernel: no TeminateTask() */
#define TerminateTask()


/***********************
 * Interrupts
 ***********************/


/*
 * Raise an interrupt immediately
 */
void fire_irq(void)
{
    MicoTimer_t *timerc = (MicoTimer_t *)TIMER_BASE_ADDRESS;
    timerc->Control = MICO32_TIMER_CONTROL_START_BIT_MASK |
        MICO32_TIMER_CONTROL_INT_BIT_MASK;
    /* Read the register again, to be sure that the interrupt fires
       before returning from the function */
    (void)(timerc->Control);
}


/*
 * Acknowledge the interrupt
 */
void acknowledge_interrupt(void)
{
    MicoTimer_t *timerc = (MicoTimer_t *)TIMER_BASE_ADDRESS;
    timerc->Status = 0;
}


/*
 * Low-level initialization of the interrupts
 */
void init_interrupts(void)
{
    MicoTimer_t *timerc = (MicoTimer_t *)TIMER_BASE_ADDRESS;
    /* Register handler and enable the interrupt */
    void interrupt_handler(int level);
    EE_mico32_register_ISR(TIMER_IRQ, interrupt_handler);
    EE_mico32_enableIRQ();
    /* Raise an interrupt 1 clock tick after the start command */
    timerc->Period = 1;
    timerc->Control = MICO32_TIMER_CONTROL_INT_BIT_MASK;
}


/*
 * Interrupt handler
 */
void interrupt_handler(int level)
{
    th_caught_irq = get_current_time();
    acknowledge_interrupt();
    if (t2_before_irq2 == 0) {
        /* First firing */
        EE_assert(3, 1, 2);
        irq_call1 = time_diff(t2_before_irq1, th_caught_irq);
        ActivateTask(Task1);
        EE_assert(4, 1, 3);
    } else {
        /* Second firing */
        EE_assert(6, 1, 5);
        irq_call2 = time_diff(t2_before_irq2, th_caught_irq);
        ActivateTask(Task3);
        EE_assert(7, t3_start_finish == 0, 6);
    }
    th_end_irq = get_current_time();
}


/***********************
 * Tasks
 ***********************/


/*
 * Task 1
 */
TASK(Task1)
{
    timer_t t, tprev, t3;
    t = get_current_time();
    end_task_new_task1 = time_diff(t2_finish, t);
    EE_assert(9, 1, 8);
    EE_assert(10, t3_start_finish == 0, EE_ASSERT_NIL);
    tprev = get_current_time();
    ActivateTask(Task3);
    t = get_current_time();
    t3 = t3_start_finish;
    end_task1 = time_diff(t3, t);
    activate_new_task1 = time_diff(tprev, t3);
    EE_assert(11, t3 != 0, 10);
    t1_before_t5 = get_current_time();
    ActivateTask(Task5);
    t = get_current_time();
    end_task2 = time_diff(t4_finish, t);
    EE_assert(15, 1, 14);
    TerminateTask();
}


/*
 * Task 2
 */
TASK(Task2)
{
    timer_t t, t3;
    EE_assert(2, 1, 1);
    t2_before_irq1 = get_current_time();
    fire_irq();
    t = get_current_time();
    irq_return = time_diff(th_end_irq, t);
    EE_assert(5, 1, 4);
    t2_before_irq2 = get_current_time();
    fire_irq();
    t = get_current_time();
    t3 = t3_start_finish;
    irq_new_task = time_diff(th_end_irq, t3);
    end_task_after_irq = time_diff(t3, t);
    EE_assert(8, t3 != 0, 7);
    t3_start_finish = 0; // Reset t3 time for another assertion
    t2_finish = get_current_time();
    TerminateTask();
}


/*
 * Task 3
 */
TASK(Task3)
{
    t3_start_finish = get_current_time();
    TerminateTask();
}


/*
 * Task 4
 */
TASK(Task4)
{
    timer_t t;
    t = get_current_time();
    end_task_new_task2 = time_diff(t5_finish, t);
    EE_assert(14, 1, 13);
    t4_finish = get_current_time();
    TerminateTask();
}


/*
 * Task 5
 */
TASK(Task5)
{
    timer_t t;
    t = get_current_time();
    activate_new_task2 = time_diff(t1_before_t5, t);
    EE_assert(12, 1, 11);
    ActivateTask(Task4);
    EE_assert(13, 1, 12);
    t5_finish = get_current_time();
    TerminateTask();
}


/*
 * MAIN TASK
 */
int main(void)
{
    started = 1;
    EE_assert(1, 1, EE_ASSERT_NIL);
    init_interrupts();
    ActivateTask(Task2);
    EE_assert_range(0, 1, 15);
    result = EE_assert_last();
    started = 0;
    return 0;
}
