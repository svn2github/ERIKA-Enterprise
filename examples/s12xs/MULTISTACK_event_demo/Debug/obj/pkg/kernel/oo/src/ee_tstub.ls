   1                         ; C Compiler for S12X [COSMIC Software].
   2                         ; Generator (Limited) V4.7.11.2 - 16 Mar 2009
   3                         ; Optimizer V4.6.16 - 02 Dec 2008
3700                         ; 57 void EE_oo_thread_stub(void)
3700                         ; 58 {
3701                         .ftext:	section	.text
3702  0000                   f_EE_oo_thread_stub:
3704  0000 1b9c              	leas	-4,s
3705       00000004          OFST:	set	4
3708                         ; 62     return EE_stkfirst;  
3711  0002 fc0002            	ldd	_EE_stkfirst+2
3712  0005 6c82              	std	OFST-2,s
3713  0007 fe0000            	ldx	_EE_stkfirst
3714  000a 6e80              	stx	OFST-4,s
3716                         ; 63 }
3721                         ; 222   EE_s12xs_terminate_savestk(&EE_terminate_data[t],
3721                         ; 223 			       (EE_ADDR)EE_terminate_real_th_body[t]);
3723  000c cd0000            	ldy	#_EE_terminate_real_th_body
3724  000f 59                	lsld	
3725  0010 59                	lsld	
3726  0011 19ee              	leay	d,y
3727  0013 ec42              	ldd	2,y
3728  0015 3b                	pshd	
3729  0016 ec40              	ldd	0,y
3730  0018 3b                	pshd	
3731  0019 ec86              	ldd	OFST+2,s
3732  001b 59                	lsld	
3733  001c c30000            	addd	#_EE_terminate_data
3734  001f 4a000000          	call	f_EE_s12xs_terminate_savestk
3736                         ; 73 }
3740  0023 1b88              	leas	8,s
3741  0025 0a                	rtc	
3753                         	xref	_EE_pit0_initialized
3754                         	xref	_EE_ApplicationMode
3755                         	xref	_EE_oo_IRQ_disable_count
3756                         	xref	_EE_oo_ErrorHook_data
3757                         	xref	_EE_oo_ErrorHook_ServiceID
3758                         	xref	_EE_stkfirst
3759                         	xref	_EE_th_next
3760                         	xref	_EE_th_status
3761                         	xref	_EE_buttons_initialized
3762                         	xref	f_EE_s12xs_terminate_task
3763                         	xref	f_EE_s12xs_terminate_savestk
3764                         	xref	_EE_IRQ_nesting_level
3765                         	xref	f_EE_s12xs_hal_stkchange
3766                         	xref	f_EE_s12xs_hal_ready2stacked
3767                         	xref	_EE_hal_endcycle_next_tos
3768                         	xref	_EE_hal_endcycle_next_thread
3769                         	xdef	f_EE_oo_thread_stub
3770                         	xref	_EE_terminate_real_th_body
3771                         	xref	_EE_terminate_data
3772                         	xref	_EE_s12xs_thread_tos
3773                         	xref	_EE_hal_thread_body
3793                         	end
