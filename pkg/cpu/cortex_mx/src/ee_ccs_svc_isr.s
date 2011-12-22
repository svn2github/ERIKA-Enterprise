; ###*B*###
; ERIKA Enterprise - a tiny RTOS for small microcontrollers
;
; Copyright (C) 2002-2011  Evidence Srl
;
; This file is part of ERIKA Enterprise.
;
; ERIKA Enterprise is free software; you can redistribute it
; and/or modify it under the terms of the GNU General Public License
; version 2 as published by the Free Software Foundation, 
; (with a special exception described below).
;
; Linking this code statically or dynamically with other modules is
; making a combined work based on this code.  Thus, the terms and
; conditions of the GNU General Public License cover the whole
; combination.
;
; As a special exception, the copyright holders of this library give you
; permission to link this code with independent modules to produce an
; executable, regardless of the license terms of these independent
; modules, and to copy and distribute the resulting executable under
; terms of your choice, provided that you also meet, for each linked
; independent module, the terms and conditions of the license of that
; module.  An independent module is a module which is not derived from
; or based on this library.  If you modify this code, you may extend
; this exception to your version of the code, but you are not
; obligated to do so.  If you do not wish to do so, delete this
; exception statement from your version.
;
; ERIKA Enterprise is distributed in the hope that it will be
; useful, but WITHOUT ANY WARRANTY; without even the implied warranty
; of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License version 2 for more details.
;
; You should have received a copy of the GNU General Public License
; version 2 along with ERIKA Enterprise; if not, write to the
; Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
; Boston, MA 02110-1301 USA.
; ###*E*###

;	@file ee_ccs_svc_isr.s
;	@brief Functions to manage the supervisor-calls for Cortex_MX
;	@author Giuseppe Serano
;	@date 2011

;*******************************************************************************
;                         PUBLIC FUNCTIONS
;*******************************************************************************

; Functions declared in this file 
	.global	EE_cortex_mx_sv_call_handler	; void EE_cortex_mx_pendsv_handler(void);
	.global	EE_set_sv_call_pri	; void EE_set_switch_context_pri(void)

;*******************************************************************************
;                              CODE SECTION
;*******************************************************************************
	.text

NVIC_SHPR2	.word	0E000ED1Ch	; System priority register (SVCall 11)
NVIC_SVCALL_PRI	.word	0FF000000h	; SVCall priority value (Lowest)

; void EE_set_sv_call_pri(void)
EE_set_sv_call_pri:
	.asmfunc
;Set SVCall priority to the minumum one
	LDR	R0, NVIC_SHPR2
	LDR	R1, NVIC_SVCALL_PRI
	LDR	R2, [R0];
	ORRS	R2, R2, R1;
	STR	R2, [R0];
	BX	LR
	.endasmfunc

; void EE_cortex_mx_sv_call_handler(void)
EE_cortex_mx_sv_call_handler:
	.asmfunc
	CPSID i				; Disable all interrupts except NMI (set PRIMASK)
exitSVCall:
	MOVS	R0,#8			; R0 = 0x8
	RSBS	R0, R0, #0		; R0 = 0xFFFFFFF8
	ADDS	R0, R0, #1		; R0 = 0xFFFFFFF9 
					; EXC_RETURN = R0 -> Return to Thread mode.
					;		  -> Exception return gets state from MSP.
					;		  -> Execution uses MSP after return.
	BX	R0			; Exit interrupt
	.endasmfunc

	.end
