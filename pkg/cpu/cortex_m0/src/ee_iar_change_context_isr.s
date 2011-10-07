/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
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
	@file ee_iar_change_context_isr.s
	@brief Functions to active and manage the context switch for Cortex_M0 
	@author Gianluca Franchino
	@date 2011
*/ 

;*******************************************************************************
;                         PUBLIC FUNCTIONS
;*******************************************************************************
		
	; Functions declared in this file 
	PUBLIC	EE_switch_context ; void EE_switch_context(void)
	PUBLIC  PendSV_Handler    ; void PendSV_Handler(void);
	PUBLIC	EE_set_switch_context_pri ; void EE_set_switch_context_pri(void)
	PUBLIC	EE_cortex_m0_change_context_active
	
	EXTERN	EE_cortex_m0_change_context
	EXTERN	EE_std_endcycle_next_tid	

;*******************************************************************************
;                              EQUATES
;*******************************************************************************	
NVIC_INT_CTRL   EQU     0xE000ED04      ; Interrupt control status register
NVIC_ICER		EQU 	0xE000E180		; Interrupt Clear Register
NVIC_SHPR3   	EQU     0xE000ED20      ; System priority register (PendSV 14) 0xE000ED20
NVIC_PENDSV_PRI EQU     0x00C00000      ; PendSV priority value (Lowest)
NVIC_PENDSVSET  EQU     0x10000000      ; Value to trigger PendSV exception
NVIC_PENDSVCLEAR  EQU   0x10000000      ; Value to trigger PendSV exception

EPSR_T_BIT_VAL	EQU 0x01000000			; Value to set the T-bit in EPSR (always Thumb mode)

;*******************************************************************************
;                              DATA SECTION
;*******************************************************************************	
	SECTION	CHN_C_DATA : DATA:NOROOT (2)
EE_cortex_m0_change_context_active: DS32 1	; EE_UREG EE_cortex_m0_change_context_active;

;*******************************************************************************
;                              CODE SECTION
;*******************************************************************************	
    SECTION    CODE : CODE(2)
    THUMB


; void EE_set_switch_context_pri(void)
EE_set_switch_context_pri:
;Set PendSV priority to the minumum one
	LDR		R0, =NVIC_SHPR3
	LDR     R1, =NVIC_PENDSV_PRI
	LDR		R2, [R0];
	ORRS	R2, R2, R1;
	STR		R2, [R0];
	BX	    LR
	
; void EE_switch_context(void)
EE_switch_context:
	;Trigger the PendSV exception (causes context switch)
    LDR     R0, =NVIC_INT_CTRL  
    LDR     R1, =NVIC_PENDSVSET
    STR     R1, [R0] 
	
    BX	    LR	
	
	
; void PendSV_Handler(void)
PendSV_Handler:
	CPSID i 						; Disable all interrupts except NMI (set PRIMASK)
									; Build a stack frame to jump into the EE_std_change_context(EE_TID)
									; at the end of PendSV_Handler.
    LDR R0, =NVIC_ICER				; Clear PendSv interrupt
	LDR	R1, =NVIC_PENDSVCLEAR 		; Load  0x10000000 in R1
	STR     R1, [R0]				; Clear any pending PendSv interrupt ICER = 0x10000000	
	MRS R2, PSR						; R2 = xPSR
	;MOVS R0, #0x80					; R0 = 0x00000080
	;LSLS R0, #0x11					; R0 = 0x01000000
	LDR	 R0, =EPSR_T_BIT_VAL		; R0 = 0x01000000
	ORRS R2, R2, R0					; R2 = (xPSR OR 0x01000000). This guarantees that Thumbs bit is set
									; to avoid an hard_fault exception
	MOVS R0, #0x20					; R0 = 0x00000020
	RSBS R0, R0, #0;				; R0 = 0xFFFFFFE0
	ANDS R2, R2, R0					; R2 = (xPSR AND 0xFFFFFE0) -> In this way, we return in Thread mode. 
	LDR R1, =EE_cortex_m0_change_context	  ; R1 = EE_cortex_m0_change_context (PC)		
	LDR R0, =exit_EE_cortex_m0_change_context ; R0 = exit_EE_cortex_m0_change_context (LR)
	PUSH {R0-R2}					;
	PUSH {R0}						;Since PUSH cannot use R12, put R0 onto stack as R12
	LDR R0, =EE_std_endcycle_next_tid ; R0 = address of EE_std_endcycle_next_tid
	LDR     R0,[R0]					; R0 = EE_std_endcycle_next_tid
									; Note: following the call convention, EE_cortex_m0_change_context
									; will get EE_std_endcycle_next_tid from R0.
	PUSH {R0-R3}					;Fake IRQ handler frame on top of PendSV frame:
									;|xPSR|
									;| PC |-> EE_std_change_context
									;| LR |-> exitPendSV (LR)
									;| R12|
									;| R3 |
									;| R2 |
									;| R1 |
									;| R0 | <- MSP									

exitPendSV:
	; EE_cortex_m0_change_context_active = 0
	SUBS R0, R0, R0
	LDR R1, =EE_cortex_m0_change_context_active    
	STR	R0, [R1]
	
    MOVS    R0,#8					; R0 = 0x8
    RSBS    R0, R0, #0              ; R0 = 0xFFFFFFF8
	ADDS	R0, R0, #1				; R0 = 0xFFFFFFF9 
									; EXC_RETURN = R0 -> Return to Thread mode.
									;			      -> Exception return gets state from MSP.
									;			      -> Execution uses MSP after return.
    BX      R0                  	; Exit interrupt

;
;This function restores the context before the IRQ that caused a context change
;through EE_cortex_m0_IRQ_active_change_context(void);
;
exit_EE_cortex_m0_change_context:
	;SVC #0
	;incrementa stack pointer per scartare frame 
	
	;mrs r0, msp
	MRS R0, MSP ; Get the stack pointer
	
	LDR R1, [R0, #28] ; Status xPSR  in R1
	MSR PSR, R1 ;Restore xPSR
	
	LDR R2, [R0, #20]; Load LR from stack
	MOV LR, R2		 ; Restore LR
	
	LDR R1, [R0, #24]; Get the value of PC from the stack
	ADDS R1, R1, #0x01	 ; Set Bit[0] of R1 to ensure that T-bit in APSR is 1,
					 ; that is, the processor must work in Thumb mode
	STR R1, [R0, #28]; Store value of PC from stack has the
					 ; first value on the stack frame. 
					 ; This value is used as return address
	
	LDR R1, [R0]; Get the value of R0 from the stack
	STR R1, [R0, #20] ;Store value of R0 from the stack
					  ;onto the stack at the place of LR
	STR R1, [R0, #24] ;Store value of R0 from the stack 
					  ;onto the stack at the place of PC
	MOV R12, R4 ; Use R12 to save the current value of R4					
	POP {R0-R4}; Restore Scratch registers
				; Note: in R4 we get the scratch register R12
	MOV R0, R12 ; Use R0 to save the value of R4 before the pop instruc.,
				;(which is stored in R12)			
	MOV R12, R4 ; Restore Scratch register R12
	MOV R4, R0	; Restore R4
	POP {R0}; Move stack pointer getting again R0
	CPSIE i ; Enable interrupts (clear PRIMASK)
	POP {R0, PC}; Move stack pointer getting again R0 and return
				; updating PC 
				
    END	
	