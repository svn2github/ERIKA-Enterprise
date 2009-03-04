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
 * ERIKA Enterprise Basic - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2007  Evidence Srl
 *
 * This file is part of ERIKA Enterprise Basic.
 *
 * ERIKA Enterprise Basic is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * ERIKA Enterprise Basic is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise Basic; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 */


/*
 * Author: 2006 Paolo Gai
 * CVS: $Id: dspic_main.c,v 1.3 2008/07/17 17:37:51 francesco Exp $
 */

#include "ee.h"
#include "cpu/pic30/inc/ee_irqstub.h"
#include <stdio.h>

#define XNAME(x,y)  x##y
#define NAME(x,y)   XNAME(x,y)

#define XSTR(x)    #x
#define STR(x)     XSTR(x)

#define MODELNAME  STR(MODELN)
#include MODELNAME 

#define _scicos_openZB_c_

#include "scicos_openZB.h"
#include "scicos_USB.h"

// Primary (XT, HS, EC) Oscillator with PLL
_FOSCSEL(FNOSC_PRIPLL);
// OSC2 Pin Function: OSC2 is Clock Output - Primary Oscillator Mode: XT Crystanl
_FOSC(OSCIOFNC_ON & POSCMD_XT);
// Watchdog Timer Enabled/disabled by user software
_FWDT(FWDTEN_OFF);
// Disable Code Protection
_FGS(GCP_OFF);            							

static double scicos_time; //simple time
static int dspic_time;
static double t;
static double actTime;

//TODO: mettere sotto ifdef __USE_ZIGBEE__
unsigned int scicosOpenZB_address_table[SCICOS_OPENZB_ADDRESSES];
unsigned int scicosOpenZB_address_count = 0;
float scicosOpenZB_rx_buffer[SCICOS_OPENZB_ADDRESSES][SCICOS_OPENZB_CHANNELS]  
__attribute__((far));
float scicosUSB_rx_buffer[SCICOS_USB_CHANNELS] __attribute__((far));

double get_scicos_time()
{
	return(actTime);
}

/* Program the Timer2 peripheral to raise interrupts */
void T1_program(void)
{
	T1CON = 0;		    /* Stops the Timer1 and reset control reg	*/
	TMR1  = 0;		    /* Clear contents of the timer register	*/
	PR1   = 0x9C40;		/* Load the Period register wit the value 50000	ticks = 25 ms*/
	IPC0bits.T1IP = 5;	/* Set Timer1 priority to 1		*/
	IFS0bits.T1IF = 0;	/* Clear the Timer1 interrupt status flag	*/
	IEC0bits.T1IE = 1;	/* Enable Timer1 interrupts		*/
	T1CONbits.TON = 1;	/* Start Timer1 with prescaler settings at 1:1
				* and clock source set to the internal 
				* instruction cycle			*/
}

/* Clear the Timer2 interrupt status flag */
void T1_clear(void)
{
	IFS0bits.T1IF = 0;
}


/* LCD update functions
 * -------------------------------------------------------------
 */

#ifdef __USE_LCD__

/* defined in contrib/scicos/src/pic20/flex_dmb_lcd.c */
volatile float scicos_lcd_value1 = 0.0;
volatile float scicos_lcd_value2 = 0.0;
volatile int scicos_lcd_used = 0;

static char lcd_buf[17];

/*
* Output syntax: n:smmmmmmmmEsaa
* where:	n is the input number (0/1);
*	s is the signum (-/+);
*	mmmmmmmm is the mantissa (max 8 chars);
*	aaa is the exponent (max 3 chars).
*/
static void write_buf(float data)
{
	/* Conversion routine */
	//** WARNING: 
	//**          Two lines = 7.5 ms !
	//** To DO: find a faster sprintf()
	sprintf(lcd_buf,"%+.6E ",(double)data);
}

void update_lcd(void)
{
	static float oldvalue1 = 1.0; // something different from 0
	static float oldvalue2 = 1.0; // something different from 0
	float newvalue1;
	float newvalue2;

	if (!scicos_lcd_used)
		return;

	/* check if we have to update the LCD */
	EE_pic30_disableIRQ();
	newvalue1 = scicos_lcd_value1;
	newvalue2 = scicos_lcd_value2;	
	EE_pic30_enableIRQ();

	/* stop if the data are the same */
	if (newvalue1 == oldvalue1 && newvalue2 == oldvalue2)
		return;
 
	/* save the new values */
	oldvalue1 = newvalue1;
	oldvalue2 = newvalue2;

	/* Write 1st value on LCD */
	EE_lcd_puts("1:");
	write_buf(newvalue1);
	EE_lcd_puts(lcd_buf);
	
	/* Move to second line */
	EE_lcd_line2();
	
	/* Write 2nd value on LCD */
	EE_lcd_puts("2:");
	write_buf(newvalue2);
	EE_lcd_puts(lcd_buf);	

	/* Reset position for the next iteration */
	EE_lcd_home();
}

#endif



/* This is an ISR Type 2 which is attached to the Timer2 peripheral IRQ pin
 * The ISR simply calls CounterTick to implement the timing reference
 */
ISR2(_T1Interrupt)
{
	/* clear the interrupt source */
	T1_clear();

	/* count the interrupts, waking up expired alarms */
	CounterTick(SciCounter);
}

TASK(rt_sci)
{
	actTime=t;
	NAME(MODEL,_isr)(actTime);
	t += scicos_time;
}

#ifdef __USE_LCD__
TASK(rt_LCD)
{
	update_lcd();
}
#endif

TASK(rx_USB)
{
	struct flex_bus_packet_t pkt;
	int retv;

	memset((EE_UINT8*) &pkt, 0, sizeof(struct flex_bus_packet_t));
	retv = EE_usb_read((EE_UINT8 *) &pkt, sizeof(struct flex_bus_packet_t));
	if (retv == sizeof(struct flex_bus_packet_t)) {
		GetResource(scicosUSB_rx_buffer_mutex);
		scicosUSB_rx_buffer[pkt.channel] = *((float*) pkt.payload.data);
		ReleaseResource(scicosUSB_rx_buffer_mutex); 
	}
}


void scicosOpenZB_rx_callback(OpenZB_ExitStatus code,  EE_UINT8* pdu, EE_UINT16 size)
{
	static int pippo;
	EE_INT16 ch, idx;
	ScicosOpenZB_Payload *packet = (ScicosOpenZB_Payload*) pdu;

	/* Check Packet */
	if (size != sizeof(ScicosOpenZB_Payload)) {
		EE_led_2_on();
	  	return;	// Wrong size
	}
	if (packet->dst_addr != openzb_device_address)
		return;	// Packet is not for me
	ch = packet->channel_id;
	if (ch >= SCICOS_OPENZB_CHANNELS)
		return; // Bad channel
	idx = scicosOpenZB_address_lookup(packet->src_addr);
	if (idx >= SCICOS_OPENZB_ADDRESSES) {
		EE_led_1_on();
	  	return; // Bad Address (unknown by the lookup table)
	}
	/* Put the float data into the channel buffer */
	GetResource(scicosOpenZB_rx_buffer_mutex);
	scicosOpenZB_rx_buffer[idx][ch] = packet->data;
	ReleaseResource(scicosOpenZB_rx_buffer_mutex);
	if(pippo) {
		EE_led_0_on();
		pippo=0;     
	} else{
		EE_led_0_off();
		pippo=1;  
	}
}

int main(void)
{
	/* Clock setup */
	CLKDIVbits.DOZEN   = 0;
	CLKDIVbits.PLLPRE  = 0;
	CLKDIVbits.PLLPOST = 0;
	PLLFBDbits.PLLDIV  = 78;
	/* Wait for PLL to lock */
	while(OSCCONbits.LOCK!=1);
	#ifdef __USE_LCD__
	EE_lcd_init(); /* Init LCD */
	EE_lcd_clear(); /* Clean LCD */
	#endif
	memset(scicosOpenZB_address_table, 0xFF, 
	       SCICOS_OPENZB_ADDRESSES * sizeof(unsigned int));

	NAME(MODEL,_init)(); 

	t = 0.0; //simulation time
  
	/* Program Timer 1 to raise interrupts */
	T1_program();
  
	//TODO: mettere questo pezzo sotto ifdef __USE_ZIGBEE__
	openZB_init(scicosOpenZB_rx_callback, NULL); 
  
	EE_demoboard_leds_init();
  
	scicos_time = get_tsamp();
	dspic_time = (int) (1000*scicos_time);
	SetRelAlarm(AlarmSci, dspic_time, dspic_time);
		
	#ifdef __USE_LCD__
	SetRelAlarm(AlarmLcd, dspic_time, 500);
	#endif
	SetRelAlarm(AlarmUSB, dspic_time, dspic_time);

	/* Forever loop: background activities (if any) should go here */
	for (;;) ;	
	
	return 0;
}
