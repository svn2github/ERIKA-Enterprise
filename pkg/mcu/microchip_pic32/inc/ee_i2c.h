#ifndef __INCLUDE_MICROCHIP_PIC32_I2C_H__
#define __INCLUDE_MICROCHIP_PIC32_I2C_H__

#include "ee.h"

/*
#ifdef __PIC32_INCLUDE_REGS__
#include "ee_pic32regs.h"
#endif
*/
/******************************************************************************/
/*			I2C available speed values			      */
/******************************************************************************/

#define EE_I2C_100KHZ		100000
#define EE_I2C_400KHZ		400000


/******************************************************************************/
/*			I2C configuration paramaters			      */
/******************************************************************************/

#define EE_I2C_DEFAULT_FLAGS 	0x0
#define CONNECTION_TIMEOUT	2000 

/******************************************************************************/
/*			Returned Messages				      */
/******************************************************************************/

#define EE_I2C_SUCCESS		1 	//Used as positive
#define EE_I2C_FAILURE	 	1
#define EE_I2C_ERR_BAD_PORT 	2
#define EE_I2C_WRONG_SPEED 	2


/******************************************************************************/
/*			Port Definition			      		      */
/******************************************************************************/


#ifdef __32MX795F512L__

enum {
	EE_I2C_PORT_1  = 0,
	EE_I2C_PORT_1A,
	EE_I2C_PORT_2,
	EE_I2C_PORT_2A,
	EE_I2C_PORT_3A,
	EE_I2C_PORT_N,
};

#else //not defined __32MX795F512L__


enum {
	EE_I2C_PORT_1  = 0,
	EE_I2C_PORT_2,
	EE_I2C_PORT_N,
};

#endif


/******************************************************************************/
/*			Interrupt Flags and Enable Registers   		      */
/******************************************************************************/



#ifdef __32MX795F512L__

/* NOTE: The following registers have different names from the ones 
	 * written in the device manual, but they are taken from the 
	 * p32mx795f512l.h header file. If some problems in the next versions
	 * of the compiler will rise, substitute these registers with the
	 *right ones. */


/* 	Interrupt Enable registers	*/

#define	EE_I2C_PORT1_MASTER_INT_ENABLE 		IEC0bits.I2C1MIE
#define	EE_I2C_PORT1_SLAVE_INT_ENABLE 		IEC0bits.I2C1SIE
#define	EE_I2C_PORT1_BUS_INT_ENABLE 		IEC0bits.I2C1BIE

#define	EE_I2C_PORT1A_MASTER_INT_ENABLE 	IEC0bits.I2C1ATXIE
#define	EE_I2C_PORT1A_SLAVE_INT_ENABLE 		IEC0bits.I2C1ARXIE
#define	EE_I2C_PORT1A_BUS_INT_ENABLE 		IEC0bits.I2C1AEIE

#define	EE_I2C_PORT2_MASTER_INT_ENABLE 		IEC1bits.I2C2MIE
#define	EE_I2C_PORT2_SLAVE_INT_ENABLE 		IEC1bits.I2C2SIE
#define	EE_I2C_PORT2_BUS_INT_ENABLE 		IEC1bits.I2C2BIE

#define	EE_I2C_PORT2A_MASTER_INT_ENABLE 	IEC1bits.I2C2ATXIE
#define	EE_I2C_PORT2A_SLAVE_INT_ENABLE 		IEC1bits.I2C2ARXIE
#define	EE_I2C_PORT2A_BUS_INT_ENABLE 		IEC1bits.I2C2AEIE

#define	EE_I2C_PORT3A_MASTER_INT_ENABLE 	IEC1bits.I2C2ATXIE
#define	EE_I2C_PORT3A_SLAVE_INT_ENABLE 		IEC1bits.I2C3ARXIE
#define	EE_I2C_PORT3A_BUS_INT_ENABLE 		IEC1bits.I2C3AEIE



/* 	Interrupt Flag bits	*/

#define	EE_I2C_PORT1_MASTER_INT_FLAG 		IFS0bits.I2C1MIF
#define	EE_I2C_PORT1_SLAVE_INT_FLAG 		IFS0bits.I2C1SIF
#define	EE_I2C_PORT1_BUS_INT_FLAG 		IFS0bits.I2C1BIF

#define	EE_I2C_PORT1A_MASTER_INT_FLAG 		IFS0bits.I2C1AMIF
#define	EE_I2C_PORT1A_SLAVE_INT_FLAG 		IFS0bits.I2C1ASIF
#define	EE_I2C_PORT1A_BUS_INT_FLAG 		IFS0bits.I2C1ABIF

#define	EE_I2C_PORT2_MASTER_INT_FLAG 		IFS1bits.I2C2MIF
#define	EE_I2C_PORT2_SLAVE_INT_FLAG 		IFS1bits.I2C2SIF
#define	EE_I2C_PORT2_BUS_INT_FLAG 		IFS1bits.I2C2BIF 

#define	EE_I2C_PORT2A_MASTER_INT_FLAG 		IFS1bits.I2C2ATXIF
#define	EE_I2C_PORT2A_SLAVE_INT_FLAG 		IFS1bits.I2C2ARXIF
#define	EE_I2C_PORT2A_BUS_INT_FLAG 		IFS1bits.I2C2AEIF

#define	EE_I2C_PORT3A_MASTER_INT_FLAG 		IFS1bits.I2C3ATXIF
#define	EE_I2C_PORT3A_SLAVE_INT_FLAG 		IFS1bits.I2C3ARXIF
#define	EE_I2C_PORT3A_BUS_INT_FLAG 		IFS1bits.I2C3AEIF


#else //not defined __32MX795F512L__


/* 	Interrupt Enable registers	*/

#define	EE_I2C_PORT1_MASTER_INT_ENABLE 		IEC0bits.I2C1MIE
#define	EE_I2C_PORT1_SLAVE_INT_ENABLE 		IEC0bits.I2C1SIE
#define	EE_I2C_PORT1_BUS_INT_ENABLE 		IEC0bits.I2C1BIE

#define	EE_I2C_PORT2_MASTER_INT_ENABLE 		IEC1bits.I2C2MIE
#define	EE_I2C_PORT2_SLAVE_INT_ENABLE 		IEC1bits.I2C2SIE
#define	EE_I2C_PORT2_BUS_INT_ENABLE 		IEC1bits.I2C2BIE



/* 	Interrupt Flag bits	*/

#define	EE_I2C_PORT1_MASTER_INT_FLAG 		IFS0bits.I2C1MIF
#define	EE_I2C_PORT1_SLAVE_INT_FLAG 		IFS0bits.I2C1SIF
#define	EE_I2C_PORT1_BUS_INT_FLAG 		IFS0bits.I2C1BIF

#define	EE_I2C_PORT2_MASTER_INT_FLAG 		IFS1bits.I2C2MIF
#define	EE_I2C_PORT2_SLAVE_INT_FLAG 		IFS1bits.I2C2SIF
#define	EE_I2C_PORT2_BUS_INT_FLAG 		IFS1bits.I2C2BIF 


#endif


#define ACTIVE_WAIT_ON(eval) 	\
			do {	\
				cto = 0;	\
				while(eval){		\
					if(++cto == CONNECTION_TIMEOUT)	\
					return -EE_I2C_FAILURE; \
					}	\
			} while(0)	


#ifdef __32MX795F512L__
__INLINE__ EE_INT8 i2c_port1_idle(void){
	return I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || 
				I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT;
}

__INLINE__ EE_INT8 i2c_port1A_idle(void){
	return I2C1ACONbits.SEN || I2C1ACONbits.PEN || I2C1ACONbits.RCEN || 
				I2C1ACONbits.ACKEN || I2C1ASTATbits.TRSTAT;
}

__INLINE__ EE_INT8 i2c_port2_idle(void){
	return I2C2CONbits.SEN || I2C2CONbits.PEN || I2C2CONbits.RCEN || 
				I2C2CONbits.ACKEN || I2C2STATbits.TRSTAT;
}

__INLINE__ EE_INT8 i2c_port2A_idle(void){
	return I2C2ACONbits.SEN || I2C2ACONbits.PEN || I2C2ACONbits.RCEN || 
				I2C2ACONbits.ACKEN || I2C2ASTATbits.TRSTAT;
}

__INLINE__ EE_INT8 i2c_port3A_idle(void){
	return I2C3ACONbits.SEN || I2C3ACONbits.PEN || I2C3ACONbits.RCEN || 
				I2C3ACONbits.ACKEN || I2C3ASTATbits.TRSTAT;
}

#else //not defined __32MX795F512L__

__INLINE__ EE_INT8 i2c_port1_idle(void){
	return I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || 
				I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT;
}

__INLINE__ EE_INT8 i2c_port2_idle(void){
	return I2C2CONbits.SEN || I2C2CONbits.PEN || I2C2CONbits.RCEN || 
				I2C2CONbits.ACKEN || I2C2STATbits.TRSTAT;
}

#endif



EE_INT8 EE_i2c_init(EE_UINT8 port, EE_UINT32 baudrate, EE_UINT16 flags);

EE_INT8 EE_i2c_idle(EE_UINT8 port);

EE_INT8 EE_i2c_read_byte(EE_UINT8 port, EE_UINT8 device, EE_UINT8 address, 
							EE_UINT8 *data);

EE_INT8 EE_i2c_write_byte(EE_UINT8 port, EE_UINT8 device, EE_UINT8 address, 
			EE_UINT8 data);

#endif //__EE_I2C_H__
