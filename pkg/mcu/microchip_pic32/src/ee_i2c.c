#include "mcu/microchip_pic32/inc/ee_i2c.h"
#include "ee_internal.h"
#include "cpu/pic32/inc/ee_irqstub.h"


/******************************************************************************/
/*			 Local variables 				      */
/******************************************************************************/

static EE_UINT8 i2c_HS_port1;
static EE_UINT8 i2c_HS_port2;


/******************************************************************************/
/* 			Inline functions 				      */
/******************************************************************************/


__INLINE__ void init_i2c_port_1(EE_UINT16 spibrg, EE_UINT16 flags) {
	/* Stop I2C port */
	I2C1CONbits.ON = 0;

	/* Disable Interrupts, due to master, slave and channel*/
	IEC0bits.I2C1MIE = 0;
	IEC0bits.I2C1SIE = 0;
	IEC0bits.I2C1BIE = 0; 

	/* Clear Interrupt flag bits */
	IFS0bits.I2C1SIF = 0;
	IFS0bits.I2C1MIF = 0;
	IFS0bits.I2C1BIF = 0; 

	/* Configre SCL/SDA pin as open-drain */
	ODCGbits.ODCG2=1;
	ODCGbits.ODCG3=1;
	
	/* Clear address and mask */
	I2C1ADD=0;
	I2C1MSK=0;

	/* Set baudrate */
	I2C1BRG = spibrg;	

	/* Configure I2C port */
	I2C1CON = 0;
	if (i2c_HS_port1)
		I2C1CONbits.DISSLW = 0; // Enable HS mode
	else
		I2C1CONbits.DISSLW = 1; // Disable HS mode
	

	I2C1CONbits.ACKDT = 1;	
			
	/* Start I2C port */
	I2C1CONbits.ON = 1;
}


__INLINE__ void init_i2c_port_2(EE_UINT16 spibrg, EE_UINT16 flags) {
	/*TODO: use the flags. */	
	/* Stop I2C port */
	I2C2CONbits.ON = 0;

	/* Disable Interrupts, due to master, slave and channel*/
	IEC1bits.I2C2MIE = 0;
	IEC1bits.I2C2SIE = 0;
	IEC1bits.I2C2BIE = 0;

	/* Clear Interrupt flag bits */
	IFS1bits.I2C2SIF = 0;
	IFS1bits.I2C2MIF = 0;
	IFS1bits.I2C2BIF = 0;

	/* Configre SCL/SDA pin as open-drain */
	ODCAbits.ODCA2=1;
	ODCAbits.ODCA3=1;
	
	/* Clear address and mask */
	I2C2ADD=0;
	I2C2MSK=0;

	/* Set baudrate */
	I2C2BRG = spibrg;

	/* Configure I2C port */
	I2C2CON = 0;
	I2C2CONbits.ACKDT = 1;
	if (i2c_HS_port2)
		I2C2CONbits.DISSLW = 0; // Enable HS mode
	else
		I2C2CONbits.DISSLW = 1; // Disable HS mode
	/* Start I2C port */
	I2C2CONbits.ON = 1;
}

/******************************************************************************/
/* 			Local functions 				      */
/******************************************************************************/

static EE_UINT8 i2c_write_port_1(EE_UINT8 device, EE_UINT8 address,
							EE_UINT8 data){
	
	unsigned int cto = 0;

	/* Ensure I2C module is idle */
	while(EE_i2c_idle(EE_I2C_PORT_1)) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Transmit a Start condition, initiate Start on SDA and SCL pins */
	I2C1CONbits.SEN = 1;		

	/* Wait till Start sequence is completed */
	while(I2C1CONbits.SEN) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}
	
	/* Write Slave address and set master for transmission 
	(R/W bit should be 0) */
	I2C1TRN = device;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -1;
	
	/* Wait till address is transmitted */
	while(I2C1STATbits.TBF) {
		if(++cto > CONNECTION_TIMEOUT)
			return  -EE_I2C_FAILURE;
	}

	/* Test for ACK condition received */
	while(I2C1STATbits.ACKSTAT) {
		if(++cto > CONNECTION_TIMEOUT)
			return  -EE_I2C_FAILURE;
	}

	/* Ensure I2C module is idle */
	while(EE_i2c_idle(EE_I2C_PORT_1)) {
		if(++cto > CONNECTION_TIMEOUT)
			return  -EE_I2C_FAILURE;
	}
	
	/* Write word address */
	I2C1TRN = address;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -1;

	/* Wait till address is transmitted */
	while(I2C1STATbits.TBF) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Test for ACK condition received */
	while(I2C1STATbits.ACKSTAT) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Ensure I2C module is idle */
	while(EE_i2c_idle(EE_I2C_PORT_1)) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	I2C1TRN = data;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -1;

	/* Wait till address is transmitted */
	while(I2C1STATbits.TBF) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Test for ACK condition received */
	while(I2C1STATbits.ACKSTAT) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Ensure I2C module is idle */
	while(EE_i2c_idle(EE_I2C_PORT_1)) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* send STOP condition */
	I2C1CONbits.PEN = 1;		// initiate Stop on SDA and SCL pins 

	/* Wait till Stop sequence is completed */
	while(I2C1CONbits.PEN) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Ensure I2C module is idle */
	while(EE_i2c_idle(EE_I2C_PORT_1)) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	return EE_I2C_SUCCESS;
}

static EE_UINT8 i2c_write_port_2(EE_UINT8 device, EE_UINT8 address, 
							EE_UINT8 data){

	unsigned int cto = 0;
	
	/* Ensure I2C module is idle */
	while(EE_i2c_idle(EE_I2C_PORT_2))  {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Transmit a Start condition */
	I2C2CONbits.SEN = 1;		// initiate Start on SDA and SCL pins
			
	/* Wait till Start sequence is completed */
	while(I2C2CONbits.SEN) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Write Slave address and set master for transmission 
	(R/W bit should be 0) */
	I2C2TRN = device;

	if(I2C2STATbits.IWCOL)		// If write collision occurs,return -1
		return -1;

	/* Wait till address is transmitted */
	while(I2C2STATbits.TBF) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Test for ACK condition received */
	while(I2C2STATbits.ACKSTAT)  {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Ensure I2C module is idle */
	while(EE_i2c_idle(EE_I2C_PORT_2))  {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Write word address */
	I2C2TRN = address;

	if(I2C2STATbits.IWCOL)		// If write collision occurs,return -1
		return -1;

	/* Wait till address is transmitted */
	while(I2C2STATbits.TBF)  {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Test for ACK condition received */
	while(I2C2STATbits.ACKSTAT) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Ensure I2C module is idle */
	while(EE_i2c_idle(EE_I2C_PORT_2)) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Write data byte to serial */
	I2C2TRN = data;
	if(I2C2STATbits.IWCOL)        // If write collision occurs,return -1
		return -1;

	/* Wait till address is transmitted */
	while(I2C2STATbits.TBF) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Test for ACK condition received */
	while(I2C2STATbits.ACKSTAT) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Ensure I2C module is idle */
	while(EE_i2c_idle(EE_I2C_PORT_2)) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}
	
	/* send STOP condition */
	I2C2CONbits.PEN = 1;		// initiate Stop on SDA and SCL pins
	
	/* Wait till Stop sequence is completed */
	while(I2C2CONbits.PEN) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Ensure I2C module is idle */
	while(EE_i2c_idle(EE_I2C_PORT_2)) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	return EE_I2C_SUCCESS;
}




static EE_INT8 i2c_read_port_1(EE_UINT8 device, EE_UINT8 address, EE_UINT8 *data){
	
	unsigned int cto = 0;
	

	/*  Ensure I2C module is idle */
	while(EE_i2c_idle(EE_I2C_PORT_1)) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}
	// Transmit a Start condition on i2c1
	I2C1CONbits.SEN = 1;		// initiate Start on SDA and SCL pins

	/*  Wait till Start sequence is completed */
	while(I2C1CONbits.SEN) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Write Slave address and set master for transmission  
	(R/W bit should be 0)*/            
	I2C1TRN = device;

	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -1;

	/* Wait till address is transmitted */
	while(I2C1STATbits.TBF) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Test for ACK condition received */
	while(I2C1STATbits.ACKSTAT) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Ensure I2C module is idle */
	while(EE_i2c_idle(EE_I2C_PORT_1)) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Write word address */
	I2C1TRN = address;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1                     
		return -1;

	/* Wait till address is transmitted */
	while(I2C1STATbits.TBF) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Test for ACK condition received */
	while(I2C1STATbits.ACKSTAT) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Ensure I2C module is idle */
	while(EE_i2c_idle(EE_I2C_PORT_1)) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Generate the I2C bus restart condition */
	I2C1CONbits.RSEN = 1;	// initiate restart on SDA and SCL pins

	/* Wait until re-start condition is over */
	while (I2C1CONbits.RSEN) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Write Slave address and set master for reception
	(R/W bit should be 1) */
	I2C1TRN = device+1;
	if(I2C1STATbits.IWCOL)	// If write collision occurs,return -1                      
		return -1;

	/* Wait till address is transmitted */
	while(I2C1STATbits.TBF) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Test for ACK condition received */
	while(I2C1STATbits.ACKSTAT) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Ensure I2C module is idle */
	while(EE_i2c_idle(EE_I2C_PORT_1)) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Read the data byte */
	I2C1CONbits.RCEN = 1;
	while(I2C1CONbits.RCEN);
	I2C1STATbits.I2COV = 0;
	*data = I2C1RCV & 0xFF;

	/* Ensure I2C module is idle */
	while(EE_i2c_idle(EE_I2C_PORT_1)) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* send NACK condition back to the I2C slave indicating master received 
	the data byte */
	I2C1CONbits.ACKDT = 1;
	I2C1CONbits.ACKEN = 1;

	/* wait until NACK sequence is over */
	while (I2C1CONbits.ACKEN) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Ensure I2C module is idle */
	while(EE_i2c_idle(EE_I2C_PORT_1)) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* send STOP condition */
	I2C1CONbits.PEN = 1;		// initiate Stop on SDA and SCL pins

	/* Wait till Stop sequence is completed */
	while(I2C1CONbits.PEN) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Ensure I2C module is idle */
	while(EE_i2c_idle(EE_I2C_PORT_1)) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}
	
	return EE_I2C_SUCCESS;			// return with data
}

static EE_INT8 i2c_read_port_2(EE_UINT8 device, EE_UINT8 address , EE_UINT8 *data){
	
	unsigned int cto = 0;

	/* Ensure I2C module is idle  */
	while(EE_i2c_idle(EE_I2C_PORT_2)){
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;

	}


	/* Transmit a Start condition on i2c2  */
	I2C2CONbits.SEN = 1;		// initiate Start on SDA and SCL pins
	
	/* Wait till Start sequence is completed  */
	while(I2C2CONbits.SEN) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;

	}

	/* Write Slave address and set master for transmission  
	(R/W bit should be 0)  */
        I2C2TRN = device;

	if(I2C2STATbits.IWCOL)	// If write collision occurs,return -1 
		return -1;

	/* Wait till address is transmitted */
	while(I2C2STATbits.TBF) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}
	
	/* Test for ACK condition received */
	while(I2C2STATbits.ACKSTAT) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	} 

	/* Ensure I2C module is idle */
	while(EE_i2c_idle(EE_I2C_PORT_2)) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;

	}

	/* Write word address */
	I2C2TRN = address;
	if(I2C2STATbits.IWCOL)		// If write collision occurs,return -1                     
		return -1;

	/* Wait till address is transmitted */
	while(I2C2STATbits.TBF) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Test for ACK condition received */
	while(I2C2STATbits.ACKSTAT) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}
		
	/* Ensure I2C module is idle */
	while(EE_i2c_idle(EE_I2C_PORT_2)) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Generate the I2C bus restart condition */
	I2C2CONbits.RSEN = 1;		// initiate restart on SDA and SCL pins

	/* Wait until re-start condition is over */
	while (I2C2CONbits.RSEN);

	/* Write Slave address and set master for reception 
						(R/W bit should be 1) */
	I2C2TRN = device+1;
	if(I2C2STATbits.IWCOL)		// If write collision occurs,return -1                      
		return -1;

	/* Wait till address is transmitted */
	while(I2C2STATbits.TBF) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Test for ACK condition received */
	while(I2C2STATbits.ACKSTAT) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Ensure I2C module is idle */
	while(EE_i2c_idle(EE_I2C_PORT_2)) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Read the data byte */
	I2C2CONbits.RCEN = 1;
	while(I2C2CONbits.RCEN) ;
	I2C2STATbits.I2COV = 0;
	*data = I2C2RCV & 0xFF;
	
	/* Ensure I2C module is idle */
	while(EE_i2c_idle(EE_I2C_PORT_2)) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}
	
	/* send NACK condition back to the I2C slave indicating master received 
	the data byte */
	I2C2CONbits.ACKDT = 1;
	I2C2CONbits.ACKEN = 1;

	/* wait until NACK sequence is over */
	while (I2C2CONbits.ACKEN)  {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* Ensure I2C module is idle */
	while(EE_i2c_idle(EE_I2C_PORT_2)) {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}

	/* send STOP condition */
	I2C2CONbits.PEN = 1;		// initiate Stop on SDA and SCL pins

	/* Wait till Stop sequence is completed */
	while(I2C2CONbits.PEN) ;

	/* Ensure I2C module is idle */
	while(EE_i2c_idle(EE_I2C_PORT_2))  {
		if(++cto > CONNECTION_TIMEOUT)
			return -EE_I2C_FAILURE;
	}
	
	return EE_I2C_SUCCESS;			// return with data
}

/******************************************************************************/
/*			Global Functions 				      */
/******************************************************************************/


/* 
 * EE_i2c_init initialize the channel.
 */

EE_INT8 EE_i2c_init(EE_UINT8 port, EE_UINT16 baudrate, EE_UINT16 flags)
{		
	if (port == EE_I2C_PORT_1) {
		switch (baudrate){
		case 100:
			i2c_HS_port1 = 0;
			init_i2c_port_1(DEFAULT_100KHZ_BRG, flags);
		/* default settings: clock @ 100 khz with peripheral clock 
					@ 40 Mhz, default ACK and no 
					interrupts */
		break;
		case 400:
			i2c_HS_port1 = 1;
			init_i2c_port_1(DEFAULT_400KHZ_BRG, flags);
		break;
		default:
			i2c_HS_port1 = 0;
			init_i2c_port_1(DEFAULT_100KHZ_BRG, DEFAULT_FLAGS);
		}
		return 1;
	} else if (port == EE_I2C_PORT_2) {
		/* default settings: clock @ 100 khz with peripheral clock 
					@ 40 Mhz, default ACK and no 
					interrupts */
		switch (baudrate){
		case 100:
			i2c_HS_port2 = 0;
			init_i2c_port_2(DEFAULT_100KHZ_BRG, flags);
		/* default settings: clock @ 100 khz with peripheral clock 
					@ 40 Mhz, default ACK and no 
					interrupts */
		break;
		case 400:
			i2c_HS_port2 = 1;
			init_i2c_port_2(DEFAULT_400KHZ_BRG, flags);
		break;
		default:
			i2c_HS_port2 = 0;
			init_i2c_port_2(DEFAULT_100KHZ_BRG, DEFAULT_FLAGS);
		}
		return EE_I2C_SUCCESS;
		
	}
	return -EE_I2C_ERR_BAD_PORT;
}

/* 
 * EE_i2c_idle verifies the state of the channel.
 */

EE_UINT8 EE_i2c_idle(EE_UINT8 port){
	if (port == EE_I2C_PORT_1) {
		return i2c_port1_idle();
	} else if (port == EE_I2C_PORT_2) {
		return i2c_port2_idle();
	}
	return -EE_I2C_ERR_BAD_PORT;
}


/* 
 * EE_i2c_read_byte calls the specific read function associated with each port
 * of the I2C to speed_up the communication task 
 */

EE_UINT8 EE_i2c_read_byte (EE_UINT8 port, EE_UINT8 device, EE_UINT8 address, 
							EE_UINT8 * data ){
	
	if (port == EE_I2C_PORT_1 )
		return i2c_read_port_1(device, address, data);
	else if (port == EE_I2C_PORT_2 )
		return i2c_read_port_2(device, address, data); 
	else
		return -EE_I2C_ERR_BAD_PORT;
}


/* EE_i2c_write_byte calls the specific write function associated with each 
 * port of the I2C to speed_up the communication task 
 */
EE_UINT8 EE_i2c_write_byte(EE_UINT8 port, EE_UINT8 device, EE_UINT8 address, 
			EE_UINT8 data) {
	if (port == EE_I2C_PORT_1 )
		return i2c_write_port_1(device, address, data);
	else if (port == EE_I2C_PORT_2 )
		return i2c_write_port_2(device, address, data);
	else
		return -EE_I2C_ERR_BAD_PORT;
}



