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
 * Author: 2012 Errico Guidieri
 */

#ifndef __PRIVATE_SYSTICK__

#include <ee_internal.h>

void EE_oo_sys_tick(void) {
  /* Array to hold ticksperbase counters */
  static EE_TYPETICK EE_oo_counter_ticksperbase_counters[EE_MAX_COUNTER];

  register EE_FREG flag;
  register EE_UREG i;
  /* register EE_TYPETICK systick_value; */
  register EE_TYPETICK ticksperbase;

  flag = EE_hal_begin_nested_primitive();

  /* Increment the system timer */
  EE_oo_counter_tick(EE_SYSTEM_TIMER);

  /* systick_value = EE_oo_counter_ROM[EE_SYSTEM_TIMER].value; */
  
  /* Loop to increment counters tied with system timer (the ones with ticksperbase != 0) */
  /* I Start from EE_SYSTEM_TIMER + 1 because EE_SYSTEM_TIMER is always the
     first timer (So implicitly EE_SYSTEM_TIMER it's forced to be 0U)*/
  for(i=(EE_SYSTEM_TIMER + 1U); i < EE_MAX_COUNTER; ++i) {
    /* register EE_TYPETICK counter_ticksperbase_value; */
    ticksperbase = EE_counter_ROM[i].ticksperbase;
    /* If ticksperbase == 0 the counter is not tied to the system timer */
    if(ticksperbase != 0U /* TODO: check default */) {
      if(++EE_oo_counter_ticksperbase_counters[i] == ticksperbase) {
        EE_oo_counter_tick(i);
        EE_oo_counter_ticksperbase_counters[i] = 0U;
      }
      /* //!!! THIS IMPLEMENTATION NEED EE_oo_counter_ticksperbase_counters
         //INITIALIZATION WITH ticksperbase COUNTER VALUES !!!.
      counter_ticksperbase_value = EE_oo_counter_ticksperbase_counters[i];
      if(systick_value == counter_ticksperbase_value) {
        EE_oo_counter_tick(i);
        if(counter_ticksperbase_value <= (EE_oo_counter_ROM[EE_SYSTEM_TIMER].
            maxallowedvalue - ticksperbase))
          //NOT WRAP AROUND
          EE_oo_counter_ticksperbase_counters[i] += ticksperbase;
        else {
          //COUNTER WRAP AROUND
          EE_oo_counter_ticksperbase_counters[i] = ticksperbase - 
            (EE_oo_counter_ROM[EE_SYSTEM_TIMER].maxallowedvalue -
              systick_value);
        }
      }
      */
    }
  }
  
  EE_hal_end_nested_primitive(flag);
}

#endif /* __PRIVATE_SYSTICK__ */

