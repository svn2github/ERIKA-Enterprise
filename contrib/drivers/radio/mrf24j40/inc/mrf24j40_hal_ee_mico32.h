/*
  Name: mrf24j40_hal_ee_mico32.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: mico32 internal functions for u-wireless (zigbee) protocol
*/

#ifndef __mrf24j40_hal_ee_mico32_h__
#define __mrf24j40_hal_ee_mico32_h__

#ifndef __USE_SPI__
#error "MRF24J40 HAL EE : The SPI module is required!"
#endif

#ifdef __USE_MICO32BOARD_ZIGBEE_MRF24J40__
#include <board/fpga_camera_mico32/inc/ee_zigbee_mrf24j40.h>
#else		/* NO board */
#error "MRF24J40_HAL: No board selected!"
#endif

/* Macros for compatibility */
#define MRF24J40_SPI_PORT_1	0x01
#define MRF24J40_SPI_PORT_2	0x02
#define ISR2(func) void func(void)

#define MRF24J40_HAL_ISR() ISR2(MRF24J40_INTERRUPT_NAME)

void mrf24j40_set_rx_callback(void (*func)(void));
void mrf24j40_set_tx_finished_callback(void (*tx_finished_func)(uint8_t tx_status));

ISR2(MRF24J40_INTERRUPT_NAME);
int8_t	mrf24j40_hal_init(void);
void	mrf24j40_hal_delay_us(uint16_t delay_count); 
int8_t	mrf24j40_hal_spi_init(uint8_t port);
int8_t	mrf24j40_hal_spi_close(void);
int8_t	mrf24j40_hal_spi_write(uint8_t *data, uint16_t len);
int8_t	mrf24j40_hal_spi_read(uint8_t *data, uint16_t len);

COMPILER_INLINE void mrf24j40_hal_retsetn_high(void)
{
	//MRF24J40_RESETn = 0;
	EE_mrf24j40_enable();
}

COMPILER_INLINE void mrf24j40_hal_retsetn_low(void)
{
	//MRF24J40_RESETn = 1;
	EE_mrf24j40_disable();
}

COMPILER_INLINE void mrf24j40_hal_csn_high(void)
{
	EE_mrf24j40_clear_SSO();
}

COMPILER_INLINE void mrf24j40_hal_csn_low(void)
{
	EE_mrf24j40_set_slave(EE_MRF24J40_DEVICE_ID);	
	EE_mrf24j40_set_SSO(); // ss is low when transmission begins...
}

COMPILER_INLINE void mrf24j40_hal_irq_enable(void)
{
	EE_mrf24j40_enable_IRQ();
}

COMPILER_INLINE void mrf24j40_hal_irq_disable(void)
{
	EE_mrf24j40_disable_IRQ();
}

COMPILER_INLINE uint8_t mrf24j40_hal_irq_status(void)
{
	return EE_mrf24j40_IRQ_enabled();
}

#endif /* Header Protection */
