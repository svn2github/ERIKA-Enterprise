/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2012  Evidence Srl
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

 /** @file  ee_tc_irq_internal.h
  *  @brief Header with definition for ISR2 Wrappers generation
  *  @author Errico Guidieri
  *  @date 2012
  */
#ifndef INCLUDE_EE_TC_IRQ_INTERNAL_H__
#define INCLUDE_EE_TC_IRQ_INTERNAL_H__

/* I need cpu internals for multistack global structures */
#include "cpu/tricore/inc/ee_tc_internal.h"
/* I need Kernel inclusion for Common Context and Service Protection */
#include "ee.h"
/* I need Kernel inclusion for IRQ callbacks */
#include "ee_irq.h"
/* Plus I need Common End-ISR Scheduler Implementation */
#include "cpu/common/inc/ee_irqstub.h"
/* Plus I need TriCore IRQ handling defines */
#include "cpu/tricore/inc/ee_tc_irq.h"

/* Labels for Kernel Tracing. It has been used an utility function to generate
   only one copy of Tracing Labels.
   Enabled when ORTI is enabled and ISR are handled by ERIKA's intvec */
#if defined(__OO_ORTI_SERVICETRACE__) && ((!defined(EE_ERIKA_ISR_HANDLING_OFF))\
  || defined(EE_MM_OPT))

void __NEVER_INLINE__ EE_tc_isr2_call_handler( EE_tc_ISR_handler f )
{
  /* Call The ISR User Handler */
  if ( f != NULL ) {
    f();
  }
}

#else /* __OO_ORTI_SERVICETRACE__ &&
  (!EE_ERIKA_ISR_HANDLING_OFF || EE_MM_OPT) */
__INLINE__ void __ALWAYS_INLINE__ EE_tc_isr2_call_handler( EE_tc_ISR_handler f )
{
  /* Call The ISR User Handler */
  if ( f != NULL ) {
    f();
  }
}
#endif /* __OO_ORTI_SERVICETRACE__ &&
    (!EE_ERIKA_ISR_HANDLING_OFF || EE_MM_OPT) */


#if defined(__OO_ORTI_RUNNINGISR2__)
/* Only ORTI local */
#define EE_generate_locals()  \
  register EE_ORTI_runningisr2_type orti_old
#else /* __OO_ORTI_RUNNINGISR2__ */
/* No locals */
#define EE_generate_locals()  ((void)0)
#endif /*__OO_ORTI_RUNNINGISR2__ || EE_TIMING_PROTECTION__ */

#ifdef __OO_ORTI_RUNNINGISR2__
/* Keep the old ORTI and switch to new one */
#define EE_ORTI_running_isr2_begin(f)         \
  do {                                        \
    orti_old = EE_ORTI_get_runningisr2();     \
    EE_ORTI_set_runningisr2(f);               \
  } while ( 0 )
/* Restore old ORTI */
#define EE_ORTI_running_isr2_end()  EE_ORTI_set_runningisr2(orti_old)
#else /* __OO_ORTI_RUNNINGISR2__ */
#define EE_ORTI_running_isr2_begin(f) ((void)0)
#define EE_ORTI_running_isr2_end()    ((void)0)
#endif /* __OO_ORTI_RUNNINGISR2__ */

#if (!defined(__OO_BCC1__)) && (!defined(__OO_BCC2__)) && \
    (!defined(__OO_ECC1__)) && (!defined(__OO_ECC2__))
#define EE_as_set_execution_context(ctx)  ((void)0)
#endif /* !__OO_BCC1__ && !__OO_BCC2__ && !__OO_ECC1__ && !__OO_ECC2__ */

__INLINE__ void __ALWAYS_INLINE__ EE_tc_isr2_wrapper_body( EE_tc_ISR_handler f )
{
  /* This macro generate the local variables eventually needed */
  EE_generate_locals();
  /* Keep the old ORTI ISR2 and switch to new one */
  EE_ORTI_running_isr2_begin(f);
  /* Increment nesting level here, with IRQ disabled */
  EE_increment_IRQ_nesting_level();
  /* Set the context execution at ISR2 */
  EE_as_set_execution_context( ISR2_Context );
  /* Enable IRQ if nesting  is allowed */
  EE_std_enableIRQ_nested();

  /* Call The ISR User Handler */
  EE_tc_isr2_call_handler(f);

  /* Disable IRQ if nesting is allowed.
     Note: if nesting is not allowed, the IRQs are
     already disabled */
  EE_std_disableIRQ_nested();
  /* ISR2 instance clean-up as requested by AR, must be
     called  before EE_decrement_IRQ_nesting_level */
  EE_std_end_IRQ_post_stub();
  /* Decrement nesting level here, with IRQ disabled */
  EE_decrement_IRQ_nesting_level();
  /* Restore the old ORTI ISR2 value */
  EE_ORTI_running_isr2_end();
  /* If the ISR at the lowest level is ended, restore old
     SP, reset CCPN and call the scheduler. */
  /* Check for scheduling point */
  if ( EE_is_inside_ISR_call() == 0 ) {
    /* Set CCPN to unmask next IRQ, it would have been
       done by RFE but we are not returning yet */
    EE_tc_set_int_prio( (EE_TYPEISR2PRIO)EE_ISR_UNMASKED );
    /* Restore task stack pointer if needed */
    EE_tc_set_prev_stack_back();
    /* Call the scheduler */
    EE_std_after_IRQ_schedule();
  }
}

/* ISR2 Wrapper Function Body */
#define EE_ISR2_WRAPPER_BODY(f)  EE_tc_isr2_wrapper_body(f)

#endif /* INCLUDE_EE_TC_IRQ_INTERNAL_H__ */

