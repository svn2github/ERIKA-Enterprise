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
 * AUTOSAR MCU Driver Header File.
 *
 * The MCU driver provides MCU services for Clock and RAM initialization.
 * In the MCU configuration set, the MCU specific settings for the Clock
 * (i.e. PLL setting) and RAM (i.e. section base address and size) shall be
 * configured.
 *
 * MCU055:	The MCU module shall provide a service to provide software
 * 		triggering of a hardware reset.
 *
 * Note:	Only an authorized user shall be able to call this reset service
 * 		function.
 *
 * MCU052:	The MCU module shall provide services to get the reset reason of
 * 		the last reset if the hardware supports such a feature.
 *
 * Note:	In an ECU, there are several sources which can cause a reset.
 * 		Depending on the reset reason, several application scenarios
 * 		might be necessary after reinitialization of the MCU.
 *
 * Author:  2011,  Giuseppe Serano
 */


#ifndef	MCU_H
#define	MCU_H

/*
 * Vendor Id form document:
 * [STD_HIS_SUPPLIER_IDS] HIS Software Supplier Identifications
 * http://www.automotive--his.de/his--ergebnisse.htm (broken link)
 */
#define	MCU_VENDOR_ID		0

/*
 * Module Id (101) from document:
 * List of Basic Software Modules
 * V1.5.0
 * R4.0 Rev 2
 */
#define	MCU_MODULE_ID		101

#define	MCU_SW_MAJOR_VERSION	1
#define	MCU_SW_MINOR_VERSION	0
#define	MCU_SW_PATCH_VERSION	0

#define	MCU_AR_MAJOR_VERSION	4
#define	MCU_AR_MINOR_VERSION	0
#define	MCU_AR_PATCH_VERSION	2

#include "Std_Types.h"

/*
 * MCU211:	Mcu.h shall include Mcu_Cfg.h for the API pre-compiler switches.
 * 		Mcu.c has access to the Mcu_Cfg.h via the implicitly included
 * 		Mcu.h file.
 */
#include "Mcu_Cfg.h"

/*
 * MCU012:	The following errors and exceptions shall be detectable by the
 * 		MCU module depending on its build version
 * 		(development/production mode)
 */
#define	MCU_E_PARAM_CONFIG	0x0A
#define	MCU_E_PARAM_CLOCK	0x0B
#define	MCU_E_PARAM_MODE	0x0C
#define	MCU_E_PARAM_RAMSECTION	0x0D
#define	MCU_E_PLL_NOT_LOCKED	0x0E
#define	MCU_E_UNINIT		0x0F
#define	MCU_E_PARAM_POINTER	0x10

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
 */
extern Mcu_ConfigType Mcu_Config;

/*
 * MCU230:	The type Mcu_PllStatusType is the type of the return value of
 * 		the function Mcu_GetPllStatus.
 *
 * MCU231:	The type of Mcu_PllStatusType is an enumeration with the
 * 		following values: MCU_PLL_LOCKED, MCU_PLL_UNLOCKED,
 * 		MCU_PLL_STATUS_UNDEFINED.
 */
typedef enum {
  MCU_PLL_LOCKED,		/* PLL is locked.	  */
  MCU_PLL_UNLOCKED,		/* PLL is unlocked.	  */
  MCU_PLL_STATUS_UNDEFINED,	/* PLL Status is unknown. */
} Mcu_PllStatusType;

/*
 * MCU232:	The type Mcu_ClockType defines the identification (ID) for clock
 * 		setting configured via the configuration structure.
 *
 * MCU233:	The type shall be uint8, uint16 or uint32, depending on uC
 * 		platform.
 */
typedef	uint8_least	Mcu_ClockType;

/*
 * MCU234:	This type represents the different reset that a specified MCU
 * 		can have.
 * 
 * MCU 134:	The MCU module shall provide at least the values
 * 		MCU_POWER_ON_RESET and MCU_RESET_UNDEFINED.
 *
 * Note:	Additional reset types may be added depending on MCU.
 */
typedef enum {
  MCU_POWER_ON_RESET,	/* Power On Reset (default)	 */
  MCU_WATCHDOG_RESET,	/* Internal Watchdog Timer Reset */
  MCU_SW_RESET,		/* Software Reset		 */
  MCU_RESET_UNDEFINED	/* Reset is undefined		 */
} Mcu_ResetType;

/*
 * MCU235:	The type Mcu_RawResetType specifies the reset reason in raw
 * 		register format, read from a reset status register.
 *
 * MCU236:	The type shall be uint8, uint16 or uint32 based on best
 * 		performance.
 */
typedef	uint8_least	Mcu_RawResetType;

/*
 * MCU237:	The Mcu_ModeType specifies the identification (ID) for a MCU
 * 		mode, configured via configuration structure.
 *
 * MCU238:	The type shall be uint8, uint16 or uint32.
 */
typedef	uint8_least	Mcu_ModeType;

/*
 * MCU237:	The Mcu_ModeType specifies the identification (ID) for a MCU
 * 		mode, configured via configuration structure.
 *
 * MCU238:	The type shall be uint8, uint16 or uint32.
 */
/* typedef	uint8_least	Mcu_ModeType; */ /* Not supported */

/*
 * MCU239:	The Mcu_RamSectionType specifies the identification (ID) for a
 * 		RAM section, configured via the configuration structure.
 *
 * MCU240:	The type shall be uint8, uint16 or uint32, based on best
 * 		performance.
 */
typedef uint8_least Mcu_RamSectionType;

/*
 * MCU?!?:	This is the Ram State data type returned by the function
 * 		Mcu_GetRamState of the Mcu module. It is not required that all
 * 		RAM state types are supported by the hardware.
 */
#if ( MCU_GET_RAM_STATE_API == STD_ON )
typedef enum {
  MCU_RAMSTATE_INVALID,	/* Ram content is not valid or unknown (default) */
  MCU_RAMSTATE_VALID	/* Ram content is valid.			 */
} Mcu_RamStateType;
#endif

/*
 * Service ID's
 */
#define	MCU_INIT_SERVICE_ID			0x00
#define	MCU_INITRAMSECTION_SERVICE_ID		0x01
#define	MCU_INITCLOCK_SERVICE_ID		0x02
#define	MCU_DISTRIBUTEPLLCLOCK_SERVICE_ID	0x03
#define	MCU_GETPLLSTATUS_SERVICE_ID		0x04
#define	MCU_GETRESETREASON_SERVICE_ID		0x05
#define	MCU_GETRESETRAWVALUE_SERVICE_ID		0x06
#define	MCU_PERFORMRESET_SERVICE_ID		0x07
#define	MCU_SETMODE_SERVICE_ID			0x08
#define	MCU_GETVERSIONINFO_SERVICE_ID		0x09
#define	MCU_GETRAMSTATE_SERVICE_ID		0x0A

/*
 * MCU153:	Service 0x00
 *
 * MCU026:	The function Mcu_Init shall initialize the MCU module, i.e. make
 * 		the configuration settings for power down, clock and RAM
 * 		sections visible within the MCU module.
 *
 * Note:	After the execution of the function Mcu_Init, the configuration
 * 		data are accessible and can be used by the MCU module functions
 * 		as, e.g., Mcu_InitRamSection.
 *
 * The MCU module’s implementer shall apply the following rules regarding
 * initialization of controller registers within the function Mcu_Init:
 * 	1. MCU116:	If the hardware allows for only one usage of the
 * 			register, the driver module implementing that
 * 			functionality is responsible for initializing the
 * 			register.
 * 	2. MCU244:	If the register can affect several hardware modules and
 * 			if it is an I/O register, it shall be initialised by the
 * 			PORT driver.
 * 	3. MCU245:	If the register can affect several hardware modules and
 * 			if it is not an I/O register, it shall be initialised by
 * 			this MCU driver.
 * 	4. MCU246:	One-time writable registers that require initialisation
 * 			directly after reset shall be initialised by the
 * 			startup code.
 * 	5. MCU247:	All other registers not mentioned before shall be
 * 			initialised by the start-up code.
 *
 * MCU127:	If not applicable, the MCU module’s environment shall pass a
 * 		NULL pointer to the function Mcu_Init. In this case the check
 * 		for this NULL pointer has to be omitted.
 *
 * Note:	The term ‘Hardware Module’ refers to internal modules of the MCU
 * 		and not to a BSW module.
 */
void Mcu_Init(
  const Mcu_ConfigType * ConfigPtr
);

/*
 * Service 0x01
 *
 * MCU011:	The function Mcu_InitRamSection shall fill the memory from
 * 		address McuRamSectionBaseAddress up to address
 * 		McuRamSectionBaseAddress + McuRamSectionSize-1 with the
 * 		byte-value contained in McuRamDefaultValue, where
 * 		McuRamSectionBaseAddress, McuRamSectionSize and
 * 		McuRamDefaultValue are the values of the configuration
 * 		parameters for each RamSection (see MCU030).
 *
 * MCU136:	The MCU module’s environment shall call the function
 * 		Mcu_InitRamSection only after the MCU module has been
 * 		initialized using the function Mcu_Init.
 */
Std_ReturnType Mcu_InitRamSection(
  Mcu_RamSectionType RamSection
);

/*
 * MCU155:	Service 0x02
 *
 * MCU137:	The function Mcu_InitClock shall initialize the PLL and other
 * 		MCU specific clock options. The clock configuration parameters
 * 		are provided via the configuration structure.
 *
 * MCU138:	The function Mcu_InitClock shall start the PLL lock procedure
 * 		(if PLL shall be initialized) and shall return without waiting
 *		until the PLL is locked.
 *
 * MCU139:	The MCU module’s environment shall only call the function
 * 		Mcu_InitClock after the MCU module has been initialized using
 * 		the function Mcu_Init.
 *
 * MCU210:	The function Mcu_InitClock shall be disabled if the parameter
 * 		McuInitClock is set to FALSE. Instead this function is available
 * 		if the former parameter is set to TRUE (see also MCU182_Conf).
 */
#if ( MCU_INIT_CLOCK == STD_ON )
Std_ReturnType Mcu_InitClock(
  Mcu_ClockType ClockSetting
);
#endif

/*
 * MCU156:	Service 0x03
 *
 * MCU140:	The function Mcu_DistributePllClock shall activate the PLL clock
 * 		to the MCU clock distribution.
 *
 * MCU141:	The MCU module’s environment shall execute the function
 * 		Mcu_DistributePllClock if the MCU module needs a separate
 * 		request to activate the PLL clock after the PLL is locked.
 * 		In this case, the function shall remove the current clock source
 * 		(for example internal oscillator clock) from MCU clock
 * 		distribution.
 *
 * MCU056:	The function Mcu_DistributePllClock shall return without
 * 		affecting the MCU hardware if the PLL clock has been
 * 		automatically activated by the MCU hardware.
 *
 * MCU142:	The MCU module’s environment shall only call the function
 * 		Mcu_DistributePllClock after the status of the PLL has been
 * 		detected as locked by the function Mcu_GetPllStatus.
 *
 * MCU205:	The function Mcu_DistributePllClock shall be available if the
 * 		pre-compile parameter McuNoPll is set to FALSE. Otherwise, this
 * 		Api has to be disabled (see also MCU180_Conf).
 */
#if ( MCU_NO_PLL == STD_OFF )
void Mcu_DistributePllClock(
  void
);
#endif

/*
 * MCU157:	Service 0x04
 *
 * MCU008:	The function Mcu_GetPllStatus shall return the lock status of
 * 		the PLL.
 *
 * MCU132:	The function Mcu_GetPllStatus shall return
 * 		MCU_PLL_STATUS_UNDEFINED if this function is called prior to
 * 		calling of the function Mcu_Init.
 *
 * MCU206:	The function Mcu_GetPllStatus shall also return
 * 		MCU_PLL_STATUS_UNDEFINED if the pre-compile parameter McuNoPll
 * 		is set to TRUE (see also MCU180_Conf).
 */
Mcu_PllStatusType Mcu_GetPllStatus(
  void
);

/*
 * MCU158:	Service 0x05
 *
 * MCU005:	The function Mcu_GetResetReason shall read the reset reason from
 * 		the hardware and return this reason if supported by the
 * 		hardware. If the hardware does not support the hardware
 * 		detection of the reset reason, the return value from the
 * 		function Mcu_GetResetReason shall always be MCU_POWER_ON_RESET.
 *
 * MCU133:	The function Mcu_GetResetReason shall return MCU_RESET_UNDEFINED
 * 		if this function is called prior to calling of the function
 * 		Mcu_Init, and if supported by the hardware.
 *
 * Note:	The User should ensure that the reset reason is cleared once it
 * 		has been read out to avoid multiple reset reasons.
 */
Mcu_ResetType Mcu_GetResetReason(
  void 
);

/*
 * MCU159:	Service 0x06
 *
 * MCU135:	The function Mcu_GetResetRawValue shall return an implementation
 * 		specific value which does not correspond to a valid value of the
 * 		reset status register and is not equal to 0 if this function is
 * 		called prior to calling of the function Mcu_Init, and if
 * 		supported by the hardware.
 *
 * MCU006:	The function Mcu_GetResetRawValue shall read the reset raw value
 * 		from the hardware register if the hardware supports this. If the
 * 		hardware does not have a reset status register, the return value
 * 		shall be 0x0.
 *
 * Note:	The User should ensure that the reset reason is cleared once it
 * 		has been read out to avoid multiple reset reasons.
 */
Mcu_RawResetType Mcu_GetResetRawValue(
  void
);

/*
 * MCU160:	Service 0x07
 *
 * MCU143:	The function Mcu_PerformReset shall perform a microcontroller
 * 		reset by using the hardware feature of the microcontroller.
 *
 * MCU144:	The function Mcu_PerformReset shall perform the reset type which
 * 		is configured in the configuration set.
 *
 * MCU145:	The MCU module’s environment shall only call the function
 * 		Mcu_PerformReset after the MCU module has been initialized by
 * 		the function Mcu_Init.
 *
 * MCU146:	The function Mcu_PerformReset is only available if the runtime
 * 		parameter McuPerformResetApi is set to TRUE. If set to FALSE,
 * 		the function Mcu_PerformReset is not applicable.
 */
#if ( MCU_PERFORM_RESET_API == STD_ON )
void Mcu_PerformReset(
  void
);
#endif

/*
 * MCU161:	Service 0x08
 *
 * MCU147:	The function Mcu_SetMode shall set the MCU power mode.
 * 		In case of CPU power down mode, the function Mcu_SetMode returns
 * 		after it has performed a wake-up.
 *
 * MCU148:	The MCU module’s environment shall only call the function
 * 		Mcu_SetMode after the MCU module has been initialized by the
 * 		function Mcu_Init.
 */
void Mcu_SetMode(
  Mcu_ModeType McuMode
);

/*
 * MCU162:	Service 0x09
 *
 * MCU103:	The function Mcu_GetVersionInfo shall return the version
 * 		information of the MCU module. The version information includes:
 * 		- Module Id
 * 		- Vendor Id
 * 		- Vendor specific version numbers (BSW00407)
 *
 * MCU104:	The function Mcu_GetVersionInfo shall be pre-compile time
 * 		configurable On/Off by the configuration parameter
 * 		McuVersionInfoApi.
 *
 * MCU149:	If source code for caller and callee of the function
 * 		Mcu_GetVersionInfo is available, the MCU module should realize
 * 		this function as a macro. The MCU module should define this
 * 		macro in the module’s header file.
 *
 * MCU204:	if development error detection is enabled, the parameter
 * 		versioninfo shall be checked for being NULL. The error
 * 		MCU_E_PARAM_POINTER shall be reported in case the value is a
 * 		NULL pointer. (TODO)
 */
#if ( MCU_VERSION_INFO_API == STD_ON )
#if ( MCU_DEV_ERROR_DETECT == STD_ON )
#define	Mcu_GetVersionInfo(_vi)	STD_GET_VERSION_INFO(_vi,MCU) \
	else \
	{\
		Det_ReportError(\
			MCU_MODULE_ID,\
			0,\
			MCU_GETVERSIONINFO_SERVICE_ID,\
			MCU_E_PARAM_POINTER\
		);\
	}
#else
#define	Mcu_GetVersionInfo(_vi)	STD_GET_VERSION_INFO(_vi,MCU)
#endif	/* MCU_DEV_ERROR_DETECT */
#endif	/* MCU_VERSION_INFO_API */

/*
 * MCU207:	Service 0x0A
 *
 * Note:	Some microcontrollers offer the functionality to check if the
 * 		Ram Status is valid after a reset. The function Mcu_GetRamState
 * 		can be used for this reason.
 *
 * MCU208:	The MCU module’s environment shall call this function only if
 * 		the MCU module has been already initialized using the function
 * 		MCU_Init.
 *
 * MCU209:	The function Mcu_GetRamState shall be available to the user if
 * 		the precompile parameter McuGetRamStateApi is set to TRUE.
 * 		Instead, if the former parameter is set to FALSE, this function
 * 		shall be disabled (e.g. the hardware does not support this
 * functionality).
 */
#if ( MCU_GET_RAM_STATE_API == STD_ON )
Mcu_RamStateType Mcu_GetRamState(
  void
);
#endif

#endif	/* MCU_H */
