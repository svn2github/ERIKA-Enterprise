#include "ee.h"
#include "define.h"
#include "eeuart.h"
#include "variable.h"
#include "driver.h"
#include "util.h"

//=========================================================================
TASK(TaskDebug)
{
	RingBuf *		pBufSrc;
	RingBuf *		pBufDst;
	unsigned char	count, byte;

	while (1) {
		// check if data available from RF
		//	then, move it to SerialTXBuf and enable TX INT
		pBufSrc = &UART1RXBuf;
		pBufDst = &UART2TXBuf;
		ENTER_CRITICAL_SECTION();
		count = CountBuffer(pBufSrc);
		EXIT_CRITICAL_SECTION();
		if (count >= DPS_MSG_SIZE) {
			// move data to SerialTXBuf
			ENTER_CRITICAL_SECTION();
			do {
				byte = PopBuffer(pBufSrc);
				if (IsBufferFull(pBufDst) == DPS_FALSE)
					PushBuffer(pBufDst, byte);
				else {
					//ERROR: buffer full
				}
			} while (IsBufferEmpty(pBufSrc) == DPS_FALSE);
			EXIT_CRITICAL_SECTION();

			if (UART2TX_INT_Enabled == DPS_FALSE)
			{
				ENTER_CRITICAL_SECTION();
				//enable UART2 TX INT to send the data via Serial Port
				IEC1bits.U2TXIE = 1;		// Enable Tx Interrupt
				// set the flag
				UART2TX_INT_Enabled = DPS_TRUE;
				EXIT_CRITICAL_SECTION();
			}
		}

		// check if data available from Serial Port
		//	then, move it to RFTXBuf and enable TX INT
		pBufSrc = &UART2RXBuf;
		pBufDst = &UART1TXBuf;
		ENTER_CRITICAL_SECTION();
		count = CountBuffer(pBufSrc);
		EXIT_CRITICAL_SECTION();
		if (count >= DPS_MSG_SIZE) {
			// move data to SerialTXBuf
			ENTER_CRITICAL_SECTION();
			do {
				byte = PopBuffer(pBufSrc);
				if (IsBufferFull(pBufDst) == DPS_FALSE)
					PushBuffer(pBufDst, byte);
				else {
					//ERROR: buffer full
				}
			} while (IsBufferEmpty(pBufSrc) == DPS_FALSE);
			EXIT_CRITICAL_SECTION();

			if (UART1TX_INT_Enabled == DPS_FALSE)
			{
				ENTER_CRITICAL_SECTION();
				//enable UART1 TX INT to send the data via RF
				IEC0bits.U1TXIE = 1;		// Enable Tx Interrupt
				// set the flag
				UART1TX_INT_Enabled = DPS_TRUE;
				EXIT_CRITICAL_SECTION();
			}
		}
	}	// while (1)
}

/* Send a character using the UART2 port
 */
TASK(TaskSend)
{
	// toggle LED
	LATBbits.LATB14 ^= 1;

	EE_UART2_Send('<');
	EE_UART2_Send('H');
	EE_UART2_Send('>');
}
