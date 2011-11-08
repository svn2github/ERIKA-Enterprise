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

#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#ifdef __EVALUATOR7T__
#include "mcu/samsung_ks32c50100/inc/ee_ic.h"
#endif

#ifdef __PPCE200Z7__
#include "cpu/e200zx/inc/ee_irq.h"
#endif

#define TRUE 1

/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[20];

DeclareTask(Task1);
DeclareTask(Task2);

volatile int ISR2_fired;

#if defined(__NIOS2__)
#include "sys/alt_alarm.h"
static void myISR2(void);
alt_u32 mycallback (void* arg)
{
  myISR2();
  return 0;
}
#endif

#if defined(__ARM7GNU__) && defined(__JANUS__)
#include "arm7gnu/janus/stub.h"
_ISR2(myISR2)
#else
	#if defined(__HCS12XS__)
		#include "cpu/hs12xs/inc/ee_irqstub.h"
		#include "ee_hs12xsregs.h" 
		ISR2(myISR2)
	#else
		static void myISR2(void)
	#endif
#endif
{
  StatusType s;

  EE_assert(8, TRUE, 7);
  s = ClearEvent(Event1);
  EE_assert(9, (s==E_OS_CALLEVEL), 8);
  s = WaitEvent(Event1);
  EE_assert(10, (s==E_OS_CALLEVEL), 9);
  
  ISR2_fired=1;

#if defined(__ARM7GNU__) && defined(__JANUS__)
  // Reset the interrupt pending bit on the EIC
  *OCCDEFINT &= ~INTF0B;
#endif

#if defined(__HCS12XS__)
	PITTF         	= 0x01;
	PITCE 			= 0;
#endif
}

TASK(Task1)
{
  StatusType s;
  EventMaskType EventMask;

  EE_assert(1, TRUE, EE_ASSERT_NIL);

  EnableAllInterrupts();
  EE_assert(2, TRUE, 1);

  s = SetEvent(INVALID_TASK, Event1);
  EE_assert(3, (s==E_OS_ID), 2);

  s = SetEvent(Task1, Event1);
  EE_assert(4, (s==E_OS_ACCESS), 3);

  s = SetEvent(Task2, Event1);
  EE_assert(5, (s==E_OS_STATE), 4);

  s = ClearEvent(Event1);
  EE_assert(6, (s==E_OS_ACCESS), 5);

  // Trigger interrupt
#if defined(__ARM7GNU__) && defined(__EVALUATOR7T__)
  EE_timer_0_start();
#endif

#if defined(__ARM7GNU__) && defined(__JANUS__)
  *OCEN |= ENF0;
  *OCCDEFIE |= IEF0B;
#endif

  EE_assert(7, TRUE, 6);

  while(!ISR2_fired);

  EE_assert(11, TRUE, 10);

  s = GetEvent(INVALID_TASK, &EventMask);
  EE_assert(12, (s==E_OS_ID), 11);

  s = GetEvent(Task1, &EventMask);
  EE_assert(13, (s==E_OS_ACCESS), 12);

  s = GetEvent(Task2, &EventMask);
  EE_assert(14, (s==E_OS_STATE), 13);

  s = WaitEvent(Event1);
  EE_assert(15, (s==E_OS_ACCESS), 14);

  ChainTask(Task2);
}

TASK(Task2)
{
  StatusType s;

  EE_assert(16, TRUE, 15);

  s = GetResource(Resource1);
  EE_assert(17, (s==E_OK), 16);

  s = WaitEvent(Event1);
  EE_assert(18, (s==E_OS_RESOURCE), 17);
  
  s = ReleaseResource(Resource1);
  EE_assert(19, (s==E_OK), 18);

  TerminateTask();
}

#ifndef __OO_AUTOSTART_TASK__
void StartupHook(void)
{
  ActivateTask(Task1);
}
#endif

int main(int argc, char **argv)
{
#if defined(__ARM7GNU__) && defined(__EVALUATOR7T__)

#define COUNTDOWN ((1 * 1000 * 1000 * 1000) / 20) /* 1 sec */

  EE_IC_clear_pending_IRQ();
  EE_IC_enable_external_IRQ(IRQ_TIMER0_MASK);
  EE_timer_0_set(((1 * 1000 * 1000 * 1000) / 20)/10); /* 100 msec */

#endif

#if defined(__ARM7GNU__) && defined(__JANUS__)

  EE_janus_IRQ_enable_channel(IRQ_ETUOCFB);
  EE_janus_IRQ_set_priority(IRQ_ETUOCFB, 1);
  EE_janus_IRQ_set_handler(IRQ_ETUOCFB, (EE_ADDR)myISR2);
  EE_janus_IRQ_enable_EIC();
  *OCREGF0B = 0x4FFF;

#endif

#if defined(__NIOS2__)
  {
    alt_alarm myalarm;
    alt_alarm_start(&myalarm, 100, mycallback, NULL);
  }

#endif

#if defined(__HCS12XS__)

  EE_pit0_init(99, 140, 2);

#endif

#if defined(__PPCE200Z7__)
  EE_e200z7_register_ISR(10, myISR2, 0);
  EE_e200z7_setup_decrementer(3000000);
#endif

  StartOS(OSDEFAULTAPPMODE);

  EE_assert_range(0,1,19);
  EE_assert_last();

  return 0;
}

#ifdef __JANUS__
EE_UINT16 fiq_arm0_handler(EE_UINT16 etu0_fir)
{
  return etu0_fir;
}
#endif
