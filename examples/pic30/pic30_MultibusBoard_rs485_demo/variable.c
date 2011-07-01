/*
 * variable.c
 *
 * Global variables
 */

#include "./define.h"

// no malloc()
unsigned char	__uart1_rx_buf[SIZE_OF_UART1_RX_BUF];
unsigned char	__uart1_tx_buf[SIZE_OF_UART1_TX_BUF];
unsigned char	__uart2_rx_buf[SIZE_OF_UART2_RX_BUF];
unsigned char	__uart2_tx_buf[SIZE_OF_UART2_TX_BUF];
unsigned char	__debug_cmd_buf[SIZE_OF_DEBUG_CMD_BUF];

RingBuf	UART1RXBuf;
RingBuf	UART1TXBuf;
RingBuf	UART2RXBuf;
RingBuf	UART2TXBuf;
RingBuf	DebugCmdBuf;

// global flags
unsigned char	UART1TX_INT_Enabled;
unsigned char	UART2TX_INT_Enabled;

void initBuffers()
{
	RingBuf	*pBuf;

	// RF RX buffer
	pBuf = &UART1RXBuf;
	pBuf->size = SIZE_OF_UART1_RX_BUF;
	// no malloc()
	//pBuf->buffer = (unsigned char *)malloc( pBuf->size);
	pBuf->buffer = __uart1_rx_buf;
	pBuf->head = 0;
	pBuf->tail = 0;
	pBuf->count = 0;

	// RF TX buffer
	pBuf = &UART1TXBuf;
	pBuf->size = SIZE_OF_UART1_TX_BUF;
	// no malloc()
	//pBuf->buffer = (unsigned char *)malloc( pBuf->size);
	pBuf->buffer = __uart1_tx_buf;
	pBuf->head = 0;
	pBuf->tail = 0;
	pBuf->count = 0;

	// Serial port RX buffer
	pBuf = &UART2RXBuf;
	pBuf->size = SIZE_OF_UART1_RX_BUF;
	// no malloc()
	//pBuf->buffer = (unsigned char *)malloc( pBuf->size);
	pBuf->buffer = __uart2_rx_buf;
	pBuf->head = 0;
	pBuf->tail = 0;
	pBuf->count = 0;

	// Serial port TX buffer
	pBuf = &UART2TXBuf;
	pBuf->size = SIZE_OF_UART2_TX_BUF;
	// no malloc()
	//pBuf->buffer = (unsigned char *)malloc( pBuf->size);
	pBuf->buffer = __uart2_tx_buf;
	pBuf->head = 0;
	pBuf->tail = 0;
	pBuf->count = 0;

	// Debug CMD buffer
	pBuf = &DebugCmdBuf;
	pBuf->size = SIZE_OF_DEBUG_CMD_BUF;
	// no malloc()
	//pBuf->buffer = (unsigned char *)malloc( pBuf->size);
	pBuf->buffer = __debug_cmd_buf;
	pBuf->head = 0;
	pBuf->tail = 0;
	pBuf->count = 0;
}

void	InitVariables()
{
	initBuffers();

	// UART TX INT
	UART1TX_INT_Enabled = DPS_FALSE;
	UART2TX_INT_Enabled = DPS_FALSE;
}


