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
 * AUTOSAR-"like" SCI Driver Channels ISRs Source File.
 *
 * Author:  2011,  Giuseppe Serano
 */

#define	SCI_AR_RELEASE_MAJOR_VERSION	4
#define	SCI_AR_RELEASE_MINOR_VERSION	0

#include "Sci.h"

/*
 * For included (external) header files:
 * - <MODULENAME>_AR_ RELEASE_MAJOR_VERSION
 * - <MODULENAME>_AR_ RELEASE_MINOR_VERSION
 * shall be verified.
 */
#if !defined( SCI_AR_MAJOR_VERSION ) || \
    ( SCI_AR_MAJOR_VERSION != SCI_AR_RELEASE_MAJOR_VERSION )
#error	Sci_Irq: version mismatch.
#endif

#include "ee.h"
#include "ee_irq.h"
#include "cpu/cortex_mx/inc/ee_nvic.h"

/*
 * SCI Global Configuration Reference.
 */
typedef struct
{
  boolean			Init;		/* SCI Driver Initialized? */

  const Sci_ConfigType *	ConfigPtr;	/* Actual Configuration */

} Sci_GlobalType;
extern Sci_GlobalType Sci_Global;

#if ( SCI_NOTIFICATIONS_API == STD_ON )

#ifdef	EE_CORTEX_MX_UART_0_ISR
/* SCI CHANNEL 0 ISR */
ISR2(EE_CORTEX_MX_UART_0_ISR)
{

  uint32 channel;

  /* Channel Look-up */
  for (
    channel = 0;
    (
      (channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
      (Sci_Global.ConfigPtr->SciChannels[channel].SciChannelId != SCI_CHANNEL_0)
    );
    channel++
  );

  /* Receception Errors */
  if (
    (
	UART0_MIS_R & (
	  UART_MIS_OEMIS | /* UART Overrun Error Masked Interrupt Status      */
	  UART_MIS_BEMIS | /* UART Break Error Masked Interrupt Status	      */
	  UART_MIS_PEMIS | /* UART Parity Error Masked Interrupt Status	      */
	  UART_MIS_FEMIS | /* UART Framing Error Masked Interrupt Status      */
	  UART_MIS_RTMIS   /* UART Receive Time-Out Masked Interrupt Status   */
	)
    ) ||
    (
	UART0_RIS_R & (
	  UART_RIS_OERIS | /* UART Overrun Error Raw Interrupt Status	      */
	  UART_RIS_BERIS | /* UART Break Error Raw Interrupt Status	      */
	  UART_RIS_PERIS | /* UART Parity Error Raw Interrupt Status	      */
	  UART_RIS_FERIS | /* UART Framing Error Raw Interrupt Status	      */
	  UART_RIS_RTRIS   /* UART Receive Time-Out Raw Interrupt Status      */
	)
      )
  ) {

    if (
      (channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
      (Sci_Global.ConfigPtr->SciChannels[channel].SciRxErrNotificationPtr)
    ) /* Call Reception Errors Notifications Callback. */
      (*(Sci_Global.ConfigPtr->SciChannels[channel].SciRxErrNotificationPtr))();

    /* Clear Interrupt */
    UART0_ICR_R |= (
	UART_ICR_OEIC | /* UART Overrun Error Interrupt Clear		      */
	UART_ICR_BEIC | /* UART Break Error Interrupt Clear		      */
	UART_ICR_PEIC | /* UART Parity Error Interrupt Clear		      */
	UART_ICR_FEIC | /* UART Framing Error Interrupt Clear		      */
	UART_ICR_RTIC   /* UART Receive Time-Out Interrupt Clear	      */
    );

  }

  /* Trasnmission Successful */
  else if ((UART0_MIS_R & UART_MIS_TXMIS ) || (UART0_RIS_R & UART_RIS_TXRIS)) {

    if (
      (channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
      (Sci_Global.ConfigPtr->SciChannels[channel].SciTxNotificationPtr)
    ) /* Call Transmission Notifications Callback. */
      (*(Sci_Global.ConfigPtr->SciChannels[channel].SciTxNotificationPtr))();

    /* Clear Interrupt */
    UART0_ICR_R |= UART_ICR_TXIC;

  }

  /* Reception Successful */
  else /* if (
    (UART0_MIS_R & UART_MIS_RXMIS) || (UART0_RIS_R & UART_RIS_RXRIS)
   ) */ {

    if (
      (channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
      (Sci_Global.ConfigPtr->SciChannels[channel].SciRxNotificationPtr)
    ) /* Call Reception Notifications Callback. */
      (*(Sci_Global.ConfigPtr->SciChannels[channel].SciRxNotificationPtr))();

    /* Clear Interrupt */
    UART0_ICR_R |= UART_ICR_RXIC;

  }

  /* NVIC Clear Pending Interrupt */
  /* NVIC_INT_CLR_PENDING(EE_CORTEX_MX_UART_0_INT_NUM); */

}
#endif	/* EE_CORTEX_MX_UART_0_ISR */

#ifdef	EE_CORTEX_MX_UART_1_ISR
/* SCI CHANNEL 1 ISR */
ISR2(EE_CORTEX_MX_UART_1_ISR)
{

  uint32 channel;

  /* Channel Look-up */
  for (
    channel = 0;
    (
      (channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
      (Sci_Global.ConfigPtr->SciChannels[channel].SciChannelId != SCI_CHANNEL_1)
    );
    channel++
  );

  /* Receception Errors */
  if (
    (
	UART1_MIS_R & (
	  UART_MIS_OEMIS | /* UART Overrun Error Masked Interrupt Status      */
	  UART_MIS_BEMIS | /* UART Break Error Masked Interrupt Status	      */
	  UART_MIS_PEMIS | /* UART Parity Error Masked Interrupt Status	      */
	  UART_MIS_FEMIS | /* UART Framing Error Masked Interrupt Status      */
	  UART_MIS_RTMIS   /* UART Receive Time-Out Masked Interrupt Status   */
	)
    ) ||
    (
	UART1_RIS_R & (
	  UART_RIS_OERIS | /* UART Overrun Error Raw Interrupt Status	      */
	  UART_RIS_BERIS | /* UART Break Error Raw Interrupt Status	      */
	  UART_RIS_PERIS | /* UART Parity Error Raw Interrupt Status	      */
	  UART_RIS_FERIS | /* UART Framing Error Raw Interrupt Status	      */
	  UART_RIS_RTRIS   /* UART Receive Time-Out Raw Interrupt Status      */
	)
      )
  ) {

    if (
      (channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
      (Sci_Global.ConfigPtr->SciChannels[channel].SciRxErrNotificationPtr)
    ) /* Call Reception Errors Notifications Callback. */
      (*(Sci_Global.ConfigPtr->SciChannels[channel].SciRxErrNotificationPtr))();

    /* Clear Interrupt */
    UART1_ICR_R |= (
	UART_ICR_OEIC | /* UART Overrun Error Interrupt Clear		      */
	UART_ICR_BEIC | /* UART Break Error Interrupt Clear		      */
	UART_ICR_PEIC | /* UART Parity Error Interrupt Clear		      */
	UART_ICR_FEIC | /* UART Framing Error Interrupt Clear		      */
	UART_ICR_RTIC   /* UART Receive Time-Out Interrupt Clear	      */
    );

  }

  /* Trasnmission Successful */
  else if ((UART1_MIS_R & UART_MIS_TXMIS ) || (UART1_RIS_R & UART_RIS_TXRIS)) {

    if (
      (channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
      (Sci_Global.ConfigPtr->SciChannels[channel].SciTxNotificationPtr)
    ) /* Call Transmission Notifications Callback. */
      (*(Sci_Global.ConfigPtr->SciChannels[channel].SciTxNotificationPtr))();

    /* Clear Interrupt */
    UART1_ICR_R |= UART_ICR_TXIC;

  }

  /* Reception Successful */
  else /* if (
    (UART1_MIS_R & UART_MIS_RXMIS) || (UART1_RIS_R & UART_RIS_RXRIS)
   ) */ {

    if (
      (channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
      (Sci_Global.ConfigPtr->SciChannels[channel].SciRxNotificationPtr)
    ) /* Call Reception Notifications Callback. */
      (*(Sci_Global.ConfigPtr->SciChannels[channel].SciRxNotificationPtr))();

    /* Clear Interrupt */
    UART1_ICR_R |= UART_ICR_RXIC;

  }

  /* NVIC Clear Pending Interrupt */
  /* NVIC_INT_CLR_PENDING(EE_CORTEX_MX_UART_1_INT_NUM); */

}
#endif	/* EE_CORTEX_MX_UART_1_ISR */

#ifdef	EE_CORTEX_MX_UART_2_ISR
/* SCI CHANNEL 2 ISR */
ISR2(EE_CORTEX_MX_UART_2_ISR)
{

  uint32 channel;

  /* Channel Look-up */
  for (
    channel = 0;
    (
      (channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
      (Sci_Global.ConfigPtr->SciChannels[channel].SciChannelId != SCI_CHANNEL_2)
    );
    channel++
  );

  /* Receception Errors */
  if (
    (
	UART2_MIS_R & (
	  UART_MIS_OEMIS | /* UART Overrun Error Masked Interrupt Status      */
	  UART_MIS_BEMIS | /* UART Break Error Masked Interrupt Status	      */
	  UART_MIS_PEMIS | /* UART Parity Error Masked Interrupt Status	      */
	  UART_MIS_FEMIS | /* UART Framing Error Masked Interrupt Status      */
	  UART_MIS_RTMIS   /* UART Receive Time-Out Masked Interrupt Status   */
	)
    ) ||
    (
	UART2_RIS_R & (
	  UART_RIS_OERIS | /* UART Overrun Error Raw Interrupt Status	      */
	  UART_RIS_BERIS | /* UART Break Error Raw Interrupt Status	      */
	  UART_RIS_PERIS | /* UART Parity Error Raw Interrupt Status	      */
	  UART_RIS_FERIS | /* UART Framing Error Raw Interrupt Status	      */
	  UART_RIS_RTRIS   /* UART Receive Time-Out Raw Interrupt Status      */
	)
      )
  ) {

    if (
      (channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
      (Sci_Global.ConfigPtr->SciChannels[channel].SciRxErrNotificationPtr)
    ) /* Call Reception Errors Notifications Callback. */
      (*(Sci_Global.ConfigPtr->SciChannels[channel].SciRxErrNotificationPtr))();

    /* Clear Interrupt */
    UART2_ICR_R |= (
	UART_ICR_OEIC | /* UART Overrun Error Interrupt Clear		      */
	UART_ICR_BEIC | /* UART Break Error Interrupt Clear		      */
	UART_ICR_PEIC | /* UART Parity Error Interrupt Clear		      */
	UART_ICR_FEIC | /* UART Framing Error Interrupt Clear		      */
	UART_ICR_RTIC   /* UART Receive Time-Out Interrupt Clear	      */
    );

  }

  /* Trasnmission Successful */
  else if ((UART2_MIS_R & UART_MIS_TXMIS ) || (UART2_RIS_R & UART_RIS_TXRIS)) {

    if (
      (channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
      (Sci_Global.ConfigPtr->SciChannels[channel].SciTxNotificationPtr)
    ) /* Call Transmission Notifications Callback. */
      (*(Sci_Global.ConfigPtr->SciChannels[channel].SciTxNotificationPtr))();

    /* Clear Interrupt */
    UART2_ICR_R |= UART_ICR_TXIC;

  }

  /* Reception Successful */
  else /* if (
    (UART2_MIS_R & UART_MIS_RXMIS) || (UART2_RIS_R & UART_RIS_RXRIS)
   ) */ {

    if (
      (channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
      (Sci_Global.ConfigPtr->SciChannels[channel].SciRxNotificationPtr)
    ) /* Call Reception Notifications Callback. */
      (*(Sci_Global.ConfigPtr->SciChannels[channel].SciRxNotificationPtr))();

    /* Clear Interrupt */
    UART2_ICR_R |= UART_ICR_RXIC;

  }

  /* NVIC Clear Pending Interrupt */
  /* NVIC_INT_CLR_PENDING(EE_CORTEX_MX_UART_2_INT_NUM); */

}
#endif	/* EE_CORTEX_MX_UART_2_ISR */

#ifdef	EE_CORTEX_MX_UART_3_ISR
/* SCI CHANNEL 3 ISR */
ISR2(EE_CORTEX_MX_UART_3_ISR)
{

  uint32 channel;

  /* Channel Look-up */
  for (
    channel = 0;
    (
      (channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
      (Sci_Global.ConfigPtr->SciChannels[channel].SciChannelId != SCI_CHANNEL_3)
    );
    channel++
  );

  /* Receception Errors */
  if (
    (
	UART3_MIS_R & (
	  UART_MIS_OEMIS | /* UART Overrun Error Masked Interrupt Status      */
	  UART_MIS_BEMIS | /* UART Break Error Masked Interrupt Status	      */
	  UART_MIS_PEMIS | /* UART Parity Error Masked Interrupt Status	      */
	  UART_MIS_FEMIS | /* UART Framing Error Masked Interrupt Status      */
	  UART_MIS_RTMIS   /* UART Receive Time-Out Masked Interrupt Status   */
	)
    ) ||
    (
	UART3_RIS_R & (
	  UART_RIS_OERIS | /* UART Overrun Error Raw Interrupt Status	      */
	  UART_RIS_BERIS | /* UART Break Error Raw Interrupt Status	      */
	  UART_RIS_PERIS | /* UART Parity Error Raw Interrupt Status	      */
	  UART_RIS_FERIS | /* UART Framing Error Raw Interrupt Status	      */
	  UART_RIS_RTRIS   /* UART Receive Time-Out Raw Interrupt Status      */
	)
      )
  ) {

    if (
      (channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
      (Sci_Global.ConfigPtr->SciChannels[channel].SciRxErrNotificationPtr)
    ) /* Call Reception Errors Notifications Callback. */
      (*(Sci_Global.ConfigPtr->SciChannels[channel].SciRxErrNotificationPtr))();

    /* Clear Interrupt */
    UART3_ICR_R |= (
	UART_ICR_OEIC | /* UART Overrun Error Interrupt Clear		      */
	UART_ICR_BEIC | /* UART Break Error Interrupt Clear		      */
	UART_ICR_PEIC | /* UART Parity Error Interrupt Clear		      */
	UART_ICR_FEIC | /* UART Framing Error Interrupt Clear		      */
	UART_ICR_RTIC   /* UART Receive Time-Out Interrupt Clear	      */
    );

  }

  /* Trasnmission Successful */
  else if ((UART3_MIS_R & UART_MIS_TXMIS ) || (UART3_RIS_R & UART_RIS_TXRIS)) {

    if (
      (channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
      (Sci_Global.ConfigPtr->SciChannels[channel].SciTxNotificationPtr)
    ) /* Call Transmission Notifications Callback. */
      (*(Sci_Global.ConfigPtr->SciChannels[channel].SciTxNotificationPtr))();

    /* Clear Interrupt */
    UART3_ICR_R |= UART_ICR_TXIC;

  }

  /* Reception Successful */
  else /* if (
    (UART3_MIS_R & UART_MIS_RXMIS) || (UART3_RIS_R & UART_RIS_RXRIS)
   ) */ {

    if (
      (channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
      (Sci_Global.ConfigPtr->SciChannels[channel].SciRxNotificationPtr)
    ) /* Call Reception Notifications Callback. */
      (*(Sci_Global.ConfigPtr->SciChannels[channel].SciRxNotificationPtr))();

    /* Clear Interrupt */
    UART3_ICR_R |= UART_ICR_RXIC;

  }

  /* NVIC Clear Pending Interrupt */
  /* NVIC_INT_CLR_PENDING(EE_CORTEX_MX_UART_3_INT_NUM); */

}
#endif	/* EE_CORTEX_MX_UART_3_ISR */

#ifdef	EE_CORTEX_MX_UART_4_ISR
/* SCI CHANNEL 4 ISR */
ISR2(EE_CORTEX_MX_UART_4_ISR)
{

  uint32 channel;

  /* Channel Look-up */
  for (
    channel = 0;
    (
      (channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
      (Sci_Global.ConfigPtr->SciChannels[channel].SciChannelId != SCI_CHANNEL_4)
    );
    channel++
  );

  /* Receception Errors */
  if (
    (
	UART4_MIS_R & (
	  UART_MIS_OEMIS | /* UART Overrun Error Masked Interrupt Status      */
	  UART_MIS_BEMIS | /* UART Break Error Masked Interrupt Status	      */
	  UART_MIS_PEMIS | /* UART Parity Error Masked Interrupt Status	      */
	  UART_MIS_FEMIS | /* UART Framing Error Masked Interrupt Status      */
	  UART_MIS_RTMIS   /* UART Receive Time-Out Masked Interrupt Status   */
	)
    ) ||
    (
	UART4_RIS_R & (
	  UART_RIS_OERIS | /* UART Overrun Error Raw Interrupt Status	      */
	  UART_RIS_BERIS | /* UART Break Error Raw Interrupt Status	      */
	  UART_RIS_PERIS | /* UART Parity Error Raw Interrupt Status	      */
	  UART_RIS_FERIS | /* UART Framing Error Raw Interrupt Status	      */
	  UART_RIS_RTRIS   /* UART Receive Time-Out Raw Interrupt Status      */
	)
      )
  ) {

    if (
      (channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
      (Sci_Global.ConfigPtr->SciChannels[channel].SciRxErrNotificationPtr)
    ) /* Call Reception Errors Notifications Callback. */
      (*(Sci_Global.ConfigPtr->SciChannels[channel].SciRxErrNotificationPtr))();

    /* Clear Interrupt */
    UART4_ICR_R |= (
	UART_ICR_OEIC | /* UART Overrun Error Interrupt Clear		      */
	UART_ICR_BEIC | /* UART Break Error Interrupt Clear		      */
	UART_ICR_PEIC | /* UART Parity Error Interrupt Clear		      */
	UART_ICR_FEIC | /* UART Framing Error Interrupt Clear		      */
	UART_ICR_RTIC   /* UART Receive Time-Out Interrupt Clear	      */
    );

  }

  /* Trasnmission Successful */
  else if ((UART4_MIS_R & UART_MIS_TXMIS ) || (UART4_RIS_R & UART_RIS_TXRIS)) {

    if (
      (channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
      (Sci_Global.ConfigPtr->SciChannels[channel].SciTxNotificationPtr)
    ) /* Call Transmission Notifications Callback. */
      (*(Sci_Global.ConfigPtr->SciChannels[channel].SciTxNotificationPtr))();

    /* Clear Interrupt */
    UART4_ICR_R |= UART_ICR_TXIC;

  }

  /* Reception Successful */
  else /* if (
    (UART4_MIS_R & UART_MIS_RXMIS) || (UART4_RIS_R & UART_RIS_RXRIS)
   ) */ {

    if (
      (channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
      (Sci_Global.ConfigPtr->SciChannels[channel].SciRxNotificationPtr)
    ) /* Call Reception Notifications Callback. */
      (*(Sci_Global.ConfigPtr->SciChannels[channel].SciRxNotificationPtr))();

    /* Clear Interrupt */
    UART4_ICR_R |= UART_ICR_RXIC;

  }

  /* NVIC Clear Pending Interrupt */
  /* NVIC_INT_CLR_PENDING(EE_CORTEX_MX_UART_4_INT_NUM); */

}
#endif	/* EE_CORTEX_MX_UART_4_ISR */

#ifdef	EE_CORTEX_MX_UART_5_ISR
/* SCI CHANNEL 5 ISR */
ISR2(EE_CORTEX_MX_UART_5_ISR)
{

  uint32 channel;

  /* Channel Look-up */
  for (
    channel = 0;
    (
      (channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
      (Sci_Global.ConfigPtr->SciChannels[channel].SciChannelId != SCI_CHANNEL_5)
    );
    channel++
  );

  /* Receception Errors */
  if (
    (
	UART5_MIS_R & (
	  UART_MIS_OEMIS | /* UART Overrun Error Masked Interrupt Status      */
	  UART_MIS_BEMIS | /* UART Break Error Masked Interrupt Status	      */
	  UART_MIS_PEMIS | /* UART Parity Error Masked Interrupt Status	      */
	  UART_MIS_FEMIS | /* UART Framing Error Masked Interrupt Status      */
	  UART_MIS_RTMIS   /* UART Receive Time-Out Masked Interrupt Status   */
	)
    ) ||
    (
	UART5_RIS_R & (
	  UART_RIS_OERIS | /* UART Overrun Error Raw Interrupt Status	      */
	  UART_RIS_BERIS | /* UART Break Error Raw Interrupt Status	      */
	  UART_RIS_PERIS | /* UART Parity Error Raw Interrupt Status	      */
	  UART_RIS_FERIS | /* UART Framing Error Raw Interrupt Status	      */
	  UART_RIS_RTRIS   /* UART Receive Time-Out Raw Interrupt Status      */
	)
      )
  ) {

    if (
      (channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
      (Sci_Global.ConfigPtr->SciChannels[channel].SciRxErrNotificationPtr)
    ) /* Call Reception Errors Notifications Callback. */
      (*(Sci_Global.ConfigPtr->SciChannels[channel].SciRxErrNotificationPtr))();

    /* Clear Interrupt */
    UART5_ICR_R |= (
	UART_ICR_OEIC | /* UART Overrun Error Interrupt Clear		      */
	UART_ICR_BEIC | /* UART Break Error Interrupt Clear		      */
	UART_ICR_PEIC | /* UART Parity Error Interrupt Clear		      */
	UART_ICR_FEIC | /* UART Framing Error Interrupt Clear		      */
	UART_ICR_RTIC   /* UART Receive Time-Out Interrupt Clear	      */
    );

  }

  /* Trasnmission Successful */
  else if ((UART5_MIS_R & UART_MIS_TXMIS ) || (UART5_RIS_R & UART_RIS_TXRIS)) {

    if (
      (channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
      (Sci_Global.ConfigPtr->SciChannels[channel].SciTxNotificationPtr)
    ) /* Call Transmission Notifications Callback. */
      (*(Sci_Global.ConfigPtr->SciChannels[channel].SciTxNotificationPtr))();

    /* Clear Interrupt */
    UART5_ICR_R |= UART_ICR_TXIC;

  }

  /* Reception Successful */
  else /* if (
    (UART5_MIS_R & UART_MIS_RXMIS) || (UART5_RIS_R & UART_RIS_RXRIS)
   ) */ {

    if (
      (channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
      (Sci_Global.ConfigPtr->SciChannels[channel].SciRxNotificationPtr)
    ) /* Call Reception Notifications Callback. */
      (*(Sci_Global.ConfigPtr->SciChannels[channel].SciRxNotificationPtr))();

    /* Clear Interrupt */
    UART5_ICR_R |= UART_ICR_RXIC;

  }

  /* NVIC Clear Pending Interrupt */
  /* NVIC_INT_CLR_PENDING(EE_CORTEX_MX_UART_5_INT_NUM); */

}
#endif	/* EE_CORTEX_MX_UART_5_ISR */

#ifdef	EE_CORTEX_MX_UART_6_ISR
/* SCI CHANNEL 6 ISR */
ISR2(EE_CORTEX_MX_UART_6_ISR)
{

  uint32 channel;

  /* Channel Look-up */
  for (
    channel = 0;
    (
      (channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
      (Sci_Global.ConfigPtr->SciChannels[channel].SciChannelId != SCI_CHANNEL_6)
    );
    channel++
  );

  /* Receception Errors */
  if (
    (
	UART6_MIS_R & (
	  UART_MIS_OEMIS | /* UART Overrun Error Masked Interrupt Status      */
	  UART_MIS_BEMIS | /* UART Break Error Masked Interrupt Status	      */
	  UART_MIS_PEMIS | /* UART Parity Error Masked Interrupt Status	      */
	  UART_MIS_FEMIS | /* UART Framing Error Masked Interrupt Status      */
	  UART_MIS_RTMIS   /* UART Receive Time-Out Masked Interrupt Status   */
	)
    ) ||
    (
	UART6_RIS_R & (
	  UART_RIS_OERIS | /* UART Overrun Error Raw Interrupt Status	      */
	  UART_RIS_BERIS | /* UART Break Error Raw Interrupt Status	      */
	  UART_RIS_PERIS | /* UART Parity Error Raw Interrupt Status	      */
	  UART_RIS_FERIS | /* UART Framing Error Raw Interrupt Status	      */
	  UART_RIS_RTRIS   /* UART Receive Time-Out Raw Interrupt Status      */
	)
      )
  ) {

    if (
      (channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
      (Sci_Global.ConfigPtr->SciChannels[channel].SciRxErrNotificationPtr)
    ) /* Call Reception Errors Notifications Callback. */
      (*(Sci_Global.ConfigPtr->SciChannels[channel].SciRxErrNotificationPtr))();

    /* Clear Interrupt */
    UART6_ICR_R |= (
	UART_ICR_OEIC | /* UART Overrun Error Interrupt Clear		      */
	UART_ICR_BEIC | /* UART Break Error Interrupt Clear		      */
	UART_ICR_PEIC | /* UART Parity Error Interrupt Clear		      */
	UART_ICR_FEIC | /* UART Framing Error Interrupt Clear		      */
	UART_ICR_RTIC   /* UART Receive Time-Out Interrupt Clear	      */
    );

  }

  /* Trasnmission Successful */
  else if ((UART6_MIS_R & UART_MIS_TXMIS ) || (UART6_RIS_R & UART_RIS_TXRIS)) {

    if (
      (channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
      (Sci_Global.ConfigPtr->SciChannels[channel].SciTxNotificationPtr)
    ) /* Call Transmission Notifications Callback. */
      (*(Sci_Global.ConfigPtr->SciChannels[channel].SciTxNotificationPtr))();

    /* Clear Interrupt */
    UART6_ICR_R |= UART_ICR_TXIC;

  }

  /* Reception Successful */
  else /* if (
    (UART6_MIS_R & UART_MIS_RXMIS) || (UART6_RIS_R & UART_RIS_RXRIS)
   ) */ {

    if (
      (channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
      (Sci_Global.ConfigPtr->SciChannels[channel].SciRxNotificationPtr)
    ) /* Call Reception Notifications Callback. */
      (*(Sci_Global.ConfigPtr->SciChannels[channel].SciRxNotificationPtr))();

    /* Clear Interrupt */
    UART6_ICR_R |= UART_ICR_RXIC;

  }

  /* NVIC Clear Pending Interrupt */
  /* NVIC_INT_CLR_PENDING(EE_CORTEX_MX_UART_6_INT_NUM); */

}
#endif	/* EE_CORTEX_MX_UART_6_ISR */

#ifdef	EE_CORTEX_MX_UART_7_ISR
/* SCI CHANNEL 7 ISR */
ISR2(EE_CORTEX_MX_UART_7_ISR)
{

  uint32 channel;

  /* Channel Look-up */
  for (
    channel = 0;
    (
      (channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
      (Sci_Global.ConfigPtr->SciChannels[channel].SciChannelId != SCI_CHANNEL_7)
    );
    channel++
  );

  /* Receception Errors */
  if (
    (
	UART7_MIS_R & (
	  UART_MIS_OEMIS | /* UART Overrun Error Masked Interrupt Status      */
	  UART_MIS_BEMIS | /* UART Break Error Masked Interrupt Status	      */
	  UART_MIS_PEMIS | /* UART Parity Error Masked Interrupt Status	      */
	  UART_MIS_FEMIS | /* UART Framing Error Masked Interrupt Status      */
	  UART_MIS_RTMIS   /* UART Receive Time-Out Masked Interrupt Status   */
	)
    ) ||
    (
	UART7_RIS_R & (
	  UART_RIS_OERIS | /* UART Overrun Error Raw Interrupt Status	      */
	  UART_RIS_BERIS | /* UART Break Error Raw Interrupt Status	      */
	  UART_RIS_PERIS | /* UART Parity Error Raw Interrupt Status	      */
	  UART_RIS_FERIS | /* UART Framing Error Raw Interrupt Status	      */
	  UART_RIS_RTRIS   /* UART Receive Time-Out Raw Interrupt Status      */
	)
      )
  ) {

    if (
      (channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
      (Sci_Global.ConfigPtr->SciChannels[channel].SciRxErrNotificationPtr)
    ) /* Call Reception Errors Notifications Callback. */
      (*(Sci_Global.ConfigPtr->SciChannels[channel].SciRxErrNotificationPtr))();

    /* Clear Interrupt */
    UART7_ICR_R |= (
	UART_ICR_OEIC | /* UART Overrun Error Interrupt Clear		      */
	UART_ICR_BEIC | /* UART Break Error Interrupt Clear		      */
	UART_ICR_PEIC | /* UART Parity Error Interrupt Clear		      */
	UART_ICR_FEIC | /* UART Framing Error Interrupt Clear		      */
	UART_ICR_RTIC   /* UART Receive Time-Out Interrupt Clear	      */
    );

  }

  /* Trasnmission Successful */
  else if ((UART7_MIS_R & UART_MIS_TXMIS ) || (UART7_RIS_R & UART_RIS_TXRIS)) {

    if (
      (channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
      (Sci_Global.ConfigPtr->SciChannels[channel].SciTxNotificationPtr)
    ) /* Call Transmission Notifications Callback. */
      (*(Sci_Global.ConfigPtr->SciChannels[channel].SciTxNotificationPtr))();

    /* Clear Interrupt */
    UART7_ICR_R |= UART_ICR_TXIC;

  }

  /* Reception Successful */
  else /* if (
    (UART7_MIS_R & UART_MIS_RXMIS) || (UART7_RIS_R & UART_RIS_RXRIS)
   ) */ {

    if (
      (channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
      (Sci_Global.ConfigPtr->SciChannels[channel].SciRxNotificationPtr)
    ) /* Call Reception Notifications Callback. */
      (*(Sci_Global.ConfigPtr->SciChannels[channel].SciRxNotificationPtr))();

    /* Clear Interrupt */
    UART7_ICR_R |= UART_ICR_RXIC;

  }

  /* NVIC Clear Pending Interrupt */
  /* NVIC_INT_CLR_PENDING(EE_CORTEX_MX_UART_7_INT_NUM); */

}
#endif	/* EE_CORTEX_MX_UART_7_ISR */

#endif	/* SCI_NOTIFICATIONS_API */

