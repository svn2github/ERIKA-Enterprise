/*
 * ERIKA Enterprise Basic - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2007  Evidence Srl
 *
 * This file is part of ERIKA Enterprise Basic.
 *
 * ERIKA Enterprise Basic is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * ERIKA Enterprise Basic is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise Basic; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 */

/*
 * Author: 2009, Dario Di Stefano
 */

#include "stdlib.h"
#include <math.h>
#include "ee.h"
#include "cpu/cosmic_hs12xs/inc/ee_irqstub.h"
#include "ee_hs12xsregs.h"


int counter = 0;

TASK(Task1)
{
    counter++;
}

/*
 * MAIN TASK
*/
int main(void)
{
	ActivateTask(Task1);
	// Forever loop: background activities (if any) should go here
	for (;;);

}

