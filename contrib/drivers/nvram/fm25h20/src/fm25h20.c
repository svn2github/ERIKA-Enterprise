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

	/* Minimum time needed to power-up the device */
	fm25h20_delay_us(1500);		
	
	/* init hal-specific things */
	fm25h20_hal_init();
	
	/* init the SPI port */	
	retv = fm25h20_spi_init(port);

	if (retv < 0)
		return -FM25H20_SPI_INIT_FAILED;

	/* Select the device */
	fm25h20_hal_cs_low();
	
	/* test the memory, reading the read status register */
	retv = fm25h20_spi_get(FM25H20_READ_STATUS_REG); // TODO: Controllare
	
	/* Deselect the device */
	fm25h20_hal_cs_high();	
	
	/* bit 6 of the Status re TODO Finire commento*/
	if (retv & CHECK_MASK)
		return -FM25H20_FRAM_INIT_FAILED;
	
	fm25h20_initialized = 1; //TODO: verificare	 
	//Initializzation succeed
	return FM25H20_ERR_NONE;
}



int8_t fm25h20_store(uint32_t address, uint32_t len, uint8_t* buf)
{
	
	/* Check the addressing */
	if (address > MEMORY_SIZE)
		return -FM25H20_WRONG_MEMORY_ADDRESS;
	
	/* Select the device */
	fm25h20_hal_cs_low();
	uint32_t i;
	
	/*Enables the writing */
	fm25h20_spi_put(FM25H20_WRITE_ENABLE, NULL);
	
	/* Sends the write command */
	fm25h20_spi_put(FM25H20_WRITE_MEMORY, NULL);
	
	/* Selects the memory location */
	fm25h20_spi_put_address(address); 
	
	/* Writes the memory */
	for (i=0;i<len;i++)
		fm25h20_spi_put(buf[i], NULL);
	
	/* Deselect the device */
	fm25h20_hal_cs_high();

	return FM25H20_ERR_NONE;
}


int8_t fm25h20_get(uint32_t address, uint32_t len, uint8_t *data)
{
	uint32_t i;	
	if (address > MEMORY_SIZE)
		return -FM25H20_WRONG_MEMORY_ADDRESS;

	/* Select the device */
	fm25h20_hal_cs_low();

	fm25h20_spi_put(FM25H20_READ_MEMORY, NULL);
	fm25h20_spi_put_address(address); //TODO: Potrei dover metter un offset negativo 
					// all'indirizzo da poi aggiungere al for per
					// tenere conto del ritardo di lettura. o usare l'hold...
	for (i=0;i<len;i++)
		data[i] = fm25h20_spi_get(FM25H20_READ_MEMORY); /*TODO: messo
								per fare in sostanza
		una dummy-read. Da verificare, potrebbe bastare andare in polling */
	
	/* Deselect the device */
	fm25h20_hal_cs_high();
	return FM25H20_ERR_NONE;
}

