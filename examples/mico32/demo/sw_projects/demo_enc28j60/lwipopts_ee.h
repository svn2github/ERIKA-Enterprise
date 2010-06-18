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

/* test7 */
#define MY_DEFAULT_MAC_BYTE1        (0x00)	// Use the default of
#define MY_DEFAULT_MAC_BYTE2        (0x04)	// 00-04-A3-00-00-00 if using
#define MY_DEFAULT_MAC_BYTE3        (0xA3)	// an ENCX24J600 or ZeroG ZG2100
#define MY_DEFAULT_MAC_BYTE4        (0x00)	// and wish to use the internal
#define MY_DEFAULT_MAC_BYTE5        (0x00)	// factory programmed MAC
#define MY_DEFAULT_MAC_BYTE6        (0x00)	// address instead.
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
#define REMOTE_PORT					(9761)
#define REMOTE_IPADDR_BYTE1 		(192)
#define REMOTE_IPADDR_BYTE2 		(168)
#define REMOTE_IPADDR_BYTE3 		(0)
#define REMOTE_IPADDR_BYTE4 		(1)
#define REMOTE_MAC_BYTE1            (0x00)	
#define REMOTE_MAC_BYTE2            (0x1E)	
#define REMOTE_MAC_BYTE3            (0x33)	
#define REMOTE_MAC_BYTE4            (0xC9)	
#define REMOTE_MAC_BYTE5            (0xD6)	
#define REMOTE_MAC_BYTE6            (0xAA)	

/* ---------- Threads configuration ---------- */
#ifndef NO_SYS
#define NO_SYS                  1			/* single thread */
#endif

/* ---------- Memory options ---------- */
#ifndef MEM_ALIGNMENT
#define MEM_ALIGNMENT           4
#endif
#ifndef MEM_SIZE
#define MEM_SIZE                64*1024
#endif
#ifndef MEMP_NUM_PBUF
#define MEMP_NUM_PBUF           32
#endif
#ifndef MEMP_NUM_SYS_TIMEOUT 
#define MEMP_NUM_SYS_TIMEOUT    0
#endif
//#define MEMP_NUM_PBUF                   16
//#define MEMP_NUM_RAW_PCB                4
//#define MEMP_NUM_UDP_PCB                4
//#define MEMP_NUM_TCP_PCB                10          // default 5
//#define MEMP_NUM_TCP_PCB_LISTEN         8
//#define MEMP_NUM_TCP_SEG                16
//#define MEMP_NUM_REASSDATA              5
//#define MEMP_NUM_ARP_QUEUE              30
//#define MEMP_NUM_IGMP_GROUP             8
//#define MEMP_NUM_SYS_TIMEOUT            3
//#define MEMP_NUM_TCPIP_MSG_API          8
//#define MEMP_NUM_TCPIP_MSG_INPKT        8
//#define PBUF_POOL_SIZE                  16

/* The following four are used only with the sequential API and can be
   set to 0 if the application only will use the raw API. */
//#define MEMP_NUM_NETBUF                 2
//#define MEMP_NUM_NETCONN                4
#ifndef MEMP_NUM_NETBUF
#define MEMP_NUM_NETBUF         0
#endif
#ifndef MEMP_NUM_NETCONN
#define MEMP_NUM_NETCONN        0
#endif
//#define MEMP_NUM_API_MSG        0
//#define MEMP_NUM_TCPIP_MSG      0

/* ---------- Pbuf options ---------- */
#ifndef PBUF_POOL_SIZE
#define PBUF_POOL_SIZE          32
#endif
#ifndef PBUF_POOL_BUFSIZE
#define PBUF_POOL_BUFSIZE       1536
#endif
#ifndef PBUF_LINK_HLEN
#define PBUF_LINK_HLEN          16
#endif

/* ---------- ARP options ---------- */
#ifndef ARP_QUEUEING
#define ARP_QUEUEING            0
#endif
//#define ETHARP_ALWAYS_INSERT    0
//#define LWIP_ARP                        1
//#define ARP_TABLE_SIZE                  10
//#define ARP_QUEUEING                    1
//#define ETHARP_TRUST_IP_MAC             1

/* ---------- IP options ---------- */
//#define IP_FORWARD                      0
//#define IP_OPTIONS_ALLOWED              1
//#define IP_REASSEMBLY                   0           // default is 1
//#define IP_FRAG                         0           // default is 1
//#define IP_REASS_MAXAGE                 3
//#define IP_REASS_MAX_PBUFS              10
//#define IP_FRAG_USES_STATIC_BUF         1
//#define IP_FRAG_MAX_MTU                 1500
//#define IP_DEFAULT_TTL                  255

/* ---------- ICMP options ---------- */
//#define LWIP_ICMP                       1
//#define ICMP_TTL                       (IP_DEFAULT_TTL)

/* ---------- RAW options ---------- */
//#define LWIP_RAW                        1
//#define RAW_TTL                        (IP_DEFAULT_TTL)

/* ---------- DHCP options ---------- */
#ifndef LWIP_DHCP
#define LWIP_DHCP               1
#endif
//#define DHCP_DOES_ARP_CHECK             ((LWIP_DHCP) && (LWIP_ARP))

/* ---------- UDP options ---------- */
#ifndef LWIP_UDP
#define LWIP_UDP                1
#endif

/* ---------- TCP options ---------- */
#define LWIP_TCP                1
#define TCP_MSS                 1460
#define TCP_SND_BUF             4096

/* ---------- Callbacks ---------- */
#ifndef LWIP_CALLBACK_API
#define LWIP_CALLBACK_API       1
#endif

/* ---------- Statistics options ---------- */
#ifndef LWIP_STATS
#define LWIP_STATS              0
#endif

/* ---------- Netconn ---------- */
#ifndef LWIP_NETCONN
#define LWIP_NETCONN            0           // default is 1
#endif

/* ---------- Socket ---------- */
#ifndef LWIP_SOCKET
#define LWIP_SOCKET             0           // default is 1
#endif

/* ---------- Ethernet ---------- */
#ifndef ETH_PAD_SIZE
#define ETH_PAD_SIZE			0
#endif

/* ---------- UPNP options ---------- */
//#define LWIP_UPNP                       0

/* ---------- PTPD options ---------- */
//#define LWIP_PTPD                       0

/* ---------- DEBUG options ---------- */
#define ETHARP_DEBUG                    LWIP_DBG_ON     // default is OFF
#define NETIF_DEBUG                     LWIP_DBG_ON     // default is OFF
#define PBUF_DEBUG                      LWIP_DBG_ON		// default is OFF
//#define API_LIB_DEBUG                   LWIP_DBG_OFF
//#define API_MSG_DEBUG                   LWIP_DBG_OFF
//#define SOCKETS_DEBUG                   LWIP_DBG_OFF
//#define ICMP_DEBUG                      LWIP_DBG_OFF
//#define IGMP_DEBUG                      LWIP_DBG_OFF
//#define INET_DEBUG                      LWIP_DBG_OFF
#define IP_DEBUG                        LWIP_DBG_ON     // default is OFF
//#define IP_REASS_DEBUG                  LWIP_DBG_OFF
//#define RAW_DEBUG                       LWIP_DBG_OFF
//#define MEM_DEBUG                       LWIP_DBG_OFF
//#define MEMP_DEBUG                      LWIP_DBG_OFF
//#define SYS_DEBUG                       LWIP_DBG_OFF
#define TCP_DEBUG                       LWIP_DBG_ON
//#define TCP_INPUT_DEBUG                 LWIP_DBG_OFF
//#define TCP_FR_DEBUG                    LWIP_DBG_OFF
//#define TCP_RTO_DEBUG                   LWIP_DBG_OFF
//#define TCP_CWND_DEBUG                  LWIP_DBG_OFF
//#define TCP_WND_DEBUG                   LWIP_DBG_OFF
//#define TCP_OUTPUT_DEBUG                LWIP_DBG_OFF
//#define TCP_RST_DEBUG                   LWIP_DBG_OFF
//#define TCP_QLEN_DEBUG                  LWIP_DBG_OFF
#define UDP_DEBUG                       LWIP_DBG_ON     // default is OFF
//#define TCPIP_DEBUG                     LWIP_DBG_OFF
//#define PPP_DEBUG                       LWIP_DBG_OFF
//#define SLIP_DEBUG                      LWIP_DBG_OFF
//#define DHCP_DEBUG                      LWIP_DBG_ON     // default is OFF
//#define AUTOIP_DEBUG                    LWIP_DBG_OFF
//#define SNMP_MSG_DEBUG                  LWIP_DBG_OFF
//#define SNMP_MIB_DEBUG                  LWIP_DBG_OFF
//#define DNS_DEBUG                       LWIP_DBG_OFF

#endif /* __LWIPOPTS_EE_H__ */
