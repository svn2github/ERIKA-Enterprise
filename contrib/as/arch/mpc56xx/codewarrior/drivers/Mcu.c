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
 * Author:  2012, Errico Guidieri
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

#include <ee.h>
#include "Utility.h"

struct EE_mcu_status_type {
  boolean               init;
  const Mcu_ConfigType  *config;
  Mcu_ClockType         clock;
} EE_mcu_status = {0, NULL};

/* Processor identification */

#define SPR_PIR 286
#define SPR_PVR 287

#define PVR_CORE_E200Z4D_LEOPARD    0x81550001UL /* Leopard Core PVR */

struct EE_cpu_info_type {
  const char * const    cpu_name;
  const uint32          pvr;
};

struct EE_mcu_info_type {
  const char * const                     mcu_name;
  const struct EE_cpu_info_type * const  cpu_ptr;
  const uint16                           mcuid1;
  const uint8                            mcuid2;
};

const struct EE_cpu_info_type EE_supported_cpu[] = {
  {
    "e200z4d",
    PVR_CORE_E200Z4D_LEOPARD
  }
};

const struct EE_mcu_info_type EE_supported_mcu[] = {
  {
    "MPC5643L",
    &EE_supported_cpu[0],
    0x5643U,
    'L'
  }
};

/* Get the mcu info from a given pvr value */
static struct EE_mcu_info_type const * EE_mcu_get_supported(uint16 mcuid1,
      uint8 mcuid2) {
    EE_UREG i;
    struct EE_mcu_info_type const * mcu_info = NULL;
    for (i = 0; i < ARRAY_LENGTH(EE_supported_mcu); ++i) {
      if (EE_supported_mcu[i].mcuid1 == mcuid1) {
        if(EE_supported_mcu[i].mcuid2 == mcuid2) {
          mcu_info = &EE_supported_mcu[i];
          break;
        }
      }
    }

    return mcu_info;
}

static EE_UREG EE_mcu_check(void) {
  EE_UREG pvr;
  uint16 mcuid1;
  uint8  mcuid2;
  struct EE_mcu_info_type const * mcu_info;

  /* Mcu ID part number */
  mcuid1 = SIU.MIDR1.B.PARTNUM;
  mcuid2 = SIU.MIDR2.B.PARTNUM2;

  mcu_info = EE_mcu_get_supported(mcuid1, mcuid2);
  pvr      = EE_e200zx_get_pvr();

  if(mcu_info != NULL) {
    /* Redundant check */
    if(mcu_info->cpu_ptr->pvr == pvr) {
      return TRUE;
    }
  }
  return FALSE;
}

/* Disable watchdog. Watchdog is enabled default after reset.*/
static EE_mcu_disable_watchdog(void) {
  SWT.SR.R = 0x0000c520;     /* Write keys to clear soft lock bit */
  SWT.SR.R = 0x0000d928; 
  SWT.CR.R = 0x8000010A;     /* Clear watchdog enable (WEN) */
}


/*  Mode switch implementation */
#define MCU_TARGET_MODE_SHIFT   28U
#define MCU_KEY_MASK            0x00005AF0U
#define MCU_INVERTED_KEY_MASK   0x0000A50FU

static void EE_mcu_perform_mode_switch(Mcu_HardawareModeIdType
    mode_hardware_id) {

  const uint32 target_mode_mask   = mode_hardware_id << MCU_TARGET_MODE_SHIFT;
  const uint32 mode_key           = target_mode_mask | MCU_KEY_MASK;
  const uint32 mode_inverted_key  = target_mode_mask | MCU_INVERTED_KEY_MASK;
 

  /* Write key and inverted key to start a  mode transition */
  /* Enter Mode & Key */
  ME.MCTL.R = mode_key;
  /* Enter Mode & Inverted Key */  
  ME.MCTL.R = mode_inverted_key;

  while (ME.GS.B.S_MTRANS != 0U) {
    ; /* Wait until the end of mode transition */
  }

#ifdef DEBUG
  while (ME.GS.B.S_CURRENT_MODE !=  mode_hardware_id)
  {
    ; /* Catch if the right transition didn't happened */
  }
#endif /* DEBUG */

  /* Clear Transition flag (w1c bit)*/
  ME.IS.R = 0x00000001U;
}

static void EE_mcu_set_mode_configuration(Mcu_HardawareModeIdType
    mode_hardware_id, uint32 run_configuration) {
  /* TODO Add bit masks to disable bit that must be disabled and to enable bit
     that must be enabled (unconfigurable bits) */
  switch(mode_hardware_id) {
    case MCU_MODE_ID_RESET:
      ME.RESET_MC.R = run_configuration;
    break;
    case MCU_MODE_ID_TEST:
      ME.TEST_MC.R = run_configuration;
    break;
    case MCU_MODE_ID_SAFE:
      ME.SAFE_MC.R = run_configuration;
    break;
    case MCU_MODE_ID_DRUN:
      ME.DRUN_MC.R = run_configuration;
    break;
    case MCU_MODE_ID_RUN0:
      ME.RUN0_MC.R = run_configuration;
    break;
    case MCU_MODE_ID_RUN1:
      ME.RUN1_MC.R = run_configuration;
    break;
    case MCU_MODE_ID_RUN2:
      ME.RUN2_MC.R = run_configuration;
    break;
    case MCU_MODE_ID_RUN3:
      ME.RUN3_MC.R = run_configuration;
    break;
    case MCU_MODE_ID_HALT0:
      ME.HALT0_MC.R = run_configuration;
    break;
    case MCU_MODE_ID_STOP0:
      ME.STOP0_MC.R = run_configuration;
    default:
      /* Unknown mode ID nothing to do (XXX: maybe Notify DET/DEM) */
      ;
  }
}

#define MCU_RESET_CLEAR_ALL_FLAGS 0xFFFFU
static void EE_mcu_clear_reset_flags(EE_UINT16 bitmask_to_clear) {
  /* Check if the any bits of the bitmask are set */
  while((RGM.FES.R & bitmask_to_clear) != 0U) {
    /* w1c bits */
    RGM.FES.R = bitmask_to_clear;
  }
}

/*
 * Mcu_Init implementation.
 */
void Mcu_Init(const Mcu_ConfigType * ConfigPtr)
{
  /* Disable watchdog. Watchdog could be enabled by default after reset. */
  EE_mcu_disable_watchdog();
  /* Check if the MCU is supported */
  if(EE_mcu_check() == FALSE){
      /* Not supported MCU */
      /* TODO choose a right policy */
      while (TRUE) {
        ; /* For now just catch it */
      }
  }

  /* Enable modes */
  ME.MER.R = MCU_ENABLED_MODES;
  /* TODO: Maybe add some FLASH and CACHE optimization here */

  /* Only peripheral configuration 0 it's used so peripheral have to be
     enabled according to this */
  /* Enable peripherals to run in all modes not LP with
     (default configuration) */
  ME.RUNPC[0].R = 0x000000FEU;
  /* Disable peripherals in LP modes (already done at reset) */
  /* ME.LPPC[0].R = 0x00000000; */

  /* save the configuration in global status */
  EE_mcu_status.config = ConfigPtr;

  /* Configure RESET */
  EE_mcu_set_mode_configuration(MCU_MODE_ID_RESET,
    ConfigPtr->McuResetSetting);

  /* FORCE DRUN mode (priviliged mode) */
  EE_mcu_perform_mode_switch(MCU_MODE_ID_DRUN);

  /* Now the MCU is initializated */
  EE_mcu_status.init = TRUE;
}

/*
 * Mcu_InitRamSection implementation
 */
Std_ReturnType Mcu_InitRamSection(Mcu_RamSectionType RamSection)
{
  /* NOT SUPPORTED, reason: no support for external RAM */

  return E_OK;
}

/*
 * Mcu_InitClock implementation
 */
#if ( MCU_INIT_CLOCK == STD_ON )


#ifdef MCU_CLOCK_MAX_FREQ_WITHOUT_RAM_WAIT
/* 21 Error Correction Status Module */
#if (! defined EE_CURRENTCPU) || (EE_CURRENTCPU == 0)
#define ECSM_BASE_ADDR 0xFFF40000U /* equal to SPP_MCM of mpc5643l header */
#else
#define ECSM_BASE_ADDR 0x8FF40000U /* ECSM_1 */
#endif /* EE_CURRENTCPU */
/* 21.4.2.7 Miscellaneous User-Defined Control Register (MUDCR) */
#define EE_ECSM_MUDCR (*((volatile EE_UREG*)(ECSM_BASE_ADDR + 0x0024U)))
#endif /* MCU_CLOCK_MAX_FREQ_WITHOUT_RAM_WAIT */

/* Bit mask to enable PLL clock switching when written on CGM.FMPLL */
#define EE_ENABLE_PLL_SWITCHING 0x00000100

Std_ReturnType Mcu_InitClock(Mcu_ClockType ClockSetting)
{
  Mcu_ClockSettingConfigType const * const clockSettingsPtr = 
    &EE_mcu_status.config->McuClockSettingConfig[ClockSetting];

  /* Configure PLL clock Source */
  const uint32 pll_source_mask = (clockSettingsPtr->McuUseExternalOscillator)?
      0x01000000U:  /* Select Xosc as PLL source clock */
      0x00000000U;  /* Select Int RC osc as PLL source clock */

  CGM.AC3_SC.R = pll_source_mask; /* Select PLL0 source clock */
  CGM.AC4_SC.R = pll_source_mask; /* Select PLL1 source clock */

  /* TODO: check the following better */
  /* Monitor FXOSC > FIRC/1 (16MHz); no PLL monitor*/
  CGM.CMU_0_CSR.R = 0x000000000;

  /* fsys = (fcrystal * ndiv) / (idf * odf) */
  /* fvco must be from 256 MHz to 512 MHz and fvco = fsys * odf */
  /* E.G. we want fsys = 120 MHz. fvco = fsys*odf = 120 MHz * 4 = 480 MHz */
  /* fsys =  (40 * 96)/(8 * 4) = 120 MHz */

  /* For system clock configure PLL 0 */
  CGM.FMPLL[0].CR.R = (clockSettingsPtr-> McuPllConfiguration | 
      EE_ENABLE_PLL_SWITCHING);

#ifdef MCU_CLOCK_MAX_FREQ_WITHOUT_RAM_WAIT
  if (clockSettingsPtr->McuClockReferencePointFrequency >=
        MCU_CLOCK_MAX_FREQ_WITHOUT_RAM_WAIT)
  {
      /* Add a wait state in RAM read */
      EE_ECSM_MUDCR = 0x40000000U;
  }
#endif /* MCU_CLOCK_MAX_FREQ_WITHOUT_RAM_WAIT */

  EE_mcu_status.clock = ClockSetting;

  while (Mcu_GetPllStatus() != MCU_PLL_LOCKED) {
    ; /* Wait until PLL lock */
  }

  return E_OK;
}
#endif

/*
 * Mcu_DistributePllClock implementation
 */
#if ( MCU_NO_PLL == STD_OFF )
void Mcu_DistributePllClock(void)
{
  /* NOT IMPLEMENTED: meaningless in this hardware */
}
#endif

/*
 * Mcu_GetPllStatus implementation
 */
Mcu_PllStatusType Mcu_GetPllStatus(void)
{
  Mcu_PllStatusType pll_status;

  /* CGM.FMPLL[0] it's system pll */
  if (CGM.FMPLL[0].CR.B.S_LOCK ) {
    pll_status = MCU_PLL_LOCKED;
  } else {
    pll_status = MCU_PLL_UNLOCKED;
  }

  return pll_status;
}

/*
 * Mcu_GetResetReason implementation
 */
Mcu_ResetType Mcu_GetResetReason(void)
{
  Mcu_ResetType reset_reason;

  /* N.B Destructive software Reset is not supported yet by this driver */
  if( RGM.FES.B.F_SOFT_FUNC || RGM.DES.B.F_SOFT_DEST ) {
    reset_reason = MCU_SW_RESET;
  } else if( RGM.FES.B.F_SWT || RGM.FES.B.F_CWD) {
    /* SWT or Core Watchdog reset */
    reset_reason = MCU_WATCHDOG_RESET;
  } else if( RGM.DES.B.F_POR ) {
    reset_reason = MCU_POWER_ON_RESET;
  } else {
    reset_reason = MCU_RESET_UNDEFINED;
  }
}

/*
 * Mcu_GetResetRawValue implementation
 */
Mcu_RawResetType Mcu_GetResetRawValue(void)
{
  Mcu_RawResetType reset_raw_value;
  if( RGM.DES.R ) {
    reset_raw_value = RGM.DES.R;
  } else {
    reset_raw_value = RGM.FES.R;
    /* Reset start-up reset events */
    EE_mcu_clear_reset_flags(MCU_RESET_CLEAR_ALL_FLAGS);
  }

  return reset_raw_value;
}

#if ( MCU_PERFORM_RESET_API == STD_ON )
/*
 * Mcu_PerformReset implementation
 */
void Mcu_PerformReset(void)
{
  /* XXX: At this time only Software Functional Reset it's supported */
  EE_mcu_perform_mode_switch(MCU_MODE_ID_RESET);
}
#endif

/*
 * Mcu_SetMode implementation
 */
void Mcu_SetMode(Mcu_ModeType McuMode)
{
  Mcu_ModeSettingConfigType const * const modeSettingsPtr = &EE_mcu_status.
    config->McuModeSettingConf[McuMode];

  const Mcu_HardawareModeIdType mode_id = modeSettingsPtr->
    McuHardawareModeId;

  /* Set mode configuration */
  EE_mcu_set_mode_configuration(mode_id, modeSettingsPtr->McuRunConfiguration);

  /* Perform Switch */
  EE_mcu_perform_mode_switch(mode_id);
}

/*
 * Mcu_GetRamState implementation
 */
#if ( MCU_GET_RAM_STATE_API == STD_ON )
Mcu_RamStateType Mcu_GetRamState(void)
{
  /* NOT YET IMPLEMENTED, reason: no support for external RAM */

  return MCU_RAMSTATE_INVALID;
}
#endif

