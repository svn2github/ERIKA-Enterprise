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

#define MCU_AR_RELEASE_MAJOR_VERSION  4
#define MCU_AR_RELEASE_MINOR_VERSION  0

#include "Mcu.h"

/*
 * MCU110:  For included (external) header files:
 *    - <MODULENAME>_AR_ RELEASE_MAJOR_VERSION
 *    - <MODULENAME>_AR_ RELEASE_MINOR_VERSION
 *    shall be verified.
 */
#if !defined( MCU_AR_MAJOR_VERSION ) || \
    ( MCU_AR_MAJOR_VERSION != MCU_AR_RELEASE_MAJOR_VERSION )
#error  Mcu: version mismatch.
#endif

/*
 * MCU124_Conf: This container contains the configuration (parameters) for the
 *    Clock settings of the MCU.
 *
 * Please see MCU031 for more information on the MCU clock settings.
 */
Mcu_ClockSettingConfigType const Mcu_ClockSettingConfigData[] =
{
  { 
    MCU_CLOCK_EXT_REF_64MHZ,      /* Clock Settings Identifier          */
    6.4E7,                        /* McuClockReferencePointFrequency    */
    0x12400000U,                  /* 40 MHz xtal: Set PLL0 to 64 MHz    */
                                  /* IDF = 4: divide Fxtal by 5 (IDF+1) */
                                  /* NDIV = 64: multiply by 64 (NDIV)   */
                                  /* ODF = 2:  divide Fpll by 8 (2**(ODF+1)) */
    TRUE                          /* External Oscillator is PLL input */

  },
  /* MCU_CLOCK_MODE_NORMAL */
  {
    MCU_CLOCK_EXT_REF_80MHZ,      /* Clock Settings Identifier          */
    8E7,                          /* McuClockReferencePointFrequency    */
    0x0D400000U,                  /* 40 MHz xtal: Set PLL0 to 120 MHz   */
                                  /* IDF = 7: divide Fxtal by 8 (IDF+1) */
                                  /* NDIV = 64: multiply by 64 (NDIV)   */
                                  /* ODF = 1:  divide Fpll by 4 (2**(ODF+1)) */
    TRUE                          /* External Oscillator is PLL input */

  },
  /* MCU_CLOCK_MODE_NORMAL */
  {
    MCU_CLOCK_EXT_REF_120MHZ,     /* Clock Settings Identifier          */
    1.2E8,                        /* McuClockReferencePointFrequency    */
    0x0D300000U,                  /* 40 MHz xtal: Set PLL0 to 120 MHz */ 
                                  /* IDF = 3: divide Fxtal by 4 (IDF+1) */
                                  /* NDIV = 48: multiply by 48 (NDIV) */
                                  /* ODF = 1:  divide Fpll by 4 (2**(ODF+1)) */
    TRUE                          /* External Oscillator is PLL input */
  }
};


/*
 * MCU123_Conf: This container contains the configuration (parameters) for the
 *    Mode setting of the MCU.
 *
 * Please see MCU035 for more information on the MCU mode settings.
 */

Mcu_ModeSettingConfigType const Mcu_ModeSettingConfigData[] =
{
  {
    /* Application Execution Mode */
    MCU_MODE_ID_RUN0, /* RUN0 hardware ID */
    0x001F0074U,      /* RUN0 cfg: 16MHzIRCON,OSC0ON,PLL0ON,syclk=PLL0 */
  },
  {
    /* Application Supervisor Mode */
    MCU_MODE_ID_DRUN, /* DRUN hardware ID */
    0x001F0074U       /* DRUN cfg: 16MHzIRCON,OSC0ON,PLL0ON,syclk=PLL0 */
  },
  {
    /* Safe mode for recovering from errors */
    MCU_MODE_ID_SAFE, /* SAFE hardware ID */
    0x001F0010U       /* SAFE cfg: 16MHzIRCON,OSC0OFF,PLL0OFF,syclk=16MHzIRC */
  }
};

/*
 * MCU129_Conf: This container contains the configuration (parameters) for the
 *    RAM Sector setting.
 *
 * Please see MCU030 for more information on RAM sector settings.
 */
Mcu_RamSectorSettingConfType const Mcu_RamSectorSettingConfigData[] =
{
  {
    0U,           /* McuRamDefaultValue       */
    0x40000000U,  /* McuRamSectionBaseAddress */
    /* 64K (0x00008000U) of RAM in Lock Step Mode */
    0x00008000U,  /* McuRamSectionSize        */
  }
};

/*
 * MCU131:  The structure Mcu_ConfigType is an external data structure (i.e.
 *    implementation specific) and shall contain the initialization
 *    data for the MCU module.
 *    It shall contain:
 *    - MCU dependent properties
 *    - Reset Configuration
 *    - Definition of MCU modes
 *    - Definition of Clock settings
 *    - Definition of RAM sections
 *
 * MCU054:  The structure Mcu_ConfigType shall provide a configurable
 *    (enable/disable) clock failure notification if the MCU provides
 *    an interrupt for such detection.
 *    If the clock failure is detected with other HW mechanisms e.g.,
 *    the generation of a trap, this notification shall be disabled
 *    and the failure reporting shall be done outside the MCU driver.
 *
 * MCU035:  The definitions for each MCU mode within the structure
 *    Mcu_ConfigType shall contain: (depending on MCU)
 *    - MCU specific properties
 *    - Change of CPU clock
 *    - Change of Peripheral clock
 *    - Change of PLL settings
 *    - Change of MCU power supply
 *
 * MCU031:  The definitions for each Clock setting within the structure
 *    Mcu_ConfigType shall contain:
 *    - MCU specific properties as, e.g., clock safety features and
 *      special clock distribution settings
 *    - PLL settings /start lock options
 *    - Internal oscillator setting
 *
 * MCU030:  The definitions for each RAM section within the structure
 *    Mcu_ConfigType shall contain:
 *    - RAM section base address
 *    - Section size
 *    - Data pre-setting to be initialized
 *    Usage of linker symbols instead of scalar values is allowed.
 */
Mcu_ConfigType Mcu_Config =
{
  /* McuClockSrcFailureNotification */
  FALSE,
  /* McuNumberOfMcuModes            */
  MCU_MODES_NUMBER,
  /* McuRamSectors                  */
  1U,
  /* McuResetSetting                */
  MCU_RESET_CONF,
  /* (Mcu_ClockSettingConfigType const * const) */
  &Mcu_ClockSettingConfigData[0],
  /* McuDemEventParametersRefs      */
  /*NULL_PTR,*/
  /* (Mcu_ModeSettingConfigType const * const) */
  &Mcu_ModeSettingConfigData[0],
  /* (Mcu_RamSectorSettingConfType const * const) */
  &Mcu_RamSectorSettingConfigData[0],
  /* McuExternalOscillatorFrequency */
  40000000U
};
