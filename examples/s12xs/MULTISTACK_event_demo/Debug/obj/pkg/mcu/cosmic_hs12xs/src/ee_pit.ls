   1                         ; C Compiler for S12X [COSMIC Software].
   2                         ; Generator (Limited) V4.7.11.2 - 16 Mar 2009
   3                         ; Optimizer V4.6.16 - 02 Dec 2008
3604                         	switch	.data
3605  0000                   _EE_pit0_initialized:
3606  0000 00                	dc.b	0
3641                         	xref	f_EE_IRQ_end_instance
3642                         	xref	f_EE_s12xs_terminate_task
3643                         	xref	f_EE_s12xs_terminate_savestk
3644                         	xref	_EE_IRQ_nesting_level
3645                         	xref	f_EE_s12xs_hal_stkchange
3646                         	xref	f_EE_s12xs_hal_ready2stacked
3647                         	xref	_EE_hal_endcycle_next_tos
3648                         	xref	_EE_hal_endcycle_next_thread
3649                         	xdef	_EE_pit0_initialized
3650                         	xref	_EE_ApplicationMode
3651                         	xref	_EE_oo_IRQ_disable_count
3652                         	xref	_EE_oo_ErrorHook_data
3653                         	xref	_EE_oo_ErrorHook_ServiceID
3654                         	xref	_EE_stkfirst
3655                         	xref	_EE_th_next
3656                         	xref	_EE_th_status
3657                         	xref	_EE_buttons_initialized
3658                         	xref	_EE_terminate_real_th_body
3659                         	xref	_EE_terminate_data
3660                         	xref	_EE_s12xs_active_tos
3661                         	xref	_EE_s12xs_thread_tos
3662                         	xref	_EE_hal_thread_body
3682                         	end
