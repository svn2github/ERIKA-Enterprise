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
#include "cpu/hs12xs/inc/ee_compiler.h"

#ifndef __INCLUDE_S12XS_EE_IRQSTUB_H__
#define __INCLUDE_S12XS_EE_IRQSTUB_H__


/* from ee_internal.h */
extern EE_ADDR EE_hal_endcycle_next_thread;
extern EE_UREG EE_hal_endcycle_next_tos;
extern EE_DADD EE_s12xs_temp_tos;
extern EE_UREG EE_IRQ_nesting_level;

void EE_IRQ_end_instance(void);
#ifdef __MONO__
void EE_s12xs_hal_ready2stacked(EE_ADDR thread_addr);
#endif
#ifdef __MULTI__
 #ifdef __CODEWARRIOR__
  void EE_s12xs_hal_ready2stacked(EE_UREG tos_index, EE_ADDR thread_addr);
 #else
  void EE_s12xs_hal_ready2stacked(EE_ADDR thread_addr, EE_UREG tos_index);
 #endif
void EE_s12xs_hal_stkchange(EE_UREG tos_index);
//void EE_s12xs_hal_stkchange(EE_ADDR thread_addr, EE_UREG tos_index); /* in ASM */
#endif


#ifdef __MULTI__
#ifdef __S12XS_SPLIM__
extern const struct EE_TOS EE_s12xs_system_splim[];
#endif
#endif

#ifdef __ALLOW_NESTED_IRQ__
 #define EE_INC_NESTING_LEVEL() EE_IRQ_nesting_level++
 #define EE_DEC_NESTING_LEVEL()\
                        EE_IRQ_nesting_level--;\
                        if (EE_IRQ_nesting_level!=0)\
                                    return
#else
 #define EE_INC_NESTING_LEVEL() EE_IRQ_nesting_level=1
 #define EE_DEC_NESTING_LEVEL() EE_IRQ_nesting_level=0
#endif

#ifdef __MULTI__
 #ifdef __IRQ_STACK_NEEDED__
  #define EE_PRESTUB_CHANGE_STACK_POINTER() \
                     if (EE_IRQ_nesting_level==1) {\
                         EE_s12xs_temp_tos =  EE_READ_SP();\
                         EE_WRITE_SP( EE_s12xs_IRQ_tos.SYS_tos ); }
						 
						 
  #define EE_POSTSTUB_CHANGE_STACK_POINTER() EE_WRITE_SP( EE_s12xs_temp_tos )
 #else
  #define EE_PRESTUB_CHANGE_STACK_POINTER() 
  #define EE_POSTSTUB_CHANGE_STACK_POINTER()
 #endif
 #define EE_S12XS_HAL_READY2STACKED() EE_s12xs_hal_ready2stacked(EE_hal_endcycle_next_tos, EE_hal_endcycle_next_thread)
 #define EE_S12XS_HAL_STKCHANGE_CHECK()\
                         else {\
                            if (EE_hal_endcycle_next_tos != EE_s12xs_active_tos) {\
                                 EE_WRITE_CCRH(0x0000);\
                                 EE_s12xs_hal_stkchange(EE_hal_endcycle_next_tos); } }

#else
  #define EE_PRESTUB_CHANGE_STACK_POINTER()
  #define EE_POSTSTUB_CHANGE_STACK_POINTER()
  #define EE_S12XS_HAL_READY2STACKED() EE_s12xs_hal_ready2stacked(EE_hal_endcycle_next_thread)
  #define EE_S12XS_HAL_STKCHANGE_CHECK()
#endif

#ifdef __CODEWARRIOR__
    #define EE_ISR2_prestub()\
                   EE_INC_NESTING_LEVEL();\
                   EE_PRESTUB_CHANGE_STACK_POINTER();\
                   EE_s12xs_enableIRQ()
#else
	__INLINE__ void __ALWAYS_INLINE__ EE_ISR2_prestub(void)
	{
	#ifdef __ALLOW_NESTED_IRQ__
	  EE_IRQ_nesting_level++;

	#ifdef __MULTI__
	#ifdef __IRQ_STACK_NEEDED__
	  if (EE_IRQ_nesting_level==1) {
		EE_s12xs_temp_tos =  EE_READ_SP();         /* save the stack pointer */
		EE_WRITE_SP( EE_s12xs_IRQ_tos.SYS_tos );   /* change the stack pointer */  
	  }
	#endif
	#endif
	  EE_s12xs_enableIRQ();
	#else
	  EE_IRQ_nesting_level=1;
	#endif
	}
#endif

#ifdef __CODEWARRIOR__
    #define EE_ISR2_poststub()\
                    EE_s12xs_disableIRQ();\
                    EE_DEC_NESTING_LEVEL();\
                    EE_POSTSTUB_CHANGE_STACK_POINTER();\
                    EE_IRQ_end_instance();\
                    if (EE_hal_endcycle_next_thread) {\
                                        EE_WRITE_CCRH(0x0000); \
                                        EE_S12XS_HAL_READY2STACKED(); }\
                    EE_S12XS_HAL_STKCHANGE_CHECK()\
                    EE_WRITE_CCRH(0x0600);\
                    EE_s12xs_enableIRQ()

#else

__INLINE__ void __ALWAYS_INLINE__ EE_ISR2_poststub(void) 
{
#ifdef __ALLOW_NESTED_IRQ__
  EE_s12xs_disableIRQ();
  EE_IRQ_nesting_level--;

  if (EE_IRQ_nesting_level!=0) 
  {
  	//EE_s12xs_enableIRQ();	
	return;
  }

#ifdef __MULTI__
#ifdef __IRQ_STACK_NEEDED__
  EE_WRITE_SP( EE_s12xs_temp_tos );        /* change the stack pointer */  
#endif
#endif

#else // not __ALLOW_NESTED_IRQ__
  EE_IRQ_nesting_level=0;
#endif // __ALLOW_NESTED_IRQ__

  EE_IRQ_end_instance();
  
  if (EE_hal_endcycle_next_thread) {
    // enable interrupt and CPU priority to 0
    EE_WRITE_CCRH(0x0000);
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
        EE_WRITE_CCRH(0x0000);
        EE_s12xs_hal_stkchange(EE_hal_endcycle_next_tos);
        //EE_s12xs_hal_stkchange(EE_hal_endcycle_next_thread, EE_hal_endcycle_next_tos);
    }
#endif
  }

  //  Set CPU priority to 6 and enable interrupt with disi
  //  retfie will restore the right priority level
  EE_WRITE_CCRH(0x0600);
  EE_s12xs_enableIRQ();
}

#endif

//#define ISR2(f) void f(void)

#ifdef __CODEWARRIOR__
 #define EE_S12_ISR @interrupt
#else
 #define EE_S12_ISR @interrupt @near
#endif

#define ISR2(f)\
static void ISR2_##f(void);\
EE_S12_ISR void f(void)\
{\
  EE_ISR2_prestub();\
  ISR2_##f();\
  EE_ISR2_poststub();\
}\
static void ISR2_##f(void)

#endif
