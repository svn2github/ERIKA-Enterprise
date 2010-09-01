/** 
* @file pcf8583_compiler_ee.h
* @brief PCF8583 real time clock Driver
* @author Dario Di Stefano 
* @date 2010-08-30
*
* Using the Erika Enterprise abstraction for the compiler.
*/

#ifndef __pcf8583_compiler_ee_h__
#define __pcf8583_compiler_ee_h__

#include <ee.h>
#include "../../../../misc/inc/ee_stdint.h"

#ifndef COMPILER_INLINE 
#define COMPILER_INLINE __INLINE__
#endif

#ifndef COMPILER_ISR
#define COMPILER_ISR(func) ISR2(func)
#endif

#endif /* Header Protection */
