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

/**
	@file ee_mcuregs.h
	@brief MCU memory mapped registers.
	@author Gianluca Franchino
	@date 2012
 */

#ifndef	__INCLUDE_RENESAS_R5F5210X_MCUREGS_H__
#define	__INCLUDE_RENESAS_R5F5210X_MCUREGS_H__


#if 1

#include "iodefine.h"

#else

#include "cpu/rx210/inc/ee_cpu.h"

#define	BSC	EE_HWREG(0x81300)
#define	CAC	EE_HWREG(0x8B000)
#define	CMPB	EE_HWREG(0x8C580)
#define	CMT	EE_HWREG(0x88000)
#define	CMT0	EE_HWREG(0x88002)
#define	CMT1	EE_HWREG(0x88008)
#define	CMT2	EE_HWREG(0x88012)
#define	CMT3	EE_HWREG(0x88018)
#define	CRC	EE_HWREG(0x88280)
#define	DA	EE_HWREG(0x880C0)
#define	DMAC	EE_HWREG(0x82200)
#define	DMAC0	EE_HWREG(0x82000)
#define	DMAC1	EE_HWREG(0x82040)
#define	DMAC2	EE_HWREG(0x82080)
#define	DMAC3	EE_HWREG(0x820C0)
#define	DOC	EE_HWREG(0x8B080)
#define	DTC	EE_HWREG(0x82400)
#define	ELC	EE_HWREG(0x8B100)	
#define	EXSYSTEM	EE_HWREG(0xFF7FFFF8)
#define	FLASH	EE_HWREG(0x8C296)
#define	ICU	EE_HWREG(0x87000)	
#define	IWDT	EE_HWREG(0x88030)
#define	MPC	EE_HWREG(0x8C11F)
#define	MTU	EE_HWREG(0x8860A)
#define	MTU0	EE_HWREG(0x88700)
#define	MTU1	EE_HWREG(0x88780)
#define	MTU2	EE_HWREG(0x88800)
#define	MTU3	EE_HWREG(0x88600)
#define	MTU4	EE_HWREG(0x88600)
#define	MTU5	EE_HWREG(0x88880)
#define	POE	EE_HWREG(0x88900)
#define	PORT	EE_HWREG(0x0x8C100)
#define	PORT0	EE_HWREG(0x8C000)
#define	PORT1	EE_HWREG(0x8C001)
#define	PORT2	EE_HWREG(0x8C002)
#define	PORT3	EE_HWREG(0x8C003)
#define	PORT4	EE_HWREG(0x8C004)
#define	PORT5	EE_HWREG(0x8C005)
#define	PORTA	EE_HWREG(0x8C00A)
#define	PORTB	EE_HWREG(0x8C00B)
#define	PORTC	EE_HWREG(0x8C00C)
#define	PORTD	EE_HWREG(0x8C00D)
#define	PORTE	EE_HWREG(0x8C00E)
#define	PORTH	EE_HWREG(0x8C011)
#define	PORTJ	EE_HWREG(0x8C012)
#define	RIIC0	EE_HWREG(0x88300)
#define	RSPI0	EE_HWREG(0x88380)
#define	RTC	EE_HWREG(0x8C400)
#define	S12AD	EE_HWREG(0x89000)
#define	SCI0	EE_HWREG(0x8A000)
#define	SCI1	EE_HWREG(0x8A020)
#define	SCI5	EE_HWREG(0x8A0A0)
#define	SCI6	EE_HWREG(0x8A0C0)
#define	SCI8	EE_HWREG(0x8A100)
#define	SCI9	EE_HWREG(0x8A120)
#define	SCI12	EE_HWREG(0x8B300)
#define	SMCI0	EE_HWREG(0x8A000)
#define	SMCI1	EE_HWREG(0x8A020)
#define	SMCI5	EE_HWREG(0x8A0A0)
#define	SMCI6	EE_HWREG(0x8A0C0)
#define	SMCI8	EE_HWREG(0x8A100)
#define	SMCI9	EE_HWREG(0x8A120)
#define	SMCI12	EE_HWREG(0x8B300)
#define	SYSTEM	EE_HWREG(0x80000)
#define	TEMPS	EE_HWREG(0x8C500)
#define	TMR0	EE_HWREG(0x88200)
#define	TMR1	EE_HWREG(0x88201)
#define	TMR2	EE_HWREG(0x88210)
#define	TMR3	EE_HWREG(0x88211)
#define	TMR01	EE_HWREG(0x88204)
#define	TMR23	EE_HWREG(0x88214)
#define	WDT	EE_HWREG(0x88020)

#endif /* #if 1*/

#define SYS_RESC_POR	0x01
#define SYS_RESC_IWDT	0x10
#define SYS_RESC_WDT	0x20
#define SYS_RESC_SW		0x40

#endif	/* __INCLUDE_RENESAS_R5F5210X_MCUREGS_H__ */
