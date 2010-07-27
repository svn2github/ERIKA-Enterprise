/*
  Name: enc28j60_hal.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: ENC28J60 driver header file for hal selection.
*/

#ifndef __enc28j60_hal_h__
#define __enc28j60_hal_h__

#include <enc28j60_compiler.h>

/**
* Start HAL Selection section
* \todo What is the global symbol for Erika Enterprise Kernel?
*/
#ifdef __ERIKA__		/* Erika OS */

#include <ee.h>

#if defined	__LM32__
#include <enc28j60_hal_ee_mico32.h>
#elif defined __PIC32__
#include <enc28j60_hal_ee_pic32.h>
#else		/* NO Architecture */
#error "ENC28J60_HAL: Architecture not supported"
#endif

#else			/* No OS */

#error "ENC28J60_HAL ERROR: OS not specified"

#endif	/* End OS Selection */

#endif /* Header Protection */
