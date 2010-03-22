/*
	ETH library functions
*/

#ifdef __USE_MICO32BOARD_ETHCTRL_ENC28J60__

#include "board/fpga_camera_mico32/inc/ee_ethctrl_enc28j60.h"

/* ---------------------- Global variables --------------------------------- */
EE_ISR_callback ee_enc28j60_cbk;	// ISR ethctrl callback function

/* ---------------------- Ethernet interrupt handler ------------------------- */

void EE_enc28j60_handler(int level)
{
	return;
}

/* ---------------------- Ethernet Library functions ------------------------- */

int EE_enc28j60_bank_select(EE_UINT8 bank)
{
	int ret;
	EE_UINT8 data; 
	
	/* BIT FIELD CLEAR */
	data = ENC28J60_ECON1_BSEL1 | ENC28J60_ECON1_BSEL0;  
	ret = EE_enc28j60_write_buffer(ENC28J60_BFC | ENC28J60_ECON1, &data, 1);
	//if(ret == ...)
	
	/* BIT FIELD SET */
	data = bank;  
	ret = EE_enc28j60_write_buffer(ENC28J60_BFS | ENC28J60_ECON1, &data, 1);
	//if(ret == ...)
	
	return ret;
}

int EE_enc28j60_set_ISR_mode(int irqf)
{
	int ret=0;
	
	// to do...
	// gpio pin management...
	
	return ret;
}

int EE_enc28j60_set_polling_mode(void)
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
	
	ret = EE_enc28j60_read_buffer(ENC28J60_RCR | add, rx_data, 1);
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
	
	ret = EE_enc28j60_read_buffer(ENC28J60_RCR | add, rx_data, 2);
	//if(ret = ...)
	
	ret = rx_data[1];
	
	return ret;
}

int EE_enc28j60_read_MII_register(int address)
{
	int ret;
	EE_UINT8 add = address & EE_ENC28J60_ADDRESS_MASK;
	EE_UINT8 rx_data[2];
	
	ret = EE_enc28j60_read_buffer(ENC28J60_RCR | add, rx_data, 2);
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
	
	ret = EE_enc28j60_write_buffer(ENC28J60_WCR | add, &data, 1);
	//if(ret = ...)
	
	return ret;
}

int EE_enc28j60_write_MAC_register(int address, EE_UINT8 data)
{
	int ret;
	EE_UINT8 add = address & EE_ENC28J60_ADDRESS_MASK;
	
	ret = EE_enc28j60_write_buffer(ENC28J60_WCR | add, &data, 1);
	//if(ret = ...)
	
	return ret;
}

int EE_enc28j60_write_MII_register(int address, EE_UINT8 data)
{
	int ret;
	EE_UINT8 add = address & EE_ENC28J60_ADDRESS_MASK;
	
	ret = EE_enc28j60_write_buffer(ENC28J60_WCR | add, &data, 1);
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
	int ret;
	
	ret = EE_enc28j60_read_buffer(ENC28J60_RBM, data, len);
	//if(ret = ...)
	
	return ret;
}

int EE_enc28j60_write_buffer_memory(EE_UINT8 *data, int len)
{
	int ret;
	
	ret = EE_enc28j60_write_buffer(ENC28J60_WBM, data, len);
	//if(ret = ...)
	
	return ret;
}

/* EE_enc28j60_bit_field_set: only for ETH control register */
int EE_enc28j60_bit_field_set(int address, EE_UINT8 data)
{
	int ret;
	EE_UINT8 add = address & EE_ENC28J60_ADDRESS_MASK;
	
    ret = EE_enc28j60_write_buffer(ENC28J60_BFS | add, &data, 1);
    //if(ret = ...)
    
	return ret;
}

/* EE_enc28j60_bit_field_clear: only for ETH control register */
int EE_enc28j60_bit_field_clear(int address, EE_UINT8 data)
{
	int ret;
	EE_UINT8 add = address & EE_ENC28J60_ADDRESS_MASK;
	
    ret = EE_enc28j60_write_buffer(ENC28J60_BFC | add, &data, 1);
    //if(ret = ...)
    
	return ret;
}

int EE_enc28j60_software_reset(void)
{
	int ret=0;
	
	// to do...
	// Note: The power save feature may prevent the reset from executing, so
    // we must make sure that the device is not in power save before issuing
    // a reset.
    EE_enc28j60_bit_field_clear(ENC28J60_ECON2, ENC28J60_ECON2_PWRSV);

    // Give some opportunity for the regulator to reach normal regulation and
    // have all clocks running
    //DelayMs(1);

	ret = EE_enc28j60_write_byte(ENC28J60_SR);
	//if(ret = ...)
	
    // Wait for the oscillator start up timer and PHY to become ready
    //DelayMs(1);
	
	return ret;
}

int EE_enc28j60_enable_IRQ(void)
{
	int ret=0;
	
	// to do...
	// gpio pin management...
	
	return ret;
}

int EE_enc28j60_disable_IRQ(void)
{
	int ret=0;
	
	// to do...
	// gpio pin management...
	
	return ret;
}

int EE_enc28j60_IRQ_enabled(void)
{
	int ret=0;
	
	// to do...
	// gpio pin management...
	
	return ret;
}

#endif // #ifdef __USE_MICO32BOARD_ETHCTRL_ENC28J60__
