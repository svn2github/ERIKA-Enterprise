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

#ifndef TRUE
#define TRUE  1U
#endif

#ifndef FALSE
#define FALSE 0U
#endif

DeclareTask(Task1);

void delay(unsigned int value)
{
        volatile int i=0;
        for (i=0; i<value; i++)
                ;
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

void main(void)
{
	StartOS(OSDEFAULTAPPMODE);
}

