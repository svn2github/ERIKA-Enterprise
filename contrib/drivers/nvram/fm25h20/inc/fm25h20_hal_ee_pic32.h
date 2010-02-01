/** 
* @file fm25h20_hal_ee_pic32.h
* @brief FM25H20 Hw Abstraction Layer using Erika OS over Microchip pic32
* @author Christian Nastasi
* @author Marco Ghibaudi
* @date 2010-01-12
*
* This file is the definition of the hardware abstraction layer 
* used by all the module
* of the FM25H20 library which uses the Erika kernel drivers. 
*
* \todo Write something about the hal support.
*/

#ifndef __fm25h20_hal_ee_pic32_h__
#define __fm25h20_hal_ee_pic32_h__

#ifndef __USE_SPI__
#error "FM25H20 HAL EE : The SPI module from MCU is required!"
#endif
#include <mcu/microchip_pic32/inc/ee_spi.h>

#define FM25H20_SPI_PORT_1	EE_SPI_PORT_1
#define FM25H20_SPI_PORT_2	EE_SPI_PORT_2

#define FM25H20_CS PORTGbits.RG9 //SS2
#define FM25H20_HOLD PORTCbits.RC2 //attivo basso
#define FM25H20_WRITE_PROTECT PORTCbits.RC3 //attivo basso


#define FM25H20_TRIS_CS TRISGbits.TRISG9
#define FM25H20_TRIS_HOLD TRISCbits.TRISC2
#define FM25H20_TRIS_WRITE_PROTECT TRISCbits.TRISC3



/* Functions prototypes */

/** 
* @brief  Add a delay. 
* 	
* This function adds a delay of \var delay_count us. Accuracy ~ 2% @ 80 Mhz.
*  	
* @ param[in]  delay_count number of us to be waited
* 
*/
void fm25h20_delay_us(uint16_t delay_count); 



/** 
* @brief Initializes SPI. 
* 	
* This function initializes the SPI.
*  	
* @ param[in]	port SPI port to be used.
* @ return	\todo 
*/
int8_t fm25h20_spi_init(uint8_t port);


/** 
* @brief Closes SPI. 
* 	
* This function closes the SPI.
*  	
* @ return	EE_SPI_PORT_CLOSED after closing the port. 
*/
int8_t fm25h20_spi_close(void);


/** 
* @brief Put on SPI. 
* 	
* This function puts data on the SPI.
*  	
* @ param[in]	in data to be transmitted.
* @ param[in]	*out address of data read-back
* @ return	\todo 
*/
int8_t fm25h20_spi_put(uint8_t in, uint8_t *out);


/** 
* @brief Get from SPI. 
* 	
* This function acquires data from the SPI.
*  	
* @ param[in]	*out address of data read-back
* @ return	\todo 
*/
int8_t fm25h20_spi_get(uint8_t *out);

COMPILER_INLINE void fm25h20_hal_cs_high(void)
{
	FM25H20_CS = 1;
}


COMPILER_INLINE void fm25h20_hal_cs_low(void)
{
	FM25H20_CS = 0;
}


#endif /* Header Protection */
