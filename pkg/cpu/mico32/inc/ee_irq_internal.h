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
 * IRQ-related stuff for Lattice Mico32; internals
 * Author: 2009 Bernardo Dal Seno
 */

#ifndef __INCLUDE_MICO32_IRQ_INTERNAL_H__
#define __INCLUDE_MICO32_IRQ_INTERNAL_H__

#include "cpu/mico32/inc/ee_irq.h"
#include "MicoInterrupts.h"
#include "cpu/mico32/inc/ee_internal.h"


extern EE_mico32_ISR_handler EE_mico32_ISR_table[];


__INLINE__ int __ALWAYS_INLINE__ mico32_get_reg_ip(void)
{
    int ip;
    asm volatile ( "rcsr %0,ip":"=r"(ip) );
    return ip;
}


__INLINE__ int __ALWAYS_INLINE__ mico32_get_reg_im(void)
{
    int im;
    asm volatile ( "rcsr %0,im":"=r"(im) );
    return im;
}


__INLINE__ void __ALWAYS_INLINE__ mico32_set_reg_im(int im)
{
    asm volatile ( "wcsr im,%0"::"r"(im) );
}


__INLINE__ void __ALWAYS_INLINE__ mico32_clear_ip_mask(int mask)
{
    asm volatile ( "wcsr ip,%0"::"r"(mask) );
}


#ifdef __IRQ_STACK_NEEDED__
void EE_mico32_call_ISR_new_stack(EE_mico32_ISR_handler fun);
/* This must be written in assembler, as it modifies the stack pointer.
   
    if (EE_IRQ_nesting_level == 1)
        change_stacks();
    EE_std_enableIRQ_nested(); // Enable IRQ if nesting is allowed
    fun();
    EE_std_disableIRQ_nested(); // Disable IRQ if nesting is allowed
    if (EE_IRQ_nesting_level == 1)
        change_stacks_back();
*/
#else /*ifndef __IRQ_STACK_NEEDED__ */
#define EE_mico32_call_ISR_new_stack(fun)                               \
 EE_std_enableIRQ_nested(); /* Enable IRQ if nesting is allowed */      \
 fun();                                                                 \
 EE_std_disableIRQ_nested() /* Disable IRQ if nesting is allowed */    
#endif

#endif /* __INCLUDE_MICO32_IRQ_INTERNAL_H__ */
