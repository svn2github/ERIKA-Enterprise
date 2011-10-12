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
 * Derived from cpu/mico32/inc/ee_internal.h
 * Author: 2010 Fabio Checconi
 *         2011 Bernardo  Dal Seno
 */

#ifndef __INCLUDE_E200ZX_INTERNAL_H__
#define __INCLUDE_E200ZX_INTERNAL_H__

#include "cpu/e200zx/inc/ee_cpu.h"
#include "ee_e200zx_multicore.h"


/*************************************************************************
 Functions
 *************************************************************************/

/*
 * Generic Primitives
 */

#include "cpu/common/inc/ee_primitives.h"


/* called as _first_ function of a primitive that can be called in
   an IRQ and in a task */
__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_hal_begin_nested_primitive(void)
{
    return EE_e200z7_disableIRQ();
}


/* Called as _last_ function of a primitive that can be called in
   an IRQ and in a task.  Enable IRQs if they were enabled before entering. */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_end_nested_primitive(EE_FREG f)
{
	if (EE_e200z7_are_IRQs_enabled(f)) {
		EE_e200z7_enableIRQ();
	}
}



/*
 * Context Handling
 */

#ifdef __MULTI__
#define EE_hal_active_tos	EE_e200z7_active_tos
#endif

#include "cpu/common/inc/ee_context.h"

/* typically called at the end of an interrupt */
#define EE_hal_IRQ_stacked EE_hal_endcycle_stacked
#define EE_hal_IRQ_ready EE_hal_endcycle_ready

/*
 * OO TerminateTask related stuffs
 */

#if defined(__OO_BCC1__) || defined(__OO_BCC2__) || defined(__OO_ECC1__) || defined(__OO_ECC2__)

void EE_hal_terminate_savestk(EE_TID tid);
void EE_hal_terminate_task(EE_TID tid) NORETURN;

#endif /* __OO_BCCx */

/*
 * ORTI OTM support
 */

/* Probably, some parts of the OTM code below does not depend on the
 * architecture.  They should be moved into pkg/oo/inc/ee_internal.h if this
 * turns out to be the case. */

#define EE_ORTI_OTM_ID_RUNNINGISR2 1

#ifdef __OO_ORTI_USE_OTM__
void EE_e200zx_send_otm32(EE_UINT8 id, EE_UINT32 data);
#else /* if __OO_ORTI_USE_OTM__ */
__INLINE__ void EE_e200zx_send_otm32(EE_UINT8 id, EE_UINT32 data)
{
}
#endif /* else __OO_ORTI_USE_OTM__ */

#ifdef __OO_ORTI_RUNNINGISR2__
__INLINE__ void EE_ORTI_send_otm_runningisr2(EE_ORTI_runningisr2_type isr2)
{
	EE_e200zx_send_otm32(EE_ORTI_OTM_ID_RUNNINGISR2, (EE_UINT32)isr2);
}
#endif /* __OO_ORTI_RUNNINGISR2__ */


#ifdef __ASM_CONVERTED_TO_C__
/* Prototypes are included only for Erika source files, but they could be useful
 * also for user C code.  In that case, a further condition should be added. */
/* Assembly functions */
void __start(void);
void intc_setup(void);
void cpu_setup(void);
void sram_setup(void);
void save_registers(void);
void restore_all_return(void);
void ivor_setup(void);
void EE_e200zx_external_input_handler(void);
void EE_e200zx_decrementer_handler(void);
void EE_e200zx_fixed_intv_handler(void);
/* Symbols provided by the linker script */
extern int _load_ram;
extern int _sbss;
extern int _sdata;
extern int _ebss;
extern int _SDA_BASE_;
extern int _SDA2_BASE_;
extern int _sstack, _estack;
extern int isram_base;
extern int isram_len;
#endif


#endif /* __INCLUDE_E200ZX_INTERNAL_H__ */
