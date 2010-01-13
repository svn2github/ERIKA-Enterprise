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
 * Some debugging facilities
 * Author: 2010,  Bernardo  Dal Seno
 */

#ifndef __INCLUDE_MICO32_DEBUG_H__
#define __INCLUDE_MICO32_DEBUG_H__


/*
 * Stack debugging
 */
#ifdef DEBUG_STACK

/*
 * This value is used as a canary (guard memory location) for stack overflow
 * detection.  This value has three interesting properties, which tend to cause
 * an exception if it's read and used by the processor:
 * 1. It's an invalid instruction
 * 2. It's a misaligned address
 * 3. It's an address in the I/O region, not suitable for code, and likely
 * invalid anyway
 * The canary is written before and after the actual stack space.  If it is
 * overwritten, you know that that the stack has been exceeded.
 */
#define MICO32_STACK_CANARY     0xabadbeef
/*
 * Value to fill uninitialized memory.  It has the same properties of the
 * canary.
 */
#define MICO32_FILL_MEMORY      0xce11f00d

#define PRE_STACK_CANARY_LEN    22  /* Enough to invalidate all caller-saved
                                     * registers */
#define POST_STACK_CANARY_LEN    4

/* Write the canary before and after the actual stack, and fill it with
 * garbage. */
#define MICO32_STACK_INIT(stack_len) {                                  \
    [0 ... POST_STACK_CANARY_LEN - 1] = MICO32_STACK_CANARY,            \
        [POST_STACK_CANARY_LEN ... stack_len + POST_STACK_CANARY_LEN - 1] \
        = MICO32_FILL_MEMORY,                                           \
        [stack_len + POST_STACK_CANARY_LEN ...                          \
            stack_len + PRE_STACK_CANARY_LEN + POST_STACK_CANARY_LEN - 1] \
        = MICO32_STACK_CANARY                                           \
        }
#define MICO32_INIT_TOS_OFFSET (PRE_STACK_CANARY_LEN+1)
#define MICO32_STACK_DEBUG_LEN (PRE_STACK_CANARY_LEN+POST_STACK_CANARY_LEN)

#endif /* DEBUG_STACK */


#endif /* __INCLUDE_MICO32_DEBUG_H__ */
