/** 
* @file tsl2561t_hal_ee_mico32.c
* @brief TSL2561T Light Sensor Driver for Lattice Mico32
* @author Dario Di Stefano
* @date 2010-04-26
*
*/

#include "tsl2561t.h"
#include "tsl2561t_hal_ee_mico32.h"

EE_UINT8 tsl2561t_hal_i2c_init(void) {

	if( EE_lightsensor_i2c_config(TSL2561T_I2C_CLK*1000, TSL2561T_I2C_FLAGS) == EE_I2C_OK )	
		return TSL2516T_NO_ERROR;
	return -TSL2516T_I2C_INIT_ERROR;
}

/* Mirtes */
void EE_analog_init(void)
{
	tsl2561t_init(SELECT_ADDRESS_VDD);
	tsl2561t_power_on(DEVICE_ADDRESS_VDD);
	tsl2561t_set_configuration(DEVICE_ADDRESS_VDD, TSL2561T_TIMING, 0); 
}

EE_UINT32 EE_analog_get_light( void )
{
	uint32_t lux;
	tsl2561t_read_lux(DEVICE_ADDRESS_VDD, &lux);
	return lux;
}
