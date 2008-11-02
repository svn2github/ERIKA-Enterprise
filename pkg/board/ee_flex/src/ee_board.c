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

/* /\************************************************************************* */
/*  Buttons */
/*  *************************************************************************\/ */

#ifdef __USE_BUTTONS__

void (*EE_button_callback)(void);
EE_UINT8 EE_button_mask;

ISR2(_CNInterrupt)
{
	// Execute callback function
	if (EE_button_callback != NULL) {
		EE_button_callback();
	}
		
	/* reset CN interrupt flag */
	IFS1bits.CNIF = 0;           
}

#endif


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
EE_UINT16 lcd_temp_count = 0;

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

#if defined (__USE_USB__) || defined (__USE_SPI__)

#define USB_BUF_SIZE 256
unsigned int Spi1TxBuffA[USB_BUF_SIZE+1] __attribute__((space(dma)));

unsigned int Spi1RxBuffA[64] __attribute__((space(dma)));
//unsigned int Spi1RxBuffB[64] __attribute__((space(dma));
//unsigned int Spi1TxBuffB[256] __attribute__((space(dma)));
unsigned int RxDmaBuffer = 0;
unsigned int TxDmaBuffer = 0;
#endif

#ifdef __USE_USB__

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

/* ************************************************************************* */

/* ************************************************************************* */

#endif // __USE_DEMOBOARD__

/* ************************************************************************* */
