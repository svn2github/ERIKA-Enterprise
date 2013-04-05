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
	@file ee_vtable_ccrx.c
	@brief Fixed Interrupt Vector Table for use with Renesas HEW.
	@author Gianluca Franchino
	@date 2012
 */

#include "ee.h"
#include "eecfg.h"

//#pragma interrupt (EE_dummy)
void EE_dummy(void){/* brk(){  } */}


/*
 * Extern declaration of the default handlers.
 */
//extern void EE_rx200_default_ISR(void);		// Default Handler


#ifndef EE_RX200_NON_MASKABLE_INT_ISR
//#pragma interrupt (EE_rx200_non_maskable_int)
void	EE_rx200_non_maskable_int(void) { while(1);}
#else
extern void	EE_rx200_non_maskable_int(void);
#endif

#ifndef EE_RX200_SUPER_VIS_EXC_ISR
//#pragma interrupt (EE_rx200_super_vis_exc)
void	EE_rx200_super_vis_exc(void) {	while(1); }
#else
extern void	EE_rx200_super_vis_exc(void);
#endif

#ifndef EE_RX200_UNDEF_INST_EXC_ISR
//#pragma interrupt (EE_rx200_undef_inst_exc)
void	EE_rx200_undef_inst_exc(void) {	while(1); }
#else
extern void	EE_rx200_undef_inst_exc(void);
#endif


#ifndef EE_RX200_FLOTING_P_EXC_ISR
//#pragma interrupt (EE_rx200_floting_p_exc)
void	EE_rx200_floting_p_exc(void) {	while(1); }
#else
extern void	EE_rx200_floting_p_exc(void);
#endif

#ifdef EE_RX200_RESET_ISR				// The reset handler
extern void EE_rx200_RESET_ISR(void);
#define EE_rx200_power_on_res EE_RX200_RESET_ISR
#else
extern void EE_rx200_power_on_res(void);
#endif


/*GF: simile a questa*/

#pragma section C FIXEDVECT

void (*const Fixed_Vectors[])(void) = {
//;0xffffffd0  Exception(Supervisor Instruction)
    EE_rx200_super_vis_exc,
//;0xffffffd4  Reserved
    EE_dummy,
//;0xffffffd8  Reserved
    EE_dummy,
//;0xffffffdc  Exception(Undefined Instruction)
    EE_rx200_undef_inst_exc,
//;0xffffffe0  Reserved
    EE_dummy,
//;0xffffffe4  Exception(Floating Point)
    EE_rx200_floting_p_exc,
//;0xffffffe8  Reserved
    EE_dummy,
//;0xffffffec  Reserved
    EE_dummy,
//;0xfffffff0  Reserved
    EE_dummy,
//;0xfffffff4  Reserved
    EE_dummy,
//;0xfffffff8  NMI
    EE_rx200_non_maskable_int,
//;0xfffffffc  RESET
//;<<VECTOR DATA START (POWER ON RESET)>>
//;Power On Reset PC
	EE_rx200_power_on_res                                                                                                                            
//;<<VECTOR DATA END (POWER ON RESET)>>
};

#pragma address _MDEreg=0xffffff80 // MDE register (Single Chip Mode)
#ifdef __BIG
	const unsigned long _MDEreg = 0xfffffff8; // big
#else
	const unsigned long _MDEreg = 0xffffffff; // little
#endif
