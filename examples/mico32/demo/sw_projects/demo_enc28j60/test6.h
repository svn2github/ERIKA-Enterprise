/*
  Name: test6.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: ENC28J60 test.
*/

#ifndef __TEST6_H__
#define __TEST6_H__

/* RT-Kernel */
#include <ee.h>

/* Mecros used in the application code */
#define SIZE_OF_ETH_HEADER 			(14)
#define SIZE_OF_IP_HEADER 			(20)
#define SIZE_OF_UDP_HEADER 			(8)
#define SIZE_OF_PAYLOAD 			(4)

#define turn_on_led() 				EE_misc_gpio_write_bit_data(1,EE_DL3_BIT)
#define turn_off_led() 				EE_misc_gpio_write_bit_data(0,EE_DL3_BIT)

#define ETHTYPE_ARP       			(0x0806)
#define ETHTYPE_IP        			(0x0800)

#define myIPaddress					(0xc0a80001)
#define myPort						(9762)

#define remoteIPaddress				(0xc0a80002)
#define remotePort					(9760)

#define REMOTE_MAC_BYTE1           	(0x00)	// Use the default of
#define REMOTE_MAC_BYTE2           	(0x04)	// 00-04-A3-00-00-00 if using
#define REMOTE_MAC_BYTE3           	(0xA3)	// an ENCX24J600 or ZeroG ZG2100
#define REMOTE_MAC_BYTE4           	(0x00)	// and wish to use the internal
#define REMOTE_MAC_BYTE5           	(0x00)	// factory programmed MAC
#define REMOTE_MAC_BYTE6           	(0x00)	// address instead.

#define MSG_BYTE1					(0x00)
#define MSG_BYTE2					(0x00)
#define MSG_BYTE3					(0x80)
#define MSG_BYTE4					(0x40)

#define UDP_CHKSUM					(0xB1FF)
#define UDP_LEN						(0x000c)
#define IP_ID						(0xD5CD)
#define TTL_PROTO					(0x8011)
#define IP_CHKSUM					(0xe3ab)

/* Types used in the application code */
typedef EE_UINT8 u8_t;		/**< Unsigned 8 bit intgerer. */
typedef EE_UINT16 u16_t;	/**< Unsigned 16 bit intgerer. */
typedef EE_UINT32 u32_t;	/**< Unsigned 32 bit intgerer. */
typedef EE_INT8 s8_t;		/**< Unsigned 8 bit intgerer. */
typedef EE_INT16 s16_t;		/**< Unsigned 16 bit intgerer. */
typedef EE_INT32 s32_t;		/**< Unsigned 32 bit intgerer. */

typedef struct ip_addr_t {
  u32_t addr;
} ip_addr;

typedef struct udp_hdr_t {
  u16_t src;
  u16_t dest;  /* src/dest UDP ports */
  u16_t len;
  u16_t chksum;
} udp_hdr;

typedef struct ip_hdr_t {
  /* version / header length / type of service */
  u16_t _v_hl_tos;
  /* total length */
  u16_t _len;
  /* identification */
  u16_t _id;
  /* fragment offset field */
  u16_t _offset;
  /* time to live / protocol*/
  u16_t _ttl_proto;
  /* checksum */
  u16_t _chksum;
  /* source and destination IP addresses */
  ip_addr src;
  ip_addr dest; 
} ip_hdr;

typedef struct eth_addr_t {
  u8_t addr[6];
} eth_addr;

typedef struct eth_hdr_t {
  eth_addr dest;
  eth_addr src;
  u16_t type;
} eth_hdr;

typedef struct payload_t {
  u8_t v[SIZE_OF_PAYLOAD];
} payload;

typedef struct packet_t{
	u8_t v[SIZE_OF_ETH_HEADER + SIZE_OF_IP_HEADER + SIZE_OF_UDP_HEADER + SIZE_OF_PAYLOAD];
} packet;


/* Functions used in the application code */
void system_timer_callback(void);
int print_string(const char *s);
void print_val(char* s, int val);
void print_vals(char* s, int val1, int val2);
void enc28j60_send(BYTE* pkt, int len);
int enc28j60_receive(BYTE* udp_data);


#endif //__TEST6_H__
