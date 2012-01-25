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
 * fake-druid AUTOSAR PORT Driver Configuration Header File.
 *
 * Configured for (MCU): TI Stellaris LM4F232H5QD
 *
 * Author: 2011, Giuseppe Serano
 */


#if !(\
 ((PORT_SW_MAJOR_VERSION == 1) && \
  (PORT_SW_MINOR_VERSION == 0) && \
  (PORT_SW_PATCH_VERSION == 0))\
)
#error Port: Configuration file expected BSW module version to be 1.0.0.*
#endif


#ifndef	PORT_CFG_H
#define	PORT_CFG_H

/*
 * PORT117_Conf:	Module wide configuration parameters of the PORT driver.
 */
/* PortGeneral */

/*
 * PORT123_Conf:	Switches the Development Error Detection and
 * 			Notification on or off. true: Enabled. false: Disabled.
 */
#define	PORT_DEV_ERROR_DETECT		STD_OFF

/*
 * PORT131_Conf:	Pre-processor switch to enable / disable the use of the
 * 			function Port_SetPinDirection(). TRUE: Enabled, Function
 * 			Port_SetPinDirection() is available. FALSE: Disabled,
 * 			Function Port_SetPinDirection() is not available.
 */
#define	PORT_SET_PIN_DIRECTION_API	STD_OFF

/*
 * PORT132_Conf:	Pre-processor switch to enable / disable the use of the
 * 			function Port_SetPinMode(). true: Enabled, Function
 * 			Port_SetPinMode() is available. false: Disabled,
 * 			Function Port_SetPinMode() is not available.
 */
#define	PORT_SET_PIN_MODE_API		STD_OFF

/*
 * PORT133_Conf:	Pre-processor switch to enable / disable the API to read
 * 			out the modules version information. true: Version info
 * 			API enabled. false: Version info API disabled.
 */
#define	PORT_VERSION_INFO_API		STD_ON

/* PORT006:	The user of the PORT Driver module shall configure the symbolic
 * 		names of the port pins of the MCU.
 *
 * PORT207:	These symbolic names for the individual port pins (e.g.
 * 		PORT_A_PIN_0) shall be defined in the configuration tool.
 *
 * PORT076:	The PORT Driver module’s implementer shall define symbolic names
 * 		in the file Port_Cfg.h
 *
 * PORT208:	The PORT Driver module’s implementer shall publish the symbolic
 * 		names through the file Port.h
 */

#define	PORT_A		0x00000000
#define	PORT_A_PIN_0	PORT_A
#define	PORT_A_PIN_1	0x00000001
#define	PORT_A_PIN_2	0x00000002
#define	PORT_A_PIN_3	0x00000003
#define	PORT_A_PIN_4	0x00000004
#define	PORT_A_PIN_5	0x00000005
#define	PORT_A_PIN_6	0x00000006
#define	PORT_A_PIN_7	0x00000007
#define	PORT_B		0x00000008
#define	PORT_B_PIN_0	PORT_B
#define	PORT_B_PIN_1	0x00000009
#define	PORT_B_PIN_2	0x0000000A
#define	PORT_B_PIN_3	0x0000000B
#define	PORT_B_PIN_4	0x0000000C
#define	PORT_B_PIN_5	0x0000000D
#define	PORT_B_PIN_6	0x0000000E
#define	PORT_B_PIN_7	0x0000000F
#define	PORT_C		0x00000010
#define	PORT_C_PIN_0	PORT_C
#define	PORT_C_PIN_1	0x00000011
#define	PORT_C_PIN_2	0x00000012
#define	PORT_C_PIN_3	0x00000013
#define	PORT_C_PIN_4	0x00000014
#define	PORT_C_PIN_5	0x00000015
#define	PORT_C_PIN_6	0x00000016
#define	PORT_C_PIN_7	0x00000017
#define	PORT_D		0x00000018
#define	PORT_D_PIN_0	PORT_D
#define	PORT_D_PIN_1	0x00000019
#define	PORT_D_PIN_2	0x0000001A
#define	PORT_D_PIN_3	0x0000001B
#define	PORT_D_PIN_4	0x0000001C
#define	PORT_D_PIN_5	0x0000001D
#define	PORT_D_PIN_6	0x0000001E
#define	PORT_D_PIN_7	0x0000001F
#define	PORT_E		0x00000020
#define	PORT_E_PIN_0	PORT_E
#define	PORT_E_PIN_1	0x00000021
#define	PORT_E_PIN_2	0x00000022
#define	PORT_E_PIN_3	0x00000023
#define	PORT_E_PIN_4	0x00000024
#define	PORT_E_PIN_5	0x00000025
#define	PORT_E_PIN_6	0x00000026
#define	PORT_E_PIN_7	0x00000027
#define	PORT_F		0x00000028
#define	PORT_F_PIN_0	PORT_F
#define	PORT_F_PIN_1	0x00000029
#define	PORT_F_PIN_2	0x0000002A
#define	PORT_F_PIN_3	0x0000002B
#define	PORT_F_PIN_4	0x0000002C
#define	PORT_F_PIN_5	0x0000002D
#define	PORT_F_PIN_6	0x0000002E
#define	PORT_F_PIN_7	0x0000002F
#define	PORT_G		0x00000030
#define	PORT_G_PIN_0	PORT_G
#define	PORT_G_PIN_1	0x00000031
#define	PORT_G_PIN_2	0x00000032
#define	PORT_G_PIN_3	0x00000033
#define	PORT_G_PIN_4	0x00000034
#define	PORT_G_PIN_5	0x00000035
#define	PORT_G_PIN_6	0x00000036
#define	PORT_G_PIN_7	0x00000037
#define	PORT_H		0x00000038
#define	PORT_H_PIN_0	PORT_H
#define	PORT_H_PIN_1	0x00000039
#define	PORT_H_PIN_2	0x0000003A
#define	PORT_H_PIN_3	0x0000003B
#define	PORT_H_PIN_4	0x0000003C
#define	PORT_H_PIN_5	0x0000003D
#define	PORT_H_PIN_6	0x0000003E
#define	PORT_H_PIN_7	0x0000003F
#define	PORT_J		0x00000040
#define	PORT_J_PIN_0	PORT_J
#define	PORT_J_PIN_1	0x00000041
#define	PORT_J_PIN_2	0x00000042
#define	PORT_J_PIN_3	0x00000043
#define	PORT_J_PIN_4	0x00000044
#define	PORT_J_PIN_5	0x00000045
#define	PORT_J_PIN_6	0x00000046
#define	PORT_J_PIN_7	0x00000047
#define	PORT_K		0x00000048
#define	PORT_K_PIN_0	PORT_K
#define	PORT_K_PIN_1	0x00000049
#define	PORT_K_PIN_2	0x0000004A
#define	PORT_K_PIN_3	0x0000004B
#define	PORT_K_PIN_4	0x0000004C
#define	PORT_K_PIN_5	0x0000004D
#define	PORT_K_PIN_6	0x0000004E
#define	PORT_K_PIN_7	0x0000004F
#define	PORT_L		0x00000050
#define	PORT_L_PIN_0	PORT_L
#define	PORT_L_PIN_1	0x00000051
#define	PORT_L_PIN_2	0x00000052
#define	PORT_L_PIN_3	0x00000053
#define	PORT_L_PIN_4	0x00000054
#define	PORT_L_PIN_5	0x00000055
#define	PORT_L_PIN_6	0x00000056
#define	PORT_L_PIN_7	0x00000057
#define	PORT_M		0x00000058
#define	PORT_M_PIN_0	PORT_M
#define	PORT_M_PIN_1	0x00000059
#define	PORT_M_PIN_2	0x0000005A
#define	PORT_M_PIN_3	0x0000005B
#define	PORT_M_PIN_4	0x0000005C
#define	PORT_M_PIN_5	0x0000005D
#define	PORT_M_PIN_6	0x0000005E
#define	PORT_M_PIN_7	0x0000005F
#define	PORT_P		0x00000060
#define	PORT_P_PIN_0	PORT_P
#define	PORT_P_PIN_1	0x00000061
#define	PORT_P_PIN_2	0x00000062
#define	PORT_P_PIN_3	0x00000063
#define	PORT_P_PIN_4	0x00000064
#define	PORT_P_PIN_5	0x00000065
#define	PORT_P_PIN_6	0x00000066
#define	PORT_P_PIN_7	0x00000067
#define	PORT_Q		0x00000068
#define	PORT_Q_PIN_0	PORT_Q
#define	PORT_Q_PIN_1	0x00000069
#define	PORT_Q_PIN_2	0x0000006A
#define	PORT_Q_PIN_3	0x0000006B
#define	PORT_Q_PIN_4	0x0000006C
#define	PORT_Q_PIN_5	0x0000006D
#define	PORT_Q_PIN_6	0x0000006E
#define	PORT_Q_PIN_7	0x0000006F

#define	PORT_PINS_NUMBER	PORT_Q_PIN_7

/*
 * Port Pin Modes.
 */
#define	PORT_PIN_MODE_DIO	0x00000000

#define	PORT_PIN_MODES_NUMBER	PORT_PIN_MODE_DIO + 1

/*
 * Port Pin Mode Hardware Configuration Data Values.
 */
#define	PORT_PIN_HW_CFG_PMC_M	0x0000000F	/* Port Mux Control Mask      */
#define	PORT_PIN_HW_CFG_DEN	0x00000010	/* Digital Enable	      */
#define	PORT_PIN_HW_CFG_AMSEL	0x00000020	/* Analog Mode Select	      */
#define	PORT_PIN_HW_CFG_AFSEL	0x00000040	/* Alternate Function Select  */
#define	PORT_PIN_HW_CFG_ODR	0x00000080	/* Open Drain Select	      */
#define	PORT_PIN_HW_CFG_PUR	0x00000100	/* Pull-Up Select	      */
#define	PORT_PIN_HW_CFG_PDR	0x00000200	/* Pull-Down Select	      */
#define	PORT_PIN_HW_CFG_DR2R	0x00000400	/* 2-mA Drive Select	      */
#define	PORT_PIN_HW_CFG_DR4R	0x00000800	/* 4-mA Drive Select	      */
#define	PORT_PIN_HW_CFG_DR8R	0x00001000	/* 8-mA Drive Select	      */
#define	PORT_PIN_HW_CFG_SLR	0x00002000	/* Slew-Rate Control Select   */
#define	PORT_PIN_HW_CFG_ADCCTL	0x00004000	/* ADC Control		      */
#define	PORT_PIN_HW_CFG_DMACTL	0x00008000	/* DMA Control		      */

/*
 * Port Pin Mode Configuration Container.
 */
typedef struct {

  /*
   * PORT130_Conf:	Port pin mode from mode list.
   * 			Note that more than one mode is allowed by default.
   * 			That way it is e.g. possible to combine DIO with another
   * 			mode such as ICU. More HW specific literals may be added
   * 			by module implementor. E.g. SPI may be further broken
   * 			down into SpiCsHw, SpiCsSw, etc. if necessary.
   */
  Port_PinModeType	PortPinMode;

  /*
   * Port Pin Mode Hardware Configuration Data.
   */
  uint32		PortPinModeHWConfig;

} Port_PinModeConfType;

/*
 * PORT118_Conf:	Configuration of the individual port pins.
 */
typedef struct {

  /*
   * PORT125_Conf:	The initial direction of the pin (IN or OUT).
   * 			If the direction is not changeable, the value configured
   * 			here is fixed. The direction must match the pin mode.
   * 			E.g. a pin used for an ADC must be configured to be an
   * 			in port.
   */
  Port_PinDirectionType		PortPinDirection;

  /*
   * PORT126_Conf:	Parameter to indicate if the direction is changeable on
   * 			a port pin during runtime.
   * 			- true:		Port Pin direction changeable enabled.
   * 			- false:	Port Pin direction changeable disabled.
   */
  boolean			PortPinDirectionChangeable;

  /*
   * PORT127_Conf:	Pin Id of the port pin. This value will be assigned to
   * 			the symbolic name derived from the port pin container
   * 			short name.
   */
  Port_PinType			PortPinId;

  /*
   * PORT128_Conf:	Port pin mode from mode list for use with Port_Init()
   * 			function.
   */
  Port_PinModeType		PortPinInitialMode;

  /*
   * PORT129_Conf:	Port Pin Level value from Port pin list.
   */
  Port_PinLevelType		PortPinLevelValue;

  /*
   * Number of Supported Port Pin Modes ( > 0 ).
   */
  uint32			PortPinModeNumber;

  /*
   * Supported Port Pin Modes.
   */
  Port_PinModeConfType *	PortPinSupportedModes;

  /*
   * PORT134_Conf:	Parameter to indicate if the mode is changeable on a
   * 			port pin during runtime.
   * 			- True:		Port Pin mode changeable allowed.
   * 			- False:	Port Pin mode changeable not permitted.
   */
  boolean			PortPinModeChangeable;

} Port_PinConfType;

/*
 * PORT122_Conf:	Container collecting the PortPins.
 */
typedef struct {

  /*
   * PORT124_Conf:	The number of specified PortPins.
   */
  uint32			PortNumberOfPortPins;

  /*
   * PortPins.
   */
  Port_PinConfType *		PortPins;

} Port_ConfigType;

#define	PORT_CONFIG_DIO_ALL	0x00000000
#define	PORT_CONFIG_DEFAULT	PORT_CONFIG_DIO_ALL

#endif	/* PORT_CFG_H */
