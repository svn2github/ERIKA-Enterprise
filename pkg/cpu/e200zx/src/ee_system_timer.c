/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
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
 * Author: 2012  Errico Guidieri
 */

#include <ee_internal.h>
#include <ee_api.h>
#include <ee_irq.h>

/* This file is needed only if System Timer is defined */
#ifdef ENABLE_SYSTEM_TIMER


#ifndef EE_PPCE200ZX_DECREMENTER_ISR
#ifdef EE_ISR_DYNAMIC_TABLE
/* Decrementer level inside ISR table */
#define EE_DECREMENTER_LEVEL    10
/* Priority doesn't make sense for internal exceptions so 0 is a value as
   another */
#define EE_DECREMENTER_PRIORITY 0
/* Default system timer handler for dynamic ISR table */
#define EE_PPCE200ZX_DECREMENTER_ISR EE_e200zx_system_timer_handler
#else /* EE_ISR_DYNAMIC_TABLE */
/* You must define system timer handler as compilation define with static ISR
   table
*/
#error "if SystemTimer is defined yo must define EE_PPCE200ZX_DECREMENTER_ISR\
 with the name of the handler for static ISR table"
#endif /* EE_ISR_DYNAMIC_TABLE */
#endif /* !EE_PPCE200ZX_DECREMENTER_ISR */

/* Handler Declaration */
void EE_PPCE200ZX_DECREMENTER_ISR(void);

#ifdef EE_ISR_DYNAMIC_TABLE
void EE_PPCE200ZX_DECREMENTER_ISR(void)
#else
ISR2_INT(EE_PPCE200ZX_DECREMENTER_ISR)
#endif
{
#if defined(__OO_BCC1__) || defined(__OO_BCC2__) || defined(__OO_ECC1__) || \
    defined(__OO_ECC2__) || defined(__AS_SC4__)
  SystemTick();
#else
  CounterTick(EE_SYSTEM_TIMER);
#endif
}

/* System Timer Initialization */
void EE_e200zx_initialize_system_timer(void) {
#ifdef EE_ISR_DYNAMIC_TABLE
  EE_e200z7_register_ISR(EE_DECREMENTER_LEVEL, EE_PPCE200ZX_DECREMENTER_ISR,
    EE_DECREMENTER_PRIORITY);
#endif /* EE_ISR_DYNAMIC_TABLE */

  EE_e200z7_setup_decrementer((EE_CPU_CLOCK + 
    EE_counter_hw_ROM[EE_SYSTEM_TIMER].microsecondspertick/2U) / 
    EE_counter_hw_ROM[EE_SYSTEM_TIMER].microsecondspertick);
}

#endif /* ENABLE_SYSTEM_TIMER */
