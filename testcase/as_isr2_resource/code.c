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

#include <ee_internal.h>
#include "test/assert/inc/ee_assert.h"
#include "../../common/test_common.h"

#define TRUE  1U
#define FALSE 0U

#define MAX_ASSERT 70

#define IRQ_LOW     0
#define IRQ_MEDIUM  1
#define IRQ_HIGH    2

/* Ack the IRQ */
#define ACK_IRQ(x) (INTC.SSCIR[(x)].B.CLR = 1)

static StatusType last_error;
static unsigned int error_count;

static unsigned int low_isr_hit;
static unsigned int medium_isr_hit;
static unsigned int high_isr_hit;

static int assert_count = EE_ASSERT_NIL;
static void assert(int test)
{
  EE_assert(assert_count + 1, test, assert_count);
  ++assert_count;
}

/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[MAX_ASSERT + 1];

DeclareTask(Task1);

TASK(Task1)
{
  /* Do not release resources and do not call Terminate Task let kernel do the
     clean-up (as another test) */
  GetResource(Resource1);

  /* Firt IRQ stack */
  test_fire_irq(0U);
  assert(low_isr_hit == 1U);
  assert(medium_isr_hit == 1U);
  assert(high_isr_hit == 1U);
  assert(EE_oo_get_ISR2_TID() == EE_NIL);
  assert(EE_isr2_index == EE_UREG_MINUS1);
  assert(EE_th_resource_last[EE_MAX_TASK] == EE_UREG_MINUS1);
  assert(EE_th_resource_last[EE_MAX_TASK + 1] == EE_UREG_MINUS1);
  /* Second IRQ stack */
  GetResource(ResourceA);
  test_fire_irq(0U);
  assert(low_isr_hit == 1U);
  ReleaseResource(ResourceA);
  assert(low_isr_hit == 2U);
  assert(medium_isr_hit == 2U);
  assert(high_isr_hit == 2U);
  assert(EE_oo_get_ISR2_TID() == EE_NIL);
  assert(EE_isr2_index == EE_UREG_MINUS1);
  assert(EE_th_resource_last[EE_MAX_TASK] == EE_UREG_MINUS1);
  /* Third IRQ Stack */
  GetResource(ResourceB);
  test_fire_irq(0U);
  test_fire_irq(1U);
  test_fire_irq(2U);
}

void ErrorHook(StatusType Error)
{
  /* I cache error ID here to check that Error hook is called and that the
     right error is set */

  last_error = Error;
  ++error_count;
}

ISR2(IsrLow)
{
#ifdef __OO_EXTENDED_STATUS__
  StatusType s;
#endif /* __OO_EXTENDED_STATUS__ */
  ACK_IRQ(IRQ_LOW);
  if (low_isr_hit == 0U) {
    assert(EE_hal_get_int_prio() == 1U);
    GetResource(ResourceA);
    assert(EE_oo_get_ISR2_TID() == EE_MAX_TASK);
    assert(EE_isr2_nesting_level[EE_isr2_index] == 1U);
    assert(EE_hal_get_int_prio() == 1U);
    test_fire_irq(1U);
    assert(medium_isr_hit == 1U);
    assert(high_isr_hit == 1U);
    assert(EE_oo_get_ISR2_TID() == EE_MAX_TASK);
    ReleaseResource(ResourceA);
    assert(EE_hal_get_int_prio() == 1U);
  } else if (low_isr_hit == 1U) {
    assert(EE_hal_get_int_prio() == 1U);
    GetResource(ResourceB);
    assert(EE_oo_get_ISR2_TID() == EE_MAX_TASK);
    assert(EE_hal_get_int_prio() == 3U);
    test_fire_irq(1U);
    test_fire_irq(2U);
    assert(medium_isr_hit == 1U);
    assert(high_isr_hit == 1U);
  } else if (low_isr_hit == 2U) {
    assert(high_isr_hit == 3U);
    assert(medium_isr_hit == 3U);
    GetResource(ResourceB);
    GetResource(ResourceA);
    assert(EE_oo_get_ISR2_TID() == EE_MAX_TASK);
    assert(EE_hal_get_int_prio() == 3U);
    assert(EE_th_resource_last[EE_MAX_TASK] == ResourceA);
#ifdef __OO_EXTENDED_STATUS__
    /* Error one more in error_count */
    s = ReleaseResource(ResourceB);
    assert(s == E_OS_NOFUNC);
    assert(EE_hal_get_int_prio() == 3U);
#endif /* __OO_EXTENDED_STATUS__ */
  }
  ++low_isr_hit;
}

ISR2(IsrMedium)
{
  ACK_IRQ(IRQ_MEDIUM);
  if (medium_isr_hit == 0U) {
    assert(low_isr_hit == 0U);
    assert(EE_hal_get_int_prio() == 2U);
    assert(EE_oo_get_ISR2_TID() == EE_MAX_TASK);
    test_fire_irq(2U);
    assert(high_isr_hit == 1U);
    assert(EE_oo_get_ISR2_TID() == EE_MAX_TASK);
    assert(EE_hal_get_int_prio() == 2U);
  } else if (medium_isr_hit == 1U) {
    assert(low_isr_hit == 2U);
    assert(high_isr_hit == 2U);
    assert(EE_hal_get_int_prio() == 2U);
  } else if (medium_isr_hit == 2U) {
    assert(high_isr_hit == 3U);
    assert(low_isr_hit == 2U);
  }
  ++medium_isr_hit;
}

ISR2(IsrHigh)
{
  ACK_IRQ(IRQ_HIGH);
  if (high_isr_hit == 0U) {
    GetResource(ResourceB);
    assert(medium_isr_hit == 0U);
    assert(EE_oo_get_ISR2_TID() == (EE_MAX_TASK + 1U));
    assert(EE_isr2_nesting_level[EE_isr2_index] == 3U);
    assert(EE_hal_get_int_prio() == 3U);
    ReleaseResource(ResourceB);
  } else if (high_isr_hit == 1U) {
    assert(low_isr_hit == 2U);
    assert(medium_isr_hit == 1U);
    assert(last_error == E_OS_RESOURCE);
    assert(error_count == 1U);
  } else if (high_isr_hit == 2U) {
    assert(last_error == E_OS_MISSINGEND);
    assert(error_count == 2U);
    assert(medium_isr_hit == 2U);
    assert(low_isr_hit == 2U);
  }
  ++high_isr_hit;
}

int main(int argc, char *argv[])
{
  StartOS(OSDEFAULTAPPMODE);

  ActivateTask(Task1);

  assert(last_error == E_OS_RESOURCE);
#ifdef __OO_EXTENDED_STATUS__
  assert(error_count == 4U);
#else
  assert(error_count == 3U);
#endif /* __OO_EXTENDED_STATUS__ */
  assert(EE_th_resource_last[Task1] == EE_UREG_MINUS1);
  assert(EE_th_resource_last[EE_MAX_TASK] == EE_UREG_MINUS1);
  assert(EE_th_resource_last[EE_MAX_TASK + 1] == EE_UREG_MINUS1);

  EE_assert_range(0, 1, assert_count); 

  EE_assert_last();

  return 0;
}
