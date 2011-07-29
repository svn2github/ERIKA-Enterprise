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
// * You should have received a copy of the GNU General Public License
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

#ifdef __CODEWARRIOR__
 #define EE_THREAD_INSTANCE_NAME     EE_thread_end_instance
 #define PPAGE_NAME                  PPAGE
 #define STACK_POINTER               SP
 #define NEXT_THREAD_NAME            EE_hal_endcycle_next_thread
 #define OFFSET_VALUE                0
 #define _EE_s12xs_system_tos        EE_s12xs_system_tos
 #define _EE_s12xs_active_tos        EE_s12xs_active_tos 
 #define _EE_hal_endcycle_next_tos   EE_hal_endcycle_next_tos
 #define _EE_s12xs_change_to_irq_tos EE_s12xs_change_to_irq_tos
 #define _EE_s12xs_change_from_irq_tos EE_s12xs_change_from_irq_tos
 #define _EE_s12xs_temp_tos          EE_s12xs_temp_tos
#else
 #define EE_THREAD_INSTANCE_NAME     f_EE_thread_end_instance
 #define PPAGE_NAME                  _PPAGE
 #define STACK_POINTER               s
 #define NEXT_THREAD_NAME            _EE_hal_endcycle_next_thread
 #define OFFSET_VALUE                0
#endif


	xref 	EE_THREAD_INSTANCE_NAME

#ifdef __CODEWARRIOR__
.text: SECTION
#else // CODEWARRIOR
.ftext:	section	.text
#endif

	xref	PPAGE_NAME
	xref 	NEXT_THREAD_NAME

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
			//xdef	_EE_s12xs_change_to_irq_tos
			//xdef	_EE_s12xs_change_from_irq_tos
			xref 	_EE_s12xs_temp_tos
		#endif
	
		//xdef	_EE_s12xs_hal_stkchange
		xref	_EE_s12xs_system_tos
		xref	_EE_s12xs_active_tos
		xref 	_EE_hal_endcycle_next_tos
			
		EE_CHANGE_TOS_MACRO: macro 			// *** this macro needs tos_index in d register ***
		 
		// if (tos_index == EE_s12xs_active_tos) goto lab2
		ldd	OFST+3,STACK_POINTER						// put tos_index in d
		cpd \1								// cpd _EE_s12xs_active_tos, compare d (-> tos_index) with EE_s12xs_active_tos
		beq \@lab2							// if equal goto lab2
		
		// save some registers:
		// ldaa \3								// put PPAGE in a
		// psha								// push a in the stack						
	
		// EE_s12xs_system_tos[EE_s12xs_active_tos] = stack pointer;
		tfr	STACK_POINTER,d								// I can use d because tos_index is in saved in the stack...
		ldy	\1								// ldy	_EE_s12xs_active_tos
		lsly	
		std \2,y							//std _EE_s12xs_system_tos,y
		
		// EE_s12xs_active_tos = tos_index (tos_index is now in w0 and w1)
		ldd	OFST+3,STACK_POINTER						// put tos_index in d
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
		ldd	\2,y							// ldd	_EE_s12xs_system_tos,y
		tfr	d,STACK_POINTER								// change the stack pointer
		
		// read some registers
		// pula								// pull a form the stack
	    // staa	\3							// change PPAGE
	
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

#ifdef __CODEWARRIOR__
	xdef EE_s12xs_hal_ready2stacked
EE_s12xs_hal_ready2stacked:
#else
	xdef f_EE_s12xs_hal_ready2stacked
f_EE_s12xs_hal_ready2stacked:
#endif

#ifdef __CODEWARRIOR__
		pshx
		pshd
		leas	1,STACK_POINTER				// remove one byte from the stack (d,x previously pushed...)
		pulx
		pula
		clrb
#endif

LAB1:	
	OFST:	set	OFFSET_VALUE							// set offset

	#ifdef __MULTI__
		std NEXT_THREAD_NAME+2
		stx NEXT_THREAD_NAME
		// now x and d are saved and they can be used by the MULTISTACK macros
		EE_CHANGE_TOS_MACRO	_EE_s12xs_active_tos, _EE_s12xs_system_tos, PPAGE_NAME			// (eventually) switch to the TOS of the new thread
		ldx NEXT_THREAD_NAME
		ldd NEXT_THREAD_NAME+2
	#endif

LAB2:	
		// le push stanno qui perché 1) la call necessita di un indirizzo con offset relativo 2) non possono stare all'inizio della funzione perché lo stack frame di ready2stacked deve essere compatibile con lo stackframe di stkchange
		pshd
		pshx
		
		cli									// enable interrupts
		// non posso usare NEXT_THREAD_NAME perchè qualcuno potrebbe farmi preemption dopo la cli
		call	[OFST+0,STACK_POINTER]					// call the thread from sp reading the content of the pointer (because d,x saved in sp)
		leas	4,STACK_POINTER							// remove four bytes from the stack (d,x previously pushed...)
		sei									// disable interrupts
									
		call	EE_THREAD_INSTANCE_NAME		// call the thread end instance
		
		#ifdef __MULTI__
			ldd	_EE_hal_endcycle_next_tos	// load in d the next tos 
			std	OFST+3,STACK_POINTER					// put the value in the stack to replace the previous one...
		#endif
		
		//ldd	NEXT_THREAD_NAME+2	// the first word loaded in d register
		//std	OFST+2,STACK_POINTER						// change the first argument word (the first address word) storing d in sp
		//std _wreg+2
		//ldd	NEXT_THREAD_NAME	// the second word loaded in d register
		//std	OFST+0,STACK_POINTER						// change the second argument word (the second address word) storing d in sp
		//std _wreg
		//ldd	OFST+0,STACK_POINTER						// check the address (first part)
		//ldd _wreg
		//ldd	NEXT_THREAD_NAME
		//bne	L21								// if not equal to zero -> branch
		//ldd	OFST+2,STACK_POINTER						// check the address (second part)
		//ldd _wreg+2
		//ldd	NEXT_THREAD_NAME+2
	    //L21:	
		//bne	L3								// if not equal to zero -> branch
	    //bra LAB4								// go to label: LAB4    

		//leggere EE_hal_endcycle_next_thread
		ldx NEXT_THREAD_NAME
		bne LAB3
		ldd NEXT_THREAD_NAME+2
		bne LAB1

		#ifdef __MULTI__
			EE_CHANGE_TOS_MACRO	_EE_s12xs_active_tos, _EE_s12xs_system_tos, PPAGE_NAME				// macro to return ... (e.g. to dummy stack)
		#endif
		
		rtc									// return from call(with PPAGE change)

LAB3:
		ldd NEXT_THREAD_NAME+2
		bra LAB1
		

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

#ifdef __CODEWARRIOR__
	xdef EE_s12xs_hal_stkchange
EE_s12xs_hal_stkchange:
#else
	xdef f_EE_s12xs_hal_stkchange
f_EE_s12xs_hal_stkchange:
#endif
		// EE_s12xs_system_tos[EE_s12xs_active_tos] = stack pointer;
		tfr	STACK_POINTER,x									// I can use d because tos_index has been saved in the stack... 
		ldy	_EE_s12xs_active_tos
		lsly	
		stx _EE_s12xs_system_tos,y 	
		
		// EE_s12xs_active_tos = tos_index (tos_index is now in w0 and w1)
		std	_EE_s12xs_active_tos			    // change _EE_s12xs_active_tos
		
		// stack pointer = EE_s12xs_system_tos[tos_index]
		ldy	_EE_s12xs_active_tos
		lsly	
		ldd	_EE_s12xs_system_tos,y
		tfr	d,STACK_POINTER									// change the stack pointer
		
		rtc										// return from call(with PPAGE change)

	#endif // __MULTI__
	
	end
	
	
