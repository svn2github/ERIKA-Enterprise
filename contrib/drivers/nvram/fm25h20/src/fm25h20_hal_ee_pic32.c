/** 
* @file fm25h20_hal_ee_pic32.c
* @brief FM25H20 Hw Abstraction Layer using Erika OS over microchip pic32.
* @author Christian Nastasi
* @author Marco Ghibaudi 
* @date 2010-01-12
*
* This file is the  hardware abstraction layer used by all the module
* of the FM25H20 which uses the Erika kernel drivers. 
*
*/

#include <fm25h20_hal.h>
      
#ifdef __MICROCHIP_PIC32__

static uint8_t spi_port; 

void fm25h20_delay_us(uint16_t delay_count) 
{	/* Provide a delay with an accuracy of approx. 2% @ 80Mhz*/
	asm volatile(	"add $t0, $a0, $zero\n\t"			  	
			"1:\n\t"
			"addi $t0, $t0, -1\n\t"
			"nop\n\t"
			"nop\n\t"
			"nop\n\t"
			"bne $t0, $zero, 1b\n\t");			
}

void fm25h20_hal_init(void)
{
	/* Set the IO pins direction */
	FM25H20_TRIS_CS = 0;
	FM25H20_TRIS_WRITE_PROTECT = 0;
	FM25H20_TRIS_HOLD = 0;	
}

int8_t	fm25h20_spi_init(uint8_t port)
{
	spi_port = port;
	return EE_spi_init(spi_port);
}

int8_t	fm25h20_spi_close(void)
{
	return EE_spi_close(spi_port);
}

int8_t	fm25h20_spi_put(uint8_t in, uint8_t *out)
{
	if (out != NULL)
		return EE_spi_rw_byte(spi_port, in, out);
	else
		return EE_spi_write_byte(spi_port, in);
}

int8_t	fm25h20_spi_get(uint8_t *out)
{
	uint8_t dummy;

	if (out != NULL)
		return EE_spi_read_byte(spi_port, out);
	else
		return EE_spi_read_byte(spi_port, &dummy);
}

#else

#error "FM25H20_HAL: Architecture not supported!"

#endif
