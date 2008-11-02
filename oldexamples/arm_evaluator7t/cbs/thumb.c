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
 * Author: 2003 Paolo Gai
 * CVS: $Id: thumb.c,v 1.2 2005/03/11 11:05:31 pj Exp $
 */

#include "code.h"

#define WITHMUTEXES

#ifndef WITHMUTEXES

/*
 * Display a number during a short pause 
 */
//#define LOOP_LENGHT 100000
//#define LOOP_LENGHT 10000
#define LOOP_LENGHT 1000
//#define LOOP_LENGHT 100
//#define LOOP_LENGHT 10
//#define LOOP_LENGHT 1
void pause_and_display(int disp)
{
    int i=0;
    int j=0;
    
    for (i=0; i<LOOP_LENGHT; i++) {
        EE_LCD_display(disp);
        for(j=0; j<10; j++) {
            /* do nothing */
        }
    }
}

void mydelay(void)
{
  volatile int i;
  for (i=0; i<100000; i++);
}

void thread0(void)
{
  int i;
  for (i=0; i<100; i++) {
    EE_hal_disableIRQ();
    EE_led_1_on();
    pause_and_display(0x0);
    EE_led_1_off();
    EE_hal_enableIRQ();
    mydelay();
  }
  EE_th_active[0] = 0;
}



void thread1(void)
{
  for (;;) {
    EE_hal_disableIRQ();
    EE_led_2_on();
    pause_and_display(0x1);
    EE_led_2_off();
    EE_hal_enableIRQ();
    mydelay();
  }
}



void thread2(void)
{
  for (;;) {
    EE_hal_disableIRQ();
    EE_led_3_on();
    pause_and_display(0x2);
    EE_led_3_off();
    EE_hal_enableIRQ();
    mydelay();
  }
}



void thread3(void)
{
  int i=0;
  for (;;) {
    EE_hal_disableIRQ();
    EE_led_4_on();
    pause_and_display(0x3);
    EE_led_4_off();
    EE_hal_enableIRQ();
    mydelay();

    if (i==130) {
      i = 0;
      EE_thread_activate(0);
    }
    else
      i++;
  }
}

#else


/*
 * Display a number during a short pause 
 */
//#define LOOP_LENGHT 100000
//#define LOOP_LENGHT 10000
#define LOOP_LENGHT 1000
//#define LOOP_LENGHT 100
//#define LOOP_LENGHT 10
//#define LOOP_LENGHT 1
void pause_and_display(void)
{
    int i=0;
    int j=0;
    static int xxx = 0;
    xxx++;
    for (i=0; i<LOOP_LENGHT; i++) {
    EE_hal_disableIRQ();
        EE_lcd_display(xxx);
    EE_hal_enableIRQ();
        for(j=0; j<10; j++) {
            /* do nothing */
        }
    }
    xxx--;
}


void mydelay(void)
{
  volatile int i;
  for (i=0; i<100000; i++) {
    EE_hal_disableIRQ();
    EE_lcd_display(EE_sys_ceiling);
    EE_hal_enableIRQ();
  }
}

void myled(int l, int onoff)
{
    EE_hal_disableIRQ();
    switch (l) {
    case 1:
      if (onoff) EE_led_1_on(); else EE_led_1_off(); break;
    case 2:
      if (onoff) EE_led_2_on(); else EE_led_2_off(); break;
    case 3:
      if (onoff) EE_led_3_on(); else EE_led_3_off(); break;
    case 4:
      if (onoff) EE_led_4_on(); else EE_led_4_off(); break;
    }
    EE_hal_enableIRQ();
}

void thread0(void)
{
  //  int i;
  for (;;) {
    EE_mutex_lock(mutex01);
    myled(1,1);
    pause_and_display();
    myled(1,0);
    EE_mutex_unlock(mutex01);
    mydelay();
  }
  EE_th_active[0] = 0;
}



void thread1(void)
{
  for (;;) {
    EE_mutex_lock(mutex01);
    myled(2,1);
    pause_and_display();
    myled(2,0);
    EE_mutex_unlock(mutex01);
    mydelay();
  }
}



void thread2(void)
{
  for (;;) {
    EE_mutex_lock(mutex23);
    myled(3,1);
    pause_and_display();
    myled(3,0);
    EE_mutex_unlock(mutex23);
    mydelay();
  }
}



void thread3(void)
{
  //  int i=0;
  for (;;) {
    EE_mutex_lock(mutex23);
    myled(4,1);
    pause_and_display();
    myled(4,0);
    EE_mutex_unlock(mutex23);
    mydelay();

    //    if (i==130) {
    //      i = 0;
    //      EE_thread_activate(0);
    //    }
    //    else
    //      i++;
  }
}

#endif
