#ifdef __USE_MICO32BOARD_ETHCTRL_ENC28J60__

#ifndef __EE_ETHCTRL_ENC28J60__
#define __EE_ETHCTRL_ENC28J60__

/* Camera header files */
#include "board/fpga_camera_mico32/inc/ee_ethctrl_enc28j60_reg.h"
#include "cpu/mico32/inc/ee_internal.h"
#include "mcu/mico32/inc/ee_internal.h"
#include <cpu/mico32/inc/ee_irq.h>

/* Other used libraries: */
#include "mcu/mico32/inc/ee_spi.h"

/* Callback function called by ethctrl driver handler  */
extern EE_ISR_callback ee_enc28j60_cbk;

/* Symbols and macros */
#define EE_ENC28J60_DEVICE_ID				(0x01)
#define EE_ENC28J60_ISR_MODE				(0x01)
#define EE_ENC28J60_POLLING_MODE			(0x00)
#define EE_ENC28J60_ADDRESS_MASK			(0x1F)
#define EE_ENC28J60_need_enable_int(mode)	(mode)
#define EE_ETHCTRL_INT_IRQ_FLAG				(0x00)

/* Default configuration */
#define EE_ENC28J60_DEFAULT_FORMAT			(0)

/* Exit status for the EE_ETHCTRL driver */
#define	ENC28J60_SUCCESS 					(0)		/* no error */
#define	ENC28J60_FAILURE					(-19)	/* generic error */
#define	ENC28J60_ERR_SPI_INIT				(-20)	/* error in spi initialization */
#define	ENC28J60_ERR_SPI_READ				(-21)	/* spi read error */
#define	ENC28J60_ERR_SPI_WRITE				(-22)	/* spi write error */
#define	ENC28J60_ERR_DEV_NOINIT				(-23)	/* eth device error */
#define	ENC28J60_ERR_MEM_NULL				(-24)	/* eth null pointer error */

/* Settings value */
#define	ENC28J60_NO_SUB  					(0)		/* ... */

/* -------------------------------- enc28j60 driver API -------------------------------------- */

/* Macros for SPI-based ethctrl functions */  
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

///* ethctrl API functions */
//#ifdef __EE_ENC28J60_USE_SPI1__
//	#ifdef __EE_ENC28J60_USE_SPI2__
//	#error enc28j60 cannot support both i2c controllers
//	#endif //#ifdef __EE_ENC28J60_USE_SPI2__
//	DECLARE_FUNC_SPI_ENC28J60(EE_SPI1_NAME_UC, EE_SPI1_NAME_LC)
//#else //#ifdef __EE_ENC28J60_USE_SPI1__
//	DECLARE_FUNC_SPI_ENC28J60(EE_SPI2_NAME_UC, EE_SPI2_NAME_LC)
//#endif //#ifdef __EE_ENC28J60_USE_SPI1__
DECLARE_FUNC_SPI_ENC28J60(EE_SPI1_NAME_UC, EE_SPI1_NAME_LC)

/* ethctrl driver functions list */
/* 
	__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_init(int settings)
	This function configures SPI controller.
 */
__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_init(int settings, int mode)
{ 
	return EE_enc28j60_spi_init(settings, mode);
} 

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
__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_set_ISR_mode(int mode)
{ 
	if(mode) 
		return EE_hal_enc28j60_set_ISR_mode(EE_ETHCTRL_INT_IRQ_FLAG); 
	else 
		return EE_hal_enc28j60_set_polling_mode(); 
} 

/*
	int EE_enc28j60_read_ETH_register(int address);
	This function reads an ETH register.
*/
int EE_enc28j60_read_ETH_register(int address);

/*
	int EE_enc28j60_read_MAC_register(int address);
	This function reads a MAC register.
*/
int EE_enc28j60_read_MAC_register(int address);

/*
	int EE_enc28j60_read_MII_register(int address);
	This function reads a MII register.
*/
int EE_enc28j60_read_MII_register(int address);

/*
	int EE_enc28j60_read_PHY_register(int address);
	This function reads a PHY register.
*/
int EE_enc28j60_read_PHY_register(int address);

/*
	int EE_enc28j60_write_ETH_register(int address, EE_UINT8 data);
	This function writes on a ETH register.
*/
int EE_enc28j60_write_ETH_register(int address, EE_UINT8 data);

/*
	int EE_enc28j60_write_MAC_register(int address, EE_UINT8 data);
	This function writes on a MAC register.
*/
int EE_enc28j60_write_MAC_register(int address, EE_UINT8 data);

/*
	int EE_enc28j60_write_MII_register(int address, EE_UINT8 data);
	This function writes on a MII register.
*/
int EE_enc28j60_write_MII_register(int address, EE_UINT8 data);

/*
	int EE_enc28j60_write_PHY_register(int address, EE_UINT8 data);
	This function writes on a PHY register.
*/
int EE_enc28j60_write_PHY_register(int address, EE_UINT8 data);

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
int EE_enc28j60_bit_field_set(int address, EE_UINT8 data);

/* 
	int EE_enc28j60_bit_field_clear(int address, EE_UINT8 data);
	This function clears up to 8 bits in a ETH register.
*/
int EE_enc28j60_bit_field_clear(int address, EE_UINT8 data);

/*
	int EE_enc28j60_software_reset(void);
	This function send a software reset command.
*/
int EE_enc28j60_software_reset(void);

/*
	int EE_enc28j60_enable_IRQ(void);
	This function enables ENC28J60 interrupts reception. 
*/
int EE_enc28j60_enable_IRQ(void);

/*
	int EE_enc28j60_disable_IRQ(void);
	This function disables ENC28J60 interrupts reception. 
*/
int EE_enc28j60_disable_IRQ(void);

/*
	int EE_enc28j60_IRQ_enabled(void);
	This function returns ENC28J60 interrupts enable state. 
*/
int EE_enc28j60_IRQ_enabled(void);

/*
	int EE_enc28j60_bank_select(EE_UINT8 bank);
	This function selects the bank.
*/
int EE_enc28j60_bank_select(EE_UINT8 bank);



#endif //#ifndef __EE_ethctrl_enc28j60__

#endif //#ifdef __USE_MICO32BOARD_ETHCTRL_ENC28J60__
