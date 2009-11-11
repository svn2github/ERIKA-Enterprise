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
 * Author: 2005 Michele Cirinei
 *         2006- Paolo Gai
 *         2008- Paolo & Francesco: change interrupt disabling/enabling
 *         procedure, now with DISI instruction  
 * CVS: $Id: ee_irqstub.h,v 1.8 2008/07/16 15:01:38 francesco Exp $
 */


#include "eecfg.h"
#include "cpu/cosmic_hs12xs/inc/ee_compiler.h"

#ifndef __INCLUDE_S12XS_EE_IRQSTUB_H__
#define __INCLUDE_S12XS_EE_IRQSTUB_H__


/* from ee_internal.h */
extern EE_ADDR EE_hal_endcycle_next_thread;
extern EE_UREG EE_hal_endcycle_next_tos;
extern EE_ADDR EE_s12xs_temp_tos;
extern EE_UREG EE_IRQ_nesting_level;

void EE_IRQ_end_instance(void);
#ifdef __MONO__
void EE_s12xs_hal_ready2stacked(EE_ADDR thread_addr);
#endif
#ifdef __MULTI__
void EE_s12xs_hal_ready2stacked(EE_ADDR thread_addr, EE_UREG tos_index);
void EE_s12xs_hal_stkchange(EE_UREG tos_index);
#endif


#ifdef __MULTI__
#ifdef __S12XS_SPLIM__
extern const struct EE_TOS EE_s12xs_system_splim[];
#endif
#endif

__INLINE__ void __ALWAYS_INLINE__ EE_ISR2_prestub(void)
{
  EE_s12xs_disableIRQ();
#ifdef __ALLOW_NESTED_IRQ__
  EE_IRQ_nesting_level++;

#ifdef __MULTI__
#ifdef __IRQ_STACK_NEEDED__
  if (EE_IRQ_nesting_level==1) {
    _asm("mov.w  sp, _EE_s12xs_temp_tos");                              //_asm("movw  w15, _EE_s12xs_temp_tos");
#ifdef __S12XS_SPLIM__
    _asm("mov    _SPLIM, sp");
    _asm("mov.w  sp, _EE_s12xs_temp_splim");
    _asm("mov	_EE_s12xs_IRQ_splim, sp");
    _asm("mov	sp, _SPLIM");
    // the next operation cannot do an access based on w15
#endif
    _asm("mov.w _EE_s12xs_IRQ_tos, sp");                               //_asm("mov.w _EE_s12xs_IRQ_tos, w15");
  }
#endif
#endif
  EE_s12xs_enableIRQ();
#else
  EE_IRQ_nesting_level=1;
#endif
}

__INLINE__ void __ALWAYS_INLINE__ EE_ISR2_poststub(void)
{
#ifdef __ALLOW_NESTED_IRQ__
  EE_s12xs_disableIRQ();
  EE_IRQ_nesting_level--;

  if (EE_IRQ_nesting_level!=0) return;

#ifdef __MULTI__
#ifdef __IRQ_STACK_NEEDED__
#ifdef __S12XS_SPLIM__
  _asm("mov.w _EE_s12xs_temp_splim, sp");
  _asm("mov	sp, _SPLIM");
  // the next operation cannot do an access based on w15
#endif
  _asm("mov.w _EE_s12xs_temp_tos, sp");
#endif
#endif

#else // not __ALLOW_NESTED_IRQ__
  EE_IRQ_nesting_level=0;
#endif // __ALLOW_NESTED_IRQ__

  EE_IRQ_end_instance();
  
  if (EE_hal_endcycle_next_thread) {
    // enable interrupt and CPU priority to 0
    _asm("BCLR.B 0x0042, #0x7");
    _asm("BCLR.B 0x0042, #0x6");
    _asm("BCLR.B 0x0042, #0x5");
#ifdef __MONO__
    EE_s12xs_hal_ready2stacked(EE_hal_endcycle_next_thread);
#endif
#ifdef __MULTI__
    EE_s12xs_hal_ready2stacked(EE_hal_endcycle_next_thread, EE_hal_endcycle_next_tos);
#endif
  }
  else {
#ifdef __MULTI__
    if (EE_hal_endcycle_next_tos != EE_s12xs_active_tos) {
      // enable interrupt and CPU priority to 0
      _asm("BCLR.B 0x0042, #0x7");
      _asm("BCLR.B 0x0042, #0x6");
      _asm("BCLR.B 0x0042, #0x5");

      EE_s12xs_hal_stkchange(EE_hal_endcycle_next_tos);
    }
#endif
  }

  //  Set CPU priority to 6 and enable interrupt with disi
  //  retfie will restore the right priority level
  _asm("BSET.B 0x0042, #0x7");
  _asm("BSET.B 0x0042, #0x6");
  _asm("BCLR.B 0x0042, #0x5");
  EE_s12xs_enableIRQ();
}


//void __attribute__((__interrupt__,__auto_psv__)) f(void) \




//#define ISR2(f) void f(void)
#define ISR2(f)\
void ISR2_##f(void);\
@interrupt @near void f(void)\
{\
  EE_ISR2_prestub();\
  ISR2_##f();\
  EE_ISR2_poststub();\
}\
void ISR2_##f(void)

#endif
