/** 
* @file pcf8583_reg.h
* @brief PCF8583 real time clock Driver
* @author Dario Di Stefano 
* @date 2010-08-30
*/

#ifndef __PCF8583_REG_H__
#define __PCF8583_REG_H__

/******************************************************************************/
/*				Registers Definition 			      */
/******************************************************************************/

/*	Slave device addresses		*/
#define RTC_DEVICE_ID      		(0xA0)

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

#endif // __PCF8583_REG_H___
