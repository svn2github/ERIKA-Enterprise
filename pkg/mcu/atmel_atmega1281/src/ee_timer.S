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

#include "mcu/atmel_atmega1281/inc/ee_avr5def.S"

.global init_timer0
.global init_timer1
.global init_timer2
.global init_timer3
.global init_timer4
.global init_timer5

.global timer0_start
.global timer1_start
.global timer2_start
.global timer3_start
.global timer4_start
.global timer5_start

.global timer0_stop
.global timer1_stop
.global timer2_stop
.global timer3_stop
.global timer4_stop
.global timer5_stop

.global timer0_get
.global timer1_get
.global timer2_get
.global timer3_get
.global timer4_get
.global timer_5get



.text

timer0_start:
	clr r18
	clr r19
	ldi r20, 0x00
	sts TCNT0, r20
	// mask
	#ifdef __TIMER0_CLK_DIV1__	
 	ldi  r19, 0x01 	// set
	#endif
	#ifdef __TIMER0_CLK_DIV8__	
 	ldi  r19, 0x02 	// set
	#endif
	#ifdef __TIMER0_CLK_DIV64__	
 	ldi  r19, 0x04 	// set
	#endif
	#ifdef __TIMER0_CLK_DIV256__	
 	ldi  r19, 0x06 	// set
	#endif
	#ifdef __TIMER0_CLK_DIV1024__	
 	ldi  r19, 0x07 	// set
	#endif
	in r18, TCCR0B
	or r18, r18	
	out TCCR0B,r19 ; Timer clock 
	sei
	ret

timer1_start:
	clr r18
	clr r19
	andi r19, 0xf8 		// mask
	#ifdef __TIMER1_CLK_DIV1__	
 	ori  r19, 0x01 	// set
	#endif
	#ifdef __TIMER1_CLK_DIV8__	
 	ori  r19, 0x02 	// set
	#endif
	#ifdef __TIMER1_CLK_DIV64__	
 	ori  r19, 0x03 	// set
	#endif
	#ifdef __TIMER1_CLK_DIV256__	
 	ori  r19, 0x04 	// set
	#endif
	#ifdef __TIMER1_CLK_DIV1024__	
 	ori  r19, 0x05 	// set
	#endif
	in r18, TCCR1B
	or r19, r18	
	out TCCR1B,r19 ; Timer clock 
	sei
	ret
	
	
timer2_start:
	clr r19
	clr r18
	// mask
	#ifdef __TIMER2_CLK_DIV1__	
 	ldi  r19, 0x01 	// set
	#endif
	#ifdef __TIMER2_CLK_DIV8__	
 	ldi  r19, 0x02 	// set
	#endif
	#ifdef __TIMER2_CLK_DIV32__	
 	ldi  r19, 0x03 	// set
	#endif
	#ifdef __TIMER2_CLK_DIV64__	
 	ldi  r19, 0x04 	// set
	#endif
	#ifdef __TIMER2_CLK_DIV128__	
 	ldi  r19, 0x05 	// set
	#endif
	#ifdef __TIMER2_CLK_DIV256__	
 	ldi  r19, 0x06 	// set
	#endif
	#ifdef __TIMER2_CLK_DIV1024__	
 	ldi  r19, 0x07 	// set
	#endif
	in r18, TCCR2B
	or r19, r18	
	out TCCR2B,r19 ; Timer clock 
	sei 
	ret
	
timer3_start:
	clr r18
	clr r19
	ldi r20, 0x00
	ldi r21, 0x00
	sts TCNT3L, r20
	sts TCNT3H, r21
	// mask
	#ifdef __TIMER3_CLK_DIV1__	
 	ldi  r19, 0x01 	// set
	#endif
	#ifdef __TIMER3_CLK_DIV8__	
 	ldi  r19, 0x02 	// set
	#endif
	#ifdef __TIMER3_CLK_DIV64__	
 	ldi  r19, 0x03 	// set
	#endif
	#ifdef __TIMER3_CLK_DIV256__	
 	ldi  r19, 0x04 	// set
	#endif
	#ifdef __TIMER3_CLK_DIV1024__	
 	ldi  r19, 0x05 	// set
	#endif
	lds r18, TCCR3B
	or r19, r18	
	sts TCCR3B,r19 ; Timer clock 
	sei
	ret

timer4_start:
	clr r18
	clr r19
	ldi r20, 0x00
	ldi r21, 0x00
	sts TCNT4L, r20
	sts TCNT4H, r21
	// mask
	#ifdef __TIMER3_CLK_DIV1__	
 	ldi  r19, 0x01 	// set
	#endif
	#ifdef __TIMER3_CLK_DIV8__	
 	ldi  r19, 0x02 	// set
	#endif
	#ifdef __TIMER3_CLK_DIV64__	
 	ldi  r19, 0x03 	// set
	#endif
	#ifdef __TIMER3_CLK_DIV256__	
 	ldi  r19, 0x04 	// set
	#endif
	#ifdef __TIMER3_CLK_DIV1024__	
 	ldi  r19, 0x05 	// set
	#endif
	lds r18, TCCR4B
	or r19, r18	
	sts TCCR4B,r19 ; Timer clock 
	sei
	ret
	
timer5_start:
	clr r18
	clr r19
	ldi r20, 0x00
	ldi r21, 0x00
	sts TCNT5L, r20
	sts TCNT5H, r21
	// mask
	#ifdef __TIMER3_CLK_DIV1__	
 	ldi  r19, 0x01 	// set
	#endif
	#ifdef __TIMER3_CLK_DIV8__	
 	ldi  r19, 0x02 	// set
	#endif
	#ifdef __TIMER3_CLK_DIV64__	
 	ldi  r19, 0x03 	// set
	#endif
	#ifdef __TIMER3_CLK_DIV256__	
 	ldi  r19, 0x04 	// set
	#endif
	#ifdef __TIMER3_CLK_DIV1024__	
 	ldi  r19, 0x05 	// set
	#endif
	lds r18, TCCR5B
	or r19, r18	
	sts TCCR5B,r19 ; Timer clock 
	sei
	ret
	
init_timer0:
	clr r19
	clr r18
	ldi r19, (1<<0)
	in r18, TIFR0
	or r19, r18
	out TIFR0, r19 ; Clear TOV0/ clear pending interrupts
	ldi r19, (1<<0)
	in r18,TIMSK0
	or r19, r18
	out TIMSK0,r19 ; Enable Timer/Counter0 Overflow Interrupt	
	ret
	
init_timer2:
	clr r19
	clr r18
	ldi r19, (1<<0)
	in r18, TIFR2
	or r19, r18
	out TIFR2, r19 ; Clear TOV2/ clear pending interrupts
	clr r19
	ldi r19, (1<<0)
	in r18,TIMSK2
	or r19, r18
	out TIMSK2,r19 ; Enable Timer/Counter2 Overflow Interrupt	
	ret
	
init_timer1:
	clr r19
	clr r18
	ldi r19, (1<<0)
	in r18, TIFR1
	or r19, r18
	out TIFR1, r16 ; Clear TOV1/ clear pending interrupts
	ldi r19, (1<<0)
	in r18,TIMSK1
	or r19, r18
	out TIMSK1,r19 ; Enable Timer/Counter1 Overflow Interrupt	
	ret
	
init_timer3:
	clr r19
	clr r18
	ldi r19, (1<<0)
	lds r18, TIFR3
	or r19, r18
	sts TIFR3, r19 ; Clear TOV3/ clear pending interrupts
	ldi r19, (1<<0)
	lds r18,TIMSK3
	or r19, r18
	sts TIMSK3,r19 ; Enable Timer/Counter3 Overflow Interrupt	
	ret
	
init_timer4:
	clr r19
	clr r18
	ldi r19, (1<<0)
	lds r18, TIFR4
	or r19, r18
	sts TIFR4, r19 ; Clear TOV4/ clear pending interrupts
	ldi r19, (1<<0)
	lds r18,TIMSK4
	or r19, r18
	sts TIMSK4,r19 ; Enable Timer/Counter4 Overflow Interrupt	
	ret

init_timer5:
	clr r19
	clr r18
	ldi r19, (1<<0)
	lds r18, TIFR5
	or r19, r18
	sts TIFR5, r19 ; Clear TOV5/ clear pending interrupts
	ldi r19, (1<<0)
	lds r18,TIMSK5
	or r19, r18
	sts TIMSK5,r19 ; Enable Timer/Counter5 Overflow Interrupt	
	ret
	
	
	
	
	
	
	
timer0_stop:
	cli	
	ldi r18, 0xF8
	in r19, TCCR0B
	and r18,r19
	out TCCR0B, r18	//clear cso cs1 cs2 of TCCR0B register. Stop the timer.
	sei
	ret
	
timer2_stop:
	cli	
	ldi r18, 0xF8
	in r19, TCCR2B
	and r18,r19
	out TCCR2B, r18	//clear cso cs1 cs2 of TCCR2B register. Stop the timer.
	sei
	ret
	
timer1_stop:
	cli	
	ldi r18, 0xF8
	in r19, TCCR1B
	and r18,r19
	out TCCR1B, r18	//clear cso cs1 cs2 of TCCR1B register. Stop the timer.
	sei
	ret
	
timer3_stop:
	cli
	ldi r18, 0xF8
	lds r19, TCCR3B
	and r18,r19
	sts TCCR3B, r18	//clear cso cs1 cs2 of TCCR3B register. Stop the timer.
	sei
	ret
	
timer4_stop:
	cli	
	ldi r18, 0xF8
	in r19, TCCR4B
	and r18,r19
	out TCCR4B, r18	//clear cso cs1 cs2 of TCCR4B register. Stop the timer.
	sei
	ret
	
timer5_stop:
	cli
	ldi r18, 0xF8
	lds r19, TCCR5B
	and r18,r19
	sts TCCR3B, r18	//clear cso cs1 cs2 of TCCR5B register. Stop the timer.
	sei
	ret
	
	
	
	
	
timer0_get:
	cli
	in r24, TCNT0
	sei 
	ret

timer2_get:
	cli
	in r24, TCNT2
	sei 
	ret
	
timer1_get:
	cli
	in r22, TCNT1L
	in r24, TCNT1H
	sei 
	ret
	
timer3_get:
	cli
	lds r24, TCNT3L
	lds r25, TCNT3H
	sei 
	ret

timer4_get:
	cli
	lds r24, TCNT4L
	lds r25, TCNT4H
	sei 
	ret

timer5_get:
	cli
	lds r24, TCNT5L
	lds r25, TCNT5H
	sei 
	ret
	
	


