   1                         ; C Compiler for S12X [COSMIC Software].
   2                         ; Generator (Limited) V4.7.11.2 - 16 Mar 2009
   3                         ; Optimizer V4.6.16 - 02 Dec 2008
3604                         	switch	.data
3605  0000                   _EE_oo_IRQ_disable_count:
3606  0000 0000              	dc.w	0
3607  0002                   _EE_ErrorHook_nested_flag:
3608  0002 0000              	dc.w	0
3609  0004                   _EE_oo_no_preemption:
3610  0004 0000              	dc.w	0
3611                         .const:	section	.data
3612  0000                   _EE_rq_lookup:
3613  0000 ff                	dc.b	255
3614  0001 00                	dc.b	0
3615  0002 01                	dc.b	1
3616  0003 01                	dc.b	1
3617  0004 02                	dc.b	2
3618  0005 02                	dc.b	2
3619  0006 02                	dc.b	2
3620  0007 02                	dc.b	2
3621  0008 03                	dc.b	3
3622  0009 03                	dc.b	3
3623  000a 03                	dc.b	3
3624  000b 03                	dc.b	3
3625  000c 03                	dc.b	3
3626  000d 03                	dc.b	3
3627  000e 03                	dc.b	3
3628  000f 03                	dc.b	3
3629  0010 04                	dc.b	4
3630  0011 04                	dc.b	4
3631  0012 04                	dc.b	4
3632  0013 04                	dc.b	4
3633  0014 04                	dc.b	4
3634  0015 04                	dc.b	4
3635  0016 04                	dc.b	4
3636  0017 04                	dc.b	4
3637  0018 04                	dc.b	4
3638  0019 04                	dc.b	4
3639  001a 04                	dc.b	4
3640  001b 04                	dc.b	4
3641  001c 04                	dc.b	4
3642  001d 04                	dc.b	4
3643  001e 04                	dc.b	4
3644  001f 04                	dc.b	4
3645  0020 05                	dc.b	5
3646  0021 05                	dc.b	5
3647  0022 05                	dc.b	5
3648  0023 05                	dc.b	5
3649  0024 05                	dc.b	5
3650  0025 05                	dc.b	5
3651  0026 05                	dc.b	5
3652  0027 05                	dc.b	5
3653  0028 05                	dc.b	5
3654  0029 05                	dc.b	5
3655  002a 05                	dc.b	5
3656  002b 05                	dc.b	5
3657  002c 05                	dc.b	5
3658  002d 05                	dc.b	5
3659  002e 05                	dc.b	5
3660  002f 05                	dc.b	5
3661  0030 05                	dc.b	5
3662  0031 05                	dc.b	5
3663  0032 05                	dc.b	5
3664  0033 05                	dc.b	5
3665  0034 05                	dc.b	5
3666  0035 05                	dc.b	5
3667  0036 05                	dc.b	5
3668  0037 05                	dc.b	5
3669  0038 05                	dc.b	5
3670  0039 05                	dc.b	5
3671  003a 05                	dc.b	5
3672  003b 05                	dc.b	5
3673  003c 05                	dc.b	5
3674  003d 05                	dc.b	5
3675  003e 05                	dc.b	5
3676  003f 05                	dc.b	5
3677  0040 06                	dc.b	6
3678  0041 06                	dc.b	6
3679  0042 06                	dc.b	6
3680  0043 06                	dc.b	6
3681  0044 06                	dc.b	6
3682  0045 06                	dc.b	6
3683  0046 06                	dc.b	6
3684  0047 06                	dc.b	6
3685  0048 06                	dc.b	6
3686  0049 06                	dc.b	6
3687  004a 06                	dc.b	6
3688  004b 06                	dc.b	6
3689  004c 06                	dc.b	6
3690  004d 06                	dc.b	6
3691  004e 06                	dc.b	6
3692  004f 06                	dc.b	6
3693  0050 06                	dc.b	6
3694  0051 06                	dc.b	6
3695  0052 06                	dc.b	6
3696  0053 06                	dc.b	6
3697  0054 06                	dc.b	6
3698  0055 06                	dc.b	6
3699  0056 06                	dc.b	6
3700  0057 06                	dc.b	6
3701  0058 06                	dc.b	6
3702  0059 06                	dc.b	6
3703  005a 06                	dc.b	6
3704  005b 06                	dc.b	6
3705  005c 06                	dc.b	6
3706  005d 06                	dc.b	6
3707  005e 06                	dc.b	6
3708  005f 06                	dc.b	6
3709  0060 06                	dc.b	6
3710  0061 06                	dc.b	6
3711  0062 06                	dc.b	6
3712  0063 06                	dc.b	6
3713  0064 06                	dc.b	6
3714  0065 06                	dc.b	6
3715  0066 06                	dc.b	6
3716  0067 06                	dc.b	6
3717  0068 06                	dc.b	6
3718  0069 06                	dc.b	6
3719  006a 06                	dc.b	6
3720  006b 06                	dc.b	6
3721  006c 06                	dc.b	6
3722  006d 06                	dc.b	6
3723  006e 06                	dc.b	6
3724  006f 06                	dc.b	6
3725  0070 06                	dc.b	6
3726  0071 06                	dc.b	6
3727  0072 06                	dc.b	6
3728  0073 06                	dc.b	6
3729  0074 06                	dc.b	6
3730  0075 06                	dc.b	6
3731  0076 06                	dc.b	6
3732  0077 06                	dc.b	6
3733  0078 06                	dc.b	6
3734  0079 06                	dc.b	6
3735  007a 06                	dc.b	6
3736  007b 06                	dc.b	6
3737  007c 06                	dc.b	6
3738  007d 06                	dc.b	6
3739  007e 06                	dc.b	6
3740  007f 06                	dc.b	6
3741  0080 07                	dc.b	7
3742  0081 07                	dc.b	7
3743  0082 07                	dc.b	7
3744  0083 07                	dc.b	7
3745  0084 07                	dc.b	7
3746  0085 07                	dc.b	7
3747  0086 07                	dc.b	7
3748  0087 07                	dc.b	7
3749  0088 07                	dc.b	7
3750  0089 07                	dc.b	7
3751  008a 07                	dc.b	7
3752  008b 07                	dc.b	7
3753  008c 07                	dc.b	7
3754  008d 07                	dc.b	7
3755  008e 07                	dc.b	7
3756  008f 07                	dc.b	7
3757  0090 07                	dc.b	7
3758  0091 07                	dc.b	7
3759  0092 07                	dc.b	7
3760  0093 07                	dc.b	7
3761  0094 07                	dc.b	7
3762  0095 07                	dc.b	7
3763  0096 07                	dc.b	7
3764  0097 07                	dc.b	7
3765  0098 07                	dc.b	7
3766  0099 07                	dc.b	7
3767  009a 07                	dc.b	7
3768  009b 07                	dc.b	7
3769  009c 07                	dc.b	7
3770  009d 07                	dc.b	7
3771  009e 07                	dc.b	7
3772  009f 07                	dc.b	7
3773  00a0 07                	dc.b	7
3774  00a1 07                	dc.b	7
3775  00a2 07                	dc.b	7
3776  00a3 07                	dc.b	7
3777  00a4 07                	dc.b	7
3778  00a5 07                	dc.b	7
3779  00a6 07                	dc.b	7
3780  00a7 07                	dc.b	7
3781  00a8 07                	dc.b	7
3782  00a9 07                	dc.b	7
3783  00aa 07                	dc.b	7
3784  00ab 07                	dc.b	7
3785  00ac 07                	dc.b	7
3786  00ad 07                	dc.b	7
3787  00ae 07                	dc.b	7
3788  00af 07                	dc.b	7
3789  00b0 07                	dc.b	7
3790  00b1 07                	dc.b	7
3791  00b2 07                	dc.b	7
3792  00b3 07                	dc.b	7
3793  00b4 07                	dc.b	7
3794  00b5 07                	dc.b	7
3795  00b6 07                	dc.b	7
3796  00b7 07                	dc.b	7
3797  00b8 07                	dc.b	7
3798  00b9 07                	dc.b	7
3799  00ba 07                	dc.b	7
3800  00bb 07                	dc.b	7
3801  00bc 07                	dc.b	7
3802  00bd 07                	dc.b	7
3803  00be 07                	dc.b	7
3804  00bf 07                	dc.b	7
3805  00c0 07                	dc.b	7
3806  00c1 07                	dc.b	7
3807  00c2 07                	dc.b	7
3808  00c3 07                	dc.b	7
3809  00c4 07                	dc.b	7
3810  00c5 07                	dc.b	7
3811  00c6 07                	dc.b	7
3812  00c7 07                	dc.b	7
3813  00c8 07                	dc.b	7
3814  00c9 07                	dc.b	7
3815  00ca 07                	dc.b	7
3816  00cb 07                	dc.b	7
3817  00cc 07                	dc.b	7
3818  00cd 07                	dc.b	7
3819  00ce 07                	dc.b	7
3820  00cf 07                	dc.b	7
3821  00d0 07                	dc.b	7
3822  00d1 07                	dc.b	7
3823  00d2 07                	dc.b	7
3824  00d3 07                	dc.b	7
3825  00d4 07                	dc.b	7
3826  00d5 07                	dc.b	7
3827  00d6 07                	dc.b	7
3828  00d7 07                	dc.b	7
3829  00d8 07                	dc.b	7
3830  00d9 07                	dc.b	7
3831  00da 07                	dc.b	7
3832  00db 07                	dc.b	7
3833  00dc 07                	dc.b	7
3834  00dd 07                	dc.b	7
3835  00de 07                	dc.b	7
3836  00df 07                	dc.b	7
3837  00e0 07                	dc.b	7
3838  00e1 07                	dc.b	7
3839  00e2 07                	dc.b	7
3840  00e3 07                	dc.b	7
3841  00e4 07                	dc.b	7
3842  00e5 07                	dc.b	7
3843  00e6 07                	dc.b	7
3844  00e7 07                	dc.b	7
3845  00e8 07                	dc.b	7
3846  00e9 07                	dc.b	7
3847  00ea 07                	dc.b	7
3848  00eb 07                	dc.b	7
3849  00ec 07                	dc.b	7
3850  00ed 07                	dc.b	7
3851  00ee 07                	dc.b	7
3852  00ef 07                	dc.b	7
3853  00f0 07                	dc.b	7
3854  00f1 07                	dc.b	7
3855  00f2 07                	dc.b	7
3856  00f3 07                	dc.b	7
3857  00f4 07                	dc.b	7
3858  00f5 07                	dc.b	7
3859  00f6 07                	dc.b	7
3860  00f7 07                	dc.b	7
3861  00f8 07                	dc.b	7
3862  00f9 07                	dc.b	7
3863  00fa 07                	dc.b	7
3864  00fb 07                	dc.b	7
3865  00fc 07                	dc.b	7
3866  00fd 07                	dc.b	7
3867  00fe 07                	dc.b	7
3868  00ff 07                	dc.b	7
4457                         	xdef	_EE_rq_lookup
4458                         	xdef	_EE_oo_no_preemption
4459                         	xdef	_EE_ErrorHook_nested_flag
4460                         	xref	_EE_pit0_initialized
4461                         	xref	_EE_ApplicationMode
4462                         	xdef	_EE_oo_IRQ_disable_count
4463                         	switch	.bss
4464  0000                   _EE_oo_ErrorHook_data:
4465  0000 0000000000000000  	ds.b	9
4466                         	xdef	_EE_oo_ErrorHook_data
4467  0009                   _EE_oo_ErrorHook_ServiceID:
4468  0009 00                	ds.b	1
4469                         	xdef	_EE_oo_ErrorHook_ServiceID
4470                         	xref	_EE_stkfirst
4471                         	xref	_EE_th_next
4472                         	xref	_EE_th_status
4473                         	xref	_EE_buttons_initialized
4474                         	xref	f_EE_s12xs_terminate_task
4475                         	xref	f_EE_s12xs_terminate_savestk
4476                         	xref	_EE_IRQ_nesting_level
4477                         	xref	f_EE_s12xs_hal_stkchange
4478                         	xref	f_EE_s12xs_hal_ready2stacked
4479                         	xref	_EE_hal_endcycle_next_tos
4480                         	xref	_EE_hal_endcycle_next_thread
4481                         	xref	_EE_terminate_real_th_body
4482                         	xref	_EE_terminate_data
4483                         	xref	_EE_s12xs_thread_tos
4484                         	xref	_EE_hal_thread_body
4505                         	end
