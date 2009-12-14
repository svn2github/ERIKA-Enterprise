   1                         ; C Compiler for S12X [COSMIC Software].
   2                         ; Generator (Limited) V4.7.11.2 - 16 Mar 2009
   3                         ; Optimizer V4.6.16 - 02 Dec 2008
3716                         ; 49 void EE_oo_alarm_insert(AlarmType AlarmID, TickType increment)
3716                         ; 50 {
3717                         .ftext:	section	.text
3718  0000                   f_EE_oo_alarm_insert:
3720  0000 3b                	pshd	
3721  0001 1b9c              	leas	-4,s
3722       00000004          OFST:	set	4
3725                         ; 58   current = EE_counter_RAM[EE_alarm_ROM[AlarmID].c].first;
3727  0003 cd000d            	ldy	#13
3728  0006 13                	emul	
3729  0007 b746              	tfr	d,y
3730  0009 eeea0000          	ldx	_EE_alarm_ROM,y
3731  000d 1848              	lslx	
3732  000f 1848              	lslx	
3733  0011 ece20002          	ldd	_EE_counter_RAM+2,x
3734  0015 6c80              	std	OFST-4,s
3735                         ; 60   if (current == -1) {
3737  0017 8cffff            	cpd	#-1
3738  001a 2619              	bne	L1372
3739                         ; 62     EE_counter_RAM[EE_alarm_ROM[AlarmID].c].first = AlarmID;
3741  001c ec84              	ldd	OFST+0,s
3742  001e cd000d            	ldy	#13
3743  0021 13                	emul	
3744  0022 b746              	tfr	d,y
3745  0024 eeea0000          	ldx	_EE_alarm_ROM,y
3746  0028 1848              	lslx	
3747  002a 1848              	lslx	
3748  002c 180284e20002      	movw	OFST+0,s,_EE_counter_RAM+2,x
3750  0032 0600c4            	bra	L3372
3751  0035                   L1372:
3752                         ; 63   } else if (EE_alarm_RAM[current].delta > increment) {
3754  0035 59                	lsld	
3755  0036 59                	lsld	
3756  0037 59                	lsld	
3757  0038 b746              	tfr	d,y
3758  003a ecea0004          	ldd	_EE_alarm_RAM+4,y
3759  003e ac89              	cpd	OFST+5,s
3760  0040 232a              	bls	L1472
3761                         ; 64     EE_counter_RAM[EE_alarm_ROM[AlarmID].c].first = AlarmID;
3763  0042 ec84              	ldd	OFST+0,s
3764  0044 cd000d            	ldy	#13
3765  0047 13                	emul	
3766  0048 b746              	tfr	d,y
3767  004a eeea0000          	ldx	_EE_alarm_ROM,y
3768  004e 1848              	lslx	
3769  0050 1848              	lslx	
3770  0052 180284e20002      	movw	OFST+0,s,_EE_counter_RAM+2,x
3771                         ; 65     EE_alarm_RAM[current].delta -= increment;
3773  0058 ed80              	ldy	OFST-4,s
3774  005a 1858              	lsly	
3775  005c 1858              	lsly	
3776  005e 1858              	lsly	
3777  0060 ecea0004          	ldd	_EE_alarm_RAM+4,y
3778  0064 a389              	subd	OFST+5,s
3779  0066 6cea0004          	std	_EE_alarm_RAM+4,y
3781  006a 2058              	bra	L3372
3782  006c                   L1472:
3783                         ; 72       increment -= EE_alarm_RAM[current].delta;
3785  006c ec89              	ldd	OFST+5,s
3786  006e ed80              	ldy	OFST-4,s
3787  0070 1858              	lsly	
3788  0072 1858              	lsly	
3789  0074 1858              	lsly	
3790  0076 a3ea0004          	subd	_EE_alarm_RAM+4,y
3791  007a 6c89              	std	OFST+5,s
3792                         ; 73       previous = current;
3794  007c ed80              	ldy	OFST-4,s
3795  007e 6d82              	sty	OFST-2,s
3796                         ; 74       current = EE_alarm_RAM[current].next;
3798  0080 1858              	lsly	
3799  0082 1858              	lsly	
3800  0084 1858              	lsly	
3801  0086 edea0006          	ldy	_EE_alarm_RAM+6,y
3802  008a 6d80              	sty	OFST-4,s
3803                         ; 75     } while(current != -1 && EE_alarm_RAM[current].delta <= increment);
3805  008c 8dffff            	cpy	#-1
3806  008f 2710              	beq	L7472
3808  0091 1858              	lsly	
3809  0093 1858              	lsly	
3810  0095 1858              	lsly	
3811  0097 ecea0004          	ldd	_EE_alarm_RAM+4,y
3812  009b ac89              	cpd	OFST+5,s
3813  009d 23cd              	bls	L1472
3814  009f ed80              	ldy	OFST-4,s
3815  00a1                   L7472:
3816                         ; 78     if (current != -1)
3818  00a1 8dffff            	cpy	#-1
3819  00a4 2710              	beq	L1572
3820                         ; 79       EE_alarm_RAM[current].delta -= increment;
3822  00a6 1858              	lsly	
3823  00a8 1858              	lsly	
3824  00aa 1858              	lsly	
3825  00ac ecea0004          	ldd	_EE_alarm_RAM+4,y
3826  00b0 a389              	subd	OFST+5,s
3827  00b2 6cea0004          	std	_EE_alarm_RAM+4,y
3828  00b6                   L1572:
3829                         ; 80     EE_alarm_RAM[previous].next = AlarmID;
3831  00b6 ed82              	ldy	OFST-2,s
3832  00b8 1858              	lsly	
3833  00ba 1858              	lsly	
3834  00bc 1858              	lsly	
3835  00be 180284ea0006      	movw	OFST+0,s,_EE_alarm_RAM+6,y
3836  00c4                   L3372:
3837                         ; 83   EE_alarm_RAM[AlarmID].delta = increment;
3839  00c4 ed84              	ldy	OFST+0,s
3840  00c6 1858              	lsly	
3841  00c8 1858              	lsly	
3842  00ca 1858              	lsly	
3843  00cc 180289ea0004      	movw	OFST+5,s,_EE_alarm_RAM+4,y
3844                         ; 84   EE_alarm_RAM[AlarmID].next = current;
3846  00d2 ed84              	ldy	OFST+0,s
3847  00d4 1858              	lsly	
3848  00d6 1858              	lsly	
3849  00d8 1858              	lsly	
3850  00da 180280ea0006      	movw	OFST-4,s,_EE_alarm_RAM+6,y
3851                         ; 85 }
3854  00e0 1b86              	leas	6,s
3855  00e2 0a                	rtc	
3951                         ; 88 void EE_oo_counter_tick(CounterType c)
3951                         ; 89 {
3952                         	switch	.ftext
3953  00e3                   f_EE_oo_counter_tick:
3955  00e3 3b                	pshd	
3956  00e4 1b94              	leas	-12,s
3957       0000000c          OFST:	set	12
3960                         ; 101   retvalue = _asm("tfr ccr,b\n");	// save CCR register (I bit)
3964  00e6 b721              	tfr	ccr,b
3966                         ; 200   ASM_DIS_INT;
3969  00e8 1410              	sei	
3971                         ; 104   return retvalue;
3974  00ea 6c8a              	std	OFST-2,s
3976                         ; 105 }
3978                         ; 104   EE_counter_RAM[c].value++;
3980  00ec ed8c              	ldy	OFST+0,s
3981  00ee 1858              	lsly	
3982  00f0 1858              	lsly	
3983  00f2 1862ea0000        	incw	_EE_counter_RAM,y
3984                         ; 107   if (EE_counter_RAM[c].first != -1) {
3986  00f7 ed8c              	ldy	OFST+0,s
3987  00f9 1858              	lsly	
3988  00fb 1858              	lsly	
3989  00fd ecea0002          	ldd	_EE_counter_RAM+2,y
3990  0101 8cffff            	cpd	#-1
3991  0104 182701c5          	beq	L7303
3992                         ; 109     EE_alarm_RAM[EE_counter_RAM[c].first].delta--;
3994  0108 ed8c              	ldy	OFST+0,s
3995  010a 1858              	lsly	
3996  010c 1858              	lsly	
3997  010e eeea0002          	ldx	_EE_counter_RAM+2,y
3998  0112 1848              	lslx	
3999  0114 1848              	lslx	
4000  0116 1848              	lslx	
4001  0118 1863e20004        	decw	_EE_alarm_RAM+4,x
4002                         ; 112     current = EE_counter_RAM[c].first;
4004  011d ed8c              	ldy	OFST+0,s
4005  011f 1858              	lsly	
4006  0121 1858              	lsly	
4007  0123 ecea0002          	ldd	_EE_counter_RAM+2,y
4008  0127 6c82              	std	OFST-10,s
4010  0129 0602bd            	bra	L3403
4011  012c                   L1403:
4012                         ; 115       switch (EE_alarm_ROM[current].action) {
4014  012c cd000d            	ldy	#13
4015  012f 13                	emul	
4016  0130 b746              	tfr	d,y
4017  0132 e6ea0002          	ldab	_EE_alarm_ROM+2,y
4019  0136 270b              	beq	L1672
4020  0138 53                	decb	
4021  0139 1827011a          	beq	L5672
4022  013d 53                	decb	
4023  013e 2776              	beq	L3672
4024  0140 060264            	bra	L1503
4025  0143                   L1672:
4026                         ; 119       case  EE_ALARM_ACTION_TASK:
4026                         ; 120 	/* activate the task; NOTE: no preemption at all... 
4026                         ; 121 	   This code was directly copied from ActivateTask */
4026                         ; 122 
4026                         ; 123 	TaskID = EE_alarm_ROM[current].TaskID;
4028  0143 ce0003            	ldx	#_EE_alarm_ROM+3
4029  0146 ec82              	ldd	OFST-10,s
4030  0148 cd000d            	ldy	#13
4031  014b 13                	emul	
4032  014c 19e6              	leay	d,x
4033  014e 18024286          	movw	2,y,OFST-6,s
4034  0152 18024084          	movw	0,y,OFST-8,s
4035                         ; 162 	if (EE_th_rnact[TaskID] == 0) {
4037  0156 ed86              	ldy	OFST-6,s
4038  0158 1858              	lsly	
4039  015a ecea0000          	ldd	_EE_th_rnact,y
4040  015e 2633              	bne	L3503
4041                         ; 168 	  if (!EE_ErrorHook_nested_flag) {
4043  0160 fc0000            	ldd	_EE_ErrorHook_nested_flag
4044  0163 26db              	bne	L1503
4045                         ; 170    	    EE_oo_ErrorHook_ServiceID = OSServiceId_CounterTick;
4047  0165 c611              	ldab	#17
4048  0167 7b0000            	stab	_EE_oo_ErrorHook_ServiceID
4049                         ; 171 	    EE_oo_ErrorHook_data.CounterTick_prm.AlarmID = current;
4051  016a 1805820000        	movw	OFST-10,s,_EE_oo_ErrorHook_data
4052                         ; 172 	    EE_oo_ErrorHook_data.CounterTick_prm.TaskID = TaskID;
4054  016f 1805860004        	movw	OFST-6,s,_EE_oo_ErrorHook_data+4
4055  0174 1805840002        	movw	OFST-8,s,_EE_oo_ErrorHook_data+2
4056                         ; 173 	    EE_oo_ErrorHook_data.CounterTick_prm.action =
4056                         ; 174 	      EE_alarm_ROM[current].action;
4058  0179 ec82              	ldd	OFST-10,s
4059  017b cd000d            	ldy	#13
4060  017e 13                	emul	
4061  017f b746              	tfr	d,y
4062  0181 180dea00020008    	movb	_EE_alarm_ROM+2,y,_EE_oo_ErrorHook_data+8
4063                         ; 176 	    EE_ErrorHook_nested_flag = 1;
4065  0188 cc0001            	ldd	#1
4066  018b 7c0000            	std	_EE_ErrorHook_nested_flag
4067                         ; 177 	    ErrorHook(E_OS_LIMIT);
4069  018e c604              	ldab	#4
4071                         ; 178 	    EE_ErrorHook_nested_flag = 0;
4073  0190 060219            	bra	LC002
4074  0193                   L3503:
4075                         ; 185 	EE_th_rnact[TaskID]--;
4077  0193 ed86              	ldy	OFST-6,s
4078  0195 1858              	lsly	
4079  0197 1863ea0000        	decw	_EE_th_rnact,y
4080                         ; 188 	if (EE_th_status[TaskID] == SUSPENDED) {
4082  019c ecea0000          	ldd	_EE_th_status,y
4083  01a0 8c0003            	cpd	#3
4084  01a3 182600a6          	bne	LC001
4085                         ; 189 	  EE_th_status[TaskID] = READY;
4087  01a7 cc0002            	ldd	#2
4088  01aa 6cea0000          	std	_EE_th_status,y
4089                         ; 193 	  EE_th_event_active[TaskID] = 0;
4091  01ae 1869ea0000        	clrw	_EE_th_event_active,y
4092                         ; 204 	EE_rq_insert(TaskID);
4095                         ; 206   	break;
4097  01b3 06024d            	bra	LC001
4098  01b6                   L3672:
4099                         ; 212       case EE_ALARM_ACTION_EVENT:
4099                         ; 213 	/* set an event for a task... NOTE: no preemption at all... 
4099                         ; 214 	   This code was directly copied from SetEvent */
4099                         ; 215 	
4099                         ; 216 	TaskID = EE_alarm_ROM[current].TaskID;
4101  01b6 ce0003            	ldx	#_EE_alarm_ROM+3
4102  01b9 ec82              	ldd	OFST-10,s
4103  01bb cd000d            	ldy	#13
4104  01be 13                	emul	
4105  01bf 19e6              	leay	d,x
4106  01c1 18024286          	movw	2,y,OFST-6,s
4107  01c5 18024084          	movw	0,y,OFST-8,s
4108                         ; 217 	Mask = EE_alarm_ROM[current].Mask;
4110  01c9 ec82              	ldd	OFST-10,s
4111  01cb cd000d            	ldy	#13
4112  01ce 13                	emul	
4113  01cf b746              	tfr	d,y
4114  01d1 1802ea000788      	movw	_EE_alarm_ROM+7,y,OFST-4,s
4115                         ; 284 	if (EE_th_status[TaskID] == SUSPENDED) {
4117  01d7 ed86              	ldy	OFST-6,s
4118  01d9 1858              	lsly	
4119  01db ecea0000          	ldd	_EE_th_status,y
4120  01df 8c0003            	cpd	#3
4121  01e2 263f              	bne	L1603
4122                         ; 290 	  if (!EE_ErrorHook_nested_flag) {
4124  01e4 fc0000            	ldd	_EE_ErrorHook_nested_flag
4125  01e7 267b              	bne	L1503
4126                         ; 292             EE_oo_ErrorHook_ServiceID = OSServiceId_CounterTick;
4128  01e9 c611              	ldab	#17
4129  01eb 7b0000            	stab	_EE_oo_ErrorHook_ServiceID
4130                         ; 293 	    EE_oo_ErrorHook_data.CounterTick_prm.AlarmID = current;
4132  01ee 1805820000        	movw	OFST-10,s,_EE_oo_ErrorHook_data
4133                         ; 294 	    EE_oo_ErrorHook_data.CounterTick_prm.TaskID = TaskID;
4135  01f3 1805860004        	movw	OFST-6,s,_EE_oo_ErrorHook_data+4
4136  01f8 1805840002        	movw	OFST-8,s,_EE_oo_ErrorHook_data+2
4137                         ; 295 	    EE_oo_ErrorHook_data.CounterTick_prm.Mask = Mask;
4139  01fd 1805880006        	movw	OFST-4,s,_EE_oo_ErrorHook_data+6
4140                         ; 296 	    EE_oo_ErrorHook_data.CounterTick_prm.action =
4140                         ; 297 	      EE_alarm_ROM[current].action;
4142  0202 ec82              	ldd	OFST-10,s
4143  0204 cd000d            	ldy	#13
4144  0207 13                	emul	
4145  0208 b746              	tfr	d,y
4146  020a 180dea00020008    	movb	_EE_alarm_ROM+2,y,_EE_oo_ErrorHook_data+8
4147                         ; 299 	    EE_ErrorHook_nested_flag = 1;
4149  0211 cc0001            	ldd	#1
4150  0214 7c0000            	std	_EE_ErrorHook_nested_flag
4151                         ; 300 	    ErrorHook(E_OS_STATE);
4153  0217 c607              	ldab	#7
4155                         ; 301 	    EE_ErrorHook_nested_flag = 0;
4157  0219                   LC002:
4158  0219 4a000000          	call	f_ErrorHook
4159  021d 18790000          	clrw	_EE_ErrorHook_nested_flag
4160  0221 2041              	bra	L1503
4161  0223                   L1603:
4162                         ; 309 	EE_th_event_active[TaskID] |= Mask;
4164  0223 ed86              	ldy	OFST-6,s
4165  0225 1858              	lsly	
4166  0227 ee88              	ldx	OFST-4,s
4167  0229 18aaea0000        	orx	_EE_th_event_active,y
4168  022e 6eea0000          	stx	_EE_th_event_active,y
4169                         ; 319 	if (EE_th_event_waitmask[TaskID] & Mask &&
4169                         ; 320 	    EE_th_status[TaskID] == WAITING) {
4171  0232 ed86              	ldy	OFST-6,s
4172  0234 1858              	lsly	
4173  0236 eeea0000          	ldx	_EE_th_event_waitmask,y
4174  023a 18a488            	andx	OFST-4,s
4175  023d 2725              	beq	L1503
4177  023f ecea0000          	ldd	_EE_th_status,y
4178  0243 04241e            	dbne	d,L1503
4179                         ; 322 	  EE_th_status[TaskID] = READY;
4181  0246 cc0002            	ldd	#2
4182  0249 6cea0000          	std	_EE_th_status,y
4183                         ; 324 	  EE_rq_insert(TaskID);
4185  024d                   LC001:
4186  024d ec86              	ldd	OFST-6,s
4187  024f ee84              	ldx	OFST-8,s
4188  0251 4a000000          	call	f_EE_rq_insert
4190  0255 200d              	bra	L1503
4191  0257                   L5672:
4192                         ; 333       case EE_ALARM_ACTION_CALLBACK:
4192                         ; 334 	((void (*)(void))EE_alarm_ROM[current].f)();
4194  0257 ce0009            	ldx	#_EE_alarm_ROM+9
4195  025a ec82              	ldd	OFST-10,s
4196  025c cd000d            	ldy	#13
4197  025f 13                	emul	
4198  0260 b756              	tfr	x,y
4199  0262 4bef              	call	[d,y]
4201                         ; 335 	break;
4203  0264                   L1503:
4204                         ; 339       EE_counter_RAM[c].first = EE_alarm_RAM[current].next;
4207  0264 ed8c              	ldy	OFST+0,s
4208  0266 1858              	lsly	
4209  0268 1858              	lsly	
4210  026a ee82              	ldx	OFST-10,s
4211  026c 1848              	lslx	
4212  026e 1848              	lslx	
4213  0270 1848              	lslx	
4214  0272 1802e20006ea0002  	movw	_EE_alarm_RAM+6,x,_EE_counter_RAM+2,y
4215                         ; 342       if (EE_alarm_RAM[current].cycle) {
4217  027a ed82              	ldy	OFST-10,s
4218  027c 1858              	lsly	
4219  027e 1858              	lsly	
4220  0280 1858              	lsly	
4221  0282 ecea0002          	ldd	_EE_alarm_RAM+2,y
4222  0286 2717              	beq	L7603
4223                         ; 346 	EE_oo_alarm_insert(current,EE_alarm_RAM[current].cycle);
4225  0288 ed82              	ldy	OFST-10,s
4226  028a 1858              	lsly	
4227  028c 1858              	lsly	
4228  028e 1858              	lsly	
4229  0290 ecea0002          	ldd	_EE_alarm_RAM+2,y
4230  0294 3b                	pshd	
4231  0295 ec84              	ldd	OFST-8,s
4232  0297 4a000000          	call	f_EE_oo_alarm_insert
4234  029b 1b82              	leas	2,s
4236  029d 200d              	bra	L1703
4237  029f                   L7603:
4238                         ; 349 	EE_alarm_RAM[current].used = 0;
4240  029f ed82              	ldy	OFST-10,s
4241  02a1 1858              	lsly	
4242  02a3 1858              	lsly	
4243  02a5 1858              	lsly	
4244  02a7 1869ea0000        	clrw	_EE_alarm_RAM,y
4245  02ac                   L1703:
4246                         ; 352       current = EE_counter_RAM[c].first;
4248  02ac ed8c              	ldy	OFST+0,s
4249  02ae 1858              	lsly	
4250  02b0 1858              	lsly	
4251  02b2 ecea0002          	ldd	_EE_counter_RAM+2,y
4252  02b6 6c82              	std	OFST-10,s
4253                         ; 353       if (current == -1) break;
4255  02b8 8cffff            	cpd	#-1
4256  02bb 2710              	beq	L7303
4259  02bd                   L3403:
4260                         ; 113     while (!EE_alarm_RAM[current].delta) {
4262  02bd b746              	tfr	d,y
4263  02bf 1858              	lsly	
4264  02c1 1858              	lsly	
4265  02c3 1858              	lsly	
4266  02c5 edea0004          	ldy	_EE_alarm_RAM+4,y
4267  02c9 1827fe5f          	beq	L1403
4268  02cd                   L7303:
4269                         ; 111   if(f & 0x10) 						// restore I bit
4272  02cd 0f8b1004          	brclr	OFST-1,s,16,L5013
4273                         ; 200   ASM_DIS_INT;
4276  02d1 1410              	sei	
4278  02d3 2002              	bra	L7772
4279  02d5                   L5013:
4280                         ; 191   ASM_EN_INT;
4283  02d5 10ef              	cli	
4285  02d7                   L7772:
4286                         ; 358 }
4290  02d7 1b8e              	leas	14,s
4291  02d9 0a                	rtc	
4303                         	xdef	f_EE_oo_alarm_insert
4304                         	xref	f_EE_rq_insert
4305                         	xref	_EE_ErrorHook_nested_flag
4306                         	xref	_EE_pit0_initialized
4307                         	xref	_EE_ApplicationMode
4308                         	xref	_EE_oo_IRQ_disable_count
4309                         	xref	f_ErrorHook
4310                         	xdef	f_EE_oo_counter_tick
4311                         	xref	_EE_oo_ErrorHook_data
4312                         	xref	_EE_oo_ErrorHook_ServiceID
4313                         	xref	_EE_alarm_RAM
4314                         	xref	_EE_alarm_ROM
4315                         	xref	_EE_counter_RAM
4316                         	xref	_EE_th_event_waitmask
4317                         	xref	_EE_th_event_active
4318                         	xref	_EE_stkfirst
4319                         	xref	_EE_th_rnact
4320                         	xref	_EE_th_next
4321                         	xref	_EE_th_status
4322                         	xref	_EE_buttons_initialized
4323                         	xref	f_EE_s12xs_terminate_task
4324                         	xref	f_EE_s12xs_terminate_savestk
4325                         	xref	_EE_IRQ_nesting_level
4326                         	xref	f_EE_s12xs_hal_stkchange
4327                         	xref	f_EE_s12xs_hal_ready2stacked
4328                         	xref	_EE_hal_endcycle_next_tos
4329                         	xref	_EE_hal_endcycle_next_thread
4330                         	xref	_EE_terminate_real_th_body
4331                         	xref	_EE_terminate_data
4332                         	xref	_EE_s12xs_thread_tos
4333                         	xref	_EE_hal_thread_body
4353                         	end
