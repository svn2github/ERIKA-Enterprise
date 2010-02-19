/** 
* ee_uart.h
*/

#ifndef __INCLUDE_EEMCUMICO32_UART_H__
#define __INCLUDE_EEMCUMICO32_UART_H__

#include "ee.h"							// to refer Erika Enterprise.
#include "cpu/mico32/inc/ee_irq.h"
#include <system_conf.h>
#include "MicoUart.h"					// to use LATTICE data structures.
#include "mcu/mico32/inc/ee_buffer.h"
#include "mcu/mico32/inc/ee_uart1.h"	// to use Uart0 functions.
//#include "mcu/mico32/inc/ee_uart2.h"	// to use Uart1 functions.


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
#ifndef EE_MICO32_CBK_DEFINED
#define EE_MICO32_CBK_DEFINED
typedef void (*EE_mico32_ISR_callback)(void);
#endif

typedef struct {
	int over;
	int ie;
    MicoUart_t* base;
    EE_mico32_ISR_callback rxcbk;
    EE_mico32_ISR_callback txcbk;
    EE_buffer rxbuf;
    EE_buffer txbuf;
} EE_uart_st;

extern EE_uart_st ee_uart1_st;		// UART1 structure
extern EE_uart_st ee_uart2_st;		// UART2 structure

#define EE_UART_MSGSIZE 	(1)		
#define EE_UART_BUFSIZE 	(4)
extern char ee_uart_isr_rxvet[EE_UART_BUFSIZE];
extern char ee_uart_isr_txvet[EE_UART_BUFSIZE];

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

#define EE_UART_POLLING_MODE		(0xC0)
#define EE_UART_ISR_RX				(0xC1)
#define EE_UART_ISR_TX				(0xC2)
#define EE_UART_ISR_RXTX			(0xC3)

#define EE_UART_NULL_BUF			((EE_buffer *)0)
#define EE_UART_NULL_VET			((char *)0)
#define EE_UART_NULL_CBK			((EE_mico32_ISR_callback)0)

#define EE_UART_OK					(0x00)
#define EE_UART_ERR_RECEPTION   	(-5)
#define EE_UART_ERR_TRANSMISSION	(-6)
#define EE_UART_ERR_BAD_VALUE		(-7)

/*************************************************** 
* Functions declarations
****************************************************/

// User API:
#define EE_uart_init(name, br, set, ief, rx_isrcbk, tx_isrcbk)  EE_uart_init_base((MicoUart_t*)(name##_BASE_ADDRESS), (name##_IRQ), (br), (set), (ief), (rx_isrcbk), (tx_isrcbk))
//#define EE_uart_set_ISR_callback(name, rx_isrcbk, tx_isrcbk, rx_buf, tx_buf) 	EE_uart_set_ISR_callback_base((name##_BASE_ADDRESS), (name##_IRQ), (rx_isrcbk), (tx_isrcbk), (rx_buf), (tx_buf))
#define EE_uart_write_byte(name, val) 							EE_uart_write_byte_base((MicoUart_t*)(name##_BASE_ADDRESS), (val))
#define EE_uart_read_byte(name, addval) 						EE_uart_read_byte_base((MicoUart_t*)(name##_BASE_ADDRESS), (addval))
#define EE_uart_write_buffer(name, vet, len) 					EE_uart_write_buffer_base((MicoUart_t*)(name##_BASE_ADDRESS), (vet), (len))
#define EE_uart_read_buffer(name, vet, len) 					EE_uart_read_buffer_base((MicoUart_t*)(name##_BASE_ADDRESS), (vet), (len))

/* Internal functions */
int EE_uart_init_base(MicoUart_t* base, int irq_flag, int baudrate, unsigned int settings, int ie_flag, EE_mico32_ISR_callback isr_rx_callback, EE_mico32_ISR_callback isr_tx_callback);
int EE_uart_set_ISR_callback_base(MicoUart_t* base, int irq_flag, int ie_flag, EE_mico32_ISR_callback isr_rx_callback, EE_mico32_ISR_callback isr_tx_callback);
int EE_uart_write_byte_base(MicoUart_t* base, char data);
int EE_uart_read_byte_base(MicoUart_t* base, char *data);
int EE_uart_read_buffer_base(MicoUart_t* base, char *vet, int len);
int EE_uart_write_buffer_base(MicoUart_t* base, char *vet, int len);
//int EE_uart_disable_base(MicoUart_t* base);		ATT! not implemented! 
//int EE_uart_enable_base(MicoUart_t* base);		ATT! not implemented!
//int EE_uart_start_base(MicoUart_t* base);			ATT! not implemented!
//int EE_uart_stop_base(MicoUart_t* base);			ATT! not implemented!
void EE_uart_handler(EE_uart_st* usp);

#endif // __INCLUDE_EEMCUMICO32_UART_H__

/****************************************************
* Notes
*****************************************************/
// _MICOUART_FILESUPPORT_DISABLED_
// _MICOUART_NO_INTERRUPTS_
