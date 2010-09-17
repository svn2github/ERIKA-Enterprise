/*
	Name: 			main.c
	Copyright: 		Evidence Srl, 2010
	Author: 		Alessandro Paolinelli
  	Description: 	Camera based web server. 
  					This demo shows how to set up a camera based web server.
  					Communication is based on the LWIP stack and uses ENC28J60 device.
  					The demo requires a RS232 serial connection (configured at 115200 bps,8N1).
					The demo requires a SPI connection with the ENC28J60 device. 
					The demo requires a I2C connection with the HV7131GP camera.
					It also requires a library that uses SDRAM for read/write data. 
*/

/* RT-Kernel */
#include <ee.h>
/* Erika Mico32 interrupts */
#include <cpu/mico32/inc/ee_irq.h>
/* Platform description */
#include <system_conf.h>
/* Standard library */
#include <stdio.h>
#include <stdarg.h>
#include <MicoMacros.h>
/* lwIP */
#include <ee_lwip.h>

#include "lwip.h"
#include "httpd.h"
#include "hv7131gp.h"


extern void test_lodePng();
extern void test_prepareImg();

/* A printf-like function */
void myprintf(const char *format, ...)
{
#define MAXCHARS 128
    const char printf_trunc[] = "..[TRUNCATED]..\n\r";
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

int main(void)
{
	hv7131gp_Q_Value_t Quality  = HV7131GP_160x120_FAST;
	hv7131gp_status_t camera_status;
    EE_led_set_all(0x01);
    test_prepareImg();
    
    /* Initialize UART */
    EE_uart_config(115200, EE_UART_BIT8_NO | EE_UART_BIT_STOP_1);
    EE_uart_set_ISR_mode(EE_UART_POLLING | EE_UART_RXTX_BLOCK);
    
    /* Initialize lwIP */
    struct ip_addr my_ipaddr, netmask, gw;
    struct eth_addr my_ethaddr;
    IP4_ADDR(&my_ipaddr, MY_IPADDR_BYTE1, MY_IPADDR_BYTE2, MY_IPADDR_BYTE3,
        MY_IPADDR_BYTE4);
    IP4_ADDR(&netmask, MY_NETMASK_BYTE1, MY_NETMASK_BYTE2, MY_NETMASK_BYTE3,
        MY_NETMASK_BYTE4);
    IP4_ADDR(&gw, MY_GATEWAY_ADDR_BYTE1, MY_GATEWAY_ADDR_BYTE2,
        MY_GATEWAY_ADDR_BYTE3, MY_GATEWAY_ADDR_BYTE4);
    ETH_ADDR(&my_ethaddr, MY_ETHERNETIF_MAC_BYTE1, MY_ETHERNETIF_MAC_BYTE2,
        MY_ETHERNETIF_MAC_BYTE3, MY_ETHERNETIF_MAC_BYTE4,
        MY_ETHERNETIF_MAC_BYTE5, MY_ETHERNETIF_MAC_BYTE6);
    EE_lwip_init(&my_ipaddr, &netmask, &gw, &my_ethaddr);
    
    /* Let's start everything: interrupts drive the application */
    EE_mico32_enableIRQ();
    
    camera_status = hv7131gp_init();
    
    if (camera_status != HV7131GP_SUCCESS){
    	myprintf("hv7131gp_init %d \n\r",camera_status);
    	while(1);
    }
    
    /* Configure the camera device */
	camera_status = hv7131gp_configure(Quality);
	if (camera_status != HV7131GP_SUCCESS)
	{
		myprintf("hv7131gp_configure %d \n\r",camera_status);
    	while(1);
	}

	//hv7131gp_configure_time_divisor(HV7131GP_T_1);
	hv7131gp_configure_color(1);
	
	httpd_init();

    while(1);
}
