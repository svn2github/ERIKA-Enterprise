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
char ee_uart_isr_rxvet[EE_UART_BUFSIZE];
char ee_uart_isr_txvet[EE_UART_BUFSIZE];

/******************************************************************************/
/*                       Private Local Functions                              */
/******************************************************************************/
// ...

/******************************************************************************/
/*                              ISRs                                          */
/******************************************************************************/
// Interrupt common handler:
void EE_uart_handler(EE_uart_st* usp)
{
    unsigned int iir;
    unsigned int lsr;
    char data = 0;
    
    MicoUart_t *uartc = (MicoUart_t *)(usp->base); 
    
    /* interrogate interrupt-cause */
    iir = uartc->iir;
    
    /* check the interrupt source */
    switch(iir){
        case MICOUART_IIR_RXRDY:	/* the interrupt is due to rx-data */
		{
            /* 
	         * read lsr to check for errors associated with current word. 
	         * reading lsr clears error bits 
	         */
            //lsr = uartc->lsr;
            /* check for error(s) with the current word */
            //if((lsr & (MICOUART_LSR_PE_MASK | MICOUART_LSR_FE_MASK)) == 0) if(uiValue & MICOUART_LSR_RX_RDY_MASK)
            data = uartc->rxtx;
            EE_buffer_putmsg(&(usp->rxbuf), &data);
            if(usp->rxcbk != EE_UART_NULL_CBK)
            	usp->rxcbk();
        }break;
        case MICOUART_IIR_TXRDY:	/* the interrupt is due to tx-data */
		{				
			EE_buffer_getmsg(&(usp->txbuf), &data);
			
	        if(EE_buffer_isempty(&(usp->txbuf)))
	        {
				if(ee_uart1_st.ie == EE_UART_ISR_RXTX)
					uartc->ier = MICOUART_IER_RX_INT_MASK;
				else
					/* disable tx interrupts as this is the last data to send */
					uartc->ier = 0;
			}
			lsr = uartc->lsr;
			while(!(lsr & MICOUART_LSR_TX_RDY_MASK));
	        uartc->rxtx = data;
	        if(usp->txcbk != EE_UART_NULL_CBK)
            	usp->txcbk();
        }break;
        default:{
            /* 
             * This will never happen unless someone's reading rx
             * in parallel.  If using interrupts, isr is the only
             * code that should be reading rx
             */
        }break;
    }

    /* all done */
    return;
}


/******************************************************************************/
/*                       Public Global Functions                              */
/******************************************************************************/
int EE_uart_init_base(MicoUart_t* base, int irq_flag, int baudrate, unsigned int settings, int ie_flag, 
						EE_mico32_ISR_callback isr_rx_callback, EE_mico32_ISR_callback isr_tx_callback)
{
	MicoUart_t *uartc = base;
	
	if(baudrate==0)
		return EE_UART_ERR_BAD_VALUE; 
	
	//switch(base)
	//	{
	//		case UART1_BASE_ADDRESS:
	//			ee_uart1_st.base = base;
	//			buf = 
	//			break;
	//		case UART2_BASE_ADDRESS:
	//			ee_uart2_st.base = base;
	//			break;
	//		default:
	//			return(EE_UART_ERR_BAD_VALUE);
	//	}  
	ee_uart1_st.base = base;  
	
	/* reset ier (isr register) */
    uartc->ier = 0;						// if ier==0 -> POLLING MODE (ATT! is a blocking mode!!!)
    									// if ier!=0 -> ISR MODE (ATT! is not a blocking mode!!!)
    
	/* set the control register */
    uartc->lcr = settings;    
    
    /* Calculate clock-divisor */
    uartc->div = (MICO32_CPU_CLOCK_MHZ)/baudrate;
    
    /* ISR management */
    return EE_uart_set_ISR_callback_base(base, irq_flag, ie_flag, isr_rx_callback, isr_tx_callback);
}

int EE_uart_set_ISR_callback_base(MicoUart_t* base, int irq_flag, int ie_flag, EE_mico32_ISR_callback isr_rx_callback, EE_mico32_ISR_callback isr_tx_callback)
{
	unsigned int iir; 
	MicoUart_t *uartc = base;
	
	/* reset ier (isr register) */
	uartc->ier = 0;
	iir = uartc->iir;
	//switch(base)
//	{
//		case UART1_BASE_ADDRESS:
//			...
//			break;
//		case UART2_BASE_ADDRESS:
//			ee_uart2_st.rxcbk = isr_rx_callback;
//			ee_uart2_st.txcbk = isr_tx_callback;
//			if( (isr_rx_callback != EE_UART_NULL_CBK)  || (isr_tx_callback != EE_UART_NULL_CBK) )
//			{
//				/* Register handler and enable the interrupt */
//				EE_mico32_register_ISR(irq_flag, EE_uart2_handler);
//			}
//			break;
//		default:
//			return(EE_UART_ERR_BAD_VALUE);
//	}   

	ee_uart1_st.rxcbk = isr_rx_callback;
	ee_uart1_st.txcbk = isr_tx_callback;
	switch(ie_flag)
	{
		case EE_UART_POLLING_MODE:
			ee_uart1_st.ie = ie_flag;  
			uartc->ier = 0;
			EE_mico32_unregister_ISR(irq_flag);
			break;
		case EE_UART_ISR_RX:
			ee_uart1_st.ie = ie_flag;  
			/* Register handler and enable the interrupt */
			EE_mico32_register_ISR(irq_flag, EE_uart1_handler);	
			EE_buffer_init(&ee_uart1_st.rxbuf, EE_UART_MSGSIZE, EE_UART_BUFSIZE, ee_uart_isr_rxvet);	// vet must be: char vet[msgsize*bufsize]
			uartc->ier = MICOUART_IER_RX_INT_MASK;
			break;
		case EE_UART_ISR_TX:	
			ee_uart1_st.ie = ie_flag;  
			/* Register handler and enable the interrupt */
			EE_mico32_register_ISR(irq_flag, EE_uart1_handler);
			EE_buffer_init(&ee_uart1_st.txbuf, EE_UART_MSGSIZE, EE_UART_BUFSIZE, ee_uart_isr_txvet);	// vet must be: char vet[msgsize*bufsize]
			//uartc->ier = MICOUART_IER_TX_INT_MASK;													// Tx Interrupts are enabled only when we need to transmit... 
			break;
		case EE_UART_ISR_RXTX:	
			ee_uart1_st.ie = ie_flag;  
			/* Register handler and enable the interrupt */
			EE_mico32_register_ISR(irq_flag, EE_uart1_handler);
			EE_buffer_init(&ee_uart1_st.rxbuf, EE_UART_MSGSIZE, EE_UART_BUFSIZE, ee_uart_isr_rxvet);	// vet must be: char vet[msgsize*bufsize]
			EE_buffer_init(&ee_uart1_st.txbuf, EE_UART_MSGSIZE, EE_UART_BUFSIZE, ee_uart_isr_txvet);	// vet must be: char vet[msgsize*bufsize]
			uartc->ier = MICOUART_IER_RX_INT_MASK; //uartc->ier = MICOUART_IER_RX_INT_MASK | MICOUART_IER_TX_INT_MASK; // Tx Interrupts are enabled only when we need to transmit... 
			break;
		default:
			return(EE_UART_ERR_BAD_VALUE);
	}

	// All done!!!
    return EE_UART_OK;
}

int EE_uart_write_byte_base(MicoUart_t* base, char data)
{
	unsigned int uiValue, ie_flag;
	EE_buffer* buffer;
	char ret = EE_UART_OK;	
	MicoUart_t *uartc = base;
	
	//switch(base)
//	{
//		case UART1_BASE_ADDRESS:
//			buffer = ee_uart1_st.txbuf;
//			ie_flag = ee_uart1_st.ie;
//			break;
//		case UART2_BASE_ADDRESS:
//			buffer = ee_uart2_st.txbuf;
//			ie_flag = ee_uart2_st.ie;
//			break;
//		default:
//			return(EE_UART_ERR_BAD_VALUE);
//	}   
	buffer = &ee_uart1_st.txbuf;
	ie_flag = ee_uart1_st.ie;
	
	if( (ie_flag!=EE_UART_ISR_TX) && (ie_flag!=EE_UART_ISR_RXTX) )	// POLLING MODE
	{
		do
		{
			/* if uart's ready to accept character, send immediately */
    		uiValue = uartc->lsr;
    		if(uiValue & MICOUART_LSR_TX_RDY_MASK)
			{
    			uartc->rxtx = data;
    			return ret;
			}
			// if you don't want a blocking procedure return here...
		}while(1);
	}
	else
	{
		if(ie_flag == EE_UART_ISR_TX)
			uartc->ier = MICOUART_IER_TX_INT_MASK;	// Enable interrupts to empty the tx buffer...
		else
			uartc->ier = MICOUART_IER_RX_INT_MASK | MICOUART_IER_TX_INT_MASK;
		ret = EE_buffer_putmsg(buffer, &data);
	}
	
	// All done!!!
	return ret;
}

int EE_uart_read_byte_base(MicoUart_t* base, char *data)
{
	unsigned int uiValue, ie_flag;
	int ret = EE_UART_OK;
	EE_buffer* buffer;
	MicoUart_t *uartc = base;
	
	if(data == EE_UART_NULL_VET)
		return EE_UART_ERR_BAD_VALUE;
		
	//switch(base)
//	{
//		case UART1_BASE_ADDRESS:
//			buffer = ee_uart1_st.rxbuf;
//			polling_mode = (ee_uart1_st.rxcbk == EE_UART_NULL_CBK);
//			break;
//		case UART2_BASE_ADDRESS:
//			buffer = ee_uart2_st.rxbuf;
//			polling_mode = (ee_uart2_st.rxcbk == EE_UART_NULL_CBK);
//			break;
//		default:
//			return(EE_UART_ERR_BAD_VALUE);
//	}  
	buffer = &ee_uart1_st.rxbuf;
	ie_flag = ee_uart1_st.ie;
	
	if( (ie_flag!=EE_UART_ISR_RX) && (ie_flag!=EE_UART_ISR_RXTX) )	// POLLING MODE
	{
		do
		{
			uiValue = uartc->lsr;
			if(uiValue & MICOUART_LSR_RX_RDY_MASK)
			{
    			*data = uartc->rxtx;
        		// All done!!!
    			return ret;
    		}
    		// if you don't want a blocking procedure return here...
		}while(1);
	}
	else
	{
		ret = EE_buffer_getmsg(buffer, data);	
	}
		
    // All done!!!
	return ret;
}

int EE_uart_read_buffer_base(MicoUart_t* base, char *vet, int len)
{
	int i=0;

	for(i=0; i<len; i++)
	{
		if(EE_uart_read_byte_base(base, &vet[i]) != EE_UART_OK)
			return EE_UART_ERR_RECEPTION;
	}
	
	return EE_UART_OK;
}

int EE_uart_write_buffer_base(MicoUart_t* base, char *vet, int len)
{
	int i=0;

	for(i=0; i<len; i++)
	{
		if(EE_uart_write_byte_base(base, vet[i]) != EE_UART_OK)
			return EE_UART_ERR_TRANSMISSION;
	}
	
	return EE_UART_OK;
}

