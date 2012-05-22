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

/** @file   Cfg.h
 *  @brief  Drivers Configuration Utilities
 *
 *  @author Errico Guidieri
 *  @date   2012
 */

#ifndef CFG_H
#define CFG_H

/* Macro for Big Endian Bit Remapping for 16/32 bit registers */

/* Big Endian Bit Remapping (for 16 bit register) */
#define   AS_16_BIT0       (1U << 15U)
#define   AS_16_BIT1       (1U << 14U)
#define   AS_16_BIT2       (1U << 13U)
#define   AS_16_BIT3       (1U << 12U)
#define   AS_16_BIT4       (1U << 11U)
#define   AS_16_BIT5       (1U << 10U)
#define   AS_16_BIT6       (1U << 9U)
#define   AS_16_BIT7       (1U << 8U)
#define   AS_16_BIT8       (1U << 7U)
#define   AS_16_BIT9       (1U << 6U)
#define   AS_16_BIT10      (1U << 5U)
#define   AS_16_BIT11      (1U << 4U)
#define   AS_16_BIT12      (1U << 3U)
#define   AS_16_BIT13      (1U << 2U)
#define   AS_16_BIT14      (1U << 1U)
#define   AS_16_BIT15      (1U)
#define   AS_16_NOBIT      0x0000U

/* Big Endian Bit Remapping (for 32 bit register) */
#define   AS_32_BIT0       (1U << 31U)
#define   AS_32_BIT1       (1U << 30U)
#define   AS_32_BIT2       (1U << 29U)
#define   AS_32_BIT3       (1U << 28U)
#define   AS_32_BIT4       (1U << 27U)
#define   AS_32_BIT5       (1U << 26U)
#define   AS_32_BIT6       (1U << 25U)
#define   AS_32_BIT7       (1U << 24U)
#define   AS_32_BIT8       (1U << 23U)
#define   AS_32_BIT9       (1U << 22U)
#define   AS_32_BIT10      (1U << 21U)
#define   AS_32_BIT11      (1U << 20U)
#define   AS_32_BIT12      (1U << 19U)
#define   AS_32_BIT13      (1U << 18U)
#define   AS_32_BIT14      (1U << 17U)
#define   AS_32_BIT15      (1U << 16U)
#define   AS_32_BIT16      (1U << 15U)
#define   AS_32_BIT17      (1U << 14U)
#define   AS_32_BIT18      (1U << 13U)
#define   AS_32_BIT19      (1U << 12U)
#define   AS_32_BIT20      (1U << 11U)
#define   AS_32_BIT21      (1U << 10U)
#define   AS_32_BIT22      (1U << 9U)
#define   AS_32_BIT23      (1U << 8U)
#define   AS_32_BIT24      (1U << 7U)
#define   AS_32_BIT25      (1U << 6U)
#define   AS_32_BIT26      (1U << 5U)
#define   AS_32_BIT27      (1U << 4U)
#define   AS_32_BIT28      (1U << 3U)
#define   AS_32_BIT29      (1U << 2U)
#define   AS_32_BIT30      (1U << 1U)
#define   AS_32_BIT31      (1U)
#define   AS_32_NOBIT      0x00000000U

#endif /* CFG_H */
