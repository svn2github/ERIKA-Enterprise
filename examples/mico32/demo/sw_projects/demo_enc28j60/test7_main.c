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

/* LWIP */
#include "lwip/opt.h"
#include "lwip/init.h"
#include "arch/init.h"
#include "lwip/ip.h"
#include "netif/etharp.h"
#include "lwip/udp.h"
#include "hal/lwip_ethernet.h"

/* Utilities */
#include "test7.h"
//#include "lwipopts_ee.h"

/* ----------------------------------------------------------- */
/* Demo Variables */
/* ----------------------------------------------------------- */
/* Main network structure */
struct netif netif;		
/* My ethernet board data */			
struct ethernetif my_ethernetif;
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
void udp_rx_handler(void *arg, struct udp_pcb *upcb,
					struct pbuf *p, struct ip_addr *addr, u16_t port)
{
	struct pbuf *q;
	int i,j=0;
	BYTE rx_payload[128];
	
	print_string("\nudp_rx_handler!\n");
	/* connect to the remote host */
    udp_connect(upcb, addr, port);               
    /* UDP received packet print */
    LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("\np->tot_len: %d\n", p->tot_len));
    for(q = p; q != NULL; q = q->next) 
    {
		 LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("payload: %x, len: %d\n", q->payload, q->len));
		 for(i=0; i<(q->len); i++)
		 {	
		 	rx_payload[j] = ((u8_t*)q->payload)[i];
		 	j++;
			LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("q->payload[%d]:%x  ", i, ((u8_t*)q->payload)[i]));
		 }
		 
	}
	/* Put the udp packet in the rx buffer */
	EE_buffer_putmsg(&UDP_rx_buffer, (EE_UINT8*)rx_payload);
    pbuf_free(p);                                // don't leak the pbuf!
}

/* myTask1 */
TASK(myTask1)
{
	/* Reception */
	if(EE_enc28j60_pending_interrupt())
	{
		print_string("interrupt signal!\n");
		print_val("eir: 0x%x\n", ReadETHReg(EIR).Val);
		print_string("Reception in progress...\n");
		/* Elaborate the received packet */
		ethernetif_input(&netif);
		print_val("eir: 0x%x\n", ReadETHReg(EIR).Val);
	}
	else
		print_string("no interrupt!\n");
		
	/* Transmission */
	int i;
	u8_t msg[UDP_PAYLOAD_PKT_SIZE];
	if(!EE_buffer_isempty(&UDP_tx_buffer))
	{
		/* if the udp socket is connected... */
		if (my_udp_socket->remote_port != (uint16_t)0) 	
		{
			/* Extract one packet */
			EE_buffer_getmsg(&UDP_tx_buffer, (EE_UINT8*)msg);
	    	struct pbuf *p = pbuf_new(msg, UDP_PAYLOAD_PKT_SIZE);
	        if (p != (struct pbuf *)0) 
	        {
	        	print_string("Transmission in progress...\n");
	        	for(i=0; i<UDP_PAYLOAD_PKT_SIZE; i++)
					print_vals("p->payload[%d]:0x%x  ", i, ((u8_t*)p->payload)[i]);
				/* Send the extracted packet */
	        	udp_send(my_udp_socket, p);
	        }
	    }
	}
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
		for(i=0; i<UDP_PAYLOAD_PKT_SIZE; i++)
		{
			print_vals("rx_v[%d]:0x%x  ", i, rx_v[i]);
			tx_v[i] = rx_v[i] + 5;
		}
		/* Send only if one packet has been received (to see proper increment...) */
		UDP_send(tx_v);
	}
}

/* LWIP_startup_task */
void LWIP_startup_task(void)
{
	struct ip_addr my_ipaddr, netmask, gw, remote_ipaddr;
	
	/* Initialize lwip */
  	ee_lwip_init();
  	
  	/* Initialize the main netif structure */
	IP4_ADDR(&my_ipaddr, MY_IPADDR_BYTE1, MY_IPADDR_BYTE2, MY_IPADDR_BYTE3, MY_IPADDR_BYTE4);
	IP4_ADDR(&netmask, MY_NETMASK_BYTE1, MY_NETMASK_BYTE2, MY_NETMASK_BYTE3, MY_NETMASK_BYTE4);
	IP4_ADDR(&gw, MY_GATEWAY_ADDR_BYTE1, MY_GATEWAY_ADDR_BYTE2, MY_GATEWAY_ADDR_BYTE3, MY_GATEWAY_ADDR_BYTE4);
	IP4_ADDR(&remote_ipaddr, REMOTE_IPADDR_BYTE1, REMOTE_IPADDR_BYTE2, REMOTE_IPADDR_BYTE3, REMOTE_IPADDR_BYTE4);
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("netif_add!\n"));
	netif_add(&netif, &my_ipaddr, &netmask, &gw,
                                          (void*)&my_ethernetif,
                                          ethernetif_init, 
                                          ethernet_input);
	netif_set_default(&netif);
    netif_set_up(&netif);                       /* bring the interface up */
    
	/* Initialize application(s) */
	err_t ret;
	EE_buffer_init(&UDP_rx_buffer, UDP_PAYLOAD_PKT_SIZE, UDP_BUFFER_SIZE, udp_rx_data);
	EE_buffer_init(&UDP_tx_buffer, UDP_PAYLOAD_PKT_SIZE, UDP_BUFFER_SIZE, udp_tx_data);
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("udp_new!\n"));
	my_udp_socket = udp_new();	/* Create an udp socket */
	ret = udp_bind(my_udp_socket, &my_ipaddr, MY_PORT);	/* Bind the udp socket */ 
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("udp_bind return value: %d\n", ret));
	udp_recv(my_udp_socket, &udp_rx_handler, 0);		/* Set the rx callback for udp packets */ 
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
	
	/* ------------------- */
	/* Background activity */
	/* ------------------- */
	/* Device initialization */
	print_string("\n\n\nLWIP configuration in progress...");
	LWIP_startup_task();	/* LWIP network interface initialization */
	print_string("Done!\n\n\n");
	
	turn_on_led();
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

/*
* Allocate a transport-layer pbuf and copies the provided data buffer 'data'
* of length 'len' bytes into the payload(s) of the pbuf. The function takes
* care of splitting the data into successive pbuf payloads, if necessary.
* The function returns the newly created pbuf or NULL if the pbuf cannot
* be allocated.
*/
struct pbuf *pbuf_new(u8_t *data, u16_t len) {
    struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, len, PBUF_RAM);
    struct pbuf *q = p;
    while ((q != (struct pbuf *)0) && (len >= q->len)) {
        memcpy(q->payload, data, q->len);         /* copy data into payload */
        len  -= q->len;                                 /* remaining length */
        data += q->len;                              /* remainig data chunk */
        q = q->next;                                       /* get next pbuf */
    }
    return p;
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


