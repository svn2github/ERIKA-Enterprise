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
 * Context switch functions used in HAL implementations
 * Author: 2009 Bernardo Dal Seno
 */


#include "ee_internal.h"

/* This version should work for both the monostack and multistack versions of
 * the kernel, thanks to the macros defined in cpu/commmon/inc/ee_context.h.
 * In the mono version, all the stack-related stuff is ignored. */
void EE_std_run_task_code(EE_FADDR thread_addr)
{
    EE_hal_enableIRQ();
    ((void (*)())thread_addr)(); /* Call thread_addr */
    EE_hal_disableIRQ();
    EE_UREG tos_index;
    do {
        EE_thread_end_instance();
        thread_addr = EE_hal_endcycle_next_thread;
        tos_index = EE_std_get_next_tos();
    } while (thread_addr != NULL);
}
