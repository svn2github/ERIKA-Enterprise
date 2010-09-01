/*
  Name: test1_main.c
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: 	Light sensor test. 
  				This demo reads and prints light value.
  				The demo requires a RS232 serial connection
  				with a 115200 bps,8N1 configuration. 
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

#define MAX_CHARS 128
#define die(a)			myprintf("\nError! code: %d\n", a)

/* This function is used to send info by serial interface. */
void myprintf(const char* format, ...)
{
	char str[MAX_CHARS];
	
	va_list args;
	va_start( args, format );
	vsnprintf(str, MAX_CHARS, format, args);
	va_end( args );
	EE_uart_send_buffer((EE_UINT8*)str, strlen(str));
}

/* This function is used for light sensor configuration. */
int lightsensor_config(void)
{
	int ret;
	EE_lightsensor_init();
	ret = EE_lightsensor_power_on();
	if(ret!=TSL2516T_NO_ERROR){
		die(1);
		while(1);
	}
	ret = EE_lightsensor_set_configuration(TSL2561T_TIMING, 0);
	if(ret!=TSL2516T_NO_ERROR){
		die(2);
		while(1);
	}
	return TSL2516T_NO_ERROR;
}

/* This function is the callback function called by the timer ISR. 
 * It calls the function CounterTick used by EE for tasks periodic activation. */
void system_timer_callback(void)
{
	CounterTick(myCounter);
}

/* The Task reads light measure and sends it to PC. */
TASK(myTask)
{
	static int read_count = 0;
    uint32_t light;
    
    read_count++;
    EE_lightsensor_read_lux(&light);	// light = EE_lightsensor_read();
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
    int ret = lightsensor_config();
    if (ret < 0){
		die(3);
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

