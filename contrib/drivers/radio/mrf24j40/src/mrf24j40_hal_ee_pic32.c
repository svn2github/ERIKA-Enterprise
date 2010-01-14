/** 
* @file mrf24j40_hal_ee_pic32.c
* @brief MRF24J40 Hw Abstraction Layer using Erika OS over microchip pic32.
* @author Christian Nastasi
* @author Marco Ghibaudi 
* @date 2010-01-12
*
* This file is the  hardware abstraction layer used by all the module
* of the MRF24J40 library which uses the Erika kernel drivers. 
*
* \todo Write something about the hal support.
*/
#include <mrf24j40_hal.h>

#ifdef __MICROCHIP_PIC32__

static uint8_t spi_port; 

void mrf24j40_delay_us(uint16_t delay_count) 
{
	asm volatile(	"lui $v0, %hi(18000)\n\t"
			"addiu $v0, $v0, %lo(18000)\n\t"
			"1:\n\t"
			"addi $v0, $v0, -1\n\t"
		      	"bne $v0, $zero, 1b\n\t"
	);
}

int8_t	mrf24j40_hal_init(void)
{
	/* Set the IO pins direction */
	MRF24J40_TRIS_RESETn = 0;
	MRF24J40_TRIS_INT = 1;
	MRF24J40_TRIS_CSn = 0;
	/* Set interrupt registers */
	MRF24J40_INTERRUPT_FLAG = 0;
	MRF24J40_INTERRUPT_PRIORITY = 1;
	MRF24J40_INTERRUPT_EDGE_POLARITY = 0;
	MRF24J40_INTERRUPT_ENABLE = 1;
	return 1;
}

int8_t	mrf24j40_spi_init(uint8_t port)
{
	spi_port = port;
	return EE_spi_init(spi_port);
}

int8_t	mrf24j40_spi_close(void)
{
	return EE_spi_close(spi_port);
}

int8_t	mrf24j40_spi_put(uint8_t in, uint8_t *out)
{
	if (out != NULL)
		return EE_spi_rw_byte(spi_port, in, out);
	else
		return EE_spi_write_byte(spi_port, in);
}

int8_t	mrf24j40_spi_get(uint8_t *out)
{
	uint8_t dummy;

	if (out != NULL)
		return EE_spi_read_byte(spi_port, out);
	else
		return EE_spi_read_byte(spi_port, &dummy);
}

#else

#error "MRF24J40_HAL: Architecture not supported!"

#endif
