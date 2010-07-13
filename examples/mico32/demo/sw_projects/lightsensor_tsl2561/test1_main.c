/*
  Name: test1_main.c
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: Light sensor test.
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
#include <stdio.h>
#include <stdarg.h>

void myprintf(const char* format, ...);

int EE_lightsensor_config(void)
{
	int ret;
	ret = tsl2561t_init(SELECT_ADDRESS_VDD);
	if(ret < 0)
	{
		myprintf("tsl2561t_init error!\n");
		while(1);
	}
	ret = tsl2561t_power_on(DEVICE_ADDRESS_VDD);
	if(ret!=TSL2516T_NO_ERROR)
	{
		myprintf("tsl2561t_power error!\n");
		while(1);
	}
	ret = tsl2561t_set_configuration(DEVICE_ADDRESS_VDD, TSL2561T_TIMING, 0);
	if(ret!=TSL2516T_NO_ERROR)
	{
		myprintf("tsl2561t_set error!\n");
		while(1);
	}
	myprintf("tsl2561t OK!\n");
	return TSL2516T_NO_ERROR;
}

uint32_t EE_lightsensor_read(void)
{
	uint32_t lux;
	tsl2561t_read_lux(DEVICE_ADDRESS_VDD, &lux);
	return lux;
}

void system_timer_callback(void)
{
	CounterTick(myCounter);
}

/* demo task */
TASK(myTask)
{
	static int read_count = 0;
    uint32_t light;
    
    read_count++;
    
    light = EE_lightsensor_read();
   	myprintf("%d: %d\n", read_count, light);
}


/*
 * MAIN TASK
 */
int main(void)
{
	/* ------------ */
	/* Disable IRQ  */
	/* ------------ */
	EE_mico32_disableIRQ();
	
	/* ------------------- */
	/* UART configuration */
	/* ------------------- */
	EE_uart_config(115200, EE_UART_BIT8_NO | EE_UART_BIT_STOP_1);
	EE_uart_set_ISR_mode(EE_UART_POLLING | EE_UART_RXTX_BLOCK);
	
    /* ------------------- */
    /* Light-sensor configuration */
    /* ------------------- */
    int ret;
    ret = EE_lightsensor_config();
    if (ret < 0) 
    {
       myprintf("Error while configuring light sensor");
        while(1);
    }     
    
    /* ------------------- */
	/* Enable IRQ */
	/* ------------------- */
	EE_mico32_enableIRQ();
	
    /* ------------------- */
	/* Kernel timer configuration */
	/* ------------------- */
	EE_timer_set_ISR_callback(system_timer_callback);
	EE_timer_init(MICROSECONDS_TO_TICKS(1000), MICO32_TIMER_CONTROL_INT_BIT_MASK | MICO32_TIMER_CONTROL_CONT_BIT_MASK | MICO32_TIMER_CONTROL_STOP_BIT_MASK);
	
	/* ------------------- */
	/* Background activity */
	/* ------------------- */
	SetRelAlarm(myAlarm, 500, 500);
	EE_timer_on();
	
	/* Forever loop: background activities (if any) should go here */
	while(1)
		;
		
	return 0;
    
}

#define MAX_CHARS 128
void myprintf(const char* format, ...)
{
	char str[MAX_CHARS];
	
	va_list args;
	va_start( args, format );
	vsnprintf(str, MAX_CHARS, format, args);
	va_end( args );
	EE_uart_send_buffer((EE_UINT8*)str, strlen(str));
}

