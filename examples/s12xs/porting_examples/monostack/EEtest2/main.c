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
 * Author: 2009 Dario Di Stefano
 */

#include "stdlib.h"
#include <math.h>
#include "ee.h"
#include "cpu/cosmic_hs12xs/inc/ee_irqstub.h"
#include "ee_hs12xsregs.h"
#include "test/assert/inc/ee_assert.h"

#define TRUE 1
/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[10];

void Periph_Init(void);
void PIT0_Program(void);
void Interrupt_Init(void);

volatile int counter_task = 0;
volatile int counter_isr = 0;

TASK(Task1)
{
    counter_task++;
    EE_assert(4, counter_task==1, 3);
    PITCFLMT      = 0x00;        
	PITCE         = 0x00;        
}

/*
 * MAIN TASK
*/
int main(void)
{
	int counter=0;
	EE_assert(1, TRUE, EE_ASSERT_NIL);
	_asm("cli");
	
	Interrupt_Init();
	Periph_Init();
	PIT0_Program();
	
	counter++;
	EE_assert(2, counter==1, 1);
	
	while(counter_task<1);
	EE_assert_range(0,1,4);
  	EE_assert_last();
	// Forever loop: background activities (if any) should go here
	for (;;);

	return 0;
}

void Periph_Init(void)
{
  // Configures PA[3..0] port as output  
  PORTA = (unsigned char)0x00;                                                    
  DDRA = (unsigned char)0x0F;  
  
  return;
}

/*	INTERRUPT registers initialisation
 */
void Interrupt_Init(void)
{
	// IVBR = 0xff;      // 0xFF default value
	INT_CFADDR = 0x7A;
	INT_CFDATA0 = 0x02;
	
	return;
}
	
	/* Program the Timer1 peripheral to raise interrupts */
void PIT0_Program(void)
{
	  /*	PIT Module
	 */
	  PITCFLMT      = 0x00;        //@0x340;	/* PIT control micro timer register */
	  PITFLT        = 0x00;        //@0x341;	/* PIT force load timer register */
	  PITCE         = 0x01;        //@0x342;	/* PIT channel enable register */
	  PITMUX        = 0x00;        //@0x343;	/* PIT multiplex register */
	  PITINTE       = 0x01;        //@0x344;	/* PIT interrupt enable register */
	  PITTF         = 0x01;        //@0x345;	/* PIT time-out flag register */
	  PITMTLD0      = 0x63;        //@0x346;	/* PIT micro timer load reg. 0 */
	  PITMTLD1      = 0x00;        //@0x347;	/* PIT micro timer load reg. 1 */
	  PITLD0        = 0x09;        //@0x348;	/* PIT load register 0 */
	  PITCNT0       = 0x00;        //@0x34a;	/* PIT count register 0 */
	  PITLD1        = 0x00;        //@0x34c;	/* PIT load register 1 */
	  PITCNT1       = 0x00;        //@0x34e;	/* PIT count register 1 */
	  PITLD2        = 0x00;        //@0x350;	/* PIT load register 2 */
	  PITCNT2       = 0x00;        //@0x352;	/* PIT count register 2 */
	  PITLD3        = 0x00;        //@0x354;	/* PIT load register 3 */
	  PITCNT3       = 0x00;        //@0x356;	/* PIT count register 3 */
	  PITCFLMT      = 0x80;        //@0x340;	/* PIT control micro timer register */
	  
	  return;
}

//@interrupt @near void uisr_pit1(void)
//{
//	PITTF         = 0x02;        //@0x345;	/* PIT time-out flag register */
//	_asm("cli");
//	if((PORTA & 0x02)==1)
//        PORTA &= 0xFD;
//	else
//        PORTA |= 0x02;
//}
