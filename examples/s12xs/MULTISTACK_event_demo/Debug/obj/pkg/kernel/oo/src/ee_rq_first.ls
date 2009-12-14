   1                         ; C Compiler for S12X [COSMIC Software].
   2                         ; Generator (Limited) V4.7.11.2 - 16 Mar 2009
   3                         ; Optimizer V4.6.16 - 02 Dec 2008
3696                         ; 51 EE_TID EE_rq_queryfirst(void)
3696                         ; 52 {
3697                         .ftext:	section	.text
3698  0000                   f_EE_rq_queryfirst:
3700  0000 37                	pshb	
3701       00000001          OFST:	set	1
3704                         ; 57   x = EE_rq_lookup[(EE_rq_bitmask & 0xFF00) >> 8];
3706  0001 b60000            	ldaa	_EE_rq_bitmask
3707  0004 c7                	clrb	
3708  0005 b784              	exg	a,d
3709  0007 b746              	tfr	d,y
3710  0009 e6ea0000          	ldab	_EE_rq_lookup,y
3711  000d 6b80              	stab	OFST-1,s
3712                         ; 58   if (x == -1)
3714  000f c1ff              	cmpb	#255
3715  0011 2609              	bne	L3272
3716                         ; 59     x = EE_rq_lookup[EE_rq_bitmask];
3718  0013 fd0000            	ldy	_EE_rq_bitmask
3719  0016 e6ea0000          	ldab	_EE_rq_lookup,y
3721  001a 2002              	bra	L5272
3722  001c                   L3272:
3723                         ; 61     x += 8;
3725  001c cb08              	addb	#8
3726  001e                   L5272:
3727  001e 6b80              	stab	OFST-1,s
3728                         ; 67   if (x == -1)
3730  0020 c1ff              	cmpb	#255
3731  0022 2607              	bne	L7272
3732                         ; 68     return EE_NIL;
3734  0024 ceffff            	ldx	#-1
3735  0027 b754              	tfr	x,d
3737  0029 2013              	bra	L6
3738  002b                   L7272:
3739                         ; 70     return EE_rq_pairs_tid[EE_rq_queues_head[x]];
3741  002b cd0000            	ldy	#_EE_rq_pairs_tid
3742  002e b715              	sex	b,x
3743  0030 1848              	lslx	
3744  0032 ece20000          	ldd	_EE_rq_queues_head,x
3745  0036 59                	lsld	
3746  0037 59                	lsld	
3747  0038 19ee              	leay	d,y
3748  003a ec42              	ldd	2,y
3749  003c ee40              	ldx	0,y
3751  003e                   L6:
3753  003e 1b81              	leas	1,s
3754  0040 0a                	rtc	
3766                         	xdef	f_EE_rq_queryfirst
3767                         	xref	_EE_rq_lookup
3768                         	xref	_EE_pit0_initialized
3769                         	xref	_EE_ApplicationMode
3770                         	xref	_EE_oo_IRQ_disable_count
3771                         	xref	_EE_oo_ErrorHook_data
3772                         	xref	_EE_oo_ErrorHook_ServiceID
3773                         	xref	_EE_rq_pairs_tid
3774                         	xref	_EE_rq_queues_head
3775                         	xref	_EE_rq_bitmask
3776                         	xref	_EE_stkfirst
3777                         	xref	_EE_th_next
3778                         	xref	_EE_th_status
3779                         	xref	_EE_buttons_initialized
3780                         	xref	f_EE_s12xs_terminate_task
3781                         	xref	f_EE_s12xs_terminate_savestk
3782                         	xref	_EE_IRQ_nesting_level
3783                         	xref	f_EE_s12xs_hal_stkchange
3784                         	xref	f_EE_s12xs_hal_ready2stacked
3785                         	xref	_EE_hal_endcycle_next_tos
3786                         	xref	_EE_hal_endcycle_next_thread
3787                         	xref	_EE_terminate_real_th_body
3788                         	xref	_EE_terminate_data
3789                         	xref	_EE_s12xs_thread_tos
3790                         	xref	_EE_hal_thread_body
3810                         	end
