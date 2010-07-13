/*
  Name: lwipopts_ee.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: LWIP defines.
  NOTE: Please move this file in the RT-Druid output folder.
*/

#ifndef __LWIPOPTS_EE_H__
#define __LWIPOPTS_EE_H__

/* ---------- Ethernet address and IP address macros ---------- */
/* test6 */
//#define MY_DEFAULT_MAC_BYTE1        (0x00)	
//#define MY_DEFAULT_MAC_BYTE2        (0x1E)	
//#define MY_DEFAULT_MAC_BYTE3        (0x33)	
//#define MY_DEFAULT_MAC_BYTE4        (0xC9)	
//#define MY_DEFAULT_MAC_BYTE5        (0xD6)	
//#define MY_DEFAULT_MAC_BYTE6        (0xAA)

/* test7, test8 */
#define ETHERNETIF_MAC_BYTE1		(0x00)
#define ETHERNETIF_MAC_BYTE2		(0x04)
#define ETHERNETIF_MAC_BYTE3		(0xA3)
#define ETHERNETIF_MAC_BYTE4		(0x00)
#define ETHERNETIF_MAC_BYTE5		(0x00)
#define ETHERNETIF_MAC_BYTE6		(0x00)

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



//#define REMOTE_PORT				(9761)
//#define REMOTE_IPADDR_BYTE1 		(192)
//#define REMOTE_IPADDR_BYTE2 		(168)
//#define REMOTE_IPADDR_BYTE3 		(0)
//#define REMOTE_IPADDR_BYTE4 		(1)
//#define REMOTE_MAC_BYTE1          (0x00)	
//#define REMOTE_MAC_BYTE2          (0x1E)	
//#define REMOTE_MAC_BYTE3          (0x33)	
//#define REMOTE_MAC_BYTE4          (0xC9)	
//#define REMOTE_MAC_BYTE5          (0xD6)	
//#define REMOTE_MAC_BYTE6          (0xAA)	

/* ---------- App options ------------ */
#define LWIP_UDP 1

/* ---------- DEBUG options ---------- */
#define ETHARP_DEBUG                    LWIP_DBG_ON     // default is OFF
#define NETIF_DEBUG                     LWIP_DBG_ON     // default is OFF
#define PBUF_DEBUG                      LWIP_DBG_ON		// default is OFF
#define IP_DEBUG                        LWIP_DBG_ON     // default is OFF
#define TCP_DEBUG                       LWIP_DBG_ON		// default is OFF
#define TCP_INPUT_DEBUG                 LWIP_DBG_ON		// default is OFF
#define TCP_OUTPUT_DEBUG                LWIP_DBG_ON		// default is OFF
#define UDP_DEBUG                       LWIP_DBG_ON     // default is OFF
#define EE_LWIP_DEBUG                   LWIP_DBG_ON		// default is OFF

#endif /* __LWIPOPTS_EE_H__ */
