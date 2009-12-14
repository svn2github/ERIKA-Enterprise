   1                         ; C Compiler for S12X [COSMIC Software].
   2                         ; Generator (Limited) V4.7.11.2 - 16 Mar 2009
   3                         ; Optimizer V4.6.16 - 02 Dec 2008
3604                         	switch	.data
3605  0000                   _wreg:
3606  0000 00000000          	dc.l	0
3607  0004                   _EE_s12xs_thread_tos:
3608  0004 0000              	dc.w	0
3609  0006 0001              	dc.w	1
3610  0008 0002              	dc.w	2
3611  000a                   _EE_s12xs_system_tos:
3612  000a 0000              	dc.w	0
3613  000c 05fe              	dc.w	_EE_s12xs_stack_1+510
3614  000e 03fe              	dc.w	_EE_s12xs_stack_2+510
3615  0010                   _EE_s12xs_active_tos:
3616  0010 0000              	dc.w	0
3617  0012                   _EE_s12xs_IRQ_tos:
3618  0012 01fe              	dc.w	_EE_s12xs_stack_3+510
3619                         .const:	section	.data
3620  0000                   _EE_hal_thread_body:
3622  0000 0000              	dc.w	f_EE_oo_thread_stub
3623  0002 0000              	dc.b	page(f_EE_oo_thread_stub),0
3625  0004 0000              	dc.w	f_EE_oo_thread_stub
3626  0006 0000              	dc.b	page(f_EE_oo_thread_stub),0
3627  0008                   _EE_terminate_real_th_body:
3629  0008 0000              	dc.w	f_FuncTask1
3630  000a 0000              	dc.b	page(f_FuncTask1),0
3632  000c 0000              	dc.w	f_FuncTask2
3633  000e 0000              	dc.b	page(f_FuncTask2),0
3634  0010                   _EE_th_ready_prio:
3635  0010 0001              	dc.w	1
3636  0012 0002              	dc.w	2
3637  0014                   _EE_th_dispatch_prio:
3638  0014 0001              	dc.w	1
3639  0016 0002              	dc.w	2
3640                         	switch	.data
3641  0014                   _EE_th_status:
3642  0014 0003              	dc.w	3
3643  0016 0003              	dc.w	3
3644  0018                   _EE_th_next:
3645  0018 ffffffff          	dc.l	-1
3646  001c ffffffff          	dc.l	-1
3647  0020                   _EE_stkfirst:
3648  0020 ffffffff          	dc.l	-1
3649  0024                   _EE_sys_ceiling:
3650  0024 0000              	dc.w	0
3651  0026                   _EE_rq_queues_head:
3652  0026 ffff              	dc.w	-1
3653  0028 ffff              	dc.w	-1
3654  002a ffff              	dc.w	-1
3655  002c ffff              	dc.w	-1
3656  002e ffff              	dc.w	-1
3657  0030 ffff              	dc.w	-1
3658  0032 ffff              	dc.w	-1
3659  0034 ffff              	dc.w	-1
3660  0036 ffff              	dc.w	-1
3661  0038 ffff              	dc.w	-1
3662  003a ffff              	dc.w	-1
3663  003c ffff              	dc.w	-1
3664  003e ffff              	dc.w	-1
3665  0040 ffff              	dc.w	-1
3666  0042 ffff              	dc.w	-1
3667  0044 ffff              	dc.w	-1
3668  0046                   _EE_rq_queues_tail:
3669  0046 ffff              	dc.w	-1
3670  0048 ffff              	dc.w	-1
3671  004a ffff              	dc.w	-1
3672  004c ffff              	dc.w	-1
3673  004e ffff              	dc.w	-1
3674  0050 ffff              	dc.w	-1
3675  0052 ffff              	dc.w	-1
3676  0054 ffff              	dc.w	-1
3677  0056 ffff              	dc.w	-1
3678  0058 ffff              	dc.w	-1
3679  005a ffff              	dc.w	-1
3680  005c ffff              	dc.w	-1
3681  005e ffff              	dc.w	-1
3682  0060 ffff              	dc.w	-1
3683  0062 ffff              	dc.w	-1
3684  0064 ffff              	dc.w	-1
3685  0066                   _EE_rq_bitmask:
3686  0066 0000              	dc.w	0
3687  0068                   _EE_th_rnact:
3688  0068 0001              	dc.w	1
3689  006a 0001              	dc.w	1
3690  006c                   _EE_rq_link:
3691  006c 0000              	dc.w	0
3692  006e 0001              	dc.w	1
3693  0070                   _EE_rq_pairs_next:
3694  0070 0001              	dc.w	1
3695  0072 ffff              	dc.w	-1
3696  0074                   _EE_rq_free:
3697  0074 0000              	dc.w	0
3698  0076                   _EE_th_terminate_nextask:
3699  0076 ffffffff          	dc.l	-1
3700  007a ffffffff          	dc.l	-1
3701  007e                   _EE_th_event_active:
3702  007e 0000              	dc.w	0
3703  0080 0000              	dc.w	0
3704  0082                   _EE_th_event_waitmask:
3705  0082 0000              	dc.w	0
3706  0084 0000              	dc.w	0
3707  0086                   _EE_th_waswaiting:
3708  0086 0000              	dc.w	0
3709  0088 0000              	dc.w	0
3710  008a                   _EE_th_is_extended:
3711  008a 0001              	dc.w	1
3712  008c 0000              	dc.w	0
3713  008e                   _EE_th_resource_last:
3714  008e ffff              	dc.w	-1
3715  0090 ffff              	dc.w	-1
3716  0092                   _EE_resource_stack:
3717  0092 ffff              	dc.w	-1
3718  0094                   _EE_resource_locked:
3719  0094 0000              	dc.w	0
3720                         	switch	.const
3721  0018                   _EE_resource_ceiling:
3722  0018 0002              	dc.w	2
3723  001a                   _EE_counter_ROM:
3724  001a ffff              	dc.w	-1
3725  001c 0001              	dc.w	1
3726  001e 0002              	dc.w	2
3727                         	switch	.data
3728  0096                   _EE_counter_RAM:
3729  0096 0000              	dc.w	0
3730  0098 ffff              	dc.w	-1
3731                         	switch	.const
3732  0020                   _EE_alarm_ROM:
3733  0020 0000              	dc.w	0
3734  0022 02                	dc.b	2
3735  0023 00000000          	dc.l	0
3736  0027 0001              	dc.w	1
3737  0029 00000000          	dc.l	0
3738  002d 0000              	dc.w	0
3739  002f 00                	dc.b	0
3740  0030 00000001          	dc.l	1
3741  0034 0000              	dc.w	0
3742  0036 00000000          	dc.l	0
3743  003a                   L1462_EE_oo_autostart_task_mode_OSDEFAULTAPPMODE:
3744  003a 00000000          	dc.l	0
3745  003e                   _EE_oo_autostart_task_data:
3746  003e 0001              	dc.w	1
3747  0040 003a              	dc.w	L1462_EE_oo_autostart_task_mode_OSDEFAULTAPPMODE
3748  0042                   L3462_EE_oo_autostart_alarm_mode_OSDEFAULTAPPMODE:
3749  0042 0000              	dc.w	0
3750  0044                   _EE_oo_autostart_alarm_data:
3751  0044 0001              	dc.w	1
3752  0046 0042              	dc.w	L3462_EE_oo_autostart_alarm_mode_OSDEFAULTAPPMODE
3753  0048                   _EE_oo_autostart_alarm_increment:
3754  0048 00fa              	dc.w	250
3755  004a 0000              	dc.w	0
3756  004c                   _EE_oo_autostart_alarm_cycle:
3757  004c 01f4              	dc.w	500
3758  004e 0000              	dc.w	0
4451                         	xdef	_EE_resource_locked
4452                         	xdef	_EE_resource_stack
4453                         	xdef	_EE_th_resource_last
4454                         	xref	f_FuncTask2
4455                         	xref	f_FuncTask1
4456                         	xdef	_EE_s12xs_IRQ_tos
4457                         	switch	.bss
4458  0000                   _EE_s12xs_stack_3:
4459  0000 0000000000000000  	ds.b	512
4460                         	xdef	_EE_s12xs_stack_3
4461  0200                   _EE_s12xs_stack_2:
4462  0200 0000000000000000  	ds.b	512
4463                         	xdef	_EE_s12xs_stack_2
4464  0400                   _EE_s12xs_stack_1:
4465  0400 0000000000000000  	ds.b	512
4466                         	xdef	_EE_s12xs_stack_1
4467                         	xdef	_wreg
4468                         	xref	_EE_pit0_initialized
4469  0600                   _EE_ApplicationMode:
4470  0600 0000              	ds.b	2
4471                         	xdef	_EE_ApplicationMode
4472                         	xref	_EE_oo_IRQ_disable_count
4473                         	xref	_EE_oo_ErrorHook_data
4474                         	xref	_EE_oo_ErrorHook_ServiceID
4475                         	xdef	_EE_oo_autostart_alarm_cycle
4476                         	xdef	_EE_oo_autostart_alarm_increment
4477                         	xdef	_EE_oo_autostart_alarm_data
4478                         	xdef	_EE_oo_autostart_task_data
4479  0602                   _EE_alarm_RAM:
4480  0602 0000000000000000  	ds.b	16
4481                         	xdef	_EE_alarm_RAM
4482                         	xdef	_EE_alarm_ROM
4483                         	xdef	_EE_counter_RAM
4484                         	xdef	_EE_counter_ROM
4485  0612                   _EE_resource_oldceiling:
4486  0612 0000              	ds.b	2
4487                         	xdef	_EE_resource_oldceiling
4488                         	xdef	_EE_resource_ceiling
4489                         	xdef	_EE_th_is_extended
4490                         	xdef	_EE_th_waswaiting
4491                         	xdef	_EE_th_event_waitmask
4492                         	xdef	_EE_th_event_active
4493                         	xdef	_EE_rq_free
4494  0614                   _EE_rq_pairs_tid:
4495  0614 0000000000000000  	ds.b	8
4496                         	xdef	_EE_rq_pairs_tid
4497                         	xdef	_EE_rq_pairs_next
4498                         	xdef	_EE_rq_queues_tail
4499                         	xdef	_EE_rq_queues_head
4500                         	xdef	_EE_rq_link
4501                         	xdef	_EE_rq_bitmask
4502                         	xdef	_EE_sys_ceiling
4503                         	xdef	_EE_stkfirst
4504                         	xdef	_EE_th_terminate_nextask
4505                         	xdef	_EE_th_rnact
4506                         	xdef	_EE_th_dispatch_prio
4507                         	xdef	_EE_th_ready_prio
4508                         	xdef	_EE_th_next
4509                         	xdef	_EE_th_status
4510                         	xref	_EE_buttons_initialized
4511                         	xref	f_EE_oo_thread_stub
4512                         	xdef	_EE_terminate_real_th_body
4513  061c                   _EE_terminate_data:
4514  061c 00000000          	ds.b	4
4515                         	xdef	_EE_terminate_data
4516                         	xdef	_EE_s12xs_active_tos
4517                         	xdef	_EE_s12xs_thread_tos
4518                         	xdef	_EE_s12xs_system_tos
4519                         	xdef	_EE_hal_thread_body
4540                         	end
