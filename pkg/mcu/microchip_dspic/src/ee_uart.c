#include "mcu/microchip_dspic/inc/ee_uart.h"
#include "ee_internal.h"
#include "cpu/pic30/inc/ee_irqstub.h"

#ifdef EE_UART_PORT_1_ISR_ENABLE
static void (*Rx1IsrFunction)(EE_UINT8 data) = NULL;
static void (*Tx1IsrFunction)(void) = NULL;
#endif
#ifdef EE_UART_PORT_2_ISR_ENABLE
static void (*Rx2IsrFunction)(EE_UINT8 data) = NULL;
static void (*Tx2IsrFunction)(void) = NULL;
#endif

EE_INT8 EE_uart_init(EE_UINT8 port, EE_UINT32 baud, EE_UINT16 byte_format, 
		     EE_UINT16 mode)
{
	if (port == EE_UART_PORT_1) {
		U1MODEbits.UARTEN = 0;		/* Stop UART port */
		IEC0bits.U1RXIE = 0;		/* Disable Interrupts */
		IEC0bits.U1TXIE = 0;
		IFS0bits.U1RXIF = 0;		/* Clear Interrupt flag bits */
		IFS0bits.U1TXIF = 0;
		#ifndef __PIC24FJ32GA004__
		TRISFbits.TRISF2 = 1;		/* Set In RX Pin */
		TRISFbits.TRISF3 = 0;		/* Set Out TX Pin */
		if (mode == EE_UART_CTRL_FLOW) {	
			TRISDbits.TRISD14 = 1;	/* Set In CTS Pin */
			TRISDbits.TRISD15 = 0;	/* Set Out RTS Pin */
		}
		#endif

		/* baud rate */
		#ifdef __PIC24FJ32GA004__
		if ( baud > 57600 )
		/* EE_UART_INSTRUCTION_CLOCK  is computed considering Fcy = 16MHz*/
			U1BRG  = (EE_UART_INSTRUCTION_CLOCK  / (4 * baud)) - 1;
		else
			U1BRG  = (EE_UART_INSTRUCTION_CLOCK / (16 * baud)) - 1;
		#else
		U1BRG  = (EE_UART_INSTRUCTION_CLOCK / baud) - 1; 
				//U1BRG = 21 // For 115200 with Fcy = 40MHz
				/* Operation settings and start port */
		#endif

		U1MODE = 0;

		#ifdef __PIC24FJ32GA004__
		if ( baud > 57600 )
			U1MODEbits.BRGH = 1;
		else
			U1MODEbits.BRGH = 0;
		#else
		U1MODEbits.BRGH = 0;
		#endif

		U1MODEbits.UARTEN = 1;
		if (mode == EE_UART_CTRL_FLOW) {	
			U1MODEbits.RTSMD = 1;
			U1MODEbits.UEN = 2;
		} else {	
			U1MODEbits.RTSMD = 0;
			U1MODEbits.UEN = 0;	
		}
		/* Number of bit, Parity and Stop bits */
		U1MODE |= byte_format & 0x07; 
		/* TX & RX interrupt modes */
		U1STA = 0;
		U1STAbits.UTXEN = 1;
		return 1;
	} else if (port == EE_UART_PORT_2) {
		U2MODEbits.UARTEN = 0;		/* Stop UART port */
		IEC1bits.U2RXIE = 0;		/* Disable Interrupts */
		IEC1bits.U2TXIE = 0;
		IFS1bits.U2RXIF = 0;		/* Clear Interrupt flag bits */
		IFS1bits.U2TXIF = 0;
		#ifndef __PIC24FJ32GA004__
		TRISFbits.TRISF4 = 1;		/* Set In RX Pin */
		TRISFbits.TRISF5 = 0;		/* Set Out TX Pin */

		if (mode == EE_UART_CTRL_FLOW) {	
			TRISFbits.TRISF12 = 1;	/* Set In RX Pin */
			TRISFbits.TRISF13 = 0;	/* Set Out TX Pin */
		}
		#endif

		/* baud rate */
		#ifdef __PIC24FJ32GA004__
		if ( baud > 57600 )
		/* EE_UART_INSTRUCTION_CLOCK  is computed considering Fcy = 16MHz*/
			U2BRG  = (EE_UART_INSTRUCTION_CLOCK  / (4 * baud)) - 1;
		else
			U2BRG  = (EE_UART_INSTRUCTION_CLOCK / (16 * baud)) - 1;
		#else
		U2BRG  = (EE_UART_INSTRUCTION_CLOCK / baud) - 1; 
				//U1BRG = 21 // For 115200 with Fcy = 40MHz
				/* Operation settings and start port */
		#endif

		U2MODE = 0;

		#ifdef __PIC24FJ32GA004__
		if ( baud > 57600 )
			U2MODEbits.BRGH = 1;
		else
			U2MODEbits.BRGH = 0;
		#else
		U2MODEbits.BRGH = 0;
		#endif

		U2MODEbits.UARTEN = 1;
		if (mode == EE_UART_CTRL_FLOW) {	
			U2MODEbits.RTSMD = 1;
			U2MODEbits.UEN = 2;
		} else {	/* Simple Mode */
			U2MODEbits.RTSMD = 0;
			U2MODEbits.UEN = 0;	
		}
		/* Number of bit, Parity and Stop bits */
		U2MODE |= byte_format & 0x07; 
		/* TX & RX interrupt modes */
		U2STA = 0;
		U2STAbits.UTXEN = 1;
		return 1;
	}
	return -EE_UART_ERR_BAD_PORT;
}

EE_INT8 EE_uart_close(EE_UINT8 port)
{
	if (port == EE_UART_PORT_1) {
		/* chris: TODO: Release something */
		return 1;
	} else if (port == EE_UART_PORT_2) {
		/* chris: TODO: Release something */
		return 1;
	}
	return -EE_UART_ERR_BAD_PORT;
}

EE_INT8 EE_uart_set_tx_callback(EE_UINT8 port, void (*TxFunc)(void), 
				EE_UINT16 txmode)
{
	if (port == EE_UART_PORT_1) {
		#ifdef EE_UART_PORT_1_ISR_ENABLE
		Tx1IsrFunction = TxFunc;
		if (TxFunc) {
			U1STA &= 0x5FFF;		
			U1STA |= txmode & 0xA000;
			IEC0bits.U1TXIE = 1;		
			IFS0bits.U1TXIF = 0;	
		}
		return 1;
		#else
		return -EE_UART_ERR_INT_DISABLED;
		#endif
	} else if (port == EE_UART_PORT_2) {
		#ifdef EE_UART_PORT_2_ISR_ENABLE
		Tx2IsrFunction = TxFunc;
		if (TxFunc) {
			U2STA &= 0x5FFF;	
			U2STA |= txmode & 0xA000;
			IEC1bits.U2TXIE = 1;		
			IFS1bits.U2TXIF = 0;	
		}
		return 1;
		#else
		return -EE_UART_ERR_INT_DISABLED;
		#endif
	}
	return -EE_UART_ERR_BAD_PORT;
}

EE_INT8 EE_uart_set_rx_callback(EE_UINT8 port, void (*RxFunc)(EE_UINT8 data), 
				EE_UINT16 rxmode)
{
	if (port == EE_UART_PORT_1) {
		#ifdef EE_UART_PORT_1_ISR_ENABLE
		Rx1IsrFunction = RxFunc;
		if (RxFunc) {
			U1STA &= 0xFF3F;		
			U1STA |= rxmode & 0x00C0;
			IEC0bits.U1RXIE = 1;		
			IFS0bits.U1RXIF = 0;	
		}
		return 1;
		#else
		return -EE_UART_ERR_INT_DISABLED;
		#endif
	} else if (port == EE_UART_PORT_2) {
		#ifdef EE_UART_PORT_2_ISR_ENABLE
		Rx2IsrFunction = RxFunc;
		if (RxFunc) {
			U2STA &= 0xFF3F;	
			U2STA |= rxmode & 0x00C0;
			IEC1bits.U2RXIE = 1;		
			IFS1bits.U2RXIF = 0;	
		}
		return 1;
		#else
		return -EE_UART_ERR_INT_DISABLED;
		#endif
	}
	return -EE_UART_ERR_BAD_PORT;
}

EE_INT8 EE_uart_write_byte(EE_UINT8 port, EE_UINT8 data)
{
	if (port == EE_UART_PORT_1) {
		/* Polling mode */
		while (U1STAbits.UTXBF) ;
		U1TXREG = data;
		while (!U1STAbits.TRMT) ;
		return 1;
	} else if (port == EE_UART_PORT_2) {
		/* Polling mode */
		while (U2STAbits.UTXBF) ;
		U2TXREG = data;
		while (!U2STAbits.TRMT) ;
		return 1;
	}
	return -EE_UART_ERR_BAD_PORT;
}

EE_INT8 EE_uart_read_byte(EE_UINT8 port, EE_UINT8 *data)
{
	if (port == EE_UART_PORT_1) {
		#ifdef EE_UART_PORT_1_ISR_ENABLE
		if (Rx1IsrFunction == NULL) {
			/* Polling mode */
		#endif
			if (U1STAbits.OERR) {
				U1STAbits.OERR = 0;
				return -EE_UART_ERR_OVERFLOW;
			}
			if (U1STAbits.URXDA) {
				*data = U1RXREG & 0x00FF;
				U1STAbits.URXDA = 0;
				return 1;
			}
			return -EE_UART_ERR_NO_DATA;
		#ifdef EE_UART_PORT_1_ISR_ENABLE
		}
		return -EE_UART_ERR_INT_MODE;
		#endif
	} else if (port == EE_UART_PORT_2) {
		#ifdef EE_UART_PORT_2_ISR_ENABLE
		if (Rx2IsrFunction == NULL) {
			/* Polling mode */
		#endif
			if (U2STAbits.OERR) {
				U2STAbits.OERR = 0;
				return -EE_UART_ERR_OVERFLOW;
			}
			if (U2STAbits.URXDA) {
				U2STAbits.URXDA = 0;
				*data = U2RXREG & 0x00FF;
				return 1;
			}
			return -EE_UART_ERR_NO_DATA;
		#ifdef EE_UART_PORT_2_ISR_ENABLE
		}
		return -EE_UART_ERR_INT_MODE;
		#endif
	}
	return -EE_UART_ERR_BAD_PORT;
}


#ifdef EE_UART_PORT_1_ISR_ENABLE
ISR2(_U1RXInterrupt)
{
	if (Rx1IsrFunction != NULL) {
		/* Execute callback function */
		Rx1IsrFunction(U1RXREG & 0x00FF);
	}
	IFS0bits.U1RXIF = 0;           
}

ISR2(_U1TXInterrupt)
{
	if (Tx1IsrFunction != NULL) {
		/* Execute callback function */
		Tx1IsrFunction();
	}   
	IFS0bits.U1TXIF = 0;   
}
#endif

#ifdef EE_UART_PORT_2_ISR_ENABLE
ISR2(_U2RXInterrupt)
{
	if (Rx2IsrFunction != NULL) {
		/* Execute callback function */
		Rx2IsrFunction(U2RXREG & 0x00FF);
	}
	IFS1bits.U2RXIF = 0;           
}

ISR2(_U2TXInterrupt)
{
	if (Tx2IsrFunction != NULL) {
		/* Execute callback function */
		Tx2IsrFunction();
	}
	IFS1bits.U2TXIF = 0;           
}
#endif

