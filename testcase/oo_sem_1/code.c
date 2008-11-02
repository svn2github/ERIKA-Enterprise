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

/* Altera Includes */ 
#include "system.h"
#include <altera_avalon_pio_regs.h>
#include <stdio.h>
#include "altera_avalon_timer_regs.h"

/* EE includes */
#include "ee.h"

/* Assertions */
#include "test/assert/inc/ee_assert.h"
#define TRUE 1
/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[9];



volatile int wecanstart=0;

SemType mySem = STATICSEM(0);


TASK(ExtTask)
{
  StatusType s;
  
  EE_assert(6, TRUE, 5);

  GetResource(Resource);
  
  /* WaitSem chiamata da un Basic task --> E_OS_ACCESS */
  s = WaitSem(&mySem);
  EE_assert(7, (s==E_OS_RESOURCE), 6);

  ReleaseResource(Resource);

  TerminateTask();
}

TASK(BasTask)
{
  StatusType s;
  
  EE_assert(4, TRUE, 3);
  
  /* WaitSem chiamata da un Basic task --> E_OS_ACCESS */
  s = WaitSem(&mySem);
  EE_assert(5, (s==E_OS_ACCESS), 4);
 
  TerminateTask();
}


int myErrorCounter;
void ErrorHook(StatusType Error)
{
  myErrorCounter++;
}

/* call the ERIKA Enterprise tick function for the Counter1 counter! */
static void handle_timer_interrupt(void* context, alt_u32 id)
{
  StatusType s;
  /* clear the interrupt */
  IOWR_ALTERA_AVALON_TIMER_STATUS (HIGH_RES_TIMER_BASE, 0);
  
  /* WaitSem chiamata a livello IRQ --> E_OS_CALLEVEL */
  s = WaitSem(&mySem);
  EE_assert(2, (s==E_OS_CALLEVEL), 1);
  
  wecanstart=1;
}

void StartupHook(void)
{
  /* set to free running mode */
  IOWR_ALTERA_AVALON_TIMER_CONTROL (HIGH_RES_TIMER_BASE, 
            ALTERA_AVALON_TIMER_CONTROL_ITO_MSK  |
            ALTERA_AVALON_TIMER_CONTROL_CONT_MSK |
            ALTERA_AVALON_TIMER_CONTROL_START_MSK);

  /* register the interrupt handler, and enable the interrupt */
    
  alt_irq_register (HIGH_RES_TIMER_IRQ, NULL, handle_timer_interrupt);    
}



int main(void)
{
  StatusType s;

  EE_assert(1, TRUE, EE_ASSERT_NIL);

  StartOS(OSDEFAULTAPPMODE);

  while (!wecanstart);
  
  /* WaitSem chiamata a livello main --> E_OS_CALLEVEL */
  s = WaitSem(&mySem);
  EE_assert(3, (s==E_OS_CALLEVEL), 2);
  
  ActivateTask(BasTask);
  ActivateTask(ExtTask);
  
  EE_assert(8, TRUE, 7);
  
  EE_assert_range(0,1,7);
  EE_assert_last();
  
  /* Background activities, none in this demo! */
  for (;;);
  
  return 0;
}
