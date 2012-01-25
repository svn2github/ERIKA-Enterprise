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
 * AUTOSAR DIO Driver Header File.
 *
 * The DIO Driver abstracts the access to the microcontroller's hardware pins.
 * Furthermore, it allows the grouping of those pins.
 *
 * The Dio SWS shall define synchronous read/write services.
 *
 * DIO005:	The Dio module’s read and write services shall ensure for all
 * 		services, that the data is consistent (Interruptible
 * 		read-modify-write sequences are not allowed).
 *
 * DIO089:	Values used by the DIO Driver for the software level of Channels
 * 		are either STD_HIGH or STD_LOW.
 *
 * DIO128:	A general-purpose digital IO pin represents a DIO channel.
 *
 * DIO061:	The Dio module shall not provide APIs for overall configuration
 * 		and initialization of the port structure which is used in the
 * 		Dio module. These actions are done by the PORT Driver Module.
 *
 * DIO063:	The Dio module shall adapt its configuration and usage to the
 * 		microcontroller and ECU.
 *
 * DIO001:	The Dio module shall not provide an interface for initialization
 * 		of the hardware. The Port Driver performs this.
 *
 * DIO002:	The PORT driver shall provide the reconfiguration of the port
 * 		pin direction during runtime.
 *
 * DIO102:	The Dio module’s user shall only use the Dio functions after the
 * 		Port Driver has been initialized. Otherwise the Dio module will
 * 		exhibit undefined behavior.
 *
 * DIO127:	The Port module shall configure a DIO channel as input or output
 * 		See DIO001 and DIO002.
 *
 * DIO053:	In the DIO Driver, it shall be possible to group several DIO
 * 		channels by hardware (typically controlled by one hardware
 * 		register) to represent a DIO port.
 *
 * Note:	The single DIO channel levels inside a DIO port represent a bit
 * 		in the DIO port value, depending on their position inside the
 * 		port.
 *
 * DIO056:	A channel group is a formal logical combination of several
 * 		adjoining DIO channels within a DIO port.
 *
 * DIO051:	The Dio module shall not buffer data when providing read and
 * 		write services.
 *
 * Author:  2011,  Giuseppe Serano
 */


#ifndef	DIO_H
#define	DIO_H

/*
 * Vendor Id form document:
 * [STD_HIS_SUPPLIER_IDS] HIS Software Supplier Identifications
 * http://www.automotive--his.de/his--ergebnisse.htm (broken link)
 */
#define	DIO_VENDOR_ID		0

/*
 * Module Id (101) from document:
 * List of Basic Software Modules
 * V1.5.0
 * R4.0 Rev 2
 */
#define	DIO_MODULE_ID		120

#define	DIO_SW_MAJOR_VERSION	1
#define	DIO_SW_MINOR_VERSION	0
#define	DIO_SW_PATCH_VERSION	0

#define	DIO_AR_MAJOR_VERSION	4
#define	DIO_AR_MINOR_VERSION	0
#define	DIO_AR_PATCH_VERSION	2

/*
 * DIO170:	Dio.h shall include Std_Types.h.
 */
#include "Std_Types.h"

/*
 * DIO065:	The Dio module shall detect the following errors and exceptions
 * 		depending on its build version (development/production mode).
 */

/*
 * DIO175:	Invalid channel name requested
 */
#define	DIO_E_PARAM_INVALID_CHANNEL_ID	0x0A

/*
 * DIO176:	API service called with “NULL pointer” parameter
 */
#define	DIO_E_PARAM_CONFIG		0x10

/*
 * DIO177:	Invalid port name requested
 */
#define	DIO_E_PARAM_INVALID_PORT_ID	0x14

/*
 * DIO178:	Invalid ChannelGroup passed
 */
#define	DIO_E_PARAM_INVALID_GROUP	0x1F

/*
 * DIO188:	API service called with a NULL pointer. In case of this error,
 * 		the API service shall return immediately without any further
 * 		action, beside reporting this development error.
 */
#define	DIO_E_PARAM_POINTER		0x20

/*
 * DIO182:	Dio_ChannelType
 *
 * DIO015:	Parameters of type Dio_ChannelType contain the numeric ID of a
 * 		DIO channel.
 *
 * DIO180:	The mapping of the ID is implementation specific but not
 * 		configurable.
 *
 * DIO017:	For parameter values of type Dio_ChannelType, the Dio’s user
 * 		shall use the symbolic names provided by the configuration
 * 		description.
 *
 * Furthermore, DIO103 applies to the type Dio_ChannelType.
 */
typedef	uint32	Dio_ChannelType;

/*
 * DIO183:	Dio_PortType
 *
 * DIO018:	Parameters of type Dio_PortType contain the numeric ID of a DIO
 * 		port.
 *
 * DIO181:	The mapping of ID is implementation specific but not
 * 		configurable.
 *
 * DIO020:	For parameter values of type Dio_PortType, the user shall use
 * 		the symbolic names provided by the configuration description.
 *
 * Furthermore, DIO103 applies to the type Dio_PortType.
 */
typedef	uint32	Dio_PortType;

/*
 * DIO184:	Dio_ChannelGroupType
 *
 * DIO021:	Dio_ChannelGroupType is the type for the definition of a channel
 * 		group, which consists of several adjoining channels within a
 * 		port.
 *
 * DIO022:	For parameter values of type Dio_ChannelGroupType, the user
 * 		shall use the symbolic names provided by the configuration
 * 		description.
 *
 * Furthermore, DIO056 applies to the type Dio_ChannelGroupType.
 */
typedef struct
{

  /*
   * This element mask which defines the positions of the channel group.
   */
  uint32	mask;
  /*
   * This element shall be the position of the Channel Group on the port,
   * counted from the LSB.
   */
  uint8		offset;
  /*
   * This shall be the port on which the Channel group is defined.
   */
  Dio_PortType	port;

} Dio_ChannelGroupType;

/*
 * DIO185:	Dio_LevelType
 *
 * DIO023:	Dio_LevelType is the type for the possible levels that a DIO
 * 		channel can have (input or output).
 */
typedef	uint8	Dio_LevelType;

/*
 * DIO186:	Dio_PortLevelType
 *
 * DIO024:	Dio_PortLevelType is the type for the value of a DIO port.
 *
 * Furthermore, DIO103 applies to the type Dio_PortLevelType.
 *
 * NOTE:	If the µC owns ports of different port widths
 * 		(e.g. 4, 8,16...Bit) Dio_PortLevelType inherits the size of the
 * 		largest port.
 */
typedef	uint32	Dio_PortLevelType;

/*
 * DIO168:	Dio.h shall include Dio_Cfg.h for the API pre-compiler switches.
 *
 * DIO169:	Dio.c has access to the Dio_Cfg.h via the implicitly include
 * 		through the Dio.h file.
 */
#include "Dio_Cfg.h"

/*
 * DIO187:	Dio_ConfigType
 *
 * DIO164:	Dio_ConfigType is the type for all post-build configurable
 * 		parameters of the DIO driver.
 */
extern Dio_ConfigType Dio_Config[];

/*
 * Service ID's
 */
#define	DIO_READCHANNEL_ID		0x00
#define	DIO_WRITECHANNEL_ID		0x01
#define	DIO_READPORT_ID			0x02
#define	DIO_WRITEPORT_ID		0x03
#define	DIO_READCHANNELGROUP_ID		0x04
#define	DIO_WRITECHANNELGROUP_ID	0x05
#define	DIO_INIT_ID			0x10
#define	DIO_FLIPCHANNEL_ID		0x11
#define	DIO_GETVERSIONINFO_ID		0x12

/*
 * DIO133:	Service 0x00
 *
 * DIO027:	The Dio_ReadChannel function shall return the value of the
 * 		specified DIO channel.
 *
 * Regarding the return value of the Dio_ReadChannel function, the requirements
 * (DIO083) and (DIO084) are applicable.
 *
 * Furthermore, the requirements DIO005, DIO118 and DIO026 are applicable to the
 * Dio_ReadChannel function.
 */
Dio_LevelType Dio_ReadChannel(
  Dio_ChannelType	ChannelId
);

/*
 * DIO134:	Service	0x01
 *
 * DIO028:	If the specified channel is configured as an output channel, the
 * 		Dio_WriteChannel function shall set the specified Level for the
 * 		specified channel.
 *
 * DIO029:	If the specified channel is configured as an input channel, the
 * 		Dio_WriteChannel function shall have no influence on the
 * 		physical output.
 *
 * DIO079:	If the specified channel is configured as an input channel, the
 * 		Dio_WriteChannel function shall have no influence on the result
 * 		of the next Read-Service.
 *
 * Furthermore, the requirements DIO005, DIO119 and DIO026 are applicable to the
 * Dio_WriteChannel function.
 */
void Dio_WriteChannel(
  Dio_ChannelType	ChannelId,
  Dio_LevelType		Level
);

/*
 * DIO135:	Service 0x02
 *
 * DIO031:	The Dio_ReadPort function shall return the level of all channels
 * 		of that port.
 *
 * DIO104:	When reading a port which is smaller than the Dio_PortType using
 * 		the Dio_ReadPort function (see DIO103), the function shall set
 * 		the bits corresponding to undefined port pins to 0.
 *
 * Furthermore, the requirements DIO005, DIO118 and DIO026 are applicable to the
 * Dio_ReadPort function.
 */
Dio_PortLevelType Dio_ReadPort(
  Dio_PortType		PortId
);

/*
 * DIO136:	Service 0x03
 *
 * DIO034:	The Dio_WritePort function shall set the specified value for the
 * 		specified port.
 *
 * DIO035:	When the Dio_WritePort function is called, DIO Channels that are
 * 		configured as input shall remain unchanged.
 *
 * DIO105:	When writing a port which is smaller than the Dio_PortType using
 * 		the Dio_WritePort function (see [DIO103]), the function shall
 * 		ignore the MSB.
 *
 * DIO108:	The Dio_WritePort function shall have no effect on channels
 * 		within this port which are configured as input channels.
 *
 * Furthermore, the requirements DIO005, DIO119 and DIO026 are applicable to the
 * Dio_WritePort function.
 */
void Dio_WritePort(
  Dio_PortType		PortId,
  Dio_PortLevelType	Level
);

/*
 * DIO137:	Service 0x04
 *
 * DIO037:	The Dio_ReadChannelGroup function shall read a subset of the
 * 		adjoining bits of a port (channel group).
 *
 * DIO092:	The Dio_ReadChannelGroup function shall do the masking of the
 * 		channel group.
 *
 * DIO093:	The Dio_ReadChannelGroup function shall do the shifting so that
 * 		the values read by the function are aligned to the LSB.
 *
 * Furthermore, the requirements DIO005, DIO056, DIO083, DIO084, DIO118 and
 * DIO026 are applicable to the Dio_ReadChannelGroup function.
 */
Dio_PortLevelType Dio_ReadChannelGroup(
  const Dio_ChannelGroupType*	ChannelGroupIdPtr
);

/*
 * DIO138:	Service 0x05
 *
 * DIO039:	The Dio_WriteChannelGroup function shall set a subset of the
 * 		adjoining bits of a port (channel group) to a specified level.
 *
 * DIO040:	The Dio_WriteChannelGroup shall not change the remaining
 * 		channels of the port and channels which are configured as input.
 *
 * DIO090:	The Dio_WriteChannelGroup function shall do the masking of the
 * 		channel group.
 *
 * DIO091:	The function Dio_WriteChannelGroup shall do the shifting so that
 * 		the values written by the function are aligned to the LSB.
 *
 * Furthermore, the requirements DIO005, DIO056, DIO119 and DIO026 are
 * applicable for the Dio_WriteChannelGroup function.
 */
void Dio_WriteChannelGroup(
  const Dio_ChannelGroupType*	ChannelGroupIdPtr,
  Dio_PortLevelType		Level
);

/*
 * DIO165:	Service 0x10
 *
 * DIO166:	The Dio_Init function shall initialize all global variables of
 * 		the DIO module.
 *
 * DIO167:	When development error detection is enabled for the DIO module:
 * 		The function Dio_Init shall check that the parameter ConfigPtr
 * 		is not NULL. If this error is detected, the function Dio_Init
 * 		shall not execute the initialization but raise the development
 * 		error DIO_E_PARAM_CONFIG.
 */
void Dio_Init(
  const Dio_ConfigType*		ConfigPtr
);

/*
 * DIO190:	Service 0x11
 *
 * DIO191:	If the specified channel is configured as an output channel, the
 * 		Dio_FlipChannel function shall read level of the channel
 * 		(requirements DIO083 & DIO084 are applicable) and invert it,
 * 		then write the inverted level to the channel.
 * 		The return value shall be the inverted level of the specified
 * 		channel.
 *
 * DIO192:	If the specified channel is configured as an input channel, the
 * 		Dio_FlipChannel function shall have no influence on the physical
 * 		output.
 * 		The return value shall be the level of the specified channel.
 *
 * DIO193:	If the specified channel is configured as an input channel, the
 * 		Dio_FlipChannel function shall have no influence on the result
 * 		of the next Read-Service.
 *
 * Furthermore, the requirements DIO005, DIO119 and DIO026 are applicable to the
 * Dio_FlipChannel function.
 */
#if ( DIO_FLIP_CHANNEL_API == STD_ON )
Dio_LevelType Dio_FlipChannel(
  Dio_ChannelType		ChannelId
);
#endif

/*
 * DIO139:	Service 0x12
 *
 * DIO123:	The Dio_GetVersionInfo function shall return the version
 * 		information of this module. The version information includes:
 * 		- Module Id
 * 		- Vendor Id
 * 		- Vendor specific version numbers.
 *
 * DIO126:	If source code for caller and callee is available, the module
 * 		Dio should realize the function Dio_GetVersionInfo as a macro
 * 		defined in the module’s header file.
 *
 * DIO124:	The Dio_GetVersionInfo function shall be pre-compile time
 * 		configurable (On/Off) by the configuration parameter
 * 		DioVersionInfoApi.
 *
 * DIO189:	If DET is enabled for the DIO Driver module, the function
 * 		Dio_GetVersionInfo shall raise DIO_E_PARAM_POINTER, if the
 * 		argument is NULL pointer and return without any action.
 */
#if ( DIO_VERSION_INFO_API == STD_ON )
#if ( DIO_DEV_ERROR_DETECT == STD_ON )
#define	Dio_GetVersionInfo(_vi)	STD_GET_VERSION_INFO(_vi,DIO) \
	else \
	{\
		Det_ReportError(\
			DIO_MODULE_ID,\
			0,\
			DIO_GETVERSIONINFO_SERVICE_ID,\
			DIO_E_PARAM_POINTER\
		);\
	}
#else
#define	Dio_GetVersionInfo(_vi)	STD_GET_VERSION_INFO(_vi,DIO)
#endif	/* DIO_DEV_ERROR_DETECT */
#endif	/* DIO_VERSION_INFO_API */

#endif	/* DIO_H */
