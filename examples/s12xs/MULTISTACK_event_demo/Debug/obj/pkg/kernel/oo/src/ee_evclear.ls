   1                         ; C Compiler for S12X [COSMIC Software].
   2                         ; Generator (Limited) V4.7.11.2 - 16 Mar 2009
   3                         ; Optimizer V4.6.16 - 02 Dec 2008
3704                         ; 63 void EE_oo_ClearEvent(EventMaskType Mask)
3704                         ; 64 #endif
3704                         ; 65 {
3705                         .ftext:	section	.text
3706  0000                   f_EE_oo_ClearEvent:
3708  0000 3b                	pshd	
3709  0001 1b9c              	leas	-4,s
3710       00000004          OFST:	set	4
3713                         ; 62     return EE_stkfirst;  
3716  0003 fd0002            	ldy	_EE_stkfirst+2
3717  0006 6d82              	sty	OFST-2,s
3718  0008 fe0000            	ldx	_EE_stkfirst
3719  000b 6e80              	stx	OFST-4,s
3721                         ; 63 }
3723                         ; 200   ASM_DIS_INT;
3726  000d 1410              	sei	
3728                         ; 137   EE_th_event_active[current] &= ~Mask;
3731  000f 1858              	lsly	
3732  0011 ee84              	ldx	OFST+0,s
3733  0013 1841              	comx	
3734  0015 18a4ea0000        	andx	_EE_th_event_active,y
3735  001a 6eea0000          	stx	_EE_th_event_active,y
3736                         ; 191   ASM_EN_INT;
3739  001e 10ef              	cli	
3741                         ; 148 }
3745  0020 1b86              	leas	6,s
3746  0022 0a                	rtc	
3758                         	xref	_EE_pit0_initialized
3759                         	xref	_EE_ApplicationMode
3760                         	xref	_EE_oo_IRQ_disable_count
3761                         	xdef	f_EE_oo_ClearEvent
3762                         	xref	_EE_oo_ErrorHook_data
3763                         	xref	_EE_oo_ErrorHook_ServiceID
3764                         	xref	_EE_th_event_active
3765                         	xref	_EE_stkfirst
3766                         	xref	_EE_th_next
3767                         	xref	_EE_th_status
3768                         	xref	_EE_buttons_initialized
3769                         	xref	f_EE_s12xs_terminate_task
3770                         	xref	f_EE_s12xs_terminate_savestk
3771                         	xref	_EE_IRQ_nesting_level
3772                         	xref	f_EE_s12xs_hal_stkchange
3773                         	xref	f_EE_s12xs_hal_ready2stacked
3774                         	xref	_EE_hal_endcycle_next_tos
3775                         	xref	_EE_hal_endcycle_next_thread
3776                         	xref	_EE_terminate_real_th_body
3777                         	xref	_EE_terminate_data
3778                         	xref	_EE_s12xs_thread_tos
3779                         	xref	_EE_hal_thread_body
3799                         	end
