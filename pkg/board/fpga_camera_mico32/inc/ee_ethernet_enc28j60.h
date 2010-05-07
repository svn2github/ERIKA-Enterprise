/*
  Name: ee_ethernet_enc28j60.h 
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.28
  Description: Ethernet library header file for MICO32 CAMERA board
*/

#ifndef __EE_ETHERNET_ENC28J60__
#define __EE_ETHERNET_ENC28J60__

/* Camera header files */
#include "board/fpga_camera_mico32/inc/ee_ethernet_enc28j60_reg.h"
#include "cpu/mico32/inc/ee_internal.h"
#include "mcu/mico32/inc/ee_internal.h"
#include "board/fpga_camera_mico32/inc/ee_internal.h"
#include <cpu/mico32/inc/ee_irq.h>
/* Other used libraries: */
#include "mcu/mico32/inc/ee_spi.h"
#include "mcu/mico32/inc/ee_gpio.h"

#define EE_ETHERNET_SPI_NAME_UC EE_SPI1_NAME_UC
#define EE_ETHERNET_SPI_NAME_LC EE_SPI1_NAME_LC

/* ------------------------------------------------------------------------------- */
/* Structures and external variables */
/* ------------------------------------------------------------------------------- */
/*
	enc28j60 structure (used in ISR mode):
*/
typedef struct {	
	int status;
	int mode;							// enc28j60 operating mode (polling, isr, ...)
    MicoGPIO_t* base;					// GPIO controller base address
    int irqf;							// GPIO irq flag to register the handler
    EE_ISR_callback rxcbk;				// rx callback
    EE_ISR_callback txcbk;				// tx callback
    EE_buffer rxbuf;					// rx buffer used in isr mode
    EE_buffer txbuf;					// tx buffer used in isr mode
} EE_enc28j60_st;

/* ZIGBEE driver functions list */
extern EE_enc28j60_st ee_enc28j60_st;
/* Callback function called by ZIGBEE driver handler  */
extern EE_ISR_callback ee_enc28j60_cbk;

/* ------------------------------------------------------------------------------- */
/* Macros used into the Ethernet driver functions */
/* ------------------------------------------------------------------------------- */

/* Symbols and macros */
#define EE_ENC28J60_DEVICE_ID				(0x01)
#define EE_ENC28J60_ISR_MODE				(0x01)
#define EE_ENC28J60_POLLING_MODE			(0x00)
#define EE_ENC28J60_ADDRESS_MASK			(0x1F)
#define EE_ENC28J60_need_enable_int(mode)	(mode)
#define EE_ETHERNET_INT_IRQ_FLAG			(0x00)

/* Default configuration */
// ...

/* Exit status for the EE_ETHERNET driver */
#define	ENC28J60_SUCCESS 			(0)		/* no error */
#define	ENC28J60_FAILURE			(-19)	/* generic error */
#define	ENC28J60_ERR_SPI_INIT		(-20)	/* error in spi initialization */
#define	ENC28J60_ERR_SPI_READ		(-21)	/* spi read error */
#define	ENC28J60_ERR_SPI_WRITE		(-22)	/* spi write error */
#define	ENC28J60_ERR_DEV_NOINIT		(-23)	/* eth device error */
#define	ENC28J60_ERR_MEM_NULL		(-24)	/* eth null pointer error */

/* Board-dependent macros */
#define EE_INT1_BIT 	0 // mask: (0x01)
#define EE_INT2_BIT 	1 // mask: (0x02)
#define EE_FIFOP_BIT 	2 // mask: (0x04)
#define EE_CN1_BIT 		3 // mask: (0x08)
#define EE_DL3_BIT 		4 // mask: (0x10)
#define EE_GP1_BIT 		5 // mask: (0x20)
#define EE_CCA_BIT 		6 // mask: (0x40)
#define EE_enc28j60_hold_in_reset()	EE_misc_gpio_write_bit_data(0, EE_GP1_BIT)
#define EE_enc28j60_release_reset()	EE_misc_gpio_write_bit_data(1, EE_GP1_BIT)
#define ENC28J60_INTERRUPT_NAME		enc28j60_isr//_EXTERNAL_3_VECTOR
extern int ee_enc28j60_dummy_flag;
#define ENC28J60_INTERRUPT_FLAG		ee_enc28j60_dummy_flag

/* enc28j60 settings */
#define EE_ENC28J60_MSGSIZE 		(1)		
#define EE_ENC28J60_BUFSIZE 		(4)
#define EE_ENC28J60_NULL_VET		((EE_UINT8 *)0)

/* ENC28J60 operating modes */
#define EE_ENC28J60POLLING			(0x00)
#define EE_ENC28J60_RX_ISR			(0x01)
#define EE_ENC28J60_TX_ISR			(0x02)	
#define EE_ENC28J60_RXTX_ISR		(0x03)
#define EE_ENC28J60_RX_BLOCK		(0x10)
#define EE_ENC28J60_TX_BLOCK		(0x20)
#define EE_ENC28J60_RXTX_BLOCK  	(0x30)

#define EE_enc28j60_need_init_rx_buf(old,new)		( !((old) & EE_ENC28J60_RX_ISR) && ((new) & EE_ENC28J60_RX_ISR) )
#define EE_enc28j60_need_init_tx_buf(old,new)  		( !((old) & EE_ENC28J60_TX_ISR) && ((new) & EE_ENC28J60_TX_ISR) )
#define EE_enc28j60_need_enable_rx_int(old, new)  	( (new) & EE_ENC28J60_RX_ISR )
#define EE_enc28j60_need_disable_rx_int(old, new)  	( !((new) & EE_ENC28J60_RX_ISR) )
#define EE_enc28j60_enabled_rx_int(mode)  			( (mode) & EE_ENC28J60_RX_ISR )
#define EE_enc28j60_need_enable_int(new)  			( ((new) & EE_ENC28J60_RX_ISR) || ((new) & EE_ENC28J60_TX_ISR) )	
#define EE_enc28j60_tx_polling(mode) 				( !((mode) & EE_ENC28J60_TX_ISR) )
#define EE_enc28j60_rx_polling(mode) 				( !((mode) & EE_ENC28J60_RX_ISR) )
#define EE_enc28j60_rx_block(mode) 					( ((mode) & EE_ENC28J60_RX_BLOCK) )
#define EE_enc28j60_tx_block(mode) 					( ((mode) & EE_ENC28J60_TX_BLOCK) )

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

/*
	void EE_enc28j60_delay_us(EE_UINT16 delay_count);
	This function contains a delay loop. 
*/
void EE_enc28j60_delay_us(EE_UINT16 delay_count);

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
	int EE_enc28j60_hardware_reset(void);
	This function resets the device (HW reset).
*/
int EE_enc28j60_hardware_reset(void);

/*
	int EE_enc28j60_enable(void);
	This function enables device by reset pin. 
*/
int EE_enc28j60_enable(void);

/*
	int EE_enc28j60_disable(void);
	This function disables device by reset pin. 
*/
int EE_enc28j60_disable(void);


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


/* INLINE functions */
__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_set_ISR_mode(int mode)
{ 
	return EE_hal_enc28j60_set_ISR_mode(mode); 
} 

__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_config(int settings, int mode)
{ 
	//ee_enc28j60_GPIO_port = (EE_GPIO_data_bits_t*)(&(ee_enc28j60_st.base->data));
	//ee_enc28j60_GPIO_intf = (EE_GPIO_data_bits_t*)(&(ee_enc28j60_st.base->edgeCapture));
	//ee_enc28j60_GPIO_inte = (EE_GPIO_data_bits_t*)(&(ee_enc28j60_st.base->irqMask));
    //EE_enc28j60_set_ISR_mode(EE_ENC28J60_RXTX_ISR);
	return EE_enc28j60_spi_init(settings, mode);
	//return EE_enc28j60_enable();
} 

#endif //#ifndef __EE_ETHERNET_enc28j60__
