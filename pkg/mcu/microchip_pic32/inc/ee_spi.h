#ifndef __INCLUDE_MICROCHIP_PIC32_SPI_H__
#define __INCLUDE_MICROCHIP_PIC32_SPI_H__

#include "ee.h"

/* Include a file with the registers from Microchip C32 distribution */ 
#ifdef __PIC32_INCLUDE_REGS__
#include "ee_pic32regs.h"
#endif

//#include "P2PDefs.h"	// FIXME: chris: from gianluca's driver

enum {
	EE_SPI_PORT_1  = 0,
	EE_SPI_PORT_2,
	EE_SPI_PORT_N,
};


#define EE_SPI_NO_ERRORS		1	//Used positive
#define EE_SPI_ERR_BAD_PORT		1

//#define EE_SPI_ERR_NO_DATA		2
//#define EE_SPI_ERR_OVERFLOW		3
//#define EE_SPI_ERR_INT_MODE		4
//#define EE_SPI_ERR_INT_DISABLED	5

/**
* @brief Initialize the SPI peripheral.
*
* This function initializes the SPI peripheral defined by 
* the input parameter \p port.
*
* @param[in] port 	
* @param[in] baudrate 	
* @param[in] flags 	
* @return 	\todo
*
* @pre		None
*/
EE_INT8 EE_spi_init(EE_UINT8 port/*, EE_UINT32 baudrate, EE_UINT16 flags*/); 



/**
* @brief Switch-off the SPI peripheral.
*
* This function switches-off the SPI peripheral defined by 
* the input parameter \p port.
*
* @param[in] port 	
* @return	EE_SPI_NO_ERRORS if no errors occurred. Otherwise a negative
*		number
*
* @pre		None
*/
EE_INT8 EE_spi_close(EE_UINT8 port); 


/**
* @brief Send a byte through the SPI peripheral.
*
* This function send a character (8 bits) through the SPI 
* port controlling the radio.
*
* @param[in] data_in	The character to be sent
* @param[out] data_out	\todo
*
* @return 	\todo
*
* @pre		The SPI port must be correctly initialized.
*/
EE_INT8 EE_spi_rw_byte(EE_UINT8 port, EE_UINT8 data_in, EE_UINT8 *data_out);


/**
* @brief Send a byte through  the SPI peripheral.
*
* This function send a character (8 bits) through the SPI 
* port controlling the radio.
*
* @param[in] data	The character to be sent
*
* @return 	\todo
*
* @pre		The SPI port must be correctly initialized.
*/
__INLINE__ EE_INT8 EE_spi_write_byte(EE_UINT8 port, EE_UINT8 data)
{
	return EE_spi_rw_byte(port, data, &data);
}


/**
* @brief Get a character through the SPI peripheral.
*
* This function send a character (8 bits) through the SPI 
* port controlling the radio.
*
* @return 	\todo
*
* @pre		The SPI port must be correctly initialized.
*/
__INLINE__ EE_INT8 EE_spi_read_byte(EE_UINT8 port, EE_UINT8 *data)
{
	return EE_spi_rw_byte(port, 0x00, data);
}

#endif
