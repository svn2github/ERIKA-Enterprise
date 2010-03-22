#ifndef __ENC28J60_REG_H
#define __ENC28J60_REG_H

/*********************************************************************
 *
 *            ENC28J60 registers/bits
 *
 *********************************************************************
 * FileName:        ENC28J60.h
 * Dependencies:    None
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 * Compiler:        Microchip C32 v1.05 or higher
 *					Microchip C30 v3.12 or higher
 *					Microchip C18 v3.30 or higher
 *					HI-TECH PICC-18 PRO 9.63PL2 or higher
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * Copyright (C) 2002-2009 Microchip Technology Inc.  All rights
 * reserved.
 *
 * Microchip licenses to you the right to use, modify, copy, and
 * distribute:
 * (i)  the Software when embedded on a Microchip microcontroller or
 *      digital signal controller product ("Device") which is
 *      integrated into Licensee's product; or
 * (ii) ONLY the Software driver source files ENC28J60.c, ENC28J60.h,
 *		ENCX24J600.c and ENCX24J600.h ported to a non-Microchip device
 *		used in conjunction with a Microchip ethernet controller for
 *		the sole purpose of interfacing with the ethernet controller.
 *
 * You should refer to the license agreement accompanying this
 * Software for additional information regarding your rights and
 * obligations.
 *
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Howard Schlunder		06/01/04	Original
 * Howard Schlunder		06/29/04	Fixed byte boundary problems on a 
 *									couple of PHY register structs.
 * Howard Schlunder		09/29/04	Matched with data sheet
 * Howard Schlunder		01/04/06	Matched with new data sheet
 * Howard Schlunder		06/29/06	Changed MACON3.PHDRLEN to PHDREN
 * Howard Schlunder		07/21/06	Several bits removed to match now 
 *									reserved bits in rev. B data sheet 
 *									(DS39662B)
 ********************************************************************/

// ENC28J60 Opcodes (to be ORed with a 5 bit address)
#define ENC28J60_WCR (0x2<<5)				// Write Control Register command
#define ENC28J60_BFS (0x4<<5)				// Bit Field Set command
#define ENC28J60_BFC (0x5<<5)				// Bit Field Clear command
#define ENC28J60_RCR (0x0<<5)				// Read Control Register command
#define ENC28J60_RBM ((0x1<<5) | 0x1A)		// Read Buffer Memory command
#define ENC28J60_WBM ((0x3<<5) | 0x1A)		// Write Buffer Memory command
#define ENC28J60_SR  ((0x7<<5) | 0x1F)		// System Reset command does not use an address.
                                			// It requires 0x1F, however.

/******************************************************************************
* Register locations
******************************************************************************/
// Bank 0 registers --------
#define ENC28J60_ERDPTL		0x00
#define ENC28J60_ERDPTH		0x01
#define ENC28J60_EWRPTL		0x02
#define ENC28J60_EWRPTH		0x03
#define ENC28J60_ETXSTL		0x04
#define ENC28J60_ETXSTH		0x05
#define ENC28J60_ETXNDL		0x06
#define ENC28J60_ETXNDH		0x07
#define ENC28J60_ERXSTL		0x08
#define ENC28J60_ERXSTH		0x09
#define ENC28J60_ERXNDL		0x0A
#define ENC28J60_ERXNDH		0x0B
#define ENC28J60_ERXRDPTL	0x0C
#define ENC28J60_ERXRDPTH	0x0D
#define ENC28J60_ERXWRPTL	0x0E
#define ENC28J60_ERXWRPTH	0x0F
#define ENC28J60_EDMASTL	0x10
#define ENC28J60_EDMASTH	0x11
#define ENC28J60_EDMANDL	0x12
#define ENC28J60_EDMANDH	0x13
#define ENC28J60_EDMADSTL	0x14
#define ENC28J60_EDMADSTH	0x15
#define ENC28J60_EDMACSL	0x16
#define ENC28J60_EDMACSH	0x17
//#define					0x18
//#define					0x19
//#define r					0x1A
#define ENC28J60_EIE		0x1B
#define ENC28J60_EIR		0x1C
#define ENC28J60_ESTAT		0x1D
#define ENC28J60_ECON2		0x1E
#define ENC28J60_ECON1		0x1F

// Bank 1 registers -----
#define ENC28J60_EHT0		0x100
#define ENC28J60_EHT1		0x101
#define ENC28J60_EHT2		0x102
#define ENC28J60_EHT3		0x103
#define ENC28J60_EHT4		0x104
#define ENC28J60_EHT5		0x105
#define ENC28J60_EHT6		0x106
#define ENC28J60_EHT7		0x107
#define ENC28J60_EPMM0		0x108
#define ENC28J60_EPMM1		0x109
#define ENC28J60_EPMM2		0x10A
#define ENC28J60_EPMM3		0x10B
#define ENC28J60_EPMM4		0x10C
#define ENC28J60_EPMM5		0x10D
#define ENC28J60_EPMM6		0x10E
#define ENC28J60_EPMM7		0x10F
#define ENC28J60_EPMCSL		0x110
#define ENC28J60_EPMCSH		0x111
//#define					0x112
//#define					0x113
#define ENC28J60_EPMOL		0x114
#define ENC28J60_EPMOH		0x115
//#define ENC28J60_r		0x116
//#define ENC28J60_r		0x117
#define ENC28J60_ERXFCON	0x118
#define ENC28J60_EPKTCNT	0x119
//#define ENC28J60_r		0x11A
//#define ENC28J60_EIE		0x11B
//#define ENC28J60_EIR		0x11C
//#define ENC28J60_ESTAT	0x11D
//#define ENC28J60_ECON2	0x11E
//#define ENC28J60_ECON1	0x11F

// Bank 2 registers -----
#define ENC28J60_MACON1		0x200
//#define ENC28J60_r		0x201
#define ENC28J60_MACON3		0x202
#define ENC28J60_MACON4		0x203
#define ENC28J60_MABBIPG	0x204
//#define					0x205
#define ENC28J60_MAIPGL		0x206
#define ENC28J60_MAIPGH		0x207
#define ENC28J60_MACLCON1	0x208
#define ENC28J60_MACLCON2	0x209
#define ENC28J60_MAMXFLL	0x20A
#define ENC28J60_MAMXFLH	0x20B
//#define ENC28J60_r		0x20C
//#define ENC28J60_r		0x20D
//#define ENC28J60_r		0x20E
//#define					0x20F
//#define ENC28J60_r		0x210
//#define ENC28J60_r		0x211
#define ENC28J60_MICMD		0x212
//#define ENC28J60_r		0x213
#define ENC28J60_MIREGADR	0x214
//#define ENC28J60_r		0x215
#define ENC28J60_MIWRL		0x216
#define ENC28J60_MIWRH		0x217
#define ENC28J60_MIRDL		0x218
#define ENC28J60_MIRDH		0x219
//#define ENC28J60_r		0x21A
//#define ENC28J60_EIE		0x21B
//#define ENC28J60_EIR		0x21C
//#define ENC28J60_ESTAT	0x21D
//#define ENC28J60_ECON2	0x21E
//#define ENC28J60_ECON1	0x21F

// Bank 3 registers -----
#define ENC28J60_MAADR5		0x300
#define ENC28J60_MAADR6		0x301
#define ENC28J60_MAADR3		0x302
#define ENC28J60_MAADR4		0x303
#define ENC28J60_MAADR1		0x304
#define ENC28J60_MAADR2		0x305
#define ENC28J60_EBSTSD		0x306
#define ENC28J60_EBSTCON	0x307
#define ENC28J60_EBSTCSL	0x308
#define ENC28J60_EBSTCSH	0x309
#define ENC28J60_MISTAT		0x30A
//#define					0x30B
//#define					0x30C
//#define					0x30D
//#define					0x30E
//#define					0x30F
//#define					0x310
//#define					0x311
#define ENC28J60_EREVID		0x312
//#define					0x313
//#define					0x314
#define ENC28J60_ECOCON		0x315
//#define					0x316
#define ENC28J60_EFLOCON	0x317
#define ENC28J60_EPAUSL		0x318
#define ENC28J60_EPAUSH		0x319
//#define ENC28J60_r		0x31A
//#define ENC28J60_EIE		0x31B
//#define ENC28J60_EIR		0x31C
//#define ENC28J60_ESTAT	0x31D
//#define ENC28J60_ECON2	0x31E
//#define ENC28J60_ECON1	0x31F

/******************************************************************************
* PH Register Locations
******************************************************************************/
#define ENC28J60_PHCON1		0x00
#define ENC28J60_PHSTAT1	0x01
#define ENC28J60_PHID1		0x02
#define ENC28J60_PHID2		0x03
#define ENC28J60_PHCON2		0x10
#define ENC28J60_PHSTAT2	0x11
#define ENC28J60_PHIE		0x12
#define ENC28J60_PHIR		0x13
#define ENC28J60_PHLCON		0x14

/******************************************************************************
* Individual Register Bits
******************************************************************************/
// ETH/MAC/MII bits

// EIE bits ----------
#define	ENC28J60_EIE_INTIE		(1<<7)
#define	ENC28J60_EIE_PKTIE		(1<<6)
#define	ENC28J60_EIE_DMAIE		(1<<5)
#define	ENC28J60_EIE_LINKIE		(1<<4)
#define	ENC28J60_EIE_TXIE		(1<<3)
#define	ENC28J60_EIE_TXERIE		(1<<1)
#define	ENC28J60_EIE_RXERIE		(1)

// EIR bits ----------
#define	ENC28J60_EIR_PKTIF		(1<<6)
#define	ENC28J60_EIR_DMAIF		(1<<5)
#define	ENC28J60_EIR_LINKIF		(1<<4)
#define	ENC28J60_EIR_TXIF		(1<<3)
#define	ENC28J60_EIR_TXERIF		(1<<1)
#define	ENC28J60_EIR_RXERIF		(1)
	
// ESTAT bits ---------
#define	ENC28J60_ESTAT_INT				(1<<7)
#define ENC28J60_ENC28J60_ESTAT_BUFER	(1<<6)
#define	ENC28J60_ESTAT_LATECOL			(1<<4)
#define	ENC28J60_ESTAT_RXBUSY			(1<<2)
#define	ENC28J60_ESTAT_TXABRT			(1<<1)
#define	ENC28J60_ESTAT_CLKRDY			(1)
	
// ECON2 bits --------
#define	ENC28J60_ECON2_AUTOINC	(1<<7)
#define	ENC28J60_ECON2_PKTDEC	(1<<6)
#define	ENC28J60_ECON2_PWRSV	(1<<5)
#define	ENC28J60_ECON2_VRPS		(1<<3)
	
// ECON1 bits --------
#define	ENC28J60_ECON1_TXRST	(1<<7)
#define	ENC28J60_ECON1_RXRST	(1<<6)
#define	ENC28J60_ECON1_DMAST	(1<<5)
#define	ENC28J60_ECON1_CSUMEN	(1<<4)
#define	ENC28J60_ECON1_TXRTS	(1<<3)
#define	ENC28J60_ECON1_RXEN		(1<<2)
#define	ENC28J60_ECON1_BSEL1	(1<<1)
#define	ENC28J60_ECON1_BSEL0	(1)
	
// ERXFCON bits ------
#define	ENC28J60_ERXFCON_UCEN	(1<<7)
#define	ENC28J60_ERXFCON_ANDOR	(1<<6)
#define	ENC28J60_ERXFCON_CRCEN	(1<<5)
#define	ENC28J60_ERXFCON_PMEN	(1<<4)
#define	ENC28J60_ERXFCON_MPEN	(1<<3)
#define	ENC28J60_ERXFCON_HTEN	(1<<2)
#define	ENC28J60_ERXFCON_MCEN	(1<<1)
#define	ENC28J60_ERXFCON_BCEN	(1)
	
// MACON1 bits --------
#define	ENC28J60_MACON1_TXPAUS	(1<<3)
#define	ENC28J60_MACON1_RXPAUS	(1<<2)
#define	ENC28J60_MACON1_PASSALL	(1<<1)
#define	ENC28J60_MACON1_MARXEN	(1)
	
// MACON3 bits --------
#define	ENC28J60_MACON3_PADCFG2	(1<<7)
#define	ENC28J60_MACON3_PADCFG1	(1<<6)
#define	ENC28J60_MACON3_PADCFG0	(1<<5)
#define	ENC28J60_MACON3_TXCRCEN	(1<<4)
#define	ENC28J60_MACON3_PHDREN	(1<<3)
#define	ENC28J60_MACON3_HFRMEN	(1<<2)
#define	ENC28J60_MACON3_FRMLNEN	(1<<1)
#define	ENC28J60_MACON3_FULDPX	(1)
	
// MACON4 bits --------
#define	ENC28J60_MACON4_DEFER	(1<<6)
#define	ENC28J60_MACON4_BPEN	(1<<5)
#define	ENC28J60_MACON4_NOBKOFF	(1<<4)
	
// MICMD bits ---------
#define	ENC28J60_MICMD_MIISCAN	(1<<1)
#define	ENC28J60_MICMD_MIIRD	(1)

// EBSTCON bits -----
#define	ENC28J60_EBSTCON_PSV2	(1<<7)
#define	ENC28J60_EBSTCON_PSV1	(1<<6)
#define	ENC28J60_EBSTCON_PSV0	(1<<5)
#define	ENC28J60_EBSTCON_PSEL	(1<<4)
#define	ENC28J60_EBSTCON_TMSEL1	(1<<3)
#define	ENC28J60_EBSTCON_TMSEL0	(1<<2)
#define	ENC28J60_EBSTCON_TME	(1<<1)
#define	ENC28J60_EBSTCON_BISTST	(1)

// MISTAT bits --------
#define	ENC28J60_MISTAT_NVALID	(1<<2)
#define	ENC28J60_MISTAT_SCAN	(1<<1)
#define	ENC28J60_MISTAT_BUSY	(1)
	
// ECOCON bits -------
#define	ECOCON_COCON2	(1<<2)
#define	ECOCON_COCON1	(1<<1)
#define	ECOCON_COCON0	(1)
	
// EFLOCON bits -----
#define	ENC28J60_EFLOCON_FULDPXS	(1<<2)
#define	ENC28J60_EFLOCON_FCEN1		(1<<1)
#define	ENC28J60_EFLOCON_FCEN0		(1)

// PHY bits
// PHCON1 bits ----------
#define	ENC28J60_PHCON1_PRST	(1ul<<15)
#define	ENC28J60_PHCON1_PLOOPBK	(1ul<<14)
#define	ENC28J60_PHCON1_PPWRSV	(1ul<<11)
#define	ENC28J60_PHCON1_PDPXMD	(1ul<<8)

// PHSTAT1 bits --------
#define	ENC28J60_PHSTAT1_PFDPX	(1ul<<12)
#define	ENC28J60_PHSTAT1_PHDPX	(1ul<<11)
#define	ENC28J60_PHSTAT1_LLSTAT	(1ul<<2)
#define	ENC28J60_PHSTAT1_JBSTAT	(1ul<<1)

// PHID2 bits --------
#define ENC28J60_PHID2_PID24	(1ul<<15)
#define ENC28J60_PHID2_PID23	(1ul<<14)
#define ENC28J60_PHID2_PID22	(1ul<<13)
#define ENC28J60_PHID2_PID21	(1ul<<12)
#define ENC28J60_PHID2_PID20	(1ul<<11)
#define ENC28J60_PHID2_PID19	(1ul<<10)
#define ENC28J60_PHID2_PPN5		(1ul<<9)
#define ENC28J60_PHID2_PPN4		(1ul<<8)
#define ENC28J60_PHID2_PPN3		(1ul<<7)
#define ENC28J60_PHID2_PPN2		(1ul<<6)
#define ENC28J60_PHID2_PPN1		(1ul<<5)
#define ENC28J60_PHID2_PPN0		(1ul<<4)
#define ENC28J60_PHID2_PREV3	(1ul<<3)
#define ENC28J60_PHID2_PREV2	(1ul<<2)
#define ENC28J60_PHID2_PREV1	(1ul<<1)
#define ENC28J60_PHID2_PREV0	(1ul)

// PHCON2 bits ----------
#define ENC28J60_PHCON2_FRCLNK	(1ul<<14)
#define ENC28J60_PHCON2_TXDIS	(1ul<<13)
#define ENC28J60_PHCON2_JABBER	(1ul<<10)
#define ENC28J60_PHCON2_HDLDIS	(1ul<<8)

// PHSTAT2 bits --------
#define ENC28J60_PHSTAT2_TXSTAT		(1ul<<13)
#define ENC28J60_PHSTAT2_RXSTAT		(1ul<<12)
#define ENC28J60_PHSTAT2_COLSTAT	(1ul<<11)
#define ENC28J60_PHSTAT2_LSTAT		(1ul<<10)
#define ENC28J60_PHSTAT2_DPXSTAT	(1ul<<9)
#define ENC28J60_PHSTAT2_PLRITY		(1ul<<5)

// PHIE bits -----------
#define ENC28J60_PHIE_PLNKIE	(1ul<<4)
#define ENC28J60_PHIE_PGEIE		(1ul<<1)

// PHIR bits -----------
#define ENC28J60_PHIR_PLNKIF	(1ul<<4)
#define ENC28J60_PHIR_PGIF		(1ul<<2)

// PHLCON bits -------
#define ENC28J60_PHLCON_LACFG3	(1ul<<11)
#define ENC28J60_PHLCON_LACFG2	(1ul<<10)
#define ENC28J60_PHLCON_LACFG1	(1ul<<9)
#define ENC28J60_PHLCON_LACFG0	(1ul<<8)
#define ENC28J60_PHLCON_LBCFG3	(1ul<<7)
#define ENC28J60_PHLCON_LBCFG2	(1ul<<6)
#define ENC28J60_PHLCON_LBCFG1	(1ul<<5)
#define ENC28J60_PHLCON_LBCFG0	(1ul<<4)
#define ENC28J60_PHLCON_LFRQ1	(1ul<<3)
#define ENC28J60_PHLCON_LFRQ0	(1ul<<2)
#define ENC28J60_PHLCON_STRCH	(1ul<<1)

#endif


