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
 * fake-druid AUTOSAR DIO Driver Configuration Header File.
 *
 * Configured for (MCU): TI Stellaris LM4F232H5QD
 *
 * Author: 2011, Giuseppe Serano
 */


#if !(\
 ((DIO_SW_MAJOR_VERSION == 1) && \
  (DIO_SW_MINOR_VERSION == 0) && \
  (DIO_SW_PATCH_VERSION == 0))\
)
#error Dio: Configuration file expected BSW module version to be 1.0.0.*
#endif


#ifndef	DIO_CFG_H
#define	DIO_CFG_H

/*
 * DIO141_Conf:	General DIO Module configuration parameters.
 */
/* DioGeneral */

/*
 * DIO142_Conf:	Switches the Development Error Detection and Notification ON or
 * 		OFF
 */
#define	DIO_DEV_ERROR_DETECT	STD_OFF

/*
 * DIO153_Conf:	Adds / removes the service Dio_FlipChannel() from the code.
 */
#define	DIO_FLIP_CHANNEL_API	STD_ON

/*
 * DIO143_Conf:	Adds / removes the service Dio_ GetVersionInfo() from the code.
 */
#define	DIO_VERSION_INFO_API	STD_ON

/*
 * DIO026:	The configuration process for Dio module shall provide symbolic
 * 		names for each configured DIO channel, port and group.
 */ 
#define	DIO_CHANNEL_A_0	0x00000000
#define	DIO_CHANNEL_A_1	0x00000001
#define	DIO_CHANNEL_A_2	0x00000002
#define	DIO_CHANNEL_A_3	0x00000003
#define	DIO_CHANNEL_A_4	0x00000004
#define	DIO_CHANNEL_A_5	0x00000005
#define	DIO_CHANNEL_A_6	0x00000006
#define	DIO_CHANNEL_A_7	0x00000007

#define	DIO_CHANNEL_B_0	0x00000008
#define	DIO_CHANNEL_B_1	0x00000009
#define	DIO_CHANNEL_B_2	0x0000000A
#define	DIO_CHANNEL_B_3	0x0000000B
#define	DIO_CHANNEL_B_4	0x0000000C
#define	DIO_CHANNEL_B_5	0x0000000D
#define	DIO_CHANNEL_B_6	0x0000000E
#define	DIO_CHANNEL_B_7	0x0000000F

#define	DIO_CHANNEL_C_0	0x00000010
#define	DIO_CHANNEL_C_1	0x00000011
#define	DIO_CHANNEL_C_2	0x00000012
#define	DIO_CHANNEL_C_3	0x00000013
#define	DIO_CHANNEL_C_4	0x00000014
#define	DIO_CHANNEL_C_5	0x00000015
#define	DIO_CHANNEL_C_6	0x00000016
#define	DIO_CHANNEL_C_7	0x00000017

#define	DIO_CHANNEL_D_0	0x00000018
#define	DIO_CHANNEL_D_1	0x00000019
#define	DIO_CHANNEL_D_2	0x0000001A
#define	DIO_CHANNEL_D_3	0x0000001B
#define	DIO_CHANNEL_D_4	0x0000001C
#define	DIO_CHANNEL_D_5	0x0000001D
#define	DIO_CHANNEL_D_6	0x0000001E
#define	DIO_CHANNEL_D_7	0x0000001F

#define	DIO_CHANNEL_E_0	0x00000020
#define	DIO_CHANNEL_E_1	0x00000021
#define	DIO_CHANNEL_E_2	0x00000022
#define	DIO_CHANNEL_E_3	0x00000023
#define	DIO_CHANNEL_E_4	0x00000024
#define	DIO_CHANNEL_E_5	0x00000025
#define	DIO_CHANNEL_E_6	0x00000026
#define	DIO_CHANNEL_E_7	0x00000027

#define	DIO_CHANNEL_F_0	0x00000028
#define	DIO_CHANNEL_F_1	0x00000029
#define	DIO_CHANNEL_F_2	0x0000002A
#define	DIO_CHANNEL_F_3	0x0000002B
#define	DIO_CHANNEL_F_4	0x0000002C
#define	DIO_CHANNEL_F_5	0x0000002D
#define	DIO_CHANNEL_F_6	0x0000002E
#define	DIO_CHANNEL_F_7	0x0000002F

#define	DIO_CHANNEL_G_0	0x00000030
#define	DIO_CHANNEL_G_1	0x00000031
#define	DIO_CHANNEL_G_2	0x00000032
#define	DIO_CHANNEL_USER_LED	DIO_CHANNEL_G_2
#define	DIO_CHANNEL_G_3	0x00000033
#define	DIO_CHANNEL_G_4	0x00000034
#define	DIO_CHANNEL_G_5	0x00000035
#define	DIO_CHANNEL_G_6	0x00000036
#define	DIO_CHANNEL_G_7	0x00000037

#define	DIO_CHANNEL_H_0	0x00000038
#define	DIO_CHANNEL_H_1	0x00000039
#define	DIO_CHANNEL_H_2	0x0000003A
#define	DIO_CHANNEL_H_3	0x0000003B
#define	DIO_CHANNEL_H_4	0x0000003C
#define	DIO_CHANNEL_H_5	0x0000003D
#define	DIO_CHANNEL_H_6	0x0000003E
#define	DIO_CHANNEL_H_7	0x0000003F

#define	DIO_CHANNEL_J_0	0x00000040
#define	DIO_CHANNEL_J_1	0x00000041
#define	DIO_CHANNEL_J_2	0x00000042
#define	DIO_CHANNEL_J_3	0x00000043
#define	DIO_CHANNEL_J_4	0x00000044
#define	DIO_CHANNEL_J_5	0x00000045
#define	DIO_CHANNEL_J_6	0x00000046
#define	DIO_CHANNEL_J_7	0x00000047

#define	DIO_CHANNEL_K_0	0x00000048
#define	DIO_CHANNEL_K_1	0x00000049
#define	DIO_CHANNEL_K_2	0x0000004A
#define	DIO_CHANNEL_K_3	0x0000004B
#define	DIO_CHANNEL_K_4	0x0000004C
#define	DIO_CHANNEL_K_5	0x0000004D
#define	DIO_CHANNEL_K_6	0x0000004E
#define	DIO_CHANNEL_K_7	0x0000004F

#define	DIO_CHANNEL_L_0	0x00000050
#define	DIO_CHANNEL_L_1	0x00000051
#define	DIO_CHANNEL_L_2	0x00000052
#define	DIO_CHANNEL_L_3	0x00000053
#define	DIO_CHANNEL_L_4	0x00000054
#define	DIO_CHANNEL_L_5	0x00000055
#define	DIO_CHANNEL_L_6	0x00000056
#define	DIO_CHANNEL_L_7	0x00000057

#define	DIO_CHANNEL_M_0	0x00000058
#define	DIO_CHANNEL_SWITCH_1	DIO_CHANNEL_M_0
#define	DIO_CHANNEL_M_1	0x00000059
#define	DIO_CHANNEL_SWITCH_2	DIO_CHANNEL_M_1
#define	DIO_CHANNEL_M_2	0x0000005A
#define	DIO_CHANNEL_SWITCH_3	DIO_CHANNEL_M_2
#define	DIO_CHANNEL_M_3	0x0000005B
#define	DIO_CHANNEL_SWITCH_4	DIO_CHANNEL_M_3
#define	DIO_CHANNEL_M_4	0x0000005C
#define	DIO_CHANNEL_SWITCH_5	DIO_CHANNEL_M_4
#define	DIO_CHANNEL_M_5	0x0000005D
#define	DIO_CHANNEL_M_6	0x0000005E
#define	DIO_CHANNEL_M_7	0x0000005F

#define	DIO_CHANNEL_P_0	0x00000060
#define	DIO_CHANNEL_P_1	0x00000061
#define	DIO_CHANNEL_P_2	0x00000062
#define	DIO_CHANNEL_P_3	0x00000063
#define	DIO_CHANNEL_P_4	0x00000064
#define	DIO_CHANNEL_P_5	0x00000065
#define	DIO_CHANNEL_P_6	0x00000066
#define	DIO_CHANNEL_P_7	0x00000067

#define	DIO_CHANNEL_Q_0	0x00000068
#define	DIO_CHANNEL_Q_1	0x00000069
#define	DIO_CHANNEL_Q_2	0x0000006A
#define	DIO_CHANNEL_Q_3	0x0000006B
#define	DIO_CHANNEL_Q_4	0x0000006C
#define	DIO_CHANNEL_Q_5	0x0000006D
#define	DIO_CHANNEL_Q_6	0x0000006E
#define	DIO_CHANNEL_Q_7	0x0000006F

#define	DIO_CHANNELS_NUMBER	DIO_CHANNEL_Q_7 + 1

#define	DIO_PORT_A	0x00000000
#define	DIO_PORT_B	0x00000001
#define	DIO_PORT_C	0x00000002
#define	DIO_PORT_D	0x00000003
#define	DIO_PORT_E	0x00000004
#define	DIO_PORT_F	0x00000005
#define	DIO_PORT_G	0x00000006
#define	DIO_PORT_USER_LED	DIO_PORT_G
#define	DIO_PORT_H	0x00000007
#define	DIO_PORT_J	0x00000008
#define	DIO_PORT_K	0x00000009
#define	DIO_PORT_L	0x0000000A
#define	DIO_PORT_M	0x0000000B
#define	DIO_PORT_SWITCHES	DIO_PORT_M
#define	DIO_PORT_P	0x0000000C
#define	DIO_PORT_Q	0x0000000D

#define	DIO_PORTS_NUMBER	DIO_PORT_Q + 1

extern Dio_ChannelGroupType DioPortGChannelsGroups[];
#define	DIO_CHANNEL_GROUP_USER_LED	&DioPortGChannelsGroups[0]

extern Dio_ChannelGroupType DioPortMChannelsGroups[];
#define	DIO_CHANNEL_GROUP_SWITCHES	&DioPortMChannelsGroups[0]

/*
 * DIO144_Conf:	Configuration of individual DIO ports, consisting of channels
 * 		and possible channel groups. Note that this container definition
 * 		does not explicitly define a symbolic name parameter. Instead,
 * 		the container's short name will be used in the Ecu Configuration
 * 		Description to specify the symbolic name of the port.
 */
typedef struct {

  /*
   * DIO145_Conf:	Numeric identifier of the DIO port. Not all MCU ports
   * 			may be used for DIO, thus there may be "gaps" in the
   * 			list of all IDs. This value will be assigned to the DIO
   * 			port symbolic name (i.e. the SHORT-NAME of the DioPort
   * 			container).
   */
  uint32			DioPortId;

  /*
   * The number of specified Port Channels.
   */
  uint32			DioNumberOfChannels;

  /*
   * Configuration of an individual DIO channel. Besides a HW specific channel
   * name which is typically fixed for a specific micro controller, additional
   * symbolic names can be defined per channel. Note hat this container
   * definition does not explicitly define a symbolic name parameter. Instead,
   * the container's short name will be used in the Ecu Configuration
   * Description to specify the symbolic name of the channel.
   */
  Dio_ChannelType *		DioChannels;

  /*
   * The number of specified Port Channels Groups.
   */
  uint32			DioNumberOfChannelsGroups;

  /*
   * DIO149_Conf:	The DIO channel group is identified in DIO API by a
   * 			pointer to a data structure (of type
   * 			Dio_ChannelGroupType). That data structure contains the
   * 			channel group information. This parameter contains the
   * 			code fragment that has to be inserted in the API call of
   * 			the calling module to get the address of the variable in
   * 			memory which holds the channel group information.
   * 			Example values are "&MyDioGroup1" or
   * 			"&MyDioGroupArray[0]"
   */
  Dio_ChannelGroupType *	Dio_ChannelsGroups;

} Dio_PortConfType;

/*
 * DIO152_Conf:	This container contains the configuration parameters and sub
 * 		containers of the AUTOSAR DIO module. This container is a
 * 		MultipleConfigurationContainer, i.e. this container and its
 * 		sub-containers exist once per configuration set.
 */
typedef struct {

  /*
   * The number of specified Ports.
   */
  uint32			DioNumberOfPorts;

  /*
   * PortPins.
   */
  Dio_PortConfType *		DioPorts;

} Dio_ConfigType;

#define	DIO_CONFIG_DIO_ALL	0x00000000
#define	DIO_CONFIG_DEFAULT	DIO_CONFIG_DIO_ALL

#endif	/* DIO_CFG_H */
