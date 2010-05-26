/*
  Name: ee_i2c_pic32like.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.28
  Description: I2C driver functions for compatibility with pic32 projects. 
*/

#ifndef __INCLUDE_EEMCUMICO32_I2C_PIC32LIKE_H__
#define __INCLUDE_EEMCUMICO32_I2C_PIC32LIKE_H__

/* ------------------------------------------------ */
/* Macros for compatibility with pic32 i2c driver*/ 
/* ------------------------------------------------ */

#define EE_mchp_i2c_init(uc, baud, flags) EE_hal_i2c_config((OCI2CMDev_t*)EE_BASE_ADD(uc), baud, flags)
#define EE_mchp_i2c_idle(uc) EE_hal_i2c_idle((OCI2CMDev_t*)EE_BASE_ADD(uc))
#define EE_mchp_i2c_read_byte(uc, device, address) EE_hal_i2c_read_byte_polling((OCI2CMDev_t*)EE_BASE_ADD(uc), device, address)
#define EE_mchp_i2c_write_byte(uc, device, address, data) EE_hal_i2c_write_byte_polling((OCI2CMDev_t*)EE_BASE_ADD(uc), device, address, data)	

__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_i2c_init(EE_UINT8 port, EE_UINT16 baudrate, EE_UINT16 flags)
{
	EE_INT8 ret;
	
	#if defined(EE_I2C1_NAME_UC) && defined(EE_I2C2_NAME_UC)
	if(port==1)
		ret = EE_mchp_i2c_init(EE_I2C1_NAME_UC, baudrate, flags);
	else
		ret = EE_mchp_i2c_init(EE_I2C2_NAME_UC, baudrate, flags);
	#else
		#if defined(EE_I2C1_NAME_UC)
		ret = EE_mchp_i2c_init(EE_I2C1_NAME_UC, baudrate, flags);
		#else
		ret = EE_mchp_i2c_init(EE_I2C2_NAME_UC, baudrate, flags);
		#endif
	#endif
		
	return ret;
}

__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_i2c_idle(EE_UINT8 port)
{
	EE_INT8 ret;
	
	#if defined(EE_I2C1_NAME_UC) && defined(EE_I2C2_NAME_UC)
	if(port==1)
		ret = EE_mchp_i2c_idle(EE_I2C1_NAME_UC);
	else
		ret = EE_mchp_i2c_idle(EE_I2C2_NAME_UC);
	#else
		#if defined(EE_I2C1_NAME_UC)
		ret = EE_mchp_i2c_idle(EE_I2C1_NAME_UC);
		#else
		ret = EE_mchp_i2c_idle(EE_I2C2_NAME_UC);
		#endif
	#endif
		
	return ret;
}

__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_i2c_read_byte(EE_UINT8 port, EE_UINT8 device, EE_UINT8 address, EE_UINT8 *data)
{
	EE_INT8 ret;
	
	#if defined(EE_I2C1_NAME_UC) && defined(EE_I2C2_NAME_UC)
	if(port==1)
		ret = EE_mchp_i2c_read_byte(EE_I2C1_NAME_UC, device, address);
	else
		ret = EE_mchp_i2c_read_byte(EE_I2C2_NAME_UC, device, address);
	#else
		#if defined(EE_I2C1_NAME_UC)
		ret = EE_mchp_i2c_read_byte(EE_I2C1_NAME_UC, device, address);
		#else
		ret = EE_mchp_i2c_read_byte(EE_I2C2_NAME_UC, device, address);
		#endif
	#endif
		
	*data = (EE_UINT8)ret;
		
	return ret;

}

__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_i2c_write_byte(EE_UINT8 port, EE_UINT8 device, EE_UINT8 address, EE_UINT8 data)
{
	EE_INT8 ret;
	
	#if defined(EE_I2C1_NAME_UC) && defined(EE_I2C2_NAME_UC)
	if(port==1)
		ret = EE_mchp_i2c_write_byte(EE_I2C1_NAME_UC, device, address, data);
	else
		ret = EE_mchp_i2c_write_byte(EE_I2C2_NAME_UC, device, address, data);
	#else
		#if defined(EE_I2C1_NAME_UC)
		ret = EE_mchp_i2c_write_byte(EE_I2C1_NAME_UC, device, address, data);
		#else
		ret = EE_mchp_i2c_write_byte(EE_I2C2_NAME_UC, device, address, data);
		#endif
	#endif
		
	return ret;

}

#endif //__INCLUDE_EEMCUMICO32_I2C_PIC32LIKE_H__
