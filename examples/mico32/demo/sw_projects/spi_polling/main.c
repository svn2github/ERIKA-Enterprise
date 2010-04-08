/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
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
  Name: main.c
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: SPI test.
*/

/* RT-Kernel */
#include <ee.h>
/* Platform description */
#include <system_conf.h>
/* Erika Mico32 interrupts */
#include <cpu/mico32/inc/ee_irq.h>
/* Lattice components */
#include <MicoGPIO.h>
#include <MicoMacros.h>
/* Other libraries */
#include <string.h>


/* ------------------------------------------------------------------- */
/* DEMOBOARD LED */
/* ------------------------------------------------------------------- */
#define APP_CPU_CLOCK_MHZ (34000000)
#define LED1 ((unsigned int)(~0x01))
#define LED2 ((unsigned int)(~0x02))
#define LED3 ((unsigned int)(~0x04))
#define LED4 ((unsigned int)(~0x08))
#define LED5 ((unsigned int)(~0x10))
#define LED6 ((unsigned int)(~0x20))
#define LED7 ((unsigned int)(~0x40))
#define LED8 ((unsigned int)(~0x80))
#define ALL_LEDS ((unsigned int)(~0xFF))
#define NONE_LED ((unsigned int)(0xFF))

void write_led(volatile unsigned int led)		// Function to turn on the leds 
{
    MicoGPIO_t *ledc = (MicoGPIO_t *)LED_BASE_ADDRESS;
    ledc->data = (EE_UINT8)led;
}

unsigned int read_led(void)						// Function to read the state of the leds 
{
    MicoGPIO_t *ledc = (MicoGPIO_t *)LED_BASE_ADDRESS;
    return (unsigned int)(~(ledc->data));
}

/* ------------------------------------------------------------------- */
/* Kernel counter incrememt  */
/* ------------------------------------------------------------------- */
void system_timer_callback(void)	// EVERY 1 MS
{
	/* count the interrupts, waking up expired alarms */
	CounterTick(system_counter);
	
	return;
}

/* ------------------------------------------------------------------- */
/* ENC28j60 section  */
/* ------------------------------------------------------------------- */
#define ENC28J60_ETXNDL		0x06

#define ENC28J60_WCR (0x2<<5)				// Write Control Register command
#define ENC28J60_BFS (0x4<<5)				// Bit Field Set command
#define ENC28J60_BFC (0x5<<5)				// Bit Field Clear command
#define ENC28J60_RCR (0x0<<5)				// Read Control Register command
#define ENC28J60_RBM ((0x1<<5) | 0x1A)		// Read Buffer Memory command
#define ENC28J60_WBM ((0x3<<5) | 0x1A)		// Write Buffer Memory command
#define ENC28J60_SR  ((0x7<<5) | 0x1F)		// System Reset command does not use an address.
                                			// It requires 0x1F, however.
#define EE_ENC28J60_ADDRESS_MASK 		(0x1F)
#define EE_ENC28J60_DEVICE_ID 			(0x01)
#define EE_enc28j60_write_buffer(a, b) 	EE_spi_send_buffer(a, b)   
#define EE_enc28j60_read_buffer(a, b) 	EE_spi_receive_buffer(a, b)    			
#define EE_enc28j60_set_slave(a) 		EE_spi_set_slave(a)
#define EE_enc28j60_set_SSO() 			EE_spi_set_SSO()
#define EE_enc28j60_clear_SSO() 		EE_spi_clear_SSO()

int enc28j60_write_ETH_register(int address, EE_UINT8 data)
{
	int ret;
	EE_UINT8 add = address & EE_ENC28J60_ADDRESS_MASK;
	EE_UINT8 tx_data[2];
	
	EE_enc28j60_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_set_SSO();
	tx_data[0] = ENC28J60_WCR | add;
	tx_data[1] = data;
	ret = EE_enc28j60_write_buffer(tx_data, 2);
	EE_enc28j60_clear_SSO();
	//if(ret = ...)
	
	return ret;
}

int enc28j60_read_ETH_register(int address)
{
	int ret;
	EE_UINT8 add = address & EE_ENC28J60_ADDRESS_MASK;
	EE_UINT8 rx_data[1];
	EE_UINT8 tx_data[1];
	
	
	EE_enc28j60_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_set_SSO();
	tx_data[0] = ENC28J60_RCR | add;
	ret = EE_enc28j60_write_buffer(tx_data, 1);
	//EE_spi_clear_SSO();
	//if(ret = ...)
	//EE_spi_set_slave(EE_ENC28J60_DEVICE_ID);	
	//EE_spi_set_SSO();
	ret = EE_enc28j60_read_buffer(rx_data, 1);
	EE_enc28j60_clear_SSO();
	//if(ret = ...)
	
	if(ret >= 0)
		ret = rx_data[0];
	
	return ret;
}


/* ------------------------------------------------------------------- */
/* Tasks  */
/* ------------------------------------------------------------------- */
TASK(Task1)
{
	int ret;
	EE_UINT8 udata;
	static EE_UINT8 data = 0;
	
	data++;
	udata = data;
	
	/* SPI Write */
	ret = enc28j60_write_ETH_register(ENC28J60_ETXNDL, data);
	if(ret<0)
	{
		write_led(LED1);
		while(1);
	}
	ret = EE_uart_send_buffer(&udata, 1);
	
	/* SPI Read */
	ret = enc28j60_read_ETH_register(ENC28J60_ETXNDL);
	udata = ret;
	if(ret<0)
	{
		write_led(LED2);
		while(1);
	}
	ret = EE_uart_send_buffer(&udata, 1);
	
}

/* ------------------------------------------------------------------- */
/* Main  */
/* ------------------------------------------------------------------- */
int main(void)
{
	//EE_mico32_disableIRQ();
	EE_mico32_enableIRQ();
	
	/* Turn off all leds */
	write_led(NONE_LED);
	
	/* Uart configuration */
	EE_uart_config(115200, EE_UART_BIT8_NO | EE_UART_BIT_STOP_1);
	
	/* SPI configuration */
	EE_spi_config(0);

	/* SYSTEM TIMER configuration */
	EE_system_timer_set_ISR_callback(system_timer_callback);
	EE_system_timer_init(MILLISECONDS_TO_TICKS(1), MICO32_TIMER_CONTROL_INT_BIT_MASK | MICO32_TIMER_CONTROL_CONT_BIT_MASK | MICO32_TIMER_CONTROL_START_BIT_MASK);
	SetRelAlarm(task1_alarm, 1000, 1000);	/* Set an alarm to activate Task1*/
	
	while(1);
		
    return 0;
}




