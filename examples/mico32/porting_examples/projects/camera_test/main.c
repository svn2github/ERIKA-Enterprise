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
 * CAMERA TEST
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


/*---------------------------------------------------------------------*/

/* Application symbols and macros */
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

#define __CAMERA_DEBUG__

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

}

void system_timer_callback(void)	// EVERY 1 MS
{
	/* count the interrupts, waking up expired alarms */
	CounterTick(system_counter);
	
	return;
}

void cam_cbk(void)
{

}

/*
 * MAIN TASK
 */
int main(void)
{
	int ret;
	unsigned int image[10];
	EE_UINT8* address = (EE_UINT8*)0x02035000;
	
	EE_mico32_enableIRQ();
	
	/* Turn off all leds */
	write_led(NONE_LED);
	
	/* UART configuration */
	if( EE_uart_config(115200, EE_UART_BIT8_NO | EE_UART_BIT_STOP_1) != EE_UART_OK )
	{
			write_led(LED1);
    		while(1);
	}
	
	/* SYSTEM TIMER configuration */
	EE_system_timer_set_callback(system_timer_callback);
	EE_system_timer_init(MILLISECONDS_TO_TICKS(1), MICO32_TIMER_CONTROL_INT_BIT_MASK | MICO32_TIMER_CONTROL_CONT_BIT_MASK | MICO32_TIMER_CONTROL_START_BIT_MASK);
	SetRelAlarm(task1_alarm, 1000, 1000);	/* Set an alarm to activate Task1*/
		
	/* Create the image */
	/*block*/{
		int i;
		for(i=0;i<10;i++)
			image[i] = i;
	}
	
	/* Read IF */
	ret = EE_uart_write_byte((EE_UINT8)EE_camera_read_IF_flag());
	if(ret<0)
	{
			write_led(LED2);
    		while(1);
	}
	
	/* Set camera driver operating mode */
	EE_camera_init(EE_CAMERA_ISR_MODE);
	
	/* Configure the camera */
	EE_camera_set_default_configuration();
	
	/* Staret frame acquisition */
	EE_camera_capture(address, cam_cbk);
	
	/* Write and read the address */
	/*block*/{
		EE_UINT8 aux[4];
		unsigned int imadd;
		char *str = "\nAddress:\n";
		imadd = (unsigned int)EE_camera_read_address();
		aux[0] = (EE_UINT8)(imadd & 0x000000FF);
		aux[1] = (EE_UINT8)((imadd >> 8) & 0x000000FF);
		aux[2] = (EE_UINT8)((imadd >> 16) & 0x000000FF);
		aux[3] = (EE_UINT8)((imadd >> 24) & 0x000000FF);
		ret = EE_uart_write_buffer((EE_UINT8 *)str,strlen(str));
		if(ret<0)
		{
			write_led(LED3);
    		while(1);
		}
		ret = EE_uart_write_buffer(aux,4);
		if(ret<0)
		{
			write_led(LED4);
    		while(1);
		}
	}
	
	/* Read IF */
	ret = EE_uart_write_byte((EE_UINT8)EE_camera_read_IF_flag());
	if(ret<0)
	{
			write_led(LED5);
    		while(1);
	}
	
	/* Final check */
	while(EE_camera_frame_terminated());	// wait the end of transmission...
	/*block*/{
		EE_UINT8 aux[4];
		unsigned int imdata;
		int i;
		for(i=0;i<10;i++)
		{
			imdata = *(address+i);
			aux[0] = (EE_UINT8)(imdata & 0x000000FF);
			aux[1] = (EE_UINT8)((imdata >> 8) & 0x000000FF);
			aux[2] = (EE_UINT8)((imdata >> 16) & 0x000000FF);
			aux[3] = (EE_UINT8)((imdata >> 24) & 0x000000FF);
			ret = EE_uart_write_buffer(aux,4);
			if(ret<0)
			{
				write_led(LED6);
    			while(1);
			}
		}
		
	}
	
	
	while(1);
	
    return 0;
}


