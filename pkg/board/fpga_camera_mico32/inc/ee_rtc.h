#ifdef __USE_MICO32BOARD_RTC__

#ifndef __EE_RTC_PCF8583__
#define __EE_RTC_PCF8583__

#include "mcu/mico32/inc/ee_i2c.h"

typedef struct {
  EE_UINT8 year, month, day, hours, minutes, seconds, hundreds_of_seconds;
} TTime;

/* Symbols and macros */
#define RTC_DEVICE_ID		(0xA0)
#define RTC_OFF 			(0x80)
#define RTC_ON				(0x00)

/* Memory address */
#define RTC_CSR_ADD 		(0x00)
#define RTC_HSECONDS_ADD 	(0x01)
#define RTC_SECONDS_ADD 	(0x02)
#define RTC_MINUTES_ADD 	(0x03)
#define RTC_HOURS_ADD 		(0x04)
#define RTC_DAYS_ADD 		(0x05)
#define RTC_MONTHS_ADD 		(0x06)
#define RTC_TIMER_ADD 		(0x07)
#define RTC_YEAR_ADD		(0x10)
#define RTC_FREE_RAM_ADD	(0x11)


/* RTC API: */

/* Macros for User functions (API) */  
#define DECLARE_FUNC_RTC(uc, lc) \
__INLINE__ int __ALWAYS_INLINE__  EE_rtc_start(void){ \
	return cat3(EE_, lc, _write_byte)(RTC_DEVICE_ID, RTC_CSR_ADD, RTC_ON); } \
__INLINE__ int __ALWAYS_INLINE__  EE_rtc_shutdown(void){ \
	return cat3(EE_, lc, _write_byte)(RTC_DEVICE_ID, RTC_CSR_ADD, RTC_OFF); } \
__INLINE__ int __ALWAYS_INLINE__  EE_rtc_write_byte(EE_UINT8 address, EE_UINT8 data){ \
	return cat3(EE_, lc, _write_byte)(RTC_DEVICE_ID, address, data); } \
__INLINE__ int __ALWAYS_INLINE__  EE_rtc_write_buffer(EE_UINT8 address, EE_UINT8 *data, int len){ \
	return cat3(EE_, lc, _write_buffer)(RTC_DEVICE_ID, address, data, len); } \
__INLINE__ int __ALWAYS_INLINE__  EE_rtc_read_byte(EE_UINT8 address){ \
	return cat3(EE_, lc, _read_byte)(RTC_DEVICE_ID, address); } \
__INLINE__ int __ALWAYS_INLINE__  EE_rtc_read_buffer(EE_UINT8 address, EE_UINT8 *data, int len){ \
	return cat3(EE_, lc, _read_buffer)(RTC_DEVICE_ID, address, data, len); }
	
#ifdef __EE_RTC_USE_I2C1__
#ifdef __EE_RTC_USE_I2C2__
#error RTC cannot support both i2c controllers
#endif

DECLARE_FUNC_RTC(EE_I2C1_NAME_UC, EE_I2C1_NAME_LC)

#else //__EE_RTC_USE_I2C1__

DECLARE_FUNC_RTC(EE_I2C2_NAME_UC, EE_I2C2_NAME_LC)

#endif //__EE_RTC_USE_I2C1__

/*
	__INLINE__ int __ALWAYS_INLINE__  EE_rtc_start(void)
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
//__INLINE__ int __ALWAYS_INLINE__  EE_rtc_start(void);

/*
	__INLINE__ int __ALWAYS_INLINE__  EE_rtc_shutdown(void)
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
//__INLINE__ int __ALWAYS_INLINE__  EE_rtc_shutdown(void);


/*
	__INLINE__ int __ALWAYS_INLINE__  EE_rtc_write_byte(EE_UINT8 address, EE_UINT8 data)
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
//__INLINE__ int __ALWAYS_INLINE__  EE_rtc_write_byte(EE_UINT8 address, EE_UINT8 data);

/*
	__INLINE__ int __ALWAYS_INLINE__  EE_rtc_write_buffer(EE_UINT8 address, EE_UINT8 *data, int len)
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
//__INLINE__ int __ALWAYS_INLINE__  EE_rtc_write_buffer(EE_UINT8 address, EE_UINT8 *data, int len)


/*
	__INLINE__ int __ALWAYS_INLINE__  EE_rtc_read_byte(EE_UINT8 address)
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
//__INLINE__ int __ALWAYS_INLINE__  EE_rtc_read_byte(EE_UINT8 address);


/*
	__INLINE__ int __ALWAYS_INLINE__  EE_rtc_read_buffer(EE_UINT8 address, EE_UINT8 *data, int len)
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
//__INLINE__ int __ALWAYS_INLINE__  EE_rtc_read_buffer(EE_UINT8 address, EE_UINT8 *data, int len);



/*
	int EE_rtc_write_time(const TTime *ttw)
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
	int EE_rtc_read_time(TTime *ttr) 
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


int EE_rtc_set_alarm(void);

/* Global variables */
//...

#endif //#ifndef __EE_RTC_PCF8583__

#endif //#ifdef __USE_MICO32BOARD_RTC__
