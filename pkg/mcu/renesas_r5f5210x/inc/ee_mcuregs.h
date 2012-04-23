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

#define	BSC		(*((volatile volatile EE_UREG __evenaccess *)0x81300))
#define	CAC		(*((volatile volatile EE_UREG __evenaccess *)0x8B000))
#define	CMPB	(*((volatile volatile EE_UREG __evenaccess *)0x8C580))
#define	CMT		(*((volatile volatile EE_UREG __evenaccess *)0x88000))
#define	CMT0	(*((volatile volatile EE_UREG __evenaccess *)0x88002))
#define	CMT1	(*((volatile volatile EE_URE	__evenaccess *)0x88008))
#define	CMT2	(*((volatile volatile EE_UREG	__evenaccess *)0x88012))
#define	CMT3	(*((volatile volatile EE_UREG	__evenaccess *)0x88018))
#define	CRC		(*((volatile volatile EE_UREG	__evenaccess *)0x88280))
#define	DA		(*((volatile volatile EE_UREG	__evenaccess *)0x880C0))
#define	DMAC	(*((volatile volatile EE_URER	__evenaccess *)0x82200))
#define	DMAC0	(*((volatile volatile EE_UREG	__evenaccess *)0x82000))
#define	DMAC1	(*((volatile volatile EE_UREG	__evenaccess *)0x82040))
#define	DMAC2	(*((volatile volatile EE_UREG	__evenaccess *)0x82080))
#define	DMAC3	(*((volatile volatile EE_UREG	__evenaccess *)0x820C0))
#define	DOC		(*((volatile volatile EE_UREG	__evenaccess *)0x8B080))
#define	DTC		(*((volatile volatile EE_UREG	__evenaccess *)0x82400))
#define	ELC		(*((volatile volatile EE_UREG	__evenaccess *)0x8B100))
#define	EXSYSTEM		(*((volatile volatile EE_UREG __evenaccess *)0xFF7FFFF8))
#define	FLASH	(*((volatile volatile EE_UREG	__evenaccess *)0x8C296))
#define	ICU		(*((volatile volatile EE_UREG	__evenaccess *)0x87000))
#define	IWDT	(*((volatile volatile EE_UREG	__evenaccess *)0x88030))
#define	MPC		(*((volatile volatile EE_UREG	__evenaccess *)0x8C11F))
#define	MTU		(*((volatile volatile EE_UREG	__evenaccess *)0x8860A))
#define	MTU0	(*((volatile volatile EE_UREG	__evenaccess *)0x88700))
#define	MTU1	(*((volatile volatile EE_UREG	__evenaccess *)0x88780))
#define	MTU2	(*((volatile volatile EE_UREG	__evenaccess *)0x88800))
#define	MTU3	(*((volatile volatile EE_UREG	__evenaccess *)0x88600))
#define	MTU4	(*((volatile volatile EE_UREG	__evenaccess *)0x88600))
#define	MTU5	(*((volatile volatile EE_UREG	__evenaccess *)0x88880))
#define	POE		(*((volatile volatile EE_UREG	__evenaccess *)0x88900))
#define	PORT	(*((volatile volatile EE_UREG	__evenaccess *)0x8C100))
#define	PORT0	(*((volatile volatile EE_UREG	__evenaccess *)0x8C000))
#define	PORT1	(*((volatile volatile EE_UREG	__evenaccess *)0x8C001))
#define	PORT2	(*((volatile volatile EE_UREG	__evenaccess *)0x8C002))
#define	PORT3	(*((volatile volatile EE_UREG	__evenaccess *)0x8C003))
#define	PORT4	(*((volatile volatile EE_UREG	__evenaccess *)0x8C004))
#define	PORT5	(*((volatile volatile EE_UREG	__evenaccess *)0x8C005))
#define	PORTA	(*((volatile volatile EE_UREG	__evenaccess *)0x8C00A))
#define	PORTB	(*((volatile volatile EE_UREG	__evenaccess *)0x8C00B))
#define	PORTC	(*((volatile volatile EE_UREG	__evenaccess *)0x8C00C))
#define	PORTD	(*((volatile volatile EE_UREG	__evenaccess *)0x8C00D))
#define	PORTE	(*((volatile volatile EE_UREG	__evenaccess *)0x8C00E))
#define	PORTH	(*((volatile volatile EE_UREG	__evenaccess *)0x8C011))
#define	PORTJ	(*((volatile volatile EE_UREG	__evenaccess *)0x8C012))
#define	RIIC0	(*((volatile volatile EE_UREG	__evenaccess *)0x88300))
#define	RSPI0	(*((volatile volatile EE_UREG	__evenaccess *)0x88380))
#define	RTC		(*((volatile volatile EE_UREG	__evenaccess *)0x8C400))
#define	S12AD	(*((volatile volatile EE_UREG	__evenaccess *)0x89000))
#define	SCI0	(*((volatile volatile EE_UREG	__evenaccess *)0x8A000))
#define	SCI1	(*((volatile volatile EE_UREG	__evenaccess *)0x8A020))
#define	SCI5	(*((volatile volatile EE_UREG	__evenaccess *)0x8A0A0))
#define	SCI6	(*((volatile volatile EE_UREG	__evenaccess *)0x8A0C0))
#define	SCI8	(*((volatile volatile EE_UREG	__evenaccess *)0x8A100))
#define	SCI9	(*((volatile volatile EE_UREG	__evenaccess *)0x8A120))
#define	SCI12	(*((volatile volatile EE_UREG	__evenaccess *)0x8B300))
#define	SMCI0	(*((volatile volatile EE_UREG	__evenaccess *)0x8A000))
#define	SMCI1	(*((volatile volatile EE_UREG	__evenaccess *)0x8A020))
#define	SMCI5	(*((volatile volatile EE_UREG	__evenaccess *)0x8A0A0))
#define	SMCI6	(*((volatile volatile EE_UREG	__evenaccess *)0x8A0C0))
#define	SMCI8	(*((volatile volatile EE_UREG	__evenaccess *)0x8A100))
#define	SMCI9	(*((volatile volatile EE_UREG	__evenaccess *)0x8A120))
#define	SMCI12	(*((volatile volatile EE_UREG	__evenaccess *)0x8B300))
#define	SYSTEM	(*((volatile volatile EE_UREG	__evenaccess *)0x80000))
#define	TEMPS	(*((volatile volatile EE_UREG	__evenaccess *)0x8C500))
#define	TMR0	(*((volatile volatile EE_UREG   __evenaccess *)0x88200))
#define	TMR1	(*((volatile volatile EE_UREG	__evenaccess *)0x88201))
#define	TMR2	(*((volatile volatile EE_UREG	__evenaccess *)0x88210))
#define	TMR3	(*((volatile volatile EE_UREG	__evenaccess *)0x88211))
#define	TMR01	(*((volatile volatile EE_UREG	__evenaccess *)0x88204))
#define	TMR23	(*((volatile volatile EE_UREG	__evenaccess *)0x88214))
#define	WDT		(*((volatile volatile EE_UREG	__evenaccess *)0x88020))

#endif /* #if 1*/

#endif	/* __INCLUDE_RENESAS_R5F5210X_MCUREGS_H__ */
