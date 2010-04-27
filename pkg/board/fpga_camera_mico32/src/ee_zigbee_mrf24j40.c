/*
  Name: ee_zigbee_mrf24j40.c
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.27
  Description: Zigbee library for MICO32 CAMERA board
*/

#ifdef __USE_MICO32BOARD_ZIGBEE_MRF24J40__

#include "board/fpga_camera_mico32/inc/ee_zigbee_mrf24j40.h"
#include "mrf24j40.h"

/* ---------------------- Global variables --------------------------------- */
EE_ISR_callback ee_mrf24j40_cbk;	// ISR ethctrl callback function
EE_UINT8 ee_mrf24j40_isr_rxvet[EE_MRF24J40_BUFSIZE];
EE_UINT8 ee_mrf24j40_isr_txvet[EE_MRF24J40_BUFSIZE];  

EE_mrf24j40_st ee_mrf24j40_st = {
	.mode= EE_MRF24J40_POLLING, .base= (MicoGPIO_t* )EE_MRF24J40_BASE_ADDRESS,
	.irqf= EE_MRF24J40_IRQ, .rxcbk= EE_NULL_CBK, .txcbk= EE_NULL_CBK,
	.rxbuf.data= ee_mrf24j40_isr_rxvet,.txbuf.data= ee_mrf24j40_isr_txvet};
	
int ee_mrf24j40_dummy_flag = 0;

/* ---------------------- Ethernet interrupt handler ------------------------- */

void EE_mrf24j40_handler(int level)
{
	//EE_gpio_common_handler(level);
	
    MRF24J40_INTERRUPT_NAME();
	
	while(1){
		if( (EE_misc_gpio_read_data() & EE_INT2_MASK) == 0 )
			break;
	}
	
	return;
}

/* ---------------------- Ethernet Library functions ------------------------- */

/* This function records ISR handler */
int EE_hal_mrf24j40_handler_setup(void)
{
    /* Register IRQ handler */
    EE_mico32_register_ISR(ee_mrf24j40_st.irqf, EE_mrf24j40_handler);	 

	return MRF24J40_SUCCESS;
}

int EE_hal_mrf24j40_set_ISR_mode(int mode)
{
	int old_mode;
	unsigned int intst;
	
	old_mode = ee_mrf24j40_st.mode;
	if(old_mode == mode)
		return MRF24J40_SUCCESS;
	
	/* Disble IRQ */
	intst = EE_mico32_disableIRQ();
	
	/* Register IRQ handler */
	EE_hal_mrf24j40_handler_setup();
	ee_mrf24j40_st.mode = mode; 	
	
	/* Buffer initialization */
	// if (EE_mrf24j40_need_init_rx_buf(old_mode, mode))
		// EE_buffer_init(&ee_mrf24j40_st.rxbuf, EE_MRF24J40_MSGSIZE, EE_MRF24J40_BUFSIZE, ee_mrf24j40_st.rxbuf.data);
	// if (EE_mrf24j40_need_init_tx_buf(old_mode, mode))
		// EE_buffer_init(&ee_mrf24j40_st.txbuf, EE_MRF24J40_MSGSIZE, EE_MRF24J40_BUFSIZE, ee_mrf24j40_st.txbuf.data);
		
	/* IRQ settings */
    if(EE_mrf24j40_need_enable_int(mode))
	{
		mico32_enable_irq(ee_mrf24j40_st.irqf);
		EE_mrf24j40_enable_IRQ();
	}
	else
	{
		mico32_disable_irq(ee_mrf24j40_st.irqf);
		EE_mrf24j40_disable_IRQ();
	}
	
	/* Enable IRQ */
	if (EE_mico32_are_IRQs_enabled(intst))
        EE_mico32_enableIRQ();
        
	return MRF24J40_SUCCESS;
}

/*
	__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_set_rx_ISR_callback(EE_ISR_callback rxcbk)
	This function sets ISR rx callback.
*/
int EE_mrf24j40_set_rx_ISR_callback(EE_ISR_callback rxcbk)
{
	ee_mrf24j40_st.rxcbk = rxcbk;
	mrf24j40_set_rx_callback(rxcbk);
	
	return MRF24J40_SUCCESS;
}

/*
	__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_set_tx_ISR_callback(EE_ISR_callback txcbk)
	This function sets ISR tx callback.
*/
void EE_mrf24j40_txfcbk(uint8_t tx_status)
{
	ee_mrf24j40_st.status = tx_status;
	ee_mrf24j40_st.txcbk();
}

int EE_mrf24j40_set_tx_ISR_callback(EE_ISR_callback txcbk)
{
	ee_mrf24j40_st.txcbk = txcbk;
	mrf24j40_set_tx_finished_callback(EE_mrf24j40_txfcbk);
	
	return MRF24J40_SUCCESS;
}



int EE_mrf24j40_read_short_address_register(int address)
{
	// int ret;
	// EE_UINT8 add = ((address & EE_MRF24J40_SHORT_ADDRESS_MASK) << 1);// | MRF24J40_SRCR;
	// EE_UINT8 rx_data[1];
	// EE_UINT8 tx_data[1];
	
	// tx_data[0] = add;
	// EE_mrf24j40_set_slave(EE_MRF24J40_DEVICE_ID);	
	// EE_mrf24j40_set_SSO();
	// ret = EE_mrf24j40_write_buffer(tx_data, 1);
	// ret = EE_mrf24j40_read_buffer(rx_data, 1);
	// EE_mrf24j40_clear_SSO();
	// if (ret >= 0)
		// ret = rx_data[0];
	
	// return ret;
	
	return mrf24j40_get_short_add_mem(address);
}

int EE_mrf24j40_read_long_address_register(int address)
{
	// int ret;
	// EE_UINT32 add = ((address & EE_MRF24J40_LONG_ADDRESS_MASK) << 1) | EE_MRF24J40_LRCR;	// 1 a9 a8 a7 a6 a5 a4 a3 a2 a1 a0 0
	// EE_UINT8 rx_data[1];
	// EE_UINT8 tx_data[2];
	
	// EE_mrf24j40_set_slave(EE_MRF24J40_DEVICE_ID);	
	// EE_mrf24j40_set_SSO();
	// tx_data[0] = (add >> 4) & 0x00FF;
	// tx_data[1] = (add << 4) & 0x00FF;
	// ret = EE_mrf24j40_write_buffer(tx_data, 2);
	// ret = EE_mrf24j40_read_buffer(rx_data, 1);
	// EE_mrf24j40_clear_SSO();
	// if(ret >= 0)
		// ret = rx_data[0];
	
	// return ret;
	return mrf24j40_get_long_add_mem(address);
}

int EE_mrf24j40_write_short_address_register(int address, EE_UINT8 data)
{
	// int ret;
	// EE_UINT8 add = ((address & EE_MRF24J40_SHORT_ADDRESS_MASK) << 1) | EE_MRF24J40_SWCR;
	// EE_UINT8 tx_data[2];
	
	// tx_data[0] = add;
	// tx_data[1] = data;
	// EE_mrf24j40_set_slave(EE_MRF24J40_DEVICE_ID);	
	// EE_mrf24j40_set_SSO();
	// ret = EE_mrf24j40_write_buffer(tx_data, 2);
	// EE_mrf24j40_clear_SSO();
	
	// return ret;
	
	mrf24j40_set_short_add_mem(address, data);
	return MRF24J40_SUCCESS;
}

int EE_mrf24j40_write_long_address_register(int address, EE_UINT8 data)
{
	// int ret;
	// EE_UINT32 add = ((address & EE_MRF24J40_LONG_ADDRESS_MASK) << 1) | EE_MRF24J40_LWCR;	// 1 a9 a8 a7 a6 a5 a4 a3 a2 a1 a0 1
	// EE_UINT8 tx_data[3];
	
	// EE_mrf24j40_set_slave(EE_MRF24J40_DEVICE_ID);	
	// EE_mrf24j40_set_SSO();
	// tx_data[0] = (add >> 4) & 0x00FF;
	// tx_data[1] = (add << 4) & 0x00FF;
	// tx_data[2] = data;
	// ret = EE_mrf24j40_write_buffer(tx_data, 3);
	// EE_mrf24j40_clear_SSO();
	
	// return ret;
	mrf24j40_set_long_add_mem(address, data);
	return MRF24J40_SUCCESS;
}

int EE_mrf24j40_read_buffer_memory(EE_UINT8 *data, int len)
{
	int ret = MRF24J40_SUCCESS;
	
	// to do...
	
	return ret;
}

int EE_mrf24j40_write_buffer_memory(EE_UINT8 *data, int len)
{
	int ret = MRF24J40_SUCCESS;
	
	// to do...
	
	return ret;
}

void EE_mrf24j40_delay_us(EE_UINT16 delay_count)
{
	/*
 * Implements a tight-loop to achieve a "sleep" of the
 * desired time specified in microseconds.
 *
 * Note: the time spent in the tight loop is only an
 * approximation and is not very precise.
 *
 * If the instruction cache is disabled, this function
 * is highly dependent on memory lattency and will be
 * grossly off than expected.
 *
 */
	MicoSleepMicroSecs((unsigned int)delay_count);
	// EE_UINT32 t1val, t2val;
	
	// EE_timer1_get_value(&t1val);
    // do {
		// EE_timer1_get_value(&t2val);
	// } while ((t2val-t1val) < delay_count);
	
}

int EE_mrf24j40_software_reset(void)
{
	EE_mrf24j40_write_short_address_register(EE_MRF24J40_SOFTRST, EE_MRF24J40_SOFTRST_MASK);
	
	return MRF24J40_SUCCESS;
}

/*
	int EE_mrf24j40_hardware_reset(void);
	This function send a hardware reset command.
*/
int EE_mrf24j40_hardware_reset(void)
{
    EE_mrf24j40_disable();
	EE_mrf24j40_delay_us(100);
	EE_mrf24j40_enable();
	EE_mrf24j40_delay_us(100);
	
    return MRF24J40_SUCCESS;
}

int EE_mrf24j40_enable_IRQ(void)
{
	EE_mrf24j40_int_enable();
	
	return MRF24J40_SUCCESS;
}

int EE_mrf24j40_disable_IRQ(void)
{
	EE_mrf24j40_int_disable();
	
	return MRF24J40_SUCCESS;
}

int EE_mrf24j40_IRQ_enabled(void)
{
	return EE_hal_gpio_read_irqMask(ee_mrf24j40_st.base) & EE_INT2_MASK;
}

/*
	int EE_mrf24j40_enable(void);
	This function enables device by reset pin. 
*/
int EE_mrf24j40_enable(void)
{
	EE_mrf24j40_release_reset();
	EE_mrf24j40_delay_us(1000);
	
    return MRF24J40_SUCCESS;
}

/*
	int EE_mrf24j40_disable(void);
	This function disables device by reset pin. 
*/
int EE_mrf24j40_disable(void)
{
	EE_mrf24j40_hold_in_reset();
	
    return MRF24J40_SUCCESS;
}

#endif // #ifdef __USE_MICO32BOARD_ZIGBEE_MRF24J40__
