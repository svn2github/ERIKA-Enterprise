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
 * Author: 2008 Paolo Tiberi & Francesco Focacci
 * CVS: $Id: ee_frsh_init.c,v 1.4 2008/07/21 13:51:54 tiberipa Exp $
 */

#include "ee_internal.h"

/* Maybe this code should go to HAL source*/
#ifdef __PIC30__
#include "mcu/microchip_dspic/inc/ee_internal.h"
#include "cpu/pic30/inc/ee_irqstub.h"

extern void EE_IRQ_end_budget(void);
extern void EE_IRQ_end_recharging(void);

ISR2(_T5Interrupt)
{
	/* clear the interrupt source */
	IFS1bits.T5IF = 0;
	T4CONbits.TON = 0;
	EE_IRQ_end_budget();
}

ISR2(_T7Interrupt)
{
	/* clear the interrupt source */
	IFS3bits.T7IF = 0;
	T6CONbits.TON = 0;
	EE_IRQ_end_recharging();
}
#endif

#ifndef __PRIVATE_FRSH_INIT__
int frsh_init(void)
{
  EE_time_init();
  EE_iris_time_init();
  return 0;
}
#endif
