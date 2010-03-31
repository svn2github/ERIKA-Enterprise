/*
  Name: ee_zigbee_mrf24j40.c
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.27
  Description: Zigbee library for MICO32 CAMERA board
*/

#ifdef __USE_MICO32BOARD_ZIGBEE_MRF24J40__

#include "board/fpga_camera_mico32/inc/ee_zigbee_mrf24j40.h"
#include "contrib/drivers/radio/mrf24j40/inc/mrf24j40_hal.h"

int to_remove;

/* ---------------------- Global variables --------------------------------- */
EE_ISR_callback ee_mrf24j40_cbk;	// ISR ethctrl callback function
EE_UINT8 ee_mrf24j40_isr_rxvet[EE_MRF24J40_BUFSIZE];
EE_UINT8 ee_mrf24j40_isr_txvet[EE_MRF24J40_BUFSIZE];  

EE_mrf24j40_st ee_mrf24j40_st = {
	.mode= EE_MRF24J40_RXTX_ISR, .base= 0,//(MicoGPIO_t* )MISC_GPIO_BASE_ADDRESS,
	.irqf= 0/*MISC_GPIO_IRQ*/, .rxcbk= EE_NULL_CBK, .txcbk= EE_NULL_CBK,
	.rxbuf.data= ee_mrf24j40_isr_rxvet,.txbuf.data= ee_mrf24j40_isr_txvet};

/* ---------------------- Ethernet interrupt handler ------------------------- */

void EE_mrf24j40_handler(int level)
{
    MRF24J40_INTERRUPT_NAME();
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
	
    //MicoGPIO_t *mrf = ee_mrf24j40_st.base; 
	
	old_mode = ee_mrf24j40_st.mode;
	if(old_mode == mode)
		return MRF24J40_SUCCESS;
	
	/* Disble IRQ */
	intst = EE_mico32_disableIRQ();
	
	/* Register IRQ handler */
	EE_hal_mrf24j40_handler_setup();
	ee_mrf24j40_st.mode = mode; 	
	/* Buffer initialization */
	if (EE_mrf24j40_need_init_rx_buf(old_mode, mode))
		EE_buffer_init(&ee_mrf24j40_st.rxbuf, EE_MRF24J40_MSGSIZE, EE_MRF24J40_BUFSIZE, ee_mrf24j40_st.rxbuf.data);
	if (EE_mrf24j40_need_init_tx_buf(old_mode, mode))
		EE_buffer_init(&ee_mrf24j40_st.txbuf, EE_MRF24J40_MSGSIZE, EE_MRF24J40_BUFSIZE, ee_mrf24j40_st.txbuf.data);
	/* IRQ settings */
    //  to do...
//  if(EE_mrf24j40_need_enable_int(mode))
//		mico32_enable_irq(ee_mrf24j40_st.irqf);
//	else
//		mico32_disable_irq(ee_mrf24j40_st.irqf);
//	if(EE_mrf24j40_need_enable_rx_int(old_mode, mode))
//		mrf->ier = MICOUART_IER_RX_INT_MASK;	// check if we lose data when ier is written...	
//	else
//		mrf->ier = 0;

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
	/* Provide a delay with an accuracy of approx. ... @ 34MHz */
    asm volatile(	"1:\n\t"
		"addi r1, r1, -1\n\t"
		"nop\n\t"
		"bne r1, r0, 1b\n\t");		
}

int EE_mrf24j40_software_reset(void)
{
	int ret = MRF24J40_SUCCESS;
	
	EE_mrf24j40_write_short_address_register(EE_MRF24J40_SOFTRST, EE_MRF24J40_SOFTRST_MASK);
	
	return ret;
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
	
    return 0;
}

int EE_mrf24j40_enable_IRQ(void)
{
	int ret = MRF24J40_SUCCESS;
	
	// to do...
	ee_mrf24j40_st.base->irqMask = 0;
	
	return ret;
}

int EE_mrf24j40_disable_IRQ(void)
{
	int ret = MRF24J40_SUCCESS;
	
	// to do...
	ee_mrf24j40_st.base->irqMask = 0;
	
	return ret;
}

int EE_mrf24j40_IRQ_enabled(void)
{
	return ee_mrf24j40_st.base->irqMask;
}

/*
	int EE_mrf24j40_enable(void);
	This function enables device by reset pin. 
*/
int EE_mrf24j40_enable(void)
{
    // to do...
	EE_MRF24J40_RESET = 1;
	EE_mrf24j40_delay_us(1000);
    return 0;
}

/*
	int EE_mrf24j40_disable(void);
	This function disables device by reset pin. 
*/
int EE_mrf24j40_disable(void)
{
    EE_MRF24J40_RESET = 0;
	
    return 0;
}

#endif // #ifdef __USE_MICO32BOARD_ZIGBEE_MRF24J40__
