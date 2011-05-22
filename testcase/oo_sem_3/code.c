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

#if defined(__NIOS2__)
/* Altera Includes */ 
#include "system.h"
#include <altera_avalon_pio_regs.h>
#include <stdio.h>
#include "altera_avalon_timer_regs.h"
#endif

/* EE includes */
#include "ee.h"

/* Assertions */
#include "test/assert/inc/ee_assert.h"
#define TRUE 1

/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[21];

volatile int irqStatus=0;
volatile int BasTask_cancontinue=0;
volatile int BasTaskLow_cancontinue=0;

SemType mySem;

DeclareTask(ExtTask);
DeclareTask(BasTask);
DeclareTask(BasTaskLow);
DeclareTask(ExtTaskLow);

TASK(ExtTask)
{
#ifdef __OO_EXTENDED_STATUS__
  StatusType s;
#endif
  
  EE_assert(3, TRUE, 2);

  /* WaitSem chiamata con contatore a 0 --> mi blocco ed eseguo un task preemptato */
#ifdef __OO_EXTENDED_STATUS__
  s = WaitSem(&mySem);
  EE_assert(8, (s==E_OK), 7);
#else
  WaitSem(&mySem);
  EE_assert(8, TRUE, 7);
#endif

  TerminateTask();
}

TASK(BasTask)
{
  int v;
  
  EE_assert(2, TRUE, 1);
  ActivateTask(ExtTask);
  EE_assert(4, TRUE, 3);
 
  v = GetValueSem(&mySem);
 
  EE_assert(5, (v == -1), 4);

  /* the IRQ can now do the Post... */
  irqStatus = 1;
  while (!BasTask_cancontinue);

  EE_assert(9, TRUE, 8);

  TerminateTask();
}


TASK(BasTaskLow)
{
  EE_assert(16, TRUE, 15);

  /* we wait for the Interrupt. the interrupt will execute a sempost waking up 
   * ExtTaskLow which will not preempt BasTaskLow */
  irqStatus = 2;
  while (!BasTaskLow_cancontinue);

  EE_assert(19, TRUE, 18);
 
  TerminateTask();
}

TASK(ExtTaskLow)
{
#ifdef __OO_EXTENDED_STATUS__
  StatusType s;
#endif
  
  EE_assert(12, TRUE, 11);

  /* WaitSem chiamata con contatore a 0 --> mi blocco e torno al main */
#ifdef __OO_EXTENDED_STATUS__
  s = WaitSem(&mySem);
  EE_assert(14, (s==E_OK), 13);
#else
  WaitSem(&mySem);
  EE_assert(14, TRUE, 13);
#endif

  /* WaitSem chiamata con contatore a 0 --> mi blocco e torno al main */
#ifdef __OO_EXTENDED_STATUS__
  s = WaitSem(&mySem);
  EE_assert(20, (s==E_OK), 19);
#else
  WaitSem(&mySem);
  EE_assert(20, TRUE, 19);
#endif


  TerminateTask();
}



int myErrorCounter;
void ErrorHook(StatusType Error)
{
  myErrorCounter++;
}

#if defined(__NIOS2__)
/* call the ERIKA Enterprise tick function for the Counter1 counter! */
static void handle_timer_interrupt(void* context, alt_u32 id)
{
  StatusType s;
  /* clear the interrupt */
  IOWR_ALTERA_AVALON_TIMER_STATUS (HIGH_RES_TIMER_BASE, 0);
  
  if (irqStatus==1) {
    /* SemPost chiamato in un IRQ con contatore =0 e qualcuno bloccato 
     * --> sblocco un task e il task sbloccato va in coda ready, no preemption, 
     * preemption alla fine dell'ISR */
    EE_assert(6, TRUE, 5);
    s = PostSem(&mySem);
    EE_assert(7, (s==E_OK), 6);
    BasTask_cancontinue = 1;
    irqStatus = 0;
  }
  
  if (irqStatus==2) {
    /*  SemPost chiamato in un IRQ con contatore =0 e qualcuno bloccato 
     * --> sblocco un task e il task sbloccato va in coda ready, no preemption, 
     * no preemption alla fine dell'ISR */
    EE_assert(17, TRUE, 16);
    s = PostSem(&mySem);
    EE_assert(18, (s==E_OK), 17);
    BasTaskLow_cancontinue = 1;
    irqStatus = 0;
  }
  
}
#endif

#if defined(__HCS12XS__)
	#include "cpu/cosmic_hs12xs/inc/ee_irqstub.h"
	#include "ee_hs12xsregs.h" 
	ISR2(myISR2)
	{
		StatusType s;
		PITTF         	= 0x01;
		
	  if (irqStatus==1) {
	    /* SemPost chiamato in un IRQ con contatore =0 e qualcuno bloccato 
	     * --> sblocco un task e il task sbloccato va in coda ready, no preemption, 
	     * preemption alla fine dell'ISR */
	    EE_assert(6, TRUE, 5);
	    s = PostSem(&mySem);
	    EE_assert(7, (s==E_OK), 6);
	    BasTask_cancontinue = 1;
	    irqStatus = 0;
	  }
  
	  if (irqStatus==2) {
	    /*  SemPost chiamato in un IRQ con contatore =0 e qualcuno bloccato 
	     * --> sblocco un task e il task sbloccato va in coda ready, no preemption, 
	     * no preemption alla fine dell'ISR */
	    EE_assert(17, TRUE, 16);
	    s = PostSem(&mySem);
	    EE_assert(18, (s==E_OK), 17);
	    BasTaskLow_cancontinue = 1;
	    irqStatus = 0;
	  }
  
  		//EE_pit0_close();
	}
#endif

#if defined(__PPCE200Z7__)
#include "cpu/e200zx/inc/ee_irq.h"
static void handle_timer_interrupt(void)
{
  StatusType s;

  if (irqStatus==1) {
    /* SemPost chiamato in un IRQ con contatore =0 e qualcuno bloccato 
     * --> sblocco un task e il task sbloccato va in coda ready, no preemption, 
     * preemption alla fine dell'ISR */
    EE_assert(6, TRUE, 5);
    s = PostSem(&mySem);
    EE_assert(7, (s==E_OK), 6);
    BasTask_cancontinue = 1;
    irqStatus = 0;
  }
  
  if (irqStatus==2) {
    /*  SemPost chiamato in un IRQ con contatore =0 e qualcuno bloccato 
     * --> sblocco un task e il task sbloccato va in coda ready, no preemption, 
     * no preemption alla fine dell'ISR */
    EE_assert(17, TRUE, 16);
    s = PostSem(&mySem);
    EE_assert(18, (s==E_OK), 17);
    BasTaskLow_cancontinue = 1;
    irqStatus = 0;
  }
  
}
#endif


void StartupHook(void)
{
	#if defined(__NIOS2__)
  	/* set to free running mode */
  	IOWR_ALTERA_AVALON_TIMER_CONTROL (HIGH_RES_TIMER_BASE, 
            ALTERA_AVALON_TIMER_CONTROL_ITO_MSK  |
            ALTERA_AVALON_TIMER_CONTROL_CONT_MSK |
            ALTERA_AVALON_TIMER_CONTROL_START_MSK);

  	/* register the interrupt handler, and enable the interrupt */
  	alt_irq_register (HIGH_RES_TIMER_IRQ, NULL, handle_timer_interrupt);    
  	#endif
  	#if defined(__HCS12XS__)
  		EE_pit0_init(99, 140, 2);
	#endif
	#if defined(__PPCE200Z7__)
		EE_e200z7_register_ISR(10, handle_timer_interrupt, 0);
		EE_e200z7_setup_decrementer(2000000);		
	#endif
}



int main(void)
{
  StatusType s;
  unsigned int v;

	#if defined(__HCS12XS__)
   	_asm("cli");
	#endif
	#if defined(__PPCE200Z7__)
	EnableAllInterrupts();
	#endif

  EE_assert(1, TRUE, EE_ASSERT_NIL);

  InitSem(&mySem, 0);
  
  StartOS(OSDEFAULTAPPMODE);

  EE_assert(10, TRUE, 9);
  
  v = GetValueSem(&mySem);
 
  EE_assert(11, (v == 0), 10);
  
  /* activate the ExtTasklow */
  s = ActivateTask(ExtTaskLow);

  EE_assert(13, (s==E_OK), 12);

  /* SemPost chiamato nel main con contatore =0 e qualcuno bloccato 
   * --> sblocco un task e parte il task sbloccato */
  s = PostSem(&mySem);
  EE_assert(15, (s==E_OK), 14);
  
  /* activate BasTaskLow, which has higher priority than ExtTasklow */
  s = ActivateTask(BasTaskLow);

  EE_assert(21, (s==E_OK), 20);

  EE_assert_range(0,1,21);
  EE_assert_last();
  
  /* Background activities, none in this demo! */
  for (;;);
  
  return 0;
}
