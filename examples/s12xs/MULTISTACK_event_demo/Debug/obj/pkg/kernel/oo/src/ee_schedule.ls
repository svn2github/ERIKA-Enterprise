   1                         ; C Compiler for S12X [COSMIC Software].
   2                         ; Generator (Limited) V4.7.11.2 - 16 Mar 2009
   3                         ; Optimizer V4.6.16 - 02 Dec 2008
3729                         ; 64 void EE_oo_Schedule(void)
3729                         ; 65 #endif
3729                         ; 66 {
3730                         .ftext:	section	.text
3731  0000                   f_EE_oo_Schedule:
3733  0000 1b94              	leas	-12,s
3734       0000000c          OFST:	set	12
3737                         ; 62     return EE_stkfirst;  
3740  0002 18018a0002        	movw	_EE_stkfirst+2,OFST-2,s
3741  0007 fe0000            	ldx	_EE_stkfirst
3742  000a 6e88              	stx	OFST-4,s
3744                         ; 63 }
3746                         ; 200   ASM_DIS_INT;
3749  000c 1410              	sei	
3751                         ; 139   rq = EE_rq_queryfirst();
3754  000e 4a000000          	call	f_EE_rq_queryfirst
3756  0012 6c86              	std	OFST-6,s
3757  0014 6e84              	stx	OFST-8,s
3758                         ; 140   if (rq != EE_NIL) {
3760  0016 04a507            	ibne	x,LC001
3761  0019 8cffff            	cpd	#-1
3762  001c 182700ab          	beq	L3772
3763  0020                   LC001:
3764                         ; 147     if (EE_th_ready_prio[current] < EE_th_ready_prio[rq]) {
3766  0020 ed8a              	ldy	OFST-2,s
3767  0022 1858              	lsly	
3768  0024 ecea0000          	ldd	_EE_th_ready_prio,y
3769  0028 ed86              	ldy	OFST-6,s
3770  002a 1858              	lsly	
3771  002c acea0000          	cpd	_EE_th_ready_prio,y
3772  0030 18240097          	bhs	L3772
3773                         ; 152       EE_sys_ceiling &= ~EE_th_dispatch_prio[current];
3775  0034 ed8a              	ldy	OFST-2,s
3776  0036 1858              	lsly	
3777  0038 eeea0000          	ldx	_EE_th_dispatch_prio,y
3778  003c 1841              	comx	
3779  003e 18b40000          	andx	_EE_sys_ceiling
3780  0042 7e0000            	stx	_EE_sys_ceiling
3781                         ; 165       EE_sys_ceiling |= EE_th_ready_prio[current];
3783  0045 edea0000          	ldy	_EE_th_ready_prio,y
3784  0049 18fa0000          	ory	_EE_sys_ceiling
3785  004d 7d0000            	sty	_EE_sys_ceiling
3786                         ; 168       EE_th_status[current] = READY;
3788  0050 cc0002            	ldd	#2
3789  0053 ed8a              	ldy	OFST-2,s
3790  0055 1858              	lsly	
3791  0057 6cea0000          	std	_EE_th_status,y
3792                         ; 174       EE_sys_ceiling |= EE_th_dispatch_prio[rq];
3794  005b ed86              	ldy	OFST-6,s
3795  005d 1858              	lsly	
3796  005f edea0000          	ldy	_EE_th_dispatch_prio,y
3797  0063 18fa0000          	ory	_EE_sys_ceiling
3798  0067 7d0000            	sty	_EE_sys_ceiling
3799                         ; 176       EE_th_status[rq] = RUNNING;
3801  006a ed86              	ldy	OFST-6,s
3802  006c 1858              	lsly	
3803  006e 1869ea0000        	clrw	_EE_th_status,y
3804                         ; 184       rq = EE_rq2stk_exchange();
3806  0073 4a000000          	call	f_EE_rq2stk_exchange
3808  0077 6c86              	std	OFST-6,s
3809  0079 6e84              	stx	OFST-8,s
3810                         ; 185       if (EE_th_waswaiting[rq]) {
3812  007b b746              	tfr	d,y
3813  007d 1858              	lsly	
3814  007f eeea0000          	ldx	_EE_th_waswaiting,y
3815  0083 270f              	beq	L7672
3816                         ; 186 	EE_th_waswaiting[rq] = 0;
3818  0085 1869ea0000        	clrw	_EE_th_waswaiting,y
3819                         ; 192     EE_s12xs_hal_stkchange(EE_s12xs_thread_tos[thread+1]);
3822  008a ecea0002          	ldd	_EE_s12xs_thread_tos+2,y
3823  008e 4a000000          	call	f_EE_s12xs_hal_stkchange
3825  0092 201b              	bra	L1772
3826  0094                   L7672:
3827                         ; 141     EE_s12xs_hal_ready2stacked(EE_hal_thread_body[thread],
3827                         ; 142 			         EE_s12xs_thread_tos[thread+1]);
3830  0094 59                	lsld	
3831  0095 b746              	tfr	d,y
3832  0097 ecea0002          	ldd	_EE_s12xs_thread_tos+2,y
3833  009b 3b                	pshd	
3834  009c cd0000            	ldy	#_EE_hal_thread_body
3835  009f ec88              	ldd	OFST-4,s
3836  00a1 59                	lsld	
3837  00a2 59                	lsld	
3838  00a3 19ee              	leay	d,y
3839  00a5 ec42              	ldd	2,y
3840  00a7 ee40              	ldx	0,y
3841  00a9 4a000000          	call	f_EE_s12xs_hal_ready2stacked
3843  00ad 1b82              	leas	2,s
3844  00af                   L1772:
3845                         ; 196       EE_sys_ceiling &= ~EE_th_ready_prio[current];
3847  00af ed8a              	ldy	OFST-2,s
3848  00b1 1858              	lsly	
3849  00b3 eeea0000          	ldx	_EE_th_ready_prio,y
3850  00b7 1841              	comx	
3851  00b9 18b40000          	andx	_EE_sys_ceiling
3852  00bd 7e0000            	stx	_EE_sys_ceiling
3853                         ; 198       EE_sys_ceiling |= EE_th_dispatch_prio[current];
3855  00c0 edea0000          	ldy	_EE_th_dispatch_prio,y
3856  00c4 18fa0000          	ory	_EE_sys_ceiling
3857  00c8 7d0000            	sty	_EE_sys_ceiling
3858  00cb                   L3772:
3859                         ; 191   ASM_EN_INT;
3862  00cb 10ef              	cli	
3864                         ; 220 }
3868  00cd 1b8c              	leas	12,s
3869  00cf 0a                	rtc	
3881                         	xref	f_EE_rq2stk_exchange
3882                         	xref	f_EE_rq_queryfirst
3883                         	xref	_EE_pit0_initialized
3884                         	xref	_EE_ApplicationMode
3885                         	xref	_EE_oo_IRQ_disable_count
3886                         	xdef	f_EE_oo_Schedule
3887                         	xref	_EE_oo_ErrorHook_data
3888                         	xref	_EE_oo_ErrorHook_ServiceID
3889                         	xref	_EE_th_waswaiting
3890                         	xref	_EE_sys_ceiling
3891                         	xref	_EE_stkfirst
3892                         	xref	_EE_th_dispatch_prio
3893                         	xref	_EE_th_ready_prio
3894                         	xref	_EE_th_next
3895                         	xref	_EE_th_status
3896                         	xref	_EE_buttons_initialized
3897                         	xref	f_EE_s12xs_terminate_task
3898                         	xref	f_EE_s12xs_terminate_savestk
3899                         	xref	_EE_IRQ_nesting_level
3900                         	xref	f_EE_s12xs_hal_stkchange
3901                         	xref	f_EE_s12xs_hal_ready2stacked
3902                         	xref	_EE_hal_endcycle_next_tos
3903                         	xref	_EE_hal_endcycle_next_thread
3904                         	xref	_EE_terminate_real_th_body
3905                         	xref	_EE_terminate_data
3906                         	xref	_EE_s12xs_thread_tos
3907                         	xref	_EE_hal_thread_body
3927                         	end
