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

/* MAC ADDRESS */
// #define MY_DEFAULT_MAC_BYTE1            (0x00)	// Use the default of
// #define MY_DEFAULT_MAC_BYTE2            (0x04)	// 00-04-A3-00-00-00 if using
// #define MY_DEFAULT_MAC_BYTE3            (0xA3)	// an ENCX24J600 or ZeroG ZG2100
// #define MY_DEFAULT_MAC_BYTE4            (0x00)	// and wish to use the internal
// #define MY_DEFAULT_MAC_BYTE5            (0x00)	// factory programmed MAC
// #define MY_DEFAULT_MAC_BYTE6            (0x00)	// address instead.

#define mydevice_init() 				EE_enc28j60_init()
#define mydevice_initiate_transfer()	EE_enc28j60_transfer_init()
#define mydevice_write(data, len)		EE_enc28j60_write(data, len)
#define mydevice_read(data, len)		EE_enc28j60_read(data, len)
#define mydevice_signal(len)			EE_enc28j60_signal(len)
#define mydevice_ack()					EE_enc28j60_ack()
#define mydevice_drop_packet()			EE_enc28j60_drop_packet()

#ifdef LWIP_DEBUG
#include <util/lwip_debug.h> //TODO: REMOVE together with the sprintf() !!!!!
//#include <stdio.h> //TODO: REMOVE together with the sprintf() !!!!!
#endif

#endif /* Header Protection */
