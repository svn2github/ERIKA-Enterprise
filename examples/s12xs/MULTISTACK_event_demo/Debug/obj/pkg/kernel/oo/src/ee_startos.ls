   1                         ; C Compiler for S12X [COSMIC Software].
   2                         ; Generator (Limited) V4.7.11.2 - 16 Mar 2009
   3                         ; Optimizer V4.6.16 - 02 Dec 2008
3767                         ; 60 void EE_oo_StartOS(AppModeType Mode)
3767                         ; 61 #endif
3767                         ; 62 { 
3768                         .ftext:	section	.text
3769  0000                   f_EE_oo_StartOS:
3771  0000 3b                	pshd	
3772  0001 1b96              	leas	-10,s
3773       0000000a          OFST:	set	10
3776                         ; 101   retvalue = _asm("tfr ccr,b\n");	// save CCR register (I bit)
3780  0003 b721              	tfr	ccr,b
3782                         ; 200   ASM_DIS_INT;
3785  0005 1410              	sei	
3787                         ; 104   return retvalue;
3790  0007 6c88              	std	OFST-2,s
3792                         ; 105 }
3794                         ; 111   EE_ApplicationMode = Mode;
3796  0009 18058a0000        	movw	OFST+0,s,_EE_ApplicationMode
3797                         ; 114   EE_oo_no_preemption = 1;
3799  000e cc0001            	ldd	#1
3800  0011 7c0000            	std	_EE_oo_no_preemption
3801                         ; 117   StartupHook();
3803  0014 4a000000          	call	f_StartupHook
3805                         ; 121   if (Mode >= 0 && Mode < EE_MAX_APPMODE) {
3807  0018 ec8a              	ldd	OFST+0,s
3808  001a 266b              	bne	L3772
3809                         ; 124     n = EE_oo_autostart_task_data[Mode].n;
3811  001c 59                	lsld	
3812  001d 59                	lsld	
3813  001e b746              	tfr	d,y
3814  0020 180aea000183      	movb	_EE_oo_autostart_task_data+1,y,OFST-7,s
3815                         ; 125     for (t = 0; t<n; t++)
3817  0026 6982              	clr	OFST-8,s
3819  0028 2017              	bra	L1003
3820  002a                   L5772:
3821                         ; 126       EE_oo_ActivateTask(EE_oo_autostart_task_data[Mode].task[t]);
3823  002a 1858              	lsly	
3824  002c 1858              	lsly	
3825  002e eeea0002          	ldx	_EE_oo_autostart_task_data+2,y
3826  0032 87                	clra	
3827  0033 59                	lsld	
3828  0034 59                	lsld	
3829  0035 19e6              	leay	d,x
3830  0037 ec42              	ldd	2,y
3831  0039 ee40              	ldx	0,y
3832  003b 4a000000          	call	f_EE_oo_ActivateTask
3834                         ; 125     for (t = 0; t<n; t++)
3836  003f 6282              	inc	OFST-8,s
3837  0041                   L1003:
3840  0041 e682              	ldab	OFST-8,s
3841  0043 e183              	cmpb	OFST-7,s
3842  0045 ed8a              	ldy	OFST+0,s
3843  0047 25e1              	blo	L5772
3844                         ; 130     n = EE_oo_autostart_alarm_data[Mode].n;
3846  0049 1858              	lsly	
3847  004b 1858              	lsly	
3848  004d 180aea000183      	movb	_EE_oo_autostart_alarm_data+1,y,OFST-7,s
3849                         ; 131     for (t = 0; t<n; t++) {
3851  0053 6982              	clr	OFST-8,s
3853  0055 202a              	bra	L1103
3854  0057                   L5003:
3855                         ; 132       EE_TYPEALARM alarm_temp = EE_oo_autostart_alarm_data[Mode].alarm[t];
3857  0057 ed8a              	ldy	OFST+0,s
3858  0059 1858              	lsly	
3859  005b 1858              	lsly	
3860  005d eeea0002          	ldx	_EE_oo_autostart_alarm_data+2,y
3861  0061 87                	clra	
3862  0062 59                	lsld	
3863  0063 ede6              	ldy	d,x
3864  0065 6d80              	sty	OFST-10,s
3865                         ; 133       EE_oo_SetRelAlarm(alarm_temp, 
3865                         ; 134 			EE_oo_autostart_alarm_increment[alarm_temp],
3865                         ; 135 			EE_oo_autostart_alarm_cycle[alarm_temp]);
3867  0067 1858              	lsly	
3868  0069 ecea0000          	ldd	_EE_oo_autostart_alarm_cycle,y
3869  006d 3b                	pshd	
3870  006e ed82              	ldy	OFST-8,s
3871  0070 1858              	lsly	
3872  0072 ecea0000          	ldd	_EE_oo_autostart_alarm_increment,y
3873  0076 3b                	pshd	
3874  0077 ec84              	ldd	OFST-6,s
3875  0079 4a000000          	call	f_EE_oo_SetRelAlarm
3877  007d 1b84              	leas	4,s
3878                         ; 131     for (t = 0; t<n; t++) {
3880  007f 6282              	inc	OFST-8,s
3881  0081                   L1103:
3884  0081 e682              	ldab	OFST-8,s
3885  0083 e183              	cmpb	OFST-7,s
3886  0085 25d0              	blo	L5003
3887  0087                   L3772:
3888                         ; 141   EE_oo_no_preemption = 0;
3890  0087 18790000          	clrw	_EE_oo_no_preemption
3891                         ; 145   rq = EE_rq_queryfirst();
3893  008b 4a000000          	call	f_EE_rq_queryfirst
3895  008f 6c86              	std	OFST-4,s
3896  0091 6e84              	stx	OFST-6,s
3897                         ; 146   if (rq != EE_NIL) {
3899  0093 04a505            	ibne	x,LC001
3900  0096 8cffff            	cpd	#-1
3901  0099 273a              	beq	L5103
3902  009b                   LC001:
3903                         ; 148       EE_sys_ceiling |= EE_th_dispatch_prio[rq];
3905  009b b746              	tfr	d,y
3906  009d 1858              	lsly	
3907  009f edea0000          	ldy	_EE_th_dispatch_prio,y
3908  00a3 18fa0000          	ory	_EE_sys_ceiling
3909  00a7 7d0000            	sty	_EE_sys_ceiling
3910                         ; 150       EE_th_status[rq] = RUNNING;
3912  00aa 59                	lsld	
3913  00ab b746              	tfr	d,y
3914  00ad 1869ea0000        	clrw	_EE_th_status,y
3915                         ; 105 }
3918  00b2 4a000000          	call	f_EE_rq2stk_exchange
3920  00b6 6c86              	std	OFST-4,s
3921  00b8 6e84              	stx	OFST-6,s
3922                         ; 141     EE_s12xs_hal_ready2stacked(EE_hal_thread_body[thread],
3922                         ; 142 			         EE_s12xs_thread_tos[thread+1]);
3924  00ba 59                	lsld	
3925  00bb b746              	tfr	d,y
3926  00bd ecea0002          	ldd	_EE_s12xs_thread_tos+2,y
3927  00c1 3b                	pshd	
3928  00c2 cd0000            	ldy	#_EE_hal_thread_body
3929  00c5 ec88              	ldd	OFST-2,s
3930  00c7 59                	lsld	
3931  00c8 59                	lsld	
3932  00c9 19ee              	leay	d,y
3933  00cb ec42              	ldd	2,y
3934  00cd ee40              	ldx	0,y
3935  00cf 4a000000          	call	f_EE_s12xs_hal_ready2stacked
3937  00d3 1b82              	leas	2,s
3938  00d5                   L5103:
3939                         ; 111   if(f & 0x10) 						// restore I bit
3942  00d5 0f891004          	brclr	OFST-1,s,16,L7203
3943                         ; 200   ASM_DIS_INT;
3946  00d9 1410              	sei	
3948  00db 2002              	bra	L1272
3949  00dd                   L7203:
3950                         ; 191   ASM_EN_INT;
3953  00dd 10ef              	cli	
3955  00df                   L1272:
3956                         ; 173 }
3960  00df 1b8c              	leas	12,s
3961  00e1 0a                	rtc	
3973                         	xref	f_EE_rq2stk_exchange
3974                         	xref	f_EE_rq_queryfirst
3975                         	xref	_EE_oo_no_preemption
3976                         	xref	_EE_pit0_initialized
3977                         	xref	_EE_ApplicationMode
3978                         	xref	_EE_oo_IRQ_disable_count
3979                         	xref	f_StartupHook
3980                         	xdef	f_EE_oo_StartOS
3981                         	xref	f_EE_oo_SetRelAlarm
3982                         	xref	f_EE_oo_ActivateTask
3983                         	xref	_EE_oo_ErrorHook_data
3984                         	xref	_EE_oo_ErrorHook_ServiceID
3985                         	xref	_EE_oo_autostart_alarm_cycle
3986                         	xref	_EE_oo_autostart_alarm_increment
3987                         	xref	_EE_oo_autostart_alarm_data
3988                         	xref	_EE_oo_autostart_task_data
3989                         	xref	_EE_sys_ceiling
3990                         	xref	_EE_stkfirst
3991                         	xref	_EE_th_dispatch_prio
3992                         	xref	_EE_th_next
3993                         	xref	_EE_th_status
3994                         	xref	_EE_buttons_initialized
3995                         	xref	f_EE_s12xs_terminate_task
3996                         	xref	f_EE_s12xs_terminate_savestk
3997                         	xref	_EE_IRQ_nesting_level
3998                         	xref	f_EE_s12xs_hal_stkchange
3999                         	xref	f_EE_s12xs_hal_ready2stacked
4000                         	xref	_EE_hal_endcycle_next_tos
4001                         	xref	_EE_hal_endcycle_next_thread
4002                         	xref	_EE_terminate_real_th_body
4003                         	xref	_EE_terminate_data
4004                         	xref	_EE_s12xs_thread_tos
4005                         	xref	_EE_hal_thread_body
4025                         	end
