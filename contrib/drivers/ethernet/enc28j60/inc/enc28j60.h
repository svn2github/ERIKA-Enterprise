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

#ifndef __ENC28J60_H
#define __ENC28J60_H

#include "enc28j60_hal.h"
#include "enc28j60_debug.h"

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* WRAPPER */

#define RESERVED_SSL_MEMORY 	0ul		// ATT!!! this macro is server dependent... (es. STACK_USE_SSL for Microchip TCPIP stack)
#define RESERVED_HTTP_MEMORY 	0ul		// ATT!!! this macro is server dependent... (es. STACK_USE_HTTP2_SERVER for Microchip TCPIP stack)
#define RAMSIZE					(8*1024ul)
#define TXSTART 				(RAMSIZE - (1ul+1518ul+7ul) - TCP_ETH_RAM_SIZE - RESERVED_HTTP_MEMORY - RESERVED_SSL_MEMORY)
#define RXSTART					(0ul)						// Should be an even memory address; must be 0 for errata
#define	RXSTOP					((TXSTART-2ul) | 0x0001ul)	// Odd for errata workaround
#define RXSIZE					(RXSTOP-RXSTART+1ul)
#define TCP_ETH_RAM_SIZE 		0u
#define ENC_MAX_SPI_FREQ    	(20000000ul)				// SPI max Hz
#define IP_ADDR					DWORD_VAL
#define SetLEDConfig(NewConfig)	WritePHYReg(PHLCON, NewConfig)
#define MAC_IP      			(0x00u)
#define MAC_UNKNOWN 			(0xFFu)

typedef struct __attribute__((__packed__))
{
    BYTE v[6];
} mac_addr;

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */


/** D E F I N I T I O N S ****************************************************/
// IMPORTANT SPI NOTE: The code in this file expects that the SPI interrupt
//      flag (ENC_SPI_IF) be clear at all times.  If the SPI is shared with
//      other hardware, the other code should clear the ENC_SPI_IF when it is
//      done using the SPI.
// Since the ENC28J60 doesn't support auto-negotiation, full-duplex mode is
// not compatible with most switches/routers.  If a dedicated network is used
// where the duplex of the remote node can be manually configured, you may
// change this configuration.  Otherwise, half duplex should always be used.
#define HALF_DUPLEX
//#define FULL_DUPLEX
//#define LEDB_DUPLEX
#define ETHER_IP    			(0x00u)
#define ETHER_ARP   			(0x06u)

#ifdef BIG_ENDIAN
typedef union {
	BYTE v[7];
	struct
    {
        BYTE HB;
		BYTE B6;
		BYTE B5;
		BYTE B4;
		BYTE B3;
		BYTE B2;
        BYTE LB;
    } byte;
	struct {
		WORD	 		ByteCount;	
		unsigned char	Done:1;
		unsigned char	LengthOutOfRange:1;
		unsigned char	LengthCheckError:1;
		unsigned char	CRCError:1;
		unsigned char	CollisionCount:4;	
		unsigned char	Underrun:1;
		unsigned char	Giant:1;
		unsigned char	LateCollision:1;
		unsigned char	MaximumCollisions:1;
		unsigned char	ExcessiveDefer:1;
		unsigned char	PacketDefer:1;
		unsigned char	Broadcast:1;
		unsigned char	Multicast:1;
		WORD 	 		BytesTransmittedOnWire;
		unsigned char	Zeros:4;
		unsigned char	VLANTaggedFrame:1;
		unsigned char	BackpressureApplied:1;
		unsigned char	PAUSEControlFrame:1;
		unsigned char	ControlFrame:1;
	} bits;
} TXSTATUS;

typedef union {
	BYTE v[4];
	struct
    {
        BYTE HB;
		BYTE B3;
		BYTE B2;
        BYTE LB;
    } byte;
	struct {
		WORD	 		ByteCount;
		unsigned char	ReceiveOk:1;
		unsigned char	LengthOutOfRange:1;
		unsigned char	LengthCheckError:1;
		unsigned char	CRCError:1;
		unsigned char	CodeViolation:1;
		unsigned char	CarrierPreviouslySeen:1;
		unsigned char	RXDCPreviouslySeen:1;
		unsigned char	PreviouslyIgnored:1;
		unsigned char	Zero:1;
		unsigned char	VLANType:1;
		unsigned char	UnsupportedOpcode:1;
		unsigned char	PauseControlFrame:1;
		unsigned char	ControlFrame:1;
		unsigned char	DribbleNibble:1;
		unsigned char	Broadcast:1;
		unsigned char	Multicast:1;	
	} bits;
} RXSTATUS;

#else	//#ifdef BIG_ENDIAN

typedef union {
	BYTE v[7];
	struct
    {
        BYTE LB;
		BYTE B2;
		BYTE B3;
		BYTE B4;
		BYTE B5;
		BYTE B6;
        BYTE HB;
    } byte;
	struct {
		WORD	 		ByteCount;
		unsigned char	CollisionCount:4;
		unsigned char	CRCError:1;
		unsigned char	LengthCheckError:1;
		unsigned char	LengthOutOfRange:1;
		unsigned char	Done:1;
		unsigned char	Multicast:1;
		unsigned char	Broadcast:1;
		unsigned char	PacketDefer:1;
		unsigned char	ExcessiveDefer:1;
		unsigned char	MaximumCollisions:1;
		unsigned char	LateCollision:1;
		unsigned char	Giant:1;
		unsigned char	Underrun:1;
		WORD 	 		BytesTransmittedOnWire;
		unsigned char	ControlFrame:1;
		unsigned char	PAUSEControlFrame:1;
		unsigned char	BackpressureApplied:1;
		unsigned char	VLANTaggedFrame:1;
		unsigned char	Zeros:4;
	} bits;
} TXSTATUS;

typedef union {
	BYTE v[4];
	struct
    {
        BYTE LB;
		BYTE B2;
		BYTE B3;
        BYTE HB;
    } byte;
	struct {
		WORD	 		ByteCount;
		unsigned char	PreviouslyIgnored:1;
		unsigned char	RXDCPreviouslySeen:1;
		unsigned char	CarrierPreviouslySeen:1;
		unsigned char	CodeViolation:1;
		unsigned char	CRCError:1;
		unsigned char	LengthCheckError:1;
		unsigned char	LengthOutOfRange:1;
		unsigned char	ReceiveOk:1;
		unsigned char	Multicast:1;
		unsigned char	Broadcast:1;
		unsigned char	DribbleNibble:1;
		unsigned char	ControlFrame:1;
		unsigned char	PauseControlFrame:1;
		unsigned char	UnsupportedOpcode:1;
		unsigned char	VLANType:1;
		unsigned char	Zero:1;
	} bits;
} RXSTATUS;
#endif

/*
 *	Mac layer API (enc28j60 driver)		
*/
#define SetRXHashTableEntry(DestMACAddr) 				EE_enc28j60_mac_set_rx_hash_table_entry(DestMACAddr)
#define GetCLKOUT() 									EE_enc28j60_get_clkout()
#define SetCLKOUT(NewConfig) 							EE_enc28j60_set_clkout(NewConfig)
#define MACPowerUp()									EE_enc28j60_mac_power_up()
#define MACPowerDown()									EE_enc28j60_mac_power_down()
#define BankSel(Register)								EE_enc28j60_bank_select(Register)
#define WritePHYReg(Register, Data)						EE_enc28j60_write_PHY_register(Register, Data)
#define BFSReg(Address, Data)							EE_enc28j60_bit_field_set_register(Address, Data)
#define BFCReg(Address, Data)							EE_enc28j60_bit_field_clear_register(Address, Data)
#define WriteReg(Address, Data)							EE_enc28j60_write_register(Address, Data)
#define ReadPHYReg(Register)							EE_enc28j60_read_PHY_register(Register)
#define ReadMACReg(Address)								EE_enc28j60_read_MAC_MII_register(Address)
#define ReadETHReg(Address)								EE_enc28j60_read_ETH_register(Address)
#define SendSystemReset()								EE_enc28j60_software_reset()
#define MACPutArray(val, len)							EE_enc28j60_mac_put_array(val, len)
#define MACPut(val)										EE_enc28j60_mac_put(val)
#define MACGetArray(val, len)							EE_enc28j60_mac_get_array(val, len)
#define MACGet()										EE_enc28j60_mac_get()
#define MACIsMemCopyDone()								EE_enc28j60_mac_IsMemCopyDone()
#define MACMemCopyAsync(destAddr, sourceAddr, len) 		EE_enc28j60_mac_MemCopyAsync(destAddr, sourceAddr, len)
#define CalcIPBufferChecksum(len)						EE_enc28j60_mac_CalcIPBufferChecksum(len)
#define MACCalcRxChecksum(offset, len)					EE_enc28j60_mac_CalcRxChecksum(offset, len)
#define MACSetReadPtr(address)							EE_enc28j60_mac_set_read_ptr(address)
#define MACSetWritePtr(address)							EE_enc28j60_mac_set_write_ptr(address)
#define MACSetReadPtrInRx(offset)						EE_enc28j60_mac_set_read_ptr_inRx(offset)
#define MACFlush()										EE_enc28j60_mac_flush()
#define MACPutHeader(remote, type, dataLen)				EE_enc28j60_mac_put_header(remote, type, dataLen)
#define MACGetHeader(remote, type, pcnt, len)			EE_enc28j60_mac_get_header(remote, type, pcnt, len)
#define MACGetFreeRxSize()								EE_enc28j60_mac_get_FreeRxSize()
#define MACDiscardRx()									EE_enc28j60_mac_discard_rx()
#define MACIsTxReady()									EE_enc28j60_mac_IsTxReady()
#define MACIsLinked()									EE_enc28j60_mac_IsLinked()
#define MACInit()										EE_enc28j60_mac_init()

#define EE_enc28j60_mac_put_array(val, len)				EE_enc28j60_put_array(val, len)
#define EE_enc28j60_mac_put(val)						EE_enc28j60_put(val)
#define EE_enc28j60_mac_get_array(val, len)				EE_enc28j60_get_array(val, len)
#define EE_enc28j60_mac_get()							EE_enc28j60_get()

#if defined(__18CXX)
#define EE_enc28j60_mac_put_ROM_array(val, len)			EE_enc28j60_put_ROM_array(val, len)
#define MACPutROMArray(val, len)						EE_enc28j60_mac_put_ROM_array(val, len)
void EE_enc28j60_mac_put_ROM_array(ROM BYTE *val, WORD len);
#endif

void EE_enc28j60_mac_init(void);
BOOL EE_enc28j60_mac_IsLinked(void);
BOOL EE_enc28j60_mac_IsTxReady(void);
void EE_enc28j60_mac_discard_rx(void);
WORD EE_enc28j60_mac_get_FreeRxSize(void);
BOOL EE_enc28j60_mac_get_header(mac_addr *remote, BYTE* type, BYTE* PacketCount, WORD* length);
void EE_enc28j60_mac_put_header(mac_addr *remote, WORD type, WORD dataLen);
void EE_enc28j60_mac_flush(void);
void EE_enc28j60_mac_set_read_ptr_inRx(WORD offset);
WORD EE_enc28j60_mac_set_write_ptr(WORD address);
WORD EE_enc28j60_mac_set_read_ptr(WORD address);
WORD EE_enc28j60_mac_CalcRxChecksum(WORD offset, WORD len);
WORD EE_enc28j60_mac_CalcIPBufferChecksum(WORD len);
void EE_enc28j60_mac_MemCopyAsync(WORD destAddr, WORD sourceAddr, WORD len);
BOOL EE_enc28j60_mac_IsMemCopyDone(void);
BYTE EE_enc28j60_mac_get();
WORD EE_enc28j60_mac_get_array(BYTE *val, WORD len);
void EE_enc28j60_mac_put(BYTE val);
void EE_enc28j60_mac_put_array(BYTE *val, WORD len);
void EE_enc28j60_software_reset(void);
REG EE_enc28j60_read_ETH_register(BYTE Address);
REG EE_enc28j60_read_MAC_MII_register(BYTE Address);
PHYREG EE_enc28j60_read_PHY_register(BYTE Register);
void EE_enc28j60_write_register(BYTE Address, BYTE Data);
void EE_enc28j60_bit_field_clear_register(BYTE Address, BYTE Data);
void EE_enc28j60_bit_field_set_register(BYTE Address, BYTE Data);
void EE_enc28j60_write_PHY_register(BYTE Register, WORD Data);
void EE_enc28j60_bank_select(WORD Register);
void EE_enc28j60_mac_power_down(void);
void EE_enc28j60_mac_power_up(void);
void EE_enc28j60_set_clkout(BYTE NewConfig);
BYTE EE_enc28j60_get_clkout(void);
#if 0
void EE_enc28j60_mac_set_rx_hash_table_entry(mac_addr DestMACAddr);
#endif
WORD swaps(WORD v);

#if 1
#define MY_DEFAULT_MAC_BYTE1            	(0x00)	
#define MY_DEFAULT_MAC_BYTE2            	(0x1E)	
#define MY_DEFAULT_MAC_BYTE3            	(0x33)	
#define MY_DEFAULT_MAC_BYTE4            	(0xC9)	
#define MY_DEFAULT_MAC_BYTE5            	(0xD6)	
#define MY_DEFAULT_MAC_BYTE6            	(0xAA)
#else
#define MY_DEFAULT_MAC_BYTE1            	(0x00)	// Use the default of
#define MY_DEFAULT_MAC_BYTE2            	(0x04)	// 00-04-A3-00-00-00 if using
#define MY_DEFAULT_MAC_BYTE3            	(0xA3)	// an ENCX24J600 or ZeroG ZG2100
#define MY_DEFAULT_MAC_BYTE4            	(0x00)	// and wish to use the internal
#define MY_DEFAULT_MAC_BYTE5            	(0x00)	// factory programmed MAC
#define MY_DEFAULT_MAC_BYTE6            	(0x00)	// address instead.
#endif

extern mac_addr ee_myMACaddress;

/* 	EE_enc28j60_debug_init
	Function used to configure the console used for debugging.
*/
int8_t EE_enc28j60_debug_init(void);

/* 	EE_enc28j60_init 
	Function used to initialize the device
*/
__INLINE__ WORD __ALWAYS_INLINE__ EE_enc28j60_init(void)
{
	int ret = 0;
	
	#ifdef ENC28J60_DEBUG
	EE_enc28j60_debug_init();
	#endif
	
	//int mode = 0;
	//EE_enc28j60_config(mode);
    EE_enc28j60_spi_init();	// SPI module configuration
	// Release reset
	EE_enc28j60_gpio_release_reset();
	// Disable IRQ
	mico32_disable_irq(EE_ENC28J60_IRQ);
	EE_enc28j60_gpio_disable_IRQ();
	// MAC layer initialization
	EE_enc28j60_mac_init();
	return ret;
}

/* 	EE_enc28j60_transfer_init
	Function used to initialize the transfer of a packet
*/
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_transfer_init(void)
{
	// Set the SPI write pointer to the beginning of the transmit buffer (post per packet control byte)
    WriteReg(EWRPTL, LOW(TXSTART+1));
    WriteReg(EWRPTH, HIGH(TXSTART+1));
}

/* 	EE_enc28j60_write
	Function used to transmit a packet
*/
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_write(BYTE* data, WORD len)
{
	MACPutArray(data, len);
}

/* 	EE_enc28j60_signal
	Function used to signal the end of a packet transfer
*/
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_signal(WORD dataLen)
{
	dataLen += TXSTART; 
    // Write the TXND pointer into the registers, given the dataLen given
	WriteReg(ETXNDL, ((WORD_VAL*)&dataLen)->byte.LB);
    WriteReg(ETXNDH, ((WORD_VAL*)&dataLen)->byte.HB);
	MACFlush();
}

/* 	EE_enc28j60_read_length
	Function used to read the length of the receive packet
*/
int EE_enc28j60_read_info(BYTE* PacketCount, WORD* length);


/* 	EE_enc28j60_read
	Function used to receive a packet
*/
__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_read(BYTE* data, WORD len)
{
	return MACGetArray(data, len);
}

/* 	EE_enc28j60_ack
	Function used to acknowledge a packet reception
*/
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_ack(void)
{
	MACDiscardRx();
}

/* 	EE_enc28j60_drop_packet
	Function used to drop a packet
*/
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_drop_packet(void)
{
	//MACDiscardRx();
}

#endif
