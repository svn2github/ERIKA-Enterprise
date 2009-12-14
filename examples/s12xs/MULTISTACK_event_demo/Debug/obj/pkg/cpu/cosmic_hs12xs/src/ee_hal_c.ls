   1                         ; C Compiler for S12X [COSMIC Software].
   2                         ; Generator (Limited) V4.7.11.2 - 16 Mar 2009
   3                         ; Optimizer V4.6.16 - 02 Dec 2008
3654                         	xref	_EE_pit0_initialized
3655                         	xref	_EE_ApplicationMode
3656                         	xref	_EE_oo_IRQ_disable_count
3657                         	xref	_EE_oo_ErrorHook_data
3658                         	xref	_EE_oo_ErrorHook_ServiceID
3659                         	xref	_EE_stkfirst
3660                         	xref	_EE_th_next
3661                         	xref	_EE_th_status
3662                         	xref	_EE_buttons_initialized
3663                         	xref	f_EE_s12xs_terminate_task
3664                         	xref	f_EE_s12xs_terminate_savestk
3665                         	switch	.bss
3666  0000                   _EE_IRQ_nesting_level:
3667  0000 0000              	ds.b	2
3668                         	xdef	_EE_IRQ_nesting_level
3669                         	xref	f_EE_s12xs_hal_stkchange
3670                         	xref	f_EE_s12xs_hal_ready2stacked
3671  0002                   _EE_hal_endcycle_next_tos:
3672  0002 0000              	ds.b	2
3673                         	xdef	_EE_hal_endcycle_next_tos
3674  0004                   _EE_hal_endcycle_next_thread:
3675  0004 00000000          	ds.b	4
3676                         	xdef	_EE_hal_endcycle_next_thread
3677                         	xref	_EE_terminate_real_th_body
3678                         	xref	_EE_terminate_data
3679                         	xref	_EE_s12xs_thread_tos
3680                         	xref	_EE_hal_thread_body
3701                         	end
