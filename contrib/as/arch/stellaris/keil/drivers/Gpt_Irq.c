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
#include "cpu/cortex_mx/inc/ee_nvic.h"

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

/*
 * Hardware Timers Interrupt Sources
 */
#define	GPT_TMR_INT_WUEIM	0x00010000	/* 32/64-Bit Write Update     */
#define	GPT_TMR_INT_TBMIM	0x00000800	/* Timer B Mode Match	      */
#define	GPT_TMR_INT_CBEIM	0x00000400	/* Capture B Event	      */
#define	GPT_TMR_INT_CBMIM	0x00000200	/* Capture B Match	      */
#define	GPT_TMR_INT_TBTOIM	0x00000100	/* Timer B Time-Out	      */
#define	GPT_TMR_INT_TAMIM	0x00000010	/* Timer A Mode Match	      */
#define	GPT_TMR_INT_RTCIM	0x00000008	/* RTC Interrupt	      */
#define	GPT_TMR_INT_CAEIM	0x00000004	/* Capture A Event	      */
#define	GPT_TMR_INT_CAMIM	0x00000002	/* Capture A Match	      */
#define	GPT_TMR_INT_TATOIM	0x00000001	/* Timer A Time-Out	      */

/*
 * Hardware Timer A Interrupt Sources
 */
#define	GPT_TMRA_INT_ALL	( \
	GPT_TMR_INT_TAMIM	|	GPT_TMR_INT_CAEIM	| \
	GPT_TMR_INT_CAMIM	|	GPT_TMR_INT_TATOIM	\
)

/*
 * Hardware Timer B Interrupt Sources
 */
#define	GPT_TMRB_INT_ALL	( \
	GPT_TMR_INT_TBMIM	|	GPT_TMR_INT_CBEIM	| \
	GPT_TMR_INT_CBMIM	|	GPT_TMR_INT_TBTOIM	\
)

/*
 * All Hardware Timers Interrupts
 */
#define	GPT_TMR_INT_ALL	( \
	GPT_TMR_INT_WUEIM	|	GPT_TMR_INT_RTCIM	| \
	GPT_TMRA_INT_ALL	|	GPT_TMRB_INT_ALL	\
)

#if ( GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )

#ifdef	EE_CORTEX_MX_TIMER_0_A_ISR
/* GPT CHANNEL 0 A or CHANNEL J 0 ISR */
ISR2(EE_CORTEX_MX_TIMER_0_A_ISR)
{

  register uint32 channel;

  /* Channel Look-up */
  for (
    channel = 0;
    (
      (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
      (
	(
	  Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	  GPT_CHANNEL_0_A
	) && (
	  Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	  GPT_CHANNEL_J_0
	)
      )
    );
    channel++
  );

  /* Notification Callback Call. */
  if (
    (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
    (Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr != NULL_PTR)
  ) (*(Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr))();

  /* GPTM Timer A Time-Out Interrupt Clear */
  TIMER0_ICR_R |= GPT_TMRA_INT_ALL | GPT_TMR_INT_WUEIM | GPT_TMR_INT_RTCIM;

  /* NVIC Clear Pending Interrupt */
  /* NVIC_INT_CLR_PENDING(EE_CORTEX_MX_TIMER_0_A_INT_NUM); */

}
#endif	/* EE_CORTEX_MX_TIMER_0_A_ISR */

#ifdef	EE_CORTEX_MX_TIMER_0_B_ISR
/* GPT CHANNEL 0 B ISR */
ISR2(EE_CORTEX_MX_TIMER_0_B_ISR)
{

  register uint32 channel;

  /* Channel Look-up */
  for (
    channel = 0;
    (
      (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
      (
	Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	GPT_CHANNEL_0_B
      )
    );
    channel++
  );

  /* Notification Callback Call. */
  if (
    (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
    (Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr != NULL_PTR)
  ) (*(Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr))();

  /* GPTM Timer B Time-Out Interrupt Clear */
  TIMER0_ICR_R |= GPT_TMRB_INT_ALL | GPT_TMR_INT_WUEIM | GPT_TMR_INT_RTCIM;

  /* NVIC Clear Pending Interrupt */
  /* NVIC_INT_CLR_PENDING(EE_CORTEX_MX_TIMER_0_B_INT_NUM); */

}
#endif	/* EE_CORTEX_MX_TIMER_0_B_ISR */

#ifdef	EE_CORTEX_MX_TIMER_1_A_ISR
/* GPT CHANNEL 1 A or CHANNEL J 1 ISR */
ISR2(EE_CORTEX_MX_TIMER_1_A_ISR)
{

  register uint32 channel;

  /* Channel Look-up */
  for (
    channel = 0;
    (
      (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
      (
	(
	  Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	  GPT_CHANNEL_1_A
	) && (
	  Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	  GPT_CHANNEL_J_1
	)
      )
    );
    channel++
  );

  /* Notification Callback Call. */
  if (
    (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
    (Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr != NULL_PTR)
  ) (*(Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr))();

  /* GPTM Timer A Time-Out Interrupt Clear */
  TIMER1_ICR_R |= GPT_TMRA_INT_ALL | GPT_TMR_INT_WUEIM | GPT_TMR_INT_RTCIM;

  /* NVIC Clear Pending Interrupt */
  /* NVIC_INT_CLR_PENDING(EE_CORTEX_MX_TIMER_1_A_INT_NUM); */

}
#endif	/* EE_CORTEX_MX_TIMER_1_A_ISR */

#ifdef	EE_CORTEX_MX_TIMER_1_B_ISR
/* GPT CHANNEL 1 B ISR */
ISR2(EE_CORTEX_MX_TIMER_1_B_ISR)
{

  register uint32 channel;

  /* Channel Look-up */
  for (
    channel = 0;
    (
      (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
      (
	Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	GPT_CHANNEL_1_B
      )
    );
    channel++
  );

  /* Notification Callback Call. */
  if (
    (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
    (Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr != NULL_PTR)
  ) (*(Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr))();

  /* GPTM Timer B Time-Out Interrupt Clear */
  TIMER1_ICR_R |= GPT_TMRB_INT_ALL | GPT_TMR_INT_WUEIM | GPT_TMR_INT_RTCIM;

  /* NVIC Clear Pending Interrupt */
  /* NVIC_INT_CLR_PENDING(EE_CORTEX_MX_TIMER_1_B_INT_NUM); */

}
#endif	/* EE_CORTEX_MX_TIMER_1_B_ISR */

#ifdef	EE_CORTEX_MX_TIMER_2_A_ISR
/* GPT CHANNEL 2 A or CHANNEL J 2 ISR */
ISR2(EE_CORTEX_MX_TIMER_2_A_ISR)
{

  register uint32 channel;

  /* Channel Look-up */
  for (
    channel = 0;
    (
      (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
      (
	(
	  Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	  GPT_CHANNEL_2_A
	) && (
	  Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	  GPT_CHANNEL_J_2
	)
      )
    );
    channel++
  );

  /* Notification Callback Call. */
  if (
    (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
    (Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr != NULL_PTR)
  ) (*(Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr))();

  /* GPTM Timer A Time-Out Interrupt Clear */
  TIMER2_ICR_R |= GPT_TMRA_INT_ALL | GPT_TMR_INT_WUEIM | GPT_TMR_INT_RTCIM;

  /* NVIC Clear Pending Interrupt */
  /* NVIC_INT_CLR_PENDING(EE_CORTEX_MX_TIMER_2_A_INT_NUM); */

}
#endif	/* EE_CORTEX_MX_TIMER_2_A_ISR */

#ifdef	EE_CORTEX_MX_TIMER_2_B_ISR
/* GPT CHANNEL 2 B ISR */
ISR2(EE_CORTEX_MX_TIMER_2_B_ISR)
{

  register uint32 channel;

  /* Channel Look-up */
  for (
    channel = 0;
    (
      (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
      (
	Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	GPT_CHANNEL_2_B
      )
    );
    channel++
  );

  /* Notification Callback Call. */
  if (
    (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
    (Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr != NULL_PTR)
  ) (*(Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr))();

  /* GPTM Timer B Time-Out Interrupt Clear */
  TIMER2_ICR_R |= GPT_TMRB_INT_ALL | GPT_TMR_INT_WUEIM | GPT_TMR_INT_RTCIM;

  /* NVIC Clear Pending Interrupt */
  /* NVIC_INT_CLR_PENDING(EE_CORTEX_MX_TIMER_2_B_INT_NUM); */

}
#endif	/* EE_CORTEX_MX_TIMER_2_B_ISR */

#ifdef	EE_CORTEX_MX_TIMER_3_A_ISR
/* GPT CHANNEL 3 A or CHANNEL J 3 ISR */
ISR2(EE_CORTEX_MX_TIMER_3_A_ISR)
{

  register uint32 channel;

  /* Channel Look-up */
  for (
    channel = 0;
    (
      (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
      (
	(
	  Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	  GPT_CHANNEL_3_A
	) && (
	  Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	  GPT_CHANNEL_J_3
      )
    );
    channel++
  );

  /* Notification Callback Call. */
  if (
    (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
    (Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr != NULL_PTR)
  ) (*(Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr))();

  /* GPTM Timer A Time-Out Interrupt Clear */
  TIMER3_ICR_R |= GPT_TMRA_INT_ALL | GPT_TMR_INT_WUEIM | GPT_TMR_INT_RTCIM;

  /* NVIC Clear Pending Interrupt */
  /* NVIC_INT_CLR_PENDING(EE_CORTEX_MX_TIMER_3_A_INT_NUM); */

}
#endif	/* EE_CORTEX_MX_TIMER_3_A_ISR */

#ifdef	EE_CORTEX_MX_TIMER_3_B_ISR
/* GPT CHANNEL 3 B ISR */
ISR2(EE_CORTEX_MX_TIMER_3_B_ISR)
{

  register uint32 channel;

  /* Channel Look-up */
  for (
    channel = 0;
    (
      (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
      (
	Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	GPT_CHANNEL_3_B
      )
    );
    channel++
  );

  /* Notification Callback Call. */
  if (
    (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
    (Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr != NULL_PTR)
  ) (*(Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr))();

  /* GPTM Timer B Time-Out Interrupt Clear */
  TIMER3_ICR_R |= GPT_TMRB_INT_ALL | GPT_TMR_INT_WUEIM | GPT_TMR_INT_RTCIM;

  /* NVIC Clear Pending Interrupt */
  /* NVIC_INT_CLR_PENDING(EE_CORTEX_MX_TIMER_3_B_INT_NUM); */

}
#endif	/* EE_CORTEX_MX_TIMER_3_B_ISR */

#ifdef	EE_CORTEX_MX_TIMER_4_A_ISR
/* GPT CHANNEL 4 A or CHANNEL J 4 ISR */
ISR2(EE_CORTEX_MX_TIMER_4_A_ISR)
{

  register uint32 channel;

  /* Channel Look-up */
  for (
    channel = 0;
    (
      (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
      (
	(
	  Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	  GPT_CHANNEL_4_A
	) && (
	  Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	  GPT_CHANNEL_J_4
      )
    );
    channel++
  );

  /* Notification Callback Call. */
  if (
    (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
    (Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr != NULL_PTR)
  ) (*(Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr))();

  /* GPTM Timer A Time-Out Interrupt Clear */
  TIMER4_ICR_R |= GPT_TMRA_INT_ALL | GPT_TMR_INT_WUEIM | GPT_TMR_INT_RTCIM;

  /* NVIC Clear Pending Interrupt */
  /* NVIC_INT_CLR_PENDING(EE_CORTEX_MX_TIMER_4_A_INT_NUM); */

}
#endif	/* EE_CORTEX_MX_TIMER_4_A_ISR */

#ifdef	EE_CORTEX_MX_TIMER_4_B_ISR
/* GPT CHANNEL 4 B ISR */
ISR2(EE_CORTEX_MX_TIMER_4_B_ISR)
{

  register uint32 channel;

  /* Channel Look-up */
  for (
    channel = 0;
    (
      (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
      (
	Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	GPT_CHANNEL_4_B
      )
    );
    channel++
  );

  /* Notification Callback Call. */
  if (
    (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
    (Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr != NULL_PTR)
  ) (*(Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr))();

  /* GPTM Timer B Time-Out Interrupt Clear */
  TIMER4_ICR_R |= GPT_TMRB_INT_ALL | GPT_TMR_INT_WUEIM | GPT_TMR_INT_RTCIM;

  /* NVIC Clear Pending Interrupt */
  /* NVIC_INT_CLR_PENDING(EE_CORTEX_MX_TIMER_4_B_INT_NUM); */

}
#endif	/* EE_CORTEX_MX_TIMER_4_B_ISR */

#ifdef	EE_CORTEX_MX_TIMER_5_A_ISR
/* GPT CHANNEL 5 A or CHANNEL J 5 ISR */
ISR2(EE_CORTEX_MX_TIMER_5_A_ISR)
{

  register uint32 channel;

  /* Channel Look-up */
  for (
    channel = 0;
    (
      (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
      (
	(
	  Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	  GPT_CHANNEL_5_A
	) && (
	  Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	  GPT_CHANNEL_J_5
      )
    );
    channel++
  );

  /* Notification Callback Call. */
  if (
    (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
    (Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr != NULL_PTR)
  ) (*(Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr))();

  /* GPTM Timer A Time-Out Interrupt Clear */
  TIMER5_ICR_R |= GPT_TMRA_INT_ALL | GPT_TMR_INT_WUEIM | GPT_TMR_INT_RTCIM;

  /* NVIC Clear Pending Interrupt */
  /* NVIC_INT_CLR_PENDING(EE_CORTEX_MX_TIMER_5_A_INT_NUM); */

}
#endif	/* EE_CORTEX_MX_TIMER_5_A_ISR */

#ifdef	EE_CORTEX_MX_TIMER_5_B_ISR
/* GPT CHANNEL 5 B ISR */
ISR2(EE_CORTEX_MX_TIMER_5_B_ISR)
{

  register uint32 channel;

  /* Channel Look-up */
  for (
    channel = 0;
    (
      (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
      (
	Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	GPT_CHANNEL_5_B
      )
    );
    channel++
  );

  /* Notification Callback Call. */
  if (
    (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
    (Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr != NULL_PTR)
  ) (*(Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr))();

  /* GPTM Timer B Time-Out Interrupt Clear */
  TIMER5_ICR_R |= GPT_TMRB_INT_ALL | GPT_TMR_INT_WUEIM | GPT_TMR_INT_RTCIM;

  /* NVIC Clear Pending Interrupt */
  /* NVIC_INT_CLR_PENDING(EE_CORTEX_MX_TIMER_5_B_INT_NUM); */

}
#endif	/* EE_CORTEX_MX_TIMER_5_B_ISR */

#ifdef	EE_CORTEX_MX_WIDE_TIMER_0_A_ISR
/* GPT CHANNEL W 0 A or CHANNEL J W 0 ISR */
ISR2(EE_CORTEX_MX_WIDE_TIMER_0_A_ISR)
{

  register uint32 channel;

  /* Channel Look-up */
  for (
    channel = 0;
    (
      (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
      (
	(
	  Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	  GPT_CHANNEL_W_0_A
	) && (
	  Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	  GPT_CHANNEL_J_W_0
	)
      )
    );
    channel++
  );

  /* Notification Callback Call. */
  if (
    (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
    (Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr != NULL_PTR)
  ) (*(Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr))();

  /* GPTM Timer A Time-Out Interrupt Clear */
  WTIMER0_ICR_R |= GPT_TMRA_INT_ALL | GPT_TMR_INT_WUEIM | GPT_TMR_INT_RTCIM;

  /* NVIC Clear Pending Interrupt */
  /* NVIC_INT_CLR_PENDING(EE_CORTEX_MX_WIDE_TIMER_0_A_INT_NUM); */

}
#endif	/* EE_CORTEX_MX_WIDE_TIMER_0_A_ISR */

#ifdef	EE_CORTEX_MX_WIDE_TIMER_0_B_ISR
/* GPT CHANNEL W 0 B ISR */
ISR2(EE_CORTEX_MX_WIDE_TIMER_0_B_ISR)
{

  register uint32 channel;

  /* Channel Look-up */
  for (
    channel = 0;
    (
      (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
      (
	Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	GPT_CHANNEL_W_0_B
      )
    );
    channel++
  );

  /* Notification Callback Call. */
  if (
    (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
    (Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr != NULL_PTR)
  ) (*(Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr))();

  /* GPTM Timer B Time-Out Interrupt Clear */
  WTIMER0_ICR_R |= GPT_TMRB_INT_ALL | GPT_TMR_INT_WUEIM | GPT_TMR_INT_RTCIM;

  /* NVIC Clear Pending Interrupt */
  /* NVIC_INT_CLR_PENDING(EE_CORTEX_MX_WIDE_TIMER_0_B_INT_NUM); */

}
#endif	/* EE_CORTEX_MX_WIDE_TIMER_0_B_ISR */

#ifdef	EE_CORTEX_MX_WIDE_TIMER_1_A_ISR
/* GPT CHANNEL W 1 A or CHANNEL J W 1 ISR */
ISR2(EE_CORTEX_MX_WIDE_TIMER_1_A_ISR)
{

  register uint32 channel;

  /* Channel Look-up */
  for (
    channel = 0;
    (
      (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
      (
	(
	  Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	  GPT_CHANNEL_W_1_A
	) && (
	  Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	  GPT_CHANNEL_J_W_1
	)
      )
    );
    channel++
  );

  /* Notification Callback Call. */
  if (
    (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
    (Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr != NULL_PTR)
  ) (*(Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr))();

  /* GPTM Timer A Time-Out Interrupt Clear */
  WTIMER1_ICR_R |= GPT_TMRA_INT_ALL | GPT_TMR_INT_WUEIM | GPT_TMR_INT_RTCIM;

  /* NVIC Clear Pending Interrupt */
  /* NVIC_INT_CLR_PENDING(EE_CORTEX_MX_WIDE_TIMER_1_A_INT_NUM); */

}
#endif	/* EE_CORTEX_MX_WIDE_TIMER_1_A_ISR */

#ifdef	EE_CORTEX_MX_WIDE_TIMER_1_B_ISR
/* GPT CHANNEL W 1 B ISR */
ISR2(EE_CORTEX_MX_WIDE_TIMER_1_B_ISR)
{

  register uint32 channel;

  /* Channel Look-up */
  for (
    channel = 0;
    (
      (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
      (
	Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	GPT_CHANNEL_W_1_B
      )
    );
    channel++
  );

  /* Notification Callback Call. */
  if (
    (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
    (Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr != NULL_PTR)
  ) (*(Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr))();

  /* GPTM Timer B Time-Out Interrupt Clear */
  WTIMER1_ICR_R |= GPT_TMRB_INT_ALL | GPT_TMR_INT_WUEIM | GPT_TMR_INT_RTCIM;

  /* NVIC Clear Pending Interrupt */
  /* NVIC_INT_CLR_PENDING(EE_CORTEX_MX_WIDE_TIMER_1_B_INT_NUM); */

}
#endif	/* EE_CORTEX_MX_WIDE_TIMER_1_B_ISR */

#ifdef	EE_CORTEX_MX_WIDE_TIMER_2_A_ISR
/* GPT CHANNEL W 2 A or CHANNEL J W 2 ISR */
ISR2(EE_CORTEX_MX_WIDE_TIMER_2_A_ISR)
{

  register uint32 channel;

  /* Channel Look-up */
  for (
    channel = 0;
    (
      (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
      (
	(
	  Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	  GPT_CHANNEL_W_2_A
	) && (
	  Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	  GPT_CHANNEL_J_W_2
	)
      )
    );
    channel++
  );

  /* Notification Callback Call. */
  if (
    (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
    (Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr != NULL_PTR)
  ) (*(Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr))();

  /* GPTM Timer A Time-Out Interrupt Clear */
  WTIMER2_ICR_R |= GPT_TMRA_INT_ALL | GPT_TMR_INT_WUEIM | GPT_TMR_INT_RTCIM;

  /* NVIC Clear Pending Interrupt */
  /* NVIC_INT_CLR_PENDING(EE_CORTEX_MX_WIDE_TIMER_2_A_INT_NUM); */

}
#endif	/* EE_CORTEX_MX_WIDE_TIMER_2_A_ISR */

#ifdef	EE_CORTEX_MX_WIDE_TIMER_2_B_ISR
/* GPT CHANNEL W 2 B ISR */
ISR2(EE_CORTEX_MX_WIDE_TIMER_2_B_ISR)
{

  register uint32 channel;

  /* Channel Look-up */
  for (
    channel = 0;
    (
      (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
      (
	Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	GPT_CHANNEL_W_2_B
      )
    );
    channel++
  );

  /* Notification Callback Call. */
  if (
    (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
    (Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr != NULL_PTR)
  ) (*(Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr))();

  /* GPTM Timer B Time-Out Interrupt Clear */
  WTIMER2_ICR_R |= GPT_TMRB_INT_ALL | GPT_TMR_INT_WUEIM | GPT_TMR_INT_RTCIM;

  /* NVIC Clear Pending Interrupt */
  /* NVIC_INT_CLR_PENDING(EE_CORTEX_MX_WIDE_TIMER_2_B_INT_NUM); */

}
#endif	/* EE_CORTEX_MX_WIDE_TIMER_2_B_ISR */

#ifdef	EE_CORTEX_MX_WIDE_TIMER_3_A_ISR
/* GPT CHANNEL W 3 A or CHANNEL J W 3 ISR */
ISR2(EE_CORTEX_MX_WIDE_TIMER_3_A_ISR)
{

  register uint32 channel;

  /* Channel Look-up */
  for (
    channel = 0;
    (
      (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
      (
	(
	  Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	  GPT_CHANNEL_W_3_A
	) && (
	  Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	  GPT_CHANNEL_J_W_3
      )
    );
    channel++
  );

  /* Notification Callback Call. */
  if (
    (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
    (Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr != NULL_PTR)
  ) (*(Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr))();

  /* GPTM Timer A Time-Out Interrupt Clear */
  WTIMER3_ICR_R |= GPT_TMRA_INT_ALL | GPT_TMR_INT_WUEIM | GPT_TMR_INT_RTCIM;

  /* NVIC Clear Pending Interrupt */
  /* NVIC_INT_CLR_PENDING(EE_CORTEX_MX_WIDE_TIMER_3_A_INT_NUM); */

}
#endif	/* EE_CORTEX_MX_WIDE_TIMER_3_A_ISR */

#ifdef	EE_CORTEX_MX_WIDE_TIMER_3_B_ISR
/* GPT CHANNEL W 3 B ISR */
ISR2(EE_CORTEX_MX_WIDE_TIMER_3_B_ISR)
{

  register uint32 channel;

  /* Channel Look-up */
  for (
    channel = 0;
    (
      (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
      (
	Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	GPT_CHANNEL_W_3_B
      )
    );
    channel++
  );

  /* Notification Callback Call. */
  if (
    (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
    (Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr != NULL_PTR)
  ) (*(Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr))();

  /* GPTM Timer B Time-Out Interrupt Clear */
  WTIMER3_ICR_R |= GPT_TMRB_INT_ALL | GPT_TMR_INT_WUEIM | GPT_TMR_INT_RTCIM;

  /* NVIC Clear Pending Interrupt */
  /* NVIC_INT_CLR_PENDING(EE_CORTEX_MX_WIDE_TIMER_3_B_INT_NUM); */

}
#endif	/* EE_CORTEX_MX_WIDE_TIMER_3_B_ISR */

#ifdef	EE_CORTEX_MX_WIDE_TIMER_4_A_ISR
/* GPT CHANNEL W 4 A or CHANNEL J W 4 ISR */
ISR2(EE_CORTEX_MX_WIDE_TIMER_4_A_ISR)
{

  register uint32 channel;

  /* Channel Look-up */
  for (
    channel = 0;
    (
      (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
      (
	(
	  Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	  GPT_CHANNEL_W_4_A
	) && (
	  Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	  GPT_CHANNEL_J_W_4
      )
    );
    channel++
  );

  /* Notification Callback Call. */
  if (
    (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
    (Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr != NULL_PTR)
  ) (*(Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr))();

  /* GPTM Timer A Time-Out Interrupt Clear */
  WTIMER4_ICR_R |= GPT_TMRA_INT_ALL | GPT_TMR_INT_WUEIM | GPT_TMR_INT_RTCIM;

  /* NVIC Clear Pending Interrupt */
  /* NVIC_INT_CLR_PENDING(EE_CORTEX_MX_WIDE_TIMER_4_A_INT_NUM); */

}
#endif	/* EE_CORTEX_MX_WIDE_TIMER_4_A_ISR */

#ifdef	EE_CORTEX_MX_WIDE_TIMER_4_B_ISR
/* GPT CHANNEL W 4 B ISR */
ISR2(EE_CORTEX_MX_WIDE_TIMER_4_B_ISR)
{

  register uint32 channel;

  /* Channel Look-up */
  for (
    channel = 0;
    (
      (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
      (
	Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	GPT_CHANNEL_W_4_B
      )
    );
    channel++
  );

  /* Notification Callback Call. */
  if (
    (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
    (Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr != NULL_PTR)
  ) (*(Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr))();

  /* GPTM Timer B Time-Out Interrupt Clear */
  WTIMER4_ICR_R |= GPT_TMRB_INT_ALL | GPT_TMR_INT_WUEIM | GPT_TMR_INT_RTCIM;

  /* NVIC Clear Pending Interrupt */
  /* NVIC_INT_CLR_PENDING(EE_CORTEX_MX_WIDE_TIMER_4_B_INT_NUM); */

}
#endif	/* EE_CORTEX_MX_WIDE_TIMER_4_B_ISR */

#ifdef	EE_CORTEX_MX_WIDE_TIMER_5_A_ISR
/* GPT CHANNEL W 5 A or CHANNEL J W 5 ISR */
ISR2(EE_CORTEX_MX_WIDE_TIMER_5_A_ISR)
{

  register uint32 channel;

  /* Channel Look-up */
  for (
    channel = 0;
    (
      (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
      (
	(
	  Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	  GPT_CHANNEL_W_5_A
	) && (
	  Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	  GPT_CHANNEL_J_W_5
      )
    );
    channel++
  );

  /* Notification Callback Call. */
  if (
    (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
    (Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr != NULL_PTR)
  ) (*(Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr))();

  /* GPTM Timer A Time-Out Interrupt Clear */
  WTIMER5_ICR_R |= GPT_TMRA_INT_ALL | GPT_TMR_INT_WUEIM | GPT_TMR_INT_RTCIM;

  /* NVIC Clear Pending Interrupt */
  /* NVIC_INT_CLR_PENDING(EE_CORTEX_MX_WIDE_TIMER_5_A_INT_NUM); */

}
#endif	/* EE_CORTEX_MX_WIDE_TIMER_5_A_ISR */

#ifdef	EE_CORTEX_MX_WIDE_TIMER_5_B_ISR
/* GPT CHANNEL W 5 B ISR */
ISR2(EE_CORTEX_MX_WIDE_TIMER_5_B_ISR)
{

  register uint32 channel;

  /* Channel Look-up */
  for (
    channel = 0;
    (
      (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
      (
	Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId !=
	GPT_CHANNEL_W_5_B
      )
    );
    channel++
  );

  /* Notification Callback Call. */
  if (
    (channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
    (Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr != NULL_PTR)
  ) (*(Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr))();

  /* GPTM Timer B Time-Out Interrupt Clear */
  WTIMER5_ICR_R |= GPT_TMRB_INT_ALL | GPT_TMR_INT_WUEIM | GPT_TMR_INT_RTCIM;

  /* NVIC Clear Pending Interrupt */
  /* NVIC_INT_CLR_PENDING(EE_CORTEX_MX_WIDE_TIMER_5_B_INT_NUM); */

}
#endif	/* EE_CORTEX_MX_WIDE_TIMER_5_B_ISR */


#endif	/* GPT_NOTIFICATIONS_API */

