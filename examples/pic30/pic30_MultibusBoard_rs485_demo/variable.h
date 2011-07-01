#ifndef	__VARIABLE_H__
#define	__VARIABLE_H__

extern unsigned char	__uart1_rx_buf[SIZE_OF_UART1_RX_BUF];
extern unsigned char	__uart1_tx_buf[SIZE_OF_UART1_TX_BUF];
extern unsigned char	__uart2_rx_buf[SIZE_OF_UART2_RX_BUF];
extern unsigned char	__uart2_tx_buf[SIZE_OF_UART2_TX_BUF];
extern unsigned char	__debug_cmd_buf[SIZE_OF_DEBUG_CMD_BUF];

extern RingBuf	UART1RXBuf;
extern RingBuf	UART1TXBuf;
extern RingBuf	UART2RXBuf;
extern RingBuf	UART2TXBuf;
extern RingBuf	DebugCmdBuf;

extern unsigned char	UART1TX_INT_Enabled;
extern unsigned char	UART2TX_INT_Enabled;

extern void InitVariables();

#endif
