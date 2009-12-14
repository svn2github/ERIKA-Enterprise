   1                         ; C Compiler for S12X [COSMIC Software].
   2                         ; Generator (Limited) V4.7.11.2 - 16 Mar 2009
   3                         ; Optimizer V4.6.16 - 02 Dec 2008
3767                         ; 57 void EE_oo_GetAlarmBase(AlarmType AlarmID, AlarmBaseRefType Info)
3767                         ; 58 #endif
3767                         ; 59 {
3768                         .ftext:	section	.text
3769  0000                   f_EE_oo_GetAlarmBase:
3771  0000 3b                	pshd	
3772  0001 3b                	pshd	
3773       00000002          OFST:	set	2
3776                         ; 99   c = &EE_counter_ROM[EE_alarm_ROM[AlarmID].c];
3778  0002 cd000d            	ldy	#13
3779  0005 13                	emul	
3780  0006 b746              	tfr	d,y
3781  0008 ecea0000          	ldd	_EE_alarm_ROM,y
3782  000c cd0006            	ldy	#6
3783  000f 13                	emul	
3784  0010 c30000            	addd	#_EE_counter_ROM
3785  0013 6c80              	std	OFST-2,s
3786                         ; 100   Info->maxallowedvalue = c->maxallowedvalue;
3788  0015 ed87              	ldy	OFST+5,s
3789  0017 b745              	tfr	d,x
3790  0019 18020040          	movw	0,x,0,y
3791                         ; 101   Info->ticksperbase = c->ticksperbase;
3793  001d 18020242          	movw	2,x,2,y
3794                         ; 115 }
3797  0021 1b84              	leas	4,s
3798  0023 0a                	rtc	
3810                         	xref	_EE_pit0_initialized
3811                         	xref	_EE_ApplicationMode
3812                         	xref	_EE_oo_IRQ_disable_count
3813                         	xdef	f_EE_oo_GetAlarmBase
3814                         	xref	_EE_oo_ErrorHook_data
3815                         	xref	_EE_oo_ErrorHook_ServiceID
3816                         	xref	_EE_alarm_ROM
3817                         	xref	_EE_counter_ROM
3818                         	xref	_EE_stkfirst
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
