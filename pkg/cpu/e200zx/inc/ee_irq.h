/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
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
 * Derived from the mico32 code.
 * Author: 2010 Fabio Checconi
 */

#ifndef __INCLUDE_E200ZX_IRQ_H__
#define __INCLUDE_E200ZX_IRQ_H__

#include "cpu/e200zx/inc/ee_cpu.h"
#include "cpu/e200zx/inc/ee_regs.h"

/* I include context because is needed by common ee_irqstub.h and I define
   EE_hal_active_tos because is needed by common context */
#ifdef __MULTI__
#define EE_hal_active_tos	EE_e200z7_active_tos
#endif

#include "cpu/common/inc/ee_context.h"
#include "cpu/common/inc/ee_irqstub.h"

#if defined(__IRQ_STACK_NEEDED__) && (! defined(__AS_SC4__))
/* Moved declaration here from ee_irq_internal.h because it is needed eventually
   by EE_e200zx_IRQ_change_stack */
extern struct EE_TOS EE_e200z7_IRQ_tos;
#endif /* __IRQ_STACK_NEEDED__&& ! __AS_SC4__ */

#if defined(__ALLOW_NESTED_IRQ__) && (!defined(__AS_SC4__))
#define EE_std_enableIRQ_nested()   EE_e200z7_enableIRQ()
#define EE_std_disableIRQ_nested()  EE_e200z7_disableIRQ()
#endif

#ifdef __FP__
/* No ORTI support for the FP kernel */
__INLINE__ EE_ORTI_runningisr2_type EE_ORTI_get_runningisr2(void)
{
	return (EE_ORTI_runningisr2_type)NULL;
}
#define EE_ORTI_set_runningisr2(isr2)   ((void)0)
#endif /* __FP__ */


#if (!defined(__OO_BCC1__)) && (!defined(__OO_BCC2__)) && \
		(!defined(__OO_ECC1__)) && (!defined(__OO_ECC2__))
/* no OO no IRQ clean-up */
#define EE_std_end_IRQ_post_stub()  ((void)0)
#endif /* !__OO_BCC1__ && !__OO_BCC2__ && !__OO_ECC1__ !__OO_ECC2__*/

/* Software Interrupt Vector */
extern EE_e200z7_ISR_handler EE_e200z7_ISR_table[];

/*                      Static ISR table implementation.
                               !!! WARNING !!!
    only external interrupt MAY be ISR hanlders, because the code that pop
    interrupt cotroller priority queue embedded in ISR macros.
    Dynamic ISR table handling make the check (level >= EE_E200ZX_MAX_CPU_EXC)
    to execute the code or not. That check is impossible in Static ISR table
    implementation.
*/

#ifndef __AS_SC4__

/*
 * Call an ISR. If the ISR is to be called on a new stack we need to
 * resort to the black magic of assembly programming, and here we're
 * left with just a declaration.  If the ISR doesn't need a new stack
 * we only need to enable the external interrupts and call it.
 *
 * The pseudocode for the full-fledged ISR call is the following:
 *
 * void EE_e200z7_call_ISR_new_stack(EE_e200z7_ISR_handler fun)
 * {
 *    if (EE_IRQ_nesting_level == 1) {
 *      change_to_IRQ_stacks();
 *      EE_std_enableIRQ_nested();    // Enable IRQs if nesting is allowed.
 *      fun();
 *      EE_std_disableIRQ_nested();   // Disable IRQs if nesting is allowed.
 *      change_back_from_IRQ_stacks();
 *    } else {
 *      EE_std_enableIRQ_nested();    // Enable IRQs if nesting is allowed.
 *      fun();
 *      EE_std_disableIRQ_nested();   // Disable IRQs if nesting is allowed.
 *    }
 * }
 */
#ifdef __IRQ_STACK_NEEDED__
extern struct EE_TOS EE_e200z7_IRQ_tos;

/* For SC4 the stack is changed within the prestub and the postub */
void EE_e200zx_call_ISR(EE_e200z7_ISR_handler fun, EE_UREG nesting);

#else /* if __IRQ_STACK_NEEDED__ */

/* Implemented as macro to remove the need of pointer null check for MISRA
   compliance. Fake do while construct to enforce ending semicolon */
#define EE_e200zx_call_ISR(fun, nesting)  \
  do {                                    \
    EE_std_enableIRQ_nested();            \
    fun();                                \
    EE_std_disableIRQ_nested();           \
  } while (0)
#endif /* else if __IRQ_STACK_NEEDED__ */


#ifdef __STATIC_ISR_TABLE__

#define ISR1(f)                                                       \
void EE_PREPROC_JOIN(ISR1_,f)(void);                                  \
void f(void)                                                          \
{                                                                     \
  EE_increment_IRQ_nesting_level();                                   \
  /* This handle stack change and nesting */                          \
  EE_e200zx_call_ISR(EE_PREPROC_JOIN(ISR1_,f), EE_IRQ_nesting_level); \
  /* Pop priority for external interrupts */                          \
  /* 9.4.3.1.2 EOIE Handler NOTE */                                   \
  EE_e200zx_mbar();                                                   \
  INTC_EOIR.R = 0U;                                                   \
  /* decrement nesting level */                                       \
  EE_decrement_IRQ_nesting_level();                                   \
}                                                                     \
void EE_PREPROC_JOIN(ISR1_,f)(void)

#define ISR2(f)                                                       \
void EE_PREPROC_JOIN(ISR2_,f)(void);                                  \
void f(void)                                                          \
{                                                                     \
  /* prestub */                                                       \
  /* keep the old ORTI */                                             \
  EE_ORTI_runningisr2_type ortiold;                                   \
  /* increment nesting level here, with isr disabled */               \
  EE_increment_IRQ_nesting_level();                                   \
  /* Save the old ORTI ID */                                          \
  ortiold = EE_ORTI_get_runningisr2();                                \
  /* Set the new ID as an ISR2 ID
     (level is not really used to build isr2id) */                    \
  EE_ORTI_set_runningisr2(EE_ORTI_build_isr2id(f));                   \
  /* prestub */                                                       \
  /* This handle stack change and nesting */                          \
  EE_e200zx_call_ISR(EE_PREPROC_JOIN(ISR2_,f), EE_IRQ_nesting_level); \
  /* poststub */                                                      \
  /* Set old ORTI ID back*/                                           \
  EE_ORTI_set_runningisr2(ortiold);                                   \
  /* ISR2 instance clean-up as requested by AR */                     \
  EE_std_end_IRQ_post_stub();                                         \
  /*  Pop priority for external interrupts
      (the only that can be ISR2) Look at reference manual:
      9.4.3.1.2 End-of-Interrupt Exception Handler NOTE
  */                                                                  \
  EE_e200zx_mbar();                                                   \
  INTC_EOIR.R = 0U;                                                   \
  /* decrement nesting level only from hereunder */                   \
  EE_decrement_IRQ_nesting_level();                                   \
  /* check for scheduling point */                                    \
  if (!EE_is_inside_ISR_call()) {                                     \
    EE_std_after_IRQ_schedule();                                      \
  }                                                                   \
  /* poststub */                                                      \
}                                                                     \
void EE_PREPROC_JOIN(ISR2_,f)(void)

#else  /* __STATIC_ISR_TABLE__ */
/*
 * Register the handler `fun' for the IRQ `level', using priority `pri'.  If
 * `fun' is 0, disable the given interrupt.  Levels 0-15 are used for the
 * primary interrupt sources for the e200 core, while levels greater than 15 are
 * used for external interrupt sources connected to the interrupt controller.
 * This function is available only if the system is configured to use a dynamic
 * interrupt table (i.e., the EEOPT __STATIC_ISR_TABLE__ is not defined).
 */
void EE_e200z7_register_ISR(int level, EE_e200z7_ISR_handler fun, EE_UINT8 pri);
#endif /* #else __STATIC_ISR_TABLE__ */

#else /* __AS_SC4__ */
/*
 * In SC4 ISR2 are somehow tricky: we need to execute them in trusted/
 * untrusted mode according to the OS application they belong to, and we
 * must be able to terminate them if necessary.  We use one ISR2 stack
 * per application and we maintain a stack of ISR2 descriptors to track
 * the active ISR2s.  A complete implementation would use two stacks per
 * application: one for trusted and one for untrusted mode.
 */
/*
 * Pseudocode:
 * void ISR2_N_handler(void)
 * {
 *	EE_as_Application_RAM_type *from, *to;
 *	EE_as_ISR_RAM_type *tos;
 *	ApplicationType toid = N, fromid;
 *	EE_ADDR sp = get_sp();
 *
 *	fromid = EE_e200zx_get_application();
 *	to = &EE_as_Application_RAM[ISR_N_appid];
 *
 *	tos = &EE_as_ISR_stack[EE_IRQ_nesting_level++];
 *	tos->ISR = N;
 *
 *	if (EE_IRQ_nesting_level == 1) {
 *		EE_e200zx_ISR_stksave.sp = sp;
 *		EE_e200zx_ISR_stksave.appl = fromid;
 *		load_sp(to->ISRTOS);
 *	} else if (fromid != ISR2_N_appid) {
 *		from = &EE_as_Application_RAM[fromid];
 *		from->ISRTOS = sp;
 *		load_sp(to->ISRTOS);
 *	}
 *
 *	tos->TerminationTOS = sp;
 *
 *	EE_std_enableIRQ_nested();
 *	load_appid(ISR2_N_appid);
 *	load_mode(ISR2_N_appmode);
 *	call_handler();
 *	TerminateISR2();
 * }
 */

#define DeclareIsr(f) void f(void)


__asm void EE_ISR2_prestub(int toid, int isrid)
{

% reg toid, isrid; lab l1, l2
! "r6", "r7", "r8", "r9", "r10", "r11"

	.set noreorder
	addis	r6, 0, EE_as_Application_RAM@ha
	ori	r6, r6, EE_as_Application_RAM@l	# r6 <= EE_as_Application_RAM
	mr	r7, toid
	slwi	r7, r7, 4
	add	r8, r6, r7			# r8 <= to

	addis	r9, 0, EE_IRQ_nesting_level@ha
	ori	r9, r9, EE_IRQ_nesting_level@l
	lwz	r7, 0(r9)
	mr	r10, r7				# r10 <= EE_IRQ_nesting_level
	addi	r7, r7, 1
	stw	r7, 0(r9)

	addis	r11, 0, EE_as_ISR_stack@ha
	ori	r11, r11, EE_as_ISR_stack@l
	slwi	r7, r10, 3			# r7 <= r10 << 3
	add	r9, r11, r7			# r9 <= tos

	stw	isrid, 4(r9)			# tos->ISR_Terminated = 0 | ID

	mfpid0	r7				# r7 <= fromid

	cmpli	cr0, 0, r10, 0
	bne	l1

	addis	r11, 0, EE_e200zx_ISR_stksave@ha
	ori	r11, r11, EE_e200zx_ISR_stksave@l
	stw	sp, 0(r11)
	stw	r7, 4(r11)

	lwz	sp, 0(r8)			# sp <= to->ISRTOS
	b	l2
l1:
	cmpl	cr0, r7, toid
	beq	l2

	slwi	r7, r7, 4
	stwx	sp, r6, r7			# from->ISRTOS <= sp

	lwz	sp, 0(r8)			# sp <= to->ISRTOS
l2:
#if 0 /* Arbitrary TerminateIsr() not supported */
	stw	sp, (r9)			# tos->TerminationTOS <= sp
#endif
	/* `isync' is needed for pid0 update */
	isync
	mtpid0	toid				# switch app

	lwz	r0, 4(r8)			# r0 <= to->Mode
	mtmsr	r0				# switch appmode
	/* `isync' is needed for both pid0 and msr updates */
	isync
	.set reorder
}

__asm void EE_ISR2_poststub(void)
{
! "r0"
	li	r0, EE_ID_TerminateISR2
	sc
}

#define ISR2(f)								\
static void EE_PREPROC_JOIN(ISR2_,f)(void);				\
void f(void)								\
{									\
	EE_ISR2_prestub(EE_PREPROC_JOIN(ISR2_APP_,f),			\
	EE_PREPROC_JOIN(ISR2_ID_,f));				\
	EE_PREPROC_JOIN(ISR2_,f)();					\
	EE_ISR2_poststub();						\
}									\
static void EE_PREPROC_JOIN(ISR2_,f)(void)
#endif /* __AS_SC4__ */


#endif /*  __INCLUDE_E200ZX_IRQ_H__ */
