/*	IO DEFINITIONS FOR MC9S12XS256, MC9S12XS128, MC9S12XS64
 *	Copyright (c) 2008 by COSMIC Software
 */
#ifndef __IOXS256_H__
#define __IOXS256_H__
 
typedef unsigned char __uchar;
typedef unsigned int __uint;

/*	PIM Module  
 */
volatile __uchar PORTA         @0x00;	/* port A */
volatile __uchar PORTB         @0x01;	/* port B */
volatile __uchar DDRA          @0x02;	/* data direction port A */
volatile __uchar DDRB          @0x03;	/* data direction port B */
volatile __uchar PORTE         @0x08;	/* port E */
volatile __uchar DDRE          @0x09;	/* data direction port E */
volatile __uchar PUCR          @0x0c;	/* pull-up control register */
volatile __uchar RDRIV         @0x0d;	/* reduced drive of I/O lines */

/*	MMC Module  
 */
volatile __uchar MODE          @0x0b;	/* mode register */
volatile __uchar GPAGE         @0x10;	/* global page register */
volatile __uchar DIRECT        @0x11;	/* direct page register */
volatile __uchar MMCCTL1       @0x13;	/* mapping control register 1 */
volatile __uchar PPAGE         @0x15;	/* program page register */
volatile __uchar RPAGE         @0x16;	/* ram page register */
volatile __uchar EPAGE         @0x17;	/* eeprom page register */
volatile __uint  PARTID        @0x1a;	/* part ID register */
volatile __uchar PARTIDH       @0x1a;	/* part ID register high */
volatile __uchar PARTIDL       @0x1b;	/* part ID register low */

/*	IRQ Module  
 */
volatile __uchar ECLKCTL       @0x1c;	/* eclk control register */
volatile __uchar IRQCR         @0x1e;	/* interrupt control register */

/*	DBG Module  
 */
volatile __uchar DBGC1         @0x20;	/* debug control register 1 */
volatile __uchar DBGSR         @0x21;	/* debug status register */
volatile __uchar DBGTCR        @0x22;	/* debug trace control register */
volatile __uchar DBGC2         @0x23;	/* debug control register 2 */
volatile __uint  DBGTB         @0x24;	/* debug trace buffer register */
volatile __uchar DBGCNT        @0x26;	/* debug count register */
volatile __uchar DBGSCRX       @0x27;	/* debug state control register */
volatile __uchar DBGMFR        @0x27;	/* debug match flag register */
volatile __uchar DBGXCTL       @0x28;	/* debug comparator control register */
volatile __uchar DBGXAH        @0x29;	/* debug comparator address high */
volatile __uchar DBGXAM        @0x2a;	/* debug comparator address medium */
volatile __uchar DBGXAL        @0x2b;	/* debug comparator address low */
volatile __uint  DBGXD         @0x2c;	/* debug comparator data */
volatile __uchar DBGXDH        @0x2c;	/* debug comparator data high */
volatile __uchar DBGXDL        @0x2d;	/* debug comparator data low */
volatile __uint  DBGXDM        @0x2e;	/* debug comparator data mask */
volatile __uchar DBGXDHM       @0x2e;	/* debug comparator data mask high */
volatile __uchar DBGXDLM       @0x2f;	/* debug comparator data mask low */

/*	PIM Module  
 */
volatile __uchar PORTK         @0x32;	/* port K data register */
volatile __uchar DDRK          @0x33;	/* port K data direction */

/*	CRG Module  
 */
volatile __uchar SYNR          @0x34;	/* synthesizer register */
volatile __uchar REFDV         @0x35;	/* reference divider register */
volatile __uchar POSTDIV       @0x36;	/* post divider register */
volatile __uchar CRGFLG        @0x37;	/* clock generator flag register */
volatile __uchar CRGINT        @0x38;	/* clock interrupt enable */
volatile __uchar CLKSEL        @0x39;	/* clock select register */
volatile __uchar PLLCTL        @0x3a;	/* PLL control register */
volatile __uchar RTICTL        @0x3b;	/* clock real time control reg. */
volatile __uchar COPCTL        @0x3c;	/* COP control register */
volatile __uchar FORBYP        @0x3d;	/* clock force and bypass reg. */
volatile __uchar CTCTL         @0x3e;	/* clock test control register */
volatile __uchar ARMCOP        @0x3f;	/* COP arm/reset register */

/*	Enhanced Capture Timer Module  
 */
volatile __uchar TIOS          @0x40;	/* timer select register */
volatile __uchar CFORC         @0x41;	/* compare force register */
volatile __uchar OC7M          @0x42;	/* oc7 mask register */
volatile __uchar OC7D          @0x43;	/* oc7 data register */
volatile __uint  TCNT          @0x44;	/* timer counter */
volatile __uchar TCNTH         @0x44;	/* timer counter high */
volatile __uchar TCNTL         @0x45;	/* timer counter low */
volatile __uchar TSCR1         @0x46;	/* system control register 1 */
volatile __uchar TTOV          @0x47;	/* toggle on overflow register */
volatile __uchar TCTL1         @0x48;	/* control register 1 */
volatile __uchar TCTL2         @0x49;	/* control register 2 */
volatile __uchar TCTL3         @0x4a;	/* control register 3 */
volatile __uchar TCTL4         @0x4b;	/* control register 4 */
volatile __uchar TIE           @0x4c;	/* interrupt enable register */
volatile __uchar TSCR2         @0x4d;	/* system control register 2 */
volatile __uchar TFLG1         @0x4e;	/* interrupt flag register 1 */
volatile __uchar TFLG2         @0x4f;	/* interrupt flag register 2 */
volatile __uint  TC0           @0x50;	/* capture/compare register 0 */
volatile __uint  TC1           @0x52;	/* capture/compare register 0 */
volatile __uint  TC2           @0x54;	/* capture/compare register 0 */
volatile __uint  TC3           @0x56;	/* capture/compare register 0 */
volatile __uint  TC4           @0x58;	/* capture/compare register 0 */
volatile __uint  TC5           @0x5a;	/* capture/compare register 0 */
volatile __uint  TC6           @0x5c;	/* capture/compare register 0 */
volatile __uint  TC7           @0x5e;	/* capture/compare register 0 */
volatile __uchar PACTL         @0x60;	/* pulse accumulator A control */
volatile __uchar PAFLG         @0x61;	/* pulse accumulator A flag */
volatile __uint  PACNT         @0x62;	/* pulse accumulators count reg */
volatile __uchar PACNTH        @0x62;	/* pulse accumulators count reg high */
volatile __uchar PACNTL        @0x63;	/* pulse accumulators count reg low */
volatile __uchar OCPD          @0x6c;	/* output compare pin disconnect */
volatile __uchar PTPSR         @0x6e;	/* precision prescaler select reg */

/*	SCI0 Module  
 */
volatile __uint  SCI0BD        @0xc8;	/* SCI 0 baud rate */
volatile __uchar SCI0BDH       @0xc8;	/* SCI 0 baud rate high */
volatile __uchar SCI0BDL       @0xc9;	/* SCI 0 baud rate low */
volatile __uchar SCI0CR1       @0xca;	/* SCI 0 control register 1 */
volatile __uchar SCI0ASR1      @0xc8;	/* SCI 0 alternative status reg */
volatile __uchar SCI0ACR1      @0xc9;	/* SCI 0 alternative control reg 1 */
volatile __uchar SCI0ACR2      @0xca;	/* SCI 0 alternative control reg 2 */
volatile __uchar SCI0CR2       @0xcb;	/* SCI 0 control register 2 */
volatile __uchar SCI0SR1       @0xcc;	/* SCI 0 status register 1 */
volatile __uchar SCI0SR2       @0xcd;	/* SCI 0 status register 2 */
volatile __uint  SCI0DR        @0xce;	/* SCI 0 data register */
volatile __uchar SCI0DRH       @0xce;	/* SCI 0 data register high */
volatile __uchar SCI0DRL       @0xcf;	/* SCI 0 data register low */

/*	SCI1 Module  
 */
volatile __uint  SCI1BD        @0xd0;	/* SCI 1 baud rate */
volatile __uchar SCI1BDH       @0xd0;	/* SCI 1 baud rate high */
volatile __uchar SCI1BDL       @0xd1;	/* SCI 1 baud rate low */
volatile __uchar SCI1CR1       @0xd2;	/* SCI 1 control register 1 */
volatile __uchar SCI1ASR1      @0xd0;	/* SCI 1 alternative status reg */
volatile __uchar SCI1ACR1      @0xd1;	/* SCI 1 alternative control reg 1 */
volatile __uchar SCI1ACR2      @0xd2;	/* SCI 1 alternative control reg 2 */
volatile __uchar SCI1CR2       @0xd3;	/* SCI 1 control register 2 */
volatile __uchar SCI1SR1       @0xd4;	/* SCI 1 status register 1 */
volatile __uchar SCI1SR2       @0xd5;	/* SCI 1 status register 2 */
volatile __uchar SCI1DRH       @0xd6;	/* SCI 1 data register high */
volatile __uchar SCI1DRL       @0xd7;	/* SCI 1 data register low */

/*	SPI0 Module  
 */	
volatile __uchar SPI0CR1       @0xd8;	/* SPI 0 control register 1 */
volatile __uchar SPI0CR2       @0xd9;	/* SPI 0 control register 2 */
volatile __uchar SPI0BR        @0xda;	/* SPI 0 baud rate register */
volatile __uchar SPI0SR        @0xdb;	/* SPI 0 status register */
volatile __uchar SPI0DRH       @0xdc;	/* SPI 0 data register high */
volatile __uchar SPI0DRL       @0xdd;	/* SPI 0 data register low */

/*	NVM Control Module  
 */
volatile __uchar FCLKDIV       @0x100;	/* flash clock divider */
volatile __uchar FSEC          @0x101;	/* flash security register */
volatile __uchar FCCOBIX       @0x102;	/* flash operation index register */
volatile __uchar FECCRIX       @0x103;	/* flash ecc index register */
volatile __uchar FCNFG         @0x104;	/* flash configuration register */
volatile __uchar FERCNFG       @0x105;	/* flash error config register */
volatile __uchar FSTAT         @0x106;	/* flash status register */
volatile __uchar FERSTAT       @0x107;	/* flash error status register */
volatile __uchar FPROT         @0x108;	/* P-flash protection register */
volatile __uchar DFPROT        @0x109;	/* D-flash protection register */
volatile __uint  FCCOB         @0x10a;	/* flash command object */
volatile __uchar FCCOBHI       @0x10a;	/* flash command object high */
volatile __uchar FCCOBLO       @0x10b;	/* flash command object low */
volatile __uint  FEECR         @0x10e;	/* flash address register */
volatile __uchar FEECRHI       @0x10e;	/* flash address register high */
volatile __uchar FEECRLO       @0x10f;	/* flash address register low */
volatile __uint  FOPT          @0x110;	/* flash option register */

/*	INT module
 */
volatile __uchar IVBR          @0x121;	/* vector base register */
volatile __uchar INT_XGPRIO    @0x126;	/* interrupt priority config. */
volatile __uchar INT_CFADDR    @0x127;	/* interrupt priority config. */
volatile __uchar INT_CFDATA0   @0x128;	/* interrupt request config. reg 0 */
volatile __uchar INT_CFDATA1   @0x129;	/* interrupt request config. reg 1 */
volatile __uchar INT_CFDATA2   @0x12a;	/* interrupt request config. reg 2 */
volatile __uchar INT_CFDATA3   @0x12b;	/* interrupt request config. reg 3 */
volatile __uchar INT_CFDATA4   @0x12c;	/* interrupt request config. reg 4 */
volatile __uchar INT_CFDATA5   @0x12d;	/* interrupt request config. reg 5 */
volatile __uchar INT_CFDATA6   @0x12e;	/* interrupt request config. reg 6 */
volatile __uchar INT_CFDATA7   @0x12f;	/* interrupt request config. reg 7 */

/*	CAN0 Module  
 */
volatile __uchar CAN0CTL0      @0x140;	/* CAN0 control register 0 */
volatile __uchar CAN0CTL1      @0x141;	/* CAN0 control register 1 */
volatile __uchar CAN0BTR0      @0x142;	/* CAN0 bus timing register 0 */
volatile __uchar CAN0BTR1      @0x143;	/* CAN0 bus timing register 1 */
volatile __uchar CAN0RFLG      @0x144;	/* CAN0 receiver flag register */
volatile __uchar CAN0RIER      @0x145;	/* CAN0 receiver interrupt reg */
volatile __uchar CAN0TFLG      @0x146;	/* CAN0 transmitter flag reg */
volatile __uchar CAN0TIER      @0x147;	/* CAN0 transmitter control reg */
volatile __uchar CAN0TARQ      @0x148;	/* CAN0 transmitter abort req. */
volatile __uchar CAN0TAAK      @0x149;	/* CAN0 transmitter abort ack. */
volatile __uchar CAN0TBSEL     @0x14a;	/* CAN0 transmit buffer selection */
volatile __uchar CAN0IDAC      @0x14b;	/* CAN0 identifier acceptance */
volatile __uchar CAN0MISC      @0x14d;	/* CAN0 micellaneous register */
volatile __uchar CAN0RXERR     @0x14e;	/* CAN0 receive error counter */
volatile __uchar CAN0TXERR     @0x14f;	/* CAN0 transmit error counter */
volatile __uchar CAN0IDAR0     @0x150;	/* CAN0 id acceptance reg 0 */
volatile __uchar CAN0IDAR1     @0x151;	/* CAN0 id acceptance reg 1 */
volatile __uchar CAN0IDAR2     @0x152;	/* CAN0 id acceptance reg 2 */
volatile __uchar CAN0IDAR3     @0x153;	/* CAN0 id acceptance reg 3 */
volatile __uchar CAN0IDMR0     @0x154;	/* CAN0 id mask register 0 */
volatile __uchar CAN0IDMR1     @0x155;	/* CAN0 id mask register 1 */
volatile __uchar CAN0IDMR2     @0x156;	/* CAN0 id mask register 2 */
volatile __uchar CAN0IDMR3     @0x157;	/* CAN0 id mask register 3 */
volatile __uchar CAN0IDAR4     @0x158;	/* CAN0 id acceptance reg 4 */
volatile __uchar CAN0IDAR5     @0x159;	/* CAN0 id acceptance reg 5 */
volatile __uchar CAN0IDAR6     @0x15a;	/* CAN0 id acceptance reg 6 */
volatile __uchar CAN0IDAR7     @0x15b;	/* CAN0 id acceptance reg 7 */
volatile __uchar CAN0IDMR4     @0x15c;	/* CAN0 id mask register 4 */
volatile __uchar CAN0IDMR5     @0x15d;	/* CAN0 id mask register 5 */
volatile __uchar CAN0IDMR6     @0x15e;	/* CAN0 id mask register 6 */
volatile __uchar CAN0IDMR7     @0x15f;	/* CAN0 id mask register 7 */
volatile __uchar CAN0RXFG[16]  @0x160;	/* CAN0 receive buffer */
volatile __uchar CAN0TXFG[16]  @0x170;	/* CAN0 transmit buffer */

/*	Port T Module  
 */
volatile __uchar PTT           @0x240;	/* port T data register */
volatile __uchar PTIT          @0x241;	/* port T input register */
volatile __uchar DDRT          @0x242;	/* port T data direction */
volatile __uchar RDRT          @0x243;	/* port T reduce drive */
volatile __uchar PERT          @0x244;	/* port T pull enable */
volatile __uchar PPST          @0x245;	/* port T polarity select */
volatile __uchar PTTRR         @0x247;	/* port T routing register */

/*	Port S Module  
 */
volatile __uchar PTS           @0x248;	/* port S data register */
volatile __uchar PTIS          @0x249;	/* port S input register */
volatile __uchar DDRS          @0x24a;	/* port S data direction */
volatile __uchar RDRS          @0x24b;	/* port S reduce drive */
volatile __uchar PERS          @0x24c;	/* port S pull enable */
volatile __uchar PPSS          @0x24d;	/* port S polarity select */
volatile __uchar WOMS          @0x24e;	/* port S wired-or mode */

/*	Port M Module  
 */
volatile __uchar PTM           @0x250;	/* port M data register */
volatile __uchar PTIM          @0x251;	/* port M input register */
volatile __uchar DDRM          @0x252;	/* port M data direction */
volatile __uchar RDRM          @0x253;	/* port M reduce drive */
volatile __uchar PERM          @0x254;	/* port M pull enable */
volatile __uchar PPSM          @0x255;	/* port M polarity select */
volatile __uchar WOMM          @0x256;	/* port M wired-or mode */
volatile __uchar MODRR         @0x257;	/* module routing register */

/*	Port P Module  
 */
volatile __uchar PTP           @0x258;	/* port P data register */
volatile __uchar PTIP          @0x259;	/* port P input register */
volatile __uchar DDRP          @0x25a;	/* port P data direction */
volatile __uchar RDRP          @0x25b;	/* port P reduce drive */
volatile __uchar PERP          @0x25c;	/* port P pull enable */
volatile __uchar PPSP          @0x25d;	/* port P polarity select */
volatile __uchar PIEP          @0x25e;	/* port P interrupt enable */
volatile __uchar PIFP          @0x25f;	/* port P interrupt flag */

/*	Port H Module  
 */
volatile __uchar PTH           @0x260;	/* port H data register */
volatile __uchar PTIH          @0x261;	/* port H input register */
volatile __uchar DDRH          @0x262;	/* port H data direction */
volatile __uchar RDRH          @0x263;	/* port H reduce drive */
volatile __uchar PERH          @0x264;	/* port H pull enable */
volatile __uchar PPSH          @0x265;	/* port H polarity select */
volatile __uchar PIEH          @0x266;	/* port H interrupt enable */
volatile __uchar PIFH          @0x267;	/* port H interrupt flag */

/*	Port J Module  
 */
volatile __uchar PTJ           @0x268;	/* port J data register */
volatile __uchar PTIJ          @0x269;	/* port J input register */
volatile __uchar DDRJ          @0x26a;	/* port J data direction */
volatile __uchar RDRJ          @0x26b;	/* port J reduce drive */
volatile __uchar PERJ          @0x26c;	/* port J pull enable */
volatile __uchar PPSJ          @0x26d;	/* port J polarity select */
volatile __uchar PIEJ          @0x26e;	/* port J interrupt enable */
volatile __uchar PIFJ          @0x26f;	/* port J interrupt flag */

/*	Port AD0 Module  
 */
volatile __uchar PT0AD0        @0x270;	/* port AD0 data register 0 */
volatile __uchar PT1AD0        @0x271;	/* port AD0 data register 1 */
volatile __uchar DDR0AD0       @0x272;	/* port AD0 data direction 0 */
volatile __uchar DDR1AD0       @0x273;	/* port AD0 data direction 1 */
volatile __uchar RDR0AD0       @0x274;	/* port AD0 reduce drive 0 */
volatile __uchar RDR1AD0       @0x275;	/* port AD0 reduce drive 1 */
volatile __uchar PER0AD0       @0x276;	/* port AD0 pull enable 0 */
volatile __uchar PER1AD0       @0x277;	/* port AD0 pull enable 1 */

/*	ATD0 Module  
 */
volatile __uchar ATD0CTL0      @0x2c0;	/* ATD0 control register 0 */
volatile __uchar ATD0CTL1      @0x2c1;	/* ATD0 control register 1 */
volatile __uchar ATD0CTL2      @0x2c2;	/* ATD0 control register 2 */
volatile __uchar ATD0CTL3      @0x2c3;	/* ATD0 control register 3 */
volatile __uchar ATD0CTL4      @0x2c4;	/* ATD0 control register 4 */
volatile __uchar ATD0CTL5      @0x2c5;	/* ATD0 control register 5 */
volatile __uchar ATD0STAT0     @0x2c6;	/* ATD0 status register 0 */
volatile __uint  ATD0CMPE      @0x2c8;	/* ATD0 compare enable */
volatile __uchar ATD0CMPEH     @0x2c8;	/* ATD0 compare enable high */
volatile __uchar ATD0CMPEL     @0x2c9;	/* ATD0 compare enable low */
volatile __uint  ATD0STAT2     @0x2ca;	/* ATD0 status register 2 */
volatile __uchar ATD0STAT2H    @0x2ca;	/* ATD0 status register 2 high */
volatile __uchar ATD0STAT2L    @0x2cb;	/* ATD0 status register 2 low */
volatile __uint  ATD0DIEN      @0x2cc;	/* ATD0 interrupt enable */
volatile __uchar ATD0DIENH     @0x2cc;	/* ATD0 interrupt enable high */
volatile __uchar ATD0DIENL     @0x2cd;	/* ATD0 interrupt enable low */
volatile __uint  ATD0CMPHT     @0x2ce;	/* ATD0 compare higher than */
volatile __uint  ATD0DR[16]    @0x2d0;	/* ATD0 result */
volatile __uint  ATD0DR0       @0x2d0;	/* ATD0 result 0 */
volatile __uint  ATD0DR1       @0x2d2;	/* ATD0 result 1 */
volatile __uint  ATD0DR2       @0x2d4;	/* ATD0 result 2 */
volatile __uint  ATD0DR3       @0x2d6;	/* ATD0 result 3 */
volatile __uint  ATD0DR4       @0x2d8;	/* ATD0 result 4 */
volatile __uint  ATD0DR5       @0x2da;	/* ATD0 result 5 */
volatile __uint  ATD0DR6       @0x2dc;	/* ATD0 result 6 */
volatile __uint  ATD0DR7       @0x2de;	/* ATD0 result 7 */
volatile __uint  ATD0DR8       @0x2e0;	/* ATD0 result 8 */
volatile __uint  ATD0DR9       @0x2e2;	/* ATD0 result 9 */
volatile __uint  ATD0DR10      @0x2e4;	/* ATD0 result 10 */
volatile __uint  ATD0DR11      @0x2e6;	/* ATD0 result 11 */
volatile __uint  ATD0DR12      @0x2e8;	/* ATD0 result 12 */
volatile __uint  ATD0DR13      @0x2ea;	/* ATD0 result 13 */
volatile __uint  ATD0DR14      @0x2ec;	/* ATD0 result 14 */
volatile __uint  ATD0DR15      @0x2ee;	/* ATD0 result 15 */

/*	VOLTAGE Module  
 */
volatile __uchar VREGHTCL      @0x2f0;	/* High Temp control register */
volatile __uchar VREGCTRL      @0x2f1;	/* Control register */
volatile __uchar VREGAPICL     @0x2f2;	/* Autonomous Periodical Int Ctrl reg */
volatile __uchar VREGAPITR     @0x2f3;	/* Autonomous Periodical Int Trimming reg */
volatile __uint  VREGAPIR      @0x2f4;	/* Autonomous Periodical Int Rate reg */
volatile __uchar VREGAPIRH     @0x2f4;	/* Autonomous Periodical Int Rate high */
volatile __uchar VREGAPIRL     @0x2f5;	/* Autonomous Periodical Inte Rate low */
volatile __uchar VREGHTTR      @0x2f7;	/* High Temperature Trimming register */

/*	PWM Module  
 */
volatile __uchar PWME          @0x300;	/* PWM Enable */
volatile __uchar PWMPOL        @0x301;	/* PWM Clock Polarity */
volatile __uchar PWMCLK        @0x302;	/* PWM Clocks */
volatile __uchar PWMPRCLK      @0x303;	/* PWM prescale clock select */
volatile __uchar PWMCAE        @0x304;	/* PWM center align enable */
volatile __uchar PWMCTL        @0x305;	/* PWM Control Register */
volatile __uchar PWMTST        @0x306;	/* PWM Test Register */
volatile __uchar PWMPRSC       @0x307;	/* PWM Test Register */
volatile __uchar PWMSCLA       @0x308;	/* PWM scale A */
volatile __uchar PWMSCLB       @0x309;	/* PWM scale B */
volatile __uchar PWMSCNTA      @0x30a;	/* PWM Test Register A */
volatile __uchar PWMSCNTB      @0x30b;	/* PWM Test Register B */
volatile __uchar PWMCNT0       @0x30c;	/* PWM Channel Counter 0 */
volatile __uchar PWMCNT1       @0x30d;	/* PWM Channel Counter 1 */
volatile __uchar PWMCNT2       @0x30e;	/* PWM Channel Counter 2 */
volatile __uchar PWMCNT3       @0x30f;	/* PWM Channel Counter 3 */
volatile __uchar PWMCNT4       @0x310;	/* PWM Channel Counter 4 */
volatile __uchar PWMCNT5       @0x311;	/* PWM Channel Counter 5 */
volatile __uchar PWMCNT6       @0x312;	/* PWM Channel Counter 6 */
volatile __uchar PWMCNT7       @0x313;	/* PWM Channel Counter 7 */
volatile __uchar PWMPER0       @0x314;	/* PWM Channel Period 0 */
volatile __uchar PWMPER1       @0x315;	/* PWM Channel Period 1 */
volatile __uchar PWMPER2       @0x316;	/* PWM Channel Period 2 */
volatile __uchar PWMPER3       @0x317;	/* PWM Channel Period 3 */
volatile __uchar PWMPER4       @0x318;	/* PWM Channel Period 4 */
volatile __uchar PWMPER5       @0x319;	/* PWM Channel Period 5 */
volatile __uchar PWMPER6       @0x31a;	/* PWM Channel Period 6 */
volatile __uchar PWMPER7       @0x31b;	/* PWM Channel Period 7 */
volatile __uchar PWMDTY0       @0x31c;	/* PWM Channel Duty 0 */
volatile __uchar PWMDTY1       @0x31d;	/* PWM Channel Duty 1 */
volatile __uchar PWMDTY2       @0x31e;	/* PWM Channel Duty 2 */
volatile __uchar PWMDTY3       @0x31f;	/* PWM Channel Duty 3 */
volatile __uchar PWMDTY4       @0x320;	/* PWM Channel Duty 4 */
volatile __uchar PWMDTY5       @0x321;	/* PWM Channel Duty 5 */
volatile __uchar PWMDTY6       @0x322;	/* PWM Channel Duty 6 */
volatile __uchar PWMDTY7       @0x323;	/* PWM Channel Duty 7 */
volatile __uchar PWMSDN        @0x324;	/* PWM Shutdown register */

/*	PIT Module
 */
volatile __uchar PITCFLMT      @0x340;	/* PIT control micro timer register */
volatile __uchar PITFLT        @0x341;	/* PIT force load timer register */
volatile __uchar PITCE         @0x342;	/* PIT channel enable register */
volatile __uchar PITMUX        @0x343;	/* PIT multiplex register */
volatile __uchar PITINTE       @0x344;	/* PIT interrupt enable register */
volatile __uchar PITTF         @0x345;	/* PIT time-out flag register */
volatile __uchar PITMTLD0      @0x346;	/* PIT micro timer load reg. 0 */
volatile __uchar PITMTLD1      @0x347;	/* PIT micro timer load reg. 1 */
volatile __uint  PITLD0        @0x348;	/* PIT load register 0 */
volatile __uint  PITCNT0       @0x34a;	/* PIT count register 0 */
volatile __uint  PITLD1        @0x34c;	/* PIT load register 1 */
volatile __uint  PITCNT1       @0x34e;	/* PIT count register 1 */
volatile __uint  PITLD2        @0x350;	/* PIT load register 2 */
volatile __uint  PITCNT2       @0x352;	/* PIT count register 2 */
volatile __uint  PITLD3        @0x354;	/* PIT load register 3 */
volatile __uint  PITCNT3       @0x356;	/* PIT count register 3 */

#endif

