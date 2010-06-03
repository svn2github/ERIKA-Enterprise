/*
  Name: mrf24j40_hal_ee_mico32.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: mico32 internal functions for u-wireless (zigbee) protocol
*/

#ifndef __mrf24j40_hal_ee_mico32_h__
#define __mrf24j40_hal_ee_mico32_h__

#include "cpu/mico32/inc/ee_internal.h"
#include "mcu/mico32/inc/ee_internal.h"
#include "board/fpga_camera_mico32/inc/ee_internal.h"
#include <cpu/mico32/inc/ee_irq.h>
#include "mcu/mico32/inc/ee_spi.h"
#include "mcu/mico32/inc/ee_gpio.h"
#include "MicoUtils.h"

#ifdef __XP2_CAMERA_BOARD__
#include "board/fpga_camera_mico32/inc/ee_zigbee_mrf24j40.h"
#else	/* NO board */
#error "MRF24J40_HAL: No board selected!"
#endif	//#ifdef __XP2_CAMERA_BOARD__

#ifndef __USE_SPI__
#error "MRF24J40 HAL EE : The SPI module is required!"
#endif // __USE_SPI__

#ifndef INT_POLARITY_HIGH
#error "mrf24j40 int polarity error! please, add INT_POLARITY_HIGH option."
#endif

#ifndef ISR2
#define ISR2(f) void f(void)
#endif

/* ------------------------------------------------------------------------------- */
/* Structures and external variables */
/* ------------------------------------------------------------------------------- */
//MRF24J40 structure (used in ISR mode):
typedef struct {	
	int status;
	int mode;							// mrf24j40 operating mode (polling, isr, ...)
    MicoGPIO_t* base;					// GPIO controller base address
    int irqf;							// GPIO irq flag to register the handler
    EE_ISR_callback rxcbk;				// rx callback
    EE_ISR_callback txcbk;				// tx callback
} EE_mrf24j40_st;

/* ZIGBEE driver functions list */
extern EE_mrf24j40_st ee_mrf24j40_st;

/* ------------------------------------------------------------------------------- */
/* Macros used into the Zigbee driver functions */
/* ------------------------------------------------------------------------------- */
#define MRF24J40_HAL_ISR() 		ISR2(MRF24J40_INTERRUPT_NAME)
#define MRF24J40_INTERRUPT_NAME	mrf24j40_isr		//_EXTERNAL_3_VECTOR
#define EE_MRF24J40_DEVICE_ID	(0x01)
#define MRF24J40_SPI_PORT_1		1
#define MRF24J40_SPI_PORT_2		2

/* Exit status for the EE_ZIGBEE driver */
#define	MRF24J40_SUCCESS 		(0)		/* no error */
#define	MRF24J40_FAILURE		(-19)	/* generic error */
#define	MRF24J40_ERR_SPI_INIT	(-20)	/* error in spi initialization */
#define	MRF24J40_ERR_SPI_READ	(-21)	/* spi read error */
#define	MRF24J40_ERR_SPI_WRITE	(-22)	/* spi write error */
#define	MRF24J40_ERR_DEV_NOINIT	(-23)	/* ZIGBEE device error */
#define	MRF24J40_ERR_MEM_NULL	(-24)	/* ZIGBEE null pointer error */

/* MRF24J40 operating modes */
#define EE_MRF24J40_POLLING		(0x00)
#define EE_MRF24J40_RX_ISR		(0x01)
#define EE_MRF24J40_TX_ISR		(0x02)	
#define EE_MRF24J40_RXTX_ISR	(0x03)
#define EE_MRF24J40_RX_BLOCK	(0x10)
#define EE_MRF24J40_TX_BLOCK	(0x20)
#define EE_MRF24J40_RXTX_BLOCK  (0x30)
#define EE_mrf24j40_need_enable_int(new)  	( ((new) & EE_MRF24J40_RX_ISR) || ((new) & EE_MRF24J40_TX_ISR) )

#define MRF24J40_SOFTRST_MASK 		(0x07)
#define MRF24J40_WAKE_ACTIVE()		EE_mrf24j40_gpio_wake_active()
#define MRF24J40_WAKE_INACTIVE()	EE_mrf24j40_gpio_wake_inactive()

#if(0) // not yet supported macros...
#define EE_MRF24J40_SHORT_ADDRESS_MASK		(0x3F)
#define EE_MRF24J40_LONG_ADDRESS_MASK		(0x3FF)
#define EE_MRF24J40_SRCR					(0x00)
#define EE_MRF24J40_SWCR					(0x01)
#define EE_MRF24J40_LRCR					(0x800)
#define EE_MRF24J40_LWCR					(0x801)
//#define EE_mrf24j40_need_init_rx_buf(old,new)		( !((old) & EE_MRF24J40_RX_ISR) && ((new) & EE_MRF24J40_RX_ISR) )
//#define EE_mrf24j40_need_init_tx_buf(old,new)  	( !((old) & EE_MRF24J40_TX_ISR) && ((new) & EE_MRF24J40_TX_ISR) )
//#define EE_mrf24j40_need_enable_rx_int(old, new)  ( (new) & EE_MRF24J40_RX_ISR )
//#define EE_mrf24j40_need_disable_rx_int(old, new) ( !((new) & EE_MRF24J40_RX_ISR) )
//#define EE_mrf24j40_enabled_rx_int(mode)  		( (mode) & EE_MRF24J40_RX_ISR )
#define EE_mrf24j40_tx_polling(mode) 				( !((mode) & EE_MRF24J40_TX_ISR) )
#define EE_mrf24j40_rx_polling(mode) 				( !((mode) & EE_MRF24J40_RX_ISR) )
#define EE_mrf24j40_rx_block(mode) 					( ((mode) & EE_MRF24J40_RX_BLOCK) )
#define EE_mrf24j40_tx_block(mode) 					( ((mode) & EE_MRF24J40_TX_BLOCK) )
#endif //#if(0) // not yet supported macros...

/* ------------------------------------------------------------------------------- */
/* ZIGBEE driver functions list */
/* ------------------------------------------------------------------------------- */
#define EE_ZIGBEE_SPI_NAME_UC NET_SPI
#define EE_ZIGBEE_SPI_NAME_LC net_spi

/* Macros for SPI-based ZIGBEE functions */  
#define DECLARE_FUNC_SPI_MRF24J40(uc, lc) \
__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_spi_config(int settings, int mode){ \
	cat3(EE_, lc, _config)(settings); \
	return cat3(EE_, lc, _set_ISR_mode)(mode); } \
__INLINE__ int __ALWAYS_INLINE__  EE_mrf24j40_spi_write_byte(EE_UINT8 data){ \
	return cat3(EE_, lc, _send_byte)(data); } \
__INLINE__ int __ALWAYS_INLINE__  EE_mrf24j40_spi_write_buffer(EE_UINT8 *data, int len){ \
	return cat3(EE_, lc, _send_buffer)(data, len); } \
__INLINE__ int __ALWAYS_INLINE__  EE_mrf24j40_spi_read(void){ \
	return cat3(EE_, lc, _receive_byte)(); } \
__INLINE__ int __ALWAYS_INLINE__  EE_mrf24j40_spi_read_buffer(EE_UINT8 *data, int len){ \
	return cat3(EE_, lc, _receive_buffer)(data, len); } \
__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_spi_set_SSO(void){ \
	return EE_hal_spi_set_SSO((MicoSPI_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_spi_clear_SSO(void){ \
	return EE_hal_spi_clear_SSO((MicoSPI_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_spi_set_slave(unsigned int mask){ \
	return EE_hal_spi_set_slave((MicoSPI_t*)EE_BASE_ADD(uc), mask); } \
__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_spi_get_slave(unsigned int *pmask ){ \
	return EE_hal_spi_get_slave((MicoSPI_t*)EE_BASE_ADD(uc), pmask); } \
__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_spi_close(){ \
	return EE_hal_spi_disable((MicoSPI_t*)EE_BASE_ADD(uc)); }
	
///* ZIGBEE API functions */
DECLARE_FUNC_SPI_MRF24J40(EE_ZIGBEE_SPI_NAME_UC, EE_ZIGBEE_SPI_NAME_LC)

/* API */
/*
	void EE_mrf24j40_delay_us(EE_UINT16 delay_count);
	This function contains a delay loop. 
*/
void EE_mrf24j40_delay_us(unsigned int delay_count);

/*
	__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_set_rx_ISR_callback(EE_ISR_callback rxcbk)
	This function sets ISR rx callback.
*/
int EE_mrf24j40_set_rx_ISR_callback(EE_ISR_callback rxcbk);

/*
	__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_set_tx_ISR_callback(EE_ISR_callback txcbk)
	This function sets ISR tx callback.
*/
int EE_mrf24j40_set_tx_ISR_callback(EE_ISR_callback txcbk);

/*
int EE_hal_mrf24j40_set_ISR_mode(int mode);
	This function is called by EE_mrf24j40_set_mode(int mode) function.
	It is used to configure the GPIO pin connected to mrf24j40 device.
*/
int EE_hal_mrf24j40_set_ISR_mode(int mode);

/*
	int EE_mrf24j40_read_short_address_register(int address);
	This function reads the content of a short address register.
*/
int EE_mrf24j40_read_short_address_register(int address);

/*
	int EE_mrf24j40_read_long_address_register(int address);
	This function reads the content of a long address register.
*/
int EE_mrf24j40_read_long_address_register(int address);

/*
	int EE_mrf24j40_write_short_address_register(int address);
	This function reads the content of a short address register.
*/
int EE_mrf24j40_write_short_address_register(int address, EE_UINT8 data);

/*
	int EE_mrf24j40_write_long_address_register(int address);
	This function reads the content of a long address register.
*/
int EE_mrf24j40_write_long_address_register(int address, EE_UINT8 data);

/*
	int EE_mrf24j40_read_buffer_memory(EE_UINT8 *data, int len);
	This function reads from the mrf24j40 memory buffer.
*/
int EE_mrf24j40_read_buffer_memory(EE_UINT8 *data, int len);

/*
	int EE_mrf24j40_write_buffer_memory(EE_UINT8 *data, int len);
	This function writes on the mrf24j40 memory buffer.
*/
int EE_mrf24j40_write_buffer_memory(EE_UINT8 *data, int len);

/*
	int EE_mrf24j40_software_reset(void);
	This function send a software reset command.
*/
int EE_mrf24j40_software_reset(void);

/*
	int EE_mrf24j40_hardware_reset(void);
	This function send a hardware reset command.
*/
int EE_mrf24j40_hardware_reset(void);

/*
	int EE_mrf24j40_enable(void);
	This function enables device by reset pin. 
*/
int EE_mrf24j40_enable(void);

/*
	int EE_mrf24j40_disable(void);
	This function disables device by reset pin. 
*/
int EE_mrf24j40_disable(void);

/*
	int EE_mrf24j40_enable_IRQ(void);
	This function enables mrf24j40 interrupts reception. 
*/
__INLINE__ void __ALWAYS_INLINE__ EE_mrf24j40_enable_IRQ(void)
{
	EE_mrf24j40_gpio_enable_IRQ();
}

/*
	int EE_mrf24j40_disable_IRQ(void);
	This function disables mrf24j40 interrupts reception. 
*/
__INLINE__ void __ALWAYS_INLINE__ EE_mrf24j40_disable_IRQ(void)
{
	EE_mrf24j40_gpio_disable_IRQ();
}

/*
	int EE_mrf24j40_IRQ_enabled(void);
	This function returns mrf24j40 interrupts enable state. 
*/
__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_IRQ_enabled(void)
{
	return EE_mrf24j40_gpio_IRQ_enabled();
}

/*
	__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_set_mode(int mode)
	This function sets mrf24j40 driver operating mode.
*/
__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_set_ISR_mode(int mode)
{ 
	return EE_hal_mrf24j40_set_ISR_mode(mode); 
} 

/*
	__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_init(void)
	This function configures mrf24j40 gpio pins.
*/
__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_init(void)
{ 
	EE_mrf24j40_gpio_write_output_pins(0);
	mico32_disable_irq(ee_mrf24j40_st.irqf);
	EE_mrf24j40_disable_IRQ();
	return MRF24J40_SUCCESS;
} 

/*
	__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_config(void)
	This function configures mrf24j40 driver.
*/
__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_config(void)
{ 
	EE_mrf24j40_init();		// init pins and disable gpio interrupt source.
	EE_mrf24j40_enable();	// set to 1 the _reset_ pin to turn on the mrf24j40 device.
	EE_mrf24j40_spi_config(0, EE_SPI_POLLING | EE_SPI_RXTX_BLOCK);
	
	#ifdef __USE_ZIGBEE_IRQ__
	return EE_mrf24j40_set_ISR_mode(EE_MRF24J40_RXTX_ISR); 
	#else // __USE_ZIGBEE_IRQ__
	return EE_mrf24j40_set_ISR_mode(EE_MRF24J40_POLLING | EE_MRF24J40_RXTX_BLOCK);
	#endif // __USE_ZIGBEE_IRQ__
} 

/*
	void EE_mrf24j40_handler(int level);
	MRF24J40 driver ISR handler. 
*/
void EE_mrf24j40_handler(int level);

#ifndef __STATIC_ISR_TABLE__
/* This function records ISR handler */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_mrf24j40_handler_setup(void)
{
    /* Register IRQ handler */
    EE_mico32_register_ISR(ee_mrf24j40_st.irqf, EE_mrf24j40_handler);	 
}
#else // __STATIC_ISR_TABLE__
#define EE_hal_mrf24j40_handler_setup()
#endif // __STATIC_ISR_TABLE__


/*
	Functions used by UWL
*/

/*
	void mrf24j40_set_rx_callback(void (*func)(void));
	This function sets the rx callback.
*/
void mrf24j40_set_rx_callback(void (*func)(void));

/*
	void mrf24j40_set_tx_finished_callback(void (*tx_finished_func)(uint8_t tx_status));
	This function sets the tx finished callback.
*/
void mrf24j40_set_tx_finished_callback(void (*tx_finished_func)(uint8_t tx_status));

/*
	Driver internal callback. It's called by the true handler. 
	Note, it is not the registered handler function. 
*/
ISR2(MRF24J40_INTERRUPT_NAME);

/*
	int8_t	mrf24j40_hal_init(void);
	This function calls the function EE_mrf24j40_init();
*/
int8_t	mrf24j40_hal_init(void);

/*
	int8_t	mrf24j40_hal_spi_init(uint8_t port);
	This function initializes spi port.
*/
int8_t	mrf24j40_hal_spi_init(uint8_t port);

/*
	int8_t	mrf24j40_hal_spi_close(void);
	This function closes spi port
*/
int8_t	mrf24j40_hal_spi_close(void);

/*
	int8_t	mrf24j40_hal_spi_write(uint8_t *data, uint16_t len);
	This function is used to write on the spi bus.
*/
int8_t	mrf24j40_hal_spi_write(uint8_t *data, uint16_t len);

/*
	int8_t	mrf24j40_hal_spi_read(uint8_t *data, uint16_t len);
	This function is used to read on the spi bus.
*/
int8_t	mrf24j40_hal_spi_read(uint8_t *data, uint16_t len);

/*
	COMPILER_INLINE void mrf24j40_hal_delay_us(uint16_t delay_count)
	This function implements a delay.
*/
COMPILER_INLINE void mrf24j40_hal_delay_us(uint16_t delay_count)
{
	EE_mrf24j40_delay_us((unsigned int)delay_count);
}

/*
	COMPILER_INLINE void mrf24j40_hal_retsetn_high(void)
	This function is used to release reset condition.
*/
COMPILER_INLINE void mrf24j40_hal_retsetn_high(void)
{
	EE_mrf24j40_gpio_release_reset();
}

/*
	COMPILER_INLINE void mrf24j40_hal_retsetn_low(void)
	This function is used to hold reset condition.
*/
COMPILER_INLINE void mrf24j40_hal_retsetn_low(void)
{
	EE_mrf24j40_gpio_hold_in_reset();
}

/*
	COMPILER_INLINE void mrf24j40_hal_csn_high(void)
	This function is used to release CSN signal.
*/
COMPILER_INLINE void mrf24j40_hal_csn_high(void)
{
	EE_mrf24j40_spi_clear_SSO();
}

/*
	COMPILER_INLINE void mrf24j40_hal_csn_low(void)
	This function is used to select the slave and configure CSN pin.
*/
COMPILER_INLINE void mrf24j40_hal_csn_low(void)
{
	EE_mrf24j40_spi_set_slave(EE_MRF24J40_DEVICE_ID);	
	EE_mrf24j40_spi_set_SSO(); // ss is low when transmission begins...
}

/*
	COMPILER_INLINE void mrf24j40_hal_irq_clean(void)
	This function is void. Kept for compatibility.
*/
COMPILER_INLINE void mrf24j40_hal_irq_clean(void)
{
	return;
}

/*
	COMPILER_INLINE void mrf24j40_hal_irq_enable(void)
	This function calls EE_mico32_enableIRQ().
*/
COMPILER_INLINE void mrf24j40_hal_irq_enable(void)
{
	EE_mico32_enableIRQ(); //EE_mrf24j40_enable_IRQ();
}

/*
	COMPILER_INLINE void mrf24j40_hal_irq_disable(void)
	This function calls EE_mico32_disableIRQ().
*/
COMPILER_INLINE void mrf24j40_hal_irq_disable(void)
{
	EE_mico32_disableIRQ(); //EE_mrf24j40_disable_IRQ();
}

/*
	COMPILER_INLINE uint8_t mrf24j40_hal_irq_status(void)
	Thsi function calls EE_mico32_get_IRQ_enabled().
*/
COMPILER_INLINE uint8_t mrf24j40_hal_irq_status(void)
{
	return EE_mico32_get_IRQ_enabled(); 
}

/*
	COMPILER_INLINE uint8_t mrf24j40_hal_int_enable(void)
	This function is used to register the handler and enable IRQ. 
*/
COMPILER_INLINE uint8_t mrf24j40_hal_int_enable(void)
{
	mico32_clear_ip_mask(1<<EE_MRF24J40_IRQ); 	// clear bit in ip register
	EE_hal_mrf24j40_handler_setup(); 			//EE_mico32_register_ISR(ee_mrf24j40_st.irqf, EE_mrf24j40_handler);	
	mico32_enable_irq(ee_mrf24j40_st.irqf);
	EE_mrf24j40_enable_IRQ();	 		//EE_mrf24j40_set_ISR_mode(EE_MRF24J40_RXTX_ISR); //(EE_MRF24J40_RXTX_ISR); //(EE_MRF24J40_POLLING | EE_MRF24J40_RXTX_BLOCK);;
	return MRF24J40_SUCCESS;
}

/*
	COMPILER_INLINE uint8_t mrf24j40_hal_int_disable(void)
	This function calls EE_mrf24j40_disable_IRQ().
*/
COMPILER_INLINE uint8_t mrf24j40_hal_int_disable(void)
{
	EE_mrf24j40_disable_IRQ();
	return MRF24J40_SUCCESS;
}

/*
	CCOMPILER_INLINE uint8_t mrf24j40_hal_int_status(void)
	This function calls EE_mrf24j40_IRQ_enabled().
*/
COMPILER_INLINE uint8_t mrf24j40_hal_int_status(void)
{
	return EE_mrf24j40_IRQ_enabled();
}

#endif /* Header Protection */
