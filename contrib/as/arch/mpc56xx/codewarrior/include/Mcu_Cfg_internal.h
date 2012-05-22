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

/** @file   Mcu_Cfg_internal.h
 *  @brief  Static part (types definition) of AUTOSAR MCU Driver Configuration
 *     Header File.
 *
 *  Configured for (MCU): Freescale MPC5643L (Leopard)
 *
 *  @author Errico Guidieri
 *  @date   2012
 */

#ifndef MCU_CFG_INTERNAL_H
#define MCU_CFG_INTERNAL_H

#include "Cfg.h"

/* Bitmak to check & set mode enabled register */
#define MCU_MODE_ENABLED_RESET          AS_32_BIT31
#define MCU_MODE_ENABLED_TEST           AS_32_BIT30
#define MCU_MODE_ENABLED_SAFE           AS_32_BIT29
#define MCU_MODE_ENABLED_DRUN           AS_32_BIT28
#define MCU_MODE_ENABLED_RUN0           AS_32_BIT27
#define MCU_MODE_ENABLED_RUN1           AS_32_BIT26
#define MCU_MODE_ENABLED_RUN2           AS_32_BIT25
#define MCU_MODE_ENABLED_RUN3           AS_32_BIT24
#define MCU_MODE_ENABLED_HALT0          AS_32_BIT23
#define MCU_MODE_ENABLED_STOP0          AS_32_BIT21

#define MCU_MODE_ENABLED_DRESET         AS_32_BIT16

/* Bitmasks to check & set mode configurations */
#define MCU_MODE_SYSCLK_RC              0x00000000U
#define MCU_MODE_SYSCLK_FMPLL           0x00000004U
#define MCU_MODE_IRCOSC_ON              AS_32_BIT27
#define MCU_MODE_XOSC_ON                AS_32_BIT26
#define MCU_MODE_PLL0_ON                AS_32_BIT25
#define MCU_MODE_PLL1_ON                AS_32_BIT24

#define MCU_MODE_FLAON_NORM             (3U << 16U)
#define MCU_MODE_FLAON_HALT0            (2U << 16U)
#define MCU_MODE_FLAON_STOP0            (1U << 16U)

#define MCU_MODE_RESERVED_NORM          (3U << 18U)
#define MCU_MODE_RESERVED_HALT0         (2U << 18U)
#define MCU_MODE_RESERVED_STOP0         (1U << 18U)

#define MCU_MODE_MAIN_VOLTAGE_REG_ON    AS_32_BIT11
#define MCU_MODE_IO_POWER_DOWN          AS_32_BIT8

/* Macros to populate FMPLL register */
#define MCU_FMPLL_IDF(n)                ((0x00000FU & ((n) - 1U)) << 26U)
#define MCU_FMPLL_ODF(n)                ((0x000003U & ((n)/2U - 1U)) << 24U)
#define MCU_FMPLL_NDIV(n)               ((0x00007FU & (n)) << 16U)
#define MCU_FMPLL_DEFAULT               AS_32_BIT31

/* Bitmask to select Auxiliary Clock Source */
#define MCU_AUX_CLOCK_SOURCE_RC         0x00000000U
#define MCU_AUX_CLOCK_SOURCE_XOSC       AS_32_BIT7
#define MCU_AUX_CLOCK_SOURCE_SYSPLL     AS_32_BIT5

/* @brief Raw Reset Type
 *
 *  <b>MCU235:</b> The type Mcu_RawResetType specifies the reset reason in raw
 *  register format, read from a reset status register.
 *
 *  <b>MCU236:</b> The type shall be <tt>uint8</tt>, <tt>uint16</tt> or
 *  <tt>uint32</tt> based on best performance.
 */
typedef uint16_least  Mcu_RawResetType;

typedef enum {
  MCU_MODE_ID_RESET = 0x00U,
  MCU_MODE_ID_TEST  = 0x01U,
  MCU_MODE_ID_SAFE  = 0x02U,
  MCU_MODE_ID_DRUN  = 0x03U,
  MCU_MODE_ID_RUN0  = 0x04U,
  MCU_MODE_ID_RUN1  = 0x05U,
  MCU_MODE_ID_RUN2  = 0x06U,
  MCU_MODE_ID_RUN3  = 0x07U,
  MCU_MODE_ID_HALT0 = 0x08U,
  MCU_MODE_ID_STOP0 = 0x0AU,
  MCU_MODE_ID_INVALID = 0xFFU
} Mcu_HardwareModeIdType;

/** @brief  Mode Setting Configuration Paramaters
 *
 *  <b>MCU123_Conf:</b> This container contains the configuration (parameters)
 *  for the Mode setting of the MCU.
 *
 *  @see <b>MCU035</b> for more information on the MCU mode settings.
 */

typedef struct {
  const Mcu_ModeType            McuModeSettingId;
  const Mcu_HardwareModeIdType  McuHardwareModeId;
  const uint32                  McuRunConfiguration;
} Mcu_ModeSettingConfigType;

typedef enum {
  MCU_AUX_CLOCK_0,
  MCU_AUX_CLOCK_1,
  MCU_AUX_CLOCK_2,
  MCU_AUX_CLOCK_3,
  MCU_AUX_CLOCK_4
} Mcu_AuxClockIdType;

typedef struct {
  const Mcu_AuxClockIdType  McuAuxClockId;
  const uint32              McuAuxClockSource;
  const uint32              McuAuxClockDivisor0;
  const uint32              McuAuxClockDivisor1;
} Mcu_AuxClockSettingConfigType;

/** @brief  Clock Settings Configuration Parameters
 *
 *  <b>MCU124_Conf:</b> This container contains the configuration (parameters)
 *  for the Clock settings of the MCU.
 *
 *  @see <b>MCU031</b> for more information on the MCU clock settings.
 */
typedef struct {

  /** @brief  Clock Settings Identifier
   *
   *  <b>MCU183_Conf:</b> The Id of this <tt>McuClockSettingConfig</tt> to
   *          be used as argument for the API call
   *          <tt>Mcu_InitClock()</tt>.
   */
  const Mcu_ClockType McuClockSettingId;

  /** @brief  Clock Frequency
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
  const float32 McuClockReferencePointFrequency;

  /** @brief FMPLL Register value for desired clock frequency */
  const uint32 McuPllConfiguration;

  /** @brief Number of Auxiliary Clock configuration */
  const uint32  McuAuxClockNumber;

  /** @brief Auxiliary Clock Setting Configuration Parameters */
  const Mcu_AuxClockSettingConfigType * const McuAuxClockSettingConfig;

} Mcu_ClockSettingConfigType;

/** @brief Invalid ID for mcu configuration */
#define MCU_MODE_INVALID           (Mcu_ModeType)-1
/** @brief Invalid ID for clock configuration */
#define MCU_CLOCKS_INVALID         (Mcu_ClockType)-1

/** @brief  Ram Sector Setting Configuration Parameters
 *
 *  <b>MCU129_Conf:</b> This container contains the configuration (parameters)
 *  for the RAM Sector setting.
 *
 *  @see <b>MCU030</b> for more information on RAM sec-tor settings.
 */
typedef struct {

  /** @brief  Default Value
   *
   *  <b>MCU177_Conf:</b> This parameter shall represent the Data pre-setting to
   *  be initialized.
   */
  const uint8   McuRamDefaultValue;
  
  /** @brief  Base Address
   *
   *  <b>MCU178_Conf:</b> This parameter shall represent the MCU RAM section
   *  base address.
   */
  const uint32  McuRamSectionBaseAddress;

  /** @brief  Section Size
   *
   *  <b>MCU179_Conf:</b> This parameter shall represent the MCU RAM Section
   *  size.
   */
  const uint32  McuRamSectionSize;

} Mcu_RamSectorSettingConfType;

/** @brief  MCU Configuration Parameters
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

  /** @brief  Clock Source Failure Notification
   *
   *  <b>MCU170_Conf:</b> Enables/Disables clock failure notification. In case
   *  this feature is not supported by HW the setting should be disabled.
   */
  const boolean McuClockSrcFailureNotification;

  /** @brief  MCU Modes Number
   *
   *  <b>MCU171_Conf:</b> This parameter shall represent the number of Modes
   *  available for the MCU. calculationFormula = Number of configured
   *  <tt>McuModeSettingConf</tt>.
   */
  const uint8   McuNumberOfMcuModes;

  /** @brief Mcu Default Initial Mode
   *
   *  Used in MCU Init to configure the default mode before return
   */
  const Mcu_ModeType  McuDefaultInitMode;

  /** @brief  RAM Sectors Number
   *
   *  <b>MCU172_Conf:</b> This parameter shall represent the number of RAM
   *  sectors available for the MCU. calculationFormula = Number of configured
   *  <tt>McuRamSectorSettingConf</tt>
   */
  const uint32  McuRamSectors;

  /** @brief  Reset Setting Configuration Parameters
   *
   *  <b>MCU173_Conf:</b> This parameter relates to the MCU specific reset
   *  configuration. This applies to the function <tt>Mcu_PerformReset()</tt>,
   *  which performs a microcontroller reset using the hardware feature of the
   *  microcontroller.
   */
  const uint32 McuResetSetting;

  /** @brief  Clock Setting Configuration Parameters
   *
   *  <b>MCU124_Conf:</b> This container contains the configuration (parameters)
   *  for the Clock settings of the MCU.
   *
   *  @see <b>MCU031</b> for more information on the MCU clock settings.
   */
  Mcu_ClockSettingConfigType const * const McuClockSettingConfig;

#if ( MCU_DEV_ERROR_DETECT == STD_ON )
  /** @brief  DEM Event Configuration Parameters
   *
   *  <b>MCU187_Conf:</b> Container for the references to
   *  <tt>DemEventParameter</tt> elements which shall be invoked using the API
   *  <tt>Dem_ReportErrorStatus()</tt> API in case the corresponding error
   *  occurs. The EventId is taken from the referenced DemEventParameter's
   *  DemEventId value. The standardized errors are provided in the container
   *  and can be extended by vendor specific error references. */
  Mcu_DemEventParametersTypeRefs const * const McuDemEventParametersRefs;
#endif

  /** @brief  Mode Setting Configuration Parameters
   *
   *  <b>MCU123_Conf:</b> This container contains the configuration (parameters)
   *  for the Mode setting of the MCU.
   *
   *  @see <b>MCU035</b> for more information on the MCU mode settings.
   */
  Mcu_ModeSettingConfigType const * const  McuModeSettingConf;

  /** @brief  Ram Sector Setting  Configuration Parameters
   *
   *  <b>MCU129_Conf:</b> This container contains the configuration (parameters)
   *  for the RAM Sector setting.
   *
   *  @see <b>MCU030</b> for more information on RAM sec-tor settings.
   */
  Mcu_RamSectorSettingConfType const * const McuRamSectorSettingConf;

  /** @brief  External Oscillator Frequency parameter */
  const uint32 McuExternalOscillatorFrequency;

} Mcu_ConfigType;

#endif  /* MCU_CFG_H */
