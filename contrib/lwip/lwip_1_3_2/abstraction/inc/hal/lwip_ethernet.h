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

#include "ee_lwip.h"
#include <hal/lwip_compiler.h>

#ifdef __USE_ETHERNET_ENC28J60__		/* Microchip enc28j60 ethernet controller */
#include <hal/lwip_enc28j60.h>
#else
#error "LWIP_HAL ERROR: ethernet controller not specified!"
#endif	/* End ethernet Selection */

/* Abstraction functions declarations. */
__INLINE__ int __ALWAYS_INLINE__ EE_ethernetif_pending_interrupt(void)
{
	return EE_ethernetif_hal_pending_interrupt();
}

__INLINE__ void __ALWAYS_INLINE__ EE_ethernetif_init(struct netif *netif)
{
	EE_ethernetif_hal_init(netif);
}

__INLINE__ void __ALWAYS_INLINE__ EE_ethernetif_initiate_transfer(void)
{
	EE_ethernetif_hal_initiate_transfer();
}

__INLINE__ void __ALWAYS_INLINE__ EE_ethernetif_write(u8_t* data, u16_t len)
{
	EE_ethernetif_hal_write(data, len);
}

__INLINE__ void __ALWAYS_INLINE__ EE_ethernetif_signal(u16_t len)
{
	EE_ethernetif_hal_signal(len);
}

__INLINE__ int __ALWAYS_INLINE__ EE_ethernetif_get_info(struct netif *netif)
{
	return EE_ethernetif_hal_get_info(netif);
}


__INLINE__ int __ALWAYS_INLINE__ EE_ethernetif_read(u8_t* data, u16_t len)
{
	return EE_ethernetif_hal_read(data, len);
}

__INLINE__ void __ALWAYS_INLINE__ EE_ethernetif_ack(void)
{
	EE_ethernetif_hal_ack();
}

__INLINE__ void __ALWAYS_INLINE__ EE_ethernetif_drop_packet(void)
{
	EE_ethernetif_hal_drop_packet();
}


/* Forward declarations. */
err_t EE_ethernet_input(struct netif *netif);
err_t EE_ethernet_init(struct netif *netif);
err_t EE_ethernet_output(struct netif *netif, struct pbuf *p, struct ip_addr *ipaddr);
//err_t EE_ethernet_service(struct netif *netif);


#endif /* Header Protection */
