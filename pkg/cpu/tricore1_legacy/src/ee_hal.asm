; Author: 2005 Paolo Gai
; CVS: $Id: ee_hal.asm,v 1.1 2005/06/03 07:05:33 pj Exp $

.include "eecfgasm.h"

.if @DEF('__MULTI__')
;	.global EE_tc1_hal_stkchange
.endif

; system TOS
.if @DEF('__MULTI__')
;	.extern	EE_tc1_system_tos
;	.extern	EE_tc1_active_tos
.endif

; this variable is used by EE_tc1_change_to_irq_tos and
; EE_tc1_change_from_irq_tos to store the current thread TOS
.if @DEF('__MULTI__')
.if @DEF('__IRQ_STACK_NEEDED__')
;EE_tc1_temp_tos:	
;	.zero 8	; sys+irq
.endif
.endif
		
;	.text

	
; 
; This code is called when we have to change the thread stack
; NOTE: r1 *MUST* contain tos_index, while r0 (the thread address)
; will be unchanged!!!
;

.if @DEF('__MULTI__')
;EE_tc1_change_tos:	
	; if tos_index == EE_tc1_active_tos then we do not have to
	; switch stack
;	LDR	r2, =EE_tc1_active_tos
;	LDR	r3, [r2]

;	CMP	r3, r1
;	MOVEQ	pc, lr

	; Before changing the stack, we have to save the registers
	; that could be modified (i.e. all the registers that should
	; be preserved through function calls). Note that if there is
	; not the stack change, the system will behave like the
	; monostack version of the kernel
; 	STMFD	sp!, {r4-r11}

	; from now until the LDMFD I can use r0-r11 as scratch!
	; r2=&EE_tc1_active_tos
	; r4=&EE_tc1_system_tos
	
	;
	; Save current TOS
	;
	; r4 = &EE_tc1_system_tos
;	LDR	r4, =EE_tc1_system_tos
	; r3 = & EE_tc1_system_tos[EE_tc1_active_tos].SYS_tos
;	ADD	r3, r4, r3, LSL#3

	; EE_tc1_system_tos[EE_tc1_active_tos].SYS_tos = sp_SYS
;	STMIA	r3!, {sp}

	; EE_tc1_system_tos[EE_tc1_active_tos].IRQ_tos = sp_IRQ
;	MOV	r5, #Mode_IRQ | I_bit
; 	MSR	cpsr_c, r5
;	STMIA	r3, {sp}	
;	MOV	r6, #Mode_SYS | I_bit
; 	MSR	cpsr_c, r6

	
	;
	; New current TOS
	;
	; remember that r4 = &EE_tc1_system_tos
	; r3 = & EE_tc1_system_tos[tos_index].SYS_tos
;	ADD	r3, r4, r1, LSL#3

	; sp_SYS = EE_tc1_system_tos[tos_index].SYS_tos
;	LDMIA	r3!, {sp}
	
	; sp_IRQ = EE_tc1_system_tos[tos_index].IRQ_tos
	; remember that r5 = #Mode_IRQ | I_bit, r6=#Mode_SYS | I_bit
; 	MSR	cpsr_c, r5
;	LDMIA	r3, {sp}
; 	MSR	cpsr_c, r6

	;
	; Update tc1_active_tos (= tos_index)
	;
	; remember that r2=&EE_tc1_active_tos
;	STR	r1, [r2]

	; Here we have to restore the registers saved before the
	; stack previous change. If this is the first time we use the
	; current stack, restoring is useless...
; 	LDMFD	sp!, {r4-r11}
	
;	MOV	pc, lr
.endif ; __MULTI__



	

.if @DEF('__MULTI__')

;
; MONO:  not defined
; MULTI: void EE_tc1_hal_stkchange(EE_UREG 0, EE_UREG tos_index)
;
; Typically called into a generic primitive to implement a blocking
; synchronization primitive.
;
;	.type	EE_tc1_hal_stkchange, #function
;EE_tc1_hal_stkchange:	
	
	; Mk: saving lr here and restoring it after EE_tc1_change_tos is mandatory, in order to
	; save lr of the preempted thread and to restore lr of the preempter thread
	;	from their respective stacks!
; 	STMFD	sp!, {lr}

	; switch to the TOS of the new thread
;	BL	EE_tc1_change_tos

	; now the stack is changed, and we need to return to the interrupted thread!
;	LDMFD	sp!, {lr}
;	BX	lr
;	.size	EE_tc1_hal_stkchange, . - EE_tc1_hal_stkchange


	
	.end
