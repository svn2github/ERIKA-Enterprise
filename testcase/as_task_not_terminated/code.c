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

#include "ee_internal.h"
#include "test/assert/inc/ee_assert.h"
#include "../../common/test_common.h"

#define TRUE  1U
#define FALSE 0U

/* assertion data */
#ifdef __OO_EXTENDED_STATUS__
EE_TYPEASSERTVALUE EE_assertions[11];
#else
EE_TYPEASSERTVALUE EE_assertions[9];
#endif /* __OO_EXTENDED_STATUS__ */

volatile EE_TYPEPRIO    oldCeiling;
volatile StatusType     errorId;
volatile unsigned char  postTaskFlag;
volatile unsigned char  irqCounter;
volatile unsigned char  prevIrqDisi;
TaskType                taskId;

DeclareTask(Task1);
DeclareTask(Task2);

TASK(Task1)
{
  /* Used later */
  GetTaskID(&taskId);

  /* I get the sesources */
  GetResource(Resource1);
  GetResource(ResourceA);
  GetResource(ResourceB);

  /* I release one - just in case something could happen */
  ReleaseResource(ResourceB);
  /* I disable all interrupt and I check that the kernel re-enable them */
  DisableAllInterrupts();
  /* This should not call the isr_callback because interrupts are disabled */
  test_fire_irq();
  prevIrqDisi = (irqCounter == 1);
  prevIrqDisi &= !EE_e200z7_isIRQEnabled();

  /* I explicitally don't call TerminateTask. I'm testing that kernel is doing
     correct clean-up in this case */
}

TASK(Task2)
{
  /* Fake Task. I need this only to share resource with higher priority with
      Task1 */
}

void ErrorHook(StatusType Error)
{
  /* I cache error ID here to check that Error hook is called and that the
     right error is set*/
  errorId = Error;
}

void PostTaskHook(void)
{
  postTaskFlag = TRUE;
}

void isr_callback(void)
{
  ++irqCounter;
}

int main(int argc, char **argv)
{
  /* I cache old value of ceiling to check it */
  oldCeiling = EE_sys_ceiling;

  /* Setup and queue an interrupt request; StartOS() should enable IRQs, so
     the request is served */
  test_setup_irq();
  test_fire_irq();

  StartOS(OSDEFAULTAPPMODE);

  EE_assert(1, TRUE, EE_ASSERT_NIL);
  /* Check that irq has bee called */
  EE_assert(2, (irqCounter == 1), 1);

  ActivateTask(Task1);
  /* I test that error hook has been called with rhe right error */
  EE_assert(3, (errorId == E_OS_MISSINGEND), 2);
  /* I test that PostTaskHook has been called */
  EE_assert(4, (postTaskFlag == TRUE), 3);
  /* I test that the ceilig is reset at start value */
  EE_assert(5, (EE_sys_ceiling == oldCeiling), 4);

  /* Test that previously were disabled */
  EE_assert(6, (prevIrqDisi == 1), 5);

  /* I test that the IRQ are enabled */
  /* FIXME: In Erika HAL doesn't exit a method to check IRQ status! */
  EE_assert(7, (irqCounter == 2), 6);
  EE_assert(8, EE_e200z7_isIRQEnabled(), 7);


#ifdef __OO_EXTENDED_STATUS__
  EE_assert(9, (taskId != INVALID_TASK), 8);
  /* I Test that hold resource stack for the task is empty */
  EE_assert(10, (EE_th_resource_last[taskId] == EE_UREG_MINUS1), 9);
  EE_assert_range(0, 1, 10); 
#else
  EE_assert_range(0, 1, 8);
#endif /* __OO_EXTENDED_STATUS__ */

  EE_assert_last();

  return 0;
}
