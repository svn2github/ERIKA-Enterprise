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
 * AUTOSAR-"like" SCI Driver Source File.
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
#error	Sci: version mismatch.
#endif

#include "ee.h"

/* Development error macros. */
#if ( SCI_DEV_ERROR_DETECT == STD_ON )

#include "Det.h"
#if defined(__AS_DEM__)
#include "Dem.h"
#endif

#define VALIDATE(_exp,_api,_err ) \
  if( !(_exp) ) { \
    Det_ReportError(SCI_MODULE_ID,0,_api,_err); \
    return; \
  }

#define VALIDATE_W_RV(_exp,_api,_err,_rv ) \
  if( !(_exp) ) { \
    Det_ReportError(SCI_MODULE_ID,0,_api,_err); \
    return (_rv); \
  }

#else	/* SCI_DEV_ERROR_DETECT */

#define VALIDATE(_exp,_api,_err ) \
  if( !(_exp) ) { \
    return; \
  }
#define VALIDATE_W_RV(_exp,_api,_err,_rv ) \
  if( !(_exp) ) { \
    return (_rv); \
  }
#endif	/* !SCI_DEV_ERROR_DETECT */

/*
 * Type that holds all global data for Sci Driver
 */
typedef struct
{
  boolean			Init;		/* SCI Driver Initialized? */

  const Sci_ConfigType *	ConfigPtr;	/* Actual Configuration */

} Sci_GlobalType;


/*
 * Global config
 */
Sci_GlobalType Sci_Global =
{
  FALSE,		/* Init		*/
  NULL_PTR,		/* ConfigPtr	*/
};

/*
 * MCU Global Configuration Reference
 */
typedef struct
{
  boolean			Init;		/* MCU Driver Initialized? */

  const Mcu_ConfigType *	ConfigPtr;	/* Actual Configuration */

  Mcu_ClockType			ClockSetting;	/* Actual Clock Setting */

} Mcu_GlobalType;
extern Mcu_GlobalType Mcu_Global;

/* UART Hardware Channel Unit Mask */
#define	HW_CH_MOD_MASK		0x00000007	/* Mask			*/

/* UART Hardware Base Address */
#define	HW_BASE_ADDR		&UART0_DR_R

#include "Hardware.h"	/* Hardware Abstraction Header File. */

/*
 * Usefull Sci Channel Macros
 */
#define	SCI_PIOSC_FREQ	1.6E7

#define	SCI_CLK_DIV_HIGH_SPEED	8
#define	SCI_CLK_DIV_LOW_SPEED	16

/* HW_CH_MOD_MASK */
#define	SCI_CH_MASK		0x00000007		/* Channel Mask	      */

#define	CH2MASK(_ch) (uint32)(_ch & SCI_CH_MASK)	/* HW_CH_2_MOD */

/* HW_MOD_ADDR_S */
#define	SCI_CH_MASK_BITS	0x0000000C

#define	CH2ADDR(_ch) (uint32)( \
  ((uint32) &UART0_DR_R) + (HW_CH_2_MOD(_ch) << SCI_CH_MASK_BITS) \
)
/*
#define	CH2ADDR(_ch) (uint32)( \
  ((uint32) &UART0_DR_R) + (CH2MASK(_ch) << SCI_CH_MASK_BITS) \
)
*/

/* Clock Control */
#define	SCI_CH_SYSCLK	0x000000000	/* System Clock			 */
#define	SCI_CH_PIOSC	0x000000001	/* Precision Internal Oscillator */

/* Channel Harware Register Offsets */
#define	UART_DATA_R_OFFSET		0x00000000	/* Data               */
#define	UART_RS_EC_R_OFFSET		0x00000004	/* Rx Status/Err Clr  */
#define	UART_FLAG_R_OFFSET		0x00000018	/* Flags	      */
#define	UART_IBRD_R_OFFSET		0x00000024	/* Integer BRD	      */
#define	UART_FBRD_R_OFFSET		0x00000028	/* Fractional BRD     */
#define	UART_LCRH_R_OFFSET		0x0000002C	/* Line Control	      */
#define	UART_CTL_R_OFFSET		0x00000030	/* System Control     */
#define	UART_IFLS_R_OFFSET		0x00000034	/* Int FIFO Lvl	      */
#define	UART_IM_R_OFFSET		0x00000038	/* Interrupt Mask     */
#define	UART_RIS_R_OFFSET		0x0000003C	/* Raw Int Status     */
#define	UART_MIS_R_OFFSET		0x00000040	/* Masked Int Status  */
#define	UART_IC_R_OFFSET		0x00000044	/* Interrupt Clear    */
#define	UART_CC_R_OFFSET		0x00000FC8	/* Clock Control      */

/* Channel Interrupt Sources */
#define	UART_INT_LME5	0x00008000	/* LIN Mode Edge 5	      */
#define	UART_INT_LME1	0x00004000	/* LIN Mode Edge 1	      */
#define	UART_INT_LMSB	0x00002000	/* LIN Mode Sync Break	      */
#define	UART_INT_9BIT	0x00001000	/* 9-Bit Mode		      */
#define	UART_INT_OE	0x00000400	/* Overrun Error	      */
#define	UART_INT_BE	0x00000200	/* Break Error		      */
#define	UART_INT_PE	0x00000100	/* Parity Error		      */
#define	UART_INT_FE	0x00000080	/* Frame Error		      */
#define	UART_INT_RT	0x00000040	/* Receive Timeout	      */
#define	UART_INT_TX	0x00000020	/* Transmission		      */
#define	UART_INT_RX	0x00000010	/* Reception		      */
#define	UART_INT_DSR	0x00000008	/* Data Set Ready	      */
#define	UART_INT_DCD	0x00000004	/* Data Carrier Detect	      */
#define	UART_INT_CTS	0x00000002	/* Clear To Send	      */
#define	UART_INT_RI	0x00000001	/* Ring Indicator	      */

/* Interrupt Receive Error	      */
#define	UART_INT_RX_ERR	( \
	UART_INT_OE  |	UART_INT_BE  |	UART_INT_PE  |	UART_INT_FE \
)

/* All Interrupt	      */
#define	UART_INT_ALL	( \
	UART_INT_LME5 |	UART_INT_LME1 |	UART_INT_LMSB |	UART_INT_9BIT | \
	UART_INT_OE   |	UART_INT_BE   |	UART_INT_PE   |	UART_INT_FE   | \
	UART_INT_RT   |	UART_INT_TX   |	UART_INT_RX   |	UART_INT_DSR  | \
	UART_INT_DCD  |	UART_INT_CTS  |	UART_INT_RI \
)

/* Channel Hardware Registers Read/Write */
#define	UART_REG(_ch,_ofs)	HW_CH_2_MOD_REG(_ch,_ofs)

#define	UART_REG_SET(_ch,_ofs,_val)	(UART_REG(_ch,_ofs) = _val)

#define	UART_REG_AND(_ch,_ofs,_val)	(UART_REG(_ch,_ofs) & _val)

#define	UART_REG_OR(_ch,_ofs,_val)	(UART_REG(_ch,_ofs) | _val)

#define	UART_REG_AND_SET(_ch,_ofs,_val)	(UART_REG(_ch,_ofs) &= _val)

#define	UART_REG_OR_SET(_ch,_ofs,_val)	(UART_REG(_ch,_ofs) |= _val)

/* Utils */
#define	UART_RX_DATA(_ch)	UART_REG(_ch, UART_DATA_R_OFFSET)

#define	UART_TX_DATA(_ch,_data)	UART_REG_SET(_ch, UART_DATA_R_OFFSET, _data)

#define	UART_RX_ERR(_ch)	UART_REG(_ch, UART_RS_EC_R_OFFSET)

#define	UART_RX_ERR_CLR(_ch)	\
	UART_REG_SET(_ch, UART_RS_EC_R_OFFSET, 0x00000000)

#define	UART_RX_FIFO_EMPTY(_ch)	\
	UART_REG_AND(_ch, UART_FLAG_R_OFFSET, UART_FR_RXFE)

#define	UART_RX_FIFO_FULL(_ch)	\
	UART_REG_AND(_ch, UART_FLAG_R_OFFSET, UART_FR_RXFF)

#define	UART_TX_FIFO_EMPTY(_ch)	\
	UART_REG_AND(_ch, UART_FLAG_R_OFFSET, UART_FR_TXFE)

#define	UART_TX_FIFO_FULL(_ch)	\
	UART_REG_AND(_ch, UART_FLAG_R_OFFSET, UART_FR_TXFF)

#define	UART_BUSY(_ch)		\
	UART_REG_AND(_ch, UART_FLAG_R_OFFSET, UART_FR_BUSY)

#define	UART_FIFO_FLUSH(_ch)	\
	UART_REG_AND_SET(_ch, UART_LCRH_R_OFFSET, ~SCI_CH_HW_FIFO)

#define	UART_ENABLE(_ch)	\
	UART_REG_OR_SET(_ch, UART_CTL_R_OFFSET, SCI_CH_HW_ENABLE)

#define	UART_ENABLE_RX(_ch)	\
	UART_REG_OR_SET(_ch, UART_CTL_R_OFFSET, SCI_CH_HW_RX)

#define	UART_ENABLE_TX(_ch)	\
	UART_REG_OR_SET(_ch, UART_CTL_R_OFFSET, SCI_CH_HW_TX)

#define	UART_DISABLE(_ch)	\
	UART_REG_AND_SET(_ch, UART_CTL_R_OFFSET, ~SCI_CH_HW_ENABLE)

#define	UART_DISABLE_RX(_ch)	\
	UART_REG_AND_SET(_ch, UART_CTL_R_OFFSET, ~SCI_CH_HW_RX)

#define	UART_DISABLE_TX(_ch)	\
	UART_REG_AND_SET(_ch, UART_CTL_R_OFFSET, ~SCI_CH_HW_TX)

#define	UART_CLK_SYS(_ch)	\
	UART_REG_SET(_ch, UART_CC_R_OFFSET, SCI_CH_SYSCLK)

#define	UART_CLK_PIOSC(_ch)	\
	UART_REG_SET(_ch, UART_CC_R_OFFSET, SCI_CH_PIOSC)

#define	UART_BRD(_br,_clk,_div)	(_clk / ((float32) (_div * _br)))

#define	UART_SET_IBRD(_ch,_ibrd)	\
	UART_REG_SET(_ch, UART_IBRD_R_OFFSET, _ibrd)

#define	UART_SET_FBRD(_ch,_fbrd)	\
	UART_REG_SET(_ch, UART_FBRD_R_OFFSET, _fbrd)

#define	UART_SET_LINE_CTRL(_ch,_ctrl)	\
	UART_REG_SET(_ch, UART_LCRH_R_OFFSET, _ctrl)

#define	UART_SET_SYS_CTRL(_ch,_ctrl)	\
	UART_REG_SET(_ch, UART_CTL_R_OFFSET, _ctrl)

#define	UART_RIS(_ch)		UART_REG(_ch, UART_RIS_R_OFFSET)

#define	UART_MIS(_ch)	 	UART_REG(_ch, UART_MIS_R_OFFSET)

#define	UART_INT_CLEAR(_ch,_srcs)	\
	UART_REG_OR_SET(_ch, UART_IC_R_OFFSET, _srcs)

#define	UART_INT_ENABLE(_ch,_srcs)	\
	UART_REG_OR_SET(_ch, UART_IM_R_OFFSET, _srcs)

#define	UART_INT_DISABLE(_ch,_srcs)	\
	UART_REG_AND_SET(_ch, UART_IM_R_OFFSET, ~((uint32)_srcs))

/*
 * Sci Channel Initialization.
 */
static void Sci_InitSciChannel(
  const Sci_ChannelConfigType *	ConfigPtr
)
{

  register float32	brd;	/* Baud-Rate Divisor	*/
  register float32	clk;	/* Clock Frequency	*/

  /* Enables Sci Module in Run-Mode */
  SYSCTL_RCGCUART_R |= HW_CH_2_CGC_MASK(ConfigPtr->SciChannelId);

  /* Disables Channel */
  UART_DISABLE(ConfigPtr->SciChannelId);

  /* Flushes Fifo */
  UART_FIFO_FLUSH(ConfigPtr->SciChannelId);

  /* Waits end of transmission/reception */
  while(
    UART_BUSY(ConfigPtr->SciChannelId) ||
    !UART_TX_FIFO_EMPTY(ConfigPtr->SciChannelId) ||
    !UART_RX_FIFO_EMPTY(ConfigPtr->SciChannelId)
  );

  /* Clear Errors */
  UART_RX_ERR_CLR(ConfigPtr->SciChannelId);

  /* UART Baud Clock Source */
  if ( ConfigPtr->SciSysClock == TRUE ) {
    UART_CLK_SYS(ConfigPtr->SciChannelId);
    clk =
    Mcu_Global.ConfigPtr->McuClockSettingConfig[
    	Mcu_Global.ClockSetting
    ].McuClockReferencePointFrequency;
  }
  else {
    UART_CLK_PIOSC(ConfigPtr->SciChannelId);
    clk = SCI_PIOSC_FREQ;
  }

  /* Baud-Rate Divisor computation waiting the peripheral to enable. */
  if ( ConfigPtr->SciSysCtrl & SCI_CH_HW_HIGH_SPEED )
    /* Clock Divider: 8 */
    brd = UART_BRD(ConfigPtr->SciChannelBaudRate, clk, SCI_CLK_DIV_HIGH_SPEED);
  else
    /* Clock Divider: 16 */
    brd = UART_BRD(ConfigPtr->SciChannelBaudRate, clk, SCI_CLK_DIV_LOW_SPEED);

  /* Integer Baud-Rate Divisor Sets-Up */
  UART_SET_IBRD(ConfigPtr->SciChannelId, (uint32) brd);

  /* Fractional Baud-Rate Divisor Sets-Up */
  UART_SET_FBRD(
    ConfigPtr->SciChannelId, (uint32) ((brd - ((uint32) brd))*64 + 0.5)
  );

  /* Line Control Sets-Up */
  UART_SET_LINE_CTRL(ConfigPtr->SciChannelId, ConfigPtr->SciLineCtrl);

  /* System Control Sets-Up */
  UART_SET_SYS_CTRL(
    ConfigPtr->SciChannelId, (ConfigPtr->SciSysCtrl & ~SCI_CH_HW_ENABLE)
  );

  /* Clear Interrupt */
  UART_INT_CLEAR(ConfigPtr->SciChannelId, UART_INT_ALL);

  /* Enables Channel */
  UART_ENABLE(ConfigPtr->SciChannelId);

}

/*
 * Sci Channel De-Initialization.
 */
#if ( SCI_DEINIT_API == STD_ON )
static void Sci_DeInitSciChannel(
  const Sci_ChannelConfigType *	ConfigPtr
)
{

  register uint32	mask = HW_CH_2_CGC_MASK(ConfigPtr->SciChannelId);

  /* Enables Sci Module in Run-Mode */
  if ( !( SYSCTL_RCGCUART_R & mask ) )	SYSCTL_RCGCUART_R |= mask;

  SYSCTL_SRUART_R |= mask;			/* Start Channel Module Reset */
  SYSCTL_SRUART_R &= ~mask;			/* Stop  Channel Module Reset */
  while ( !( SYSCTL_PRUART_R & mask ) );	/* Wait Reset		      */

  /* Disables Sci Module in Run-Mode */
  SYSCTL_RCGCUART_R &= ~(mask);

}
#endif

/*
 * Sci_Init implementation.
 */
void Sci_Init(
  const Sci_ConfigType *	ConfigPtr
)
{

  register uint32 channel;

  VALIDATE( ( ConfigPtr != NULL ), SCI_INIT_SERVICE_ID, SCI_E_PARAM_CONFIG );

  VALIDATE( ( Hw_CheckCore() == E_OK ), SCI_INIT_SERVICE_ID, SCI_E_UNINIT );

  Sci_Global.ConfigPtr = ConfigPtr;
  Sci_Global.Init = TRUE;

  for (channel = 0; channel < ConfigPtr->SciNumberOfSciChannels; channel++)
  {

    /* Initializes Sci Channel. */
    Sci_InitSciChannel(&(ConfigPtr->SciChannels[channel]));

  }

}

/*
 * Sci_WriteTxData implementation.
 */
Std_ReturnType Sci_WriteTxData(
  Sci_ChannelType	Channel,
  uint8			Data
)
{

  VALIDATE_W_RV(
    ( Sci_Global.Init == TRUE ),
    SCI_WRITETXDATA_SERVICE_ID,
    SCI_E_UNINIT,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    ( Channel < SCI_CHANNELS_NUMBER ),
    SCI_WRITETXDATA_SERVICE_ID,
    SCI_E_INVALID_CHANNEL,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    ( SYSCTL_RCGCUART_R & HW_CH_2_CGC_MASK(Channel) ),
    SCI_WRITETXDATA_SERVICE_ID,
    SCI_E_STATE_TRANSITION,
    E_NOT_OK
  );

  if (UART_TX_FIFO_FULL(Channel)) return E_NOT_OK;

  UART_TX_DATA(Channel, (uint32) Data);

  return E_OK;

}

/*
 * Sci_ReadRxData implementation.
 */
Std_ReturnType Sci_ReadRxData(
  Sci_ChannelType	Channel,
  uint8 *		DataPtr
)
{

  register uint32	rx;

  VALIDATE_W_RV(
    ( Sci_Global.Init == TRUE ),
    SCI_READRXDATA_SERVICE_ID,
    SCI_E_UNINIT,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    ( Channel < SCI_CHANNELS_NUMBER ),
    SCI_READRXDATA_SERVICE_ID,
    SCI_E_INVALID_CHANNEL,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    ( SYSCTL_RCGCUART_R & HW_CH_2_CGC_MASK(Channel) ),
    SCI_READRXDATA_SERVICE_ID,
    SCI_E_STATE_TRANSITION,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    ( DataPtr != NULL_PTR ),
    SCI_READRXDATA_SERVICE_ID,
    SCI_E_PARAM_POINTER,
    E_NOT_OK
  );

  if (UART_RX_FIFO_EMPTY(Channel)) return E_NOT_OK;

  rx = UART_RX_DATA(Channel);
  (*DataPtr) = (uint8) rx;

  return E_OK;

}

#if ( SCI_NOTIFICATIONS_API == STD_ON )
/*
 * Sci_EnableNotifications implementation.
 */
void Sci_EnableNotifications(
  Sci_ChannelType	Channel
)
{

  VALIDATE(
    ( Sci_Global.Init == TRUE ),
    SCI_ENABLE_NOTIFICATIONS_SERVICE_ID,
    SCI_E_UNINIT
  );

  VALIDATE(
    ( Channel < SCI_CHANNELS_NUMBER ),
    SCI_ENABLE_NOTIFICATIONS_SERVICE_ID,
    SCI_E_INVALID_CHANNEL
  );

  if ( SYSCTL_RCGCUART_R & HW_CH_2_CGC_MASK(Channel) ) {

    UART_INT_ENABLE(
      Channel,
      UART_INT_TX | UART_INT_RX | UART_INT_RT | UART_INT_RX_ERR
    );
  
  };

}

/*
 * Sci_DisableNotifications implementation.
 */
void Sci_DisableNotifications(
  Sci_ChannelType	Channel
)
{

  VALIDATE(
    ( Sci_Global.Init == TRUE ),
    SCI_ENABLE_NOTIFICATIONS_SERVICE_ID,
    SCI_E_UNINIT
  );

  VALIDATE(
    ( Channel < SCI_CHANNELS_NUMBER ),
    SCI_ENABLE_NOTIFICATIONS_SERVICE_ID,
    SCI_E_INVALID_CHANNEL
  );

  if ( SYSCTL_RCGCUART_R & HW_CH_2_CGC_MASK(Channel) ) {

    UART_INT_DISABLE(
      Channel,
      UART_INT_TX | UART_INT_RX | UART_INT_RT | UART_INT_RX_ERR
    );

  }

}
#endif

#if ( SCI_WAKEUP_FUNCTIONALITY_API == STD_ON )
/*
 * Sci_GoToSleep implementation.
 */
Std_ReturnType Sci_GoToSleep(
  Sci_ChannelType	Channel
)
{

  register uint32	mask = HW_CH_2_CGC_MASK(Channel);

  VALIDATE_W_RV(
    ( Sci_Global.Init == TRUE ),
    SCI_GOTOSLEEP_SERVICE_ID,
    SCI_E_UNINIT,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    ( Channel < SCI_CHANNELS_NUMBER ),
    SCI_GOTOSLEEP_SERVICE_ID,
    SCI_E_INVALID_CHANNEL,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    ( SYSCTL_RCGCUART_R & mask ),
    SCI_GOTOSLEEP_SERVICE_ID,
    SCI_E_STATE_TRANSITION,
    E_NOT_OK
  );

  /* Disables Sci Module in Run-Mode */
  SYSCTL_RCGCUART_R &= ~mask;

  return E_OK;

}
#endif

#if ( SCI_WAKEUP_FUNCTIONALITY_API == STD_ON )
/*
 * Sci_Wakeup implementation.
 */
Std_ReturnType Sci_Wakeup(
  Sci_ChannelType	Channel
)
{

  register uint32	mask = HW_CH_2_CGC_MASK(Channel);

  VALIDATE_W_RV(
    ( Sci_Global.Init == TRUE ),
    SCI_WAKEUP_SERVICE_ID,
    SCI_E_UNINIT,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    ( Channel < SCI_CHANNELS_NUMBER ),
    SCI_WAKEUP_SERVICE_ID,
    SCI_E_INVALID_CHANNEL,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    ( !( SYSCTL_RCGCUART_R & mask ) ),
    SCI_WAKEUP_SERVICE_ID,
    SCI_E_STATE_TRANSITION,
    E_NOT_OK
  );

  /* Enables Sci Module in Run-Mode */
  SYSCTL_RCGCUART_R |= mask;

  return E_OK;

}
#endif

/*
 * Sci_GetStatus implementation.
 */
Sci_StatusType Sci_GetStatus(
  Sci_ChannelType	Channel
)
{

  register Sci_StatusType	ret;

  VALIDATE_W_RV(
    ( Sci_Global.Init == TRUE ),
    SCI_GETSTATUS_SERVICE_ID,
    SCI_E_UNINIT,
    SCI_NOT_OK
  );

  VALIDATE_W_RV(
    ( Channel < SCI_CHANNELS_NUMBER ),
    SCI_GETSTATUS_SERVICE_ID,
    SCI_E_INVALID_CHANNEL,
    SCI_NOT_OK
  );

  VALIDATE_W_RV(
    ( SYSCTL_RCGCUART_R & HW_CH_2_CGC_MASK(Channel) ),
    SCI_GETSTATUS_SERVICE_ID,
    SCI_E_STATE_TRANSITION,
    SCI_CH_SLEEP
  );

  VALIDATE_W_RV(
    ( !(UART_RIS(Channel) & UART_INT_RT) ),
    SCI_GETSTATUS_SERVICE_ID,
    SCI_E_TIMEOUT,
    SCI_NOT_OK
  );

  if (!UART_RX_FIFO_EMPTY(Channel)) {
    if (UART_RX_ERR(Channel))	ret = SCI_RX_ERROR;
    else			ret = SCI_RX_OK;
  }
  else if (UART_BUSY(Channel))	ret = SCI_TX_BUSY;
  else if (
    ( UART_RIS(Channel) & UART_INT_TX ) || ( UART_MIS(Channel) & UART_INT_TX )
  )				ret = SCI_TX_OK;
  else				ret = SCI_OPERATIONAL;

  return ret;

}

#if ( SCI_DEINIT_API == STD_ON )
/*
 * Sci_DeInit implementation.
 */
void Sci_DeInit(
  void
)
{

  register uint32 channel;

  VALIDATE(
    ( Sci_Global.Init == TRUE ),
    SCI_DEINIT_SERVICE_ID,
    SCI_E_UNINIT
  );

  for (
    channel = 0;
    channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels;
    channel++
  )
  {

    /* De-Initializes Sci Channel. */
    Sci_DeInitSciChannel(&(Sci_Global.ConfigPtr->SciChannels[channel]));

  }

}
#endif

#if ( SCI_WAKEUP_FUNCTIONALITY_API == STD_ON )
/*
 * Sci_CheckWakeup implementation.
 */
Std_ReturnType Sci_CheckWakeup(
  Sci_ChannelType	Channel
)
{

  VALIDATE_W_RV(
    ( Sci_Global.Init == TRUE ),
    SCI_CHECKWAKEUP_SERVICE_ID,
    SCI_E_UNINIT,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    ( Channel < SCI_CHANNELS_NUMBER ),
    SCI_CHECKWAKEUP_SERVICE_ID,
    SCI_E_INVALID_CHANNEL,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    ( SYSCTL_RCGCUART_R & HW_CH_2_CGC_MASK(Channel) ),
    SCI_CHECKWAKEUP_SERVICE_ID,
    SCI_E_STATE_TRANSITION,
    E_NOT_OK
  );

  return E_OK;

}
#endif

/*
 * Sci_DisableTx implementation.
 */
Std_ReturnType Sci_DisableTx(
  Sci_ChannelType	Channel
)
{

  VALIDATE_W_RV(
    ( Sci_Global.Init == TRUE ),
    SCI_DISABLETX_SERVICE_ID,
    SCI_E_UNINIT,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    ( Channel < SCI_CHANNELS_NUMBER ),
    SCI_DISABLETX_SERVICE_ID,
    SCI_E_INVALID_CHANNEL,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    ( SYSCTL_RCGCUART_R & HW_CH_2_CGC_MASK(Channel) ),
    SCI_DISABLETX_SERVICE_ID,
    SCI_E_STATE_TRANSITION,
    E_NOT_OK
  );

  /* Disables Channel */
  UART_DISABLE(Channel);

  /* Flushes Fifo */
  UART_FIFO_FLUSH(Channel);

  /* Waits end of transmission/reception */
  while(UART_BUSY(Channel) || !UART_TX_FIFO_EMPTY(Channel));

  /* Disable TX */
  UART_DISABLE_TX(Channel);

  /* Enables Channel */
  UART_ENABLE(Channel);

  return E_OK;

}

/*
 * Sci_EnableTx implementation.
 */
Std_ReturnType Sci_EnableTx(
  Sci_ChannelType	Channel
)
{

  VALIDATE_W_RV(
    ( Sci_Global.Init == TRUE ),
    SCI_ENABLETX_SERVICE_ID,
    SCI_E_UNINIT,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    ( Channel < SCI_CHANNELS_NUMBER ),
    SCI_ENABLETX_SERVICE_ID,
    SCI_E_INVALID_CHANNEL,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    ( SYSCTL_RCGCUART_R & HW_CH_2_CGC_MASK(Channel) ),
    SCI_ENABLETX_SERVICE_ID,
    SCI_E_STATE_TRANSITION,
    E_NOT_OK
  );

  /* Disables Channel */
  UART_DISABLE(Channel);

  /* Flushes Fifo */
  UART_FIFO_FLUSH(Channel);

  /* Waits end of transmission/reception */
  while(UART_BUSY(Channel));

  /* Enable TX */
  UART_ENABLE_TX(Channel);

  /* Enables Channel */
  UART_ENABLE(Channel);

  return E_OK;

}

/*
 * Sci_DisableRx implementation.
 */
Std_ReturnType Sci_DisableRx(
  Sci_ChannelType	Channel
)
{

  VALIDATE_W_RV(
    ( Sci_Global.Init == TRUE ),
    SCI_DISABLERX_SERVICE_ID,
    SCI_E_UNINIT,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    ( Channel < SCI_CHANNELS_NUMBER ),
    SCI_DISABLERX_SERVICE_ID,
    SCI_E_INVALID_CHANNEL,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    ( SYSCTL_RCGCUART_R & HW_CH_2_CGC_MASK(Channel) ),
    SCI_DISABLERX_SERVICE_ID,
    SCI_E_STATE_TRANSITION,
    E_NOT_OK
  );

  /* Disables Channel */
  UART_DISABLE(Channel);

  /* Flushes Fifo */
  UART_FIFO_FLUSH(Channel);

  /* Waits end of transmission/reception */
  while(UART_BUSY(Channel) || !UART_RX_FIFO_EMPTY(Channel));

  /* Disable RX */
  UART_DISABLE_RX(Channel);

  /* Enables Channel */
  UART_ENABLE(Channel);

  return E_OK;

}

/*
 * Sci_EnableRx implementation.
 */
Std_ReturnType Sci_EnableRx(
  Sci_ChannelType	Channel
)
{

  VALIDATE_W_RV(
    ( Sci_Global.Init == TRUE ),
    SCI_ENABLERX_SERVICE_ID,
    SCI_E_UNINIT,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    ( Channel < SCI_CHANNELS_NUMBER ),
    SCI_ENABLERX_SERVICE_ID,
    SCI_E_INVALID_CHANNEL,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    ( SYSCTL_RCGCUART_R & HW_CH_2_CGC_MASK(Channel) ),
    SCI_ENABLERX_SERVICE_ID,
    SCI_E_STATE_TRANSITION,
    E_NOT_OK
  );

  /* Disables Channel */
  UART_DISABLE(Channel);

  /* Flushes Fifo */
  UART_FIFO_FLUSH(Channel);

  /* Waits end of transmission/reception */
  while(UART_BUSY(Channel));

  /* Enable RX */
  UART_ENABLE_RX(Channel);

  /* Enables Channel */
  UART_ENABLE(Channel);

  return E_OK;

}

