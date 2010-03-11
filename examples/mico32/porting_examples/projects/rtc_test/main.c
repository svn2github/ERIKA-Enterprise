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
 * RTC TEST
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
//#include <stdio.h>

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

#define __RTC_DEBUG__

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

int rtc_display_time(TTime *TimeRead);

/*
 * Task 1
 */
TASK(Task1)
{
//	static int led_flag=0;
//	
//	if(led_flag==0)
//		write_led(LED1);
//	else
//		write_led(LED2);
//	
//	led_flag ^= 1;

	int ret;
	TTime now;
    
    ret = EE_rtc_read_time(&now);
    
    if(ret == EE_I2C_OK)
    {
		ret = rtc_display_time(&now); 
		if(ret<0)
		{
			write_led(LED4);
			#ifdef __RTC_DEBUG__
			char *str = "I2C error in rtc_display_time\n";
			EE_uart_write_buffer((EE_UINT8 *)str,strlen(str));
			#endif
			while(1);
		}
   	}
   	else
   	{
   		write_led(LED6);
   		#ifdef __RTC_DEBUG__
		char *str = "I2C error in EE_rtc_read_time\n";
		EE_uart_write_buffer((EE_UINT8 *)str,strlen(str));
		#endif
   		while(1);
   	}
	
}

void system_timer_callback(void)
{
	/* count the interrupts, waking up expired alarms */
	CounterTick(system_counter);
	
	return;
}

/*
 * MAIN TASK
 */
int main(void)
{
	int ret;
	TTime tt;
	
	EE_mico32_enableIRQ();
	
	/* Turn off all leds */
	write_led(NONE_LED);
	
	/* UART configuration */
	if( EE_uart_config(115200, EE_UART_BIT8_NO | EE_UART_BIT_STOP_1) != EE_UART_OK )
	{
			write_led(LED5);
    		while(1);
	}
	
	/* I2C configuration */
	if( EE_i2c_config(100000, 0) != EE_I2C_OK )
	{
		#ifdef __RTC_DEBUG__
		char *str = "I2C error in EE_i2c_config\n";
		EE_uart_write_buffer((EE_UINT8 *)str,strlen(str));
		#endif
		write_led(LED8);
		while(1);
	}
	
	/* Write Time in RTC */
	tt.year    = 9;    				// 2009 (offset from 2000)
    tt.month   = 12;
    tt.day     = 31;
    tt.hours   = 23;
   	tt.minutes = 59;
   	tt.seconds = 40;
   	tt.hundreds_of_seconds = 0;
	ret = EE_rtc_write_time(&tt);
	if(ret == EE_I2C_OK)
	{
		write_led(LED2);
		/* Set timer callback */
		EE_system_timer_set_callback(system_timer_callback);
		/* Configure System Timer */
		EE_system_timer_init(MILLISECONDS_TO_TICKS(1), MICO32_TIMER_CONTROL_INT_BIT_MASK | MICO32_TIMER_CONTROL_CONT_BIT_MASK | MICO32_TIMER_CONTROL_START_BIT_MASK);
		/* Activate an alarm */
		SetRelAlarm(task1_alarm, 1000, 1000);
	}
	else
	{
		#ifdef __RTC_DEBUG__
		char *str = "I2C error in EE_rtc_write_time\n";
		EE_uart_write_buffer((EE_UINT8 *)str,strlen(str));
		#endif
		write_led(LED7);
		while(1);
	}
	
	while(1);
	
    return 0;
}

int rtc_display_time(TTime *TimeRead) 
{
	EE_UINT8 txt[12];
	int ret1, ret2;
	
   	// output values to USART
   	txt[0] = (TimeRead->day / 10) + 48;
   	txt[1] = (TimeRead->day % 10) + 48;
   	txt[2] = '/';
   	txt[3] = (TimeRead->month / 10) + 48;
   	txt[4] = (TimeRead->month % 10) + 48;
   	txt[5] = '/';
   	txt[6] = ((TimeRead->year % 100) / 10) + 48;
   	txt[7] = (TimeRead->year % 10)  + 48;
   	txt[8] = ' ';
   	ret1 = EE_uart_write_buffer(txt,9);
	if(ret1 < 0) return ret1;
	
   	txt[0] = (TimeRead->hours / 10) + 48;
   	txt[1] = (TimeRead->hours % 10) + 48;
   	txt[2] = ':';
   	txt[3] = (TimeRead->minutes / 10) + 48;
   	txt[4] = (TimeRead->minutes % 10) + 48;
   	txt[5] = ':';
   	txt[6] = (TimeRead->seconds / 10) + 48;
   	txt[7] = (TimeRead->seconds % 10) + 48;
   	txt[8] = ':';
   	txt[9] = (TimeRead->hundreds_of_seconds / 10) + 48;
   	txt[10] = (TimeRead->hundreds_of_seconds % 10) + 48;;
   	txt[11] = '\n';
   	ret2 = EE_uart_write_buffer(txt,12);
	if(ret2 < 0) return ret2;
	
   	return ret1+ret2;
}


