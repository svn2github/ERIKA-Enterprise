/** 
* ee_i2c.h
*/

#ifndef __INCLUDE_EEMCUMICO32_I2C_H__
#define __INCLUDE_EEMCUMICO32_I2C_H__

#include "ee.h"
#include "cpu/mico32/inc/ee_irq.h"
#include <system_conf.h>
#include "mcu/mico32/inc/ee_buffer.h"
#include "mcu/mico32/inc/ee_i2c_internal.h"

/***************************************************************************
     *
     * I2C Component Register Structure
     * 
     * Note: The OpenCores I2C Master device has byte-aligned registers.
     *    However, modifications for LatticeMico32 (32-bit addressing)
     *    make the registers word-aligned (4-byte aligned).  Other than
     *    that, the register structure remains unchanged
     *
***************************************************************************/
//   typedef struct st_OCI2CMDev_t {
//        /* Prescale register: lower byte, R/W */
//        volatile unsigned int PrescaleLo;
//        /* Prescale register: upper byte, R/W */
//        volatile unsigned int PrescaleHi;
//        /* Control register: R/W */
//        volatile unsigned int Control;
//        /* Data register: read = rxdata, write = txdata */
//        volatile unsigned int Data;
//        /* Command/Status register: !!!read = status!!!, !!!write = command!!! */
//        volatile unsigned int StatusCommand;	
//    }OCI2CMDev_t;

/*************************************************** 
* Symbols and macros definition
****************************************************/
#define EE_I2C_MSGSIZE 				(1)		
#define EE_I2C_BUFSIZE 				(12)

/* i2c settings */
//...to do...

/* i2c return values */
#define EE_I2C_OK					(0)
#define EE_I2C_ERR_RECEPTION   		(-12)
#define EE_I2C_ERR_TRANSMISSION		(-13)
#define EE_I2C_ERR_BAD_VALUE		(-14)
#define EE_I2C_ERR_ADD_ACK			(-15)
#define EE_I2C_ERR_DATA_ACK			(-16)
#define EE_I2C_ERR_ARB_LOST			(-17)

/* i2c operating modes */
#define EE_I2C_POLLING				(0x00)
#define EE_I2C_RX_ISR				(0x01)
#define EE_I2C_TX_ISR				(0x02)	
#define EE_I2C_RXTX_ISR				(0x03)	
#define EE_I2C_RX_BLOCK				(0x10)
#define EE_I2C_TX_BLOCK				(0x20)
#define EE_I2C_RXTX_BLOCK  			(0x30)	


#define EE_i2c_need_init_rx_buf(old,new)  (!((old) & EE_I2C_RX_ISR) && ((new) & EE_I2C_RX_ISR))
#define EE_i2c_need_init_tx_buf(old,new)  (!((old) & EE_I2C_TX_ISR) && ((new) & EE_I2C_TX_ISR))
#define EE_i2c_need_enable_int(new)  ( ((new) & EE_I2C_RX_ISR) || ((new) & EE_I2C_TX_ISR) )
#define EE_i2c_tx_polling(mode) ( !((mode) & EE_I2C_TX_ISR) )
#define EE_i2c_rx_polling(mode) ( !((mode) & EE_I2C_RX_ISR) )

/* i2c utils */
// Slave Address
#define EE_I2C_RX_INT_MASK			()
#define EE_I2C_RW_MASK              (0x01) // 1=Read,0=Write
#define EE_I2C_ADDR_MASK            (0xFE)
// MACRO FOR WAITING TILL CURRENT TRANSFER IS IN PROGRESS (check TIP flag of the Status register)
#define EE_i2c_pend_for_TIP_done(ADDR)  \
    while( *(volatile unsigned int *)(ADDR + 0x10) & OCI2CM_STATUS_TRANSFER ) 
    
#define EE_I2C_NULL_CBK				((EE_ISR_callback)0)

////#define EE_i2c_init(name, per, set) 							EE_i2c_init_base((name##_BASE_ADDRESS), (per), (set))
////#define EE_i2c_set_ISR_callback(name, rx_isrcbk, tx_isrcbk, rx_buf, tx_buf) 	EE_i2c_set_ISR_callback_base((name##_BASE_ADDRESS), (name##_IRQ), (rx_isrcbk), (tx_isrcbk), (rx_buf), (tx_buf))
//#define EE_i2c_init(name, per, set, rx_isrcbk, tx_isrcbk, rx_buf, tx_buf) EE_i2c_init_base((name##_BASE_ADDRESS), (name##_IRQ), (per), (set), (rx_isrcbk), (tx_isrcbk), (rx_buf), (tx_buf))
//#define EE_i2c_disable(name) 									EE_i2c_disable_base((name##_BASE_ADDRESS))
//#define EE_i2c_enable(name) 									EE_i2c_enable_base((name##_BASE_ADDRESS))
//#define EE_i2c_start(name) 										EE_i2c_startbase((name##_BASE_ADDRESS))
//#define EE_i2c_stop(name) 										EE_i2c_stop_base((name##_BASE_ADDRESS))
//#define EE_i2c_write_byte(name, val) 							EE_i2c_write_byte_base((name##_BASE_ADDRESS), (val))
//#define EE_i2c_read_byte(name, addval) 							EE_i2c_read_byte_base((name##_BASE_ADDRESS), (addval))
//#define EE_i2c_write_buffer(name, vet, len) 					EE_i2c_write_buffer_base((name##_BASE_ADDRESS), (vet), (len))
//#define EE_i2c_read_buffer(name, vet, len) 						EE_i2c_read_buffer_base((name##_BASE_ADDRESS), (vet), (len))

/*************************************************** 
* Functions declarations
****************************************************/
//EE_UINT8 EE_i2c_init_base(EE_UINT32 base, EE_UINT32 speed, EE_UINT32 settings);
//EE_UINT8 EE_i2c_set_ISR_callback_base(EE_UINT32 base, EE_UINT32 irq_flag, EE_mico32_ISR_handler isr_rx_callback, EE_mico32_ISR_handler isr_tx_callback, EE_buffer* rx_buf, EE_buffer* tx_buf);
//EE_UINT8 EE_i2c_init_base(EE_UINT32 base, EE_UINT32 irq_flag, EE_UINT32 speed, EE_UINT32 settings, EE_mico32_ISR_handler isr_rx_callback, EE_mico32_ISR_handler isr_tx_callback, EE_buffer* rx_buf, EE_buffer* tx_buf);
//EE_UINT8 EE_i2c_disable_base(EE_UINT32 base);
//EE_UINT8 EE_i2c_enable_base(EE_UINT32 base);
//EE_UINT8 EE_i2c_start_base(EE_UINT32 base);
//EE_UINT8 EE_i2c_stop_base(EE_UINT32 base);
//EE_UINT8 EE_i2c_write_buffer_base(EE_UINT32 base, EE_UINT32 address, EE_INT8 *vet, EE_INT16 len);
//EE_UINT8 EE_i2c_write_byte_base(EE_UINT32 base, EE_UINT32 address, EE_INT8 data);
//EE_UINT8 EE_i2c_read_buffer_base(EE_UINT32 base, EE_UINT32 address, EE_INT8 *vet, EE_INT16 len);
//EE_UINT8 EE_i2c_read_byte_base(EE_UINT32 base, EE_UINT32 address, EE_INT8 *data)
//void EE_i2c_handler(EE_i2c_st* i2csp);

#endif // __INCLUDE_EEMCUMICO32_I2C_H__


/*************************************************** 
* Notes
****************************************************/
// Interrupt works only byte-by-byte data transfers...
//	The interface defines 3 transmission speeds:
//	- Normal: 100Kbps
//	- Fast: 400Kbps
//	- High speed: 3.5Mbps
//	Only 100Kbps and 400Kbps modes are supported directly. For High speed special IOs
//	are needed. If these IOs are available and used, then High speed is also supported.
