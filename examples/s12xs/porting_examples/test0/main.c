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
 * Author: 2009 Francesco Prosperi, Dario Di Stefano
 */

#include "stdlib.h"
#include <math.h>
//#include <time.h>

#include "ee.h"

#include "cpu/cosmic_hs12xs/inc/ee_irqstub.h"
//#include "mcu/cosmic_hs12xs/inc/ee_uart.h"
#include "ee_hs12xsregs.h"

//EE_FREG DISICNT = 0;


#define active_wait {int kk=0;for(kk=0;kk<10;kk++);}

int counter = 0;

/* Program the Timer1 peripheral to raise interrupts */
void T1_program(void)
{
//	T1CON = 0;		/* Stops the Timer1 and reset control reg	*/
//	TMR1  = 0;		/* Clear contents of the timer register	*/
//	PR1 = 8000;
//	IPC0bits.T1IP = 5;	/* Set Timer1 priority to 1		*/
//	IFS0bits.T1IF = 0;	/* Clear the Timer1 interrupt status flag	*/
//	IEC0bits.T1IE = 1;	/* Enable Timer1 interrupts		*/
//	T1CONbits.TON = 1;	/* Start Timer1 with prescaler settings at 1:1  and clock source set to the internal  instruction cycle */
}

/* Clear the Timer1 interrupt status flag */
void T1_clear(void)
{
	//IFS0bits.T1IF = 0;
}

/* This is an ISR Type 2 which is attached to the Timer 1 peripheral IRQ pin
 * The ISR simply calls CounterTick to implement the timing reference
 */
ISR2(_T1Interrupt)
{
	// clear the interrupt source
	T1_clear();
	// count the interrupts, waking up expired alarms
	//CounterTick(DUMMY_COUNTER);
}

//TASK(TASK_SEND)
//{
//    counter++;
//}

/*
 * MAIN TASK
*/
int main(void)
{
	//srand((unsigned)time(NULL));

	active_wait;
	active_wait;
	active_wait;
	
	/* Program Timer 1 to raise interrupts */
	T1_program();
	//SetRelAlarm(Alarm_Send, 250, 250);	// Alarm of the task

	//_asm("tfr b,ccr\n", 0x00);
	//_asm("tfr a,ccrh\n", 0x00);

	// Forever loop: background activities (if any) should go here
	for (;;);

}

