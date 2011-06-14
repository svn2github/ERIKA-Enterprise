#ifndef	__DRIVER_H__
#define	__DRIVER_H__

extern void EE_UART1_Init(EE_UINT32 baud, EE_UINT16 byteformat, EE_UINT16 mode);
extern void EE_UART1_SetCallback(EE_INT8 (*RxFunc)(EE_UINT8 data), EE_INT8 (*TxFunc)(EE_UINT8 data), EE_UINT8 rxmode, EE_UINT8 txmode);
extern EE_INT8 EE_UART1_Send(unsigned char data);
extern EE_INT8 EE_UART1_Receive(unsigned char* data);

extern void EE_UART2_Init(EE_UINT32 baud, EE_UINT16 byteformat, EE_UINT16 mode);
extern void EE_UART2_SetCallback(EE_INT8 (*RxFunc)(EE_UINT8 data), EE_INT8 (*TxFunc)(EE_UINT8 data), EE_UINT8 rxmode, EE_UINT8 txmode);
extern EE_INT8 EE_UART2_Send(unsigned char data);
extern EE_INT8 EE_UART2_Receive(unsigned char* data);

extern void	T1_program();
extern void	T1_clear();
#endif
