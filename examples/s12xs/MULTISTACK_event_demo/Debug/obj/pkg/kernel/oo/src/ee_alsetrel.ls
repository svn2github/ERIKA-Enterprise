   1                         ; C Compiler for S12X [COSMIC Software].
   2                         ; Generator (Limited) V4.7.11.2 - 16 Mar 2009
   3                         ; Optimizer V4.6.16 - 02 Dec 2008
3748                         ; 63 StatusType EE_oo_SetRelAlarm(AlarmType AlarmID, 
3748                         ; 64 				  TickType increment, 
3748                         ; 65 				  TickType cycle)
3748                         ; 66 {
3749                         .ftext:	section	.text
3750  0000                   f_EE_oo_SetRelAlarm:
3752  0000 3b                	pshd	
3753  0001 1b9c              	leas	-4,s
3754       00000004          OFST:	set	4
3757                         ; 101   retvalue = _asm("tfr ccr,b\n");	// save CCR register (I bit)
3761  0003 b721              	tfr	ccr,b
3763                         ; 200   ASM_DIS_INT;
3766  0005 1410              	sei	
3768                         ; 104   return retvalue;
3771  0007 6c82              	std	OFST-2,s
3773                         ; 105 }
3775                         ; 143   if (EE_alarm_RAM[AlarmID].used) {
3777  0009 ed84              	ldy	OFST+0,s
3778  000b 1858              	lsly	
3779  000d 1858              	lsly	
3780  000f 1858              	lsly	
3781  0011 ecea0000          	ldd	_EE_alarm_RAM,y
3782  0015 2737              	beq	L1003
3783                         ; 149     if (!EE_ErrorHook_nested_flag) {
3785  0017 fc0000            	ldd	_EE_ErrorHook_nested_flag
3786  001a 2624              	bne	L3003
3787                         ; 151       EE_oo_ErrorHook_ServiceID = OSServiceId_SetRelAlarm;
3789  001c c60e              	ldab	#14
3790  001e 7b0000            	stab	_EE_oo_ErrorHook_ServiceID
3791                         ; 152       EE_oo_ErrorHook_data.SetRelAlarm_prm.AlarmID = AlarmID;
3793  0021 1805840000        	movw	OFST+0,s,_EE_oo_ErrorHook_data
3794                         ; 153       EE_oo_ErrorHook_data.SetRelAlarm_prm.increment = increment;
3796  0026 1805890002        	movw	OFST+5,s,_EE_oo_ErrorHook_data+2
3797                         ; 154       EE_oo_ErrorHook_data.SetRelAlarm_prm.cycle = cycle;
3799  002b 18058b0004        	movw	OFST+7,s,_EE_oo_ErrorHook_data+4
3800                         ; 156       EE_ErrorHook_nested_flag = 1;
3802  0030 cc0001            	ldd	#1
3803  0033 7c0000            	std	_EE_ErrorHook_nested_flag
3804                         ; 157       ErrorHook(E_OS_STATE);
3806  0036 c607              	ldab	#7
3807  0038 4a000000          	call	f_ErrorHook
3809                         ; 158       EE_ErrorHook_nested_flag = 0;
3811  003c 18790000          	clrw	_EE_ErrorHook_nested_flag
3812  0040                   L3003:
3813                         ; 111   if(f & 0x10) 						// restore I bit
3816  0040 0f831004          	brclr	OFST-1,s,16,L5103
3817                         ; 200   ASM_DIS_INT;
3820  0044 1410              	sei	
3822  0046 2002              	bra	L7172
3823  0048                   L5103:
3824                         ; 191   ASM_EN_INT;
3827  0048 10ef              	cli	
3829  004a                   L7172:
3830                         ; 168     return E_OS_STATE;
3833  004a c607              	ldab	#7
3835  004c 2033              	bra	L6
3836  004e                   L1003:
3837                         ; 172   EE_alarm_RAM[AlarmID].used = 1;
3839  004e cc0001            	ldd	#1
3840  0051 ed84              	ldy	OFST+0,s
3841  0053 1858              	lsly	
3842  0055 1858              	lsly	
3843  0057 1858              	lsly	
3844  0059 6cea0000          	std	_EE_alarm_RAM,y
3845                         ; 173   EE_alarm_RAM[AlarmID].cycle = cycle;
3847  005d ed84              	ldy	OFST+0,s
3848  005f 1858              	lsly	
3849  0061 1858              	lsly	
3850  0063 1858              	lsly	
3851  0065 18028bea0002      	movw	OFST+7,s,_EE_alarm_RAM+2,y
3852                         ; 176   EE_oo_alarm_insert(AlarmID,increment);
3854  006b ec89              	ldd	OFST+5,s
3855  006d 3b                	pshd	
3856  006e ec86              	ldd	OFST+2,s
3857  0070 4a000000          	call	f_EE_oo_alarm_insert
3859  0074 1b82              	leas	2,s
3860                         ; 111   if(f & 0x10) 						// restore I bit
3863  0076 0f831004          	brclr	OFST-1,s,16,L1303
3864                         ; 200   ASM_DIS_INT;
3867  007a 1410              	sei	
3869  007c 2002              	bra	L1372
3870  007e                   L1303:
3871                         ; 191   ASM_EN_INT;
3874  007e 10ef              	cli	
3876  0080                   L1372:
3877                         ; 184   return E_OK;
3880  0080 c7                	clrb	
3882  0081                   L6:
3884  0081 1b86              	leas	6,s
3885  0083 0a                	rtc	
3897                         	xref	f_EE_oo_alarm_insert
3898                         	xref	_EE_ErrorHook_nested_flag
3899                         	xref	_EE_pit0_initialized
3900                         	xref	_EE_ApplicationMode
3901                         	xref	_EE_oo_IRQ_disable_count
3902                         	xref	f_ErrorHook
3903                         	xdef	f_EE_oo_SetRelAlarm
3904                         	xref	_EE_oo_ErrorHook_data
3905                         	xref	_EE_oo_ErrorHook_ServiceID
3906                         	xref	_EE_alarm_RAM
3907                         	xref	_EE_stkfirst
3908                         	xref	_EE_th_next
3909                         	xref	_EE_th_status
3910                         	xref	_EE_buttons_initialized
3911                         	xref	f_EE_s12xs_terminate_task
3912                         	xref	f_EE_s12xs_terminate_savestk
3913                         	xref	_EE_IRQ_nesting_level
3914                         	xref	f_EE_s12xs_hal_stkchange
3915                         	xref	f_EE_s12xs_hal_ready2stacked
3916                         	xref	_EE_hal_endcycle_next_tos
3917                         	xref	_EE_hal_endcycle_next_thread
3918                         	xref	_EE_terminate_real_th_body
3919                         	xref	_EE_terminate_data
3920                         	xref	_EE_s12xs_thread_tos
3921                         	xref	_EE_hal_thread_body
3941                         	end
