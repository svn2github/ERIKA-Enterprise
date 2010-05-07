/*
  Name: ee_i2c.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.28
  Description: I2C header file. 
*/

#ifndef __INCLUDE_EEMCUMICO32_I2C_H__
#define __INCLUDE_EEMCUMICO32_I2C_H__

#include "mcu/mico32/inc/ee_i2c_internal.h"

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
