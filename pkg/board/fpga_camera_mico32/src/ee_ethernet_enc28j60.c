/*
  Name: ee_ethernet_enc28j60.c
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.28
  Description: Ethernet driver source file (MICO32 CAMERA board dependent). 
*/

#ifdef __USE_ETHERNET_ENC28J60__

#include "board/fpga_camera_mico32/inc/ee_ethernet_enc28j60.h"

/* ---------------------- Global variables --------------------------------- */
EE_ISR_callback ee_enc28j60_cbk;	// ISR ETHERNET callback function
EE_UINT8 ee_enc28j60_isr_rxvet[EE_ENC28J60_BUFSIZE];
EE_UINT8 ee_enc28j60_isr_txvet[EE_ENC28J60_BUFSIZE];  

EE_enc28j60_st ee_enc28j60_st = {
	.mode= 0/*EE_ENC28J60_RXTX_ISR*/, .base= (MicoGPIO_t* )MISC_GPIO_BASE_ADDRESS,
	.irqf= MISC_GPIO_IRQ, .rxcbk= EE_NULL_CBK, .txcbk= EE_NULL_CBK,
	.rxbuf.data= ee_enc28j60_isr_rxvet,.txbuf.data= ee_enc28j60_isr_txvet};
	
int ee_enc28j60_dummy_flag = 0;

/* ---------------------- Ethernet interrupt handler ------------------------- */

void EE_enc28j60_handler(int level)
{
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
	data[0] = ENC28J60_BFC | ENC28J60_ECON1;
	data[1] = ENC28J60_ECON1_BSEL1 | ENC28J60_ECON1_BSEL0;  
	ret = EE_enc28j60_write_buffer(data, 2);
	EE_enc28j60_clear_SSO();
	//if(ret == ...)
	
	/* BIT FIELD SET */
	EE_enc28j60_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_set_SSO();
	data[0] = ENC28J60_BFS | ENC28J60_ECON1;
	data[1] = bank;  
	ret = EE_enc28j60_write_buffer(data, 2);
	EE_enc28j60_clear_SSO();
	//if(ret == ...)
	
	return ret;
}

int EE_hal_enc28j60_set_ISR_mode(int irqf)
{
	int ret=0;
	
	// to do...
	// gpio pin management...
	
	return ret;
}

int EE_hal_enc28j60_set_polling_mode(void)
{
	int ret=0;
	
	// to do...
	
	return ret;
}

int EE_enc28j60_read_ETH_register(int address)
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

int EE_enc28j60_read_MAC_register(int address)
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

int EE_enc28j60_read_MII_register(int address)
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

int EE_enc28j60_read_PHY_register(int address)
{
	int ret=0;
	
	// to do...
	
	return ret;
}

int EE_enc28j60_write_ETH_register(int address, EE_UINT8 data)
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

int EE_enc28j60_write_MAC_register(int address, EE_UINT8 data)
{
	int ret;
	EE_UINT8 add = address & EE_ENC28J60_ADDRESS_MASK;
	EE_UINT8 tx_data[2];
	
	EE_enc28j60_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_set_SSO();
	tx_data[0] = ENC28J60_WCR | add;
	tx_data[1] = data;
	ret = EE_enc28j60_write_buffer(tx_data,2);
	EE_enc28j60_clear_SSO();
	//if(ret = ...)
	
	return ret;
}

int EE_enc28j60_write_MII_register(int address, EE_UINT8 data)
{
	int ret;
	EE_UINT8 add = address & EE_ENC28J60_ADDRESS_MASK;
	EE_UINT8 tx_data[2];
	
	EE_enc28j60_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_set_SSO();
	tx_data[0] = ENC28J60_WCR | add;
	tx_data[1] = data;
	ret = EE_enc28j60_write_buffer(tx_data,2);
	EE_enc28j60_clear_SSO();
	//if(ret = ...)
	
	return ret;
}

int EE_enc28j60_write_PHY_register(int address, EE_UINT8 data)
{
	int ret=0;
	
	// to do...
	
	return ret;
}

int EE_enc28j60_read_buffer_memory(EE_UINT8 *data, int len)
{
	int ret=0;
	
	//ret = EE_enc28j60_read_buffer(ENC28J60_RBM, data, len);
	//if(ret = ...)
	
	return ret;
}

int EE_enc28j60_write_buffer_memory(EE_UINT8 *data, int len)
{
	int ret=0;
	
	//ret = EE_enc28j60_write_buffer(ENC28J60_WBM, data, len);
	//if(ret = ...)
	
	return ret;
}

/* EE_enc28j60_bit_field_set: only for ETH control register */
int EE_enc28j60_bit_field_set(int address, EE_UINT8 mask)
{
	int ret;
	EE_UINT8 add = address & EE_ENC28J60_ADDRESS_MASK;
	EE_UINT8 tx_data[2];
	
	/* BIT FIELD SET */
	EE_enc28j60_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_set_SSO();
	tx_data[0] = ENC28J60_BFS | add;	//ENC28J60_ECON1;
	tx_data[1] = mask;  
	ret = EE_enc28j60_write_buffer(tx_data, 2);
	EE_enc28j60_clear_SSO();
	//if(ret == ...)
	
	return ret;
}

/* EE_enc28j60_bit_field_clear: only for ETH control register */
int EE_enc28j60_bit_field_clear(int address, EE_UINT8 mask)
{
	int ret;
	EE_UINT8 add = address & EE_ENC28J60_ADDRESS_MASK;
	EE_UINT8 tx_data[2];
	
	/* BIT FIELD CLEAR */
	EE_enc28j60_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_set_SSO();
	tx_data[0] = ENC28J60_BFC | add;	//ENC28J60_ECON1;
	tx_data[1] = mask;					//ENC28J60_ECON1_BSEL1 | ENC28J60_ECON1_BSEL0;  
	ret = EE_enc28j60_write_buffer(tx_data, 2);
	EE_enc28j60_clear_SSO();
	//if(ret == ...)
    
	return ret;
}

void EE_enc28j60_delay_us(EE_UINT16 delay_count)
{
	/* Provide a delay with an accuracy of approx. ... @ 34MHz */
    asm volatile(	"1:\n\t"
		"addi r1, r1, -1\n\t"
		"nop\n\t"
		"bne r1, r0, 1b\n\t");		
}

int EE_enc28j60_software_reset(void)
{
	int ret;
	
	// Note: The power save feature may prevent the reset from executing, so
    // we must make sure that the device is not in power save before issuing
    // a reset.
    EE_enc28j60_bit_field_clear(ENC28J60_ECON2, ENC28J60_ECON2_PWRSV);

    // Give some opportunity for the regulator to reach normal regulation and
    // have all clocks running
    EE_enc28j60_delay_us(2000);

	ret = EE_enc28j60_write_byte(ENC28J60_SR);
	
    // Wait for the oscillator start up timer and PHY to become ready
    EE_enc28j60_delay_us(2000);
	
	return ret;
}

int EE_enc28j60_hardware_reset(void)
{
	int ret = ENC28J60_SUCCESS;
	
	EE_enc28j60_hold_in_reset();
	EE_enc28j60_delay_us(2000);
	EE_enc28j60_release_reset();
	
	return ret;
}

/*
	int EE_enc28j60_enable(void);
	This function enables device by reset pin. 
*/
int EE_enc28j60_enable(void)
{
	EE_enc28j60_release_reset();
	//EE_enc28j60_delay_us(1000);
	
    return ENC28J60_SUCCESS;
}

/*
	int EE_enc28j60_disable(void);
	This function disables device by reset pin. 
*/
int EE_enc28j60_disable(void)
{
	EE_enc28j60_hold_in_reset();
	
    return ENC28J60_SUCCESS;
}

int EE_enc28j60_enable_IRQ(void)
{
	int ret = ENC28J60_SUCCESS;
	
	// to do...
	// gpio pin management...
	
	return ret;
}

int EE_enc28j60_disable_IRQ(void)
{
	int ret = ENC28J60_SUCCESS;
	
	// to do...
	// gpio pin management...
	
	return ret;
}

int EE_enc28j60_IRQ_enabled(void)
{
	int ret = ENC28J60_SUCCESS;
	
	// to do...
	// gpio pin management...
	
	return ret;
}

#endif // #ifdef __USE_ETHERNET_ENC28J60__
