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
 * Author: Dario Di Stefano
 */
 
#include "eecfg.h"
#include "cpu/hs12xs/inc/ee_cpu.h"

#ifndef __INCLUDE_FREESCALE_S12XS_MCU_H__
#define __INCLUDE_FREESCALE_S12XS_MCU_H__

/* Include a file with the registers of the s12 micro-controller */ 
#include "mcu/hs12xs/inc/ee_mcuregs.h"

/* Functions and Utilities */

extern volatile unsigned int ee_s12_peripheral_frequency_mhz;
#define EE_get_peripheral_frequency_mhz()    ee_s12_peripheral_frequency_mhz
#define EE_set_peripheral_frequency_mhz(mhz) ee_s12_peripheral_frequency_mhz = mhz


/*************************************************************************
 System startup
 *************************************************************************/
#ifdef __OO_CPU_HAS_STARTOS_ROUTINE__
 
 /* This function starts ths system,
 * register the IPIC and synchronize the CPUs 
 * returns 1 in case of error (typically a mutex name error)
 */
#ifdef __OO_EXTENDED_STATUS__
int EE_cpu_startos(void);
#else
void EE_cpu_startos(void);
#endif	/* __OO_EXTENDED_STATUS__ */


#if(EE_MAX_COUNTER>0)
/* defining this let the StartOS routine to call this function 
#ifndef __OO_CPU_HAS_STARTOS_ROUTINE__
#define __OO_CPU_HAS_STARTOS_ROUTINE__
#endif
*/

/*************************************************************************
 Time handling
 *************************************************************************/

/*
 * Time handling on the s12 is made by using timer T0 as a
 * 16 bit register value to have a bigger lifetime.
 */

#ifndef EE_TIMER0_COUNTER

/* Timer0 module */
#define EE_TIMER0_COUNTER
/*
#define EE_PRESCALE_FACTOR_128 		7
#define EE_PRESCALE_FACTOR_64 		6
#define EE_PRESCALE_FACTOR_32 		5
#define EE_PRESCALE_FACTOR_16 		4
#define EE_PRESCALE_FACTOR_8 		3
#define EE_PRESCALE_FACTOR_4 		2
#define EE_PRESCALE_FACTOR_2 		1
#define EE_PRESCALE_FACTOR_1 		0
*/
/* EE_TIMER_PRESCALER		es. 128 */
//extern unsigned int EE_TIMER_PRESCALER;
/* EE_PRESCALE_FACTOR		es. EE_PRESCALE_FACTOR_128 */
//extern unsigned int EE_PRESCALE_FACTOR;
/* EE_BUS_CLOCK				es. 32000000 */
//extern unsigned long int EE_BUS_CLOCK; 
/* EE_TIMER_PERIOD			es. 1 in ms */
extern unsigned int EE_TIMER_PERIOD;
//#define EE_TIMER0_STEP 			(((unsigned long int)(EE_BUS_CLOCK))/((unsigned long int)(EE_TIMER_PRESCALER))*((unsigned long int)(EE_TIMER_PERIOD)))/((unsigned long int)(1000))	/* es. 250 */
extern unsigned int EE_TIMER0_STEP;

#define EE_s12_hal_cpu_startos()\
		EE_timer_init_ms(EE_TIMER_0, EE_TIMER_PERIOD, EE_TIMER_ISR_ON);\
		EE_TIMER0_STEP = TC0;\
		EE_timer_start()

#if 0
__INLINE__ int __ALWAYS_INLINE__ EE_s12_hal_cpu_startos( void )
{
	EE_timer_init_ms(EE_TIMER_0, EE_TIMER_PERIOD, EE_TIMER_ISR_ON);
	EE_TIMER0_STEP = TC0;
	EE_timer_start();
	return 0;

	TSCR1 = 0;							/* turn off Timer0 module */
	TFLG1 = 0x01;						/* clear isr flag */
	TCNT = 0;							/* clear Timer0 counter */
	TIOS |= 0x01;						/* output compare mode */
	TCTL2 &= 0xFC;						/* do not use pins */
	TCTL4 &= 0xFC;						/* do not use pins */
	TIE |= 0x01; 						/* enable interrupt */
	OCPD |= 0x01;						/* disable Timer0 channel port  */
	_asm("cli");						/* cli */
	INT_CFADDR = 0xE0;					/* set base address */
	INT_CFDATA7 = 0x01; 				/* set priority */
	TC0 = (unsigned int)(EE_TIMER0_STEP);			/* 1ms -> Freq: 64MHz, Bus_clock: 32MHz, -> 32MHz/prescaler*1ms */
	TSCR2 = (unsigned char)(EE_PRESCALE_FACTOR);	/* prescaler 128 */
	TSCR1 = 0x80; 						/* turn on Timer0 module */
	return 0;
}
#endif


#endif	/* TIMER0_COUNTER */

#else	/* EE_MAX_COUNTER>0 */
  #define EE_s12_hal_cpu_startos() do{}while(0)
#endif	/* EE_MAX_COUNTER>0 */

#else	/* __OO_CPU_HAS_STARTOS_ROUTINE__ */
  #define EE_s12_hal_cpu_startos() do{}while(0)
#endif	/* __OO_CPU_HAS_STARTOS_ROUTINE__ */

#endif	/* __INCLUDE_FREESCALE_S12XS_MCU_H__ */
