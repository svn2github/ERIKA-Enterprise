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
 * CVS: $Id: thumb.c,v 1.1.1.1 2004/11/05 16:03:03 pj Exp $
 */

#include "code.h"

EE_TIME t1,t2,t3,t4, ov0, ov1;
EE_TIME tact, tpostcapacity, tpremutexl, tpostmutexl;
EE_TIME tpremutexu,tpostmutexu, tpostendcycle;
EE_TIME tprecapacity, tpostcapacity,tpremutexu2,tpostmutexu2;
EE_TIME overhead,tkmkready1,thmkready2,thmkready3,thact,capacityirq,mutexl,mutexu_nopreempt,tecycle,mutexu_preempt;

void thread0(void)
{
  int i;
  tact = EE_timer_0_get();

  for (i =0; i< 1000000000; i++) {
  }
}



void thread1(void)
{
  tpostcapacity = EE_timer_0_get();

  tpremutexl = EE_timer_0_get();
  EE_mutex_lock(mutex01);
  tpostmutexl = EE_timer_0_get();

  tpremutexu = EE_timer_0_get();
  EE_mutex_unlock(mutex01);
  tpostmutexu = EE_timer_0_get();
}



void thread2(void)
{
  int i;
  tpostendcycle = EE_timer_0_get();

  EE_mutex_lock(mutex01);
  for (i=0; i<10000; i++);
  tpremutexu2 = EE_timer_0_get();
  EE_mutex_unlock(mutex01);

}

int yyy;
void pippo()
{
  yyy = 0;
}


void thread3(void)
{
  tpostmutexu2 = EE_timer_0_get();

  overhead = ov0-ov1;

  tkmkready1  = (t1-t2-overhead)*20;
  thmkready2  = (t2-t3-overhead)*20;
  thmkready3  = (t3-t4-overhead)*20;
  thact       = (t4-tact-overhead)*20;
  capacityirq = (tprecapacity-tpostcapacity-overhead)*20;
  mutexl      = (tpremutexl-tpostmutexl-overhead)*20;
  mutexu_nopreempt = (tpremutexu - tpostmutexu-overhead)*20;
  tecycle     = (tpostmutexu-tpostendcycle-overhead)*20;
  mutexu_preempt = (tpremutexu2- tpostmutexu2-overhead)*20;
  pippo();
}

