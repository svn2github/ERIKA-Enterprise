/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
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
 * A minimal EE demo for BCC2 mode testing. Task1 is a non-preemptive task
 * and Task2 can have pending activations.
 * Author: 2012 Carlo Caione
 * Based on examples\cortex_mx\lpc12xx\porting_examples\monostack\EEtest7
 */

#include "ee.h"
#include "stm32f4xx_conf.h"
#include "stm32f4_discovery.h"
#include "ee_irq.h"
#include "test/assert/inc/ee_assert.h"

#define TRUE 1

/* Assertions */
enum EE_ASSERTIONS {
  EE_ASSERT_FIN = 0,
  EE_ASSERT_INIT,
  EE_ASSERT_TASK2_FIRED,
  EE_ASSERT_TIMER_FIRED,
  EE_ASSERT_TASK1_FIRED,
  EE_ASSERT_TASK2_ACTIVATIONS,
  EE_ASSERT_DIM
};
EE_TYPEASSERTVALUE EE_assertions[EE_ASSERT_DIM];

/* Final result */
volatile EE_TYPEASSERTVALUE result;

/* A few counters incremented at each event 
 * (alarm, button press or task activation...)
 */
volatile int timer_fired=0;
volatile int task1_fired=0;
volatile int task2_fired=0;
volatile int timer_divisor = 0;
volatile uint16_t capture = 0;

/*
 * Timer3
 */
void TIM3_IRQHandler(void)
{

  if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET) {
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
	capture = TIM_GetCapture1(TIM3);
	TIM_SetCompare1(TIM3, capture + 1000);
    timer_divisor++;
    if (timer_divisor == 2000) {
      timer_divisor = 0;
      timer_fired++;
      if (timer_fired == 1) {
        EE_assert(EE_ASSERT_TIMER_FIRED, timer_fired == 1, EE_ASSERT_TASK2_FIRED);
        ActivateTask(Task1);
      }
    }
  }

}

/*
 * INTERRUPT INITIALIZATION
 */
void interrupt_init()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	/* Enable the TIM3 gloabal Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_SetPriority(TIM3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 1));
}


/*
 * Initialize Timer3
 */
void timer_init()
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	uint16_t PrescalerValue = 0;
	
	PrescalerValue = (uint16_t) ((SystemCoreClock / 2) / 1000000) - 1;
	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 65535;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/* Prescaler configuration */
	TIM_PrescalerConfig(TIM3, PrescalerValue, TIM_PSCReloadMode_Immediate);

	/* Output Compare Timing Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 1000;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(TIM3, &TIM_OCInitStructure);

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);

	/* TIM Interrupts enable */
	TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);

	/* TIM3 enable counter */
	TIM_Cmd(TIM3, ENABLE);
}

/*
 * TASK 1
 */
TASK(Task1)
{
  task1_fired++;
  EE_assert(EE_ASSERT_TASK1_FIRED, task1_fired == 1, EE_ASSERT_TIMER_FIRED);
  ActivateTask(Task2); 
  //TerminateTask();
}

/*
 * TASK 2
 */
TASK(Task2)
{
  task2_fired++;
  if(task2_fired == 1)
  {
    ActivateTask(Task2);
    ActivateTask(Task2);
    ActivateTask(Task2);
    ActivateTask(Task2);
    ActivateTask(Task2);
    ActivateTask(Task2);
    EE_assert(EE_ASSERT_TASK2_FIRED, task2_fired == 1, EE_ASSERT_INIT);
  }
  else {
    TerminateTask();
  }
}

/*
 * MAIN TASK
 */
int main()
{

  /*Initializes Erika related stuffs*/
  EE_system_init();

  interrupt_init();
  timer_init();

  EE_assert(EE_ASSERT_INIT, TRUE, EE_ASSERT_NIL);

  /* let's start the multiprogramming environment...*/
  StartOS(OSDEFAULTAPPMODE);

  ActivateTask(Task2);

  while(task2_fired<5);
  EE_assert(
    EE_ASSERT_TASK2_ACTIVATIONS, task2_fired == 5, EE_ASSERT_TASK1_FIRED
  );
  EE_assert_range(EE_ASSERT_FIN, EE_ASSERT_INIT, EE_ASSERT_TASK2_ACTIVATIONS);
  result = EE_assert_last();

  for(;;)
  {
    ;
  }

}
