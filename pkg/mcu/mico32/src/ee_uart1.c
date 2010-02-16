/** 
* @file ee_uart.c
*/

#include "mcu/mico32/inc/ee_uart.h"
//#include "ee_internal.h"

/******************************************************************************/
/*                             Utility Macros                                 */
/******************************************************************************/
// ...

/******************************************************************************/
/*                       Private Local Variables                              */
/******************************************************************************/
// ...

/******************************************************************************/
/*                       Private Local Functions                              */
/******************************************************************************/
// ...

/******************************************************************************/
/*                              ISRs                                          */
/******************************************************************************/
EE_uart_st ee_uart_st_1;

void EE_uart1_handler(void)
{
	EE_uart_handler(&ee_uart_st_1);
	return;	
}

//// ISR example:
//void MicoUartISR(void)
//{
//    unsigned int iir;
//    unsigned int ier;
//    
//    MicoUart_t *uartc = (MicoUart_t *)UART0_BASE_ADDRESS;
//
//    /* interrogate interrupt-cause */
//    iir = uartc->iir;
//    ier = uartc->ier;
//
//    /* see if the interrupt is due to rx-data */
//    switch(iir){
//        case MICOUART_IIR_RXRDY:
//		{
//            /* 
//	         * read lsr to check for errors associated with current word. 
//	         * reading lsr clears error bits 
//	         */
//            unsigned int lsr = uartc->lsr;
//            /* check for error(s) with the current word */
//            if((lsr & (MICOUART_LSR_PE_MASK | MICOUART_LSR_FE_MASK)) == 0) 
//            	EE_buffer_putmsg(&UART0_buffer, &uartc->rxtx)
//        }break;
//        case MICOUART_IIR_TXRDY:
//		{
//            unsigned int count;
//            if(uart->fifoenable){ 
//                /* see if there's stuff to transmit */
//                count = (uart->txDataBytes > 16)?16:uart->txDataBytes;
//                count = 16;
//            }else {
//                count = 1;
//            }
//            /* put 16 data words to the TX FIFO of 
//             * the UART if data is available
//             */
//            while (count != 0) 
//			{				
//	            if(uart->txDataBytes == 1)
//				{
//					/* disable tx interrupts as this is the last data to send */
//					uart->ier &= (~MICOUART_IER_TX_INT_MASK);
//					dev->ier = uart->ier;
//	            }
//	            dev->rxtx = uart->txBuffer[uart->txReadLoc];
//	            uart->txReadLoc++;
//	            if(uart->txReadLoc >= uart->txBufferSize)
//				{
//	                uart->txReadLoc = 0;
//	            }
//                --uart->txDataBytes;
//                --count;
//                if(uart->txDataBytes == 0)
//				{
//                    break;
//                }
//            }
//        }break;
//        default:{
//            /* 
//             * This will never happen unless someone's reading rx
//             * in parallel.  If using interrupts, isr is the only
//             * code that should be reading rx
//             */
//        }break;
//    }
//
//    /* all done */
//    return;
//}

/******************************************************************************/
/*                       Public Global Functions                              */
/******************************************************************************/
// ...
