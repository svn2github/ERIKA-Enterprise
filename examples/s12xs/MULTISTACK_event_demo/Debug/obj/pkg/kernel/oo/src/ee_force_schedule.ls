   1                         ; C Compiler for S12X [COSMIC Software].
   2                         ; Generator (Limited) V4.7.11.2 - 16 Mar 2009
   3                         ; Optimizer V4.6.16 - 02 Dec 2008
3731                         ; 74 void EE_oo_ForceSchedule(void)
3731                         ; 75 #endif
3731                         ; 76 {
3732                         .ftext:	section	.text
3733  0000                   f_EE_oo_ForceSchedule:
3735  0000 1b94              	leas	-12,s
3736       0000000c          OFST:	set	12
3739                         ; 200   ASM_DIS_INT;
3742  0002 1410              	sei	
3744                         ; 62     return EE_stkfirst;  
3748  0004 18018a0002        	movw	_EE_stkfirst+2,OFST-2,s
3749  0009 fe0000            	ldx	_EE_stkfirst
3750  000c 6e88              	stx	OFST-4,s
3752                         ; 63 }
3754                         ; 117   rq = EE_rq_queryfirst();
3756  000e 4a000000          	call	f_EE_rq_queryfirst
3758  0012 6c86              	std	OFST-6,s
3759  0014 6e84              	stx	OFST-8,s
3760                         ; 118   if (rq != EE_NIL) {
3762  0016 04a505            	ibne	x,LC001
3763  0019 8cffff            	cpd	#-1
3764  001c 2775              	beq	L5772
3765  001e                   LC001:
3766                         ; 121     if (EE_sys_ceiling < EE_th_ready_prio[rq]) {
3768  001e 59                	lsld	
3769  001f b746              	tfr	d,y
3770  0021 ecea0000          	ldd	_EE_th_ready_prio,y
3771  0025 bc0000            	cpd	_EE_sys_ceiling
3772  0028 2369              	bls	L5772
3773                         ; 122       if (current != EE_NIL) { 
3775  002a ec88              	ldd	OFST-4,s
3776  002c 04a405            	ibne	d,LC002
3777  002f ec8a              	ldd	OFST-2,s
3778  0031 04840b            	ibeq	d,L7672
3779  0034                   LC002:
3780                         ; 127 	EE_th_status[current] = READY;
3782  0034 cc0002            	ldd	#2
3783  0037 ed8a              	ldy	OFST-2,s
3784  0039 1858              	lsly	
3785  003b 6cea0000          	std	_EE_th_status,y
3786  003f                   L7672:
3787                         ; 134       EE_sys_ceiling |= EE_th_dispatch_prio[rq];
3789  003f ed86              	ldy	OFST-6,s
3790  0041 1858              	lsly	
3791  0043 edea0000          	ldy	_EE_th_dispatch_prio,y
3792  0047 18fa0000          	ory	_EE_sys_ceiling
3793  004b 7d0000            	sty	_EE_sys_ceiling
3794                         ; 136       EE_th_status[rq] = RUNNING;
3796  004e ed86              	ldy	OFST-6,s
3797  0050 1858              	lsly	
3798  0052 1869ea0000        	clrw	_EE_th_status,y
3799                         ; 143       rq = EE_rq2stk_exchange();
3801  0057 4a000000          	call	f_EE_rq2stk_exchange
3803  005b 6c86              	std	OFST-6,s
3804  005d 6e84              	stx	OFST-8,s
3805                         ; 144       if (EE_th_waswaiting[rq]) {
3807  005f b746              	tfr	d,y
3808  0061 1858              	lsly	
3809  0063 eeea0000          	ldx	_EE_th_waswaiting,y
3810  0067 270f              	beq	L1772
3811                         ; 145 	EE_th_waswaiting[rq] = 0;
3813  0069 1869ea0000        	clrw	_EE_th_waswaiting,y
3814                         ; 192     EE_s12xs_hal_stkchange(EE_s12xs_thread_tos[thread+1]);
3817  006e ecea0002          	ldd	_EE_s12xs_thread_tos+2,y
3818  0072 4a000000          	call	f_EE_s12xs_hal_stkchange
3820  0076 201b              	bra	L5772
3821  0078                   L1772:
3822                         ; 141     EE_s12xs_hal_ready2stacked(EE_hal_thread_body[thread],
3822                         ; 142 			         EE_s12xs_thread_tos[thread+1]);
3825  0078 59                	lsld	
3826  0079 b746              	tfr	d,y
3827  007b ecea0002          	ldd	_EE_s12xs_thread_tos+2,y
3828  007f 3b                	pshd	
3829  0080 cd0000            	ldy	#_EE_hal_thread_body
3830  0083 ec88              	ldd	OFST-4,s
3831  0085 59                	lsld	
3832  0086 59                	lsld	
3833  0087 19ee              	leay	d,y
3834  0089 ec42              	ldd	2,y
3835  008b ee40              	ldx	0,y
3836  008d 4a000000          	call	f_EE_s12xs_hal_ready2stacked
3838  0091 1b82              	leas	2,s
3839  0093                   L5772:
3840                         ; 191   ASM_EN_INT;
3843  0093 10ef              	cli	
3845                         ; 170 }
3849  0095 1b8c              	leas	12,s
3850  0097 0a                	rtc	
3862                         	xref	f_EE_rq2stk_exchange
3863                         	xref	f_EE_rq_queryfirst
3864                         	xref	_EE_pit0_initialized
3865                         	xref	_EE_ApplicationMode
3866                         	xref	_EE_oo_IRQ_disable_count
3867                         	xdef	f_EE_oo_ForceSchedule
3868                         	xref	_EE_oo_ErrorHook_data
3869                         	xref	_EE_oo_ErrorHook_ServiceID
3870                         	xref	_EE_th_waswaiting
3871                         	xref	_EE_sys_ceiling
3872                         	xref	_EE_stkfirst
3873                         	xref	_EE_th_dispatch_prio
3874                         	xref	_EE_th_ready_prio
3875                         	xref	_EE_th_next
3876                         	xref	_EE_th_status
3877                         	xref	_EE_buttons_initialized
3878                         	xref	f_EE_s12xs_terminate_task
3879                         	xref	f_EE_s12xs_terminate_savestk
3880                         	xref	_EE_IRQ_nesting_level
3881                         	xref	f_EE_s12xs_hal_stkchange
3882                         	xref	f_EE_s12xs_hal_ready2stacked
3883                         	xref	_EE_hal_endcycle_next_tos
3884                         	xref	_EE_hal_endcycle_next_thread
3885                         	xref	_EE_terminate_real_th_body
3886                         	xref	_EE_terminate_data
3887                         	xref	_EE_s12xs_thread_tos
3888                         	xref	_EE_hal_thread_body
3908                         	end
