/** 
* @file fm25h20_compiler.h
* @brief FM25H20 Driver
* @author Christian Nastasi
* @author Marco Ghibaudi 
* @date 2010-01-25
*
* This file is the definition of the abstract compiler used by all the module
* of the FM25H20 library. 
*
* \todo Write something about the supported compilers.
*/

#ifndef _fm25h20_h_
#define _fm25h20_h_

#include "fm25h20_hal.h"

///* Functions prototypes */
//uint8_t fm25h20_init(uint8_t int_setup, uint8_t ch, uint8_t port);
//uint8_t fm25h20_write(uint8_t* buf, uint8_t len);
//uint8_t fm25h20_read(uint8_t *msg);
//uint8_t fm25h20_put_to_sleep();
//uint8_t fm25h20_wake() ;
//
///* Standard Command */
//
//#define FM25H20_WRITE_ENABLE (0b00000110)	//Enables write operation
//#define FM25H20_WRITE_DISABLE (0b00000100)	//Disables write operation
//#define FM25H20_READ_STATUS_REG (0b00000101)    //Read the status register
//#define FM25H20_WRITE_STATUS_REG (0b00000001)	//Writes the status register
//#define FM25H20_READ_MEMORY (0b00000011)	//Reads the memory
//#define FM25H20_WRITE_MEMORY (0b00000010)	//Writes the memory
//#define FM25H20_SLEEP (0b10111001)		//Enters in the Sleep mode
//
///**
//* Write single byte in the memory
//*/
//COMPILER_INLINE void fm25h20_write_byte(uint32_t addr, uint8_t val)
//{
//	mrf24j40_spi_put(FM25H20_WRITE_ENABLE, NULL); //TODO: non è ancora la funzione giusta,rimappare
//	mrf24j40_spi_put(FM25H20_WRITE_MEMORY, NULL);
//	mrf24j40_spi_put(((uint8_t)(addr>>16))&0x3, NULL);
//	mrf24j40_spi_put((uint8_t)(addr>>8), NULL);
//	mrf24j40_spi_put((uint8_t)(addr), NULL);
//	mrf24j40_spi_put(val, NULL);
//}
//
//
//COMPILER_INLINE uint8_t fm25h20_read_byte(uint32_t addr) //TODO: non è ancora la funzione giusta,rimappare
//{
//	uint8_t ret_val;
//	mrf24j40_spi_put(FM25H20_READ_MEMORY, NULL);
//	mrf24j40_spi_put(((uint8_t)(addr>>16))&0x3, NULL);
//	mrf24j40_spi_put((uint8_t)(addr>>8), NULL);
//	mrf24j40_spi_put((uint8_t)(addr), NULL);
//	mrf24j40_spi_get(&ret_val);
//	return ret_val;
//}
//
//COMPILER_INLINE void fm25h20_sleep() //TODO: non è ancora la funzione giusta,rimappare
//{
//	mrf24j40_spi_put(FM25H20_SLEEP, NULL);
//}
//
//COMPILER_INLINE void fm25h20_wake() //TODO: non è ancora la funzione giusta,rimappare
//{
//	//Probabilmente basta alzare il CS, 
//	
//	mrf24j40_spi_put(FM25H20_READ_MEMORY, NULL);
//	while ( mrf24j40_spi_get(&retval) ) ; //Potrebbe andare attende che arrivi qualcosa
//}
//

#endif /* _fm25h20_h_*/
