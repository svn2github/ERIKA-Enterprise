/*
  Name: ee_lightsensor_tsl2561.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.28
  Description: Light sensor driver header file.
*/

#ifndef __EE_LIGHTSENSOR_XP2CAMERABOARD_TSL2561T__
#define __EE_LIGHTSENSOR_XP2CAMERABOARD_TSL2561T__

/* Board dependent macros */
#define EE_tsl2561t_board_set_address_gnd()
#define EE_tsl2561t_board_set_address_vdd()
#define EE_tsl2561t_board_set_address_float()
#define EE_tsl2561t_board_set_int_pin()

/* Macros for User functions (API) */  
#define EE_LIGHTSENSOR_I2C_UC CAMERA_I2C
#define EE_LIGHTSENSOR_I2C_LC camera_i2c
	
/* Functions for Mirtes compatibility */
void EE_analog_init(void);
#define EE_analogsensors_init() EE_analog_init()
EE_UINT32 EE_analog_get_light( void );
	
#endif //#ifndef __EE_LIGHTSENSOR_XP2CAMERABOARD_TSL2561T__


