   1                         ; C Compiler for S12X [COSMIC Software].
   2                         ; Generator (Limited) V4.7.11.2 - 16 Mar 2009
   3                         ; Optimizer V4.6.16 - 02 Dec 2008
3717                         ; 64 StatusType EE_oo_ChainTask(TaskType TaskID)
3717                         ; 65 {
3718                         .ftext:	section	.text
3719  0000                   f_EE_oo_ChainTask:
3721  0000 3b                	pshd	
3722  0001 34                	pshx	
3723  0002 1b98              	leas	-8,s
3724       00000008          OFST:	set	8
3727                         ; 62     return EE_stkfirst;  
3730  0004 1801860002        	movw	_EE_stkfirst+2,OFST-2,s
3731  0009 fe0000            	ldx	_EE_stkfirst
3732  000c 6e84              	stx	OFST-4,s
3734                         ; 63 }
3736                         ; 200   ASM_DIS_INT;
3739  000e 1410              	sei	
3741                         ; 168   if (TaskID != current &&
3741                         ; 169       EE_th_rnact[TaskID] == 0) {
3744  0010 ec88              	ldd	OFST+0,s
3745  0012 ac84              	cpd	OFST-4,s
3746  0014 2606              	bne	LC001
3747  0016 ec8a              	ldd	OFST+2,s
3748  0018 ac86              	cpd	OFST-2,s
3749  001a 2734              	beq	L5572
3750  001c                   LC001:
3752  001c ed8a              	ldy	OFST+2,s
3753  001e 1858              	lsly	
3754  0020 ecea0000          	ldd	_EE_th_rnact,y
3755  0024 262a              	bne	L5572
3756                         ; 175     if (!EE_ErrorHook_nested_flag) {  
3758  0026 fc0000            	ldd	_EE_ErrorHook_nested_flag
3759  0029 261f              	bne	L1672
3760                         ; 177       EE_oo_ErrorHook_ServiceID = OSServiceId_ChainTask;
3762  002b c603              	ldab	#3
3763  002d 7b0000            	stab	_EE_oo_ErrorHook_ServiceID
3764                         ; 178       EE_oo_ErrorHook_data.ChainTask_prm.TaskID = TaskID;
3766  0030 18058a0002        	movw	OFST+2,s,_EE_oo_ErrorHook_data+2
3767  0035 1805880000        	movw	OFST+0,s,_EE_oo_ErrorHook_data
3768                         ; 180       EE_ErrorHook_nested_flag = 1;
3770  003a cc0001            	ldd	#1
3771  003d 7c0000            	std	_EE_ErrorHook_nested_flag
3772                         ; 181       ErrorHook(E_OS_LIMIT);
3774  0040 c604              	ldab	#4
3775  0042 4a000000          	call	f_ErrorHook
3777                         ; 182       EE_ErrorHook_nested_flag = 0;
3779  0046 18790000          	clrw	_EE_ErrorHook_nested_flag
3780  004a                   L1672:
3781                         ; 191   ASM_EN_INT;
3784  004a 10ef              	cli	
3786                         ; 192     return E_OS_LIMIT;
3789  004c c604              	ldab	#4
3791  004e 2025              	bra	L01
3792  0050                   L5572:
3793                         ; 209       EE_th_rnact[TaskID]--;  
3795  0050 ed8a              	ldy	OFST+2,s
3796  0052 1858              	lsly	
3797  0054 1863ea0000        	decw	_EE_th_rnact,y
3798                         ; 211       EE_th_terminate_nextask[current] = TaskID;
3800  0059 cd0000            	ldy	#_EE_th_terminate_nextask
3801  005c ec86              	ldd	OFST-2,s
3802  005e 59                	lsld	
3803  005f 59                	lsld	
3804  0060 19ee              	leay	d,y
3805  0062 18028a42          	movw	OFST+2,s,2,y
3806  0066 18028840          	movw	OFST+0,s,0,y
3807                         ; 228   EE_s12xs_terminate_task(&EE_terminate_data[t]);
3810  006a ec86              	ldd	OFST-2,s
3811  006c 59                	lsld	
3812  006d c30000            	addd	#_EE_terminate_data
3813  0070 4a000000          	call	f_EE_s12xs_terminate_task
3815                         ; 222   return E_OK;
3818  0074 c7                	clrb	
3820  0075                   L01:
3822  0075 1b8c              	leas	12,s
3823  0077 0a                	rtc	
3835                         	xref	_EE_ErrorHook_nested_flag
3836                         	xref	_EE_pit0_initialized
3837                         	xref	_EE_ApplicationMode
3838                         	xref	_EE_oo_IRQ_disable_count
3839                         	xref	f_ErrorHook
3840                         	xdef	f_EE_oo_ChainTask
3841                         	xref	_EE_oo_ErrorHook_data
3842                         	xref	_EE_oo_ErrorHook_ServiceID
3843                         	xref	_EE_stkfirst
3844                         	xref	_EE_th_terminate_nextask
3845                         	xref	_EE_th_rnact
3846                         	xref	_EE_th_next
3847                         	xref	_EE_th_status
3848                         	xref	_EE_buttons_initialized
3849                         	xref	f_EE_s12xs_terminate_task
3850                         	xref	f_EE_s12xs_terminate_savestk
3851                         	xref	_EE_IRQ_nesting_level
3852                         	xref	f_EE_s12xs_hal_stkchange
3853                         	xref	f_EE_s12xs_hal_ready2stacked
3854                         	xref	_EE_hal_endcycle_next_tos
3855                         	xref	_EE_hal_endcycle_next_thread
3856                         	xref	_EE_terminate_real_th_body
3857                         	xref	_EE_terminate_data
3858                         	xref	_EE_s12xs_thread_tos
3859                         	xref	_EE_hal_thread_body
3879                         	end
