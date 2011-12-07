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
 * Author: Dario Di Stefano
 */

#ifdef __USE_TIMER__
 
#ifndef __INCLUDE_MC9S12_TIMER_H__
#define __INCLUDE_MC9S12_TIMER_H__

/* Include a file with the registers of the s12 micro-controller */ 
#include "mcu/hs12xs/inc/ee_mcuregs.h"

#define EE_TIMER_ISR_ON  1
#define EE_TIMER_ISR_OFF 0

#define EE_TIMER_SET_PERIOD(id, per) *(&(EE_S12_TIMER_TC0_REG) + id) = per
#define EE_TIMER_SET_PRESCALER(ps)   EE_S12_TIMER_SYSCTRL_REG2=ps

#define EE_TIMER_PRESCALE_FACTOR_128 	7
#define EE_TIMER_PRESCALE_FACTOR_64 	6
#define EE_TIMER_PRESCALE_FACTOR_32 	5
#define EE_TIMER_PRESCALE_FACTOR_16 	4
#define EE_TIMER_PRESCALE_FACTOR_8 		3
#define EE_TIMER_PRESCALE_FACTOR_4 		2
#define EE_TIMER_PRESCALE_FACTOR_2 		1
#define EE_TIMER_PRESCALE_FACTOR_1 		0

#if defined (__MC9S12G128__) || defined (__MC9S12XS128__)

#define EE_TIMER_0 0
#define EE_TIMER_1 1
#define EE_TIMER_2 2
#define EE_TIMER_3 3
#define EE_TIMER_4 4
#define EE_TIMER_5 5
#define EE_TIMER_6 6
#define EE_TIMER_7 7

#define EE_S12_TIMER_SYSCTRL_REG1 TSCR1
#define EE_S12_TIMER_SYSCTRL_REG2 TSCR2
#define EE_S12_TIMER_ISR_FLAG1    TFLG1
#define EE_S12_TIMER_ISR_FLAG2    TFLG2
#define EE_S12_TIMER_CNT_REG      TCNT
#define EE_S12_TIMER_ICOC_SEL     TIOS
#define EE_S12_TIMER_CTRL_REG1    TCTL1
#define EE_S12_TIMER_CTRL_REG2    TCTL2
#define EE_S12_TIMER_CTRL_REG3    TCTL3
#define EE_S12_TIMER_CTRL_REG4    TCTL4
#define EE_S12_TIMER_IE_REG       TIE
#define EE_S12_OUTCMP_DIS_REG     OCPD
#define EE_S12_OUTCMP_MASK_REG    OC7M
#define EE_S12_OUTCMP_DATA_REG    OC7D
#define EE_S12_TIMER_TC0_REG      TC0
#define EE_S12_TIMER_TC1_REG      TC1
#define EE_S12_TIMER_TC2_REG      TC2
#define EE_S12_TIMER_TC3_REG      TC3
#define EE_S12_TIMER_TC4_REG      TC4
#define EE_S12_TIMER_TC5_REG      TC5
#define EE_S12_TIMER_TC6_REG      TC6
#define EE_S12_TIMER_TC7_REG      TC7

#endif

#ifdef __MC9S12G128__

#define EE_TIMER_SET_PRIORITY(prio)

#endif /* __MC9S12G128__ */

#ifdef  __MC9S12XS128__

#define EE_TIMER_ISR_ON_PRIO1  1
#define EE_TIMER_ISR_ON_PRIO2  2
#define EE_TIMER_ISR_ON_PRIO3  3
#define EE_TIMER_ISR_ON_PRIO4  4
#define EE_TIMER_ISR_ON_PRIO5  5
#define EE_TIMER_ISR_ON_PRIO6  6
#define EE_TIMER_ISR_ON_PRIO7  7

/* Set base address and set ISR priority */
#define EE_TIMER_SET_PRIORITY(prio) INT_CFADDR = 0xE0;\
                                    INT_CFDATA7 = prio;

#endif /* __MC9S12XS128__ */

__INLINE__ int __ALWAYS_INLINE__ EE_timer_init_us(EE_UINT16 tim_id, EE_UINT32 period_us, EE_UINT8 isr_mode) {
	
	EE_UINT32 max_period, ticks, prd;
	EE_UINT8 psc;
	
	if( EE_get_peripheral_frequency_mhz()==0 )
		return -1; /* Please set peripheral frequency before timer initialization... */
	
	/* Reset timer module */
	EE_S12_TIMER_SYSCTRL_REG1 = 0;		/* turn off Timer module */
	EE_S12_TIMER_SYSCTRL_REG2 = 0;		/* clear Timer sys_reg 2 */
	EE_S12_TIMER_CNT_REG = 0;			/* clear Timer counter */
	EE_S12_TIMER_ISR_FLAG1 = 0;			/* clear isr flags */
	EE_S12_OUTCMP_MASK_REG = 0;			/* Output compare mask cleared */
	EE_S12_OUTCMP_DATA_REG = 0; 		/* Output compare data cleared */
	
	EE_S12_TIMER_ICOC_SEL |= (0x01 << tim_id);	/* output compare mode */
	EE_S12_TIMER_CTRL_REG2 &= (~(0x03 << (tim_id << 1)));		/* do not use timer pins */
	EE_S12_TIMER_CTRL_REG4 &= (~(0x03 << (tim_id << 1)));		/* do not use input capture */
	EE_S12_OUTCMP_DIS_REG |= (0x01 << tim_id);	/* disable output compare pin */
	
	/* Timer ID dependent feature */
	max_period  = 0xffff;
	ticks = period_us * EE_get_peripheral_frequency_mhz();
	if (ticks < max_period) {
		prd = ticks;
		psc = EE_TIMER_PRESCALE_FACTOR_1;
	} else if (ticks / 8 < max_period) {
		prd = ticks / 8;
		psc = EE_TIMER_PRESCALE_FACTOR_8;
	} else if (ticks / 64 < max_period) {
		prd = ticks / 64;
		psc = EE_TIMER_PRESCALE_FACTOR_64;
	} else if (ticks / 128 < max_period) {
		prd = ticks / 128;
		psc = EE_TIMER_PRESCALE_FACTOR_128;
	} else {
		/* Please, the desired period is too big! */
		return -2;
	}

	EE_TIMER_SET_PERIOD( tim_id, (EE_UINT16)prd );
	EE_TIMER_SET_PRESCALER(psc);					/* Prescaler should be the same for all the timers */

	if( isr_mode ) {
		EE_S12_TIMER_IE_REG |= (0x01 << tim_id);	/* enable interrupt */
		EE_TIMER_SET_PRIORITY(isr_mode)
	}
	else {
		EE_S12_TIMER_IE_REG &= (~(0x01 << tim_id));	/* disable interrupt */
	}
	
	return 1; /* all is ok! */
}

__INLINE__ int __ALWAYS_INLINE__ EE_timer_init_ms(EE_UINT16 tim_id, EE_UINT16 period_ms, EE_UINT8 isr_mode) {
	return EE_timer_init_us(tim_id, (EE_UINT32)period_ms*1000ul,isr_mode);
}

__INLINE__ void __ALWAYS_INLINE__ EE_timer_start( void ) {
	EE_S12_TIMER_SYSCTRL_REG1 = 0x80;	/* turn on Timer module */
}

__INLINE__ void __ALWAYS_INLINE__ EE_timer_stop( void ) {
	EE_S12_TIMER_SYSCTRL_REG1 = 0;		/* turn off Timer module */
}

__INLINE__ void __ALWAYS_INLINE__ EE_timer_reset( void ) {
	EE_S12_TIMER_CNT_REG = 0;			/* clear Timer counter */
}

__INLINE__ void __ALWAYS_INLINE__ EE_timer_clear_ISRflag( EE_UINT16 tim_id ) {
	EE_S12_TIMER_ISR_FLAG1 = 0x01 << tim_id;		/* clear isr flag */
}

__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_timer_get_counter( void ) {
	return EE_S12_TIMER_CNT_REG;
}

__INLINE__ void __ALWAYS_INLINE__ EE_timer_enable_ISR( EE_UINT16 tim_id, EE_UINT8 isr_mode ) {
	EE_S12_TIMER_IE_REG |= (0x01 << tim_id);		/* enable interrupt */
	EE_TIMER_SET_PRIORITY(isr_mode)
}

__INLINE__ void __ALWAYS_INLINE__ EE_timer_disable_ISR( EE_UINT16 tim_id ) {
	EE_S12_TIMER_IE_REG &= (~(0x01 << tim_id));		/* disable interrupt */
}

#endif /* __INCLUDE_MC9S12_TIMER_H__ */

#endif /* __USE_TIMER__ */
