/*
  Name: ee_zugbee_mrf24j40.h 
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.28
  Description: zigbee library header file for MICO32 CAMERA board
*/

#ifdef __USE_MICO32BOARD_ZIGBEE_MRF24J40__

#ifndef __EE_ZIGBEE_MRF24J40_H__
#define __EE_ZIGBEE_MRF24J40_H__

/* Camera header files */
#include "cpu/mico32/inc/ee_internal.h"
#include "mcu/mico32/inc/ee_internal.h"
#include <cpu/mico32/inc/ee_irq.h>

/* Other used libraries: */
#include "mcu/mico32/inc/ee_spi.h"
#include <MicoGPIO.h>

/* Symbols and macros */
#define EE_MRF24J40_DEVICE_ID				(0x01)
#define EE_MRF24J40_SHORT_ADDRESS_MASK		(0x3F)
#define EE_MRF24J40_LONG_ADDRESS_MASK		(0x3FF)
#define EE_MRF24J40_SRCR					(0x00)
#define EE_MRF24J40_SWCR					(0x01)
#define EE_MRF24J40_LRCR					(0x800)
#define EE_MRF24J40_LWCR					(0x801)
#define EE_MRF24J40_SOFTRST 				(0x2A)
#define EE_MRF24J40_SOFTRST_MASK 			(0x07)


/* Default configuration */
#define EE_MRF24J40_DEFAULT_FORMAT			(0)

/* Settings value */
#define	MRF24J40_NO_SUB  					(0)		/* ... */

/* Exit status for the EE_ZIGBEE driver */
#define	MRF24J40_SUCCESS 					(0)		/* no error */
#define	MRF24J40_FAILURE					(-19)	/* generic error */
#define	MRF24J40_ERR_SPI_INIT				(-20)	/* error in spi initialization */
#define	MRF24J40_ERR_SPI_READ				(-21)	/* spi read error */
#define	MRF24J40_ERR_SPI_WRITE				(-22)	/* spi write error */
#define	MRF24J40_ERR_DEV_NOINIT				(-23)	/* ZIGBEE device error */
#define	MRF24J40_ERR_MEM_NULL				(-24)	/* ZIGBEE null pointer error */

/* Uart settings */
#define EE_MRF24J40_MSGSIZE 	(1)		
#define EE_MRF24J40_BUFSIZE 	(4)
#define EE_MRF24J40_NULL_VET	((EE_UINT8 *)0)

/* Uart operating modes */
#define EE_MRF24J40POLLING		(0x00)
#define EE_MRF24J40_RX_ISR		(0x01)
#define EE_MRF24J40_TX_ISR		(0x02)	
#define EE_MRF24J40_RXTX_ISR	(0x03)
#define EE_MRF24J40_RX_BLOCK	(0x10)
#define EE_MRF24J40_TX_BLOCK	(0x20)
#define EE_MRF24J40_RXTX_BLOCK  (0x30)

#define EE_mrf24j40_need_init_rx_buf(old,new)		( !((old) & EE_MRF24J40_RX_ISR) && ((new) & EE_MRF24J40_RX_ISR) )
#define EE_mrf24j40_need_init_tx_buf(old,new)  		( !((old) & EE_MRF24J40_TX_ISR) && ((new) & EE_MRF24J40_TX_ISR) )
#define EE_mrf24j40_need_enable_rx_int(old, new)  	( (new) & EE_MRF24J40_RX_ISR )
#define EE_mrf24j40_need_disable_rx_int(old, new)  	( !((new) & EE_MRF24J40_RX_ISR) )
#define EE_mrf24j40_enabled_rx_int(mode)  			( (mode) & EE_MRF24J40_RX_ISR )
#define EE_mrf24j40_need_enable_int(new)  			( ((new) & EE_MRF24J40_RX_ISR) || ((new) & EE_MRF24J40_TX_ISR) )	
#define EE_mrf24j40_tx_polling(mode) 				( !((mode) & EE_MRF24J40_TX_ISR) )
#define EE_mrf24j40_rx_polling(mode) 				( !((mode) & EE_MRF24J40_RX_ISR) )
#define EE_mrf24j40_rx_block(mode) 					( ((mode) & EE_MRF24J40_RX_BLOCK) )
#define EE_mrf24j40_tx_block(mode) 					( ((mode) & EE_MRF24J40_TX_BLOCK) )

/* Board-dependent macros */
//#define MRF24J40_PORTbits ((MRF24J40_GPIO_Data_t)((MicoGPIO_t *)MRF24J40_GPIO_BASE_ADDRESS)->data)
//
//typedef union _MRF24J40_GPIO_Data {
//	uint8_t val;
//	struct MRF24J40_GPIO_Data_Bits {
//		unsigned char CH0: 1;
//		unsigned char CH1: 1;
//		unsigned char CH2: 1;
//		unsigned char CH3: 1;
//		unsigned char CH4: 1;
//		unsigned char CH5: 1;
//		unsigned char CH6: 1;
//		unsigned char CH7: 1;
//	}bits; 
//}MRF24J40_GPIO_Data_t;

extern int to_remove;
#define EE_MRF24J40_INT		to_remove
#define EE_MRF24J40_RESET	to_remove

//#define MRF24J40_RESETn		    to_remove
//#define MRF24J40_VREG_EN        0//PORTGbits.RG15
//#define MRF24J40_INT		    0//PORTAbits.RA14
//#define MRF24J40_CSn		    0//PORTAbits.RA15
//#define MRF24J40_TRIS_RESETn	0//TRISFbits.TRISF1
//#define MRF24J40_TRIS_VREG_EN   0//TRISGbits.TRISG15
//#define MRF24J40_TRIS_INT		0//TRISAbits.TRISA14
//#define MRF24J40_TRIS_CSn		0//TRISAbits.TRISA15
#define MRF24J40_INTERRUPT_NAME             mrf24j40_isr//_EXTERNAL_3_VECTOR
#define MRF24J40_INTERRUPT_FLAG             to_remove
//#define MRF24J40_INTERRUPT_ENABLE           0//IEC0bits.INT3IE
//#define MRF24J40_INTERRUPT_PRIORITY         0//IPC3bits.INT3IP
//#define MRF24J40_INTERRUPT_EDGE_POLARITY    0//INTCONbits.INT3EP

/* -------------------------------- MRF24J40 driver API -------------------------------------- */

/*
	MRF24J40 structure (used in ISR mode):
*/
typedef struct {	
	int status;
	int mode;							// mrf24j40 operating mode (polling, isr, ...)
    MicoGPIO_t* base;					// GPIO controller base address
    int irqf;							// GPIO irq flag to register the handler
    EE_ISR_callback rxcbk;				// rx callback
    EE_ISR_callback txcbk;				// tx callback
    EE_buffer rxbuf;					// rx buffer used in isr mode
    EE_buffer txbuf;					// tx buffer used in isr mode
} EE_mrf24j40_st;

/* ZIGBEE driver functions list */
extern EE_mrf24j40_st ee_mrf24j40_st;

/* Callback function called by ZIGBEE driver handler  */
extern EE_ISR_callback ee_mrf24j40_cbk;

/* Macros for SPI-based ZIGBEE functions */  
#define DECLARE_FUNC_SPI_MRF24J40(uc, lc) \
__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_spi_config(int settings, int mode){ \
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
	return EE_hal_spi_get_slave((MicoSPI_t*)EE_BASE_ADD(uc), pmask); } \
__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_spi_close(){ \
	return EE_hal_spi_disable((MicoSPI_t*)EE_BASE_ADD(uc)); }
	
///* ZIGBEE API functions */
//#ifdef __EE_MRF24J40_USE_SPI1__
//	#ifdef __EE_MRF24J40_USE_SPI2__
//	#error mrf24j40 cannot support both i2c controllers
//	#endif //#ifdef __EE_MRF24J40_USE_SPI2__
//	DECLARE_FUNC_SPI_MRF24J40(EE_SPI1_NAME_UC, EE_SPI1_NAME_LC)
//#else //#ifdef __EE_MRF24J40_USE_SPI1__
//	DECLARE_FUNC_SPI_MRF24J40(EE_SPI2_NAME_UC, EE_SPI2_NAME_LC)
//#endif //#ifdef __EE_MRF24J40_USE_SPI1__

//DECLARE_FUNC_SPI_MRF24J40(NET_SPI, net_spi)
DECLARE_FUNC_SPI_MRF24J40(EE_SPI1_NAME_UC, EE_SPI1_NAME_LC)

/* API */
/*
	void EE_mrf24j40_delay_us(EE_UINT16 delay_count);
	This function contains a delay loop. 
*/
void EE_mrf24j40_delay_us(EE_UINT16 delay_count);

/*
	__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_set_rx_ISR_callback(EE_ISR_callback rxcbk)
	This function sets ISR rx callback.
*/
int EE_mrf24j40_set_rx_ISR_callback(EE_ISR_callback rxcbk);
// {
    // ee_mrf24j40_st.rxcbk = rxcbk;
	// return MRF24J40_SUCCESS;
// }


/*
	__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_set_tx_ISR_callback(EE_ISR_callback txcbk)
	This function sets ISR tx callback.
*/
int EE_mrf24j40_set_tx_ISR_callback(EE_ISR_callback txcbk);
// {
	// ee_mrf24j40_st.txcbk = txcbk;
	// return MRF24J40_SUCCESS;
// }

/*
int EE_hal_mrf24j40_set_ISR_mode(int mode);
	This function is called by EE_mrf24j40_set_mode(int mode) function.
	It is used to configure the GPIO pin connected to mrf24j40 device.
*/
int EE_hal_mrf24j40_set_ISR_mode(int mode);

/*
	__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_set_mode(int mode)
	This function sets mrf24j40 driver operating mode.
*/
__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_set_ISR_mode(int mode)
{ 
	return EE_hal_mrf24j40_set_ISR_mode(mode); 
} 

/*
	__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_config(int settings, int mode)
	This function configures mrf24j40 driver.
*/
__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_config(int settings, int mode)
{ 
    EE_mrf24j40_set_ISR_mode(EE_MRF24J40_RXTX_ISR);
	return EE_mrf24j40_spi_config(settings, mode); 
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


#endif //__EE_ZIGBEE_MRF24J40_H__

#endif //#ifdef __USE_MICO32BOARD_ZIGBEE_MRF24J40__
