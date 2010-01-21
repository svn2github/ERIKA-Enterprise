/** 
* @file mrf24j40_hal_ee_pic32.h
* @brief MRF24J40 Hw Abstraction Layer using Erika OS over Microchip pic32
* @author Christian Nastasi
* @author Marco Ghibaudi
* @date 2010-01-12
*
* This file is the definition of the hardware abstraction layer 
* used by all the module
* of the MRF24J40 library which uses the Erika kernel drivers. 
*
* \todo Write something about the hal support.
*/


#ifndef __mrf24j40_hal_ee_pic32_h__
#define __mrf24j40_hal_ee_pic32_h__

#ifndef __USE_SPI__
#error "MRF24J40 HAL EE : The SPI module from MCU is required!"
#endif
#include <mcu/microchip_pic32/inc/ee_spi.h>

#define MRF24J40_SPI_PORT_1	EE_SPI_PORT_1
#define MRF24J40_SPI_PORT_2	EE_SPI_PORT_2

#ifndef MRF24J40_RESETn
#define MRF24J40_RESETn		PORTFbits.RF1
#endif

#define MRF24J40_VREG_EN   	PORTGbits.RG15


#ifndef MRF24J40_INT
#define MRF24J40_INT		PORTAbits.RA14
#endif

#ifndef MRF24J40_CSn
#define MRF24J40_CSn		PORTAbits.RA15
#endif

#ifndef MRF24J40_TRIS_RESETn
#define MRF24J40_TRIS_RESETn		TRISFbits.TRISF1
#endif

#define MRF24J40_TRIS_VREG_EN   TRISGbits.TRISG15



#ifndef MRF24J40_TRIS_INT
#define MRF24J40_TRIS_INT		TRISAbits.TRISA14
#endif

#ifndef MRF24J40_TRIS_CSn
#define MRF24J40_TRIS_CSn		TRISAbits.TRISA15
#endif

#ifndef MRF24J40_INTERRUPT_NAME	
#define MRF24J40_INTERRUPT_NAME		_EXTERNAL_3_VECTOR
#endif

#ifndef MRF24J40_INTERRUPT_FLAG	
#define MRF24J40_INTERRUPT_FLAG		IFS0bits.INT3IF
#endif

#ifndef MRF24J40_INTERRUPT_ENABLE
#define MRF24J40_INTERRUPT_ENABLE 	IEC0bits.INT3IE
#endif

#ifndef MRF24J40_INTERRUPT_PRIORITY
#define MRF24J40_INTERRUPT_PRIORITY 	IPC3bits.INT3IP
#endif

#ifndef MRF24J40_INTERRUPT_EDGE_POLARITY	
#define MRF24J40_INTERRUPT_EDGE_POLARITY	 INTCONbits.INT3EP
#endif

int8_t	mrf24j40_hal_init(void);
void	mrf24j40_delay_us(uint16_t delay_count); 
int8_t	mrf24j40_spi_init(uint8_t port);
int8_t	mrf24j40_spi_close(void);
int8_t	mrf24j40_spi_put(uint8_t in, uint8_t *out);
int8_t	mrf24j40_spi_get(uint8_t *out);

COMPILER_INLINE void mrf24j40_hal_retsetn_high(void)
{
	// chris: FIXME: This is due to the inverter of the elco v1 board!
	//MRF24J40_RESETn = 1;
	MRF24J40_RESETn = 0;
}

COMPILER_INLINE void mrf24j40_hal_retsetn_low(void)
{
	// chris: FIXME: This is due to the inverter of the elco v1 board!
	//MRF24J40_RESETn = 0;
	MRF24J40_RESETn = 1;
}

COMPILER_INLINE void mrf24j40_hal_csn_high(void)
{
	MRF24J40_CSn = 1;
}

COMPILER_INLINE void mrf24j40_hal_csn_low(void)
{
	MRF24J40_CSn = 0;
}

COMPILER_INLINE void mrf24j40_hal_irq_enable(void)
{
	MRF24J40_INTERRUPT_ENABLE = 1;
}

COMPILER_INLINE void mrf24j40_hal_irq_disable(void)
{
	MRF24J40_INTERRUPT_ENABLE = 0;
}

COMPILER_INLINE uint8_t mrf24j40_hal_irq_status(void)
{
	return MRF24J40_INTERRUPT_ENABLE;
}

#endif /* Header Protection */
