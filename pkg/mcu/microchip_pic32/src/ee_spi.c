#include "mcu/microchip_pic32/inc/ee_spi.h"

EE_INT8 EE_spi_init(EE_UINT8 port)
{
	/* Enable SPI internal clock
	 * Enable 8 bits communication mode
	 * Enable Master Mode
	 * Note: with these prescale values the port works at 5 MHz. 
	*/
	int rData; // chris: FIXME: is the regi cleaning required?
	if (port == EE_SPI_PORT_1) {
		IEC0CLR = _IEC0_SPI1EIE_MASK | _IEC0_SPI1TXIE_MASK | 
			  _IEC0_SPI1RXIE_MASK;
		SPI1CON = 0; 		
		rData = SPI1BUF; 	/* Clears the receive buffer */	
		SPI1BRG = 0x1; 	// TODO: change this hard-coding.
				//Bibo: FCLK_SPI = Fpb/(SPIBRG+1) = 9 Mhz
		SPI1STATCLR = _SPI1STAT_SPIROV_MASK; 
		SPI1CON = _SPI1CON_MSTEN_MASK | _SPI1CON_SMP_MASK |
			  _SPI1CON_ON_MASK;
		return 1;
	} else if (port == EE_SPI_PORT_2) {
		IEC1CLR = _IEC1_SPI2EIE_MASK | _IEC1_SPI2TXIE_MASK | 
			  _IEC1_SPI2RXIE_MASK;
		SPI2CON = 0; 		
		TRISGCLR = 0x0140;
		TRISGSET = 0x0800;
		rData = SPI2BUF; 	/* Clears the receive buffer */
		SPI2BRG = 0x4; 	// TODO: change this hard-coding.
				//Bibo: FCLK_SPI = Fpb/(SPIBRG+1) = 9 Mhz
		SPI2STATCLR = _SPI2STAT_SPIROV_MASK; 
		/*@author BibO: trial modification SPI2CON = _SPI2CON_MSTEN_MASK | _SPI2CON_SMP_MASK |
			  _SPI2CON_ON_MASK; */
		SPI2CON = 0x8120;		 
		/*@author Bibo: end of modification */		
		return 1;
	}
	return -EE_SPI_ERR_BAD_PORT;
}

/* chris: TODO: Release something 
EE_INT8 EE_spi_close(EE_UINT8 port)
{
	if (port == EE_SPI_PORT_1) {
		return 1;
	} else if (port == EE_SPI_PORT_2) {
		return 1;
	}
	return -EE_SPI_ERR_BAD_PORT;
}
*/

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
   		return 1;
	} else if (port == EE_SPI_PORT_2) {
		SPI2STATCLR = _SPI2STAT_SPIROV_MASK; 
   		while (!SPI2STATbits.SPITBE); 
   		SPI2BUF = data_in;
   		while (!SPI2STATbits.SPIRBF);
		SPI2STATCLR = _SPI2STAT_SPIROV_MASK; 
		*data_out = SPI2BUF & 0x00FF;
   		return 1;
   	}
	return -EE_SPI_ERR_BAD_PORT;
}

