/**
* @file cc2420_hal_.h
* @brief CC2420 Hw Abstraction Layer using Erika OS
* @author Gianluca Franchino
* @author Christian Nastasi
* @author Mauro Nino Marinoni
* @date 2009-03-24
*
* This file is the definition of the hardware abstraction layer used by all the module
* of the CC2420 library which uses the Erika kernel drivers.
*
* \todo Write something about the hal support.
*/
#ifndef __cc2420_hal_ee_h__
#define __cc2420_hal_ee_h__

#if defined __MICROCHIP_DSPIC30__

#ifndef __USE_SPI__
#error "CC2420 HAL EE : The SPI module from MCU is required!"
#endif
#include <mcu/microchip_dspic/inc/ee_spi.h>

#define CC2420_SPI_PORT_1	EE_SPI_PORT_1
#define CC2420_SPI_PORT_2	EE_SPI_PORT_2

#ifndef CC2420_RESETn
#define CC2420_RESETn		PORTGbits.RG0
#endif

#ifndef CC2420_VREG_EN
#define CC2420_VREG_EN		PORTGbits.RG12
#endif

#ifndef CC2420_FIFO
#ifdef __USE_DEMOBOARD__	/* Demoboard defaults */
#define CC2420_FIFO		PORTDbits.RD14
#else				/* Gianluca's board default*/
#define CC2420_FIFO		PORTEbits.RE9
#endif
#endif

#ifndef CC2420_FIFOP
#ifdef __USE_DEMOBOARD__	/* Demoboard defaults */
#define CC2420_FIFOP		PORTAbits.RA15
#else				/* Gianluca's board default*/
#define CC2420_FIFOP		PORTFbits.RF6
#endif
#endif

#ifndef CC2420_CCA
#define CC2420_CCA	PORTGbits.RG1
#endif

#ifndef CC2420_SFD
#define CC2420_SFD	PORTDbits.RD13
#endif

#ifndef CC2420_CSn
#define CC2420_CSn		PORTGbits.RG9
#endif

#ifndef CC2420_TRIS_RESETn
#define CC2420_TRIS_RESETn	TRISGbits.TRISG0
#endif

#ifndef CC2420_TRIS_VREG_EN
#define CC2420_TRIS_VREG_EN	TRISGbits.TRISG12
#endif

#ifndef CC2420_TRIS_FIFO
#ifdef __USE_DEMOBOARD__	/* Demoboard defaults */
#define CC2420_TRIS_FIFO	TRISDbits.TRISD14
#else				/* Gianluca's board default*/
#define CC2420_TRIS_FIFO	TRISEbits.TRISE9
#endif
#endif

#ifndef CC2420_TRIS_FIFOP
#ifdef __USE_DEMOBOARD__	/* Demoboard defaults */
#define CC2420_TRIS_FIFOP	TRISAbits.TRISA15
#else				/* Gianluca's board default*/
#define CC2420_TRIS_FIFOP	TRISFbits.TRISF6
#endif
#endif

#ifndef CC2420_TRIS_CCA
#define CC2420_TRIS_CCA	TRISGbits.TRISG1
#endif

#ifndef CC2420_TRIS_SFD
#define CC2420_TRIS_SFD	TRISDbits.TRISD13
#endif

#ifndef CC2420_TRIS_CSn
#define CC2420_TRIS_CSn		TRISGbits.TRISG9
#endif


#ifdef __USE_DEMOBOARD__	/* Demoboard defaults */

#ifndef CC2420_INTERRUPT_NAME
#define CC2420_INTERRUPT_NAME	_INT4Interrupt
#endif

#ifndef CC2420_INTERRUPT_FLAG
#define CC2420_INTERRUPT_FLAG	IFS3bits.INT4IF
#endif

#ifndef CC2420_INTERRUPT_ENABLE
#define CC2420_INTERRUPT_ENABLE IEC3bits.INT4IE
#endif

#ifndef CC2420_INTERRUPT_PRIORITY
#define CC2420_INTERRUPT_PRIORITY IPC13bits.INT4IP
#endif

#ifndef CC2420_INTERRUPT_EDGE_POLARITY
#define CC2420_INTERRUPT_EDGE_POLARITY	 INTCON2bits.INT4EP
#endif

#else				/* Gianluca's board default*/

#ifndef CC2420_INTERRUPT_NAME
#define CC2420_INTERRUPT_NAME	_INT0Interrupt
#endif

#ifndef CC2420_INTERRUPT_FLAG
#define CC2420_INTERRUPT_FLAG	IFS0bits.INT0IF
#endif

#ifndef CC2420_INTERRUPT_ENABLE
#define CC2420_INTERRUPT_ENABLE IEC0bits.INT0IE
#endif

#ifndef CC2420_INTERRUPT_PRIORITY
#define CC2420_INTERRUPT_PRIORITY IPC0bits.INT0IP
#endif

#ifndef CC2420_INTERRUPT_EDGE_POLARITY
#define CC2420_INTERRUPT_EDGE_POLARITY	 INTCON2bits.INT0EP
#endif

#endif	/* End default booard selection for ISR */

int8_t	cc2420_hal_init(void);
void	cc2420_delay_us(uint16_t delay_count);
int8_t	cc2420_spi_init(uint8_t port);
int8_t	cc2420_spi_close(void);
int8_t	cc2420_spi_put(uint8_t in, uint8_t *out);
int8_t	cc2420_spi_get(uint8_t *out);

COMPILER_INLINE uint8_t cc2420_get_cca(void)
{
	return CC2420_CCA;
}

COMPILER_INLINE uint8_t cc2420_get_sfd(void)
{
	return CC2420_SFD;
}

// TODO: (Nino) Check avr5 or atmega128?
#elif defined __AVR5__

#ifndef __USE_SPI__
#error "CC2420 HAL EE : The SPI module from MCU is required!"
#endif
#include <mcu/atmel_atmega128/inc/ee_spi.h>

#define CC2420_SPI_PORT_1	EE_SPI_PORT_1
#define CC2420_SPI_PORT_2	EE_SPI_PORT_2

// TODO: (Nino) Change from pic30 to avr5
#ifndef CC2420_RESETn
#define CC2420_RESETn		PORTGbits.RG0
#endif

#ifndef CC2420_VREG_EN
#define CC2420_VREG_EN		PORTGbits.RG12
#endif

#ifndef CC2420_FIFO
#define CC2420_FIFO		PORTDbits.RD14
#endif

#ifndef CC2420_FIFOP
#define CC2420_FIFOP		PORTAbits.RA15
#endif

#ifndef CC2420_CCA
#define CC2420_CCA	PORTGbits.RG1
#endif

#ifndef CC2420_SFD
#define CC2420_SFD	PORTDbits.RD13
#endif

#ifndef CC2420_CSn
#define CC2420_CSn		PORTGbits.RG9
#endif

#ifndef CC2420_TRIS_RESETn
#define CC2420_TRIS_RESETn	TRISGbits.TRISG0
#endif

#ifndef CC2420_TRIS_VREG_EN
#define CC2420_TRIS_VREG_EN	TRISGbits.TRISG12
#endif

#ifndef CC2420_TRIS_FIFO
#define CC2420_TRIS_FIFO	TRISDbits.TRISD14
#endif

#ifndef CC2420_TRIS_FIFOP
#define CC2420_TRIS_FIFOP	TRISAbits.TRISA15
#endif

#ifndef CC2420_TRIS_CCA
#define CC2420_TRIS_CCA	TRISGbits.TRISG1
#endif

#ifndef CC2420_TRIS_SFD
#define CC2420_TRIS_SFD	TRISDbits.TRISD13
#endif

#ifndef CC2420_TRIS_CSn
#define CC2420_TRIS_CSn		TRISGbits.TRISG9
#endif


#ifndef CC2420_INTERRUPT_NAME
#define CC2420_INTERRUPT_NAME	_INT4Interrupt
#endif

#ifndef CC2420_INTERRUPT_FLAG
#define CC2420_INTERRUPT_FLAG	IFS3bits.INT4IF
#endif

#ifndef CC2420_INTERRUPT_ENABLE
#define CC2420_INTERRUPT_ENABLE IEC3bits.INT4IE
#endif

#ifndef CC2420_INTERRUPT_PRIORITY
#define CC2420_INTERRUPT_PRIORITY IPC13bits.INT4IP
#endif

#ifndef CC2420_INTERRUPT_EDGE_POLARITY
#define CC2420_INTERRUPT_EDGE_POLARITY	 INTCON2bits.INT4EP
#endif


int8_t	cc2420_hal_init(void);
void	cc2420_delay_us(uint16_t delay_count);
int8_t	cc2420_spi_init(uint8_t port);
int8_t	cc2420_spi_close(void);
int8_t	cc2420_spi_put(uint8_t in, uint8_t *out);
int8_t	cc2420_spi_get(uint8_t *out);

COMPILER_INLINE uint8_t cc2420_get_cca(void)
{
	return CC2420_CCA;
}

COMPILER_INLINE uint8_t cc2420_get_sfd(void)
{
	return CC2420_SFD;
}


#else

#error "CC2420_HAL: Architecture not supported!"

#endif

#endif /* Header Protection */
