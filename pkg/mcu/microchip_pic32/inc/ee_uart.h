#ifndef __INCLUDE_MICROCHIP_PIC32_UART_H__
#define __INCLUDE_MICROCHIP_PIC32_UART_H__

#include "ee.h"

/* Include a file with the registers from Microchip C30 distribution */ 
#ifdef __PIC32_INCLUDE_REGS__
#include "ee_pic32regs.h"
#endif

// NINO - TODO!!!
#define EE_UART_BIT9		0x06
#define EE_UART_BIT8_ODD	0x04
#define EE_UART_BIT8_EVEN	0x02
#define EE_UART_BIT8_NO		0x00

#define EE_UART_BIT_STOP_1	0x00
#define EE_UART_BIT_STOP_2	0x01

#define EE_UART_CTRL_SIMPLE	0x00
#define EE_UART_CTRL_FLOW	0x01

#define EE_UART_TX_INT_SINGLE	0x8000
#define EE_UART_TX_INT_EMPTY	0x2000
#define EE_UART_TX_INT_LAST	0x0000

#define EE_UART_RX_INT_FULL	0x00C0
#define EE_UART_RX_INT_3OF4	0x0080
#define EE_UART_RX_INT_SINGLE	0x0040

#define EE_UART_PORT_1	0
#define EE_UART_PORT_2	1

#define EE_UART_ERR_BAD_PORT		1
#define EE_UART_ERR_NO_DATA		2
#define EE_UART_ERR_OVERFLOW		3
#define EE_UART_ERR_INT_MODE		4
#define EE_UART_ERR_INT_DISABLED	5

#ifndef EE_UART_INSTRUCTION_CLOCK
#define EE_UART_INSTRUCTION_CLOCK	5000000ul
#endif

EE_INT8 EE_uart_init(EE_UINT8 port, EE_UINT32 baud, EE_UINT16 byte_format, 
		     EE_UINT16 mode);
EE_INT8 EE_uart_close(EE_UINT8 port);
EE_INT8 EE_uart_write_byte(EE_UINT8 port, EE_UINT8 data);
EE_INT8 EE_uart_read_byte(EE_UINT8 port, EE_UINT8 *data);
EE_INT8 EE_uart_set_rx_callback(EE_UINT8 port, void (*RxFunc)(EE_UINT8 data), 
				EE_UINT8 rxmode);



#endif
