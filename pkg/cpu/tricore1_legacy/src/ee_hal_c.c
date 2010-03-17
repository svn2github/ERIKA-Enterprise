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
 * Author: 2005 Paolo Gai
 * CVS: $Id: ee_hal_c.c,v 1.3 2006/01/24 10:23:01 pj Exp $
 */

#include "ee_internal.h"

/*
 * Endcycle Next thread, Endcycle Next tos, nesting level
 */
EE_ADDR EE_hal_endcycle_next_thread;
#ifdef ___MULTI__
EE_UREG EE_hal_endcycle_next_tos;
#endif
EE_UREG EE_IRQ_nesting_level;


void EE_thread_end_instance(void);

/*
 * change_tos
 */

#ifdef __MULTI__
void EE_tc1_change_tos(EE_ADDR thread_addr, EE_UREG tos_index);
#endif


#ifdef __MONO__
void EE_tc1_hal_ready2stacked(EE_ADDR thread_addr)
#endif
#ifdef __MULTI__
void EE_tc1_ready2stacked(EE_ADDR thread_addr, EE_UREG tos_index)
#endif
{
EE_tc1_ready2stacked_start:
#ifdef __MULTI__
	EE_tc1_change_tos(thread_addr, tos_index);
#endif

    EE_tc1_enableIRQ();
    (*((void (*)(void))thread_addr))();
	EE_tc1_disableIRQ();

	EE_thread_end_instance();

#ifdef __MULTI__
	tos_index = EE_hal_endcycle_next_tos;
#endif
	thread_addr = (EE_ADDR)EE_hal_endcycle_next_thread;
	if (thread_addr != 0)
	  goto EE_tc1_ready2stacked_start;

#ifdef __MULTI__
	EE_tc1_change_tos(thread_addr, tos_index);
#endif
}
