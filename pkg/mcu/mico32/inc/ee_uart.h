/** 
* ee_uart.h
*/

#ifndef __INCLUDE_EEMCUMICO32_UART_H__
#define __INCLUDE_EEMCUMICO32_UART_H__

#include <cpu/mico32/inc/ee_irq.h>
#include <system_conf.h>
#include <mcu/mico32/inc/ee_buffer.h>
#include "mcu/mico32/inc/ee_uart_internal.h"

/****************************************************************
     *                                                  
     * UART Device Register-map                          
     *                                                   
*****************************************************************/
//    typedef struct st_MicoUart{
//        volatile unsigned int rxtx;
//        volatile unsigned int ier;
//        volatile unsigned int iir;
//        volatile unsigned int lcr;
//        volatile unsigned int mcr;
//        volatile unsigned int lsr;
//        volatile unsigned int msr;
//        volatile unsigned int div;
//    }MicoUart_t;

/*************************************************** 
* Symbols and macros definition
****************************************************/
#define EE_UART_MSGSIZE 	(1)		
#define EE_UART_BUFSIZE 	(12)

/* Uart settings */
#define EE_UART_BIT8_ODD	(0x0B)
#define EE_UART_BIT8_EVEN	(0x1B)
#define EE_UART_BIT8_NO		(0x03)

#define EE_UART_BIT7_ODD	(0x0A)
#define EE_UART_BIT7_EVEN	(0x1A)
#define EE_UART_BIT7_NO		(0x02)

#define EE_UART_BIT6_ODD	(0x09)
#define EE_UART_BIT6_EVEN	(0x19)
#define EE_UART_BIT6_NO		(0x01)

#define EE_UART_BIT5_ODD	(0x08)
#define EE_UART_BIT5_EVEN	(0x18)
#define EE_UART_BIT5_NO		(0x00)

#define EE_UART_BIT_STOP_1	(0x00)
#define EE_UART_BIT_STOP_2	(0x04)

/* Uart operating modes */
#define EE_UART_POLLING		(0x00)
#define EE_UART_RX_ISR		(0x01)
#define EE_UART_TX_ISR		(0x02)	
#define EE_UART_RXTX_ISR	(0x03)	

#define EE_uart_need_init_rx_buf(old,new)  ( !((old) & EE_UART_RX_ISR) && ((new) & EE_UART_RX_ISR) )
#define EE_uart_need_init_tx_buf(old,new)  ( !((old) & EE_UART_TX_ISR) && ((new) & EE_UART_TX_ISR) )
#define EE_uart_need_enable_rx_int(new)  ( (new) & EE_UART_RX_ISR )
#define EE_uart_tx_polling(mode) ( !((mode) & EE_UART_TX_ISR) )
#define EE_uart_rx_polling(mode) ( !((mode) & EE_UART_RX_ISR) )

/* Uart utils */
#define EE_UART_NULL_VET			((char *)0)
#define EE_UART_NULL_CBK			((EE_ISR_callback)0)

/* Uart return values */
#define EE_UART_OK					(0x00)
#define EE_UART_ERR_RECEPTION   	(-5)
#define EE_UART_ERR_TRANSMISSION	(-6)
#define EE_UART_ERR_BAD_VALUE		(-7)

#endif // __INCLUDE_EEMCUMICO32_UART_H__

/****************************************************
* Notes
*****************************************************/
// _MICOUART_FILESUPPORT_DISABLED_
// _MICOUART_NO_INTERRUPTS_
