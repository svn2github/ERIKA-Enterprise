   1                         ; C Compiler for S12X [COSMIC Software].
   2                         ; Generator (Limited) V4.7.11.2 - 16 Mar 2009
   3                         ; Optimizer V4.6.16 - 02 Dec 2008
3768                         ; 71 void EE_oo_SetEvent(TaskType TaskID, EventMaskType Mask)
3768                         ; 72 #endif
3768                         ; 73 {
3769                         .ftext:	section	.text
3770  0000                   f_EE_oo_SetEvent:
3772  0000 3b                	pshd	
3773  0001 34                	pshx	
3774  0002 1b90              	leas	-16,s
3775       00000010          OFST:	set	16
3778                         ; 101   retvalue = _asm("tfr ccr,b\n");	// save CCR register (I bit)
3782  0004 b721              	tfr	ccr,b
3784                         ; 200   ASM_DIS_INT;
3787  0006 1410              	sei	
3789                         ; 104   return retvalue;
3792  0008 6c8e              	std	OFST-2,s
3794                         ; 105 }
3796                         ; 192   EE_th_event_active[TaskID] |= Mask;
3798  000a edf012            	ldy	OFST+2,s
3799  000d 1858              	lsly	
3800  000f eef017            	ldx	OFST+7,s
3801  0012 18aaea0000        	orx	_EE_th_event_active,y
3802  0017 6eea0000          	stx	_EE_th_event_active,y
3803                         ; 202   if (EE_th_event_waitmask[TaskID] & Mask &&
3803                         ; 203       EE_th_status[TaskID] == WAITING) {
3805  001b edf012            	ldy	OFST+2,s
3806  001e 1858              	lsly	
3807  0020 eeea0000          	ldx	_EE_th_event_waitmask,y
3808  0024 18a4f017          	andx	OFST+7,s
3809  0028 182700b2          	beq	L3003
3811  002c ecea0000          	ldd	_EE_th_status,y
3812  0030 8c0001            	cpd	#1
3813  0033 182600a7          	bne	L3003
3814                         ; 205     EE_th_status[TaskID] = READY;
3816  0037 cc0002            	ldd	#2
3817  003a 6cea0000          	std	_EE_th_status,y
3818                         ; 207     EE_rq_insert(TaskID);
3820  003e ecf012            	ldd	OFST+2,s
3821  0041 eef010            	ldx	OFST+0,s
3822  0044 4a000000          	call	f_EE_rq_insert
3827  0048 fc0000            	ldd	_EE_IRQ_nesting_level
3828  004b 6c84              	std	OFST-12,s
3830                         ; 208 }
3832  004d 1826008d          	bne	L3003
3833                         ; 212       tmp = EE_rq_queryfirst();
3835  0051 4a000000          	call	f_EE_rq_queryfirst
3837  0055 6c88              	std	OFST-8,s
3838  0057 6e86              	stx	OFST-10,s
3839                         ; 213       if (tmp != EE_NIL) {
3841  0059 04a505            	ibne	x,LC001
3842  005c 8cffff            	cpd	#-1
3843  005f 277d              	beq	L3003
3844  0061                   LC001:
3845                         ; 214 	if (EE_sys_ceiling < EE_th_ready_prio[tmp]) {
3847  0061 59                	lsld	
3848  0062 b746              	tfr	d,y
3849  0064 ecea0000          	ldd	_EE_th_ready_prio,y
3850  0068 bc0000            	cpd	_EE_sys_ceiling
3851  006b 2371              	bls	L3003
3852                         ; 62     return EE_stkfirst;  
3855  006d fc0002            	ldd	_EE_stkfirst+2
3856  0070 6c8c              	std	OFST-4,s
3857  0072 fe0000            	ldx	_EE_stkfirst
3858  0075 6e8a              	stx	OFST-6,s
3860                         ; 63 }
3862                         ; 218 	  if (tmp_stacked != EE_NIL) {
3864  0077 04a503            	ibne	x,LC002
3865  007a 04840b            	ibeq	d,L3103
3866  007d                   LC002:
3867                         ; 223 	    EE_th_status[tmp_stacked] = READY;
3869  007d cc0002            	ldd	#2
3870  0080 ed8c              	ldy	OFST-4,s
3871  0082 1858              	lsly	
3872  0084 6cea0000          	std	_EE_th_status,y
3873  0088                   L3103:
3874                         ; 227 	  EE_th_status[tmp] = RUNNING;
3876  0088 ed88              	ldy	OFST-8,s
3877  008a 1858              	lsly	
3878  008c 1869ea0000        	clrw	_EE_th_status,y
3879                         ; 229 	  EE_sys_ceiling |= EE_th_dispatch_prio[tmp];
3881  0091 edea0000          	ldy	_EE_th_dispatch_prio,y
3882  0095 18fa0000          	ory	_EE_sys_ceiling
3883  0099 7d0000            	sty	_EE_sys_ceiling
3884                         ; 236 	  tmp = EE_rq2stk_exchange();
3886  009c 4a000000          	call	f_EE_rq2stk_exchange
3888  00a0 6c88              	std	OFST-8,s
3889  00a2 6e86              	stx	OFST-10,s
3890                         ; 237 	  if (EE_th_waswaiting[tmp]) {
3892  00a4 b746              	tfr	d,y
3893  00a6 1858              	lsly	
3894  00a8 18e7ea0000        	tstw	_EE_th_waswaiting,y
3895  00ad 270f              	beq	L5103
3896                         ; 238 	    EE_th_waswaiting[tmp] = 0;
3898  00af 1869ea0000        	clrw	_EE_th_waswaiting,y
3899                         ; 192     EE_s12xs_hal_stkchange(EE_s12xs_thread_tos[thread+1]);
3902  00b4 ecea0002          	ldd	_EE_s12xs_thread_tos+2,y
3903  00b8 4a000000          	call	f_EE_s12xs_hal_stkchange
3905  00bc 2020              	bra	L3003
3906  00be                   L5103:
3907                         ; 194 }
3910  00be b746              	tfr	d,y
3911  00c0 6d8c              	sty	OFST-4,s
3912  00c2 6e8a              	stx	OFST-6,s
3913                         ; 141     EE_s12xs_hal_ready2stacked(EE_hal_thread_body[thread],
3913                         ; 142 			         EE_s12xs_thread_tos[thread+1]);
3915  00c4 1858              	lsly	
3916  00c6 ecea0002          	ldd	_EE_s12xs_thread_tos+2,y
3917  00ca 3b                	pshd	
3918  00cb cd0000            	ldy	#_EE_hal_thread_body
3919  00ce ec8e              	ldd	OFST-2,s
3920  00d0 59                	lsld	
3921  00d1 59                	lsld	
3922  00d2 19ee              	leay	d,y
3923  00d4 ec42              	ldd	2,y
3924  00d6 ee40              	ldx	0,y
3925  00d8 4a000000          	call	f_EE_s12xs_hal_ready2stacked
3927  00dc 1b82              	leas	2,s
3928  00de                   L3003:
3929                         ; 111   if(f & 0x10) 						// restore I bit
3932  00de 0f8f1004          	brclr	OFST-1,s,16,L1303
3933                         ; 200   ASM_DIS_INT;
3936  00e2 1410              	sei	
3938  00e4 2002              	bra	L7272
3939  00e6                   L1303:
3940                         ; 191   ASM_EN_INT;
3943  00e6 10ef              	cli	
3945  00e8                   L7272:
3946                         ; 263 }
3950  00e8 1bf014            	leas	20,s
3951  00eb 0a                	rtc	
3963                         	xref	f_EE_rq2stk_exchange
3964                         	xref	f_EE_rq_insert
3965                         	xref	f_EE_rq_queryfirst
3966                         	xref	_EE_pit0_initialized
3967                         	xref	_EE_ApplicationMode
3968                         	xref	_EE_oo_IRQ_disable_count
3969                         	xdef	f_EE_oo_SetEvent
3970                         	xref	_EE_oo_ErrorHook_data
3971                         	xref	_EE_oo_ErrorHook_ServiceID
3972                         	xref	_EE_th_waswaiting
3973                         	xref	_EE_th_event_waitmask
3974                         	xref	_EE_th_event_active
3975                         	xref	_EE_sys_ceiling
3976                         	xref	_EE_stkfirst
3977                         	xref	_EE_th_dispatch_prio
3978                         	xref	_EE_th_ready_prio
3979                         	xref	_EE_th_next
3980                         	xref	_EE_th_status
3981                         	xref	_EE_buttons_initialized
3982                         	xref	f_EE_s12xs_terminate_task
3983                         	xref	f_EE_s12xs_terminate_savestk
3984                         	xref	_EE_IRQ_nesting_level
3985                         	xref	f_EE_s12xs_hal_stkchange
3986                         	xref	f_EE_s12xs_hal_ready2stacked
3987                         	xref	_EE_hal_endcycle_next_tos
3988                         	xref	_EE_hal_endcycle_next_thread
3989                         	xref	_EE_terminate_real_th_body
3990                         	xref	_EE_terminate_data
3991                         	xref	_EE_s12xs_thread_tos
3992                         	xref	_EE_hal_thread_body
4012                         	end
