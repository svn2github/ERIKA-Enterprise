   1                         ; C Compiler for S12X [COSMIC Software].
   2                         ; Generator (Limited) V4.7.11.2 - 16 Mar 2009
   3                         ; Optimizer V4.6.16 - 02 Dec 2008
3722                         ; 64 void EE_oo_GetResource(ResourceType ResID)
3722                         ; 65 #endif
3722                         ; 66 {
3723                         .ftext:	section	.text
3724  0000                   f_EE_oo_GetResource:
3726  0000 3b                	pshd	
3727  0001 1b9c              	leas	-4,s
3728       00000004          OFST:	set	4
3731                         ; 101   retvalue = _asm("tfr ccr,b\n");	// save CCR register (I bit)
3735  0003 b721              	tfr	ccr,b
3737                         ; 200   ASM_DIS_INT;
3740  0005 1410              	sei	
3742                         ; 104   return retvalue;
3745  0007 6c82              	std	OFST-2,s
3747                         ; 105 }
3749                         ; 174   EE_resource_oldceiling[ResID] = EE_sys_ceiling;
3751  0009 ed84              	ldy	OFST+0,s
3752  000b 1858              	lsly	
3753  000d 1801ea00000000    	movw	_EE_sys_ceiling,_EE_resource_oldceiling,y
3754                         ; 175   EE_sys_ceiling |= EE_resource_ceiling[ResID];
3756  0014 edea0000          	ldy	_EE_resource_ceiling,y
3757  0018 18fa0000          	ory	_EE_sys_ceiling
3758  001c 7d0000            	sty	_EE_sys_ceiling
3759                         ; 111   if(f & 0x10) 						// restore I bit
3762  001f 0f831004          	brclr	OFST-1,s,16,L7672
3763                         ; 200   ASM_DIS_INT;
3766  0023 1410              	sei	
3768  0025 2002              	bra	L7172
3769  0027                   L7672:
3770                         ; 191   ASM_EN_INT;
3773  0027 10ef              	cli	
3775  0029                   L7172:
3776                         ; 197 }
3780  0029 1b86              	leas	6,s
3781  002b 0a                	rtc	
3793                         	xref	_EE_pit0_initialized
3794                         	xref	_EE_ApplicationMode
3795                         	xref	_EE_oo_IRQ_disable_count
3796                         	xdef	f_EE_oo_GetResource
3797                         	xref	_EE_oo_ErrorHook_data
3798                         	xref	_EE_oo_ErrorHook_ServiceID
3799                         	xref	_EE_resource_oldceiling
3800                         	xref	_EE_resource_ceiling
3801                         	xref	_EE_sys_ceiling
3802                         	xref	_EE_stkfirst
3803                         	xref	_EE_th_next
3804                         	xref	_EE_th_status
3805                         	xref	_EE_buttons_initialized
3806                         	xref	f_EE_s12xs_terminate_task
3807                         	xref	f_EE_s12xs_terminate_savestk
3808                         	xref	_EE_IRQ_nesting_level
3809                         	xref	f_EE_s12xs_hal_stkchange
3810                         	xref	f_EE_s12xs_hal_ready2stacked
3811                         	xref	_EE_hal_endcycle_next_tos
3812                         	xref	_EE_hal_endcycle_next_thread
3813                         	xref	_EE_terminate_real_th_body
3814                         	xref	_EE_terminate_data
3815                         	xref	_EE_s12xs_thread_tos
3816                         	xref	_EE_hal_thread_body
3836                         	end
