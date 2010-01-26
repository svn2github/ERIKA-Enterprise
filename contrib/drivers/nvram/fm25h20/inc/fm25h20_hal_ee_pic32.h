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

int8_t fm25h20_spi_init(uint8_t port);
int8_t fm25h20_spi_close(void);
int8_t fm25h20_spi_put(uint8_t in, uint8_t *out);
int8_t fm25h20_spi_get(uint8_t *out);

#endif /* Header Protection */
