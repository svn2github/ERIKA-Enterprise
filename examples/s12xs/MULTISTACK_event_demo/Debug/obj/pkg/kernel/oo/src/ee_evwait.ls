   1                         ; C Compiler for S12X [COSMIC Software].
   2                         ; Generator (Limited) V4.7.11.2 - 16 Mar 2009
   3                         ; Optimizer V4.6.16 - 02 Dec 2008
3748                         ; 65 void EE_oo_WaitEvent(EventMaskType Mask)
3748                         ; 66 #endif
3748                         ; 67 {
3749                         .ftext:	section	.text
3750  0000                   f_EE_oo_WaitEvent:
3752  0000 3b                	pshd	
3753  0001 1b94              	leas	-12,s
3754       0000000c          OFST:	set	12
3757                         ; 62     return EE_stkfirst;  
3760  0003 fd0002            	ldy	_EE_stkfirst+2
3761  0006 6d8a              	sty	OFST-2,s
3762  0008 fe0000            	ldx	_EE_stkfirst
3763  000b 6e88              	stx	OFST-4,s
3765                         ; 63 }
3767                         ; 200   ASM_DIS_INT;
3770  000d 1410              	sei	
3772                         ; 167   if (!(EE_th_event_active[current] & Mask)) {
3775  000f 1858              	lsly	
3776  0011 eeea0000          	ldx	_EE_th_event_active,y
3777  0015 18a48c            	andx	OFST+0,s
3778  0018 182600d4          	bne	L5103
3779                         ; 173     EE_th_event_waitmask[current] = Mask;
3781  001c ed8a              	ldy	OFST-2,s
3782  001e 1858              	lsly	
3783  0020 18028cea0000      	movw	OFST+0,s,_EE_th_event_waitmask,y
3784                         ; 176     EE_th_status[current] = WAITING;
3786  0026 cc0001            	ldd	#1
3787  0029 6cea0000          	std	_EE_th_status,y
3788                         ; 109     EE_stkfirst = EE_th_next[EE_stkfirst];
3791  002d cd0000            	ldy	#_EE_th_next
3792  0030 fc0002            	ldd	_EE_stkfirst+2
3793  0033 59                	lsld	
3794  0034 59                	lsld	
3795  0035 19ee              	leay	d,y
3796  0037 1805420002        	movw	2,y,_EE_stkfirst+2
3797  003c 1805400000        	movw	0,y,_EE_stkfirst
3798                         ; 182     EE_sys_ceiling &= ~EE_th_dispatch_prio[current];
3801  0041 ed8a              	ldy	OFST-2,s
3802  0043 1858              	lsly	
3803  0045 eeea0000          	ldx	_EE_th_dispatch_prio,y
3804  0049 1841              	comx	
3805  004b 18b40000          	andx	_EE_sys_ceiling
3806  004f 7e0000            	stx	_EE_sys_ceiling
3807                         ; 191     EE_th_waswaiting[current] = 1;
3809  0052 cc0001            	ldd	#1
3810  0055 6cea0000          	std	_EE_th_waswaiting,y
3811                         ; 200     tmp = EE_rq_queryfirst();
3813  0059 4a000000          	call	f_EE_rq_queryfirst
3815  005d 6c86              	std	OFST-6,s
3816  005f 6e84              	stx	OFST-8,s
3817                         ; 202     if (tmp == EE_NIL ||
3817                         ; 203         EE_sys_ceiling >= EE_th_ready_prio[tmp])
3819  0061 04a505            	ibne	x,LC001
3820  0064 8cffff            	cpd	#-1
3821  0067 270c              	beq	L3003
3822  0069                   LC001:
3824  0069 59                	lsld	
3825  006a b746              	tfr	d,y
3826  006c ecea0000          	ldd	_EE_th_ready_prio,y
3827  0070 bc0000            	cpd	_EE_sys_ceiling
3828  0073 2231              	bhi	L1003
3829  0075                   L3003:
3830                         ; 62     return EE_stkfirst;  
3833  0075 fc0002            	ldd	_EE_stkfirst+2
3834  0078 6c86              	std	OFST-6,s
3835  007a fe0000            	ldx	_EE_stkfirst
3836  007d 6e84              	stx	OFST-8,s
3838                         ; 63 }
3840                         ; 208 	if (tmp != EE_NIL)
3842  007f 04a505            	ibne	x,LC002
3843  0082 8cffff            	cpd	#-1
3844  0085 2708              	beq	L5003
3845  0087                   LC002:
3846                         ; 209 	  EE_th_status[tmp] = RUNNING;
3848  0087 59                	lsld	
3849  0088 b746              	tfr	d,y
3850  008a 1869ea0000        	clrw	_EE_th_status,y
3851  008f                   L5003:
3852                         ; 192     EE_s12xs_hal_stkchange(EE_s12xs_thread_tos[thread+1]);
3855  008f ed86              	ldy	OFST-6,s
3856  0091 1858              	lsly	
3857  0093                   LC003:
3858  0093 ecea0002          	ldd	_EE_s12xs_thread_tos+2,y
3859  0097 4a000000          	call	f_EE_s12xs_hal_stkchange
3861  009b                   L7003:
3862                         ; 231     EE_th_event_waitmask[current] = 0;
3864  009b ed8a              	ldy	OFST-2,s
3865  009d 1858              	lsly	
3866  009f 1869ea0000        	clrw	_EE_th_event_waitmask,y
3867  00a4 204a              	bra	L5103
3868  00a6                   L1003:
3869                         ; 214         EE_th_status[tmp] = RUNNING;
3871  00a6 ed86              	ldy	OFST-6,s
3872  00a8 1858              	lsly	
3873  00aa 1869ea0000        	clrw	_EE_th_status,y
3874                         ; 215         EE_sys_ceiling |= EE_th_dispatch_prio[tmp];
3876  00af edea0000          	ldy	_EE_th_dispatch_prio,y
3877  00b3 18fa0000          	ory	_EE_sys_ceiling
3878  00b7 7d0000            	sty	_EE_sys_ceiling
3879                         ; 221 	tmp = EE_rq2stk_exchange();
3881  00ba 4a000000          	call	f_EE_rq2stk_exchange
3883  00be 6c86              	std	OFST-6,s
3884  00c0 6e84              	stx	OFST-8,s
3885                         ; 222 	if (EE_th_waswaiting[tmp]) {
3887  00c2 b746              	tfr	d,y
3888  00c4 1858              	lsly	
3889  00c6 eeea0000          	ldx	_EE_th_waswaiting,y
3890  00ca 2707              	beq	L1103
3891                         ; 223 	  EE_th_waswaiting[tmp] = 0;
3893  00cc 1869ea0000        	clrw	_EE_th_waswaiting,y
3894                         ; 192     EE_s12xs_hal_stkchange(EE_s12xs_thread_tos[thread+1]);
3898  00d1 20c0              	bra	LC003
3899  00d3                   L1103:
3900                         ; 141     EE_s12xs_hal_ready2stacked(EE_hal_thread_body[thread],
3900                         ; 142 			         EE_s12xs_thread_tos[thread+1]);
3903  00d3 59                	lsld	
3904  00d4 b746              	tfr	d,y
3905  00d6 ecea0002          	ldd	_EE_s12xs_thread_tos+2,y
3906  00da 3b                	pshd	
3907  00db cd0000            	ldy	#_EE_hal_thread_body
3908  00de ec88              	ldd	OFST-4,s
3909  00e0 59                	lsld	
3910  00e1 59                	lsld	
3911  00e2 19ee              	leay	d,y
3912  00e4 ec42              	ldd	2,y
3913  00e6 ee40              	ldx	0,y
3914  00e8 4a000000          	call	f_EE_s12xs_hal_ready2stacked
3916  00ec 1b82              	leas	2,s
3917  00ee 20ab              	bra	L7003
3918  00f0                   L5103:
3919                         ; 191   ASM_EN_INT;
3922  00f0 10ef              	cli	
3924                         ; 250 }
3928  00f2 1b8e              	leas	14,s
3929  00f4 0a                	rtc	
3941                         	xref	f_EE_rq2stk_exchange
3942                         	xref	f_EE_rq_queryfirst
3943                         	xref	_EE_pit0_initialized
3944                         	xref	_EE_ApplicationMode
3945                         	xref	_EE_oo_IRQ_disable_count
3946                         	xdef	f_EE_oo_WaitEvent
3947                         	xref	_EE_oo_ErrorHook_data
3948                         	xref	_EE_oo_ErrorHook_ServiceID
3949                         	xref	_EE_th_waswaiting
3950                         	xref	_EE_th_event_waitmask
3951                         	xref	_EE_th_event_active
3952                         	xref	_EE_sys_ceiling
3953                         	xref	_EE_stkfirst
3954                         	xref	_EE_th_dispatch_prio
3955                         	xref	_EE_th_ready_prio
3956                         	xref	_EE_th_next
3957                         	xref	_EE_th_status
3958                         	xref	_EE_buttons_initialized
3959                         	xref	f_EE_s12xs_terminate_task
3960                         	xref	f_EE_s12xs_terminate_savestk
3961                         	xref	_EE_IRQ_nesting_level
3962                         	xref	f_EE_s12xs_hal_stkchange
3963                         	xref	f_EE_s12xs_hal_ready2stacked
3964                         	xref	_EE_hal_endcycle_next_tos
3965                         	xref	_EE_hal_endcycle_next_thread
3966                         	xref	_EE_terminate_real_th_body
3967                         	xref	_EE_terminate_data
3968                         	xref	_EE_s12xs_thread_tos
3969                         	xref	_EE_hal_thread_body
3989                         	end
