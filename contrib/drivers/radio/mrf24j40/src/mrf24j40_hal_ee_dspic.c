/** 
* @file mrf24j40_hal_ee_dspic.c
* @brief MRF24J40 Hw Abstraction Layer using Erika OS over microchip dsPIC
* @author Gianluca Franchino
* @author Christian Nastasi
* @author Mauro Nino Marinoni
* @date 2009-03-24
*
* This file is the  hardware abstraction layer used by all the module
* of the MRF24J40 library which uses the Erika kernel drivers. 
*
* \todo Write something about the hal support.
*/
#include <mrf24j40_hal.h>

#ifdef __MICROCHIP_DSPIC30__


static uint16_t temp_count = 0;

void mrf24j40_delay_us( uint16_t delay_count ) 
{
	temp_count = delay_count +1;
	asm volatile("outer: dec _temp_count");	
	asm volatile("cp0 _temp_count");
	asm volatile("bra z, done");
	asm volatile("do #1500, inner" );	
	asm volatile("nop");
	asm volatile("inner: nop");
	asm volatile("bra outer");
	asm volatile("done:");
}

int8_t	mrf24j40_hal_init(void)
{
	/* Set the IO pins direction */
	MRF24J40_TRIS_RESETn = 0;
	MRF24J40_TRIS_VREG_EN = 0;
	MRF24J40_TRIS_FIFO = 1;
	MRF24J40_TRIS_FIFOP = 1;
	MRF24J40_TRIS_CSn = 0;
	/* Set interrupt registers */
	MRF24J40_INTERRUPT_FLAG = 0;
	MRF24J40_INTERRUPT_PRIORITY = 1;
	MRF24J40_INTERRUPT_EDGE_POLARITY = 0;
	MRF24J40_INTERRUPT_ENABLE = 1;
	return 1;
}

static uint8_t spi_port; 

int8_t	mrf24j40_spi_init(uint8_t port)
{
	spi_port = port;
	return EE_spi_init(spi_port);
}

int8_t	mrf24j40_spi_close(void)
{
	return EE_spi_close(spi_port);
}

int8_t	mrf24j40_spi_write(uint8_t *data, uint16_t len)
{
	uint16_t i;

	for (i = 0; i < len; i++)
		EE_spi_write_byte(spi_port, data[i]);
	return 1;
}

int8_t	mrf24j40_spi_read(uint8_t *data, uint16_t len)
{
	uint16_t i;

	for (i = 0; i < len; i++)
		EE_spi_read_byte(spi_port, data + i);
	return 1;
}

#else

#error "MRF24J40_HAL: Architecture not supported!"

#endif
