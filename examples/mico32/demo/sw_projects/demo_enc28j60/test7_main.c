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
#include "ee_lwip.h"
/* Utilities */
#include "test7.h"

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

/* myTask1 */
TASK(myTask1)
{
    /* Reception */
    if(EE_enc28j60_pending_interrupt())
    {
        print_string("\ninterrupt signal! Reception in progress...\n");
        /* Elaborate the received packet */
        ethernetif_input(&lwip_netif);
    }
    /* --------- */
        
    /* Transmission */
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
                print_string("\nTransmission in progress...\n");   
                print_pbuf("tx_p", p);    
                /* Send the extracted packet */
                udp_send(my_udp_socket, p);
                pbuf_free(p); 
            }
        }
    }
    /* --------- */
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
    print_string("\n\n\nLWIP configuration in progress...");
    EE_lwip_init();
    print_string("Done!\n");
    
    /* ------------------- */
    /* My app initialization   */
    /* ------------------- */
    err_t ret;
    struct ip_addr my_ipaddr;
    
    EE_buffer_init(&UDP_rx_buffer, UDP_PAYLOAD_PKT_SIZE, UDP_BUFFER_SIZE, udp_rx_data);
    EE_buffer_init(&UDP_tx_buffer, UDP_PAYLOAD_PKT_SIZE, UDP_BUFFER_SIZE, udp_tx_data);
    my_udp_socket = udp_new();  /* Create an udp socket */
    print_string("udp_new!\n");
    IP4_ADDR(&my_ipaddr, MY_IPADDR_BYTE1, MY_IPADDR_BYTE2, MY_IPADDR_BYTE3, MY_IPADDR_BYTE4);
    ret = udp_bind(my_udp_socket, &my_ipaddr, MY_PORT); /* Bind the udp socket */ 
    print_val("udp_bind return value: %d\n", ret);
    udp_recv(my_udp_socket, &udp_rx_handler, 0);        /* Set the rx callback for udp packets */ 
    print_string("udp_recv!\n");
    
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
    print_string("\nudp_rx_handler!\n");
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

void print_string(const char *s)
{
    #ifdef PRINT_ON 
    EE_uart_send_buffer((EE_UINT8*)s,strlen(s));
    #endif
}

void print_val(char* s, int val)
{
    #ifdef PRINT_ON 
    char str[64];
    sprintf(str, s, val);
    print_string(str);
    #endif
}

void print_vals(char* s, int val1, int val2)
{
    #ifdef PRINT_ON 
    char str[64];
    sprintf(str, s, val1, val2);
    print_string(str);
    #endif
}

void print_pbuf(const char *name, struct pbuf *p)
{
	#ifdef PRINT_ON 
	int i;
	struct pbuf *q;
	
	print_string(name);
	print_val("\np->tot_len: %d\n", p->tot_len);
	for(q = p; q != NULL; q = q->next) 
	{
		print_vals("payload: %x, len: %d\n", (unsigned int)q->payload, q->len);
		for(i=0; i<(q->len); i++)
		{
			print_vals("q->payload[%d]:%x  ", i, ((u8_t*)q->payload)[i]);
		}	
	}
	print_string("\n");
	#endif
}

void print_array(const char *name, BYTE* vet, int len)
{
	#ifdef PRINT_ON 
	int i;
	
	for(i=0; i<len; i++)
	{
		print_string(name);
		print_vals("[%d]:%x  ", i, vet[i]);
	}
	print_string("\n");
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


