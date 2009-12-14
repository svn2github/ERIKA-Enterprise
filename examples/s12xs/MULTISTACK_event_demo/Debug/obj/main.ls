   1                         ; C Compiler for S12X [COSMIC Software].
   2                         ; Generator (Limited) V4.7.11.2 - 16 Mar 2009
   3                         ; Optimizer V4.6.16 - 02 Dec 2008
3604                         	switch	.data
3605  0000                   _timer_fired:
3606  0000 0000              	dc.w	0
3607  0002                   _button_fired:
3608  0002 0000              	dc.w	0
3609  0004                   _dummit_counter:
3610  0004 0000              	dc.w	0
3611  0006                   _led_status:
3612  0006 0000              	dc.w	0
3703                         ; 61 void mydelay(unsigned long int del)
3703                         ; 62 {
3704                         .ftext:	section	.text
3705  0000                   f_mydelay:
3707  0000 3b                	pshd	
3708  0001 34                	pshx	
3709  0002 3b                	pshd	
3710       00000002          OFST:	set	2
3713                         ; 64   for (i=0; i<del; i++);
3715  0003 186980            	clrw	OFST-2,s
3717  0006 2003              	bra	L5762
3718  0008                   L1762:
3722  0008 186280            	incw	OFST-2,s
3723  000b                   L5762:
3726  000b ec80              	ldd	OFST-2,s
3727  000d b74d              	sex	d,x
3728  000f ac84              	cpd	OFST+2,s
3729  0011 18ae82            	cpex	OFST+0,s
3730  0014 25f2              	blo	L1762
3731                         ; 65 }
3734  0016 1b86              	leas	6,s
3735  0018 0a                	rtc	
3798                         ; 70 void led_blink(unsigned char theled)
3798                         ; 71 {
3799                         	switch	.ftext
3800  0019                   f_led_blink:
3802  0019 37                	pshb	
3803       00000000          OFST:	set	0
3806                         ; 200   ASM_DIS_INT;
3809  001a 1410              	sei	
3811                         ; 73   led_status |= theled;
3814  001c b796              	exg	b,y
3815  001e 18fa0006          	ory	_led_status
3816  0022 7d0006            	sty	_led_status
3817                         ; 81 	PORTA = (EE_UINT8)(data & ((EE_UINT8)0x0F));
3820  0025 f60007            	ldab	_led_status+1
3821  0028 c40f              	andb	#15
3822  002a 7b0000            	stab	_PORTA
3823                         ; 191   ASM_EN_INT;
3826  002d 10ef              	cli	
3828                         ; 77   mydelay((long int)125000);
3831  002f ce0001            	ldx	#1
3832  0032 cce848            	ldd	#-6072
3833  0035 4a000000          	call	f_mydelay
3835                         ; 200   ASM_DIS_INT;
3838  0039 1410              	sei	
3840                         ; 80   led_status &= ~theled;
3843  003b e680              	ldab	OFST+0,s
3844  003d b796              	exg	b,y
3845  003f 1851              	comy	
3846  0041 18f40006          	andy	_led_status
3847  0045 7d0006            	sty	_led_status
3848                         ; 81 	PORTA = (EE_UINT8)(data & ((EE_UINT8)0x0F));
3851  0048 f60007            	ldab	_led_status+1
3852  004b c40f              	andb	#15
3853  004d 7b0000            	stab	_PORTA
3854                         ; 191   ASM_EN_INT;
3857  0050 10ef              	cli	
3859                         ; 83 }
3863  0052 1b81              	leas	1,s
3864  0054 0a                	rtc	
3900                         ; 85 TASK(Task1)
3900                         ; 86 {
3901                         	switch	.ftext
3902  0055                   f_FuncTask1:
3904  0055 3b                	pshd	
3905       00000002          OFST:	set	2
3908  0056                   L5103:
3909                         ; 90     WaitEvent(TimerEvent|ButtonEvent);
3911  0056 cc0003            	ldd	#3
3912  0059 4a000000          	call	f_EE_oo_WaitEvent
3914                         ; 91     GetEvent(Task1, &mask);
3916  005d 1a80              	leax	OFST-2,s
3917  005f 34                	pshx	
3918  0060 87                	clra	
3919  0061 c7                	clrb	
3920  0062 1887              	clrx	
3921  0064 4a000000          	call	f_EE_oo_GetEvent
3923  0068 1b82              	leas	2,s
3924                         ; 93     if (mask & TimerEvent) {
3926  006a e681              	ldab	OFST-1,s
3927  006c c501              	bitb	#1
3928  006e 270f              	beq	L1203
3929                         ; 94       led_blink(0x01);
3931  0070 c601              	ldab	#1
3932  0072 4a001919          	call	f_led_blink
3934                         ; 95       ClearEvent(TimerEvent);
3936  0076 cc0001            	ldd	#1
3937  0079 4a000000          	call	f_EE_oo_ClearEvent
3939  007d e681              	ldab	OFST-1,s
3940  007f                   L1203:
3941                         ; 98     if (mask & ButtonEvent) {
3943  007f c502              	bitb	#2
3944  0081 27d3              	beq	L5103
3945                         ; 99       led_blink(0x02);
3947  0083 c602              	ldab	#2
3948  0085 4a001919          	call	f_led_blink
3950                         ; 100       ClearEvent(ButtonEvent);
3952  0089 cc0002            	ldd	#2
3953  008c 4a000000          	call	f_EE_oo_ClearEvent
3955  0090 20c4              	bra	L5103
3979                         ; 106 TASK(Task2)
3979                         ; 107 {
3980                         	switch	.ftext
3981  0092                   f_FuncTask2:
3985                         ; 108   led_blink(0x04);
3987  0092 c604              	ldab	#4
3988  0094 4a001919          	call	f_led_blink
3990                         ; 109   TerminateTask();
3992  0098 4a000000          	call	f_EE_oo_TerminateTask
3994                         ; 110 }
3997  009c 0a                	rtc	
4030                         ; 112 void ErrorHook(StatusType Error)
4030                         ; 113 {
4031                         	switch	.ftext
4032  009d                   f_ErrorHook:
4036                         ; 114   myErrorCounter++;
4038  009d 18720000          	incw	_myErrorCounter
4039                         ; 115   led_blink(0xFF);
4041  00a1 c6ff              	ldab	#255
4042  00a3 4a001919          	call	f_led_blink
4044                         ; 116 }
4047  00a7 0a                	rtc	
4142                         ; 122 void StartupHook(void)
4142                         ; 123 {
4143                         	switch	.ftext
4144  00a8                   f_StartupHook:
4148                         ; 130 	if(EE_buttons_initialized == 1)
4151  00a8 f60000            	ldab	_EE_buttons_initialized
4152  00ab 040119            	dbeq	b,L1503
4153                         ; 131 		return;
4155                         ; 132 	DDRP = (unsigned char)0x00;		// configured in input mode
4157  00ae 79025a            	clr	_DDRP
4158                         ; 133 	PIEP = (EE_UINT8)(bx+1);
4160  00b1 c601              	ldab	#1
4161  00b3 7b025e            	stab	_PIEP
4162                         ; 134 	_asm("cli");
4165  00b6 10ef              	cli	
4167                         ; 135 	INT_CFADDR = 0x8E;
4169  00b8 c68e              	ldab	#142
4170  00ba 7b0127            	stab	_INT_CFADDR
4171                         ; 136 	INT_CFDATA0 = prio;
4173  00bd c603              	ldab	#3
4174  00bf 7b0128            	stab	_INT_CFDATA0
4175                         ; 137 	EE_buttons_initialized = 1;
4177  00c2 c601              	ldab	#1
4178  00c4 7b0000            	stab	_EE_buttons_initialized
4179  00c7                   L1503:
4180                         ; 17 	if(EE_pit0_initialized==1)
4184  00c7 f60000            	ldab	_EE_pit0_initialized
4185  00ca 040153            	dbeq	b,L3503
4186                         ; 18 		return;
4188                         ; 21 	  PITCFLMT      = 0x00;        //@0x340;	/* PIT control micro timer register */
4190  00cd 790340            	clr	_PITCFLMT
4191                         ; 22 	  PITFLT        = 0x00;        //@0x341;	/* PIT force load timer register */
4193  00d0 790341            	clr	_PITFLT
4194                         ; 23 	  PITCE         = 0x01;        //@0x342;	/* PIT channel enable register */
4196  00d3 c601              	ldab	#1
4197  00d5 7b0342            	stab	_PITCE
4198                         ; 24 	  PITMUX        = 0x00;        //@0x343;	/* PIT multiplex register */
4200  00d8 790343            	clr	_PITMUX
4201                         ; 25 	  PITINTE       = 0x01;        //@0x344;	/* PIT interrupt enable register */
4203  00db 7b0344            	stab	_PITINTE
4204                         ; 26 	  PITTF         = 0x01;        //@0x345;	/* PIT time-out flag register */
4206  00de 7b0345            	stab	_PITTF
4207                         ; 27 	  PITMTLD0      = pitmtld0;        //@0x346;	/* PIT micro timer load reg. 0 */
4209  00e1 c663              	ldab	#99
4210  00e3 7b0346            	stab	_PITMTLD0
4211                         ; 28 	  PITMTLD1      = 0x00;        //@0x347;	/* PIT micro timer load reg. 1 */
4213  00e6 790347            	clr	_PITMTLD1
4214                         ; 29 	  PITLD0        = pitld0;        //@0x348;	/* PIT load register 0 */
4216  00e9 cc000e            	ldd	#14
4217  00ec 7c0348            	std	_PITLD0
4218                         ; 30 	  PITCNT0       = 0x00;        //@0x34a;	/* PIT count register 0 */
4220  00ef 1879034a          	clrw	_PITCNT0
4221                         ; 31 	  PITLD1        = 0x00;        //@0x34c;	/* PIT load register 1 */
4223  00f3 1879034c          	clrw	_PITLD1
4224                         ; 32 	  PITCNT1       = 0x00;        //@0x34e;	/* PIT count register 1 */
4226  00f7 1879034e          	clrw	_PITCNT1
4227                         ; 33 	  PITLD2        = 0x00;        //@0x350;	/* PIT load register 2 */
4229  00fb 18790350          	clrw	_PITLD2
4230                         ; 34 	  PITCNT2       = 0x00;        //@0x352;	/* PIT count register 2 */
4232  00ff 18790352          	clrw	_PITCNT2
4233                         ; 35 	  PITLD3        = 0x00;        //@0x354;	/* PIT load register 3 */
4235  0103 18790354          	clrw	_PITLD3
4236                         ; 36 	  PITCNT3       = 0x00;        //@0x356;	/* PIT count register 3 */
4238  0107 18790356          	clrw	_PITCNT3
4239                         ; 37 	  PITCFLMT      = 0x80;        //@0x340;	/* PIT control micro timer register */
4241  010b c680              	ldab	#128
4242  010d 7b0340            	stab	_PITCFLMT
4243                         ; 40 	  _asm("cli");
4246  0110 10ef              	cli	
4248                         ; 41 	  INT_CFADDR = 0x7A;
4250  0112 c67a              	ldab	#122
4251  0114 7b0127            	stab	_INT_CFADDR
4252                         ; 42 	  INT_CFDATA0 = prio;
4254  0117 c602              	ldab	#2
4255  0119 7b0128            	stab	_INT_CFDATA0
4256                         ; 43 	  EE_pit0_initialized = 1;
4258  011c 53                	decb	
4259  011d 7b0000            	stab	_EE_pit0_initialized
4260                         ; 45 	  return;
4261  0120                   L3503:
4262                         ; 129 }
4266  0120 0a                	rtc	
4293                         ; 133 int main(void)
4293                         ; 134 {
4294                         	switch	.ftext
4295  0121                   f_main:
4299                         ; 74 	PORTA = (unsigned char)0x00;	// values                                             
4302  0121 c7                	clrb	
4303  0122 7b0000            	stab	_PORTA
4304                         ; 75   	DDRA = (unsigned char)0x0F;		// configured in output mode
4306  0125 c60f              	ldab	#15
4307  0127 7b0002            	stab	_DDRA
4308                         ; 142   mydelay(1000);
4311  012a ce0000            	ldx	#0
4312  012d cc03e8            	ldd	#1000
4313  0130 4a000000          	call	f_mydelay
4315                         ; 145   StartOS(OSDEFAULTAPPMODE);
4317  0134 87                	clra	
4318  0135 c7                	clrb	
4319  0136 4a000000          	call	f_EE_oo_StartOS
4321  013a                   L1313:
4322                         ; 148   while(1);
4324  013a 20fe              	bra	L1313
4383                         	xdef	f_main
4384                         	switch	.bss
4385  0000                   _myErrorCounter:
4386  0000 0000              	ds.b	2
4387                         	xdef	_myErrorCounter
4388                         	xdef	_led_status
4389                         	xdef	_dummit_counter
4390                         	xdef	_button_fired
4391                         	xdef	_timer_fired
4392                         	xdef	f_FuncTask2
4393                         	xdef	f_FuncTask1
4394                         	xdef	f_led_blink
4395                         	xdef	f_mydelay
4396                         	xref	f_EE_s12xs_hal_stkchange
4397                         	xref	f_EE_s12xs_hal_ready2stacked
4398                         	xref	f_EE_IRQ_end_instance
4399                         	xref	_EE_IRQ_nesting_level
4400                         	xref	_EE_hal_endcycle_next_tos
4401                         	xref	_EE_hal_endcycle_next_thread
4402                         	xref	_EE_pit0_initialized
4403                         	xref	_EE_ApplicationMode
4404                         	xref	_EE_oo_IRQ_disable_count
4405                         	xdef	f_StartupHook
4406                         	xdef	f_ErrorHook
4407                         	xref	f_EE_oo_StartOS
4408                         	xref	f_EE_oo_WaitEvent
4409                         	xref	f_EE_oo_GetEvent
4410                         	xref	f_EE_oo_ClearEvent
4411                         	xref	f_EE_oo_TerminateTask
4412                         	xref	_EE_oo_ErrorHook_data
4413                         	xref	_EE_oo_ErrorHook_ServiceID
4414                         	xref	_EE_stkfirst
4415                         	xref	_EE_th_status
4416                         	xref	_EE_buttons_initialized
4417                         	xref	_EE_s12xs_active_tos
4438                         	end
