/** 
* @file ozb_compiler.h
* @brief OpenZB Abstract Compiler
* @author Christian Nastasi
* @date 2009-03-22
*
* This file is the definition of the abstract compiler used by all the module
* of the OpenZB library. 
*
* \todo Write something about the supporte compiler.
*/
#ifndef __ozb_compiler_h__
#define __ozb_compiler_h__

/**
* Start Compiler Selection section
* \todo What is the global symbol for Erika Enterprise Kernel?
*/
#ifdef __ERIKA__	/* Erika Abstract Compiler */
#include <ee.h>
#include <hal/ozb_compiler_ee.h>

#elif defined __C30__ 	/* Microchip C30 */
#include <hal/ozb_compiler_c30.h>

#else			/* No compiler */
#error "OZB_HAL ERROR: compiler type not specified"

#endif	/* End Compiler Selection */

#endif /* Header Protection */
