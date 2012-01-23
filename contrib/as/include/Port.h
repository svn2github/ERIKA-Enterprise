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
 * AUTOSAR PORT Driver Header File.
 *
 * PORT001:	The PORT Driver module shall initialize the whole port structure
 * 		of the microcontroller.
 *
 * Note:	Defining the order in which the ports and port pins are
 * 		configured is the task of the configuration tool.
 *
 * Author:  2011,  Giuseppe Serano
 */


#ifndef	AR_PORT_H
#define	AR_PORT_H

/*
 * Vendor Id form document:
 * [STD_HIS_SUPPLIER_IDS] HIS Software Supplier Identifications
 * http://www.automotive--his.de/his--ergebnisse.htm (broken link)
 */
#define	PORT_VENDOR_ID		0

/*
 * Module Id (101) from document:
 * List of Basic Software Modules
 * V1.5.0
 * R4.0 Rev 2
 */
#define	PORT_MODULE_ID		124

#define	PORT_SW_MAJOR_VERSION	1
#define	PORT_SW_MINOR_VERSION	0
#define	PORT_SW_PATCH_VERSION	0

#define	PORT_AR_MAJOR_VERSION	4
#define	PORT_AR_MINOR_VERSION	0
#define	PORT_AR_PATCH_VERSION	2

/*
 * PORT130:	Port.h shall include Port_Cfg.h for the API pre-compiler
 * 		switches, Std_Types.h and EcuM.h
 */
#include "Std_Types.h"

/*
 * PORT051:	The following errors and exceptions shall be detectable by the
 * 		PORT driver depending on its build version
 * 		(development/production).
 */
#define	PORT_E_PARAM_PIN		0x0A
#define	PORT_E_DIRECTION_UNCHANGEABLE	0x0B
#define	PORT_E_PARAM_CONFIG		0x0C
#define	PORT_E_PARAM_INVALID_MODE	0x0D
#define	PORT_E_MODE_UNCHANGEABLE	0x0E
#define	PORT_E_UNINIT			0x0F
#define	PORT_E_PARAM_POINTER		0x10

/*
 * PORT013:	The type Port_PinType shall be used for the symbolic name of a
 * 		Port Pin.
 *
 * PORT219:	The type Port_PinType shall be uint8, uint16 or uint32 based on
 * 		the specific MCU platform.
 *
 * Note:	The user shall use the symbolic names provided by the
 * 		configuration tool.
 */
typedef	uint8_least	Port_PinType;

/*
 * PORT046:	The type Port_PinDirectionType is a type for defining the
 * 		direction of a Port Pin.
 *
 * PORT220:	The type Port_PinDirectionType shall be of enumeration type
 * 		having range as PORT_PIN_IN and PORT_PIN_OUT.
 */
typedef enum
{
  PORT_PIN_IN	=	STD_OFF,	/* Sets port pin as input.  */
  PORT_PIN_OUT	=	STD_ON		/* Sets port pin as output. */
} Port_PinDirectionType;

/*
 * Port Pin Level.
 */
typedef enum {
  PORT_PIN_LEVEL_HIGH	=	STD_HIGH,	/* Port Pin level is High */
  PORT_PIN_LEVEL_LOW	=	STD_LOW		/* Port Pin level is Low  */
} Port_PinLevelType;

/*
 * PORT124:	A port pin shall be configurable with a number of port pin modes
 * 		(type Port_PinModeType).
 *
 * PORT212:	The type Port_PinModeType shall be used with the function call
 * 		Port_SetPinMode.
 *
 * PORT221:	The type Port_PinModeType shall be uint8, uint16 or uint32.
 */
typedef	uint8_least	Port_PinModeType;

/*
 * PORT130:	Port.h shall include Port_Cfg.h for the API pre-compiler
 * 		switches, Std_Types.h and EcuM.h
 */
#include "Port_Cfg.h"

/*
 * PORT073:	The type Port_ConfigType is a type for the external data
 * 		structure containing the initialization data for the PORT
 * 		Driver.
 *
 * Note:	The user shall use the symbolic names defined in the
 * 		configuration tool.
 *
 * Note:	The configuration of each port pin is MCU specific. Therefore,
 * 		it is not possible to include a complete list of different
 * 		configurations in this specification.
 *
 * PORT072:	A list of possible port configurations for the structure
 * 		Port_ConfigType is given below:
 * 		- Pin mode (e.g. DIO, ADC, SPI …): this port pin configuration
 * 		  is mandatory unless the port pin is configured for DIO.
 * 		- Pin direction (input, output): this port pin configuration is
 * 		  mandatory when the port pin is to be used for DIO.
 * 		- Pin level init value (see PORT055): this port pin
 * 		  configuration is mandatory when the port pin is used for DIO.
 * 		- Pin direction changeable during runtime (STD_ON/STD_OFF): this
 * 		  port pin configuration is MCU dependent.
 * 		- Pin mode changeable during runtime (STD_ON/STD_OFF):
 * 		  configuration is MCU dependent.
 * 		Optional parameters (if supported by hardware):
 * 		- Slew rate control.
 * 		- Activation of internal pull-ups.
 * 		- Microcontroller specific port pin properties.
 */
extern	Port_ConfigType	Port_Config[];

/*
 * Service ID's
 */
#define	PORT_INIT_ID			0x00
#define	PORT_SET_PIN_DIRECTION_ID	0x01
#define	PORT_REFRESH_PORT_DIRECTION_ID	0x02
#define	PORT_GET_VERSION_INFO_ID	0x03
#define	PORT_SET_PIN_MODE_ID		0x04

/*
 * PORT140:	Service 0x00
 *
 * PORT041:	The function Port_Init shall initialize ALL ports and port pins
 * 		with the configuration set pointed to by the parameter
 * 		ConfigPtr.
 *
 * PORT078:	The Port Driver module’s environment shall call the function
 * 		Port_Init first in order to initialize the port for use.
 *
 * PORT213:	If Port_Init function is not called first, then no operation can
 * 		occur on the MCU ports and port pins.
 *
 * PORT042:	The function Port_Init shall initialize all configured
 * 		resources.
 *
 * The function Port_Init shall apply the following rules regarding
 * initialisation of controller registers.
 *
 * - PORT113:	If the hardware allows for only one usage of the register, the
 * 		driver module implementing that functionality is responsible for
 * 		initializing the register.
 *
 * - PORT214:	If the register can affect several hardware modules and if it is
 * 		an I/O register it shall be initialised by this PORT driver.
 *
 * - PORT215:	If the register can affect several hardware modules and if it is 
 * 		not an I/O register, it shall be initialised by the MCU driver.
 *
 * - PORT217:	One-time writable registers that require initialisation directly
 * 		after reset shall be initialised by the startup code.
 *
 * - PORT218:	All the other registers not mentioned before, shall be
 * 		initialised by the start-up code.
 *
 * PORT043:	The function Port_Init shall avoid glitches and spikes on the
 * 		affected port pins.
 *
 * PORT071:	The Port Driver module’s environment shall call the function
 * 		Port_Init after a reset in order to reconfigure the ports and
 * 		port pins of the MCU.
 *
 * PORT002:	The function Port_Init shall initialize all variables used by
 * 		the PORT driver module to an initial state.
 *
 * PORT003:	The Port Driver module’s environment may also uses the function
 * 		Port_Init to initialize the driver software and reinitialize the
 * 		ports and port pins to another configured state depending on the
 * 		configuration set passed to this function.
 *
 * Note:	In some cases, MCU port control hardware provides an output
 * 		latch for setting the output level on a port pin that may be
 * 		used as a DIO port pin.
 *
 * PORT055:	The function Port_Init shall set the port pin output latch to a
 * 		default level (defined during configuration) before setting the
 * 		port pin direction to output.
 *
 * Requirement PORT055 ensures that the default level is immediately output on
 * the port pin when it is set to an output port pin.
 *
 * Example: On some MCU’s, after a power-on-reset, a DIO configurable port pin
 * will be configured as an input pin. If the required configuration of the port
 * pin is an output pin, then the function Port_Init shall ensure that the
 * default level is set before switching the functionality of the port pin from
 * input to output.
 *
 * PORT105:	If development error detection for the Port Driver module is
 * 		enabled: In case the function Port_Init is called with a NULL
 * 		ConfigPtr and if a variant containing postbuild multiple
 * 		selectable configuration parameters is used (VARIANT-POSTBUILD),
 * 		the function Port_Init shall raise the development error
 * 		PORT_E_PARAM_CONFIG and return without any action.
 *
 * PORT121:	The function Port_Init shall always have a pointer as a
 * 		parameter, even though for the configuration variant
 * 		VARIANT-PRE-COMPILE, no configuration set shall be given.
 * 		In this case, the Port Driver module’s environment shall pass a
 * 		NULL pointer to the function Port_Init.
 *
 * The Port Driver module’s environment shall not call the function Port_Init
 * during a running operation. This shall only apply if there is more than one 
 * caller of the PORT module.
 *
 * Configuration of Port_Init: All port pins and their functions, and alternate
 * functions shall be configured by the configuration tool.
 */
void Port_Init(
  const Port_ConfigType*	ConfigPtr
);

/*
 * PORT141:	Service 0x01
 *
 * PORT063:	The function Port_SetPinDirection shall set the port pin
 * 		direction during runtime.
 *
 * PORT054:	The function Port_SetPinDirection shall be re-entrant if
 * 		accessing different pins independent of a port.
 *
 * PORT086:	The function Port_SetPinDirection shall only be available to the
 * 		user if the pre-compile parameter PortSetPinDirectionApi is set
 * 		to TRUE. If set to FALSE, the function Port_SetPinDirection is
 * 		not available.
 *
 * Configuration of Port_SetPinDirection: All ports and port pins shall be
 * configured by the configuration tool.
 */
#if ( PORT_SET_PIN_DIRECTION_API == STD_ON )
void Port_SetPinDirection(
  Port_PinType		Pin,
  Port_PinDirectionType	Direction
);
#endif

/*
 * PORT142:	Service 0x02
 *
 * PORT060:	The function Port_RefreshPortDirection shall refresh the
 * 		direction of all configured ports to the configured direction
 * 		(PortPinDirection).
 *
 * PORT061:	The function Port_RefreshPortDirection shall exclude those port
 * 		pins from refreshing that are configured as ‘pin direction
 * 		changeable during runtime‘.
 *
 * The configuration tool shall provide names for each configured port pin.
 */
void Port_RefreshPortDirection(
  void
);

/*
 * PORT143:	Service 0x03
 *
 * PORT102: 	The function Port_GetVersionInfo shall return the version
 * 		information of this module. The version information includes:
 * 		- Module Id
 * 		- Vendor Id
 * 		- Vendor specific version numbers.
 *
 * PORT103:	The function Port_GetVersionInfo shall be pre compile time
 * 		configurable On/Off by the configuration parameter
 * 		PortVersionInfoApi.
 *
 * PORT144:	If source code for caller and callee of Port_GetVersionInfo is
 * 		available, the PORT Driver module should realize
 * 		Port_GetVersionInfo as a macro, defined in the module’s header
 * 		file.
 *
 * PORT225:	if Det is enabled, the parameter versioninfo shall be checked
 * 		for being NULL. The error PORT_E_PARAM_POINTER shall be reported
 * 		in case the value is a NULL pointer.
 */
#if ( PORT_VERSION_INFO_API == STD_ON )
#if ( PORT_DEV_ERROR_DETECT == STD_ON )
#define	Port_GetVersionInfo(_vi)	STD_GET_VERSION_INFO(_vi,PORT) \
	else \
	{\
		Det_ReportError(\
			PORT_MODULE_ID,\
			0,\
			PORT_GETVERSIONINFO_SERVICE_ID,\
			PORT_E_PARAM_POINTER\
		);\
	}
#else
#define	Port_GetVersionInfo(_vi)	STD_GET_VERSION_INFO(_vi,PORT)
#endif	/* PORT_DEV_ERROR_DETECT */
#endif	/* PORT_VERSION_INFO_API */

/*
 * PORT145:	Service 0x04
 *
 * PORT125:	The function Port_SetPinMode shall set the port pin mode of the
 * 		referenced pin during runtime.
 *
 * PORT128:	The function Port_SetPinMode shall be re-entrant if accessing
 * 		different pins, independent of a port.
 *
 * PORT223:	If Det is enabled, the function Port_SetPinMode shall return
 * 		PORT_E_MODE_UNCHANGEABLE and return without any action, if the
 * 		parameter PortPinModeChangeable is set to FALSE.
 *
 * Configuration of Port_SetPinMode: All ports and port pins shall be configured
 * by the configuration tool.
 */
#if ( PORT_SET_PIN_MODE_API == STD_ON )
void Port_SetPinMode(
  Port_PinType		Pin,
  Port_PinModeType	Mode
);
#endif

#endif	/* AR_PORT_H */
