/*
  Name: test6_main.c
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: ENC28J60 transmission/reception test (LWIP-like types)
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
#include "test6.h"
#include "lwipopts_ee.h"

/* ----------------------------------------------------------- */
/* Variables */
/* ----------------------------------------------------------- */
/* ENC28J60 demo variables */
packet test_pkt;

payload msg = {.v[0] = MSG_BYTE1, .v[1] = MSG_BYTE2, .v[2] = MSG_BYTE3, .v[3] = MSG_BYTE4};

eth_hdr ethernet_header = {
					.dest = { 	.addr[0] = REMOTE_MAC_BYTE1, .addr[1] = REMOTE_MAC_BYTE2, .addr[2] = REMOTE_MAC_BYTE3, 
								.addr[3] = REMOTE_MAC_BYTE4, .addr[4] = REMOTE_MAC_BYTE5, .addr[5] = REMOTE_MAC_BYTE6},
  					.src = { 	.addr[0] = MY_DEFAULT_MAC_BYTE1, .addr[1] = MY_DEFAULT_MAC_BYTE2, .addr[2] = MY_DEFAULT_MAC_BYTE3, 
								.addr[3] = MY_DEFAULT_MAC_BYTE4, .addr[4] = MY_DEFAULT_MAC_BYTE5, .addr[5] = MY_DEFAULT_MAC_BYTE6},
  					.type = ETHTYPE_IP };

udp_hdr udp_header = {
					.src = myPort,
					.dest = remotePort,
					.len = UDP_LEN,
					.chksum = UDP_CHKSUM };
					
ip_hdr ip_header = {
  					._v_hl_tos = 0x4500,
  					._len = 0x0020,
  					._id = IP_ID,
  					._offset = 0x0000,
  					._ttl_proto = TTL_PROTO,
  					._chksum = IP_CHKSUM,
  					.src = {.addr = myIPaddress},
  					.dest = {.addr = remoteIPaddress} };
  					
u16_t header_plus_len = sizeof(ip_header) + sizeof(udp_header) + sizeof(payload) + sizeof(ethernet_header); 

/* ----------------------------------------------------------- */
/* Functions */
/* ----------------------------------------------------------- */
/* myTask1 */
TASK(myTask1)
{
	BYTE udp_data[128];
	int pktlen;
	
	/* Reception */
	if(EE_enc28j60_pending_interrupt())
	{
		print_string("interrupt signal!\n");
		print_val("eir: 0x%x\n", ReadETHReg(EIR).Val);
		print_string("Reception in progress...\n");
		pktlen = enc28j60_receive(udp_data);
		print_val("eir: 0x%x\n", ReadETHReg(EIR).Val);
	}
	else
	{
		print_string("no interrupt!\n");
	}
		
	/* Transmission */
	print_string("Transmission in progress...\n");
	enc28j60_send((BYTE*)&test_pkt, sizeof(test_pkt));
}

/* myTask2 */
TASK(myTask2)
{
	// void
}

/* MAIN (Background task) */
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
	EE_uart_set_ISR_mode(EE_UART_POLLING | EE_UART_RXTX_BLOCK);   
	
	/* ------------------- */
	/* Kernel timer configuration */
	/* ------------------- */
	EE_timer_set_ISR_callback(system_timer_callback);
	EE_timer_init(MILLISECONDS_TO_TICKS(1), MICO32_TIMER_CONTROL_INT_BIT_MASK | MICO32_TIMER_CONTROL_CONT_BIT_MASK | MICO32_TIMER_CONTROL_STOP_BIT_MASK);
	
	/* ------------------- */
	/* Enable IRQ         */
	/* ------------------- */
	EE_mico32_enableIRQ();
	
	/* ------------------------ */
	/* MAC layer initialization */
	/* ------------------------ */
	print_string("\n\n\nDevice configuration in progress...");
	EE_enc28j60_init();
	turn_on_led();
	print_string("Done!\n\n\n");
	
	/* Packet initialization */
	int i,j=0;
	for(i = j; i<(SIZE_OF_ETH_HEADER + j); i++)
		test_pkt.v[i] = ((u8_t*)&ethernet_header)[i-j];
	j = i; 
	for(i = j; i<(SIZE_OF_IP_HEADER + j); i++)
		test_pkt.v[i] = ((u8_t*)&ip_header)[i-j];
	j = i; 
	for(i = j; i<(SIZE_OF_UDP_HEADER + j); i++)
		test_pkt.v[i] = ((u8_t*)&udp_header)[i-j];
	j = i; 
	for(i = j; i<(SIZE_OF_PAYLOAD + j); i++)
		test_pkt.v[i] = ((u8_t*)&msg)[i-j];
	/* Packet print */
	char str[128];
	sprintf(str, "\nsizeof(test_pkt) = %d\n", sizeof(packet));
	print_string(str);
	sprintf(str, "header_plus_len = %d\n", header_plus_len);
	print_string(str);
	for(i=0; i<sizeof(test_pkt); i++)
	{
		sprintf(str, "pkt[%d]=0x%x  ", i, ((BYTE *)&test_pkt)[i]);
		print_string(str);
	}
	
	/* ------------------- */
	/* Background activity */
	/* ------------------- */
	SetRelAlarm(myAlarm1, 10, 100);
	SetRelAlarm(myAlarm2, 20, 1000);
	EE_timer_on();
		
	while(1)
		;
		
    return 0;
}

/* ---------------------- */
/* User functions */
/* ---------------------- */
void system_timer_callback(void)
{
	/* count the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}

int print_string(const char *s)
{
	return EE_uart_send_buffer((EE_UINT8*)s,strlen(s));
}

void print_val(char* s, int val)
{
	char str[64];
	sprintf(str, s, val);
	print_string(str);
}

void print_vals(char* s, int val1, int val2)
{
	char str[64];
	sprintf(str, s, val1, val2);
	print_string(str);
}

void enc28j60_send(BYTE* pkt, int len)
{
	/* Transmission */
	print_string("\nstart transmission\n");
	EE_enc28j60_transfer_init();
	EE_enc28j60_write(pkt, len);
	EE_enc28j60_signal(len);
	print_string("end transmission\n");
}

int enc28j60_receive(BYTE* udp_data)
{
	int rb,i;
	BYTE packet_count = 0;
	WORD len = 0; 
	
	/* Reception */
	print_string("\nstart reception\n");
	if(EE_enc28j60_read_info(&packet_count, &len)>=0)
	{
		print_val("pcnt: %d\n", packet_count);
		print_val("len: %d\n", len);
		rb = EE_enc28j60_read(udp_data, len);
		for(i=0; i<len; i++)
			print_vals("data[%d]:0x%x  ", i, udp_data[i]);
		EE_enc28j60_ack();
	}
	print_string("end reception\n");
	return len;
}

