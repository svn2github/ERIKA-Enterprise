#include "mcu/microchip_pic32/inc/ee_spi.h"

__INLINE__ void init_port_1(EE_UINT16 spibrg, EE_UINT16 flags)
{
	int rData; // chris: FIXME: is the regi cleaning required?

	IEC0CLR = _IEC0_SPI1EIE_MASK | _IEC0_SPI1TXIE_MASK | 
		  _IEC0_SPI1RXIE_MASK;
	SPI1CON = 0;
	rData = SPI1BUF; 	/* Clears the receive buffer */	
	SPI1BRG = spibrg; 	
	SPI1STATCLR = _SPI1STAT_SPIROV_MASK; 
	SPI1CON = _SPI1CON_MSTEN_MASK | _SPI2CON_CKE_MASK | _SPI1CON_ON_MASK;
}

__INLINE__ void init_port_2(EE_UINT16 spibrg, EE_UINT16 flags)
{
	int rData; // chris: FIXME: is the regi cleaning required?

	IEC1CLR = _IEC1_SPI2EIE_MASK | _IEC1_SPI2TXIE_MASK | 
		  _IEC1_SPI2RXIE_MASK;
	SPI2CON = 0;
	rData = SPI2BUF; 
	SPI2BRG = spibrg; 	
			
	SPI2STATCLR = _SPI2STAT_SPIROV_MASK; 
	
	SPI2CON = _SPI2CON_MSTEN_MASK |_SPI2CON_ON_MASK |_SPI2CON_CKE_MASK;
								//0x8120;		 			
}

EE_INT8 EE_spi_init(EE_UINT8 port/*, EE_UINT32 baudrate, EE_UINT16 flags*/) 
{
	if (port == EE_SPI_PORT_1) {
		init_port_1(0x4, 0); //Bibo: FCLK_SPI = Fpb/(SPIBRG+1) = 8 Mhz
		return EE_SPI_NO_ERRORS;
	} else if (port == EE_SPI_PORT_2) {
		init_port_2(0x4, 0); //Bibo: FCLK_SPI = Fpb/(SPIBRG+1) = 8 Mhz
		return EE_SPI_NO_ERRORS;
	}
	return -EE_SPI_ERR_BAD_PORT;
}



EE_INT8 EE_spi_close(EE_UINT8 port)
{
	if (port == EE_SPI_PORT_1) {
		SPI1CONCLR= _SPI1CON_ON_MASK;
		return EE_SPI_NO_ERRORS;
	} else if (port == EE_SPI_PORT_2) {
		SPI2CONCLR= _SPI2CON_ON_MASK;
		return EE_SPI_NO_ERRORS;
	}
	return -EE_SPI_ERR_BAD_PORT;
}


EE_INT8 EE_spi_rw_byte(EE_UINT8 port, EE_UINT8 data_in, EE_UINT8 *data_out)
{
	/* NOTE: Current implementation makes use of polling mode. 
	 * Moreover this might lead to deadlock condition if the bus is not 
	 * working properly.
	*/
	if (port == EE_SPI_PORT_1) {
		SPI1STATCLR = _SPI1STAT_SPIROV_MASK; 
   		while (!SPI1STATbits.SPITBE); 
   		SPI1BUF = data_in;
   		while (!SPI1STATbits.SPIRBF);
		SPI1STATCLR = _SPI1STAT_SPIROV_MASK; 
		*data_out = SPI1BUF & 0x00FF;
   		return EE_SPI_NO_ERRORS;
	} else if (port == EE_SPI_PORT_2) {
		SPI2STATCLR = _SPI2STAT_SPIROV_MASK; 
   		while (!SPI2STATbits.SPITBE); 
   		SPI2BUF = data_in;
   		while (!SPI2STATbits.SPIRBF);
		SPI2STATCLR = _SPI2STAT_SPIROV_MASK; 
		*data_out = SPI2BUF & 0x00FF;
   		return EE_SPI_NO_ERRORS;
   	}
	return -EE_SPI_ERR_BAD_PORT;
}

