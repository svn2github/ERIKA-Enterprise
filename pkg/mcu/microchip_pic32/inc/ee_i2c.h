
#ifndef __EE_I2C_H__
#define __EE_I2C_H__

#include "ee.h"

#ifdef __PIC32_INCLUDE_REGS__
#include "ee_pic32regs.h"
#endif


#define DEFAULT_100KHZ_BRG 0xC6 // Works @ 80 Mhz
#define DEFAULT_400KHZ_BRG 0x30 // Works @ 80 Mhz

#define DEFAULT_FLAGS 0x0
#define EE_I2C_ERR_BAD_PORT 1

#define EE_I2C_SUCCESS		1 	//Used as positive
#define EE_I2C_FAILURE	 	1


#define CONNECTION_TIMEOUT	2000 

enum {
	EE_I2C_PORT_1  = 0,
	EE_I2C_PORT_2,
	EE_I2C_PORT_N,
};



#define ACTIVE_WAIT_ON(eval) 	\
			do {	\
				cto = 0;	\
				while(eval){		\
					if(++cto == CONNECTION_TIMEOUT)	\
					return -EE_I2C_FAILURE; \
					}	\
			} while(0)	



__INLINE__ EE_INT8 i2c_port1_idle(void){
	return I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || 
				I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT;
}

__INLINE__ EE_INT8 i2c_port2_idle(void){
	return I2C2CONbits.SEN || I2C2CONbits.PEN || I2C2CONbits.RCEN || 
				I2C2CONbits.ACKEN || I2C2STATbits.TRSTAT;
}




EE_INT8 EE_i2c_init(EE_UINT8 port, EE_UINT16 baudrate, EE_UINT16 flags);

EE_INT8 EE_i2c_idle(EE_UINT8 port);

EE_INT8 EE_i2c_read_byte(EE_UINT8 port, EE_UINT8 device, EE_UINT8 address, 
							EE_UINT8 *data);

EE_INT8 EE_i2c_write_byte(EE_UINT8 port, EE_UINT8 device, EE_UINT8 address, 
			EE_UINT8 data);

#endif //__EE_I2C_H__
