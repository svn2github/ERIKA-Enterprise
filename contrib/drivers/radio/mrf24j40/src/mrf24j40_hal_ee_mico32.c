/*
  Name: mrf24j40_hal_ee_mico32.c
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: MRF24J40 Hw Abstraction Layer using Erika OS over Lattice mico32.
*/

#include <mrf24j40_hal.h>

#ifdef __LM32__

int8_t	mrf24j40_hal_init(void)
{
    EE_mrf24j40_init();
	
	return 1;
} 

int8_t	mrf24j40_hal_spi_init(uint8_t port)
{
    EE_mrf24j40_hal_spi_config(0, EE_SPI_POLLING | EE_SPI_RXTX_BLOCK);
	EE_mrf24j40_set_ISR_mode(EE_MRF24J40_RXTX_ISR); //(EE_MRF24J40_POLLING | EE_MRF24J40_RXTX_BLOCK);

    return 1;
}

int8_t	mrf24j40_hal_spi_close(void)
{
    EE_mrf24j40_hal_spi_close();
	
    return 1;
}

int8_t	mrf24j40_hal_spi_write(uint8_t *data, uint16_t len)
{
    EE_mrf24j40_write_buffer(data, len);
	
    return 1;
}

int8_t	mrf24j40_hal_spi_read(uint8_t *data, uint16_t len)
{
    EE_mrf24j40_read_buffer(data, len);
	
	return 1;
}

void mrf24j40_hal_delay_us(EE_UINT16 delay_count) 
{	
    EE_mrf24j40_hal_delay_us(delay_count);
}

#else

#error "MRF24J40_HAL: Architecture not supported!"

#endif
