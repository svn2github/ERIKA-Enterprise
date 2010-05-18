/*
  Name: ee_uart.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.28
  Description: Uart library header file. 
*/

#ifndef __INCLUDE_EEMCUMICO32_UART_H__
#define __INCLUDE_EEMCUMICO32_UART_H__

#define EE_UART_BIT8_ODD    (0x0B)  // 8 bit, odd parity
#define EE_UART_BIT8_EVEN   (0x1B)  // 8 bit, even parity
#define EE_UART_BIT8_NO     (0x03)  // 8 bit, no parity

#define EE_UART_BIT7_ODD    (0x0A)  // 7 bit, odd parity
#define EE_UART_BIT7_EVEN   (0x1A)  // 7 bit, even parity
#define EE_UART_BIT7_NO     (0x02)  // 7 bit, no parity

#define EE_UART_BIT6_ODD    (0x09)  // 6 bit, odd parity
#define EE_UART_BIT6_EVEN   (0x19)  // 6 bit, even parity
#define EE_UART_BIT6_NO     (0x01)  // 6 bit, no parity

#define EE_UART_BIT5_ODD    (0x08)  // 5 bit, odd parity
#define EE_UART_BIT5_EVEN   (0x18)  // 5 bit, even parity
#define EE_UART_BIT5_NO     (0x00)  // 5 bit, no parity

#define EE_UART_BIT_STOP_1  (0x00)  // 1 stop bit
#define EE_UART_BIT_STOP_2  (0x04)  // 2 stop bits

/* Uart operating modes */
#define EE_UART_POLLING     (0x00)  // polling mode
#define EE_UART_RX_ISR      (0x01)  // Reception IRQ enabled 
#define EE_UART_TX_ISR      (0x02)  // Transmission IRQ enabled 
#define EE_UART_RXTX_ISR    (0x03)  // Transmission/Reception IRQ enabled 
#define EE_UART_RX_BLOCK    (0x10)  // Blocking mode in reception
#define EE_UART_TX_BLOCK    (0x20)  // Blocking mode in transmission
#define EE_UART_RXTX_BLOCK  (0x30)  // Blocking mode in transmission/reception

/* Uart return values */
#define EE_UART_OK                  (0x00)
#define EE_UART_ERR_RX_BUF_FULL     (-20)
#define EE_UART_ERR_RX_BUF_EMPTY    (-21)
#define EE_UART_ERR_TX_BUF_FULL     (-22)
#define EE_UART_ERR_TX_BUF_EMPTY    (-23)
#define EE_UART_ERR_BAD_VALUE       (-24)
#define EE_UART_ERR_TX_NOT_READY    (-25)
#define EE_UART_ERR_RX_NOT_READY    (-26)

#include "mcu/mico32/inc/ee_uart_internal.h"

#endif // __INCLUDE_EEMCUMICO32_UART_H__


