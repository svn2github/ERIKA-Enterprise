#ifdef __USE_SCI__

#ifndef __INCLUDE_FREESCALE_S12XS_SCI_H__
#define __INCLUDE_FREESCALE_S12XS_SCI_H__

#include "ee.h"

/* Include a file with the registers from Microchip C30 distribution */ 
#ifdef __S12XS_INCLUDE_REGS__
#include "ee_hs12xsregs.h"
#endif

//#define EE_UART_BIT9		0x06
//#define EE_UART_BIT8_ODD	0x04
//#define EE_UART_BIT8_EVEN	0x02
//#define EE_UART_BIT8_NO		0x00
//
//#define EE_UART_BIT_STOP_1	0x00
//#define EE_UART_BIT_STOP_2	0x01
//
//#define EE_UART_CTRL_SIMPLE	0x00
//#define EE_UART_CTRL_FLOW	0x01
//
//#define EE_UART_TX_INT_SINGLE	0x8000
//#define EE_UART_TX_INT_EMPTY	0x2000
//#define EE_UART_TX_INT_LAST	0x0000
//
//#define EE_UART_RX_INT_FULL	0x00C0
//#define EE_UART_RX_INT_3OF4	0x0080
//#define EE_UART_RX_INT_SINGLE	0x0040
//
//#define EE_UART_PORT_1	0
//#define EE_UART_PORT_2	1
//
//#define EE_UART_ERR_BAD_PORT		1
//#define EE_UART_ERR_NO_DATA		2
//#define EE_UART_ERR_OVERFLOW		3
//#define EE_UART_ERR_INT_MODE		4
//#define EE_UART_ERR_INT_DISABLED	5
//
//#ifndef EE_UART_INSTRUCTION_CLOCK
//#define EE_UART_INSTRUCTION_CLOCK	2500000ul
//#endif

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
#define SCI_0             0
#define SCI_1             1

#define SCIBDH            0x00
#define SCIBDL            0x01
#define SCICR1            0x02
#define SCIASR1           0x00
#define SCIACR1           0x01
#define SCIACR2           0x02
#define SCICR2            0x03
#define SCISR1            0x04
#define SCISR2            0x05
#define SCIDRH            0x06
#define SCIDRL            0x07

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
void EE_SCIOpenCommunication(unsigned char sci_num);
void EE_SCICloseCommunication(unsigned char sci_num);
Bool EE_SCISendBuffer(unsigned char sci_num, unsigned char buffer);
Bool EE_SCIGetBuffer(unsigned char sci_num, unsigned char *buffer);
Bool EE_SCICheckGetBuffer(unsigned char sci_num);

#endif

#endif
