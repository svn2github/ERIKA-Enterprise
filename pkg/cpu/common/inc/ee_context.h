/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2009  Evidence Srl
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
 * Context switch functions used in HAL implementations, to be included by a
 * specific ee_internal.h header.
 * Derived from pkg/cpu/pic30/inc/ee_internal.h
 * Author: 2009 Bernardo Dal Seno
 */


#ifndef __INCLUDE_CPU_COMMON_EE_CONTEXT__
#define __INCLUDE_CPU_COMMON_EE_CONTEXT__


/* After a task terminates, the scheduler puts the new thread and the new stack
 * into these variables.  They represents the new context to switch to. */
extern EE_FADDR EE_hal_endcycle_next_thread;
extern EE_UREG EE_hal_endcycle_next_tos;

/* These must be implemented in ASM; no standard implementation, sorry.  This is
 * the only function that performs context switching.  The _multi version
 * doesn't jump to a new address if 'thread_addr' is NULL.  This is used to
 * switch to a thread that has been suspend by a call to
 * EE_std_change_contex_multi() */
void EE_std_change_context_mono(EE_FADDR thread_addr);
void EE_std_change_context_multi(EE_FADDR thread_addr, EE_UREG tos_index);
/* Pseudo code for EE_std_change_context_multi():
   save_caller_saved_registers();
   switch_stacks(tos_index);
   restore_caller_saved_registers();
   if (thread_addr != 0) {
      enable_interrupts();
      save_registers_you_care_about();
      call_function(thread_addr);
      restore_registers_you_care_about();
      disable_interrupts();
   }
*/
*/

#ifdef __MONO__
#define EE_std_get_tos_from_index(ind) (0)
#define EE_std_get_next_tos() (0)
__INLINE__ void __ALWAYS_INLINE__ EE_std_change_context(EE_FADDR thread_addr, EE_UREG tos_index )
{
    EE_std_change_context_mono(thread_addr)
}
#endif
#ifdef __MULTI__
#define EE_std_get_tos_from_index(ind) (EE_std_thread_tos[ind+1])
#define EE_std_get_next_tos() EE_hal_endcycle_next_tos
__INLINE__ void __ALWAYS_INLINE__ EE_std_change_context(EE_FADDR thread_addr, EE_UREG tos_index )
{
    EE_std_change_context_multi(thread_addr, tos_index)
}
#endif


void EE_hal_ready2stacked(EE_TID thread);

#ifdef __MULTI__
__INLINE__ void __ALWAYS_INLINE__ EE_hal_stkchange(EE_TID thread)
{
    EE_std_change_context_multi(NULL, EE_std_thread_tos[thread+1]);
}
#endif



#endif /* __INCLUDE_CPU_COMMON_EE_CONTEXT__ */
