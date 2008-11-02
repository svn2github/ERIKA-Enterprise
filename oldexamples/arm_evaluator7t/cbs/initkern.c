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
 * CVS: $Id: initkern.c,v 1.1.1.1 2004/11/05 16:03:03 pj Exp $
 */

#include "ee.h"

const EE_TYPERELDLINE EE_th_prlevel[THREAD_MAX] = {
  0x40, 0x10, 0x04, 0x01
};        /* task preemption level */

const EE_TYPECAPACITY EE_th_budget[THREAD_MAX] = {
  0x2000, 0x2000, 0x2000, 0x2000
};         /* CBS mean execution time */

const EE_TYPERELDLINE EE_th_period[THREAD_MAX] = {
  0x10000, 0x20000, 0x40000, 0x80000
};         /* CBS replenishment period */

const EE_TYPEPRIO     EE_mutex_ceiling[MUTEX_MAX] =
{ 
  0x40,  /* mutex01 */
  0x04   /* mutex23 */
};     /* mutex ceiling */


/* RAM */
EE_TYPECAPACITY EE_th_budget_avail[THREAD_MAX];	 /* available budget */
EE_TYPEABSDLINE EE_th_absdline[THREAD_MAX];        /* task absolute deadline */

EE_TYPESTATUS   EE_th_status[THREAD_MAX] = {
    EE_READY,
    EE_READY,
    EE_READY,
    EE_READY
};	         /* thread status */

EE_TYPENACT     EE_th_nact[THREAD_MAX];		 /* pending activations */

EE_TID          EE_th_next[THREAD_MAX] = {
    EE_NIL,
    EE_NIL,
    EE_NIL,
    EE_NIL
};		 /* next task in queue */

EE_TYPEPRIO     EE_mutex_oldceiling[MUTEX_MAX];	 /* old mutex ceiling */

EE_UREG     EE_th_lockedcounter[THREAD_MAX];	 /* number of mutexes locked */
/* EE_mutex_lockedcounter is used to know if a task have to be put in the ready or 
   in the stacked queue */

EE_UREG         EE_th_active[THREAD_MAX];             /* task is active ? */
/* a task is set to not active whenever its deadline goes too much in
   the past. usually, it is an user interrupt that calls
   EE_cbs_deadlinecheck */

/* system ceiling */
EE_TYPEPRIO EE_sys_ceiling;

/* The first task into the ready queue -> ready means that the task
   has been activated without never running or that it has been
   preempted by another task, in both cases without currently locking
   any resource */
EE_TID EE_rqfirst = EE_NIL;

/* The first stacked task -> stacked means a preempted task that owns a mutex */
EE_TID EE_stkfirst = EE_NIL;

/* The running task */
EE_TID EE_exec = EE_NIL;

/* a temporary value that stores the timer read that was done before
   executing a task. That value is useful for capacity accounting */
EE_TIME EE_last_time;
