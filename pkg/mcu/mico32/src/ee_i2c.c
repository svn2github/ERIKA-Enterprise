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
// ...

/******************************************************************************/
/*                       Public Global Functions                              */
/******************************************************************************/

EE_UINT8 EE_i2c_init(EE_UINT32 base, EE_UINT32 speed, EE_UINT32 settings, EE_mico32_ISR_handler isr_callback)
{
	OCI2CMDev_t *i2cc = (OCI2CMDev_t *)base;
	
	/* disable core */
	i2cc->Control &= ~OCI2CM_CTL_CORE_ENABLE;    
	/* Load Prescaler LSB */                       
	i2cc->PrescaleLo = ((MICO32_CPU_CLOCK_MHZ/(5*speed*1000)-1));  
	/* Load Prescaler MSB */                                  
    i2cc->PrescaleHi = 0;   
	/* Clear Tx Data */                                         
    i2cc->Data = 0;     
	/* Clear out all commands */                                              
    i2cc->StatusCommand = 0;   
    /* Isr management */
    if(isr_callback==NULL)
	{
    	/* enable core, disable ints */
		i2cc->Control = OCI2CM_CTL_CORE_ENABLE; 
	}
	else
	{
		EE_mico32_register_ISR(I2C_IRQ, isr_callback);
		i2cc->Control = OCI2CM_CTL_CORE_ENABLE | OCI2CM_CTL_INT_ENABLE;	
	}                                   
	// All done!!!
	return 0;
}

EE_UINT8 EE_i2c_disable(EE_UINT32 base)
{
	OCI2CMDev_t *i2cc = (OCI2CMDev_t *)base;
	
	/* disable core */
	i2cc->Control &= ~OCI2CM_CTL_CORE_ENABLE; 
	
	// All done!!!
	return 0;
}

EE_UINT8 EE_i2c_enable(EE_UINT32 base)
{
	OCI2CMDev_t *i2cc = (OCI2CMDev_t *)base;
	
	/* enable core */
	i2cc->Control |= OCI2CM_CTL_CORE_ENABLE;  
	
	// All done!!!
	return 0;
}

EE_UINT8 EE_i2c_start(EE_UINT32 base)
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

EE_UINT8 EE_i2c_stop(EE_UINT32 base)
{
	OCI2CMDev_t *i2cc = (OCI2CMDev_t *)base;

    /* wait for pending transaction to complete */
    OCI2CM_PEND_FOR_TIP_DONE(base);

    /* issue a stop */
    i2cc->StatusCommand = OCI2CM_CMD_STOP;

    /* all done */
    return;
}

EE_UINT8 EE_i2c_write(EE_UINT32 base, unsigned int address, unsigned int buffersize, unsigned char *data)
{
	unsigned int i;
	OCI2CMDev_t *i2cc = (OCI2CMDev_t *)base;

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
		// All done!!!
        return 0;
}

EE_UINT8 EE_i2c_write_byte(EE_UINT32 base, unsigned int address, unsigned char data)
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
        return 0;
}
	
EE_UINT8 EE_i2c_read(EE_UINT32 base, unsigned int address, unsigned int buffersize, unsigned char *data)
{
	unsigned int i;
    unsigned int uiData;
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
        return i;	// return the number of bytes received... 

}	
	
EE_UINT8 EE_i2c_read_byte(EE_UINT32 base, unsigned int address, unsigned char *data)
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
        return 1;	// 1 if data was received...
}
	
