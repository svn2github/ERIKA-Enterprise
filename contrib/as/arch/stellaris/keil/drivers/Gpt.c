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
 * GPT367:	Gpt.c Module source file.
 *
 * AUTOSAR-"like" GPT Driver Source File.
 *
 * Author:  2011,  Giuseppe Serano
 */

/*
 * GPT293:	Gpt.c shall include Gpt.h.
 *
 * Comment: Gpt.c has implicit access to the Gpt_Cfg.h through the Gpt.h file.
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
#error	Gpt: version mismatch.
#endif

#include "ee.h"

/* Development error macros. */
#if ( GPT_DEV_ERROR_DETECT == STD_ON )

#include "Det.h"
#if defined(USE_DEM)
#include "Dem.h"
#endif

#define VALIDATE(_exp,_api,_err ) \
  if( !(_exp) ) { \
    Det_ReportError(GPT_MODULE_ID,0,_api,_err); \
    return; \
  }

#define VALIDATE_W_RV(_exp,_api,_err,_rv ) \
  if( !(_exp) ) { \
    Det_ReportError(GPT_MODULE_ID,0,_api,_err); \
    return (_rv); \
  }

#else	/* GPT_DEV_ERROR_DETECT */

#define VALIDATE(_exp,_api,_err ) \
  if( !(_exp) ) { \
    return; \
  }
#define VALIDATE_W_RV(_exp,_api,_err,_rv ) \
  if( !(_exp) ) { \
    return (_rv); \
  }
#endif	/* !GPT_DEV_ERROR_DETECT */

/* GPT Hardware Unit Mask */
#define	HW_CH_UNIT_MASK		0x00000001	/* Mask			*/
#define	HW_CH_UNIT_MASK_SZ_S	0x00000001	/* Mask Size Shift Bits */

/* GPT Hardware Module Mask */
#define	HW_CH_MOD_MASK		0x0000003E	/* Mask */

/* GPT Hardware Base Address */
#define	HW_BASE_ADDR		&TIMER0_CFG_R

/* Hardware Abstraction */
#include "Hardware.h"

/* Hardware Timer Mask */
#define	GPT_HW_TMR_MASK		0x03		/* Mask			*/
#define	GPT_HW_TMR_MASK_SZ	0x02		/* Mask Size in bits    */
#define	GPT_HW_TMR_MASK_SZ_S	0x01		/* Mask Size Shift Bits */

#define	GPT_HW_TMR_WIDE_MASK	0x0000000F	/* Wide Timer Mask */

#define	GPT_HW_TMR_JOIN_MASK	0x00000040	/* Timer Join Mask */

/* Value Masks */
#define	GPT_HW_TMR_EMPTY_VALUE			0x0000000000000000
#define	GPT_HW_TMR_SPLIT_VALUE_MASK		0xFFFFFFFFFF000000
#define	GPT_HW_TMR_SPLIT_WIDE_VALUE_MASK	0xFFFF000000000000
#define	GPT_HW_TMR_JOIN_VALUE_MASK		0xFFFFFFFF00000000
#define	GPT_HW_TMR_JOIN_WIDE_VALUE_MASK		0x0000000000000000
#define	GPT_HW_TMR_JOIN_WIDE_VALUE_S		0x0000000000000020

/* Prescaler Masks */
#define	GPT_HW_TMR_PRESCALER_IN_MASK		0x00000000000000FF
#define	GPT_HW_TMR_PRESCALER_IN_S		0x0000000000000008
#define	GPT_HW_TMR_PRESCALER_OUT_MASK		0x0000000000FF0000
#define	GPT_HW_TMR_PRESCALER_OUT_S		0x0000000000000010
#define	GPT_HW_TMR_WIDE_PRESCALER_IN_MASK	0x000000000000FFFF
#define	GPT_HW_TMR_WIDE_PRESCALER_IN_S		0x0000000000000010
#define	GPT_HW_TMR_WIDE_PRESCALER_OUT_MASK	0x0000FFFF00000000
#define	GPT_HW_TMR_WIDE_PRESCALER_OUT_S		0x0000000000000020
/*
 * Channel to Mask Shift Bits.
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * return	 Mask Shift Bits of a Hardware Timer Module.
 *
 * This macro function returns the number mask shift bits of a hardware timer
 * module referred to numeric id of a channel.
 *
 * Note:	Requires HW_CH_MOD_MASK, GPT_HW_TMR_WIDE_MASK and
 * 		HW_CH_UNIT_MASK_SZ_S macros.
 */
#define	GTP_CH_2_MASK_S(_ch)		(uint32) ( \
  (uint32)(HW_CH_2_MOD(_ch) & (uint32)GPT_HW_TMR_WIDE_MASK) << \
  (uint32)GPT_HW_TMR_MASK_SZ_S \
)

/* Hardware Timer Module Status */
#define	GPT_HW_TMR_STAT_ALL_OFF		0x00
#define	GPT_HW_TMR_STAT_TMRA_ON		0x01
#define	GPT_HW_TMR_STAT_TMRB_ON		0x02
#define	GPT_HW_TMR_STAT_ALL_ON		0x03

/*
 * Channel to Module Status Mask.
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * return	Status Mask of a Hardware Timer Module.
 *
 * This macro function returns the status mask of a hardware timer module
 * referred to numeric id of a channel.
 *
 * Note:	Requires HW_CH_MOD_MASK and HW_CH_UNIT_MASK_SZ_S macros.
 */
#define	GPT_CH_2_MOD_STAT_MASK(_ch)	(uint32)( \
  (uint32)GPT_HW_TMR_STAT_ALL_ON << GTP_CH_2_MASK_S(_ch) \
)

/*
 * Channel to Unit Status Mask.
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * return	Status Mask of a Hardware Timer Unit.
 *
 * This macro function returns the status mask of a hardware timer unit referred
 * to numeric id of a channel.
 *
 * Note:	Requires <tt>HW_CH_MOD_MASK</tt>, <tt>HW_CH_UNIT_MASK</tt> and
 * 		<tt>HW_CH_UNIT_MASK_SZ_S</tt> macros.
 */
#define	GPT_CH_2_UNIT_STAT_MASK(_ch)	(uint32)( \
  ( (uint32)GPT_HW_TMR_STAT_TMRA_ON << HW_CH_2_UNIT(_ch) ) << \
  GTP_CH_2_MASK_S(_ch) \
)

/* Hardware Timer Module Notifications */
#define	GPT_HW_TMR_NOTIF_ALL_OFF	0x00
#define	GPT_HW_TMR_NOTIF_TMRA_ON	0x01
#define	GPT_HW_TMR_NOTIF_TMRB_ON	0x02
#define	GPT_HW_TMR_NOTIF_ALL_ON		0x03

/*
 * Channel to Unit Notifications Mask.
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * return	Notifications Mask of a Hardware Timer Unit.
 *
 * This macro function returns the Notifications mask of a hardware timer unit
 * referred to numeric id of a channel.
 *
 * Note:	Requires <tt>HW_CH_MOD_MASK</tt>, <tt>HW_CH_UNIT_MASK</tt> and
 * 		<tt>HW_CH_UNIT_MASK_SZ_S</tt> macros.
 */
#define	GPT_CH_2_UNIT_NOTIF_MASK(_ch)	(uint32)( \
  ( (uint32)GPT_HW_TMR_NOTIF_TMRA_ON << HW_CH_2_UNIT(_ch) ) << \
  GTP_CH_2_MASK_S(_ch) \
)

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
 * Global config
 */
Gpt_GlobalType Gpt_Global =
{
  FALSE,		/* Init		*/
  NULL_PTR,		/* ConfigPtr	*/
  0x00000000		/* Status	*/
};

/*
 * MCU Global Configuration Reference
 */
typedef struct
{
  boolean			Init;		/* MCU Driver Initialized?    */

  const Mcu_ConfigType *	ConfigPtr;	/* Actual Configuration	      */

  Mcu_ClockType			ClockSetting;	/* Actual Clock Setting	      */

} Mcu_GlobalType;

/*
 * MCU Global Configuration External Reference
 */
extern Mcu_GlobalType Mcu_Global;

/*
 * Usefull Gpt Channel Macros
 */
/* GTP Wide Timer Not in Row Mask */
#define	GTP_TMR_WIDE_ROW_MASK	0x00000010

/* GTP Wide Timer Not in Row Channel Offset */
#define	GTP_TMR_WIDE_ROW_OFFSET	0x00000034

/*
 * Harware Timers Register Offsets
 */
#define	GPT_TMR_CFG_R_OFFSET	0x00000000	/* Configuration	      */
#define	GPT_TMR_MODE_R_OFFSET	0x00000004	/* Mode			      */
#define	GPT_TMR_CTL_R_OFFSET	0x0000000C	/* Control		      */

#define	GPT_TMR_IM_R_OFFSET	0x00000018	/* Interrupt Mask	      */
#define	GPT_TMR_RIS_R_OFFSET	0x0000001C	/* Raw Int Status	      */
#define	GPT_TMR_MIS_R_OFFSET	0x00000020	/* Masked Int Status	      */
#define	GPT_TMR_IC_R_OFFSET	0x00000024	/* Interrupt Clear	      */

#define	GPT_TMR_IL_R_OFFSET	0x00000028	/* Interval Load	      */
#define	GPT_TMR_P_R_OFFSET	0x00000038	/* Prescaler		      */

#define	GPT_TMR_V_R_OFFSET	0x00000050	/* Value		      */
#define	GPT_TMR_PV_R_OFFSET	0x00000064	/* Prescaler Value	      */

/*
 * Hardware Timers Controls
 */
#define	GPT_CH_HW_CTL_A_S_S		0x00000000	/* Timer A Shift Bits */
#define	GPT_CH_HW_CTL_B_S_S		0x00000003	/* Timer B Shift Bits */

/*
 * Hardware Timer Module Interrupt Sources
 */
#define	GPT_TMR_INT_WUE		0x00010000	/* 32/64-Bit Write Update     */
#define	GPT_TMR_INT_TBM		0x00000800	/* Timer B Mode Match	      */
#define	GPT_TMR_INT_CBE		0x00000400	/* Capture B Event	      */
#define	GPT_TMR_INT_CBM		0x00000200	/* Capture B Match	      */
#define	GPT_TMR_INT_TBTO	0x00000100	/* Timer B Time-Out	      */
#define	GPT_TMR_INT_TAM		0x00000010	/* Timer A Mode Match	      */
#define	GPT_TMR_INT_RTC		0x00000008	/* RTC Interrupt	      */
#define	GPT_TMR_INT_CAE		0x00000004	/* Capture A Event	      */
#define	GPT_TMR_INT_CAM		0x00000002	/* Capture A Match	      */
#define	GPT_TMR_INT_TATO	0x00000001	/* Timer A Time-Out	      */

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

/*
 * Hardware Timers Units Interrupt
 */
#define	GPT_CH_HW_INT_A_S_S		0x00000000	/* Timer A Shift Bits */
#define	GPT_CH_HW_INT_B_S_S		0x00000003	/* Timer B Shift Bits */

/*
 * MACRO Utils
 */

/*
 * Channel is Valid Test
 *
 * param	_ch	Numeric ID of a GPT channel. (Gpt_ChannelType)
 * return	TRUE:	Numeric ID od a GPT channel 
 * 		FALSE:	Invalid Channel
 *
 * This macro function returns if numeric id of a channel is valid or not.
 */
#define	GPT_CH_IS_VALID(_ch)	(boolean)( \
	( (uint32)_ch <= (uint32)GPT_CHANNEL_W_1_B ) || ( \
		( (uint32)_ch >= (uint32)GPT_CHANNEL_W_2_A ) && \
		( (uint32)_ch <= (uint32)GPT_CHANNEL_W_5_B ) \
	) || ( \
		(\
			( \
				( (uint32)_ch >= (uint32)GPT_CHANNEL_J_0 ) && \
				( (uint32)_ch <= (uint32)GPT_CHANNEL_J_W_1 ) \
			) || ( \
				( \
					(uint32)_ch >= \
					(uint32)GPT_CHANNEL_J_W_2 \
				) && ( \
					(uint32)_ch <= \
					(uint32)GPT_CHANNEL_J_W_5 \
				) \
			) \
		) && !HW_CH_2_UNIT(_ch) \
	) \
)

/*
 * Channel is Wide Timer Test
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * return	TRUE:	Wide Timer
 * 		FALSE:	Normal Timer
 *
 * This macro function returns if the hardware timer module, referred to numeric
 * id of a channel is a wide timer or not.
 */
#define	GPT_CH_IS_WIDE(_ch)	(boolean)( \
	( \
		( (uint32)_ch >= (uint32)GPT_CHANNEL_W_0_A ) && \
		( (uint32)_ch <= (uint32)GPT_CHANNEL_W_5_B ) \
	) || \
	( \
		( (uint32)_ch >= (uint32)GPT_CHANNEL_J_W_0 ) && \
		( (uint32)_ch <= (uint32)GPT_CHANNEL_J_W_5 ) \
	) \
)

/*
 * Channel is Joined Timer Test
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * return	TRUE:	Joined Timer
 * 		FALSE:	Splitted Timer
 *
 * This macro function returns if the hardware timer module, referred to numeric
 * id of a channel is a joined timer or not.
 */
#define	GPT_CH_IS_JOINED(_ch)	(boolean)( \
	(uint32)_ch & (uint32)GPT_HW_TMR_JOIN_MASK \
)

/*
 * Channel is Wide Timer Not In Row Test
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * return	TRUE:	Wide Timer Not In Row
 * 		FALSE:	Wide Timer In Row
 *
 * This macro function returns if the hardware timer module, referred to numeric
 * id of a channel is a "wide timer not in row" or not.
 */
#define	GPT_CH_IS_WIDE_NOT_IN_ROW(_ch)	(boolean)( \
	( (uint32)_ch & (uint32)GTP_TMR_WIDE_ROW_MASK ) \
)

/*
 * Hardware Configuration Retrieval.
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * return	Hardware Timer Module Configuration
 */
#define	GPT_GET_CFG(_ch)	HW_CH_2_MOD_REG(_ch, GPT_TMR_CFG_R_OFFSET)

/*
 * Hardware Configuration Setup.
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * param	_cfg	Harware Timer Module Configuratione
 */
#define	GPT_SET_CFG(_ch, _cfg)	( \
	HW_CH_2_MOD_REG(_ch, GPT_TMR_CFG_R_OFFSET) = (uint32)_cfg \
)

/*
 * Harware Mode Retrieval.
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * return	Hardware Timer Unit Mode
 */
#define	GPT_GET_MODE(_ch)	HW_CH_2_UINT_REG(_ch, GPT_TMR_MODE_R_OFFSET)

/*
 * Hardware Mode Setup.
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * param	_mode	Hardware Timer Unit Mode
 */
#define	GPT_SET_MODE(_ch, _mode)	( \
	HW_CH_2_UNIT_REG(_ch, GPT_TMR_MODE_R_OFFSET) = (uint32)_mode \
)

/*
 * Hardware Control Retrieval.
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * return	Hardware Timer Module Control
 */
#define	GPT_GET_CTL(_ch)	( \
	HW_CH_2_MOD_REG(_ch, GPT_TMR_CTL_R_OFFSET) >> (uint32)( \
		HW_CH_2_UNIT(_ch) << (uint32)GPT_CH_HW_CTL_B_S_S \
	) \
)

/*
 * Hardware Control Setup.
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * param	_ctl	Hardware Timer Module Control
 */
#define	GPT_SET_CTL(_ch, _ctl)	( \
	HW_CH_2_MOD_REG(_ch, GPT_TMR_CTL_R_OFFSET) |= ( \
		(uint32)_ctl << (uint32)( \
			HW_CH_2_UNIT(_ch) << (uint32)GPT_CH_HW_CTL_B_S_S \
		) \
	) \
)

/*
 * Hardware Counter Retrieval
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * return	Hardware Timer Unit Counter
 */
#define	GPT_GET_COUNTER(_ch)	HW_CH_2_UNIT_REG(_ch, GPT_TMR_V_R_OFFSET)

/*
 * Hardware Start Counter Retrieval
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * return	Hardware Timer Unit Start Counter
 */
#define	GPT_GET_START_COUNTER(_ch)	\
	HW_CH_2_UNIT_REG(_ch, GPT_TMR_IL_R_OFFSET)

/*
 * Hardware Counter Setup.
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * param	_val	Hardware Timer Unit Counter Value
 */
#define	GPT_SET_COUNTER(_ch, _val)	( \
	HW_CH_2_UNIT_REG(_ch, GPT_TMR_IL_R_OFFSET) = (uint32)_val \
)

/*
 * Hardware Prescaler Retrieval
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * return	Hardware Timer Unit Prescaler
 */
#define	GPT_GET_PRESCALER(_ch)	HW_CH_2_UNIT_REG(_ch, GPT_TMR_PV_R_OFFSET)

/*
 * Hardware Start Prescaler Retrieval
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * return	Hardware Timer Unit Start Prescaler
 */
#define	GPT_GET_START_PRESCALER(_ch)	\
	HW_CH_2_UNIT_REG(_ch, GPT_TMR_P_R_OFFSET)

/*
 * Hardware Prescaler Setup.
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * param	_val	Hardware Timer Unit Prescaler Value
 */
#define	GPT_SET_PRESCALER(_ch, _val)	( \
	HW_CH_2_UNIT_REG(_ch, GPT_TMR_P_R_OFFSET) = (uint32)_val \
)

/*
 * Raw Interrupt Status Retrieval.
 */
#define	GPT_GET_RIS(_ch)	HW_CH_2_MOD_REG(_ch, GPT_TMR_RIS_R_OFFSET)

/*
 * Masked Interrupt Status Retrieval.
 */
#define	GPT_GET_MIS(_ch)	HW_CH_2_MOD_REG(_ch, GPT_TMR_MIS_R_OFFSET)

/*
 * Interrupt Clear
 */
#define	GPT_INT_CLR(_ch, _srcs)	( \
	HW_CH_2_MOD_REG(_ch, GPT_TMR_IC_R_OFFSET) |= (uint32)_srcs \
)

/*
 * Interrupt Enable
 */
#define	GPT_INT_EN(_ch, _srcs)	( \
	HW_CH_2_MOD_REG(_ch, GPT_TMR_IM_R_OFFSET) |= (uint32)_srcs \
)

/*
 * Interrupt Disable
 */
#define	GPT_INT_DIS(_ch, _srcs)	( \
	HW_CH_2_MOD_REG(_ch, GPT_TMR_IM_R_OFFSET) &= ~((uint32)_srcs) \
)

/*
 * Timer Stop.
 */
#define	GPT_TMR_STOP(_ch)	( \
	HW_CH_2_MOD_REG(_ch, GPT_TMR_CTL_R_OFFSET) &= \
	(uint32)~( \
		(uint32)GPT_CH_HW_CTL_ENABLE << (uint32)( \
			HW_CH_2_UNIT(_ch) << (uint32)GPT_CH_HW_CTL_B_S_S \
		) \
	) \
)

/*
 * Timer Start.
 */
#define	GPT_TMR_START(_ch)	( \
	HW_CH_2_MOD_REG(_ch, GPT_TMR_CTL_R_OFFSET) |= \
	(uint32)( \
		(uint32)GPT_CH_HW_CTL_ENABLE << (uint32)( \
			HW_CH_2_UNIT(_ch) << (uint32)GPT_CH_HW_CTL_B_S_S \
		)\
	) \
)

/*
 * Timer Running.
 */
#define	GPT_TMR_RUNNING(_ch)	( \
	HW_CH_2_MOD_REG(_ch, GPT_TMR_CTL_R_OFFSET) & \
	(uint32)( \
		(uint32)GPT_CH_HW_CTL_ENABLE << (uint32)( \
			HW_CH_2_UNIT(_ch) << (uint32)GPT_CH_HW_CTL_B_S_S \
		)\
	) \
)

/*
 * Timer Time-Out
 */
#define	GPT_TMR_TIMEOUT(_ch) ( \
	( \
		( \
			GPT_GET_RIS(_ch) >> (uint32)( \
				HW_CH_2_UNIT(_ch) << \
				(uint32)GPT_CH_HW_INT_B_S_S \
			) \
		) & GPT_TMR_INT_TATO \
	) || ( \
		( \
			GPT_GET_MIS(_ch) >> (uint32)( \
				HW_CH_2_UNIT(_ch) << \
				(uint32)GPT_CH_HW_INT_B_S_S \
			) \
		) & GPT_TMR_INT_TATO \
	) \
)

/*
 * Timer Time-Out Interrupt Clear
 */
#define	GPT_TMR_TIMEOUT_INT_CLR(_ch) ( \
	GPT_INT_CLR( \
		_ch, \
		( \
			(uint32)GPT_TMR_INT_TATO << (uint32)( \
				HW_CH_2_UNIT(_ch) << \
				(uint32)GPT_CH_HW_INT_B_S_S \
			) \
		) \
	)\
)


/*
 * Timer Time-Out Interrupt Enable
 */
#define	GPT_TMR_TIMEOUT_INT_EN(_ch) ( \
	GPT_INT_EN( \
		_ch, \
		( \
			(uint32)GPT_TMR_INT_TATO << (uint32)( \
				HW_CH_2_UNIT(_ch) << \
				(uint32)GPT_CH_HW_INT_B_S_S \
			) \
		) \
	)\
)

/*
 * Timer Time-Out Interrupt Disable
 */
#define	GPT_TMR_TIMEOUT_INT_DIS(_ch) ( \
	GPT_INT_DIS( \
		_ch, \
		( \
			(uint32)GPT_TMR_INT_TATO << (uint32)( \
				HW_CH_2_UNIT(_ch) << \
				(uint32)GPT_CH_HW_INT_B_S_S \
			) \
		) \
	)\
)

/*
 * Gpt Enable Channel
 *
 * param	Channel	Numeric ID of a GPT Channel.
 */
static void Gpt_EnableChannel(
  Gpt_ChannelType	Channel
)
{

  if ( !GPT_CH_IS_WIDE(Channel) )
    SYSCTL_RCGCTIMER_R |= HW_CH_2_CGC_MASK(Channel);
  else if ( GPT_CH_IS_WIDE_NOT_IN_ROW(Channel) )
    SYSCTL_RCGCWTIMER_R |= 
    HW_CH_2_CGC_MASK(Channel - (Gpt_ChannelType)GTP_TMR_WIDE_ROW_OFFSET);
  else
    SYSCTL_RCGCWTIMER_R |=
    HW_CH_2_CGC_MASK(Channel - (Gpt_ChannelType)GPT_CHANNEL_W_0_A);

}

/*
 * Gpt Disable Channel
 *
 * param	Channel	Numeric ID of a GPT Channel.
 */
static void Gpt_DisableChannel(
  Gpt_ChannelType	Channel
)
{

  if ( !GPT_CH_IS_WIDE(Channel) )
    SYSCTL_RCGCTIMER_R &= ~HW_CH_2_CGC_MASK(Channel);
  else if ( GPT_CH_IS_WIDE_NOT_IN_ROW(Channel) )
    SYSCTL_RCGCWTIMER_R &= 
    ~HW_CH_2_CGC_MASK(Channel - (Gpt_ChannelType)GTP_TMR_WIDE_ROW_OFFSET);
  else
    SYSCTL_RCGCWTIMER_R &=
    ~HW_CH_2_CGC_MASK(Channel - (Gpt_ChannelType)GPT_CHANNEL_W_0_A);

}

/*
 * Gpt Reset Channel
 *
 * param	Channel	Numeric ID of a GPT Channel.
 */
static void Gpt_ResetChannel(
  Gpt_ChannelType	Channel
)
{

  register uint32	mask;

  if ( !GPT_CH_IS_WIDE(Channel) ) {
    mask = HW_CH_2_CGC_MASK(Channel);
    SYSCTL_SRTIMER_R |= mask;			/* Start Channel Module Reset */
    SYSCTL_SRTIMER_R &= ~mask;			/* Stop  Channel Module Reset */
    while ( !( SYSCTL_PRTIMER_R & mask ) );	/* Wait Reset		      */
  }
  else {
    if ( GPT_CH_IS_WIDE_NOT_IN_ROW(Channel) ) {
      mask =
      HW_CH_2_CGC_MASK(Channel - (Gpt_ChannelType)GTP_TMR_WIDE_ROW_OFFSET);
    }
    else {
      mask =
      HW_CH_2_CGC_MASK(Channel - (Gpt_ChannelType)GPT_CHANNEL_W_0_A);
    }
    SYSCTL_SRWTIMER_R |= mask;			/* Start Channel Module Reset */
    SYSCTL_SRWTIMER_R &= ~mask;			/* Stop  Channel Module Reset */
    while ( !( SYSCTL_PRWTIMER_R & mask ) );	/* Wait Reset		      */
  }

}

/*
 * Gpt Channel Initialization.
 */
static void Gpt_InitGptChannel(
  const Gpt_ChannelConfigType *	ConfigPtr
)
{

  register boolean		joined;
  register boolean		wide;

  /* Gpt Module Disabled? */
  if ( 
    !( Gpt_Global.Status & GPT_CH_2_MOD_STAT_MASK(ConfigPtr->GptChannelId) )
  ) {

    /* Enables Gpt Module in Run-Mode */
    Gpt_EnableChannel(ConfigPtr->GptChannelId);

  }

  /* Turn-on Gpt Unit */
  Gpt_Global.Status |= GPT_CH_2_UNIT_STAT_MASK(ConfigPtr->GptChannelId);

  /* Stop Timer. */
  GPT_TMR_STOP(ConfigPtr->GptChannelId);

  /* Heavy Checks Made Once!!! */
  joined = GPT_CH_IS_JOINED(ConfigPtr->GptChannelId);
  wide = GPT_CH_IS_WIDE(ConfigPtr->GptChannelId);

  /* Configuration Setup */
  /* GPT_SET_CFG(ConfigPtr->GptChannelId, ConfigPtr->GptChannelHWConfig); */
  if ( joined )
    GPT_SET_CFG(ConfigPtr->GptChannelId, GPT_CH_HW_CFG_JOIN);
  else
    GPT_SET_CFG(ConfigPtr->GptChannelId, GPT_CH_HW_CFG_SPLIT);

  /* Mode Setup */
  /* GPT_SET_MODE(ConfigPtr->GptChannelId, ConfigPtr->GptChannelHWMode); */
  if (ConfigPtr->GptChannelMode == GPT_CH_MODE_CONTINUOUS)
    GPT_SET_MODE(ConfigPtr->GptChannelId, GPT_CH_HW_MODE_PERIODIC);
  else
    GPT_SET_MODE(ConfigPtr->GptChannelId, GPT_CH_HW_MODE_ONE_SHOT);

  /* Control Setup */
  /* GPT_SET_CTL(ConfigPtr->GptChannelId, ConfigPtr->GptChannelHWCtrl); */
#ifdef	DEBUG
  GPT_SET_CTL(ConfigPtr->GptChannelId, GPT_CH_HW_CTL_STALL);
#endif

  /* Clear Interrupts: cleared by harware initialization */
  /* GPT_INT_CLR(ConfigPtr->GptChannelId, GPT_TMR_INT_ALL); */

  /* Clear Prescaler: cleared by hardware initialization */
  /* GPT_SET_PRESCALER(ConfigPtr->GptChannelId, GPT_HW_TMR_EMPTY_VALUE); */
  
  /* Clear Counter */
  if ( joined && wide ) 
    GPT_SET_COUNTER(ConfigPtr->GptChannelId + 1, GPT_HW_TMR_EMPTY_VALUE);

  GPT_SET_COUNTER(ConfigPtr->GptChannelId, GPT_HW_TMR_EMPTY_VALUE);

}

/*
 * Gpt Channel De-Initialization.
 */
#if ( GPT_DEINIT_API == STD_ON )
static void Gpt_DeInitGptChannel(
  const Gpt_ChannelConfigType *	ConfigPtr
)
{

  /* Gpt Module Disabled? */
  if (
    !( Gpt_Global.Status & GPT_CH_2_MOD_STAT_MASK(ConfigPtr->GptChannelId) )
  ) {

    /* Enables Gpt Module in Run-Mode */
    Gpt_EnableChannel(ConfigPtr->GptChannelId);

  }

  /* Disable Gpt Module in Run-Mode */
  Gpt_ResetChannel(ConfigPtr->GptChannelId);

  /* Turn-off Gpt Unit */
  Gpt_Global.Status &= ~GPT_CH_2_UNIT_STAT_MASK(ConfigPtr->GptChannelId);

  /* Gpt Module Disabled? */
  if (
    !( Gpt_Global.Status & GPT_CH_2_MOD_STAT_MASK(ConfigPtr->GptChannelId) )
  ) {

    /* Disable Gpt Module in Run-Mode */
    Gpt_DisableChannel(ConfigPtr->GptChannelId);

  }

}
#endif

/*
 * Gpt_Init implementation.
 */
void Gpt_Init(
  const Gpt_ConfigType *	ConfigPtr
)
{

  register uint32 channel;

  VALIDATE( ( ConfigPtr != NULL), GPT_INIT_SERVICE_ID, GPT_E_PARAM_CONFIG );

  VALIDATE( ( Hw_CheckCore() == E_OK), GPT_INIT_SERVICE_ID, GPT_E_UNINIT );

  for (channel = 0; channel < ConfigPtr->GptNumberOfGptChannels; channel++)
  {

    /* Initializes Gpt Channel. */
    Gpt_InitGptChannel(&(ConfigPtr->GptChannels[channel]));

  }

  Gpt_Global.ConfigPtr = ConfigPtr;
  Gpt_Global.Init = TRUE;

}

#if ( GPT_DEINIT_API == STD_ON )
/*
 * Gpt_DeInit implementation.
 */
void Gpt_DeInit(
  void
)
{

  register uint32 channel;

  VALIDATE(
    ( Gpt_Global.Init == TRUE ),
    GPT_DEINIT_SERVICE_ID,
    GPT_E_UNINIT
  );

  for (
    channel = 0;
    channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels;
    channel++
  )
  {

    /* De-Initializes Gpt Channel. */
    Gpt_DeInitGptChannel(&(Gpt_Global.ConfigPtr->GptChannels[channel]));

  }

  Gpt_Global.Init = FALSE;
  Gpt_Global.ConfigPtr = NULL_PTR;

}
#endif

#if ( \
  ( GPT_TIME_ELAPSED_API == STD_ON ) || ( GPT_TIME_REMAINING_API == STD_ON ) \
)
/*
 * Gpt_GetHWTimeRemaining implementation.
 */
static Gpt_ValueType Gpt_GetHWTimeRemaining(
  Gpt_ChannelType	Channel
)
{

  Gpt_ValueType		ret = GPT_HW_TMR_EMPTY_VALUE;
  register boolean	wide;
  register uint32	counter1;
  register uint32	counter2;
  register uint32	prescaler1;
  register uint32	prescaler2;

  wide = GPT_CH_IS_WIDE(Channel);	/* Heavy Check Made Once!!! */

  if ( GPT_CH_IS_JOINED(Channel) ) {
    /* Joined Channel: NO PRESCALERS!!! */
    if ( wide ) {

      do {
	counter1 = GPT_GET_COUNTER(Channel + 1);	/* TMR B 1st Read     */
	prescaler1 = GPT_GET_COUNTER(Channel);		/* TMR A Read	      */
	counter2 = GPT_GET_COUNTER(Channel + 1);	/* TMR B 2nd Read     */
      } while (counter1 != counter2);			/* Consistency Check  */
      
      ret = ((Gpt_ValueType)counter1 << GPT_HW_TMR_JOIN_WIDE_VALUE_S) +
	    (Gpt_ValueType)prescaler1;

    }
    else ret = (Gpt_ValueType)GPT_GET_COUNTER(Channel);
  }
  else if ( wide ) {	/* Wide Channel Not Joined */
    prescaler1 = GPT_HW_TMR_EMPTY_VALUE;
    do {
      prescaler2 = prescaler1;
      counter2 = GPT_GET_COUNTER(Channel);	/* Counter 1st Read	*/
      prescaler1 = GPT_GET_PRESCALER(Channel);	/* Prescaler Read	*/
      counter1 = GPT_GET_COUNTER(Channel);	/* Counter 2nd Read	*/
      if (
	( prescaler1 == prescaler2 ) &&
	( prescaler1 == GPT_HW_TMR_EMPTY_VALUE )
      ) {	/* Channel Without Prescaler */
	counter2 = counter1;
	ret = (Gpt_ValueType)counter1;
      }
      else {	/* Channel With Prescaler */
	ret = ((Gpt_ValueType)counter1 << GPT_HW_TMR_WIDE_PRESCALER_IN_S) +
	      (Gpt_ValueType)prescaler1;
      }
    } while (counter1 != counter2);	/* Consistency Check	*/
  }
  else {	/* Not Wide Channel Not Joined */
    do {
      /* Counter 1st Read	*/
      counter2 = GPT_GET_COUNTER(Channel);
      /* Counter 2nd Read	*/
      counter1 = GPT_GET_COUNTER(Channel);
      prescaler1 =
      (counter1 & GPT_HW_TMR_PRESCALER_OUT_MASK) >> GPT_HW_TMR_PRESCALER_OUT_S;
      prescaler2 =
      (counter2 & GPT_HW_TMR_PRESCALER_OUT_MASK) >> GPT_HW_TMR_PRESCALER_OUT_S;
      counter1 = (counter1 & ~((Gpt_ValueType)GPT_HW_TMR_PRESCALER_OUT_MASK));
      counter2 = (counter2 & ~((Gpt_ValueType)GPT_HW_TMR_PRESCALER_OUT_MASK));
      if ( 
	( prescaler1 == prescaler2 ) &&
	( prescaler1 == GPT_HW_TMR_EMPTY_VALUE )
      ) {	/* Channel Without Prescaler */
	ret = (Gpt_ValueType)counter1;
	counter2 = counter1;
      }
      else {	/* Channel With Prescaler */
	ret = ((Gpt_ValueType)counter1 << GPT_HW_TMR_PRESCALER_IN_S) + 
	      (Gpt_ValueType)prescaler1;
      }
    } while (counter1 != counter2);	/* Consistency Check	*/
  }

  return ret;

}
#endif	/* 
	 * ( GPT_TIME_ELAPSED_API == STD_ON ) ||
	 * ( GPT_TIME_REMAINING_API == STD_ON )
	 */

#if ( GPT_TIME_ELAPSED_API == STD_ON )
/*
 * Gpt_GetHWStartTime implementation.
 */
static Gpt_ValueType Gpt_GetHWStartTime(
  Gpt_ChannelType	Channel
)
{

  Gpt_ValueType		ret = GPT_HW_TMR_EMPTY_VALUE;
  register boolean	wide;
  register uint32	counter;
  register uint32	prescaler;

  wide = GPT_CH_IS_WIDE(Channel);	/* Heavy Check Made Once!!! */

  if ( GPT_CH_IS_JOINED(Channel) ) {
    /* Joined Channel: NO PRESCALERS!!! */
    if ( wide ) {
      counter = GPT_GET_START_COUNTER(Channel + 1);	/* TMR B Read	      */
      prescaler = GPT_GET_START_COUNTER(Channel);	/* TMR A Read	      */
      ret = ((Gpt_ValueType)counter << GPT_HW_TMR_JOIN_WIDE_VALUE_S) +
	    (Gpt_ValueType)prescaler;
    }
    else ret = (Gpt_ValueType)GPT_GET_START_COUNTER(Channel);
  }
  else {	/* Splitted Channel */

    prescaler = GPT_GET_START_PRESCALER(Channel);
    counter = GPT_GET_START_COUNTER(Channel);

    if ( prescaler == GPT_HW_TMR_EMPTY_VALUE ) {

      /* NO PRESCALER */
      ret = (Gpt_ValueType)counter;

    }
    else if ( wide ) {

      /* Wide Channel With Prescaler */
      ret = ((Gpt_ValueType)counter << GPT_HW_TMR_WIDE_PRESCALER_IN_S) +
	    (Gpt_ValueType)prescaler;

    }
    else {

      /* Not-Wide Channel With Prescaler */
      ret = ((Gpt_ValueType)counter << GPT_HW_TMR_PRESCALER_IN_S) +
	    (Gpt_ValueType)prescaler;

    }

  }
  
  return ret;

}

/*
 * Gpt_GetTimeElapsed implementation.
 */
Gpt_ValueType Gpt_GetTimeElapsed(
  Gpt_ChannelType	Channel
)
{
  register uint32	channel;

  VALIDATE_W_RV(
    ( Gpt_Global.Init == TRUE ),
    GPT_GETTIMEELAPSED_SERVICE_ID,
    GPT_E_UNINIT,
    GPT_HW_TMR_EMPTY_VALUE
  );

  VALIDATE_W_RV(
    GPT_CH_IS_VALID(Channel) == TRUE,
    GPT_GETTIMEELAPSED_SERVICE_ID,
    GPT_E_PARAM_CHANNEL,
    GPT_HW_TMR_EMPTY_VALUE
  );

  for (
    channel = 0;
    (
      ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
      ( Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId != Channel )
    );
    channel++
  );

  VALIDATE_W_RV(
    ( ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) ),
    GPT_GETTIMEELAPSED_SERVICE_ID,
    GPT_E_PARAM_CHANNEL,
    GPT_HW_TMR_EMPTY_VALUE
  );

  VALIDATE_W_RV(
    ( (Gpt_Global.Status & GPT_CH_2_UNIT_STAT_MASK(Channel)) ),
    GPT_GETTIMEELAPSED_SERVICE_ID,
    GPT_E_STATE_TRANSITION,
    GPT_HW_TMR_EMPTY_VALUE
  );

  return Gpt_GetHWStartTime(Channel) - Gpt_GetHWTimeRemaining(Channel);
}
#endif

#if ( GPT_TIME_REMAINING_API == STD_ON )
/*
 * Gpt_GetTimeRemainig implementation.
 */
Gpt_ValueType Gpt_GetTimeRemaining(
  Gpt_ChannelType	Channel
)
{

  register uint32	channel;

  VALIDATE_W_RV(
    ( Gpt_Global.Init == TRUE ),
    GPT_GETTIMEREMAINING_SERVICE_ID,
    GPT_E_UNINIT,
    GPT_HW_TMR_EMPTY_VALUE
  );

  VALIDATE_W_RV(
    GPT_CH_IS_VALID(Channel) == TRUE,
    GPT_GETTIMEREMAINING_SERVICE_ID,
    GPT_E_PARAM_CHANNEL,
    GPT_HW_TMR_EMPTY_VALUE
  );

  for (
    channel = 0;
    (
      ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
      ( Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId != Channel )
    );
    channel++
  );

  VALIDATE_W_RV(
    ( ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) ),
    GPT_GETTIMEREMAINING_SERVICE_ID,
    GPT_E_PARAM_CHANNEL,
    GPT_HW_TMR_EMPTY_VALUE
  );

  VALIDATE_W_RV(
    ( (Gpt_Global.Status & GPT_CH_2_UNIT_STAT_MASK(Channel)) ),
    GPT_GETTIMEREMAINING_SERVICE_ID,
    GPT_E_STATE_TRANSITION,
    GPT_HW_TMR_EMPTY_VALUE
  );

  return Gpt_GetHWTimeRemaining(Channel);
}
#endif

/*
 * Gpt_StartTimer implementation.
 */
void Gpt_StartTimer(
  Gpt_ChannelType	Channel,
  Gpt_ValueType		Value
)
{

  register uint32 channel;
  register boolean joined;
  register boolean wide;

  VALIDATE(
    ( Gpt_Global.Init == TRUE ),
    GPT_STARTTIMER_SERVICE_ID,
    GPT_E_UNINIT
  );

  VALIDATE(
    GPT_CH_IS_VALID(Channel) == TRUE,
    GPT_STARTTIMER_SERVICE_ID,
    GPT_E_PARAM_CHANNEL
  );

  for (
    channel = 0;
    (
      ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
      ( Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId != Channel )
    );
    channel++
  );

  VALIDATE(
    ( ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) ),
    GPT_STARTTIMER_SERVICE_ID,
    GPT_E_PARAM_CHANNEL
  );

  VALIDATE(
    ( (Gpt_Global.Status & GPT_CH_2_UNIT_STAT_MASK(Channel)) ),
    GPT_STARTTIMER_SERVICE_ID,
    GPT_E_STATE_TRANSITION
  );

  /* Heavy Checks Made Once!!! */
  joined = GPT_CH_IS_JOINED(Channel);
  wide = GPT_CH_IS_WIDE(Channel);

  VALIDATE(
    ( 
      (Value > 0) && 
      ( 
	( 
	  joined && wide	/* Joined-Wide Channel: 64 bits	      */
	) || (
	  joined && !wide &&	/* Joined Channel: 32 bits	      */
	  !(Value & GPT_HW_TMR_JOIN_VALUE_MASK)
	) || (
	  !joined && wide &&	/* Splitted-Wide Channel: max 48 bits */
	  !(Value & GPT_HW_TMR_SPLIT_WIDE_VALUE_MASK)
	) || (
	  !joined && !wide &&	/* Splitted Channel: max 24 bits      */
	  !(Value & GPT_HW_TMR_SPLIT_VALUE_MASK)
	)
      )
    ),
    GPT_STARTTIMER_SERVICE_ID,
    GPT_E_PARAM_VALUE
  );

  VALIDATE(
    ( !GPT_TMR_RUNNING(Channel) ),
    GPT_STARTTIMER_SERVICE_ID,
    GPT_E_BUSY
  );

  if ( joined ) {
    /* Joined Channels: NO PRESCALERS!!! */
    if ( wide ) {
      /* Joined-Wide Channel: TMR B Write */
      GPT_SET_COUNTER(
	Channel + 1, ( (uint64)Value >> (uint32)GPT_HW_TMR_JOIN_WIDE_VALUE_S )
      );
    }
    GPT_SET_COUNTER(Channel, Value);
  }
  else if ( wide && (Value & GPT_HW_TMR_WIDE_PRESCALER_OUT_MASK) ) {
    /* Wide Channel With Prescaler */
    GPT_SET_PRESCALER(Channel, ( Value & GPT_HW_TMR_WIDE_PRESCALER_IN_MASK ));
    GPT_SET_COUNTER(Channel, ( Value >> GPT_HW_TMR_WIDE_PRESCALER_IN_S ));
  }
  else if ( !wide && (Value & GPT_HW_TMR_PRESCALER_OUT_MASK) ) {
    /* Not-Wide Channel With Prescaler */
    GPT_SET_PRESCALER(Channel, ( Value & GPT_HW_TMR_PRESCALER_IN_MASK ));
    GPT_SET_COUNTER(Channel, ( Value >> GPT_HW_TMR_PRESCALER_IN_S ));
  }
  else {
    /* Wide or Not-Wide Channel Without Prescaler */
    GPT_SET_PRESCALER(Channel, GPT_HW_TMR_EMPTY_VALUE);
    GPT_SET_COUNTER(Channel, Value);
  }

  /* Time-Out Interrupt Clear*/
  GPT_TMR_TIMEOUT_INT_CLR(Channel);

  /* Start Timer */
  GPT_TMR_START(Channel);

}

/*
 * Gpt_StopTimer implementation.
 */
void Gpt_StopTimer(
  Gpt_ChannelType	Channel
)
{

  register uint32 channel;

  VALIDATE(
    ( Gpt_Global.Init == TRUE ),
    GPT_STOPTIMER_SERVICE_ID,
    GPT_E_UNINIT
  );

  VALIDATE(
    GPT_CH_IS_VALID(Channel) == TRUE,
    GPT_STOPTIMER_SERVICE_ID,
    GPT_E_PARAM_CHANNEL
  );

  for (
    channel = 0;
    (
      ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
      ( Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId != Channel )
    );
    channel++
  );

  VALIDATE(
    ( ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) ),
    GPT_STOPTIMER_SERVICE_ID,
    GPT_E_PARAM_CHANNEL
  );

  VALIDATE(
    ( (Gpt_Global.Status & GPT_CH_2_UNIT_STAT_MASK(Channel)) ),
    GPT_STOPTIMER_SERVICE_ID,
    GPT_E_STATE_TRANSITION
  );

  /* Stop Timer */
  GPT_TMR_STOP(Channel);

  /* Time-Out Interrupt Clear*/
  GPT_TMR_TIMEOUT_INT_CLR(Channel);

}

#if ( GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )
/*
 * Gpt_EnableNotification implementation.
 */
void Gpt_EnableNotification(
  Gpt_ChannelType	Channel
)
{

  register uint32 channel;

  VALIDATE(
    ( Gpt_Global.Init == TRUE ),
    GPT_ENABLENOTIFICATION_SERVICE_ID,
    GPT_E_UNINIT
  );

  VALIDATE(
    GPT_CH_IS_VALID(Channel) == TRUE,
    GPT_ENABLENOTIFICATION_SERVICE_ID,
    GPT_E_PARAM_CHANNEL
  );

  for (
    channel = 0;
    (
      ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
      ( Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId != Channel )
    );
    channel++
  );

  VALIDATE(
    (
      ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
      (
	Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr !=
	NULL_PTR
      )
    ),
    GPT_ENABLENOTIFICATION_SERVICE_ID,
    GPT_E_PARAM_CHANNEL
  );

  /* Gpt Unit Enabled? */
  if ( (Gpt_Global.Status & GPT_CH_2_UNIT_STAT_MASK(Channel)) )
  {
    /* Enable Time-out Interrupt */
    GPT_TMR_TIMEOUT_INT_EN(Channel);
  }

  /* Turn-on Gpt Unit Notifications*/
  Gpt_Global.Notifications |= GPT_CH_2_UNIT_NOTIF_MASK(Channel);

}

/*
 * Gpt_DisableNotification implementation.
 */
void Gpt_DisableNotification(
  Gpt_ChannelType	Channel
)
{

  register uint32 channel;

  VALIDATE(
    ( Gpt_Global.Init == TRUE ),
    GPT_DISABLENOTIFICATIONS_SERVICE_ID,
    GPT_E_UNINIT
  );

  VALIDATE(
    GPT_CH_IS_VALID(Channel),
    GPT_DISABLENOTIFICATIONS_SERVICE_ID,
    GPT_E_PARAM_CHANNEL
  );

  for (
    channel = 0;
    (
      ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
      ( Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId != Channel )
    );
    channel++
  );

  VALIDATE(
    (
      ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
      ( 
	Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr !=
	NULL_PTR
      )
    ),
    GPT_DISABLENOTIFICATION_SERVICE_ID,
    GPT_E_PARAM_CHANNEL
  );

  /* Gpt Unit Enabled? */
  if ( (Gpt_Global.Status & GPT_CH_2_UNIT_STAT_MASK(Channel)) )
  {
    /* Disable Time-out Interrupt */
    GPT_TMR_TIMEOUT_INT_DIS(Channel);
  }

  /* Turn-off Gpt Unit Notifications */
  Gpt_Global.Notifications &= ~GPT_CH_2_UNIT_NOTIF_MASK(Channel);

}
#endif

#if ( \
  ( GPT_REPORT_WAKEUP_SOURCE == STD_ON ) && \
  ( GPT_WAKEUP_FUNCTIONALITY_API == STD_ON ) \
)
/*
 * Gpt_SetMode implementation.
 */
void Gpt_SetMode(
  Gpt_ModeType	Mode
)
{

  VALIDATE(
    ( Gpt_Global.Init == TRUE ),
    GPT_SETMODE_SERVICE_ID,
    GPT_E_UNINIT
  );

  VALIDATE(
    ( ( Mode == GPT_MODE_NORMAL ) || ( Mode == GPT_MODE_SLEEP ) ),
    GPT_SETMODE_SERVICE_ID,
    GPT_E_PARAM_MODE
  );

  /* NOT IMPLEMENTED. */

}

/*
 * Gpt_DisableWakeup implementation.
 */
void Gpt_DisableWakeup(
  Gpt_ChannelType	Channel
)
{

  register uint32 channel;

  VALIDATE(
    ( Gpt_Global.Init == TRUE ),
    GPT_DISABLEWAKEUP_SERVICE_ID,
    GPT_E_UNINIT
  );

  VALIDATE(
    GPT_CH_IS_VALID(Channel),
    GPT_DISABLEWAKEUP_SERVICE_ID,
    GPT_E_PARAM_CHANNEL
  );

  for (
    channel = 0;
    (
      ( channel < ConfigPtr->GptNumberOfGptChannels ) &&
      ( ConfigPtr->GptChannels[channel].GptChannelId != Channel )
    );
    channel++
  );

  VALIDATE(
    (
      ( channel < ConfigPtr->GptNumberOfGptChannels ) &&
      ( ConfigPtr->GptChannels[channel].GptEnableWakeup == TRUE )
    ),
    GPT_DISABLEWAKEUP_SERVICE_ID,
    GPT_E_PARAM_CHANNEL
  );

  /* NOT IMPLEMENTED. */

}

/*
 * Gpt_EnableWakeup implementation.
 */
void Gpt_EnableWakeup(
  Gpt_ChannelType	Channel
)
{

  register uint32 channel;

  VALIDATE(
    ( Gpt_Global.Init == TRUE ),
    GPT_ENABLEWAKEUP_SERVICE_ID,
    GPT_E_UNINIT
  );

  VALIDATE(
    GPT_CH_IS_VALID(Channel),
    GPT_ENABLEWAKEUP_SERVICE_ID,
    GPT_E_PARAM_CHANNEL
  );

  for (
    channel = 0;
    (
      ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
      ( Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId != Channel )
    );
    channel++
  );

  VALIDATE(
    (
      ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
      ( Gpt_Global.ConfigPtr->GptChannels[channel].GptEnableWakeup == TRUE )
    ),
    GPT_ENABLEWAKEUP_SERVICE_ID,
    GPT_E_PARAM_CHANNEL
  );

  /* NOT IMPLEMENTED. */

}

/*
 * Gpt_CheckWakeup implementation.
 */
void Gpt_CheckWakeup(
  EcuM_WakeupSourceType	WakeupSource
)
{

  VALIDATE_W_RV(
    ( Gpt_Global.Init == TRUE ),
    GPT_CHECKWAKEUP_SERVICE_ID,
    GPT_E_UNINIT
  );

  /* NOT IMPLEMENTED. */

}
#endif

#if ( GPT_CHANNEL_WAKEUP_FUNCTIONALITY_API == STD_ON )
/*
 * Gpt_GoToSleep implementation.
 */
Std_ReturnType Gpt_GoToSleep(
  Gpt_ChannelType	Channel
)
{

  register uint32 channel;

  VALIDATE_W_RV(
    ( Gpt_Global.Init == TRUE ),
    GPT_GOTOSLEEP_SERVICE_ID,
    GPT_E_UNINIT,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    GPT_CH_IS_VALID(Channel),
    GPT_GOTOSLEEP_SERVICE_ID,
    GPT_E_PARAM_CHANNEL,
    E_NOT_OK
  );

  for (
    channel = 0;
    (
      ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
      ( Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId != Channel )
    );
    channel++
  );

  VALIDATE_W_RV(
    (
      ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
      ( Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelWakeupSupport )
    ),
    GPT_GOTOSLEEP_SERVICE_ID,
    GPT_E_PARAM_CHANNEL,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    ( Gpt_Global.Status & GPT_CH_2_UNIT_STAT_MASK(Channel) ),
    GPT_GOTOSLEEP_SERVICE_ID,
    GPT_E_STATE_TRANSITION,
    E_NOT_OK
  );

  /* Stop Timer. */
  GPT_TMR_STOP(Channel);

  /* Disable Time-out Interrupt */
  GPT_TMR_TIMEOUT_INT_DIS(Channel);

  /* Turn-off Gpt Unit */
  Gpt_Global.Status &= ~GPT_CH_2_UNIT_STAT_MASK(Channel);

  /* Gpt Module Disabled? */
  if (
    !( Gpt_Global.Status & GPT_CH_2_MOD_STAT_MASK(Channel) )
  ) {

    /* Disable Gpt Module in Run-Mode */
    Gpt_DisableChannel(Channel);

  }

  return E_OK;

}

/*
 * Gpt_Wakeup implementation.
 */
Std_ReturnType Gpt_Wakeup(
  Gpt_ChannelType	Channel
)
{

  register uint32 channel;

  VALIDATE_W_RV(
    ( Gpt_Global.Init == TRUE ),
    GPT_WAKEUP_SERVICE_ID,
    GPT_E_UNINIT,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    GPT_CH_IS_VALID(Channel),
    GPT_WAKEUP_SERVICE_ID,
    GPT_E_PARAM_CHANNEL,
    E_NOT_OK
  );

  for (
    channel = 0;
    (
      ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
      ( Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId != Channel )
    );
    channel++
  );

  VALIDATE_W_RV(
    (
      ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
      ( Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelWakeupSupport )
    ),
    GPT_WAKEUP_SERVICE_ID,
    GPT_E_PARAM_CHANNEL,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    !( Gpt_Global.Status & GPT_CH_2_UNIT_STAT_MASK(Channel) ),
    GPT_WAKEUP_SERVICE_ID,
    GPT_E_STATE_TRANSITION,
    E_NOT_OK
  );

  /* Gpt Module Disabled? */
  if ( 
    !( Gpt_Global.Status & GPT_CH_2_MOD_STAT_MASK(Channel) )
  ) {

    /* Enables Gpt Module in Run-Mode */
    Gpt_EnableChannel(Channel);

  }

  /* Gpt Notifications Enabled? */
  if ( 
    ( Gpt_Global.Notifications & GPT_CH_2_UNIT_NOTIF_MASK(Channel) )
  ) {

    /* Enable Time-out Interrupt */
    GPT_TMR_TIMEOUT_INT_EN(Channel);

  }

  /* Turn-on Gpt Unit */
  Gpt_Global.Status |= GPT_CH_2_UNIT_STAT_MASK(Channel);

  return E_OK;

}

/*
 * Gpt_GetStatus implementation.
 */
Gpt_StatusType Gpt_GetStatus(
  Gpt_ChannelType	Channel
)
{

  register Gpt_StatusType	ret = GPT_NOT_OK;
  register uint32		channel;
  register boolean		joined;
  register boolean		wide;

  VALIDATE_W_RV(
    ( Gpt_Global.Init == TRUE ),
    GPT_GETSTATUS_SERVICE_ID,
    GPT_E_UNINIT,
    ret
  );

  VALIDATE_W_RV(
    GPT_CH_IS_VALID(Channel),
    GPT_GETSTATUS_SERVICE_ID,
    GPT_E_PARAM_CHANNEL,
    ret
  );

  for (
    channel = 0;
    (
      ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
      ( Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId != Channel )
    );
    channel++
  );

  VALIDATE_W_RV(
    (
      ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
      ( Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelWakeupSupport )
    ),
    GPT_GETSTATUS_SERVICE_ID,
    GPT_E_PARAM_CHANNEL,
    ret
  );

  /* Heavy Checks Made Once!!! */
  joined = GPT_CH_IS_JOINED(Channel);
  wide = GPT_CH_IS_WIDE(Channel);

  if ( 
    !( Gpt_Global.Status & GPT_CH_2_UNIT_STAT_MASK(Channel) )
  ) {

      ret = GPT_CH_SLEEP;

  }
  else if ( GPT_TMR_RUNNING(Channel) ) {

    ret = GPT_CH_RUNNING;

  }
  else if ( GPT_TMR_TIMEOUT(Channel) ) {

    ret = GPT_CH_EXPIRED;

  }
  else if ( GPT_GET_START_COUNTER(Channel) != GPT_HW_TMR_EMPTY_VALUE ) {
  
    ret = GPT_CH_STOPPED;
  }
  else if ( !joined || !wide ) {

    ret = GPT_OPERATIONAL;

  }
  else if ( (GPT_GET_START_COUNTER(Channel + 1) == GPT_HW_TMR_EMPTY_VALUE) ) {

    ret = GPT_OPERATIONAL;

  }
  else {

    ret = GPT_CH_STOPPED;

  }

  return ret;

}
#endif
