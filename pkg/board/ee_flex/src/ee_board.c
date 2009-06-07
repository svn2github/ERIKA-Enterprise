/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation,
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/*
 * Author: 20065 Mauro Marinoni
 * CVS: $Id: ee_board.c,v 1.11 2008/08/29 11:21:08 francesco Exp $
 */

#include "ee_internal.h"

/* /\************************************************************************* */
/* Check if the Flex DemoBoard has been selected */
/* /\************************************************************************* */

#ifdef __USE_DEMOBOARD__

#include "cpu/pic30/inc/ee_irqstub.h"

//Start GF
/* /\************************************************************************* */
/*  Buttons and PICDEM Z */
/*  *************************************************************************\/ */

#ifdef __USE_BUTTONS__
void (*EE_button_callback)(void);
EE_UINT8 EE_button_mask;

union cn_st cn_st_old;
#endif

#if defined (__USE_PICDEMZ_WITH_INT4__) || (__USE_PICDEMZ_WITH_CN20INT__)
void (*EE_picdemz_callback)(void);
#endif

#if defined (__USE_BUTTONS__) || (__USE_PICDEMZ_WITH_CN20INT__)
ISR2(_CNInterrupt)
{
	#ifdef __USE_BUTTONS__
	/* Execute callback function if there is a change notification related
	 * to a button.
	 */
	if (EE_button_callback != NULL
			|| PORTDbits.RD4 != cn_st_old.bits.s1
			|| PORTDbits.RD5 != cn_st_old.bits.s2
			|| PORTDbits.RD6 != cn_st_old.bits.s3
			|| PORTDbits.RD15 != cn_st_old.bits.s4) {

		cn_st_old.bits.s1 = PORTDbits.RD4;
		cn_st_old.bits.s2 = PORTDbits.RD5;
		cn_st_old.bits.s3 = PORTDbits.RD6;
		cn_st_old.bits.s4 = PORTDbits.RD15;

		EE_button_callback();
	}
	#endif

	#ifdef __USE_PICDEMZ_WITH_CN20INT__
	/*
	 * call interrupt handler only with RF_INT_PIN low
	 */
	//if ( !RF_INT_PIN && RFIE && RFIF && RFIEC20)
	if (!PORTDbits.RD14 && IEC1bits.CNIE && IFS1bits.CNIF && CNEN2bits.CN20IE)
	// Execute callback function
		if (EE_picdemz_callback != NULL) {
			EE_picdemz_callback();
		}
	#endif

	/* reset CN interrupt flag */
	IFS1bits.CNIF = 0;
}

#endif

#ifdef __USE_PICDEMZ_WITH_INT4__

ISR2(_INT4Interrupt)
{
	if(IEC3bits.INT4IE && IFS3bits.INT4IF) { //if(RFIE && RFIF)
		// Execute callback function
		if (EE_picdemz_callback != NULL)
			EE_picdemz_callback();
	}
	IFS3bits.INT4IF = 0; // clear interrupt flag

}
#endif
//End GF


/* /\************************************************************************* */
/*  Analog input */
/*  *************************************************************************\/ */

#if defined(__USE_SENSORS__) || defined(__USE_TRIMMER__) || defined(__USE_ACCELEROMETER__) || defined(__USE_ADC_IN__)
EE_UINT8 EE_adc_init = 0;
#endif

#ifdef __USE_ACCELEROMETER__
EE_UINT8 EE_accelerometer_g = 6;
#endif


/* /\************************************************************************* */
/*  LCD */
/*  *************************************************************************\/ */

#ifdef __USE_LCD__
EE_UINT16 lcd_temp_count __attribute__((near)) = 0;

void Delay( unsigned int delay_count )
{
	lcd_temp_count = delay_count +1;
	asm volatile("outer: dec _lcd_temp_count");
	asm volatile("cp0 _lcd_temp_count");
	asm volatile("bra z, done");
	asm volatile("do #3200, inner" );
	asm volatile("nop");
	asm volatile("inner: nop");
	asm volatile("bra outer");
	asm volatile("done:");
}

void Delay_Us( unsigned int delayUs_count )
{
	lcd_temp_count = delayUs_count +1;
	asm volatile("outer1: dec _lcd_temp_count");
	asm volatile("cp0 _lcd_temp_count");
	asm volatile("bra z, done1");
	asm volatile("do #1500, inner1" );
	asm volatile("nop");
	asm volatile("inner1: nop");
	asm volatile("bra outer1");
	asm volatile("done1:");
}

#endif

/* /\************************************************************************* */
/*  Buzzer */
/*  *************************************************************************\/ */

#ifdef __USE_BUZZER__

EE_UINT16 buzzer_freq;
EE_UINT16 buzzer_ticks;
EE_UINT16 count;

#endif

#if defined (__USE_USB_OLD__) || defined (__USE_SPI__)

#define USB_BUF_SIZE 256
unsigned int Spi1TxBuffA[USB_BUF_SIZE+1] __attribute__((space(dma)));

unsigned int Spi1RxBuffA[64] __attribute__((space(dma)));
//unsigned int Spi1RxBuffB[64] __attribute__((space(dma));
//unsigned int Spi1TxBuffB[256] __attribute__((space(dma)));
unsigned int RxDmaBuffer = 0;
unsigned int TxDmaBuffer = 0;
#endif

#if defined __USE_USB__

#include <string.h>

#define USB_PIC18_REQ 		LATAbits.LATA14
#define USB_PIC18_REQ_TRIS 	TRISAbits.TRISA14
#define FLEX_USB_HEADER_START 0x15	/**< The start header: 10101 */
#define FLEX_USB_PACKET_PAYLOAD_SIZE 60	/**< The packet payload size */
#ifndef FLEX_USB_RX_BUFFER_SIZE
#define FLEX_USB_RX_BUFFER_SIZE	240
#endif

struct flex_usb_packet_t {
	/*CHRIS: TODO: METTERE LA CRC IN FONDO!!!!! */
    unsigned crc : 8;               /**< The checksum, including header */
	unsigned start : 5;	/**< Commone header 10101 */
	unsigned type : 3;	/**< Packet type */
	unsigned more : 1; 	/**< Is last fragment */
	unsigned seq : 4; 	/**< Fragment sequence number */
	unsigned reserved1 : 3;	/**< Reserverd (seq, length) */
	unsigned reserved2 : 2;	/**< Reserverd (seq, length) */
	unsigned length : 6;	/**< Payload lenght */
	EE_UINT8 payload[FLEX_USB_PACKET_PAYLOAD_SIZE]; /**< Packet payload */
	//EE_UINT8 crc;		/**< The checksum, including header */
};

enum flex_usb_header_type_t {
	FLEX_USB_HEADER_NULL = 0x00,
	FLEX_USB_HEADER_COMMAND = 0x01,
	FLEX_USB_HEADER_DATA = 0x02,
	FLEX_USB_HEADER_ACK = 0x03,
};

enum flex_usb_command_type_t {
	FLEX_USB_COMMAND_CONNECT = 0x0001,
	FLEX_USB_COMMAND_DISCONNECT = 0x0002,
};

static struct flex_usb_packet_t dma_tx_pkt __attribute__((space(dma)));
static struct flex_usb_packet_t dma_rx_pkt __attribute__((space(dma)));
static EE_UINT8 rx_buffer[FLEX_USB_RX_BUFFER_SIZE] __attribute__((far));
static EE_UINT16 rx_first = 0;
static EE_UINT16 rx_last = 0;
static EE_UINT16 rx_held = 0;
static volatile char dummy_send_lock = 0;
static char usb_initialized = 0;

void EE_usb_init(void)
{
	if(usb_initialized)
		return;
	/* dsPIC SPI communication busy */
	USB_PIC18_REQ_TRIS = 0;	/* Output: USB request by dsPIC (SPI Slave) */
	USB_PIC18_REQ = 0; 	/* No request at the beginning */
	/* Following code shows SPI register configuration for SLAVE Mode */
  	SPI1BUF = 0x00;
  	SPI1CON1bits.DISSCK = 0;/* Internal Serial Clock is Enabled. */
  	SPI1CON1bits.DISSDO = 0;/* SDOx pin is controlled by the module. */
  	SPI1CON1bits.MODE16 = 0;/* Communication is byte-wide (8 bits).*/
  	SPI1CON1bits.SMP = 0; 	/* Input Data is sampled at the middle of data
				   output time. */
	SPI1CON1bits.CKE = 0; 	/* Serial output data changes on transition from
				   Idle clock state to active clock state. */
  	SPI1CON1bits.CKP = 0; 	/* Idle state for clock is a low level; active
				   state is a high level. */
  	SPI1CON1bits.MSTEN = 0; /* Master Mode disabled. */
  	SPI1CON1bits.SSEN = 0; 	/* Slave Select pin NOT used by SPI. */
  	SPI1STATbits.SPIROV = 0;/* No Receive Overflow Has Occurred. */
  	SPI1STATbits.SPIEN = 1; /* Enable SPI Module. */
  	IFS0bits.SPI1IF = 0;
  	IEC0bits.SPI1IE = 0;
  	/* DMA0 configuration for SPI Tx */
  	DMA0CON = 0;		/* Restore Default */
	DMA0CONbits.SIZE = 1; 	/* Byte oriented */
	DMA0CONbits.DIR = 1; 	/* From DMA memory to peripheral */
	DMA0CONbits.MODE = 1; 	/* One shot, ping-pong disabled */
  	DMA0REQ = 0x00A;
  	DMA0PAD = (volatile EE_UINT16) &(SPI1BUF);
  	DMA0STA = __builtin_dmaoffset(&dma_tx_pkt);
  	DMA0CONbits.CHEN = 0;	/* Disable Tx DMA Channel. */
  	IFS0bits.DMA0IF = 0;
  	IEC0bits.DMA0IE = 0;
  	/* DMA1 configuration for SPI Rx; lower priority than DMA0 */
  	DMA1CON = 0;		/* Restore Default */
	DMA1CONbits.SIZE = 1; 	/* Byte oriented */
	//DMA1CONbits.MODE = 1; 	/* One shot, ping-pong disabled */
  	DMA1REQ = 0x00A;
  	DMA1PAD = (volatile EE_UINT16) &SPI1BUF;
  	DMA1STA = __builtin_dmaoffset(&dma_rx_pkt);
	DMA1CNT = 63;	/* NOTE 63 = sizeof(dma_tx_pkt) - 1 */
  	IFS0bits.DMA1IF = 0;
  	IEC0bits.DMA1IE = 1;
  	DMA1CONbits.CHEN = 1;	/* Enable Rx DMA Channel. */
	/* Init variables */
	memset(rx_buffer, 0, FLEX_USB_RX_BUFFER_SIZE);
	rx_first = 0;
	rx_last = 0;
	rx_held = 0;
	dummy_send_lock = 0;
	usb_initialized = 1;
}

EE_INT16 EE_usb_write(EE_UINT8 *buf, EE_UINT16 len)
{
	EE_UINT16 i;
	EE_UINT8 sum;

	/* chris: current policy is: have no packet buffer, no fragmentation,
		  no ack and wait until the previous packet transmission ends.
	*/
	if (len == 0 || len > FLEX_USB_PACKET_PAYLOAD_SIZE)
		return -1;
	//while (USB_PIC18_REQ) ; /* Wait previous transfer to be completed. */
	if(USB_PIC18_REQ) 
		return -1; 
	memset((EE_UINT8 *) &dma_tx_pkt, 0x0, 64);
	dma_tx_pkt.start = FLEX_USB_HEADER_START;
	dma_tx_pkt.type = FLEX_USB_HEADER_DATA;
	dma_tx_pkt.more = 0;
	dma_tx_pkt.seq = 0;
	dma_tx_pkt.length = len;
	memcpy(dma_tx_pkt.payload, buf, len);
	/* NOTE 63 = sizeof(dma_tx_pkt) - sizeof(CRC) */
	//for (sum = 0, i = 0; i < 63; i++)
	for (sum = 0, i = 1; i < 64; i++) // COMPLIANT TO "HEADER" CRC
		sum += ((EE_UINT8 *) &dma_tx_pkt)[i];
	dma_tx_pkt.crc = sum;
	DMA0STA = __builtin_dmaoffset(&dma_tx_pkt);
	DMA0CNT = 63;	/* NOTE 63 = sizeof(dma_tx_pkt) - 1 */
	IFS0bits.DMA0IF  = 0;
	IEC0bits.DMA0IE  = 1;
	DMA0CONbits.CHEN = 1;
	DMA0REQbits.FORCE = 1;
	USB_PIC18_REQ = 1;	/* Request transmission */
	/* chris: TODO: non usare il bloccaggio attivo qui!!! */
	//dummy_send_lock = 1;
	//while (dummy_send_lock) ;
	return len;
}

EE_INT16 EE_usb_read(EE_UINT8 *buf, EE_UINT16 len)
{
	EE_UINT16 idx;

	if (len == 0 || len > FLEX_USB_RX_BUFFER_SIZE)
		return -1;
  	IEC0bits.DMA1IE = 0;	/* mutex: disable DMA SPI RX Interrupt */
	if (rx_held == 0) {
  		IEC0bits.DMA1IE = 1;	/* mutex: enable DMA SPI RX Interrupt */
		return 0;
	}
	if (len > rx_held)
		len = rx_held;
	idx = (rx_first + len) % FLEX_USB_RX_BUFFER_SIZE;
	/* NOTE: idx = new_first position for rx */
	if (idx > rx_first) {
		/* Message is located from rx_first to the end of the buffer. */
		memcpy(buf, rx_buffer + rx_first, len);
	} else {
		/* The first part of message is stored from rx_first to the end
		    of the buffer, the remaining part goes from the of the
		    begin buffer to idx index.  */
		memcpy(buf, rx_buffer + rx_first,
		       FLEX_USB_RX_BUFFER_SIZE - rx_first);
		memcpy(buf + (FLEX_USB_RX_BUFFER_SIZE - rx_first),
		       rx_buffer, idx + 1);
	}
	rx_held -= len;
	rx_first = idx;
  	IEC0bits.DMA1IE = 1;	/* mutex: enable DMA SPI RX Interrupt */
	/* chris: note: if len > 2^16 a wrong negative value is returned */
	return (EE_INT16) len;
}

/**
* @brief DMA ISR for SPI transmission
*/
void __attribute__((interrupt, no_auto_psv)) _DMA0Interrupt(void)
{
	IFS0bits.DMA0IF  = 0;
	IEC0bits.DMA0IE  = 0;
	DMA0CONbits.CHEN = 0;
	/* TODO: do something eventually here to start another transfer */
	/* chris: TODO: versione di test.... sblocca il dummy lock! */
	USB_PIC18_REQ = 0;
	dummy_send_lock = 0;
}

/**
* @brief DMA ISR for SPI reception
*/
void __attribute__((interrupt, no_auto_psv)) _DMA1Interrupt(void)
{
	EE_UINT16 idx;
	IFS0bits.DMA1IF = 0;
	/* TODO: controllare header start, controllare CRC */
	if (dma_rx_pkt.type == FLEX_USB_HEADER_DATA) {
		/* If the read message is larger than the whole buffer,
		   write the last FLEX_USB_RX_BUFFER_SIZE bytes in the buffer.
		   TODO: is this a possible scenario?? */
		idx = dma_rx_pkt.length; /* NOTE: idx as temp vari to silent compiler */
		if (idx >= FLEX_USB_RX_BUFFER_SIZE) {
			idx = dma_rx_pkt.length - FLEX_USB_RX_BUFFER_SIZE;
			memcpy(rx_buffer, dma_rx_pkt.payload + idx,
			       FLEX_USB_RX_BUFFER_SIZE);
			rx_last = 0;
			rx_first = 0;
			rx_held = FLEX_USB_RX_BUFFER_SIZE;
			return;
		}
		if (FLEX_USB_RX_BUFFER_SIZE - rx_held < dma_rx_pkt.length) {
			/* Overriding condition: implement shift policy
			   on the rx_first indec,  idx=amount of
			   overriding bytes. */
			idx = dma_rx_pkt.length -
			      (FLEX_USB_RX_BUFFER_SIZE - rx_held);
			rx_first = (rx_first + idx) % FLEX_USB_RX_BUFFER_SIZE;
		}
		/* NOTE: idx = new_last position for rx */
		idx = (rx_last + dma_rx_pkt.length) % FLEX_USB_RX_BUFFER_SIZE;
		if (idx > rx_last) {
			/* The message fits from rx_last to the
			   end of the buffer. */
			memcpy(rx_buffer + rx_last, dma_rx_pkt.payload,
			       dma_rx_pkt.length);
		} else {
			/* The first part of message must be stored
			   from rx_last to the end of the buffer, the
			   remaining part goes from begin buffer to
			   idx index.  */
			memcpy(rx_buffer + rx_last, dma_rx_pkt.payload,
			       (FLEX_USB_RX_BUFFER_SIZE - rx_last));
			memcpy(rx_buffer,
			       dma_rx_pkt.payload + FLEX_USB_RX_BUFFER_SIZE -
			       rx_last, idx+1);
		}
		rx_last = idx;
		rx_held += dma_rx_pkt.length;
	}
}

#elif defined __USE_USB_OLD__
unsigned int j=0;
char usb_buf[USB_BUF_SIZE] __attribute__((far));
unsigned int EE_usb_buf_in[USB_BUF_SIZE] __attribute__((far));
long int sent_prot2=0;
int tosend=1, sent=1;
int EE_toread=0, EE_read=0;
unsigned int EE_read_length=0;
long int sent_prot1=0;
char usb_initialized;

void EE_usb_init( void ) {
  if(!usb_initialized){

    LATAbits.LATA14 = 1; // dsPIC SPI communication busy

    /* Following code snippet shows SPI register configuration for SLAVE Mode*/
  	SPI1BUF = 0x00;
  	IFS0bits.SPI1IF = 0; //Clear the Interrupt Flag
  	IEC0bits.SPI1IE = 0; //Disable The Interrupt
    // SPI1CON1 Register Settings
  	SPI1CON1bits.DISSCK = 0; //Internal Serial Clock is Enabled.
  	SPI1CON1bits.DISSDO = 0; //SDOx pin is controlled by the module.
  	SPI1CON1bits.MODE16 = 1; //Communication is word-wide (16 bits).
  	SPI1CON1bits.SMP = 0; //Input Data is sampled at the middle of data
    //output time.
  	SPI1CON1bits.CKE = 0; //Serial output data changes on transition
    //from Idle clock state to active clock state
  	SPI1CON1bits.CKP = 0; //Idle state for clock is a low level; active
    //state is a high level
  	SPI1CON1bits.MSTEN = 0; //Master Mode disabled
  	SPI1STATbits.SPIROV=0; //No Receive Overflow Has Occurred
  	SPI1STATbits.SPIEN = 1; //Enable SPI Module
    //Interrupt Controller Settings
  	IFS0bits.SPI1IF = 0; //Clear the Interrupt Flag
  	IEC0bits.SPI1IE = 0; //Enable The Interrupt

  	// DMA0 configuration for SPI Tx
  	DMA0CON = 0x2000;

  	DMA0REQ = 0x00A;

  	DMA0PAD = (volatile unsigned int) &(SPI1BUF);
  	DMA0STA= __builtin_dmaoffset(Spi1TxBuffA);
//  	DMA0STB= __builtin_dmaoffset(Spi1TxBuffB);

  	IFS0bits.DMA0IF  = 0;			// Clear DMA interrupt
  	IEC0bits.DMA0IE  = 0;			// Disable DMA interrupt
  	DMA0CONbits.CHEN = 0;    // Disable Tx DMA Channel

  	// DMA1 configuration for SPI Rx; lower priority than DMA0
  	DMA1CON = 0x0000;
  	DMA1CNT = 3;
  	DMA1REQ = 0x00A;

  	DMA1PAD = (volatile unsigned int) &SPI1BUF;
  	DMA1STA= __builtin_dmaoffset(Spi1RxBuffA);
//  	DMA1STB= __builtin_dmaoffset(Spi1RxBuffB);

  	IFS0bits.DMA1IF  = 0;			// Clear DMA interrupt

  	IEC0bits.DMA1IE  = 1;			// Enable Rx DMA interrupt
  	DMA1CONbits.CHEN = 1;			// Enable DMA Channel

    IFS0bits.DMA0IF  = 0;			// Clear DMA interrupt
  	IEC0bits.DMA0IE  = 0;			// Disable DMA interrupt
  	DMA0CONbits.CHEN = 0;// Disable Tx DMA Channel

    usb_initialized=1;
	}

}


int EE_usb_send(unsigned int *buf, int len)
{

  int i = 0, busybuf = 0;
  //LATAbits.LATA14 = 1 means that dsPIC SPI communication busy
  if(!len) return len;
  EE_hal_begin_primitive();
  busybuf = (tosend - sent) % USB_BUF_SIZE;
  if(!((busybuf+1)% USB_BUF_SIZE)) {// the buffer is full
    len = 0;
    goto end;
  }
  if(busybuf < 0) busybuf+=USB_BUF_SIZE;
  if(len > (USB_BUF_SIZE-1-(busybuf))) len = (USB_BUF_SIZE-1-(busybuf));

  for(i=0; i<len; i++, tosend++){
    if(tosend == USB_BUF_SIZE+1) tosend = 1;
    Spi1TxBuffA[tosend] = buf[i];
  }
  if(tosend == USB_BUF_SIZE+1) tosend = 1;

  if(LATAbits.LATA14){ // DMA dedicated to SPI not active

    //if(sent != DMA0STA) for(;;); // debug
    busybuf = tosend - sent;
    if(busybuf < 0) busybuf+=USB_BUF_SIZE;
    if(busybuf > 31) busybuf = 31;
    if(busybuf > (USB_BUF_SIZE + 1 - sent)) busybuf = (USB_BUF_SIZE + 1 - sent);
    if(sent<1 || sent >256)
	     for(;;) EE_hal_begin_primitive();
    Spi1TxBuffA[sent-1] = busybuf;
    DMA0STA= __builtin_dmaoffset(Spi1TxBuffA);
    DMA0STA += (sent-1) << 1;
    DMA0CNT = busybuf+1;
    IFS0bits.DMA0IF  = 0;			// Clear DMA interrupt
  	IEC0bits.DMA0IE  = 1;			// Enable DMA interrupt
    DMA0CONbits.CHEN = 1;// Enable Tx DMA Channel
    LATAbits.LATA14 = 0; // wake up PIC18
  }


end:
  EE_hal_end_primitive();
  return len;
}

int EE_usb_read(unsigned int *buf, int log_channel)
{
  EE_hal_begin_primitive();
  if(EE_usb_buf_in[log_channel * 3])
  {
    buf[0]=EE_usb_buf_in[log_channel * 3];
    buf[1]=EE_usb_buf_in[(log_channel * 3)+1];
    buf[2]=EE_usb_buf_in[(log_channel * 3)+2];
  }
  else
  {
    EE_hal_end_primitive();
    return 0;
  }
  EE_hal_end_primitive();
  return 1;
}

int temp;
void __attribute__((interrupt, no_auto_psv)) _DMA0Interrupt(void)
{
  EE_hal_begin_primitive();
	LATAbits.LATA14 = 1;
	IFS0bits.DMA0IF  = 0;			// Clear DMA interrupt
	IEC0bits.DMA0IE  = 0;			// Disable DMA interrupt
	DMA0CONbits.CHEN = 0;    // Disable Tx DMA Channel

	int busybuf = 0;
	if(sent<1 || sent >256)
	 for(;;) EE_hal_begin_primitive();

	temp =sent;
  sent = (sent + Spi1TxBuffA[sent-1]);

  if(sent==USB_BUF_SIZE + 1) sent = 1;

  if(sent<1 || sent >256)
#ifdef ARIZONADEMO
    sent=tosend=1;
#else
	  for(;;) EE_hal_begin_primitive();
#endif

  if(tosend != sent) {
    //if(sent != DMA0STA) for(;;); // debug
    busybuf = tosend - sent;
    if(busybuf < 0) busybuf+=USB_BUF_SIZE;
    if(busybuf > 31) busybuf = 31;
    if(busybuf > (USB_BUF_SIZE + 1 - sent)) busybuf = (USB_BUF_SIZE + 1 - sent);
    Spi1TxBuffA[sent-1] = busybuf;
    DMA0STA= __builtin_dmaoffset(Spi1TxBuffA);
    DMA0STA += (sent-1) << 1;
    DMA0CNT = busybuf+1;

  	IFS0bits.DMA0IF  = 0;			// Clear DMA interrupt
  	IEC0bits.DMA0IE  = 1;			// Enable DMA interrupt
  	DMA0CONbits.CHEN = 1;    // Enable Tx DMA Channel

  	IFS0bits.DMA1IF  = 0;			// Clear DMA interrupt

    LATAbits.LATA14 = 0; // wake up PIC18
  }
  EE_hal_end_primitive();
}

void ProcessSpiRxSamples(unsigned int SpiRxBuffer[])
{
  int log_channel;
	if(!SpiRxBuffer[0])
		return;
	else if(SpiRxBuffer[0]==75) // received usb packet
  {
    IEC0bits.DMA1IE  = 0;			// Disable Rx DMA interrupt
  	DMA1CONbits.CHEN = 0;			// Disable DMA Channel


	 	IEC0bits.DMA1IE  = 1;			// Enable Rx DMA interrupt
  	DMA1CONbits.CHEN = 1;			// Enable DMA Channel
	}
	else if(SpiRxBuffer[0]==77) // reset usb send buffer
  {
    DMA0CONbits.CHEN = 0;// Disable Tx DMA Channel
    sent = tosend = 1;
    LATAbits.LATA14 = 1; // dsPIC SPI communication busy
	}
	else if(SpiRxBuffer[0]==80)
  {
    IEC0bits.DMA1IE  = 0;			// Disable Rx DMA interrupt
  	DMA1CONbits.CHEN = 0;			// Disable DMA Channel
    log_channel = SpiRxBuffer[1] >> 8;
    EE_usb_buf_in[(log_channel * 3)] = (SpiRxBuffer[1] & 0xFF); // id data
    EE_usb_buf_in[(log_channel * 3)+1] = SpiRxBuffer[2]; // float_h
    EE_usb_buf_in[(log_channel * 3)+2] = SpiRxBuffer[3]; // float_l
    IEC0bits.DMA1IE  = 1;			// Enable Rx DMA interrupt
  	DMA1CONbits.CHEN = 1;			// Enable DMA Channel
  }
}

void __attribute__((interrupt, no_auto_psv)) _DMA1Interrupt(void)
{
  EE_hal_begin_primitive();
  LATBbits.LATB14 =!LATBbits.LATB14;
 	ProcessSpiRxSamples(&Spi1RxBuffA[0]);

  IFS0bits.DMA1IF = 0;		// Clear the DMA0 Interrupt Flag
  EE_hal_end_primitive();
}

#endif // use usb

#ifdef __USE_PWM_OUT__

EE_UINT8 t_pre_scaler;

void EE_pwm_init(EE_UINT8 chan, unsigned long int pwm_period, unsigned long int init_pw)
{
  /* OutputCompare PWM constants
  *
  * pwm_timer2_period = (fcy/pre_scaler) x pwm_period - 1
  *     fcy [MHz]
  *     pwm_perdiod [microseconds]
  *
  * pwm_resolution = log_2((fcy/pre_scaler) x pwm_perdiod) [bits]
  */

  unsigned char pre_scaler=0;
  unsigned int p=0;

  /* Check PW limits */
  if( init_pw > pwm_period)
    return;

  T2CON = 0; /* Stops the Timer2 and reset control reg */

  TMR2  = 0; /* Clear contents of the timer register */

  IFS0bits.T2IF = 0; /* Clear the Disable Timer2 interrupt status flag */
  IEC0bits.T2IE = 0;

  /* Calculate the best(minimum) pre-scaling factor */
  for(pre_scaler=0; pre_scaler<4; pre_scaler++)
  {
    p = (((40*pwm_period) -1) / 0xFFFE) + 1;
    if(pre_scaler < 3){
      if( p <= (0x0001 << (pre_scaler*3)) ){
        p = (pre_scaler*3);
        break;
      }
    }
    else{
      if( p <= 256 ){
        p = 8;
        break;
      }
    }
  }
  if(pre_scaler > 3)
    return;

  T2CONbits.TCKPS = pre_scaler;       /* Set pre-scaler for Timer2 */

	t_pre_scaler = p;

  PR2 = ((pwm_period * 40) >> p);
	if(PR2 > 0) PR2 -= 1; /* Set period for Timer2 */
  p = (unsigned int)(( init_pw * 40) >> p );
	if(p>0) p -= 1;  /* Compute the initial PulseWidth to set */

  switch(chan)
  {
    case EE_PWM_PORT1:
			TRISDbits.TRISD7 = 0; /* Set OC8 as output */
      OC8R = p; /* Set the initial duty cycle */
      OC8RS = p; /* Load OCRS: current pwm duty cycle */
      OC8CON = 0x0006; /* Set OC8 module: PWM, no fault check, Timer2 */
      break;

    case EE_PWM_PORT2:
			TRISDbits.TRISD6 = 0; /* Set OC7 as output */
      OC7R = p; /* Set the initial duty cycle */
      OC7RS = p; /* Load OCRS: current pwm duty cycle */
      OC7CON = 0x0006; /* Set OC7 module: PWM, no fault check, Timer2 */
      break;
  }

	T2CONbits.TON = 1; 

  return;

}

void EE_pwm_set_duty_f( EE_UINT8 chan , float duty )
{
  /* The computed duty cycle*/
  float duty_out ;

  /* Get period from Timer2 period register PR2 */
  EE_UINT16 period = PR2;

  if (duty <= 0.0)
    duty_out = 0; //** for negative values assume zero
  else if(duty >= 1.0)
    duty_out = 1; //** for exessive values assume one
  else
    duty_out = duty; //** for the correct values ...

  // Computer register valure
  switch (chan) {
    case EE_PWM_PORT1:
      OC8RS = duty_out * (period+1);
      break;
    case EE_PWM_PORT2:
      OC7RS = duty_out * (period+1);
      break;
  }
}


#endif // __USE_PWM_OUT__

/* ************************************************************************* */

/* ************************************************************************* */

#endif // __USE_DEMOBOARD__

/* ************************************************************************* */
