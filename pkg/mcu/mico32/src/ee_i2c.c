/** 
* ee_i2c.c
*/

#include "mcu/mico32/inc/ee_i2c.h"

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
void EE_i2c_common_handler(int level)
{
	unsigned int iir;
    unsigned int lsr;
    unsigned int spint;
    char data = 0;
    
    EE_i2c_st *i2csp = EE_get_i2c_st_from_level(level);
    OCI2CMDev_t *i2cc = i2csp->base; 

    /* interrogate interrupt-cause */
    ...
    
    /* check the interrupt source */
    switch(...){
        case RX:	/* the interrupt is due to rx-data */
		{
            /* 
	         * read lsr to check for errors associated with current word. 
	         * reading lsr clears error bits 
	         */
            //lsr = uartc->lsr;
            //if((lsr & (MICOUART_LSR_PE_MASK | MICOUART_LSR_FE_MASK)) == 0) if(uiValue & MICOUART_LSR_RX_RDY_MASK)
            data = i2cc->rxtx;
            EE_buffer_putmsg(&(i2csp->rxbuf), &data);
            
            /* Call user Callback */
	            if(i2csp->rxcbk != EE_I2C_NULL_CBK)
            	i2csp->rxcbk();
        }break;
        case TX:	/* the interrupt is due to tx-data */
		{
			spint = 1;
			/* Loop to empty the buffer */
			while(!EE_buffer_isempty(&(i2csp->txbuf)))
			{
				EE_buffer_getmsg(&(i2csp->txbuf), &data);
				lsr = i2cc->lsr;
				//while(!(lsr & MICOUART_LSR_TX_RDY_MASK));	
				i2cc->rxtx = data;
				if(spint) spint = 0;	// is not a spurious interrupt...
			}
			
			/* To avoid interrupt is again asserted by the UART after reading the IIR register, 
	   		   we must to disable TX isr-source. NOTE: Could start spurious tx interrupt... */
			if(i2csp->mode == EE_I2C_RXTX_ISR)
				i2cc->ier = ;						//rx ie mask
			else if(i2csp->mode == EE_I2C_TX_ISR)
				i2cc->ier = 0;
			i2csp->txie = 0;
				
			/* Call user Callback (not for spurious interrupt...) */
	       	if( (i2csp->txcbk != EE_I2C_NULL_CBK) && (!spint) )
            	i2csp->txcbk();
            		
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
    
	return;	
}

/******************************************************************************/
/*                       Public Global Functions                              */
/******************************************************************************/
/* This function records ISR handler */
int EE_hal_i2c_handler_setup(EE_i2c_st* i2csp)
{
    /* Register IRQ handler */
    EE_mico32_register_ISR(i2csp->irqf, EE_i2c_common_handler);	 

	return EE_UART_OK;
}


//int EE_i2c_init(EE_UINT32 base, EE_UINT32 speed, EE_UINT32 settings)
//int EE_i2c_init_base(EE_UINT32 base, EE_UINT32 irq_flag, EE_UINT32 speed, EE_UINT32 settings, EE_mico32_ISR_handler isr_rx_callback, EE_mico32_ISR_handler isr_tx_callback, EE_buffer* rx_buf, EE_buffer* tx_buf)
int EE_hal_i2c_config(EE_i2c_st* i2csp, int baudrate, int setttings)	// baudrate in Hz 									
{
	OCI2CMDev_t *i2cc = i2csp->base;
	
	/* disable core */
	EE_hal_i2c_disable(i2csp);	//i2cc->Control &= ~(unsigned int)(OCI2CM_CTL_CORE_ENABLE);    
	/* Register IRQ handler */
	EE_hal_i2c_handler_setup(i2csp);
	/* Load Prescaler LSB */                       
	i2cc->PrescaleLo = ((MICO32_CPU_CLOCK_MHZ/(5*baudrate)-1));  
	/* Load Prescaler MSB */                                  
    i2cc->PrescaleHi = 0;   
	/* Clear Tx Data */                                         
    i2cc->Data = 0;     
	/* Clear out all commands */                                              
    i2cc->StatusCommand = 0;   
	/* enable core */
	EE_hal_i2c_enable(i2csp);	//i2cc->Control |= OCI2CM_CTL_CORE_ENABLE;  
	
	// All done!!!
	return EE_I2C_OK;
}

int EE_hal_i2c_set_ISR_mode(EE_i2c_st* i2csp, int mode)
{
	int ret;
	int old_mode;
	unsigned int intst;
	
	#ifdef EE_UART_DEBUG
		if( (mode<EE_I2C_POLLING) || (mode>EE_I2C_RXTX_ISR) )
		return EE_I2C_ERR_BAD_VALUE;
	#endif
	
	/* Disble IRQ */
	intst = EE_mico32_disableIRQ();
	
	/* Register IRQ handler */
	EE_hal_i2c_handler_setup(usp);
	
	/* FSM */
	old_mode = usp->mode;
	if(old_mode == mode)
		ret = EE_I2C_OK;
	else
	{	
		usp->mode = mode; 	
		/* Buffer initialization */
		if (EE_i2c_need_init_rx_buf(old_mode, mode))
			EE_buffer_init(&usp->rxbuf, EE_I2C_MSGSIZE, EE_I2C_BUFSIZE, usp->rxbuf.data);
		if (EE_i2c_need_init_tx_buf(old_mode, mode))
			EE_buffer_init(&usp->txbuf, EE_I2C_MSGSIZE, EE_I2C_BUFSIZE, usp->txbuf.data);
		/* IRQ settings */
		if(EE_i2c_need_enable_rx_int(mode))
			i2cc->ier = EE_I2C_RX_INT_MASK;	// check if we lose data when ier is written...	
	}		
	
	/* Enable IRQ */
	if (EE_mico32_are_IRQs_enabled(intst))
        EE_mico32_enableIRQ();
        
	return ret;
}

int EE_hal_i2c_enable_IRQ(EE_i2c_st* i2csp)
{
	OCI2CMDev_t *i2cc = i2csp->base;
	
	i2cc->Control |= OCI2CM_CTL_INT_ENABLE;
	
	return EE_I2C_OK;	
}															

int EE_hal_i2c_disable_IRQ(EE_i2c_st* i2csp)
{
	OCI2CMDev_t *i2cc = i2csp->base;
	
	i2cc->Control &= ~(OCI2CM_CTL_INT_ENABLE);
	
	return EE_I2C_OK;
}

int EE_hal_i2c_set_rx_callback(EE_i2c_st* i2csp, EE_ISR_callback isr_rx_callback)
{
	i2csp->rxcbk = isr_rx_callback;
	
	return EE_I2C_OK;
}

int EE_hal_i2c_set_tx_callback(EE_i2c_st* i2csp, EE_ISR_callback isr_tx_callback)															
{
	i2csp->txcbk = isr_tx_callback;
	
	return EE_I2C_OK;
}

int EE_hal_i2c_disable(EE_i2c_st* i2csp)
{
	OCI2CMDev_t *i2cc = i2csp->base;
	
	/* Clear the ‘EN’ bit only when no transfer is in progress, i.e. after a STOP
	   command, or when the command register has the STO bit set. When halted during a
	   transfer, the core can hang the I2C bus.  
	*/	
	while(tip);
	EE_hal_i2c_stop(i2csp);
	/* disable core */
	i2cc->Control &= ~(unsigned int)(OCI2CM_CTL_CORE_ENABLE); 
	
	// All done!!!
	return EE_I2C_OK;
}

int EE_hal_i2c_enable(EE_i2c_st* i2csp)
{
	OCI2CMDev_t *i2cc = (OCI2CMDev_t *)base;
	
	/* enable core */
	i2cc->Control |= OCI2CM_CTL_CORE_ENABLE;  
	
	// All done!!!
	return EE_I2C_OK;
}

int EE_hal_i2c_start(EE_i2c_st* i2csp)
{
	OCI2CMDev_t *i2cc = i2csp->base;
	
	/* wait for pending transaction to complete */
    OCI2CM_PEND_FOR_TIP_DONE(i2csp->base);

    /* issue a start */
    i2cc->StatusCommand = OCI2CM_CMD_START;

    /*
     * see if arbitration was lost; return 0 if arbitration
     * wasn't lost i.e. start was successful
     */
    return ( i2cc->StatusCommand & OCI2CM_STATUS_ARB_LOST );
}

int EE_hal_i2c_stop(EE_i2c_st* i2csp)
{
	OCI2CMDev_t *i2cc = i2csp->base;

    /* wait for pending transaction to complete */
    OCI2CM_PEND_FOR_TIP_DONE(i2csp->base);

    /* issue a stop */
    i2cc->StatusCommand = OCI2CM_CMD_STOP;

    /* all done */
    return EE_I2C_OK;
}

int EE_hal_i2c_write_buffer(EE_i2c_st* i2csp, int address, char *vet, int len)	// ATT! vet is a vector of messages (packets)
{
	int i, mode;
	int ret;
	EE_buffer* buffer;
	
	OCI2CMDev_t *i2cc = i2csp->base;

	buffer = i2csp->txbuf;
	mode = i2csp->mode;
	
	if( (mode!=EE_I2C_TX_ISR) && (mode!=EE_I2C_RXTX_ISR) )	// POLLING MODE
	{
		/* load address, set-up a write to write the address out to the bus */
    	i2cc->Data = ((address<<1) & ~OCI2CM_RW_MASK);
    	/* initiate a start (repeated) and write out the address */
    	i2cc->StatusCommand = (OCI2CM_CMD_START|OCI2CM_CMD_WRITE);
    	//i2cc->StatusCommand = (OCI2CM_CMD_WRITE);
    	/* wait for transfer to complete */
    	OCI2CM_PEND_FOR_TIP_DONE(i2csp->base);
    	/* check if ack is received */
    	if( i2cc->StatusCommand & OCI2CM_STATUS_RX_ACK )
        	ret = EE_I2C_ERR_ADD_ACK;
        else
        {
    		/* transfer the bytes */
    		for ( i = 0; i < len; i++)
    		{
        		/* load data in register */
        		i2cc->Data = (unsigned int)(vet[i]);
        		/* write the data out to the bus  */
        		i2cc->StatusCommand = OCI2CM_CMD_WRITE;
        		/* wait for current transfer to complete */
        		OCI2CM_PEND_FOR_TIP_DONE(i2csp->base);
        		/* check for ack */
        		if( i2cc->StatusCommand & OCI2CM_STATUS_RX_ACK )
            		ret = EE_I2C_ERR_DATA_ACK;
    		}
    		/* see if arbitration was lost during this transaction */
    		if( i2cc->StatusCommand & OCI2CM_STATUS_ARB_LOST )
        		ret = EE_I2C_ERR_ARB;
    		else
    		{
				EE_hal_i2c_stop(i2csp);
				// All done!!!
        		ret = EE_I2C_OK;
			}
		}
	}
	else
	{
		for(i=0;i<len,i++)
		{
			ret = EE_buffer_putmsg(buffer, vet[i]);	
			...tx ie...
		}
	}
	
	// All done!!!
	return ret;
	
    
}

int EE_hal_i2c_write_byte(EE_i2c_st* i2csp, int address, char data)	// ATT! data is a message (packet)
{
	int mode;
	int ret;
	EE_buffer* buffer;
	
	OCI2CMDev_t *i2cc = i2csp->base;

	buffer = i2csp->txbuf;
	mode = i2csp->mode;
	
	if( (mode!=EE_I2C_TX_ISR) && (mode!=EE_I2C_RXTX_ISR) )	// POLLING MODE
	{
	    /* load address, set-up a write to write the address out to the bus */
	    i2cc->Data = ((address<<1) & ~OCI2CM_RW_MASK);
	    /* initiate a start (repeated) and write out the address */
	    i2cc->StatusCommand = (OCI2CM_CMD_START|OCI2CM_CMD_WRITE);
	    /* wait for transfer to complete */
	    OCI2CM_PEND_FOR_TIP_DONE(i2csp->base);
	    /* check if ack is received */
	    if( i2cc->StatusCommand & OCI2CM_STATUS_RX_ACK )
	        ret = EE_I2C_ERR_ADD_ACK;
	    else
	    {
	    	/* load data in register */
		    i2cc->Data = (unsigned int)data;
		    /* write the data out to the bus */
		    i2cc->StatusCommand = OCI2CM_CMD_WRITE;
		    /* wait for current transfer to complete */
		    OCI2CM_PEND_FOR_TIP_DONE(base);
		    /* check for ack  and if arb was lost during this transaction */
		    if( i2cc->StatusCommand & OCI2CM_STATUS_RX_ACK )
		        ret = EE_I2C_ERR_DATA_ACK;
		    else if( i2cc->StatusCommand & OCI2CM_STATUS_ARB_LOST )
		        ret = EE_I2C_ERR_ARB;
		    else
		        ret = EE_I2C_OK;
		}
	}
	else
	{
		ret = EE_buffer_putmsg(buffer, data);	
		...tx ie...
	}
	
	// All done!!!
	return ret;
}
	
int EE_hal_i2c_read_buffer(EE_i2c_st* i2csp, int address, char *vet, int len)	// ATT! vet is a vector of messages (packets)
{
	int i, mode;
	int ret;
	EE_buffer* buffer;
	
	OCI2CMDev_t *i2cc = i2csp->base;

	buffer = i2csp->rxbuf;
	mode = i2csp->mode;

	if( (mode!=EE_I2C_TX_ISR) && (mode!=EE_I2C_RXTX_ISR) )	// POLLING MODE
	{
		/* load address, set-up a write to write the address out to the bus */
	    i2cc->Data = ((address<<1) | (OCI2CM_RW_MASK) );
	    /* initiate a start (repeated) and write out the address */
	    i2cc->StatusCommand = (OCI2CM_CMD_START|OCI2CM_CMD_WRITE);
	    /* wait for transfer to complete */
	    OCI2CM_PEND_FOR_TIP_DONE(i2csp->base);
	    /* check if ack is received */
	    if( i2cc->StatusCommand & OCI2CM_STATUS_RX_ACK )
	        ret = EE_I2C_ERR_ADD_ACK;
	    else
	    {
	    	/* begin reading data */
	    	for (i = 0; i < len; i++)
	    	{
	        	/* read data; send ACK on all reads except the last one */
	        	if( i == (len - 1) )
	            	i2cc->StatusCommand = (OCI2CM_CMD_READ|OCI2CM_CMD_NACK);
	        	else
	            	pDevStruct->StatusCommand = (OCI2CM_CMD_READ|OCI2CM_CMD_ACK);	
	        	/* wait while transfer is in progress */
	        	OCI2CM_PEND_FOR_TIP_DONE(i2csp->base);
	        	/* read data */
	        	vet[i] = (char)(i2cc->Data);
			}
	    }
	    /* check for ack  and if arb was lost during this transaction */
	    if( i2cc->StatusCommand & OCI2CM_STATUS_ARB_LOST )
	        ret = EE_I2C_ERR_ARB;
	    else
	        ret = EE_I2C_OK;	// return the number of bytes received... 
	}
	else
	{
		for(i=0;i<len,i++)
		{
			ret = EE_buffer_getmsg(buffer, vet[i]);
		}	
	}
	
	// All done!!!
	return ret;
}	
	
int EE_hal_i2c_read_byte(EE_i2c_st* i2csp, int address, char *adddata)			// ATT! adddata is a pointer to message (packet)
{
	int mode;
	int ret;
	EE_buffer* buffer;
	
	OCI2CMDev_t *i2cc = i2csp->base;

	buffer = i2csp->rxbuf;
	mode = i2csp->mode;

	if( (mode!=EE_I2C_TX_ISR) && (mode!=EE_I2C_RXTX_ISR) )	// POLLING MODE
	{
	    /* load address, set-up a write to write the address out to the bus */
	    i2cc->Data = ((address<<1) | (OCI2CM_RW_MASK) );
	    /* initiate a start (repeated) and write out the address */
	    i2cc->StatusCommand = (OCI2CM_CMD_START|OCI2CM_CMD_WRITE);
	    /* wait for transfer to complete */
	    OCI2CM_PEND_FOR_TIP_DONE(base);
	    /* check if ack is received */
	    if( i2cc->StatusCommand & OCI2CM_STATUS_RX_ACK )
	        ret = EE_I2C_ERR_ADD_ACK;
	    else
	    {
	    	/* issue a read with a NACK */
	    	i2cc->StatusCommand = (OCI2CM_CMD_READ | OCI2CM_CMD_NACK);
	    	/* wait till transfer is in progress */
	    	while(i2cc->StatusCommand & OCI2CM_STATUS_TRANSFER);
	    	/* read data */
	    	*adddata = (unsigned char)(i2cc->Data);
	    	/* check for ack  and if arb was lost during this transaction */
	    	if( i2cc->StatusCommand & OCI2CM_STATUS_ARB_LOST )
	        	 ret = EE_I2C_ERR_ARB;
	    	else
	        	return EE_I2C_OK;
		}
	}
	else
	{
		ret = EE_buffer_getmsg(buffer, adddata);	
	}
	
	// All done!!!
	return ret;
}
	
