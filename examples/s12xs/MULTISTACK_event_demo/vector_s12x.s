; C Compiler for S12X [COSMIC Software].
; Generator (Limited) V4.7.11.2 - 16 Mar 2009
; Optimizer V4.6.16 - 02 Dec 2008
	nolist
_PORTA:	equ	0
	xdef	_PORTA
_PORTB:	equ	1
	xdef	_PORTB
_DDRA:	equ	2
	xdef	_DDRA
_DDRB:	equ	3
	xdef	_DDRB
_PORTE:	equ	8
	xdef	_PORTE
_DDRE:	equ	9
	xdef	_DDRE
_PUCR:	equ	12
	xdef	_PUCR
_RDRIV:	equ	13
	xdef	_RDRIV
_MODE:	equ	11
	xdef	_MODE
_GPAGE:	equ	16
	xdef	_GPAGE
_DIRECT:	equ	17
	xdef	_DIRECT
_MMCCTL1:	equ	19
	xdef	_MMCCTL1
_PPAGE:	equ	21
	xdef	_PPAGE
_RPAGE:	equ	22
	xdef	_RPAGE
_EPAGE:	equ	23
	xdef	_EPAGE
_PARTID:	equ	26
	xdef	_PARTID
_PARTIDH:	equ	26
	xdef	_PARTIDH
_PARTIDL:	equ	27
	xdef	_PARTIDL
_ECLKCTL:	equ	28
	xdef	_ECLKCTL
_IRQCR:	equ	30
	xdef	_IRQCR
_DBGC1:	equ	32
	xdef	_DBGC1
_DBGSR:	equ	33
	xdef	_DBGSR
_DBGTCR:	equ	34
	xdef	_DBGTCR
_DBGC2:	equ	35
	xdef	_DBGC2
_DBGTB:	equ	36
	xdef	_DBGTB
_DBGCNT:	equ	38
	xdef	_DBGCNT
_DBGSCRX:	equ	39
	xdef	_DBGSCRX
_DBGMFR:	equ	39
	xdef	_DBGMFR
_DBGXCTL:	equ	40
	xdef	_DBGXCTL
_DBGXAH:	equ	41
	xdef	_DBGXAH
_DBGXAM:	equ	42
	xdef	_DBGXAM
_DBGXAL:	equ	43
	xdef	_DBGXAL
_DBGXD:	equ	44
	xdef	_DBGXD
_DBGXDH:	equ	44
	xdef	_DBGXDH
_DBGXDL:	equ	45
	xdef	_DBGXDL
_DBGXDM:	equ	46
	xdef	_DBGXDM
_DBGXDHM:	equ	46
	xdef	_DBGXDHM
_DBGXDLM:	equ	47
	xdef	_DBGXDLM
_PORTK:	equ	50
	xdef	_PORTK
_DDRK:	equ	51
	xdef	_DDRK
_SYNR:	equ	52
	xdef	_SYNR
_REFDV:	equ	53
	xdef	_REFDV
_POSTDIV:	equ	54
	xdef	_POSTDIV
_CRGFLG:	equ	55
	xdef	_CRGFLG
_CRGINT:	equ	56
	xdef	_CRGINT
_CLKSEL:	equ	57
	xdef	_CLKSEL
_PLLCTL:	equ	58
	xdef	_PLLCTL
_RTICTL:	equ	59
	xdef	_RTICTL
_COPCTL:	equ	60
	xdef	_COPCTL
_FORBYP:	equ	61
	xdef	_FORBYP
_CTCTL:	equ	62
	xdef	_CTCTL
_ARMCOP:	equ	63
	xdef	_ARMCOP
_TIOS:	equ	64
	xdef	_TIOS
_CFORC:	equ	65
	xdef	_CFORC
_OC7M:	equ	66
	xdef	_OC7M
_OC7D:	equ	67
	xdef	_OC7D
_TCNT:	equ	68
	xdef	_TCNT
_TCNTH:	equ	68
	xdef	_TCNTH
_TCNTL:	equ	69
	xdef	_TCNTL
_TSCR1:	equ	70
	xdef	_TSCR1
_TTOV:	equ	71
	xdef	_TTOV
_TCTL1:	equ	72
	xdef	_TCTL1
_TCTL2:	equ	73
	xdef	_TCTL2
_TCTL3:	equ	74
	xdef	_TCTL3
_TCTL4:	equ	75
	xdef	_TCTL4
_TIE:	equ	76
	xdef	_TIE
_TSCR2:	equ	77
	xdef	_TSCR2
_TFLG1:	equ	78
	xdef	_TFLG1
_TFLG2:	equ	79
	xdef	_TFLG2
_TC0:	equ	80
	xdef	_TC0
_TC1:	equ	82
	xdef	_TC1
_TC2:	equ	84
	xdef	_TC2
_TC3:	equ	86
	xdef	_TC3
_TC4:	equ	88
	xdef	_TC4
_TC5:	equ	90
	xdef	_TC5
_TC6:	equ	92
	xdef	_TC6
_TC7:	equ	94
	xdef	_TC7
_PACTL:	equ	96
	xdef	_PACTL
_PAFLG:	equ	97
	xdef	_PAFLG
_PACNT:	equ	98
	xdef	_PACNT
_PACNTH:	equ	98
	xdef	_PACNTH
_PACNTL:	equ	99
	xdef	_PACNTL
_OCPD:	equ	108
	xdef	_OCPD
_PTPSR:	equ	110
	xdef	_PTPSR
_SCI0BD:	equ	200
	xdef	_SCI0BD
_SCI0BDH:	equ	200
	xdef	_SCI0BDH
_SCI0BDL:	equ	201
	xdef	_SCI0BDL
_SCI0CR1:	equ	202
	xdef	_SCI0CR1
_SCI0ASR1:	equ	200
	xdef	_SCI0ASR1
_SCI0ACR1:	equ	201
	xdef	_SCI0ACR1
_SCI0ACR2:	equ	202
	xdef	_SCI0ACR2
_SCI0CR2:	equ	203
	xdef	_SCI0CR2
_SCI0SR1:	equ	204
	xdef	_SCI0SR1
_SCI0SR2:	equ	205
	xdef	_SCI0SR2
_SCI0DR:	equ	206
	xdef	_SCI0DR
_SCI0DRH:	equ	206
	xdef	_SCI0DRH
_SCI0DRL:	equ	207
	xdef	_SCI0DRL
_SCI1BD:	equ	208
	xdef	_SCI1BD
_SCI1BDH:	equ	208
	xdef	_SCI1BDH
_SCI1BDL:	equ	209
	xdef	_SCI1BDL
_SCI1CR1:	equ	210
	xdef	_SCI1CR1
_SCI1ASR1:	equ	208
	xdef	_SCI1ASR1
_SCI1ACR1:	equ	209
	xdef	_SCI1ACR1
_SCI1ACR2:	equ	210
	xdef	_SCI1ACR2
_SCI1CR2:	equ	211
	xdef	_SCI1CR2
_SCI1SR1:	equ	212
	xdef	_SCI1SR1
_SCI1SR2:	equ	213
	xdef	_SCI1SR2
_SCI1DRH:	equ	214
	xdef	_SCI1DRH
_SCI1DRL:	equ	215
	xdef	_SCI1DRL
_SPI0CR1:	equ	216
	xdef	_SPI0CR1
_SPI0CR2:	equ	217
	xdef	_SPI0CR2
_SPI0BR:	equ	218
	xdef	_SPI0BR
_SPI0SR:	equ	219
	xdef	_SPI0SR
_SPI0DRH:	equ	220
	xdef	_SPI0DRH
_SPI0DRL:	equ	221
	xdef	_SPI0DRL
_FCLKDIV:	equ	256
	xdef	_FCLKDIV
_FSEC:	equ	257
	xdef	_FSEC
_FCCOBIX:	equ	258
	xdef	_FCCOBIX
_FECCRIX:	equ	259
	xdef	_FECCRIX
_FCNFG:	equ	260
	xdef	_FCNFG
_FERCNFG:	equ	261
	xdef	_FERCNFG
_FSTAT:	equ	262
	xdef	_FSTAT
_FERSTAT:	equ	263
	xdef	_FERSTAT
_FPROT:	equ	264
	xdef	_FPROT
_DFPROT:	equ	265
	xdef	_DFPROT
_FCCOB:	equ	266
	xdef	_FCCOB
_FCCOBHI:	equ	266
	xdef	_FCCOBHI
_FCCOBLO:	equ	267
	xdef	_FCCOBLO
_FEECR:	equ	270
	xdef	_FEECR
_FEECRHI:	equ	270
	xdef	_FEECRHI
_FEECRLO:	equ	271
	xdef	_FEECRLO
_FOPT:	equ	272
	xdef	_FOPT
_IVBR:	equ	289
	xdef	_IVBR
_INT_XGPRIO:	equ	294
	xdef	_INT_XGPRIO
_INT_CFADDR:	equ	295
	xdef	_INT_CFADDR
_INT_CFDATA0:	equ	296
	xdef	_INT_CFDATA0
_INT_CFDATA1:	equ	297
	xdef	_INT_CFDATA1
_INT_CFDATA2:	equ	298
	xdef	_INT_CFDATA2
_INT_CFDATA3:	equ	299
	xdef	_INT_CFDATA3
_INT_CFDATA4:	equ	300
	xdef	_INT_CFDATA4
_INT_CFDATA5:	equ	301
	xdef	_INT_CFDATA5
_INT_CFDATA6:	equ	302
	xdef	_INT_CFDATA6
_INT_CFDATA7:	equ	303
	xdef	_INT_CFDATA7
_CAN0CTL0:	equ	320
	xdef	_CAN0CTL0
_CAN0CTL1:	equ	321
	xdef	_CAN0CTL1
_CAN0BTR0:	equ	322
	xdef	_CAN0BTR0
_CAN0BTR1:	equ	323
	xdef	_CAN0BTR1
_CAN0RFLG:	equ	324
	xdef	_CAN0RFLG
_CAN0RIER:	equ	325
	xdef	_CAN0RIER
_CAN0TFLG:	equ	326
	xdef	_CAN0TFLG
_CAN0TIER:	equ	327
	xdef	_CAN0TIER
_CAN0TARQ:	equ	328
	xdef	_CAN0TARQ
_CAN0TAAK:	equ	329
	xdef	_CAN0TAAK
_CAN0TBSEL:	equ	330
	xdef	_CAN0TBSEL
_CAN0IDAC:	equ	331
	xdef	_CAN0IDAC
_CAN0MISC:	equ	333
	xdef	_CAN0MISC
_CAN0RXERR:	equ	334
	xdef	_CAN0RXERR
_CAN0TXERR:	equ	335
	xdef	_CAN0TXERR
_CAN0IDAR0:	equ	336
	xdef	_CAN0IDAR0
_CAN0IDAR1:	equ	337
	xdef	_CAN0IDAR1
_CAN0IDAR2:	equ	338
	xdef	_CAN0IDAR2
_CAN0IDAR3:	equ	339
	xdef	_CAN0IDAR3
_CAN0IDMR0:	equ	340
	xdef	_CAN0IDMR0
_CAN0IDMR1:	equ	341
	xdef	_CAN0IDMR1
_CAN0IDMR2:	equ	342
	xdef	_CAN0IDMR2
_CAN0IDMR3:	equ	343
	xdef	_CAN0IDMR3
_CAN0IDAR4:	equ	344
	xdef	_CAN0IDAR4
_CAN0IDAR5:	equ	345
	xdef	_CAN0IDAR5
_CAN0IDAR6:	equ	346
	xdef	_CAN0IDAR6
_CAN0IDAR7:	equ	347
	xdef	_CAN0IDAR7
_CAN0IDMR4:	equ	348
	xdef	_CAN0IDMR4
_CAN0IDMR5:	equ	349
	xdef	_CAN0IDMR5
_CAN0IDMR6:	equ	350
	xdef	_CAN0IDMR6
_CAN0IDMR7:	equ	351
	xdef	_CAN0IDMR7
_CAN0RXFG:	equ	352
	xdef	_CAN0RXFG
_CAN0TXFG:	equ	368
	xdef	_CAN0TXFG
_PTT:	equ	576
	xdef	_PTT
_PTIT:	equ	577
	xdef	_PTIT
_DDRT:	equ	578
	xdef	_DDRT
_RDRT:	equ	579
	xdef	_RDRT
_PERT:	equ	580
	xdef	_PERT
_PPST:	equ	581
	xdef	_PPST
_PTTRR:	equ	583
	xdef	_PTTRR
_PTS:	equ	584
	xdef	_PTS
_PTIS:	equ	585
	xdef	_PTIS
_DDRS:	equ	586
	xdef	_DDRS
_RDRS:	equ	587
	xdef	_RDRS
_PERS:	equ	588
	xdef	_PERS
_PPSS:	equ	589
	xdef	_PPSS
_WOMS:	equ	590
	xdef	_WOMS
_PTM:	equ	592
	xdef	_PTM
_PTIM:	equ	593
	xdef	_PTIM
_DDRM:	equ	594
	xdef	_DDRM
_RDRM:	equ	595
	xdef	_RDRM
_PERM:	equ	596
	xdef	_PERM
_PPSM:	equ	597
	xdef	_PPSM
_WOMM:	equ	598
	xdef	_WOMM
_MODRR:	equ	599
	xdef	_MODRR
_PTP:	equ	600
	xdef	_PTP
_PTIP:	equ	601
	xdef	_PTIP
_DDRP:	equ	602
	xdef	_DDRP
_RDRP:	equ	603
	xdef	_RDRP
_PERP:	equ	604
	xdef	_PERP
_PPSP:	equ	605
	xdef	_PPSP
_PIEP:	equ	606
	xdef	_PIEP
_PIFP:	equ	607
	xdef	_PIFP
_PTH:	equ	608
	xdef	_PTH
_PTIH:	equ	609
	xdef	_PTIH
_DDRH:	equ	610
	xdef	_DDRH
_RDRH:	equ	611
	xdef	_RDRH
_PERH:	equ	612
	xdef	_PERH
_PPSH:	equ	613
	xdef	_PPSH
_PIEH:	equ	614
	xdef	_PIEH
_PIFH:	equ	615
	xdef	_PIFH
_PTJ:	equ	616
	xdef	_PTJ
_PTIJ:	equ	617
	xdef	_PTIJ
_DDRJ:	equ	618
	xdef	_DDRJ
_RDRJ:	equ	619
	xdef	_RDRJ
_PERJ:	equ	620
	xdef	_PERJ
_PPSJ:	equ	621
	xdef	_PPSJ
_PIEJ:	equ	622
	xdef	_PIEJ
_PIFJ:	equ	623
	xdef	_PIFJ
_PT0AD0:	equ	624
	xdef	_PT0AD0
_PT1AD0:	equ	625
	xdef	_PT1AD0
_DDR0AD0:	equ	626
	xdef	_DDR0AD0
_DDR1AD0:	equ	627
	xdef	_DDR1AD0
_RDR0AD0:	equ	628
	xdef	_RDR0AD0
_RDR1AD0:	equ	629
	xdef	_RDR1AD0
_PER0AD0:	equ	630
	xdef	_PER0AD0
_PER1AD0:	equ	631
	xdef	_PER1AD0
_ATD0CTL0:	equ	704
	xdef	_ATD0CTL0
_ATD0CTL1:	equ	705
	xdef	_ATD0CTL1
_ATD0CTL2:	equ	706
	xdef	_ATD0CTL2
_ATD0CTL3:	equ	707
	xdef	_ATD0CTL3
_ATD0CTL4:	equ	708
	xdef	_ATD0CTL4
_ATD0CTL5:	equ	709
	xdef	_ATD0CTL5
_ATD0STAT0:	equ	710
	xdef	_ATD0STAT0
_ATD0CMPE:	equ	712
	xdef	_ATD0CMPE
_ATD0CMPEH:	equ	712
	xdef	_ATD0CMPEH
_ATD0CMPEL:	equ	713
	xdef	_ATD0CMPEL
_ATD0STAT2:	equ	714
	xdef	_ATD0STAT2
_ATD0STAT2H:	equ	714
	xdef	_ATD0STAT2H
_ATD0STAT2L:	equ	715
	xdef	_ATD0STAT2L
_ATD0DIEN:	equ	716
	xdef	_ATD0DIEN
_ATD0DIENH:	equ	716
	xdef	_ATD0DIENH
_ATD0DIENL:	equ	717
	xdef	_ATD0DIENL
_ATD0CMPHT:	equ	718
	xdef	_ATD0CMPHT
_ATD0DR:	equ	720
	xdef	_ATD0DR
_ATD0DR0:	equ	720
	xdef	_ATD0DR0
_ATD0DR1:	equ	722
	xdef	_ATD0DR1
_ATD0DR2:	equ	724
	xdef	_ATD0DR2
_ATD0DR3:	equ	726
	xdef	_ATD0DR3
_ATD0DR4:	equ	728
	xdef	_ATD0DR4
_ATD0DR5:	equ	730
	xdef	_ATD0DR5
_ATD0DR6:	equ	732
	xdef	_ATD0DR6
_ATD0DR7:	equ	734
	xdef	_ATD0DR7
_ATD0DR8:	equ	736
	xdef	_ATD0DR8
_ATD0DR9:	equ	738
	xdef	_ATD0DR9
_ATD0DR10:	equ	740
	xdef	_ATD0DR10
_ATD0DR11:	equ	742
	xdef	_ATD0DR11
_ATD0DR12:	equ	744
	xdef	_ATD0DR12
_ATD0DR13:	equ	746
	xdef	_ATD0DR13
_ATD0DR14:	equ	748
	xdef	_ATD0DR14
_ATD0DR15:	equ	750
	xdef	_ATD0DR15
_VREGHTCL:	equ	752
	xdef	_VREGHTCL
_VREGCTRL:	equ	753
	xdef	_VREGCTRL
_VREGAPICL:	equ	754
	xdef	_VREGAPICL
_VREGAPITR:	equ	755
	xdef	_VREGAPITR
_VREGAPIR:	equ	756
	xdef	_VREGAPIR
_VREGAPIRH:	equ	756
	xdef	_VREGAPIRH
_VREGAPIRL:	equ	757
	xdef	_VREGAPIRL
_VREGHTTR:	equ	759
	xdef	_VREGHTTR
_PWME:	equ	768
	xdef	_PWME
_PWMPOL:	equ	769
	xdef	_PWMPOL
_PWMCLK:	equ	770
	xdef	_PWMCLK
_PWMPRCLK:	equ	771
	xdef	_PWMPRCLK
_PWMCAE:	equ	772
	xdef	_PWMCAE
_PWMCTL:	equ	773
	xdef	_PWMCTL
_PWMTST:	equ	774
	xdef	_PWMTST
_PWMPRSC:	equ	775
	xdef	_PWMPRSC
_PWMSCLA:	equ	776
	xdef	_PWMSCLA
_PWMSCLB:	equ	777
	xdef	_PWMSCLB
_PWMSCNTA:	equ	778
	xdef	_PWMSCNTA
_PWMSCNTB:	equ	779
	xdef	_PWMSCNTB
_PWMCNT0:	equ	780
	xdef	_PWMCNT0
_PWMCNT1:	equ	781
	xdef	_PWMCNT1
_PWMCNT2:	equ	782
	xdef	_PWMCNT2
_PWMCNT3:	equ	783
	xdef	_PWMCNT3
_PWMCNT4:	equ	784
	xdef	_PWMCNT4
_PWMCNT5:	equ	785
	xdef	_PWMCNT5
_PWMCNT6:	equ	786
	xdef	_PWMCNT6
_PWMCNT7:	equ	787
	xdef	_PWMCNT7
_PWMPER0:	equ	788
	xdef	_PWMPER0
_PWMPER1:	equ	789
	xdef	_PWMPER1
_PWMPER2:	equ	790
	xdef	_PWMPER2
_PWMPER3:	equ	791
	xdef	_PWMPER3
_PWMPER4:	equ	792
	xdef	_PWMPER4
_PWMPER5:	equ	793
	xdef	_PWMPER5
_PWMPER6:	equ	794
	xdef	_PWMPER6
_PWMPER7:	equ	795
	xdef	_PWMPER7
_PWMDTY0:	equ	796
	xdef	_PWMDTY0
_PWMDTY1:	equ	797
	xdef	_PWMDTY1
_PWMDTY2:	equ	798
	xdef	_PWMDTY2
_PWMDTY3:	equ	799
	xdef	_PWMDTY3
_PWMDTY4:	equ	800
	xdef	_PWMDTY4
_PWMDTY5:	equ	801
	xdef	_PWMDTY5
_PWMDTY6:	equ	802
	xdef	_PWMDTY6
_PWMDTY7:	equ	803
	xdef	_PWMDTY7
_PWMSDN:	equ	804
	xdef	_PWMSDN
_PITCFLMT:	equ	832
	xdef	_PITCFLMT
_PITFLT:	equ	833
	xdef	_PITFLT
_PITCE:	equ	834
	xdef	_PITCE
_PITMUX:	equ	835
	xdef	_PITMUX
_PITINTE:	equ	836
	xdef	_PITINTE
_PITTF:	equ	837
	xdef	_PITTF
_PITMTLD0:	equ	838
	xdef	_PITMTLD0
_PITMTLD1:	equ	839
	xdef	_PITMTLD1
_PITLD0:	equ	840
	xdef	_PITLD0
_PITCNT0:	equ	842
	xdef	_PITCNT0
_PITLD1:	equ	844
	xdef	_PITLD1
_PITCNT1:	equ	846
	xdef	_PITCNT1
_PITLD2:	equ	848
	xdef	_PITLD2
_PITCNT2:	equ	850
	xdef	_PITCNT2
_PITLD3:	equ	852
	xdef	_PITLD3
_PITCNT3:	equ	854
	xdef	_PITCNT3
	list
	switch	.debug
	.dopt	"../hs12xsregs.h:0",L2
	.dfile	"../hs12xsregs.h"
L3:
	dc.l	L7
	dc.l	L5
L7:
	dc.b	"../hs12xsregs.h",0
	dc.b	140
L5:
	dc.l	0
	dc.l	L3
	dc.l	0
	dc.l	1
	dc.l	408
	dc.l	0
	dc.l	0
	dc.l	L11
L31:
	dc.b	"PITCNT3",0
	dc.b	8
L51:
	dc.l	16384
L71:
	dc.b	"PITLD3",0
	dc.b	8
L12:
	dc.l	16384
L32:
	dc.b	"PITCNT2",0
	dc.b	8
L52:
	dc.l	16384
L72:
	dc.b	"PITLD2",0
	dc.b	8
L13:
	dc.l	16384
L33:
	dc.b	"PITCNT1",0
	dc.b	8
L53:
	dc.l	16384
L73:
	dc.b	"PITLD1",0
	dc.b	8
L14:
	dc.l	16384
L34:
	dc.b	"PITCNT0",0
	dc.b	8
L54:
	dc.l	16384
L74:
	dc.b	"PITLD0",0
	dc.b	8
L15:
	dc.l	16384
L35:
	dc.b	"PITMTLD1",0
	dc.b	8
L55:
	dc.l	16384
L75:
	dc.b	"PITMTLD0",0
	dc.b	8
L16:
	dc.l	16384
L36:
	dc.b	"PITTF",0
	dc.b	8
L56:
	dc.l	16384
L76:
	dc.b	"PITINTE",0
	dc.b	8
L17:
	dc.l	16384
L37:
	dc.b	"PITMUX",0
	dc.b	8
L57:
	dc.l	16384
L77:
	dc.b	"PITCE",0
	dc.b	8
L101:
	dc.l	16384
L301:
	dc.b	"PITFLT",0
	dc.b	8
L501:
	dc.l	16384
L701:
	dc.b	"PITCFLMT",0
	dc.b	8
L111:
	dc.l	16384
L311:
	dc.b	"PWMSDN",0
	dc.b	8
L511:
	dc.l	16384
L711:
	dc.b	"PWMDTY7",0
	dc.b	8
L121:
	dc.l	16384
L321:
	dc.b	"PWMDTY6",0
	dc.b	8
L521:
	dc.l	16384
L721:
	dc.b	"PWMDTY5",0
	dc.b	8
L131:
	dc.l	16384
L331:
	dc.b	"PWMDTY4",0
	dc.b	8
L531:
	dc.l	16384
L731:
	dc.b	"PWMDTY3",0
	dc.b	8
L141:
	dc.l	16384
L341:
	dc.b	"PWMDTY2",0
	dc.b	8
L541:
	dc.l	16384
L741:
	dc.b	"PWMDTY1",0
	dc.b	8
L151:
	dc.l	16384
L351:
	dc.b	"PWMDTY0",0
	dc.b	8
L551:
	dc.l	16384
L751:
	dc.b	"PWMPER7",0
	dc.b	8
L161:
	dc.l	16384
L361:
	dc.b	"PWMPER6",0
	dc.b	8
L561:
	dc.l	16384
L761:
	dc.b	"PWMPER5",0
	dc.b	8
L171:
	dc.l	16384
L371:
	dc.b	"PWMPER4",0
	dc.b	8
L571:
	dc.l	16384
L771:
	dc.b	"PWMPER3",0
	dc.b	8
L102:
	dc.l	16384
L302:
	dc.b	"PWMPER2",0
	dc.b	8
L502:
	dc.l	16384
L702:
	dc.b	"PWMPER1",0
	dc.b	8
L112:
	dc.l	16384
L312:
	dc.b	"PWMPER0",0
	dc.b	8
L512:
	dc.l	16384
L712:
	dc.b	"PWMCNT7",0
	dc.b	8
L122:
	dc.l	16384
L322:
	dc.b	"PWMCNT6",0
	dc.b	8
L522:
	dc.l	16384
L722:
	dc.b	"PWMCNT5",0
	dc.b	8
L132:
	dc.l	16384
L332:
	dc.b	"PWMCNT4",0
	dc.b	8
L532:
	dc.l	16384
L732:
	dc.b	"PWMCNT3",0
	dc.b	8
L142:
	dc.l	16384
L342:
	dc.b	"PWMCNT2",0
	dc.b	8
L542:
	dc.l	16384
L742:
	dc.b	"PWMCNT1",0
	dc.b	8
L152:
	dc.l	16384
L352:
	dc.b	"PWMCNT0",0
	dc.b	8
L552:
	dc.l	16384
L752:
	dc.b	"PWMSCNTB",0
	dc.b	8
L162:
	dc.l	16384
L362:
	dc.b	"PWMSCNTA",0
	dc.b	8
L562:
	dc.l	16384
L762:
	dc.b	"PWMSCLB",0
	dc.b	8
L172:
	dc.l	16384
L372:
	dc.b	"PWMSCLA",0
	dc.b	8
L572:
	dc.l	16384
L772:
	dc.b	"PWMPRSC",0
	dc.b	8
L103:
	dc.l	16384
L303:
	dc.b	"PWMTST",0
	dc.b	8
L503:
	dc.l	16384
L703:
	dc.b	"PWMCTL",0
	dc.b	8
L113:
	dc.l	16384
L313:
	dc.b	"PWMCAE",0
	dc.b	8
L513:
	dc.l	16384
L713:
	dc.b	"PWMPRCLK",0
	dc.b	8
L123:
	dc.l	16384
L323:
	dc.b	"PWMCLK",0
	dc.b	8
L523:
	dc.l	16384
L723:
	dc.b	"PWMPOL",0
	dc.b	8
L133:
	dc.l	16384
L333:
	dc.b	"PWME",0
	dc.b	8
L533:
	dc.l	16384
L733:
	dc.b	"VREGHTTR",0
	dc.b	8
L143:
	dc.l	16384
L343:
	dc.b	"VREGAPIRL",0
	dc.b	8
L543:
	dc.l	16384
L743:
	dc.b	"VREGAPIRH",0
	dc.b	8
L153:
	dc.l	16384
L353:
	dc.b	"VREGAPIR",0
	dc.b	8
L553:
	dc.l	16384
L753:
	dc.b	"VREGAPITR",0
	dc.b	8
L163:
	dc.l	16384
L363:
	dc.b	"VREGAPICL",0
	dc.b	8
L563:
	dc.l	16384
L763:
	dc.b	"VREGCTRL",0
	dc.b	8
L173:
	dc.l	16384
L373:
	dc.b	"VREGHTCL",0
	dc.b	8
L573:
	dc.l	16384
L773:
	dc.b	"ATD0DR15",0
	dc.b	8
L104:
	dc.l	16384
L304:
	dc.b	"ATD0DR14",0
	dc.b	8
L504:
	dc.l	16384
L704:
	dc.b	"ATD0DR13",0
	dc.b	8
L114:
	dc.l	16384
L314:
	dc.b	"ATD0DR12",0
	dc.b	8
L514:
	dc.l	16384
L714:
	dc.b	"ATD0DR11",0
	dc.b	8
L124:
	dc.l	16384
L324:
	dc.b	"ATD0DR10",0
	dc.b	8
L524:
	dc.l	16384
L724:
	dc.b	"ATD0DR9",0
	dc.b	8
L134:
	dc.l	16384
L334:
	dc.b	"ATD0DR8",0
	dc.b	8
L534:
	dc.l	16384
L734:
	dc.b	"ATD0DR7",0
	dc.b	8
L144:
	dc.l	16384
L344:
	dc.b	"ATD0DR6",0
	dc.b	8
L544:
	dc.l	16384
L744:
	dc.b	"ATD0DR5",0
	dc.b	8
L154:
	dc.l	16384
L354:
	dc.b	"ATD0DR4",0
	dc.b	8
L554:
	dc.l	16384
L754:
	dc.b	"ATD0DR3",0
	dc.b	8
L164:
	dc.l	16384
L364:
	dc.b	"ATD0DR2",0
	dc.b	8
L564:
	dc.l	16384
L764:
	dc.b	"ATD0DR1",0
	dc.b	8
L174:
	dc.l	16384
L374:
	dc.b	"ATD0DR0",0
	dc.b	8
L574:
	dc.l	16384
L774:
	dc.b	"ATD0DR",0
	dc.b	8
L105:
	dc.l	16384
	dc.l	16
L305:
	dc.b	"ATD0CMPHT",0
	dc.b	8
L505:
	dc.l	16384
L705:
	dc.b	"ATD0DIENL",0
	dc.b	8
L115:
	dc.l	16384
L315:
	dc.b	"ATD0DIENH",0
	dc.b	8
L515:
	dc.l	16384
L715:
	dc.b	"ATD0DIEN",0
	dc.b	8
L125:
	dc.l	16384
L325:
	dc.b	"ATD0STAT2L",0
	dc.b	8
L525:
	dc.l	16384
L725:
	dc.b	"ATD0STAT2H",0
	dc.b	8
L135:
	dc.l	16384
L335:
	dc.b	"ATD0STAT2",0
	dc.b	8
L535:
	dc.l	16384
L735:
	dc.b	"ATD0CMPEL",0
	dc.b	8
L145:
	dc.l	16384
L345:
	dc.b	"ATD0CMPEH",0
	dc.b	8
L545:
	dc.l	16384
L745:
	dc.b	"ATD0CMPE",0
	dc.b	8
L155:
	dc.l	16384
L355:
	dc.b	"ATD0STAT0",0
	dc.b	8
L555:
	dc.l	16384
L755:
	dc.b	"ATD0CTL5",0
	dc.b	8
L165:
	dc.l	16384
L365:
	dc.b	"ATD0CTL4",0
	dc.b	8
L565:
	dc.l	16384
L765:
	dc.b	"ATD0CTL3",0
	dc.b	8
L175:
	dc.l	16384
L375:
	dc.b	"ATD0CTL2",0
	dc.b	8
L575:
	dc.l	16384
L775:
	dc.b	"ATD0CTL1",0
	dc.b	8
L106:
	dc.l	16384
L306:
	dc.b	"ATD0CTL0",0
	dc.b	8
L506:
	dc.l	16384
L706:
	dc.b	"PER1AD0",0
	dc.b	8
L116:
	dc.l	16384
L316:
	dc.b	"PER0AD0",0
	dc.b	8
L516:
	dc.l	16384
L716:
	dc.b	"RDR1AD0",0
	dc.b	8
L126:
	dc.l	16384
L326:
	dc.b	"RDR0AD0",0
	dc.b	8
L526:
	dc.l	16384
L726:
	dc.b	"DDR1AD0",0
	dc.b	8
L136:
	dc.l	16384
L336:
	dc.b	"DDR0AD0",0
	dc.b	8
L536:
	dc.l	16384
L736:
	dc.b	"PT1AD0",0
	dc.b	8
L146:
	dc.l	16384
L346:
	dc.b	"PT0AD0",0
	dc.b	8
L546:
	dc.l	16384
L746:
	dc.b	"PIFJ",0
	dc.b	8
L156:
	dc.l	16384
L356:
	dc.b	"PIEJ",0
	dc.b	8
L556:
	dc.l	16384
L756:
	dc.b	"PPSJ",0
	dc.b	8
L166:
	dc.l	16384
L366:
	dc.b	"PERJ",0
	dc.b	8
L566:
	dc.l	16384
L766:
	dc.b	"RDRJ",0
	dc.b	8
L176:
	dc.l	16384
L376:
	dc.b	"DDRJ",0
	dc.b	8
L576:
	dc.l	16384
L776:
	dc.b	"PTIJ",0
	dc.b	8
L107:
	dc.l	16384
L307:
	dc.b	"PTJ",0
	dc.b	8
L507:
	dc.l	16384
L707:
	dc.b	"PIFH",0
	dc.b	8
L117:
	dc.l	16384
L317:
	dc.b	"PIEH",0
	dc.b	8
L517:
	dc.l	16384
L717:
	dc.b	"PPSH",0
	dc.b	8
L127:
	dc.l	16384
L327:
	dc.b	"PERH",0
	dc.b	8
L527:
	dc.l	16384
L727:
	dc.b	"RDRH",0
	dc.b	8
L137:
	dc.l	16384
L337:
	dc.b	"DDRH",0
	dc.b	8
L537:
	dc.l	16384
L737:
	dc.b	"PTIH",0
	dc.b	8
L147:
	dc.l	16384
L347:
	dc.b	"PTH",0
	dc.b	8
L547:
	dc.l	16384
L747:
	dc.b	"PIFP",0
	dc.b	8
L157:
	dc.l	16384
L357:
	dc.b	"PIEP",0
	dc.b	8
L557:
	dc.l	16384
L757:
	dc.b	"PPSP",0
	dc.b	8
L167:
	dc.l	16384
L367:
	dc.b	"PERP",0
	dc.b	8
L567:
	dc.l	16384
L767:
	dc.b	"RDRP",0
	dc.b	8
L177:
	dc.l	16384
L377:
	dc.b	"DDRP",0
	dc.b	8
L577:
	dc.l	16384
L777:
	dc.b	"PTIP",0
	dc.b	8
L1001:
	dc.l	16384
L3001:
	dc.b	"PTP",0
	dc.b	8
L5001:
	dc.l	16384
L7001:
	dc.b	"MODRR",0
	dc.b	8
L1101:
	dc.l	16384
L3101:
	dc.b	"WOMM",0
	dc.b	8
L5101:
	dc.l	16384
L7101:
	dc.b	"PPSM",0
	dc.b	8
L1201:
	dc.l	16384
L3201:
	dc.b	"PERM",0
	dc.b	8
L5201:
	dc.l	16384
L7201:
	dc.b	"RDRM",0
	dc.b	8
L1301:
	dc.l	16384
L3301:
	dc.b	"DDRM",0
	dc.b	8
L5301:
	dc.l	16384
L7301:
	dc.b	"PTIM",0
	dc.b	8
L1401:
	dc.l	16384
L3401:
	dc.b	"PTM",0
	dc.b	8
L5401:
	dc.l	16384
L7401:
	dc.b	"WOMS",0
	dc.b	8
L1501:
	dc.l	16384
L3501:
	dc.b	"PPSS",0
	dc.b	8
L5501:
	dc.l	16384
L7501:
	dc.b	"PERS",0
	dc.b	8
L1601:
	dc.l	16384
L3601:
	dc.b	"RDRS",0
	dc.b	8
L5601:
	dc.l	16384
L7601:
	dc.b	"DDRS",0
	dc.b	8
L1701:
	dc.l	16384
L3701:
	dc.b	"PTIS",0
	dc.b	8
L5701:
	dc.l	16384
L7701:
	dc.b	"PTS",0
	dc.b	8
L1011:
	dc.l	16384
L3011:
	dc.b	"PTTRR",0
	dc.b	8
L5011:
	dc.l	16384
L7011:
	dc.b	"PPST",0
	dc.b	8
L1111:
	dc.l	16384
L3111:
	dc.b	"PERT",0
	dc.b	8
L5111:
	dc.l	16384
L7111:
	dc.b	"RDRT",0
	dc.b	8
L1211:
	dc.l	16384
L3211:
	dc.b	"DDRT",0
	dc.b	8
L5211:
	dc.l	16384
L7211:
	dc.b	"PTIT",0
	dc.b	8
L1311:
	dc.l	16384
L3311:
	dc.b	"PTT",0
	dc.b	8
L5311:
	dc.l	16384
L7311:
	dc.b	"CAN0TXFG",0
	dc.b	8
L1411:
	dc.l	16384
	dc.l	16
L3411:
	dc.b	"CAN0RXFG",0
	dc.b	8
L5411:
	dc.l	16384
	dc.l	16
L7411:
	dc.b	"CAN0IDMR7",0
	dc.b	8
L1511:
	dc.l	16384
L3511:
	dc.b	"CAN0IDMR6",0
	dc.b	8
L5511:
	dc.l	16384
L7511:
	dc.b	"CAN0IDMR5",0
	dc.b	8
L1611:
	dc.l	16384
L3611:
	dc.b	"CAN0IDMR4",0
	dc.b	8
L5611:
	dc.l	16384
L7611:
	dc.b	"CAN0IDAR7",0
	dc.b	8
L1711:
	dc.l	16384
L3711:
	dc.b	"CAN0IDAR6",0
	dc.b	8
L5711:
	dc.l	16384
L7711:
	dc.b	"CAN0IDAR5",0
	dc.b	8
L1021:
	dc.l	16384
L3021:
	dc.b	"CAN0IDAR4",0
	dc.b	8
L5021:
	dc.l	16384
L7021:
	dc.b	"CAN0IDMR3",0
	dc.b	8
L1121:
	dc.l	16384
L3121:
	dc.b	"CAN0IDMR2",0
	dc.b	8
L5121:
	dc.l	16384
L7121:
	dc.b	"CAN0IDMR1",0
	dc.b	8
L1221:
	dc.l	16384
L3221:
	dc.b	"CAN0IDMR0",0
	dc.b	8
L5221:
	dc.l	16384
L7221:
	dc.b	"CAN0IDAR3",0
	dc.b	8
L1321:
	dc.l	16384
L3321:
	dc.b	"CAN0IDAR2",0
	dc.b	8
L5321:
	dc.l	16384
L7321:
	dc.b	"CAN0IDAR1",0
	dc.b	8
L1421:
	dc.l	16384
L3421:
	dc.b	"CAN0IDAR0",0
	dc.b	8
L5421:
	dc.l	16384
L7421:
	dc.b	"CAN0TXERR",0
	dc.b	8
L1521:
	dc.l	16384
L3521:
	dc.b	"CAN0RXERR",0
	dc.b	8
L5521:
	dc.l	16384
L7521:
	dc.b	"CAN0MISC",0
	dc.b	8
L1621:
	dc.l	16384
L3621:
	dc.b	"CAN0IDAC",0
	dc.b	8
L5621:
	dc.l	16384
L7621:
	dc.b	"CAN0TBSEL",0
	dc.b	8
L1721:
	dc.l	16384
L3721:
	dc.b	"CAN0TAAK",0
	dc.b	8
L5721:
	dc.l	16384
L7721:
	dc.b	"CAN0TARQ",0
	dc.b	8
L1031:
	dc.l	16384
L3031:
	dc.b	"CAN0TIER",0
	dc.b	8
L5031:
	dc.l	16384
L7031:
	dc.b	"CAN0TFLG",0
	dc.b	8
L1131:
	dc.l	16384
L3131:
	dc.b	"CAN0RIER",0
	dc.b	8
L5131:
	dc.l	16384
L7131:
	dc.b	"CAN0RFLG",0
	dc.b	8
L1231:
	dc.l	16384
L3231:
	dc.b	"CAN0BTR1",0
	dc.b	8
L5231:
	dc.l	16384
L7231:
	dc.b	"CAN0BTR0",0
	dc.b	8
L1331:
	dc.l	16384
L3331:
	dc.b	"CAN0CTL1",0
	dc.b	8
L5331:
	dc.l	16384
L7331:
	dc.b	"CAN0CTL0",0
	dc.b	8
L1431:
	dc.l	16384
L3431:
	dc.b	"INT_CFDATA7",0
	dc.b	8
L5431:
	dc.l	16384
L7431:
	dc.b	"INT_CFDATA6",0
	dc.b	8
L1531:
	dc.l	16384
L3531:
	dc.b	"INT_CFDATA5",0
	dc.b	8
L5531:
	dc.l	16384
L7531:
	dc.b	"INT_CFDATA4",0
	dc.b	8
L1631:
	dc.l	16384
L3631:
	dc.b	"INT_CFDATA3",0
	dc.b	8
L5631:
	dc.l	16384
L7631:
	dc.b	"INT_CFDATA2",0
	dc.b	8
L1731:
	dc.l	16384
L3731:
	dc.b	"INT_CFDATA1",0
	dc.b	8
L5731:
	dc.l	16384
L7731:
	dc.b	"INT_CFDATA0",0
	dc.b	8
L1041:
	dc.l	16384
L3041:
	dc.b	"INT_CFADDR",0
	dc.b	8
L5041:
	dc.l	16384
L7041:
	dc.b	"INT_XGPRIO",0
	dc.b	8
L1141:
	dc.l	16384
L3141:
	dc.b	"IVBR",0
	dc.b	8
L5141:
	dc.l	16384
L7141:
	dc.b	"FOPT",0
	dc.b	8
L1241:
	dc.l	16384
L3241:
	dc.b	"FEECRLO",0
	dc.b	8
L5241:
	dc.l	16384
L7241:
	dc.b	"FEECRHI",0
	dc.b	8
L1341:
	dc.l	16384
L3341:
	dc.b	"FEECR",0
	dc.b	8
L5341:
	dc.l	16384
L7341:
	dc.b	"FCCOBLO",0
	dc.b	8
L1441:
	dc.l	16384
L3441:
	dc.b	"FCCOBHI",0
	dc.b	8
L5441:
	dc.l	16384
L7441:
	dc.b	"FCCOB",0
	dc.b	8
L1541:
	dc.l	16384
L3541:
	dc.b	"DFPROT",0
	dc.b	8
L5541:
	dc.l	16384
L7541:
	dc.b	"FPROT",0
	dc.b	8
L1641:
	dc.l	16384
L3641:
	dc.b	"FERSTAT",0
	dc.b	8
L5641:
	dc.l	16384
L7641:
	dc.b	"FSTAT",0
	dc.b	8
L1741:
	dc.l	16384
L3741:
	dc.b	"FERCNFG",0
	dc.b	8
L5741:
	dc.l	16384
L7741:
	dc.b	"FCNFG",0
	dc.b	8
L1051:
	dc.l	16384
L3051:
	dc.b	"FECCRIX",0
	dc.b	8
L5051:
	dc.l	16384
L7051:
	dc.b	"FCCOBIX",0
	dc.b	8
L1151:
	dc.l	16384
L3151:
	dc.b	"FSEC",0
	dc.b	8
L5151:
	dc.l	16384
L7151:
	dc.b	"FCLKDIV",0
	dc.b	8
L1251:
	dc.l	16384
L3251:
	dc.b	"SPI0DRL",0
	dc.b	8
L5251:
	dc.l	20480
L7251:
	dc.b	"SPI0DRH",0
	dc.b	8
L1351:
	dc.l	20480
L3351:
	dc.b	"SPI0SR",0
	dc.b	8
L5351:
	dc.l	20480
L7351:
	dc.b	"SPI0BR",0
	dc.b	8
L1451:
	dc.l	20480
L3451:
	dc.b	"SPI0CR2",0
	dc.b	8
L5451:
	dc.l	20480
L7451:
	dc.b	"SPI0CR1",0
	dc.b	8
L1551:
	dc.l	20480
L3551:
	dc.b	"SCI1DRL",0
	dc.b	8
L5551:
	dc.l	20480
L7551:
	dc.b	"SCI1DRH",0
	dc.b	8
L1651:
	dc.l	20480
L3651:
	dc.b	"SCI1SR2",0
	dc.b	8
L5651:
	dc.l	20480
L7651:
	dc.b	"SCI1SR1",0
	dc.b	8
L1751:
	dc.l	20480
L3751:
	dc.b	"SCI1CR2",0
	dc.b	8
L5751:
	dc.l	20480
L7751:
	dc.b	"SCI1ACR2",0
	dc.b	8
L1061:
	dc.l	20480
L3061:
	dc.b	"SCI1ACR1",0
	dc.b	8
L5061:
	dc.l	20480
L7061:
	dc.b	"SCI1ASR1",0
	dc.b	8
L1161:
	dc.l	20480
L3161:
	dc.b	"SCI1CR1",0
	dc.b	8
L5161:
	dc.l	20480
L7161:
	dc.b	"SCI1BDL",0
	dc.b	8
L1261:
	dc.l	20480
L3261:
	dc.b	"SCI1BDH",0
	dc.b	8
L5261:
	dc.l	20480
L7261:
	dc.b	"SCI1BD",0
	dc.b	8
L1361:
	dc.l	20480
L3361:
	dc.b	"SCI0DRL",0
	dc.b	8
L5361:
	dc.l	20480
L7361:
	dc.b	"SCI0DRH",0
	dc.b	8
L1461:
	dc.l	20480
L3461:
	dc.b	"SCI0DR",0
	dc.b	8
L5461:
	dc.l	20480
L7461:
	dc.b	"SCI0SR2",0
	dc.b	8
L1561:
	dc.l	20480
L3561:
	dc.b	"SCI0SR1",0
	dc.b	8
L5561:
	dc.l	20480
L7561:
	dc.b	"SCI0CR2",0
	dc.b	8
L1661:
	dc.l	20480
L3661:
	dc.b	"SCI0ACR2",0
	dc.b	8
L5661:
	dc.l	20480
L7661:
	dc.b	"SCI0ACR1",0
	dc.b	8
L1761:
	dc.l	20480
L3761:
	dc.b	"SCI0ASR1",0
	dc.b	8
L5761:
	dc.l	20480
L7761:
	dc.b	"SCI0CR1",0
	dc.b	8
L1071:
	dc.l	20480
L3071:
	dc.b	"SCI0BDL",0
	dc.b	8
L5071:
	dc.l	20480
L7071:
	dc.b	"SCI0BDH",0
	dc.b	8
L1171:
	dc.l	20480
L3171:
	dc.b	"SCI0BD",0
	dc.b	8
L5171:
	dc.l	20480
L7171:
	dc.b	"PTPSR",0
	dc.b	8
L1271:
	dc.l	20480
L3271:
	dc.b	"OCPD",0
	dc.b	8
L5271:
	dc.l	20480
L7271:
	dc.b	"PACNTL",0
	dc.b	8
L1371:
	dc.l	20480
L3371:
	dc.b	"PACNTH",0
	dc.b	8
L5371:
	dc.l	20480
L7371:
	dc.b	"PACNT",0
	dc.b	8
L1471:
	dc.l	20480
L3471:
	dc.b	"PAFLG",0
	dc.b	8
L5471:
	dc.l	20480
L7471:
	dc.b	"PACTL",0
	dc.b	8
L1571:
	dc.l	20480
L3571:
	dc.b	"TC7",0
	dc.b	8
L5571:
	dc.l	20480
L7571:
	dc.b	"TC6",0
	dc.b	8
L1671:
	dc.l	20480
L3671:
	dc.b	"TC5",0
	dc.b	8
L5671:
	dc.l	20480
L7671:
	dc.b	"TC4",0
	dc.b	8
L1771:
	dc.l	20480
L3771:
	dc.b	"TC3",0
	dc.b	8
L5771:
	dc.l	20480
L7771:
	dc.b	"TC2",0
	dc.b	8
L1002:
	dc.l	20480
L3002:
	dc.b	"TC1",0
	dc.b	8
L5002:
	dc.l	20480
L7002:
	dc.b	"TC0",0
	dc.b	8
L1102:
	dc.l	20480
L3102:
	dc.b	"TFLG2",0
	dc.b	8
L5102:
	dc.l	20480
L7102:
	dc.b	"TFLG1",0
	dc.b	8
L1202:
	dc.l	20480
L3202:
	dc.b	"TSCR2",0
	dc.b	8
L5202:
	dc.l	20480
L7202:
	dc.b	"TIE",0
	dc.b	8
L1302:
	dc.l	20480
L3302:
	dc.b	"TCTL4",0
	dc.b	8
L5302:
	dc.l	20480
L7302:
	dc.b	"TCTL3",0
	dc.b	8
L1402:
	dc.l	20480
L3402:
	dc.b	"TCTL2",0
	dc.b	8
L5402:
	dc.l	20480
L7402:
	dc.b	"TCTL1",0
	dc.b	8
L1502:
	dc.l	20480
L3502:
	dc.b	"TTOV",0
	dc.b	8
L5502:
	dc.l	20480
L7502:
	dc.b	"TSCR1",0
	dc.b	8
L1602:
	dc.l	20480
L3602:
	dc.b	"TCNTL",0
	dc.b	8
L5602:
	dc.l	20480
L7602:
	dc.b	"TCNTH",0
	dc.b	8
L1702:
	dc.l	20480
L3702:
	dc.b	"TCNT",0
	dc.b	8
L5702:
	dc.l	20480
L7702:
	dc.b	"OC7D",0
	dc.b	8
L1012:
	dc.l	20480
L3012:
	dc.b	"OC7M",0
	dc.b	8
L5012:
	dc.l	20480
L7012:
	dc.b	"CFORC",0
	dc.b	8
L1112:
	dc.l	20480
L3112:
	dc.b	"TIOS",0
	dc.b	8
L5112:
	dc.l	20480
L7112:
	dc.b	"ARMCOP",0
	dc.b	8
L1212:
	dc.l	20480
L3212:
	dc.b	"CTCTL",0
	dc.b	8
L5212:
	dc.l	20480
L7212:
	dc.b	"FORBYP",0
	dc.b	8
L1312:
	dc.l	20480
L3312:
	dc.b	"COPCTL",0
	dc.b	8
L5312:
	dc.l	20480
L7312:
	dc.b	"RTICTL",0
	dc.b	8
L1412:
	dc.l	20480
L3412:
	dc.b	"PLLCTL",0
	dc.b	8
L5412:
	dc.l	20480
L7412:
	dc.b	"CLKSEL",0
	dc.b	8
L1512:
	dc.l	20480
L3512:
	dc.b	"CRGINT",0
	dc.b	8
L5512:
	dc.l	20480
L7512:
	dc.b	"CRGFLG",0
	dc.b	8
L1612:
	dc.l	20480
L3612:
	dc.b	"POSTDIV",0
	dc.b	8
L5612:
	dc.l	20480
L7612:
	dc.b	"REFDV",0
	dc.b	8
L1712:
	dc.l	20480
L3712:
	dc.b	"SYNR",0
	dc.b	8
L5712:
	dc.l	20480
L7712:
	dc.b	"DDRK",0
	dc.b	8
L1022:
	dc.l	20480
L3022:
	dc.b	"PORTK",0
	dc.b	8
L5022:
	dc.l	20480
L7022:
	dc.b	"DBGXDLM",0
	dc.b	8
L1122:
	dc.l	20480
L3122:
	dc.b	"DBGXDHM",0
	dc.b	8
L5122:
	dc.l	20480
L7122:
	dc.b	"DBGXDM",0
	dc.b	8
L1222:
	dc.l	20480
L3222:
	dc.b	"DBGXDL",0
	dc.b	8
L5222:
	dc.l	20480
L7222:
	dc.b	"DBGXDH",0
	dc.b	8
L1322:
	dc.l	20480
L3322:
	dc.b	"DBGXD",0
	dc.b	8
L5322:
	dc.l	20480
L7322:
	dc.b	"DBGXAL",0
	dc.b	8
L1422:
	dc.l	20480
L3422:
	dc.b	"DBGXAM",0
	dc.b	8
L5422:
	dc.l	20480
L7422:
	dc.b	"DBGXAH",0
	dc.b	8
L1522:
	dc.l	20480
L3522:
	dc.b	"DBGXCTL",0
	dc.b	8
L5522:
	dc.l	20480
L7522:
	dc.b	"DBGMFR",0
	dc.b	8
L1622:
	dc.l	20480
L3622:
	dc.b	"DBGSCRX",0
	dc.b	8
L5622:
	dc.l	20480
L7622:
	dc.b	"DBGCNT",0
	dc.b	8
L1722:
	dc.l	20480
L3722:
	dc.b	"DBGTB",0
	dc.b	8
L5722:
	dc.l	20480
L7722:
	dc.b	"DBGC2",0
	dc.b	8
L1032:
	dc.l	20480
L3032:
	dc.b	"DBGTCR",0
	dc.b	8
L5032:
	dc.l	20480
L7032:
	dc.b	"DBGSR",0
	dc.b	8
L1132:
	dc.l	20480
L3132:
	dc.b	"DBGC1",0
	dc.b	8
L5132:
	dc.l	20480
L7132:
	dc.b	"IRQCR",0
	dc.b	8
L1232:
	dc.l	20480
L3232:
	dc.b	"ECLKCTL",0
	dc.b	8
L5232:
	dc.l	20480
L7232:
	dc.b	"PARTIDL",0
	dc.b	8
L1332:
	dc.l	20480
L3332:
	dc.b	"PARTIDH",0
	dc.b	8
L5332:
	dc.l	20480
L7332:
	dc.b	"PARTID",0
	dc.b	8
L1432:
	dc.l	20480
L3432:
	dc.b	"EPAGE",0
	dc.b	8
L5432:
	dc.l	20480
L7432:
	dc.b	"RPAGE",0
	dc.b	8
L1532:
	dc.l	20480
L3532:
	dc.b	"PPAGE",0
	dc.b	8
L5532:
	dc.l	20480
L7532:
	dc.b	"MMCCTL1",0
	dc.b	8
L1632:
	dc.l	20480
L3632:
	dc.b	"DIRECT",0
	dc.b	8
L5632:
	dc.l	20480
L7632:
	dc.b	"GPAGE",0
	dc.b	8
L1732:
	dc.l	20480
L3732:
	dc.b	"MODE",0
	dc.b	8
L5732:
	dc.l	20480
L7732:
	dc.b	"RDRIV",0
	dc.b	8
L1042:
	dc.l	20480
L3042:
	dc.b	"PUCR",0
	dc.b	8
L5042:
	dc.l	20480
L7042:
	dc.b	"DDRE",0
	dc.b	8
L1142:
	dc.l	20480
L3142:
	dc.b	"PORTE",0
	dc.b	8
L5142:
	dc.l	20480
L7142:
	dc.b	"DDRB",0
	dc.b	8
L1242:
	dc.l	20480
L3242:
	dc.b	"DDRA",0
	dc.b	8
L5242:
	dc.l	20480
L7242:
	dc.b	"PORTB",0
	dc.b	8
L1342:
	dc.l	20480
L3342:
	dc.b	"PORTA",0
	dc.b	8
L5342:
	dc.l	20480
L11:
	dc.l	L31
	dc.l	_PITCNT3
	dc.l	436207616
	dc.l	L51
	dc.l	L71
	dc.l	_PITLD3
	dc.l	436207616
	dc.l	L12
	dc.l	L32
	dc.l	_PITCNT2
	dc.l	436207616
	dc.l	L52
	dc.l	L72
	dc.l	_PITLD2
	dc.l	436207616
	dc.l	L13
	dc.l	L33
	dc.l	_PITCNT1
	dc.l	436207616
	dc.l	L53
	dc.l	L73
	dc.l	_PITLD1
	dc.l	436207616
	dc.l	L14
	dc.l	L34
	dc.l	_PITCNT0
	dc.l	436207616
	dc.l	L54
	dc.l	L74
	dc.l	_PITLD0
	dc.l	436207616
	dc.l	L15
	dc.l	L35
	dc.l	_PITMTLD1
	dc.l	167772160
	dc.l	L55
	dc.l	L75
	dc.l	_PITMTLD0
	dc.l	167772160
	dc.l	L16
	dc.l	L36
	dc.l	_PITTF
	dc.l	167772160
	dc.l	L56
	dc.l	L76
	dc.l	_PITINTE
	dc.l	167772160
	dc.l	L17
	dc.l	L37
	dc.l	_PITMUX
	dc.l	167772160
	dc.l	L57
	dc.l	L77
	dc.l	_PITCE
	dc.l	167772160
	dc.l	L101
	dc.l	L301
	dc.l	_PITFLT
	dc.l	167772160
	dc.l	L501
	dc.l	L701
	dc.l	_PITCFLMT
	dc.l	167772160
	dc.l	L111
	dc.l	L311
	dc.l	_PWMSDN
	dc.l	167772160
	dc.l	L511
	dc.l	L711
	dc.l	_PWMDTY7
	dc.l	167772160
	dc.l	L121
	dc.l	L321
	dc.l	_PWMDTY6
	dc.l	167772160
	dc.l	L521
	dc.l	L721
	dc.l	_PWMDTY5
	dc.l	167772160
	dc.l	L131
	dc.l	L331
	dc.l	_PWMDTY4
	dc.l	167772160
	dc.l	L531
	dc.l	L731
	dc.l	_PWMDTY3
	dc.l	167772160
	dc.l	L141
	dc.l	L341
	dc.l	_PWMDTY2
	dc.l	167772160
	dc.l	L541
	dc.l	L741
	dc.l	_PWMDTY1
	dc.l	167772160
	dc.l	L151
	dc.l	L351
	dc.l	_PWMDTY0
	dc.l	167772160
	dc.l	L551
	dc.l	L751
	dc.l	_PWMPER7
	dc.l	167772160
	dc.l	L161
	dc.l	L361
	dc.l	_PWMPER6
	dc.l	167772160
	dc.l	L561
	dc.l	L761
	dc.l	_PWMPER5
	dc.l	167772160
	dc.l	L171
	dc.l	L371
	dc.l	_PWMPER4
	dc.l	167772160
	dc.l	L571
	dc.l	L771
	dc.l	_PWMPER3
	dc.l	167772160
	dc.l	L102
	dc.l	L302
	dc.l	_PWMPER2
	dc.l	167772160
	dc.l	L502
	dc.l	L702
	dc.l	_PWMPER1
	dc.l	167772160
	dc.l	L112
	dc.l	L312
	dc.l	_PWMPER0
	dc.l	167772160
	dc.l	L512
	dc.l	L712
	dc.l	_PWMCNT7
	dc.l	167772160
	dc.l	L122
	dc.l	L322
	dc.l	_PWMCNT6
	dc.l	167772160
	dc.l	L522
	dc.l	L722
	dc.l	_PWMCNT5
	dc.l	167772160
	dc.l	L132
	dc.l	L332
	dc.l	_PWMCNT4
	dc.l	167772160
	dc.l	L532
	dc.l	L732
	dc.l	_PWMCNT3
	dc.l	167772160
	dc.l	L142
	dc.l	L342
	dc.l	_PWMCNT2
	dc.l	167772160
	dc.l	L542
	dc.l	L742
	dc.l	_PWMCNT1
	dc.l	167772160
	dc.l	L152
	dc.l	L352
	dc.l	_PWMCNT0
	dc.l	167772160
	dc.l	L552
	dc.l	L752
	dc.l	_PWMSCNTB
	dc.l	167772160
	dc.l	L162
	dc.l	L362
	dc.l	_PWMSCNTA
	dc.l	167772160
	dc.l	L562
	dc.l	L762
	dc.l	_PWMSCLB
	dc.l	167772160
	dc.l	L172
	dc.l	L372
	dc.l	_PWMSCLA
	dc.l	167772160
	dc.l	L572
	dc.l	L772
	dc.l	_PWMPRSC
	dc.l	167772160
	dc.l	L103
	dc.l	L303
	dc.l	_PWMTST
	dc.l	167772160
	dc.l	L503
	dc.l	L703
	dc.l	_PWMCTL
	dc.l	167772160
	dc.l	L113
	dc.l	L313
	dc.l	_PWMCAE
	dc.l	167772160
	dc.l	L513
	dc.l	L713
	dc.l	_PWMPRCLK
	dc.l	167772160
	dc.l	L123
	dc.l	L323
	dc.l	_PWMCLK
	dc.l	167772160
	dc.l	L523
	dc.l	L723
	dc.l	_PWMPOL
	dc.l	167772160
	dc.l	L133
	dc.l	L333
	dc.l	_PWME
	dc.l	167772160
	dc.l	L533
	dc.l	L733
	dc.l	_VREGHTTR
	dc.l	167772160
	dc.l	L143
	dc.l	L343
	dc.l	_VREGAPIRL
	dc.l	167772160
	dc.l	L543
	dc.l	L743
	dc.l	_VREGAPIRH
	dc.l	167772160
	dc.l	L153
	dc.l	L353
	dc.l	_VREGAPIR
	dc.l	436207616
	dc.l	L553
	dc.l	L753
	dc.l	_VREGAPITR
	dc.l	167772160
	dc.l	L163
	dc.l	L363
	dc.l	_VREGAPICL
	dc.l	167772160
	dc.l	L563
	dc.l	L763
	dc.l	_VREGCTRL
	dc.l	167772160
	dc.l	L173
	dc.l	L373
	dc.l	_VREGHTCL
	dc.l	167772160
	dc.l	L573
	dc.l	L773
	dc.l	_ATD0DR15
	dc.l	436207616
	dc.l	L104
	dc.l	L304
	dc.l	_ATD0DR14
	dc.l	436207616
	dc.l	L504
	dc.l	L704
	dc.l	_ATD0DR13
	dc.l	436207616
	dc.l	L114
	dc.l	L314
	dc.l	_ATD0DR12
	dc.l	436207616
	dc.l	L514
	dc.l	L714
	dc.l	_ATD0DR11
	dc.l	436207616
	dc.l	L124
	dc.l	L324
	dc.l	_ATD0DR10
	dc.l	436207616
	dc.l	L524
	dc.l	L724
	dc.l	_ATD0DR9
	dc.l	436207616
	dc.l	L134
	dc.l	L334
	dc.l	_ATD0DR8
	dc.l	436207616
	dc.l	L534
	dc.l	L734
	dc.l	_ATD0DR7
	dc.l	436207616
	dc.l	L144
	dc.l	L344
	dc.l	_ATD0DR6
	dc.l	436207616
	dc.l	L544
	dc.l	L744
	dc.l	_ATD0DR5
	dc.l	436207616
	dc.l	L154
	dc.l	L354
	dc.l	_ATD0DR4
	dc.l	436207616
	dc.l	L554
	dc.l	L754
	dc.l	_ATD0DR3
	dc.l	436207616
	dc.l	L164
	dc.l	L364
	dc.l	_ATD0DR2
	dc.l	436207616
	dc.l	L564
	dc.l	L764
	dc.l	_ATD0DR1
	dc.l	436207616
	dc.l	L174
	dc.l	L374
	dc.l	_ATD0DR0
	dc.l	436207616
	dc.l	L574
	dc.l	L774
	dc.l	_ATD0DR
	dc.l	436207808
	dc.l	L105
	dc.l	L305
	dc.l	_ATD0CMPHT
	dc.l	436207616
	dc.l	L505
	dc.l	L705
	dc.l	_ATD0DIENL
	dc.l	167772160
	dc.l	L115
	dc.l	L315
	dc.l	_ATD0DIENH
	dc.l	167772160
	dc.l	L515
	dc.l	L715
	dc.l	_ATD0DIEN
	dc.l	436207616
	dc.l	L125
	dc.l	L325
	dc.l	_ATD0STAT2L
	dc.l	167772160
	dc.l	L525
	dc.l	L725
	dc.l	_ATD0STAT2H
	dc.l	167772160
	dc.l	L135
	dc.l	L335
	dc.l	_ATD0STAT2
	dc.l	436207616
	dc.l	L535
	dc.l	L735
	dc.l	_ATD0CMPEL
	dc.l	167772160
	dc.l	L145
	dc.l	L345
	dc.l	_ATD0CMPEH
	dc.l	167772160
	dc.l	L545
	dc.l	L745
	dc.l	_ATD0CMPE
	dc.l	436207616
	dc.l	L155
	dc.l	L355
	dc.l	_ATD0STAT0
	dc.l	167772160
	dc.l	L555
	dc.l	L755
	dc.l	_ATD0CTL5
	dc.l	167772160
	dc.l	L165
	dc.l	L365
	dc.l	_ATD0CTL4
	dc.l	167772160
	dc.l	L565
	dc.l	L765
	dc.l	_ATD0CTL3
	dc.l	167772160
	dc.l	L175
	dc.l	L375
	dc.l	_ATD0CTL2
	dc.l	167772160
	dc.l	L575
	dc.l	L775
	dc.l	_ATD0CTL1
	dc.l	167772160
	dc.l	L106
	dc.l	L306
	dc.l	_ATD0CTL0
	dc.l	167772160
	dc.l	L506
	dc.l	L706
	dc.l	_PER1AD0
	dc.l	167772160
	dc.l	L116
	dc.l	L316
	dc.l	_PER0AD0
	dc.l	167772160
	dc.l	L516
	dc.l	L716
	dc.l	_RDR1AD0
	dc.l	167772160
	dc.l	L126
	dc.l	L326
	dc.l	_RDR0AD0
	dc.l	167772160
	dc.l	L526
	dc.l	L726
	dc.l	_DDR1AD0
	dc.l	167772160
	dc.l	L136
	dc.l	L336
	dc.l	_DDR0AD0
	dc.l	167772160
	dc.l	L536
	dc.l	L736
	dc.l	_PT1AD0
	dc.l	167772160
	dc.l	L146
	dc.l	L346
	dc.l	_PT0AD0
	dc.l	167772160
	dc.l	L546
	dc.l	L746
	dc.l	_PIFJ
	dc.l	167772160
	dc.l	L156
	dc.l	L356
	dc.l	_PIEJ
	dc.l	167772160
	dc.l	L556
	dc.l	L756
	dc.l	_PPSJ
	dc.l	167772160
	dc.l	L166
	dc.l	L366
	dc.l	_PERJ
	dc.l	167772160
	dc.l	L566
	dc.l	L766
	dc.l	_RDRJ
	dc.l	167772160
	dc.l	L176
	dc.l	L376
	dc.l	_DDRJ
	dc.l	167772160
	dc.l	L576
	dc.l	L776
	dc.l	_PTIJ
	dc.l	167772160
	dc.l	L107
	dc.l	L307
	dc.l	_PTJ
	dc.l	167772160
	dc.l	L507
	dc.l	L707
	dc.l	_PIFH
	dc.l	167772160
	dc.l	L117
	dc.l	L317
	dc.l	_PIEH
	dc.l	167772160
	dc.l	L517
	dc.l	L717
	dc.l	_PPSH
	dc.l	167772160
	dc.l	L127
	dc.l	L327
	dc.l	_PERH
	dc.l	167772160
	dc.l	L527
	dc.l	L727
	dc.l	_RDRH
	dc.l	167772160
	dc.l	L137
	dc.l	L337
	dc.l	_DDRH
	dc.l	167772160
	dc.l	L537
	dc.l	L737
	dc.l	_PTIH
	dc.l	167772160
	dc.l	L147
	dc.l	L347
	dc.l	_PTH
	dc.l	167772160
	dc.l	L547
	dc.l	L747
	dc.l	_PIFP
	dc.l	167772160
	dc.l	L157
	dc.l	L357
	dc.l	_PIEP
	dc.l	167772160
	dc.l	L557
	dc.l	L757
	dc.l	_PPSP
	dc.l	167772160
	dc.l	L167
	dc.l	L367
	dc.l	_PERP
	dc.l	167772160
	dc.l	L567
	dc.l	L767
	dc.l	_RDRP
	dc.l	167772160
	dc.l	L177
	dc.l	L377
	dc.l	_DDRP
	dc.l	167772160
	dc.l	L577
	dc.l	L777
	dc.l	_PTIP
	dc.l	167772160
	dc.l	L1001
	dc.l	L3001
	dc.l	_PTP
	dc.l	167772160
	dc.l	L5001
	dc.l	L7001
	dc.l	_MODRR
	dc.l	167772160
	dc.l	L1101
	dc.l	L3101
	dc.l	_WOMM
	dc.l	167772160
	dc.l	L5101
	dc.l	L7101
	dc.l	_PPSM
	dc.l	167772160
	dc.l	L1201
	dc.l	L3201
	dc.l	_PERM
	dc.l	167772160
	dc.l	L5201
	dc.l	L7201
	dc.l	_RDRM
	dc.l	167772160
	dc.l	L1301
	dc.l	L3301
	dc.l	_DDRM
	dc.l	167772160
	dc.l	L5301
	dc.l	L7301
	dc.l	_PTIM
	dc.l	167772160
	dc.l	L1401
	dc.l	L3401
	dc.l	_PTM
	dc.l	167772160
	dc.l	L5401
	dc.l	L7401
	dc.l	_WOMS
	dc.l	167772160
	dc.l	L1501
	dc.l	L3501
	dc.l	_PPSS
	dc.l	167772160
	dc.l	L5501
	dc.l	L7501
	dc.l	_PERS
	dc.l	167772160
	dc.l	L1601
	dc.l	L3601
	dc.l	_RDRS
	dc.l	167772160
	dc.l	L5601
	dc.l	L7601
	dc.l	_DDRS
	dc.l	167772160
	dc.l	L1701
	dc.l	L3701
	dc.l	_PTIS
	dc.l	167772160
	dc.l	L5701
	dc.l	L7701
	dc.l	_PTS
	dc.l	167772160
	dc.l	L1011
	dc.l	L3011
	dc.l	_PTTRR
	dc.l	167772160
	dc.l	L5011
	dc.l	L7011
	dc.l	_PPST
	dc.l	167772160
	dc.l	L1111
	dc.l	L3111
	dc.l	_PERT
	dc.l	167772160
	dc.l	L5111
	dc.l	L7111
	dc.l	_RDRT
	dc.l	167772160
	dc.l	L1211
	dc.l	L3211
	dc.l	_DDRT
	dc.l	167772160
	dc.l	L5211
	dc.l	L7211
	dc.l	_PTIT
	dc.l	167772160
	dc.l	L1311
	dc.l	L3311
	dc.l	_PTT
	dc.l	167772160
	dc.l	L5311
	dc.l	L7311
	dc.l	_CAN0TXFG
	dc.l	167772352
	dc.l	L1411
	dc.l	L3411
	dc.l	_CAN0RXFG
	dc.l	167772352
	dc.l	L5411
	dc.l	L7411
	dc.l	_CAN0IDMR7
	dc.l	167772160
	dc.l	L1511
	dc.l	L3511
	dc.l	_CAN0IDMR6
	dc.l	167772160
	dc.l	L5511
	dc.l	L7511
	dc.l	_CAN0IDMR5
	dc.l	167772160
	dc.l	L1611
	dc.l	L3611
	dc.l	_CAN0IDMR4
	dc.l	167772160
	dc.l	L5611
	dc.l	L7611
	dc.l	_CAN0IDAR7
	dc.l	167772160
	dc.l	L1711
	dc.l	L3711
	dc.l	_CAN0IDAR6
	dc.l	167772160
	dc.l	L5711
	dc.l	L7711
	dc.l	_CAN0IDAR5
	dc.l	167772160
	dc.l	L1021
	dc.l	L3021
	dc.l	_CAN0IDAR4
	dc.l	167772160
	dc.l	L5021
	dc.l	L7021
	dc.l	_CAN0IDMR3
	dc.l	167772160
	dc.l	L1121
	dc.l	L3121
	dc.l	_CAN0IDMR2
	dc.l	167772160
	dc.l	L5121
	dc.l	L7121
	dc.l	_CAN0IDMR1
	dc.l	167772160
	dc.l	L1221
	dc.l	L3221
	dc.l	_CAN0IDMR0
	dc.l	167772160
	dc.l	L5221
	dc.l	L7221
	dc.l	_CAN0IDAR3
	dc.l	167772160
	dc.l	L1321
	dc.l	L3321
	dc.l	_CAN0IDAR2
	dc.l	167772160
	dc.l	L5321
	dc.l	L7321
	dc.l	_CAN0IDAR1
	dc.l	167772160
	dc.l	L1421
	dc.l	L3421
	dc.l	_CAN0IDAR0
	dc.l	167772160
	dc.l	L5421
	dc.l	L7421
	dc.l	_CAN0TXERR
	dc.l	167772160
	dc.l	L1521
	dc.l	L3521
	dc.l	_CAN0RXERR
	dc.l	167772160
	dc.l	L5521
	dc.l	L7521
	dc.l	_CAN0MISC
	dc.l	167772160
	dc.l	L1621
	dc.l	L3621
	dc.l	_CAN0IDAC
	dc.l	167772160
	dc.l	L5621
	dc.l	L7621
	dc.l	_CAN0TBSEL
	dc.l	167772160
	dc.l	L1721
	dc.l	L3721
	dc.l	_CAN0TAAK
	dc.l	167772160
	dc.l	L5721
	dc.l	L7721
	dc.l	_CAN0TARQ
	dc.l	167772160
	dc.l	L1031
	dc.l	L3031
	dc.l	_CAN0TIER
	dc.l	167772160
	dc.l	L5031
	dc.l	L7031
	dc.l	_CAN0TFLG
	dc.l	167772160
	dc.l	L1131
	dc.l	L3131
	dc.l	_CAN0RIER
	dc.l	167772160
	dc.l	L5131
	dc.l	L7131
	dc.l	_CAN0RFLG
	dc.l	167772160
	dc.l	L1231
	dc.l	L3231
	dc.l	_CAN0BTR1
	dc.l	167772160
	dc.l	L5231
	dc.l	L7231
	dc.l	_CAN0BTR0
	dc.l	167772160
	dc.l	L1331
	dc.l	L3331
	dc.l	_CAN0CTL1
	dc.l	167772160
	dc.l	L5331
	dc.l	L7331
	dc.l	_CAN0CTL0
	dc.l	167772160
	dc.l	L1431
	dc.l	L3431
	dc.l	_INT_CFDATA7
	dc.l	167772160
	dc.l	L5431
	dc.l	L7431
	dc.l	_INT_CFDATA6
	dc.l	167772160
	dc.l	L1531
	dc.l	L3531
	dc.l	_INT_CFDATA5
	dc.l	167772160
	dc.l	L5531
	dc.l	L7531
	dc.l	_INT_CFDATA4
	dc.l	167772160
	dc.l	L1631
	dc.l	L3631
	dc.l	_INT_CFDATA3
	dc.l	167772160
	dc.l	L5631
	dc.l	L7631
	dc.l	_INT_CFDATA2
	dc.l	167772160
	dc.l	L1731
	dc.l	L3731
	dc.l	_INT_CFDATA1
	dc.l	167772160
	dc.l	L5731
	dc.l	L7731
	dc.l	_INT_CFDATA0
	dc.l	167772160
	dc.l	L1041
	dc.l	L3041
	dc.l	_INT_CFADDR
	dc.l	167772160
	dc.l	L5041
	dc.l	L7041
	dc.l	_INT_XGPRIO
	dc.l	167772160
	dc.l	L1141
	dc.l	L3141
	dc.l	_IVBR
	dc.l	167772160
	dc.l	L5141
	dc.l	L7141
	dc.l	_FOPT
	dc.l	436207616
	dc.l	L1241
	dc.l	L3241
	dc.l	_FEECRLO
	dc.l	167772160
	dc.l	L5241
	dc.l	L7241
	dc.l	_FEECRHI
	dc.l	167772160
	dc.l	L1341
	dc.l	L3341
	dc.l	_FEECR
	dc.l	436207616
	dc.l	L5341
	dc.l	L7341
	dc.l	_FCCOBLO
	dc.l	167772160
	dc.l	L1441
	dc.l	L3441
	dc.l	_FCCOBHI
	dc.l	167772160
	dc.l	L5441
	dc.l	L7441
	dc.l	_FCCOB
	dc.l	436207616
	dc.l	L1541
	dc.l	L3541
	dc.l	_DFPROT
	dc.l	167772160
	dc.l	L5541
	dc.l	L7541
	dc.l	_FPROT
	dc.l	167772160
	dc.l	L1641
	dc.l	L3641
	dc.l	_FERSTAT
	dc.l	167772160
	dc.l	L5641
	dc.l	L7641
	dc.l	_FSTAT
	dc.l	167772160
	dc.l	L1741
	dc.l	L3741
	dc.l	_FERCNFG
	dc.l	167772160
	dc.l	L5741
	dc.l	L7741
	dc.l	_FCNFG
	dc.l	167772160
	dc.l	L1051
	dc.l	L3051
	dc.l	_FECCRIX
	dc.l	167772160
	dc.l	L5051
	dc.l	L7051
	dc.l	_FCCOBIX
	dc.l	167772160
	dc.l	L1151
	dc.l	L3151
	dc.l	_FSEC
	dc.l	167772160
	dc.l	L5151
	dc.l	L7151
	dc.l	_FCLKDIV
	dc.l	167772160
	dc.l	L1251
	dc.l	L3251
	dc.l	_SPI0DRL
	dc.l	167772160
	dc.l	L5251
	dc.l	L7251
	dc.l	_SPI0DRH
	dc.l	167772160
	dc.l	L1351
	dc.l	L3351
	dc.l	_SPI0SR
	dc.l	167772160
	dc.l	L5351
	dc.l	L7351
	dc.l	_SPI0BR
	dc.l	167772160
	dc.l	L1451
	dc.l	L3451
	dc.l	_SPI0CR2
	dc.l	167772160
	dc.l	L5451
	dc.l	L7451
	dc.l	_SPI0CR1
	dc.l	167772160
	dc.l	L1551
	dc.l	L3551
	dc.l	_SCI1DRL
	dc.l	167772160
	dc.l	L5551
	dc.l	L7551
	dc.l	_SCI1DRH
	dc.l	167772160
	dc.l	L1651
	dc.l	L3651
	dc.l	_SCI1SR2
	dc.l	167772160
	dc.l	L5651
	dc.l	L7651
	dc.l	_SCI1SR1
	dc.l	167772160
	dc.l	L1751
	dc.l	L3751
	dc.l	_SCI1CR2
	dc.l	167772160
	dc.l	L5751
	dc.l	L7751
	dc.l	_SCI1ACR2
	dc.l	167772160
	dc.l	L1061
	dc.l	L3061
	dc.l	_SCI1ACR1
	dc.l	167772160
	dc.l	L5061
	dc.l	L7061
	dc.l	_SCI1ASR1
	dc.l	167772160
	dc.l	L1161
	dc.l	L3161
	dc.l	_SCI1CR1
	dc.l	167772160
	dc.l	L5161
	dc.l	L7161
	dc.l	_SCI1BDL
	dc.l	167772160
	dc.l	L1261
	dc.l	L3261
	dc.l	_SCI1BDH
	dc.l	167772160
	dc.l	L5261
	dc.l	L7261
	dc.l	_SCI1BD
	dc.l	436207616
	dc.l	L1361
	dc.l	L3361
	dc.l	_SCI0DRL
	dc.l	167772160
	dc.l	L5361
	dc.l	L7361
	dc.l	_SCI0DRH
	dc.l	167772160
	dc.l	L1461
	dc.l	L3461
	dc.l	_SCI0DR
	dc.l	436207616
	dc.l	L5461
	dc.l	L7461
	dc.l	_SCI0SR2
	dc.l	167772160
	dc.l	L1561
	dc.l	L3561
	dc.l	_SCI0SR1
	dc.l	167772160
	dc.l	L5561
	dc.l	L7561
	dc.l	_SCI0CR2
	dc.l	167772160
	dc.l	L1661
	dc.l	L3661
	dc.l	_SCI0ACR2
	dc.l	167772160
	dc.l	L5661
	dc.l	L7661
	dc.l	_SCI0ACR1
	dc.l	167772160
	dc.l	L1761
	dc.l	L3761
	dc.l	_SCI0ASR1
	dc.l	167772160
	dc.l	L5761
	dc.l	L7761
	dc.l	_SCI0CR1
	dc.l	167772160
	dc.l	L1071
	dc.l	L3071
	dc.l	_SCI0BDL
	dc.l	167772160
	dc.l	L5071
	dc.l	L7071
	dc.l	_SCI0BDH
	dc.l	167772160
	dc.l	L1171
	dc.l	L3171
	dc.l	_SCI0BD
	dc.l	436207616
	dc.l	L5171
	dc.l	L7171
	dc.l	_PTPSR
	dc.l	167772160
	dc.l	L1271
	dc.l	L3271
	dc.l	_OCPD
	dc.l	167772160
	dc.l	L5271
	dc.l	L7271
	dc.l	_PACNTL
	dc.l	167772160
	dc.l	L1371
	dc.l	L3371
	dc.l	_PACNTH
	dc.l	167772160
	dc.l	L5371
	dc.l	L7371
	dc.l	_PACNT
	dc.l	436207616
	dc.l	L1471
	dc.l	L3471
	dc.l	_PAFLG
	dc.l	167772160
	dc.l	L5471
	dc.l	L7471
	dc.l	_PACTL
	dc.l	167772160
	dc.l	L1571
	dc.l	L3571
	dc.l	_TC7
	dc.l	436207616
	dc.l	L5571
	dc.l	L7571
	dc.l	_TC6
	dc.l	436207616
	dc.l	L1671
	dc.l	L3671
	dc.l	_TC5
	dc.l	436207616
	dc.l	L5671
	dc.l	L7671
	dc.l	_TC4
	dc.l	436207616
	dc.l	L1771
	dc.l	L3771
	dc.l	_TC3
	dc.l	436207616
	dc.l	L5771
	dc.l	L7771
	dc.l	_TC2
	dc.l	436207616
	dc.l	L1002
	dc.l	L3002
	dc.l	_TC1
	dc.l	436207616
	dc.l	L5002
	dc.l	L7002
	dc.l	_TC0
	dc.l	436207616
	dc.l	L1102
	dc.l	L3102
	dc.l	_TFLG2
	dc.l	167772160
	dc.l	L5102
	dc.l	L7102
	dc.l	_TFLG1
	dc.l	167772160
	dc.l	L1202
	dc.l	L3202
	dc.l	_TSCR2
	dc.l	167772160
	dc.l	L5202
	dc.l	L7202
	dc.l	_TIE
	dc.l	167772160
	dc.l	L1302
	dc.l	L3302
	dc.l	_TCTL4
	dc.l	167772160
	dc.l	L5302
	dc.l	L7302
	dc.l	_TCTL3
	dc.l	167772160
	dc.l	L1402
	dc.l	L3402
	dc.l	_TCTL2
	dc.l	167772160
	dc.l	L5402
	dc.l	L7402
	dc.l	_TCTL1
	dc.l	167772160
	dc.l	L1502
	dc.l	L3502
	dc.l	_TTOV
	dc.l	167772160
	dc.l	L5502
	dc.l	L7502
	dc.l	_TSCR1
	dc.l	167772160
	dc.l	L1602
	dc.l	L3602
	dc.l	_TCNTL
	dc.l	167772160
	dc.l	L5602
	dc.l	L7602
	dc.l	_TCNTH
	dc.l	167772160
	dc.l	L1702
	dc.l	L3702
	dc.l	_TCNT
	dc.l	436207616
	dc.l	L5702
	dc.l	L7702
	dc.l	_OC7D
	dc.l	167772160
	dc.l	L1012
	dc.l	L3012
	dc.l	_OC7M
	dc.l	167772160
	dc.l	L5012
	dc.l	L7012
	dc.l	_CFORC
	dc.l	167772160
	dc.l	L1112
	dc.l	L3112
	dc.l	_TIOS
	dc.l	167772160
	dc.l	L5112
	dc.l	L7112
	dc.l	_ARMCOP
	dc.l	167772160
	dc.l	L1212
	dc.l	L3212
	dc.l	_CTCTL
	dc.l	167772160
	dc.l	L5212
	dc.l	L7212
	dc.l	_FORBYP
	dc.l	167772160
	dc.l	L1312
	dc.l	L3312
	dc.l	_COPCTL
	dc.l	167772160
	dc.l	L5312
	dc.l	L7312
	dc.l	_RTICTL
	dc.l	167772160
	dc.l	L1412
	dc.l	L3412
	dc.l	_PLLCTL
	dc.l	167772160
	dc.l	L5412
	dc.l	L7412
	dc.l	_CLKSEL
	dc.l	167772160
	dc.l	L1512
	dc.l	L3512
	dc.l	_CRGINT
	dc.l	167772160
	dc.l	L5512
	dc.l	L7512
	dc.l	_CRGFLG
	dc.l	167772160
	dc.l	L1612
	dc.l	L3612
	dc.l	_POSTDIV
	dc.l	167772160
	dc.l	L5612
	dc.l	L7612
	dc.l	_REFDV
	dc.l	167772160
	dc.l	L1712
	dc.l	L3712
	dc.l	_SYNR
	dc.l	167772160
	dc.l	L5712
	dc.l	L7712
	dc.l	_DDRK
	dc.l	167772160
	dc.l	L1022
	dc.l	L3022
	dc.l	_PORTK
	dc.l	167772160
	dc.l	L5022
	dc.l	L7022
	dc.l	_DBGXDLM
	dc.l	167772160
	dc.l	L1122
	dc.l	L3122
	dc.l	_DBGXDHM
	dc.l	167772160
	dc.l	L5122
	dc.l	L7122
	dc.l	_DBGXDM
	dc.l	436207616
	dc.l	L1222
	dc.l	L3222
	dc.l	_DBGXDL
	dc.l	167772160
	dc.l	L5222
	dc.l	L7222
	dc.l	_DBGXDH
	dc.l	167772160
	dc.l	L1322
	dc.l	L3322
	dc.l	_DBGXD
	dc.l	436207616
	dc.l	L5322
	dc.l	L7322
	dc.l	_DBGXAL
	dc.l	167772160
	dc.l	L1422
	dc.l	L3422
	dc.l	_DBGXAM
	dc.l	167772160
	dc.l	L5422
	dc.l	L7422
	dc.l	_DBGXAH
	dc.l	167772160
	dc.l	L1522
	dc.l	L3522
	dc.l	_DBGXCTL
	dc.l	167772160
	dc.l	L5522
	dc.l	L7522
	dc.l	_DBGMFR
	dc.l	167772160
	dc.l	L1622
	dc.l	L3622
	dc.l	_DBGSCRX
	dc.l	167772160
	dc.l	L5622
	dc.l	L7622
	dc.l	_DBGCNT
	dc.l	167772160
	dc.l	L1722
	dc.l	L3722
	dc.l	_DBGTB
	dc.l	436207616
	dc.l	L5722
	dc.l	L7722
	dc.l	_DBGC2
	dc.l	167772160
	dc.l	L1032
	dc.l	L3032
	dc.l	_DBGTCR
	dc.l	167772160
	dc.l	L5032
	dc.l	L7032
	dc.l	_DBGSR
	dc.l	167772160
	dc.l	L1132
	dc.l	L3132
	dc.l	_DBGC1
	dc.l	167772160
	dc.l	L5132
	dc.l	L7132
	dc.l	_IRQCR
	dc.l	167772160
	dc.l	L1232
	dc.l	L3232
	dc.l	_ECLKCTL
	dc.l	167772160
	dc.l	L5232
	dc.l	L7232
	dc.l	_PARTIDL
	dc.l	167772160
	dc.l	L1332
	dc.l	L3332
	dc.l	_PARTIDH
	dc.l	167772160
	dc.l	L5332
	dc.l	L7332
	dc.l	_PARTID
	dc.l	436207616
	dc.l	L1432
	dc.l	L3432
	dc.l	_EPAGE
	dc.l	167772160
	dc.l	L5432
	dc.l	L7432
	dc.l	_RPAGE
	dc.l	167772160
	dc.l	L1532
	dc.l	L3532
	dc.l	_PPAGE
	dc.l	167772160
	dc.l	L5532
	dc.l	L7532
	dc.l	_MMCCTL1
	dc.l	167772160
	dc.l	L1632
	dc.l	L3632
	dc.l	_DIRECT
	dc.l	167772160
	dc.l	L5632
	dc.l	L7632
	dc.l	_GPAGE
	dc.l	167772160
	dc.l	L1732
	dc.l	L3732
	dc.l	_MODE
	dc.l	167772160
	dc.l	L5732
	dc.l	L7732
	dc.l	_RDRIV
	dc.l	167772160
	dc.l	L1042
	dc.l	L3042
	dc.l	_PUCR
	dc.l	167772160
	dc.l	L5042
	dc.l	L7042
	dc.l	_DDRE
	dc.l	167772160
	dc.l	L1142
	dc.l	L3142
	dc.l	_PORTE
	dc.l	167772160
	dc.l	L5142
	dc.l	L7142
	dc.l	_DDRB
	dc.l	167772160
	dc.l	L1242
	dc.l	L3242
	dc.l	_DDRA
	dc.l	167772160
	dc.l	L5242
	dc.l	L7242
	dc.l	_PORTB
	dc.l	167772160
	dc.l	L1342
	dc.l	L3342
	dc.l	_PORTA
	dc.l	167772160
	dc.l	L5342
	dc.l	0
	.dopt	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:0",L2
	.dfile	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c"
L7552:
	dc.l	L3652
	dc.l	L1652
L3652:
	dc.b	"c:\Porting_Work\Co"
	dc.b	"smic_Work\Test\mul"
	dc.b	"ti1\vector_s12x.c",0
	dc.b	140
L5652:
	dc.b	"PIT0_Interrupt",0
	dc.b	6
L7652:
	dc.l	10304
	.dtable	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c~PIT0_Interrupt"
L1652:
	dc.l	L1752
	dc.l	L7552
	dc.l	L5652
	dc.l	17
	dc.l	17
	dc.l	1342177280
	dc.l	L7652
	dc.l	0
	dc.l	L3752
L3752:
	.dstring	"~ISR2_PIT0_Interrupt"
	.dstring	"~EE_ISR2_poststub"
	.dstring	"~EE_ISR2_prestub"
	.dstring	"~EE_s12xs_hal_stkchange"
	.dstring	"~EE_s12xs_hal_ready2stacked"
	.dstring	"~EE_IRQ_end_instance"
	.dstring	"~EE_SCISendBuffer"
	.dstring	"~EE_s12xs_disableIRQ"
	.dstring	"~EE_s12xs_enableIRQ"
	.dstring	"~_asm"
	.dstring	"~_asm"
	.dstring	"~_asm"
	dc.l	12
	.dstring	"~EE_IRQ_nesting_level"
	.dstring	"~EE_s12xs_temp_tos"
	.dstring	"~EE_hal_endcycle_next_tos"
	.dstring	"~EE_hal_endcycle_next_thread"
	.dstring	"~sci"
	.dstring	"~EE_pit0_initialized"
	.dstring	"~EE_buttons_initialized"
	.dstring	"~EE_s12xs_IRQ_tos"
	.dstring	"~EE_s12xs_active_tos"
	.dstring	"~PITCNT3"
	.dstring	"~PITLD3"
	.dstring	"~PITCNT2"
	.dstring	"~PITLD2"
	.dstring	"~PITCNT1"
	.dstring	"~PITLD1"
	.dstring	"~PITCNT0"
	.dstring	"~PITLD0"
	.dstring	"~PITMTLD1"
	.dstring	"~PITMTLD0"
	.dstring	"~PITTF"
	.dstring	"~PITINTE"
	.dstring	"~PITMUX"
	.dstring	"~PITCE"
	.dstring	"~PITFLT"
	.dstring	"~PITCFLMT"
	.dstring	"~PIFP"
	.dstring	"~PIEP"
	.dstring	"~DDRP"
	.dstring	"~PTP"
	.dstring	"~INT_CFDATA0"
	.dstring	"~INT_CFADDR"
	.dstring	"~DDRA"
	.dstring	"~PORTA"
	dc.l	33
	.source	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:17"
	switch	.text
_PIT0_Interrupt:
	.nobank
	.dstart	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c~PIT0_Interrupt:17-17"
	.dentry	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c~PIT0_Interrupt:-0.0"
	.dcall	"10,0;_PIT0_Interrupt"
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:82"
	.dline	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:17"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:82.2.24"
	incw	_EE_IRQ_nesting_level
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:86"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:86.2.29"
	ldd	_EE_IRQ_nesting_level
	dbne	d,L7752
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:87"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:87.4.52"
	.sfile	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h",87
	tfr	s, d
	.sfile
	std	_EE_s12xs_temp_tos
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:95"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:95.4.37"
	ldd	_EE_s12xs_IRQ_tos
	pshd	
	.sfile	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h",95
	tfr	d, s
	.sfile
	leas	2,s
L7752:
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_cpu.h:191"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_cpu.h:191.2"
	.sfile	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_cpu.h",191
	cli	
	.sfile
	.source	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:17"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:103"
	.dline	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:17"
	call	f_ISR2_PIT0_Interrupt
	.dcall	"_PIT0_Interrupt:f_ISR2_PIT0_Interrupt"
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_cpu.h:200"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_cpu.h:200.2"
	.sfile	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_cpu.h",200
	sei	
	.sfile
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:109"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_cpu.h:201"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:109.2.24"
	decw	_EE_IRQ_nesting_level
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:111"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:111.2.29"
	bne	L5552
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:114"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:114.1.7"
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:124"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:124.2.37"
	ldd	_EE_s12xs_temp_tos
	.sfile	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h",124
	tfr	d, s
	.sfile
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:132"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:132.2.23"
	call	f_EE_IRQ_end_instance
	.dcall	"_PIT0_Interrupt:f_EE_IRQ_end_instance"
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:134"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:134.2.33"
	ldd	_EE_hal_endcycle_next_thread
	bne	LC001
	ldd	_EE_hal_endcycle_next_thread+2
	beq	L1162
LC001:
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:136"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:136.4.32"
	clra	
	.sfile	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h",136
	tfr	a,ccrh
	.sfile
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:143"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:143.4.85"
	ldd	_EE_hal_endcycle_next_tos
	pshd	
	ldd	_EE_hal_endcycle_next_thread+2
	ldx	_EE_hal_endcycle_next_thread
	call	f_EE_s12xs_hal_ready2stacked
	.dcall	"_PIT0_Interrupt:f_EE_s12xs_hal_ready2stacked"
	leas	2,s
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:143"
	bra	L3162
L1162:
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:148"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:148.4.55"
	ldd	_EE_hal_endcycle_next_tos
	cpd	_EE_s12xs_active_tos
	beq	L3162
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:150"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:150.6.34"
	clra	
	.sfile	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h",150
	tfr	a,ccrh
	.sfile
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:154"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:154.6.54"
	ldd	_EE_hal_endcycle_next_tos
	call	f_EE_s12xs_hal_stkchange
	.dcall	"_PIT0_Interrupt:f_EE_s12xs_hal_stkchange"
L3162:
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:161"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:161.2.30"
	ldaa	#6
	.sfile	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h",161
	tfr	a,ccrh
	.sfile
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_cpu.h:191"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_cpu.h:191.2"
	.sfile	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_cpu.h",191
	cli	
	.sfile
L5552:
	.source	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:17"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:165"
	.dline	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:17"
	.dquit	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c~PIT0_Interrupt:0"
	rti	
	.dendfn	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:17-17"
	switch	.debug
L5262:
	dc.b	"ISR2_PIT0_Interrup"
	dc.b	"t",0
	dc.b	6
L7262:
	dc.l	14336
	.dtable	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c~ISR2_PIT0_Interrupt"
L1752:
	dc.l	L1362
	dc.l	L7552
	dc.l	L5262
	dc.l	17
	dc.l	28
	dc.l	1342177280
	dc.l	L7262
	dc.l	0
	dc.l	L3362
L3362:
	.dstring	"~EE_PIT0_clear_ISRflag"
	.dstring	"~EE_fp_ActivateTask"
	dc.l	2
	.dstring	"~timer_divisor"
	.dstring	"~timer_fired"
	.dstring	"~PITTF"
	dc.l	3
	.source	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:17-18"
.ftext:	section	.text
f_ISR2_PIT0_Interrupt:
	.dstart	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c~ISR2_PIT0_Interrupt:+17-18"
	.dentry	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c~ISR2_PIT0_Interrupt:-0.0"
	.dcall	"3,0,f_ISR2_PIT0_Interrupt"
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\mcu/cosmic_hs12xs/inc/ee_pit.h:56"
	.dline	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:20.1.24"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\mcu/cosmic_hs12xs/inc/ee_pit.h:56.1.21"
	ldab	#1
	stab	_PITTF
	.source	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:21"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\mcu/cosmic_hs12xs/inc/ee_pit.h:57"
	.dline	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:21.1.16"
	incw	_timer_divisor
	.source	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:22"
	.dline	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:22.1.27"
	ldd	_timer_divisor
	cpd	#10000
	bne	L5362
	.source	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:23"
	.dline	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:23.2.19"
	clra	
	clrb	
	std	_timer_divisor
	.source	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:24"
	.dline	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:24.2.15"
	incw	_timer_fired
	.source	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:25"
	.dline	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:25.8.27"
	clrx	
	call	f_EE_fp_ActivateTask
	.dcall	"f_ISR2_PIT0_Interrupt:f_EE_fp_ActivateTask"
L5362:
	.source	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:28"
	.dline	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:28"
	.dquit	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c~ISR2_PIT0_Interrupt:0"
	rtc	
	.dendfn	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:28-28"
	switch	.debug
L1562:
	dc.b	"Buttons_Interrupt",0
	dc.b	6
L3562:
	dc.l	10304
	.dtable	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c~Buttons_Interrupt"
L1362:
	dc.l	L5562
	dc.l	L7552
	dc.l	L1562
	dc.l	31
	dc.l	31
	dc.l	1342177280
	dc.l	L3562
	dc.l	0
	dc.l	L7562
L7562:
	.dstring	"~ISR2_Buttons_Interrupt"
	.dstring	"~EE_ISR2_poststub"
	.dstring	"~EE_ISR2_prestub"
	.dstring	"~EE_s12xs_hal_stkchange"
	.dstring	"~EE_s12xs_hal_ready2stacked"
	.dstring	"~EE_IRQ_end_instance"
	.dstring	"~EE_s12xs_disableIRQ"
	.dstring	"~EE_s12xs_enableIRQ"
	.dstring	"~_asm"
	.dstring	"~_asm"
	.dstring	"~_asm"
	dc.l	11
	.dstring	"~EE_IRQ_nesting_level"
	.dstring	"~EE_s12xs_temp_tos"
	.dstring	"~EE_hal_endcycle_next_tos"
	.dstring	"~EE_hal_endcycle_next_thread"
	.dstring	"~EE_s12xs_IRQ_tos"
	.dstring	"~EE_s12xs_active_tos"
	dc.l	6
	.source	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:31"
	switch	.text
_Buttons_Interrupt:
	.nobank
	.dstart	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c~Buttons_Interrupt:31-31"
	.dentry	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c~Buttons_Interrupt:-0.0"
	.dcall	"10,0;_Buttons_Interrupt"
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:82"
	.dline	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:31"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:82.2.24"
	incw	_EE_IRQ_nesting_level
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:86"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:86.2.29"
	ldd	_EE_IRQ_nesting_level
	dbne	d,L3662
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:87"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:87.4.52"
	.sfile	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h",87
	tfr	s, d
	.sfile
	std	_EE_s12xs_temp_tos
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:95"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:95.4.37"
	ldd	_EE_s12xs_IRQ_tos
	pshd	
	.sfile	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h",95
	tfr	d, s
	.sfile
	leas	2,s
L3662:
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_cpu.h:191"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_cpu.h:191.2"
	.sfile	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_cpu.h",191
	cli	
	.sfile
	.source	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:31"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:103"
	.dline	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:31"
	call	f_ISR2_Buttons_Interrupt
	.dcall	"_Buttons_Interrupt:f_ISR2_Buttons_Interrupt"
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_cpu.h:200"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_cpu.h:200.2"
	.sfile	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_cpu.h",200
	sei	
	.sfile
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:109"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_cpu.h:201"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:109.2.24"
	decw	_EE_IRQ_nesting_level
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:111"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:111.2.29"
	bne	L7462
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:114"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:114.1.7"
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:124"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:124.2.37"
	ldd	_EE_s12xs_temp_tos
	.sfile	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h",124
	tfr	d, s
	.sfile
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:132"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:132.2.23"
	call	f_EE_IRQ_end_instance
	.dcall	"_Buttons_Interrupt:f_EE_IRQ_end_instance"
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:134"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:134.2.33"
	ldd	_EE_hal_endcycle_next_thread
	bne	LC002
	ldd	_EE_hal_endcycle_next_thread+2
	beq	L5762
LC002:
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:136"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:136.4.32"
	clra	
	.sfile	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h",136
	tfr	a,ccrh
	.sfile
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:143"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:143.4.85"
	ldd	_EE_hal_endcycle_next_tos
	pshd	
	ldd	_EE_hal_endcycle_next_thread+2
	ldx	_EE_hal_endcycle_next_thread
	call	f_EE_s12xs_hal_ready2stacked
	.dcall	"_Buttons_Interrupt:f_EE_s12xs_hal_ready2stacked"
	leas	2,s
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:143"
	bra	L7762
L5762:
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:148"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:148.4.55"
	ldd	_EE_hal_endcycle_next_tos
	cpd	_EE_s12xs_active_tos
	beq	L7762
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:150"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:150.6.34"
	clra	
	.sfile	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h",150
	tfr	a,ccrh
	.sfile
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:154"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:154.6.54"
	ldd	_EE_hal_endcycle_next_tos
	call	f_EE_s12xs_hal_stkchange
	.dcall	"_Buttons_Interrupt:f_EE_s12xs_hal_stkchange"
L7762:
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:161"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:161.2.30"
	ldaa	#6
	.sfile	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h",161
	tfr	a,ccrh
	.sfile
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_cpu.h:191"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_cpu.h:191.2"
	.sfile	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_cpu.h",191
	cli	
	.sfile
L7462:
	.source	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:31"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\cpu/cosmic_hs12xs/inc/ee_irqstub.h:165"
	.dline	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:31"
	.dquit	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c~Buttons_Interrupt:0"
	rti	
	.dendfn	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:31-31"
	switch	.debug
L5172:
	dc.b	"ISR2_Buttons_Inter"
	dc.b	"rupt",0
	dc.b	6
L7172:
	dc.l	14336
	.dtable	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c~ISR2_Buttons_Interrupt"
L5562:
	dc.l	L1272
	dc.l	L7552
	dc.l	L5172
	dc.l	31
	dc.l	39
	dc.l	1342177280
	dc.l	L7172
	dc.l	L5272
	dc.l	L3272
L7272:
	dc.b	"bx",0
	dc.b	3
L1372:
	dc.l	32768
L3372:
	dc.b	"x",0
	dc.b	3
L5372:
	dc.b	"bx",0
	dc.b	3
L7372:
	dc.l	32768
L1472:
	dc.b	"x",0
	dc.b	3
L3472:
	dc.b	"bx",0
	dc.b	3
L5472:
	dc.l	32768
L7472:
	dc.b	"x",0
	dc.b	3
L5272:
	dc.l	L7272
	dc.l	1
	dc.l	167772160
	dc.l	L5472
	dc.l	L3372
	dc.l	2
	dc.l	167772160
	dc.l	L5472
	dc.l	L5372
	dc.l	1
	dc.l	167772160
	dc.l	L5472
	dc.l	L1472
	dc.l	2
	dc.l	167772160
	dc.l	L5472
	dc.l	L3472
	dc.l	1
	dc.l	167772160
	dc.l	L5472
	dc.l	L7472
	dc.l	2
	dc.l	167772160
	dc.l	L5472
	dc.l	0
L3272:
	.dstring	"~mydelay"
	.dstring	"~EE_fp_ActivateTask"
	.dstring	"~EE_demo9s12xsfame_buttons_clear_ISRflag"
	.dstring	"~EE_demo9s12xsfame_buttons_enable_interrupts"
	.dstring	"~EE_demo9s12xsfame_buttons_disable_interrupts"
	dc.l	5
	.dstring	"~button_fired"
	.dstring	"~PIFP"
	.dstring	"~PIEP"
	dc.l	3
	.source	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:31-32"
	switch	.ftext
f_ISR2_Buttons_Interrupt:
	.dstart	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c~ISR2_Buttons_Interrupt:+31-32"
	pshd	
OFST:	set	2
	.dentry	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c~ISR2_Buttons_Interrupt:-2.2"
	.dcall	"5,0,f_ISR2_Buttons_Interrupt"
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\board\cosmic_hs12xs_demo9s12xsfame\inc\demo9s12xsfame_peripherals.h:153"
	.dline	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:33.1.40"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\board\cosmic_hs12xs_demo9s12xsfame\inc\demo9s12xsfame_peripherals.h:153.2.33"
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\board\cosmic_hs12xs_demo9s12xsfame\inc\demo9s12xsfame_peripherals.h:154"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\board\cosmic_hs12xs_demo9s12xsfame\inc\demo9s12xsfame_peripherals.h:154.1.19"
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\board\cosmic_hs12xs_demo9s12xsfame\inc\demo9s12xsfame_peripherals.h:155"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\board\cosmic_hs12xs_demo9s12xsfame\inc\demo9s12xsfame_peripherals.h:155.1.10"
	bclr	_PIEP,1
	.source	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:34"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\board\cosmic_hs12xs_demo9s12xsfame\inc\demo9s12xsfame_peripherals.h:156"
	.dline	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:34.1.15"
	incw	_button_fired
	.source	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:35"
	.dline	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:35.1.20"
	clrx	
	ldd	#1
	call	f_EE_fp_ActivateTask
	.dcall	"f_ISR2_Buttons_Interrupt:f_EE_fp_ActivateTask"
	.source	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:36"
	.dline	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:36.1.25"
	ldx	#0
	ldd	#10000
	call	f_mydelay
	.dcall	"f_ISR2_Buttons_Interrupt:f_mydelay"
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\board\cosmic_hs12xs_demo9s12xsfame\inc\demo9s12xsfame_peripherals.h:161"
	.dline	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:37.1.39"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\board\cosmic_hs12xs_demo9s12xsfame\inc\demo9s12xsfame_peripherals.h:161.2.33"
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\board\cosmic_hs12xs_demo9s12xsfame\inc\demo9s12xsfame_peripherals.h:162"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\board\cosmic_hs12xs_demo9s12xsfame\inc\demo9s12xsfame_peripherals.h:162.1.10"
	bset	_PIFP,1
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\board\cosmic_hs12xs_demo9s12xsfame\inc\demo9s12xsfame_peripherals.h:163"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\board\cosmic_hs12xs_demo9s12xsfame\inc\demo9s12xsfame_peripherals.h:163.3.12"
	bset	_PIEP,1
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\board\cosmic_hs12xs_demo9s12xsfame\inc\demo9s12xsfame_peripherals.h:169"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\board\cosmic_hs12xs_demo9s12xsfame\inc\demo9s12xsfame_peripherals.h:164"
	.dline	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:38.1.35"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\board\cosmic_hs12xs_demo9s12xsfame\inc\demo9s12xsfame_peripherals.h:169.2.33"
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\board\cosmic_hs12xs_demo9s12xsfame\inc\demo9s12xsfame_peripherals.h:170"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\board\cosmic_hs12xs_demo9s12xsfame\inc\demo9s12xsfame_peripherals.h:170.1.10"
	bset	_PIFP,1
	.source	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:39"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\board\cosmic_hs12xs_demo9s12xsfame\inc\demo9s12xsfame_peripherals.h:171"
	.dline	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:39"
	.dquit	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c~ISR2_Buttons_Interrupt:0"
	puly	
	rtc	
	.dendfn	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:39-39"
	switch	.debug
L5572:
	dc.b	"dummit",0
	dc.b	1
L7572:
	dc.l	10304
	.dtable	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c~dummit"
L1272:
	dc.l	L1672
	dc.l	L7552
	dc.l	L5572
	dc.l	46
	dc.l	49
	dc.l	1342177280
	dc.l	L7572
	dc.l	L5672
	dc.l	L3672
L7672:
	dc.b	"buffer",0
	dc.b	3
L1772:
	dc.l	32768
L3772:
	dc.b	"sci_num",0
	dc.b	3
L5772:
	dc.l	32768
L7772:
	dc.b	"sci_pt",0
	dc.b	3
L1003:
	dc.l	0
	dc.l	0
L5672:
	dc.l	L7672
	dc.l	1
	dc.l	167772160
	dc.l	L5772
	dc.l	L3772
	dc.l	2
	dc.l	167772160
	dc.l	L5772
	dc.l	L7772
	dc.l	4
	dc.l	167772224
	dc.l	L1003
	dc.l	0
L3672:
	.dstring	"~EE_SCISendBuffer"
	dc.l	1
	.dstring	"~sci"
	dc.l	1
	.source	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:46-47"
	switch	.text
L1572_dummit:
	.nobank
	.dstart	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c~dummit:46-47"
	leas	-4,s
OFST:	set	4
	.dentry	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c~dummit:-4.4"
	.dcall	"14,0;L1572_dummit"
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\mcu/cosmic_hs12xs/inc/ee_sci.h:110"
	.dline	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:48.2.30"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\mcu/cosmic_hs12xs/inc/ee_sci.h:110.2.22"
	ldab	_sci
	bne	L3003
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\mcu/cosmic_hs12xs/inc/ee_sci.h:111"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\mcu/cosmic_hs12xs/inc/ee_sci.h:111.4.17"
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\mcu/cosmic_hs12xs/inc/ee_sci.h:111"
L3572:
	.source	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:49"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\mcu/cosmic_hs12xs/inc/ee_sci.h:120"
	.dline	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:49.1"
	.dquit	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c~dummit:0"
	leas	4,s
	rti	
L3003:
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\mcu/cosmic_hs12xs/inc/ee_sci.h:112"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\mcu/cosmic_hs12xs/inc/ee_sci.h:112.2.32"
	ldy	_sci+1
	sty	OFST-4,s
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\mcu/cosmic_hs12xs/inc/ee_sci.h:112"
L1103:
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\mcu/cosmic_hs12xs/inc/ee_sci.h:114"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\mcu/cosmic_hs12xs/inc/ee_sci.h:114.2.30"
	brclr	4,y,128,L1103
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\mcu/cosmic_hs12xs/inc/ee_sci.h:117"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\mcu/cosmic_hs12xs/inc/ee_sci.h:117.2.25"
	ldab	#238
	stab	7,y
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\mcu/cosmic_hs12xs/inc/ee_sci.h:118"
	.dline	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\mcu/cosmic_hs12xs/inc/ee_sci.h:118.2.14"
	.source	"C:\cygwin\home\Dario\repos\ee\trunk\ee\pkg\.\mcu/cosmic_hs12xs/inc/ee_sci.h:118"
	bra	L3572
	.dendfn	"c:\Porting_Work\Cosmic_Work\Test\multi1\vector_s12x.c:49-49"
.vector:	section	.data
__vectab:
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:_PIT0_Interrupt"
	dc.w	_PIT0_Interrupt
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:_Buttons_Interrupt"
	dc.w	_Buttons_Interrupt
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:L1572_dummit"
	dc.w	L1572_dummit
	.dcall	"__vectab.T:__stext"
	dc.w	__stext
	switch	.debug
L1672:
	dc.l	0
	dc.l	L7552
	dc.l	0
	dc.l	1
	dc.l	151
	dc.l	0
	dc.l	0
	dc.l	L5103
L7103:
	dc.b	"_vectab",0
	dc.b	6
L1203:
	dc.l	32768
	dc.l	120
	dc.l	10304
	dc.l	0
L5103:
	dc.l	L7103
	dc.w	page(__vectab),__vectab
	dc.l	1342177496
	dc.l	L1203
	dc.l	0
	xdef	__vectab
	xref	__stext
	xdef	_Buttons_Interrupt
	xdef	f_ISR2_Buttons_Interrupt
	xdef	_PIT0_Interrupt
	xdef	f_ISR2_PIT0_Interrupt
	xref	_button_fired
	xref	_timer_divisor
	xref	_timer_fired
	xref	f_mydelay
	xref	f_EE_s12xs_hal_stkchange
	xref	f_EE_s12xs_hal_ready2stacked
	xref	f_EE_IRQ_end_instance
	xref	_EE_IRQ_nesting_level
	xref	_EE_s12xs_temp_tos
	xref	_EE_hal_endcycle_next_tos
	xref	_EE_hal_endcycle_next_thread
	xref	_sci
	xref	_EE_pit0_initialized
	xref	f_EE_fp_ActivateTask
	xref	_EE_buttons_initialized
	xref	_EE_s12xs_IRQ_tos
	xref	_EE_s12xs_active_tos
	even
L2:
	dc.l	256
	dc.l	128
	dc.l	64
	dc.l	2
	dc.l	512
	dc.l	8192
	dc.l	32
	dc.l	0
	dc.l	16384
	dc.l	16
	dc.l	0
	dc.l	0
	dc.l	0
	dc.l	0
	dc.l	0
	dc.l	0
	dc.l	0
	end
