   1                         ; C Compiler for S12X [COSMIC Software].
   2                         ; Generator (Limited) V4.7.11.2 - 16 Mar 2009
   3                         ; Optimizer V4.6.16 - 02 Dec 2008
3775                         ; 60 StatusType EE_oo_ActivateTask(TaskType TaskID)
3775                         ; 61 {
3776                         .ftext:	section	.text
3777  0000                   f_EE_oo_ActivateTask:
3779  0000 3b                	pshd	
3780  0001 34                	pshx	
3781  0002 1b90              	leas	-16,s
3782       00000010          OFST:	set	16
3785                         ; 101   retvalue = _asm("tfr ccr,b\n");	// save CCR register (I bit)
3789  0004 b721              	tfr	ccr,b
3791                         ; 200   ASM_DIS_INT;
3794  0006 1410              	sei	
3796                         ; 104   return retvalue;
3799  0008 6c8c              	std	OFST-4,s
3801                         ; 105 }
3803                         ; 115   if (EE_th_rnact[TaskID] == 0) {
3805  000a edf012            	ldy	OFST+2,s
3806  000d 1858              	lsly	
3807  000f ecea0000          	ldd	_EE_th_rnact,y
3808  0013 2632              	bne	L7103
3809                         ; 121     if (!EE_ErrorHook_nested_flag) {
3811  0015 fc0000            	ldd	_EE_ErrorHook_nested_flag
3812  0018 261e              	bne	L1203
3813                         ; 123       EE_oo_ErrorHook_ServiceID = OSServiceId_ActivateTask;
3815  001a c601              	ldab	#1
3816  001c 7b0000            	stab	_EE_oo_ErrorHook_ServiceID
3817                         ; 124       EE_oo_ErrorHook_data.ActivateTask_prm.TaskID = TaskID;
3819  001f 1805f0120002      	movw	OFST+2,s,_EE_oo_ErrorHook_data+2
3820  0025 1805f0100000      	movw	OFST+0,s,_EE_oo_ErrorHook_data
3821                         ; 126       EE_ErrorHook_nested_flag = 1;
3823  002b 7c0000            	std	_EE_ErrorHook_nested_flag
3824                         ; 127       ErrorHook(E_OS_LIMIT);
3826  002e c604              	ldab	#4
3827  0030 4a000000          	call	f_ErrorHook
3829                         ; 128       EE_ErrorHook_nested_flag = 0;
3831  0034 18790000          	clrw	_EE_ErrorHook_nested_flag
3832  0038                   L1203:
3833                         ; 111   if(f & 0x10) 						// restore I bit
3836  0038 0f8d1004          	brclr	OFST-3,s,16,L3303
3837                         ; 200   ASM_DIS_INT;
3840  003c 1410              	sei	
3842  003e 2002              	bra	L7172
3843  0040                   L3303:
3844                         ; 191   ASM_EN_INT;
3847  0040 10ef              	cli	
3849  0042                   L7172:
3850                         ; 138     return E_OS_LIMIT;
3853  0042 c604              	ldab	#4
3855  0044 060118            	bra	L21
3856  0047                   L7103:
3857                         ; 140   EE_th_rnact[TaskID]--;
3859  0047 edf012            	ldy	OFST+2,s
3860  004a 1858              	lsly	
3861  004c 1863ea0000        	decw	_EE_th_rnact,y
3862                         ; 150   if (EE_th_status[TaskID] == SUSPENDED) {
3864  0051 ecea0000          	ldd	_EE_th_status,y
3865  0055 8c0003            	cpd	#3
3866  0058 260c              	bne	L7303
3867                         ; 151     EE_th_status[TaskID] = READY;
3869  005a cc0002            	ldd	#2
3870  005d 6cea0000          	std	_EE_th_status,y
3871                         ; 155     EE_th_event_active[TaskID] = 0;
3873  0061 1869ea0000        	clrw	_EE_th_event_active,y
3874  0066                   L7303:
3875                         ; 168   EE_rq_insert(TaskID);
3877  0066 ecf012            	ldd	OFST+2,s
3878  0069 eef010            	ldx	OFST+0,s
3879  006c 4a000000          	call	f_EE_rq_insert
3881                         ; 207   return EE_IRQ_nesting_level;
3884  0070 fc0000            	ldd	_EE_IRQ_nesting_level
3885  0073 6c8e              	std	OFST-2,s
3887                         ; 208 }
3889  0075 18260094          	bne	L1403
3891  0079 fc0000            	ldd	_EE_oo_no_preemption
3892  007c 1826008d          	bne	L1403
3893                         ; 178     tmp = EE_rq_queryfirst();
3895  0080 4a000000          	call	f_EE_rq_queryfirst
3897  0084 6c86              	std	OFST-10,s
3898  0086 6e84              	stx	OFST-12,s
3899                         ; 179     if (tmp != EE_NIL) {
3901  0088 04a505            	ibne	x,LC001
3902  008b 8cffff            	cpd	#-1
3903  008e 277d              	beq	L1403
3904  0090                   LC001:
3905                         ; 180       if (EE_sys_ceiling < EE_th_ready_prio[tmp]) {
3907  0090 59                	lsld	
3908  0091 b746              	tfr	d,y
3909  0093 ecea0000          	ldd	_EE_th_ready_prio,y
3910  0097 bc0000            	cpd	_EE_sys_ceiling
3911  009a 2371              	bls	L1403
3912                         ; 62     return EE_stkfirst;  
3915  009c fc0002            	ldd	_EE_stkfirst+2
3916  009f 6c8a              	std	OFST-6,s
3917  00a1 fe0000            	ldx	_EE_stkfirst
3918  00a4 6e88              	stx	OFST-8,s
3920                         ; 63 }
3922                         ; 184 	if (current != EE_NIL) { 
3924  00a6 04a503            	ibne	x,LC002
3925  00a9 04840b            	ibeq	d,L7403
3926  00ac                   LC002:
3927                         ; 191 	  EE_th_status[current] = READY;
3929  00ac cc0002            	ldd	#2
3930  00af ed8a              	ldy	OFST-6,s
3931  00b1 1858              	lsly	
3932  00b3 6cea0000          	std	_EE_th_status,y
3933  00b7                   L7403:
3934                         ; 195 	EE_th_status[tmp] = RUNNING;
3936  00b7 ed86              	ldy	OFST-10,s
3937  00b9 1858              	lsly	
3938  00bb 1869ea0000        	clrw	_EE_th_status,y
3939                         ; 197 	EE_sys_ceiling |= EE_th_dispatch_prio[tmp];
3941  00c0 edea0000          	ldy	_EE_th_dispatch_prio,y
3942  00c4 18fa0000          	ory	_EE_sys_ceiling
3943  00c8 7d0000            	sty	_EE_sys_ceiling
3944                         ; 204 	tmp = EE_rq2stk_exchange();
3946  00cb 4a000000          	call	f_EE_rq2stk_exchange
3948  00cf 6c86              	std	OFST-10,s
3949  00d1 6e84              	stx	OFST-12,s
3950                         ; 205 	if (EE_th_waswaiting[tmp]) {
3952  00d3 b746              	tfr	d,y
3953  00d5 1858              	lsly	
3954  00d7 18e7ea0000        	tstw	_EE_th_waswaiting,y
3955  00dc 270f              	beq	L1503
3956                         ; 206 	  EE_th_waswaiting[tmp] = 0;
3958  00de 1869ea0000        	clrw	_EE_th_waswaiting,y
3959                         ; 192     EE_s12xs_hal_stkchange(EE_s12xs_thread_tos[thread+1]);
3962  00e3 ecea0002          	ldd	_EE_s12xs_thread_tos+2,y
3963  00e7 4a000000          	call	f_EE_s12xs_hal_stkchange
3965  00eb 2020              	bra	L1403
3966  00ed                   L1503:
3967                         ; 194 }
3970  00ed b746              	tfr	d,y
3971  00ef 6d8a              	sty	OFST-6,s
3972  00f1 6e88              	stx	OFST-8,s
3973                         ; 141     EE_s12xs_hal_ready2stacked(EE_hal_thread_body[thread],
3973                         ; 142 			         EE_s12xs_thread_tos[thread+1]);
3975  00f3 1858              	lsly	
3976  00f5 ecea0002          	ldd	_EE_s12xs_thread_tos+2,y
3977  00f9 3b                	pshd	
3978  00fa cd0000            	ldy	#_EE_hal_thread_body
3979  00fd ec8c              	ldd	OFST-4,s
3980  00ff 59                	lsld	
3981  0100 59                	lsld	
3982  0101 19ee              	leay	d,y
3983  0103 ec42              	ldd	2,y
3984  0105 ee40              	ldx	0,y
3985  0107 4a000000          	call	f_EE_s12xs_hal_ready2stacked
3987  010b 1b82              	leas	2,s
3988  010d                   L1403:
3989                         ; 111   if(f & 0x10) 						// restore I bit
3992  010d 0f8d1004          	brclr	OFST-3,s,16,L5603
3993                         ; 200   ASM_DIS_INT;
3996  0111 1410              	sei	
3998  0113 2002              	bra	L1472
3999  0115                   L5603:
4000                         ; 191   ASM_EN_INT;
4003  0115 10ef              	cli	
4005  0117                   L1472:
4006                         ; 232   return E_OK;
4009  0117 c7                	clrb	
4011  0118                   L21:
4013  0118 1bf014            	leas	20,s
4014  011b 0a                	rtc	
4026                         	xref	f_EE_rq2stk_exchange
4027                         	xref	f_EE_rq_insert
4028                         	xref	f_EE_rq_queryfirst
4029                         	xref	_EE_oo_no_preemption
4030                         	xref	_EE_ErrorHook_nested_flag
4031                         	xref	_EE_pit0_initialized
4032                         	xref	_EE_ApplicationMode
4033                         	xref	_EE_oo_IRQ_disable_count
4034                         	xref	f_ErrorHook
4035                         	xdef	f_EE_oo_ActivateTask
4036                         	xref	_EE_oo_ErrorHook_data
4037                         	xref	_EE_oo_ErrorHook_ServiceID
4038                         	xref	_EE_th_waswaiting
4039                         	xref	_EE_th_event_active
4040                         	xref	_EE_sys_ceiling
4041                         	xref	_EE_stkfirst
4042                         	xref	_EE_th_rnact
4043                         	xref	_EE_th_dispatch_prio
4044                         	xref	_EE_th_ready_prio
4045                         	xref	_EE_th_next
4046                         	xref	_EE_th_status
4047                         	xref	_EE_buttons_initialized
4048                         	xref	f_EE_s12xs_terminate_task
4049                         	xref	f_EE_s12xs_terminate_savestk
4050                         	xref	_EE_IRQ_nesting_level
4051                         	xref	f_EE_s12xs_hal_stkchange
4052                         	xref	f_EE_s12xs_hal_ready2stacked
4053                         	xref	_EE_hal_endcycle_next_tos
4054                         	xref	_EE_hal_endcycle_next_thread
4055                         	xref	_EE_terminate_real_th_body
4056                         	xref	_EE_terminate_data
4057                         	xref	_EE_s12xs_thread_tos
4058                         	xref	_EE_hal_thread_body
4078                         	end
