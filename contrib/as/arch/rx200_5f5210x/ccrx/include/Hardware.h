/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2012  Evidence Srl
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

/** @file	Hardware.h
 *  @brief	Hardware Abstraction Header File.
 *
 *  This file contains all the functions and macros for abstraction of hardware
 *  for Renesas RX200 (r5f5210x) and CCRX compiler.
 *
 *  @author	Gianluca Franchino
 *  @date	2012
 */

#ifndef	HARDWARE_H
#define	HARDWARE_H

/*
 * MACROS
 */
#define	HW_REG_SZ	0x00000004			/**< Register Size in Bytes   */
#define	HW_REG_SZ_S	0x00000002			/**< Register Size Shift Bits */

/* I/O and PORT related registers. */
#define HW_PWPR_B0WI_SET	0x80		/**< Set B0WI bit in the PWPR reg.  */
#define HW_PWPR_B0WI_CLEAR	0x00		/**< Clear B0WI bit in the PWPR reg.*/
#define HW_PWPR_PFSWE_SET	0x01		/**< Set PFSWE bit in the PWPR reg. */
#define HW_PWPR_PFSWE_CLEAR	0x00		/**< Clear PFSWE bi in the PWPR reg.*/
#define HW_PFS_ASEL_SET		0x80		/**< Set ASEL bit in the PFS reg. 	*/
#define HW_PFS_ISEL_SET		0x40		/**< Set ISEL bit in the PFS reg. 	*/

#define HW_IO_PDR_OFFSET	0x00000000	/**< I/O PORT PDR registers offset  */
#define HW_IO_PODR_OFFSET	0x00000020	/**< I/O PORT PODR registers offset */
#define HW_IO_PIDR_OFFSET 	0x00000040	/**< I/O PORT PIDR registers offset */
#define HW_IO_PMR_OFFSET 	0x00000060	/**< I/O PORT PMR registers offset  */
#define HW_IO_PCR_OFFSET 	0x000000C0	/**< I/O PORT PCR registers offset  */
#define HW_IO_DSCR_OFFSET 	0x000000E0	/**< I/O PORT DSCR registers offset  */

/**< PORT0 PDR register address */
#define HW_PORT0_ADDR	EE_HWREG_ADDR(0x0008C000)

/**< PORT1 ODR register base address */
#define HW_ODR_BASE_ADDR		EE_HWREG_ADDR(0x0008C080)
/**< PORT Pin Function Select register base address. */
#define HW_PORT_PFS_BASE_ADDR	EE_HWREG_ADDR(0x0008C140)
/**< Port Write Protect (PWPR) Register address. */
#define HW_PORT_WPR_ADDR		EE_HWREG_ADDR(0x0008C11F)
/* IO Hardware Base Address */
#define	HW_IO_BASE_ADDR			HW_PORT0_ADDR

/* Timers related registers. */
/**< TMR module Timer Counter Control Register address base. */
#define HW_SYSTEM_TCCR_ADDR_BASE	EE_HWREG8_ADDR(0x0008820A)
/**< TMR module Timer Control Register address base. */
#define HW_SYSTEM_TMR_TCR_ADDR_BASE		EE_HWREG8_ADDR(0x00088200)
/**< TMR module Timer Counter Register address base. */
#define HW_SYSTEM_TCNT_ADDR_BASE	EE_HWREG8_ADDR(0x00088200)
/**< TMR01 module Timer Counter Register 16 bits address base. */
#define HW_SYSTEM_TMR01_TCNT_ADDR_BASE	EE_HWREG16_ADDR(0x00088208)
/**< TMR23 module Timer Counter Register 16 bits address base. */
#define HW_SYSTEM_TMR23_TCNT_ADDR_BASE	EE_HWREG16_ADDR(0x00088218)
/**< TMR0 Time Constant Register A (TCORA). */
#define HW_SYSTEM_TMR0_TCORA_ADDR	EE_HWREG8_ADDR(0x00088204)
/**< TMR1 Time Constant Register A (TCORA). */
#define HW_SYSTEM_TMR1_TCORA_ADDR	EE_HWREG8_ADDR(0x00088205)
/**< TMR2 Time Constant Register A (TCORA). */
#define HW_SYSTEM_TMR2_TCORA_ADDR	EE_HWREG8_ADDR(0x00088214)
/**< TMR3 Time Constant Register A (TCORA). */
#define HW_SYSTEM_TMR3_TCORA_ADDR	EE_HWREG8_ADDR(0x00088215)
/**< TMR0 Time Constant Register B (TCORB). */
#define HW_SYSTEM_TMR0_TCORB_ADDR	EE_HWREG8_ADDR(0x00088206)
/**< TMR1 Time Constant Register B (TCORB). */
#define HW_SYSTEM_TMR1_TCORB_ADDR	EE_HWREG8_ADDR(0x00088207)
/**< TMR2 Time Constant Register B (TCORB). */
#define HW_SYSTEM_TMR2_TCORB_ADDR	EE_HWREG8_ADDR(0x00088216)
/**< TMR3 Time Constant Register B (TCORB). */
#define HW_SYSTEM_TMR3_TCORB_ADDR	EE_HWREG8_ADDR(0x00088217)
/**< Compare Match Timer (CMT) Start Register 0 (CMSTR0) address. */
#define HW_SYSTEM_CMSTR0_ADDR			EE_HWREG16_ADDR(0x00088000)
/**< Compare Match Timer (CMT) Start Register 1 (CMSTR1) address. */
#define HW_SYSTEM_CMSTR1_ADDR			EE_HWREG16_ADDR(0x00088010)
/**< Compare Match Timer (CMT) Compare Match Counter (CMCNT) CMT0 address. */
#define HW_SYSTEM_CMT0_CMCNT_ADDR		EE_HWREG16_ADDR(0x00088004)
/**< MTU0 Timer Control Register address. */
#define HW_SYSTEM_MTU0_TCR_ADDR			EE_HWREG8_ADDR(0x00088700)
/**< MTU1 Timer Control Register address. */
#define HW_SYSTEM_MTU1_TCR_ADDR			EE_HWREG8_ADDR(0x00088780)
/**< MTU2 Timer Control Register address. */
#define HW_SYSTEM_MTU2_TCR_ADDR			EE_HWREG8_ADDR(0x00088800)
/**< MTU3 Timer Control Register address. */
#define HW_SYSTEM_MTU3_TCR_ADDR			EE_HWREG8_ADDR(0x00088600)
/**< MTU4 Timer Control Register address. */
#define HW_SYSTEM_MTU4_TCR_ADDR			EE_HWREG8_ADDR(0x00088601)
/**< MTU5U Timer Control Register address. */
#define HW_SYSTEM_MTU5U_TCR_ADDR		EE_HWREG8_ADDR(0x00088884)
/**< MTU5V Timer Control Register address. */
#define HW_SYSTEM_MTU5V_TCR_ADDR		EE_HWREG8_ADDR(0x00088894)
/**< MTU5W Timer Control Register address. */
#define HW_SYSTEM_MTU5W_TCR_ADDR		EE_HWREG8_ADDR(0x000888A4)
/**< Timer Compare Match Clear Register (TCNTCMPCLR)*/
#define HW_SYSTEM_MTU5_TCNTCMPCLR_ADDR	EE_HWREG8_ADDR(0x000888B6)
/**< MTU0 Timer Control Register address. */
#define HW_SYSTEM_MTU0_TMDR_ADDR 		EE_HWREG8_ADDR(0x00088701)
/**< MTU1 Timer Control Register address. */
#define HW_SYSTEM_MTU1_TMDR_ADDR 		EE_HWREG8_ADDR(0x00088781)
/**< MTU2 Timer Control Register address. */
#define HW_SYSTEM_MTU2_TMDR_ADDR 		EE_HWREG8_ADDR(0x00088801)
/**< MTU3 Timer Control Register address. */
#define HW_SYSTEM_MTU3_TMDR_ADDR 		EE_HWREG8_ADDR(0x00088602)
/**< MTU4 Timer Control Register address. */
#define HW_SYSTEM_MTU4_TMDR_ADDR 		EE_HWREG8_ADDR(0x00088603)
/**< MTU0 Timer Status Register address. */
#define HW_SYSTEM_MTU0_TSR_ADDR 		EE_HWREG8_ADDR(0x00088705)
/**< MTU1 Timer Status Register address. */
#define HW_SYSTEM_MTU1_TSR_ADDR 		EE_HWREG8_ADDR(0x00088785)
/**< MTU2 Timer Status Register address. */
#define HW_SYSTEM_MTU2_TSR_ADDR 		EE_HWREG8_ADDR(0x00088805)
/**< MTU3 Timer Status Register address. */
#define HW_SYSTEM_MTU3_TSR_ADDR 		EE_HWREG8_ADDR(0x0008862C)
/**< MTU4 Timer Status Register address. */
#define HW_SYSTEM_MTU4_TSR_ADDR 		EE_HWREG8_ADDR(0x0008862D)
/**< MTU0 Timer Status Register address. */
#define HW_SYSTEM_MTU0_TCNT_ADDR 		EE_HWREG16_ADDR(0x00088706)
/**< MTU1 Timer Status Register address. */
#define HW_SYSTEM_MTU1_TCNT_ADDR 		EE_HWREG16_ADDR(0x00088786)
/**< MTU2 Timer Status Register address. */
#define HW_SYSTEM_MTU2_TCNT_ADDR 		EE_HWREG16_ADDR(0x00088806)
/**< MTU3 Timer Status Register address. */
#define HW_SYSTEM_MTU3_TCNT_ADDR 		EE_HWREG16_ADDR(0x00088610)
/**< MTU4 Timer Status Register address. */
#define HW_SYSTEM_MTU4_TCNT_ADDR 		EE_HWREG16_ADDR(0x00088612)
/**< MTU5U Timer Status Register address. */
#define HW_SYSTEM_MTU5U_TCNT_ADDR 		EE_HWREG16_ADDR(0x00088880)
/**< MTU5V Timer Status Register address. */
#define HW_SYSTEM_MTU5V_TCNT_ADDR 		EE_HWREG16_ADDR(0x00088890)
/**< MTU5W Timer Status Register address. */
#define HW_SYSTEM_MTU5W_TCNT_ADDR 		EE_HWREG16_ADDR(0x000888A0)
/**< MTU3 and MTU4 Timer Read/Write Enable Registers (TRWER) address. */
#define HW_SYSTEM_MTU34_TRWER_ADDR		EE_HWREG16_ADDR(0x00088684)
/**< MTU0 Timer General Register A (TGRA) address. */
#define HW_SYSTEM_MTU0_TGRA_ADDR		EE_HWREG16_ADDR(0x00088708)
/**< MTU0 Timer General Register B (TGRB) address. */
#define HW_SYSTEM_MTU0_TGRB_ADDR		EE_HWREG16_ADDR(0x0008870A)
/**< MTU0 Timer General Register C (TGRC) address. */
#define HW_SYSTEM_MTU0_TGRC_ADDR		EE_HWREG16_ADDR(0x0008870C)
/**< MTU0 Timer General Register D (TGRD) address. */
#define HW_SYSTEM_MTU0_TGRD_ADDR		EE_HWREG16_ADDR(0x0008870E)
/**< MTU0 Timer General Register E (TGRE) address. */
#define HW_SYSTEM_MTU0_TGRE_ADDR		EE_HWREG16_ADDR(0x00088720)
/**< MTU0 Timer General Register F (TGRF) address. */
#define HW_SYSTEM_MTU0_TGRF_ADDR		EE_HWREG16_ADDR(0x00088722)
/**< MTU1 Timer General Register A (TGRA) address. */
#define HW_SYSTEM_MTU1_TGRA_ADDR		EE_HWREG16_ADDR(0x00088788)
/**< MTU1 Timer General Register B (TGRB) address. */
#define HW_SYSTEM_MTU1_TGRB_ADDR		EE_HWREG16_ADDR(0x0008878A)
/**< MTU2 Timer General Register A (TGRA) address. */
#define HW_SYSTEM_MTU2_TGRA_ADDR		EE_HWREG16_ADDR(0x00088808)
/**< MTU2 Timer General Register B (TGRB) address. */
#define HW_SYSTEM_MTU2_TGRB_ADDR		EE_HWREG16_ADDR(0x0008880A)
/**< MTU3 Timer General Register A (TGRA) address. */
#define HW_SYSTEM_MTU3_TGRA_ADDR		EE_HWREG16_ADDR(0x00088618)
/**< MTU3 Timer General Register B (TGRB) address. */
#define HW_SYSTEM_MTU3_TGRB_ADDR		EE_HWREG16_ADDR(0x0008861A)
/**< MTU3 Timer General Register C (TGRC) address. */
#define HW_SYSTEM_MTU3_TGRC_ADDR		EE_HWREG16_ADDR(0x00088624)
/**< MTU3 Timer General Register D (TGRD) address. */
#define HW_SYSTEM_MTU3_TGRD_ADDR		EE_HWREG16_ADDR(0x00088626)
/**< MTU4 Timer General Register A (TGRA) address. */
#define HW_SYSTEM_MTU4_TGRA_ADDR		EE_HWREG16_ADDR(0x0008861C)
/**< MTU4 Timer General Register B (TGRB) address. */
#define HW_SYSTEM_MTU4_TGRB_ADDR		EE_HWREG16_ADDR(0x0008861E)
/**< MTU4 Timer General Register C (TGRC) address. */
#define HW_SYSTEM_MTU4_TGRC_ADDR		EE_HWREG16_ADDR(0x00088628)
/**< MTU4 Timer General Register D (TGRD) address. */
#define HW_SYSTEM_MTU4_TGRD_ADDR		EE_HWREG16_ADDR(0x0008862A)
/**< MTU4 Timer General Register U (TGRB) address. */
#define HW_SYSTEM_MTU5_TGRU_ADDR		EE_HWREG16_ADDR(0x00088882)
/**< MTU4 Timer General Register V (TGRC) address. */
#define HW_SYSTEM_MTU5_TGRV_ADDR		EE_HWREG16_ADDR(0x00088892)
/**< MTU4 Timer General Register W (TGRD) address. */
#define HW_SYSTEM_MTU5_TGRW_ADDR		EE_HWREG16_ADDR(0x000888A2)
/**< MTU0 Timer Interrupt Enable Register (TIER) address. */
#define HW_SYSTEM_MTU0_TIER_ADDR 		EE_HWREG8_ADDR(0x00088704)
/**< MTU1 Timer Interrupt Enable Register (TIER) address. */
#define HW_SYSTEM_MTU1_TIER_ADDR 		EE_HWREG8_ADDR(0x00088784)
/**< MTU2 Timer Interrupt Enable Register (TIER) address. */
#define HW_SYSTEM_MTU2_TIER_ADDR 		EE_HWREG8_ADDR(0x00088804)
/**< MTU3 Timer Interrupt Enable Register (TIER) address. */
#define HW_SYSTEM_MTU3_TIER_ADDR 		EE_HWREG8_ADDR(0x00088608)
/**< MTU4 Timer Interrupt Enable Register (TIER) address. */
#define HW_SYSTEM_MTU4_TIER_ADDR 		EE_HWREG8_ADDR(0x00088609)
/**< MTU5 Timer Interrupt Enable Register (TIER) address. */
#define HW_SYSTEM_MTU5_TIER_ADDR 		EE_HWREG8_ADDR(0x000088B2)
/**< MTU2A Timer Synchronous Registers (TSYR) address. */
#define HW_SYSTEM_MTU2A_TSYR_ADDR		EE_HWREG8_ADDR(0x00008681)

/**< MTU0 to MTU4 Timer Start Registers (TSTR) address. */
#define HW_SYSTEM_TSTR_BASE_ADDR			EE_HWREG8_ADDR(0x00088680)
/**< MTU5 Timer Start Registers (TSTR) address. */
#define HW_SYSTEM_TSTR5_ADDR		EE_HWREG8_ADDR(0x000888B4)

/* Module Stop/Start related registers. */
/**< Module Stop Control Register A (MSTPCRA) address. */
#define HW_SYSTEM_MSTPCRA_ADDR	EE_HWREG_ADDR(0x00080010)

/**< CMT module registers base address. */
#define HW_SYSTEM_CMT_BASE_ADDR HW_SYSTEM_CMSTR0_ADDR


/** @brief	Channel to Hardware Unit.
 *  @param	_ch	Numeric ID of a Channel.
 *  @return	Numeric ID of Hardware Unit.
 *
 *  This macro function returns the numeric ID of the harware unit referred to
 *  numeric id of a channel.
 *
 *  @note	Requires <tt>HW_CH_UNIT_MASK</tt> macro.
 */
#ifdef	HW_CH_UNIT_MASK
#define	HW_CH_2_UNIT(_ch)	(uint32)( \
  (uint32)_ch & (uint32)HW_CH_UNIT_MASK \
)
#else
#define	HW_CH_2_UNIT(_ch)	(uint32)( 0x00000000 )
#endif

/** @brief	Channel to Hardware Module.
 *  @param	_ch	Numeric ID of a Channel.
 *  @return	Numeric ID of Hardware Module.
 *
 *  This macro function returns the numeric ID of the harware module referred to
 *  numeric id of a channel.
 *
 *  @note	Requires <tt>HW_CH_MOD_MASK</tt> macro.
 */
#ifdef	HW_CH_MOD_MASK
#ifdef	HW_CH_UNIT_MASK_SZ_S
#define	HW_CH_2_MOD(_ch)	(uint32)( \
  ( (uint32)_ch & (uint32)HW_CH_MOD_MASK ) >> (uint32)HW_CH_UNIT_MASK_SZ_S \
  )

#else	/* HW_CH_UNIT_MASK_SZ_S */

#define	HW_CH_2_MOD(_ch)	(uint32)( \
  (uint32)_ch & (uint32)HW_CH_MOD_MASK \
)
#endif	/* !HW_CH_UNIT_MASK_SZ_S */
#endif	/* HW_CH_MOD_MASK */

#if	( defined(HW_CH_MOD_MASK) && defined(HW_IO_BASE_ADDR) )
/** @brief	Channel to Hardware Module Base Address 
 *  @param	ch	Channel Identifier.
 *  @return	Hardware Module Base Address.
 *
 *  @note	Requires <tt>HW_CH_MOD_MASK</tt> and
 *  		<tt>HW_IO_BASE_ADDR</tt> macros.
 *
 *  @see	<tt>HW_CH_2_MOD</tt> macro.
 */
#define  HW_CH_2_MOD_BASE_ADDR(_ch) \
	(uint32)((uint32)HW_IO_BASE_ADDR + HW_CH_2_MOD(_ch))


#endif /*( defined(HW_CH_MOD_MASK) && defined(HW_IO_BASE_ADDR) )*/

#if	( defined(HW_CH_MOD_MASK) && defined(HW_ODR_BASE_ADDR) )
/** @brief	Channel to Hardware ODR Base Address 
 *  @param	ch	Channel Identifier.
 *  @return	Hardware ODR Base Address.
 *
 *  @note	Requires <tt>HW_CH_MOD_MASK</tt> and
 *  		<tt>HW_ODR_BASE_ADDR</tt> macros.
 *
 *  @see	<tt>HW_CH_2_MOD</tt> macro.
 */
#define  HW_CH_2_ODR_BASE_ADDR(_ch) \
	(HW_ODR_BASE_ADDR + (HW_CH_2_MOD(_ch) << (uint32) 0x1))

#endif /*( defined(HW_CH_MOD_MASK) && defined(HW_ODR_BASE_ADDR) )*/



/** @brief	Channel to Hardware Module Register Address
 *  @param	_ch	Channel Identifier.
 *  @param	_ro	Harware Module Register Offset.
 *  @return	Hardware Module Register Address.
 *
 *  @note	Requires <tt>HW_CH_MOD_MASK</tt> and
 *  		and <tt>HW_IO_BASE_ADDR</tt> macros.
 *
 *  @see	<tt>hw_ch_2_mod_base_addr</tt> inline func.
 */
#if	( defined(HW_CH_MOD_MASK) && defined(HW_IO_BASE_ADDR) )
#define	HW_CH_2_MOD_REG_ADDR(_ch, _ro)	(uint32)( \
  hw_ch_2_mod_base_addr(_ch) + (uint32)_ro \
)
#endif	/* HW_CH_MOD_MASK && HW_IO_BASE_ADDR */

/** @brief	Channel to Hardware Module Register
 *  @param	_ch	Channel Identifier.
 *  @param	_ro	Harware Module Register Offset.
 *  @return	Hardware Module Register.
 *
 *  @note	Requires <tt>HW_CH_MOD_MASK</tt> and
 *  		<tt>HW_IO_BASE_ADDR</tt> macros.
 *
 *  @see	<tt>HW_CH_2_MOD_REG_ADDR</tt> macro.
 */
#if	( defined(HW_CH_MOD_MASK) && defined(HW_IO_BASE_ADDR) )
#define	HW_CH_2_MOD_REG(_ch, _ro)	EE_HWREG( \
  HW_CH_2_MOD_REG_ADDR(_ch, _ro) \
)
#endif	/* HW_CH_MOD_MASK && HW_IO_BASE_ADDR */

/** @brief	Channel to Hardware Unit Register Address
 *  @param	_ch	Channel Identifier.
 *  @param	_ro	Harware Unit Register Offset.
 *  @return	Hardware Unit Register Address.
 *
 *  @note	Requires <tt>HW_CH_MOD_MASK</tt> and
 *  		<tt>HW_IO_BASE_ADDR</tt> macros.
 *
 *  @see	<tt>HW_CH_2_MOD_REG_ADDR</tt> and <tt>HW_CH_2_UNIT</tt> macros.
 */
#if	( defined(HW_CH_MOD_MASK) && defined(HW_IO_BASE_ADDR) )
#ifdef	HW_CH_UNIT_MASK
#define	HW_CH_2_UNIT_REG_ADDR(_ch, _ro)	(uint32)( \
  HW_CH_2_MOD_REG_ADDR(_ch,_ro) + (uint32)( \
    HW_CH_2_UNIT(_ch) << (uint32)HW_REG_SZ_S \
  ) \
)
#else	/* HW_CH_UNIT_MASK */
#define	HW_CH_2_UNIT_REG_ADDR(_ch, _ro)	(uint32)( HW_CH_2_MOD_REG_ADDR(_ch) )
#endif	/* !HW_CH_UNIT_MASK */
#endif	/* HW_CH_MOD_MASK && HW_IO_BASE_ADDR */

/** @brief	Channel to Hardware Unit Register
 *  @param	_ch	Channel Identifier.
 *  @param	_ro	Harware Unit Register Offset.
 *  @return	Hardware Unit Register.
 *
 *  @note	Requires <tt>HW_CH_MOD_MASK</tt> and
 *  		<tt>HW_IO_BASE_ADDR</tt> macros.
 *
 *  @see	<tt>HW_CH_2_UNIT_REG_ADDR</tt> macro.
 */
#if	( defined(HW_CH_MOD_MASK) && defined(HW_IO_BASE_ADDR) )
#define	HW_CH_2_UNIT_REG(_ch, _ro)	EE_HWREG( \
  HW_CH_2_UNIT_REG_ADDR(_ch, _ro) \
)
#endif	/* HW_CH_MOD_MASK && HW_IO_BASE_ADDR */


#endif	/* HARDWARE_H */
