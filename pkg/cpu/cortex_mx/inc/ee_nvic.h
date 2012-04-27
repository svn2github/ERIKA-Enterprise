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

/* NVIC registers (NVIC) */
#define NVIC_INT_TYPE_R         (*((volatile EE_UREG *)0xE000E004))
#define NVIC_ACTLR_R            (*((volatile EE_UREG *)0xE000E008))
#define NVIC_ST_CTRL_R          (*((volatile EE_UREG *)0xE000E010))
#define NVIC_ST_RELOAD_R        (*((volatile EE_UREG *)0xE000E014))
#define NVIC_ST_CURRENT_R       (*((volatile EE_UREG *)0xE000E018))
#define NVIC_ST_CAL_R           (*((volatile EE_UREG *)0xE000E01C))
#define NVIC_EN0_R              (*((volatile EE_UREG *)0xE000E100))
#define NVIC_EN1_R              (*((volatile EE_UREG *)0xE000E104))
#define NVIC_EN2_R              (*((volatile EE_UREG *)0xE000E108))
#define NVIC_EN3_R              (*((volatile EE_UREG *)0xE000E10C))
#define NVIC_EN4_R              (*((volatile EE_UREG *)0xE000E110))
#define NVIC_DIS0_R             (*((volatile EE_UREG *)0xE000E180))
#define NVIC_DIS1_R             (*((volatile EE_UREG *)0xE000E184))
#define NVIC_DIS2_R             (*((volatile EE_UREG *)0xE000E188))
#define NVIC_DIS3_R             (*((volatile EE_UREG *)0xE000E18C))
#define NVIC_DIS4_R             (*((volatile EE_UREG *)0xE000E190))
#define NVIC_PEND0_R            (*((volatile EE_UREG *)0xE000E200))
#define NVIC_PEND1_R            (*((volatile EE_UREG *)0xE000E204))
#define NVIC_PEND2_R            (*((volatile EE_UREG *)0xE000E208))
#define NVIC_PEND3_R            (*((volatile EE_UREG *)0xE000E20C))
#define NVIC_PEND4_R            (*((volatile EE_UREG *)0xE000E210))
#define NVIC_UNPEND0_R          (*((volatile EE_UREG *)0xE000E280))
#define NVIC_UNPEND1_R          (*((volatile EE_UREG *)0xE000E284))
#define NVIC_UNPEND2_R          (*((volatile EE_UREG *)0xE000E288))
#define NVIC_UNPEND3_R          (*((volatile EE_UREG *)0xE000E28C))
#define NVIC_UNPEND4_R          (*((volatile EE_UREG *)0xE000E290))
#define NVIC_ACTIVE0_R          (*((volatile EE_UREG *)0xE000E300))
#define NVIC_ACTIVE1_R          (*((volatile EE_UREG *)0xE000E304))
#define NVIC_ACTIVE2_R          (*((volatile EE_UREG *)0xE000E308))
#define NVIC_ACTIVE3_R          (*((volatile EE_UREG *)0xE000E30C))
#define NVIC_ACTIVE4_R          (*((volatile EE_UREG *)0xE000E310))
#define NVIC_PRI0_R             (*((volatile EE_UREG *)0xE000E400))
#define NVIC_PRI1_R             (*((volatile EE_UREG *)0xE000E404))
#define NVIC_PRI2_R             (*((volatile EE_UREG *)0xE000E408))
#define NVIC_PRI3_R             (*((volatile EE_UREG *)0xE000E40C))
#define NVIC_PRI4_R             (*((volatile EE_UREG *)0xE000E410))
#define NVIC_PRI5_R             (*((volatile EE_UREG *)0xE000E414))
#define NVIC_PRI6_R             (*((volatile EE_UREG *)0xE000E418))
#define NVIC_PRI7_R             (*((volatile EE_UREG *)0xE000E41C))
#define NVIC_PRI8_R             (*((volatile EE_UREG *)0xE000E420))
#define NVIC_PRI9_R             (*((volatile EE_UREG *)0xE000E424))
#define NVIC_PRI10_R            (*((volatile EE_UREG *)0xE000E428))
#define NVIC_PRI11_R            (*((volatile EE_UREG *)0xE000E42C))
#define NVIC_PRI12_R            (*((volatile EE_UREG *)0xE000E430))
#define NVIC_PRI13_R            (*((volatile EE_UREG *)0xE000E434))
#define NVIC_PRI14_R            (*((volatile EE_UREG *)0xE000E438))
#define NVIC_PRI15_R            (*((volatile EE_UREG *)0xE000E43C))
#define NVIC_PRI16_R            (*((volatile EE_UREG *)0xE000E440))
#define NVIC_PRI17_R            (*((volatile EE_UREG *)0xE000E444))
#define NVIC_PRI18_R            (*((volatile EE_UREG *)0xE000E448))
#define NVIC_PRI19_R            (*((volatile EE_UREG *)0xE000E44C))
#define NVIC_PRI20_R            (*((volatile EE_UREG *)0xE000E450))
#define NVIC_PRI21_R            (*((volatile EE_UREG *)0xE000E454))
#define NVIC_PRI22_R            (*((volatile EE_UREG *)0xE000E458))
#define NVIC_PRI23_R            (*((volatile EE_UREG *)0xE000E45C))
#define NVIC_PRI24_R            (*((volatile EE_UREG *)0xE000E460))
#define NVIC_PRI25_R            (*((volatile EE_UREG *)0xE000E464))
#define NVIC_PRI26_R            (*((volatile EE_UREG *)0xE000E468))
#define NVIC_PRI27_R            (*((volatile EE_UREG *)0xE000E46C))
#define NVIC_PRI28_R            (*((volatile EE_UREG *)0xE000E470))
#define NVIC_PRI29_R            (*((volatile EE_UREG *)0xE000E474))
#define NVIC_PRI30_R            (*((volatile EE_UREG *)0xE000E478))
#define NVIC_PRI31_R            (*((volatile EE_UREG *)0xE000E47C))
#define NVIC_PRI32_R            (*((volatile EE_UREG *)0xE000E480))
#define NVIC_CPUID_R            (*((volatile EE_UREG *)0xE000ED00))
#define NVIC_INT_CTRL_R         (*((volatile EE_UREG *)0xE000ED04))
#define NVIC_VTABLE_R           (*((volatile EE_UREG *)0xE000ED08))
#define NVIC_APINT_R            (*((volatile EE_UREG *)0xE000ED0C))
#define NVIC_SYS_CTRL_R         (*((volatile EE_UREG *)0xE000ED10))
#define NVIC_CFG_CTRL_R         (*((volatile EE_UREG *)0xE000ED14))
#define NVIC_SYS_PRI1_R         (*((volatile EE_UREG *)0xE000ED18))
#define NVIC_SYS_PRI2_R         (*((volatile EE_UREG *)0xE000ED1C))
#define NVIC_SYS_PRI3_R         (*((volatile EE_UREG *)0xE000ED20))
#define NVIC_SYS_HND_CTRL_R     (*((volatile EE_UREG *)0xE000ED24))
#define NVIC_FAULT_STAT_R       (*((volatile EE_UREG *)0xE000ED28))
#define NVIC_HFAULT_STAT_R      (*((volatile EE_UREG *)0xE000ED2C))
#define NVIC_DEBUG_STAT_R       (*((volatile EE_UREG *)0xE000ED30))
#define NVIC_MM_ADDR_R          (*((volatile EE_UREG *)0xE000ED34))
#define NVIC_FAULT_ADDR_R       (*((volatile EE_UREG *)0xE000ED38))
#define NVIC_CPAC_R             (*((volatile EE_UREG *)0xE000ED88))
#define NVIC_MPU_TYPE_R         (*((volatile EE_UREG *)0xE000ED90))
#define NVIC_MPU_CTRL_R         (*((volatile EE_UREG *)0xE000ED94))
#define NVIC_MPU_NUMBER_R       (*((volatile EE_UREG *)0xE000ED98))
#define NVIC_MPU_BASE_R         (*((volatile EE_UREG *)0xE000ED9C))
#define NVIC_MPU_ATTR_R         (*((volatile EE_UREG *)0xE000EDA0))
#define NVIC_MPU_BASE1_R        (*((volatile EE_UREG *)0xE000EDA4))
#define NVIC_MPU_ATTR1_R        (*((volatile EE_UREG *)0xE000EDA8))
#define NVIC_MPU_BASE2_R        (*((volatile EE_UREG *)0xE000EDAC))
#define NVIC_MPU_ATTR2_R        (*((volatile EE_UREG *)0xE000EDB0))
#define NVIC_MPU_BASE3_R        (*((volatile EE_UREG *)0xE000EDB4))
#define NVIC_MPU_ATTR3_R        (*((volatile EE_UREG *)0xE000EDB8))
#define NVIC_DBG_CTRL_R         (*((volatile EE_UREG *)0xE000EDF0))
#define NVIC_DBG_XFER_R         (*((volatile EE_UREG *)0xE000EDF4))
#define NVIC_DBG_DATA_R         (*((volatile EE_UREG *)0xE000EDF8))
#define NVIC_DBG_INT_R          (*((volatile EE_UREG *)0xE000EDFC))
#define NVIC_SW_TRIG_R          (*((volatile EE_UREG *)0xE000EF00))
#define NVIC_FPCC_R             (*((volatile EE_UREG *)0xE000EF34))
#define NVIC_FPCA_R             (*((volatile EE_UREG *)0xE000EF38))
#define NVIC_FPDSC_R            (*((volatile EE_UREG *)0xE000EF3C))

/* The following are defines for the bit fields in the NVIC_INT_TYPE register. */
#define NVIC_INT_TYPE_LINES_M   0x0000001F  // Number of interrupt lines (x32)
#define NVIC_INT_TYPE_LINES_S   0

/* The following are defines for the bit fields in the NVIC_ACTLR register. */
#define NVIC_ACTLR_DISOOFP      0x00000200  // Disable Out-Of-Order Floating
                                            // Point
#define NVIC_ACTLR_DISFPCA      0x00000100  // Disable CONTROL
#define NVIC_ACTLR_DISFOLD      0x00000004  // Disable IT Folding
#define NVIC_ACTLR_DISWBUF      0x00000002  // Disable Write Buffer
#define NVIC_ACTLR_DISMCYC      0x00000001  // Disable Interrupts of Multiple
                                            // Cycle Instructions

/* The following are defines for the bit fields in the NVIC_ST_CTRL register. */
#define NVIC_ST_CTRL_COUNT      0x00010000  // Count Flag
#define NVIC_ST_CTRL_CLK_SRC    0x00000004  // Clock Source
#define NVIC_ST_CTRL_INTEN      0x00000002  // Interrupt Enable
#define NVIC_ST_CTRL_ENABLE     0x00000001  // Enable

/* The following are defines for the bit fields in the NVIC_ST_RELOAD register. */
#define NVIC_ST_RELOAD_M        0x00FFFFFF  // Reload Value
#define NVIC_ST_RELOAD_S        0

/* The following are defines for the bit fields in the NVIC_ST_CURRENT
 * register. */
#define NVIC_ST_CURRENT_M       0x00FFFFFF  // Current Value
#define NVIC_ST_CURRENT_S       0

/* The following are defines for the bit fields in the NVIC_ST_CAL register. */
#define NVIC_ST_CAL_NOREF       0x80000000  // No reference clock
#define NVIC_ST_CAL_SKEW        0x40000000  // Clock skew
#define NVIC_ST_CAL_ONEMS_M     0x00FFFFFF  // 1ms reference value
#define NVIC_ST_CAL_ONEMS_S     0

/* The following are defines for the bit fields in the NVIC_EN0 register. */
#define NVIC_EN0_INT_M          0xFFFFFFFF  // Interrupt Enable
#define NVIC_EN0_INT0           0x00000001  // Interrupt 0 enable
#define NVIC_EN0_INT1           0x00000002  // Interrupt 1 enable
#define NVIC_EN0_INT2           0x00000004  // Interrupt 2 enable
#define NVIC_EN0_INT3           0x00000008  // Interrupt 3 enable
#define NVIC_EN0_INT4           0x00000010  // Interrupt 4 enable
#define NVIC_EN0_INT5           0x00000020  // Interrupt 5 enable
#define NVIC_EN0_INT6           0x00000040  // Interrupt 6 enable
#define NVIC_EN0_INT7           0x00000080  // Interrupt 7 enable
#define NVIC_EN0_INT8           0x00000100  // Interrupt 8 enable
#define NVIC_EN0_INT9           0x00000200  // Interrupt 9 enable
#define NVIC_EN0_INT10          0x00000400  // Interrupt 10 enable
#define NVIC_EN0_INT11          0x00000800  // Interrupt 11 enable
#define NVIC_EN0_INT12          0x00001000  // Interrupt 12 enable
#define NVIC_EN0_INT13          0x00002000  // Interrupt 13 enable
#define NVIC_EN0_INT14          0x00004000  // Interrupt 14 enable
#define NVIC_EN0_INT15          0x00008000  // Interrupt 15 enable
#define NVIC_EN0_INT16          0x00010000  // Interrupt 16 enable
#define NVIC_EN0_INT17          0x00020000  // Interrupt 17 enable
#define NVIC_EN0_INT18          0x00040000  // Interrupt 18 enable
#define NVIC_EN0_INT19          0x00080000  // Interrupt 19 enable
#define NVIC_EN0_INT20          0x00100000  // Interrupt 20 enable
#define NVIC_EN0_INT21          0x00200000  // Interrupt 21 enable
#define NVIC_EN0_INT22          0x00400000  // Interrupt 22 enable
#define NVIC_EN0_INT23          0x00800000  // Interrupt 23 enable
#define NVIC_EN0_INT24          0x01000000  // Interrupt 24 enable
#define NVIC_EN0_INT25          0x02000000  // Interrupt 25 enable
#define NVIC_EN0_INT26          0x04000000  // Interrupt 26 enable
#define NVIC_EN0_INT27          0x08000000  // Interrupt 27 enable
#define NVIC_EN0_INT28          0x10000000  // Interrupt 28 enable
#define NVIC_EN0_INT29          0x20000000  // Interrupt 29 enable
#define NVIC_EN0_INT30          0x40000000  // Interrupt 30 enable
#define NVIC_EN0_INT31          0x80000000  // Interrupt 31 enable

/* The following are defines for the bit fields in the NVIC_EN1 register. */
#define NVIC_EN1_INT_M          0xFFFFFFFF  // Interrupt Enable

/* The following are defines for the bit fields in the NVIC_EN2 register. */
#define NVIC_EN2_INT_M          0xFFFFFFFF  // Interrupt Enable

/* The following are defines for the bit fields in the NVIC_EN3 register. */
#define NVIC_EN3_INT_M          0xFFFFFFFF  // Interrupt Enable

/* The following are defines for the bit fields in the NVIC_EN4 register. */
#define NVIC_EN4_INT_M          0x0000000F  // Interrupt Enable

/* The following are defines for the bit fields in the NVIC_DIS0 register. */
#define NVIC_DIS0_INT_M         0xFFFFFFFF  // Interrupt Disable
#define NVIC_DIS0_INT0          0x00000001  // Interrupt 0 disable
#define NVIC_DIS0_INT1          0x00000002  // Interrupt 1 disable
#define NVIC_DIS0_INT2          0x00000004  // Interrupt 2 disable
#define NVIC_DIS0_INT3          0x00000008  // Interrupt 3 disable
#define NVIC_DIS0_INT4          0x00000010  // Interrupt 4 disable
#define NVIC_DIS0_INT5          0x00000020  // Interrupt 5 disable
#define NVIC_DIS0_INT6          0x00000040  // Interrupt 6 disable
#define NVIC_DIS0_INT7          0x00000080  // Interrupt 7 disable
#define NVIC_DIS0_INT8          0x00000100  // Interrupt 8 disable
#define NVIC_DIS0_INT9          0x00000200  // Interrupt 9 disable
#define NVIC_DIS0_INT10         0x00000400  // Interrupt 10 disable
#define NVIC_DIS0_INT11         0x00000800  // Interrupt 11 disable
#define NVIC_DIS0_INT12         0x00001000  // Interrupt 12 disable
#define NVIC_DIS0_INT13         0x00002000  // Interrupt 13 disable
#define NVIC_DIS0_INT14         0x00004000  // Interrupt 14 disable
#define NVIC_DIS0_INT15         0x00008000  // Interrupt 15 disable
#define NVIC_DIS0_INT16         0x00010000  // Interrupt 16 disable
#define NVIC_DIS0_INT17         0x00020000  // Interrupt 17 disable
#define NVIC_DIS0_INT18         0x00040000  // Interrupt 18 disable
#define NVIC_DIS0_INT19         0x00080000  // Interrupt 19 disable
#define NVIC_DIS0_INT20         0x00100000  // Interrupt 20 disable
#define NVIC_DIS0_INT21         0x00200000  // Interrupt 21 disable
#define NVIC_DIS0_INT22         0x00400000  // Interrupt 22 disable
#define NVIC_DIS0_INT23         0x00800000  // Interrupt 23 disable
#define NVIC_DIS0_INT24         0x01000000  // Interrupt 24 disable
#define NVIC_DIS0_INT25         0x02000000  // Interrupt 25 disable
#define NVIC_DIS0_INT26         0x04000000  // Interrupt 26 disable
#define NVIC_DIS0_INT27         0x08000000  // Interrupt 27 disable
#define NVIC_DIS0_INT28         0x10000000  // Interrupt 28 disable
#define NVIC_DIS0_INT29         0x20000000  // Interrupt 29 disable
#define NVIC_DIS0_INT30         0x40000000  // Interrupt 30 disable
#define NVIC_DIS0_INT31         0x80000000  // Interrupt 31 disable

/* The following are defines for the bit fields in the NVIC_DIS1 register. */
#define NVIC_DIS1_INT_M         0xFFFFFFFF  // Interrupt Disable

/* The following are defines for the bit fields in the NVIC_DIS2 register. */
#define NVIC_DIS2_INT_M         0xFFFFFFFF  // Interrupt Disable

/* The following are defines for the bit fields in the NVIC_DIS3 register. */
#define NVIC_DIS3_INT_M         0xFFFFFFFF  // Interrupt Disable

/* The following are defines for the bit fields in the NVIC_DIS4 register. */
#define NVIC_DIS4_INT_M         0x0000000F  // Interrupt Disable

/* The following are defines for the bit fields in the NVIC_PEND0 register. */
#define NVIC_PEND0_INT_M        0xFFFFFFFF  // Interrupt Set Pending
#define NVIC_PEND0_INT0         0x00000001  // Interrupt 0 pend
#define NVIC_PEND0_INT1         0x00000002  // Interrupt 1 pend
#define NVIC_PEND0_INT2         0x00000004  // Interrupt 2 pend
#define NVIC_PEND0_INT3         0x00000008  // Interrupt 3 pend
#define NVIC_PEND0_INT4         0x00000010  // Interrupt 4 pend
#define NVIC_PEND0_INT5         0x00000020  // Interrupt 5 pend
#define NVIC_PEND0_INT6         0x00000040  // Interrupt 6 pend
#define NVIC_PEND0_INT7         0x00000080  // Interrupt 7 pend
#define NVIC_PEND0_INT8         0x00000100  // Interrupt 8 pend
#define NVIC_PEND0_INT9         0x00000200  // Interrupt 9 pend
#define NVIC_PEND0_INT10        0x00000400  // Interrupt 10 pend
#define NVIC_PEND0_INT11        0x00000800  // Interrupt 11 pend
#define NVIC_PEND0_INT12        0x00001000  // Interrupt 12 pend
#define NVIC_PEND0_INT13        0x00002000  // Interrupt 13 pend
#define NVIC_PEND0_INT14        0x00004000  // Interrupt 14 pend
#define NVIC_PEND0_INT15        0x00008000  // Interrupt 15 pend
#define NVIC_PEND0_INT16        0x00010000  // Interrupt 16 pend
#define NVIC_PEND0_INT17        0x00020000  // Interrupt 17 pend
#define NVIC_PEND0_INT18        0x00040000  // Interrupt 18 pend
#define NVIC_PEND0_INT19        0x00080000  // Interrupt 19 pend
#define NVIC_PEND0_INT20        0x00100000  // Interrupt 20 pend
#define NVIC_PEND0_INT21        0x00200000  // Interrupt 21 pend
#define NVIC_PEND0_INT22        0x00400000  // Interrupt 22 pend
#define NVIC_PEND0_INT23        0x00800000  // Interrupt 23 pend
#define NVIC_PEND0_INT24        0x01000000  // Interrupt 24 pend
#define NVIC_PEND0_INT25        0x02000000  // Interrupt 25 pend
#define NVIC_PEND0_INT26        0x04000000  // Interrupt 26 pend
#define NVIC_PEND0_INT27        0x08000000  // Interrupt 27 pend
#define NVIC_PEND0_INT28        0x10000000  // Interrupt 28 pend
#define NVIC_PEND0_INT29        0x20000000  // Interrupt 29 pend
#define NVIC_PEND0_INT30        0x40000000  // Interrupt 30 pend
#define NVIC_PEND0_INT31        0x80000000  // Interrupt 31 pend

/* The following are defines for the bit fields in the NVIC_PEND1 register. */
#define NVIC_PEND1_INT_M        0xFFFFFFFF  // Interrupt Set Pending

/* The following are defines for the bit fields in the NVIC_PEND2 register. */
#define NVIC_PEND2_INT_M        0xFFFFFFFF  // Interrupt Set Pending

/* The following are defines for the bit fields in the NVIC_PEND3 register. */
#define NVIC_PEND3_INT_M        0xFFFFFFFF  // Interrupt Set Pending

/* The following are defines for the bit fields in the NVIC_PEND4 register. */
#define NVIC_PEND4_INT_M        0x0000000F  // Interrupt Set Pending

/* The following are defines for the bit fields in the NVIC_UNPEND0 register. */
#define NVIC_UNPEND0_INT_M      0xFFFFFFFF  // Interrupt Clear Pending
#define NVIC_UNPEND0_INT0       0x00000001  // Interrupt 0 unpend
#define NVIC_UNPEND0_INT1       0x00000002  // Interrupt 1 unpend
#define NVIC_UNPEND0_INT2       0x00000004  // Interrupt 2 unpend
#define NVIC_UNPEND0_INT3       0x00000008  // Interrupt 3 unpend
#define NVIC_UNPEND0_INT4       0x00000010  // Interrupt 4 unpend
#define NVIC_UNPEND0_INT5       0x00000020  // Interrupt 5 unpend
#define NVIC_UNPEND0_INT6       0x00000040  // Interrupt 6 unpend
#define NVIC_UNPEND0_INT7       0x00000080  // Interrupt 7 unpend
#define NVIC_UNPEND0_INT8       0x00000100  // Interrupt 8 unpend
#define NVIC_UNPEND0_INT9       0x00000200  // Interrupt 9 unpend
#define NVIC_UNPEND0_INT10      0x00000400  // Interrupt 10 unpend
#define NVIC_UNPEND0_INT11      0x00000800  // Interrupt 11 unpend
#define NVIC_UNPEND0_INT12      0x00001000  // Interrupt 12 unpend
#define NVIC_UNPEND0_INT13      0x00002000  // Interrupt 13 unpend
#define NVIC_UNPEND0_INT14      0x00004000  // Interrupt 14 unpend
#define NVIC_UNPEND0_INT15      0x00008000  // Interrupt 15 unpend
#define NVIC_UNPEND0_INT16      0x00010000  // Interrupt 16 unpend
#define NVIC_UNPEND0_INT17      0x00020000  // Interrupt 17 unpend
#define NVIC_UNPEND0_INT18      0x00040000  // Interrupt 18 unpend
#define NVIC_UNPEND0_INT19      0x00080000  // Interrupt 19 unpend
#define NVIC_UNPEND0_INT20      0x00100000  // Interrupt 20 unpend
#define NVIC_UNPEND0_INT21      0x00200000  // Interrupt 21 unpend
#define NVIC_UNPEND0_INT22      0x00400000  // Interrupt 22 unpend
#define NVIC_UNPEND0_INT23      0x00800000  // Interrupt 23 unpend
#define NVIC_UNPEND0_INT24      0x01000000  // Interrupt 24 unpend
#define NVIC_UNPEND0_INT25      0x02000000  // Interrupt 25 unpend
#define NVIC_UNPEND0_INT26      0x04000000  // Interrupt 26 unpend
#define NVIC_UNPEND0_INT27      0x08000000  // Interrupt 27 unpend
#define NVIC_UNPEND0_INT28      0x10000000  // Interrupt 28 unpend
#define NVIC_UNPEND0_INT29      0x20000000  // Interrupt 29 unpend
#define NVIC_UNPEND0_INT30      0x40000000  // Interrupt 30 unpend
#define NVIC_UNPEND0_INT31      0x80000000  // Interrupt 31 unpend

/* The following are defines for the bit fields in the NVIC_UNPEND1 register. */
#define NVIC_UNPEND1_INT_M      0xFFFFFFFF  // Interrupt Clear Pending
#define NVIC_UNPEND1_INT32      0x00000001  // Interrupt 32 unpend
#define NVIC_UNPEND1_INT33      0x00000002  // Interrupt 33 unpend
#define NVIC_UNPEND1_INT34      0x00000004  // Interrupt 34 unpend
#define NVIC_UNPEND1_INT35      0x00000008  // Interrupt 35 unpend
#define NVIC_UNPEND1_INT36      0x00000010  // Interrupt 36 unpend
#define NVIC_UNPEND1_INT37      0x00000020  // Interrupt 37 unpend
#define NVIC_UNPEND1_INT38      0x00000040  // Interrupt 38 unpend
#define NVIC_UNPEND1_INT39      0x00000080  // Interrupt 39 unpend
#define NVIC_UNPEND1_INT40      0x00000100  // Interrupt 40 unpend
#define NVIC_UNPEND1_INT41      0x00000200  // Interrupt 41 unpend
#define NVIC_UNPEND1_INT42      0x00000400  // Interrupt 42 unpend
#define NVIC_UNPEND1_INT43      0x00000800  // Interrupt 43 unpend
#define NVIC_UNPEND1_INT44      0x00001000  // Interrupt 44 unpend
#define NVIC_UNPEND1_INT45      0x00002000  // Interrupt 45 unpend
#define NVIC_UNPEND1_INT46      0x00004000  // Interrupt 46 unpend
#define NVIC_UNPEND1_INT47      0x00008000  // Interrupt 47 unpend
#define NVIC_UNPEND1_INT48      0x00010000  // Interrupt 48 unpend
#define NVIC_UNPEND1_INT49      0x00020000  // Interrupt 49 unpend
#define NVIC_UNPEND1_INT50      0x00040000  // Interrupt 50 unpend
#define NVIC_UNPEND1_INT51      0x00080000  // Interrupt 51 unpend
#define NVIC_UNPEND1_INT52      0x00100000  // Interrupt 52 unpend
#define NVIC_UNPEND1_INT53      0x00200000  // Interrupt 53 unpend
#define NVIC_UNPEND1_INT54      0x00400000  // Interrupt 54 unpend
#define NVIC_UNPEND1_INT55      0x00800000  // Interrupt 55 unpend

/* The following are defines for the bit fields in the NVIC_UNPEND2 register. */
#define NVIC_UNPEND2_INT_M      0xFFFFFFFF  // Interrupt Clear Pending

/* The following are defines for the bit fields in the NVIC_UNPEND3 register. */
#define NVIC_UNPEND3_INT_M      0xFFFFFFFF  // Interrupt Clear Pending

/* The following are defines for the bit fields in the NVIC_UNPEND4 register. */
#define NVIC_UNPEND4_INT_M      0x0000000F  // Interrupt Clear Pending

/* The following are defines for the bit fields in the NVIC_ACTIVE0 register. */
#define NVIC_ACTIVE0_INT_M      0xFFFFFFFF  // Interrupt Active
#define NVIC_ACTIVE0_INT0       0x00000001  // Interrupt 0 active
#define NVIC_ACTIVE0_INT1       0x00000002  // Interrupt 1 active
#define NVIC_ACTIVE0_INT2       0x00000004  // Interrupt 2 active
#define NVIC_ACTIVE0_INT3       0x00000008  // Interrupt 3 active
#define NVIC_ACTIVE0_INT4       0x00000010  // Interrupt 4 active
#define NVIC_ACTIVE0_INT5       0x00000020  // Interrupt 5 active
#define NVIC_ACTIVE0_INT6       0x00000040  // Interrupt 6 active
#define NVIC_ACTIVE0_INT7       0x00000080  // Interrupt 7 active
#define NVIC_ACTIVE0_INT8       0x00000100  // Interrupt 8 active
#define NVIC_ACTIVE0_INT9       0x00000200  // Interrupt 9 active
#define NVIC_ACTIVE0_INT10      0x00000400  // Interrupt 10 active
#define NVIC_ACTIVE0_INT11      0x00000800  // Interrupt 11 active
#define NVIC_ACTIVE0_INT12      0x00001000  // Interrupt 12 active
#define NVIC_ACTIVE0_INT13      0x00002000  // Interrupt 13 active
#define NVIC_ACTIVE0_INT14      0x00004000  // Interrupt 14 active
#define NVIC_ACTIVE0_INT15      0x00008000  // Interrupt 15 active
#define NVIC_ACTIVE0_INT16      0x00010000  // Interrupt 16 active
#define NVIC_ACTIVE0_INT17      0x00020000  // Interrupt 17 active
#define NVIC_ACTIVE0_INT18      0x00040000  // Interrupt 18 active
#define NVIC_ACTIVE0_INT19      0x00080000  // Interrupt 19 active
#define NVIC_ACTIVE0_INT20      0x00100000  // Interrupt 20 active
#define NVIC_ACTIVE0_INT21      0x00200000  // Interrupt 21 active
#define NVIC_ACTIVE0_INT22      0x00400000  // Interrupt 22 active
#define NVIC_ACTIVE0_INT23      0x00800000  // Interrupt 23 active
#define NVIC_ACTIVE0_INT24      0x01000000  // Interrupt 24 active
#define NVIC_ACTIVE0_INT25      0x02000000  // Interrupt 25 active
#define NVIC_ACTIVE0_INT26      0x04000000  // Interrupt 26 active
#define NVIC_ACTIVE0_INT27      0x08000000  // Interrupt 27 active
#define NVIC_ACTIVE0_INT28      0x10000000  // Interrupt 28 active
#define NVIC_ACTIVE0_INT29      0x20000000  // Interrupt 29 active
#define NVIC_ACTIVE0_INT30      0x40000000  // Interrupt 30 active
#define NVIC_ACTIVE0_INT31      0x80000000  // Interrupt 31 active

/* The following are defines for the bit fields in the NVIC_ACTIVE1 register. */
#define NVIC_ACTIVE1_INT_M      0xFFFFFFFF  // Interrupt Active

/* The following are defines for the bit fields in the NVIC_ACTIVE2 register. */
#define NVIC_ACTIVE2_INT_M      0xFFFFFFFF  // Interrupt Active

/* The following are defines for the bit fields in the NVIC_ACTIVE3 register. */
#define NVIC_ACTIVE3_INT_M      0xFFFFFFFF  // Interrupt Active

/* The following are defines for the bit fields in the NVIC_ACTIVE4 register. */
#define NVIC_ACTIVE4_INT_M      0x0000000F  // Interrupt Active

/* The following are defines for the bit fields in the NVIC_PRI0 register. */
#define NVIC_PRI0_INT3_M        0xE0000000  // Interrupt 3 Priority Mask
#define NVIC_PRI0_INT2_M        0x00E00000  // Interrupt 2 Priority Mask
#define NVIC_PRI0_INT1_M        0x0000E000  // Interrupt 1 Priority Mask
#define NVIC_PRI0_INT0_M        0x000000E0  // Interrupt 0 Priority Mask
#define NVIC_PRI0_INT3_S        29
#define NVIC_PRI0_INT2_S        21
#define NVIC_PRI0_INT1_S        13
#define NVIC_PRI0_INT0_S        5

/* The following are defines for the bit fields in the NVIC_PRI1 register. */
#define NVIC_PRI1_INT7_M        0xE0000000  // Interrupt 7 Priority Mask
#define NVIC_PRI1_INT6_M        0x00E00000  // Interrupt 6 Priority Mask
#define NVIC_PRI1_INT5_M        0x0000E000  // Interrupt 5 Priority Mask
#define NVIC_PRI1_INT4_M        0x000000E0  // Interrupt 4 Priority Mask
#define NVIC_PRI1_INT7_S        29
#define NVIC_PRI1_INT6_S        21
#define NVIC_PRI1_INT5_S        13
#define NVIC_PRI1_INT4_S        5

/* The following are defines for the bit fields in the NVIC_PRI2 register. */
#define NVIC_PRI2_INT11_M       0xE0000000  // Interrupt 11 Priority Mask
#define NVIC_PRI2_INT10_M       0x00E00000  // Interrupt 10 Priority Mask
#define NVIC_PRI2_INT9_M        0x0000E000  // Interrupt 9 Priority Mask
#define NVIC_PRI2_INT8_M        0x000000E0  // Interrupt 8 Priority Mask
#define NVIC_PRI2_INT11_S       29
#define NVIC_PRI2_INT10_S       21
#define NVIC_PRI2_INT9_S        13
#define NVIC_PRI2_INT8_S        5

/* The following are defines for the bit fields in the NVIC_PRI3 register. */
#define NVIC_PRI3_INT15_M       0xE0000000  // Interrupt 15 Priority Mask
#define NVIC_PRI3_INT14_M       0x00E00000  // Interrupt 14 Priority Mask
#define NVIC_PRI3_INT13_M       0x0000E000  // Interrupt 13 Priority Mask
#define NVIC_PRI3_INT12_M       0x000000E0  // Interrupt 12 Priority Mask
#define NVIC_PRI3_INT15_S       29
#define NVIC_PRI3_INT14_S       21
#define NVIC_PRI3_INT13_S       13
#define NVIC_PRI3_INT12_S       5

/* The following are defines for the bit fields in the NVIC_PRI4 register. */
#define NVIC_PRI4_INT19_M       0xE0000000  // Interrupt 19 Priority Mask
#define NVIC_PRI4_INT18_M       0x00E00000  // Interrupt 18 Priority Mask
#define NVIC_PRI4_INT17_M       0x0000E000  // Interrupt 17 Priority Mask
#define NVIC_PRI4_INT16_M       0x000000E0  // Interrupt 16 Priority Mask
#define NVIC_PRI4_INT19_S       29
#define NVIC_PRI4_INT18_S       21
#define NVIC_PRI4_INT17_S       13
#define NVIC_PRI4_INT16_S       5

/* The following are defines for the bit fields in the NVIC_PRI5 register. */
#define NVIC_PRI5_INT23_M       0xE0000000  // Interrupt 23 Priority Mask
#define NVIC_PRI5_INT22_M       0x00E00000  // Interrupt 22 Priority Mask
#define NVIC_PRI5_INT21_M       0x0000E000  // Interrupt 21 Priority Mask
#define NVIC_PRI5_INT20_M       0x000000E0  // Interrupt 20 Priority Mask
#define NVIC_PRI5_INT23_S       29
#define NVIC_PRI5_INT22_S       21
#define NVIC_PRI5_INT21_S       13
#define NVIC_PRI5_INT20_S       5

/* The following are defines for the bit fields in the NVIC_PRI6 register. */
#define NVIC_PRI6_INT27_M       0xE0000000  // Interrupt 27 Priority Mask
#define NVIC_PRI6_INT26_M       0x00E00000  // Interrupt 26 Priority Mask
#define NVIC_PRI6_INT25_M       0x0000E000  // Interrupt 25 Priority Mask
#define NVIC_PRI6_INT24_M       0x000000E0  // Interrupt 24 Priority Mask
#define NVIC_PRI6_INT27_S       29
#define NVIC_PRI6_INT26_S       21
#define NVIC_PRI6_INT25_S       13
#define NVIC_PRI6_INT24_S       5

/* The following are defines for the bit fields in the NVIC_PRI7 register. */
#define NVIC_PRI7_INT31_M       0xE0000000  // Interrupt 31 Priority Mask
#define NVIC_PRI7_INT30_M       0x00E00000  // Interrupt 30 Priority Mask
#define NVIC_PRI7_INT29_M       0x0000E000  // Interrupt 29 Priority Mask
#define NVIC_PRI7_INT28_M       0x000000E0  // Interrupt 28 Priority Mask
#define NVIC_PRI7_INT31_S       29
#define NVIC_PRI7_INT30_S       21
#define NVIC_PRI7_INT29_S       13
#define NVIC_PRI7_INT28_S       5

/* The following are defines for the bit fields in the NVIC_PRI8 register. */
#define NVIC_PRI8_INT35_M       0xE0000000  // Interrupt 35 Priority Mask
#define NVIC_PRI8_INT34_M       0x00E00000  // Interrupt 34 Priority Mask
#define NVIC_PRI8_INT33_M       0x0000E000  // Interrupt 33 Priority Mask
#define NVIC_PRI8_INT32_M       0x000000E0  // Interrupt 32 Priority Mask
#define NVIC_PRI8_INT35_S       29
#define NVIC_PRI8_INT34_S       21
#define NVIC_PRI8_INT33_S       13
#define NVIC_PRI8_INT32_S       5

/* The following are defines for the bit fields in the NVIC_PRI9 register. */
#define NVIC_PRI9_INT39_M       0xE0000000  // Interrupt 39 Priority Mask
#define NVIC_PRI9_INT38_M       0x00E00000  // Interrupt 38 Priority Mask
#define NVIC_PRI9_INT37_M       0x0000E000  // Interrupt 37 Priority Mask
#define NVIC_PRI9_INT36_M       0x000000E0  // Interrupt 36 Priority Mask
#define NVIC_PRI9_INT39_S       29
#define NVIC_PRI9_INT38_S       21
#define NVIC_PRI9_INT37_S       13
#define NVIC_PRI9_INT36_S       5

/* The following are defines for the bit fields in the NVIC_PRI10 register. */
#define NVIC_PRI10_INT43_M      0xE0000000  // Interrupt 43 Priority Mask
#define NVIC_PRI10_INT42_M      0x00E00000  // Interrupt 42 Priority Mask
#define NVIC_PRI10_INT41_M      0x0000E000  // Interrupt 41 Priority Mask
#define NVIC_PRI10_INT40_M      0x000000E0  // Interrupt 40 Priority Mask
#define NVIC_PRI10_INT43_S      29
#define NVIC_PRI10_INT42_S      21
#define NVIC_PRI10_INT41_S      13
#define NVIC_PRI10_INT40_S      5

/* The following are defines for the bit fields in the NVIC_PRI11 register. */
#define NVIC_PRI11_INT47_M      0xE0000000  // Interrupt 47 Priority Mask
#define NVIC_PRI11_INT46_M      0x00E00000  // Interrupt 46 Priority Mask
#define NVIC_PRI11_INT45_M      0x0000E000  // Interrupt 45 Priority Mask
#define NVIC_PRI11_INT44_M      0x000000E0  // Interrupt 44 Priority Mask
#define NVIC_PRI11_INT47_S      29
#define NVIC_PRI11_INT46_S      21
#define NVIC_PRI11_INT45_S      13
#define NVIC_PRI11_INT44_S      5

/* The following are defines for the bit fields in the NVIC_PRI12 register. */
#define NVIC_PRI12_INT51_M      0xE0000000  // Interrupt 51 Priority Mask
#define NVIC_PRI12_INT50_M      0x00E00000  // Interrupt 50 Priority Mask
#define NVIC_PRI12_INT49_M      0x0000E000  // Interrupt 49 Priority Mask
#define NVIC_PRI12_INT48_M      0x000000E0  // Interrupt 48 Priority Mask
#define NVIC_PRI12_INT51_S      29
#define NVIC_PRI12_INT50_S      21
#define NVIC_PRI12_INT49_S      13
#define NVIC_PRI12_INT48_S      5

/* The following are defines for the bit fields in the NVIC_PRI13 register. */
#define NVIC_PRI13_INT55_M      0xE0000000  // Interrupt 55 Priority Mask
#define NVIC_PRI13_INT54_M      0x00E00000  // Interrupt 54 Priority Mask
#define NVIC_PRI13_INT53_M      0x0000E000  // Interrupt 53 Priority Mask
#define NVIC_PRI13_INT52_M      0x000000E0  // Interrupt 52 Priority Mask
#define NVIC_PRI13_INT55_S      29
#define NVIC_PRI13_INT54_S      21
#define NVIC_PRI13_INT53_S      13
#define NVIC_PRI13_INT52_S      5

/* The following are defines for the bit fields in the NVIC_PRI14 register. */
#define NVIC_PRI14_INTD_M       0xE0000000  // Interrupt 59 Priority Mask
#define NVIC_PRI14_INTC_M       0x00E00000  // Interrupt 58 Priority Mask
#define NVIC_PRI14_INTB_M       0x0000E000  // Interrupt 57 Priority Mask
#define NVIC_PRI14_INTA_M       0x000000E0  // Interrupt 56 Priority Mask
#define NVIC_PRI14_INTD_S       29
#define NVIC_PRI14_INTC_S       21
#define NVIC_PRI14_INTB_S       13
#define NVIC_PRI14_INTA_S       5

/* The following are defines for the bit fields in the NVIC_PRI15 register. */
#define NVIC_PRI15_INTD_M       0xE0000000  // Interrupt 63 Priority Mask
#define NVIC_PRI15_INTC_M       0x00E00000  // Interrupt 62 Priority Mask
#define NVIC_PRI15_INTB_M       0x0000E000  // Interrupt 61 Priority Mask
#define NVIC_PRI15_INTA_M       0x000000E0  // Interrupt 60 Priority Mask
#define NVIC_PRI15_INTD_S       29
#define NVIC_PRI15_INTC_S       21
#define NVIC_PRI15_INTB_S       13
#define NVIC_PRI15_INTA_S       5

/* The following are defines for the bit fields in the NVIC_PRI16 register. */
#define NVIC_PRI16_INTD_M       0xE0000000  // Interrupt 67 Priority Mask
#define NVIC_PRI16_INTC_M       0x00E00000  // Interrupt 66 Priority Mask
#define NVIC_PRI16_INTB_M       0x0000E000  // Interrupt 65 Priority Mask
#define NVIC_PRI16_INTA_M       0x000000E0  // Interrupt 64 Priority Mask
#define NVIC_PRI16_INTD_S       29
#define NVIC_PRI16_INTC_S       21
#define NVIC_PRI16_INTB_S       13
#define NVIC_PRI16_INTA_S       5

/* The following are defines for the bit fields in the NVIC_PRI17 register. */
#define NVIC_PRI17_INTD_M       0xE0000000  // Interrupt 71 Priority Mask
#define NVIC_PRI17_INTC_M       0x00E00000  // Interrupt 70 Priority Mask
#define NVIC_PRI17_INTB_M       0x0000E000  // Interrupt 69 Priority Mask
#define NVIC_PRI17_INTA_M       0x000000E0  // Interrupt 68 Priority Mask
#define NVIC_PRI17_INTD_S       29
#define NVIC_PRI17_INTC_S       21
#define NVIC_PRI17_INTB_S       13
#define NVIC_PRI17_INTA_S       5

/* The following are defines for the bit fields in the NVIC_PRI18 register. */
#define NVIC_PRI18_INTD_M       0xE0000000  // Interrupt 75 Priority Mask
#define NVIC_PRI18_INTC_M       0x00E00000  // Interrupt 74 Priority Mask
#define NVIC_PRI18_INTB_M       0x0000E000  // Interrupt 73 Priority Mask
#define NVIC_PRI18_INTA_M       0x000000E0  // Interrupt 72 Priority Mask
#define NVIC_PRI18_INTD_S       29
#define NVIC_PRI18_INTC_S       21
#define NVIC_PRI18_INTB_S       13
#define NVIC_PRI18_INTA_S       5

/* The following are defines for the bit fields in the NVIC_PRI19 register. */
#define NVIC_PRI19_INTD_M       0xE0000000  // Interrupt 79 Priority Mask
#define NVIC_PRI19_INTC_M       0x00E00000  // Interrupt 78 Priority Mask
#define NVIC_PRI19_INTB_M       0x0000E000  // Interrupt 77 Priority Mask
#define NVIC_PRI19_INTA_M       0x000000E0  // Interrupt 76 Priority Mask
#define NVIC_PRI19_INTD_S       29
#define NVIC_PRI19_INTC_S       21
#define NVIC_PRI19_INTB_S       13
#define NVIC_PRI19_INTA_S       5

/* The following are defines for the bit fields in the NVIC_PRI20 register. */
#define NVIC_PRI20_INTD_M       0xE0000000  // Interrupt 83 Priority Mask
#define NVIC_PRI20_INTC_M       0x00E00000  // Interrupt 82 Priority Mask
#define NVIC_PRI20_INTB_M       0x0000E000  // Interrupt 81 Priority Mask
#define NVIC_PRI20_INTA_M       0x000000E0  // Interrupt 80 Priority Mask
#define NVIC_PRI20_INTD_S       29
#define NVIC_PRI20_INTC_S       21
#define NVIC_PRI20_INTB_S       13
#define NVIC_PRI20_INTA_S       5

/* The following are defines for the bit fields in the NVIC_PRI21 register. */
#define NVIC_PRI21_INTD_M       0xE0000000  // Interrupt 87 Priority Mask
#define NVIC_PRI21_INTC_M       0x00E00000  // Interrupt 86 Priority Mask
#define NVIC_PRI21_INTB_M       0x0000E000  // Interrupt 85 Priority Mask
#define NVIC_PRI21_INTA_M       0x000000E0  // Interrupt 84 Priority Mask
#define NVIC_PRI21_INTD_S       29
#define NVIC_PRI21_INTC_S       21
#define NVIC_PRI21_INTB_S       13
#define NVIC_PRI21_INTA_S       5

/* The following are defines for the bit fields in the NVIC_PRI22 register. */
#define NVIC_PRI22_INTD_M       0xE0000000  // Interrupt 91 Priority Mask
#define NVIC_PRI22_INTC_M       0x00E00000  // Interrupt 90 Priority Mask
#define NVIC_PRI22_INTB_M       0x0000E000  // Interrupt 89 Priority Mask
#define NVIC_PRI22_INTA_M       0x000000E0  // Interrupt 88 Priority Mask
#define NVIC_PRI22_INTD_S       29
#define NVIC_PRI22_INTC_S       21
#define NVIC_PRI22_INTB_S       13
#define NVIC_PRI22_INTA_S       5

/* The following are defines for the bit fields in the NVIC_PRI23 register. */
#define NVIC_PRI23_INTD_M       0xE0000000  // Interrupt 95 Priority Mask
#define NVIC_PRI23_INTC_M       0x00E00000  // Interrupt 94 Priority Mask
#define NVIC_PRI23_INTB_M       0x0000E000  // Interrupt 93 Priority Mask
#define NVIC_PRI23_INTA_M       0x000000E0  // Interrupt 92 Priority Mask
#define NVIC_PRI23_INTD_S       29
#define NVIC_PRI23_INTC_S       21
#define NVIC_PRI23_INTB_S       13
#define NVIC_PRI23_INTA_S       5

/* The following are defines for the bit fields in the NVIC_PRI24 register. */
#define NVIC_PRI24_INTD_M       0xE0000000  // Interrupt 99 Priority Mask
#define NVIC_PRI24_INTC_M       0x00E00000  // Interrupt 98 Priority Mask
#define NVIC_PRI24_INTB_M       0x0000E000  // Interrupt 97 Priority Mask
#define NVIC_PRI24_INTA_M       0x000000E0  // Interrupt 96 Priority Mask
#define NVIC_PRI24_INTD_S       29
#define NVIC_PRI24_INTC_S       21
#define NVIC_PRI24_INTB_S       13
#define NVIC_PRI24_INTA_S       5

/* The following are defines for the bit fields in the NVIC_PRI25 register. */
#define NVIC_PRI25_INTD_M       0xE0000000  // Interrupt 103 Priority Mask
#define NVIC_PRI25_INTC_M       0x00E00000  // Interrupt 102 Priority Mask
#define NVIC_PRI25_INTB_M       0x0000E000  // Interrupt 101 Priority Mask
#define NVIC_PRI25_INTA_M       0x000000E0  // Interrupt 100 Priority Mask
#define NVIC_PRI25_INTD_S       29
#define NVIC_PRI25_INTC_S       21
#define NVIC_PRI25_INTB_S       13
#define NVIC_PRI25_INTA_S       5

/* The following are defines for the bit fields in the NVIC_PRI26 register. */
#define NVIC_PRI26_INTD_M       0xE0000000  // Interrupt 107 Priority Mask
#define NVIC_PRI26_INTC_M       0x00E00000  // Interrupt 106 Priority Mask
#define NVIC_PRI26_INTB_M       0x0000E000  // Interrupt 105 Priority Mask
#define NVIC_PRI26_INTA_M       0x000000E0  // Interrupt 104 Priority Mask
#define NVIC_PRI26_INTD_S       29
#define NVIC_PRI26_INTC_S       21
#define NVIC_PRI26_INTB_S       13
#define NVIC_PRI26_INTA_S       5

/* The following are defines for the bit fields in the NVIC_PRI27 register. */
#define NVIC_PRI27_INTD_M       0xE0000000  // Interrupt 111 Priority Mask
#define NVIC_PRI27_INTC_M       0x00E00000  // Interrupt 110 Priority Mask
#define NVIC_PRI27_INTB_M       0x0000E000  // Interrupt 109 Priority Mask
#define NVIC_PRI27_INTA_M       0x000000E0  // Interrupt 108 Priority Mask
#define NVIC_PRI27_INTD_S       29
#define NVIC_PRI27_INTC_S       21
#define NVIC_PRI27_INTB_S       13
#define NVIC_PRI27_INTA_S       5

/* The following are defines for the bit fields in the NVIC_PRI28 register. */
#define NVIC_PRI28_INTD_M       0xE0000000  // Interrupt 115 Priority Mask
#define NVIC_PRI28_INTC_M       0x00E00000  // Interrupt 114 Priority Mask
#define NVIC_PRI28_INTB_M       0x0000E000  // Interrupt 113 Priority Mask
#define NVIC_PRI28_INTA_M       0x000000E0  // Interrupt 112 Priority Mask
#define NVIC_PRI28_INTD_S       29
#define NVIC_PRI28_INTC_S       21
#define NVIC_PRI28_INTB_S       13
#define NVIC_PRI28_INTA_S       5

/* The following are defines for the bit fields in the NVIC_PRI29 register. */
#define NVIC_PRI29_INTD_M       0xE0000000  // Interrupt 119 Priority Mask
#define NVIC_PRI29_INTC_M       0x00E00000  // Interrupt 118 Priority Mask
#define NVIC_PRI29_INTB_M       0x0000E000  // Interrupt 117 Priority Mask
#define NVIC_PRI29_INTA_M       0x000000E0  // Interrupt 116 Priority Mask
#define NVIC_PRI29_INTD_S       29
#define NVIC_PRI29_INTC_S       21
#define NVIC_PRI29_INTB_S       13
#define NVIC_PRI29_INTA_S       5

/* The following are defines for the bit fields in the NVIC_PRI30 register. */
#define NVIC_PRI30_INTD_M       0xE0000000  // Interrupt 123 Priority Mask
#define NVIC_PRI30_INTC_M       0x00E00000  // Interrupt 122 Priority Mask
#define NVIC_PRI30_INTB_M       0x0000E000  // Interrupt 121 Priority Mask
#define NVIC_PRI30_INTA_M       0x000000E0  // Interrupt 120 Priority Mask
#define NVIC_PRI30_INTD_S       29
#define NVIC_PRI30_INTC_S       21
#define NVIC_PRI30_INTB_S       13
#define NVIC_PRI30_INTA_S       5

/* The following are defines for the bit fields in the NVIC_PRI31 register. */
#define NVIC_PRI31_INTD_M       0xE0000000  // Interrupt 127 Priority Mask
#define NVIC_PRI31_INTC_M       0x00E00000  // Interrupt 126 Priority Mask
#define NVIC_PRI31_INTB_M       0x0000E000  // Interrupt 125 Priority Mask
#define NVIC_PRI31_INTA_M       0x000000E0  // Interrupt 124 Priority Mask
#define NVIC_PRI31_INTD_S       29
#define NVIC_PRI31_INTC_S       21
#define NVIC_PRI31_INTB_S       13
#define NVIC_PRI31_INTA_S       5

/* The following are defines for the bit fields in the NVIC_PRI32 register. */
#define NVIC_PRI32_INTD_M       0xE0000000  // Interrupt 131 Priority Mask
#define NVIC_PRI32_INTC_M       0x00E00000  // Interrupt 130 Priority Mask
#define NVIC_PRI32_INTB_M       0x0000E000  // Interrupt 129 Priority Mask
#define NVIC_PRI32_INTA_M       0x000000E0  // Interrupt 128 Priority Mask
#define NVIC_PRI32_INTD_S       29
#define NVIC_PRI32_INTC_S       21
#define NVIC_PRI32_INTB_S       13
#define NVIC_PRI32_INTA_S       5

/* The following are defines for the bit fields in the NVIC_CPUID register. */
#define NVIC_CPUID_IMP_M        0xFF000000  // Implementer Code
#define NVIC_CPUID_IMP_ARM      0x41000000  // ARM
#define NVIC_CPUID_VAR_M        0x00F00000  // Variant Number
#define NVIC_CPUID_CON_M        0x000F0000  // Constant
#define NVIC_CPUID_PARTNO_M     0x0000FFF0  // Part Number
#define NVIC_CPUID_PARTNO_CM4   0x0000C240  // Cortex-M4 processor
#define NVIC_CPUID_REV_M        0x0000000F  // Revision Number

/* The following are defines for the bit fields in the NVIC_INT_CTRL register. */
#define NVIC_INT_CTRL_NMI_SET   0x80000000  // NMI Set Pending
#define NVIC_INT_CTRL_PEND_SV   0x10000000  // PendSV Set Pending
#define NVIC_INT_CTRL_UNPEND_SV 0x08000000  // PendSV Clear Pending
#define NVIC_INT_CTRL_PENDSTSET 0x04000000  // SysTick Set Pending
#define NVIC_INT_CTRL_PENDSTCLR 0x02000000  // SysTick Clear Pending
#define NVIC_INT_CTRL_ISR_PRE   0x00800000  // Debug Interrupt Handling
#define NVIC_INT_CTRL_ISR_PEND  0x00400000  // Interrupt Pending
#define NVIC_INT_CTRL_VEC_PEN_M 0x000FF000  // Interrupt Pending Vector Number
#define NVIC_INT_CTRL_VEC_PEN_NMI \
                                0x00002000  // NMI
#define NVIC_INT_CTRL_VEC_PEN_HARD \
                                0x00003000  // Hard fault
#define NVIC_INT_CTRL_VEC_PEN_MEM \
                                0x00004000  // Memory management fault
#define NVIC_INT_CTRL_VEC_PEN_BUS \
                                0x00005000  // Bus fault
#define NVIC_INT_CTRL_VEC_PEN_USG \
                                0x00006000  // Usage fault
#define NVIC_INT_CTRL_VEC_PEN_SVC \
                                0x0000B000  // SVCall
#define NVIC_INT_CTRL_VEC_PEN_PNDSV \
                                0x0000E000  // PendSV
#define NVIC_INT_CTRL_VEC_PEN_TICK \
                                0x0000F000  // SysTick
#define NVIC_INT_CTRL_RET_BASE  0x00000800  // Return to Base
#define NVIC_INT_CTRL_VEC_ACT_M 0x000000FF  // Interrupt Pending Vector Number
#define NVIC_INT_CTRL_VEC_ACT_S 0

/* The following are defines for the bit fields in the NVIC_VTABLE register. */
#define NVIC_VTABLE_BASE        0x20000000  // Vector Table Base
#define NVIC_VTABLE_OFFSET_M    0x1FFFFC00  // Vector Table Offset
#define NVIC_VTABLE_OFFSET_S    10

/* The following are defines for the bit fields in the NVIC_APINT register. */
#define NVIC_APINT_VECTKEY_M    0xFFFF0000  // Register Key
#define NVIC_APINT_VECTKEY      0x05FA0000  // Vector key
#define NVIC_APINT_ENDIANESS    0x00008000  // Data Endianess
#define NVIC_APINT_PRIGROUP_M   0x00000700  // Interrupt Priority Grouping
#define NVIC_APINT_PRIGROUP_7_1 0x00000000  // Priority group 7.1 split
#define NVIC_APINT_PRIGROUP_6_2 0x00000100  // Priority group 6.2 split
#define NVIC_APINT_PRIGROUP_5_3 0x00000200  // Priority group 5.3 split
#define NVIC_APINT_PRIGROUP_4_4 0x00000300  // Priority group 4.4 split
#define NVIC_APINT_PRIGROUP_3_5 0x00000400  // Priority group 3.5 split
#define NVIC_APINT_PRIGROUP_2_6 0x00000500  // Priority group 2.6 split
#define NVIC_APINT_PRIGROUP_1_7 0x00000600  // Priority group 1.7 split
#define NVIC_APINT_PRIGROUP_0_8 0x00000700  // Priority group 0.8 split
#define NVIC_APINT_SYSRESETREQ  0x00000004  // System Reset Request
#define NVIC_APINT_VECT_CLR_ACT 0x00000002  // Clear Active NMI / Fault
#define NVIC_APINT_VECT_RESET   0x00000001  // System Reset

/* The following are defines for the bit fields in the NVIC_SYS_CTRL register. */
#define NVIC_SYS_CTRL_SEVONPEND 0x00000010  // Wake Up on Pending
#define NVIC_SYS_CTRL_SLEEPDEEP 0x00000004  // Deep Sleep Enable
#define NVIC_SYS_CTRL_SLEEPEXIT 0x00000002  // Sleep on ISR Exit

/* The following are defines for the bit fields in the NVIC_CFG_CTRL register. */
#define NVIC_CFG_CTRL_STKALIGN  0x00000200  // Stack Alignment on Exception
                                            // Entry
#define NVIC_CFG_CTRL_BFHFNMIGN 0x00000100  // Ignore Bus Fault in NMI and
                                            // Fault
#define NVIC_CFG_CTRL_DIV0      0x00000010  // Trap on Divide by 0
#define NVIC_CFG_CTRL_UNALIGNED 0x00000008  // Trap on Unaligned Access
#define NVIC_CFG_CTRL_MAIN_PEND 0x00000002  // Allow Main Interrupt Trigger
#define NVIC_CFG_CTRL_BASE_THR  0x00000001  // Thread State Control

/* The following are defines for the bit fields in the NVIC_SYS_PRI1 register. */
#define NVIC_SYS_PRI1_USAGE_M   0x00E00000  // Usage Fault Priority
#define NVIC_SYS_PRI1_BUS_M     0x0000E000  // Bus Fault Priority
#define NVIC_SYS_PRI1_MEM_M     0x000000E0  // Memory Management Fault Priority
#define NVIC_SYS_PRI1_USAGE_S   21
#define NVIC_SYS_PRI1_BUS_S     13
#define NVIC_SYS_PRI1_MEM_S     5

/* The following are defines for the bit fields in the NVIC_SYS_PRI2 register. */
#define NVIC_SYS_PRI2_SVC_M     0xE0000000  // SVCall Priority
#define NVIC_SYS_PRI2_SVC_S     29

/* The following are defines for the bit fields in the NVIC_SYS_PRI3 register. */
#define NVIC_SYS_PRI3_TICK_M    0xE0000000  // SysTick Exception Priority
#define NVIC_SYS_PRI3_PENDSV_M  0x00E00000  // PendSV Priority
#define NVIC_SYS_PRI3_DEBUG_M   0x000000E0  // Debug Priority
#define NVIC_SYS_PRI3_TICK_S    29
#define NVIC_SYS_PRI3_PENDSV_S  21
#define NVIC_SYS_PRI3_DEBUG_S   5

/* The following are defines for the bit fields in the NVIC_SYS_HND_CTRL
 * register. */
#define NVIC_SYS_HND_CTRL_USAGE 0x00040000  // Usage Fault Enable
#define NVIC_SYS_HND_CTRL_BUS   0x00020000  // Bus Fault Enable
#define NVIC_SYS_HND_CTRL_MEM   0x00010000  // Memory Management Fault Enable
#define NVIC_SYS_HND_CTRL_SVC   0x00008000  // SVC Call Pending
#define NVIC_SYS_HND_CTRL_BUSP  0x00004000  // Bus Fault Pending
#define NVIC_SYS_HND_CTRL_MEMP  0x00002000  // Memory Management Fault Pending
#define NVIC_SYS_HND_CTRL_USAGEP \
                                0x00001000  // Usage Fault Pending
#define NVIC_SYS_HND_CTRL_TICK  0x00000800  // SysTick Exception Active
#define NVIC_SYS_HND_CTRL_PNDSV 0x00000400  // PendSV Exception Active
#define NVIC_SYS_HND_CTRL_MON   0x00000100  // Debug Monitor Active
#define NVIC_SYS_HND_CTRL_SVCA  0x00000080  // SVC Call Active
#define NVIC_SYS_HND_CTRL_USGA  0x00000008  // Usage Fault Active
#define NVIC_SYS_HND_CTRL_BUSA  0x00000002  // Bus Fault Active
#define NVIC_SYS_HND_CTRL_MEMA  0x00000001  // Memory Management Fault Active

/* The following are defines for the bit fields in the NVIC_FAULT_STAT
 * register. */
#define NVIC_FAULT_STAT_DIV0    0x02000000  // Divide-by-Zero Usage Fault
#define NVIC_FAULT_STAT_UNALIGN 0x01000000  // Unaligned Access Usage Fault
#define NVIC_FAULT_STAT_NOCP    0x00080000  // No Coprocessor Usage Fault
#define NVIC_FAULT_STAT_INVPC   0x00040000  // Invalid PC Load Usage Fault
#define NVIC_FAULT_STAT_INVSTAT 0x00020000  // Invalid State Usage Fault
#define NVIC_FAULT_STAT_UNDEF   0x00010000  // Undefined Instruction Usage
                                            // Fault
#define NVIC_FAULT_STAT_BFARV   0x00008000  // Bus Fault Address Register Valid
#define NVIC_FAULT_STAT_BLSPERR 0x00002000  // Bus Fault on Floating-Point Lazy
                                            // State Preservation
#define NVIC_FAULT_STAT_BSTKE   0x00001000  // Stack Bus Fault
#define NVIC_FAULT_STAT_BUSTKE  0x00000800  // Unstack Bus Fault
#define NVIC_FAULT_STAT_IMPRE   0x00000400  // Imprecise Data Bus Error
#define NVIC_FAULT_STAT_PRECISE 0x00000200  // Precise Data Bus Error
#define NVIC_FAULT_STAT_IBUS    0x00000100  // Instruction Bus Error
#define NVIC_FAULT_STAT_MMARV   0x00000080  // Memory Management Fault Address
                                            // Register Valid
#define NVIC_FAULT_STAT_MLSPERR 0x00000020  // Memory Management Fault on
                                            // Floating-Point Lazy State
                                            // Preservation
#define NVIC_FAULT_STAT_MSTKE   0x00000010  // Stack Access Violation
#define NVIC_FAULT_STAT_MUSTKE  0x00000008  // Unstack Access Violation
#define NVIC_FAULT_STAT_DERR    0x00000002  // Data Access Violation
#define NVIC_FAULT_STAT_IERR    0x00000001  // Instruction Access Violation

/* The following are defines for the bit fields in the NVIC_HFAULT_STAT
 * register. */
#define NVIC_HFAULT_STAT_DBG    0x80000000  // Debug Event
#define NVIC_HFAULT_STAT_FORCED 0x40000000  // Forced Hard Fault
#define NVIC_HFAULT_STAT_VECT   0x00000002  // Vector Table Read Fault

/* The following are defines for the bit fields in the NVIC_DEBUG_STAT
 * register. */
#define NVIC_DEBUG_STAT_EXTRNL  0x00000010  // EDBGRQ asserted
#define NVIC_DEBUG_STAT_VCATCH  0x00000008  // Vector catch
#define NVIC_DEBUG_STAT_DWTTRAP 0x00000004  // DWT match
#define NVIC_DEBUG_STAT_BKPT    0x00000002  // Breakpoint instruction
#define NVIC_DEBUG_STAT_HALTED  0x00000001  // Halt request

/* The following are defines for the bit fields in the NVIC_MM_ADDR register. */
#define NVIC_MM_ADDR_M          0xFFFFFFFF  // Fault Address
#define NVIC_MM_ADDR_S          0

/* The following are defines for the bit fields in the NVIC_FAULT_ADDR
 * register. */
#define NVIC_FAULT_ADDR_M       0xFFFFFFFF  // Fault Address
#define NVIC_FAULT_ADDR_S       0

/* The following are defines for the bit fields in the NVIC_CPAC register. */
#define NVIC_CPAC_CP11_M        0x00C00000  // CP11 Coprocessor Access
                                            // Privilege
#define NVIC_CPAC_CP11_DIS      0x00000000  // Access Denied
#define NVIC_CPAC_CP11_PRIV     0x00400000  // Privileged Access Only
#define NVIC_CPAC_CP11_FULL     0x00C00000  // Full Access
#define NVIC_CPAC_CP10_M        0x00300000  // CP10 Coprocessor Access
                                            // Privilege
#define NVIC_CPAC_CP10_DIS      0x00000000  // Access Denied
#define NVIC_CPAC_CP10_PRIV     0x00100000  // Privileged Access Only
#define NVIC_CPAC_CP10_FULL     0x00300000  // Full Access

/* The following are defines for the bit fields in the NVIC_MPU_TYPE register. */
#define NVIC_MPU_TYPE_IREGION_M 0x00FF0000  // Number of I Regions
#define NVIC_MPU_TYPE_DREGION_M 0x0000FF00  // Number of D Regions
#define NVIC_MPU_TYPE_SEPARATE  0x00000001  // Separate or Unified MPU
#define NVIC_MPU_TYPE_IREGION_S 16
#define NVIC_MPU_TYPE_DREGION_S 8

/* The following are defines for the bit fields in the NVIC_MPU_CTRL register. */
#define NVIC_MPU_CTRL_PRIVDEFEN 0x00000004  // MPU Default Region
#define NVIC_MPU_CTRL_HFNMIENA  0x00000002  // MPU Enabled During Faults
#define NVIC_MPU_CTRL_ENABLE    0x00000001  // MPU Enable

/* The following are defines for the bit fields in the NVIC_MPU_NUMBER
 * register. */
#define NVIC_MPU_NUMBER_M       0x00000007  // MPU Region to Access
#define NVIC_MPU_NUMBER_S       0

/* The following are defines for the bit fields in the NVIC_MPU_BASE register. */
#define NVIC_MPU_BASE_ADDR_M    0xFFFFFFE0  // Base Address Mask
#define NVIC_MPU_BASE_VALID     0x00000010  // Region Number Valid
#define NVIC_MPU_BASE_REGION_M  0x00000007  // Region Number
#define NVIC_MPU_BASE_ADDR_S    5
#define NVIC_MPU_BASE_REGION_S  0

/* The following are defines for the bit fields in the NVIC_MPU_ATTR register. */
#define NVIC_MPU_ATTR_XN        0x10000000  // Instruction Access Disable
#define NVIC_MPU_ATTR_AP_M      0x07000000  // Access Privilege
#define NVIC_MPU_ATTR_TEX_M     0x00380000  // Type Extension Mask
#define NVIC_MPU_ATTR_SHAREABLE 0x00040000  // Shareable
#define NVIC_MPU_ATTR_CACHEABLE 0x00020000  // Cacheable
#define NVIC_MPU_ATTR_BUFFRABLE 0x00010000  // Bufferable
#define NVIC_MPU_ATTR_SRD_M     0x0000FF00  // Subregion Disable Bits
#define NVIC_MPU_ATTR_SIZE_M    0x0000003E  // Region Size Mask
#define NVIC_MPU_ATTR_ENABLE    0x00000001  // Region Enable

/* The following are defines for the bit fields in the NVIC_MPU_BASE1 register. */
#define NVIC_MPU_BASE1_ADDR_M   0xFFFFFFE0  // Base Address Mask
#define NVIC_MPU_BASE1_VALID    0x00000010  // Region Number Valid
#define NVIC_MPU_BASE1_REGION_M 0x00000007  // Region Number
#define NVIC_MPU_BASE1_ADDR_S   5
#define NVIC_MPU_BASE1_REGION_S 0

/* The following are defines for the bit fields in the NVIC_MPU_ATTR1 register. */
#define NVIC_MPU_ATTR1_XN       0x10000000  // Instruction Access Disable
#define NVIC_MPU_ATTR1_AP_M     0x07000000  // Access Privilege
#define NVIC_MPU_ATTR1_TEX_M    0x00380000  // Type Extension Mask
#define NVIC_MPU_ATTR1_SHAREABLE \
                                0x00040000  // Shareable
#define NVIC_MPU_ATTR1_CACHEABLE \
                                0x00020000  // Cacheable
#define NVIC_MPU_ATTR1_BUFFRABLE \
                                0x00010000  // Bufferable
#define NVIC_MPU_ATTR1_SRD_M    0x0000FF00  // Subregion Disable Bits
#define NVIC_MPU_ATTR1_SIZE_M   0x0000003E  // Region Size Mask
#define NVIC_MPU_ATTR1_ENABLE   0x00000001  // Region Enable

/* The following are defines for the bit fields in the NVIC_MPU_BASE2 register. */
#define NVIC_MPU_BASE2_ADDR_M   0xFFFFFFE0  // Base Address Mask
#define NVIC_MPU_BASE2_VALID    0x00000010  // Region Number Valid
#define NVIC_MPU_BASE2_REGION_M 0x00000007  // Region Number
#define NVIC_MPU_BASE2_ADDR_S   5
#define NVIC_MPU_BASE2_REGION_S 0

/* The following are defines for the bit fields in the NVIC_MPU_ATTR2 register. */
#define NVIC_MPU_ATTR2_XN       0x10000000  // Instruction Access Disable
#define NVIC_MPU_ATTR2_AP_M     0x07000000  // Access Privilege
#define NVIC_MPU_ATTR2_TEX_M    0x00380000  // Type Extension Mask
#define NVIC_MPU_ATTR2_SHAREABLE \
                                0x00040000  // Shareable
#define NVIC_MPU_ATTR2_CACHEABLE \
                                0x00020000  // Cacheable
#define NVIC_MPU_ATTR2_BUFFRABLE \
                                0x00010000  // Bufferable
#define NVIC_MPU_ATTR2_SRD_M    0x0000FF00  // Subregion Disable Bits
#define NVIC_MPU_ATTR2_SIZE_M   0x0000003E  // Region Size Mask
#define NVIC_MPU_ATTR2_ENABLE   0x00000001  // Region Enable

/* The following are defines for the bit fields in the NVIC_MPU_BASE3 register. */
#define NVIC_MPU_BASE3_ADDR_M   0xFFFFFFE0  // Base Address Mask
#define NVIC_MPU_BASE3_VALID    0x00000010  // Region Number Valid
#define NVIC_MPU_BASE3_REGION_M 0x00000007  // Region Number
#define NVIC_MPU_BASE3_ADDR_S   5
#define NVIC_MPU_BASE3_REGION_S 0

/* The following are defines for the bit fields in the NVIC_MPU_ATTR3 register. */
#define NVIC_MPU_ATTR3_XN       0x10000000  // Instruction Access Disable
#define NVIC_MPU_ATTR3_AP_M     0x07000000  // Access Privilege
#define NVIC_MPU_ATTR3_TEX_M    0x00380000  // Type Extension Mask
#define NVIC_MPU_ATTR3_SHAREABLE \
                                0x00040000  // Shareable
#define NVIC_MPU_ATTR3_CACHEABLE \
                                0x00020000  // Cacheable
#define NVIC_MPU_ATTR3_BUFFRABLE \
                                0x00010000  // Bufferable
#define NVIC_MPU_ATTR3_SRD_M    0x0000FF00  // Subregion Disable Bits
#define NVIC_MPU_ATTR3_SIZE_M   0x0000003E  // Region Size Mask
#define NVIC_MPU_ATTR3_ENABLE   0x00000001  // Region Enable

/* The following are defines for the bit fields in the NVIC_DBG_CTRL register. */
#define NVIC_DBG_CTRL_DBGKEY_M  0xFFFF0000  // Debug key mask
#define NVIC_DBG_CTRL_DBGKEY    0xA05F0000  // Debug key
#define NVIC_DBG_CTRL_S_RESET_ST \
                                0x02000000  // Core has reset since last read
#define NVIC_DBG_CTRL_S_RETIRE_ST \
                                0x01000000  // Core has executed insruction
                                            // since last read
#define NVIC_DBG_CTRL_S_LOCKUP  0x00080000  // Core is locked up
#define NVIC_DBG_CTRL_S_SLEEP   0x00040000  // Core is sleeping
#define NVIC_DBG_CTRL_S_HALT    0x00020000  // Core status on halt
#define NVIC_DBG_CTRL_S_REGRDY  0x00010000  // Register read/write available
#define NVIC_DBG_CTRL_C_SNAPSTALL \
                                0x00000020  // Breaks a stalled load/store
#define NVIC_DBG_CTRL_C_MASKINT 0x00000008  // Mask interrupts when stepping
#define NVIC_DBG_CTRL_C_STEP    0x00000004  // Step the core
#define NVIC_DBG_CTRL_C_HALT    0x00000002  // Halt the core
#define NVIC_DBG_CTRL_C_DEBUGEN 0x00000001  // Enable debug

/* The following are defines for the bit fields in the NVIC_DBG_XFER register. */
#define NVIC_DBG_XFER_REG_WNR   0x00010000  // Write or not read
#define NVIC_DBG_XFER_REG_SEL_M 0x0000001F  // Register
#define NVIC_DBG_XFER_REG_R0    0x00000000  // Register R0
#define NVIC_DBG_XFER_REG_R1    0x00000001  // Register R1
#define NVIC_DBG_XFER_REG_R2    0x00000002  // Register R2
#define NVIC_DBG_XFER_REG_R3    0x00000003  // Register R3
#define NVIC_DBG_XFER_REG_R4    0x00000004  // Register R4
#define NVIC_DBG_XFER_REG_R5    0x00000005  // Register R5
#define NVIC_DBG_XFER_REG_R6    0x00000006  // Register R6
#define NVIC_DBG_XFER_REG_R7    0x00000007  // Register R7
#define NVIC_DBG_XFER_REG_R8    0x00000008  // Register R8
#define NVIC_DBG_XFER_REG_R9    0x00000009  // Register R9
#define NVIC_DBG_XFER_REG_R10   0x0000000A  // Register R10
#define NVIC_DBG_XFER_REG_R11   0x0000000B  // Register R11
#define NVIC_DBG_XFER_REG_R12   0x0000000C  // Register R12
#define NVIC_DBG_XFER_REG_R13   0x0000000D  // Register R13
#define NVIC_DBG_XFER_REG_R14   0x0000000E  // Register R14
#define NVIC_DBG_XFER_REG_R15   0x0000000F  // Register R15
#define NVIC_DBG_XFER_REG_FLAGS 0x00000010  // xPSR/Flags register
#define NVIC_DBG_XFER_REG_MSP   0x00000011  // Main SP
#define NVIC_DBG_XFER_REG_PSP   0x00000012  // Process SP
#define NVIC_DBG_XFER_REG_DSP   0x00000013  // Deep SP
#define NVIC_DBG_XFER_REG_CFBP  0x00000014  // Control/Fault/BasePri/PriMask

/* The following are defines for the bit fields in the NVIC_DBG_DATA register. */
#define NVIC_DBG_DATA_M         0xFFFFFFFF  // Data temporary cache
#define NVIC_DBG_DATA_S         0

/* The following are defines for the bit fields in the NVIC_DBG_INT register. */
#define NVIC_DBG_INT_HARDERR    0x00000400  // Debug trap on hard fault
#define NVIC_DBG_INT_INTERR     0x00000200  // Debug trap on interrupt errors
#define NVIC_DBG_INT_BUSERR     0x00000100  // Debug trap on bus error
#define NVIC_DBG_INT_STATERR    0x00000080  // Debug trap on usage fault state
#define NVIC_DBG_INT_CHKERR     0x00000040  // Debug trap on usage fault check
#define NVIC_DBG_INT_NOCPERR    0x00000020  // Debug trap on coprocessor error
#define NVIC_DBG_INT_MMERR      0x00000010  // Debug trap on mem manage fault
#define NVIC_DBG_INT_RESET      0x00000008  // Core reset status
#define NVIC_DBG_INT_RSTPENDCLR 0x00000004  // Clear pending core reset
#define NVIC_DBG_INT_RSTPENDING 0x00000002  // Core reset is pending
#define NVIC_DBG_INT_RSTVCATCH  0x00000001  // Reset vector catch

/* The following are defines for the bit fields in the NVIC_SW_TRIG register. */
#define NVIC_SW_TRIG_INTID_M    0x000000FF  // Interrupt ID
#define NVIC_SW_TRIG_INTID_S    0

/* The following are defines for the bit fields in the NVIC_FPCC register. */
#define NVIC_FPCC_ASPEN         0x80000000  // Automatic State Preservation
                                            // Enable
#define NVIC_FPCC_LSPEN         0x40000000  // Lazy State Preservation Enable
#define NVIC_FPCC_MONRDY        0x00000100  // Monitor Ready
#define NVIC_FPCC_BFRDY         0x00000040  // Bus Fault Ready
#define NVIC_FPCC_MMRDY         0x00000020  // Memory Management Fault Ready
#define NVIC_FPCC_HFRDY         0x00000010  // Hard Fault Ready
#define NVIC_FPCC_THREAD        0x00000008  // Thread Mode
#define NVIC_FPCC_USER          0x00000002  // User Privilege Level
#define NVIC_FPCC_LSPACT        0x00000001  // Lazy State Preservation Active

/* The following are defines for the bit fields in the NVIC_FPCA register. */
#define NVIC_FPCA_ADDRESS_M     0xFFFFFFF8  // Address
#define NVIC_FPCA_ADDRESS_S     3

/* The following are defines for the bit fields in the NVIC_FPDSC register. */
#define NVIC_FPDSC_AHP          0x04000000  // AHP Bit Default
#define NVIC_FPDSC_DN           0x02000000  // DN Bit Default
#define NVIC_FPDSC_FZ           0x01000000  // FZ Bit Default
#define NVIC_FPDSC_RMODE_M      0x00C00000  // RMODE Bit Default
#define NVIC_FPDSC_RMODE_RN     0x00000000  // Round to Nearest (RN) mode
#define NVIC_FPDSC_RMODE_RP     0x00400000  // Round towards Plus Infinity (RP)
                                            // mode
#define NVIC_FPDSC_RMODE_RM     0x00800000  // Round towards Minus Infinity
                                            // (RM) mode
#define NVIC_FPDSC_RMODE_RZ     0x00C00000  // Round towards Zero (RZ) mode

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

/* NVIC Get Priority */
#define	NVIC_GET_PRI(_int)	(\
	(\
	  ( NVIC_INT_PRI_REG(_int) & NVIC_INT_PRI_M(_int) )  >> (\
	    ((EE_UREG)_int & NVIC_INT_PRI_REG_M) << NVIC_INT_PRI_REG_M\
	  )\
	) >> NVIC_INT_PRI_S \
)\

/* NVIC Set Pending Interrupt */
#define	NVIC_INT_SET_PENDING(_int)	(\
	NVIC_INT_REG(_int, NVIC_INT_SET_PENDING_REG_B) |= NVIC_INT_M(_int)\
)

/* NVIC Clear Pending Interrupt */
#define	NVIC_INT_CLR_PENDING(_int)	(\
	NVIC_INT_REG(_int, NVIC_INT_CLR_PENDING_REG_B) |= NVIC_INT_M(_int)\
)

#endif /* __INCLUDE_CORTEX_MX_NVIC_H__ */
