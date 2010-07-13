/*
  Name: test10_main.c
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: LWIP udp test (time check).
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
/* LWIP */
#include "ee_lwip.h"
/* Utilities */
#include "test10.h"
#include "MicoUtils.h"

/* ----------------------------------------------------------- */
/* Macros */
/* ----------------------------------------------------------- */
#define MY_PORT						(9760)
#define MY_IPADDR_BYTE1 			(192)
#define MY_IPADDR_BYTE2 			(168)
#define MY_IPADDR_BYTE3 			(0)
#define MY_IPADDR_BYTE4 			(2)
#define MY_NETMASK_BYTE1 			(255)
#define MY_NETMASK_BYTE2 			(255)
#define MY_NETMASK_BYTE3 			(255)
#define MY_NETMASK_BYTE4 			(0)
#define MY_GATEWAY_ADDR_BYTE1 		(192)
#define MY_GATEWAY_ADDR_BYTE2 		(168)
#define MY_GATEWAY_ADDR_BYTE3 		(0)
#define MY_GATEWAY_ADDR_BYTE4 		(10)
#define MY_ETHERNETIF_MAC_BYTE1		(0x00)
#define MY_ETHERNETIF_MAC_BYTE2		(0x04)
#define MY_ETHERNETIF_MAC_BYTE3		(0xA3)
#define MY_ETHERNETIF_MAC_BYTE4		(0x00)
#define MY_ETHERNETIF_MAC_BYTE5		(0x00)
#define MY_ETHERNETIF_MAC_BYTE6		(0x00)

/* ----------------------------------------------------------- */
/* Demo Variables */
/* ----------------------------------------------------------- */
/* UDP socket used in this demo */
struct udp_pcb* my_udp_socket;

/* ----------------------------------------------------------- */
/* Callbacks and tasks */
/* ----------------------------------------------------------- */
/* UDP rx handler */
void udp_rx_handler(void *arg, struct udp_pcb *upcb, struct pbuf *p, struct ip_addr *addr, u16_t port);
u8_t msg[UDP_PAYLOAD_PKT_SIZE];
struct pbuf *tx_p;

#define MAXIMUM_PAYLOAD 1456
#define die(a)			tsprintf("\nError! code: %d\n", a)

uint32_t t1,t2;

void comm_write(const void *buf, uint32_t len)
{
    struct pbuf *out_pb;
    const uint8_t *p = buf;
    uint32_t clen;
    err_t ret;
    int counter=0;

    GetResource(LwipMutex);
    out_pb = pbuf_alloc(PBUF_TRANSPORT, MAXIMUM_PAYLOAD, PBUF_REF);
    ReleaseResource(LwipMutex);
    if (0 == out_pb)
        die(44);
    while (len > 0) {
        GetResource(LwipMutex);
        if (len > MAXIMUM_PAYLOAD) {
            clen = MAXIMUM_PAYLOAD;
        } else {
            clen = len;
            pbuf_realloc(out_pb, len);
        }
        out_pb->payload = (uint8_t *)p;
        p += clen; 
        len -= clen;
        ret = udp_send(my_udp_socket, out_pb);
        if(counter==1)
        	t1 = EE_hal_lwip_read_timer();
        else if(counter==2) {
        	t2 = EE_hal_lwip_read_timer();
        	tsprintf("t1 - t2:     %u\n", lwip_time_diff_us(t1, t2));
        	print_time_results();
        	EE_lwip_reset_timestamp();
        }
        ReleaseResource(LwipMutex);
        counter++;
    }
    GetResource(LwipMutex);
    pbuf_free(out_pb);
    ReleaseResource(LwipMutex);
}

/* myTask1 */
TASK(myTask1)
{
	#if 0
    /* Reception */
    if(EE_enc28j60_pending_interrupt())
    {
        myprintf("\ninterrupt signal! Reception in progress...\n");
        /* Elaborate the received packet */
        ethernetif_input(&EE_lwip_netif);
    }
    /* --------- */
    #endif
    
    /* Transmission */
    #if 1   
    if (my_udp_socket->remote_port != (uint16_t)0)  
	{ 
	    comm_write((const void*)SDRAM_BASE_ADDRESS, 8000); 
	    while(1);
	}
	#else
    /* if the udp socket is connected... */
    if (my_udp_socket->remote_port != (uint16_t)0)  
	{
		myprintf("\nTransmission in progress...\n");  
		int i;
		for(i=0; i<5; i++)
		{ 
			tx_p = pbuf_new(msg, UDP_PAYLOAD_PKT_SIZE); 	// we need a new pbuf without headers...
			myprintf("tx n: %d\n", i);
			print_pbuf("tx_p", tx_p);	
			/* Send the extracted packet */
			udp_send(my_udp_socket, tx_p);
			pbuf_free(tx_p);								// tx_p is changed (headers added) so we need free tx_p...
			MicoSleepMilliSecs(10);
			print_time_results();
			EE_lwip_reset_timestamp();
		}
		while(1);
	}
	#endif
    /* --------- */
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
    EE_timer_init(MILLISECONDS_TO_TICKS(1), MICO32_TIMER_CONTROL_INT_BIT_MASK | MICO32_TIMER_CONTROL_CONT_BIT_MASK);
    
    /* ------------------- */
    /* Enable IRQ         */
    /* ------------------- */
    EE_mico32_enableIRQ();
    
    /* ------------------- */
    /* LWIP configuration  */
    /* ------------------- */
    myprintf("\n\n\nLWIP configuration in progress...");
    struct ip_addr my_ipaddr, netmask, gw;
    struct eth_addr my_ethaddr;
	IP4_ADDR(&my_ipaddr, MY_IPADDR_BYTE1, MY_IPADDR_BYTE2, MY_IPADDR_BYTE3, MY_IPADDR_BYTE4);
	IP4_ADDR(&netmask, MY_NETMASK_BYTE1, MY_NETMASK_BYTE2, MY_NETMASK_BYTE3, MY_NETMASK_BYTE4);
	IP4_ADDR(&gw, MY_GATEWAY_ADDR_BYTE1, MY_GATEWAY_ADDR_BYTE2, MY_GATEWAY_ADDR_BYTE3, MY_GATEWAY_ADDR_BYTE4);
	ETH_ADDR(&my_ethaddr, MY_ETHERNETIF_MAC_BYTE1, MY_ETHERNETIF_MAC_BYTE2, MY_ETHERNETIF_MAC_BYTE3, 
				MY_ETHERNETIF_MAC_BYTE4, MY_ETHERNETIF_MAC_BYTE5, MY_ETHERNETIF_MAC_BYTE6);	
    EE_lwip_init(&my_ipaddr, &netmask, &gw, &my_ethaddr);
    myprintf("Done!\n");
    
    /* ------------------- */
    /* My app initialization   */
    /* ------------------- */
    err_t ret;
    my_udp_socket = udp_new();  /* Create an udp socket */
    myprintf("udp_new!\n");
    ret = udp_bind(my_udp_socket, &my_ipaddr, MY_PORT); /* Bind the udp socket */ 
    myprintf("udp_bind return value: %d\n", ret);
    udp_recv(my_udp_socket, &udp_rx_handler, 0);        /* Set the rx callback for udp packets */ 
    myprintf("udp_recv!\n");
    
    int i;
    for(i=0; i<UDP_PAYLOAD_PKT_SIZE; i++)
    	msg[i]=i;
    
    /* ------------------- */
    /* Start demo */
    /* ------------------- */
    turn_on_led();
    SetRelAlarm(myAlarm1, 10, 100);
	//SetRelAlarm(myAlarm2, 20, 1000);
    EE_timer_on();
        
    /* ------------------- */
    /* Background activity */
    /* ------------------- */
    while(1)
        ;
        
    return 0;
}

/* ###################################################################################### */

/* ---------------------- */
/* User functions */
/* ---------------------- */
void udp_rx_handler(void *arg, struct udp_pcb *upcb,
                    struct pbuf *p, struct ip_addr *addr, u16_t port)
{
    myprintf("\nudp_rx_handler!\n");
    /* connect to the remote host */
    udp_connect(upcb, addr, port);               
    /* UDP received packet print */
    print_pbuf("rx_p",p);
    /* don't leak the pbuf! */
    pbuf_free(p);	
}


void system_timer_callback(void)
{
    /* count the interrupts, waking up expired alarms */
    CounterTick(myCounter);
}



//LWIP_START_ETH_OUT,
//	LWIP_START_LOWLEV_OUT, 
//	LWIP_START_UDP_SEND, 
//	LWIP_START_LOWLEV_IN,
//	LWIP_START_ETH_IN,
//	LWIP_START_UDP_INPUT,
//	LWIP_START_UDP_RX_CBK,
//	
//	LWIP_END_ETH_OUT,
//	LWIP_END_LOWLEV_OUT,
//	LWIP_END_UDP_SEND,
//	LWIP_END_LOWLEV_IN,
//	LWIP_END_ETH_IN,
//	LWIP_END_UDP_INPUT,
//	LWIP_END_UDP_RX_CBK,

void print_time_results(void)
{
	tsprintf("\n");
	
	tsprintf("Absolute time:\n");
	#if 0
	tsprintf("LWIP_START_ETH_OUT:      %u\n", EE_lwip_read_timestamp(LWIP_START_ETH_OUT));
	tsprintf("LWIP_START_LOWLEV_OUT:   %u\n", EE_lwip_read_timestamp(LWIP_START_LOWLEV_OUT));
	tsprintf("LWIP_START_UDP_SEND:     %u\n", EE_lwip_read_timestamp(LWIP_START_UDP_SEND));
	tsprintf("LWIP_START_LOWLEV_INIT:  %u\n", EE_lwip_read_timestamp(LWIP_START_LOWLEV_INIT));
	tsprintf("LWIP_START_ETH_INIT:     %u\n", EE_lwip_read_timestamp(LWIP_START_ETH_INIT));
	tsprintf("LWIP_START_LOWLEV_INPUT: %u\n", EE_lwip_read_timestamp(LWIP_START_LOWLEV_INPUT));
	tsprintf("LWIP_START_ETH_INPUT:    %u\n", EE_lwip_read_timestamp(LWIP_START_ETH_INPUT));
	tsprintf("LWIP_START_UDP_INPUT:    %u\n", EE_lwip_read_timestamp(LWIP_START_UDP_INPUT));
	tsprintf("LWIP_START_UDP_RX_CBK:   %u\n", EE_lwip_read_timestamp(LWIP_START_UDP_RX_CBK));
	tsprintf("LWIP_END_ETH_OUT:        %u\n", EE_lwip_read_timestamp(LWIP_END_ETH_OUT));
	tsprintf("LWIP_END_LOWLEV_OUT:     %u\n", EE_lwip_read_timestamp(LWIP_END_LOWLEV_OUT));
	tsprintf("LWIP_END_UDP_SEND:       %u\n", EE_lwip_read_timestamp(LWIP_END_UDP_SEND));
	tsprintf("LWIP_END_LOWLEV_INIT:    %u\n", EE_lwip_read_timestamp(LWIP_END_LOWLEV_INIT));
	tsprintf("LWIP_END_ETH_INIT:       %u\n", EE_lwip_read_timestamp(LWIP_END_ETH_INIT));
	tsprintf("LWIP_END_LOWLEV_INPUT:   %u\n", EE_lwip_read_timestamp(LWIP_END_LOWLEV_INPUT));
	tsprintf("LWIP_END_ETH_INPUT:      %u\n", EE_lwip_read_timestamp(LWIP_END_ETH_INPUT));
	tsprintf("LWIP_END_UDP_INPUT:      %u\n", EE_lwip_read_timestamp(LWIP_END_UDP_INPUT));
	tsprintf("LWIP_END_UDP_RX_CBK:     %u\n", EE_lwip_read_timestamp(LWIP_END_UDP_RX_CBK));
	#endif
	
	tsprintf("Init time:\n");
	tsprintf("LWIP_START_ETH_INIT - LWIP_END_ETH_INIT:         %u\n", lwip_time_diff_us(EE_lwip_read_timestamp(LWIP_START_ETH_INIT), EE_lwip_read_timestamp(LWIP_END_ETH_INIT)));
	tsprintf("LWIP_START_LOWLEV_INIT - LWIP_END_LOWLEV_INIT:   %u\n", lwip_time_diff_us(EE_lwip_read_timestamp(LWIP_START_LOWLEV_INIT), EE_lwip_read_timestamp(LWIP_END_LOWLEV_INIT)));
	
	tsprintf("Transmission time:\n");
	tsprintf("LWIP_START_UDP_SEND - LWIP_END_UDP_SEND:         %u\n", lwip_time_diff_us(EE_lwip_read_timestamp(LWIP_START_UDP_SEND), EE_lwip_read_timestamp(LWIP_END_UDP_SEND)));
	tsprintf("LWIP_START_ETH_OUT - LWIP_END_ETH_OUT:           %u\n", lwip_time_diff_us(EE_lwip_read_timestamp(LWIP_START_ETH_OUT), EE_lwip_read_timestamp(LWIP_END_ETH_OUT)));
	tsprintf("LWIP_START_UDP_CHECKSUM - LWIP_END_UDP_CHECKSUM: %u\n", lwip_time_diff_us(EE_lwip_read_timestamp(LWIP_START_UDP_CHECKSUM), EE_lwip_read_timestamp(LWIP_END_UDP_CHECKSUM)));
	tsprintf("LWIP_START_IP_OUTPUT - LWIP_END_IP_BEFORE_NETIF_OUTPUT:              %u\n", lwip_time_diff_us(EE_lwip_read_timestamp(LWIP_START_IP_OUTPUT), EE_lwip_read_timestamp(LWIP_END_IP_BEFORE_NETIF_OUTPUT)));
	tsprintf("LWIP_START_LOWLEV_OUT - LWIP_END_LOWLEV_OUT:     %u\n", lwip_time_diff_us(EE_lwip_read_timestamp(LWIP_START_LOWLEV_OUT), EE_lwip_read_timestamp(LWIP_END_LOWLEV_OUT)));
	tsprintf("LWIP_START_UDP_SEND_IPROUTE - LWIP_END_UDP_SEND_IPROUTE:             %u\n", lwip_time_diff_us(EE_lwip_read_timestamp(LWIP_START_UDP_SEND_IPROUTE), EE_lwip_read_timestamp(LWIP_END_UDP_SEND_IPROUTE)));
	tsprintf("LWIP_START_LOWLEV_INIT_TRANSFER - LWIP_END_LOWLEV_INIT_TRANSFER:     %u\n", lwip_time_diff_us(EE_lwip_read_timestamp(LWIP_START_LOWLEV_INIT_TRANSFER), EE_lwip_read_timestamp(LWIP_END_LOWLEV_INIT_TRANSFER)));
	tsprintf("LWIP_START_LOWLEV_WRITE - LWIP_END_LOWLEV_WRITE:                     %u\n", lwip_time_diff_us(EE_lwip_read_timestamp(LWIP_START_LOWLEV_WRITE), EE_lwip_read_timestamp(LWIP_END_LOWLEV_WRITE)));
	tsprintf("LWIP_START_LOWLEV_SIGNAL - LWIP_END_LOWLEV_SIGNAL:                   %u\n", lwip_time_diff_us(EE_lwip_read_timestamp(LWIP_START_LOWLEV_SIGNAL), EE_lwip_read_timestamp(LWIP_END_LOWLEV_SIGNAL)));
	tsprintf("ENC28J60_START_MAC_FLUSH_WAIT - ENC28J60_END_MAC_FLUSH_WAIT:         %u\n", enc28j60_time_diff_us(EE_enc28j60_read_timestamp(ENC28J60_START_MAC_FLUSH_WAIT), EE_enc28j60_read_timestamp(ENC28J60_END_MAC_FLUSH_WAIT)));
	tsprintf("ENC28J60_START_MAC_FLUSH_RETX - ENC28J60_END_MAC_FLUSH_RETX:         %u\n", enc28j60_time_diff_us(EE_enc28j60_read_timestamp(ENC28J60_START_MAC_FLUSH_RETX), EE_enc28j60_read_timestamp(ENC28J60_END_MAC_FLUSH_RETX)));
	
	tsprintf("Reception time:\n");
	tsprintf("LWIP_START_UDP_INPUT - LWIP_END_UDP_INPUT:       %u\n", lwip_time_diff_us(EE_lwip_read_timestamp(LWIP_START_UDP_INPUT), EE_lwip_read_timestamp(LWIP_END_UDP_INPUT)));
	tsprintf("LWIP_START_ETH_INPUT - LWIP_END_ETH_INPUT:       %u\n", lwip_time_diff_us(EE_lwip_read_timestamp(LWIP_START_ETH_INPUT), EE_lwip_read_timestamp(LWIP_END_ETH_INPUT)));
	tsprintf("LWIP_START_LOWLEV_INPUT - LWIP_END_LOWLEV_INPUT: %u\n", lwip_time_diff_us(EE_lwip_read_timestamp(LWIP_START_LOWLEV_INPUT), EE_lwip_read_timestamp(LWIP_END_LOWLEV_INPUT)));
	
}

#define MAX_CHARS 128
void myprintf(const char* format, ...)
{
#ifdef PRINT_ON 
	char str[MAX_CHARS];
	
	va_list args;
	va_start( args, format );
	vsnprintf(str, MAX_CHARS, format, args);
	va_end( args );
	EE_uart_send_buffer((EE_UINT8*)str, strlen(str));
#endif
}

void tsprintf(const char* format, ...)
{
	char str[MAX_CHARS];
	
	va_list args;
	va_start( args, format );
	vsnprintf(str, MAX_CHARS, format, args);
	va_end( args );
	EE_uart_send_buffer((EE_UINT8*)str, strlen(str));
}

void print_pbuf(const char *name, struct pbuf *p)
{
	#ifdef PRINT_ON 
	int i;
	struct pbuf *q;
	
	myprintf(name);
	myprintf("\np->tot_len: %d\n", p->tot_len);
	for(q = p; q != NULL; q = q->next) 
	{
		myprintf("payload: %x, len: %d\n", (unsigned int)q->payload, q->len);
		for(i=0; i<(q->len); i++)
		{
			myprintf("q->payload[%d]:%x  ", i, ((u8_t*)q->payload)[i]);
		}	
	}
	myprintf("\n");
	#endif
}

void print_array(const char *name, BYTE* vet, int len)
{
	#ifdef PRINT_ON 
	int i;
	
	for(i=0; i<len; i++)
	{
		myprintf(name);
		myprintf("[%d]:%x  ", i, vet[i]);
	}
	myprintf("\n");
	#endif
}

