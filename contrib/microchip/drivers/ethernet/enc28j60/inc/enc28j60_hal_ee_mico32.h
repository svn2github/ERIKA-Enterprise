/*
  Name: enc28j60_hal_ee_mico32.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: ENC28J60 driver header file.
*/

#ifndef __ENC28J60_HAL_EE_MICO32_H__
#define __ENC28J60_HAL_EE_MICO32_H__

/* Needed header files */
#include "cpu/mico32/inc/ee_internal.h"
#include "cpu/mico32/inc/ee_irq.h"
#include "mcu/mico32/inc/ee_internal.h"
#include "mcu/mico32/inc/ee_spi.h"
#include "mcu/mico32/inc/ee_gpio.h"
/* Board header */
#ifdef __XP2_CAMERA_BOARD__
#include "board/fpga_camera_mico32/inc/ee_internal.h"
#include "board/fpga_camera_mico32/inc/ee_ethernet_enc28j60.h"
#else	/* NO board */
#error "ENC28J60_HAL: No board selected!"
#endif	//#ifdef __XP2_CAMERA_BOARD__
/* Other used libraries */
#include "MicoUtils.h"
/* Check */
#ifndef __USE_SPI__
#error "ENC28J60 HAL EE : The SPI module from MCU is required!"
#endif
/* Endianness */
#ifndef BIG_ENDIAN
#define BIG_ENDIAN
#endif

/* ENC28J60 structure (used in ISR mode) */
typedef struct {	
    MicoGPIO_t* base;					// GPIO controller base address
    int irqf;							// GPIO irq flag to register the handler
    EE_ISR_callback rxcbk;				// rx callback
    EE_ISR_callback txcbk;				// tx callback
} EE_enc28j60_st;

/* ZIGBEE driver functions list */
extern EE_enc28j60_st ee_enc28j60_st;

/* ------------------------------------------------------------------------------- */
/* Macros used into the Ethernet driver functions */
/* ------------------------------------------------------------------------------- */

/* Symbols and macros */
#define EE_ENC28J60_DEVICE_ID		(0x01)
#define EE_ENC28J60_ADDRESS_MASK	(0x1F)
#define ENC28J60_INTERRUPT_NAME()

/* Exit status for the EE_ETHERNET driver */
#define	ENC28J60_SUCCESS 			(0)		/* no error */
#define	ENC28J60_FAILURE			(-19)	/* generic error */
#define	ENC28J60_ERR_SPI_INIT		(-20)	/* error in spi initialization */
#define	ENC28J60_ERR_SPI_READ		(-21)	/* spi read error */
#define	ENC28J60_ERR_SPI_WRITE		(-22)	/* spi write error */
#define	ENC28J60_ERR_DEV_NOINIT		(-23)	/* eth device error */
#define	ENC28J60_ERR_MEM_NULL		(-24)	/* eth null pointer error */

/* -------------------------------------------------------------------- */
/* Pseudo functions (Wrapper) */
#define ENC_CS_IO_f(p)				/* null definition */
#define ENC_CS_TRIS_f(p)			/* null definition */
#define DelayMs(ms)					EE_enc28j60_delay_ms(ms)
#define Reset()						EE_enc28j60_hardware_reset() // to do... asm("RESET")
#define ClearSPIDoneFlag()			/* null definition */
//#define WaitForDataByte()  
//#define SPI_ON_BIT   
//#define ENC_CS_IO(p1) 				
//#define ENC_CS_TRIS(p1)				
//#define ENC_SSPBUF					
/* ---------------------------------------------------------------------*/

// /* ENC28J60 operating modes */
// #define EE_ENC28J60POLLING							(0x00)
// #define EE_ENC28J60_RX_ISR							(0x01)
// #define EE_ENC28J60_TX_ISR							(0x02)	
// #define EE_ENC28J60_RXTX_ISR							(0x03)
// #define EE_ENC28J60_RX_BLOCK							(0x10)
// #define EE_ENC28J60_TX_BLOCK							(0x20)
// #define EE_ENC28J60_RXTX_BLOCK  						(0x30)
// #define EE_enc28j60_need_init_rx_buf(old,new)		( !((old) & EE_ENC28J60_RX_ISR) && ((new) & EE_ENC28J60_RX_ISR) )
// #define EE_enc28j60_need_init_tx_buf(old,new)  		( !((old) & EE_ENC28J60_TX_ISR) && ((new) & EE_ENC28J60_TX_ISR) )
// #define EE_enc28j60_need_enable_rx_int(old, new)  	( (new) & EE_ENC28J60_RX_ISR )
// #define EE_enc28j60_need_disable_rx_int(old, new)  	( !((new) & EE_ENC28J60_RX_ISR) )
// #define EE_enc28j60_enabled_rx_int(mode)  			( (mode) & EE_ENC28J60_RX_ISR )
// #define EE_enc28j60_need_enable_int(new)  			( ((new) & EE_ENC28J60_RX_ISR) || ((new) & EE_ENC28J60_TX_ISR) )	
// #define EE_enc28j60_tx_polling(mode) 				( !((mode) & EE_ENC28J60_TX_ISR) )
// #define EE_enc28j60_rx_polling(mode) 				( !((mode) & EE_ENC28J60_RX_ISR) )
// #define EE_enc28j60_rx_block(mode) 					( ((mode) & EE_ENC28J60_RX_BLOCK) )
// #define EE_enc28j60_tx_block(mode) 					( ((mode) & EE_ENC28J60_TX_BLOCK) )

/* ------------------------------------------------------------------------------- */
/* ETHERNET driver functions list */
/* ------------------------------------------------------------------------------- */

/* Macros for SPI-based ETHERNET functions */  
#define DECLARE_FUNC_SPI_ENC28J60(uc, lc) \
__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_spi_init(int settings, int mode){ \
	cat3(EE_, lc, _config)(settings); \
	return cat3(EE_, lc, _set_ISR_mode)(mode); } \
__INLINE__ int __ALWAYS_INLINE__  EE_enc28j60_write_byte(EE_UINT8 data){ \
	return cat3(EE_, lc, _send_byte)(data); } \
__INLINE__ int __ALWAYS_INLINE__  EE_enc28j60_write_buffer(EE_UINT8 *data, int len){ \
	return cat3(EE_, lc, _send_buffer)(data, len); } \
__INLINE__ int __ALWAYS_INLINE__  EE_enc28j60_read(void){ \
	return cat3(EE_, lc, _receive_byte)(); } \
__INLINE__ int __ALWAYS_INLINE__  EE_enc28j60_read_buffer(EE_UINT8 *data, int len){ \
	return cat3(EE_, lc, _receive_buffer)(data, len); } \
__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_set_SSO(void){ \
	return EE_hal_spi_set_SSO((MicoSPI_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_clear_SSO(void){ \
	return EE_hal_spi_clear_SSO((MicoSPI_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_set_slave(unsigned int mask){ \
	return EE_hal_spi_set_slave((MicoSPI_t*)EE_BASE_ADD(uc), mask); } \
__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_get_slave(unsigned int *pmask ){ \
	return EE_hal_spi_get_slave((MicoSPI_t*)EE_BASE_ADD(uc), pmask); }

///* ETHERNET API functions */
DECLARE_FUNC_SPI_ENC28J60(EE_ETHERNET_SPI_NAME_UC, EE_ETHERNET_SPI_NAME_LC)

#ifndef __STATIC_ISR_TABLE__
/* This function records ISR handler */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_enc28j60_handler_setup(void)
{
    /* Register IRQ handler */
    EE_mico32_register_ISR(ee_enc28j60_st.irqf, EE_enc28j60_handler);	 
}
#else // __STATIC_ISR_TABLE__
#define EE_hal_enc28j60_handler_setup()
#endif // __STATIC_ISR_TABLE__

/*
	void EE_enc28j60_delay_us(EE_UINT16 delay_count);
	This function contains a delay loop. 
*/
void EE_enc28j60_delay_us(unsigned int delay_count);

/*
	void EE_enc28j60_delay_ms(EE_UINT16 delay_count);
	This function contains a delay loop. 
*/
void EE_enc28j60_delay_ms(unsigned int delay_count);

/* 
	__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_init(int settings)
	This function configures SPI controller.
 */
__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_config(int settings, int mode);

/*
	int EE_enc28j60_set_ISR_mode(int irqf);
	This function is called by EE_enc28j60_set_mode(int mode) function.
	It is used to configure the GPIO pin connected to ENC28J60 device.
*/
int EE_hal_enc28j60_set_ISR_mode(int irqf);

/*
	int EE_enc28j60_set_polling_mode(void);
	This function is called by EE_enc28j60_set_mode(int mode) function.
	It is used to configure ENC28J60 driver in polling mode.
*/
int EE_hal_enc28j60_set_polling_mode(void);

/*
	__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_set_mode(int mode)
	This function sets ENC28J60 driver operating mode.
*/
__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_set_ISR_mode(int mode);

/*
	int EE_enc28j60_read_ETH_register(int address);
	This function reads an ETH register.
*/
int EE_enc28j60_read_ETH_register(EE_UINT8 address);

/*
	int EE_enc28j60_read_MACMII_register(int address);
	This function reads a MAC/MII register.
*/
int EE_enc28j60_read_MAC_MII_register(EE_UINT8 address);

/*
	int EE_enc28j60_read_PHY_register(int address);
	This function reads a PHY register.
*/
int EE_enc28j60_read_PHY_register(EE_UINT8 address);

/*
	int EE_enc28j60_write_register(int address, EE_UINT8 data);
	This function writes on a generic register.
*/
int EE_enc28j60_write_register(EE_UINT8 address, EE_UINT8 data);

/*
	int EE_enc28j60_write_PHY_register(int address, EE_UINT8 data);
	This function writes on a PHY register.
*/
int EE_enc28j60_write_PHY_register(EE_UINT8 address, int data);

/*
	int EE_enc28j60_read_buffer_memory(EE_UINT8 *data, int len);
	This function reads from the ENC28J60 memory buffer.
*/
int EE_enc28j60_read_buffer_memory(EE_UINT8 *data, int len);

/*
	int EE_enc28j60_write_buffer_memory(EE_UINT8 *data, int len);
	This function writes on the ENC28J60 memory buffer.
*/
int EE_enc28j60_write_buffer_memory(EE_UINT8 *data, int len);

/* 
	int EE_enc28j60_bit_field_set(int address, EE_UINT8 data);
	This function sets up to 8 bits in a ETH register.
*/
int EE_enc28j60_bit_field_set(EE_UINT8 address, EE_UINT8 data);

/* 
	int EE_enc28j60_bit_field_clear(int address, EE_UINT8 data);
	This function clears up to 8 bits in a ETH register.
*/
int EE_enc28j60_bit_field_clear(EE_UINT8 address, EE_UINT8 data);

/*
	int EE_enc28j60_software_reset(void);
	This function send a software reset command.
*/
int EE_enc28j60_software_reset(void);

/*
	void EE_enc28j60_hardware_reset(void);
	This function resets the device (HW reset).
*/
void EE_enc28j60_hardware_reset(void);

/*
	int EE_enc28j60_bank_select(EE_UINT8 bank);
	This function selects the bank.
*/
int EE_enc28j60_bank_select(EE_UINT8 bank);

/* ---------------- */
/* INLINE functions */
/* ---------------- */

/*
	int EE_enc28j60_read_MAC_register(int address);
	This function reads a MAC register.
*/
__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_read_MAC_register(EE_UINT8 address)
{
	return EE_enc28j60_read_MAC_MII_register(address);
}

/*
	int EE_enc28j60_read_MII_register(int address);
	This function reads a MII register.
*/
__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_read_MII_register(EE_UINT8 address)
{
	return EE_enc28j60_read_MAC_MII_register(address);
}

/*
	int EE_enc28j60_write_ETH_register(int address, EE_UINT8 data);
	This function writes on a ETH register.
*/
__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_write_ETH_register(EE_UINT8 address, EE_UINT8 data)
{
	return EE_enc28j60_write_register(address, data);
}

/*
	int EE_enc28j60_write_MAC_register(int address, EE_UINT8 data);
	This function writes on a MAC register.
*/
__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_write_MAC_register(EE_UINT8 address, EE_UINT8 data)
{
	return EE_enc28j60_write_register(address, data);
}

/*
	int EE_enc28j60_write_MII_register(int address, EE_UINT8 data);
	This function writes on a MII register.
*/
__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_write_MII_register(EE_UINT8 address, EE_UINT8 data)
{
	return EE_enc28j60_write_register(address, data);
}

/*
	__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_enable(void);
	This function enables device by reset pin. 
*/
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_enable(void)
{
	EE_enc28j60_gpio_release_reset();
}

/*
	__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_disable(void);
	This function disables device by reset pin. 
*/
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_disable(void)
{
	EE_enc28j60_gpio_hold_in_reset();
}

/*
	__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_enable_IRQ(void);
	This function enables ENC28J60 interrupts reception. 
*/
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_enable_IRQ(void)
{
	EE_enc28j60_gpio_enable_IRQ();
}

/*
	__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_disable_IRQ(void);
	This function disables ENC28J60 interrupts reception. 
*/
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_disable_IRQ(void)
{
	EE_enc28j60_gpio_disable_IRQ();
}

/*
	__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_IRQ_enabled(void);
	This function returns ENC28J60 interrupts enable state. 
*/
__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_IRQ_enabled(void)
{
	return EE_enc28j60_gpio_IRQ_enabled();
}

/*
	__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_set_ISR_mode(int mode)
	This function configures ISR mode.
*/
__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_set_ISR_mode(int mode)
{ 
	return EE_hal_enc28j60_set_ISR_mode(mode); 
} 

/*
	__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_config(int settings, int mode)
	This function configures the device.
*/
__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_config(int settings, int mode)
{ 
	//ee_enc28j60_GPIO_port = (EE_GPIO_data_bits_t*)(&(ee_enc28j60_st.base->data));
	//ee_enc28j60_GPIO_intf = (EE_GPIO_data_bits_t*)(&(ee_enc28j60_st.base->edgeCapture));
	//ee_enc28j60_GPIO_inte = (EE_GPIO_data_bits_t*)(&(ee_enc28j60_st.base->irqMask));
    //EE_enc28j60_set_ISR_mode(EE_ENC28J60_RXTX_ISR);
	return EE_enc28j60_spi_init(settings, mode);
	//return EE_enc28j60_enable();
} 


#endif //__ENC28J60_HAL_EE_MICO32_H__

