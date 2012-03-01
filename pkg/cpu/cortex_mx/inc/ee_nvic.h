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

/**
 *	@file	ee_nvic.h
 *	@brief	ARM Cortex-MX Nested Vector Interrupt Controller (NVIC) Macros
 *	@author	Giuseppe Serano
 *	@date	2011
 */ 

#ifndef __INCLUDE_CORTEX_MX_NVIC_H__
#define __INCLUDE_CORTEX_MX_NVIC_H__

/* Exceptions */
/* Reset */
#define	EE_CORTEX_MX_RESET_EXC_NUM		0x00000001
/* NMI */
#define	EE_CORTEX_MX_NMI_EXC_NUM		0x00000002
/* hard fault */
#define	EE_CORTEX_MX_HARD_FAULT_EXC_NUM		0x00000003
/* MPU fault */
#define	EE_CORTEX_MX_MPU_FAULT_EXC_NUM		0x00000004
/* bus fault */
#define	EE_CORTEX_MX_BUS_FAULT_EXC_NUM		0x00000005
/* usage fault */
#define	EE_CORTEX_MX_USAGE_FAULT_EXC_NUM	0x00000006
/* SVCall */
#define	EE_CORTEX_MX_SVCALL_EXC_NUM		0x0000000B
/* PendSV */
#define	EE_CORTEX_MX_PENDSV_EXC_NUM		0x0000000E
/* SysTick */
#define	EE_CORTEX_MX_SYSTICK_EXC_NUM		0x0000000F
/* Debug monitor */
#define	EE_CORTEX_MX_DEBUG_MONITOR_EXC_NUM	0x0000000C

/* Interrupts */
/* GPIO Port A */
#define	EE_CORTEX_MX_GPIO_A_INT_NUM		0x00000000
/* GPIO Port B */
#define	EE_CORTEX_MX_GPIO_B_INT_NUM		0x00000001
/* GPIO Port C */
#define	EE_CORTEX_MX_GPIO_C_INT_NUM		0x00000002
/* GPIO Port D */
#define	EE_CORTEX_MX_GPIO_D_INT_NUM		0x00000003
/* GPIO Port E */
#define	EE_CORTEX_MX_GPIO_E_INT_NUM		0x00000004
/* GPIO Port F */
#define	EE_CORTEX_MX_GPIO_F_INT_NUM		0x0000001E
/* GPIO Port G */
#define	EE_CORTEX_MX_GPIO_G_INT_NUM		0x0000001F
/* GPIO Port H */
#define	EE_CORTEX_MX_GPIO_H_INT_NUM		0x00000020
/* GPIO Port J */
#define	EE_CORTEX_MX_GPIO_J_INT_NUM		0x00000036
/* GPIO Port K */
#define	EE_CORTEX_MX_GPIO_K_INT_NUM		0x00000037
/* GPIO Port L */
#define	EE_CORTEX_MX_GPIO_L_INT_NUM		0x00000038
/* GPIO Port M */
#define	EE_CORTEX_MX_GPIO_M_INT_NUM		0x0000006F
/* GPIO Port N */
#define	EE_CORTEX_MX_GPIO_N_INT_NUM		0x00000070
/* GPIO Port P (Summary or P0) */
#define	EE_CORTEX_MX_GPIO_P0_INT_NUM		0x00000074
/* GPIO Port P1 */
#define	EE_CORTEX_MX_GPIO_P1_INT_NUM		0x00000075
/* GPIO Port P2 */
#define	EE_CORTEX_MX_GPIO_P2_INT_NUM		0x00000076
/* GPIO Port P3 */
#define	EE_CORTEX_MX_GPIO_P3_INT_NUM		0x00000077
/* GPIO Port P4 */
#define	EE_CORTEX_MX_GPIO_P4_INT_NUM		0x00000078
/* GPIO Port P5 */
#define	EE_CORTEX_MX_GPIO_P5_INT_NUM		0x00000079
/* GPIO Port P6 */
#define	EE_CORTEX_MX_GPIO_P6_INT_NUM		0x0000007A
/* GPIO Port P7 */
#define	EE_CORTEX_MX_GPIO_P7_INT_NUM		0x0000007B
/* GPIO Port Q (Summary or Q0) */
#define	EE_CORTEX_MX_GPIO_Q0_INT_NUM		0x0000007C
/* GPIO Port Q1 */
#define	EE_CORTEX_MX_GPIO_Q1_INT_NUM		0x0000007D
/* GPIO Port Q2 */
#define	EE_CORTEX_MX_GPIO_Q2_INT_NUM		0x0000007E
/* GPIO Port Q3 */
#define	EE_CORTEX_MX_GPIO_Q3_INT_NUM		0x0000007F
/* GPIO Port Q4 */
#define	EE_CORTEX_MX_GPIO_Q4_INT_NUM		0x00000080
/* GPIO Port Q5 */
#define	EE_CORTEX_MX_GPIO_Q5_INT_NUM		0x00000081
/* GPIO Port Q6 */
#define	EE_CORTEX_MX_GPIO_Q6_INT_NUM		0x00000082
/* GPIO Port Q7 */
#define	EE_CORTEX_MX_GPIO_Q7_INT_NUM		0x00000083
/* GPIO Port R */
#define	EE_CORTEX_MX_GPIO_R_INT_NUM		0x00000084
/* GPIO Port S */
#define	EE_CORTEX_MX_GPIO_S_INT_NUM		0x00000085
/* UART0 Rx and Tx */
#define	EE_CORTEX_MX_UART_0_INT_NUM		0x00000005
/* UART1 Rx and Tx */
#define	EE_CORTEX_MX_UART_1_INT_NUM		0x00000006
/* UART2 Rx and Tx */
#define	EE_CORTEX_MX_UART_2_INT_NUM		0x00000021
/* UART3 Rx and Tx */
#define	EE_CORTEX_MX_UART_3_INT_NUM		0x0000003B
/* UART4 Rx and Tx */
#define	EE_CORTEX_MX_UART_4_INT_NUM		0x0000003C
/* UART5 Rx and Tx */
#define	EE_CORTEX_MX_UART_5_INT_NUM		0x0000003D
/* UART6 Rx and Tx */
#define	EE_CORTEX_MX_UART_6_INT_NUM		0x0000003E
/* UART7 Rx and Tx */
#define	EE_CORTEX_MX_UART_7_INT_NUM		0x0000003F
/* SSI0 Rx and Tx */
#define	EE_CORTEX_MX_SSI_0_INT_NUM		0x00000007
/* SSI1 Rx and Tx */
#define	EE_CORTEX_MX_SSI_1_INT_NUM		0x00000022
/* SSI2 Rx and Tx */
#define	EE_CORTEX_MX_SSI_2_INT_NUM		0x00000039
/* SSI3 Rx and Tx */
#define	EE_CORTEX_MX_SSI_3_INT_NUM		0x0000003A
/* I2C0 Master and Slave */
#define	EE_CORTEX_MX_I2C_0_INT_NUM		0x00000008
/* I2C1 Master and Slave */
#define	EE_CORTEX_MX_I2C_1_INT_NUM		0x00000025
/* I2C2 Master and Slave */
#define	EE_CORTEX_MX_I2C_2_INT_NUM		0x00000044
/* I2C3 Master and Slave */
#define	EE_CORTEX_MX_I2C_3_INT_NUM		0x00000045
/* I2C4 Master and Slave */
#define	EE_CORTEX_MX_I2C_4_INT_NUM		0x0000006D
/* I2C5 Master and Slave */
#define	EE_CORTEX_MX_I2C_5_INT_NUM		0x0000006E
/* PWM Fault */
#define	EE_CORTEX_MX_PWM_0_FAULT_INT_NUM	0x00000009
/* PWM Generator 0  */
#define	EE_CORTEX_MX_PWM_0_0_INT_NUM		0x0000000A
/* PWM Generator 1 */
#define	EE_CORTEX_MX_PWM_0_1_INT_NUM		0x0000000B
/* PWM Generator 2 */
#define	EE_CORTEX_MX_PWM_0_2_INT_NUM		0x0000000C
/* PWM Generator 3 */
#define	EE_CORTEX_MX_PWM_0_3_INT_NUM		0x0000002D
/* PWM 1 Fault */
#define	EE_CORTEX_MX_PWM_1_FAULT_INT_NUM	0x0000008A
/* PWM 1 Generator 0 */
#define	EE_CORTEX_MX_PWM_1_0_INT_NUM		0x00000086
/* PWM 1 Generator 1 */
#define	EE_CORTEX_MX_PWM_1_1_INT_NUM		0x00000087
/* PWM 1 Generator 2 */
#define	EE_CORTEX_MX_PWM_1_2_INT_NUM		0x00000088
/* PWM 1 Generator 3 */
#define	EE_CORTEX_MX_PWM_1_3_INT_NUM		0x00000089
/* Quadrature Encoder 0 */
#define	EE_CORTEX_MX_QUAD_ENC_0_INT_NUM		0x0000000D
/* Quadrature Encoder 1 */
#define	EE_CORTEX_MX_QUAD_ENC_1_INT_NUM		0x00000026
/* Quadrature Encoder 2 */
#define	EE_CORTEX_MX_QUAD_ENC_2_INT_NUM		0x00000071
/* ADC Sequence 0 */
#define	EE_CORTEX_MX_ADC_0_0_INT_NUM		0x0000000E
/* ADC Sequence 1 */
#define	EE_CORTEX_MX_ADC_0_1_INT_NUM		0x0000000F
/* ADC Sequence 2 */
#define	EE_CORTEX_MX_ADC_0_2_INT_NUM		0x00000010
/* ADC Sequence 3 */
#define	EE_CORTEX_MX_ADC_0_3_INT_NUM		0x00000011
/* ADC1 Sequence 0 */
#define	EE_CORTEX_MX_ADC_1_0_INT_NUM		0x00000030
/* ADC1 Sequence 1 */
#define	EE_CORTEX_MX_ADC_1_1_INT_NUM		0x00000031
/* ADC1 Sequence 2 */
#define	EE_CORTEX_MX_ADC_1_2_INT_NUM		0x00000032
/* ADC1 Sequence 3 */
#define	EE_CORTEX_MX_ADC_1_3_INT_NUM		0x00000033
/* Watchdog timer */
#define	EE_CORTEX_MX_WATCHDOG_TIMER_INT_NUM	0x00000012
/* Timer 0 subtimer A */
#define	EE_CORTEX_MX_TIMER_0_A_INT_NUM		0x00000013
/* Timer 0 subtimer B */
#define	EE_CORTEX_MX_TIMER_0_B_INT_NUM		0x00000014
/* Timer 1 subtimer A */
#define	EE_CORTEX_MX_TIMER_1_A_INT_NUM		0x00000015
/* Timer 1 subtimer B */
#define	EE_CORTEX_MX_TIMER_1_B_INT_NUM		0x00000016
/* Timer 2 subtimer A */
#define	EE_CORTEX_MX_TIMER_2_A_INT_NUM		0x00000017
/* Timer 2 subtimer B */
#define	EE_CORTEX_MX_TIMER_2_B_INT_NUM		0x00000018
/* Timer 3 subtimer A */
#define	EE_CORTEX_MX_TIMER_3_A_INT_NUM		0x00000023
/* Timer 3 subtimer B */
#define	EE_CORTEX_MX_TIMER_3_B_INT_NUM		0x00000024
/* Timer 4 subtimer A */
#define	EE_CORTEX_MX_TIMER_4_A_INT_NUM		0x00000046
/* Timer 4 subtimer B */
#define	EE_CORTEX_MX_TIMER_4_B_INT_NUM		0x00000047
/* Timer 5 subtimer A */
#define	EE_CORTEX_MX_TIMER_5_A_INT_NUM		0x0000005C
/* Timer 5 subtimer B */
#define	EE_CORTEX_MX_TIMER_5_B_INT_NUM		0x0000005D
/* Wide Timer 0 subtimer A */
#define	EE_CORTEX_MX_WIDE_TIMER_0_A_INT_NUM	0x0000005E
/* Wide Timer 0 subtimer B */
#define	EE_CORTEX_MX_WIDE_TIMER_0_B_INT_NUM	0x0000005F
/* Wide Timer 1 subtimer A */
#define	EE_CORTEX_MX_WIDE_TIMER_1_A_INT_NUM	0x00000060
/* Wide Timer 1 subtimer B */
#define	EE_CORTEX_MX_WIDE_TIMER_1_B_INT_NUM	0x00000061
/* Wide Timer 2 subtimer A */
#define	EE_CORTEX_MX_WIDE_TIMER_2_A_INT_NUM	0x00000062
/* Wide Timer 2 subtimer B */
#define	EE_CORTEX_MX_WIDE_TIMER_2_B_INT_NUM	0x00000063
/* Wide Timer 3 subtimer A */
#define	EE_CORTEX_MX_WIDE_TIMER_3_A_INT_NUM	0x00000064
/* Wide Timer 3 subtimer B */
#define	EE_CORTEX_MX_WIDE_TIMER_3_B_INT_NUM	0x00000065
/* Wide Timer 4 subtimer A */
#define	EE_CORTEX_MX_WIDE_TIMER_4_A_INT_NUM	0x00000066
/* Wide Timer 4 subtimer B */
#define	EE_CORTEX_MX_WIDE_TIMER_4_B_INT_NUM	0x00000067
/* Wide Timer 5 subtimer A */
#define	EE_CORTEX_MX_WIDE_TIMER_5_A_INT_NUM	0x00000068
/* Wide Timer 5 subtimer B */
#define	EE_CORTEX_MX_WIDE_TIMER_5_B_INT_NUM	0x00000069
/* Analog Comparator 0 */
#define	EE_CORTEX_MX_ANALOG_CMP_0_INT_NUM	0x00000019
/* Analog Comparator 1 */
#define	EE_CORTEX_MX_ANALOG_CMP_1_INT_NUM	0x0000001A
/* Analog Comparator 2 */
#define	EE_CORTEX_MX_ANALOG_CMP_2_INT_NUM	0x0000001B
/* System Control (PLL, OSC, BO) */
#define	EE_CORTEX_MX_SYS_CTRL_INT_NUM		0x0000001C
/* FLASH Control */
#define	EE_CORTEX_MX_FLASH_CTRL_INT_NUM		0x0000001D
/* CAN0 */
#define	EE_CORTEX_MX_CAN_0_INT_NUM		0x00000027
/* CAN1 */
#define	EE_CORTEX_MX_CAN_1_INT_NUM		0x00000028
/* CAN2 */
#define	EE_CORTEX_MX_CAN_2_INT_NUM		0x00000029
/* Ethernet */
#define	EE_CORTEX_MX_ETHERNET_INT_NUM		0x0000002A
/* Hibernate */
#define	EE_CORTEX_MX_HIBERNATE_INT_NUM		0x0000002B
/* USB0 */
#define	EE_CORTEX_MX_USB_0_INT_NUM		0x0000002C
/* uDMA Software Transfer */
#define	EE_CORTEX_MX_UDMA_SOFT_TRANSF_INT_NUM	0x0000002E
/* uDMA Error */
#define	EE_CORTEX_MX_UDMA_ERR_INT_NUM		0x0000002F
/* I2S0 */
#define	EE_CORTEX_MX_I2S_0_INT_NUM		0x00000034
/* External Bus Interface 0 */
#define	EE_CORTEX_MX_EXT_BUS_0_INT_NUM		0x00000035
/* FPU */
#define	EE_CORTEX_MX_FPU_INT_NUM		0x0000006A
/* PECI 0 */
#define	EE_CORTEX_MX_PECI_0_INT_NUM		0x0000006B
/* LPC 0 */
#define	EE_CORTEX_MX_LCP_0_INT_NUM		0x0000006C
/* Fan 0 */
#define	EE_CORTEX_MX_FAN_0_INT_NUM		0x00000072


/* Register Shift-Bits Number */
#define	NVIC_REG_S	2

/* NVIC Interrupt Registers Base Address */
#define	NVIC_INT_REG_B		(EE_UREG)0xE000E100

/* NVIC Interrupt Register Mask */
#define	NVIC_INT_REG_M		(EE_UREG)0x0000001F

/* NVIC Interrupt Register Shift-Bits Number */
#define	NVIC_INT_REG_S		(EE_UREG)0x00000005

/* NVIC Interrupt Register Number */
#define	NVIC_INT_REG_N(_int)	\
	(((EE_UREG)_int >> NVIC_INT_REG_S) << NVIC_REG_S)

/* NVIC Interrupt Register */
#define	NVIC_INT_REG(_int,_base)	\
	(*((volatile EE_UREG *)(_base + NVIC_INT_REG_N(_int))))

/* NVIC Interrupt Mask */
#define	NVIC_INT_M(_int)	\
	((EE_UREG)0x00000001 << ((EE_UREG)_int & NVIC_INT_REG_M))

/* NVIC Interrupt Priority Registers Base Address */
#define	NVIC_INT_PRI_REG_B	(EE_UREG)0xE000E400

/* NVIC Interrupt Priority Register Mask */
#define	NVIC_INT_PRI_REG_M	(EE_UREG)0x00000003

/* NVIC Interrupt Priority Register Shift-Bits Number */
#define	NVIC_INT_PRI_REG_S	(EE_UREG)0x00000002

/* NVIC Interrupt Priority Register Number */
#define	NVIC_INT_PRI_REG_N(_int)	\
	(((EE_UREG)_int >> NVIC_INT_PRI_REG_S) << NVIC_REG_S)

/* NVIC Interrupt Priority Register */
#define	NVIC_INT_PRI_REG(_int) \
	(*((volatile EE_UREG *)(NVIC_INT_PRI_REG_B + NVIC_INT_PRI_REG_N(_int))))

/* NVIC Interrupt Priority Mask */
#define	NVIC_INT_PRI_M(_int)	(\
  (EE_UREG)0x000000E0 << (\
    ((EE_UREG)_int & NVIC_INT_PRI_REG_M) << NVIC_INT_PRI_REG_M\
  )\
)

/* NVIC Interrupt Priority Shift-Bits Number */
#define	NVIC_INT_PRI_S		(EE_UREG)0x00000005

/* NVIC Interrupt Priority */
#define	NVIC_INT_PRI(_int,_pri)	(\
  ((EE_UREG)_pri << NVIC_INT_PRI_S) << (\
    ((EE_UREG)_int & NVIC_INT_PRI_REG_M) << NVIC_INT_PRI_REG_M\
  )\
)

/* NVIC Interrupt Set Pending Registers Base Address */
#define	NVIC_INT_SET_PENDING_REG_B	(EE_UREG)0xE000E200

/* NVIC Interrupt Clear Pending Registers Base Address */
#define	NVIC_INT_CLR_PENDING_REG_B	(EE_UREG)0xE000E280

/* NVIC Enable Interrupt */
#define	NVIC_INT_ENABLE(_int)	(\
	NVIC_INT_REG(_int, NVIC_INT_REG_B) |= NVIC_INT_M(_int)\
)

/* NVIC Disable Interrupt */
#define	NVIC_INT_DISABLE(_int)	(\
	NVIC_INT_REG(_int, NVIC_INT_REG_B) &= ~NVIC_INT_M(_int))

/* NVIC Clear Priority */
#define	NVIC_CLR_PRI(_int)	\
	(NVIC_INT_PRI_REG(_int) &= ~NVIC_INT_PRI_M(_int)\
)

/* NVIC Set Priority */
#define	NVIC_SET_PRI(_int,_pri)	{\
	NVIC_CLR_PRI(_int);\
	(\
	  NVIC_INT_PRI_REG(_int) |= (\
	    NVIC_INT_PRI_M(_int) & NVIC_INT_PRI(_int, _pri)\
	  )\
	);\
}

/* NVIC Set Pending Interrupt */
#define	NVIC_INT_SET_PENDING(_int)	(\
	NVIC_INT_REG(_int, NVIC_INT_SET_PENDING_REG_B) |= NVIC_INT_M(_int)\
)

/* NVIC Clear Pending Interrupt */
#define	NVIC_INT_CLR_PENDING(_int)	(\
	NVIC_INT_REG(_int, NVIC_INT_CLR_PENDING_REG_B) |= NVIC_INT_M(_int)\
)

#endif /* __INCLUDE_CORTEX_MX_NVIC_H__ */
