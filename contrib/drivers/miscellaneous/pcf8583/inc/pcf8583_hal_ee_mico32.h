/** 
* @file pcf8583_hal_ee_mico32.h
* @brief pcf8583 Real time clock Driver for Lattice Mico32
* @author Dario Di Stefano
* @date 2010-04-26
*
*/

#ifndef __PCF8583_HAL_EE_MICO32_H__
#define __PCF8583_HAL_EE_MICO32_H__

#include "pcf8583_reg.h"
#include "pcf8583_compiler.h"
#include "mcu/mico32/inc/ee_i2c.h"

#ifdef __XP2_CAMERA_BOARD__
#include "board/fpga_camera_mico32/inc/ee_internal.h"
#include "board/fpga_camera_mico32/inc/ee_rtc_pcf8583.h"
#else	/* NO board */
#error "MRF24J40_HAL: Board specification is required!"
#endif	//#ifdef __XP2_CAMERA_BOARD__

#ifndef __USE_I2C__
#error "PCF8583 HAL EE : The I2C module from MCU is required!"
#endif

/******************************************************************************/
/*				Inlinde Functions 			      */
/******************************************************************************/

COMPILER_INLINE void EE_rtc_hal_init(void)
{
    cat3_ind(EE_, EE_RTC_I2C_LC, _config)(100000, 0);
}

COMPILER_INLINE void EE_rtc_hal_config(uint32_t baudrate, uint32_t settings)
{
    cat3_ind(EE_, EE_RTC_I2C_LC, _config)(baudrate, settings);
}

COMPILER_INLINE void EE_rtc_hal_start(void)
{
    cat3_ind(EE_, EE_RTC_I2C_LC, _send_byte)(RTC_DEVICE_ID, RTC_CSR_ADD, RTC_ON);
}

COMPILER_INLINE void EE_rtc_hal_shutdown(void)
{
    cat3_ind(EE_, EE_RTC_I2C_LC, _send_byte)(RTC_DEVICE_ID, RTC_CSR_ADD, RTC_OFF);
}

COMPILER_INLINE void EE_rtc_hal_write_byte(uint8_t address, uint8_t data)
{
    cat3_ind(EE_, EE_RTC_I2C_LC, _send_byte)(RTC_DEVICE_ID, address, data);
}

COMPILER_INLINE void EE_rtc_hal_write_buffer(uint8_t address, const uint8_t *data, uint32_t len)
{
    cat3_ind(EE_, EE_RTC_I2C_LC, _send_buffer)(RTC_DEVICE_ID, address, data, len);
}

COMPILER_INLINE int EE_rtc_hal_read_byte(uint8_t address)
{
    return cat3_ind(EE_, EE_RTC_I2C_LC, _receive_byte)(RTC_DEVICE_ID, address);
}

COMPILER_INLINE void EE_rtc_hal_read_buffer(uint8_t address, uint8_t *data, uint32_t len)
{
    cat3_ind(EE_, EE_RTC_I2C_LC, _receive_buffer)(RTC_DEVICE_ID, address, data, len);
}


#endif //__PCF8583_HAL_EE_MICO32_H__

