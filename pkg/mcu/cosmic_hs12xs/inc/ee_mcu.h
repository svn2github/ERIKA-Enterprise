/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation, 
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/*
 * Author: 2006 Paolo Gai
 * CVS: $Id: ee_mcu.h,v 1.9 2008/07/14 10:40:17 pj Exp $
 */

//#include "mcu/cosmic_hs12xs/inc/ee_mcuregs.h"
#include "eecfg.h"
#include "cpu/cosmic_hs12xs/inc/ee_cpu.h"

#ifndef __INCLUDE_FREESCALE_S12XS_MCU_H__
#define __INCLUDE_FREESCALE_S12XS_MCU_H__

/* Include a file with the registers of the s12 micro-controller */ 
#ifdef __S12XS_INCLUDE_REGS__
#include "ee_hs12xsregs.h"
#endif

#ifdef __USE_PIT__
#include "mcu/cosmic_hs12xs/inc/ee_pit.h"
#endif

#ifdef __USE_SCI__
#include "mcu/cosmic_hs12xs/inc/ee_sci.h"
#endif

/*************************************************************************
 System startup
 *************************************************************************/

#if(EE_MAX_COUNTER>0)
/* defining this let the StartOS routine to call this function */
#ifndef __OO_CPU_HAS_STARTOS_ROUTINE__
#define __OO_CPU_HAS_STARTOS_ROUTINE__	// Symbol defined in eeopt.h
#endif
/* This function starts ths system,
 * register the IPIC and synchronize the CPUs 
 * returns 1 in case of error (typically a mutex name error)
 */
#ifdef __OO_EXTENDED_STATUS__
int EE_cpu_startos(void);
#else
void EE_cpu_startos(void);
#endif	// __OO_EXTENDED_STATUS__

/*************************************************************************
 Time handling
 *************************************************************************/

/*
 * Time handling on the s12 is made by using timer T0 as a
 * 16 bit register value to have a bigger lifetime.
 */

#ifndef EE_TIMER0_COUNTER
///*
//*	Timer0 module
//*/
#define EE_TIMER0_COUNTER
#define EE_PRESCALE_FACTOR_128 		7
#define EE_PRESCALE_FACTOR_64 		6
#define EE_PRESCALE_FACTOR_32 		5
#define EE_PRESCALE_FACTOR_16 		4
#define EE_PRESCALE_FACTOR_8 		3
#define EE_PRESCALE_FACTOR_4 		2
#define EE_PRESCALE_FACTOR_2 		1
#define EE_PRESCALE_FACTOR_1 		0

//#define EE_TIMER_PRESCALER		128
extern unsigned int EE_TIMER_PRESCALER;
//#define EE_PRESCALE_FACTOR		EE_PRESCALE_FACTOR_128
extern unsigned int EE_PRESCALE_FACTOR;
//#define EE_BUS_CLOCK			32e6
extern double EE_BUS_CLOCK; 
//#define EE_TIMER_PERIOD			1e-3
extern double EE_TIMER_PERIOD; 
#define EE_TIMER0_STEP 			((double)(EE_BUS_CLOCK))/((double)(EE_TIMER_PRESCALER))*((double)(EE_TIMER_PERIOD))	///250

//#ifndef __EECFG_THIS_IS_ASSEMBLER__
static @inline int EE_s12xs_hal_cpu_startos( void )
{
		TSCR1 = 0;							// turn off Timer0 module
		TFLG1 = 0x01;						// clear isr flag
		TCNT = 0;							// clear Timer0 counter
		TIOS |= 0x01;						// output compare mode
		TCTL2 &= 0xFC;						// do not use pins
		TCTL4 &= 0xFC;						// do not use pins
		TIE |= 0x01; 						// enable interrupt
		OCPD |= 0x01;						// disable Timer0 channel port 
		_asm("cli");						// cli
		INT_CFADDR = 0xEE;					// set base address
		INT_CFDATA0 = 0x01; 				// set priority
		TC0 = (int)(EE_TIMER0_STEP);		// 1ms -> Freq: 64MHz, Bus_clock: 32MHz, -> 32MHz/prescaler*1ms
		TSCR2 = (int)(EE_PRESCALE_FACTOR);	// prescaler 128
		TSCR1 = 0x80; 						// turn on Timer0 module

  		return 0;
}
//#endif	//__EECFG_THIS_IS_ASSEMBLER__

#endif	//TIMER0_COUNTER

#endif	//EE_MAX_COUNTER>0

#endif	//__INCLUDE_FREESCALE_S12XS_MCU_H__
