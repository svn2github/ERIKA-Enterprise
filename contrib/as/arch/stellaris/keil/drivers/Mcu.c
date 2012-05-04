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
 * Author:  2011,  Giuseppe Serano
 */

#define	MCU_AR_RELEASE_MAJOR_VERSION	4
#define	MCU_AR_RELEASE_MINOR_VERSION	0

#include "Mcu.h"

/*
 * MCU110:	For included (external) header files:
 * 		- <MODULENAME>_AR_ RELEASE_MAJOR_VERSION
 * 		- <MODULENAME>_AR_ RELEASE_MINOR_VERSION
 * 		shall be verified.
 */
#if !defined( MCU_AR_MAJOR_VERSION ) || \
    ( MCU_AR_MAJOR_VERSION != MCU_AR_RELEASE_MAJOR_VERSION )
#error	Mcu: version mismatch.
#endif

#include "ee.h"

/* Development error macros. */
#if ( MCU_DEV_ERROR_DETECT == STD_ON )

#include "Det.h"
#if defined(__AS_DEM__)
#include "Dem.h"
#endif

#define VALIDATE(_exp,_api,_err ) \
  if( !(_exp) ) { \
    Det_ReportError(MCU_MODULE_ID,0,_api,_err); \
    return; \
  }

#define VALIDATE_W_RV(_exp,_api,_err,_rv ) \
  if( !(_exp) ) { \
    Det_ReportError(MCU_MODULE_ID,0,_api,_err); \
    return (_rv); \
  }

#else	/* MCU_DEV_ERROR_DETECT */

#define VALIDATE(_exp,_api,_err ) \
  if( !(_exp) ) { \
    return; \
  }
#define VALIDATE_W_RV(_exp,_api,_err,_rv ) \
  if( !(_exp) ) { \
    return (_rv); \
  }
#endif	/* !MCU_DEV_ERROR_DETECT */

/*
 * Type that holds all global data for Mcu
 */
typedef struct
{
  boolean			Init;		/* MCU Driver Initialized? */

  const Mcu_ConfigType *	ConfigPtr;	/* Actual Configuration */

  Mcu_ClockType			ClockSetting;	/* Actual Clock Setting */

} Mcu_GlobalType;


/*
 * MCU Global Configuration
 */
Mcu_GlobalType Mcu_Global =
{
  FALSE,			/* Init		*/
  NULL_PTR,			/* ConfigPtr	*/
  MCU_CLOCK_MODE_NORMAL		/* ClockSetting	*/
};

#include "Hardware.h"	/* Hardware Abstraction Header File. */

/*
 * Mcu_Init implementation.
 */
void Mcu_Init(
  const Mcu_ConfigType * ConfigPtr
)
{

  VALIDATE( ( ConfigPtr != NULL ), MCU_INIT_SERVICE_ID, MCU_E_PARAM_CONFIG );

  VALIDATE( ( Hw_CheckCore() == E_OK ), MCU_INIT_SERVICE_ID, MCU_E_UNINIT );

  Mcu_Global.ConfigPtr = ConfigPtr;
  Mcu_Global.Init = TRUE;

  EE_system_init();

}

/*
 * Mcu_InitRamSection implementation
 */
Std_ReturnType Mcu_InitRamSection(
  Mcu_RamSectionType RamSection
)
{

  VALIDATE_W_RV(
    ( Mcu_Global.Init == TRUE ),
    MCU_INITRAMSECTION_SERVICE_ID,
    MCU_E_UNINIT,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    ( RamSection <= Mcu_Global.ConfigPtr->McuRamSectors ),
    MCU_INITRAMSECTION_SERVICE_ID,
    MCU_E_PARAM_RAMSECTION,
    E_NOT_OK 
  );

  /* NOT YET IMPLEMENTED, reason: no support for external RAM */

  return E_OK;

}

/*
 * Mcu_InitSystemClock implementation
 */
#if ( MCU_INIT_CLOCK == STD_ON )
static void Mcu_InitSystemClock(Mcu_ClockSettingConfigType *ConfigPtr)
{
  register uint32 rccsrc;	/* Run-Mode Clock Configuration Source        */
  register uint32 rcc2src;	/* Run-Mode Clock Configuration 2 Source      */
  register uint32 rccdst;	/* Run-Mode Clock Configuration Destination   */
  register uint32 rcc2dst;	/* Run-Mode Clock Configuration 2 Destination */

  rccsrc = ConfigPtr->McuRunModeClockConfiguration;
  rcc2src = ConfigPtr->McuRunModeClockConfiguration2;

  /* Configuring the microcontroller to run of a "raw" clock source */
  rccdst = SYSCTL_RCC_R;		/* Read RCC			      */
  rccdst |= SYSCTL_RCC_BYPASS;		/* PLL Bypass			      */
  rccdst |= SYSCTL_RCC_PWRDN;		/* PLL Power-Down		      */
  rccdst &= ~SYSCTL_RCC_USESYSDIV;	/* Disable System Divisor	      */
  rccdst |= SYSCTL_RCC_SYSDIV_M;	/* Reset System Divisor Configuration */
  rccdst &= ~SYSCTL_RCC_XTAL_M;		/* Clear XTAL			      */
  rccdst |= SYSCTL_RCC_XTAL_16MHZ;	/* 16MHz			      */
  rccdst &= ~SYSCTL_RCC_OSCSRC_M;	/* Clear Oscillator Source	      */
  rccdst |= SYSCTL_RCC_OSCSRC_INT;	/* Precision Internal Oscillator      */
  rccdst &= ~SYSCTL_RCC_IOSCDIS;	/* Enable Internal Oscillator	      */
  rccdst |= SYSCTL_RCC_MOSCDIS;		/* Disable Main Oscillator	      */
  SYSCTL_RCC_R = rccdst;		/* Write RCC			      */
  rcc2dst = SYSCTL_RCC2_R;		/* Read RCC2			      */
  rcc2dst &= ~SYSCTL_RCC2_USERCC2;	/* Don't use RCC2		      */
  rcc2dst &= ~SYSCTL_RCC2_DIV400;	/* Divide PLL as 200MHz		      */
  rcc2dst |= SYSCTL_RCC2_SYSDIV2_M;	/* Reset System Divisor Configuration */
  rcc2dst |= SYSCTL_RCC2_SYSDIV2LSB;	/* Set System Divisor LSB	      */
  rcc2dst |= SYSCTL_RCC2_PWRDN2;	/* PLL Power-Down		      */
  rcc2dst |= SYSCTL_RCC2_BYPASS2;	/* PLL Bypass			      */
  rcc2dst &= ~SYSCTL_RCC2_OSCSRC2_M;	/* Clear Oscillator Source	      */
  rcc2dst |= SYSCTL_RCC2_OSCSRC2_IO;	/* Precision Internal Oscillator      */
  SYSCTL_RCC2_R = rcc2dst;		/* Write RCC2			      */

  /* PIOSC Automatic Calibration using Hibernation Module if present */
  if ( SYSCTL_PPHIB_R & SYSCTL_PPHIB_P0) {

    /* Hibernation Module Clock Gating */
    SYSCTL_RCGCHIB_R |= SYSCTL_RCGCHIB_R0;

    /* Hibernation Module 32.768-kHz Oscillator Enable. */
    HIB_CTL_R |= HIB_CTL_CLK32EN;

    /* Wait Hibenation Module 32.768-kHz Oscillator to Enable. */
    while ( !((HIB_RIS_R & HIB_RIS_WC) || (HIB_MIS_R & HIB_MIS_WC)) );

    /* Repeat Calibration Process until Pass */
    while ( !(SYSCTL_PIOSCSTAT_R & SYSCTL_PIOSCSTAT_CRPASS))
      SYSCTL_PIOSCCAL_R |= SYSCTL_PIOSCCAL_CAL;

    /* Hibernation Module 32.768-kHz Oscillator Disable. */
    HIB_CTL_R &= ~HIB_CTL_CLK32EN;

    /* Hibernation Module Clock Gating Removal */
    SYSCTL_RCGCHIB_R &= ~SYSCTL_RCGCHIB_R0;

  }

  /* Set XTAL Frequency */
  rccdst &= ~SYSCTL_RCC_XTAL_M;
  rccdst |= (rccsrc & SYSCTL_RCC_XTAL_M);

  /* Enable Selected Oscillator */
  rccdst &= ~SYSCTL_RCC_MOSCDIS;
  rccdst |= rccsrc & (SYSCTL_RCC_IOSCDIS | SYSCTL_RCC_MOSCDIS);

  /* Enable System Divisor */
  rccdst |= rccsrc & (SYSCTL_RCC_USESYSDIV);

  if (rcc2src & SYSCTL_RCC2_USERCC2) {
    SYSCTL_RCC_R = rccdst;		/* Write RCC			      */
    rcc2dst = SYSCTL_RCC2_R;		/* Read RCC2			      */
    rcc2dst |= SYSCTL_RCC2_USERCC2;	/* Use RCC2			      */
    rcc2dst &= ~SYSCTL_RCC2_OSCSRC2_M;	/* Clear Oscillator Source	      */
    rcc2dst |= (rcc2src & SYSCTL_RCC2_OSCSRC2_M); /* Set Oscillator Source    */
    if (!(rcc2src & SYSCTL_RCC2_PWRDN2))
      rcc2dst &= ~SYSCTL_RCC2_PWRDN2;	/* PLL Power-Up			      */
    rcc2dst &= ~SYSCTL_RCC2_SYSDIV2_M;	/* Clear System Divisor Configuration */
    rcc2dst |= (rcc2src & SYSCTL_RCC2_SYSDIV2_M); /* Set System Divisor	      */
    SYSCTL_RCC2_R = rcc2dst;		/* Wriet RCC2			      */
  }
  else {
    rccdst &= ~SYSCTL_RCC_OSCSRC_M;	/* Clear Oscillator Source	      */
    rccdst |= (rccsrc & SYSCTL_RCC_OSCSRC_M); /* Set Oscillator Source	      */
    if (!(rccsrc & SYSCTL_RCC_PWRDN))
      rccdst &= ~SYSCTL_RCC_PWRDN;	/* PLL Power-Up			      */
    rccdst &= ~SYSCTL_RCC_SYSDIV_M;	/* Clear System Divisor Configuration */
    rccdst |= (rccsrc & SYSCTL_RCC_SYSDIV_M); /* Set System Divisor	      */
    SYSCTL_RCC_R = rccdst;		/* Write RCC			      */
    rcc2dst = SYSCTL_RCC2_R;		/* Read RCC2			      */
    SYSCTL_RCC2_R = rcc2dst;		/* Wriet RCC2			      */
  }

}
#endif

/*
 * Mcu_InitClock implementation
 */
#if ( MCU_INIT_CLOCK == STD_ON )
Std_ReturnType Mcu_InitClock(
  Mcu_ClockType ClockSetting
)
{

  VALIDATE_W_RV(
    ( Mcu_Global.Init == TRUE ),
    MCU_INITCLOCK_SERVICE_ID,
    MCU_E_UNINIT,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    ( ClockSetting <= MCU_CLOCK_MODES_NUMBER ),
    MCU_INITCLOCK_SERVICE_ID,
    MCU_E_PARAM_CLOCK,
    E_NOT_OK
  );

  Mcu_InitSystemClock(
    &Mcu_Global.ConfigPtr->McuClockSettingConfig[ClockSetting]
  );

  Mcu_Global.ClockSetting = ClockSetting;

  return E_OK;

}
#endif

/*
 * Mcu_DistributePllClock implementation
 */
#if ( MCU_NO_PLL == STD_OFF )
void Mcu_DistributePllClock(
  void
)
{
  register uint32 rccdst;	/* Run-Mode Clock Configuration Destination   */
  register uint32 rcc2dst;	/* Run-Mode Clock Configuration 2 Destination */

  VALIDATE(
    ( Mcu_Global.Init == TRUE ),
    MCU_DISTRIBUTEPLLCLOCK_SERVICE_ID,
    MCU_E_UNINIT
  );

  rccdst = SYSCTL_RCC_R;	/* Read RCC	*/
  rcc2dst = SYSCTL_RCC2_R;	/* Read RCC2	*/

  /* PLL undefined check */
  VALIDATE(
    (
      ( SYSCTL_DC1_R & SYSCTL_DC1_PLL ) &&
      (
	(
	  ( rcc2dst & SYSCTL_RCC2_USERCC2 ) && 
	  !( rcc2dst & SYSCTL_RCC2_PWRDN2 )
	) ||
	!(
	  ( SYSCTL_RCC2_R & SYSCTL_RCC2_USERCC2 ) ||
	  ( SYSCTL_RCC_R & SYSCTL_RCC_PWRDN )
	)
      )
    ),
    MCU_DISTRIBUTEPLLCLOCK_SERVICE_ID,
    MCU_E_PLL_UNDEFINED
  );

  /* PLL locked check */
  VALIDATE(
    ( SYSCTL_PLLSTAT_R & SYSCTL_PLLSTAT_LOCK ),
    MCU_DISTRIBUTEPLLCLOCK_SERVICE_ID,
    MCU_E_PLL_NOT_LOCKED
  );

  if (SYSCTL_RCC2_R & SYSCTL_RCC2_USERCC2) {
    rccdst = SYSCTL_RCC_R;		/* Read RCC */
    SYSCTL_RCC_R = rccdst;		/* Write RCC */
    rcc2dst = SYSCTL_RCC2_R;		/* Read RCC2 */
    rcc2dst &= ~SYSCTL_RCC2_BYPASS2;	/* Remove PLL Bypass */
    SYSCTL_RCC2_R = rcc2dst;		/* Write RCC2 */
  }
  else {
    rccdst = SYSCTL_RCC_R;		/* Read RCC */
    rccdst &= ~SYSCTL_RCC_BYPASS;	/* Remove PLL Bypass */
    SYSCTL_RCC_R = rccdst;		/* Write RCC */
    rcc2dst = SYSCTL_RCC2_R;		/* Read RCC2 */
    SYSCTL_RCC2_R = rcc2dst;		/* Write RCC2 */
  }

}
#endif

/*
 * Mcu_GetPllStatus implementation
 */
Mcu_PllStatusType Mcu_GetPllStatus(
  void
)
{

  Mcu_PllStatusType ret;

  VALIDATE_W_RV(
    ( Mcu_Global.Init == TRUE ),
    MCU_GETPLLSTATUS_SERVICE_ID,
    MCU_E_UNINIT,
    MCU_PLL_STATUS_UNDEFINED
  );

#if ( MCU_NO_PLL == STD_ON )
  ret = MCU_PLL_STATUS_UNDEFINED;
#else
  /* PLL present and powered check. */
  if ( 
    !( SYSCTL_DC1_R & SYSCTL_DC1_PLL ) ||
    (
      ( SYSCTL_RCC2_R & SYSCTL_RCC2_USERCC2 ) && 
      ( SYSCTL_RCC2_R & SYSCTL_RCC2_PWRDN2 )
    ) ||
    (
      !( SYSCTL_RCC2_R & SYSCTL_RCC2_USERCC2 ) && 
      ( SYSCTL_RCC_R & SYSCTL_RCC_PWRDN )
    )
  )
    ret = MCU_PLL_STATUS_UNDEFINED;
  else if ( SYSCTL_PLLSTAT_R & SYSCTL_PLLSTAT_LOCK )
    ret = MCU_PLL_LOCKED;
  else
    ret = MCU_PLL_UNLOCKED;
#endif

  return ret;

}

/*
 * Mcu_GetResetReason implementation
 */
Mcu_ResetType Mcu_GetResetReason(
  void
) {

  register uint32 resc;
  Mcu_ResetType ret;

  VALIDATE_W_RV(
    ( Mcu_Global.Init == TRUE ),
    MCU_GETRESETREASON_SERVICE_ID,
    MCU_E_UNINIT,
    MCU_RESET_UNDEFINED
  );

  resc = SYSCTL_RESC_R;

  if ( (resc & SYSCTL_RESC_POR) )
    ret = MCU_POWER_ON_RESET;
  else if ( (resc & (SYSCTL_RESC_WDT1 | SYSCTL_RESC_WDT0)) )
    ret = MCU_WATCHDOG_RESET;
  else if ( (resc & SYSCTL_RESC_SW) )
    ret = MCU_SW_RESET;
  else ret = MCU_RESET_UNDEFINED;
  
  SYSCTL_RESC_R = 0x00000000;

  return ret;

}

/*
 * Mcu_GetResetRawValue implementation
 */
Mcu_RawResetType Mcu_GetResetRawValue(
  void
)
{

  Mcu_RawResetType ret;

  VALIDATE_W_RV(
    ( Mcu_Global.Init == TRUE ),
    MCU_GETRESETREASON_SERVICE_ID,
    MCU_E_UNINIT,
    0x00000000
  );

  ret = SYSCTL_RESC_R;

  SYSCTL_RESC_R = 0x000000000;

  return ret;

}

#if ( MCU_PERFORM_RESET_API == STD_ON )
/*
 * Mcu_PerformReset implementation
 */
void Mcu_PerformReset(
  void
)
{

  register uint32 apint;

  VALIDATE(
    ( Mcu_Global.Init == TRUE ),
    MCU_PERFORMRESET_SERVICE_ID,
    MCU_E_UNINIT
  );

  /* 
   * Ensure all outstanding memory accesses included buffered write are
   * completed before reset
   */
  __dsb(0xF);

  apint = NVIC_APINT_R;
  NVIC_APINT_R = (
    NVIC_APINT_VECTKEY |		/* Vector key 			 */
    (apint & NVIC_APINT_PRIGROUP_M) |	/* Keep priority group unchanged */
    NVIC_APINT_SYSRESETREQ		/* System Reset Request		 */
  );

  __dsb(0xF);	/* Ensure completion of memory access */

  while(1);	/* Waiting for Reset to perform. */

}
#endif

/*
 * Mcu_SetMode implementation
 */
void Mcu_SetMode(
  Mcu_ModeType McuMode
)
{

  VALIDATE( ( Mcu_Global.Init == TRUE ), MCU_SETMODE_SERVICE_ID, MCU_E_UNINIT );

  VALIDATE(
    ( Mcu_Global.ConfigPtr->McuNumberOfMcuModes > McuMode ),
    MCU_SETMODE_SERVICE_ID,
    MCU_E_PARAM_MODE 
  );

  /* NOT YET IMPLEMENTED, reason: operational mode only */
  return;

}

/*
 * Mcu_GetRamState implementation
 */
#if ( MCU_GET_RAM_STATE_API == STD_ON )
Mcu_RamStateType Mcu_GetRamState(
  void
)
{

  VALIDATE_W_RV(
    ( Mcu_Global.Init == TRUE ),
    MCU_GETRAMSTATE_SERVICE_ID,
    MCU_E_UNINIT,
    MCU_RAMSTATE_INVALID
  );

  /* NOT YET IMPLEMENTED, reason: no support for external RAM */

  return MCU_RAMSTATE_INVALID;

}
#endif

