/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2012  Evidence Srl
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
 * SPI372:	Spi_Irq.c File for implementation of interrupt service routine
 * 		(BSW00314)
 *
 * AUTOSAR SPI Handler/Driver Channels ISRs Source File.
 *
 * Author:  2012,  Giuseppe Serano
 */

/*
 * SPI276:	Spi_Irq.c file could exist depending upon implementation and
 * 		also it could or not include Spi.h.
 */
#include "Spi.h"

/* 
 * SPI069:	Spi.c shall check if the correct version of Spi.h is included.
 * 		This shall be done by a pre-processor check.
 *
 * SPI369:	The SPI module shall avoid the integration of incompatible files
 * 		by the following pre-processor checks:
 * 		for included (external) header files,
 * 		- <MODULENAME>_AR_RELEASE_MAJOR_VERSION
 * 		- <MODULENAME>_AR_RELEASE_MINOR_VERSION
 * 		shall be verified.
 *
 * If the values are not identical to the expected values, an error shall be
 * reported.
 */
#define	SPI_AR_RELEASE_MAJOR_VERSION	4
#define	SPI_AR_RELEASE_MINOR_VERSION	0

#if !defined( SPI_AR_MAJOR_VERSION ) || \
    ( SPI_AR_MAJOR_VERSION != SPI_AR_RELEASE_MAJOR_VERSION )
#error	Spi_Irq: version mismatch.
#endif

#include "ee.h"
#include "ee_irq.h"

#if	( \
	defined(SPI_0_RX_DMA_XFER_ERR_NOTIF_SYM) || \
	defined(SPI_0_TX_DMA_XFER_ERR_NOTIF_SYM) || \
	defined(SPI_1_RX_DMA_XFER_ERR_NOTIF_SYM) || \
	defined(SPI_1_TX_DMA_XFER_ERR_NOTIF_SYM) || \
	defined(SPI_2_RX_DMA_XFER_ERR_NOTIF_SYM) || \
	defined(SPI_2_TX_DMA_XFER_ERR_NOTIF_SYM) || \
	defined(SPI_3_RX_DMA_XFER_ERR_NOTIF_SYM) || \
	defined(SPI_3_TX_DMA_XFER_ERR_NOTIF_SYM) || \
	defined(EE_CORTEX_MX_SSI_0_ISR) || defined(EE_CORTEX_MX_SSI_1_ISR) || \
	defined(EE_CORTEX_MX_SSI_2_ISR) || defined(EE_CORTEX_MX_SSI_3_ISR) \
)

#include "Spi_Internal.h"

/*
 * Job End.
 *
 * param	HWUnit		SPI Hardware Unit on which Error Occurred.
 * param	JobResult	SPI Job Result.
 */
void Spi_JobEnd(
  Spi_HWUnitType	HWUnit,
  Spi_JobResultType	JobResult
)
{

  register EE_UREG				flags;
#if	0
  register uint32				mode;
#endif
  register Spi_HWUnitType			HWUnitIdx;
  register Spi_JobType				JobIdx;
  register Spi_ChannelType			AssChNum, ChIdx;
  register const Spi_ExternalDeviceConfigType *	ExtDevCfgPtr;

  flags = EE_hal_suspendIRQ();

  SSI_DISABLE(HWUnit);

  SSI_INT_DIS(HWUnit, SSI_INT_RX_ERR);

  SSI_INT_CLR(HWUnit, SSI_INT_ALL);

  /* External Device Look-up. */
  for (
    HWUnitIdx = 0;
    ( Spi_Global.ConfigPtr->SpiExternalDevice[HWUnitIdx].SpiHwUnit != HWUnit );
    HWUnitIdx++
  ) {
    ;
  }

  ExtDevCfgPtr =	&Spi_Global.ConfigPtr->SpiExternalDevice[HWUnitIdx];

  Dma_DisableChannel(ExtDevCfgPtr->SpiDmaRxChannel);

  Dma_DisableChannel(ExtDevCfgPtr->SpiDmaTxChannel);

#if	0
  /*
   * Flush FIFOs - START.
   */

  /* Save Hardware Unit Mode. */
  mode = SSI_GET_CR1(HWUnit);

  /* Hardware Unit Master+Loopback Mode. */
  SSI_SET_CR1(HWUnit, ( SPI_HW_UNIT_MASTER | SPI_HW_UNIT_LOOPBACK ));

  /* Enables Harware Unit. */
  SSI_ENABLE(HWUnit);

  /* Tx FIFO Flush. */
  while ( !( SSI_GET_SR(HWUnit) & SSI_STAT_TFE ) ) {
    ;
  }

  /* Disables Harware Unit. */
  SSI_DISABLE(HWUnit);

  /* Rx FIFO Flush. */
  while ( SSI_GET_SR(HWUnit) & SSI_STAT_RNE ) {

    SSI_FIFO_RX(HWUnit);

  }

  /* Restore Hardware Unit Mode. */
  SSI_SET_CR1(HWUnit, mode);

  /*
   * Flush FIFOs - END.
   */
#endif	/* 0 */

  JobIdx = SpiHwUnitStatus[HWUnitIdx].SpiOwnerIdx;

  SpiHwUnitStatus[HWUnitIdx].SpiTxEnd = FALSE;
  SpiHwUnitStatus[HWUnitIdx].SpiOwnerIdx = SPI_JOB_END_LIST;

  SpiJobStatus[JobIdx].SpiJobResult = JobResult;

  for (
    AssChNum = 0;
    Spi_Global.ConfigPtr->SpiJob[JobIdx].SpiChannelList[AssChNum] !=
    SPI_CHANNEL_END_LIST;
    AssChNum++
  ) {

    for (
      ChIdx = 0;
      ( 
	Spi_Global.ConfigPtr->SpiChannel[ChIdx].SpiChannelId !=
	Spi_Global.ConfigPtr->SpiJob[JobIdx].SpiChannelList[AssChNum]
      );
      ChIdx++
    ) {
      ;
    }

    SpiChannelStatus[ChIdx].SpiBuffLen = 0x0000U;
    SpiChannelStatus[ChIdx].SpiSrcBuffPtr = NULL_PTR;

#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
    if ( Spi_Global.ConfigPtr->SpiChannel[ChIdx].SpiChannelType == SPI_EB ) {
#endif	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */

#if	( \
	  ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) || \
	  ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) \
	)
      SpiChannelStatus[ChIdx].SpiDstBuffPtr = NULL_PTR;
#endif	/*
	 * (
	 *   ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) ||
	 *    ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
	 *  )
	 */

#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
    }
#endif	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */

  }

#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
  if ( 
#if	( SPI_LEVEL_DELIVERED == 2 )
    ( ExtDevCfgPtr->SpiHwUnitSynchronous & SPI_ASYNCHRONOUS ) &&
#endif
    ( Spi_Global.AsyncMode == SPI_INTERRUPT_MODE )
  ){

    EE_hal_resumeIRQ(flags);

    Spi_MainFunction_Internal_Handling(
#if	( SPI_LEVEL_DELIVERED == 2 )
      SPI_ASYNCHRONOUS
#endif
    );

    flags = EE_hal_suspendIRQ();

  }
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */

  EE_hal_resumeIRQ(flags);

}
#endif	/*
	 * SPI_0_RX_DMA_XFER_ERR_NOTIF_SYM || SPI_0_TX_DMA_XFER_ERR_NOTIF_SYM ||
	 * SPI_1_RX_DMA_XFER_ERR_NOTIF_SYM || SPI_1_TX_DMA_XFER_ERR_NOTIF_SYM ||
	 * SPI_2_RX_DMA_XFER_ERR_NOTIF_SYM || SPI_2_TX_DMA_XFER_ERR_NOTIF_SYM ||
	 * SPI_3_RX_DMA_XFER_ERR_NOTIF_SYM || SPI_3_TX_DMA_XFER_ERR_NOTIF_SYM ||
	 * EE_CORTEX_MX_SSI_0_ISR || EE_CORTEX_MX_SSI_1_ISR ||
	 * EE_CORTEX_MX_SSI_2_ISR || EE_CORTEX_MX_SSI_3_ISR
	 */

#if	( \
	defined(SPI_0_RX_DMA_XFER_ERR_NOTIF_SYM) || \
	defined(SPI_0_TX_DMA_XFER_ERR_NOTIF_SYM) || \
	defined(SPI_1_RX_DMA_XFER_ERR_NOTIF_SYM) || \
	defined(SPI_1_TX_DMA_XFER_ERR_NOTIF_SYM) || \
	defined(SPI_2_RX_DMA_XFER_ERR_NOTIF_SYM) || \
	defined(SPI_2_TX_DMA_XFER_ERR_NOTIF_SYM) || \
	defined(SPI_3_RX_DMA_XFER_ERR_NOTIF_SYM) || \
	defined(SPI_3_TX_DMA_XFER_ERR_NOTIF_SYM) \
)

#ifdef	SPI_0_RX_DMA_XFER_ERR_NOTIF_SYM
void SPI_0_RX_DMA_XFER_ERR_NOTIF_SYM(void)
{ Spi_JobEnd(SPI_HW_UNIT_0, SPI_JOB_FAILED); }
#endif

#ifdef	SPI_0_TX_DMA_XFER_ERR_NOTIF_SYM
void SPI_0_TX_DMA_XFER_ERR_NOTIF_SYM(void)
{ Spi_JobEnd(SPI_HW_UNIT_0, SPI_JOB_FAILED); }
#endif

#ifdef	SPI_1_RX_DMA_XFER_ERR_NOTIF_SYM
void SPI_1_RX_DMA_XFER_ERR_NOTIF_SYM(void)
{ Spi_JobEnd(SPI_HW_UNIT_1, SPI_JOB_FAILED); }
#endif

#ifdef	SPI_1_TX_DMA_XFER_ERR_NOTIF_SYM
void SPI_1_TX_DMA_XFER_ERR_NOTIF_SYM(void)
{ Spi_JobEnd(SPI_HW_UNIT_1, SPI_JOB_FAILED); }
#endif

#ifdef	SPI_2_RX_DMA_XFER_ERR_NOTIF_SYM
void SPI_2_RX_DMA_XFER_ERR_NOTIF_SYM(void)
{ Spi_JobEnd(SPI_HW_UNIT_2, SPI_JOB_FAILED); }
#endif

#ifdef	SPI_2_TX_DMA_XFER_ERR_NOTIF_SYM
void SPI_2_TX_DMA_XFER_ERR_NOTIF_SYM(void)
{ Spi_JobEnd(SPI_HW_UNIT_2, SPI_JOB_FAILED); }
#endif

#ifdef	SPI_3_RX_DMA_XFER_ERR_NOTIF_SYM
void SPI_3_RX_DMA_XFER_ERR_NOTIF_SYM(void)
{ Spi_JobEnd(SPI_HW_UNIT_3, SPI_JOB_FAILED); }
#endif

#ifdef	SPI_3_TX_DMA_XFER_ERR_NOTIF_SYM
void SPI_3_TX_DMA_XFER_ERR_NOTIF_SYM(void)
{ Spi_JobEnd(SPI_HW_UNIT_3, SPI_JOB_FAILED); }
#endif

#endif	/*
	 * SPI_0_RX_DMA_XFER_ERR_NOTIF_SYM || SPI_0_TX_DMA_XFER_ERR_NOTIF_SYM ||
	 * SPI_1_RX_DMA_XFER_ERR_NOTIF_SYM || SPI_1_TX_DMA_XFER_ERR_NOTIF_SYM ||
	 * SPI_2_RX_DMA_XFER_ERR_NOTIF_SYM || SPI_2_TX_DMA_XFER_ERR_NOTIF_SYM ||
	 * SPI_3_RX_DMA_XFER_ERR_NOTIF_SYM || SPI_3_TX_DMA_XFER_ERR_NOTIF_SYM
	 */

#if	( \
  defined(EE_CORTEX_MX_SSI_0_ISR) || defined(EE_CORTEX_MX_SSI_1_ISR) || \
  defined(EE_CORTEX_MX_SSI_2_ISR) || defined(EE_CORTEX_MX_SSI_3_ISR) \
)
/*
 * SPI Interrupt Service Routine.
 *
 * param	HWUint	SPI Hardware Unit who fired Interrupt.
 */
void Spi_Isr(
  Spi_HWUnitType HWUnit
)
{

  EE_FREG			flags;
  register Spi_HWUnitType	HWUnitIdx;
  register boolean		rx_err, tx_end;

  flags = EE_hal_suspendIRQ();

  rx_err = (
	( SSI_GET_RIS(HWUnit) & SSI_INT_ROR ) ||
	( SSI_GET_MIS(HWUnit) & SSI_INT_ROR )
  );

  SSI_INT_CLR(HWUnit, SSI_INT_RX_ERR);

  /* External Device Look-up. */
  for (
    HWUnitIdx = 0;
    ( Spi_Global.ConfigPtr->SpiExternalDevice[HWUnitIdx].SpiHwUnit != HWUnit );
    HWUnitIdx++
  ) {
    ;
  }

  tx_end = SpiHwUnitStatus[HWUnitIdx].SpiTxEnd;

  SpiHwUnitStatus[HWUnitIdx].SpiTxEnd = TRUE;

  EE_hal_resumeIRQ(flags);

  if ( rx_err ) {

    Spi_JobEnd(HWUnit, SPI_JOB_FAILED);

  }
  else if ( tx_end ) {

    Spi_JobEnd(HWUnit, SPI_JOB_OK);

  }

}

#endif	/*
	 * EE_CORTEX_MX_SSI_0_ISR || EE_CORTEX_MX_SSI_1_ISR ||
	 * EE_CORTEX_MX_SSI_2_ISR || EE_CORTEX_MX_SSI_3_ISR
	 */

#ifdef	EE_CORTEX_MX_SSI_0_ISR
ISR2(EE_CORTEX_MX_SSI_0_ISR) { Spi_Isr(SPI_HW_UNIT_0); }
#endif

#ifdef	EE_CORTEX_MX_SSI_1_ISR
ISR2(EE_CORTEX_MX_SSI_1_ISR) { Spi_Isr(SPI_HW_UNIT_1); }
#endif

#ifdef	EE_CORTEX_MX_SSI_2_ISR
ISR2(EE_CORTEX_MX_SSI_2_ISR) { Spi_Isr(SPI_HW_UNIT_2); }
#endif

#ifdef	EE_CORTEX_MX_SSI_3_ISR
ISR2(EE_CORTEX_MX_SSI_3_ISR) { Spi_Isr(SPI_HW_UNIT_3); }
#endif
