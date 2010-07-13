/* ###*B*###
* ERIKA Enterprise - a tiny RTOS for small microcontrollers
*
* Copyright (C) 2002-2008  Evidence Srl
*
* This file is part of ERIKA Enterprise.
*
* ERIKA Enterprise is free software; you can redistribute it
* and/or modify it under the terms of the GNU General Public License
* version 2 as published by the Free Software Foundation,
* (with a special exception described below).
*
* Linking this code statically or dynamically with other modules is
* making a combined work based on this code.  Thus, the terms and
* conditions of the GNU General Public License cover the whole
* combination.
*
* As a special exception, the copyright holders of this library give you
* permission to link this code with independent modules to produce an
* executable, regardless of the license terms of these independent
* modules, and to copy and distribute the resulting executable under
* terms of your choice, provided that you also meet, for each linked
* independent module, the terms and conditions of the license of that
* module.  An independent module is a module which is not derived from
* or based on this library.  If you modify this code, you may extend
* this exception to your version of the code, but you are not
* obligated to do so.  If you do not wish to do so, delete this
* exception statement from your version.
*
* ERIKA Enterprise is distributed in the hope that it will be
* useful, but WITHOUT ANY WARRANTY; without even the implied warranty
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License version 2 for more details.
*
* You should have received a copy of the GNU General Public License
* version 2 along with ERIKA Enterprise; if not, write to the
* Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
* Boston, MA 02110-1301 USA.
* ###*E*### */

#include "ee_lwip.h"
#include <string.h>

/* Main network structure */
struct netif EE_lwip_netif;

u8_t ETHERNETIF_MAC_BYTE1;
u8_t ETHERNETIF_MAC_BYTE2;
u8_t ETHERNETIF_MAC_BYTE3;
u8_t ETHERNETIF_MAC_BYTE4;
u8_t ETHERNETIF_MAC_BYTE5;
u8_t ETHERNETIF_MAC_BYTE6;

void EE_lwip_init(struct ip_addr *my_ipaddr, struct ip_addr *netmask, struct ip_addr *gw, struct eth_addr *my_ethaddr)
{
	#ifdef LWIP_DEBUG
	/* Debug initialization */
	lwip_debug_init();
	#endif
	
	/* Ethernet address */
	ETHERNETIF_MAC_BYTE1 = my_ethaddr->addr[0];
	ETHERNETIF_MAC_BYTE2 = my_ethaddr->addr[1];
	ETHERNETIF_MAC_BYTE3 = my_ethaddr->addr[2];
	ETHERNETIF_MAC_BYTE4 = my_ethaddr->addr[3];
	ETHERNETIF_MAC_BYTE5 = my_ethaddr->addr[4];
	ETHERNETIF_MAC_BYTE6 = my_ethaddr->addr[5];
	
	/* LWIP stack initialization */
	lwip_init();

	/* Initialize the main netif structure */
	LWIP_DEBUGF(EE_LWIP_DEBUG, ("netif initialization start!\n"));
	netif_add(&EE_lwip_netif, my_ipaddr, netmask, gw, (void*)0, EE_ethernet_init, ethernet_input);
	netif_set_default(&EE_lwip_netif);				/* default settings */
	netif_set_up(&EE_lwip_netif);					/* bring the interface up */
	LWIP_DEBUGF(EE_LWIP_DEBUG, ("netif initialization end!\n"));

	/* Timers configuration */
	EE_lwip_timers_configuration();
}

/* lwIP task for timers */
TASK(LwipPeriodic)
{
	EE_UINT16 pending;

	GetResource(LwipMutex);
	/* The access to the `pending' field must be protected from
	* interferences by the timer ISR */
	EE_hal_disableIRQ();
	pending = EE_lwip_timers.pending;
	EE_lwip_timers.pending = 0;
	EE_hal_enableIRQ();
	EE_lwip_maybe_call_tcp_timers(pending);
	EE_lwip_maybe_call_arp_timer(pending);
	ReleaseResource(LwipMutex);
}

/* lwIP task for handling incoming packets */
TASK(LwipReceive)
{
	GetResource(LwipMutex);
	/* We are assuming that the only interrupt source is an incoming packet */
	while (EE_ethernetif_pending_interrupt()) {
		//LWIP_DEBUGF(EE_LWIP_DEBUG,
		//    ("Got an Ethernet packet at 0x%04x\n", ReadETHReg(EIR).Val));
		EE_ethernet_input(&EE_lwip_netif);
	}
	/* We should enable interrupts  */
	/* EE_enc28j60_unmask_interrupts(); */
	/* There is no race condition, as if an interrupt has become pending, it
	will be served at the next timer tick */
	EE_lwip_irq_pending = 0;
	ReleaseResource(LwipMutex);
}



