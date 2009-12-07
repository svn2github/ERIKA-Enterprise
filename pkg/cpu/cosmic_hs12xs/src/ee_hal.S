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
//#include "eecfg.h"	
//#include "cpu/cosmic_hs12xs/inc/ee_compiler.h"

xref 	f_EE_thread_end_instance

.ftext:	section	.text

	xref	_PPAGE
	xref 	_EE_hal_endcycle_next_thread	

	//--------------------------------------------------------------------------------
	//
	// MACRO Actions:
	//  - 1. If exiting_tos == entering_tos nothing must be done (end of macro)
	//  - 2. Save registers in the current stack (exiting one)
	//  - 3. Save the SP (exiting_tos) in EE_s12xs_system_tos[EE_s12xs_active_tos]
	//  - 4. Set EE_s12xs_active_tos = tos_index (index of the entering_tos)
	//  - 5. Load the SP with the entering_tos in EE_s12xs_system_tos[tos_index]
	//  - 6. Load registers from current stack (entering one)
	//
	//--------------------------------------------------------------------------------
		
	#ifdef __MULTI__

		#ifdef __IRQ_STACK_NEEDED__
			xdef	_EE_s12xs_change_to_irq_tos
			xdef	_EE_s12xs_change_from_irq_tos
			xref 	_EE_s12xs_temp_tos
		#endif
	
		xdef	_EE_s12xs_hal_stkchange
		xref	_EE_s12xs_system_tos
		xref	_EE_s12xs_active_tos
		xref 	_EE_hal_endcycle_next_tos
			
		EE_CHANGE_TOS_MACRO: macro 			// *** this macro needs tos_index in d register ***
		 
		// if (tos_index == EE_s12xs_active_tos) goto lab2
		ldd	OFST+7,s						// put tos_index in d
		cpd \1								//cpd _EE_s12xs_active_tos, compare d (-> tos_index) with EE_s12xs_active_tos
		beq \@lab2							// if equal goto lab2
		
		// save some registers
		ldaa \3								// put _PPAGE in a
		psha								// push a in the stack						
	
		// EE_s12xs_system_tos[EE_s12xs_active_tos] = stack pointer;
		tfr	s,d								// I can use d because tos_index is in saved in the stack...
		ldy	\1								//ldy	_EE_s12xs_active_tos
		lsly	
		std \2,y							//std _EE_s12xs_system_tos,y
		
		// EE_s12xs_active_tos = tos_index (tos_index is now in w0 and w1)
		ldd	OFST+8,s						// put tos_index in d
		std	\1								// change _EE_s12xs_active_tos
		
		// stack pointer = EE_s12xs_system_tos[tos_index]
		//sl	w0,w0
		//		#ifdef __S12XS_SPLIM__
		//			mov	#_EE_s12xs_system_splim,w4
		//			mov	[w0+w4],w4
		//			mov	w4, _SPLIM
		//			// the next operation cannot do an access based on w15
		//		#endif		
		//mov	[w0+w3],w15
		ldy	\1								// ldy	_EE_s12xs_active_tos==tos_index
		lsly	
		ldd	\2								// ldd	_EE_s12xs_system_tos,y
		tfr	d,s								// change the stack pointer
		
		// read some registers
		pula								// pull a form the stack
	    staa	\3							// change _PPAGE
	
	\@lab2:	
		endm								// end of macro

	#endif // __MULTI__
	
	//--------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------
	//
	// MONOSTACK:
	// void EE_s12xs_hal_ready2stacked(EE_ADDR thread_addr);
	//
	// MULTISTACK:
	// void EE_s12xs_hal_ready2stacked(EE_ADDR thread_addr, EE_UREG tos_index);
	//
	// a0 = thread_addr	-> Function pointer to the thread body to activate.
	// a1 = tos_index	-> Index in EE_s12xs_system_tos[] memory array 
	//                     from which the SP of the entering thread
	//                     (the caller) must be retrieved.
	//
	// Actions: 
	//  - NOTE: the context is saved by the C compiler calling mechanism, the 
	//          caller (exiting thread) save what it has to save and the callee 
	//          (entering thread) will save what it has to (the actual call is done
	//          by this function). 
	//  - 1. If MULTISTACK: swap stacks of the exiting thread and the entering one
	//                      (initially the entering SP is in a1)
	//  - 2. Enable interrupts: the thread MUST run with enabled interrupts
	//  - 3. Execute the thread: call the function pointer (initially is in a0)
	//  - 4. Disable interrupts
	//  - 5. Call EE_thread_end_instance: this check if there is an other threads to
	//                                    be activated by setting the global
	//                                    variable EE_hal_endcycle_next_thread
	//  - 6. If MULTISTACK: read the SP for the new (possible) entering thread from 
	//                      from the global variable EE_hal_endcycle_next_tos
	//  - 7. If EE_hal_endcycle_next_thread != 0 activate it: goint to point 1.
	//  - 8. If MULTISTACK: swap stacks of the entering thread and the exiting one
	//  - 9. If EE_hal_endcycle_next_thread == 0: go the the stacked thread, i.e.
	//                                            simply return to the stacked one
	//
	//--------------------------------------------------------------------------------

xdef f_EE_s12xs_hal_ready2stacked	
f_EE_s12xs_hal_ready2stacked:
	pshd									// push d in the stack
	pshx									// push x in the stack

	OFST:	set	0							// set offset = zero
	
		#ifdef __MULTI__
			EE_CHANGE_TOS_MACRO	_EE_s12xs_active_tos, _EE_s12xs_system_tos, _PPAGE			// (eventually) switch to the TOS of the new thread
		#endif
	
	L3:	
		cli									// enable interrupts
		call	[OFST+0,s]					// call the thread from sp reading the content of the pointer (because d,x saved in sp)
		sei									// disable interrupts
		call	f_EE_thread_end_instance	// call the thread end instance
		
		ldd	_EE_hal_endcycle_next_thread+2	// the first word loaded in d register
		std	OFST+2,s						// change the first argument word (the first address word) storing d in sp
		ldd	_EE_hal_endcycle_next_thread	// the second word loaded in d register
		std	OFST+0,s						// change the second argument word (the second address word) storing d in sp
		
		ldd	OFST+0,s						// check the address (first part)
		bne	L21								// if not equal to zero -> branch
		ldd	OFST+2,s						// check the address (second part)
	L21:	
		bne	L3								// if not equal to zero -> branch
		
		#ifdef __MULTI__
			ldd	_EE_hal_endcycle_next_tos	// load in d the next tos 
			std	OFST+7,s
		// #endif
		// #ifdef __MULTI__
			EE_CHANGE_TOS_MACRO	_EE_s12xs_active_tos, _EE_s12xs_system_tos, _PPAGE				// macro to ...
		#endif
		
		leas	4,s							// remove four bytes from the stack pointer
		
		rtc									// return from call(with ppage change)

	//--------------------------------------------------------------------------------
	//
	// MONOSTACK:
	// not defined
	//
	// MULTISTACK: 
	// void EE_s12xs_hal_stkchange(EE_UREG tos_index);
	//
	// a0 = tos_index	-> Index in EE_s12xs_system_tos[] memory array 
	//                     from which the SP of the entering thread
	//                     (the caller) must be retrieved.
	//
	// Actions: 
	//  - 1. Save registers in the current stack (exiting one)
	//  - 2. Save the SP (exiting_tos) in EE_s12xs_system_tos[EE_s12xs_active_tos]
	//  - 3. Set EE_s12xs_active_tos = tos_index (index of the entering_tos)
	//  - 4. Load the SP with the entering_tos in EE_s12xs_system_tos[tos_index]
	//  - 5. Load registers from current stack (entering one)
	//
	//--------------------------------------------------------------------------------

	#ifdef __MULTI__
	
xdef f_EE_s12xs_hal_stkchange		
f_EE_s12xs_hal_stkchange:
		pshd									// push d in the stack
		pshx									// push x in the stack

OFST:	set	0								// set offset = zero
		// save some registers
		ldaa _PPAGE							// put _PPAGE in a
		psha								// push a in the stack	
        
		// EE_s12xs_system_tos[EE_s12xs_active_tos] = stack pointer;
		tfr	s,d								// I can use d because tos_index has been saved in the stack... 
		ldy	_EE_s12xs_active_tos
		lsly	
		std _EE_s12xs_system_tos,y 	
		
		
		// EE_s12xs_active_tos = tos_index (tos_index is now in w0 and w1)
		ldd	OFST+8,s						// put tos_index in d
		std	_EE_s12xs_active_tos			// change _EE_s12xs_active_tos
		
		// stack pointer = EE_s12xs_system_tos[tos_index]
		// sl	w0,w0
		//  #ifdef __S12XS_SPLIM__
		//		mov	#_EE_s12xs_system_splim,w4
		//		mov	[w0+w4], w4
		//		mov	w4, _SPLIM
		//		// the next operation cannot do an access based on w15
		//	#endif
		// mov	[w0+w3],w15
		ldy	_EE_s12xs_active_tos
		lsly	
		ldd	_EE_s12xs_system_tos,y
		tfr	d,s								// change the stack pointer
		
		// read some registers
		pula								// pull a
	    staa	_PPAGE						// change _PPAGE
	
		leas	4,s							// remove two bytes from the stack pointer
		rtc									// return from call(with ppage change)

	#endif // __MULTI__
	
	end
	
	
