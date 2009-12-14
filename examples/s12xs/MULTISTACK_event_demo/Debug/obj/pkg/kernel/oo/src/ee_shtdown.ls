   1                         ; C Compiler for S12X [COSMIC Software].
   2                         ; Generator (Limited) V4.7.11.2 - 16 Mar 2009
   3                         ; Optimizer V4.6.16 - 02 Dec 2008
3693                         ; 64 void EE_oo_ShutdownOS(StatusType Error)
3693                         ; 65 {
3694                         .ftext:	section	.text
3695  0000                   f_EE_oo_ShutdownOS:
3699  0000                   L5272:
3700                         ; 133 __INLINE__ void __ALWAYS_INLINE__ EE_oo_shutdown(void) { for(;;); }
3702  0000 20fe              	bra	L5272
3714                         	xref	_EE_pit0_initialized
3715                         	xref	_EE_ApplicationMode
3716                         	xref	_EE_oo_IRQ_disable_count
3717                         	xdef	f_EE_oo_ShutdownOS
3718                         	xref	_EE_oo_ErrorHook_data
3719                         	xref	_EE_oo_ErrorHook_ServiceID
3720                         	xref	_EE_stkfirst
3721                         	xref	_EE_th_next
3722                         	xref	_EE_th_status
3723                         	xref	_EE_buttons_initialized
3724                         	xref	f_EE_s12xs_terminate_task
3725                         	xref	f_EE_s12xs_terminate_savestk
3726                         	xref	_EE_IRQ_nesting_level
3727                         	xref	f_EE_s12xs_hal_stkchange
3728                         	xref	f_EE_s12xs_hal_ready2stacked
3729                         	xref	_EE_hal_endcycle_next_tos
3730                         	xref	_EE_hal_endcycle_next_thread
3731                         	xref	_EE_terminate_real_th_body
3732                         	xref	_EE_terminate_data
3733                         	xref	_EE_s12xs_thread_tos
3734                         	xref	_EE_hal_thread_body
3754                         	end
