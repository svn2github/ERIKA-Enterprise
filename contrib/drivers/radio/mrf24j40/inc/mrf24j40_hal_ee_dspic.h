/** 
* @file mrf24j40_hal_.h
* @brief MRF24J40 Hw Abstraction Layer using Erika OS
* @author Gianluca Franchino
* @author Christian Nastasi
* @author Mauro Nino Marinoni
* @date 2009-03-24
*
* This file is the definition of the hardware abstraction layer used by all the module
* of the MRF24J40 library which uses the Erika kernel drivers. 
*
* \todo Write something about the hal support.
*/

// TODO: Check radio pins.

#ifndef __mrf24j40_hal_ee_dspic_h__
#define __mrf24j40_hal_ee_dspic_h__

#ifndef __USE_SPI__
#error "MRF24J40 HAL EE : The SPI module from MCU is required!"
#endif
#include <mcu/microchip_dspic/inc/ee_spi.h>

#define MRF24J40_SPI_PORT_1	EE_SPI_PORT_1
#define MRF24J40_SPI_PORT_2	EE_SPI_PORT_2

#ifndef MRF24J40_RESETn
#define MRF24J40_RESETn		PORTGbits.RG0
#endif

#ifndef MRF24J40_VREG_EN
#define MRF24J40_VREG_EN		PORTGbits.RG12
#endif

#ifndef MRF24J40_FIFO
#ifdef __USE_DEMOBOARD__	/* Demoboard defaults */
#define MRF24J40_FIFO		PORTDbits.RD14
#else				/* Gianluca's board default*/
#define MRF24J40_FIFO		PORTEbits.RE9
#endif
#endif

#ifndef MRF24J40_FIFOP
#ifdef __USE_DEMOBOARD__	/* Demoboard defaults */
#define MRF24J40_FIFOP		PORTAbits.RA15
#else				/* Gianluca's board default*/
#define MRF24J40_FIFOP		PORTFbits.RF6
#endif
#endif

#ifndef MRF24J40_CSn
#define MRF24J40_CSn		PORTGbits.RG9
#endif

#ifndef MRF24J40_TRIS_RESETn
#define MRF24J40_TRIS_RESETn	TRISGbits.TRISG0
#endif

#ifndef MRF24J40_TRIS_VREG_EN
#define MRF24J40_TRIS_VREG_EN	TRISGbits.TRISG12
#endif

#ifndef MRF24J40_TRIS_FIFO
#ifdef __USE_DEMOBOARD__	/* Demoboard defaults */
#define MRF24J40_TRIS_FIFO	TRISDbits.TRISD14
#else				/* Gianluca's board default*/
#define MRF24J40_TRIS_FIFO	TRISEbits.TRISE9
#endif
#endif

#ifndef MRF24J40_TRIS_FIFOP
#ifdef __USE_DEMOBOARD__	/* Demoboard defaults */
#define MRF24J40_TRIS_FIFOP	TRISAbits.TRISA15
#else				/* Gianluca's board default*/
#define MRF24J40_TRIS_FIFOP	TRISFbits.TRISF6
#endif
#endif

#ifndef MRF24J40_TRIS_CSn
#define MRF24J40_TRIS_CSn		TRISGbits.TRISG9
#endif

#ifdef __USE_DEMOBOARD__	/* Demoboard defaults */

#ifndef MRF24J40_INTERRUPT_NAME	
#define MRF24J40_INTERRUPT_NAME	_INT4Interrupt
#endif

#ifndef MRF24J40_INTERRUPT_FLAG	
#define MRF24J40_INTERRUPT_FLAG	IFS3bits.INT4IF
#endif

#ifndef MRF24J40_INTERRUPT_ENABLE
#define MRF24J40_INTERRUPT_ENABLE IEC3bits.INT4IE
#endif

#ifndef MRF24J40_INTERRUPT_PRIORITY
#define MRF24J40_INTERRUPT_PRIORITY IPC13bits.INT4IP
#endif

#ifndef MRF24J40_INTERRUPT_EDGE_POLARITY	
#define MRF24J40_INTERRUPT_EDGE_POLARITY	 INTCON2bits.INT4EP
#endif

#else				/* Gianluca's board default*/

#ifndef MRF24J40_INTERRUPT_NAME	
#define MRF24J40_INTERRUPT_NAME	_INT0Interrupt
#endif

#ifndef MRF24J40_INTERRUPT_FLAG	
#define MRF24J40_INTERRUPT_FLAG	IFS0bits.INT0IF
#endif

#ifndef MRF24J40_INTERRUPT_ENABLE
#define MRF24J40_INTERRUPT_ENABLE IEC0bits.INT0IE
#endif

#ifndef MRF24J40_INTERRUPT_PRIORITY
#define MRF24J40_INTERRUPT_PRIORITY IPC0bits.INT0IP
#endif

#ifndef MRF24J40_INTERRUPT_EDGE_POLARITY	
#define MRF24J40_INTERRUPT_EDGE_POLARITY	 INTCON2bits.INT0EP
#endif

#endif	/* End default booard selection for ISR */

int8_t	mrf24j40_hal_init(void);
void	mrf24j40_delay_us(uint16_t delay_count); 
int8_t	mrf24j40_spi_init(uint8_t port);
int8_t	mrf24j40_spi_close(void);
int8_t	mrf24j40_spi_put(uint8_t in, uint8_t *out);
int8_t	mrf24j40_spi_get(uint8_t *out);

#endif /* Header Protection */
