/** 
* @file fm25h20.c
* @brief FM25H20 Drive over Microchip pic32
* @author Christian Nastasi
* @author Marco Ghibaudi
* @date 2010-01-26
*
* This file is the driver used by the FM25H20 non volatile memory. 
*
* @todo verificare la variabile fm25h20_initialized e la sua gestione
*/

#include "fm25h20.h"


uint8_t fm25h20_initialized = 0; /*TODO: verificare se si può gestire in modo +
					elegante */

int8_t fm25h20_init(uint8_t port)
{  

	int8_t retv;
	if (fm25h20_initialized) 
		return -FM25H20_DOUBLE_INIT; 

	/* Wait the minimum time needed to power-up the device */
	fm25h20_delay_us(2500);	

	/* Init hal-specific things and disable the hardware protections */
	fm25h20_hal_init();
	fm25h20_hold_off();
	//fm25h20_write_protection_off();
	
	/* Init the SPI port with the default values */	
	retv = fm25h20_spi_init(port, FM25H20_SPI_CLOCK, FM25H20_SPI_FLAGS);

	if (retv < 0)
		return -FM25H20_SPI_INIT_FAILED;
	

	/* Select the device */
	fm25h20_cs_low();


	/* TODO: sistemare questa inizializzazione */	
	uint8_t set_write = FM25H20_WRITE_ENABLE;
	fm25h20_spi_write(&set_write, 1);
	uint8_t app = FM25H20_READ_STATUS_REG;
	/* test the memory, reading the read status register */
	retv = fm25h20_spi_read(&app,1); // TODO: Controllare
		
	/* Deselect the device */
	fm25h20_cs_high();	
	
	/* bit 6 of the Status re TODO Finire commento*/
	if (retv & CHECK_MASK){
		fm25h20_initialized = 1;
		return retv;//FM25H20_ERR_NONE
	}			
	return -FM25H20_FRAM_INIT_FAILED;

}



int8_t fm25h20_store(uint32_t address, uint32_t len, uint8_t *buf)
{
	
	/* Check the addressing */
	if (address > MEMORY_SIZE)
		return -FM25H20_WRONG_MEMORY_ADDRESS;
	
	/* Define the command to be sent */
	uint8_t set_write [WRITE_ARRAY_SIZE];
	set_write[0] = FM25H20_WRITE_ENABLE;
	set_write[1] = FM25H20_WRITE_MEMORY;
	set_write[2] = (uint8_t)(address>>16);
	set_write[3] = (uint8_t)(address>>8);
	set_write[4] = (uint8_t)(address &0XFF);
	
	/* Select the device */
	fm25h20_cs_low();

	/* Send the command and write the memory */
	fm25h20_spi_write(set_write, WRITE_ARRAY_SIZE); 
	fm25h20_spi_write(buf, len); 

	/* Deselect the device */
	fm25h20_cs_high();

	return FM25H20_ERR_NONE;
}


int8_t fm25h20_get(uint32_t address, uint32_t len, uint8_t *data)
{
	
 	/* Check the precondition */
	if (address > MEMORY_SIZE)
		return -FM25H20_WRONG_MEMORY_ADDRESS;

	/* Define the command to be sent */
	uint8_t set_read [READ_ARRAY_SIZE];
	set_read[0] = (uint8_t)(FM25H20_READ_MEMORY);
	set_read[1] = (uint8_t)(address>>16);
	set_read[2] = (uint8_t)(address>>8);
	set_read[3] = (uint8_t)(address &0XFF);
	
	/* Select the device */
	fm25h20_cs_low();
	
	/* Send the command and read the memory */
	fm25h20_spi_write(set_read, READ_ARRAY_SIZE);
	fm25h20_spi_read(data, len);

	/* Deselect the device */
	fm25h20_cs_high();
	return FM25H20_ERR_NONE;
}

