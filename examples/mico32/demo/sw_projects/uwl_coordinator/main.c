/*
  Name: main.c
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: UWL coordinator test.
*/

#include "uwl_ieee802154.h"	
#include "kal/uwl_kal.h"	
#include "ee.h"
#include <MicoMacros.h>
#include <string.h>
#include <stdio.h>

#define EE_led_off() EE_misc_gpio_write_bit_data(0, EE_DL3_BIT)
#define EE_led_on() EE_misc_gpio_write_bit_data(1, EE_DL3_BIT)

#define TEST_PANID			0x000A
#define TEST_COORD_ADDR		0x0001
#define TEST_CHANNEL		0x0D
#define TEST_BO				6
#define TEST_SO				6
#define MAX_PCK_LEN			127
#define USE_GTS				1
#define DO_NOT_USE_GTS		0

static EE_UINT8 last_msg[MAX_PCK_LEN];
static EE_UINT8 last_msg_len = 0;
static EE_UINT16 last_sender = 0;

int print_string(char* s)
{
	return EE_uart_send_buffer((EE_UINT8*)s, strlen(s));
}

/* RX callback */
void rx_callback(EE_INT8 err, EE_UINT8* msg, EE_UINT8 len, EE_UINT16 addr)
{
	int i = 0;
	char s[64];
	
	EE_led_on();
	
	sprintf(s,"rx_cbk!\n err: %d, len: %d, addr: %d\n", err, len, addr);
	print_string(s);
	
	if (len > MAX_PCK_LEN)
		len = MAX_PCK_LEN;
	for (i = 0; i < len; i++) {
		last_msg[i] = msg[i];
		sprintf(s, "msg[%d]:0x%02x  ", i, msg[i]);
		print_string(s);
	}
	sprintf(s, "\n");
	print_string(s);
	
	last_msg_len = len;
	last_sender = addr;
	
	ActivateTask(myTask);
}

/* myTask */
TASK(myTask)
{
	EE_led_on();
	uwl_simple154_send(last_msg, last_msg_len, last_sender, DO_NOT_USE_GTS);
	EE_led_off();
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
	char s[128];
	int ret;
	uwl_simple154_init_coordinator(	TEST_COORD_ADDR, TEST_PANID,
									TEST_CHANNEL, TEST_BO, TEST_SO);
	uwl_simple154_set_rx_callback(&rx_callback);
	ret = uwl_simple154_gts_add(0x0022, 2, 0);
	sprintf(s, "0x0022 ret: %d!\n", ret);
	print_string(s);
	ret = uwl_simple154_gts_add(0x0023, 2, 0);
	sprintf(s, "0x0023 ret: %d!\n", ret);
	print_string(s);
	ret = uwl_simple154_gts_add(0x0024, 2, 0);
	sprintf(s, "0x0024 ret: %d!\n", ret);
	print_string(s);
	ret = uwl_simple154_gts_add(0x0025, 2, 0);
	sprintf(s, "0x0025 ret: %d!\n", ret);
	print_string(s);
	ret = uwl_simple154_gts_add(0x0026, 2, 0);
	sprintf(s, "0x0026 ret: %d!\n", ret);
	print_string(s);
	ret = uwl_simple154_gts_add(0x0027, 2, 0);
	sprintf(s, "0x0027 ret: %d!\n", ret);
	print_string(s);
	ret = uwl_simple154_gts_add(0x0028, 2, 0);
	sprintf(s, "0x0028 ret: %d!\n", ret);
	print_string(s);
	sprintf(s, "Init coordinator...Done!\n");
	print_string(s);
	
	/* ------------------- */
	/* Background activity */
	/* ------------------- */
	while(1)
		;
	
	return 0;
}


