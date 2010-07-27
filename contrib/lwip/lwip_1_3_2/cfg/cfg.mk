## Author: 2010 Dario Di Stefano 

## Check the Console library selection
ifeq ($(findstring __LIB_LWIP__,$(LIB_OPT)),__LIB_LWIP__)

##
## Application files
##

# core ipv4
ifeq ($(findstring __LWIP_IPV4__,$(EEOPT)) , __LWIP_IPV4__)
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv4/autoip.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv4/icmp.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv4/igmp.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv4/inet.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv4/inet_chksum.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv4/ip.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv4/ip_addr.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv4/ip_frag.c
endif

# core ipv6
ifeq ($(findstring __LWIP_IPV6__,$(EEOPT)) , __LWIP_IPV6__)
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv6/icmp6.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv6/inet6.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv6/ip6.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv6/ip6_addr.c
endif

# core snmp
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/snmp/asn1_dec.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/snmp/asn1_enc.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/snmp/mib2.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/snmp/mib_structs.c 
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/snmp/msg_in.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/snmp/msg_out.c

# ARP
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/etharp.c  

# LOOP
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/loopif.c  

# SLIP
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/slipif.c

# api
EE_SRCS += contrib/lwip/lwip_1_3_2/src/api/api_lib.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/api/api_msg.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/api/err.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/api/netbuf.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/api/netdb.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/api/netifapi.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/api/sockets.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/api/tcpip.c

# core
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/dhcp.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/dns.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/init.c   
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/mem.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/memp.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/netif.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/pbuf.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/raw.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/stats.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/sys.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/tcp.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/tcp_in.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/tcp_out.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/udp.c

# ppp
ifeq ($(findstring __LWIP_PPP_SUPPORT__,$(EEOPT)) , __LWIP_PPP_SUPPORT__)
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/auth.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/chap.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/chpms.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/fsm.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/ipcp.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/lcp.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/magic.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/md5.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/pap.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/ppp.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/ppp_oe.c    
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/randm.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/vj.c 
endif

# LWIP manager
EE_SRCS += contrib/lwip/lwip_1_3_2/abstraction/src/ee_lwip.c
EE_SRCS += contrib/lwip/lwip_1_3_2/abstraction/src/util/lwip_debug.c

# Ethernet interface
EE_SRCS += contrib/lwip/lwip_1_3_2/abstraction/src/hal/lwip_ethernet.c
EE_SRCS += contrib/lwip/lwip_1_3_2/abstraction/src/hal/lwip_timer.c

# enc28j60
ifeq ($(findstring __LIB_ENC28J60__,$(LIB_OPT)),__LIB_ENC28J60__)
EE_SRCS += contrib/lwip/lwip_1_3_2/abstraction/src/hal/lwip_enc28j60.c
endif

# lm32
ifeq ($(findstring __LM32__,$(EEOPT)) , __LM32__)
EE_SRCS += contrib/lwip/lwip_1_3_2/abstraction/src/hal/lwip_timer_mico32.c
endif

ifeq ($(findstring __PIC32__,$(EEOPT)) , __PIC32__)
EE_SRCS += contrib/lwip/lwip_1_3_2/abstraction/src/hal/lwip_timer_pic32.c
endif

endif
