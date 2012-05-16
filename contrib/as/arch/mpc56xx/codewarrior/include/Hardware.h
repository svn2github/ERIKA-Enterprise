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

/** @file   Hardware.h
 *  @brief  Hardware Abstraction Header File.
 *
 *  This file contains all the functions and macros for abstraction of hardware
 *  for Freescale Leopard (MPC5643L) and Codewarrior compiler.
 *
 *  In order to use the following macros you need to include header with
 *  hardware info somewere before the first use site
 *
 *  @author Errico Guidieri
 *  @date 2012
 */

#ifndef HARDWARE_H
#define HARDWARE_H

/*
 * MACROS
 */
#define HW_REG_SZ   0x00000004U   /**< Register Size in Bytes   */
#define HW_REG_SZ_S 0x00000002U   /**< Register Size Shift Bits */

/** @brief Macro used to actually use a integer as register offset */
#define HW_REG_OFFSET(index) ((index) << HW_REG_SZ_S)

/** @brief Macro used to check a reg value againt a bit mask */
#define HW_REG_BITMASK_CHECK(reg, bitmask) (((reg) & (bitmask)) == bitmask)

/* Processor identification */

/** @brief Core identification special register */
#define SPR_PIR 286
/** @brief Core version special register */
#define SPR_PVR 287

/** @brief Leopard Core PVR */
#define PVR_CORE_E200Z4D_LEOPARD    0x81550001UL 

/* MCU Macros access */

/** @brief Return Active Hardware Mode */
#define MCU_HARDWARE_MODE_ACTIVE()  (ME.GS.B.S_CURRENT_MODE)

/** @brief Return Active Clock Type */
#define MCU_CLOCK_ACTIVE()          (ME.GS.B.S_SYSCLK)

/** @brief Return if PLL0 is actually enabled */
#define MCU_PLL0_IS_ENABLED()       (ME.GS.B.S_PLL0)

/** @brief Return if PLL1 is actually enabled */
#define MCU_PLL1_IS_ENABLED()       (ME.GS.B.S_PLL1)


/* Mode Entry Module Macros (MC_ME) */

/** @brief Mode Entry base address */
#define ME_BASE_ADDR 0xC3FDC000U
/** @brief Mode Entry Global Status */
#define ME_GS   ((volatile uint32 *) ME_BASE_ADDR)

/** @brief Mode Entry Mode Configuration Base */
#define ME_MC_BASE_ADDR   0xC3FDC020U

/** @brief Read Mode Configuration */
#define ME_GET_MC(mode) (*(volatile uint32 *)(ME_MC_BASE_ADDR +\
    HW_REG_OFFSET(mode)))

/** @bried Write Mode Configuration */
#define ME_SET_MC(mode, conf) (ME_GET_MC(mode) = (conf))

#endif  /* HARDWARE_H */
