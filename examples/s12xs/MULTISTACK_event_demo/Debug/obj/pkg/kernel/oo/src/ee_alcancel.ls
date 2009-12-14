   1                         ; C Compiler for S12X [COSMIC Software].
   2                         ; Generator (Limited) V4.7.11.2 - 16 Mar 2009
   3                         ; Optimizer V4.6.16 - 02 Dec 2008
3749                         ; 56 StatusType EE_oo_CancelAlarm(AlarmType AlarmID)
3749                         ; 57 {
3750                         .ftext:	section	.text
3751  0000                   f_EE_oo_CancelAlarm:
3753  0000 3b                	pshd	
3754  0001 1b98              	leas	-8,s
3755       00000008          OFST:	set	8
3758                         ; 101   retvalue = _asm("tfr ccr,b\n");	// save CCR register (I bit)
3762  0003 b721              	tfr	ccr,b
3764                         ; 200   ASM_DIS_INT;
3767  0005 1410              	sei	
3769                         ; 104   return retvalue;
3772  0007 6c84              	std	OFST-4,s
3774                         ; 105 }
3776                         ; 96   if (!EE_alarm_RAM[AlarmID].used) {
3778  0009 ed88              	ldy	OFST+0,s
3779  000b 1858              	lsly	
3780  000d 1858              	lsly	
3781  000f 1858              	lsly	
3782  0011 ecea0000          	ldd	_EE_alarm_RAM,y
3783  0015 262e              	bne	L1003
3784                         ; 102     if (!EE_ErrorHook_nested_flag) {
3786  0017 fc0000            	ldd	_EE_ErrorHook_nested_flag
3787  001a 261a              	bne	L3003
3788                         ; 104       EE_oo_ErrorHook_ServiceID = OSServiceId_CancelAlarm;
3790  001c c610              	ldab	#16
3791  001e 7b0000            	stab	_EE_oo_ErrorHook_ServiceID
3792                         ; 105       EE_oo_ErrorHook_data.CancelAlarm_prm.AlarmID = AlarmID;
3794  0021 1805880000        	movw	OFST+0,s,_EE_oo_ErrorHook_data
3795                         ; 107       EE_ErrorHook_nested_flag = 1;
3797  0026 cc0001            	ldd	#1
3798  0029 7c0000            	std	_EE_ErrorHook_nested_flag
3799                         ; 108       ErrorHook(E_OS_NOFUNC);
3801  002c c605              	ldab	#5
3802  002e 4a000000          	call	f_ErrorHook
3804                         ; 109       EE_ErrorHook_nested_flag = 0;
3806  0032 18790000          	clrw	_EE_ErrorHook_nested_flag
3807  0036                   L3003:
3808                         ; 111   if(f & 0x10) 						// restore I bit
3811  0036 0f851004          	brclr	OFST-3,s,16,L5103
3812                         ; 200   ASM_DIS_INT;
3815  003a 1410              	sei	
3817  003c 2002              	bra	L7172
3818  003e                   L5103:
3819                         ; 191   ASM_EN_INT;
3822  003e 10ef              	cli	
3824  0040                   L7172:
3825                         ; 119     return E_OS_NOFUNC;
3828  0040 c605              	ldab	#5
3831  0042 1b8a              	leas	10,s
3832  0044 0a                	rtc	
3833  0045                   L1003:
3834                         ; 124   current = EE_counter_RAM[EE_alarm_ROM[AlarmID].c].first;
3836  0045 ec88              	ldd	OFST+0,s
3837  0047 cd000d            	ldy	#13
3838  004a 13                	emul	
3839  004b b746              	tfr	d,y
3840  004d eeea0000          	ldx	_EE_alarm_ROM,y
3841  0051 1848              	lslx	
3842  0053 1848              	lslx	
3843  0055 ece20002          	ldd	_EE_counter_RAM+2,x
3844  0059 6c82              	std	OFST-6,s
3845                         ; 126   if (current == AlarmID) {
3847  005b ac88              	cpd	OFST+0,s
3848  005d 261a              	bne	L5203
3849                         ; 128     EE_counter_RAM[EE_alarm_ROM[AlarmID].c].first = 
3849                         ; 129       EE_alarm_RAM[AlarmID].next;
3851  005f eeea0000          	ldx	_EE_alarm_ROM,y
3852  0063 1848              	lslx	
3853  0065 1848              	lslx	
3854  0067 ed88              	ldy	OFST+0,s
3855  0069 1858              	lsly	
3856  006b 1858              	lsly	
3857  006d 1858              	lsly	
3858  006f 1802ea0006e20002  	movw	_EE_alarm_RAM+6,y,_EE_counter_RAM+2,x
3860  0077 202b              	bra	L3203
3861  0079                   L5203:
3862                         ; 133       previous = current;
3864  0079 b746              	tfr	d,y
3865  007b 6d86              	sty	OFST-2,s
3866                         ; 134       current = EE_alarm_RAM[current].next;
3868  007d 1858              	lsly	
3869  007f 1858              	lsly	
3870  0081 1858              	lsly	
3871  0083 ecea0006          	ldd	_EE_alarm_RAM+6,y
3872  0087 6c82              	std	OFST-6,s
3873                         ; 135     } while (current != AlarmID);
3875  0089 ac88              	cpd	OFST+0,s
3876  008b 26ec              	bne	L5203
3877                         ; 136     EE_alarm_RAM[previous].next = EE_alarm_RAM[AlarmID].next;
3879  008d cc0006            	ldd	#_EE_alarm_RAM+6
3880  0090 ed86              	ldy	OFST-2,s
3881  0092 1858              	lsly	
3882  0094 1858              	lsly	
3883  0096 1858              	lsly	
3884  0098 ee88              	ldx	OFST+0,s
3885  009a 1848              	lslx	
3886  009c 1848              	lslx	
3887  009e 1848              	lslx	
3888  00a0 1802e6ee          	movw	d,x,d,y
3889  00a4                   L3203:
3890                         ; 139   if (EE_alarm_RAM[AlarmID].next != -1) {
3892  00a4 ed88              	ldy	OFST+0,s
3893  00a6 1858              	lsly	
3894  00a8 1858              	lsly	
3895  00aa 1858              	lsly	
3896  00ac ecea0006          	ldd	_EE_alarm_RAM+6,y
3897  00b0 048426            	ibeq	d,L3303
3898                         ; 140     EE_alarm_RAM[EE_alarm_RAM[AlarmID].next].delta +=
3898                         ; 141       EE_alarm_RAM[AlarmID].delta;
3900  00b3 ed88              	ldy	OFST+0,s
3901  00b5 1858              	lsly	
3902  00b7 1858              	lsly	
3903  00b9 1858              	lsly	
3904  00bb eeea0006          	ldx	_EE_alarm_RAM+6,y
3905  00bf 1848              	lslx	
3906  00c1 1848              	lslx	
3907  00c3 1848              	lslx	
3908  00c5 ed88              	ldy	OFST+0,s
3909  00c7 1858              	lsly	
3910  00c9 1858              	lsly	
3911  00cb 1858              	lsly	
3912  00cd ece20004          	ldd	_EE_alarm_RAM+4,x
3913  00d1 e3ea0004          	addd	_EE_alarm_RAM+4,y
3914  00d5 6ce20004          	std	_EE_alarm_RAM+4,x
3915  00d9                   L3303:
3916                         ; 144   EE_alarm_RAM[AlarmID].used = 0;
3918  00d9 ed88              	ldy	OFST+0,s
3919  00db 1858              	lsly	
3920  00dd 1858              	lsly	
3921  00df 1858              	lsly	
3922  00e1 1869ea0000        	clrw	_EE_alarm_RAM,y
3923                         ; 111   if(f & 0x10) 						// restore I bit
3926  00e6 0f851004          	brclr	OFST-3,s,16,L5403
3927                         ; 200   ASM_DIS_INT;
3930  00ea 1410              	sei	
3932  00ec 2002              	bra	L1372
3933  00ee                   L5403:
3934                         ; 191   ASM_EN_INT;
3937  00ee 10ef              	cli	
3939  00f0                   L1372:
3940                         ; 152   return E_OK;
3943  00f0 c7                	clrb	
3946  00f1 1b8a              	leas	10,s
3947  00f3 0a                	rtc	
3959                         	xref	_EE_ErrorHook_nested_flag
3960                         	xref	_EE_pit0_initialized
3961                         	xref	_EE_ApplicationMode
3962                         	xref	_EE_oo_IRQ_disable_count
3963                         	xref	f_ErrorHook
3964                         	xdef	f_EE_oo_CancelAlarm
3965                         	xref	_EE_oo_ErrorHook_data
3966                         	xref	_EE_oo_ErrorHook_ServiceID
3967                         	xref	_EE_alarm_RAM
3968                         	xref	_EE_alarm_ROM
3969                         	xref	_EE_counter_RAM
3970                         	xref	_EE_stkfirst
3971                         	xref	_EE_th_next
3972                         	xref	_EE_th_status
3973                         	xref	_EE_buttons_initialized
3974                         	xref	f_EE_s12xs_terminate_task
3975                         	xref	f_EE_s12xs_terminate_savestk
3976                         	xref	_EE_IRQ_nesting_level
3977                         	xref	f_EE_s12xs_hal_stkchange
3978                         	xref	f_EE_s12xs_hal_ready2stacked
3979                         	xref	_EE_hal_endcycle_next_tos
3980                         	xref	_EE_hal_endcycle_next_thread
3981                         	xref	_EE_terminate_real_th_body
3982                         	xref	_EE_terminate_data
3983                         	xref	_EE_s12xs_thread_tos
3984                         	xref	_EE_hal_thread_body
4004                         	end
