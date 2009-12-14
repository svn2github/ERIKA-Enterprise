   1                         ; C Compiler for S12X [COSMIC Software].
   2                         ; Generator (Limited) V4.7.11.2 - 16 Mar 2009
   3                         ; Optimizer V4.6.16 - 02 Dec 2008
3761                         ; 65 void EE_oo_ReleaseResource(ResourceType ResID)
3761                         ; 66 #endif
3761                         ; 67 {
3762                         .ftext:	section	.text
3763  0000                   f_EE_oo_ReleaseResource:
3765  0000 3b                	pshd	
3766  0001 1b92              	leas	-14,s
3767       0000000e          OFST:	set	14
3770                         ; 62     return EE_stkfirst;  
3773  0003 18018c0002        	movw	_EE_stkfirst+2,OFST-2,s
3774  0008 18018a0000        	movw	_EE_stkfirst,OFST-4,s
3776                         ; 63 }
3778  000d a68c              	ldaa	OFST-2,s
3779  000f ee8a              	ldx	OFST-4,s
3780                         ; 101   retvalue = _asm("tfr ccr,b\n");	// save CCR register (I bit)
3784  0011 b721              	tfr	ccr,b
3786                         ; 200   ASM_DIS_INT;
3789  0013 1410              	sei	
3791                         ; 104   return retvalue;
3794  0015 6c88              	std	OFST-6,s
3796                         ; 105 }
3798                         ; 207   rq = EE_rq_queryfirst();
3800  0017 4a000000          	call	f_EE_rq_queryfirst
3802  001b 6c86              	std	OFST-8,s
3803  001d 6e84              	stx	OFST-10,s
3804                         ; 209   EE_sys_ceiling = EE_resource_oldceiling[ResID];
3806  001f ed8e              	ldy	OFST+0,s
3807  0021 1858              	lsly	
3808  0023 1805ea00000000    	movw	_EE_resource_oldceiling,y,_EE_sys_ceiling
3809                         ; 216   if (rq != EE_NIL) {
3811  002a 04a503            	ibne	x,LC001
3812  002d 048468            	ibeq	d,L1003
3813  0030                   LC001:
3814                         ; 217     if (EE_sys_ceiling < EE_th_ready_prio[rq]) {
3816  0030 ed86              	ldy	OFST-8,s
3817  0032 1858              	lsly	
3818  0034 ecea0000          	ldd	_EE_th_ready_prio,y
3819  0038 bc0000            	cpd	_EE_sys_ceiling
3820  003b 235b              	bls	L1003
3821                         ; 224       EE_th_status[current] = READY;
3823  003d cc0002            	ldd	#2
3824  0040 ed8c              	ldy	OFST-2,s
3825  0042 1858              	lsly	
3826  0044 6cea0000          	std	_EE_th_status,y
3827                         ; 226       EE_th_status[rq] = RUNNING;
3829  0048 ed86              	ldy	OFST-8,s
3830  004a 1858              	lsly	
3831  004c 1869ea0000        	clrw	_EE_th_status,y
3832                         ; 228       EE_sys_ceiling |= EE_th_dispatch_prio[rq];
3834  0051 edea0000          	ldy	_EE_th_dispatch_prio,y
3835  0055 18fa0000          	ory	_EE_sys_ceiling
3836  0059 7d0000            	sty	_EE_sys_ceiling
3837                         ; 235       rq = EE_rq2stk_exchange();
3839  005c 4a000000          	call	f_EE_rq2stk_exchange
3841  0060 6c86              	std	OFST-8,s
3842  0062 6e84              	stx	OFST-10,s
3843                         ; 236       if (EE_th_waswaiting[rq]) {
3845  0064 b746              	tfr	d,y
3846  0066 1858              	lsly	
3847  0068 eeea0000          	ldx	_EE_th_waswaiting,y
3848  006c 270f              	beq	L5003
3849                         ; 237 	EE_th_waswaiting[rq] = 0;
3851  006e 1869ea0000        	clrw	_EE_th_waswaiting,y
3852                         ; 192     EE_s12xs_hal_stkchange(EE_s12xs_thread_tos[thread+1]);
3855  0073 ecea0002          	ldd	_EE_s12xs_thread_tos+2,y
3856  0077 4a000000          	call	f_EE_s12xs_hal_stkchange
3858  007b 201b              	bra	L1003
3859  007d                   L5003:
3860                         ; 141     EE_s12xs_hal_ready2stacked(EE_hal_thread_body[thread],
3860                         ; 142 			         EE_s12xs_thread_tos[thread+1]);
3863  007d 59                	lsld	
3864  007e b746              	tfr	d,y
3865  0080 ecea0002          	ldd	_EE_s12xs_thread_tos+2,y
3866  0084 3b                	pshd	
3867  0085 cd0000            	ldy	#_EE_hal_thread_body
3868  0088 ec88              	ldd	OFST-6,s
3869  008a 59                	lsld	
3870  008b 59                	lsld	
3871  008c 19ee              	leay	d,y
3872  008e ec42              	ldd	2,y
3873  0090 ee40              	ldx	0,y
3874  0092 4a000000          	call	f_EE_s12xs_hal_ready2stacked
3876  0096 1b82              	leas	2,s
3877  0098                   L1003:
3878                         ; 111   if(f & 0x10) 						// restore I bit
3881  0098 0f891004          	brclr	OFST-5,s,16,L1203
3882                         ; 200   ASM_DIS_INT;
3885  009c 1410              	sei	
3887  009e 2002              	bra	L5272
3888  00a0                   L1203:
3889                         ; 191   ASM_EN_INT;
3892  00a0 10ef              	cli	
3894  00a2                   L5272:
3895                         ; 261 }
3899  00a2 1bf010            	leas	16,s
3900  00a5 0a                	rtc	
3912                         	xref	f_EE_rq2stk_exchange
3913                         	xref	f_EE_rq_queryfirst
3914                         	xref	_EE_pit0_initialized
3915                         	xref	_EE_ApplicationMode
3916                         	xref	_EE_oo_IRQ_disable_count
3917                         	xdef	f_EE_oo_ReleaseResource
3918                         	xref	_EE_oo_ErrorHook_data
3919                         	xref	_EE_oo_ErrorHook_ServiceID
3920                         	xref	_EE_resource_oldceiling
3921                         	xref	_EE_th_waswaiting
3922                         	xref	_EE_sys_ceiling
3923                         	xref	_EE_stkfirst
3924                         	xref	_EE_th_dispatch_prio
3925                         	xref	_EE_th_ready_prio
3926                         	xref	_EE_th_next
3927                         	xref	_EE_th_status
3928                         	xref	_EE_buttons_initialized
3929                         	xref	f_EE_s12xs_terminate_task
3930                         	xref	f_EE_s12xs_terminate_savestk
3931                         	xref	_EE_IRQ_nesting_level
3932                         	xref	f_EE_s12xs_hal_stkchange
3933                         	xref	f_EE_s12xs_hal_ready2stacked
3934                         	xref	_EE_hal_endcycle_next_tos
3935                         	xref	_EE_hal_endcycle_next_thread
3936                         	xref	_EE_terminate_real_th_body
3937                         	xref	_EE_terminate_data
3938                         	xref	_EE_s12xs_thread_tos
3939                         	xref	_EE_hal_thread_body
3959                         	end
