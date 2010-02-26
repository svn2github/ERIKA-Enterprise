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
/* Vectors and I2C structures definitions */

#ifdef __USE_I2C_IRQ__

#ifdef EE_I2C1_NAME_UC
DEFINE_VET_I2C(EE_I2C1_NAME_UC, EE_I2C1_NAME_LC)
DEFINE_STRUCT_I2C(EE_I2C1_NAME_UC, EE_I2C1_NAME_LC)
#endif

#ifdef EE_I2C2_NAME_UC
DEFINE_VET_I2C(EE_I2C2_NAME_UC, EE_I2C2_NAME_LC)
DEFINE_STRUCT_I2C(EE_I2C2_NAME_UC, EE_I2C2_NAME_LC)
#endif

#endif //#ifdef __USE_I2C_IRQ__

/******************************************************************************/
/*                       Private Local Functions                              */
/******************************************************************************/
// ...

/******************************************************************************/
/*                              ISRs                                          */
/******************************************************************************/
#ifdef __USE_I2C_IRQ__

void EE_i2c_common_handler(int level)
{

//    EE_i2c_st *i2csp = EE_get_i2c_st_from_level(level);
//    OCI2CMDev_t *i2cc = i2csp->base; 

	return;	
}

#endif //#ifdef __USE_I2C_IRQ__

/******************************************************************************/
/*                       Public Global Functions                              */
/******************************************************************************/

/* This function records ISR handler */
int EE_hal_i2c_handler_setup(EE_i2c_st* i2csp)
{
    /* Register IRQ handler */
    EE_mico32_register_ISR(i2csp->irqf, EE_i2c_common_handler);	 

	return EE_I2C_OK;
}

/* This function is used to change settings of the I2C controller */
int EE_hal_i2c_config(EE_i2c_st* i2csp, int baudrate, int setttings)	// baudrate in Hz 									
{
	OCI2CMDev_t *i2cc = i2csp->base;
	
	/* disable core */
	EE_hal_i2c_disable(i2csp);		 
	/* disable interrupts */
	EE_hal_i2c_disable_IRQ(i2csp);
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
	EE_hal_i2c_enable(i2csp);	
	
	// All done!!!
	return EE_I2C_OK;
}

/* This function is used to set ISR operating mode */
int EE_hal_i2c_set_mode(EE_i2c_st* i2csp, int mode)
{
	int ret;
	int old_mode;
	unsigned int intst;
	
	OCI2CMDev_t *i2cc = i2csp->base;
	
	/* Disble IRQ */
	intst = EE_mico32_disableIRQ();
	
	/* Register IRQ handler */
	EE_hal_i2c_handler_setup(i2csp);
	
	/* FSM */
	old_mode = i2csp->mode;
	if(old_mode == mode)
		ret = EE_I2C_OK;
	else
	{	
		i2csp->mode = mode; 	
		/* Buffer initialization */
		if (EE_i2c_need_init_rx_buf(old_mode, mode))
			EE_buffer_init(&i2csp->rxbuf, EE_I2C_MSGSIZE, EE_I2C_BUFSIZE, i2csp->rxbuf.data);
		if (EE_i2c_need_init_tx_buf(old_mode, mode))
			EE_buffer_init(&i2csp->txbuf, EE_I2C_MSGSIZE, EE_I2C_BUFSIZE, i2csp->txbuf.data);
		/* IRQ settings */
		if(EE_i2c_need_enable_int(mode))
			i2cc->Control |= (volatile unsigned int)OCI2CM_CTL_INT_ENABLE;
	}		
	
	/* Enable IRQ */
	if (EE_mico32_are_IRQs_enabled(intst))
        EE_mico32_enableIRQ();
        
	return ret;
}

/* This function is used to enable IRQ */
int EE_hal_i2c_enable_IRQ(EE_i2c_st* i2csp)
{
	OCI2CMDev_t *i2cc = i2csp->base;
	
	i2cc->Control |= (volatile unsigned int)OCI2CM_CTL_INT_ENABLE;
	
	return EE_I2C_OK;	
}															

/* This function is used to disable IRQ */
int EE_hal_i2c_disable_IRQ(EE_i2c_st* i2csp)
{
	OCI2CMDev_t *i2cc = i2csp->base;
	
	i2cc->Control &= (volatile unsigned int)(~(OCI2CM_CTL_INT_ENABLE));
	
	return EE_I2C_OK;
}

/* This function is used to set rx callback */
int EE_hal_i2c_set_rx_callback(EE_i2c_st* i2csp, EE_ISR_callback isr_rx_callback)
{
	i2csp->rxcbk = isr_rx_callback;
	
	return EE_I2C_OK;
}

/* This function is used to set tx callback */
int EE_hal_i2c_set_tx_callback(EE_i2c_st* i2csp, EE_ISR_callback isr_tx_callback)															
{
	i2csp->txcbk = isr_tx_callback;
	
	return EE_I2C_OK;
}

/* This function is used to turn off I2C controller */
int EE_hal_i2c_disable(EE_i2c_st* i2csp)
{
	OCI2CMDev_t *i2cc = i2csp->base;
	
	/* Clear the ‘EN’ bit only when no transfer is in progress, i.e. after a STOP
	   command, or when the command register has the STO bit set. When halted during a
	   transfer, the core can hang the I2C bus.  
	*/	
	EE_hal_i2c_stop(i2csp);
	/* disable core */
	i2cc->Control &= (volatile unsigned int)(~(unsigned int)(OCI2CM_CTL_CORE_ENABLE)); 
	
	// All done!!!
	return EE_I2C_OK;
}

/* This function is used to turn on I2C controller */
int EE_hal_i2c_enable(EE_i2c_st* i2csp)
{
	OCI2CMDev_t *i2cc = i2csp->base;
	
	/* enable core */
	i2cc->Control |= (volatile unsigned int)(OCI2CM_CTL_CORE_ENABLE);  
	
	// All done!!!
	return EE_I2C_OK;
}

/* This function is used to send a start (or a repeated start) condition on the bus */
int EE_hal_i2c_start(EE_i2c_st* i2csp)		//note: all read/write functions issue a start...this function can be removed??? 
{
	OCI2CMDev_t *i2cc = i2csp->base;
	
	/* wait for pending transaction to complete */
    while(i2cc->StatusCommand & OCI2CM_STATUS_TRANSFER);	//EE_i2c_pend_for_TIP_done(i2csp->base);

    /* issue a start */
    i2cc->StatusCommand = OCI2CM_CMD_START;

    /*
     * see if arbitration was lost; return 0 if arbitration
     * wasn't lost i.e. start was successful
     */
    return ( i2cc->StatusCommand & OCI2CM_STATUS_ARB_LOST );
}

/* This function is used to send a stop condition on the bus */
int EE_hal_i2c_stop(EE_i2c_st* i2csp)		//note: stop condition manual or not???
{
	OCI2CMDev_t *i2cc = i2csp->base;

    /* wait for pending transaction to complete */
    while(i2cc->StatusCommand & OCI2CM_STATUS_TRANSFER);	//EE_i2c_pend_for_TIP_done(i2csp->base);

    /* issue a stop */
    i2cc->StatusCommand = OCI2CM_CMD_STOP;

    /* all done */
    return EE_I2C_OK;
}

/* This function is used to send a byte on the bus */
int EE_hal_i2c_write_byte(EE_i2c_st* i2csp, EE_UINT8 device, EE_UINT8 address, EE_UINT8 data)	// ATT! data is a message (packet)
{
	int mode;
	int ret;
	EE_buffer* buffer;
	
	OCI2CMDev_t *i2cc = i2csp->base;

	buffer = &i2csp->txbuf;
	mode = i2csp->mode;
	
	if( EE_i2c_tx_polling(mode) )	// POLLING MODE
	{
	    /* load address, set-up a write to write the address out to the bus */
	    i2cc->Data = ((address<<1) & ~EE_I2C_RW_MASK);
	    /* initiate a start (repeated) and write out the address */
	    i2cc->StatusCommand = (OCI2CM_CMD_START|OCI2CM_CMD_WRITE);
	    /* wait for transfer to complete */
	    while(i2cc->StatusCommand & OCI2CM_STATUS_TRANSFER);	//EE_i2c_pend_for_TIP_done(i2csp->base);
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
		    while(i2cc->StatusCommand & OCI2CM_STATUS_TRANSFER);	//EE_i2c_pend_for_TIP_done(i2csp->base);
		    /* check for ack  and if arb was lost during this transaction */
		    if( i2cc->StatusCommand & OCI2CM_STATUS_RX_ACK )
		        ret = EE_I2C_ERR_DATA_ACK;
		    else if( i2cc->StatusCommand & OCI2CM_STATUS_ARB_LOST )
		        ret = EE_I2C_ERR_ARB_LOST;
		    else
		        ret = EE_I2C_OK;
		}
	}
	else
	{
		// to do...
		ret = EE_I2C_ERR_BAD_VALUE;
	}
	
	// All done!!!
	return ret;
}	
	
/* This function is used to read a byte from the bus */
int EE_hal_i2c_read_byte(EE_i2c_st* i2csp, int address, EE_UINT8 *data)			// ATT! adddata is a pointer to message (packet)
{
	int mode;
	int ret;
	EE_buffer* buffer;
	
	OCI2CMDev_t *i2cc = i2csp->base;

	buffer = &i2csp->rxbuf;
	mode = i2csp->mode;

	if( EE_i2c_rx_polling(mode) )	// POLLING MODE
	{
	    /* load address, set-up a write to write the address out to the bus */
	    i2cc->Data = ((address<<1) | (EE_I2C_RW_MASK) );
	    /* initiate a start (repeated) and write out the address */
	    i2cc->StatusCommand = (OCI2CM_CMD_START|OCI2CM_CMD_WRITE);
	    /* wait for transfer to complete */
	    while(i2cc->StatusCommand & OCI2CM_STATUS_TRANSFER);	//EE_i2c_pend_for_TIP_done(i2csp->base);
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
	    	*data = (EE_UINT8)(i2cc->Data);
	    	/* check for ack  and if arb was lost during this transaction */
	    	if( i2cc->StatusCommand & OCI2CM_STATUS_ARB_LOST )
	        	 ret = EE_I2C_ERR_ARB_LOST;
	    	else
	        	return EE_I2C_OK;
		}
	}
	else
	{
		// to do...
		ret = EE_I2C_ERR_BAD_VALUE;
	}
	
	// All done!!!
	return ret;
}
	


int EE_hal_i2c_write_buffer(EE_i2c_st* i2csp, int address, EE_UINT8 *vet, int len)	// ATT! vet is a vector of messages (packets)
{
	int i, mode;
	int ret;
	EE_buffer* buffer;
	
	OCI2CMDev_t *i2cc = i2csp->base;

	buffer = &i2csp->txbuf;
	mode = i2csp->mode;
	
	if( EE_i2c_tx_polling(mode) )	// POLLING MODE
	{
		/* load address, set-up a write to write the address out to the bus */
    	i2cc->Data = ((address<<1) & ~EE_I2C_RW_MASK);
    	/* initiate a start (repeated) and write out the address */
    	i2cc->StatusCommand = (OCI2CM_CMD_START|OCI2CM_CMD_WRITE);
    	//i2cc->StatusCommand = (OCI2CM_CMD_WRITE);
    	/* wait for transfer to complete */
    	while(i2cc->StatusCommand & OCI2CM_STATUS_TRANSFER);	//EE_i2c_pend_for_TIP_done(i2csp->base);
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
        		while(i2cc->StatusCommand & OCI2CM_STATUS_TRANSFER);	//EE_i2c_pend_for_TIP_done(i2csp->base);
        		/* check for ack */
        		if( i2cc->StatusCommand & OCI2CM_STATUS_RX_ACK )
            		ret = EE_I2C_ERR_DATA_ACK;
    		}
    		/* see if arbitration was lost during this transaction */
    		if( i2cc->StatusCommand & OCI2CM_STATUS_ARB_LOST )
        		ret = EE_I2C_ERR_ARB_LOST;
    		else	
        		ret = EE_I2C_OK;
		}
	}
	else
	{
		// to do...
		ret = EE_I2C_ERR_BAD_VALUE;
	}
	
	// All done!!!
	return ret;
	
    
}

int EE_hal_i2c_read_buffer(EE_i2c_st* i2csp, int address, EE_UINT8 *vet, int len)	// ATT! vet is a vector of messages (packets)
{
	int i, mode;
	int ret;
	EE_buffer* buffer;
	
	OCI2CMDev_t *i2cc = i2csp->base;

	buffer = &i2csp->rxbuf;
	mode = i2csp->mode;

	if( EE_i2c_rx_polling(mode) )	// POLLING MODE
	{
		/* load address, set-up a write to write the address out to the bus */
	    i2cc->Data = ((address<<1) | (EE_I2C_RW_MASK) );
	    /* initiate a start (repeated) and write out the address */
	    i2cc->StatusCommand = (OCI2CM_CMD_START|OCI2CM_CMD_WRITE);
	    /* wait for transfer to complete */
	    while(i2cc->StatusCommand & OCI2CM_STATUS_TRANSFER);	//EE_i2c_pend_for_TIP_done(i2csp->base);
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
	            	i2cc->StatusCommand = (OCI2CM_CMD_READ|OCI2CM_CMD_ACK);	
	        	/* wait while transfer is in progress */
	        	while(i2cc->StatusCommand & OCI2CM_STATUS_TRANSFER);	//EE_i2c_pend_for_TIP_done(i2csp->base);
	        	/* read data */
	        	vet[i] = (EE_UINT8)(i2cc->Data);
			}
	    }
	    /* check for ack  and if arb was lost during this transaction */
	    if( i2cc->StatusCommand & OCI2CM_STATUS_ARB_LOST )
	        ret = EE_I2C_ERR_ARB_LOST;
	    else
	        ret = EE_I2C_OK;	// return the number of bytes received... 
	}
	else
	{
		// to do...
		ret = EE_I2C_ERR_BAD_VALUE;
	}
	
	// All done!!!
	return ret;
}	

int EE_hal_i2c_return_error(EE_i2c_st* i2csp)
{
	return i2csp->err;
}
	

