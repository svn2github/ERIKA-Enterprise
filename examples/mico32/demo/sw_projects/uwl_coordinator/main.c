/*
	Name: main.c
	Copyright: Evidence Srl
	Author: Dario Di Stefano
  	Description: 	UWL coordinator test.
  					This demo shows how to configure a coordinator node in a
  					ZIGBEE net. The stack si based on the uWIRELESS library.
  					The demo requires a RS232 serial connection with a 115200 bps,8N1 configuration.
					The demo requires a SPI connection with the MRF24J40MA/MB device. 
*/


#include "ee.h"
#include "uwl_ieee802154.h"	
#include "kal/uwl_kal.h"	
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

/* Constants */
#define TEST_PANID			0x000A
#define TEST_COORD_ADDR		0x0001
#define TEST_CHANNEL		0x0D
#define TEST_BO				6
#define TEST_SO				6
#define MAX_PCK_LEN			127
#define USE_GTS				1
#define DO_NOT_USE_GTS		0

/* Global variables */
static EE_UINT8 last_msg[MAX_PCK_LEN];
static EE_UINT8 last_msg_len = 0;
static EE_UINT16 last_sender = 0;

/* RX callback */
void rx_callback(EE_INT8 err, EE_UINT8* msg, EE_UINT8 len, EE_UINT16 addr)
{
	int i = 0;
	
	myprintf("rx_cbk!\n err: %d, len: %d, addr: %d\n", err, len, addr);
	if (len > MAX_PCK_LEN)
		len = MAX_PCK_LEN;
	for (i = 0; i < len; i++) {
		last_msg[i] = msg[i];
		myprintf("msg[%d]:0x%02x  ", i, msg[i]);
	}
	myprintf("\n");
	last_msg_len = len;
	last_sender = addr;
	ActivateTask(myTask);
}

/* myTask */
TASK(myTask)
{
	uwl_simple154_send(last_msg, last_msg_len, last_sender, DO_NOT_USE_GTS);
}

/* Main */
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

	/* ---------- */
	/* Enable IRQ */
	/* ---------- */
	EE_mico32_enableIRQ();
	
	/* -------------------------- */
	/* Coordinator initialization */
	/* -------------------------- */
	int ret;
	uwl_simple154_init_coordinator(	TEST_COORD_ADDR, TEST_PANID,
									TEST_CHANNEL, TEST_BO, TEST_SO);
	uwl_simple154_set_rx_callback(&rx_callback);
	ret = uwl_simple154_gts_add(0x0022, 2, 0);
	myprintf("0x0022 ret: %d!\n", ret);
	ret = uwl_simple154_gts_add(0x0023, 2, 0);
	myprintf("0x0023 ret: %d!\n", ret);
	ret = uwl_simple154_gts_add(0x0024, 2, 0);
	myprintf("0x0024 ret: %d!\n", ret);
	ret = uwl_simple154_gts_add(0x0025, 2, 0);
	myprintf("0x0025 ret: %d!\n", ret);
	ret = uwl_simple154_gts_add(0x0026, 2, 0);
	myprintf("0x0026 ret: %d!\n", ret);
	ret = uwl_simple154_gts_add(0x0027, 2, 0);
	myprintf("0x0027 ret: %d!\n", ret);
	ret = uwl_simple154_gts_add(0x0028, 2, 0);
	myprintf("0x0028 ret: %d!\n", ret);
	myprintf("Init coordinator...Done!\n");
	
	/* ------------------- */
	/* Background activity */
	/* ------------------- */
	while(1)
		;
	
	return 0;
}


