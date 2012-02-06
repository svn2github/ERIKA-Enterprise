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

/** @file	Mcu_Cfg.h
 *  @brief	fake-druid AUTOSAR MCU Driver Configuration Header File.
 *
 * Configured for (MCU): TI Stellaris LM4F232H5QD
 *
 *  @author	Giuseppe Serano
 *  @date	2011
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

/** @brief	Development Error Detection
 *
 *  <b>MCU166_Conf:</b> Pre-processor switch for enabling the development error
 *  detection and reporting.
 */
#define	MCU_DEV_ERROR_DETECT	STD_OFF

/** @brief	Ram State Retrieval API
 *
 *  <b>MCU181_Conf:</b> Pre-processor switch to enable/disable the API
 *  <tt>Mcu_GetRamState()</tt>. (e.g. If the H/W does not support the
 *  functionality, this parameter can be used to disable the Api).
 */
#define	MCU_GET_RAM_STATE_API	STD_OFF

/** @brief	Clock Initialization API
 *
 *  <b>MCU182_Conf:</b> If this parameter is set to FALSE, the clock
 *  initialization has to be disabled from the MCU driver. This concept applies
 *  when there are some write once clock registers and a bootloader is present.
 *  If this parameter is set to TRUE, the MCU driver is responsible of the clock
 +  initialization.
 */
#define	MCU_INIT_CLOCK		STD_ON

/** @brief	Hardware PLL
 *
 *  <b>MCU180_Conf:</b>	This parameter shall be set True, if the H/W does not
 *  have a PLL or the PLL circuitry is enabled after the power on without S/W
 *  intervention. In this case <tt>MCU_DistributePllClock()</tt> has to be
 *  disabled and <tt>MCU_GetPllStatus()</tt> has to return
 *  <tt>MCU_PLL_STATUS_UNDEFINED</tt>. Otherwise this parameters has to be set
 *  False.
 */
#define	MCU_NO_PLL		STD_OFF

/** @brief	Microcontroller Reset API
 *
 *  <b>MCU167_Conf:</b> Pre-processor switch to enable / disable the use of the
 *  function <tt>Mcu_PerformReset()</tt>.
 */
#define	MCU_PERFORM_RESET_API	STD_ON

/** @brief	Version Informations Retrieval API
 *
 *  <b>MCU168_Conf:</b> Pre-processor switch to enable / disable the API to read
 *  out the modules version information.
 */
#define	MCU_VERSION_INFO_API	STD_ON

/*
 * MCU183_Conf:	The Id of this McuClockSettingConfig to be used as argument for
 * 		the API call "Mcu_InitClock".
 */

/** @brief	16MHz
 *
 *  Precision Internal Oscillator - No PLL - No System Clock Divisor.
 */
#define	MCU_CLOCK_MODE_PRIOSC_NO_PLL	0x00
/** @brief	Clock Mode Normal
 *
 *  <b>16MHz:</b> Precision Internal Oscillator - No PLL - No System Clock
 *  Divisor.
 */
#define	MCU_CLOCK_MODE_NORMAL		MCU_CLOCK_MODE_PRIOSC_NO_PLL
/** @brief	8MHz
 *
 *  Precision Internal Oscillator - No PLL - System Clock Divisor (2).
 */
#define	MCU_CLOCK_MODE_PRIOSC_2_NO_PLL	0x01
/** @brief	5.33MHz
 *
 *  Precision Internal Oscillator - No PLL - System Clock Divisor (3).
 */
#define	MCU_CLOCK_MODE_PRIOSC_3_NO_PLL	0x02
/** @brief	4MHz
 *
 *  Precision Internal Oscillator - No PLL - System Clock Divisor (4).
 */
#define	MCU_CLOCK_MODE_PRIOSC_4_NO_PLL	0x03
/** @brief	3.2MHz
 *
 *  Precision Internal Oscillator - No PLL - System Clock Divisor (5).
 */
#define	MCU_CLOCK_MODE_PRIOSC_5_NO_PLL	0x04
/** @brief	2.67MHz
 *
 *  Precision Internal Oscillator - No PLL - System Clock Divisor (6).
 */
#define	MCU_CLOCK_MODE_PRIOSC_6_NO_PLL	0x05
/** @brief	2.28MHz
 *
 *  Precision Internal Oscillator - No PLL - System Clock Divisor (7).
 */
#define	MCU_CLOCK_MODE_PRIOSC_7_NO_PLL	0x06
/** @brief	2MHz
 *
 *  Precision Internal Oscillator - No PLL - System Clock Divisor (8).
 */
#define	MCU_CLOCK_MODE_PRIOSC_8_NO_PLL	0x07
/** @brief	1.78MHz
 *
 *  Precision Internal Oscillator - No PLL - System Clock Divisor (9).
 */
#define	MCU_CLOCK_MODE_PRIOSC_9_NO_PLL	0x08
/** @brief	1.6MHz
 *
 *  Precision Internal Oscillator - No PLL - System Clock Divisor (10).
 */
#define	MCU_CLOCK_MODE_PRIOSC_10_NO_PLL	0x09
/** @brief	1.45MHz
 *
 *  Precision Internal Oscillator - No PLL - System Clock Divisor (11).
 */
#define	MCU_CLOCK_MODE_PRIOSC_11_NO_PLL	0x0A
/** @brief	1.33MHz
 *
 *  Precision Internal Oscillator - No PLL - System Clock Divisor (12).
 */
#define	MCU_CLOCK_MODE_PRIOSC_12_NO_PLL	0x0B
/** @brief	1.23MHz
 *
 *  Precision Internal Oscillator - No PLL - System Clock Divisor (13).
 */
#define	MCU_CLOCK_MODE_PRIOSC_13_NO_PLL	0x0C
/** @brief	1.14MHz
 *
 *  Precision Internal Oscillator - No PLL - System Clock Divisor (14).
 */
#define	MCU_CLOCK_MODE_PRIOSC_14_NO_PLL	0x0D
/** @brief	1.06MHz
 *
 *  Precision Internal Oscillator - No PLL - System Clock Divisor (15).
 */
#define	MCU_CLOCK_MODE_PRIOSC_15_NO_PLL	0x0E
/** @brief	1MHz
 *
 *  Precision Internal Oscillator - No PLL - System Clock Divisor (16).
 */
#define	MCU_CLOCK_MODE_PRIOSC_16_NO_PLL	0x0F
/** @brief	200MHz
 *
 *  Precision Internal Oscillator - PLL - No System Clock Divisor.
 *
 *  @note	NOT SUPPORTED BY HARDWARE.
 */
#define	MCU_CLOCK_MODE_PRIOSC_PLL	0x10
/** @brief	100MHz
 *
 *  Precision Internal Oscillator - PLL - System Clock Divisor (2).
 *
 *  @note	NOT SUPPORTED BY HARDWARE.
 */
#define	MCU_CLOCK_MODE_PRIOSC_2_PLL	0x11
/** @brief	66.7MHz
 *
 *  Precision Internal Oscillator - PLL - System Clock Divisor (3).
 */
#define	MCU_CLOCK_MODE_PRIOSC_3_PLL	0x12
/** @brief	50MHz
 *
 *  Precision Internal Oscillator - PLL - System Clock Divisor (4).
 */
#define	MCU_CLOCK_MODE_PRIOSC_4_PLL	0x13
/** @brief	40MHz
 *
 *  Precision Internal Oscillator - PLL - System Clock Divisor (5).
 */
#define	MCU_CLOCK_MODE_PRIOSC_5_PLL	0x14
/** @brief	33.3MHz
 *
 *  Precision Internal Oscillator - PLL - System Clock Divisor (6).
 */
#define	MCU_CLOCK_MODE_PRIOSC_6_PLL	0x15
/** @brief	28.6MHz
 *
 *  Precision Internal Oscillator - PLL - System Clock Divisor (7).
 */
#define	MCU_CLOCK_MODE_PRIOSC_7_PLL	0x16
/** @brief	25MHz
 *
 *  Precision Internal Oscillator - PLL - System Clock Divisor (8).
 */
#define	MCU_CLOCK_MODE_PRIOSC_8_PLL	0x17
/** @brief	22.2MHz
 *
 *  Precision Internal Oscillator - PLL - System Clock Divisor (9).
 */
#define	MCU_CLOCK_MODE_PRIOSC_9_PLL	0x18
/** @brief	20MHz
 *
 *  Precision Internal Oscillator - PLL - System Clock Divisor (10).
 */
#define	MCU_CLOCK_MODE_PRIOSC_10_PLL	0x19
/** @brief	18.1MHz
 *
 *  Precision Internal Oscillator - PLL - System Clock Divisor (11).
 */
#define	MCU_CLOCK_MODE_PRIOSC_11_PLL	0x1A
/** @brief	16.7MHz
 *
 *  Precision Internal Oscillator - PLL - System Clock Divisor (12).
 */
#define	MCU_CLOCK_MODE_PRIOSC_12_PLL	0x1B
/** @brief	15.4MHz
 *
 *  Precision Internal Oscillator - PLL - System Clock Divisor (13).
 */
#define	MCU_CLOCK_MODE_PRIOSC_13_PLL	0x1C
/** @brief	14.3MHz
 *
 *  Precision Internal Oscillator - PLL - System Clock Divisor (14).
 */
#define	MCU_CLOCK_MODE_PRIOSC_14_PLL	0x1D
/** @brief	13.3MHz
 *
 *  Precision Internal Oscillator - PLL - System Clock Divisor (15).
 */
#define	MCU_CLOCK_MODE_PRIOSC_15_PLL	0x1E
/** @brief	12.5MHz
 *
 *  Precision Internal Oscillator - PLL - System Clock Divisor (16).
 */
#define	MCU_CLOCK_MODE_PRIOSC_16_PLL	0x1F

/**
 *  Number of supported clock mode.
 */
#define	MCU_CLOCK_MODE_NUMBER		MCU_CLOCK_MODE_PRIOSC_16_PLL + 1

/** @brief	Clock Settings Configuration Parameters
 *
 *  <b>MCU124_Conf:</b> This container contains the configuration (parameters)
 *  for the Clock settings of the MCU.
 *
 *  @see <b>MCU031</b> for more information on the MCU clock settings.
 */
typedef struct {

  /*
   * MCU183_Conf:	The Id of this McuClockSettingConfig to be used as
   * 			argument for the API call "Mcu_InitClock".
   */
  /*Mcu_ClockType	McuClockSettingId;*/

  /** @brief	Clock Frequency
   *
   *  <b>MCU174_Conf:</b> This container defines a reference point in the Mcu
   *  Clock tree. It defines the frequency which then can be used by other
   *  modules as an input value. Lower multiplictiy is 1, as even in the
   *  simpliest case (only one frequency is used), there is one frequency to be
   *  defined.
   *
   *  <b>MCU175_Conf:</b> This is the frequency for the specific instance of the
   *  <tt>McuClockReferencePoint</tt> container. It shall be given in Hz.
   */
  float	McuClockReferencePointFrequency;

  /** @brief Run-Mode Clock Configuration
   *
   *  <pre>
   *  Bit/Field	Description
   *  31:28		Undefined
   *  27		Auto Clock Gating
   *  26:23		System Clock Divisor
   *  22		Enable System Clock Divisor
   *  21:14		Undefined
   *  13		PLL Power Down
   *  12		Undeifned
   *  11		PLL Bypass
   *  10:6		Crystal Value
   *  5:4		Oscillator Source
   *  3:2		Undefined
   *  1		Precision Internal Oscillator Disable
   *  0		Main Oscillator Disable
   *  </pre>
   */
  uint32 McuRunModeClockConfiguration;

  /** @brief	Run-Mode Clock Configuration 2
   *
   *  <pre>
   *  Bit/Field	Description
   *  31		Overrides Run-Mode Clock Configuration
   *  30		Divide PLL as 400 MHz vs. 200 MHz
   *  29		Undefined
   *  28:23		System Clock Divisor
   *  22		Additional LSB for System Clock Divisor
   *  21:14		Undefined
   *  13		PLL Power Down
   *  12		Undeifned
   *  11		PLL Bypass
   *  10:7		Undefined
   *  6:4		Oscillator Source
   *  3:0		Undeifned
   *  </pre>
   */
  uint32 McuRunModeClockConfiguration2;

} Mcu_ClockSettingConfigType;

/*
 * MCU176_Conf:	The parameter represents the MCU Mode settings.
 */

/** @brief	MCU Mode Normal
 */
#define	MCU_MODE_NORMAL	0x00

/**
 *  Number of supported MCU mode.
 */
#define	MCU_MODE_NUMBER	MCU_MODE_NORMAL + 1

/** @brief	Mode Setting Configuration Paramaters
 *
 *  <b>MCU123_Conf:</b> This container contains the configuration (parameters)
 *  for the Mode setting of the MCU.
 *
 *  @see <b>MCU035</b> for more information on the MCU mode settings.
 */
typedef struct {

  /** @brief	MCU Mode
   *
   *  <b>MCU176_Conf:</b> The parameter represents the MCU Mode settings.
   */
  uint8_least	mode;

} Mcu_ModeSettingConfigType;

/** @brief	Ram Sector Setting Configuration Parameters
 *
 *  <b>MCU129_Conf:</b> This container contains the configuration (parameters)
 *  for the RAM Sector setting.
 *
 *  @see <b>MCU030</b> for more information on RAM sec-tor settings.
 */
typedef struct {

  /** @brief	Default Value
   *
   *  <b>MCU177_Conf:</b> This parameter shall represent the Data pre-setting to
   *  be initialized.
   */
  uint8		McuRamDefaultValue;
  
  /** @brief	Base Address
   *
   *  <b>MCU178_Conf:</b> This parameter shall represent the MCU RAM section
   *  base address.
   */
  uint32	McuRamSectionBaseAddress;

  /** @brief	Section Size
   *
   *  <b>MCU179_Conf:</b> This parameter shall represent the MCU RAM Section
   *  size.
   */
  uint32	McuRamSectionSize;

} Mcu_RamSectorSettingConfType;

/** @brief	MCU Configuration Parameters
 *
 *  <b>MCU131:</b> The structure <tt>Mcu_ConfigType</tt> is an external data
 *  structure (i.e. implementation specific) and shall contain the
 *  initialization data for the MCU module. It shall contain:
 *  - MCU dependent properties
 *  - Reset Configuration
 *  - Definition of MCU modes
 *  - Definition of Clock settings
 *  - Definition of RAM sections
 *
 *  <b>MCU054:</b> The structure <tt>Mcu_ConfigType</tt> shall provide a
 *  configurable (enable/disable) clock failure notification if the MCU provides
 *  an interrupt for such detection. If the clock failure is detected with other
 *  HW mechanisms e.g., the generation of a trap, this notification shall be
 *  disabled and the failure reporting shall be done outside the MCU driver.
 *
 *  <b>MCU035:</b> The definitions for each MCU mode within the structure
 *  <tt>Mcu_ConfigType</tt> shall contain: (depending on MCU)
 *  - MCU specific properties
 *  - Change of CPU clock
 *  - Change of Peripheral clock
 *  - Change of PLL settings
 *  - Change of MCU power supply
 *
 *  <b>MCU031:</b> The definitions for each Clock setting within the structure
 *  <tt>Mcu_ConfigType</tt> shall contain:
 *  - MCU specific properties as, e.g., clock safety features and special clock
 *  distribution settings
 *  - PLL settings /start lock options
 *  - Internal oscillator setting
 *
 *  <b>MCU030:</b> The definitions for each RAM section within the structure
 *  <tt>Mcu_ConfigType</tt> shall contain:
 *  - RAM section base address
 *  - Section size
 *  - Data pre-setting to be initialized
 * Usage of linker symbols instead of scalar values is allowed.
 */
typedef struct {

  /** @brief	Clock Source Failure Notification
   *
   *  <b>MCU170_Conf:</b> Enables/Disables clock failure notification. In case
   *  this feature is not supported by HW the setting should be disabled.
   */
  boolean	McuClockSrcFailureNotification;

  /** @brief	MCU Modes Number
   *
   *  <b>MCU171_Conf:</b> This parameter shall represent the number of Modes
   *  available for the MCU. calculationFormula = Number of configured
   *  <tt>McuModeSettingConf</tt>.
   */
  uint8		McuNumberOfMcuModes;

  /** @brief	RAM Sectors Number
   *
   *  <b>MCU172_Conf:</b> This parameter shall represent the number of RAM
   *  sectors available for the MCU. calculationFormula = Number of configured
   *  <tt>McuRamSectorSettingConf</tt>
   */
  uint32	McuRamSectors;

  /** @brief	Reset Setting Configuration Parameters
   *
   *  <b>MCU173_Conf:</b> This parameter relates to the MCU specific reset
   *  configuration. This applies to the function <tt>Mcu_PerformReset()</tt>,
   *  which performs a microcontroller reset using the hardware feature of the
   *  microcontroller.
   */
  uint8		* McuResetSettingPtr;

  /** @brief	Clock Setting Configuration Parameters
   *
   *  <b>MCU124_Conf:</b> This container contains the configuration (parameters)
   *  for the Clock settings of the MCU.
   *
   *  @see <b>MCU031</b> for more information on the MCU clock settings.
   */
  Mcu_ClockSettingConfigType * McuClockSettingConfig;

#if ( MCU_DEV_ERROR_DETECT == STD_ON )
  /** @brief	DEM Event Configuration Parameters
   *
   *  <b>MCU187_Conf:</b> Container for the references to
   *  <tt>DemEventParameter</tt> elements which shall be invoked using the API
   *  <tt>Dem_ReportErrorStatus()</tt> API in case the corresponding error
   *  occurs. The EventId is taken from the referenced DemEventParameter's
   *  DemEventId value. The standardized errors are provided in the container
   *  and can be extended by vendor specific error references. */
  Mcu_DemEventParametersTypeRefs * McuDemEventParametersRefs;
#endif

  /** @brief	Mode Setting Configuration Parameters
   *
   *  <b>MCU123_Conf:</b> This container contains the configuration (parameters)
   *  for the Mode setting of the MCU.
   *
   *  @see <b>MCU035</b> for more information on the MCU mode settings.
   */
  Mcu_ModeSettingConfigType  * McuModeSettingConf;

  /** @brief	Ram Sector Setting  Configuration Parameters
   *
   *  <b>MCU129_Conf:</b> This container contains the configuration (parameters)
   *  for the RAM Sector setting.
   *
   *  @see <b>MCU030</b> for more information on RAM sec-tor settings.
   */
  Mcu_RamSectorSettingConfType * McuRamSectorSettingConf;

} Mcu_ConfigType;

#endif	/* MCU_CFG_H */
