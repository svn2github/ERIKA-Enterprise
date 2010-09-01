/** 
* @file pcf8583.h
* @brief PCF8583 real time clock Driver
* @author Dario Di Stefano 
* @date 2010-08-30
*
* This file is the definition of the hardware abstraction layer used by the 
* pcf8583 device driver 
*
* \todo Write something about the supported compilers.
*/

#ifndef __PCF8583_H__
#define __PCF8583_H__

#include "pcf8583_compiler.h"
#include "pcf8583_hal.h"

/* Time structure */
typedef struct {
    uint8_t year, month, day, hours, minutes, seconds, hundredths;
} TTime;

/******************************************************************************/
/*				Registers Definition 			      */
/******************************************************************************/

/*	Slave device addresses		*/
#define RTC_DEVICE_ADDRESS      (0xA0)

/* Driver Macros */
#define RTC_OFF                 (0x80)
#define RTC_ON                  (0x00)

/*	Register adresses		*/
#define RTC_CSR_ADD             (0x00)
#define RTC_HSECONDS_ADD        (0x01)
#define RTC_SECONDS_ADD         (0x02)
#define RTC_MINUTES_ADD         (0x03)
#define RTC_HOURS_ADD           (0x04)
#define RTC_DAYS_ADD            (0x05)
#define RTC_MONTHS_ADD          (0x06)
#define RTC_TIMER_ADD           (0x07)
#define RTC_YEAR_ADD            (0x10)
#define RTC_FREE_RAM_ADD        (0x11)

/*	Operation Status		*/
#define RTC_NO_ERROR		1	//returned as positive

/******************************************************************************/
/* 			Constants			      */
/******************************************************************************/


/******************************************************************************/
/*				 Inline Functions 			      */
/******************************************************************************/
/**
 * \brief RTC driver initialization.
 *
 * It configures the I2C bus.
 */
__INLINE__ void __ALWAYS_INLINE__ EE_rtc_init(void)
{
    EE_rtc_hal_init();
}

/* Probably, EE_rtc_init() makes this obsolete */
__INLINE__ void __ALWAYS_INLINE__  EE_rtc_config(uint32_t baudrate, uint32_t settings)
{
    EE_rtc_hal_config(baudrate, settings);
}

/*
		This function is used to turn on the rt-clock. 
		Arguments: 
			- none 
		Actions: 
			- turn on the rt-clock
		Return values:
			- the function return the result:	EE_I2C_ERR_DEV_ACK if ACK is not received after slave address transmission
												EE_I2C_ERR_ADD_ACK if ACK is not received after memory address transmission
												EE_I2C_ERR_DATA_ACK if ACK is not received after data transmission
												EE_I2C_ERR_ARB_LOST if arbitration is lost
												EE_I2C_OK if no errors found							
*/
__INLINE__ void __ALWAYS_INLINE__  EE_rtc_start(void)
{
    EE_rtc_hal_start();
}

/*
		This function is used to turn off the rt-clock. 
		Arguments: 
			- none 
		Actions: 
			- turn off the rt-clock
		Return values:
			- the function return the result:	EE_I2C_ERR_DEV_ACK if ACK is not received after slave address transmission
												EE_I2C_ERR_ADD_ACK if ACK is not received after memory address transmission
												EE_I2C_ERR_DATA_ACK if ACK is not received after data transmission
												EE_I2C_ERR_ARB_LOST if arbitration is lost
												EE_I2C_OK if no errors found							
*/
__INLINE__ void __ALWAYS_INLINE__  EE_rtc_shutdown(void)
{
    EE_rtc_hal_shutdown();
}


/*
		This function is used to store one byte in the rt-clock RAM. 
		Arguments: 
			- EE_UINT8 address: memory address in rt-clock RAM
			- EE_UINT8 data: byte to be stored 
		Actions: 
			- store one byte in the rt-clock RAM.
		Return values:
			- the function return the result:	EE_I2C_ERR_DEV_ACK if ACK is not received after slave address transmission
												EE_I2C_ERR_ADD_ACK if ACK is not received after memory address transmission
												EE_I2C_ERR_DATA_ACK if ACK is not received after data transmission
												EE_I2C_ERR_ARB_LOST if arbitration is lost
												EE_I2C_OK if no errors found							
*/
__INLINE__ void __ALWAYS_INLINE__  EE_rtc_write_byte(uint8_t address, uint8_t data)
{
    EE_rtc_hal_write_byte(address, data);
}

/*
		This function is used to store one byte in the rt-clock RAM. 
		Arguments: 
			- EE_UINT8 address: memory address in rt-clock RAM
			- EE_UINT8 data: address of the first byte to be stored 
			- int len: number of bytes to be written
		Actions: 
			- store bytes in the rt-clock RAM.
		Return values:
			- the function return the result:	EE_I2C_ERR_DEV_ACK if ACK is not received after slave address transmission
												EE_I2C_ERR_ADD_ACK if ACK is not received after memory address transmission
												EE_I2C_ERR_DATA_ACK if ACK is not received after data transmission
												EE_I2C_ERR_ARB_LOST if arbitration is lost
												EE_I2C_OK if no errors found							
*/
__INLINE__ void __ALWAYS_INLINE__  EE_rtc_write_buffer(uint8_t address, const uint8_t *data, uint32_t len)
{
	EE_rtc_hal_write_buffer(address, data, len);
}


/*
		This function is used to read one byte from the rt-clock RAM. 
		Arguments: 
			- EE_UINT8 address: memory address in rt-clock RAM to be read
		Actions: 
			- read one byte from the rt-clock RAM.
		Return values:
			- the function return the result:	EE_I2C_ERR_DEV_ACK if ACK is not received after slave address transmission
												EE_I2C_ERR_ADD_ACK if ACK is not received after memory address transmission
												EE_I2C_ERR_DATA_ACK if ACK is not received after data transmission
												EE_I2C_ERR_ARB_LOST if arbitration is lost
												EE_I2C_OK if no errors found							
*/
__INLINE__ int __ALWAYS_INLINE__  EE_rtc_read_byte(uint8_t address)
{
    return EE_rtc_hal_read_byte(address);
}

/*
		This function is used to store one byte in the rt-clock RAM. 
		Arguments: 
			- EE_UINT8 address: memory address of the first location in rt-clock RAM to be read
			- EE_UINT8 *data: memory address of the first location of the array used to store received bytes
			- int len: number of bytes to be read
		Actions: 
			- read a number of bytes from the rt-clock RAM.
		Return values:
			- the function return the result:	EE_I2C_ERR_DEV_ACK if ACK is not received after slave address transmission
												EE_I2C_ERR_ADD_ACK if ACK is not received after memory address transmission
												EE_I2C_ERR_DATA_ACK if ACK is not received after data transmission
												EE_I2C_ERR_ARB_LOST if arbitration is lost
												EE_I2C_OK if no errors found							
*/
__INLINE__ void __ALWAYS_INLINE__  EE_rtc_read_buffer(uint8_t address, uint8_t *data, uint32_t len)
{
    EE_rtc_hal_read_buffer(address, data, len);
}





/******************************************************************************/
/*				 Prototipes	 			      */
/******************************************************************************/

/*
		This function is used to change the rt-clock internal time. 
		Arguments: 
			- const TTime *ttw: pointer to the TTime structure with the time to be written; 
		Actions: 
			- send i2c commands to turn off the clock, write new time and then turn on the clock;
		Return values:
			- the function return the result:	EE_I2C_ERR_DEV_ACK if ACK is not received after slave address transmission
												EE_I2C_ERR_ADD_ACK if ACK is not received after memory address transmission
												EE_I2C_ERR_DATA_ACK if ACK is not received after data transmission
												EE_I2C_ERR_ARB_LOST if arbitration is lost
												EE_I2C_OK if no errors found							
*/
int EE_rtc_write_time(const TTime *ttw);

/*
		This function is used to read the rt-clock internal time. 
		Arguments: 
			- TTime *ttr: pointer to the TTime structure with the time to be read; 
		Actions: 
			- send i2c commands to read the time;
		Return values:
			- the function return the result:	EE_I2C_ERR_DEV_ACK if ACK is not received after slave address transmission
												EE_I2C_ERR_ADD_ACK if ACK is not received after memory address transmission
												EE_I2C_ERR_DATA_ACK if ACK is not received after data transmission
												EE_I2C_ERR_ARB_LOST if arbitration is lost
												EE_I2C_OK if no errors found							
*/
int EE_rtc_read_time(TTime *ttr); 

#endif // __PCF8583_H___
