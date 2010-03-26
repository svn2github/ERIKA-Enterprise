#ifdef __USE_MICO32BOARD_WIFICTRL_MRF24J40__

#ifndef __EE_WIFICTRL_MRF24J40_H__
#define __EE_WIFICTRL_MRF24J40_H__

/* Camera header files */
#include "cpu/mico32/inc/ee_internal.h"
#include "mcu/mico32/inc/ee_internal.h"
#include <cpu/mico32/inc/ee_irq.h>

/* Other used libraries: */
#include "mcu/mico32/inc/ee_spi.h"

/* Callback function called by wifictrl driver handler  */
extern EE_ISR_callback ee_mrf24j40_cbk;

/* Symbols and macros */
#define EE_MRF24J40_DEVICE_ID				(0x01)
#define EE_MRF24J40_ISR_MODE				(0x01)
#define EE_MRF24J40_POLLING_MODE			(0x00)
#define EE_MRF24J40_SHORT_ADDRESS_MASK		(0x3F)
#define EE_MRF24J40_LONG_ADDRESS_MASK		(0x3FF)
#define EE_MRF24J40_need_enable_int(mode)	(mode)
#define EE_WIFICTRL_INT_IRQ_FLAG			(0x00)

#define EE_MRF24J40_SRCR					(0x00)
#define EE_MRF24J40_SWCR					(0x01)
#define EE_MRF24J40_LRCR					(0x800)
#define EE_MRF24J40_LWCR					(0x801)

/* Default configuration */
#define EE_MRF24J40_DEFAULT_FORMAT			(0)

/* Exit status for the EE_wifiCTRL driver */
#define	MRF24J40_SUCCESS 					(0)		/* no error */
#define	MRF24J40_FAILURE					(-19)	/* generic error */
#define	MRF24J40_ERR_SPI_INIT				(-20)	/* error in spi initialization */
#define	MRF24J40_ERR_SPI_READ				(-21)	/* spi read error */
#define	MRF24J40_ERR_SPI_WRITE				(-22)	/* spi write error */
#define	MRF24J40_ERR_DEV_NOINIT				(-23)	/* wifi device error */
#define	MRF24J40_ERR_MEM_NULL				(-24)	/* wifi null pointer error */

/* Settings value */
#define	MRF24J40_NO_SUB  					(0)		/* ... */

/* -------------------------------- MRF24J40 driver API -------------------------------------- */

/* Macros for SPI-based wifictrl functions */  
#define DECLARE_FUNC_SPI_MRF24J40(uc, lc) \
__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_spi_init(int settings, int mode){ \
	cat3(EE_, lc, _config)(settings); \
	return cat3(EE_, lc, _set_ISR_mode)(mode); } \
__INLINE__ int __ALWAYS_INLINE__  EE_mrf24j40_write_byte(EE_UINT8 data){ \
	return cat3(EE_, lc, _send_byte)(data); } \
__INLINE__ int __ALWAYS_INLINE__  EE_mrf24j40_write_buffer(EE_UINT8 *data, int len){ \
	return cat3(EE_, lc, _send_buffer)(data, len); } \
__INLINE__ int __ALWAYS_INLINE__  EE_mrf24j40_read(void){ \
	return cat3(EE_, lc, _receive_byte)(); } \
__INLINE__ int __ALWAYS_INLINE__  EE_mrf24j40_read_buffer(EE_UINT8 *data, int len){ \
	return cat3(EE_, lc, _receive_buffer)(data, len); } \
__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_set_SSO(void){ \
	return EE_hal_spi_set_SSO((MicoSPI_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_clear_SSO(void){ \
	return EE_hal_spi_clear_SSO((MicoSPI_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_set_slave(unsigned int mask){ \
	return EE_hal_spi_set_slave((MicoSPI_t*)EE_BASE_ADD(uc), mask); } \
__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_get_slave(unsigned int *pmask ){ \
	return EE_hal_spi_get_slave((MicoSPI_t*)EE_BASE_ADD(uc), pmask); }
	
///* wifictrl API functions */
//#ifdef __EE_MRF24J40_USE_SPI1__
//	#ifdef __EE_MRF24J40_USE_SPI2__
//	#error mrf24j40 cannot support both i2c controllers
//	#endif //#ifdef __EE_MRF24J40_USE_SPI2__
//	DECLARE_FUNC_SPI_MRF24J40(EE_SPI1_NAME_UC, EE_SPI1_NAME_LC)
//#else //#ifdef __EE_MRF24J40_USE_SPI1__
//	DECLARE_FUNC_SPI_MRF24J40(EE_SPI2_NAME_UC, EE_SPI2_NAME_LC)
//#endif //#ifdef __EE_MRF24J40_USE_SPI1__
DECLARE_FUNC_SPI_MRF24J40(EE_SPI1_NAME_UC, EE_SPI1_NAME_LC)

/* wifictrl driver functions list */
__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_init(int settings, int mode)
{ 
	return EE_mrf24j40_spi_init(settings, mode); 
} 

/*
	int EE_mrf24j40_set_ISR_mode(int irqf);
	This function is called by EE_mrf24j40_set_mode(int mode) function.
	It is used to configure the GPIO pin connected to mrf24j40 device.
*/
int EE_hal_mrf24j40_set_ISR_mode(int irqf);

/*
	int EE_mrf24j40_set_polling_mode(void);
	This function is called by EE_mrf24j40_set_mode(int mode) function.
	It is used to configure mrf24j40 driver in polling mode.
*/
int EE_hal_mrf24j40_set_polling_mode(void);

/*
	__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_set_mode(int mode)
	This function sets mrf24j40 driver operating mode.
*/
__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_set_ISR_mode(int mode)
{ 
	if(mode) 
		return EE_hal_mrf24j40_set_ISR_mode(EE_WIFICTRL_INT_IRQ_FLAG); 
	else 
		return EE_hal_mrf24j40_set_polling_mode(); 
} 

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
	int EE_mrf24j40_enable_IRQ(void);
	This function enables mrf24j40 interrupts reception. 
*/
int EE_mrf24j40_enable_IRQ(void);

/*
	int EE_mrf24j40_disable_IRQ(void);
	This function disables mrf24j40 interrupts reception. 
*/
int EE_mrf24j40_disable_IRQ(void);

/*
	int EE_mrf24j40_IRQ_enabled(void);
	This function returns mrf24j40 interrupts enable state. 
*/
int EE_mrf24j40_IRQ_enabled(void);


#endif //__EE_WIFICTRL_MRF24J40_H__

#endif //#ifdef __USE_MICO32BOARD_WIFICTRL_MRF24J40__
