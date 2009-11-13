///* ###*B*###
// * ERIKA Enterprise - a tiny RTOS for small microcontrollers
// *
// * Copyright (C) 2002-2008  Evidence Srl
// *
// * This file is part of ERIKA Enterprise.
// *
// * ERIKA Enterprise is free software; you can redistribute it
// * and/or modify it under the terms of the GNU General Public License
// * version 2 as published by the Free Software Foundation, 
// * (with a special exception described below).
// *
// * Linking this code statically or dynamically with other modules is
// * making a combined work based on this code.  Thus, the terms and
// * conditions of the GNU General Public License cover the whole
// * combination.
// *
// * As a special exception, the copyright holders of this library give you
// * permission to link this code with independent modules to produce an
// * executable, regardless of the license terms of these independent
// * modules, and to copy and distribute the resulting executable under
// * terms of your choice, provided that you also meet, for each linked
// * independent module, the terms and conditions of the license of that
// * module.  An independent module is a module which is not derived from
// * or based on this library.  If you modify this code, you may extend
// * this exception to your version of the code, but you are not
// * obligated to do so.  If you do not wish to do so, delete this
// * exception statement from your version.
// *
// * ERIKA Enterprise is distributed in the hope that it will be
// * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// * GNU General Public License version 2 for more details.
// *
 //* You should have received a copy of the GNU General Public License
// * version 2 along with ERIKA Enterprise; if not, write to the
// * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
// * Boston, MA 02110-1301 USA.
// * ###*E*### */

///*
// * Author: 2005 Michele Cirinei
// *         2006- Paolo Gai
// *
// * CVS: $Id: ee_hal.S,v 1.7 2008/06/16 14:26:31 francesco Exp $
// */

///* the define is needed for binary distributions */
#define __EECFG_THIS_IS_ASSEMBLER__
#include "eecfg.h"
	
//#include "cpu/cosmic_hs12xs/inc/ee_compiler.h"


//	//.text
//
//	xref 	_EE_hal_endcycle_next_thread	
//#ifdef __MULTI__
//
//#ifdef __IRQ_STACK_NEEDED__
//	xdef	_EE_s12xs_change_to_irq_tos
//	xdef	_EE_s12xs_change_from_irq_tos
//	xref 	_EE_s12xs_temp_tos
//#endif
//
//	xdef	_EE_s12xs_hal_stkchange
//	xref	_EE_s12xs_system_tos
//	xref	_EE_s12xs_active_tos
//	xref 	_EE_hal_endcycle_next_tos
//
//EE_CHANGE_TOS_MACRO: macro 
//	// if (tos_index == EE_s12xs_active_tos) goto 2f
//	mov w0,w2
//	mov w1, w0
//	cp _EE_s12xs_active_tos
//	bra z,2f
//
//	// save some registers
//        mov.d   w8,[w15++]
//        mov.d   w10,[w15++]
//        mov.d   w12,[w15++]
//        mov     w14,[w15++]
//
//	// here I CANNOT use w1 and w2
//
//	// EE_s12xs_system_tos[EE_s12xs_active_tos] = stack pointer;
//	mov	#_EE_s12xs_system_tos,w3
//	mov	_EE_s12xs_active_tos,w4
//	sl	w4,w4
//	mov	w15,[w4+w3]
//	// EE_s12xs_active_tos = tos_index (tos_index is now in w0 and w1)
//	mov	w0,_EE_s12xs_active_tos
//	// stack pointer = EE_s12xs_system_tos[tos_index]
//	sl	w0,w0
//#ifdef __S12XS_SPLIM__
//	mov	#_EE_s12xs_system_splim,w4
//	mov	[w0+w4],w4
//	mov	w4, _SPLIM
//	// the next operation cannot do an access based on w15
//#endif
//	mov	[w0+w3],w15
//
//	// read some registers
//        mov     [--w15],w14
//        mov.d   [--w15],w12
//        mov.d   [--w15],w10
//        mov.d   [--w15],w8
//
//2:	// put back w0
//	mov w2, w0
//	endm
//
//#endif // __MULTI__
//
//
//	
//
////
//// MONO:  void EE_s12xs_hal_ready2stacked(ADDR thread_addr)
//// MULTI: void EE_s12xs_hal_ready2stacked(ADDR thread_addr, EE_UREG tos_index)
//// parameters are in w0 and w1
////
////	.type	_EE_s12xs_hal_ready2stacked, #function
xdef f_EE_s12xs_hal_ready2stacked	// xdef _EE_s12xs_hal_ready2stacked
f_EE_s12xs_hal_ready2stacked:
//
//1:
//#ifdef __MULTI__
//	// (eventually) switch to the TOS of the new thread
//	EE_CHANGE_TOS_MACRO
//#endif
//
//	// enable interrupts	
//	//DISI #0
//	cli
////  DISI #3
////  BCLR.B 0x0042, #0x7
////  BCLR.B 0x0042, #0x6
////  BCLR.B 0x0042, #0x5
//
//	// call the thread
//	call	w0
//  
//	// disable interrupts
//	//DISI #0x3fff
//	sei
////  DISI #3
////  BSET.B 0x0042, #0x7
////  BSET.B 0x0042, #0x6
////  BSET.B 0x0042, #0x5
//	
//	// call the thread end instance
//	call	_EE_thread_end_instance		// rcall
//
//#ifdef __MULTI__
//	mov	_EE_hal_endcycle_next_tos,aux_w1	//w1
//#endif
//	mov	_EE_hal_endcycle_next_thread,aux_w0		//w0
//
//	// EE_hal_endcycle_next_thread == 0 >>> wake up a stacked thread
//	// EE_hal_endcycle_next_thread != 0 >>> wake up a ready thread
//	cp0	aux_w0
//	bra	nz,1b
//#ifdef __MULTI__
//	EE_CHANGE_TOS_MACRO
//#endif
//	rtc									//return	
//
//
//
//
//#ifdef __MULTI__
//
////
//// MONO:  not defined
//// MULTI: void EE_s12xs_hal_stkchange(EE_UREG 0, EE_UREG tos_index)
////
//// Typically called into a generic primitive to implement a blocking
//// synchronization primitive.
////
////	.type	_EE_s12xs_hal_stkchange, #function
//_EE_s12xs_hal_stkchange:
//	// save some registers
//        mov.d   w8,[w15++]
//        mov.d   w10,[w15++]
//        mov.d   w12,[w15++]
//        mov     w14,[w15++]
//
//	// EE_s12xs_system_tos[EE_s12xs_active_tos] = stack pointer;
//	mov	#_EE_s12xs_system_tos,w3
//	mov	_EE_s12xs_active_tos,w4
//	sl	w4,w4
//	mov	w15,[w4+w3]
//	// EE_s12xs_active_tos = tos_index (tos_index is now in w0 and w1)
//	mov	w0,_EE_s12xs_active_tos
//	// stack pointer = EE_s12xs_system_tos[tos_index]
//	sl	w0,w0
//#ifdef __S12XS_SPLIM__
//	mov	#_EE_s12xs_system_splim,w4
//	mov	[w0+w4], w4
//	mov	w4, _SPLIM
//	// the next operation cannot do an access based on w15
//#endif
//	mov	[w0+w3],w15
//
//	// read some registers
//        mov     [--w15],w14
//        mov.d   [--w15],w12
//        mov.d   [--w15],w10
//        mov.d   [--w15],w8
//
//	return
//
//#endif // __MULTI__
//
//	
//	
//	
//		
	end
