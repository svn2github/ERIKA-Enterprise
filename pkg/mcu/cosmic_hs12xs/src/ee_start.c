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
 * Author: 2004 Paolo Gai
 * CVS: $Id: ee_start.c,v 1.17 2006/04/23 12:45:49 pj Exp $
 */

//#include "ee.h"
#include "ee_internal.h"
//#include "cpu/cosmic_hs12xs/inc/ee_irqstub.h"
//#include "ee_utils.h"

/* Include a file with the registers of the s12 micro-controller */ 
#ifdef __S12XS_INCLUDE_REGS__
#include "ee_hs12xsregs.h"
#endif

#if(EE_MAX_COUNTER>0)
volatile EE_UINT8 EE_timer0_initialized = 1;

//#define EE_TIMER0_STEP 250
#ifdef __OO_EXTENDED_STATUS__
int EE_cpu_startos(void)
#else
void EE_cpu_startos(void)
#endif
{
		///*	Timer0 Module
//		*/
//		TSCR1 = 0;
//		TFLG1 = 0x01;
//		//TCNT = 0;
//		TIOS |= 0x01;
//		TCTL2 &= 0xFC;
//		TCTL4 &= 0xFC;
//		TIE |= 0x01; 
//		OCPD |= 0x01;
//		_asm("cli");
//		INT_CFADDR = 0xEE;
//		INT_CFDATA0 = 0x01; 
//		TC0 = (int)(EE_TIMER0_STEP);		// 1ms -> Freq: 64MHz, Bus_clock: 32MHz, -> 32MHz/prescaler*1ms
//		TSCR2 = 0x03;	// prescaler 128
//		TSCR1 = 0x80; 
//		#ifdef __OO_EXTENDED_STATUS__
//  		return 0;
//		#endif
		#ifdef __OO_EXTENDED_STATUS__
			return EE_s12xs_hal_cpu_startos();	// 0 OK, 1 ERROR
		#else
			EE_s12xs_hal_cpu_startos();
		#endif	
}

//ISR2(T0_ISR)
//{
//	int val = TC0;
//	/* clear the interrupt source */
//	TFLG1 = 0x01;	// Clear interrupt flag
//
//	if (  ((signed)(TCNT-TC0)) > 0) 	// to avoid spurious interrupts...
//	{
//		do
//		{
//			CounterTick(SystemTimer);	// SystemTimer is a symbol defined in EE_utils.h
//			val += (int)(EE_TIMER0_STEP);
//   			TC0 = val;					// to manage critical courses...
//		}while( ((signed) (TCNT-val) ) >= 0);
//	}
//}
//
//#else
//ISR2(T0_ISR)
//{
//}

#else
volatile EE_UINT8 EE_timer0_initialized = 0;

#endif
