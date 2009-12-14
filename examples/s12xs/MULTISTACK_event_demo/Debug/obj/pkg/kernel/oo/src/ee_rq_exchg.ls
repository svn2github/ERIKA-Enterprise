   1                         ; C Compiler for S12X [COSMIC Software].
   2                         ; Generator (Limited) V4.7.11.2 - 16 Mar 2009
   3                         ; Optimizer V4.6.16 - 02 Dec 2008
3713                         ; 68 EE_TID EE_rq2stk_exchange(void)
3713                         ; 69 {
3714                         .ftext:	section	.text
3715  0000                   f_EE_rq2stk_exchange:
3717  0000 1b99              	leas	-7,s
3718       00000007          OFST:	set	7
3721                         ; 76   x = EE_rq_lookup[(EE_rq_bitmask & 0xFF00) >> 8];
3723  0002 b60000            	ldaa	_EE_rq_bitmask
3724  0005 c7                	clrb	
3725  0006 b784              	exg	a,d
3726  0008 b746              	tfr	d,y
3727  000a e6ea0000          	ldab	_EE_rq_lookup,y
3728  000e 6b80              	stab	OFST-7,s
3729                         ; 77   if (x == -1)
3731  0010 c1ff              	cmpb	#255
3732  0012 2609              	bne	L7272
3733                         ; 78     x = EE_rq_lookup[EE_rq_bitmask];
3735  0014 fd0000            	ldy	_EE_rq_bitmask
3736  0017 e6ea0000          	ldab	_EE_rq_lookup,y
3738  001b 2002              	bra	L1372
3739  001d                   L7272:
3740                         ; 80     x += 8;
3742  001d cb08              	addb	#8
3743  001f                   L1372:
3744  001f 6b80              	stab	OFST-7,s
3745                         ; 88   temp = EE_rq_pairs_tid[EE_rq_queues_head[x]];
3747  0021 cd0000            	ldy	#_EE_rq_pairs_tid
3748  0024 b715              	sex	b,x
3749  0026 1848              	lslx	
3750  0028 ece20000          	ldd	_EE_rq_queues_head,x
3751  002c 59                	lsld	
3752  002d 59                	lsld	
3753  002e 19ee              	leay	d,y
3754  0030 18024283          	movw	2,y,OFST-4,s
3755  0034 18024081          	movw	0,y,OFST-6,s
3756                         ; 91   y = EE_rq_queues_head[x];
3758  0038 e680              	ldab	OFST-7,s
3759  003a b716              	sex	b,y
3760  003c 1858              	lsly	
3761  003e 1802ea000085      	movw	_EE_rq_queues_head,y,OFST-2,s
3762                         ; 92   EE_rq_queues_head[x] = EE_rq_pairs_next[EE_rq_queues_head[x]];
3764  0044 eee20000          	ldx	_EE_rq_queues_head,x
3765  0048 1848              	lslx	
3766  004a 1802e20000ea0000  	movw	_EE_rq_pairs_next,x,_EE_rq_queues_head,y
3767                         ; 93   EE_rq_pairs_next[y] = EE_rq_free;
3769  0052 ed85              	ldy	OFST-2,s
3770  0054 1858              	lsly	
3771  0056 1801ea00000000    	movw	_EE_rq_free,_EE_rq_pairs_next,y
3772                         ; 94   EE_rq_free = y;
3774  005d 1805850000        	movw	OFST-2,s,_EE_rq_free
3775                         ; 96   if (EE_rq_queues_head[x] == -1) {
3777  0062 b716              	sex	b,y
3778  0064 1858              	lsly	
3779  0066 ecea0000          	ldd	_EE_rq_queues_head,y
3780  006a 04a41c            	ibne	d,L3372
3781                         ; 97     EE_rq_queues_tail[x] = -1;
3783  006d ccffff            	ldd	#-1
3784  0070 6cea0000          	std	_EE_rq_queues_tail,y
3785                         ; 99     EE_rq_bitmask &= ~(1<<x);
3787  0074 cd0001            	ldy	#1
3788  0077 e680              	ldab	OFST-7,s
3789  0079 2705              	beq	L6
3790  007b                   L01:
3791  007b 1858              	lsly	
3792  007d 0431fb            	dbne	b,L01
3793  0080                   L6:
3794  0080 1851              	comy	
3795  0082 18f40000          	andy	_EE_rq_bitmask
3796  0086 7d0000            	sty	_EE_rq_bitmask
3797  0089                   L3372:
3798                         ; 103   EE_th_next[temp] = EE_stkfirst;
3800  0089 cd0000            	ldy	#_EE_th_next
3801  008c ec83              	ldd	OFST-4,s
3802  008e 59                	lsld	
3803  008f 59                	lsld	
3804  0090 19ee              	leay	d,y
3805  0092 1801420002        	movw	_EE_stkfirst+2,2,y
3806  0097 1801400000        	movw	_EE_stkfirst,0,y
3807                         ; 104   EE_stkfirst = temp;
3809  009c 1805830002        	movw	OFST-4,s,_EE_stkfirst+2
3810  00a1 1805810000        	movw	OFST-6,s,_EE_stkfirst
3811                         ; 106   return temp;
3813  00a6 ec83              	ldd	OFST-4,s
3814  00a8 ee81              	ldx	OFST-6,s
3817  00aa 1b87              	leas	7,s
3818  00ac 0a                	rtc	
3830                         	xdef	f_EE_rq2stk_exchange
3831                         	xref	_EE_rq_lookup
3832                         	xref	_EE_pit0_initialized
3833                         	xref	_EE_ApplicationMode
3834                         	xref	_EE_oo_IRQ_disable_count
3835                         	xref	_EE_oo_ErrorHook_data
3836                         	xref	_EE_oo_ErrorHook_ServiceID
3837                         	xref	_EE_rq_free
3838                         	xref	_EE_rq_pairs_tid
3839                         	xref	_EE_rq_pairs_next
3840                         	xref	_EE_rq_queues_tail
3841                         	xref	_EE_rq_queues_head
3842                         	xref	_EE_rq_bitmask
3843                         	xref	_EE_stkfirst
3844                         	xref	_EE_th_next
3845                         	xref	_EE_th_status
3846                         	xref	_EE_buttons_initialized
3847                         	xref	f_EE_s12xs_terminate_task
3848                         	xref	f_EE_s12xs_terminate_savestk
3849                         	xref	_EE_IRQ_nesting_level
3850                         	xref	f_EE_s12xs_hal_stkchange
3851                         	xref	f_EE_s12xs_hal_ready2stacked
3852                         	xref	_EE_hal_endcycle_next_tos
3853                         	xref	_EE_hal_endcycle_next_thread
3854                         	xref	_EE_terminate_real_th_body
3855                         	xref	_EE_terminate_data
3856                         	xref	_EE_s12xs_thread_tos
3857                         	xref	_EE_hal_thread_body
3877                         	end
