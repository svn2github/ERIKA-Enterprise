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
 * Author: 2001-2002 Marko bertogna
 * CVS: $Id: ee_internal.h,v 1.3 2006/05/14 17:50:30 pj Exp $
 */

#include "arm7gnu/triscend_a7s/drivers.h"

#ifndef __INCLUDE_TRISCEND_INTERNAL_H__
#define __INCLUDE_TRISCEND_INTERNAL_H__


/*************************************************************************
 Timers
 *************************************************************************/

/*
 * CBS
 */

#ifdef __CBS__

/* This function set the capacity timer to raise in t ticks.
   In this implementation, timer1 is used to raise a capacity
   interrupt. The capacity interrupt is then programmed simply setting
   the delay into the timer1 counter. That is, whenever the timer
   fires, it restart counting down from 0xffffffff, and it will take a
   few seconds to do that. */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_capacityIRQ(EE_TIME t)
{
  *TCNT1 = t;
}

#endif


#endif /* __INCLUDE_TRISCEND_INTERNAL_H__ */
