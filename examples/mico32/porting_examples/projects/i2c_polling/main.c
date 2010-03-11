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
 * I2C POLLING TEST
 */

/* RT-Kernel */
#include <ee.h>
/* Platform description */
#include <system_conf.h>
/* Erika Mico32 interrupts */
#include <cpu/mico32/inc/ee_irq.h>
/* Lattice components */
//#include "mcu/mico32/inc/ee_i2c.h"
//#include "mcu/mico32/inc/ee_uart.h"
#include <MicoGPIO.h>
/* Other libraries */
#include <string.h>
#include <stdio.h>

/* Application symbols and macros */
// #define ONLY_TX	// to check transmission only...
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

struct TTime {
  char year, month, day, hours, minutes, seconds;
};

int rtc_write(int * retvalue);
int rtc_read(int * retvalue);
int Display_Time(void); 
void write_led(volatile unsigned int led);
unsigned int read_led(void);
int print_error(EE_UINT8 *s, int len);

/* Global variables  */
volatile int counter1 = 0;				// Counters; volatile because they are accessed in interrupt handlers and different tasks 
volatile EE_INT8 uart_byte = 'A'-1;		// used in ONLY_TX mode...
struct TTime TimeToWrite, TimeRead;
char yearmod4, byteRead;
EE_UINT8 rx_data[16];
EE_UINT8 tx_data[16];
char str1[100];
char str2[100];


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
	int ret;
	int retval=0;
	
    counter1++;
    
    ret = rtc_read(&retval);
    
    if(ret == EE_I2C_OK)
    {
		ret = Display_Time(); 
		if(ret<0)
		{
			write_led(LED4);
			while(1);
		}
   	}
   	else
   	{
   		write_led(LED6);
   		while(1);
   	}
	
}

/*
 * MAIN TASK
 */
int main(void)
{
	int i = 0;
	int ret;
	int retval=0;
	
	EE_mico32_disableIRQ();

	/* Turn off all leds */
	write_led(NONE_LED);
	
	if( EE_uart_config(115200, EE_UART_BIT8_NO | EE_UART_BIT_STOP_1) != EE_UART_OK )
	{
			write_led(LED5);
			/* Activate a periodic task */
    		while(1);
	}

	write_led(LED1);

	///* Background activity */
	if( EE_i2c_config(100000, 0) == EE_I2C_OK )
	{
			ret = rtc_write(&retval);
			if(ret == EE_I2C_OK)
			{
				write_led(LED2);
				/* Activate a periodic task */
	    		while(1)
	    		{
		 			for(i=0;i<1000000;i++);
	   				ActivateTask(Task1);
	    		}
			}
			else
				write_led(LED7);
	}
	else
		write_led(LED8);

	while(1);
	
    return 0;
}

int rtc_write(int * retvalue) {
	EE_UINT8 device = 0xA0;
	EE_UINT8 address;
	
    TimeToWrite.year    = 7;    			// 2007 (offset from 2000)
    TimeToWrite.month   = 12;
    TimeToWrite.day     = 31;
    TimeToWrite.hours   = 23;
   	TimeToWrite.minutes = 59;
   	TimeToWrite.seconds = 40;
   	
   	address = 0;							// address in memory
   	tx_data[0] = 0x80;
   	tx_data[1] = 0;
   	tx_data[2] = ((TimeToWrite.seconds/10)<<4) + (TimeToWrite.seconds%10);
   	tx_data[3] = ((TimeToWrite.minutes/10)<<4) + (TimeToWrite.minutes%10);
   	tx_data[4] = ((TimeToWrite.hours/10)<<4) + (TimeToWrite.hours%10);
   	tx_data[5] = ((TimeToWrite.year%4)<<6) + ((TimeToWrite.day/10)<<4) +(TimeToWrite.day%10);
   	tx_data[6] = ((TimeToWrite.month/10)<<4) + (TimeToWrite.month%10);
   	retvalue[0] = EE_i2c_write_buffer(device, address, tx_data, 7);	
   	
   	if(retvalue[0]!= EE_I2C_OK) 
   	{
   		str1[0] = '\0';
   		str2[0] = '\0';
   		sprintf(str2,"%d",retvalue[0]);
   		strcat(str1,"\nrtc_write error code: -1\nreturn value: ");
   		strcat(str1,str2);
   		print_error((EE_UINT8 *)str1, strlen(str1));	
   		return -1;
   	}

	address = 0x10;							// address in memory
   	tx_data[0] = TimeToWrite.year;			// data to be written
   	retvalue[0] = EE_i2c_write_byte(device, address, tx_data[0]);	
   	if(retvalue[0]!= EE_I2C_OK)
   	{
   		str1[0] = '\0';
   		str2[0] = '\0';
   		sprintf(str2,"%d",retvalue[0]);
   		strcat(str1,"\nrtc_write error code: -2\nreturn value: ");
   		strcat(str1,str2);
   		print_error((EE_UINT8 *)str1, strlen(str1));		
   		return -2;
   	}

	address = 0;							// address in memory
   	tx_data[0] = 0;							// data to be written
   	retvalue[0] = EE_i2c_write_byte(device, address, tx_data[0]);	
   	if(retvalue[0]!= EE_I2C_OK)
   	{
   		str1[0] = '\0';
   		str2[0] = '\0';
   		sprintf(str2,"%d",retvalue[0]);
   		strcat(str1,"\nrtc_write error code: -2\nreturn value: ");
   		strcat(str1,str2);
   		print_error((EE_UINT8 *)str1, strlen(str1));		
   		return -2;
   	}
	
   	return 0;
}

int rtc_read(int * retvalue) 
{
	EE_UINT8 device = 0xA0;
	EE_UINT8 address;
	
	address = 2;											// address in memory
   	retvalue[0] = EE_i2c_read_buffer(device, address, rx_data, 5);	
   	if(retvalue[0]!= EE_I2C_OK)
   	{
   		str1[0] = '\0';
   		str2[0] = '\0';
   		sprintf(str2,"%d",retvalue[0]);
   		strcat(str1,"\nrtc_write error code: -4\nreturn value: ");
   		strcat(str1,str2);
   		print_error((EE_UINT8 *)str1, strlen(str1));	
   		return -4;
   	}
   	
   	byteRead = rx_data[0];		// read seconds byte
   	TimeRead.seconds = (byteRead >> 4)*10 + (byteRead & 0x0F); // transform seconds
   	byteRead = rx_data[1];     	// read minutes byte
   	TimeRead.minutes = (byteRead >> 4)*10 + (byteRead & 0x0F); // transform minutes
   	byteRead = rx_data[2];     	// read hours byte
   	TimeRead.hours = (byteRead >> 4)*10 + (byteRead & 0x0F); // transform hours
    byteRead = rx_data[3];     	// read year/day byte
   	TimeRead.day = ((byteRead & 0b00110000) >> 4)*10 + (byteRead & 0x0F); // transform day
   	yearmod4 = (byteRead & 0b11000000) >> 6;   // get year mod 4 from RTC
    byteRead = rx_data[4];     	// read weekday/month byte
   	TimeRead.month = ((byteRead & 0b00010000) >> 4)*10 + (byteRead & 0x0F); // transform month
   	
	address = 0x10;				// address in memory
	
	rx_data[0] = EE_i2c_read_byte(device, address);	
	retvalue[0] = rx_data[0];
   	if(rx_data[0] < 0)
   	{
   		str1[0] = '\0';
   		str2[0] = '\0';
   		sprintf(str2,"%d",retvalue[0]);
   		strcat(str1,"\nrtc_write error code: -5\nreturn value: ");
   		strcat(str1,str2);
   		print_error((EE_UINT8 *)str1, strlen(str1));	
   		return -5;
   	}
  
    byteRead = rx_data[0];  		// read year
   	if (yearmod4 != byteRead % 4 )  // check if year is incremented in RTC
   	{	// in this case the new value should be written to RTC RAM at address 16(0x10)
   		byteRead++;  
   		address = 0x10;				// address in memory
   		tx_data[0] = byteRead;		// data to be written
   		retvalue[0] = EE_i2c_write_byte(device, address, tx_data[0]);	
   		if(retvalue[0]!= EE_I2C_OK)
   		{
	   		str1[0] = '\0';
	   		str2[0] = '\0';
	   		sprintf(str2,"%d",retvalue[0]);
	   		strcat(str1,"\nrtc_write error code: -6\nreturn value: ");
	   		strcat(str1,str2);
	   		print_error((EE_UINT8 *)str1, strlen(str1));		
	   		return -6;
   		}
    	
   	}
   	TimeRead.year = byteRead;
   	
   	return 0;
}

int Display_Time(void) 
{
	EE_UINT8 txt[16];
	int ret1, ret2;
	
   	// output values to USART
   	txt[0] = (TimeRead.day / 10) + 48;
   	txt[1] = (TimeRead.day % 10) + 48;
   	txt[2] = '/';
   	txt[3] = (TimeRead.month / 10) + 48;
   	txt[4] = (TimeRead.month % 10) + 48;
   	txt[5] = '/';
   	txt[6] = ((TimeRead.year % 100) / 10) + 48;
   	txt[7] = (TimeRead.year % 10)  + 48;
   	txt[8] = ' ';
   	ret1 = EE_uart_write_buffer(txt,9);
	if(ret1 < 0) return ret1;
	
   	txt[0] = (TimeRead.hours / 10) + 48;
   	txt[1] = (TimeRead.hours % 10) + 48;
   	txt[2] = ':';
   	txt[3] = (TimeRead.minutes / 10) + 48;
   	txt[4] = (TimeRead.minutes % 10) + 48;
   	txt[5] = ':';
   	txt[6] = (TimeRead.seconds / 10) + 48;
   	txt[7] = (TimeRead.seconds % 10) + 48;
   	txt[8] = '\n';
   	ret2 = EE_uart_write_buffer(txt,9);
	if(ret2 < 0) return ret2;
	
   	return ret1+ret2;
}

int print_error(EE_UINT8 *s, int len)
{
	int ret;
	
	ret = EE_uart_write_buffer(s,len);
	
	return ret;
}


