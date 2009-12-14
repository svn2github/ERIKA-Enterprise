   1                         ; C Compiler for S12X [COSMIC Software].
   2                         ; Generator (Limited) V4.7.11.2 - 16 Mar 2009
   3                         ; Optimizer V4.6.16 - 02 Dec 2008
3714                         ; 76 void EE_rq_insert(EE_TID t)
3714                         ; 77 {
3715                         .ftext:	section	.text
3716  0000                   f_EE_rq_insert:
3718  0000 3b                	pshd	
3719  0001 34                	pshx	
3720  0002 1b9c              	leas	-4,s
3721       00000004          OFST:	set	4
3724                         ; 81   p = EE_rq_link[t];
3726  0004 59                	lsld	
3727  0005 b746              	tfr	d,y
3728  0007 1802ea000082      	movw	_EE_rq_link,y,OFST-2,s
3729                         ; 84   temp = EE_rq_free;
3731  000d fd0000            	ldy	_EE_rq_free
3732  0010 6d80              	sty	OFST-4,s
3733                         ; 85   EE_rq_free = EE_rq_pairs_next[EE_rq_free];
3735  0012 1858              	lsly	
3736  0014 1805ea00000000    	movw	_EE_rq_pairs_next,y,_EE_rq_free
3737                         ; 88   EE_rq_pairs_tid[temp] = t;
3739  001b cd0000            	ldy	#_EE_rq_pairs_tid
3740  001e ec80              	ldd	OFST-4,s
3741  0020 59                	lsld	
3742  0021 59                	lsld	
3743  0022 19ee              	leay	d,y
3744  0024 18028642          	movw	OFST+2,s,2,y
3745  0028 18028440          	movw	OFST+0,s,0,y
3746                         ; 89   EE_rq_pairs_next[temp] = -1;
3748  002c ccffff            	ldd	#-1
3749  002f ed80              	ldy	OFST-4,s
3750  0031 1858              	lsly	
3751  0033 6cea0000          	std	_EE_rq_pairs_next,y
3752                         ; 92   if (EE_rq_queues_tail[p] == -1) {
3754  0037 ed82              	ldy	OFST-2,s
3755  0039 1858              	lsly	
3756  003b ecea0000          	ldd	_EE_rq_queues_tail,y
3757  003f 04a41b            	ibne	d,L7272
3758                         ; 95     EE_rq_bitmask |= EE_th_ready_prio[t];
3760  0042 ed86              	ldy	OFST+2,s
3761  0044 1858              	lsly	
3762  0046 edea0000          	ldy	_EE_th_ready_prio,y
3763  004a 18fa0000          	ory	_EE_rq_bitmask
3764  004e 7d0000            	sty	_EE_rq_bitmask
3765                         ; 96     EE_rq_queues_head[p] = temp;
3767  0051 ec80              	ldd	OFST-4,s
3768  0053 ed82              	ldy	OFST-2,s
3769  0055 1858              	lsly	
3770  0057 6cea0000          	std	_EE_rq_queues_head,y
3772  005b 2010              	bra	L1372
3773  005d                   L7272:
3774                         ; 98     EE_rq_pairs_next[EE_rq_queues_tail[p]] = temp;
3776  005d ec80              	ldd	OFST-4,s
3777  005f ed82              	ldy	OFST-2,s
3778  0061 1858              	lsly	
3779  0063 eeea0000          	ldx	_EE_rq_queues_tail,y
3780  0067 1848              	lslx	
3781  0069 6ce20000          	std	_EE_rq_pairs_next,x
3782  006d                   L1372:
3783                         ; 100   EE_rq_queues_tail[p] = temp;
3785  006d ed82              	ldy	OFST-2,s
3786  006f 1858              	lsly	
3787  0071 6cea0000          	std	_EE_rq_queues_tail,y
3788                         ; 101 }
3791  0075 1b88              	leas	8,s
3792  0077 0a                	rtc	
3804                         	xdef	f_EE_rq_insert
3805                         	xref	_EE_pit0_initialized
3806                         	xref	_EE_ApplicationMode
3807                         	xref	_EE_oo_IRQ_disable_count
3808                         	xref	_EE_oo_ErrorHook_data
3809                         	xref	_EE_oo_ErrorHook_ServiceID
3810                         	xref	_EE_rq_free
3811                         	xref	_EE_rq_pairs_tid
3812                         	xref	_EE_rq_pairs_next
3813                         	xref	_EE_rq_queues_tail
3814                         	xref	_EE_rq_queues_head
3815                         	xref	_EE_rq_link
3816                         	xref	_EE_rq_bitmask
3817                         	xref	_EE_stkfirst
3818                         	xref	_EE_th_ready_prio
3819                         	xref	_EE_th_next
3820                         	xref	_EE_th_status
3821                         	xref	_EE_buttons_initialized
3822                         	xref	f_EE_s12xs_terminate_task
3823                         	xref	f_EE_s12xs_terminate_savestk
3824                         	xref	_EE_IRQ_nesting_level
3825                         	xref	f_EE_s12xs_hal_stkchange
3826                         	xref	f_EE_s12xs_hal_ready2stacked
3827                         	xref	_EE_hal_endcycle_next_tos
3828                         	xref	_EE_hal_endcycle_next_thread
3829                         	xref	_EE_terminate_real_th_body
3830                         	xref	_EE_terminate_data
3831                         	xref	_EE_s12xs_thread_tos
3832                         	xref	_EE_hal_thread_body
3852                         	end
