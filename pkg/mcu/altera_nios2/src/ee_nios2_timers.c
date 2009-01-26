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
 * CVS: $Id: ee_mcu.h,v 1.2 2008/07/24 14:26:55 francesco Exp $
 */

#include "altera_avalon_timer_regs.h"
#include "system.h"
#include "ee_internal.h"

#ifndef __PRIVATE_TIME_INIT__
void EE_time_init(void)
{
  IOWR_ALTERA_AVALON_TIMER_PERIODH(TIMER_SYSTEM_BASE, 0xFFFF);
  IOWR_ALTERA_AVALON_TIMER_PERIODL(TIMER_SYSTEM_BASE, 0xFFFF);
  IOWR_ALTERA_AVALON_TIMER_CONTROL (TIMER_SYSTEM_BASE, 
            ALTERA_AVALON_TIMER_CONTROL_CONT_MSK |
            ALTERA_AVALON_TIMER_CONTROL_START_MSK);
}

#endif

#ifndef __PRIVATE_HAL_GETTIME__
EE_TIME EE_hal_gettime(void)
{
  union {
    struct { EE_UINT16 low, hi; } lowhi;
    EE_TIME time;
  } retvalue;
  IOWR(TIMER_SYSTEM_BASE, ALTERA_AVALON_TIMER_SNAPH_REG, 0xFFFF);

  retvalue.lowhi.low = IORD_ALTERA_AVALON_TIMER_SNAPL(TIMER_SYSTEM_BASE);
  retvalue.lowhi.hi = IORD_ALTERA_AVALON_TIMER_SNAPH(TIMER_SYSTEM_BASE);
  retvalue.time = 0xFFFFFFFF - retvalue.time;
  
  return retvalue.time;
}
#endif

#if defined(__FRSH__)


void EE_nios2_IRQ_budget(void* context, alt_u32 id)
{
  /* clear the interrupt */
  IOWR_ALTERA_AVALON_TIMER_STATUS (TIMER_CAPACITY_BASE, 0);

  EE_frsh_IRQ_budget();
}

void EE_nios2_IRQ_recharging(void* context, alt_u32 id)
{
  /* clear the interrupt */
  IOWR_ALTERA_AVALON_TIMER_STATUS (TIMER_RECHARGING_BASE, 0);

  EE_frsh_IRQ_recharging();
}

/* This function is used to initialize the two timers used for 
 * budget exaustion and for the recharging queue
 */
void EE_frsh_time_init(void)
{
  IOWR_ALTERA_AVALON_TIMER_PERIODH(TIMER_CAPACITY_BASE, 0xFFFF);
  IOWR_ALTERA_AVALON_TIMER_PERIODL(TIMER_CAPACITY_BASE, 0xFFFF);
  IOWR_ALTERA_AVALON_TIMER_CONTROL (TIMER_CAPACITY_BASE, 
            ALTERA_AVALON_TIMER_CONTROL_ITO_MSK  |
            ALTERA_AVALON_TIMER_CONTROL_CONT_MSK |
            ALTERA_AVALON_TIMER_CONTROL_STOP_MSK);

  alt_irq_register (TIMER_CAPACITY_IRQ, NULL, EE_nios2_IRQ_budget);    

  
  IOWR_ALTERA_AVALON_TIMER_PERIODH(TIMER_RECHARGING_BASE, 0xFFFF);
  IOWR_ALTERA_AVALON_TIMER_PERIODL(TIMER_RECHARGING_BASE, 0xFFFF);
  IOWR_ALTERA_AVALON_TIMER_CONTROL (TIMER_RECHARGING_BASE, 
            ALTERA_AVALON_TIMER_CONTROL_ITO_MSK  |
            ALTERA_AVALON_TIMER_CONTROL_CONT_MSK |
            ALTERA_AVALON_TIMER_CONTROL_STOP_MSK);

  alt_irq_register (TIMER_RECHARGING_IRQ, NULL, EE_nios2_IRQ_recharging);    
}

#endif





#if defined(__CBS__) || defined(__FRSH__)
void EE_hal_set_nios2_timer(EE_UINT32 base, EE_TIME t) 
{
  union {
    struct { EE_UINT16 low, hi; } lowhi;
    EE_TIME time;
  } retvalue;


  /* stop the timer */
  IOWR_ALTERA_AVALON_TIMER_CONTROL (base, 
            ALTERA_AVALON_TIMER_CONTROL_STOP_MSK);

  /* clear the interrupt */
  IOWR_ALTERA_AVALON_TIMER_STATUS (base, 0); 

  /* set the next period */
  retvalue.time = t;
  IOWR_ALTERA_AVALON_TIMER_PERIODH(base, (retvalue.lowhi.hi));
  IOWR_ALTERA_AVALON_TIMER_PERIODL(base, (retvalue.lowhi.low));

  /* restart the timer */
  IOWR_ALTERA_AVALON_TIMER_CONTROL (base, 
            ALTERA_AVALON_TIMER_CONTROL_ITO_MSK  |
            ALTERA_AVALON_TIMER_CONTROL_CONT_MSK |
            ALTERA_AVALON_TIMER_CONTROL_START_MSK);  
} 

void EE_hal_stop_nios2_timer(EE_UINT32 base)
{
  IOWR_ALTERA_AVALON_TIMER_CONTROL (base, 
            ALTERA_AVALON_TIMER_CONTROL_STOP_MSK);
  /* clear the interrupt */
  IOWR_ALTERA_AVALON_TIMER_STATUS (base, 0); 
}

#endif
