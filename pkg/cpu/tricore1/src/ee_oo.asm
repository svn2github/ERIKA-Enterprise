; Author: 2005 Paolo Gai
; CVS: $Id: ee_oo.asm,v 1.1 2005/07/16 12:48:14 pj Exp $

.include "eecfgasm.h"

;	.global	EE_arm7_terminate_task
;	.global EE_arm7_terminate_savestk
	
;	.text

	;  kernel code is in ARM-mode
;	.arm
	
	; r0 = &terminate_data[t]
	; r1 = terminate_real_th_body[t]()
;	.type	EE_arm7_terminate_savestk, #function
;EE_arm7_terminate_savestk:
	; save some registers:	
	; - r0-r3 do not need to be saved 9they are already dirty
	;   with the call to this function;
	; - r4-r11 have to be saved because they maybe contain some
	;   data of the preempted threads
	; - r12 has to be saved because it is not guaranteed that the value
	;   will remain the same after we return from the TerminateTask
	; - lr has to be saved to be able to jump back to the thread final }
	;   in the thread stub into tstub.h
	; - only the data from the System level have to be saved, the others
	;   will be restored when needed directly by the prempter 
	;   threads/irqs
	;
	; Please note that the interrupt are ENABLED
;	STMFD	sp!, {r4-r12,lr}
	
	; save sp_sys in terminate_data[t]
;	STR sp, [r0]
	
	; jmp terminate_real_th_body[t]
;	BX r1
	
;	.size	EE_arm7_terminate_savestk, . - EE_arm7_terminate_savestk

	; r0 = &terminate_data[t]
;	.type	EE_arm7_terminate_task, #function
;EE_arm7_terminate_task:
	; reload sp_sys from terminate_data[t]	
;	LDR sp, [r0]
	; reload the registers saved before
;	LDMFD	sp!, {r4-r12,lr}
	; return back to the caller (in tstub.c!!!)
;	BX lr
;	.size	EE_arm7_terminate_task, . - EE_arm7_terminate_task
	
	.end
