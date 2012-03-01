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

#ifndef	ARRAY_SIZE
#define	ARRAY_SIZE(_x)	(sizeof(_x)/sizeof((_x)[0]))
#endif

/* Development error macros. */
#if ( SCI_DEV_ERROR_DETECT == STD_ON )

#include "Det.h"
#if defined(USE_DEM)
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

/*
 * Supported Cores Identifitication Numbers
 */
#define	CORE_CPUID_CORTEX_M4	0x410FC241

/*
 * Core Informations Container Type
 */
typedef struct {
  char		*Name;	/* Core Name String		*/
  uint32	Id;	/* Core Identifier Number	*/
} Sci_CoreInfoType;

/*
 * Supported Cores Array
 */
Sci_CoreInfoType Sci_SupportedCoreArray[] =
{
  {
    "CORE_ARM_CORTEX_M4",	/* .Name	*/
    CORE_CPUID_CORTEX_M4,	/* .Id		*/
  },
};

/*
 * Supported Core Information Retrieval
 */
static Sci_CoreInfoType * Sci_GetSupportedCoreInfo(
  uint32 Id
)
{
  register uint32 i;
  Sci_CoreInfoType *info = NULL;
  for (i = 0; i < ARRAY_SIZE(Sci_SupportedCoreArray); i++) {
    if (Sci_SupportedCoreArray[i].Id == Id) {
      info = &Sci_SupportedCoreArray[i];
    }
  }
  return info;
}

/*
 * Identify the core, just to check that we have support for it.
 */
static boolean Sci_CheckCore( void ) {
  /* NVIC - System Control Block - Register 64: CPUID */
  register uint32 Id = NVIC_CPUID_R;
  Sci_CoreInfoType *info = NULL;
  info = Sci_GetSupportedCoreInfo(Id);
  return (info != NULL);
}

/*
 * Usefull Sci Channel Macros
 */
#define	SCI_PIOSC_FREQ	1.6E7

#define	SCI_CLK_DIV_HIGH_SPEED	8
#define	SCI_CLK_DIV_LOW_SPEED	16

#define	SCI_CH_MASK		0x00000007		/* Channel Mask	      */
#define	CH2MASK(_ch) (uint32)(_ch & SCI_CH_MASK)

#define	SCI_CH_MASK_BITS	0x0000000C
#define	CH2ADDR(_ch) (uint32)( \
  ((uint32) &UART0_DR_R) + (CH2MASK(_ch) << SCI_CH_MASK_BITS) \
)

/* Clock Control */
#define	SCI_CH_SYSCLK	0x000000000	/* System Clock			 */
#define	SCI_CH_PIOSC	0x000000001	/* Precision Internal Oscillator */

/* Channel Harware Register Offsets */
#define	SCI_UART_DATA_R_OFFSET		0x00000000	/* Data               */
#define	SCI_UART_RS_EC_R_OFFSET		0x00000004	/* Rx Status/Err Clr  */
#define	SCI_UART_FLAG_R_OFFSET		0x00000018	/* Flags	      */
#define	SCI_UART_IBRD_R_OFFSET		0x00000024	/* Integer BRD	      */
#define	SCI_UART_FBRD_R_OFFSET		0x00000028	/* Fractional BRD     */
#define	SCI_UART_LCRH_R_OFFSET		0x0000002C	/* Line Control	      */
#define	SCI_UART_CTL_R_OFFSET		0x00000030	/* System Control     */
#define	SCI_UART_IFLS_R_OFFSET		0x00000034	/* Int FIFO Lvl	      */
#define	SCI_UART_IM_R_OFFSET		0x00000038	/* Interrupt Mask     */
#define	SCI_UART_RIS_R_OFFSET		0x0000003C	/* Raw Int Status     */
#define	SCI_UART_MIS_R_OFFSET		0x00000040	/* Masked Int Status  */
#define	SCI_UART_IC_R_OFFSET		0x00000044	/* Interrupt Clear    */
#define	SCI_UART_CC_R_OFFSET		0x00000FC8	/* Clock Control      */

/* Channel Interrupt Sources */
#define	SCI_UART_INT_LME5	0x00008000	/* LIN Mode Edge 5	      */
#define	SCI_UART_INT_LME1	0x00004000	/* LIN Mode Edge 1	      */
#define	SCI_UART_INT_LMSB	0x00002000	/* LIN Mode Sync Break	      */
#define	SCI_UART_INT_9BIT	0x00001000	/* 9-Bit Mode		      */
#define	SCI_UART_INT_OE		0x00000400	/* Overrun Error	      */
#define	SCI_UART_INT_BE		0x00000200	/* Break Error		      */
#define	SCI_UART_INT_PE		0x00000100	/* Parity Error		      */
#define	SCI_UART_INT_FE		0x00000080	/* Frame Error		      */
#define	SCI_UART_INT_RT		0x00000040	/* Receive Timeout	      */
#define	SCI_UART_INT_TX		0x00000020	/* Transmission		      */
#define	SCI_UART_INT_RX		0x00000010	/* Reception		      */
#define	SCI_UART_INT_DSR	0x00000008	/* Data Set Ready	      */
#define	SCI_UART_INT_DCD	0x00000004	/* Data Carrier Detect	      */
#define	SCI_UART_INT_CTS	0x00000002	/* Clear To Send	      */
#define	SCI_UART_INT_RI		0x00000001	/* Ring Indicator	      */

/* Interrupt Receive Error	      */
#define	SCI_UART_INT_RX_ERR	( \
	SCI_UART_INT_OE  |	SCI_UART_INT_BE  | \
	SCI_UART_INT_PE  |	SCI_UART_INT_FE \
)

/* All Interrupt	      */
#define	SCI_UART_INT_ALL	( \
	SCI_UART_INT_LME5 |	SCI_UART_INT_LME1 |	SCI_UART_INT_LMSB | \
	SCI_UART_INT_9BIT |	SCI_UART_INT_OE   |	SCI_UART_INT_BE   | \
	SCI_UART_INT_PE   |	SCI_UART_INT_FE   |	SCI_UART_INT_RT   | \
	SCI_UART_INT_TX   |	SCI_UART_INT_RX   |	SCI_UART_INT_DSR  | \
	SCI_UART_INT_DCD  |	SCI_UART_INT_CTS  |	SCI_UART_INT_RI \
)

/* Channel Hardware Registers Read/Write */
#define	SCI_UART_REG(_ch,_ofs) (*((volatile uint32 *)(CH2ADDR(_ch) + _ofs)))

#define	SCI_UART_REG_SET(_ch,_ofs,_val)	(SCI_UART_REG(_ch,_ofs) = _val)

#define	SCI_UART_REG_AND(_ch,_ofs,_val)	(SCI_UART_REG(_ch,_ofs) & _val)

#define	SCI_UART_REG_OR(_ch,_ofs,_val)	(SCI_UART_REG(_ch,_ofs) | _val)

#define	SCI_UART_REG_AND_SET(_ch,_ofs,_val)	(SCI_UART_REG(_ch,_ofs) &= _val)

#define	SCI_UART_REG_OR_SET(_ch,_ofs,_val)	(SCI_UART_REG(_ch,_ofs) |= _val)

/* Utils */
#define	RXDATA(_ch)	  SCI_UART_REG(_ch, SCI_UART_DATA_R_OFFSET)

#define	TXDATA(_ch,_data) SCI_UART_REG_SET(_ch, SCI_UART_DATA_R_OFFSET, _data)

#define	RXERR(_ch)  SCI_UART_REG(_ch, SCI_UART_RS_EC_R_OFFSET)

#define	ERRCLR(_ch) SCI_UART_REG_SET(_ch, SCI_UART_RS_EC_R_OFFSET, 0x00000000)

#define	EMPTYRXFIFO(_ch) \
  SCI_UART_REG_AND(_ch, SCI_UART_FLAG_R_OFFSET, UART_FR_RXFE)

#define	FULLRXFIFO(_ch) \
  SCI_UART_REG_AND(_ch, SCI_UART_FLAG_R_OFFSET, UART_FR_RXFF)

#define	EMPTYTXFIFO(_ch) \
  SCI_UART_REG_AND(_ch, SCI_UART_FLAG_R_OFFSET, UART_FR_TXFE)

#define	FULLTXFIFO(_ch) \
  SCI_UART_REG_AND(_ch, SCI_UART_FLAG_R_OFFSET, UART_FR_TXFF)

#define	BUSY(_ch) \
  SCI_UART_REG_AND(_ch, SCI_UART_FLAG_R_OFFSET, UART_FR_BUSY)

#define	FLUSHFIFO(_ch) \
  SCI_UART_REG_AND_SET(_ch,SCI_UART_LCRH_R_OFFSET, ~SCI_CH_HW_FIFO)

#define	CHEN(_ch) \
  SCI_UART_REG_OR_SET(_ch, SCI_UART_CTL_R_OFFSET, SCI_CH_HW_ENABLE)

#define	CHENRX(_ch) \
  SCI_UART_REG_OR_SET(_ch, SCI_UART_CTL_R_OFFSET, SCI_CH_HW_RX)

#define	CHENTX(_ch) \
  SCI_UART_REG_OR_SET(_ch, SCI_UART_CTL_R_OFFSET, SCI_CH_HW_TX)

#define	CHDIS(_ch) \
  SCI_UART_REG_AND_SET(_ch, SCI_UART_CTL_R_OFFSET, ~SCI_CH_HW_ENABLE)

#define	CHDISRX(_ch) \
  SCI_UART_REG_AND_SET(_ch, SCI_UART_CTL_R_OFFSET, ~SCI_CH_HW_RX)

#define	CHDISTX(_ch) \
  SCI_UART_REG_AND_SET(_ch, SCI_UART_CTL_R_OFFSET, ~SCI_CH_HW_TX)

#define	CLKSYS(_ch)   SCI_UART_REG_SET(_ch, SCI_UART_CC_R_OFFSET, SCI_CH_SYSCLK)

#define	CLKPIOSC(_ch) SCI_UART_REG_SET(_ch, SCI_UART_CC_R_OFFSET, SCI_CH_PIOSC)

#define	BRD(_br,_clk,_div) (_clk / ((float32) (_div * _br)))

#define	SETIBRD(_ch,_ibrd) SCI_UART_REG_SET(_ch, SCI_UART_IBRD_R_OFFSET, _ibrd)

#define	SETFBRD(_ch,_fbrd) SCI_UART_REG_SET(_ch, SCI_UART_FBRD_R_OFFSET, _fbrd)

#define	SETLINECTRL(_ch,_ctrl) \
  SCI_UART_REG_SET(_ch, SCI_UART_LCRH_R_OFFSET, _ctrl)

#define	SETSYSCTRL(_ch,_ctrl) \
  SCI_UART_REG_SET(_ch, SCI_UART_CTL_R_OFFSET, _ctrl)

#define	RIS(_ch)	  SCI_UART_REG(_ch, SCI_UART_RIS_R_OFFSET)

#define	MIS(_ch)	  SCI_UART_REG(_ch, SCI_UART_MIS_R_OFFSET)

#define	INTCLR(_ch,_srcs) SCI_UART_REG_OR_SET(_ch, SCI_UART_IC_R_OFFSET, _srcs)

#define	INTEN(_ch,_srcs)  SCI_UART_REG_OR_SET(_ch, SCI_UART_IM_R_OFFSET, _srcs)

/*
 * Sci Channel Initialization.
 */
static void Sci_InitSciChannel(
  Sci_ChannelConfigType *	ConfigPtr
)
{

  register float32	brd;	/* Baud-Rate Divisor	*/
  register float32	clk;	/* Clock Frequency	*/

  /* Enables Sci Module in Run-Mode */
  SYSCTL_RCGCUART_R |= 
  (uint32) (SYSCTL_RCGCUART_R0 << CH2MASK(ConfigPtr->SciChannelId));

  /* Disables Channel */
  CHDIS(ConfigPtr->SciChannelId);

  /* Flushes Fifo */
  FLUSHFIFO(ConfigPtr->SciChannelId);

  /* Waits end of transmission/reception */
  while(
    BUSY(ConfigPtr->SciChannelId) ||
    !EMPTYTXFIFO(ConfigPtr->SciChannelId) ||
    !EMPTYRXFIFO(ConfigPtr->SciChannelId)
  );

  /* Clear Errors */
  ERRCLR(ConfigPtr->SciChannelId);

  /* UART Baud Clock Source */
  if ( ConfigPtr->SciSysClock == TRUE ) {
    CLKSYS(ConfigPtr->SciChannelId);
    clk =
    Mcu_Global.ConfigPtr->McuClockSettingConfig[
    	Mcu_Global.ClockSetting
    ].McuClockReferencePointFrequency;
  }
  else {
    CLKPIOSC(ConfigPtr->SciChannelId);
    clk = SCI_PIOSC_FREQ;
  }

  /* Baud-Rate Divisor computation waiting the peripheral to enable. */
  if ( ConfigPtr->SciSysCtrl & SCI_CH_HW_HIGH_SPEED )
    /* Clock Divider: 8 */
    brd = BRD(ConfigPtr->SciChannelBaudRate, clk, SCI_CLK_DIV_HIGH_SPEED);
  else
    /* Clock Divider: 16 */
    brd = BRD(ConfigPtr->SciChannelBaudRate, clk, SCI_CLK_DIV_LOW_SPEED);

  /* Integer Baud-Rate Divisor Sets-Up */
  SETIBRD(ConfigPtr->SciChannelId, (uint32) brd);

  /* Fractional Baud-Rate Divisor Sets-Up */
  SETFBRD(ConfigPtr->SciChannelId, (uint32) ((brd - ((uint32) brd))*64 + 0.5));

  /* Line Control Sets-Up */
  SETLINECTRL(ConfigPtr->SciChannelId, ConfigPtr->SciLineCtrl);

  /* System Control Sets-Up */
  SETSYSCTRL(
    ConfigPtr->SciChannelId, (ConfigPtr->SciSysCtrl & ~SCI_CH_HW_ENABLE)
  );

  /* Clear Interrupt */
  INTCLR(ConfigPtr->SciChannelId, SCI_UART_INT_ALL);

  /* Enables Channel */
  CHEN(ConfigPtr->SciChannelId);

}

/*
 * Sci Channel De-Initialization.
 */
#if ( SCI_DEINIT_API == STD_ON )
static void Sci_DeInitSciChannel(
  Sci_ChannelConfigType *	ConfigPtr
)
{

  if ( 
    SYSCTL_RCGCUART_R & 
    ((uint32) (SYSCTL_RCGCUART_R0 << CH2MASK(ConfigPtr->SciChannelId))) 
  )
    /* Enables Sci Module in Run-Mode */
    SYSCTL_RCGCUART_R |= 
    (uint32) (SYSCTL_RCGCUART_R0 << CH2MASK(ConfigPtr->SciChannelId));

  /* Disables Channel */
  CHDIS(ConfigPtr->SciChannelId);

  /* Flushes Fifo */
  FLUSHFIFO(ConfigPtr->SciChannelId);

  /* Waits end of transmission/reception */
  while(
    BUSY(ConfigPtr->SciChannelId) ||
    !EMPTYTXFIFO(ConfigPtr->SciChannelId) ||
    !EMPTYRXFIFO(ConfigPtr->SciChannelId)
  );

  /* Clear Errors */
  ERRCLR(ConfigPtr->SciChannelId);

  /* UART Baud Clock Source */
  CLKSYS(ConfigPtr->SciChannelId);

  /* Integer Baud-Rate Divisor Sets-Up */
  SETIBRD(ConfigPtr->SciChannelId, (uint32) STD_OFF);

  /* Fractional Baud-Rate Divisor Sets-Up */
  SETFBRD(ConfigPtr->SciChannelId, (uint32) STD_OFF);

  /* Line Control Sets-Up */
  SETLINECTRL(ConfigPtr->SciChannelId, (uint32) STD_OFF);

  /* System Control Sets-Up */
  SETSYSCTRL(ConfigPtr->SciChannelId, (SCI_CH_HW_RX | SCI_CH_HW_TX));

  /* Clear Interrupt */
  INTCLR(ConfigPtr->SciChannelId, SCI_UART_INT_ALL);

  /* Disables Sci Module in Run-Mode */
  SYSCTL_RCGCUART_R &= 
  ~((uint32) (SYSCTL_RCGCUART_R0 << CH2MASK(ConfigPtr->SciChannelId)));

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

  VALIDATE( ( ConfigPtr != NULL), SCI_INIT_SERVICE_ID, SCI_E_PARAM_CONFIG );

  VALIDATE( ( Sci_CheckCore() != FALSE), SCI_INIT_SERVICE_ID, SCI_E_UNINIT );

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
    ( SYSCTL_RCGCUART_R & ((uint32) (SYSCTL_RCGCUART_R0 << CH2MASK(Channel))) ),
    SCI_WRITETXDATA_SERVICE_ID,
    SCI_E_STATE_TRANSITION,
    E_NOT_OK
  );

  if (FULLTXFIFO(Channel)) return E_NOT_OK;

  TXDATA(Channel, (uint32) Data);

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
    ( SYSCTL_RCGCUART_R & ((uint32) (SYSCTL_RCGCUART_R0 << CH2MASK(Channel))) ),
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

  if (EMPTYRXFIFO(Channel)) return E_NOT_OK;

  rx = RXDATA(Channel);
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

  if (
    SYSCTL_RCGCUART_R & ((uint32) (SYSCTL_RCGCUART_R0 << CH2MASK(Channel)))
  ) {

    INTEN(
      Channel,
      SCI_UART_INT_TX | SCI_UART_INT_RX | SCI_UART_INT_RT | SCI_UART_INT_RX_ERR
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

  if (
    SYSCTL_RCGCUART_R & ((uint32) (SYSCTL_RCGCUART_R0 << CH2MASK(Channel)))
  ) {

    INTCLR(
      Channel,
      SCI_UART_INT_TX | SCI_UART_INT_RX | SCI_UART_INT_RT | SCI_UART_INT_RX_ERR
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
    ( SYSCTL_RCGCUART_R & ((uint32) (SYSCTL_RCGCUART_R0 << CH2MASK(Channel))) ),
    SCI_GOTOSLEEP_SERVICE_ID,
    SCI_E_STATE_TRANSITION,
    E_NOT_OK
  );

  /* Disables Sci Module in Run-Mode */
  SYSCTL_RCGCUART_R &= ~((uint32) (SYSCTL_RCGCUART_R0 << CH2MASK(Channel)));

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
    ( 
      !(
        SYSCTL_RCGCUART_R & ((uint32) (SYSCTL_RCGCUART_R0 << CH2MASK(Channel)))
       )
    ),
    SCI_WAKEUP_SERVICE_ID,
    SCI_E_STATE_TRANSITION,
    E_NOT_OK
  );

  /* Enables Sci Module in Run-Mode */
  SYSCTL_RCGCUART_R |= (uint32) (SYSCTL_RCGCUART_R0 << CH2MASK(Channel));

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
    ( SYSCTL_RCGCUART_R & ((uint32) (SYSCTL_RCGCUART_R0 << CH2MASK(Channel))) ),
    SCI_GETSTATUS_SERVICE_ID,
    SCI_E_STATE_TRANSITION,
    SCI_CH_SLEEP
  );

  VALIDATE_W_RV(
    ( !(RIS(Channel) & SCI_UART_INT_RT) ),
    SCI_GETSTATUS_SERVICE_ID,
    SCI_E_TIMEOUT,
    SCI_NOT_OK
  );

  if (!EMPTYRXFIFO(Channel)) {
    if (RXERR(Channel))		ret = SCI_RX_ERROR;
    else			ret = SCI_RX_OK;
  }
  else if (BUSY(Channel))	ret = SCI_TX_BUSY;
  else if (
    ( RIS(Channel) & SCI_UART_INT_TX ) || ( MIS(Channel) & SCI_UART_INT_TX )
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
    ( SYSCTL_RCGCUART_R & ((uint32) (SYSCTL_RCGCUART_R0 << CH2MASK(Channel))) ),
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
    ( SYSCTL_RCGCUART_R & ((uint32) (SYSCTL_RCGCUART_R0 << CH2MASK(Channel))) ),
    SCI_DISABLETX_SERVICE_ID,
    SCI_E_STATE_TRANSITION,
    E_NOT_OK
  );

  /* Disables Channel */
  CHDIS(Channel);

  /* Flushes Fifo */
  FLUSHFIFO(Channel);

  /* Waits end of transmission/reception */
  while(BUSY(Channel) || !EMPTYTXFIFO(Channel));

  /* Disable TX */
  CHDISTX(Channel);

  /* Enables Channel */
  CHEN(Channel);

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
    ( SYSCTL_RCGCUART_R & ((uint32) (SYSCTL_RCGCUART_R0 << CH2MASK(Channel))) ),
    SCI_ENABLETX_SERVICE_ID,
    SCI_E_STATE_TRANSITION,
    E_NOT_OK
  );

  /* Disables Channel */
  CHDIS(Channel);

  /* Flushes Fifo */
  FLUSHFIFO(Channel);

  /* Waits end of transmission/reception */
  while(BUSY(Channel));

  /* Enable TX */
  CHENTX(Channel);

  /* Enables Channel */
  CHEN(Channel);

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
    ( SYSCTL_RCGCUART_R & ((uint32) (SYSCTL_RCGCUART_R0 << CH2MASK(Channel))) ),
    SCI_DISABLERX_SERVICE_ID,
    SCI_E_STATE_TRANSITION,
    E_NOT_OK
  );

  /* Disables Channel */
  CHDIS(Channel);

  /* Flushes Fifo */
  FLUSHFIFO(Channel);

  /* Waits end of transmission/reception */
  while(BUSY(Channel) || !EMPTYRXFIFO(Channel));

  /* Disable RX */
  CHDISRX(Channel);

  /* Enables Channel */
  CHEN(Channel);

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
    ( SYSCTL_RCGCUART_R & ((uint32) (SYSCTL_RCGCUART_R0 << CH2MASK(Channel))) ),
    SCI_ENABLERX_SERVICE_ID,
    SCI_E_STATE_TRANSITION,
    E_NOT_OK
  );

  /* Disables Channel */
  CHDIS(Channel);

  /* Flushes Fifo */
  FLUSHFIFO(Channel);

  /* Waits end of transmission/reception */
  while(BUSY(Channel));

  /* Enable RX */
  CHENRX(Channel);

  /* Enables Channel */
  CHEN(Channel);

  return E_OK;

}

