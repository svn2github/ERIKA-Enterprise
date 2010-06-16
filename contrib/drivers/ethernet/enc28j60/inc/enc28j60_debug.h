/*
  Name: enc28j60_debug.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: ENC28J60 debug macros
*/


#ifndef __ENC28J60_DEBUG_H__
#define __ENC28J60_DEBUG_H__

#ifdef ENC28J60_DEBUG

#include <stdio.h>
#include <string.h>

#ifdef ENC28J60_DEBUG_SERIAL

#include "console_serial.h"

#ifndef ENC28J60_DEBUG_SERIAL_PORT
#define ENC28J60_DEBUG_SERIAL_PORT 1
#endif

#ifndef ENC28J60_DEBUG_SERIAL_PORT 
#define ENC28J60_DEBUG_SERIAL_PORT 	CONSOLE_SERIAL_PORT_1		
#endif

#ifndef ENC28J60_DEBUG_SERIAL_BAUDRATE 
#define ENC28J60_DEBUG_SERIAL_BAUDRATE 	115200 
#endif

#ifndef ENC28J60_DEBUG_SERIAL_OPT
#define ENC28J60_DEBUG_SERIAL_OPT (CONSOLE_SERIAL_FLAG_BIT8_NO | CONSOLE_SERIAL_FLAG_BIT_STOP1)
#endif

#endif	//ENC28J60_DEBUG_SERIAL

#ifndef ENC28J60_STRING_MAXSIZE
#define ENC28J60_STRING_MAXSIZE 64
#endif

extern uint8_t ee_enc28j60_db_msg[ENC28J60_STRING_MAXSIZE];

#ifndef ENC28J60_DEBUG_PORT
#define ENC28J60_DEBUG_PORT 0
#endif

#define enc28j60_dbg_print(msg) console_write(ENC28J60_DEBUG_PORT, (uint8_t*) msg, strlen((char*)msg))
#define enc28j60_dbg_set_msg(str,val) sprintf((char*)ee_enc28j60_db_msg, str, val)

#else	//ENC28J60_DEBUG

#define	enc28j60_dbg_print(msg)
#define enc28j60_dbg_set_msg(str,val)

#endif	//ENC28J60_DEBUG

#endif	//__ENC28J60_DEBUG_H__