/** 
* ee_uart.h
*/

#ifndef __INCLUDE_EEMCUMICO32_UART_H__
#define __INCLUDE_EEMCUMICO32_UART_H__

#include "ee.h"						// to refer Erika Enterprise.
#include "cpu/mico32/inc/ee_irq.h"
#include <system_conf.h>
#include "MicoUart.h"				// to use LATTICE data structures.
#include "mcu/mico32/inc/ee_buffer.h"
#include "mcu/mico32/inc/ee_uart1.h"	// to use Uart0 functions.
#include "mcu/mico32/inc/ee_uart2.h"	// to use Uart1 functions.


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
    EE_UINT32 base;
    EE_mico32_ISR_callback rxcbk;
    EE_mico32_ISR_callback txcbk;
    EE_buffer* rxbuf;
    EE_buffer* txbuf;
} EE_uart_st;

extern EE_uart_st ee_uart_st_1;
extern EE_uart_st ee_uart_st_2;

//#define EE_UART_BIT9		0x06
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

//#define EE_UART_CTRL_SIMPLE	0x00
//#define EE_UART_CTRL_FLOW		0x01
//#define EE_UART_TX_INT_SINGLE	0x8000
//#define EE_UART_TX_INT_EMPTY	0x2000
//#define EE_UART_TX_INT_LAST	0x0000
//#define EE_UART_RX_INT_FULL	0x00C0
//#define EE_UART_RX_INT_3OF4	0x0080
//#define EE_UART_RX_INT_SINGLE	0x0040
//#define EE_UART_ERR_BAD_PORT		1
//#define EE_UART_ERR_NO_DATA		2
//#define EE_UART_ERR_OVERFLOW		3
//#define EE_UART_ERR_INT_MODE		4
//#define EE_UART_ERR_INT_DISABLED	5
//#ifndef EE_UART_INSTRUCTION_CLOCK
//#define EE_UART_INSTRUCTION_CLOCK	40000000ul
//#endif

#define EE_UART_POLLING_MODE		(0xC0)
#define EE_UART_ISR_MODE			(0xC1)
#define EE_UART_NULL_BUF			((EE_buffer *)0)
#define EE_UART_NULL_VET			((EE_INT8 *)0)

#define EE_UART_OK					(0x00)
#define EE_UART_ERR_RECEPTION   	(0xE1)
#define EE_UART_ERR_TRANSMISSION	(0xE2)
#define EE_UART_ERR_BAD_VALUE		(0xE3)

#define EE_uart_init(name, per, set) 							EE_uart_init_base((name##_BASE_ADDRESS), (per), (set))
#define EE_uart_set_ISR_callback(name, rx_isrcbk, tx_isrcbk, rx_buf, tx_buf) 	EE_uart_set_ISR_callback_base((name##_BASE_ADDRESS), (name##_IRQ), (rx_isrcbk), (tx_isrcbk), (rx_buf), (tx_buf))
#define EE_uart_close(name) 									EE_uart_close_base((name##_BASE_ADDRESS))
#define EE_uart_write_byte(name, val) 							EE_uart_write_byte_base((name##_BASE_ADDRESS), (val))
#define EE_uart_read_byte(name, addval) 						EE_uart_read_byte_base((name##_BASE_ADDRESS), (addval))
#define EE_uart_write_buffer(name, vet, len) 					EE_uart_write_buffer_base((name##_BASE_ADDRESS), (vet), (len))
#define EE_uart_read_buffer(name, vet, len) 					EE_uart_read_buffer_base((name##_BASE_ADDRESS), (vet), (len))

/*************************************************** 
* Functions declarations
****************************************************/
EE_UINT8 EE_uart_init_base(EE_UINT32 base, EE_UINT32 baudrate, EE_UINT32 settings);
EE_UINT8 EE_uart_set_ISR_callback_base(EE_UINT32 base, EE_UINT32 irq_flag, EE_mico32_ISR_handler isr_rx_callback, EE_mico32_ISR_handler isr_tx_callback, EE_buffer* rx_buf, EE_buffer* tx_buf);
EE_UINT8 EE_uart_close_base(EE_UINT32 base);
EE_UINT8 EE_uart_write_byte_base(EE_UINT32 base, EE_INT8 data);
EE_UINT8 EE_uart_read_byte_base(EE_UINT32 base, EE_INT8 *data);
EE_UINT8 EE_uart_read_buffer_base(EE_UINT32 base, EE_INT8 *vet, EE_INT16 len);
EE_UINT8 EE_uart_write_buffer_base(EE_UINT32 base, EE_INT8 *vet, EE_INT16 len);
void EE_uart_handler(EE_uart_st* usp);

#endif // __INCLUDE_EEMCUMICO32_UART_H__
