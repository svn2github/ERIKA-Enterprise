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

#include "enc28j60.h"
#include <hal/lwip_compiler.h>
#include <lwip/debug.h>

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

/* MAC ADDRESS */
// #define MY_DEFAULT_MAC_BYTE1            (0x00)	// Use the default of
// #define MY_DEFAULT_MAC_BYTE2            (0x04)	// 00-04-A3-00-00-00 if using
// #define MY_DEFAULT_MAC_BYTE3            (0xA3)	// an ENCX24J600 or ZeroG ZG2100
// #define MY_DEFAULT_MAC_BYTE4            (0x00)	// and wish to use the internal
// #define MY_DEFAULT_MAC_BYTE5            (0x00)	// factory programmed MAC
// #define MY_DEFAULT_MAC_BYTE6            (0x00)	// address instead.

__INLINE__ void __ALWAYS_INLINE__ mydevice_init()
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("mydevice_init\n"));
	EE_enc28j60_init();
	
}

__INLINE__ void __ALWAYS_INLINE__ mydevice_initiate_transfer(void)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("mydevice_initiate_transfer\n"));
	EE_enc28j60_transfer_init();
}

__INLINE__ void __ALWAYS_INLINE__ mydevice_write(u8_t* data, u16_t len)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("mydevice_write: %x, %d\n", data, len));
	EE_enc28j60_write(data, len);
}

__INLINE__ void __ALWAYS_INLINE__ mydevice_signal(u16_t len)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("mydevice_signal: %d\n", len));
	EE_enc28j60_signal(len);
}

__INLINE__ int __ALWAYS_INLINE__ mydevice_get_info(struct ethernetif *ethernetif)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("mydevice_get_info: %x\n", ethernetif));
	return EE_enc28j60_read_info(&ethernetif->pkt_cnt, &ethernetif->length);
}


__INLINE__ int __ALWAYS_INLINE__ mydevice_read(u8_t* data, u16_t len)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("mydevice_read: %x, %d\n", data, len));
	return EE_enc28j60_read(data, len);
}

__INLINE__ void __ALWAYS_INLINE__ mydevice_ack(void)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("mydevice_ack\n"));
	EE_enc28j60_ack();
}

__INLINE__ void __ALWAYS_INLINE__ mydevice_drop_packet(void)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("mydevice_drop_packet\n"));
	EE_enc28j60_drop_packet();
}

#ifdef LWIP_DEBUG
#include <util/lwip_debug.h> //TODO: REMOVE together with the sprintf() !!!!!
//#include <stdio.h> //TODO: REMOVE together with the sprintf() !!!!!
#endif

#endif /* Header Protection */
