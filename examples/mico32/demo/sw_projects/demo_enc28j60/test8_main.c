/*
  Name: test8_main.c
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: LWIP tcp test (tcp server).
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
#include "MicoUtils.h"

/* LWIP */
#include "ee_lwip.h"

/* Utilities */
#include "test8.h"
#include "echo.h"

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
/* Socket status structure */
struct mysocket_state {
  struct pbuf *p;
  u32_t  pos;    /* where to start in this pbuf */
  u32_t  left;   /* how many are left in this pbuf */
};

/* ----------------------------------------------------------- */
/* Callbacks and tasks */
/* ----------------------------------------------------------- */
void tcp_close_connection(struct tcp_pcb *pcb, struct mysocket_state *mss);
void tcp_send_data(struct tcp_pcb *pcb, struct mysocket_state *mss);
err_t tcp_poll_callback(void *arg, struct tcp_pcb *pcb);
err_t tcp_tx_callback(void *arg, struct tcp_pcb *pcb, u16_t len);
err_t tcp_rx_callback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
err_t tcp_accept_callback(void *arg, struct tcp_pcb *pcb, err_t err);

/* myTask1 */
TASK(myTask1)
{
	#if 0
	/* Reception */
	if(EE_enc28j60_pending_interrupt())
	{
		myprintf("Reception in progress...\n");
		ethernetif_input(&EE_lwip_netif);	/* Elaborate the received packet */
	}
	#endif
}

/* myTask2 */
TASK(myTask2)
{
	#if 0
	tcp_tmr();
	#endif
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
	/* My app initialization */
	/* ------------------- */
	/* TCP socket used in this demo */
	
	#if 1
	err_t ret;
	struct tcp_pcb* my_tcp_socket = tcp_new();	/* Create an tcp socket */
	myprintf("tcp_new!\n");
	ret = tcp_bind(my_tcp_socket, &my_ipaddr, MY_PORT);	/* Bind the tcp socket */ 
	myprintf("tcp_bind return value: %d\n", ret);
	my_tcp_socket = tcp_listen(my_tcp_socket);
	myprintf("tcp_listen\n");
	tcp_accept(my_tcp_socket, &tcp_accept_callback);
	myprintf("tcp_accept\n");
	#else
	echo_init();
	#endif
	
	/* ------------------- */
	/* Background activity */
	/* ------------------- */
	turn_on_led();
	SetRelAlarm(myAlarm1, 1000, 100);
	SetRelAlarm(myAlarm2, 10, 250);	
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

/* TCP send data callback */
void tcp_close_connection(struct tcp_pcb *pcb, struct mysocket_state *mss)
{
	myprintf("\ntcp_close_connection start!\n");
	tcp_arg(pcb, NULL);
	tcp_sent(pcb, NULL);
	tcp_recv(pcb, NULL);
	if (mss) {
    	if (mss->p) {
      		pbuf_free(mss->p);
    	}
    	mem_free(mss);
	}
	tcp_close(pcb);
	myprintf("\ntcp_close_connection end!\n");
}

/* TCP send data callback */
void tcp_send_data(struct tcp_pcb *pcb, struct mysocket_state *mss)
{
	err_t err;
	u16_t len;
  
	myprintf("\ntcp_send_data start!\n");
	if (mss->p == NULL) {
		myprintf("\ntcp_send_data end!\n");
    	return;
	}
	/* We cannot send more data than space avaliable in the send
     buffer. */    
	len = tcp_sndbuf(pcb); 
	myprintf("tcp_send_data sndbuf: %d\n", len);
	if(len > mss->left) {
		len = mss->left;
	} 
  	myprintf("tcp_send_data len: %d\n", len);
  	int i;
  	for(i=0; i<len; i++)
		myprintf("p->payload[%d]:0x%x  ", i, ((u8_t*)(mss->p->payload + mss->pos))[i]);
	/* Send the extracted packet */
	myprintf("tcp_send_data write...\n");
  	err = tcp_write(pcb, mss->p->payload + mss->pos, len, 1);
  	if(err == ERR_OK) {
    	mss->pos  += len;
    	mss->left -= len;
  	} else {
    	myprintf("tcp_send_data: error %d len %d %d\n", err, len, tcp_sndbuf(pcb));
  	}
  	myprintf("\ntcp_send_data end!\n");
}

/* TCP poll callback */
err_t tcp_poll_callback(void *arg, struct tcp_pcb *pcb)
{
	myprintf("\ntcp_poll_callback!\n");
	return ERR_OK;
}

/* TCP tx handler */
err_t tcp_tx_callback(void *arg, struct tcp_pcb *pcb, u16_t len)
{
	struct pbuf *p;
	struct mysocket_state *mss = arg;
	
	myprintf("\ntxcbk start!\n");
	if (mss->left > 0) {
		tcp_send_data(pcb, mss);
	} else {
    	if (mss->p) {
			/* free the pbuf and send the next one */
			p = mss->p;
			mss->p = pbuf_dechain(p);
			mss->pos = 0;
			if (mss->p) 
				mss->left = mss->p->len;
			else       
				mss->left = 0;
			pbuf_free(p);
			if (mss->left > 0) 
				tcp_send_data(pcb, mss);
		}
  	}
  	myprintf("\ntxcbk end!\n");
	return ERR_OK;
}

/* TCP rx handler */
err_t tcp_rx_callback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
	struct mysocket_state *mss = arg;
	
	myprintf("\ntcp_rx_callback start!\n");
	if(p != NULL) 
	{
		/* Print received data */
		print_pbuf("rx_p",p);
		/* Do something with received data */
		do_something(p);
    	/* Inform TCP that we have taken the data. */
    	tcp_recved(tpcb, p->tot_len);
	} 
	else 
	{
		myprintf("rxcbk no data received, connection closed\n");
		//close_conn(pcb, mss);
	}
	if (err != ERR_OK) 
	{
		myprintf("rxcbk error %d, connection closed \n", err);
		//close_conn(pcb, mss);
	}
	
	/* Transmission */
    if (mss->p) {						/* append this pbuf to the sending list */
      pbuf_chain(mss->p, p);	
    }
    else {
      mss->p    = p;
      mss->left = p->len;
      mss->pos  = 0;
    }
    if(err == ERR_OK && p != NULL)
    	 tcp_send_data(tpcb, mss);		/* Send data */

	myprintf("\ntcp_rx_callback end!\n");
	return err;
}

/* TCP accept callback */
err_t tcp_accept_callback(void *arg, struct tcp_pcb *pcb, err_t err)
{
	myprintf("\ntcp_accept_callback start!\n");
	
	/* Initialize the server structure. */
	struct mysocket_state *mss;
	mss = mem_malloc(sizeof(struct mysocket_state));
  	if(mss == NULL) {
		myprintf("\ntcp_accept_callback: mem_malloc out of memory!\n");
    	return ERR_MEM;
  	}
	mss->p    = NULL;
	mss->left = 0;
	mss->pos  = 0;

  	/* Tell TCP that this is the structure we wish to be passed for our
     callbacks. */
  	tcp_arg(pcb, mss);
  	tcp_sent(pcb, &tcp_tx_callback);		/* Set the tx callback for tcp packets */
	tcp_recv(pcb, &tcp_rx_callback);		/* Set the rx callback for tcp packets */ 
	tcp_poll(pcb, &tcp_poll_callback, 10);	/* Set the poll callback for tcp */
	
	myprintf("\ntcp_accept_callback end!\n");
	return ERR_OK;
}


void print_time_results(void)
{
	tsprintf("\n");
	
	tsprintf("Absolute time:\n");
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
	
	tsprintf("Init time:\n");
	tsprintf("LWIP_START_ETH_INIT - LWIP_END_ETH_INIT:         %u\n", lwip_time_diff_us(EE_lwip_read_timestamp(LWIP_START_ETH_INIT), EE_lwip_read_timestamp(LWIP_END_ETH_INIT)));
	tsprintf("LWIP_START_LOWLEV_INIT - LWIP_END_LOWLEV_INIT:   %u\n", lwip_time_diff_us(EE_lwip_read_timestamp(LWIP_START_LOWLEV_INIT), EE_lwip_read_timestamp(LWIP_END_LOWLEV_INIT)));
	
	tsprintf("Transmission time:\n");
	tsprintf("LWIP_START_UDP_SEND - LWIP_END_UDP_SEND:         %u\n", lwip_time_diff_us(EE_lwip_read_timestamp(LWIP_START_UDP_SEND), EE_lwip_read_timestamp(LWIP_END_UDP_SEND)));
	tsprintf("LWIP_START_ETH_OUT - LWIP_END_ETH_OUT:           %u\n", lwip_time_diff_us(EE_lwip_read_timestamp(LWIP_START_ETH_OUT), EE_lwip_read_timestamp(LWIP_END_ETH_OUT)));
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

void do_something(struct pbuf *p)
{
	struct pbuf *q;
	int i;
	
    for(q = p; q != NULL; q = q->next) 
         for(i=0; i<(q->len); i++)
            ((u8_t*)q->payload)[i] += 5; 
}
