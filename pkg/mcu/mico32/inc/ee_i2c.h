/** 
* ee_i2c.h
*/

#ifndef __INCLUDE_EEMCUMICO32_I2C_H__
#define __INCLUDE_EEMCUMICO32_I2C_H__

#include "ee.h"
#include "cpu/mico32/inc/ee_irq.h"
#include <system_conf.h>
#include "OpenCoresI2CMaster.h"
#include "mcu/mico32/inc/ee_buffer.h"

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
//        /* Command/Status register: read = status, write = command */
//        volatile unsigned int StatusCommand;
//    }OCI2CMDev_t;

/*************************************************** 
* Symbols and macros definition
****************************************************/
//#define DEFAULT_BRG 0xC6
//#define DEFAULT_FLAGS 0x0
//#define EE_I2C_ERR_BAD_PORT -1

// Slave Address
#define OCI2CM_RW_MASK                  (0x01) // 1=Read,0=Write
#define OCI2CM_ADDR_MASK                (0xFE)
/* MACRO FOR WAITING TILL CURRENT TRANSFER IS IN PROGRESS */
#define OCI2CM_PEND_FOR_TIP_DONE(ADDR)  \
    while( *(volatile unsigned int *)(ADDR + 0x10) & OCI2CM_STATUS_TRANSFER )


#define EE_i2c_init(name, per, set) 							EE_i2c_init_base((name##_BASE_ADDRESS), (per), (set))
#define EE_i2c_set_callback(name, rx_isrcbk, tx_isrcbk) 		EE_i2c_set_callback_base((name##_BASE_ADDRESS), (rx_isrcbk), (tx_isrcbk))
#define EE_i2c_close(name) 									EE_i2c_close_base((name##_BASE_ADDRESS))
#define EE_i2c_write_byte(name, val, buf) 						EE_i2c_write_byte_base((name##_BASE_ADDRESS), (val), (buf))
#define EE_i2c_read_byte(name, addval, buf) 					EE_i2c_read_byte_base((name##_BASE_ADDRESS), (addval), (buf))
#define EE_i2c_write_buffer(name, vet, len, buf) 				EE_i2c_write_buffer_base((name##_BASE_ADDRESS), (vet), (len), (buf))
#define EE_i2c_read_buffer(name, vet, len, buf) 				EE_i2c_read_buffer_base((name##_BASE_ADDRESS), (vet), (len), (buf))


/*************************************************** 
* Functions declarations
****************************************************/
EE_UINT8 EE_i2c_init_base(EE_UINT32 base, EE_UINT32 speed, EE_UINT32 settings, EE_mico32_ISR_handler isr_callback);
EE_UINT8 EE_i2c_disable_base(EE_UINT32 base);
EE_UINT8 EE_i2c_enable_base(EE_UINT32 base);
EE_UINT8 EE_i2c_start_base(EE_UINT32 base);
EE_UINT8 EE_i2c_stop_base(EE_UINT32 base);
EE_UINT8 EE_i2c_write_buffer_base(EE_UINT32 base, unsigned int address, unsigned int buffersize, unsigned char *data);
EE_UINT8 EE_i2c_write_byte_base(EE_UINT32 base, unsigned int address, unsigned char data);
EE_UINT8 EE_i2c_read_buffer_base(EE_UINT32 base, unsigned int address, unsigned int buffersize, unsigned char *data);
EE_UINT8 EE_i2c_read_byte_base(EE_UINT32 base, unsigned int address, unsigned char *data);


#endif // __INCLUDE_EEMCUMICO32_I2C_H__


/*************************************************** 
* Notes
****************************************************/
//	The interface defines 3 transmission speeds:
//	- Normal: 100Kbps
//	- Fast: 400Kbps
//	- High speed: 3.5Mbps
//	Only 100Kbps and 400Kbps modes are supported directly. For High speed special IOs
//	are needed. If these IOs are available and used, then High speed is also supported.
