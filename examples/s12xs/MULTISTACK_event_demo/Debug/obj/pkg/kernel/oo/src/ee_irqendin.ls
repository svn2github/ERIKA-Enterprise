   1                         ; C Compiler for S12X [COSMIC Software].
   2                         ; Generator (Limited) V4.7.11.2 - 16 Mar 2009
   3                         ; Optimizer V4.6.16 - 02 Dec 2008
3733                         ; 56 void EE_IRQ_end_instance(void)
3733                         ; 57 {
3734                         .ftext:	section	.text
3735  0000                   f_EE_IRQ_end_instance:
3737  0000 1b94              	leas	-12,s
3738       0000000c          OFST:	set	12
3741                         ; 61   tmp = EE_rq_queryfirst();
3743  0002 4a000000          	call	f_EE_rq_queryfirst
3745  0006 6c86              	std	OFST-6,s
3746  0008 6e84              	stx	OFST-8,s
3747                         ; 62     return EE_stkfirst;  
3750  000a 18018a0002        	movw	_EE_stkfirst+2,OFST-2,s
3751  000f fe0000            	ldx	_EE_stkfirst
3752  0012 6e88              	stx	OFST-4,s
3754                         ; 63 }
3756                         ; 64   if (tmp != EE_NIL && EE_sys_ceiling < EE_th_ready_prio[tmp]) {
3758  0014 ec84              	ldd	OFST-8,s
3759  0016 04a407            	ibne	d,LC001
3760  0019 ec86              	ldd	OFST-6,s
3761  001b 8cffff            	cpd	#-1
3762  001e 2772              	beq	L1572
3763  0020                   LC001:
3765  0020 ed86              	ldy	OFST-6,s
3766  0022 1858              	lsly	
3767  0024 ecea0000          	ldd	_EE_th_ready_prio,y
3768  0028 bc0000            	cpd	_EE_sys_ceiling
3769  002b 2365              	bls	L1572
3770                         ; 67       if (tmp_stacked != EE_NIL) {
3772  002d 04a505            	ibne	x,LC002
3773  0030 ec8a              	ldd	OFST-2,s
3774  0032 04840b            	ibeq	d,L3572
3775  0035                   LC002:
3776                         ; 73 	EE_th_status[tmp_stacked] = READY;
3778  0035 cc0002            	ldd	#2
3779  0038 ed8a              	ldy	OFST-2,s
3780  003a 1858              	lsly	
3781  003c 6cea0000          	std	_EE_th_status,y
3782  0040                   L3572:
3783                         ; 77       EE_th_status[tmp] = RUNNING;
3785  0040 ed86              	ldy	OFST-6,s
3786  0042 1858              	lsly	
3787  0044 1869ea0000        	clrw	_EE_th_status,y
3788                         ; 79       EE_sys_ceiling |= EE_th_dispatch_prio[tmp];
3790  0049 edea0000          	ldy	_EE_th_dispatch_prio,y
3791  004d 18fa0000          	ory	_EE_sys_ceiling
3792  0051 7d0000            	sty	_EE_sys_ceiling
3793                         ; 86       tmp = EE_rq2stk_exchange();
3795  0054 4a000000          	call	f_EE_rq2stk_exchange
3797  0058 6c86              	std	OFST-6,s
3798  005a 6e84              	stx	OFST-8,s
3799                         ; 87       if (EE_th_waswaiting[tmp]) {
3801  005c b746              	tfr	d,y
3802  005e 1858              	lsly	
3803  0060 18e7ea0000        	tstw	_EE_th_waswaiting,y
3804  0065 2707              	beq	L5572
3805                         ; 88 	EE_th_waswaiting[tmp] = 0;
3807  0067 1869ea0000        	clrw	_EE_th_waswaiting,y
3808                         ; 159   EE_hal_endcycle_next_tos = EE_s12xs_thread_tos[thread+1];
3811                         ; 160   EE_hal_endcycle_next_thread = 0;
3813  006c 2029              	bra	LC003
3814  006e                   L5572:
3815                         ; 161 }
3818  006e b746              	tfr	d,y
3819  0070 6d8a              	sty	OFST-2,s
3820  0072 6e88              	stx	OFST-4,s
3821                         ; 176   EE_hal_endcycle_next_tos = EE_s12xs_thread_tos[thread+1];
3823  0074 1858              	lsly	
3824  0076 1805ea00020000    	movw	_EE_s12xs_thread_tos+2,y,_EE_hal_endcycle_next_tos
3825                         ; 177   EE_hal_endcycle_next_thread = EE_hal_thread_body[thread];
3827  007d cd0000            	ldy	#_EE_hal_thread_body
3828  0080 ec8a              	ldd	OFST-2,s
3829  0082 59                	lsld	
3830  0083 59                	lsld	
3831  0084 19ee              	leay	d,y
3832  0086 1805420002        	movw	2,y,_EE_hal_endcycle_next_thread+2
3833  008b 1805400000        	movw	0,y,_EE_hal_endcycle_next_thread
3834  0090 2014              	bra	L1672
3835  0092                   L1572:
3836                         ; 62     return EE_stkfirst;  
3839  0092 fd0002            	ldy	_EE_stkfirst+2
3841                         ; 159   EE_hal_endcycle_next_tos = EE_s12xs_thread_tos[thread+1];
3844  0095 1858              	lsly	
3845                         ; 160   EE_hal_endcycle_next_thread = 0;
3847  0097                   LC003:
3848  0097 1805ea00020000    	movw	_EE_s12xs_thread_tos+2,y,_EE_hal_endcycle_next_tos
3849  009e 87                	clra	
3850  009f c7                	clrb	
3851  00a0 7c0000            	std	_EE_hal_endcycle_next_thread
3852  00a3 7c0002            	std	_EE_hal_endcycle_next_thread+2
3853  00a6                   L1672:
3854                         ; 102 }
3857  00a6 1b8c              	leas	12,s
3858  00a8 0a                	rtc	
3870                         	xdef	f_EE_IRQ_end_instance
3871                         	xref	f_EE_rq2stk_exchange
3872                         	xref	f_EE_rq_queryfirst
3873                         	xref	_EE_pit0_initialized
3874                         	xref	_EE_ApplicationMode
3875                         	xref	_EE_oo_IRQ_disable_count
3876                         	xref	_EE_oo_ErrorHook_data
3877                         	xref	_EE_oo_ErrorHook_ServiceID
3878                         	xref	_EE_th_waswaiting
3879                         	xref	_EE_sys_ceiling
3880                         	xref	_EE_stkfirst
3881                         	xref	_EE_th_dispatch_prio
3882                         	xref	_EE_th_ready_prio
3883                         	xref	_EE_th_next
3884                         	xref	_EE_th_status
3885                         	xref	_EE_buttons_initialized
3886                         	xref	f_EE_s12xs_terminate_task
3887                         	xref	f_EE_s12xs_terminate_savestk
3888                         	xref	_EE_IRQ_nesting_level
3889                         	xref	f_EE_s12xs_hal_stkchange
3890                         	xref	f_EE_s12xs_hal_ready2stacked
3891                         	xref	_EE_hal_endcycle_next_tos
3892                         	xref	_EE_hal_endcycle_next_thread
3893                         	xref	_EE_terminate_real_th_body
3894                         	xref	_EE_terminate_data
3895                         	xref	_EE_s12xs_thread_tos
3896                         	xref	_EE_hal_thread_body
3916                         	end
