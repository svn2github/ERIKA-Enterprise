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
#include <ee.h>
#include <mcu/microchip_pic32/inc/ee_spi.h>

#define MRF24J40_SPI_PORT_1	EE_SPI_PORT_1
#define MRF24J40_SPI_PORT_2	EE_SPI_PORT_2

/* ------------------------------ Pin Mapping ------------------------------- */
#ifndef MRF24J40_RESETn
#define MRF24J40_RESETn		PORTFbits.RF1
#endif

#ifndef MRF24J40_INT
#define MRF24J40_INT		PORTAbits.RA14
#endif

#ifndef MRF24J40_CSn
#define MRF24J40_CSn		PORTAbits.RA15
#endif

#ifndef MRF24J40_VREG_EN
#define MRF24J40_VREG_EN   	PORTGbits.RG15
#endif

/* ---------------------------- Pin Tri-States ------------------------------ */
#ifndef MRF24J40_TRIS_RESETn
#define MRF24J40_TRIS_RESETn	TRISFbits.TRISF1
#endif

#ifndef MRF24J40_TRIS_INT
#define MRF24J40_TRIS_INT	TRISAbits.TRISA14
#endif

#ifndef MRF24J40_TRIS_CSn
#define MRF24J40_TRIS_CSn	TRISAbits.TRISA15
#endif

#ifndef MRF24J40_TRIS_VREG_EN
#define MRF24J40_TRIS_VREG_EN   TRISGbits.TRISG15
#endif

/* --------------------------- IRQ Type Selection --------------------------- */

#ifdef MRF24J40_IRQ_EE_CN	/* IRQ type is Change Notification (EE_CN) */

#define MRF24J40_HAL_ISR() 		 EE_CN_HANDLER(mrf24j40_cn_isr)
#define MRF24J40_INTERRUPT_FLAG_CLR()		
#define MRF24J40_INTERRUPT_ENABLE_SET()	 EE_cn_enable(mrf24j40_cn_isr)
#define MRF24J40_INTERRUPT_ENABLE_CLR()	 EE_cn_disable(mrf24j40_cn_isr)
#define MRF24J40_INTERRUPT_ENABLE_STAT() EE_cn_status(mrf24j40_cn_isr)
#define MRF24J40_INTERRUPT_INIT(p, s)	 EE_cn_init(p, s)

#else				/* IRQ type is External Interrupt */

#ifndef MRF24J40_INTERRUPT_NAME	
#define MRF24J40_INTERRUPT_NAME			_EXTERNAL_3_VECTOR
#endif
#ifndef MRF24J40_INTERRUPT_FLAG	
#define MRF24J40_INTERRUPT_FLAG			IFS0bits.INT3IF
#endif
#ifndef MRF24J40_INTERRUPT_ENABLE
#define MRF24J40_INTERRUPT_ENABLE 		IEC0bits.INT3IE
#endif
#ifndef MRF24J40_INTERRUPT_PRIORITY
#define MRF24J40_INTERRUPT_PRIORITY	 	IPC3bits.INT3IP
#endif
#ifndef MRF24J40_INTERRUPT_SUBPRIORITY
#define MRF24J40_INTERRUPT_SUBPRIORITY 		IPC3bits.INT3IS
#endif
#ifndef MRF24J40_INTERRUPT_EDGE_POLARITY	
#define MRF24J40_INTERRUPT_EDGE_POLARITY	 INTCONbits.INT3EP
#endif

#define MRF24J40_HAL_ISR() 		 ISR2(MRF24J40_INTERRUPT_NAME)
#define MRF24J40_INTERRUPT_FLAG_CLR()	 MRF24J40_INTERRUPT_FLAG = 0
#define MRF24J40_INTERRUPT_ENABLE_SET()	 MRF24J40_INTERRUPT_ENABLE = 1
#define MRF24J40_INTERRUPT_ENABLE_CLR()	 MRF24J40_INTERRUPT_ENABLE = 0
#define MRF24J40_INTERRUPT_ENABLE_STAT() MRF24J40_INTERRUPT_ENABLE
#define MRF24J40_INTERRUPT_INIT(p, s)		\
do {						\
	MRF24J40_INTERRUPT_PRIORITY = p;	\
	MRF24J40_INTERRUPT_SUBPRIORITY = s;	\
	MRF24J40_INTERRUPT_EDGE_POLARITY = 0;	\
} while (0)					

#endif /* IRQ Type Selection */

/* ------------------------------ HAL APIs ---------------------------------- */

int8_t	mrf24j40_hal_init(void);
void	mrf24j40_hal_delay_us(uint16_t delay_count); 
int8_t	mrf24j40_hal_spi_init(uint8_t port);
int8_t	mrf24j40_hal_spi_close(void);
int8_t	mrf24j40_hal_spi_write(uint8_t *data, uint16_t len);
int8_t	mrf24j40_hal_spi_read(uint8_t *data, uint16_t len);

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

COMPILER_INLINE void mrf24j40_hal_irq_init(void)
{
	MRF24J40_INTERRUPT_INIT(6, 3);
}

COMPILER_INLINE void mrf24j40_hal_irq_clean(void)
{
	MRF24J40_INTERRUPT_FLAG_CLR();
}

COMPILER_INLINE void mrf24j40_hal_irq_enable(void)
{
	MRF24J40_INTERRUPT_ENABLE_SET();
}

COMPILER_INLINE void mrf24j40_hal_irq_disable(void)
{
	MRF24J40_INTERRUPT_ENABLE_CLR();
}

COMPILER_INLINE uint8_t mrf24j40_hal_irq_status(void)
{
	return MRF24J40_INTERRUPT_ENABLE_STAT();
}

#endif /* Header Protection */
