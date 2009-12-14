   1                         ; C Compiler for S12X [COSMIC Software].
   2                         ; Generator (Limited) V4.7.11.2 - 16 Mar 2009
   3                         ; Optimizer V4.6.16 - 02 Dec 2008
3756                         ; 49 void EE_thread_end_instance(void)
3756                         ; 50 {
3757                         .ftext:	section	.text
3758  0000                   f_EE_thread_end_instance:
3760  0000 1b98              	leas	-8,s
3761       00000008          OFST:	set	8
3764                         ; 62     return EE_stkfirst;  
3767  0002 fd0002            	ldy	_EE_stkfirst+2
3768  0005 6d86              	sty	OFST-2,s
3770                         ; 63 }
3774  0007 1858              	lsly	
3775  0009 1862ea0000        	incw	_EE_th_rnact,y
3776                         ; 68     EE_th_status[current] = SUSPENDED;
3778  000e cc0003            	ldd	#3
3779  0011 ed86              	ldy	OFST-2,s
3780  0013 1858              	lsly	
3781  0015 6cea0000          	std	_EE_th_status,y
3782                         ; 71     EE_sys_ceiling &= ~EE_th_dispatch_prio[current];
3784  0019 eeea0000          	ldx	_EE_th_dispatch_prio,y
3785  001d 1841              	comx	
3786  001f 18b40000          	andx	_EE_sys_ceiling
3787  0023 7e0000            	stx	_EE_sys_ceiling
3788                         ; 109     EE_stkfirst = EE_th_next[EE_stkfirst];
3791  0026 cd0000            	ldy	#_EE_th_next
3792  0029 fc0002            	ldd	_EE_stkfirst+2
3793  002c 59                	lsld	
3794  002d 59                	lsld	
3795  002e 19ee              	leay	d,y
3796  0030 1805420002        	movw	2,y,_EE_stkfirst+2
3797  0035 1805400000        	movw	0,y,_EE_stkfirst
3798                         ; 84     TaskID = EE_th_terminate_nextask[current];
3801  003a cd0000            	ldy	#_EE_th_terminate_nextask
3802  003d ec86              	ldd	OFST-2,s
3803  003f 59                	lsld	
3804  0040 59                	lsld	
3805  0041 19ee              	leay	d,y
3806  0043 18024286          	movw	2,y,OFST-2,s
3807  0047 ec40              	ldd	0,y
3808  0049 6c84              	std	OFST-4,s
3809                         ; 85     if (TaskID != EE_NIL) {
3811  004b 04a405            	ibne	d,LC001
3812  004e ec86              	ldd	OFST-2,s
3813  0050 048421            	ibeq	d,L5772
3814  0053                   LC001:
3815                         ; 94       if (EE_th_status[TaskID] == SUSPENDED) {
3817  0053 ed86              	ldy	OFST-2,s
3818  0055 1858              	lsly	
3819  0057 ecea0000          	ldd	_EE_th_status,y
3820  005b 8c0003            	cpd	#3
3821  005e 260c              	bne	L7772
3822                         ; 95 	EE_th_status[TaskID] = READY;
3824  0060 cc0002            	ldd	#2
3825  0063 6cea0000          	std	_EE_th_status,y
3826                         ; 99 	EE_th_event_active[TaskID] = 0;
3828  0067 1869ea0000        	clrw	_EE_th_event_active,y
3829  006c                   L7772:
3830                         ; 111       EE_rq_insert(TaskID);
3832  006c ec86              	ldd	OFST-2,s
3833  006e ee84              	ldx	OFST-4,s
3834  0070 4a000000          	call	f_EE_rq_insert
3836  0074                   L5772:
3837                         ; 117     rqfirst = EE_rq_queryfirst();
3839  0074 4a000000          	call	f_EE_rq_queryfirst
3841  0078 6c86              	std	OFST-2,s
3842  007a 6e84              	stx	OFST-4,s
3843                         ; 118     if (rqfirst == EE_NIL) {
3845  007c 04a51b            	ibne	x,L1003
3846  007f 8cffff            	cpd	#-1
3847  0082 2616              	bne	L1003
3848                         ; 62     return EE_stkfirst;  
3851  0084 fd0002            	ldy	_EE_stkfirst+2
3852  0087 6d86              	sty	OFST-2,s
3853  0089 fc0000            	ldd	_EE_stkfirst
3854  008c 6c84              	std	OFST-4,s
3856                         ; 63 }
3858  008e 8cffff            	cpd	#-1
3859  0091 2616              	bne	LC005
3860  0093 8dffff            	cpy	#-1
3861  0096 271b              	beq	LC004
3862                         ; 62     return EE_stkfirst;  
3866                         ; 63 }
3868                         ; 62     return EE_stkfirst;  
3872                         ; 159   EE_hal_endcycle_next_tos = EE_s12xs_thread_tos[thread+1];
3875                         ; 160   EE_hal_endcycle_next_thread = 0;
3877  0098 200f              	bra	LC005
3878  009a                   L1003:
3879                         ; 128     else if (EE_sys_ceiling >= EE_th_ready_prio[rqfirst]) {
3881  009a 59                	lsld	
3882  009b b746              	tfr	d,y
3883  009d ecea0000          	ldd	_EE_th_ready_prio,y
3884  00a1 bc0000            	cpd	_EE_sys_ceiling
3885  00a4 2218              	bhi	L7003
3886                         ; 62     return EE_stkfirst;  
3889  00a6 fd0002            	ldy	_EE_stkfirst+2
3891                         ; 63 }
3893                         ; 62     return EE_stkfirst;  
3896  00a9                   LC005:
3897  00a9 1858              	lsly	
3898  00ab 1869ea0000        	clrw	_EE_th_status,y
3899  00b0 fd0002            	ldy	_EE_stkfirst+2
3901                         ; 159   EE_hal_endcycle_next_tos = EE_s12xs_thread_tos[thread+1];
3904  00b3                   LC004:
3905  00b3 6d86              	sty	OFST-2,s
3906  00b5 1801840000        	movw	_EE_stkfirst,OFST-4,s
3907  00ba 1858              	lsly	
3908                         ; 160   EE_hal_endcycle_next_thread = 0;
3910  00bc 202b              	bra	LC003
3911  00be                   L7003:
3912                         ; 139 	EE_th_status[rqfirst] = RUNNING;
3914  00be ed86              	ldy	OFST-2,s
3915  00c0 1858              	lsly	
3916  00c2 1869ea0000        	clrw	_EE_th_status,y
3917                         ; 140 	EE_sys_ceiling |= EE_th_dispatch_prio[rqfirst];
3919  00c7 edea0000          	ldy	_EE_th_dispatch_prio,y
3920  00cb 18fa0000          	ory	_EE_sys_ceiling
3921  00cf 7d0000            	sty	_EE_sys_ceiling
3922                         ; 148 	rqfirst = EE_rq2stk_exchange();
3924  00d2 4a000000          	call	f_EE_rq2stk_exchange
3926  00d6 6c86              	std	OFST-2,s
3927  00d8 6e84              	stx	OFST-4,s
3928                         ; 149 	if (EE_th_waswaiting[rqfirst]) {
3930  00da b746              	tfr	d,y
3931  00dc 1858              	lsly	
3932  00de eeea0000          	ldx	_EE_th_waswaiting,y
3933  00e2 2716              	beq	L3103
3934                         ; 150 	  EE_th_waswaiting[rqfirst] = 0;
3936  00e4 1869ea0000        	clrw	_EE_th_waswaiting,y
3937                         ; 159   EE_hal_endcycle_next_tos = EE_s12xs_thread_tos[thread+1];
3940                         ; 160   EE_hal_endcycle_next_thread = 0;
3942  00e9                   LC003:
3943  00e9 1805ea00020000    	movw	_EE_s12xs_thread_tos+2,y,_EE_hal_endcycle_next_tos
3944  00f0 87                	clra	
3945  00f1 c7                	clrb	
3946  00f2 7c0000            	std	_EE_hal_endcycle_next_thread
3947  00f5 7c0002            	std	_EE_hal_endcycle_next_thread+2
3948  00f8 201d              	bra	L5003
3949  00fa                   L3103:
3950                         ; 176   EE_hal_endcycle_next_tos = EE_s12xs_thread_tos[thread+1];
3953  00fa 59                	lsld	
3954  00fb b746              	tfr	d,y
3955  00fd 1805ea00020000    	movw	_EE_s12xs_thread_tos+2,y,_EE_hal_endcycle_next_tos
3956                         ; 177   EE_hal_endcycle_next_thread = EE_hal_thread_body[thread];
3958  0104 cd0000            	ldy	#_EE_hal_thread_body
3959  0107 ec86              	ldd	OFST-2,s
3960  0109 59                	lsld	
3961  010a 59                	lsld	
3962  010b 19ee              	leay	d,y
3963  010d 1805420002        	movw	2,y,_EE_hal_endcycle_next_thread+2
3964  0112 1805400000        	movw	0,y,_EE_hal_endcycle_next_thread
3965  0117                   L5003:
3966                         ; 164 }  
3969  0117 1b88              	leas	8,s
3970  0119 0a                	rtc	
3982                         	xdef	f_EE_thread_end_instance
3983                         	xref	f_EE_rq2stk_exchange
3984                         	xref	f_EE_rq_insert
3985                         	xref	f_EE_rq_queryfirst
3986                         	xref	_EE_pit0_initialized
3987                         	xref	_EE_ApplicationMode
3988                         	xref	_EE_oo_IRQ_disable_count
3989                         	xref	_EE_oo_ErrorHook_data
3990                         	xref	_EE_oo_ErrorHook_ServiceID
3991                         	xref	_EE_th_waswaiting
3992                         	xref	_EE_th_event_active
3993                         	xref	_EE_sys_ceiling
3994                         	xref	_EE_stkfirst
3995                         	xref	_EE_th_terminate_nextask
3996                         	xref	_EE_th_rnact
3997                         	xref	_EE_th_dispatch_prio
3998                         	xref	_EE_th_ready_prio
3999                         	xref	_EE_th_next
4000                         	xref	_EE_th_status
4001                         	xref	_EE_buttons_initialized
4002                         	xref	f_EE_s12xs_terminate_task
4003                         	xref	f_EE_s12xs_terminate_savestk
4004                         	xref	_EE_IRQ_nesting_level
4005                         	xref	f_EE_s12xs_hal_stkchange
4006                         	xref	f_EE_s12xs_hal_ready2stacked
4007                         	xref	_EE_hal_endcycle_next_tos
4008                         	xref	_EE_hal_endcycle_next_thread
4009                         	xref	_EE_terminate_real_th_body
4010                         	xref	_EE_terminate_data
4011                         	xref	_EE_s12xs_thread_tos
4012                         	xref	_EE_hal_thread_body
4032                         	end
