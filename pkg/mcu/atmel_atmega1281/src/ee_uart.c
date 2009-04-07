#include "mcu/atmel_atmega1281/inc/ee_uart.h"
#include "ee_internal.h"

#ifdef EE_UART_PORT_1_ISR_ENABLE
static void (*Rx1IsrFunction)(EE_UINT8 data) = NULL;
#endif

EE_INT8 EE_uart_init(EE_UINT8 port, EE_UINT32 baud, EE_UINT16 byte_format, EE_UINT16 mode)
{
	if (port != EE_UART_PORT_1)
		return -EE_UART_ERR_BAD_PORT;
		
	// TODO: (Nino) Initialize UART Port
	
	/*U1MODEbits.UARTEN = 0;		// Stop UART port 
	IEC0bits.U1RXIE = 0;		// Disable Interrupts
	IEC0bits.U1TXIE = 0;
	IFS0bits.U1RXIF = 0;		// Clear Interrupt flag bits
	IFS0bits.U1TXIF = 0;
	TRISFbits.TRISF2 = 1;		// Set In RX Pin
	TRISFbits.TRISF3 = 0;		// Set Out TX Pin
	if (mode == EE_UART_CTRL_FLOW) {	
		TRISDbits.TRISD14 = 1;	// Set In CTS Pin
		TRISDbits.TRISD15 = 0;	// Set Out RTS Pin
	}
	// baud rate
	U1BRG  = (EE_UART_INSTRUCTION_CLOCK / baud) - 1; 
	//U1BRG = 21 // For 115200 with Fcy = 40MHz
	// Operation settings and start port 
	U1MODE = 0;
	U1MODEbits.BRGH = 0;
	U1MODEbits.UARTEN = 1;
	if (mode == EE_UART_CTRL_FLOW) {	
		U1MODEbits.RTSMD = 1;
		U1MODEbits.UEN = 2;
	} else {	
		U1MODEbits.RTSMD = 0;
		U1MODEbits.UEN = 0;	
	}
	// Number of bit, Parity and Stop bits 
	U1MODE |= byte_format & 0x07; 
	//* TX & RX interrupt modes
	U1STA = 0;
	U1STAbits.UTXEN = 1;*/
	return 1;
}

EE_INT8 EE_uart_close(EE_UINT8 port)
{
	if (port != EE_UART_PORT_1)
		return -EE_UART_ERR_BAD_PORT;
	
	/* chris: TODO: Release something */
	return 1;
}

EE_INT8 EE_uart_set_rx_callback(EE_UINT8 port, void (*RxFunc)(EE_UINT8 data), EE_UINT8 rxmode)
{
	if (port != EE_UART_PORT_1)
		return -EE_UART_ERR_BAD_PORT;
	
#ifdef EE_UART_PORT_1_ISR_ENABLE
	Rx1IsrFunction = RxFunc;
	
	// TODO: (Nino) Initialize UART  ISR
	/*if (RxFunc) {
		U1STA &= 0x5FFF;		
		U1STA |= rxmode & 0xA000;
		IEC0bits.U1RXIE = 1;		
		IFS0bits.U1RXIF = 0;	
	}*/
	return 1;
#else
	return -EE_UART_ERR_INT_DISABLED;
#endif
}

EE_INT8 EE_uart_write_byte(EE_UINT8 port, EE_UINT8 data)
{
	if (port == EE_UART_PORT_1)
		return -EE_UART_ERR_BAD_PORT;
		
	/* Polling mode */
	// TODO: (Nino) UART Send
	/*while (U1STAbits.UTXBF) ;
	U1TXREG = data;
	while (!U1STAbits.TRMT) ;*/
	return 1;
}

EE_INT8 EE_uart_read_byte(EE_UINT8 port, EE_UINT8 *data)
{
	if (port == EE_UART_PORT_1)
		return -EE_UART_ERR_BAD_PORT;
		
#ifdef EE_UART_PORT_1_ISR_ENABLE
	if (Rx1IsrFunction == NULL) {
		/* Polling mode */
#endif
		// TODO: (Nino) UART Receive
		/*if (U1STAbits.OERR) {
			U1STAbits.OERR = 0;
			return -EE_UART_ERR_OVERFLOW;
		}
		if (U1STAbits.URXDA) {
			*data = U1RXREG & 0x00FF;
			return 1;
		}*/
		return -EE_UART_ERR_NO_DATA;
#ifdef EE_UART_PORT_1_ISR_ENABLE
	}
	return -EE_UART_ERR_INT_MODE;
#endif
}


#ifdef EE_UART_PORT_1_ISR_ENABLE
ISR2(_U1RXInterrupt)
{
	if (Rx1IsrFunction != NULL) {
		/* Execute callback function */
		// TODO: (Nino) Call function with correct data
		//Rx1IsrFunction(U1RXREG & 0x00FF);
	}
	IFS0bits.U1RXIF = 0;           
}
#endif
