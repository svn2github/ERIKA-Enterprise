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
 * fake-druid AUTOSAR MCU Driver Configuration Source File.
 *
 * Configured for (MCU): TI Stellaris LM4F232H5QD
 *
 * Author: 2011, Giuseppe Serano
 */

#include "Mcu.h"

/* TODO: AUTOSAR MCU Driver Version Check */

/*
 * MCU124_Conf:	This container contains the configuration (parameters) for the
 * 		Clock settings of the MCU.
 *
 * Please see MCU031 for more information on the MCU clock settings.
 */
Mcu_ClockSettingConfigType Mcu_ClockSettingConfigData[] =
{
  /* MCU_CLOCK_MODE_NORMAL, MCU_CLOCK_MODE_PRIOSC_NO_PLL */
  {
    1.6E7,		/* McuClockReferencePointFrequency	*/
    0x07802D51,		/* Run-Mode Clock Configuration		*/
    0x07C02810,		/* Run-Mode Clock Configuration 2	*/
  },
  /* MCU_CLOCK_MODE_PRIOSC_2_NO_PLL */
  {
    8E6,		/* McuClockReferencePointFrequency	*/
    0x00C02D51,		/* Run-Mode Clock Configuration		*/
    0x07C02810,		/* Run-Mode Clock Configuration 2	*/
  },
  /* MCU_CLOCK_MODE_PRIOSC_3_NO_PLL */
  {
    5.33E6,		/* McuClockReferencePointFrequency	*/
    0x01402D51,		/* Run-Mode Clock Configuration		*/
    0x07C02810,		/* Run-Mode Clock Configuration 2	*/
  },
  /* MCU_CLOCK_MODE_PRIOSC_4_NO_PLL */
  {
    4E6,		/* McuClockReferencePointFrequency	*/
    0x01C02D51,		/* Run-Mode Clock Configuration		*/
    0x07C02810,		/* Run-Mode Clock Configuration 2	*/
  },
  /* MCU_CLOCK_MODE_PRIOSC_5_NO_PLL */
  {
    3.2E6,		/* McuClockReferencePointFrequency	*/
    0x02402D51,		/* Run-Mode Clock Configuration		*/
    0x07C02810,		/* Run-Mode Clock Configuration 2	*/
  },
  /* MCU_CLOCK_MODE_PRIOSC_6_NO_PLL */
  {
    2.67E6,		/* McuClockReferencePointFrequency	*/
    0x02C02D51,		/* Run-Mode Clock Configuration		*/
    0x07C02810,		/* Run-Mode Clock Configuration 2	*/
  },
  /* MCU_CLOCK_MODE_PRIOSC_7_NO_PLL */
  {
    2.28E6,		/* McuClockReferencePointFrequency	*/
    0x03402D51,		/* Run-Mode Clock Configuration		*/
    0x07C02810,		/* Run-Mode Clock Configuration 2	*/
  },
  /* MCU_CLOCK_MODE_PRIOSC_8_NO_PLL */
  {
    2E6,		/* McuClockReferencePointFrequency	*/
    0x03C02D51,		/* Run-Mode Clock Configuration		*/
    0x07C02810,		/* Run-Mode Clock Configuration 2	*/
  },
  /* MCU_CLOCK_MODE_PRIOSC_9_NO_PLL */
  {
    1.78E6,		/* McuClockReferencePointFrequency	*/
    0x04402D51,		/* Run-Mode Clock Configuration		*/
    0x07C02810,		/* Run-Mode Clock Configuration 2	*/
  },
  /* MCU_CLOCK_MODE_PRIOSC_10_NO_PLL */
  {
    1.6E6,		/* McuClockReferencePointFrequency	*/
    0x04C02D51,		/* Run-Mode Clock Configuration		*/
    0x07C02810,		/* Run-Mode Clock Configuration 2	*/
  },
  /* MCU_CLOCK_MODE_PRIOSC_11_NO_PLL */
  {
    1.45E6,		/* McuClockReferencePointFrequency	*/
    0x05402D51,		/* Run-Mode Clock Configuration		*/
    0x07C02810,		/* Run-Mode Clock Configuration 2	*/
  },
  /* MCU_CLOCK_MODE_PRIOSC_12_NO_PLL */
  {
    1.33E6,		/* McuClockReferencePointFrequency	*/
    0x05C02D51,		/* Run-Mode Clock Configuration		*/
    0x07C02810,		/* Run-Mode Clock Configuration 2	*/
  },
  /* MCU_CLOCK_MODE_PRIOSC_13_NO_PLL */
  {
    1.23E7,		/* McuClockReferencePointFrequency	*/
    0x06402D51,		/* Run-Mode Clock Configuration		*/
    0x07C02810,		/* Run-Mode Clock Configuration 2	*/
  },
  /* MCU_CLOCK_MODE_PRIOSC_14_NO_PLL */
  {
    1.14E6,		/* McuClockReferencePointFrequency	*/
    0x06C02D51,		/* Run-Mode Clock Configuration		*/
    0x07C02810,		/* Run-Mode Clock Configuration 2	*/
  },
  /* MCU_CLOCK_MODE_PRIOSC_15_NO_PLL */
  {
    1.06E6,		/* McuClockReferencePointFrequency	*/
    0x07402D51,		/* Run-Mode Clock Configuration		*/
    0x07C02810,		/* Run-Mode Clock Configuration 2	*/
  },
  /* MCU_CLOCK_MODE_PRIOSC_16_NO_PLL */
  {
    1E6,		/* McuClockReferencePointFrequency	*/
    0x07C02D51,		/* Run-Mode Clock Configuration		*/
    0x07C02810,		/* Run-Mode Clock Configuration 2	*/
  },
  /* MCU_CLOCK_MODE_PRIOSC_PLL - NOT VALID */
  {
    2E8,		/* McuClockReferencePointFrequency	*/
    0x07C00551,		/* Run-Mode Clock Configuration		*/
    0x80400010,		/* Run-Mode Clock Configuration 2	*/
  },
  /* MCU_CLOCK_MODE_PRIOSC_2_PLL - NOT VALID */
  {
    2E8,		/* McuClockReferencePointFrequency	*/
    0x07C00551,		/* Run-Mode Clock Configuration		*/
    0x80C00010,		/* Run-Mode Clock Configuration 2	*/
  },
  /* MCU_CLOCK_MODE_PRIOSC_3_PLL */
  {
    6.67E7,		/* McuClockReferencePointFrequency	*/
    0x07C00551,		/* Run-Mode Clock Configuration		*/
    0x81400010,		/* Run-Mode Clock Configuration 2	*/
  },
  /* MCU_CLOCK_MODE_PRIOSC_4_PLL */
  {
    5E7,		/* McuClockReferencePointFrequency	*/
    0x07C00551,		/* Run-Mode Clock Configuration		*/
    0x81C00010,		/* Run-Mode Clock Configuration 2	*/
  },
  /* MCU_CLOCK_MODE_PRIOSC_5_PLL */
  {
    4E7,		/* McuClockReferencePointFrequency	*/
    0x07C00551,		/* Run-Mode Clock Configuration		*/
    0x82400010,		/* Run-Mode Clock Configuration 2	*/
  },
  /* MCU_CLOCK_MODE_PRIOSC_6_PLL */
  {
    3.33E7,		/* McuClockReferencePointFrequency	*/
    0x07C00551,		/* Run-Mode Clock Configuration		*/
    0x82C00010,		/* Run-Mode Clock Configuration 2	*/
  },
  /* MCU_CLOCK_MODE_PRIOSC_7_PLL */
  {
    2.86E7,		/* McuClockReferencePointFrequency	*/
    0x07C00551,		/* Run-Mode Clock Configuration		*/
    0x83400010,		/* Run-Mode Clock Configuration 2	*/
  },
  /* MCU_CLOCK_MODE_PRIOSC_8_PLL */
  {
    2.5E7,		/* McuClockReferencePointFrequency	*/
    0x07C00551,		/* Run-Mode Clock Configuration		*/
    0x83C00010,		/* Run-Mode Clock Configuration 2	*/
  },
  /* MCU_CLOCK_MODE_PRIOSC_9_PLL */
  {
    2.22E7,		/* McuClockReferencePointFrequency	*/
    0x07C00551,		/* Run-Mode Clock Configuration		*/
    0x84400010,		/* Run-Mode Clock Configuration 2	*/
  },
  /* MCU_CLOCK_MODE_PRIOSC_10_PLL */
  {
    2E7,		/* McuClockReferencePointFrequency	*/
    0x07C00551,		/* Run-Mode Clock Configuration		*/
    0x84C00010,		/* Run-Mode Clock Configuration 2	*/
  },
  /* MCU_CLOCK_MODE_PRIOSC_11_PLL */
  {
    1.81E7,		/* McuClockReferencePointFrequency	*/
    0x07C00551,		/* Run-Mode Clock Configuration		*/
    0x85400010,		/* Run-Mode Clock Configuration 2	*/
  },
  /* MCU_CLOCK_MODE_PRIOSC_12_PLL */
  {
    1.67E7,		/* McuClockReferencePointFrequency	*/
    0x07C00551,		/* Run-Mode Clock Configuration		*/
    0x85C00010,		/* Run-Mode Clock Configuration 2	*/
  },
  /* MCU_CLOCK_MODE_PRIOSC_13_PLL */
  {
    1.54E7,		/* McuClockReferencePointFrequency	*/
    0x07C00551,		/* Run-Mode Clock Configuration		*/
    0x86400010,		/* Run-Mode Clock Configuration 2	*/
  },
  /* MCU_CLOCK_MODE_PRIOSC_14_PLL */
  {
    1.43E7,		/* McuClockReferencePointFrequency	*/
    0x07C00551,		/* Run-Mode Clock Configuration		*/
    0x86C00010,		/* Run-Mode Clock Configuration 2	*/
  },
  /* MCU_CLOCK_MODE_PRIOSC_15_PLL */
  {
    1.33E7,		/* McuClockReferencePointFrequency	*/
    0x07C00551,		/* Run-Mode Clock Configuration		*/
    0x87400010,		/* Run-Mode Clock Configuration 2	*/
  },
  /* MCU_CLOCK_MODE_PRIOSC_16_PLL */
  {
    1.25E7,		/* McuClockReferencePointFrequency	*/
    0x07C00551,		/* Run-Mode Clock Configuration		*/
    0x87C00010,		/* Run-Mode Clock Configuration 2	*/
  },
};

/*
 * MCU123_Conf:	This container contains the configuration (parameters) for the
 * 		Mode setting of the MCU.
 *
 * Please see MCU035 for more information on the MCU mode settings.
 */

Mcu_ModeSettingConfigType Mcu_ModeSettingConfigData[] = 
{
  {
    MCU_MODE_NORMAL,
  }
};

/*
 * MCU129_Conf:	This container contains the configuration (parameters) for the
 * 		RAM Sector setting.
 *
 * Please see MCU030 for more information on RAM sec-tor settings.
 */
Mcu_RamSectorSettingConfType Mcu_RamSectorSettingConfigData[] =
{
  {
    0,		/* McuRamDefaultValue		*/
    0x20000000,	/* McuRamSectionBaseAddress	*/
    0x00008000,	/* McuRamSectionSize		*/
  }
};

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
Mcu_ConfigType Mcu_Config =
{
  FALSE,				/* McuClockSrcFailureNotification */
  1,					/* McuNumberOfMcuModes		  */
  1,					/* McuRamSectors		  */
  NULL_PTR,				/* McuResetSetting		  */
  &Mcu_ClockSettingConfigData[0],	/* McuClockSettingConfig	  */
/*NULL_PTR,*/				/* McuDemEventParametersRefs	  */
  &Mcu_ModeSettingConfigData[0],	/* McuModeSettingConf		  */
  &Mcu_RamSectorSettingConfigData[0],	/* McuRamSectorSettingConf	  */
};
