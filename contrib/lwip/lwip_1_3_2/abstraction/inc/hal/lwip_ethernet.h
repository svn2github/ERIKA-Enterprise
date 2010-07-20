/*
  Name: lwip_ethernet.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: 	This file contains the declarations of the abstract 
				ethernet used by LWIP modules.
*/

#ifndef __lwip_ethernet_h__
#define __lwip_ethernet_h__

//#include "ee_lwip.h"
#include <hal/lwip_compiler.h>

#ifdef __USE_ETHERNET_ENC28J60__		/* Microchip enc28j60 ethernet controller */
#include <hal/lwip_enc28j60.h>
#else
#error "LWIP_HAL ERROR: ethernet controller not specified!"
#endif	/* End ethernet Selection */

/* Forward declarations. */
err_t EE_ethernet_input(struct netif *netif);
err_t EE_ethernet_init(struct netif *netif);
err_t EE_ethernet_output(struct netif *netif, struct pbuf *p, struct ip_addr *ipaddr);
//err_t EE_ethernet_service(struct netif *netif);


#endif /* Header Protection */
