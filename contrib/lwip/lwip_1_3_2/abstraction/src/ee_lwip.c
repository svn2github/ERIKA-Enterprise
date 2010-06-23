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
struct netif lwip_netif;

void EE_lwip_init(void)
{
	struct ip_addr my_ipaddr, netmask, gw;
	struct ethernetif my_ethernetif;	 /* My ethernet board info */  
	
#ifdef LWIP_DEBUG
	/* Debug initialization */
	lwip_debug_init();
#endif
	/* LWIP stack initialization */
	lwip_init();
	
    /* Create the IP4 addresses */
    IP4_ADDR(&my_ipaddr, MY_IPADDR_BYTE1, MY_IPADDR_BYTE2, MY_IPADDR_BYTE3, MY_IPADDR_BYTE4);
    IP4_ADDR(&netmask, MY_NETMASK_BYTE1, MY_NETMASK_BYTE2, MY_NETMASK_BYTE3, MY_NETMASK_BYTE4);
    IP4_ADDR(&gw, MY_GATEWAY_ADDR_BYTE1, MY_GATEWAY_ADDR_BYTE2, MY_GATEWAY_ADDR_BYTE3, MY_GATEWAY_ADDR_BYTE4);
	
    /* Initialize the main netif structure */
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("netif initialization start!\n"));
    netif_add(&lwip_netif, &my_ipaddr, &netmask, &gw,
                                          (void*)&my_ethernetif,
                                          ethernetif_init, 
                                          ethernet_input);
    netif_set_default(&lwip_netif);				/* default settings */
    netif_set_up(&lwip_netif);					/* bring the interface up */
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("netif initialization end!\n"));
	
	/* Periodic task for TCP and IP timers */
	#ifdef __USE_LWIP_TIMER__
	SetRelAlarm(LWIP_ALARM, LWIP_ALARM_OFFSET, LWIP_ALARM_OFFSET_PERIOD);
	#endif
}

void EE_lwip_handler(void)
{

}

TASK(LWIP_PERIODIC_TASK)
{
	tcp_tmr();
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


