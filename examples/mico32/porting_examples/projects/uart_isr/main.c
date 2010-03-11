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
 * UART ISR TEST
 */

/* RT-Kernel */
#include <ee.h>
/* Platform description */
#include <system_conf.h>
/* Erika Mico32 interrupts */
#include <cpu/mico32/inc/ee_irq.h>
/* Lattice components */
//#include "mcu/mico32/inc/ee_uart.h"
#include <MicoGPIO.h>


/* Application symbols and macros */

//#define ISR_BLOCK_MODE							// to check blocking mode

#define APP_CPU_CLOCK_MHZ (34000000)			// CPU clock frequency
#define LED1 ((unsigned int)(~0x01))			// select Led1 (write 0 to turn on, write 1 to turn off)
#define LED2 ((unsigned int)(~0x02))			// select Led2 (write 0 to turn on, write 1 to turn off)
#define LED3 ((unsigned int)(~0x04))			// select Led3 (write 0 to turn on, write 1 to turn off)
#define LED4 ((unsigned int)(~0x08))			// select Led4 (write 0 to turn on, write 1 to turn off)
#define LED5 ((unsigned int)(~0x10))			// select Led5 (write 0 to turn on, write 1 to turn off)
#define LED6 ((unsigned int)(~0x20))			// select Led6 (write 0 to turn on, write 1 to turn off)
#define LED7 ((unsigned int)(~0x40))			// select Led7 (write 0 to turn on, write 1 to turn off)
#define LED8 ((unsigned int)(~0x80))			// select Led8 (write 0 to turn on, write 1 to turn off)
#define ALL_LEDS ((unsigned int)(~0xFF))		// select all leds (write 0 to turn on, write 1 to turn off)
#define NONE_LED ((unsigned int)(0xFF))			// no leds selected (write 0 to turn on, write 1 to turn off)

/* User functions */
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

/*
 * Task 1
 */
TASK(Task1)
{
	EE_UINT8 uart_byte; 
    int ret = 0;
   
 	ret = EE_uart_read_byte(&uart_byte);
 	
 	if( ret == EE_UART_ERR_RX_BUF_EMPTY )			// This function gets a byte from the rx buffer...
    {
    	/* Turn on ERROR led */
    	write_led(LED2);							// LED2 is always turned off in blocking mode
    }
	else if(ret == 1)
    {
    	write_led(LED4);
    	ret = EE_uart_write_byte(uart_byte);		// This function puts bytes in the tx buffer...
  		if(ret!=1)
  			write_led(LED3);
  		else
  			write_led(LED1);

	}

}

/* User tx-callback */
void tx_cbk(void)
{
	write_led(NONE_LED);
	return;
}

/*
 * MAIN TASK
 */
int main(void)
{
	int mode;
	int i;
	
	EE_mico32_enableIRQ();
	
	/* Turn off all leds */
	write_led(NONE_LED);
	
	/* Initialization */
	EE_uart_config(115200, EE_UART_BIT8_NO | EE_UART_BIT_STOP_1);
	
	/* Background activity */
	#ifdef ISR_BLOCK_MODE
	mode = EE_UART_RXTX_ISR | EE_UART_RXTX_BLOCK;
	#else
	mode = EE_UART_RXTX_ISR;
	#endif
	
	/* Set the user tx-callback */
	EE_uart_set_tx_callback(tx_cbk);

	/* Set ISR mode */
	if( EE_uart_set_mode(mode) == EE_UART_OK )
	{
			/* Activate a periodic task */
    		while(1)
    		{
	 			for(i=0;i<100000;i++);
   				ActivateTask(Task1);		// Task1 is used to fill tx buffer and get bytes from rx buffer...  
    		}
	}

	/* Turn on ERROR led */
	write_led(LED4);
	
    return 0;
}
