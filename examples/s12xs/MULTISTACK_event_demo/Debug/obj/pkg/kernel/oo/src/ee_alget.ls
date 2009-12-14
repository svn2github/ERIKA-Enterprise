   1                         ; C Compiler for S12X [COSMIC Software].
   2                         ; Generator (Limited) V4.7.11.2 - 16 Mar 2009
   3                         ; Optimizer V4.6.16 - 02 Dec 2008
3752                         ; 57 StatusType EE_oo_GetAlarm(AlarmType AlarmID, TickRefType Tick)
3752                         ; 58 {
3753                         .ftext:	section	.text
3754  0000                   f_EE_oo_GetAlarm:
3756  0000 3b                	pshd	
3757  0001 1b9a              	leas	-6,s
3758       00000006          OFST:	set	6
3761                         ; 101   retvalue = _asm("tfr ccr,b\n");	// save CCR register (I bit)
3765  0003 b721              	tfr	ccr,b
3767                         ; 200   ASM_DIS_INT;
3770  0005 1410              	sei	
3772                         ; 104   return retvalue;
3775  0007 6c84              	std	OFST-2,s
3777                         ; 105 }
3779                         ; 104   if (!EE_alarm_RAM[AlarmID].used) {
3781  0009 ed86              	ldy	OFST+0,s
3782  000b 1858              	lsly	
3783  000d 1858              	lsly	
3784  000f 1858              	lsly	
3785  0011 ecea0000          	ldd	_EE_alarm_RAM,y
3786  0015 2632              	bne	L3003
3787                         ; 110     if (!EE_ErrorHook_nested_flag) {
3789  0017 fc0000            	ldd	_EE_ErrorHook_nested_flag
3790  001a 261f              	bne	L5003
3791                         ; 112       EE_oo_ErrorHook_ServiceID = OSServiceId_GetAlarm;
3793  001c c60d              	ldab	#13
3794  001e 7b0000            	stab	_EE_oo_ErrorHook_ServiceID
3795                         ; 113       EE_oo_ErrorHook_data.GetAlarm_prm.AlarmID = AlarmID;
3797  0021 1805860000        	movw	OFST+0,s,_EE_oo_ErrorHook_data
3798                         ; 114       EE_oo_ErrorHook_data.GetAlarm_prm.Tick = Tick;
3800  0026 18058b0002        	movw	OFST+5,s,_EE_oo_ErrorHook_data+2
3801                         ; 116       EE_ErrorHook_nested_flag = 1;
3803  002b cc0001            	ldd	#1
3804  002e 7c0000            	std	_EE_ErrorHook_nested_flag
3805                         ; 117       ErrorHook(E_OS_NOFUNC);
3807  0031 c605              	ldab	#5
3808  0033 4a000000          	call	f_ErrorHook
3810                         ; 118       EE_ErrorHook_nested_flag = 0;
3812  0037 18790000          	clrw	_EE_ErrorHook_nested_flag
3813  003b                   L5003:
3814                         ; 111   if(f & 0x10) 						// restore I bit
3817  003b 0f851004          	brclr	OFST-1,s,16,L7103
3818                         ; 200   ASM_DIS_INT;
3821  003f 1410              	sei	
3823  0041 2002              	bra	L7172
3824  0043                   L7103:
3825                         ; 191   ASM_EN_INT;
3828  0043 10ef              	cli	
3830  0045                   L7172:
3831                         ; 128     return E_OS_NOFUNC;
3834  0045 c605              	ldab	#5
3836  0047 2052              	bra	L6
3837  0049                   L3003:
3838                         ; 133   current = EE_counter_RAM[EE_alarm_ROM[AlarmID].c].first;
3840  0049 ec86              	ldd	OFST+0,s
3841  004b cd000d            	ldy	#13
3842  004e 13                	emul	
3843  004f b746              	tfr	d,y
3844  0051 eeea0000          	ldx	_EE_alarm_ROM,y
3845  0055 1848              	lslx	
3846  0057 1848              	lslx	
3847  0059 eee20002          	ldx	_EE_counter_RAM+2,x
3848  005d 6e82              	stx	OFST-4,s
3849                         ; 134   *Tick = EE_alarm_RAM[current].delta;
3851  005f ed8b              	ldy	OFST+5,s
3852  0061 1848              	lslx	
3853  0063 1848              	lslx	
3854  0065 1848              	lslx	
3855  0067 1802e2000440      	movw	_EE_alarm_RAM+4,x,0,y
3857  006d 201b              	bra	L7203
3858  006f                   L3203:
3859                         ; 136     current = EE_alarm_RAM[current].next;
3861  006f 1858              	lsly	
3862  0071 1858              	lsly	
3863  0073 1858              	lsly	
3864  0075 ecea0006          	ldd	_EE_alarm_RAM+6,y
3865  0079 6c82              	std	OFST-4,s
3866                         ; 137     *Tick += EE_alarm_RAM[current].delta;
3868  007b ed8b              	ldy	OFST+5,s
3869  007d 59                	lsld	
3870  007e 59                	lsld	
3871  007f 59                	lsld	
3872  0080 b745              	tfr	d,x
3873  0082 ec40              	ldd	0,y
3874  0084 e3e20004          	addd	_EE_alarm_RAM+4,x
3875  0088 6c40              	std	0,y
3876  008a                   L7203:
3877                         ; 135   while (current != AlarmID) {
3879  008a ed82              	ldy	OFST-4,s
3880  008c ad86              	cpy	OFST+0,s
3881  008e 26df              	bne	L3203
3882                         ; 111   if(f & 0x10) 						// restore I bit
3885  0090 0f851004          	brclr	OFST-1,s,16,L3403
3886                         ; 200   ASM_DIS_INT;
3889  0094 1410              	sei	
3891  0096 2002              	bra	L1372
3892  0098                   L3403:
3893                         ; 191   ASM_EN_INT;
3896  0098 10ef              	cli	
3898  009a                   L1372:
3899                         ; 146   return E_OK;
3902  009a c7                	clrb	
3904  009b                   L6:
3906  009b 1b88              	leas	8,s
3907  009d 0a                	rtc	
3919                         	xref	_EE_ErrorHook_nested_flag
3920                         	xref	_EE_pit0_initialized
3921                         	xref	_EE_ApplicationMode
3922                         	xref	_EE_oo_IRQ_disable_count
3923                         	xref	f_ErrorHook
3924                         	xdef	f_EE_oo_GetAlarm
3925                         	xref	_EE_oo_ErrorHook_data
3926                         	xref	_EE_oo_ErrorHook_ServiceID
3927                         	xref	_EE_alarm_RAM
3928                         	xref	_EE_alarm_ROM
3929                         	xref	_EE_counter_RAM
3930                         	xref	_EE_stkfirst
3931                         	xref	_EE_th_next
3932                         	xref	_EE_th_status
3933                         	xref	_EE_buttons_initialized
3934                         	xref	f_EE_s12xs_terminate_task
3935                         	xref	f_EE_s12xs_terminate_savestk
3936                         	xref	_EE_IRQ_nesting_level
3937                         	xref	f_EE_s12xs_hal_stkchange
3938                         	xref	f_EE_s12xs_hal_ready2stacked
3939                         	xref	_EE_hal_endcycle_next_tos
3940                         	xref	_EE_hal_endcycle_next_thread
3941                         	xref	_EE_terminate_real_th_body
3942                         	xref	_EE_terminate_data
3943                         	xref	_EE_s12xs_thread_tos
3944                         	xref	_EE_hal_thread_body
3964                         	end
