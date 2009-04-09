/**
* @file cc2420_hal_.c
* @brief CC2420 Hw Abstraction Layer using Erika OS
* @author Gianluca Franchino
* @author Christian Nastasi
* @author Mauro Nino Marinoni
* @date 2009-03-24
*
* This file is the  hardware abstraction layer used by all the module
* of the CC2420 library which uses the Erika kernel drivers.
*
* \todo Write something about the hal support.
*/
#include <cc2420_hal.h>

#if defined __MICROCHIP_DSPIC30__

static uint16_t temp_count = 0;

void cc2420_delay_us( uint16_t delay_count )
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

int8_t	cc2420_hal_init(void)
{
	/* Set the IO pins direction */
	CC2420_TRIS_RESETn = 0;
	CC2420_TRIS_VREG_EN = 0;
	CC2420_TRIS_FIFO = 1;
	CC2420_TRIS_FIFOP = 1;
	CC2420_TRIS_CCA = 1;
	CC2420_TRIS_CSn = 0;
	/* Set interrupt registers */
	CC2420_INTERRUPT_FLAG = 0;
	CC2420_INTERRUPT_PRIORITY = 1;
	CC2420_INTERRUPT_EDGE_POLARITY = 0;
	CC2420_INTERRUPT_ENABLE = 1;
	return 1;
}

static uint8_t spi_port;

int8_t	cc2420_spi_init(uint8_t port)
{
	spi_port = port;
	return EE_spi_init(spi_port);
}

int8_t	cc2420_spi_close(void)
{
	return EE_spi_close(spi_port);
}

int8_t	cc2420_spi_put(uint8_t in, uint8_t *out)
{
	if (out != NULL)
		return EE_spi_rw_byte(spi_port, in, out);
	else
		return EE_spi_write_byte(spi_port, in);
}

int8_t	cc2420_spi_get(uint8_t *out)
{
	uint8_t dummy;

	if (out != NULL)
		return EE_spi_read_byte(spi_port, out);
	else
		return EE_spi_read_byte(spi_port, &dummy);
}

#elif defined __AVR5__

static uint16_t temp_count = 0;

// TODO: (Nino) Change to AVR5
void cc2420_delay_us( uint16_t delay_count )
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

// TODO: (Nino) Change to AVR5
int8_t	cc2420_hal_init(void)
{
	/* Set the IO pins direction */
	CC2420_TRIS_RESETn = 0;
	CC2420_TRIS_VREG_EN = 0;
	CC2420_TRIS_FIFO = 1;
	CC2420_TRIS_FIFOP = 1;
	CC2420_TRIS_CCA = 1;
	CC2420_TRIS_CSn = 0;
	/* Set interrupt registers */
	CC2420_INTERRUPT_FLAG = 0;
	CC2420_INTERRUPT_PRIORITY = 1;
	CC2420_INTERRUPT_EDGE_POLARITY = 0;
	CC2420_INTERRUPT_ENABLE = 1;
	return 1;
}

static uint8_t spi_port;

int8_t	cc2420_spi_init(uint8_t port)
{
	spi_port = port;
	return EE_spi_init(spi_port);
}

int8_t	cc2420_spi_close(void)
{
	return EE_spi_close(spi_port);
}

int8_t	cc2420_spi_put(uint8_t in, uint8_t *out)
{
	if (out != NULL)
		return EE_spi_rw_byte(spi_port, in, out);
	else
		return EE_spi_write_byte(spi_port, in);
}

int8_t	cc2420_spi_get(uint8_t *out)
{
	uint8_t dummy;

	if (out != NULL)
		return EE_spi_read_byte(spi_port, out);
	else
		return EE_spi_read_byte(spi_port, &dummy);
}

#else

#error "CC2420_HAL: Architecture not supported!"

#endif
