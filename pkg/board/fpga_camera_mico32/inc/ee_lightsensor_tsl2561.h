/*
  Name: ee_lightsensor_tsl2561.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.28
  Description: Light sensor driver header file.
*/

#ifndef __EE_LIGHTSENSOR_TSL2561__
#define __EE_LIGHTSENSOR_TSL2561__

#include "mcu/mico32/inc/ee_i2c.h"

/* Driver macros */
#define TLS2561_DEVICE_ID		(0x49<<1)
#define TLS2561_COMMAND_BIT     (0x80)
#define TLS2561_CLEAR_INT       (0x40)
#define TLS2561_WORD_PROT       (0x20)
#define TLS2561_BLOCK_PROT      (0x10)
#define TLS2561_WORD_COMMAND(x) (TLS2561_COMMAND_BIT | TLS2561_WORD_PROT | (x))
#define TLS2561_BLOCK_COMMAND(x) (TLS2561_COMMAND_BIT | TLS2561_BLOCK_PROT | (x))
#define TLS2561_BYTE_COMMAND(x) (TLS2561_COMMAND_BIT | (x))
#define TLS2561_REG_CONTROL     (0x0)
#define TLS2561_REG_DATA0LOW    (0xC)
#define TLS2561_REG_DATA0HIGH   (0xD)
#define TLS2561_REG_DATA0       (TLS2561_REG_DATA0LOW)
#define TLS2561_REG_DATA1LOW    (0xE)
#define TLS2561_REG_DATA1HIGH   (0xF)
#define TLS2561_REG_DATA1       (TLS2561_REG_DATA1LOW)
#define TLS2561_POWER_UP       	(0x03)
#define TLS2561_POWER_DOWN		(0x00)

/* Board dependent macros */
// void

/* Macros for User functions (API) */  
#define DECLARE_FUNC_I2C_LIGHTSENSOR(uc, lc) \
__INLINE__ int __ALWAYS_INLINE__  EE_lightsensor_i2c_config(int baudrate, int settings){ \
	return cat3(EE_, lc, _config)(baudrate, settings); } \
__INLINE__ int __ALWAYS_INLINE__  EE_lightsensor_write_byte(EE_UINT8 address, EE_UINT8 data){ \
	return cat3(EE_, lc, _send_byte)(TLS2561_DEVICE_ID, address, data); } \
__INLINE__ int __ALWAYS_INLINE__  EE_lightsensor_write_buffer(EE_UINT8 address, EE_UINT8 *data, int len){ \
	return cat3(EE_, lc, _send_buffer)(TLS2561_DEVICE_ID, address, data, len); } \
__INLINE__ int __ALWAYS_INLINE__  EE_lightsensor_read_byte(EE_UINT8 address){ \
	return cat3(EE_, lc, _receive_byte)(TLS2561_DEVICE_ID, address); } \
__INLINE__ int __ALWAYS_INLINE__  EE_lightsensor_read_buffer(EE_UINT8 address, EE_UINT8 *data, int len){ \
	return cat3(EE_, lc, _receive_buffer)(TLS2561_DEVICE_ID, address, data, len); }
	
DECLARE_FUNC_I2C_LIGHTSENSOR(CAMERA_I2C, camera_i2c)

__INLINE__ int __ALWAYS_INLINE__  EE_lightsensor_config(int baudrate, int settings);
__INLINE__ int __ALWAYS_INLINE__  EE_lightsensor_powerup(void);
__INLINE__ int __ALWAYS_INLINE__  EE_lightsensor_powerdown(void);

__INLINE__ int __ALWAYS_INLINE__  EE_lightsensor_config(int baudrate, int settings)
{
	EE_lightsensor_i2c_config(baudrate, settings);
	return EE_lightsensor_powerup();
}

__INLINE__ int __ALWAYS_INLINE__  EE_lightsensor_powerup(void)
{
	return EE_lightsensor_write_byte(TLS2561_BYTE_COMMAND(TLS2561_REG_CONTROL), TLS2561_POWER_UP);
}

__INLINE__ int __ALWAYS_INLINE__  EE_lightsensor_powerdown(void)
{
	return EE_lightsensor_write_byte(TLS2561_BYTE_COMMAND(TLS2561_REG_CONTROL), TLS2561_POWER_DOWN);
}

__INLINE__ int __ALWAYS_INLINE__  EE_lightsensor_read(void)
{
	EE_UINT8 buf[2];
	
	EE_lightsensor_read_buffer(TLS2561_WORD_COMMAND(TLS2561_REG_DATA0), buf, 2);

	return (buf[0] + buf[1] * 256);
}
	
/* Functions for Mirtes compatibility */
__INLINE__ void __ALWAYS_INLINE__ EE_analog_init( void )
{
	EE_lightsensor_config(100000, 0);
}
__INLINE__ void __ALWAYS_INLINE__ EE_analogsensors_init( void ) { EE_analog_init(); }

__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_analog_get_light( void )
{
	return EE_lightsensor_read();
}	
	
#endif //#ifndef __EE_LIGHTSENSOR_TSL2561__


