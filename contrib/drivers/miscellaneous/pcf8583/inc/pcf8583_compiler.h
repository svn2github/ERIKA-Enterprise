/** 
* @file pcf8583_compiler.h
* @brief PCF8583 real time clock Driver
* @author Dario Di Stefano 
* @date 2010-08-30
*
* This file is the definition of the abstract compiler used by all the module
* of the pcf8583 library. 
*
* \todo Write something about the supported compiler.
*/
#ifndef __PCF8583_COMPILER_H__
#define __PCF8583_COMPILER_H__

/**
* Start Compiler Selection section
* \todo What is the global symbol for Erika Enterprise Kernel?
*/
#ifdef __ERIKA__		/* Erika Abstract Compiler */
#include "pcf8583_compiler_ee.h"

#else			/* No compiler */
#error "PCF8583_HAL ERROR: compiler type not specified"

#endif	/* End Compiler Selection */

#endif /* Header Protection */
