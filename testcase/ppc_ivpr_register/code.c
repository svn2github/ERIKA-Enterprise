/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.  ERIKA Enterprise is free software;
 * you can redistribute it and/or modify it under the terms of the
 * GPLv2 + Linking Exception license (contained in the file `ee/LICENSE').
 *
 * ERIKA Enterprise is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the license for more details.
 *
 * ###*E*### */

/*
 * Author: Francesco Esposito
 * date: 2013 - February
 * Description: test added in order to fix a bug found in PPC IVPR register
 * configuration. Such a bug was fixed in release "r2647" on Feb-2013.
 * Details can be found in the repository commit message. This test checks the
 * correctness of the content of IVPR in a particular context (when vector base
 * address has a negative 16-bit low part value, e.g.: 0x00008YYY). This test
 * deliberately places isr base vector in a location greater then 0x40008000
 * (by using a custom linker script) to cause the critic scenario and 
 * performs a test on the content of IVPR.
 */

#include <ee.h>
#include <ee_irq.h>
#include "test/assert/inc/ee_assert.h"

EE_TYPEASSERTVALUE EE_assertions[3];

#define TRUE  1U
#define FALSE 0U

DeclareTask(Task1);

void mpc5674f_stm_freeze_on(void);
void mpc5674f_stm_freeze_off(void);
void mpc5674f_stm_set_prescaler(unsigned int val);
void mpc5674f_stm_select_channel(unsigned int ch);
void mpc5674f_stm_unselect_channel(unsigned int ch);
void mpc5674f_stm_channel_cmp(unsigned int ch, unsigned int val);
void mpc5674f_stm_clear_int(unsigned int ch);
void mpc5674f_stm_set_counter(unsigned int val);
void mpc5674f_stm_enable(void);
void mpc5674f_stm_disable(void);


void delay(unsigned int value)
{
        volatile int i=0;
        for (i=0; i<value; i++)
                ;
}

void alert_stm(void)
{
        /* perform a dummy activity */
        ActivateTask(Task1);

        /* clear request */
        mpc5674f_stm_clear_int(0);

          /* stop timer */
        mpc5674f_stm_disable();

        /* enable channel 0 to raise a new interrupt*/
        mpc5674f_stm_select_channel(0);

        /* initial counter value (equal to 0) */
        mpc5674f_stm_set_counter(0);

        /* start timer */
        mpc5674f_stm_enable();
}

static void init_stm_timer(void)
{
        /* register isr */
        EE_e200z7_register_ISR(216, alert_stm, 15);

        /* freeze anabled */
        mpc5674f_stm_freeze_on();

        /* set prescaler to 0x0 */
        mpc5674f_stm_set_prescaler(1);

        /* set compare register to 0x400000 */
        mpc5674f_stm_channel_cmp(0,0x400000);

        /* enable channel 0 */
        mpc5674f_stm_select_channel(0);

        /* initial counter value */
        mpc5674f_stm_set_counter(0);

        /* start timer */
        mpc5674f_stm_enable();
}

__asm static EE_UREG get_IVPR(void)
{
! "r3"
	mfspr	r3, ivpr
}

__asm static EE_UREG get_IVOR0(void)
{
! "r3"
	mfspr	r3, ivor0
}

TASK(Task1)
{
    static unsigned char first_time = 0x0U;

    /* Init variables used to check the content of ivpr and ivor0 */
    EE_UREG ivpr = 0xFFFFFFFFU;
    EE_UREG ivor0 = 0xFFFFFFFFU;

    if (first_time == 0U) {
        EE_assert(1, TRUE, EE_ASSERT_NIL);
    }

	delay(1000);

    /* Get IVPR */
    ivpr = get_IVPR();

    /* Get IVOR0 */
    ivor0 = get_IVOR0();

    if (first_time == 0U) {
        /*
         * Check if IVPR is as expected
         * We expect the higher 16-bit part of ivpr == 0x4000
         * and the lower 16-bit part of ivor0 being
         * negative (16-th bit set to 1, e.g.: 0x8YYY)
         */
        EE_assert(2, ((ivpr>>16)==0x4000) && ((ivor0 & 0x8000) == 0x8000), 1);

        EE_assert_range(0,1,2);
        EE_assert_last();

        /* Execute this test the only first time */
        first_time = 1U;
    }
}

void main(void)
{
    init_stm_timer();
	StartOS(OSDEFAULTAPPMODE);
}

void mpc5674f_stm_freeze_on(void)
{
        STM.CR.B.FRZ = 1;
}

void mpc5674f_stm_freeze_off(void)
{
        STM.CR.B.FRZ = 0;
}

void mpc5674f_stm_set_prescaler(unsigned int val)
{
        STM.CR.B.CPS = val-1;
}

void mpc5674f_stm_select_channel(unsigned int ch)
{
        if (ch == 0) {
                STM.CCR0.B.CEN = 1;
        }
        else if (ch == 1) {
                STM.CCR1.B.CEN = 1;
        }
        else if (ch == 2) {
                STM.CCR2.B.CEN = 1;
        }
        else if (ch == 3) {
                STM.CCR3.B.CEN = 1;
        }
}

void mpc5674f_stm_unselect_channel(unsigned int ch)
{
        if (ch == 0) {
                STM.CCR0.B.CEN = 0;
        }
        else if (ch == 1) {
                STM.CCR1.B.CEN = 0;
        }
        else if (ch == 2) {
                STM.CCR2.B.CEN = 0;
        }
        else if (ch == 3) {
                STM.CCR3.B.CEN = 0;
        }
}

void mpc5674f_stm_channel_cmp(unsigned int ch, unsigned int val)
{
        if (ch == 0) {
                STM.CMP0.R = val;
        }
        else if (ch == 1) {
                STM.CMP1.R = val;
        }
        else if (ch == 2) {
                STM.CMP2.R = val;
        }
        else if (ch == 3) {
                STM.CMP3.R = val;
        }
}

void mpc5674f_stm_clear_int(unsigned int ch)
{
        if (ch == 0) {
                STM.CIR0.B.CIF = 1;
        }
        else if (ch == 1) {
                STM.CIR1.B.CIF = 1;
        }
        else if (ch == 2) {
                STM.CIR2.B.CIF = 1;
        }
        else if (ch == 3) {
                STM.CIR3.B.CIF = 1;
        }
}

void mpc5674f_stm_set_counter(unsigned int val)
{
        STM.CNT.R = val;
}

void mpc5674f_stm_enable(void)
{
        STM.CR.B.TEN = 1;
}

void mpc5674f_stm_disable(void)
{
        STM.CR.B.TEN = 0;
}

