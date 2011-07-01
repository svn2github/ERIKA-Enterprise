#ifndef	__DEFINE_H__
#define	__DEFINE_H__

//-----------------------------------------------------------------------------
// General
//-----------------------------------------------------------------------------
#define		DPS_TRUE			1
#define		DPS_FALSE			0

#define		LED_OFF				1
#define		LED_ON				0

// NOTE: No type checking for these macros.
//			Thus, always use without any arguments as follows:
//				 ENTER_CRITICAL_SECTION();
//				 EXIT_CRITICAL_SECTION();
#define		ENTER_CRITICAL_SECTION	EE_hal_disableIRQ
#define		EXIT_CRITICAL_SECTION	EE_hal_enableIRQ

//-----------------------------------------------------------------------------
// Buffers
//-----------------------------------------------------------------------------
#define		SIZE_OF_UART1_RX_BUF		100
#define		SIZE_OF_UART1_TX_BUF		100
#define		SIZE_OF_UART2_RX_BUF		100
#define		SIZE_OF_UART2_TX_BUF		100
#define		SIZE_OF_DEBUG_CMD_BUF		100

//-----------------------------------------------------------------------------
// Debug
//-----------------------------------------------------------------------------
// commands from user console
//	for debugging purposes
#define		CMD_PRINT			0
#define		CMD_SET				1

//-----------------------------------------------------------------------------
// DPS Protocol
//-----------------------------------------------------------------------------
#define		DPS_MSG_SIZE		1

//-----------------------------------------------------------------------------
// RS485
//-----------------------------------------------------------------------------
#define		ERROR_NONE			0
#define		ERROR_FRAME			1
#define		ERROR_OVERRUN		2
#define		ERROR_PARITY		4

/*
#define		RS485_PORT_UART1
#undef		RS485_PORT_UART1

#ifdef		RS485_PORT_UART1		// half-duplex
#define		RS485_UART1_SENDER		// set as Transmitter
#undef		RS485_UART1_SENDER		// set as Receiver
#endif
 */

#define		RS485_PORT_UART2
//#undef		RS485_PORT_UART2

#ifdef		RS485_PORT_UART2		// half-duplex
#define		RS485_UART2_SENDER		// set as Transmitter
#undef		RS485_UART2_SENDER		// set as Receiver
#endif

//-----------------------------------------------------------------------------
// ECAN
//-----------------------------------------------------------------------------
#define		ECAN1_TIMER_TRIGGERED
//#undef		ECAN1_TIMER_TRIGGERED

#define		ECAN1_LOOPBACK
#undef		ECAN1_LOOPBACK

#ifdef		ECAN1_LOOPBACK
// run while(1)
#undef		ECAN1_TIMER_TRIGGERED
#else
// select the role
#define		ECAN1_SENDER
#undef		ECAN1_SENDER
#endif

#define		ECAN2_TIMER_TRIGGERED
#undef		ECAN2_TIMER_TRIGGERED

#define		ECAN2_LOOPBACK
#undef		ECAN2_LOOPBACK

#ifdef		ECAN2_LOOPBACK
// run while(1)
#undef		ECAN2_TIMER_TRIGGERED
#else
// select the role
#define		ECAN2_SENDER
#undef		ECAN2_SENDER
#endif

//-----------------------------------------------------------------------------
// Interrupt
//-----------------------------------------------------------------------------

// UART
#define		INT_UART1_ENABLED
//#undef		INT_UART1_ENABLED

#define		INT_UART2_ENABLED
//#undef		INT_UART2_ENABLED

// Interrupt priority levels (3 bits)
//		1 (lowest) ~ 7 (highest)
#define		DPS_U1RXIP			1
#define		DPS_U1TXIP			1
#define		DPS_U2RXIP			1
#define		DPS_U2TXIP			1

//-----------------------------------------------------------------------------
// Typedef
//-----------------------------------------------------------------------------
typedef		unsigned char		t_cmd;

// buffers (ring buffers)
typedef	struct {
	unsigned char 	*buffer;
	unsigned int	head;
	unsigned int	tail;
	unsigned int	count;
	unsigned int	size;
} RingBuf;

#endif
