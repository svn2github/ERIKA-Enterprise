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
 * GPT372:	Gpt_Irq.c File for implementation of interrupt service routine
 * 		(BSW00314)
 *
 * AUTOSAR-"like" GPT Driver Channels ISRs Source File.
 *
 * Author:  2011,  Giuseppe Serano
 */

/*
 * GPT261:	Gpt_Irq.c shall include Gpt.h for the prototype declaration of
 * 		the notification functions. (BSW164)
 */
#include "Gpt.h"

/* 
 * GPT256:	The GPT module shall perform Inter Module Checks to avoid
 * 		integration of incompatible files. The imported included files
 * 		shall be checked by preprocessing directives. (BSW004)
 *
 * The following version numbers shall be verified:
 * - <MODULENAME>_AR_RELEASE_MAJOR_VERSION
 * - <MODULENAME>_AR_RELEASE_MINOR_VERSION
 * Where <MODULENAME> is the module abbreviation of the other (external) modules
 * which provide header files included by the GPT module.
 *
 * If the values are not identical to the expected values, an error shall be
 * reported.
 */
#define	GPT_AR_RELEASE_MAJOR_VERSION	4
#define	GPT_AR_RELEASE_MINOR_VERSION	0

#if !defined( GPT_AR_MAJOR_VERSION ) || \
    ( GPT_AR_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION )
#error	Gpt_Irq: version mismatch.
#endif

#include "ee.h"
#include "ee_irq.h"

/*
 * Type that holds all global data for Gpt Driver
 */
typedef struct
{
  boolean			Init;		/* GPT Driver Initialized?    */

  const Gpt_ConfigType *	ConfigPtr;	/* Actual Configuration	      */

  uint32			Status;		/* Channel Status	      */

  uint32			Notifications;	/* Channel Notifications      */

} Gpt_GlobalType;

/*
 * GPT Driver Global Configuration Reference
 */
extern Gpt_GlobalType Gpt_Global;

#if ( GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )

#if ( \
  defined(EE_CORTEX_MX_TIMER_0_A_ISR) || \
  defined(EE_CORTEX_MX_TIMER_1_A_ISR) || \
  defined(EE_CORTEX_MX_TIMER_2_A_ISR) || \
  defined(EE_CORTEX_MX_TIMER_3_A_ISR) || \
  defined(EE_CORTEX_MX_TIMER_4_A_ISR) || \
  defined(EE_CORTEX_MX_TIMER_5_A_ISR) || \
  defined(EE_CORTEX_MX_WIDE_TIMER_0_A_ISR) || \
  defined(EE_CORTEX_MX_WIDE_TIMER_1_A_ISR) || \
  defined(EE_CORTEX_MX_WIDE_TIMER_2_A_ISR) || \
  defined(EE_CORTEX_MX_WIDE_TIMER_3_A_ISR) || \
  defined(EE_CORTEX_MX_WIDE_TIMER_4_A_ISR) || \
  defined(EE_CORTEX_MX_WIDE_TIMER_5_A_ISR) \
)
static void Gpt_Isr_A(
  Gpt_ChannelType		Channel_A,
  Gpt_ChannelType		Channel_J
)
{

  register EE_FREG			flags;
  register boolean			init;
  register const Gpt_ConfigType *	cfg;
  register uint32			ris;
  register uint32			mis;
  register Gpt_ChannelType		ch;

  flags = EE_hal_suspendIRQ();
  init = Gpt_Global.Init;
  cfg = Gpt_Global.ConfigPtr;
  ris = GPT_GET_RIS(Channel_A);
  mis = GPT_GET_MIS(Channel_A);
  GPT_INT_CLR(
    Channel_A, GPT_TMRA_INT_ALL | GPT_TMR_INT_WUE | GPT_TMR_INT_RTC
  );
  EE_hal_resumeIRQ(flags);

  if ( 
    ( init == TRUE ) &&
    (
      ( ris & GPT_TMR_INT_TATO ) ||
      ( mis & GPT_TMR_INT_TATO )
    )
  ) {

    /* Channel Look-up */
    for (
      ch = 0;
      (
	( ch < cfg->GptNumberOfGptChannels ) &&
	(
	  ( cfg->GptChannels[ch].GptChannelId != Channel_A ) &&
	  ( cfg->GptChannels[ch].GptChannelId != Channel_J )
	)
      );
      ch++
    ) {
      ;
    }

    /* Notification Callback Call. */
    if (
      ( ch < cfg->GptNumberOfGptChannels ) &&
      ( cfg->GptChannels[ch].GptNotificationPtr != NULL_PTR )
    ) {

      (*(cfg->GptChannels[ch].GptNotificationPtr))();

    }

  }

}
#endif

#if ( \
  defined(EE_CORTEX_MX_TIMER_0_B_ISR) || \
  defined(EE_CORTEX_MX_TIMER_1_B_ISR) || \
  defined(EE_CORTEX_MX_TIMER_2_B_ISR) || \
  defined(EE_CORTEX_MX_TIMER_3_B_ISR) || \
  defined(EE_CORTEX_MX_TIMER_4_B_ISR) || \
  defined(EE_CORTEX_MX_TIMER_5_B_ISR) || \
  defined(EE_CORTEX_MX_WIDE_TIMER_0_B_ISR) || \
  defined(EE_CORTEX_MX_WIDE_TIMER_1_B_ISR) || \
  defined(EE_CORTEX_MX_WIDE_TIMER_2_B_ISR) || \
  defined(EE_CORTEX_MX_WIDE_TIMER_3_B_ISR) || \
  defined(EE_CORTEX_MX_WIDE_TIMER_4_B_ISR) || \
  defined(EE_CORTEX_MX_WIDE_TIMER_5_B_ISR) \
)
static void Gpt_Isr_B(
  Gpt_ChannelType		Channel_B
)
{

  register EE_FREG			flags;
  register boolean			init;
  register const Gpt_ConfigType *	cfg;
  register uint32			ris;
  register uint32			mis;
  register Gpt_ChannelType		ch;

  flags = EE_hal_suspendIRQ();
  init = Gpt_Global.Init;
  cfg = Gpt_Global.ConfigPtr;
  ris = GPT_GET_RIS(Channel_B);
  mis = GPT_GET_MIS(Channel_B);
  GPT_INT_CLR(
    Channel_B, GPT_TMRB_INT_ALL | GPT_TMR_INT_WUE | GPT_TMR_INT_RTC
  );
  EE_hal_resumeIRQ(flags);

  if ( 
    ( init == TRUE ) &&
    (
      ( ris & GPT_TMR_INT_TBTO ) ||
      ( mis & GPT_TMR_INT_TBTO )
    )
  ) {

    /* Channel Look-up */
    for (
      ch = 0;
      (
	( ch < cfg->GptNumberOfGptChannels ) &&
	( cfg->GptChannels[ch].GptChannelId != Channel_B )
      );
      ch++
    ) {
      ;
    }

    /* Notification Callback Call. */
    if (
      ( ch < cfg->GptNumberOfGptChannels ) &&
      ( cfg->GptChannels[ch].GptNotificationPtr != NULL_PTR )
    ) {

      (*(cfg->GptChannels[ch].GptNotificationPtr))();

    }

  }

}
#endif

#ifdef	EE_CORTEX_MX_TIMER_0_A_ISR
/* GPT CHANNEL 0 A or CHANNEL J 0 ISR */
ISR2(EE_CORTEX_MX_TIMER_0_A_ISR)
{
  Gpt_Isr_A(GPT_CHANNEL_0_A, GPT_CHANNEL_J_0);
}
#endif

#ifdef	EE_CORTEX_MX_TIMER_0_B_ISR
/* GPT CHANNEL 0 B ISR */
ISR2(EE_CORTEX_MX_TIMER_0_B_ISR) { Gpt_Isr_B(GPT_CHANNEL_0_B); }
#endif

#ifdef	EE_CORTEX_MX_TIMER_1_A_ISR
/* GPT CHANNEL 1 A or CHANNEL J 1 ISR */
ISR2(EE_CORTEX_MX_TIMER_1_A_ISR)
{
  Gpt_Isr_A(GPT_CHANNEL_1_A, GPT_CHANNEL_J_1);
}
#endif

#ifdef	EE_CORTEX_MX_TIMER_1_B_ISR
/* GPT CHANNEL 1 B ISR */
ISR2(EE_CORTEX_MX_TIMER_1_B_ISR) { Gpt_Isr_B(GPT_CHANNEL_1_B); }
#endif

#ifdef	EE_CORTEX_MX_TIMER_2_A_ISR
/* GPT CHANNEL 2 A or CHANNEL J 2 ISR */
ISR2(EE_CORTEX_MX_TIMER_2_A_ISR)
{
  Gpt_Isr_A(GPT_CHANNEL_2_A, GPT_CHANNEL_J_2);
}
#endif

#ifdef	EE_CORTEX_MX_TIMER_2_B_ISR
/* GPT CHANNEL 2 B ISR */
ISR2(EE_CORTEX_MX_TIMER_2_B_ISR) { Gpt_Isr_B(GPT_CHANNEL_2_B); }
#endif

#ifdef	EE_CORTEX_MX_TIMER_3_A_ISR
/* GPT CHANNEL 3 A or CHANNEL J 3 ISR */
ISR2(EE_CORTEX_MX_TIMER_3_A_ISR)
{
  Gpt_Isr_A(GPT_CHANNEL_0_A, GPT_CHANNEL_J_0);
}
#endif

#ifdef	EE_CORTEX_MX_TIMER_3_B_ISR
/* GPT CHANNEL 3 B ISR */
ISR2(EE_CORTEX_MX_TIMER_3_B_ISR) { Gpt_Isr_B(GPT_CHANNEL_3_B); }
#endif

#ifdef	EE_CORTEX_MX_TIMER_4_A_ISR
/* GPT CHANNEL 4 A or CHANNEL J 4 ISR */
ISR2(EE_CORTEX_MX_TIMER_4_A_ISR)
{
  Gpt_Isr_A(GPT_CHANNEL_4_A, GPT_CHANNEL_J_4);
}
#endif

#ifdef	EE_CORTEX_MX_TIMER_4_B_ISR
/* GPT CHANNEL 4 B ISR */
ISR2(EE_CORTEX_MX_TIMER_4_B_ISR){ Gpt_Isr_B(GPT_CHANNEL_4_B); }
#endif

#ifdef	EE_CORTEX_MX_TIMER_5_A_ISR
/* GPT CHANNEL 5 A or CHANNEL J 5 ISR */
ISR2(EE_CORTEX_MX_TIMER_5_A_ISR)
{
  Gpt_Isr_A(GPT_CHANNEL_0_A, GPT_CHANNEL_J_0);
}
#endif

#ifdef	EE_CORTEX_MX_TIMER_5_B_ISR
/* GPT CHANNEL 5 B ISR */
ISR2(EE_CORTEX_MX_TIMER_5_B_ISR){ Gpt_Isr_B(GPT_CHANNEL_5_B); }
#endif

#ifdef	EE_CORTEX_MX_WIDE_TIMER_0_A_ISR
/* GPT CHANNEL W 0 A or CHANNEL J W 0 ISR */
ISR2(EE_CORTEX_MX_WIDE_TIMER_0_A_ISR)
{
  Gpt_Isr_A(GPT_CHANNEL_W_0_A, GPT_CHANNEL_J_W_0);
}
#endif

#ifdef	EE_CORTEX_MX_WIDE_TIMER_0_B_ISR
/* GPT CHANNEL W 0 B ISR */
ISR2(EE_CORTEX_MX_WIDE_TIMER_0_B_ISR) { Gpt_Isr_B(GPT_CHANNEL_W_0_B); }
#endif

#ifdef	EE_CORTEX_MX_WIDE_TIMER_1_A_ISR
/* GPT CHANNEL W 1 A or CHANNEL J W 1 ISR */
ISR2(EE_CORTEX_MX_WIDE_TIMER_1_A_ISR)
{
  Gpt_Isr_A(GPT_CHANNEL_W_1_A, GPT_CHANNEL_J_W_1);
}
#endif

#ifdef	EE_CORTEX_MX_WIDE_TIMER_1_B_ISR
/* GPT CHANNEL W 1 B ISR */
ISR2(EE_CORTEX_MX_WIDE_TIMER_1_B_ISR) { Gpt_Isr_B(GPT_CHANNEL_W_1_B); }
#endif

#ifdef	EE_CORTEX_MX_WIDE_TIMER_2_A_ISR
/* GPT CHANNEL W 2 A or CHANNEL J W 2 ISR */
ISR2(EE_CORTEX_MX_WIDE_TIMER_2_A_ISR)
{
  Gpt_Isr_A(GPT_CHANNEL_W_2_A, GPT_CHANNEL_J_W_2);
}
#endif

#ifdef	EE_CORTEX_MX_WIDE_TIMER_2_B_ISR
/* GPT CHANNEL W 2 B ISR */
ISR2(EE_CORTEX_MX_WIDE_TIMER_2_B_ISR) { Gpt_Isr_B(GPT_CHANNEL_W_2_B); }
#endif

#ifdef	EE_CORTEX_MX_WIDE_TIMER_3_A_ISR
/* GPT CHANNEL W 3 A or CHANNEL J W 3 ISR */
ISR2(EE_CORTEX_MX_WIDE_TIMER_3_A_ISR)
{
  Gpt_Isr_A(GPT_CHANNEL_W_3_A, GPT_CHANNEL_J_W_3);
}
#endif

#ifdef	EE_CORTEX_MX_WIDE_TIMER_3_B_ISR
/* GPT CHANNEL W 3 B ISR */
ISR2(EE_CORTEX_MX_WIDE_TIMER_3_B_ISR) { Gpt_Isr_B(GPT_CHANNEL_W_3_B); }
#endif

#ifdef	EE_CORTEX_MX_WIDE_TIMER_4_A_ISR
/* GPT CHANNEL W 4 A or CHANNEL J W 4 ISR */
ISR2(EE_CORTEX_MX_WIDE_TIMER_4_A_ISR)
{
  Gpt_Isr_A(GPT_CHANNEL_W_4_A, GPT_CHANNEL_J_W_4);
}
#endif

#ifdef	EE_CORTEX_MX_WIDE_TIMER_4_B_ISR
/* GPT CHANNEL W 4 B ISR */
ISR2(EE_CORTEX_MX_WIDE_TIMER_4_B_ISR) { Gpt_Isr_B(GPT_CHANNEL_W_4_B); }
#endif

#ifdef	EE_CORTEX_MX_WIDE_TIMER_5_A_ISR
/* GPT CHANNEL W 5 A or CHANNEL J W 5 ISR */
ISR2(EE_CORTEX_MX_WIDE_TIMER_5_A_ISR)
{
  Gpt_Isr_A(GPT_CHANNEL_W_5_A, GPT_CHANNEL_J_W_5);
}
#endif

#ifdef	EE_CORTEX_MX_WIDE_TIMER_5_B_ISR
/* GPT CHANNEL W 5 B ISR */
ISR2(EE_CORTEX_MX_WIDE_TIMER_5_B_ISR) { Gpt_Isr_B(GPT_CHANNEL_W_5_B); }
#endif

#endif	/* GPT_NOTIFICATIONS_API */
