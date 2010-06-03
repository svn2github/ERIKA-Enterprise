/*
  Name: enc28j60_hal_ee_mico32.c
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: ENC28J60 driver source file.
*/

#include "ENC28J60.h"

/* ---------------------- Global variables --------------------------------- */
EE_enc28j60_st ee_enc28j60_st = {
	.base= (MicoGPIO_t* )MISC_GPIO_BASE_ADDRESS,
	.irqf= MISC_GPIO_IRQ, 
	.rxcbk= EE_NULL_CBK, 
	.txcbk= EE_NULL_CBK };
	
/* ---------------------- Ethernet interrupt handler ------------------------- */

void EE_enc28j60_handler(int level)
{
	EE_gpio_common_handler(level);
	
	EE_enc28j60_gpio_IRQ_pre_stub();
    ENC28J60_INTERRUPT_NAME();
	EE_enc28j60_gpio_IRQ_post_stub();
	
	return;
}

/* ---------------------- Ethernet Library functions ------------------------- */

int EE_enc28j60_bank_select(EE_UINT8 bank)
{
	int ret;
	EE_UINT8 data[2]; 
	
	/* BIT FIELD CLEAR */
	EE_enc28j60_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_set_SSO();
	data[0] = ENC28J60_BFC | ECON1;
	data[1] = ECON1_BSEL1 | ECON1_BSEL0;  
	ret = EE_enc28j60_write_buffer(data, 2);
	EE_enc28j60_clear_SSO();
	//if(ret == ...)
	
	/* BIT FIELD SET */
	EE_enc28j60_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_set_SSO();
	data[0] = ENC28J60_BFS | ECON1;
	data[1] = bank;  
	ret = EE_enc28j60_write_buffer(data, 2);
	EE_enc28j60_clear_SSO();
	//if(ret == ...)
	
	return ret;
}

int EE_hal_enc28j60_set_ISR_mode(int irqf)
{
	unsigned int intst;
	
	/* Disble IRQ */
	intst = EE_mico32_disableIRQ();
	
	/* Register IRQ handler */
	EE_hal_enc28j60_handler_setup();
		
	mico32_enable_irq(ee_enc28j60_st.irqf);
	EE_enc28j60_enable_IRQ();
	
	/* Enable IRQ */
	if (EE_mico32_are_IRQs_enabled(intst))
        EE_mico32_enableIRQ();
        
	return ENC28J60_SUCCESS;
}

int EE_enc28j60_read_ETH_register(EE_UINT8 address)
{
	int ret;
	EE_UINT8 add = address & EE_ENC28J60_ADDRESS_MASK;
	EE_UINT8 rx_data[1];
	EE_UINT8 tx_data[1];
	
	
	EE_enc28j60_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_set_SSO();
	tx_data[0] = ENC28J60_RCR | add;
	ret = EE_enc28j60_write_buffer(tx_data, 1);
	//EE_spi_clear_SSO();
	//if(ret = ...)
	//EE_spi_set_slave(EE_ENC28J60_DEVICE_ID);	
	//EE_spi_set_SSO();
	ret = EE_enc28j60_read_buffer(rx_data, 1);
	EE_enc28j60_clear_SSO();
	//if(ret = ...)
	
	if(ret >= 0)
		ret = rx_data[0];
	
	return ret;
}

int EE_enc28j60_read_MAC_MII_register(EE_UINT8 address)
{
	int ret;
	EE_UINT8 add = address & EE_ENC28J60_ADDRESS_MASK;
	EE_UINT8 rx_data[2];
	EE_UINT8 tx_data[1];
	
	EE_enc28j60_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_set_SSO();
	tx_data[0] = ENC28J60_RCR | add;
	ret = EE_enc28j60_write_buffer(tx_data, 1);
	//EE_spi_clear_SSO();
	//if(ret = ...)
	//EE_spi_set_slave(EE_ENC28J60_DEVICE_ID);	
	//EE_spi_set_SSO();
	ret = EE_enc28j60_read_buffer(rx_data, 2);
	EE_enc28j60_clear_SSO();
	//if(ret = ...)
	
	ret = rx_data[1];
	
	return ret;
}

int EE_enc28j60_read_PHY_register(EE_UINT8 address)
{
	int ret=0;
	
	// to do...
	
	return ret;
}

int EE_enc28j60_write_register(EE_UINT8 address, EE_UINT8 data)
{
	int ret;
	EE_UINT8 add = address & EE_ENC28J60_ADDRESS_MASK;
	EE_UINT8 tx_data[2];
	
	EE_enc28j60_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_set_SSO();
	tx_data[0] = ENC28J60_WCR | add;
	tx_data[1] = data;
	ret = EE_enc28j60_write_buffer(tx_data, 2);
	EE_enc28j60_clear_SSO();
	//if(ret = ...)
	
	return ret;
}

int EE_enc28j60_write_PHY_register(EE_UINT8 address, int data)
{
	int ret=0;
	
	// to do...
	
	return ret;
}

int EE_enc28j60_read_buffer_memory(EE_UINT8 *data, int len)
{
	int ret;
	
	EE_enc28j60_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_set_SSO();
	ret = EE_enc28j60_write_byte(ENC28J60_RBM);
	if(ret>=0)
		ret = EE_enc28j60_read_buffer(data, len);
	EE_enc28j60_clear_SSO();
	return ret;
}

int EE_enc28j60_write_buffer_memory(EE_UINT8 *data, int len)
{
	int ret;
	
	EE_enc28j60_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_set_SSO();
	ret = EE_enc28j60_write_byte(ENC28J60_WBM);
	if(ret>=0)
		ret = EE_enc28j60_write_buffer(data, len);
	EE_enc28j60_clear_SSO();
	return ret;
}

/* EE_enc28j60_bit_field_set: only for ETH control register */
int EE_enc28j60_bit_field_set(EE_UINT8 address, EE_UINT8 mask)
{
	int ret;
	EE_UINT8 add = address & EE_ENC28J60_ADDRESS_MASK;
	EE_UINT8 tx_data[2];
	
	/* BIT FIELD SET */
	EE_enc28j60_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_set_SSO();
	tx_data[0] = ENC28J60_BFS | add;	
	tx_data[1] = mask;  
	ret = EE_enc28j60_write_buffer(tx_data, 2);
	EE_enc28j60_clear_SSO();
	//if(ret == ...)
	
	return ret;
}

/* EE_enc28j60_bit_field_clear: only for ETH control register */
int EE_enc28j60_bit_field_clear(EE_UINT8 address, EE_UINT8 mask)
{
	int ret;
	EE_UINT8 add = address & EE_ENC28J60_ADDRESS_MASK;
	EE_UINT8 tx_data[2];
	
	/* BIT FIELD CLEAR */
	EE_enc28j60_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_set_SSO();
	tx_data[0] = ENC28J60_BFC | add;	
	tx_data[1] = mask;					 
	ret = EE_enc28j60_write_buffer(tx_data, 2);
	EE_enc28j60_clear_SSO();
	//if(ret == ...)
    
	return ret;
}

void EE_enc28j60_delay_us(unsigned int delay_count)
{
	MicoSleepMicroSecs((unsigned int)delay_count);
}

void EE_enc28j60_delay_ms(unsigned int delay_count)
{
	MicoSleepMilliSecs((unsigned int)delay_count);
}

int EE_enc28j60_software_reset(void)
{
	int ret;
	
	// Note: The power save feature may prevent the reset from executing, so
    // we must make sure that the device is not in power save before issuing
    // a reset.
    EE_enc28j60_bit_field_clear(ECON2, ECON2_PWRSV);

    // Give some opportunity for the regulator to reach normal regulation and
    // have all clocks running
    EE_enc28j60_delay_us(1000);

	ret = EE_enc28j60_write_byte(ENC28J60_SR);
	
    // Wait for the oscillator start up timer and PHY to become ready
    EE_enc28j60_delay_us(1000);
	
	return ret;
}

void EE_enc28j60_hardware_reset(void)
{
	EE_enc28j60_disable();
	EE_enc28j60_delay_us(1000);
	EE_enc28j60_enable();
}



