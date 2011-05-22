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
EE_TYPEASSERTVALUE EE_assertions[26];



volatile int wecanstart=0;

SemType mySem = STATICSEM(0);
SemType mySemMax = STATICSEM(EE_MAX_SEM_COUNTER);

DeclareTask(BasTask);


TASK(BasTask)
{
  StatusType s;
  unsigned int v;
  
  EE_assert(10, TRUE, 9);

  /* SemPost chiamato in un task con contatore >=0 e nessuno bloccato --> contatore incrementato */
  s = PostSem(&mySem);
  EE_assert(11, (s==E_OK), 10);
  v = GetValueSem(&mySem);
  EE_assert(12, (v == 3), 11);
 
  /* SemPost chiamato in un task con contatore =EE_MAX_SEM_COUNTER e nessuno bloccato --> E_OS_VALUE */
  s = PostSem(&mySemMax);
  EE_assert(13, (s==E_OS_VALUE), 12);
  v = GetValueSem(&mySemMax);
  EE_assert(14, (v == EE_MAX_SEM_COUNTER), 13);

  /* TryWaitSem chiamata  con contatore !=0 --> contatore decrementato, ritorna 0 */
  s = TryWaitSem(&mySem);
  EE_assert(15, (s==0), 14);
  v = GetValueSem(&mySem);
  EE_assert(16, (v == 2), 15);

  /* TryWaitSem chiamata  con contatore !=0 --> contatore decrementato, ritorna 0 */
  s = TryWaitSem(&mySem);
  EE_assert(17, (s==0), 16);
  v = GetValueSem(&mySem);
  EE_assert(18, (v == 1), 17);

  /* TryWaitSem chiamata  con contatore !=0 --> contatore decrementato, ritorna 0 */
  s = TryWaitSem(&mySem);
  EE_assert(19, (s==0), 18);
  v = GetValueSem(&mySem);
  EE_assert(20, (v == 0), 19);

  /* TryWaitSem chiamata  con contatore a 0 --> ritorna 1 */
  s = TryWaitSem(&mySem);
  EE_assert(21, (s==1), 20);
  v = GetValueSem(&mySem);
  EE_assert(22, (v == 0), 21);

  /* TryWaitSem chiamata  con contatore a 0 --> ritorna 1 */
  s = TryWaitSem(&mySem);
  EE_assert(23, (s==1), 22);
  v = GetValueSem(&mySem);
  EE_assert(24, (v == 0), 23);
 
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
  unsigned int v;
  
  /* clear the interrupt */
  IOWR_ALTERA_AVALON_TIMER_STATUS (HIGH_RES_TIMER_BASE, 0);
  
  /* SemPost chiamato in un ISR con contatore >=0 e nessuno bloccato 
   * --> contatore incrementato */
  s = PostSem(&mySem);
  EE_assert(2, (s==E_OK), 1);
  
  v = GetValueSem(&mySem);
  EE_assert(3, (v == 1), 2);
 
  /* SemPost chiamato in un ISR con contatore =EE_MAX_SEM_COUNTER 
   * e nessuno bloccato --> E_OS_VALUE */
  s = PostSem(&mySemMax);
  EE_assert(4, (s==E_OS_VALUE), 3);
  
  v = GetValueSem(&mySemMax);
  EE_assert(5, (v = EE_MAX_SEM_COUNTER), 4);

  wecanstart=1;
}
#endif

#if defined(__HCS12XS__)
	#include "cpu/cosmic_hs12xs/inc/ee_irqstub.h"
	#include "ee_hs12xsregs.h" 
	ISR2(myISR2)
	{
		
		StatusType s;
  		unsigned int v;
  
  		PITTF         	= 0x01;
  
	  /* SemPost chiamato in un ISR con contatore >=0 e nessuno bloccato 
	   * --> contatore incrementato */
	  s = PostSem(&mySem);
	  EE_assert(2, (s==E_OK), 1);
  
	  v = GetValueSem(&mySem);
	  EE_assert(3, (v == 1), 2);
	 
	  /* SemPost chiamato in un ISR con contatore =EE_MAX_SEM_COUNTER 
	   * e nessuno bloccato --> E_OS_VALUE */
	  s = PostSem(&mySemMax);
	  EE_assert(4, (s==E_OS_VALUE), 3);
	  
	  v = GetValueSem(&mySemMax);
	  EE_assert(5, (v = EE_MAX_SEM_COUNTER), 4);
	
	  wecanstart=1;
  	  EE_pit0_close();
	}
#endif

#if defined(__PPCE200Z7__)
#include "cpu/e200zx/inc/ee_irq.h"
static void handle_timer_interrupt(void)
{
  StatusType s;
  unsigned int v;
  
  /* SemPost chiamato in un ISR con contatore >=0 e nessuno bloccato 
   * --> contatore incrementato */
  s = PostSem(&mySem);
  EE_assert(2, (s==E_OK), 1);
  
  v = GetValueSem(&mySem);
  EE_assert(3, (v == 1), 2);
 
  /* SemPost chiamato in un ISR con contatore =EE_MAX_SEM_COUNTER 
   * e nessuno bloccato --> E_OS_VALUE */
  s = PostSem(&mySemMax);
  EE_assert(4, (s==E_OS_VALUE), 3);
  
  v = GetValueSem(&mySemMax);
  EE_assert(5, (v = EE_MAX_SEM_COUNTER), 4);

  wecanstart=1;
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

  StartOS(OSDEFAULTAPPMODE);

  while (!wecanstart);
  
  /* SemPost chiamato nel main task con contatore >=0 e nessuno bloccato --> contatore incrementato */
  s = PostSem(&mySem);
  EE_assert(6, (s==E_OK), 5);
  
  v = GetValueSem(&mySem);
  EE_assert(7, (v == 2), 6);
 
  /* SemPost chiamato nel main task con contatore =EE_MAX_SEM_COUNTER e nessuno bloccato --> E_OS_VALUE */
  s = PostSem(&mySemMax);
  EE_assert(8, (s==E_OS_VALUE), 7);
  
  v = GetValueSem(&mySemMax);
  EE_assert(9, (v = EE_MAX_SEM_COUNTER), 8);

  ActivateTask(BasTask);
  EE_assert(25, TRUE, 24);
  
  EE_assert_range(0,1,25);
  EE_assert_last();
  
  /* Background activities, none in this demo! */
  for (;;);
  
  return 0;
}
