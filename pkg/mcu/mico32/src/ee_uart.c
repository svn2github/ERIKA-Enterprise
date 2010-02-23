/** 
* @file ee_uart.c
*/

#include "mcu/mico32/inc/ee_uart.h"

/******************************************************************************/
/*                             Utility Macros                                 */
/******************************************************************************/
// ...

/******************************************************************************/
/*                       Private Local Variables                              */
/******************************************************************************/
/* Vectors and uart structures definitions */
#ifdef EE_UART1_NAME_UC
DEFINE_VET_UART(EE_UART1_NAME_UC, EE_UART1_NAME_LC)
DEFINE_STRUCT_UART(EE_UART1_NAME_UC, EE_UART1_NAME_LC)
#endif

#ifdef EE_UART2_NAME_UC
DEFINE_VET_UART(EE_UART2_NAME_UC, EE_UART2_NAME_LC)
DEFINE_STRUCT_UART(EE_UART2_NAME_UC, EE_UART2_NAME_LC)
#endif

/******************************************************************************/
/*                       Private Local Functions                              */
/******************************************************************************/
// ...

/******************************************************************************/
/*                              ISRs                                          */
/******************************************************************************/
// Interrupt common handler:
void EE_uart_common_handler(int level)
{
    unsigned int iir;
    unsigned int spint;
    char data = 0;
    
    EE_uart_st *usp = EE_get_uart_st_from_level(level);
    MicoUart_t *uartc = usp->base; 

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
            //if((lsr & (MICOUART_LSR_PE_MASK | MICOUART_LSR_FE_MASK)) == 0) if(uiValue & MICOUART_LSR_RX_RDY_MASK)
            data = uartc->rxtx;
            EE_buffer_putmsg(&(usp->rxbuf), &data);
            
            /* Call user Callback */
            if(usp->rxcbk != EE_UART_NULL_CBK)
            	usp->rxcbk();
        }break;
        case MICOUART_IIR_TXRDY:	/* the interrupt is due to tx-data */
		{
			spint = 1;
			/* Loop to empty the buffer */
			while(!EE_buffer_isempty(&(usp->txbuf)))
			{
				EE_buffer_getmsg(&(usp->txbuf), &data);
				while( !((uartc->lsr) & MICOUART_LSR_TX_RDY_MASK) );	
				uartc->rxtx = data;
				if(spint) spint = 0;	// is not a spurious interrupt...
			}
			
			/* To avoid interrupt is again asserted by the UART after reading the IIR register, 
	   		   we must to disable TX isr-source. NOTE: Could start spurious tx interrupt... */
			if(usp->mode == EE_UART_RXTX_ISR)
				uartc->ier = (volatile unsigned int)(MICOUART_IER_RX_INT_MASK);
			else if(usp->mode == EE_UART_TX_ISR)
				uartc->ier = 0;
				
			/* Call user Callback (not for spurious interrupt...) */
	       	if( (usp->txcbk != EE_UART_NULL_CBK) && (!spint) )
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

    return;
}


/******************************************************************************/
/*                       Public Global Functions                              */
/******************************************************************************/
/* This function records ISR handler */
int EE_hal_uart_handler_setup(EE_uart_st* usp)
{
    /* Register IRQ handler */
    EE_mico32_register_ISR(usp->irqf, EE_uart_common_handler);	 

	return EE_UART_OK;
}

/* This function configures UART baudrate and other features (parity, stop bits...) */
int EE_hal_uart_config(EE_uart_st* usp, int baudrate, int settings)
{
	unsigned int iir;
	MicoUart_t *uartc = usp->base; 
	
	/* reset ier (isr register) */
    uartc->ier = 0;						// if ier==0 -> POLLING MODE (ATT! is a blocking mode!!!)
    									// if ier!=0 -> ISR MODE (ATT! is not a blocking mode!!!)
    iir = uartc->iir;					// read iir register to clean ISR flags.	FARE PROVA!!!
	
	/* Register IRQ handler */
    EE_hal_uart_handler_setup(usp);
    
	/* set the control register */
    uartc->lcr = settings;    
    
    /* Calculate clock-divisor */
    uartc->div = (MICO32_CPU_CLOCK_MHZ)/baudrate;
    
    /* ISR management */
    return EE_UART_OK;	//EE_uart_set_ISR_callback_base(base, irq_flag, ie_flag, isr_rx_callback, isr_tx_callback);
}

/* This function sets UART operating mode */
int EE_hal_uart_set_ISR_mode(EE_uart_st* usp, int mode)
{
	int old_mode;
	unsigned int intst;
	
	MicoUart_t *uartc = usp->base; 
	
	#ifdef EE_UART_DEBUG
	if( (mode<EE_UART_POLLING) || (mode>EE_UART_RXTX_ISR) )
	{
		usp->err = EE_UART_ERR_BAD_VALUE;
		return EE_UART_ERR_BAD_VALUE;
	}
	#endif
	
	old_mode = usp->mode;
	if(old_mode == mode)
		return EE_UART_OK;
	
	/* Disble IRQ */
	intst = EE_mico32_disableIRQ();
	
	/* Register IRQ handler */
	EE_hal_uart_handler_setup(usp);
	usp->mode = mode; 	
	/* Buffer initialization */
	if (EE_uart_need_init_rx_buf(old_mode, mode))
		EE_buffer_init(&usp->rxbuf, EE_UART_MSGSIZE, EE_UART_BUFSIZE, usp->rxbuf.data);
	if (EE_uart_need_init_tx_buf(old_mode, mode))
		EE_buffer_init(&usp->txbuf, EE_UART_MSGSIZE, EE_UART_BUFSIZE, usp->txbuf.data);
	/* IRQ settings */
	if(EE_uart_need_enable_rx_int(mode))
		uartc->ier = (volatile unsigned int)(MICOUART_IER_RX_INT_MASK);	// check if we lose data when ier is written...	
		
	/* Enable IRQ */
	if (EE_mico32_are_IRQs_enabled(intst))
        EE_mico32_enableIRQ();
        
	return EE_UART_OK;
}

/* This functions sets rx callback */
int EE_hal_uart_set_rx_callback(EE_uart_st* usp, EE_ISR_callback isr_rx_callback)
{
	usp->rxcbk = isr_rx_callback;
	
	return EE_UART_OK;
}

/* This functions sets tx callback */
int EE_hal_uart_set_tx_callback(EE_uart_st* usp, EE_ISR_callback isr_tx_callback)
{
	usp->txcbk = isr_tx_callback;
	
	return EE_UART_OK;
}

/* This functions can be used to write a character */
int EE_hal_uart_write_byte(EE_uart_st* usp, char data)
{
	unsigned int uiValue, mode;
	EE_buffer* buffer;
	int ret;
	unsigned int intst;
  
	MicoUart_t *uartc = usp->base; 
	
	buffer = &usp->txbuf;
	mode = usp->mode;
	
	if( EE_uart_tx_polling(mode) )	// POLLING MODE
	{
		do
		{
			/* if uart's ready to accept character, send immediately */
    		uiValue = uartc->lsr;
    		if(uiValue & MICOUART_LSR_TX_RDY_MASK)
			{
    			uartc->rxtx = data;
    			break;
			}
			// if you don't want a blocking procedure return here...
		}while(1);
		ret = 1;		// one byte transmitted
    	usp->err = EE_UART_OK;
	}
	else
	{
		ret = EE_buffer_putmsg(buffer, &data);
		usp->err = ret;
		intst = EE_mico32_disableIRQ();				//EE_hal_disableIRQ();
		if(mode == EE_UART_TX_ISR)
			uartc->ier = (volatile unsigned int)(MICOUART_IER_TX_INT_MASK);	// Enable interrupts to empty the tx buffer...
		else
			uartc->ier = (volatile unsigned int)(MICOUART_IER_RX_INT_MASK | MICOUART_IER_TX_INT_MASK);
		if (EE_mico32_are_IRQs_enabled(intst))		//EE_hal_enableIRQ();
        	EE_mico32_enableIRQ();
        if(ret == EE_BUF_OK)
        	ret = 1;	// one byte loaded in the buffer
	}
	
	// All done!!!
	return ret;
}

/* This functions can be used to read a character */
int EE_hal_uart_read_byte(EE_uart_st* usp, char *adddata)
{
	unsigned int uiValue, mode;
	int ret;
	EE_buffer* buffer;
	
	MicoUart_t *uartc = usp->base; 

	buffer = &usp->rxbuf;
	mode = usp->mode;
	
	if( EE_uart_rx_polling(mode) )	// POLLING MODE
	{
		do
		{
			uiValue = uartc->lsr;
			if(uiValue & MICOUART_LSR_RX_RDY_MASK)
			{
    			*adddata = uartc->rxtx;
        		// All done!!!
    			break;
    		}
    		// if you don't want a blocking procedure return here...
		}while(1);
		ret = 1;			// one byte received.
    	usp->err = EE_UART_OK;
	}
	else
	{
		ret = EE_buffer_getmsg(buffer, adddata);	
		usp->err = ret;
		if(ret == EE_BUF_OK)
			ret = 1;		// one byte read from the buffer.
	}
		
    // All done!!!
	return ret;
}

/* This functions can be used to write a buffer of characters */
int EE_hal_uart_write_buffer(EE_uart_st* usp, char *vet, int len)
{
	unsigned int uiValue, mode;
	EE_buffer* buffer;
	int ret,i;
	unsigned int intst;
  
	MicoUart_t *uartc = usp->base; 
	
	buffer = &usp->txbuf;
	mode = usp->mode;
	
	if( EE_uart_tx_polling(mode) )	// POLLING MODE
	{
		for(i=0; i<len; i++)
		{
			do
			{
				/* if uart's ready to accept character, send immediately */
    			uiValue = uartc->lsr;
    			if(uiValue & MICOUART_LSR_TX_RDY_MASK)
				{
    				uartc->rxtx = vet[i];
    				break;
				}
				// if you don't want a blocking procedure return here...
			}while(1);
		}
		ret = len;		// number of bytes transmitted... 
    	usp->err = EE_UART_OK;
	}
	else
	{
		for(i=0; i<len; i++)
		{
			ret = EE_buffer_putmsg(buffer, vet+i);
			usp->err = ret;
			if( ret != EE_BUF_OK )
				break;
		}
		intst = EE_mico32_disableIRQ();				//EE_hal_disableIRQ();
		if(mode == EE_UART_TX_ISR)
			uartc->ier = (volatile unsigned int)(MICOUART_IER_TX_INT_MASK);	// Enable interrupts to empty the tx buffer...
		else
			uartc->ier = (volatile unsigned int)(MICOUART_IER_RX_INT_MASK | MICOUART_IER_TX_INT_MASK);
		if (EE_mico32_are_IRQs_enabled(intst))		//EE_hal_enableIRQ();
        	EE_mico32_enableIRQ();
        ret = i;		// number of bytes loaded in the tx buffer
	}
	
	// All done!!!
	return ret;
}

/* This functions can be used to read a buffer of characters */
int EE_hal_uart_read_buffer(EE_uart_st* usp, char *vet, int len)
{
	int i;

	for(i=0; i<len; i++)
	{
		if(EE_hal_uart_read_byte(usp, &vet[i]) < 0)
			break;
	}
	
	return i;	// number of bytes read.
}

/* This functions enables IRQ */
int EE_hal_uart_enable_IRQ(EE_uart_st* usp, int ier)
{
	usp->base->ier = (volatile unsigned int)(ier);
	
	return EE_UART_OK;
}

/* This functions disables IRQ */
int EE_hal_uart_disable_IRQ(EE_uart_st* usp)
{
	usp->base->ier = 0;
	
	return EE_UART_OK;
}

