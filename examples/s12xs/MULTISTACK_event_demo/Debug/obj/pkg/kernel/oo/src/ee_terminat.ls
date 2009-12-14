   1                         ; C Compiler for S12X [COSMIC Software].
   2                         ; Generator (Limited) V4.7.11.2 - 16 Mar 2009
   3                         ; Optimizer V4.6.16 - 02 Dec 2008
3697                         ; 147 void EE_oo_TerminateTask(void)
3697                         ; 148 {
3698                         .ftext:	section	.text
3699  0000                   f_EE_oo_TerminateTask:
3701  0000 1b98              	leas	-8,s
3702       00000008          OFST:	set	8
3705                         ; 62     return EE_stkfirst;  
3708  0002 fc0002            	ldd	_EE_stkfirst+2
3710                         ; 63 }
3712  0005 cd0000            	ldy	#_EE_th_terminate_nextask
3713  0008 59                	lsld	
3714  0009 59                	lsld	
3715  000a 19ee              	leay	d,y
3716  000c ccffff            	ldd	#-1
3717  000f 6c42              	std	2,y
3718  0011 6c40              	std	0,y
3719                         ; 62     return EE_stkfirst;  
3722  0013 1801860002        	movw	_EE_stkfirst+2,OFST-2,s
3723  0018 1801840000        	movw	_EE_stkfirst,OFST-4,s
3725                         ; 228   EE_s12xs_terminate_task(&EE_terminate_data[t]);
3728  001d ec86              	ldd	OFST-2,s
3729  001f 59                	lsld	
3730  0020 c30000            	addd	#_EE_terminate_data
3731  0023 4a000000          	call	f_EE_s12xs_terminate_task
3733                         ; 165 }
3737  0027 1b88              	leas	8,s
3738  0029 0a                	rtc	
3750                         	xref	_EE_pit0_initialized
3751                         	xref	_EE_ApplicationMode
3752                         	xref	_EE_oo_IRQ_disable_count
3753                         	xdef	f_EE_oo_TerminateTask
3754                         	xref	_EE_oo_ErrorHook_data
3755                         	xref	_EE_oo_ErrorHook_ServiceID
3756                         	xref	_EE_stkfirst
3757                         	xref	_EE_th_terminate_nextask
3758                         	xref	_EE_th_next
3759                         	xref	_EE_th_status
3760                         	xref	_EE_buttons_initialized
3761                         	xref	f_EE_s12xs_terminate_task
3762                         	xref	f_EE_s12xs_terminate_savestk
3763                         	xref	_EE_IRQ_nesting_level
3764                         	xref	f_EE_s12xs_hal_stkchange
3765                         	xref	f_EE_s12xs_hal_ready2stacked
3766                         	xref	_EE_hal_endcycle_next_tos
3767                         	xref	_EE_hal_endcycle_next_thread
3768                         	xref	_EE_terminate_real_th_body
3769                         	xref	_EE_terminate_data
3770                         	xref	_EE_s12xs_thread_tos
3771                         	xref	_EE_hal_thread_body
3791                         	end
