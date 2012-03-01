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

#define	DIO_AR_RELEASE_MAJOR_VERSION	4
#define	DIO_AR_RELEASE_MINOR_VERSION	0

#include "Dio.h"

/*
 * DIO106:	The DIO module shall perform Inter Module Checks to avoid
 * 		integration of incompatible files.
 * 		The imported included files shall be checked by preprocessing
 * 		directives.
 * 		The following version numbers shall be verified:
 * 		- <MODULENAME>_AR_RELEASE_MAJOR_VERSION
 * 		- <MODULENAME>_AR_RELEASE_MINOR_VERSION
 * 		Where <MODULENAME> is the module short name of the other
 * 		(external) modules which provide header files included by DIO
 * 		module.
 * 		If the values are not identical to the expected values, an
 * 		error shall be reported.
 */
#if !defined( DIO_AR_MAJOR_VERSION ) || \
    ( DIO_AR_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION )
#error	Dio: version mismatch.
#endif

#include "ee.h"

#ifndef	ARRAY_SIZE
#define	ARRAY_SIZE(_x)	(sizeof(_x)/sizeof((_x)[0]))
#endif

/* Development error macros. */
#if ( DIO_DEV_ERROR_DETECT == STD_ON )

#include "Det.h"
#if defined(USE_DEM)
#include "Dem.h"
#endif

#define VALIDATE(_exp,_api,_err ) \
  if( !(_exp) ) { \
    Det_ReportError(DIO_MODULE_ID,0,_api,_err); \
    return; \
  }

#define VALIDATE_W_RV(_exp,_api,_err,_rv ) \
  if( !(_exp) ) { \
    Det_ReportError(DIO_MODULE_ID,0,_api,_err); \
    return (_rv); \
  }

#else	/* DIO_DEV_ERROR_DETECT */

#define VALIDATE(_exp,_api,_err ) \
  if( !(_exp) ) { \
    return; \
  }
#define VALIDATE_W_RV(_exp,_api,_err,_rv ) \
  if( !(_exp) ) { \
    return (_rv); \
  }
#endif	/* !DIO_DEV_ERROR_DETECT */

/*
 * Type that holds all global data for Mcu
 */
typedef struct
{
  boolean			Init;		/* PORT Driver Initialized? */

  const Dio_ConfigType *	ConfigPtr;	/* Actual Configuration */

} Dio_GlobalType;


/*
 * Global config
 */
Dio_GlobalType Dio_Global =
{
  FALSE,		/* Init		*/
  NULL_PTR,		/* ConfigPtr	*/
};

/*
 * Supported Cores Identifitication Numbers
 */
#define	CORE_CPUID_CORTEX_M4	0x410FC241

/*
 * Core Informations Container Type
 */
typedef struct {
  char		*Name;	/* Core Name String		*/
  uint32	Id;	/* Core Identifier Number	*/
} Dio_CoreInfoType;

/*
 * Supported Cores Array
 */
Dio_CoreInfoType Dio_SupportedCoreArray[] =
{
  {
    "CORE_ARM_CORTEX_M4",	/* .Name	*/
    CORE_CPUID_CORTEX_M4,	/* .Id		*/
  },
};

/*
 * Supported Core Information Retrieval
 */
static Dio_CoreInfoType * Dio_GetSupportedCoreInfo(
  uint32 Id
)
{
  register uint32 i;
  Dio_CoreInfoType *info = NULL;
  for (i = 0; i < ARRAY_SIZE(Dio_SupportedCoreArray); i++) {
    if (Dio_SupportedCoreArray[i].Id == Id) {
      info = &Dio_SupportedCoreArray[i];
    }
  }
  return info;
}

/*
 * Identify the core, just to check that we have support for it.
 */
static boolean Dio_CheckCore( void ) {
  /* NVIC - System Control Block - Register 64: CPUID */
  register uint32 Id = NVIC_CPUID_R;
  Dio_CoreInfoType *info = NULL;
  info = Dio_GetSupportedCoreInfo(Id);
  return (info != NULL);
}

/*
 * Usefull Dio Channel Macros
 */
#define	DIO_CHANNEL_MASK		0x00000007
#define	CHANNEL2MASK(_ch) (uint32)(_ch & DIO_CHANNEL_MASK)

#define	DIO_CHANNEL_MASK_BITS	0x00000003
#define	CHANNEL2PORT(_ch) (uint32)(_ch >> DIO_CHANNEL_MASK_BITS)

#define	GPIO_PORT_PIN_MASK_BITS	0x0000000C
#define	CHANNEL2PORTADDR(_ch) (uint32)( \
  (uint32)GPIO_PORTA_AHB_DATA_BITS_R + \
  (CHANNEL2PORT(_ch) << GPIO_PORT_PIN_MASK_BITS) \
)

#define	PORT_DATA_BIT_0_ADDRESS_MASK	0x00000004
#define	CHANNEL2ADDR(_ch) (uint32)(\
  CHANNEL2PORTADDR(_ch) + (PORT_DATA_BIT_0_ADDRESS_MASK << CHANNEL2MASK(_ch))\
)

#define	SETCHANNELVAL(_ch,_val) \
  (*((volatile uint32 *)CHANNEL2ADDR(_ch))) = (_val << CHANNEL2MASK(_ch))

#define	GETCHANNELVAL(_ch) \
  ((*((volatile uint32 *)CHANNEL2ADDR(_ch))) >> CHANNEL2MASK(_ch))

#define	PORT_DATA_ADDRESS_MASK		0x000003FC
#define	PORT2ADDR(_port) (uint32)( \
  (uint32)GPIO_PORTA_AHB_DATA_BITS_R + \
  (_port << GPIO_PORT_PIN_MASK_BITS) + \
  PORT_DATA_ADDRESS_MASK\
)

#define	SETPORTVAL(_port, _val) \
  (*((volatile uint32 *)PORT2ADDR(_port))) = _val

#define	GETPORTVAL(_port) \
  (*((volatile uint32 *)PORT2ADDR(_port)))

/*
 * Dio_ReadChannel implementation
 */
Dio_LevelType Dio_ReadChannel(
  Dio_ChannelType	ChannelId
)
{
  register uint32			p, c;
  register EE_UREG			f;
  register boolean			init;
  register const Dio_ConfigType *	cfgptr;

  f = EE_hal_suspendIRQ();
  init = Dio_Global.Init;
  cfgptr = Dio_Global.ConfigPtr;
  EE_hal_resumeIRQ(f);

  VALIDATE_W_RV(
    ( init == TRUE ),
    DIO_READCHANNEL_ID,
    DIO_E_PARAM_CONFIG,
    STD_LOW
  );

  VALIDATE_W_RV(
    ( ChannelId < DIO_CHANNELS_NUMBER ),
    DIO_READCHANNEL_ID,
    DIO_E_PARAM_INVALID_CHANNEL_ID,
    STD_LOW
  );

  for (p = 0; (p < cfgptr->DioNumberOfPorts) && init; p++) {
    if (CHANNEL2PORT(ChannelId) == cfgptr->DioPorts[p].DioPortId) {
      for (c = 0; (c < cfgptr->DioPorts[p].DioNumberOfChannels) && init; c++) {
	if (ChannelId == cfgptr->DioPorts[p].DioChannels[c]) {
	  init = FALSE;
	}
      }
    }
  }

  VALIDATE_W_RV(
    ( init == FALSE ),
    DIO_READCHANNEL_ID,
    DIO_E_PARAM_INVALID_CHANNEL_ID,
    STD_LOW
  );

  return GETCHANNELVAL(ChannelId);
}

/*
 * Dio_WriteChannel implementation
 */
void Dio_WriteChannel(
  Dio_ChannelType	ChannelId,
  Dio_LevelType		Level
)
{
  register uint32			p, c;
  register EE_UREG			f;
  register boolean			init;
  register const Dio_ConfigType *	cfgptr;

  f = EE_hal_suspendIRQ();
  init = Dio_Global.Init;
  cfgptr = Dio_Global.ConfigPtr;
  EE_hal_resumeIRQ(f);

  VALIDATE(
    ( init == TRUE ),
    DIO_WRITECHANNEL_ID,
    DIO_E_PARAM_CONFIG
  );

  VALIDATE(
    ( ChannelId < DIO_CHANNELS_NUMBER ),
    DIO_WRITECHANNEL_ID,
    DIO_E_PARAM_INVALID_CHANNEL_ID
  );

  for (p = 0; (p < cfgptr->DioNumberOfPorts) && init; p++) {
    if (CHANNEL2PORT(ChannelId) == cfgptr->DioPorts[p].DioPortId) {
      for (c = 0; (c < cfgptr->DioPorts[p].DioNumberOfChannels) && init; c++) {
	if (ChannelId == cfgptr->DioPorts[p].DioChannels[c]) {
	  init = FALSE;
	}
      }
    }
  }

  VALIDATE(
    ( init == FALSE ),
    DIO_WRITECHANNEL_ID,
    DIO_E_PARAM_INVALID_CHANNEL_ID
  );

  SETCHANNELVAL(ChannelId, Level);
}

/*
 * Dio_ReadPort implementation
 */
Dio_PortLevelType Dio_ReadPort(
  Dio_PortType		PortId
)
{
  register uint32			p;
  register EE_UREG			f;
  register boolean			init;
  register const Dio_ConfigType *	cfgptr;

  f = EE_hal_suspendIRQ();
  init = Dio_Global.Init;
  cfgptr = Dio_Global.ConfigPtr;
  EE_hal_resumeIRQ(f);

  VALIDATE_W_RV(
    ( init == TRUE ),
    DIO_READPORT_ID,
    DIO_E_PARAM_CONFIG,
    STD_LOW
  );

  VALIDATE_W_RV(
    ( PortId < DIO_PORTS_NUMBER ),
    DIO_READPORT_ID,
    DIO_E_PARAM_INVALID_PORT_ID,
    STD_LOW
  );

  for (p = 0; (p < cfgptr->DioNumberOfPorts) && init; p++) {
    if (PortId == cfgptr->DioPorts[p].DioPortId) {
      init = FALSE;
    }
  }

  VALIDATE_W_RV(
    ( init == FALSE ),
    DIO_READPORT_ID,
    DIO_E_PARAM_INVALID_PORT_ID,
    STD_LOW
  );

  return GETPORTVAL(PortId);
}

/*
 * Dio_WritePort implementation
 */
void Dio_WritePort(
  Dio_PortType		PortId,
  Dio_PortLevelType	Level
)
{
  register uint32			p;
  register EE_UREG			f;
  register boolean			init;
  register const Dio_ConfigType *	cfgptr;

  f = EE_hal_suspendIRQ();
  init = Dio_Global.Init;
  cfgptr = Dio_Global.ConfigPtr;
  EE_hal_resumeIRQ(f);

  VALIDATE(
    ( init == TRUE ),
    DIO_WRITEPORT_ID,
    DIO_E_PARAM_CONFIG
  );

  VALIDATE(
    ( PortId < DIO_PORTS_NUMBER ),
    DIO_WRITEPORT_ID,
    DIO_E_PARAM_INVALID_PORT_ID
  );

  for (p = 0; (p < cfgptr->DioNumberOfPorts) && init; p++) {
    if (PortId == cfgptr->DioPorts[p].DioPortId) {
      init = FALSE;
    }
  }

  VALIDATE(
    ( init == FALSE ),
    DIO_WRITEPORT_ID,
    DIO_E_PARAM_INVALID_PORT_ID
  );

  SETPORTVAL(PortId, Level);
}

/*
 * Dio_ReadChannelGroup implementation
 */
Dio_PortLevelType Dio_ReadChannelGroup(
  const Dio_ChannelGroupType*	ChannelGroupIdPtr
)
{
  register uint32			p;
  register EE_UREG			f;
  register boolean			init;
  register const Dio_ConfigType *	cfgptr;

  f = EE_hal_suspendIRQ();
  init = Dio_Global.Init;
  cfgptr = Dio_Global.ConfigPtr;
  EE_hal_resumeIRQ(f);

  VALIDATE_W_RV(
    ( init == TRUE ),
    DIO_READCHANNELGROUP_ID,
    DIO_E_PARAM_CONFIG,
    STD_LOW
  );

  VALIDATE_W_RV(
    ( ChannelGroupIdPtr != NULL_PTR ),
    DIO_READCHANNELGROUP_ID,
    DIO_E_PARAM_POINTER,
    STD_LOW
  );

  VALIDATE_W_RV(
    ( ChannelGroupIdPtr->port < DIO_PORTS_NUMBER ),
    DIO_READCHANNELGROUP_ID,
    DIO_E_PARAM_INVALID_PORT_ID,
    STD_LOW
  );

  for (p = 0; (p < cfgptr->DioNumberOfPorts) && init; p++) {
    if (ChannelGroupIdPtr->port == cfgptr->DioPorts[p].DioPortId) {
      init = FALSE;
    }
  }

  VALIDATE_W_RV(
    ( init == FALSE ),
    DIO_READCHANNELGROUP_ID,
    DIO_E_PARAM_INVALID_PORT_ID,
    STD_LOW
  );

  return (
    (GETPORTVAL(ChannelGroupIdPtr->port) &  ChannelGroupIdPtr->mask) >>
    ChannelGroupIdPtr->offset
  );
}

/*
 * Dio_WriteChannelGroup implementation
 */
void Dio_WriteChannelGroup(
  const Dio_ChannelGroupType*	ChannelGroupIdPtr,
  Dio_PortLevelType		Level
)
{
  register uint32			p;
  register EE_UREG			f;
  register boolean			init;
  register const Dio_ConfigType *	cfgptr;

  f = EE_hal_suspendIRQ();
  init = Dio_Global.Init;
  cfgptr = Dio_Global.ConfigPtr;
  EE_hal_resumeIRQ(f);

  VALIDATE(
    ( init == TRUE ),
    DIO_WRITECHANNELGROUP_ID,
    DIO_E_PARAM_CONFIG
  );

  VALIDATE(
    ( ChannelGroupIdPtr != NULL_PTR ),
    DIO_WRITECHANNELGROUP_ID,
    DIO_E_PARAM_POINTER
  );

  VALIDATE(
    ( ChannelGroupIdPtr->port < DIO_PORTS_NUMBER ),
    DIO_WRITECHANNELGROUP_ID,
    DIO_E_PARAM_INVALID_PORT_ID
  );

  for (p = 0; (p < cfgptr->DioNumberOfPorts) && init; p++) {
    if (ChannelGroupIdPtr->port == cfgptr->DioPorts[p].DioPortId) {
      init = FALSE;
    }
  }

  VALIDATE(
    ( init == FALSE ),
    DIO_WRITECHANNELGROUP_ID,
    DIO_E_PARAM_INVALID_PORT_ID
  );

  SETPORTVAL(
    ChannelGroupIdPtr->port,
    ((Level << ChannelGroupIdPtr->offset) & ChannelGroupIdPtr->mask)
  );
}

/*
 * Dio_Init implementation.
 */
void Dio_Init(
  const Dio_ConfigType *	ConfigPtr
)
{

  VALIDATE( ( ConfigPtr != NULL), DIO_INIT_SERVICE_ID, DIO_E_PARAM_CONFIG );

  VALIDATE(
    ( Dio_CheckCore() != FALSE), DIO_INIT_SERVICE_ID, DIO_E_PARAM_CONFIG
  );

  Dio_Global.ConfigPtr = ConfigPtr;
  Dio_Global.Init = TRUE;

}

/*
 * Dio_FlipChannel implementation
 */
#if ( DIO_FLIP_CHANNEL_API == STD_ON )
Dio_LevelType Dio_FlipChannel(
  Dio_ChannelType		ChannelId
)
{
  register uint32			p, c;
  register EE_UREG			f;
  register boolean			init;
  register const Dio_ConfigType *	cfgptr;
  register Dio_LevelType		lvl;

  f = EE_hal_suspendIRQ();
  init = Dio_Global.Init;
  cfgptr = Dio_Global.ConfigPtr;
  EE_hal_resumeIRQ(f);

  VALIDATE_W_RV(
    ( init == TRUE ),
    DIO_READCHANNEL_ID,
    DIO_E_PARAM_CONFIG,
    STD_LOW
  );

  VALIDATE_W_RV(
    ( ChannelId < DIO_CHANNELS_NUMBER ),
    DIO_READCHANNEL_ID,
    DIO_E_PARAM_INVALID_CHANNEL_ID,
    STD_LOW
  );

  for (p = 0; (p < cfgptr->DioNumberOfPorts) && init; p++) {
    if (CHANNEL2PORT(ChannelId) == cfgptr->DioPorts[p].DioPortId) {
      for (c = 0; (c < cfgptr->DioPorts[p].DioNumberOfChannels) && init; c++) {
	if (ChannelId == cfgptr->DioPorts[p].DioChannels[c]) {
	  init = FALSE;
	}
      }
    }
  }

  VALIDATE_W_RV(
    ( init == FALSE ),
    DIO_READCHANNEL_ID,
    DIO_E_PARAM_INVALID_CHANNEL_ID,
    STD_LOW
  );

  f = EE_hal_suspendIRQ();
  lvl = GETCHANNELVAL(ChannelId);
  
  if ( lvl == STD_LOW )
    SETCHANNELVAL(ChannelId, STD_HIGH);
  else
    SETCHANNELVAL(ChannelId, STD_LOW);
  EE_hal_resumeIRQ(f);
  
  return lvl;
}
#endif
