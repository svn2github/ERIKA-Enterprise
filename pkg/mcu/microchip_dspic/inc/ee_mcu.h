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

#include "mcu/microchip_dspic/inc/ee_mcuregs.h"

#ifndef __INCLUDE_MICROCHIP_DSPIC_MCU_H__
#define __INCLUDE_MICROCHIP_DSPIC_MCU_H__

/*************************************************************************
 Time handling
 *************************************************************************/

/*
 * Time handling on the dsPIC33 is made by using timer T8 and T9 as a
 * 32 bit register value to have a bigger lifetime.
 */

/* Time types
 *
 * This is the type used to store the circular timer. It is in the MCU
 * because it highly depends on the hardware timers which are present 
 * in a particular microcontroller version.
 *
 * There are two TIME types, an unsigned type, typically used to store
 * time values since they are read from a register which is
 * traditionally considered as unsigned, and a signed type, which is
 * used in the EDF comparisons.
 */

#ifndef EE_TIME
#define EE_TIME EE_UINT32
#endif

#ifndef EE_STIME
#define EE_STIME EE_INT32
#endif

#define EE_TIMER_MINCAPACITY 5000
#define EE_TIMER_MAXFUTUREVALUE    0x7fffffff
#define EE_TIMER_LIFETIME          0xffffffff

/* compile these functions only if TMR8 is available on the
   particular microcontroller */
#ifdef __PIC30_HAS_TMR8__

/* This function initializes the timer T8 and T9 as freerunning.
   Timer T8 and T9 will be used to get the timing reference for the
   circular timer in EDF.
*/
#ifndef __PRIVATE_TIME_INIT__
__INLINE__ void __ALWAYS_INLINE__ EE_time_init(void)
{
  T8CON = 0;          /* Stops the Timer8 and reset control reg	*/
  T8CONbits.T32 = 1;  /* Set Timer8 in 32bit mode */
  TMR8  = 0;          /* Clear contents of the timer registers	*/
  TMR9  = 0;
  PR8   = 0xffff;     /* Load the Period registers wit the value 0xffffffff */
  PR9   = 0xffff;
  IFS3bits.T9IF  = 0; /* Clear the Timer9 interrupt status flag	*/
  IEC3bits.T9IE  = 0; /* Clear Timer9 interrupts		*/
  T8CONbits.TON  = 1; /* Start Timer8 with prescaler settings at 1:1
		       * and clock source set to the internal 
		       * instruction cycle			*/
}

#endif

/*
 * The function gets the current time by concatenating two timer values.
 *
 * Note: we must take care of the correctness of the value in case of
 * overflow!
 */
#ifndef __PRIVATE_HAL_GETTIME__
__INLINE__ EE_TIME __ALWAYS_INLINE__ EE_hal_gettime(void)
{
  union {
    struct { EE_UREG low, hi; } lowhi;
    EE_TIME time;
  } retvalue;
  
  // I split the reading to guarantee that in any case TMR8 will be
  // read before TMR9. In this way, the TMR9 hold register will be
  // read correctly!

  retvalue.lowhi.low = TMR8;
  retvalue.lowhi.hi = TMR9;
  return retvalue.time;
}
#endif

#if defined(__FRSH__)

/* This function is used to initialize the two timers used for handling
 * budget exaustion and the recharging queue in FRSH
 */
__INLINE__ void __ALWAYS_INLINE__ EE_frsh_time_init(void)
{
  T4CON = 0; 
  T4CONbits.T32 = 1;  /* Set Timer6 in 32bit mode */ 
  TMR4  = 0;          /* Clear contents of the timer registers	*/
  TMR5  = 0;
  IFS1bits.T5IF  = 0; /* Clear the Timer9 interrupt status flag	*/
  _T5IE = 1; // Enable interrupt for Timer 4/5
  
  T6CON = 0;          /* Stops the Timer6 and reset control reg	*/
  T6CONbits.T32 = 1;  /* Set Timer6 in 32bit mode */
  TMR6  = 0;          /* Clear contents of the timer registers	*/
  TMR7  = 0;
  IFS3bits.T7IF  = 0; /* Clear the Timer7 interrupt status flag	*/
  _T7IE = 1; // Enable interrupt for Timer 6/7
}

#endif

#else

/* If you are using EDF with a MCU without TMR8, then put a warning! */
#ifdef __EDF__
#ifndef __PRIVATE_TIME_INIT__
#warning Please provide a custom EE_time_init because the MCU you are using does not have TMR8!
#endif
#ifndef __PRIVATE_HAL_GETTIME__
#warning Please provide a custom EE_hal_gettime because the MCU you are using does not have TMR8!
#endif
#endif

#endif

/* 
 * Hard timers related stuffs
 * with hard alarms the logical timer identifier 0
 * corresponds to the TMR8/9 (system timer) and TMR 4/5
 * for the hard alarm interrupt   
 */
#ifdef __HARD_ALARMS__
#if (1 < EE_N_HARD_ALARMS)
#error "too many hard alarms!!!"
#else

__INLINE__ EE_TIME __ALWAYS_INLINE__ EE_hal_init_timer()
{
  T8CON = 0;          /* Stops the Timer8 and reset control reg	*/
  T8CONbits.T32 = 1;  /* Set Timer8 in 32bit mode */
  TMR8  = 0;          /* Clear contents of the timer registers	*/
  TMR9  = 0;
  IFS3bits.T9IF  = 0; /* Clear the Timer9 interrupt status flag	*/
  IEC3bits.T9IE  = 0; /* Clear Timer9 interrupts		*/
  T8CONbits.TON  = 1; /* Start Timer8 with prescaler settings at 1:1 */
  
  T4CON = 0;  
  TMR4  = 0;          /* Clear contents of the timer registers	*/
  TMR5  = 0;
  PR4 = PR5 = 0xFFFF; 
  T4CON = 0x0008;  // Timer 4/5 as a 32 bit timer. Timer stop.
  _T5IE = 1; // Enable interrupt for Timer 4/5
}

__INLINE__ EE_TIME __ALWAYS_INLINE__ EE_hal_read_timer (EE_SREG timer)
{
  switch(timer){
    case 0:
    {
      union {
        struct { EE_UREG low, hi; } lowhi;
        EE_TIME time;
      } retvalue;
  
  // I split the reading to guarantee that in any case TMR8 will be
  // read before TMR9. In this way, the TMR9 hold register will be
  // read correctly!

      retvalue.lowhi.low = TMR8;
      retvalue.lowhi.hi = TMR9;
      return retvalue.time;
    }
    break;
    case 1:; //TODO
  }
}

/* This function have to set next capcom trigger
 * if there isn't an already set interrupt flag
 * with hard alarms the logical timer identifier 0
 * corresponds to the TMR8/9 (system timer) and TMR 4/5
 * for the hard alarm interrupt    
 */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_set_timer (EE_SREG timer, EE_TIME value)
{
  switch(timer){
    case 0:
    {
      PR4 = value & 0xFFFF;
      PR5 = value >> 16;
      TMR4 = 0;
      TMR5 = 0;
      _T5IE = 1; // Enable interrupt for Timer 4/5
      T4CONbits.TON = 1; // Start Timer 4/5;
    }
    break;
    case 1:; //TODO 
  }
}
#endif
#endif

#endif
