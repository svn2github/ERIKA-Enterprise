/*
  Name: test1_main.c
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: RTC test.
*/

/* RT-Kernel */
#include <ee.h>
/* Platform description */
#include <system_conf.h>
/* Erika Mico32 interrupts */
#include <cpu/mico32/inc/ee_irq.h>
/* Lattice components */
#include <MicoMacros.h>
#include <string.h>

#define turn_on_led() 	EE_misc_gpio_write_bit_data(1,0)
#define turn_off_led() 	EE_misc_gpio_write_bit_data(0,0)

int rtc_display_time(TTime *TimeRead);

int print_string(const char *s)
{
	return EE_uart_send_buffer(s,strlen(s));
}

TASK(myTask)
{
	int ret;
	TTime now;
	    
	ret = EE_rtc_read_time(&now);
	if(ret == EE_I2C_OK)
	{
		print_string("Time:\n");
		ret = rtc_display_time(&now); 
		if(ret<0)
		{
			print_string("I2C error in rtc_display_time\n");
			while(1);
		}
  	}
  	else
  	{
		print_string("EE_rtc_read_time: Error\n");
  		while(1);
  	}

}

void system_timer_callback(void)
{
	/* count the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}

/*
 * MAIN TASK
 */
int main(void)
{
	/* ------------------- */
	/* Disable IRQ         */
	/* ------------------- */
	EE_mico32_disableIRQ();
	
	/* -------------------------- */
	/* Uart configuration         */
	/* -------------------------- */
	EE_uart_config(115200, EE_UART_BIT8_NO | EE_UART_BIT_STOP_1);
	EE_uart_set_ISR_mode(EE_UART_POLLING | EE_UART_RXTX_BLOCK); // polling, blocking mode  
	
	/* -------------------------- */
	/* RTC configuration         */
	/* -------------------------- */
	int ret;
	TTime tt;
	/* I2C configuration */
	EE_rtc_config(100000, 0);
	/* Write Time in RTC */
	tt.year    = 10;    				// 2010 (offset from 2000)
	tt.month   = 4;
	tt.day     = 1;
	tt.hours   = 10;
	tt.minutes = 43;
	tt.seconds = 0;
	tt.hundredths = 0;
	ret = EE_rtc_write_time(&tt);
	if(ret != EE_I2C_OK)
	{
		print_string("EE_rtc_write_time: Error\n");
		while(1);
	}

	/* ------------------- */
	/* Kernel timer configuration */
	/* ------------------- */
	EE_timer_set_ISR_callback(system_timer_callback);
	EE_timer_init(MILLISECONDS_TO_TICKS(1), MICO32_TIMER_CONTROL_INT_BIT_MASK | MICO32_TIMER_CONTROL_CONT_BIT_MASK | MICO32_TIMER_CONTROL_STOP_BIT_MASK);
	
	/* ------------------- */
	/* Enable IRQ         */
	/* ------------------- */
	EE_mico32_enableIRQ();
	
	/* ------------------- */
	/* Background activity */
	/* ------------------- */
	SetRelAlarm(myAlarm, 1000, 500);
	EE_timer_on();

	while(1)
		;
		
    return 0;
}

/* ------------------------------------------------------- */
/* Other RTC functions                                     */
/* ------------------------------------------------------- */

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
  	ret1 = EE_uart_send_buffer(txt,9);
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
  	txt[9] = (TimeRead->hundredths / 10) + 48;
  	txt[10] = (TimeRead->hundredths % 10) + 48;;
  	txt[11] = '\n';
  	ret2 = EE_uart_send_buffer(txt,12);
	if(ret2 < 0) return ret2;
	
  	return ret1+ret2;
}





