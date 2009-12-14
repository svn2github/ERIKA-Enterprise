   1                         ; C Compiler for S12X [COSMIC Software].
   2                         ; Generator (Limited) V4.7.11.2 - 16 Mar 2009
   3                         ; Optimizer V4.6.16 - 02 Dec 2008
3730                         ; 64 void EE_oo_GetEvent(TaskType TaskID, EventMaskRefType Event)
3730                         ; 65 #endif
3730                         ; 66 {
3731                         .ftext:	section	.text
3732  0000                   f_EE_oo_GetEvent:
3734  0000 3b                	pshd	
3735  0001 34                	pshx	
3736  0002 1b9c              	leas	-4,s
3737       00000004          OFST:	set	4
3740                         ; 101   retvalue = _asm("tfr ccr,b\n");	// save CCR register (I bit)
3744  0004 b721              	tfr	ccr,b
3746                         ; 200   ASM_DIS_INT;
3749  0006 1410              	sei	
3751                         ; 104   return retvalue;
3754  0008 6c82              	std	OFST-2,s
3756                         ; 105 }
3758                         ; 161   *Event = EE_th_event_active[TaskID];
3760  000a ed8b              	ldy	OFST+7,s
3761  000c ee86              	ldx	OFST+2,s
3762  000e 1848              	lslx	
3763  0010 1802e2000040      	movw	_EE_th_event_active,x,0,y
3764                         ; 111   if(f & 0x10) 						// restore I bit
3767  0016 c510              	bitb	#16
3768  0018 2704              	beq	L3772
3769                         ; 200   ASM_DIS_INT;
3772  001a 1410              	sei	
3774  001c 2002              	bra	L7172
3775  001e                   L3772:
3776                         ; 191   ASM_EN_INT;
3779  001e 10ef              	cli	
3781  0020                   L7172:
3782                         ; 172 }
3786  0020 1b88              	leas	8,s
3787  0022 0a                	rtc	
3799                         	xref	_EE_pit0_initialized
3800                         	xref	_EE_ApplicationMode
3801                         	xref	_EE_oo_IRQ_disable_count
3802                         	xdef	f_EE_oo_GetEvent
3803                         	xref	_EE_oo_ErrorHook_data
3804                         	xref	_EE_oo_ErrorHook_ServiceID
3805                         	xref	_EE_th_event_active
3806                         	xref	_EE_stkfirst
3807                         	xref	_EE_th_next
3808                         	xref	_EE_th_status
3809                         	xref	_EE_buttons_initialized
3810                         	xref	f_EE_s12xs_terminate_task
3811                         	xref	f_EE_s12xs_terminate_savestk
3812                         	xref	_EE_IRQ_nesting_level
3813                         	xref	f_EE_s12xs_hal_stkchange
3814                         	xref	f_EE_s12xs_hal_ready2stacked
3815                         	xref	_EE_hal_endcycle_next_tos
3816                         	xref	_EE_hal_endcycle_next_thread
3817                         	xref	_EE_terminate_real_th_body
3818                         	xref	_EE_terminate_data
3819                         	xref	_EE_s12xs_thread_tos
3820                         	xref	_EE_hal_thread_body
3840                         	end
