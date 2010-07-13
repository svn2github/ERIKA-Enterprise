/*
  Name: main.c
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: UWL device test.
*/

#include "uwl_ieee802154.h"	
#include "kal/uwl_kal.h"	
#include "ee.h"
#include "console_serial.h"
#include <MicoMacros.h>
#include <string.h>
#include <stdio.h>

/******************************************************************************/
/*                         Constant Definitions                               */
/******************************************************************************/
#define TEST_PANID			0x000A
#define TEST_COORD_ADDR		0x0001
#define TEST_CHANNEL		0x0D
#define TEST_BO				6
#define TEST_SO				6
#define TEST_DEVICE_ADDR	0x0028

#define MAX_PCK_LEN			127
#define USE_GTS				1
#define DO_NOT_USE_GTS		0

#define MSG_LEN		90

#define EE_led_off() 	EE_misc_gpio_write_bit_data(0, EE_DL3_BIT)
#define EE_led_on() 	EE_misc_gpio_write_bit_data(1, EE_DL3_BIT)

void system_timer_callback(void)
{
	CounterTick(TASK_COUNTER);
}

int print_string(char* s)
{
	return EE_uart_send_buffer((EE_UINT8*)s, strlen(s));
}

/******************************************************************************/
/*                                  TASKs                                     */
/******************************************************************************/
TASK(SEND_TASK)
{
	EE_UINT8 msg[MSG_LEN];
	static int sw = 0;
	int i = 0;
	
	EE_led_on();
	
	for (i = 0; i < MSG_LEN; i++) {
		msg[i] = i;
	}
	
	// CAP send
	sw ^= 1;
	if (sw){
		print_string("uwl_simple154_send without GTS \n");
		uwl_simple154_send(msg, MSG_LEN, TEST_COORD_ADDR, DO_NOT_USE_GTS);
		
	}
	else {
		print_string("uwl_simple154_send with GTS \n");
		// GTS send
		uwl_simple154_send(msg, 10, TEST_COORD_ADDR, USE_GTS);
		
	}

	EE_led_off();
}

/* Main */
int main(void)
{
	char debug_string[128];
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
		for (;;) 
			; // Fatal Error
	console_init(0, cons);
	if (console_open(0) < 0)
		for (;;) 
			; // Fatal Error
	print_string("Serial console configuration...Done!\n");
	
	
	/* ------------------- */
	/* Enable IRQ */
	/* ------------------- */
	EE_mico32_enableIRQ();
	
	/* ------------------- */
	/* DEVICE init */
	/* ------------------- */
	print_string("\nDevice init...");
	EE_led_off();
	retv = uwl_simple154_init_device(TEST_DEVICE_ADDR, TEST_COORD_ADDR, TEST_PANID, TEST_CHANNEL);
	if (retv < 0) {
		print_string("Error!\n");
		sprintf(debug_string, "retv: %d\n", retv);
		print_string(debug_string);
		while (1)
			;
	} else {
		print_string("Done!\n");
		sprintf(debug_string, "retv: %d\n", retv);
		print_string(debug_string);
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


