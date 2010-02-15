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
EE_UINT8 EE_uart_init_base(EE_UINT32 base, EE_UINT32 baudrate, EE_UINT32 settings)
{
	MicoUart_t *uartc = (MicoUart_t *)base;
	
	if(baudrate==0)
		return EE_UART_ERR_BAD_VALUE; 
	
	/* reset ier (isr register) */
    uartc->ier = 0;						// if ier==0 -> POLLING MODE (ATT! is a blocking mode!!!)
    									// if ier!=0 -> ISR MODE (ATT! is not a blocking mode!!!)
    
	/* set the control register */
    uartc->lcr = settings;    
    
    /* Calculate clock-divisor */
    uartc->div = (MICO32_CPU_CLOCK_MHZ)/baudrate;
    
    // All done!!!
    return EE_UART_OK;
}

EE_UINT8 EE_uart_set_ISR_callback_base(EE_UINT32 base, EE_UINT32 irq_flag, EE_mico32_ISR_handler isr_rx_callback, EE_mico32_ISR_handler isr_tx_callback)
{
	MicoUart_t *uartc = (MicoUart_t *)base;
	
	/* reset ier (isr register) */
	uartc->ier = 0;
	
    /* ISR configuration  */
    if(isr_rx_callback != NULL)
	{
    	/* Register handler and enable the interrupt */
    	EE_mico32_register_ISR(irq_flag, isr_rx_callback);
    	uartc->ier |= MICOUART_IER_RX_INT_MASK;
	}
	if(isr_tx_callback != NULL)
	{
    	/* Register handler and enable the interrupt */
    	EE_mico32_register_ISR(irq_flag, isr_tx_callback);
    	uartc->ier |= MICOUART_IER_TX_INT_MASK;
	}	
	
	// All done!!!
    return EE_UART_OK;
}

EE_UINT8 EE_uart_close_base(EE_UINT32 base)
{
	MicoUart_t *uartc = (MicoUart_t *)base;
	
	/* reset ier (isr register) */
	uartc->ier = 0;
	
	// All done!!!
    return EE_UART_OK;
}

EE_UINT8 EE_uart_write_byte_base(EE_UINT32 base, EE_INT8 data, ee_buffer *buf)
{
	unsigned int uiValue, mode;
	EE_UINT8 ret = EE_UART_OK;
	
	MicoUart_t *uartc = (MicoUart_t *)base;
	
	/* read IER register to check the operating mode */
	mode = uartc->ier;
	
	if(mode == EE_UART_POLLING_MODE)
	{
		do
		{
			/* if uart's ready to accept character, send immediately */
    		uiValue = uartc->lsr;
    		if(uiValue & MICOUART_LSR_TX_RDY_MASK)
			{
    			uartc->rxtx = data;
        		if(buf != EE_UART_NULL_BUF)
        			ret = EE_UART_ERR_BAD_VALUE;
    			return ret;
			}
			// if you don't want a blocking procedure return here...
		}while(1);
	}
	else if(mode == EE_UART_ISR_MODE)
	{
		if(buf == EE_UART_NULL_BUF)
			return EE_UART_ERR_BAD_VALUE;
		ret = EE_buffer_putmsg(buf, &data);	
	}
	else
		 return EE_UART_ERR_BAD_VALUE;
	
	// All done!!!
	return ret;
}

EE_UINT8 EE_uart_read_byte_base(EE_UINT32 base, EE_INT8 *data, ee_buffer *buf)
{
	unsigned int uiValue, mode;
	EE_UINT8 ret = EE_UART_OK;
	
	MicoUart_t *uartc = (MicoUart_t *)base;
	
	if(data == EE_UART_NULL_VET)
		return EE_UART_ERR_BAD_VALUE;
	
	/* read IER register to check the operating mode */
	mode = uartc->ier;
	
	if(mode == EE_UART_POLLING_MODE)
	{
		do
		{
			uiValue = uartc->lsr;
			if(uiValue & MICOUART_LSR_RX_RDY_MASK)
			{
    			*data = uartc->rxtx;
    			if(buf != EE_UART_NULL_BUF)
        			ret = EE_UART_ERR_BAD_VALUE;
        		// All done!!!
    			return ret;
    		}
    		// if you don't want a blocking procedure return here...
		}while(1);
	}
	else if(mode == EE_UART_ISR_MODE)
	{
		if(buf == EE_UART_NULL_BUF)
			return EE_UART_ERR_BAD_VALUE;
		ret = EE_buffer_getmsg(buf, data);	
	}
	else
		return EE_UART_ERR_BAD_VALUE;
		
    // All done!!!
	return ret;
}

EE_UINT8 EE_uart_read_buffer_base(EE_UINT32 base, EE_INT8 *vet, EE_INT16 len, ee_buffer *buf)
{
	int i=0;

	for(i=0; i<len; i++)
	{
		if(EE_uart_read_byte_base(base, &vet[i], buf) != EE_UART_OK)
			return EE_UART_ERR_RECEPTION;
	}
	
	return EE_UART_OK;
}

EE_UINT8 EE_uart_write_buffer_base(EE_UINT32 base, EE_INT8 *vet, EE_INT16 len, ee_buffer *buf)
{
	int i=0;

	for(i=0; i<len; i++)
	{
		if(EE_uart_write_byte_base(base, vet[i], buf) != EE_UART_OK)
			return EE_UART_ERR_TRANSMISSION;
	}
	
	return EE_UART_OK;
}

