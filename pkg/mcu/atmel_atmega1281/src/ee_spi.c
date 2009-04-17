#include "mcu/atmel_atmega128/inc/ee_mcuregs.h"
#include "mcu/atmel_atmega128/inc/ee_spi.h"

// TODO: (Nino) Convert from PIC30 to AVR5!

EE_INT8 EE_spi_init(void)
{
	/* Note: the chip select pin (SS1)  work manually in master mode,
		we drive this pin  directly setting it as a normal I/O pin.  */

	/* Setup SPI I/O pins */
	EE_reg(PORTB) |= (1<<PB1);	// set SCK hi
	EE_reg(DDRB) &= ~(1<<PB3);	// set MISO as input
	EE_reg(DDRB) |= (1<<PB0);	// SS must be output for Master mode to work
	EE_reg(DDRB) |= (1<<PB1);	// set SCK as output
	EE_reg(DDRB) |= (1<<PB2);	// set MOSI as output
	
	/* Enable SPI, Master, set clock rate fck/4 */
	/* Note: with these prescale values the port works at 2 MHz. */
	
	// TODO: (Nino): Clock polarity and Phase are ok?
	EE_reg(SPCR) = (1<<SPE)|(1<<MSTR);
	
	return 1;
}

EE_INT8 EE_spi_close(void)
{
	return 1;
}

EE_INT8 EE_spi_rw_byte(EE_UINT8 data_in, EE_UINT8 *data_out)
{
	/* Wait for transmission complete */
	while( !(EE_reg(SPSR) & (1<<SPIF)) );

	/* Start transmission */
	EE_reg(SPDR) = data_in;

	/* Wait for transmission complete */
	while( !(EE_reg(SPSR) & (1<<SPIF)) );

	/* Start transmission */
	*data_out = EE_reg(SPDR);

	return 1;
}

EE_INT8 EE_spi_write_byte(EE_UINT8 data)
{
	/* Wait for transmission complete */
	while( !(EE_reg(SPSR) & (1<<SPIF)) );

	/* Start transmission */
	EE_reg(SPDR) = data;

	return 1;
}

EE_INT8 EE_spi_read_byte(EE_UINT8 *data)
{
	/* Wait for transmission complete */
	while( !(EE_reg(SPSR) & (1<<SPIF)) );

	/* Start transmission */
	EE_reg(SPDR) = 0x00;

	/* Wait for transmission complete */
	while( !(EE_reg(SPSR) & (1<<SPIF)) );

	/* Start transmission */
	*data = EE_reg(SPDR);

	return 1;
}
