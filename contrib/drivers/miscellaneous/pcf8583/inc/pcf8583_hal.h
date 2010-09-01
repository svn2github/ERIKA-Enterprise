/** 
* @file pcf8583_hal.h
* @brief PCF8583 Light Sensor Driver
* @author Dario Di Stefano
* @date 2010-08-30
*
* This file is the definition of the hardware abstraction layer used by the 
* RTC pcf8583 device
*
* \todo Write something about the supported compilers.
*/

#ifndef __pcf8583_hal_h__
#define __pcf8583_hal_h__

#include <pcf8583_compiler.h>


/**
* Start HAL Selection section
* \todo What is the global symbol for Erika Enterprise Kernel?
*/
#ifdef __ERIKA__		/* Erika OS */

#include <ee.h>

#if defined	__MICROCHIP_PIC32__
#include <pcf8583_hal_ee_pic32.h>
#else
	#if defined __LM32__
	#include <pcf8583_hal_ee_mico32.h>
	#else /* NO Architecture */		
	#error "PCF8583_HAL: Architecture not supported"
	#endif
#endif

#else			/* No OS */

#error "PCF8583_HAL ERROR: OS not specified"

#endif	/* End OS Selection */

#endif /* Header Protection */
