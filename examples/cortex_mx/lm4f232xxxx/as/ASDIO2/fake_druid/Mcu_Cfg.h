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
 * fake-druid AUTOSAR MCU Driver Configuration Header File.
 *
 * Configured for (MCU): TI Stellaris LM4F232H5QD
 *
 * Author: 2011, Giuseppe Serano
 */


#if !(\
 ((MCU_SW_MAJOR_VERSION == 1) && \
  (MCU_SW_MINOR_VERSION == 0) && \
  (MCU_SW_PATCH_VERSION == 0))\
)
#error Mcu: Configuration file expected BSW module version to be 1.0.0.*
#endif


#ifndef	MCU_CFG_H
#define	MCU_CFG_H

/*
 * MCU118_Conf:	This container contains the configuration (parameters) of the
 * 		MCU driver.
 */
/* McuGeneralConfiguration */

/*
 * MCU166_Conf:	Pre-processor switch for enabling the development error
 * 		detection and reporting.
 */
#define	MCU_DEV_ERROR_DETECT	STD_OFF

/*
 * MCU181_Conf:	Pre-processor switch to enable/disable the API Mcu_GetRamState.
 * 		(e.g. If the H/W does not support the functionality, this
 * 		parameter can be used to disable the Api).
 */
#define	MCU_GET_RAM_STATE_API	STD_OFF

/*
 * MCU182_Conf:	If this parameter is set to FALSE, the clock initialization has
 * 		to be disabled from the MCU driver. This concept applies when
 * 		there are some write once clock registers and a bootloader is
 * 		present. If this parameter is set to TRUE, the MCU driver is
 * 		responsible of the clock initialization.
 */
#define	MCU_INIT_CLOCK		STD_ON

/*
 * MCU180_Conf:	This parameter shall be set True, if the H/W does not have a PLL
 * 		or the PLL circuitry is enabled after the power on without S/W
 * 		intervention. In this case MCU_DistributePllClock has to be
 * 		disabled and MCU_GetPllStatus has to return
 * 		MCU_PLL_STATUS_UNDEFINED. Otherwise this parameters has to be
 * 		set False.
 */
#define	MCU_NO_PLL		STD_OFF

/*
 * MCU167_Conf:	Pre-processor switch to enable / disable the use of the function
 * 		Mcu_PerformReset().
 */
#define	MCU_PERFORM_RESET_API	STD_ON

/*
 * MCU168_Conf:	Pre-processor switch to enable / disable the API to read out the
 * 		modules version information.
 */
#define	MCU_VERSION_INFO_API	STD_ON

/*
 * MCU124_Conf:	This container contains the configuration (parameters) for the
 * 		Clock settings of the MCU.
 *
 * Please see MCU031 for more information on the MCU clock settings.
 */
#define	MCU_CLOCK_MODE_NUMBER		0x20

/*
 * MCU183_Conf:	The Id of this McuClockSettingConfig to be used as argument for
 * 		the API call "Mcu_InitClock".
 */
#define	MCU_CLOCK_MODE_NORMAL		0x00
#define	MCU_CLOCK_MODE_PRIOSC_NO_PLL	0x00
#define	MCU_CLOCK_MODE_PRIOSC_2_NO_PLL	0x01
#define	MCU_CLOCK_MODE_PRIOSC_3_NO_PLL	0x02
#define	MCU_CLOCK_MODE_PRIOSC_4_NO_PLL	0x03
#define	MCU_CLOCK_MODE_PRIOSC_5_NO_PLL	0x04
#define	MCU_CLOCK_MODE_PRIOSC_6_NO_PLL	0x05
#define	MCU_CLOCK_MODE_PRIOSC_7_NO_PLL	0x06
#define	MCU_CLOCK_MODE_PRIOSC_8_NO_PLL	0x07
#define	MCU_CLOCK_MODE_PRIOSC_9_NO_PLL	0x08
#define	MCU_CLOCK_MODE_PRIOSC_10_NO_PLL	0x09
#define	MCU_CLOCK_MODE_PRIOSC_11_NO_PLL	0x0A
#define	MCU_CLOCK_MODE_PRIOSC_12_NO_PLL	0x0B
#define	MCU_CLOCK_MODE_PRIOSC_13_NO_PLL	0x0C
#define	MCU_CLOCK_MODE_PRIOSC_14_NO_PLL	0x0D
#define	MCU_CLOCK_MODE_PRIOSC_15_NO_PLL	0x0E
#define	MCU_CLOCK_MODE_PRIOSC_16_NO_PLL	0x0F
#define	MCU_CLOCK_MODE_PRIOSC_PLL	0x10
#define	MCU_CLOCK_MODE_PRIOSC_2_PLL	0x11
#define	MCU_CLOCK_MODE_PRIOSC_3_PLL	0x12
#define	MCU_CLOCK_MODE_PRIOSC_4_PLL	0x13
#define	MCU_CLOCK_MODE_PRIOSC_5_PLL	0x14
#define	MCU_CLOCK_MODE_PRIOSC_6_PLL	0x15
#define	MCU_CLOCK_MODE_PRIOSC_7_PLL	0x16
#define	MCU_CLOCK_MODE_PRIOSC_8_PLL	0x17
#define	MCU_CLOCK_MODE_PRIOSC_9_PLL	0x18
#define	MCU_CLOCK_MODE_PRIOSC_10_PLL	0x19
#define	MCU_CLOCK_MODE_PRIOSC_11_PLL	0x1A
#define	MCU_CLOCK_MODE_PRIOSC_12_PLL	0x1B
#define	MCU_CLOCK_MODE_PRIOSC_13_PLL	0x1C
#define	MCU_CLOCK_MODE_PRIOSC_14_PLL	0x1D
#define	MCU_CLOCK_MODE_PRIOSC_15_PLL	0x1E
#define	MCU_CLOCK_MODE_PRIOSC_16_PLL	0x1F

typedef struct {

  /*
   * MCU183_Conf:	The Id of this McuClockSettingConfig to be used as
   * 			argument for the API call "Mcu_InitClock".
   */
  /*Mcu_ClockType	McuClockSettingId;*/

  /*
   * MCU174_Conf:	This container defines a reference point in the Mcu
   * 			Clock tree. It defines the frequency which then can be
   * 			used by other modules as an input value. Lower
   * 			multiplictiy is 1, as even in the simpliest case (only
   * 			one frequency is used), there is one frequency to be
   * 			defined.
   *
   * MCU175_Conf:	This is the frequency for the specific instance of the
   * 			McuClockReferencePoint container. It shall be given in
   * 			Hz.
   */
  float	McuClockReferencePointFrequency;

  /*
   * Run-Mode Clock Configuration
   *
   * Bit/Field	Description
   * 31:28	Undefined
   * 27		Auto Clock Gating
   * 26:23	System Clock Divisor
   * 22		Enable System Clock Divisor
   * 21:14	Undefined
   * 13		PLL Power Down
   * 12		Undeifned.
   * 11		PLL Bypass
   * 10:6	Crystal Value
   * 5:4	Oscillator Source
   * 3:2	Undefined
   * 1		Precision Internal Oscillator Disable
   * 0		Main Oscillator Disable
   */
  uint32 McuRunModeClockConfiguration;

  /*
   * Run-Mode Clock Configuration 2
   *
   * Bit/Field	Description
   * 31		Overrides Run-Mode Clock Configuration
   * 20		Divide PLL as 400 MHz vs. 200 MHz
   * 29		Undefined
   * 28:23	System Clock Divisor
   * 22		Additional LSB for System Clock Divisor
   * 21:14	Undefined
   * 13		PLL Power Down
   * 12		Undeifned
   * 11		PLL Bypass
   * 10:7	Undefined
   * 6:4	Oscillator Source
   * 3:0	Undeifned
   */
  uint32 McuRunModeClockConfiguration2;

} Mcu_ClockSettingConfigType;

/*
 * MCU123_Conf:	This container contains the configuration (parameters) for the
 * 		Mode setting of the MCU.
 *
 * Please see MCU035 for more information on the MCU mode settings.
 */
#define	MCU_MODE_NUMBER	0x01

/*
 * MCU176_Conf:	The parameter represents the MCU Mode settings.
 */
#define	MCU_MODE_NORMAL	0x00

typedef struct {

  /*
   * MCU176_Conf:	The parameter represents the MCU Mode settings.
   */
  uint8_least	mode;

} Mcu_ModeSettingConfigType;

/*
 * MCU129_Conf:	This container contains the configuration (parameters) for the
 * 		RAM Sector setting.
 *
 * Please see MCU030 for more information on RAM sec-tor settings.
 */
typedef struct {

  /*
   * MCU177_Conf:	This parameter shall represent the Data pre-setting to
   * 			be initialized.
   */
  uint8		McuRamDefaultValue;
  
  /*
   * MCU178_Conf:	This parameter shall represent the MCU RAM section base
   * 			address.
   */
  uint32	McuRamSectionBaseAddress;

  /*
   * MCU179_Conf:	This parameter shall represent the MCU RAM Section size
   */
  uint32	McuRamSectionSize;

} Mcu_RamSectorSettingConfType;

/*
 * MCU131:	The structure Mcu_ConfigType is an external data structure (i.e.
 * 		implementation specific) and shall contain the initialization
 * 		data for the MCU module.
 * 		It shall contain:
 * 		- MCU dependent properties
 * 		- Reset Configuration
 * 		- Definition of MCU modes
 * 		- Definition of Clock settings
 * 		- Definition of RAM sections
 *
 * MCU054:	The structure Mcu_ConfigType shall provide a configurable
 * 		(enable/disable) clock failure notification if the MCU provides
 * 		an interrupt for such detection.
 * 		If the clock failure is detected with other HW mechanisms e.g.,
 * 		the generation of a trap, this notification shall be disabled
 * 		and the failure reporting shall be done outside the MCU driver.
 *
 * MCU035:	The definitions for each MCU mode within the structure
 * 		Mcu_ConfigType shall contain: (depending on MCU)
 * 		- MCU specific properties
 * 		- Change of CPU clock
 * 		- Change of Peripheral clock
 * 		- Change of PLL settings
 * 		- Change of MCU power supply
 *
 * MCU031:	The definitions for each Clock setting within the structure
 * 		Mcu_ConfigType shall contain:
 * 		- MCU specific properties as, e.g., clock safety features and
 * 		  special clock distribution settings
 * 		- PLL settings /start lock options
 * 		- Internal oscillator setting
 *
 * MCU030:	The definitions for each RAM section within the structure
 * 		Mcu_ConfigType shall contain:
 * 		- RAM section base address
 * 		- Section size
 * 		- Data pre-setting to be initialized
 * 		Usage of linker symbols instead of scalar values is allowed.
 */
typedef struct {

  /*
   * MCU170_Conf:	Enables/Disables clock failure notification. In case
   * 			this feature is not supported by HW the setting should
   * 			be disabled.
   */
  boolean	McuClockSrcFailureNotification;

  /*
   * MCU171_Conf:	This parameter shall represent the number of Modes
   * 			available for the MCU. calculationFormula = Number of
   * 			configured McuModeSettingConf
   */
  uint8		McuNumberOfMcuModes;

    /*
   * MCU172_Conf:	This parameter shall represent the number of RAM sectors
   * 			available for the MCU. calculationFormula = Number of
   * 			configured McuRamSectorSettingConf
   */
  uint32	McuRamSectors;

  /*
   * MCU173_Conf:	This parameter relates to the MCU specific reset
   * 			configuration. This applies to the function
   * 			Mcu_PerformReset, which performs a microcontroller reset
   * 			using the hardware feature of the microcontroller.
   */
  uint8		* McuResetSettingPtr;

  /*
   * MCU124_Conf:	This container contains the configuration (parameters)
   * 			for the Clock settings of the MCU.
   *
   * Please see MCU031 for more information on the MCU clock settings.
   */
  Mcu_ClockSettingConfigType * McuClockSettingConfig;

  /*
   * MCU187_Conf:	Container for the references to DemEventParameter
   * 			elements which shall be invoked using the API
   * 			Dem_ReportErrorStatus API in case the corresponding
   * 			error occurs. The EventId is taken from the referenced
   * 			DemEventParameter's DemEventId value. The standardized
   * 			errors are provided in the container and can be extended
   * 			by vendor specific error references. */
  /* Mcu_DemEventPataemtersTypeRefs * McuDemEventParametersRefs; */

  /*
   * MCU123_Conf:	This container contains the configuration (parameters)
   * 			for the Mode setting of the MCU.
   *
   * Please see MCU035 for more information on the MCU mode settings.
   */
  Mcu_ModeSettingConfigType  * McuModeSettingConf;

  /*
   * MCU129_Conf:	This container contains the configuration (parameters)
   * 			for the RAM Sector setting.
   *
   * Please see MCU030 for more information on RAM sec-tor settings.
   */
  Mcu_RamSectorSettingConfType * McuRamSectorSettingConf;

} Mcu_ConfigType;

#endif	/* MCU_CFG_H */
