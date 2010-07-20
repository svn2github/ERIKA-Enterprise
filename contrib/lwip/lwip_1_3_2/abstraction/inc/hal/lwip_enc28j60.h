/*
  Name: lwip_enc28j60.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: 	This file contains the declarations of the abstract 
				enc28j60 functions used by LWIP modules.
*/

#ifndef __lwip_ethernet_enc28j60_h__
#define __lwip_ethernet_enc28j60_h__

#include "ee_lwip.h"
#include "enc28j60.h"
#include <hal/lwip_compiler.h>

/**
 * Helper struct to hold private data used to operate your ethernet interface.
 * Keeping the ethernet address of the MAC in this struct is not necessary
 * as it is already kept in the struct netif.
 * But this is only an example, anyway...
 */
struct ethernetif {
  /* Add whatever per-interface state that is needed here. */
  struct eth_addr *ethaddr;
  u8_t pkt_cnt;
  u16_t length;
};

__INLINE__ void __ALWAYS_INLINE__ EE_ethernetif_hal_set_Rx_task(EE_TID task)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_ethernetif_hal_set_Rx_task\n"));
	EE_enc28j60_set_rx_task(task);
}

__INLINE__ void __ALWAYS_INLINE__ EE_lwip_hal_rx_service(void)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_lwip_hal_rx_service\n"));
	EE_enc28j60_enable_IRQ();
}

__INLINE__ void __ALWAYS_INLINE__ EE_ethernetif_hal_enable_interrupt(void)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_ethernetif_hal_enable_interrupt\n"));
	EE_enc28j60_enable_IRQ();
}

__INLINE__ void __ALWAYS_INLINE__ EE_ethernetif_hal_disable_interrupt(void)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_ethernetif_hal_disable_interrupt\n"));
	EE_enc28j60_disable_IRQ();
}

__INLINE__ int __ALWAYS_INLINE__ EE_ethernetif_hal_pending_interrupt(void)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_ethernetif_hal_pending_interrupt\n"));
	return EE_enc28j60_pending_interrupt();
}

__INLINE__ void __ALWAYS_INLINE__ EE_ethernetif_hal_init(struct netif *netif)
{
	struct ethernetif *ethernet_if;
	mac_addr myMACaddress;
	
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_ethernetif_hal_init\n"));
	
	/* Allocate memory for ethernetif */
	ethernet_if = mem_malloc(sizeof(struct ethernetif));
	if (ethernet_if == NULL)
		LWIP_DEBUGF(NETIF_DEBUG, ("EE_ethernetif_hal_init: out of memory\n"));
	
	netif->state = ethernet_if;
	ethernet_if->ethaddr = 	(struct eth_addr *)&(netif->hwaddr[0]);
	ethernet_if->pkt_cnt = 	0; 
	ethernet_if->length = 	0;
	
	myMACaddress.v[0] = netif->hwaddr[0];
	myMACaddress.v[1] = netif->hwaddr[1];
	myMACaddress.v[2] = netif->hwaddr[2];
	myMACaddress.v[3] = netif->hwaddr[3];
	myMACaddress.v[4] = netif->hwaddr[4];
	myMACaddress.v[5] = netif->hwaddr[5];

	EE_enc28j60_init(myMACaddress);
}

__INLINE__ void __ALWAYS_INLINE__ EE_ethernetif_hal_initiate_transfer(void)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_ethernetif_hal_initiate_transfer\n"));
	EE_enc28j60_transfer_init();
}

__INLINE__ void __ALWAYS_INLINE__ EE_ethernetif_hal_write(u8_t* data, u16_t len)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_ethernetif_hal_write: %x, %d\n", data, len));
	EE_enc28j60_write(data, len);
}

__INLINE__ void __ALWAYS_INLINE__ EE_ethernetif_hal_signal(u16_t len)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_ethernetif_hal_signal: %d\n", len));
	EE_enc28j60_signal(len);
}

__INLINE__ int __ALWAYS_INLINE__ EE_ethernetif_hal_get_info(struct netif *netif)
{
	struct ethernetif *ethernet_if = (struct ethernetif *)netif->state;
	
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_ethernetif_hal_get_info: %x\n", ethernet_if));
	
	if(EE_enc28j60_read_info(&ethernet_if->pkt_cnt, &ethernet_if->length)<0)
		return 0;
	else
		return ethernet_if->length;
}


__INLINE__ int __ALWAYS_INLINE__ EE_ethernetif_hal_read(u8_t* data, u16_t len)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_ethernetif_hal_read: %x, %d\n", data, len));
	return EE_enc28j60_read(data, len);
}

__INLINE__ void __ALWAYS_INLINE__ EE_ethernetif_hal_ack(void)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_ethernetif_hal_ack\n"));
	EE_enc28j60_ack();
}

__INLINE__ void __ALWAYS_INLINE__ EE_ethernetif_hal_drop_packet(void)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_ethernetif_hal_drop_packet\n"));
	EE_enc28j60_drop_packet();
}

#endif /* Header Protection */
