/*
  Copyright: 2010, Evidence Srl
  Author: Bernardo  Dal Seno
  Description: LWIP udp test.
*/

/* RT-Kernel */
#include <ee.h>
/* Platform description */
#include <system_conf.h>
/* Standard library */
#include <stdio.h>

/* lwIP */
#include <lwip/pbuf.h>
#include <lwip/udp.h>
#include "lwip.h"

#include <MicoMacros.h>

/* Variables for UDP communication */
static const u16_t my_port = 9760;
static const u16_t remote_port = 8640;
#define MY_UDP_BUFFER_LEN 256
static EE_UINT8 my_udp_buffer[MY_UDP_BUFFER_LEN];


/* A printf-like function */
void myprintf(const char *format, ...)
{
#define MAXCHARS 128
    const char printf_trunc[] = "..[TRUNCATED]..\n";
    char str[MAXCHARS];
    int len;
    va_list args;
    va_start(args, format);
    len = vsnprintf(str, MAXCHARS, format, args);
    va_end(args);
    if (len > MAXCHARS - 1) {
        /* vsnptintf() returns the number of characters needed */
        EE_uart_send_buffer(str, MAXCHARS - 1 );
        EE_uart_send_buffer(printf_trunc, sizeof(printf_trunc) - 1);
    } else {
        EE_uart_send_buffer(str, len);
    }
}


static void hex_dump(const void *base, int size)
{
    const unsigned char *p = base;
    char lbuf[16*3+4];
    int k, j;
    
    j = 0;
    for (k = 0; k < size; ++k) {
        sprintf(&lbuf[j], "%02x ", p[k]);
        j += 3;
        if (0 == ((k+1) % 16) || k == size-1) {
            lbuf[j++] = '\n';
            lbuf[j] = 0;
            EE_uart_send_buffer(lbuf, j);
            j = 0;
        } else if (0 == ((k+1) % 8)) {
            lbuf[j++] = ' ';
        }
    }
}


/* UDP rx handler */
static void udp_rx_handler(void *arg, struct udp_pcb *upcb,
    struct pbuf *p, struct ip_addr *addr, u16_t port)
{
    struct pbuf *q;
    int i;
    u16_t len;
    EE_UINT32 leds;
    err_t ret;

    /* The red leds form an 8-bit counter for packets.  The system led (9)
     * indicates activity. */
    leds = EE_led_get_all();
    EE_led_set_all(((leds + 1) & 0xff) | (1<<9));

    /* Connect to the remote host, for replies */
    if (! (upcb->flags & UDP_FLAGS_CONNECTED))
        udp_connect(upcb, addr, port);
    
    /* Print the received UDP packet */
    myprintf("\nReceived %d bytes from %d.%d.%d.%d, port %d\n", p->tot_len,
        ip4_addr1(addr), ip4_addr2(addr), ip4_addr3(addr), ip4_addr4(addr),
        port );
    for(i = 1, q = p; q != NULL; q = q->next, ++i) {
        myprintf("Chunk #%d, %d byte long\n",i, q->len);
        hex_dump(q->payload, q->len);
    }

    /* Estract the payload in a buffer, put it in a new pbuf, and send */
    len = pbuf_copy_partial(p, my_udp_buffer, MY_UDP_BUFFER_LEN, 0);
    if (len > 0) {
        q = pbuf_alloc(PBUF_TRANSPORT, len, PBUF_REF);
        if (q != 0) {
            q->payload = my_udp_buffer;
            ret = udp_send(upcb, q);
            if (ret != ERR_OK)
                myprintf("ERROR in sending a reply\n");
            pbuf_free(q);
        } else {
            myprintf("ERROR while allocating a pbuf\n");
        }
    } else {
        myprintf("ERROR while extracting data\n");
    }
    
    /* Don't leak the pbuf! */
    pbuf_free(p);
    
    EE_led_off(9);
}


TASK(Sender)
{
    struct udp_pcb *socket;
    struct ip_addr ipaddr;
#define UDP_SENDER_BUF_SIZE 1408
    static EE_UINT8 buf[UDP_SENDER_BUF_SIZE];
    const unsigned num_packets = 512;
    static EE_UINT16 size = 11;
    struct pbuf *pb;
    err_t ret;
    unsigned i;

    myprintf("\nSender: sending %d %d-byte packets\n", num_packets, size);

    
    GetResource(LwipMutex);
    socket = udp_new();
    if (0 == socket) {
        ReleaseResource(LwipMutex);
        myprintf("ERROR: cannot create UDP socket\n");
        return;
    }
    ret = udp_bind(socket, IP_ADDR_ANY, my_port+1);
    if (ret != ERR_OK) {
        udp_remove(socket);
        ReleaseResource(LwipMutex);
        myprintf("ERROR while binding to UDP port %d\n", my_port+1);
        return;
    }
    IP4_ADDR(&ipaddr, MY_IPADDR_BYTE1, MY_IPADDR_BYTE2,
        MY_IPADDR_BYTE3, MY_IPADDR_BYTE4 + 1);
    udp_connect(socket, &ipaddr, remote_port);

    pb = pbuf_alloc(PBUF_TRANSPORT, size, PBUF_REF);
    ReleaseResource(LwipMutex);
    if (pb != 0) {
        pb->payload = buf;
        for (i = 0; i < num_packets; ++i) {
            sprintf((char *)buf, "%5d", i);
            GetResource(LwipMutex);
            ret = udp_send(socket, pb);
            ReleaseResource(LwipMutex);
            if (ret != ERR_OK)
                myprintf("ERROR in sending a packet\n");
        }
        pbuf_free(pb);
    } else {
        myprintf("ERROR while allocating a pbuf\n");
    }
    GetResource(LwipMutex);
    udp_remove(socket);
    ReleaseResource(LwipMutex);
    if (size*2 <= UDP_SENDER_BUF_SIZE)
        size *= 2;
}


static void timer_tick(void)
{
    CounterTick(SenderCounter);
}


int main(void)
{
    struct udp_pcb *my_udp_socket;
    err_t ret;
    
    /* Initialize UART */
    EE_uart_config(115200, EE_UART_BIT8_NO | EE_UART_BIT_STOP_1);
    EE_uart_set_ISR_mode(EE_UART_POLLING | EE_UART_RXTX_BLOCK);   

    /* Initialize lwIP */
    init_lwip();

    /* Sender timer */
    EE_timer_init(MILLISECONDS_TO_TICKS(1000),
        MICO32_TIMER_CONTROL_INT_BIT_MASK | MICO32_TIMER_CONTROL_CONT_BIT_MASK);
    EE_timer_set_ISR_callback(timer_tick);
    SetRelAlarm(SenderAlarm, 1, 10);
    EE_timer_on();
    
    /* Let's start everything: interrupts drive the application */
    EE_mico32_enableIRQ();

    /* Create a UDP socket */
    my_udp_socket = udp_new();
    if (my_udp_socket != 0) {
        /* Set the incoming callback */
        udp_recv(my_udp_socket, &udp_rx_handler, 0);
        /* Bind to a local port */
        ret = udp_bind(my_udp_socket, IP_ADDR_ANY, my_port);
        if (ret != ERR_OK) {
            myprintf("ERROR while binding to UDP port %d\n", my_port);
        } else {
            myprintf("Listening on UDP port %d\n", my_port);
        }
    } else {
        myprintf("ERROR: cannot create UDP socket\n");
    }

    while(1)
        ;
}
