/*
	Name: main.c
	Copyright: Evidence Srl
	Author: Dario Di Stefano
  	Description: 	UWL device test.
  					This demo shows how to configure a device node in a
  					ZIGBEE net. The stack si based on the uWIRELESS library.
  					The demo requires a RS232 serial connection with a 115200 bps,8N1 configuration.
					The demo requires a SPI connection with the MRF24J40MA/MB device. 
*/

#include "uwl_ieee802154.h"	
#include "kal/uwl_kal.h"	
#include "ee.h"
#include "console_serial.h"
#include <MicoMacros.h>
/* Other libraries */
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

/* Constant Definitions */
#define TEST_PANID			0x000A
#define TEST_COORD_ADDR		0x0001
#define TEST_CHANNEL		0x0D
#define TEST_BO				6
#define TEST_SO				6
#define TEST_DEVICE_ADDR	0x0028
#define MAX_PCK_LEN			127
#define USE_GTS				1
#define DO_NOT_USE_GTS		0
#define MSG_LEN				90

void system_timer_callback(void)
{
	CounterTick(TASK_COUNTER);
}

/* TASKs */
TASK(SEND_TASK)
{
	EE_UINT8 msg[MSG_LEN];
	static int sw = 0;
	int i = 0;
	
	for (i = 0; i < MSG_LEN; i++) {
		msg[i] = i;
	}
	
	// CAP send
	sw ^= 1;
	if (sw){
		myprintf("uwl_simple154_send without GTS \n");
		uwl_simple154_send(msg, MSG_LEN, TEST_COORD_ADDR, DO_NOT_USE_GTS);
		
	}
	else {
		myprintf("uwl_simple154_send with GTS \n");
		// GTS send
		uwl_simple154_send(msg, 10, TEST_COORD_ADDR, USE_GTS);
		
	}
}

/* Main */
int main(void)
{
	EE_INT8 retv;
	
	/* ------------ */
	/* Disable IRQ  */
	/* ------------ */
	EE_mico32_disableIRQ();
	mico32_disable_irq_mask(0xFFFFFFFF);
	
	/* ------------------- */
	/* UART configuration  */
	/* ------------------- */
	EE_uart_config(115200, EE_UART_BIT8_NO | EE_UART_BIT_STOP_1);
	EE_uart_set_ISR_mode(EE_UART_POLLING | EE_UART_RXTX_BLOCK);
	
	
	/* ----------------- */
	/* CONSOLE */
	/* ----------------- */
	/* Serial Console configuration */
	console_descriptor_t *cons;    
	cons = console_serial_config(1, 115200, CONSOLE_SERIAL_FLAG_BIT8_NO | CONSOLE_SERIAL_FLAG_BIT_STOP1);
	if (!cons)
	{
		die(1);
		for (;;) 
			; // Fatal Error
	}
	console_init(0, cons);
	if (console_open(0) < 0)
	{
		die(2);
		for (;;) 
			; // Fatal Error
	}
	myprintf("Serial console configuration...Done!\n");
	
	/* ------------------- */
	/* Enable IRQ */
	/* ------------------- */
	EE_mico32_enableIRQ();
	
	/* ------------------- */
	/* DEVICE init */
	/* ------------------- */
	myprintf("\nDevice init...");
	retv = uwl_simple154_init_device(TEST_DEVICE_ADDR, TEST_COORD_ADDR, TEST_PANID, TEST_CHANNEL);
	if (retv < 0) {
		die(retv);
		while (1)
			;
	} else {
		myprintf("Done!\n");
	}
	
	/* ------------------- */
	/* Kernel timer configuration */
	/* ------------------- */
	EE_timer_set_ISR_callback(system_timer_callback);
	EE_timer_init(MICROSECONDS_TO_TICKS(1000), MICO32_TIMER_CONTROL_INT_BIT_MASK | MICO32_TIMER_CONTROL_CONT_BIT_MASK);
	
	/* ------------------- */
	/* Background activity */
	/* ------------------- */
	SetRelAlarm(TASK_ALARM, 1000, 2500);
	EE_timer_on();
	
	/* Forever loop: background activities (if any) should go here */
	for (;;) {

	}
	return 0;
}


