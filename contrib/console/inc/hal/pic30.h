#ifndef __pic30_h__
#define __pic30_h__
/** 
* @file pic30.h
* @brief PIC30 Hardware Abstraction Layer definition.
* @author Marinoni Mauro, Nastasi Christian
* @date 2008-11-03
*/

#ifdef __PIC30__

#include "console_serial.h"
#include "ee.h"

/* ************************************************************************** */
/*                          HAL Macros Declaration                            */
/* ************************************************************************** */
/** 
* @name Serial console HAL.
*
* These macros are required by the serial console implementation.
*
* @{ */
#define CONSOLE_SERIAL_HAL_FLAG_BIT9		0x06
#define CONSOLE_SERIAL_HAL_FLAG_BIT8_ODD	0x04
#define CONSOLE_SERIAL_HAL_FLAG_BIT8_EVEN	0x02
#define CONSOLE_SERIAL_HAL_FLAG_BIT8_NO		0x00
#define CONSOLE_SERIAL_HAL_FLAG_BIT_STOP1	0x00
#define CONSOLE_SERIAL_HAL_FLAG_BIT_STOP2	0x01
/**  @} */


/* Included waiting for the new ee_board - BEGIN */

#define CLOCK_FREQ	(40000000)      // Hz
#define INSTR_FREQ	(CLOCK_FREQ/2)	// Hz

//#define BIT9		0x06
//#define BIT8_ODD	0x04
//#define BIT8_EVEN	0x02
//#define BIT8_NO		0x00
//#define BIT_STOP_1	0x00
//#define BIT_STOP_2	0x01

#define CTRL_SIMPLE	0x00
#define CTRL_FLOW	0x01
#define TX_INT_SINGLE	0x8000
#define TX_INT_EMPTY	0x2000
#define TX_INT_LAST	0x0000
#define RX_INT_FULL	0x00C0
#define RX_INT_3OF4	0x0080
#define RX_INT_SINGLE	0x0040

/* /\************************************************************************* */
/*  UART Port 1 */
/*  *************************************************************************\/ */

__INLINE__ void EE_UART1_Init(EE_UINT32 baud, EE_UINT16 byteformat, EE_UINT16 mode)
{
	/* Stop UART port */
	U1MODEbits.UARTEN = 0;
	
	/* Disable Interrupts */
	IEC0bits.U1RXIE = 0;
	IEC0bits.U1TXIE = 0;
	
	/* Clear Interrupt flag bits */
	IFS0bits.U1RXIF = 0;
	IFS0bits.U1TXIF = 0;
		
	/* Set IO pins */
	TRISFbits.TRISF2 = 1;	// RX Pin
	TRISFbits.TRISF3 = 0;	// TX Pin
	if (mode) {
		TRISDbits.TRISD14 = 1;	// CTS Pin
		TRISDbits.TRISD15 = 0;	// RTS Pin
	}
	
	/* baud rate */
	U1BRG  = (2500000ul / baud) - 1; // With BRGH = 0
	//U1BRG = 21 // For 115200 with Fcy = 40MHz
	
	/* Operation settings and start port */
	U1MODE = 0;
	U1MODEbits.BRGH = 0;
	U1MODEbits.UARTEN = 1;
	if (mode) {	// Flow Control Mode
		U1MODEbits.RTSMD = 1;
		U1MODEbits.UEN = 2;
	} else {	// Simple Mode
		U1MODEbits.RTSMD = 0;
		U1MODEbits.UEN = 0;	
	}
	U1MODE |= byteformat & 0x07; // Number of bit, Parity and Stop bits

	/* TX & RX interrupt modes */
	U1STA = 0;
	U1STAbits.UTXEN = 1;
}

__INLINE__ EE_INT8 EE_UART1_Send(unsigned char data)
{
	//unsigned int i;
	
	while (U1STAbits.UTXBF);
	U1TXREG = data;
	while(!U1STAbits.TRMT);
	//for(i=0; i<2000; i++);	

	return 0;
}

__INLINE__ EE_INT8 EE_UART1_Receive(unsigned char* data)
{
	if (U1STAbits.OERR) {
		U1STAbits.OERR = 0;
		return -2;
	}
	
	if (U1STAbits.URXDA) {
		*data = U1RXREG & 0x00FF;
		return 0;
	} else {
		*data = 0;
		return -1;
	}
	
	return 0;
}

/* /\************************************************************************* */
/*  UART Port 2 */
/*  *************************************************************************\/ */

__INLINE__ void EE_UART2_Init(EE_UINT32 baud, EE_UINT16 byteformat, EE_UINT16 mode)
{
	/* Stop UART port */
	U2MODEbits.UARTEN = 0;
	
	/* Disable Interrupts */
	IEC1bits.U2RXIE = 0;
	IEC1bits.U2TXIE = 0;
	
	/* Clear Interrupt flag bits */
	IFS1bits.U2RXIF = 0;
	IFS1bits.U2TXIF = 0;
		
	/* Set IO pins */
	TRISFbits.TRISF4 = 1;	// RX Pin
	TRISFbits.TRISF5 = 0;	// TX Pin
	if (mode) {
		TRISFbits.TRISF12 = 1;	// CTS Pin
		TRISFbits.TRISF13 = 0;	// RTS Pin
	}
	
	/* baud rate */
	U2BRG  = (2500000ul / baud) - 1; // With BRGH = 0
	//U2BRG = 21; // For 115200 with Fcy = 40MHz
	
	/* Operation settings and start port */
	U2MODE = 0;
	U2MODEbits.BRGH = 0;
	U2MODEbits.UARTEN = 1;
	if (mode) {	// Flow Control Mode
		U2MODEbits.RTSMD = 1;
		U2MODEbits.UEN = 2;
	} else {	// Simple Mode
		U2MODEbits.RTSMD = 0;
		U2MODEbits.UEN = 0;	
	}
	U2MODE |= byteformat & 0x07; // Number of bit, Parity and Stop bits

	/* TX & RX interrupt modes */
	U2STA = 0;
	U2STAbits.UTXEN = 1;
}

__INLINE__ EE_INT8 EE_UART2_Send(unsigned char data)
{
	//unsigned int i;
	
	while (U2STAbits.UTXBF);
	U2TXREG = data;
	while(!U2STAbits.TRMT);
	//for(i=0; i<2000; i++);	

	return 0;
}

__INLINE__ EE_INT8 EE_UART2_Receive(unsigned char* data)
{
	if (U2STAbits.OERR) {
		U2STAbits.OERR = 0;
		return -2;
	}
	
	if (U2STAbits.URXDA) {
		*data = U2RXREG & 0x00FF;
		return 0;
	} else {
		*data = 0;
		return -1;
	}

	return 0;
}

/* Included waiting for the new ee_board - BEGIN */

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

#endif /* __PIC30__ */
#endif /* __pic30_h__ */
