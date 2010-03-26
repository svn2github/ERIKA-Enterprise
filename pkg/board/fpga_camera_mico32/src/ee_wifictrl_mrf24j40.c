/*
	ETH library functions
*/

#ifdef __USE_MICO32BOARD_WIFICTRL_MRF24J40__

#include "board/fpga_camera_mico32/inc/ee_wifictrl_mrf24j40.h"

/* ---------------------- Global variables --------------------------------- */
EE_ISR_callback ee_mrf24j40_cbk;	// ISR ethctrl callback function

/* ---------------------- Ethernet interrupt handler ------------------------- */

void EE_mrf24j40_handler(int level)
{
	return;
}

/* ---------------------- Ethernet Library functions ------------------------- */

int EE_hal_mrf24j40_set_ISR_mode(int irqf)
{
	int ret=0;
	
	// to do...
	// gpio pin management...
	
	return ret;
}

int EE_hal_mrf24j40_set_polling_mode(void)
{
	int ret=0;
	
	// to do...
	// gpio pin management...
	
	return ret;
}

int EE_mrf24j40_read_short_address_register(int address)
{
	int ret;
	EE_UINT8 add = ((address & EE_MRF24J40_SHORT_ADDRESS_MASK) << 1);// | MRF24J40_SRCR;
	EE_UINT8 rx_data[1];
	EE_UINT8 tx_data[1];
	
	//mrf24j40_hal_irq_disable();
	tx_data[0] = add;
	EE_mrf24j40_set_slave(EE_MRF24J40_DEVICE_ID);	
	EE_mrf24j40_set_SSO();
	ret = EE_mrf24j40_write_buffer(tx_data, 1);
	//EE_spi_clear_SSO();
	//if(ret = ...)
	//EE_spi_set_slave(EE_MRF24J40_DEVICE_ID);	
	//EE_spi_set_SSO();
	ret = EE_mrf24j40_read_buffer(rx_data, 1);
	EE_mrf24j40_clear_SSO();
	//if(ret = ...)
	if (ret >= 0)
		ret = rx_data[0];
	
	return ret;
}

int EE_mrf24j40_read_long_address_register(int address)
{
	int ret;
	EE_UINT32 add = ((address & EE_MRF24J40_LONG_ADDRESS_MASK) << 1) | EE_MRF24J40_LRCR;	// 1 a9 a8 a7 a6 a5 a4 a3 a2 a1 a0 0
	EE_UINT8 rx_data[1];
	EE_UINT8 tx_data[2];
	
	//mrf24j40_hal_irq_disable();
	EE_mrf24j40_set_slave(EE_MRF24J40_DEVICE_ID);	
	EE_mrf24j40_set_SSO();
	tx_data[0] = (add >> 4) & 0x00FF;
	tx_data[1] = (add << 4) & 0x00FF;
	ret = EE_mrf24j40_write_buffer(tx_data, 2);
	//EE_spi_clear_SSO();
	//if(ret = ...)
	//EE_spi_set_slave(EE_MRF24J40_DEVICE_ID);	
	//EE_spi_set_SSO();
	ret = EE_mrf24j40_read_buffer(rx_data, 1);
	EE_mrf24j40_clear_SSO();
	//if(ret = ...)
	if(ret >= 0)
		ret = rx_data[0];
	
	return ret;
}

int EE_mrf24j40_write_short_address_register(int address, EE_UINT8 data)
{
	int ret;
	EE_UINT8 add = ((address & EE_MRF24J40_SHORT_ADDRESS_MASK) << 1) | EE_MRF24J40_SWCR;
	EE_UINT8 tx_data[2];
	
	//mrf24j40_hal_irq_disable();
	tx_data[0] = add;
	tx_data[1] = data;
	EE_mrf24j40_set_slave(EE_MRF24J40_DEVICE_ID);	
	EE_mrf24j40_set_SSO();
	ret = EE_mrf24j40_write_buffer(tx_data, 2);
	EE_mrf24j40_clear_SSO();
	//if(ret = ...)
	
	return ret;
}

int EE_mrf24j40_write_long_address_register(int address, EE_UINT8 data)
{
	int ret;
	EE_UINT32 add = ((address & EE_MRF24J40_LONG_ADDRESS_MASK) << 1) | EE_MRF24J40_LWCR;	// 1 a9 a8 a7 a6 a5 a4 a3 a2 a1 a0 1
	EE_UINT8 tx_data[3];
	
	//mrf24j40_hal_irq_disable();
	EE_mrf24j40_set_slave(EE_MRF24J40_DEVICE_ID);	
	EE_mrf24j40_set_SSO();
	tx_data[0] = (add >> 4) & 0x00FF;
	tx_data[1] = (add << 4) & 0x00FF;
	tx_data[2] = data;
	ret = EE_mrf24j40_write_buffer(tx_data, 3);
	EE_mrf24j40_clear_SSO();
	//if(ret = ...)
	
	return ret;
}

int EE_mrf24j40_read_buffer_memory(EE_UINT8 *data, int len)
{
	int ret=0;
	
	// to do...
	
	return ret;
}

int EE_mrf24j40_write_buffer_memory(EE_UINT8 *data, int len)
{
	int ret=0;
	
	// to do...
	
	return ret;
}

int EE_mrf24j40_software_reset(void)
{
	int ret=0;
	
	// to do...
	// Note: The power save feature may prevent the reset from executing, so
    // we must make sure that the device is not in power save before issuing
    // a reset.
    // EE_enc28j60_bit_field_clear(ENC28J60_ECON2, ENC28J60_ECON2_PWRSV);
    // Give some opportunity for the regulator to reach normal regulation and
    // have all clocks running
    //DelayMs(1);
	// ret = EE_enc28j60_write_byte(ENC28J60_SR);
	//if(ret = ...)
    // Wait for the oscillator start up timer and PHY to become ready
    //DelayMs(1);
	
	return ret;
}

int EE_mrf24j40_enable_IRQ(void)
{
	int ret=0;
	
	// to do...
	// gpio pin management...
	
	return ret;
}

int EE_mrf24j40_disable_IRQ(void)
{
	int ret=0;
	
	// to do...
	// gpio pin management...
	
	return ret;
}

int EE_mrf24j40_IRQ_enabled(void)
{
	int ret=0;
	
	// to do...
	// gpio pin management...
	
	return ret;
}

#endif // #ifdef __USE_MICO32BOARD_WIFICTRL_MRF24J40__
