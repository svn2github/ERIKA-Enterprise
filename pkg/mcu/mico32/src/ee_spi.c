/*
  Name: ee_spi.c
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: SPI library source file.
*/

#include "mcu/mico32/inc/ee_spi.h"

/******************************************************************************/
/*                              Global Variables                              */
/******************************************************************************/
/* Vectors and SPI structures definitions */

#ifdef __USE_SPI_IRQ__

#ifdef EE_SPI1_NAME_UC
DEFINE_VET_SPI(EE_SPI1_NAME_UC, EE_SPI1_NAME_LC)
DEFINE_STRUCT_SPI(EE_SPI1_NAME_UC, EE_SPI1_NAME_LC)
#endif

#ifdef EE_SPI2_NAME_UC
DEFINE_VET_SPI(EE_SPI2_NAME_UC, EE_SPI2_NAME_LC)
DEFINE_STRUCT_SPI(EE_SPI2_NAME_UC, EE_SPI2_NAME_LC)
#endif

#endif //#ifdef __USE_SPI_IRQ__

/******************************************************************************/
/*                       Private Local Functions                              */
/******************************************************************************/
// ...

/******************************************************************************/
/*                              ISRs                                          */
/******************************************************************************/
#ifdef __USE_SPI_IRQ__

/* EE SPI Interrupt handler */
void EE_spi_common_handler(int level)
{
	unsigned int uiValue;
	
	EE_spi_st *spisp = EE_get_spi_st_from_level(level);
	MicoSPI_t *spic = spisp->base; 
	
	uiValue = spic->status;
	
	/* received new data */
	if(uiValue & EE_SPI_STATUS_RX_RDY_MASK)
	{
        if(spic->control & EE_SPI_CTL_RX_INTR_EN_MASK)
            ;
    }
    
	/* transmitter's ready to accept new data */
    if(uiValue & EE_SPI_STATUS_TX_RDY_MASK)
	{
        if(spic->control & EE_SPI_CTL_TX_INTR_EN_MASK)
            ;
    }
    
	return;	
}

#endif //#ifdef __USE_SPI_IRQ__

/******************************************************************************/
/*                       Public Global Functions                              */
/******************************************************************************/	
int EE_hal_spi_read_byte_polling(MicoSPI_t *spic)
{
	EE_UINT8 dummy;

	/* wait the end of previous transmission */
	while(!EE_spi_tmt_ready(spic->status))		
		;
	/* clean overrun and reception ready flags */
	dummy = spic->rx;
	
	/* send a dummy byte on spi bus */
	spic->tx = dummy;		
	/* wait data to be received */
	while(!EE_spi_rx_ready(spic->status))
		;
	return spic->rx;
}

int EE_hal_spi_read_buffer_polling(MicoSPI_t *spic, void *data, int len)
{
	int i;
	EE_UINT8 *buf = data;  
	EE_UINT8 dummy;

	/* wait the end of previous transmission */
	while(!EE_spi_tmt_ready(spic->status))		
		;
	/* clean overrun and reception ready flags */
	dummy = spic->rx;
	
	for(i=0; i<len; i++)
	{
		/* send a dummy byte on spi bus */
		spic->tx = dummy;
		/* wait data to be received */
		while(!EE_spi_rx_ready(spic->status))
			;
		buf[i] = spic->rx;
	}		
	return len;
}

int EE_hal_spi_write_buffer_polling(MicoSPI_t *spic, const void *data, int len)
{
	int i;
	const EE_UINT8 *buf = data;   
	EE_UINT8 preload;
	
	for(i=0; i<len; i++)
	{
		/* pre-load for speed optimization */
		preload = buf[i];
		while(!EE_spi_tx_ready(spic->status))		
			;
		spic->tx = preload;
	}
	return len;	

}	

int EE_hal_spi_write_byte_polling(MicoSPI_t *spic, EE_UINT8 data)
{
	while(!EE_spi_tx_ready(spic->status))		
		;
	spic->tx = data;
		
	return 1;
}														
#ifndef __USE_SPI_IRQ__

int EE_hal_spi_config(MicoSPI_t* spic, int settings)
{
	EE_hal_spi_disable(spic);
	/* if master, deselect all slaves */	
	//    if(EE_spi_is_master(settings))								
    spic->sSelect = 0;
	spic->control = settings & EE_SPI_CTL_ALL_INTR_DIS_MASK;	
	
	return EE_SPI_OK;
}

int EE_hal_spi_set_ISR_mode(MicoSPI_t* spic, int irqf, int mode)
{
	int ret = EE_SPI_OK;
	
	mico32_disable_irq(irqf);
	// with mode you can choose blocking or non-blocking mode...
	
	return ret;
}

#else

int EE_hal_spi_config(EE_spi_st* spisp, int settings)
{
	MicoSPI_t *spic = spisp->base; 
	
	EE_hal_spi_disable(spisp);
	///* Register IRQ handler */
	//EE_hal_spi_handler_setup(spisp);
	/* if master, deselect all slaves */	
    //if(EE_spi_is_master(settings))								
    spic->sSelect = 0;
	spic->control = settings;	
	
	return EE_SPI_OK;
}

int EE_hal_spi_set_ISR_mode(EE_spi_st* spisp, int mode)
{
	int ret = EE_SPI_OK;
	int old_mode;
	unsigned int intst;
	
	/* Disble IRQ */
	intst = EE_mico32_disableIRQ();
	/* Register IRQ handler */
	EE_hal_spi_handler_setup(spisp);
	/* FSM */
	old_mode = spisp->mode;
	if(old_mode == mode)
		ret = EE_SPI_OK;
	else
	{	
		spisp->mode = mode; 	
		/* Buffer initialization */
		if (EE_spi_need_init_rx_buf(old_mode, mode))
			EE_buffer_init(&spisp->rxbuf, EE_SPI_MSGSIZE, EE_SPI_BUFSIZE, spisp->rxbuf.data);
		if (EE_spi_need_init_tx_buf(old_mode, mode))
			EE_buffer_init(&spisp->txbuf, EE_SPI_MSGSIZE, EE_SPI_BUFSIZE, spisp->txbuf.data);
		/* IRQ settings */
		if(EE_spi_need_enable_int(mode))
		{
			mico32_enable_irq(spisp->irqf);
			EE_hal_spi_enable_IRQ(spisp);
		}
		else
		{
			EE_hal_spi_disable_IRQ(spisp);
			mico32_disable_irq(spisp->irqf);
		}
	}		
	/* Enable IRQ */
	if (EE_mico32_are_IRQs_enabled(intst))
        EE_mico32_enableIRQ();

	return ret;
}

/* This function is used to set rx callback */
int EE_hal_spi_set_rx_ISR_callback(EE_spi_st* spisp, EE_ISR_callback isr_rx_callback)
{
	spisp->rxcbk = isr_rx_callback;
	
	return EE_SPI_OK;
}

/* This function is used to set tx callback */
int EE_hal_spi_set_tx_ISR_callback(EE_spi_st* spisp, EE_ISR_callback isr_tx_callback)															
{
	spisp->txcbk = isr_tx_callback;
	
	return EE_SPI_OK;
}

/* This function is used to send a byte on the bus */
int EE_hal_spi_write_byte_irq(EE_spi_st* spisp, EE_UINT8 data)	// ATT! data is a message (packet)
{
	int ret = EE_SPI_OK;
	//MicoSPI_t *spic = spisp->base; 
		
	// EE_hal_spi_set_slave(spic, device);	
	// EE_spi_set_SSO(spic->control);

	// to do...
	
	// EE_spi_clear_SSO(spic->control);
	
	return ret;
}	
	
/* This function is used to read a byte from the bus */
int EE_hal_spi_read_byte_irq(EE_spi_st* spisp)					// ATT! adddata is a pointer to message (packet)
{
	int ret = EE_SPI_OK;
	//MicoSPI_t *spic = spisp->base; 
	
	// EE_hal_spi_set_slave(spic, device);	
	// EE_spi_set_SSO(spic->control);

	// to do...
	
	// EE_spi_clear_SSO(spic->control);
	
	return ret;
}
	
int EE_hal_spi_write_buffer_irq(EE_spi_st* spisp, EE_UINT8* data, int len)	// ATT! data is a vector of messages (packets)
{
	int ret = EE_SPI_OK;
	//MicoSPI_t *spic = spisp->base; 
	
	// EE_hal_spi_set_slave(spic, device);	
	// EE_spi_set_SSO(spic->control);

	// to do...
	
	// EE_spi_clear_SSO(spic->control);
	
	return ret;
}

int EE_hal_spi_read_buffer_irq(EE_spi_st* spisp, EE_UINT8* data, int len)	// ATT! data is a vector of messages (packets)
{
	int ret = EE_SPI_OK;
	//MicoSPI_t *spic = spisp->base; 
	
	// EE_hal_spi_set_slave(spic, device);	
	// EE_spi_set_SSO(spic->control);
	
	// to do...
	
	// EE_spi_clear_SSO(spic->control);
	
	return ret;
}	

int EE_hal_spi_return_error(EE_spi_st* spisp)
{
	return spisp->err;
}
	
#endif //#ifdef __USE_SPI_IRQ__







