/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
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
 * MPC5668 register map
 * Author: 2011 Bernardo  Dal Seno
 */

#ifndef EE_MCU_MPC5668_H
#define EE_MCU_MPC5668_H

/* ISO int types used by mpc5668.h */
#define __EE_STDINT_SKIP_64BIT__
#include <cpu/common/inc/ee_stdint.h>

#include "mpc5668.h"

#define EE_E200ZX_MAX_EXT_IRQ 316

#if ! defined EE_CURRENTCPU || EE_CURRENTCPU == 0
/* For duplicated registers, pick the Z6 instance */
#define INTC_CPR (INTC.CPR_PRC0)
#define INTC_IACKR (INTC.IACKR_PRC0)
#define INTC_EOIR (INTC.EOIR_PRC0)
/* Target CPU for external interrupts: Z6 */
#define EE_E200ZX_INTC_CURRPROC 0U

#else /* if EE_CURRENTCPU != 0 */
/* For duplicated registers, pick the Z0 instance */
#define INTC_CPR (INTC.CPR_PRC1)
#define INTC_IACKR (INTC.IACKR_PRC1)
#define INTC_EOIR (INTC.EOIR_PRC1)
/* Target CPU for external interrupts: Z0 */
#define EE_E200ZX_INTC_CURRPROC 0xc0U

#endif /* EE_CURRENTCPU */

#endif /* EE_MCU_MPC5668_H */
