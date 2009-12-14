   1                         ; C Compiler for S12X [COSMIC Software].
   2                         ; Generator (Limited) V4.7.11.2 - 16 Mar 2009
   3                         ; Optimizer V4.6.16 - 02 Dec 2008
3684                         ; 16 ISR2(PIT0_Interrupt)
3685                         	switch	.text
3686  0000                   _PIT0_Interrupt:
3691                         ; 83   EE_IRQ_nesting_level++;
3694  0000 18720000          	incw	_EE_IRQ_nesting_level
3695                         ; 191   ASM_EN_INT;
3698  0004 10ef              	cli	
3700                         ; 16 ISR2(PIT0_Interrupt)
3703  0006 4a000000          	call	f_ISR2_PIT0_Interrupt
3705                         ; 200   ASM_DIS_INT;
3708  000a 1410              	sei	
3710                         ; 110   EE_IRQ_nesting_level--;
3713  000c 18730000          	decw	_EE_IRQ_nesting_level
3714                         ; 112   if (EE_IRQ_nesting_level!=0) 
3716  0010 263b              	bne	L5562
3717                         ; 115 	return;
3719                         ; 133   EE_IRQ_end_instance();
3721  0012 4a000000          	call	f_EE_IRQ_end_instance
3723                         ; 135   if (EE_hal_endcycle_next_thread) {
3725  0016 fc0000            	ldd	_EE_hal_endcycle_next_thread
3726  0019 2605              	bne	LC001
3727  001b fc0002            	ldd	_EE_hal_endcycle_next_thread+2
3728  001e 2715              	beq	L7072
3729  0020                   LC001:
3730                         ; 137     _asm("tfr a,ccrh\n", 0x0000);		//_asm("BCLR.B 0x0042, #0x7");
3732  0020 87                	clra	
3734  0021 b70a              	tfr	a,ccrh
3736                         ; 144     EE_s12xs_hal_ready2stacked(EE_hal_endcycle_next_thread, EE_hal_endcycle_next_tos);
3738  0023 fc0000            	ldd	_EE_hal_endcycle_next_tos
3739  0026 3b                	pshd	
3740  0027 fc0002            	ldd	_EE_hal_endcycle_next_thread+2
3741  002a fe0000            	ldx	_EE_hal_endcycle_next_thread
3742  002d 4a000000          	call	f_EE_s12xs_hal_ready2stacked
3744  0031 1b82              	leas	2,s
3746  0033 2012              	bra	L1172
3747  0035                   L7072:
3748                         ; 149     if (EE_hal_endcycle_next_tos != EE_s12xs_active_tos) {
3750  0035 fc0000            	ldd	_EE_hal_endcycle_next_tos
3751  0038 bc0000            	cpd	_EE_s12xs_active_tos
3752  003b 270a              	beq	L1172
3753                         ; 151       _asm("tfr a,ccrh\n", 0x0000);	//_asm("BCLR.B 0x0042, #0x7");
3755  003d 87                	clra	
3757  003e b70a              	tfr	a,ccrh
3759                         ; 154 		EE_s12xs_hal_stkchange(EE_hal_endcycle_next_tos);
3761  0040 fc0000            	ldd	_EE_hal_endcycle_next_tos
3762  0043 4a000000          	call	f_EE_s12xs_hal_stkchange
3764  0047                   L1172:
3765                         ; 162   _asm("tfr a,ccrh\n", 0x0600);	//_asm("BSET.B 0x0042, #0x7");
3767  0047 8606              	ldaa	#6
3769  0049 b70a              	tfr	a,ccrh
3771                         ; 191   ASM_EN_INT;
3774  004b 10ef              	cli	
3776  004d                   L5562:
3777                         ; 16 ISR2(PIT0_Interrupt)
3781  004d 0b                	rti	
3807                         ; 16 ISR2(PIT0_Interrupt)
3807                         ; 17 {
3808                         .ftext:	section	.text
3809  0000                   f_ISR2_PIT0_Interrupt:
3813                         ; 56 	PITTF         = 0x01;        
3816  0000 c601              	ldab	#1
3817  0002 7b0345            	stab	_PITTF
3818                         ; 20 	CounterTick(Counter1);
3821  0005 87                	clra	
3822  0006 c7                	clrb	
3823  0007 4a000000          	call	f_EE_oo_counter_tick
3825                         ; 21 }
3828  000b 0a                	rtc	
3866                         ; 26 ISR2(Buttons_Interrupt)
3867                         	switch	.text
3868  004e                   _Buttons_Interrupt:
3873                         ; 83   EE_IRQ_nesting_level++;
3876  004e 18720000          	incw	_EE_IRQ_nesting_level
3877                         ; 191   ASM_EN_INT;
3880  0052 10ef              	cli	
3882                         ; 26 ISR2(Buttons_Interrupt)
3885  0054 4a000c0c          	call	f_ISR2_Buttons_Interrupt
3887                         ; 200   ASM_DIS_INT;
3890  0058 1410              	sei	
3892                         ; 110   EE_IRQ_nesting_level--;
3895  005a 18730000          	decw	_EE_IRQ_nesting_level
3896                         ; 112   if (EE_IRQ_nesting_level!=0) 
3898  005e 263b              	bne	L3472
3899                         ; 115 	return;
3901                         ; 133   EE_IRQ_end_instance();
3903  0060 4a000000          	call	f_EE_IRQ_end_instance
3905                         ; 135   if (EE_hal_endcycle_next_thread) {
3907  0064 fc0000            	ldd	_EE_hal_endcycle_next_thread
3908  0067 2605              	bne	LC002
3909  0069 fc0002            	ldd	_EE_hal_endcycle_next_thread+2
3910  006c 2715              	beq	L7672
3911  006e                   LC002:
3912                         ; 137     _asm("tfr a,ccrh\n", 0x0000);		//_asm("BCLR.B 0x0042, #0x7");
3914  006e 87                	clra	
3916  006f b70a              	tfr	a,ccrh
3918                         ; 144     EE_s12xs_hal_ready2stacked(EE_hal_endcycle_next_thread, EE_hal_endcycle_next_tos);
3920  0071 fc0000            	ldd	_EE_hal_endcycle_next_tos
3921  0074 3b                	pshd	
3922  0075 fc0002            	ldd	_EE_hal_endcycle_next_thread+2
3923  0078 fe0000            	ldx	_EE_hal_endcycle_next_thread
3924  007b 4a000000          	call	f_EE_s12xs_hal_ready2stacked
3926  007f 1b82              	leas	2,s
3928  0081 2012              	bra	L1772
3929  0083                   L7672:
3930                         ; 149     if (EE_hal_endcycle_next_tos != EE_s12xs_active_tos) {
3932  0083 fc0000            	ldd	_EE_hal_endcycle_next_tos
3933  0086 bc0000            	cpd	_EE_s12xs_active_tos
3934  0089 270a              	beq	L1772
3935                         ; 151       _asm("tfr a,ccrh\n", 0x0000);	//_asm("BCLR.B 0x0042, #0x7");
3937  008b 87                	clra	
3939  008c b70a              	tfr	a,ccrh
3941                         ; 154 		EE_s12xs_hal_stkchange(EE_hal_endcycle_next_tos);
3943  008e fc0000            	ldd	_EE_hal_endcycle_next_tos
3944  0091 4a000000          	call	f_EE_s12xs_hal_stkchange
3946  0095                   L1772:
3947                         ; 162   _asm("tfr a,ccrh\n", 0x0600);	//_asm("BSET.B 0x0042, #0x7");
3949  0095 8606              	ldaa	#6
3951  0097 b70a              	tfr	a,ccrh
3953                         ; 191   ASM_EN_INT;
3956  0099 10ef              	cli	
3958  009b                   L3472:
3959                         ; 26 ISR2(Buttons_Interrupt)
3963  009b 0b                	rti	
4045                         ; 26 ISR2(Buttons_Interrupt)
4045                         ; 27 {
4046                         	switch	.ftext
4047  000c                   f_ISR2_Buttons_Interrupt:
4049  000c 3b                	pshd	
4050       00000002          OFST:	set	2
4053                         ; 153 		x = (EE_UINT8)((EE_UINT8)1<<bx);
4056                         ; 154 	x = (EE_UINT8)(~x);
4058                         ; 155 	PIEP &= x;
4060  000d 1d025e01          	bclr	_PIEP,1
4061                         ; 29 	button_fired++;
4064  0011 18720000          	incw	_button_fired
4065                         ; 31 	SetRelAlarm(AlarmTask2, 1000, 0);
4067  0015 87                	clra	
4068  0016 c7                	clrb	
4069  0017 3b                	pshd	
4070  0018 cc03e8            	ldd	#1000
4071  001b 3b                	pshd	
4072  001c cc0001            	ldd	#1
4073  001f 4a000000          	call	f_EE_oo_SetRelAlarm
4075  0023 1b84              	leas	4,s
4076                         ; 33     SetEvent(Task1, ButtonEvent);
4078  0025 cc0002            	ldd	#2
4079  0028 3b                	pshd	
4080  0029 c7                	clrb	
4081  002a 1887              	clrx	
4082  002c 4a000000          	call	f_EE_oo_SetEvent
4084  0030 1b82              	leas	2,s
4085                         ; 34 	mydelay((long int)1000);
4087  0032 ce0000            	ldx	#0
4088  0035 cc03e8            	ldd	#1000
4089  0038 4a000000          	call	f_mydelay
4091                         ; 161 		x = (EE_UINT8)((EE_UINT8)1<<bx);
4094                         ; 162 	PIFP |= x;
4096  003c 1c025f01          	bset	_PIFP,1
4097                         ; 163   	PIEP |= x;
4099  0040 1c025e01          	bset	_PIEP,1
4100                         ; 169 		x = (EE_UINT8)((EE_UINT8)1<<bx);
4104                         ; 170 	PIFP |= x;
4106  0044 1c025f01          	bset	_PIFP,1
4107                         ; 37 }
4111  0048 31                	puly	
4112  0049 0a                	rtc	
4135                         ; 44 static @interrupt @near void dummit(void)
4135                         ; 45 	{
4136                         	switch	.text
4137  009c                   L3403_dummit:
4142                         ; 46 		dummit_counter++;
4144  009c 18720000          	incw	_dummit_counter
4145                         ; 48 	}
4148  00a0 0b                	rti	
4150                         .vector:	section	.data
4151  0000                   __vectab:
4153  0000 009c              	dc.w	L3403_dummit
4155  0002 009c              	dc.w	L3403_dummit
4157  0004 009c              	dc.w	L3403_dummit
4159  0006 009c              	dc.w	L3403_dummit
4161  0008 009c              	dc.w	L3403_dummit
4163  000a 009c              	dc.w	L3403_dummit
4165  000c 009c              	dc.w	L3403_dummit
4167  000e 009c              	dc.w	L3403_dummit
4169  0010 009c              	dc.w	L3403_dummit
4171  0012 009c              	dc.w	L3403_dummit
4173  0014 009c              	dc.w	L3403_dummit
4175  0016 009c              	dc.w	L3403_dummit
4177  0018 009c              	dc.w	L3403_dummit
4179  001a 009c              	dc.w	L3403_dummit
4181  001c 009c              	dc.w	L3403_dummit
4183  001e 009c              	dc.w	L3403_dummit
4185  0020 009c              	dc.w	L3403_dummit
4187  0022 009c              	dc.w	L3403_dummit
4189  0024 009c              	dc.w	L3403_dummit
4191  0026 009c              	dc.w	L3403_dummit
4193  0028 009c              	dc.w	L3403_dummit
4195  002a 009c              	dc.w	L3403_dummit
4197  002c 009c              	dc.w	L3403_dummit
4199  002e 009c              	dc.w	L3403_dummit
4201  0030 009c              	dc.w	L3403_dummit
4203  0032 009c              	dc.w	L3403_dummit
4205  0034 009c              	dc.w	L3403_dummit
4207  0036 009c              	dc.w	L3403_dummit
4209  0038 009c              	dc.w	L3403_dummit
4211  003a 009c              	dc.w	L3403_dummit
4213  003c 009c              	dc.w	L3403_dummit
4215  003e 009c              	dc.w	L3403_dummit
4217  0040 009c              	dc.w	L3403_dummit
4219  0042 009c              	dc.w	L3403_dummit
4221  0044 009c              	dc.w	L3403_dummit
4223  0046 009c              	dc.w	L3403_dummit
4225  0048 009c              	dc.w	L3403_dummit
4227  004a 009c              	dc.w	L3403_dummit
4229  004c 009c              	dc.w	L3403_dummit
4231  004e 009c              	dc.w	L3403_dummit
4233  0050 009c              	dc.w	L3403_dummit
4235  0052 009c              	dc.w	L3403_dummit
4237  0054 009c              	dc.w	L3403_dummit
4239  0056 009c              	dc.w	L3403_dummit
4241  0058 009c              	dc.w	L3403_dummit
4243  005a 009c              	dc.w	L3403_dummit
4245  005c 009c              	dc.w	L3403_dummit
4247  005e 009c              	dc.w	L3403_dummit
4249  0060 009c              	dc.w	L3403_dummit
4251  0062 009c              	dc.w	L3403_dummit
4253  0064 009c              	dc.w	L3403_dummit
4255  0066 009c              	dc.w	L3403_dummit
4257  0068 009c              	dc.w	L3403_dummit
4259  006a 0000              	dc.w	_PIT0_Interrupt
4261  006c 009c              	dc.w	L3403_dummit
4263  006e 009c              	dc.w	L3403_dummit
4265  0070 009c              	dc.w	L3403_dummit
4267  0072 009c              	dc.w	L3403_dummit
4269  0074 009c              	dc.w	L3403_dummit
4271  0076 009c              	dc.w	L3403_dummit
4273  0078 009c              	dc.w	L3403_dummit
4275  007a 009c              	dc.w	L3403_dummit
4277  007c 009c              	dc.w	L3403_dummit
4279  007e 004e              	dc.w	_Buttons_Interrupt
4281  0080 009c              	dc.w	L3403_dummit
4283  0082 009c              	dc.w	L3403_dummit
4285  0084 009c              	dc.w	L3403_dummit
4287  0086 009c              	dc.w	L3403_dummit
4289  0088 009c              	dc.w	L3403_dummit
4291  008a 009c              	dc.w	L3403_dummit
4293  008c 009c              	dc.w	L3403_dummit
4295  008e 009c              	dc.w	L3403_dummit
4297  0090 009c              	dc.w	L3403_dummit
4299  0092 009c              	dc.w	L3403_dummit
4301  0094 009c              	dc.w	L3403_dummit
4303  0096 009c              	dc.w	L3403_dummit
4305  0098 009c              	dc.w	L3403_dummit
4307  009a 009c              	dc.w	L3403_dummit
4309  009c 009c              	dc.w	L3403_dummit
4311  009e 009c              	dc.w	L3403_dummit
4313  00a0 009c              	dc.w	L3403_dummit
4315  00a2 009c              	dc.w	L3403_dummit
4317  00a4 009c              	dc.w	L3403_dummit
4319  00a6 009c              	dc.w	L3403_dummit
4321  00a8 009c              	dc.w	L3403_dummit
4323  00aa 009c              	dc.w	L3403_dummit
4325  00ac 009c              	dc.w	L3403_dummit
4327  00ae 009c              	dc.w	L3403_dummit
4329  00b0 009c              	dc.w	L3403_dummit
4331  00b2 009c              	dc.w	L3403_dummit
4333  00b4 009c              	dc.w	L3403_dummit
4335  00b6 009c              	dc.w	L3403_dummit
4337  00b8 009c              	dc.w	L3403_dummit
4339  00ba 009c              	dc.w	L3403_dummit
4341  00bc 009c              	dc.w	L3403_dummit
4343  00be 009c              	dc.w	L3403_dummit
4345  00c0 009c              	dc.w	L3403_dummit
4347  00c2 009c              	dc.w	L3403_dummit
4349  00c4 009c              	dc.w	L3403_dummit
4351  00c6 009c              	dc.w	L3403_dummit
4353  00c8 009c              	dc.w	L3403_dummit
4355  00ca 009c              	dc.w	L3403_dummit
4357  00cc 009c              	dc.w	L3403_dummit
4359  00ce 009c              	dc.w	L3403_dummit
4361  00d0 009c              	dc.w	L3403_dummit
4363  00d2 009c              	dc.w	L3403_dummit
4365  00d4 009c              	dc.w	L3403_dummit
4367  00d6 009c              	dc.w	L3403_dummit
4369  00d8 009c              	dc.w	L3403_dummit
4371  00da 009c              	dc.w	L3403_dummit
4373  00dc 009c              	dc.w	L3403_dummit
4375  00de 009c              	dc.w	L3403_dummit
4377  00e0 009c              	dc.w	L3403_dummit
4379  00e2 009c              	dc.w	L3403_dummit
4381  00e4 009c              	dc.w	L3403_dummit
4383  00e6 009c              	dc.w	L3403_dummit
4385  00e8 009c              	dc.w	L3403_dummit
4387  00ea 009c              	dc.w	L3403_dummit
4389  00ec 009c              	dc.w	L3403_dummit
4391  00ee 0000              	dc.w	__stext
4416                         	xdef	__vectab
4417                         	xref	__stext
4418                         	xdef	_Buttons_Interrupt
4419                         	xdef	f_ISR2_Buttons_Interrupt
4420                         	xdef	_PIT0_Interrupt
4421                         	xdef	f_ISR2_PIT0_Interrupt
4422                         	xref	_dummit_counter
4423                         	xref	_button_fired
4424                         	xref	f_mydelay
4425                         	xref	f_EE_s12xs_hal_stkchange
4426                         	xref	f_EE_s12xs_hal_ready2stacked
4427                         	xref	f_EE_IRQ_end_instance
4428                         	xref	_EE_IRQ_nesting_level
4429                         	xref	_EE_hal_endcycle_next_tos
4430                         	xref	_EE_hal_endcycle_next_thread
4431                         	xref	_EE_pit0_initialized
4432                         	xref	_EE_ApplicationMode
4433                         	xref	_EE_oo_IRQ_disable_count
4434                         	xref	f_EE_oo_SetRelAlarm
4435                         	xref	f_EE_oo_counter_tick
4436                         	xref	f_EE_oo_SetEvent
4437                         	xref	_EE_oo_ErrorHook_data
4438                         	xref	_EE_oo_ErrorHook_ServiceID
4439                         	xref	_EE_stkfirst
4440                         	xref	_EE_th_status
4441                         	xref	_EE_buttons_initialized
4442                         	xref	_EE_s12xs_active_tos
4462                         	end
