/** 
* ee_i2c.c
*/

#include "mcu/mico32/inc/ee_i2c.h"
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
void EE_i2c_handler(EE_i2c_st* i2csp)
{
	OCI2CMDev_t *i2cc = (i2cspOCI2CMDev_t *)(i2csp->base);
	
	return;	
}

/******************************************************************************/
/*                       Public Global Functions                              */
/******************************************************************************/
//EE_UINT8 EE_i2c_init(EE_UINT32 base, EE_UINT32 speed, EE_UINT32 settings)
EE_UINT8 EE_i2c_init_base(EE_UINT32 base, EE_UINT32 irq_flag, EE_UINT32 speed, EE_UINT32 settings, EE_mico32_ISR_handler isr_rx_callback, EE_mico32_ISR_handler isr_tx_callback, EE_buffer* rx_buf, EE_buffer* tx_buf)
{
	OCI2CMDev_t *i2cc = (OCI2CMDev_t *)base;
	
	switch(base)
	{
		case I2C1_BASE_ADDRESS:
			ee_i2c_st_1.base = base;
			break;
		case I2C2_BASE_ADDRESS:
			ee_i2c_st_2.base = base;
			break;
		default:
			return(EE_I2C_ERR_BAD_VALUE);
	}    
	
	/* disable core */
	i2cc->Control &= ~(unsigned int)(OCI2CM_CTL_CORE_ENABLE);    
	/* Load Prescaler LSB */                       
	i2cc->PrescaleLo = ((MICO32_CPU_CLOCK_MHZ/(5*speed*1000)-1));  
	/* Load Prescaler MSB */                                  
    i2cc->PrescaleHi = 0;   
	/* Clear Tx Data */                                         
    i2cc->Data = 0;     
	/* Clear out all commands */                                              
    i2cc->StatusCommand = 0;   
	/* Isr management */
	EE_i2c_set_ISR_callback_base(base, irq_flag, isr_rx_callback, isr_tx_callback, rx_buf, tx_buf);                            
	    
	// All done!!!
	return EE_I2C_OK;
}

EE_UINT8 EE_i2c_set_ISR_callback_base(EE_UINT32 base, EE_UINT32 irq_flag, EE_mico32_ISR_handler isr_rx_callback, EE_mico32_ISR_handler isr_tx_callback, EE_buffer* rx_buf, EE_buffer* tx_buf)
{
	OCI2CMDev_t *i2cc = (OCI2CMDev_t *)base;
	
	/* reset isr register */
	// ...
	
	switch(base)
	{
		case I2C1_BASE_ADDRESS:
			ee_i2c_st_1.rxcbk = isr_rx_callback;
			ee_i2c_st_1.txcbk = isr_tx_callback;
			ee_i2c_st_1.rxbuf = rx_buf;
			ee_i2c_st_1.txbuf = tx_buf;
			if( (isr_rx_callback != EE_I2C_NULL_CBK)  || (isr_tx_callback != EE_I2C_NULL_CBK) )
			{
				/* Register handler and enable the interrupt */
				EE_mico32_register_ISR(irq_flag, EE_i2c1_handler);
				if(isr_rx_callback != EE_I2C_NULL_CBK)
					i2cc->Control = OCI2CM_CTL_CORE_ENABLE | OCI2CM_CTL_INT_ENABLE;
				else if(isr_tx_callback != EE_I2C_NULL_CBK)
					i2cc->Control = OCI2CM_CTL_CORE_ENABLE | OCI2CM_CTL_INT_ENABLE;
			}
			break;
		case I2C2_BASE_ADDRESS:
			ee_i2c_st_2.rxcbk = isr_rx_callback;
			ee_i2c_st_2.txcbk = isr_tx_callback;
			ee_i2c_st_2.rxbuf = rx_buf;
			ee_i2c_st_2.txbuf = tx_buf;
			if( (isr_rx_callback != EE_I2C_NULL_CBK)  || (isr_tx_callback != EE_I2C_NULL_CBK) )
			{
				/* Register handler and enable the interrupt */
				EE_mico32_register_ISR(irq_flag, EE_i2c2_handler);
				if(isr_rx_callback != EE_I2C_NULL_CBK)
					i2cc->Control = OCI2CM_CTL_CORE_ENABLE | OCI2CM_CTL_INT_ENABLE;
				if(isr_tx_callback != EE_I2C_NULL_CBK)
					i2cc->Control = OCI2CM_CTL_CORE_ENABLE | OCI2CM_CTL_INT_ENABLE;
			}
			break;
		default:
			return(EE_I2C_ERR_BAD_VALUE);
	}   
	
	// All done!!!
	return EE_I2C_OK;	
}

EE_UINT8 EE_i2c_disable_base(EE_UINT32 base)
{
	OCI2CMDev_t *i2cc = (OCI2CMDev_t *)base;
	
	/* disable core */
	i2cc->Control &= ~(unsigned int)(OCI2CM_CTL_CORE_ENABLE); 
	
	// All done!!!
	return EE_I2C_OK;
}

EE_UINT8 EE_i2c_enable_base(EE_UINT32 base)
{
	OCI2CMDev_t *i2cc = (OCI2CMDev_t *)base;
	
	/* enable core */
	i2cc->Control |= OCI2CM_CTL_CORE_ENABLE;  
	
	// All done!!!
	return EE_I2C_OK;
}

EE_UINT8 EE_i2c_start_base(EE_UINT32 base)
{
	OCI2CMDev_t *i2cc = (OCI2CMDev_t *)base;
	
	/* wait for pending transaction to complete */
    OCI2CM_PEND_FOR_TIP_DONE(base);

    /* issue a start */
    i2cc->StatusCommand = OCI2CM_CMD_START;

    /*
     * see if arbitration was lost; return 0 if arbitration
     * wasn't lost i.e. start was successful
     */
    return ( i2cc->StatusCommand & OCI2CM_STATUS_ARB_LOST );
}

EE_UINT8 EE_i2c_stop_base(EE_UINT32 base)
{
	OCI2CMDev_t *i2cc = (OCI2CMDev_t *)base;

    /* wait for pending transaction to complete */
    OCI2CM_PEND_FOR_TIP_DONE(base);

    /* issue a stop */
    i2cc->StatusCommand = OCI2CM_CMD_STOP;

    /* all done */
    return EE_I2C_OK;
}

EE_UINT8 EE_i2c_write_buffer_base(EE_UINT32 base, EE_UINT32 address, EE_INT8 *vet, EE_INT16 len)
{
	unsigned int i, polling_mode;
	EE_buffer* buffer;
	OCI2CMDev_t *i2cc = (OCI2CMDev_t *)base;

	switch(base)
	{
		case I2C1_BASE_ADDRESS:
			buffer = ee_i2c_st_1.txbuf;
			polling_mode = (ee_i2c_st_1.txcbk == EE_I2C_NULL_CBK);
			break;
		case I2C2_BASE_ADDRESS:
			buffer = ee_i2c_st_2.txbuf;
			polling_mode = (ee_i2c_st_2.txcbk == EE_I2C_NULL_CBK);
			break;
		default:
			return(EE_I2C_ERR_BAD_VALUE);
	}   
	
	if(polling_mode)	// POLLING MODE
	{
		/* load address, set-up a write to write the address out to the bus */
    	i2cc->Data = ((address<<1) & ~OCI2CM_RW_MASK);
    	/* initiate a start (repeated) and write out the address */
    	i2cc->StatusCommand = (OCI2CM_CMD_START|OCI2CM_CMD_WRITE);
    	//i2cc->StatusCommand = (OCI2CM_CMD_WRITE);
    	/* wait for transfer to complete */
    	OCI2CM_PEND_FOR_TIP_DONE(base);
    	/* check if ack is received */
    	if( i2cc->StatusCommand & OCI2CM_STATUS_RX_ACK )
        	return -1;
    	/* transfer the bytes */
    	for ( i = 0; i < buffersize; ++i, ++data )
    	{
        	/* load data in register */
        	i2cc->Data = (unsigned int)(*data);
        	/* write the data out to the bus  */
        	i2cc->StatusCommand = OCI2CM_CMD_WRITE;
        	/* wait for current transfer to complete */
        	OCI2CM_PEND_FOR_TIP_DONE(base);
        	/* check for ack */
        	if( i2cc->StatusCommand & OCI2CM_STATUS_RX_ACK )
            	return -2;
    	}
    	/* see if arbitration was lost during this transaction */
    	if( i2cc->StatusCommand & OCI2CM_STATUS_ARB_LOST )
        	return -3;
    	else
    	{
			EE_i2c_stop_base(base);
			// All done!!!
        	return EE_I2C_OK;
		}
	}
	else
	{
		for(i=0;i<len,i++)
		{
			ret = EE_buffer_putmsg(buffer, vet[i]);	
			if(ret<0)
				return error;
		}
	}
	else
		 return EE_UART_ERR_BAD_VALUE;
	
	// All done!!!
	return ret;
	
    
}

EE_UINT8 EE_i2c_write_byte_base(EE_UINT32 base, EE_UINT32 address, EE_INT8 data)
{
	unsigned int i, polling_mode;
	EE_buffer* buffer;
	OCI2CMDev_t *i2cc = (OCI2CMDev_t *)base;

	switch(base)
	{
		case I2C1_BASE_ADDRESS:
			buffer = ee_i2c_st_1.txbuf;
			polling_mode = (ee_i2c_st_1.txcbk == EE_I2C_NULL_CBK);
			break;
		case I2C2_BASE_ADDRESS:
			buffer = ee_i2c_st_2.txbuf;
			polling_mode = (ee_i2c_st_2.txcbk == EE_I2C_NULL_CBK);
			break;
		default:
			return(EE_I2C_ERR_BAD_VALUE);
	}   
	
	if(polling_mode)	// POLLING MODE
	{
		OCI2CMDev_t *i2cc = (OCI2CMDev_t *)base;
	    /* load address, set-up a write to write the address out to the bus */
	    i2cc->Data = ((address<<1) & ~OCI2CM_RW_MASK);
	    /* initiate a start (repeated) and write out the address */
	    i2cc->StatusCommand = (OCI2CM_CMD_START|OCI2CM_CMD_WRITE);
	    /* wait for transfer to complete */
	    OCI2CM_PEND_FOR_TIP_DONE(base);
	    /* check if ack is received */
	    if( i2cc->StatusCommand & OCI2CM_STATUS_RX_ACK )
	        return -1;
	    /* load data in register */
	    i2cc->Data = (unsigned int)data;
	    /* write the data out to the bus */
	    i2cc->StatusCommand = OCI2CM_CMD_WRITE;
	    /* wait for current transfer to complete */
	    OCI2CM_PEND_FOR_TIP_DONE(base);
	    /* check for ack  and if arb was lost during this transaction */
	    if( i2cc->StatusCommand & OCI2CM_STATUS_RX_ACK )
	        return -2;
	    else if( i2cc->StatusCommand & OCI2CM_STATUS_ARB_LOST )
	        return -3;
	    else
	        return EE_I2C_OK;
	}
	else
	{
		ret = EE_buffer_putmsg(buffer, vet[i]);	
	}
	
	// All done!!!
	return ret;
}
	
EE_UINT8 EE_i2c_read_buffer_base(EE_UINT32 base, unsigned int address, unsigned int buffersize, unsigned char *data)
{
	//unsigned int i;
    //unsigned int uiData;
	unsigned int i, polling_mode;
	EE_buffer* buffer;
	OCI2CMDev_t *i2cc = (OCI2CMDev_t *)base;

	switch(base)
	{
		case I2C1_BASE_ADDRESS:
			buffer = ee_i2c_st_1.rxbuf;
			polling_mode = (ee_i2c_st_1.rxcbk == EE_I2C_NULL_CBK);
			break;
		case I2C2_BASE_ADDRESS:
			buffer = ee_i2c_st_2.rxbuf;
			polling_mode = (ee_i2c_st_2.rxcbk == EE_I2C_NULL_CBK);
			break;
		default:
			return(EE_I2C_ERR_BAD_VALUE);
	}   
	
	if(polling_mode)	// POLLING MODE
	{
		OCI2CMDev_t *i2cc = (OCI2CMDev_t *)base;
		/* load address, set-up a write to write the address out to the bus */
	    i2cc->Data = ((address<<1) | (OCI2CM_RW_MASK) );
	    /* initiate a start (repeated) and write out the address */
	    i2cc->StatusCommand = (OCI2CM_CMD_START|OCI2CM_CMD_WRITE);
	    /* wait for transfer to complete */
	    OCI2CM_PEND_FOR_TIP_DONE(base);
	    /* check if ack is received */
	    if( i2cc->StatusCommand & OCI2CM_STATUS_RX_ACK )
	        return -1;
	    /* begin reading data */
	    for (i = 0; i < buffersize; ++i, ++data)
	    {
	        /* read data; send ACK on all reads except the last one */
	        if( i == (buffersize - 1) )
	            i2cc->StatusCommand = (OCI2CM_CMD_READ|OCI2CM_CMD_NACK);
	        else
	            pDevStruct->StatusCommand = (OCI2CM_CMD_READ|OCI2CM_CMD_ACK);
	
	        /* wait while transfer is in progress */
	        OCI2CM_PEND_FOR_TIP_DONE(base);
	
	        /* read data */
	        *data = (unsigned char)(i2cc->Data);
	    }
	    /* check for ack  and if arb was lost during this transaction */
	    if( i2cc->StatusCommand & OCI2CM_STATUS_ARB_LOST )
	        return -3;
	    else
	        return EE_I2C_OK;	// return the number of bytes received... 
	}
	else
	{
		for(i=0;i<len,i++)
		{
			ret = EE_buffer_getmsg(buffer, data);
			if(ret<0)
				return error;
		}	
	}
	
	// All done!!!
	return ret;
}	
	
EE_UINT8 EE_i2c_read_byte_base(EE_UINT32 base, unsigned int address, unsigned char *data)
{
	//unsigned int i;
    //unsigned int uiData;
	unsigned int i, polling_mode;
	EE_buffer* buffer;
	OCI2CMDev_t *i2cc = (OCI2CMDev_t *)base;

	switch(base)
	{
		case I2C1_BASE_ADDRESS:
			buffer = ee_i2c_st_1.rxbuf;
			polling_mode = (ee_i2c_st_1.rxcbk == EE_I2C_NULL_CBK);
			break;
		case I2C2_BASE_ADDRESS:
			buffer = ee_i2c_st_2.rxbuf;
			polling_mode = (ee_i2c_st_2.rxcbk == EE_I2C_NULL_CBK);
			break;
		default:
			return(EE_I2C_ERR_BAD_VALUE);
	}   
	
	if(polling_mode)	// POLLING MODE
	{
		OCI2CMDev_t *i2cc = (OCI2CMDev_t *)base;
	    /* load address, set-up a write to write the address out to the bus */
	    i2cc->Data = ((address<<1) | (OCI2CM_RW_MASK) );
	    /* initiate a start (repeated) and write out the address */
	    i2cc->StatusCommand = (OCI2CM_CMD_START|OCI2CM_CMD_WRITE);
	    /* wait for transfer to complete */
	    OCI2CM_PEND_FOR_TIP_DONE(base);
	    /* check if ack is received */
	    if( i2cc->StatusCommand & OCI2CM_STATUS_RX_ACK )
	        return -1;
	    /* issue a read with a NACK */
	    i2cc->StatusCommand = (OCI2CM_CMD_READ | OCI2CM_CMD_NACK);
	    /* wait till transfer is in progress */
	    while(i2cc->StatusCommand & OCI2CM_STATUS_TRANSFER);
	    /* read data */
	    *data = (unsigned char)(i2cc->Data);
	    /* check for ack  and if arb was lost during this transaction */
	    if( i2cc->StatusCommand & OCI2CM_STATUS_ARB_LOST )
	        return -3;
	    else
	        return EE_I2C_OK;
	}
	else
	{
		ret = EE_buffer_getmsg(buffer, data);	
	}
	
	// All done!!!
	return ret;
}
	
