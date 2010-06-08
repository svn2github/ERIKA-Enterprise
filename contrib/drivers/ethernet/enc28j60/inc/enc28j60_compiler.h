/*
  Name: enc28j60_compiler.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: ENC28J60 driver header file for compiler settings.
*/

#ifndef __ENC28J60_COMPILER_H__
#define __ENC28J60_COMPILER_H__

/**
* Start Compiler Selection section
* \todo What is the global symbol for Erika Enterprise Kernel?
*/
#ifdef __ERIKA__		/* Erika Abstract Compiler */
#include <enc28j60_compiler_ee.h>

#else			/* No compiler */
#error "ENC28J60_HAL ERROR: compiler type not specified"

#endif	/* End Compiler Selection */

#endif /* Header Protection */
