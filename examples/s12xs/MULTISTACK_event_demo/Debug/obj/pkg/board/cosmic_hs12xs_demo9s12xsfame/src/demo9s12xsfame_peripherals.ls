   1                         ; C Compiler for S12X [COSMIC Software].
   2                         ; Generator (Limited) V4.7.11.2 - 16 Mar 2009
   3                         ; Optimizer V4.6.16 - 02 Dec 2008
3604                         	switch	.data
3605  0000                   _EE_buttons_initialized:
3606  0000 00                	dc.b	0
3607  0001                   _EE_adc_init:
3608  0001 00                	dc.b	0
3654                         	xdef	_EE_adc_init
3655                         	xref	f_EE_IRQ_end_instance
3656                         	xref	_EE_pit0_initialized
3657                         	xref	_EE_ApplicationMode
3658                         	xref	_EE_oo_IRQ_disable_count
3659                         	xref	_EE_oo_ErrorHook_data
3660                         	xref	_EE_oo_ErrorHook_ServiceID
3661                         	xref	_EE_stkfirst
3662                         	xref	_EE_th_next
3663                         	xref	_EE_th_status
3664                         	xdef	_EE_buttons_initialized
3665                         	xref	f_EE_s12xs_terminate_task
3666                         	xref	f_EE_s12xs_terminate_savestk
3667                         	xref	_EE_IRQ_nesting_level
3668                         	xref	f_EE_s12xs_hal_stkchange
3669                         	xref	f_EE_s12xs_hal_ready2stacked
3670                         	xref	_EE_hal_endcycle_next_tos
3671                         	xref	_EE_hal_endcycle_next_thread
3672                         	xref	_EE_terminate_real_th_body
3673                         	xref	_EE_terminate_data
3674                         	xref	_EE_s12xs_active_tos
3675                         	xref	_EE_s12xs_thread_tos
3676                         	xref	_EE_hal_thread_body
3696                         	end
