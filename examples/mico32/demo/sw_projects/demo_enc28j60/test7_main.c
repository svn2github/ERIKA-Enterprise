/*
  Name: test7_main.c
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: LWIP udp test.
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
#include "test7.h"

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
/* UDP buffers used to store udp packets payloads */
EE_buffer UDP_rx_buffer;
EE_buffer UDP_tx_buffer;
EE_UINT8 udp_rx_data[UDP_BUFFER_SIZE*UDP_PAYLOAD_PKT_SIZE];
EE_UINT8 udp_tx_data[UDP_BUFFER_SIZE*UDP_PAYLOAD_PKT_SIZE];

/* ----------------------------------------------------------- */
/* Callbacks and tasks */
/* ----------------------------------------------------------- */
/* UDP rx handler */
void udp_rx_handler(void *arg, struct udp_pcb *upcb, struct pbuf *p, struct ip_addr *addr, u16_t port);
void load_buffer(EE_buffer *buf, struct pbuf *p);
u8_t msg[UDP_PAYLOAD_PKT_SIZE];

/* myTask1 */
TASK(myTask1)
{
	GetResource(LwipMutex);
	
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
    if(!EE_buffer_isempty(&UDP_tx_buffer))
    {
        /* if the udp socket is connected... */
        if (my_udp_socket->remote_port != (uint16_t)0)  
        {
            /* Extract one packet */
            EE_buffer_getmsg(&UDP_tx_buffer, (EE_UINT8*)msg);
            struct pbuf* p = pbuf_alloc(PBUF_TRANSPORT, UDP_PAYLOAD_PKT_SIZE, PBUF_REF);
            p->payload = msg;
            if (p != (struct pbuf *)0) 
            {
                myprintf("\nTransmission in progress...\n");   
                print_pbuf("tx_p", p);    
                /* Send the extracted packet */
                udp_send(my_udp_socket, p);
                pbuf_free(p); 
            }
        }
    }
    /* --------- */
    
	ReleaseResource(LwipMutex);
}

/* myTask2 */
TASK(myTask2)
{
    BYTE rx_v[UDP_PAYLOAD_PKT_SIZE];
    BYTE tx_v[UDP_PAYLOAD_PKT_SIZE];
    int i;
    
    /* Receive one UDP packet (loaded in the tx buffer by the handler...) */
    if(UDP_receive(rx_v)>=0)
    {
    	print_array("rx_v", rx_v, UDP_PAYLOAD_PKT_SIZE);
        for(i=0; i<UDP_PAYLOAD_PKT_SIZE; i++)
            tx_v[i] = rx_v[i] + 5; /* dummy increment */
        /* Send only if one packet has been received (to see proper increment...) */
        UDP_send(tx_v);
    }
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
    EE_buffer_init(&UDP_rx_buffer, UDP_PAYLOAD_PKT_SIZE, UDP_BUFFER_SIZE, udp_rx_data);
    EE_buffer_init(&UDP_tx_buffer, UDP_PAYLOAD_PKT_SIZE, UDP_BUFFER_SIZE, udp_tx_data);
    my_udp_socket = udp_new();  /* Create an udp socket */
    myprintf("udp_new!\n");
    ret = udp_bind(my_udp_socket, &my_ipaddr, MY_PORT); /* Bind the udp socket */ 
    myprintf("udp_bind return value: %d\n", ret);
    udp_recv(my_udp_socket, &udp_rx_handler, 0);        /* Set the rx callback for udp packets */ 
    myprintf("udp_recv!\n");
    
    /* ------------------- */
    /* Start demo */
    /* ------------------- */
    turn_on_led();
    SetRelAlarm(myAlarm1, 10, 100);
    SetRelAlarm(myAlarm2, 20, 1000);
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
    /* Put the udp packet in the rx buffer */
    load_buffer(&UDP_rx_buffer, p);
    /* don't leak the pbuf! */
    pbuf_free(p);	
}


void system_timer_callback(void)
{
    /* count the interrupts, waking up expired alarms */
    CounterTick(myCounter);
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

int UDP_receive(BYTE* rxv)
{
    if(EE_buffer_getmsg(&UDP_rx_buffer, (EE_UINT8*)rxv)==EE_BUF_OK)
        return 1;
    else
        return -1;
}

int UDP_send(BYTE* txv)
{
    EE_buffer_putmsg(&UDP_tx_buffer, (EE_UINT8*)txv);
    return 1;
}

void load_buffer(EE_buffer *buf, struct pbuf *p)
{
	BYTE rx_payload[128];
	struct pbuf *q;
	int i, j=0;
	
    for(q = p; q != NULL; q = q->next) 
    {
         for(i=0; i<(q->len); i++)
         {  
            rx_payload[j] = ((u8_t*)q->payload)[i]; /* load data in rx vector */
            j++;
         }
    }
    EE_buffer_putmsg(buf, (EE_UINT8*)rx_payload);
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

