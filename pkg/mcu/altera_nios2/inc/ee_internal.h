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
 * CVS: $Id: ee_internal.h,v 1.2 2008/07/21 16:46:40 francesco Exp $
 */

#include "mcu/altera_nios2/inc/ee_mcu.h"

#ifndef __INCLUDE_NIOSII_INTERNAL_H__
#define __INCLUDE_NIOSII_INTERNAL_H__

#include "altera_avalon_timer_regs.h"
#include "system.h"

/*************************************************************************
 Timers
 *************************************************************************/

/*
 * CBS
 */

#if defined(__CBS__) || defined(__IRIS__) || defined(__FRSH__)

/* This function set the capacity timer to raise in t ticks.
   In this implementation, timer1 is used to raise a capacity
   interrupt. The capacity interrupt is then programmed simply setting
   the delay into the timer1 counter. That is, whenever the timer
   fires, it restart counting down from 0xffffffff, and it will take a
   few seconds to do that. */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_capacityIRQ(EE_TIME t) 
{  
  if((EE_STIME)(t)<0) t=10;
  IOWR_ALTERA_AVALON_TIMER_CONTROL (TIMER_CAPACITY_BASE, 
            ALTERA_AVALON_TIMER_CONTROL_STOP_MSK);
  /* clear the interrupt */
  IOWR_ALTERA_AVALON_TIMER_STATUS (TIMER_CAPACITY_BASE, 0); 
  IOWR_ALTERA_AVALON_TIMER_PERIODH(TIMER_CAPACITY_BASE, (t >> 16));
  IOWR_ALTERA_AVALON_TIMER_PERIODL(TIMER_CAPACITY_BASE, (t & 0xFFFF));
  IOWR_ALTERA_AVALON_TIMER_CONTROL (TIMER_CAPACITY_BASE, 
            ALTERA_AVALON_TIMER_CONTROL_ITO_MSK  |
            ALTERA_AVALON_TIMER_CONTROL_CONT_MSK |
            ALTERA_AVALON_TIMER_CONTROL_START_MSK);  
} 

__INLINE__ void __ALWAYS_INLINE__ EE_hal_stop_budget_timer(void)
{
  IOWR_ALTERA_AVALON_TIMER_CONTROL (TIMER_CAPACITY_BASE, 
            ALTERA_AVALON_TIMER_CONTROL_STOP_MSK);
  /* clear the interrupt */
  IOWR_ALTERA_AVALON_TIMER_STATUS (TIMER_CAPACITY_BASE, 0); 
}

#endif

#if defined(__IRIS__) || defined(__FRSH__)

__INLINE__ void __ALWAYS_INLINE__ EE_hal_rechargingIRQ(EE_TIME t)
{
  if((EE_STIME)(t)<0) t=10;
  IOWR_ALTERA_AVALON_TIMER_CONTROL (TIMER_RECHARGING_BASE, 
            ALTERA_AVALON_TIMER_CONTROL_STOP_MSK);
  /* clear the interrupt */
  IOWR_ALTERA_AVALON_TIMER_STATUS (TIMER_RECHARGING_BASE, 0); 
  IOWR_ALTERA_AVALON_TIMER_PERIODH(TIMER_RECHARGING_BASE, (t >> 16));
  IOWR_ALTERA_AVALON_TIMER_PERIODL(TIMER_RECHARGING_BASE, (t & 0xFFFF));
  IOWR_ALTERA_AVALON_TIMER_CONTROL (TIMER_RECHARGING_BASE, 
            ALTERA_AVALON_TIMER_CONTROL_ITO_MSK  |
            ALTERA_AVALON_TIMER_CONTROL_CONT_MSK |
            ALTERA_AVALON_TIMER_CONTROL_START_MSK); 
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_stop_recharging_timer(void)
{
  IOWR_ALTERA_AVALON_TIMER_CONTROL (TIMER_RECHARGING_BASE, 
            ALTERA_AVALON_TIMER_CONTROL_STOP_MSK);
  /* clear the interrupt */
  IOWR_ALTERA_AVALON_TIMER_STATUS (TIMER_RECHARGING_BASE, 0); 
}

#endif

#endif
