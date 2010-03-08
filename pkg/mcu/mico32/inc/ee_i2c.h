/** 
* ee_i2c.h
*/

#ifndef __INCLUDE_EEMCUMICO32_I2C_H__
#define __INCLUDE_EEMCUMICO32_I2C_H__

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
//...
    

    
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
