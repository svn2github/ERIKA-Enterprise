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
 * Author: 2002-2008 Paolo Gai
 */

#include "ee.h"
#include "cpu/cosmic_hs12xs/inc/ee_irqstub.h"

void Interrupt_Init(void);
static void mydelay(int end);
void EE_leds(unsigned char value);
void led_blink(int theled);
void PIT0_program(void);
void Interrupt_Init(void);
static void handle_button_interrupts(void);
void EE_leds_init(void);
void EE_buttons_init(void);

/* Let's declare the tasks identifiers */
DeclareTask(Task1);
DeclareTask(Task2);

/* insert a stub for the functions not directly supported by __FP__ */
#ifdef __FP__
__INLINE__ void __ALWAYS_INLINE__ DisableAllInterrupts(void)
{
  EE_hal_disableIRQ();
}

__INLINE__ void __ALWAYS_INLINE__ EnableAllInterrupts(void)
{
  EE_hal_enableIRQ();
}

__INLINE__ void __ALWAYS_INLINE__ TerminateTask(void)
{
}

#define OSDEFAULTAPPMODE 1
__INLINE__ void __ALWAYS_INLINE__ StartOS(int i)
{
}
#endif

/* A few counters incremented at each event 
 * (alarm, button press or task activation...)
 */
volatile int timer_fired=0;
volatile int button_fired=0;
volatile int task1_fired=0;
volatile int task2_fired=0;
volatile int timer_divisor = 0;

/* Let's remember the led status! 
 * Mutual exclusion on this variable is not included in the demo to make it
 * not too complicated; in general shared variables should be protected using
 * GetResource/ReleaseResource calls
 */
volatile int led_status = 0;



/* just a dummy delay */ 
static void mydelay(int end)
{
  	int i;
  	for (i=0; i<end; i++);
    
  	return;  
}

/* sets and resets a led configuration passed as parameter, leaving the other
 * bits unchanged
 * 
 * Note: led_blink is called both from Task1 and Task2. To avoid race 
 * conditions, we forced the atomicity of the led manipulation using IRQ
 * enabling/disabling. We did not use Resources in this case because the 
 * critical section is -really- small. An example of critical section using 
 * resources can be found in the osek_resource example.
 */
 
void EE_leds(unsigned char value)
{
	PORTA = value;
	
    return;
} 
 
void led_blink(int theled)
{
  	DisableAllInterrupts();
	led_status |= theled;
	EE_leds(led_status);
	EnableAllInterrupts();
	
	mydelay(1000);
	
	DisableAllInterrupts();
	led_status &= ~theled;
	EE_leds(led_status);
	EnableAllInterrupts();
	
	return;
}


/* Program the Timer1 peripheral to raise interrupts */

void PIT0_program(void)
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
	  PITLD0        = 0x04;        //@0x348;	/* PIT load register 0 */
	  PITCNT0       = 0x03;        //@0x34a;	/* PIT count register 0 */
	  PITLD1        = 0x00;        //@0x34c;	/* PIT load register 1 */
	  PITCNT1       = 0x00;        //@0x34e;	/* PIT count register 1 */
	  PITLD2        = 0x00;        //@0x350;	/* PIT load register 2 */
	  PITCNT2       = 0x00;        //@0x352;	/* PIT count register 2 */
	  PITLD3        = 0x00;        //@0x354;	/* PIT load register 3 */
	  PITCNT3       = 0x00;        //@0x356;	/* PIT count register 3 */
	  PITCFLMT      = 0x80;        //@0x340;	/* PIT control micro timer register */
	  
	  Interrupt_Init();
	  return;
}

/*	INTERRUPT registers initialisation
 */
void Interrupt_Init(void)
{
	// IVBR = 0xff;      // 0xFF default value
	_asm("cli");
	INT_CFADDR = 0x7A;
	INT_CFDATA0 = 0x02;
	
	return;
}

/* Task1: just call the ChristmasTree */
TASK(Task1)
{
  	task1_fired++;
  
  	///* First half of the christmas tree */
//  	led_blink(0x01);
//  	led_blink(0x02);
//  	led_blink(0x04);
//  	led_blink(0x08);
//  
//  	/* CONFIGURATION 3 and 4: we put an additional Schedule() here! */
//	#ifdef MYSCHEDULE
//  	Schedule();
//	#endif
//
//  	/* Second half of the christmas tree */
//  	led_blink(0x08);
//  	led_blink(0x04);
//  	led_blink(0x02);
//  	led_blink(0x01);

	PORTA |= 0x03;
	mydelay(2000);
	PORTA &= 0xFC;
	
  	TerminateTask();
}


/* Task2: Print the counters on the JTAG UART */
TASK(Task2)
{
  	// static int which_led = 0;
	//  /* count the number of Task2 activations */
    task2_fired++;

  	///* let blink leds 6 or 7 */
//  	if (which_led) 
//	{
//        led_blink(0x09);
//    	which_led = 0;
//    }
//  	else 
//	{
//	    led_blink(0x06);
//    	which_led = 1;
//  	}
  	
  	PORTA |= 0x0C;
	mydelay(1000);
	PORTA &= 0xF3;
	
  	TerminateTask();
 
}

/*
 * Handle button_pio interrupts activates Task2.
 */
static void handle_button_interrupts(void)
{
  	
  	button_fired++;					/* count the number of button presses */
  
  	ActivateTask(Task2);  
  	
  	return;
}

/*
 * Peripherals configuration
 */  
void EE_leds_init(void)
{
  	PORTA = (unsigned char)0x00;	// values                                             
  	DDRA = (unsigned char)0x0F;		// configured in output mode
  
  	return; 
}  

void EE_buttons_init(void)
{
	DDRP = (unsigned char)0x00;		// configured in input mode
	
	return;
}
  
  
  
// MAIN function 
int main()
{ 
  /* let's start the multiprogramming environment...*/
  StartOS(OSDEFAULTAPPMODE);
  
  ///* Program Timer 1 to raise interrupts */
  PIT0_program();
	
  /* Init devices */
  EE_buttons_init();
  
  /* Init leds */
  EE_leds_init();

  mydelay(10);
  
  /* now the background activities... */
  for (;;)
  {
      if(!(PTP&0x01))        			// PP0 pushed
      {
          handle_button_interrupts(); 
      }   
  }


  
  return 0;
}
