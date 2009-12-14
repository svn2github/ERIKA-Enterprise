   1                         ; C Compiler for S12X [COSMIC Software].
   2                         ; Generator (Limited) V4.7.11.2 - 16 Mar 2009
   3                         ; Optimizer V4.6.16 - 02 Dec 2008
3750                         ; 63 StatusType EE_oo_SetAbsAlarm(AlarmType AlarmID, 
3750                         ; 64 				  TickType start, 
3750                         ; 65 				  TickType cycle)
3750                         ; 66 {
3751                         .ftext:	section	.text
3752  0000                   f_EE_oo_SetAbsAlarm:
3754  0000 3b                	pshd	
3755  0001 1b9c              	leas	-4,s
3756       00000004          OFST:	set	4
3759                         ; 101   retvalue = _asm("tfr ccr,b\n");	// save CCR register (I bit)
3763  0003 b721              	tfr	ccr,b
3765                         ; 200   ASM_DIS_INT;
3768  0005 1410              	sei	
3770                         ; 104   return retvalue;
3773  0007 6c82              	std	OFST-2,s
3775                         ; 105 }
3777                         ; 144   if (EE_alarm_RAM[AlarmID].used) {
3779  0009 ed84              	ldy	OFST+0,s
3780  000b 1858              	lsly	
3781  000d 1858              	lsly	
3782  000f 1858              	lsly	
3783  0011 ecea0000          	ldd	_EE_alarm_RAM,y
3784  0015 2737              	beq	L1003
3785                         ; 150     if (!EE_ErrorHook_nested_flag) {
3787  0017 fc0000            	ldd	_EE_ErrorHook_nested_flag
3788  001a 2624              	bne	L3003
3789                         ; 152       EE_oo_ErrorHook_ServiceID = OSServiceId_SetAbsAlarm;
3791  001c c60e              	ldab	#14
3792  001e 7b0000            	stab	_EE_oo_ErrorHook_ServiceID
3793                         ; 153       EE_oo_ErrorHook_data.SetAbsAlarm_prm.AlarmID = AlarmID;
3795  0021 1805840000        	movw	OFST+0,s,_EE_oo_ErrorHook_data
3796                         ; 154       EE_oo_ErrorHook_data.SetAbsAlarm_prm.start = start;
3798  0026 1805890002        	movw	OFST+5,s,_EE_oo_ErrorHook_data+2
3799                         ; 155       EE_oo_ErrorHook_data.SetAbsAlarm_prm.cycle = cycle;
3801  002b 18058b0004        	movw	OFST+7,s,_EE_oo_ErrorHook_data+4
3802                         ; 157       EE_ErrorHook_nested_flag = 1;
3804  0030 cc0001            	ldd	#1
3805  0033 7c0000            	std	_EE_ErrorHook_nested_flag
3806                         ; 158       ErrorHook(E_OS_STATE);
3808  0036 c607              	ldab	#7
3809  0038 4a000000          	call	f_ErrorHook
3811                         ; 159       EE_ErrorHook_nested_flag = 0;
3813  003c 18790000          	clrw	_EE_ErrorHook_nested_flag
3814  0040                   L3003:
3815                         ; 111   if(f & 0x10) 						// restore I bit
3818  0040 0f831004          	brclr	OFST-1,s,16,L5103
3819                         ; 200   ASM_DIS_INT;
3822  0044 1410              	sei	
3824  0046 2002              	bra	L7172
3825  0048                   L5103:
3826                         ; 191   ASM_EN_INT;
3829  0048 10ef              	cli	
3831  004a                   L7172:
3832                         ; 169     return E_OS_STATE;
3835  004a c607              	ldab	#7
3837  004c 2047              	bra	L6
3838  004e                   L1003:
3839                         ; 173   EE_alarm_RAM[AlarmID].used = 1;
3841  004e cc0001            	ldd	#1
3842  0051 ed84              	ldy	OFST+0,s
3843  0053 1858              	lsly	
3844  0055 1858              	lsly	
3845  0057 1858              	lsly	
3846  0059 6cea0000          	std	_EE_alarm_RAM,y
3847                         ; 174   EE_alarm_RAM[AlarmID].cycle = cycle;
3849  005d ed84              	ldy	OFST+0,s
3850  005f 1858              	lsly	
3851  0061 1858              	lsly	
3852  0063 1858              	lsly	
3853  0065 18028bea0002      	movw	OFST+7,s,_EE_alarm_RAM+2,y
3854                         ; 176   EE_oo_alarm_insert(AlarmID, start - 
3854                         ; 177 			  EE_counter_RAM[EE_alarm_ROM[AlarmID].c].value);
3856  006b ec84              	ldd	OFST+0,s
3857  006d cd000d            	ldy	#13
3858  0070 13                	emul	
3859  0071 b746              	tfr	d,y
3860  0073 eeea0000          	ldx	_EE_alarm_ROM,y
3861  0077 1848              	lslx	
3862  0079 1848              	lslx	
3863  007b ec89              	ldd	OFST+5,s
3864  007d a3e20000          	subd	_EE_counter_RAM,x
3865  0081 3b                	pshd	
3866  0082 ec86              	ldd	OFST+2,s
3867  0084 4a000000          	call	f_EE_oo_alarm_insert
3869  0088 1b82              	leas	2,s
3870                         ; 111   if(f & 0x10) 						// restore I bit
3873  008a 0f831004          	brclr	OFST-1,s,16,L1303
3874                         ; 200   ASM_DIS_INT;
3877  008e 1410              	sei	
3879  0090 2002              	bra	L1372
3880  0092                   L1303:
3881                         ; 191   ASM_EN_INT;
3884  0092 10ef              	cli	
3886  0094                   L1372:
3887                         ; 185   return E_OK;
3890  0094 c7                	clrb	
3892  0095                   L6:
3894  0095 1b86              	leas	6,s
3895  0097 0a                	rtc	
3907                         	xref	f_EE_oo_alarm_insert
3908                         	xref	_EE_ErrorHook_nested_flag
3909                         	xref	_EE_pit0_initialized
3910                         	xref	_EE_ApplicationMode
3911                         	xref	_EE_oo_IRQ_disable_count
3912                         	xref	f_ErrorHook
3913                         	xdef	f_EE_oo_SetAbsAlarm
3914                         	xref	_EE_oo_ErrorHook_data
3915                         	xref	_EE_oo_ErrorHook_ServiceID
3916                         	xref	_EE_alarm_RAM
3917                         	xref	_EE_alarm_ROM
3918                         	xref	_EE_counter_RAM
3919                         	xref	_EE_stkfirst
3920                         	xref	_EE_th_next
3921                         	xref	_EE_th_status
3922                         	xref	_EE_buttons_initialized
3923                         	xref	f_EE_s12xs_terminate_task
3924                         	xref	f_EE_s12xs_terminate_savestk
3925                         	xref	_EE_IRQ_nesting_level
3926                         	xref	f_EE_s12xs_hal_stkchange
3927                         	xref	f_EE_s12xs_hal_ready2stacked
3928                         	xref	_EE_hal_endcycle_next_tos
3929                         	xref	_EE_hal_endcycle_next_thread
3930                         	xref	_EE_terminate_real_th_body
3931                         	xref	_EE_terminate_data
3932                         	xref	_EE_s12xs_thread_tos
3933                         	xref	_EE_hal_thread_body
3953                         	end
