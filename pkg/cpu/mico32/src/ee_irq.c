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
 * IRQ-related stuff for Lattice Mico32
 * Author: 2009 Bernardo Dal Seno
 */

#include "cpu/mico32/inc/ee_irq_internal.h"
#include "ee_internal.h"
#include "cpu/common/inc/ee_irqstub.h"

EE_mico32_ISR_handler EE_mico32_ISR_table[MAX_MICO32_ISR_LEVEL+1];


/* Possible improvement: Enable higher-level interrupts while processing lower
 * level interrupts, even in this function */
void MicoISRHandler(void)
{
    EE_increment_IRQ_nesting_level();
    int mask, level;
    int im, ip;

    for (;;) {
        ip = mico32_get_reg_ip();
        im = mico32_get_reg_im();
        ip &= im;
        if (ip == 0)
            break;
        for (mask = 1, level = 0; ; ++level, mask <<= 1) {
            if (ip & mask) {
                EE_mico32_ISR_handler f = EE_mico32_ISR_table[level];
                if (f)
                    EE_mico32_call_ISR_new_stack( f );
                mico32_clear_ip_mask( mask );
                break;
            }
        }
    }
    EE_decrement_IRQ_nesting_level();
    if (! EE_is_inside_ISR_call()) {
        /* Outer nesting level: call the scheduler.  If we have also type-ISR1
         * interrupts, the scheduler should be called only for type-ISR2
         * interrupts. */
        EE_std_after_IRQ_schedule();
    }
}


void EE_mico32_register_ISR(int level, EE_mico32_ISR_handler fun)
{
    int mask;
    EE_FREG intst = EE_mico32_disableIRQ();
    EE_mico32_ISR_table[level] = fun;
    mask = mico32_get_reg_im();
    if (fun)
        mask |= 1 << level;
    else
        mask &= ~(1 << level);
    mico32_set_reg_im(mask);
    if (EE_mico32_are_IRQs_enabled(intst))
        EE_mico32_enableIRQ();
}
