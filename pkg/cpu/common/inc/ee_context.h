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


/*
 * Instructions
 *
 * The monostack part is complete (obviously, the functions to disable/enable
 *  interrupts are not included here).  For the multistack part you have to
 *  provide two additional things:
 *  1. An assembly implementation of EE_std_change_context_multi(); see below.
 *  2. A #define directive for EE_hal_active_tos, which is just an alias for the
 *  actual architecture-dependent variable.  This variable contains the index of
 *  the current stack.
 */

/* After a task terminates, the scheduler puts the new thread and the new stack
 * into these variables.  They represents the new context to switch to. */
extern EE_FADDR EE_hal_endcycle_next_thread;
extern EE_UREG EE_hal_endcycle_next_tos;


/* The _multi version must be implemented in ASM; no standard implementation,
 * sorry.  This is the only function that performs context switching.  The
 * _multi version doesn't jump to a new address if 'thread_addr' is NULL.  This
 * is used to switch to a thread that has been suspend by a previous call to
 * EE_std_change_contex_multi() */
#ifdef __MONO__
__DECLARE_INLINE__ void EE_std_change_context_mono(EE_FADDR thread_addr);
#endif
#ifdef __MULTI__
void EE_std_change_context_multi(EE_FADDR thread_addr, EE_UREG tos_index);
#endif
/* Pseudo code for EE_std_change_context_multi():
     begin:
      if is_not_the_current_stack(tos_index) {
          save_caller_saved_registers();
          switch_stacks(tos_index);
          restore_caller_saved_registers();
      }
      if (thread_addr != 0) {
          thread_addr = EE_std_run_task_code(thread_addr);
          tos_index = EE_std_get_next_tos();
          goto begin;
      }

      Please notice that the "goto begin" is actually a recursive call to
      EE_std_change_context_multi(), but in this way there is no stack growing.
      
      Please notice also that 'thread_addr' and 'tos_index' must NOT be saved
      onto the stack before switching stacks, otherwise when switching from
      another stack back to current one, you would overwrite their values.

      For processors where the return address is saved in a register, that
      register must be saved in the stack too.

      switch_stacks() should also update EE_hal_active_tos.
*/

/* True if `tos_index' is not the current stack.  Only the implementation for
 * the monostack version is provided below, as the multistack implementation
 * depends on the architecture. */
__DECLARE_INLINE__ int EE_hal_need_change_stack(EE_UREG tos_index);

#ifdef __MONO__
/* To avoid missing any side effect, the parmaters of macro are inserted in the
 * expansion even when not needed.  */
#define EE_std_get_tos_from_index(ind) ((void)(ind), 0)
#define EE_std_get_next_tos() (0)
__DECLARE_INLINE__ void EE_std_change_context(EE_FADDR thread_addr, EE_UREG tos_index );
#define EE_std_set_next_tos_from_index(ind) ((void)(ind))
#endif
#ifdef __MULTI__
#define EE_std_get_tos_from_index(ind) (EE_std_thread_tos[(ind)+1])
#define EE_std_get_next_tos() EE_hal_endcycle_next_tos
__DECLARE_INLINE__ void EE_std_change_context(EE_FADDR thread_addr, EE_UREG tos_index );
__DECLARE_INLINE__ void EE_std_set_next_tos_from_index(EE_TID ind);
#endif

/* Launch a new task, possibly switching to a different stack, clean up the task
 * after it ends, and call the scheduler (and switch to other tasks/stacks)
 * until there are no more tasks to switch to.  In the multistack version, also
 * change the current stack before returning if the scheduler asks for it. */
__DECLARE_INLINE__ void EE_hal_ready2stacked(EE_TID thread);

/* Launch a new task on the current stack, clean up the task after it ends, and
 * call the scheduler.  Return the next task to launch (or NULL if there is no
 * new task to launch).  Please notice that in the multistack version the
 * scheduler may ask to switch stacks. */
EE_FADDR EE_std_run_task_code(EE_FADDR thread_addr);



/*
 * Inline implementations
 */

#ifdef __MONO__
__INLINE__ void __ALWAYS_INLINE__ EE_std_change_context_mono(EE_FADDR thread_addr)
{
    do {
        thread_addr = EE_std_run_task_code(thread_addr);
    } while (thread_addr != NULL);
}


__INLINE__ void __ALWAYS_INLINE__ EE_std_change_context(EE_FADDR thread_addr,
    EE_UREG tos_index )
{
    EE_std_change_context_mono(thread_addr);
}

__INLINE__ int __ALWAYS_INLINE__ EE_hal_need_change_stack(EE_UREG tos_index)
{
    return 0;
}
#endif


#ifdef __MULTI__
__INLINE__ void __ALWAYS_INLINE__ EE_std_change_context(
    EE_FADDR thread_addr, EE_UREG tos_index )
{
    EE_std_change_context_multi(thread_addr, tos_index);
}


__INLINE__ void __ALWAYS_INLINE__ EE_hal_stkchange(EE_TID thread)
{
    EE_std_change_context_multi(NULL, EE_std_thread_tos[thread+1]);
}


__INLINE__ void  __ALWAYS_INLINE__ EE_std_set_next_tos_from_index(EE_TID ind)
{
    EE_hal_endcycle_next_tos = EE_std_thread_tos[ind+1];
}


__INLINE__ int __ALWAYS_INLINE__ EE_hal_need_change_stack(EE_UREG tos_index)
{
    return (EE_hal_active_tos != tos_index);
}
#endif


/* The functions below should work for both the monostack and multistack
 * versions of the kernel, thanks to the macros defined above.  In the mono
 * version, all the stack-related stuff is ignored. */


__INLINE__ void EE_hal_ready2stacked(EE_TID thread)
{
    EE_FADDR thread_addr = EE_hal_thread_body[thread];
    EE_UREG tos_index = EE_std_get_tos_from_index(thread);
    EE_std_change_context(thread_addr, tos_index);
}


__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_ready(EE_TID thread)
{
    EE_std_set_next_tos_from_index(thread);
    EE_hal_endcycle_next_thread = EE_hal_thread_body[thread];
}


__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_stacked(EE_TID thread)
{
    EE_std_set_next_tos_from_index(thread);
    EE_hal_endcycle_next_thread = 0;
}


#endif /* __INCLUDE_CPU_COMMON_EE_CONTEXT__ */
