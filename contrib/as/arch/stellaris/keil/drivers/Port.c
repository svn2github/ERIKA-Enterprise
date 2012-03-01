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

#define	PORT_AR_RELEASE_MAJOR_VERSION	4
#define	PORT_AR_RELEASE_MINOR_VERSION	0

#include "Port.h"

/*
 * PORT114:	For included (external) header files:
 * 		- <MODULENAME>_AR_ RELEASE_MAJOR_VERSION
 * 		- <MODULENAME>_AR_ RELEASE_MINOR_VERSION
 * 		shall be verified.
 */
#if !defined( PORT_AR_MAJOR_VERSION ) || \
    ( PORT_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION )
#error	Port: version mismatch.
#endif

#include "ee.h"

#ifndef	ARRAY_SIZE
#define	ARRAY_SIZE(_x)	(sizeof(_x)/sizeof((_x)[0]))
#endif

/* Development error macros. */
#if ( PORT_DEV_ERROR_DETECT == STD_ON )

#include "Det.h"
#if defined(USE_DEM)
#include "Dem.h"
#endif

#define VALIDATE(_exp,_api,_err ) \
  if( !(_exp) ) { \
    Det_ReportError(PORT_MODULE_ID,0,_api,_err); \
    return; \
  }

#define VALIDATE_W_RV(_exp,_api,_err,_rv ) \
  if( !(_exp) ) { \
    Det_ReportError(PORT_MODULE_ID,0,_api,_err); \
    return (_rv); \
  }

#else	/* PORT_DEV_ERROR_DETECT */

#define VALIDATE(_exp,_api,_err ) \
  if( !(_exp) ) { \
    return; \
  }
#define VALIDATE_W_RV(_exp,_api,_err,_rv ) \
  if( !(_exp) ) { \
    return (_rv); \
  }
#endif	/* !PORT_DEV_ERROR_DETECT */

/*
 * Type that holds all global data for Port Driver
 */
typedef struct
{
  boolean			Init;		/* PORT Driver Initialized? */

  const Port_ConfigType *	ConfigPtr;	/* Actual Configuration */

} Port_GlobalType;


// Global config
Port_GlobalType Port_Global =
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
} Port_CoreInfoType;

/*
 * Supported Cores Array
 */
Port_CoreInfoType Port_SupportedCoreArray[] =
{
  {
    "CORE_ARM_CORTEX_M4",	/* .Name	*/
    CORE_CPUID_CORTEX_M4,	/* .Id		*/
  },
};

/*
 * Supported Core Information Retrieval
 */
static Port_CoreInfoType * Port_GetSupportedCoreInfo(
  uint32 Id
)
{
  register uint32 i;
  Port_CoreInfoType *info = NULL;
  for (i = 0; i < ARRAY_SIZE(Port_SupportedCoreArray); i++) {
    if (Port_SupportedCoreArray[i].Id == Id) {
      info = &Port_SupportedCoreArray[i];
    }
  }
  return info;
}

/*
 * Identify the core, just to check that we have support for it.
 */
static boolean Port_CheckCore( void ) {
  /* NVIC - System Control Block - Register 64: CPUID */
  register uint32 Id = NVIC_CPUID_R;
  Port_CoreInfoType *info = NULL;
  info = Port_GetSupportedCoreInfo(Id);
  return (info != NULL);
}

/*
 * Usefull Port Pin Macros
 */
#define	PORT_PIN_MASK		0x00000007
#define	PIN2MASK(_pin) (uint32)(_pin & PORT_PIN_MASK)

#define	PORT_PIN_MASK_BITS	0x00000003
#define	PIN2PORT(_pin) (uint32)(_pin >> PORT_PIN_MASK_BITS)

#define	GPIO_PORT_PIN_MASK_BITS	0x0000000C
#define	PIN2PORTADDR(_pin) (uint32)( \
  (uint32)GPIO_PORTA_AHB_DATA_BITS_R + \
  (PIN2PORT(_pin) << GPIO_PORT_PIN_MASK_BITS) \
)

#define	PORT_DATA_BIT_0_ADDRESS_MASK	0x00000004
#define	PIN2ADDR(_pin) (uint32)(\
  PIN2PORTADDR(_pin) + (PORT_DATA_BIT_0_ADDRESS_MASK << PIN2MASK(_pin))\
)

#define	SETPINVAL(_pin,_val) \
  (*((volatile uint32 *)PIN2ADDR(_pin))) = (_val << PIN2MASK(_pin))

#define	GETPINVAL(_pin) \
  ((*((volatile uint32 *)PIN2ADDR(_pin))) >> PIN2MASK(_pin))

#define	SETPINREGVAL(_pin,_val,_ofs) \
  if ( _val == STD_OFF ) \
    (*((volatile uint32 *)(PIN2PORTADDR(_pin) + _ofs))) &= \
      ~(_val << PIN2MASK(_pin)); \
  else \
    (*((volatile uint32 *)(PIN2PORTADDR(_pin) + _ofs))) |= \
      (_val << PIN2MASK(_pin))


#define	PORT_PIN_PMC_MASK_BITS		0x00000004

#define	GPIO_PORT_DIR_R_OFFSET		0x00000400
#define	GPIO_PORT_AFSEL_R_OFFSET	0x00000420
#define	GPIO_PORT_DR2R_R_OFFSET		0x00000500
#define	GPIO_PORT_DR4R_R_OFFSET		0x00000504
#define	GPIO_PORT_DR8R_R_OFFSET		0x00000508
#define	GPIO_PORT_ODR_R_OFFSET		0x0000050C
#define	GPIO_PORT_PUR_R_OFFSET		0x00000510
#define	GPIO_PORT_PDR_R_OFFSET		0x00000514
#define	GPIO_PORT_SLR_R_OFFSET		0x00000518
#define	GPIO_PORT_DEN_R_OFFSET		0x0000051C
#define	GPIO_PORT_AMSEL_R_OFFSET	0x00000528
#define	GPIO_PORT_CTL_R_OFFESET		0x0000052C

#define	SETPINDIR(_pin,_dir)	SETPINREGVAL(_pin,_dir,GPIO_PORT_DIR_R_OFFSET)
#define	SETPINAFSEL(_pin,_val)	SETPINREGVAL(_pin,_val,GPIO_PORT_AFSEL_R_OFFSET)
#define	SETPINDR2R(_pin,_val)	SETPINREGVAL(_pin,_val,GPIO_PORT_DR2R_R_OFFSET)
#define	SETPINDR4R(_pin,_val)	SETPINREGVAL(_pin,_val,GPIO_PORT_DR4R_R_OFFSET)
#define	SETPINDR8R(_pin,_val)	SETPINREGVAL(_pin,_val,GPIO_PORT_DR8R_R_OFFSET)
#define	SETPINODR(_pin,_val)	SETPINREGVAL(_pin,_val,GPIO_PORT_ODR_R_OFFSET)
#define	SETPINPUR(_pin,_val)	SETPINREGVAL(_pin,_val,GPIO_PORT_PUR_R_OFFSET)
#define	SETPINPDR(_pin,_val)	SETPINREGVAL(_pin,_val,GPIO_PORT_PDR_R_OFFSET)
#define	SETPINSLR(_pin,_val)	SETPINREGVAL(_pin,_val,GPIO_PORT_SLR_R_OFFSET)
#define	SETPINDEN(_pin,_val)	SETPINREGVAL(_pin,_val,GPIO_PORT_DEN_R_OFFSET)
#define	SETPINAMSEL(_pin,_val)	SETPINREGVAL(_pin,_val,GPIO_PORT_AMSEL_R_OFFSET)

#define	SETPINPMC(_pin,_pmc)	\
  (*((volatile uint32 *)(PIN2PORTADDR(_pin) + GPIO_PORT_CTL_R_OFFESET))) &= \
  ~(PORT_PIN_HW_CFG_PMC_M << (PIN2MASK(_pin) * PORT_PIN_PMC_MASK_BITS)); \
  (*((volatile uint32 *)(PIN2PORTADDR(_pin) + GPIO_PORT_CTL_R_OFFESET))) |= \
  ((_pmc & PORT_PIN_HW_CFG_PMC_M) << (PIN2MASK(_pin) * PORT_PIN_PMC_MASK_BITS))

/*
 * Port Pin Mode Hardware Configuration.
 */
static void Port_SetPortPinHWMode(
  Port_PinType			Pin,
  Port_PinModeConfType *	ConfigPtr
)
{
  register EE_UREG	flag;
  register uint32	mode;

  /* Starts Atomic Section. */
  flag = EE_hal_suspendIRQ();

  mode = ConfigPtr->PortPinModeHWConfig;

  /* Sets-up Analog Mode Select */
  if ( mode & PORT_PIN_HW_CFG_AMSEL ) {
    SETPINDEN(Pin, STD_OFF);
    SETPINAMSEL(Pin, STD_ON);
  }
  else {

    SETPINAMSEL(Pin, STD_OFF);

    /* Sets-up Alternate Function Select */
    if ( mode & PORT_PIN_HW_CFG_AFSEL ) {
      SETPINPMC(Pin, mode);
      SETPINAFSEL(Pin, STD_ON);
    }
    else
      SETPINAFSEL(Pin, STD_OFF);

    /* Sets-up Strenght Drive Select */
    if ( mode & PORT_PIN_HW_CFG_DR2R ) {
      SETPINDR2R(Pin, STD_ON);
      SETPINSLR(Pin, STD_OFF);
    }
    else if ( mode & PORT_PIN_HW_CFG_DR4R ) {
      SETPINDR4R(Pin, STD_ON);
      SETPINSLR(Pin, STD_OFF);
    }
    else if ( mode & PORT_PIN_HW_CFG_DR8R ) {

      SETPINDR8R(Pin, STD_ON);

      /* Sets-up Slew-rate Control */
      if ( mode & PORT_PIN_HW_CFG_SLR )
	SETPINSLR(Pin, STD_ON);
      else
	SETPINSLR(Pin, STD_OFF);

    } /* DR8R */

    /* Sets-up Open Drain */
    if ( mode & PORT_PIN_HW_CFG_ODR )
      SETPINODR(Pin, STD_ON);
    else {

      SETPINODR(Pin, STD_OFF);

      /* Sets-up Pull-Up */
      if ( mode & PORT_PIN_HW_CFG_PUR )
	SETPINPUR(Pin, STD_ON);
      else
	SETPINPUR(Pin, STD_OFF);

      /* Sets-up Pull-Down */
      if ( mode & PORT_PIN_HW_CFG_PDR )
	SETPINPDR(Pin, STD_ON);
      else
	SETPINPDR(Pin, STD_OFF);

    } /* !(Open Drain) */

    /* Sets-up Digital Enable */
    if ( mode & PORT_PIN_HW_CFG_DEN )
      SETPINDEN(Pin, STD_ON);
    else
      SETPINDEN(Pin, STD_OFF);

  }	/* !(Analog Mode Select) */

  /* Ends Atomic Section. */
  EE_hal_resumeIRQ(flag);

}

/*
 * Port Pin Initialization.
 */
static void Port_InitPortPin(
  Port_PinConfType *	ConfigPtr
)
{
  register uint32 port;
  register uint32 mode;

  /* Sets-up Port Mask */
  port = (uint32) (SYSCTL_RCGCGPIO_R0 << PIN2PORT(ConfigPtr->PortPinId));

  /* Sets Advanced High-Performance Bus Memory Access for the Port Module */
  SYSCTL_GPIOHBCTL_R |= port;

  /* Enables GPIO Port Module in Run-Mode */
  SYSCTL_RCGCGPIO_R |= port;

  /* Does a dummy read to insert a few cycles after enabling the peripheral. */
  /*port = SYSCTL_RCGCGPIO_R;*/

  /* Sets Initial Port Pin Level Value */
  if (ConfigPtr->PortPinDirection == PORT_PIN_OUT)
    SETPINVAL(ConfigPtr->PortPinId, ConfigPtr->PortPinLevelValue);

  /* Sets Initial Port Pin Direction */
  SETPINDIR(ConfigPtr->PortPinId, ConfigPtr->PortPinDirection);

  /* Sets Port Pin Initial Mode. */
  for (mode = 0; mode < ConfigPtr->PortPinModeNumber; mode++) {

    if (
      ConfigPtr->PortPinSupportedModes[mode].PortPinMode ==
      ConfigPtr->PortPinInitialMode
    ) {

      Port_SetPortPinHWMode(
	ConfigPtr->PortPinId,
	&(ConfigPtr->PortPinSupportedModes[mode])
      );
    }

  }

}

/*
 * Port_Init implementation.
 */
void Port_Init(
  const Port_ConfigType *	ConfigPtr
)
{

  register uint32 pin;

  VALIDATE( ( ConfigPtr != NULL), PORT_INIT_SERVICE_ID, PORT_E_PARAM_CONFIG );

  VALIDATE( ( Port_CheckCore() != FALSE), PORT_INIT_SERVICE_ID, PORT_E_UNINIT );

  Port_Global.ConfigPtr = ConfigPtr;
  Port_Global.Init = TRUE;

  for (pin = 0; pin < ConfigPtr->PortNumberOfPortPins; pin++)
  {

    /* Initializes Port Pin. */
    Port_InitPortPin(&(ConfigPtr->PortPins[pin]));

  }

}

/*
 * Port_SetPinDirection implementation
 */
#if ( PORT_SET_PIN_DIRECTION_API == STD_ON )
void Port_SetPinDirection(
  Port_PinType		Pin,
  Port_PinDirectionType	Direction
)
{

  register uint32		p;
  register EE_UREG		f;
  register boolean		init;
  register Port_ConfigType *	cfgptr;

  f = EE_hal_suspendIRQ();
  init = Port_Global.Init;
  cfgptr = Port_Global.ConfigPtr;
  EE_hal_resumeIRQ(f);

  VALIDATE(
    ( init == TRUE ),
    PORT_SET_PIN_DIRECTION_SERVICE_ID,
    PORT_E_UNINIT
  );

  VALIDATE(
    ( Pin < PORT_PINS_NUMBER ),
    PORT_SET_PIN_DIRECTION_SERVICE_ID,
    PORT_E_PARAM_PIN
  );

  /* Pin Look-up */
  for (
    p = 0;
    ( p < cfgptr->PortNumberOfPortPins ) &&
    ( cfgptr->PortPins[p].PortPinId != Pin );
    p++
  );

  VALIDATE(
    ( p < cfgptr->PortNumberOfPortPins ),
    PORT_SET_PIN_DIRECTION_SERVICE_ID,
    PORT_E_PARAM_PIN
  );

  VALIDATE(
    ( cfgptr->PortPins[p].PortPinDirectionChangeable == TRUE ),
    PORT_SET_PIN_DIRECTION_SERVICE_ID,
    PORT_E_DIRECTION_UNCHANGEABLE
  );

  /* Starts Atomic Section. */
  f = EE_hal_suspendIRQ();

  /* Sets Initial Port Pin Level Value */
  if ( Direction == PORT_PIN_OUT )
    SETPINVAL(cfgPtr->PortPinId, cfgPtr->PortPinLevelValue);

  SETPINDIR(cfgptr->PortPins[p].PortPinId, Direction);

  /* Ends Atomic Section. */
  EE_hal_resumeIRQ(f);

}
#endif

/*
 * Port_RefreshPortDirection implementation
 */
void Port_RefreshPortDirection(
  void
)
{

  register uint32 pin;

  VALIDATE(
    ( Port_Global.Init == TRUE ),
    PORT_REFRESH_PORT_DIRECTION_SERVICE_ID,
    PORT_E_UNINIT
  );

  for (pin = 0; pin < Port_Global.ConfigPtr->PortNumberOfPortPins; pin++)
  {
    if (
      Port_Global.ConfigPtr->PortPins[pin].PortPinDirectionChangeable == FALSE
    ) {
      SETPINDIR(
        Port_Global.ConfigPtr->PortPins[pin].PortPinId,
        Port_Global.ConfigPtr->PortPins[pin].PortPinDirection
      );
    }
  }

}

/*
 * Port_SetPinMode implementation
 */
#if ( PORT_SET_PIN_MODE_API == STD_ON )
void Port_SetPinMode(
  Port_PinType		Pin,
  Port_PinModeType	Mode
)
{

  register uint32			p, m;
  register EE_UREG			f;
  register boolan			init;
  register const Port_ConfigType *	cfgptr;

  f = EE_hal_suspendIRQ();
  init = Port_Global.Init;
  cfgptr = Port_Global.ConfigPtr;
  EE_hal_resumeIRQ(f);

  VALIDATE(
    ( init == TRUE ),
    PORT_SET_PIN_MODE_SERVICE_ID,
    PORT_E_UNINIT
  );

  VALIDATE(
    ( Pin < PORT_PINS_NUMBER ),
    PORT_SET_PIN_MODE_SERVICE_ID,
    PORT_E_PARAM_PIN
  );

  /* Pin Look-up */
  for (
    p = 0;
    ( p < cfgptr->PortNumberOfPortPins ) &&
    ( cfgptr->PortPins[p].PortPinId != Pin );
    p++
  );

  VALIDATE(
    ( p < cfgptr->PortNumberOfPortPins ),
    PORT_SET_PIN_MODE_SERVICE_ID,
    PORT_E_PARAM_PIN
  );

  VALIDATE(
    ( cfgptr->PortPins[p].PortPinModeChangeable == TRUE ),
    PORT_SET_PIN_MODE_SERVICE_ID,
    PORT_E_MODE_UNCHANGEABLE
  );

  VALIDATE(
    ( Mode < PORT_MODES_NUMBER ),
    PORT_SET_PIN_MODE_SERVICE_ID,
    PORT_E_PARAM_INVALID_MODE
  );

  /* Pin Modes Look-up */
  for(
    m = 0;
    ( m < cfgptr->PortPins[p].PortPinModeNumber ) &&
    ( cfgptr->PortPins[p].PortPinSupportedModes[m].PortPinMode != Mode );
    m++
  );

  VALIDATE(
    ( m < cfgptr->PortPins[p].PortPinModeNumber ),
    PORT_SET_PIN_MODE_SERVICE_ID,
    PORT_E_PARAM_INVALID_MODE
  );

  /* Change Port Pin Mode. */
  Port_SetPortPinMode(
    cfgptr->PortPins[p].PortPinId,
    &(cfgptr->PortPins[p].PortPinSupportedModes[m])
  );

}
#endif

