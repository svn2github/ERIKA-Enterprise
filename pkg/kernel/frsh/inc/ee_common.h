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
 * Author: 2008 Paolo Tiberi & Francesco Focacci
 * CVS: $Id: ee_common.h,v 1.6 2008/07/18 09:53:55 tiberipa Exp $
 */

#ifndef __INCLUDE_FRSH_COMMON_H__
#define __INCLUDE_FRSH_COMMON_H__


/*************************************************************************
 Note
 *************************************************************************/

// (currently in italian, sorry)
// ho una coda stacked, che contiene tutti i task che sono stati messi in esecuzione che hanno lockato una risorsa
//per essere messi in esecuzione vuo dire che avevano prlevel>del sysceiling e che avevano deadline < di quello in cima alla coda stacked,
// questo vuol dire che la coda stacked e' ordinata per deadline in modo naturale.

// se quando vengo preemptato ho lockato una risorsa vado a finire nella coda stacked altrimenti nella ready
// il check di preemption nella activate e' tra il task in esecuzione ed il primo nella coda ready, considerando naturalmente il preemption level.
// quando termina il task si suppone che non abbia nessuna risorsa lockata. pertanto (se il suo nact>0) il task viene inserito nella coda ready (non ha risorse lockate), ed il task da eseguire e' scelto tra la coda stacked e la coda ready. la coda ready vince se il preemption level e' > sysceiling & la deadline e' <
// quando un task e' schedulato partendo dalla coda stacked, il task e' rimosso dalla coda stacked e messo dentro exec

// a differenza dei kernel FP e EDF, nel kernel IRIS ho fatto la
// distinzione tra exec e stkfirst. il motivo e' che in generale exec
// potrebbe non influenzare il system ceiling (ad esempio, non ha
// lockato nessun mutex), mentre stacked conserva il significato
// comune dei task che hanno in qualche modo modificato il system
// ceiling. notare che dal momento che FP e EDF implementano i
// preemption thresholds, tutti i task modificano il system ceiling, e
// quindi il task exec viene a coincidere con il primo task stacked.

/*************************************************************************
 Kernel Constants
 *************************************************************************/

/* invalid TID */
#define EE_NIL       ((EE_TID)-1)

/* Thread statuses:
   the thread status is used with a Multistack HAL, for storing a flag that let
   the kernel know if the task has some space allocated on its stack.
*/

#define EE_READY      0

/* used for tasks which go recharging */
#define EE_RECHARGING 2

/* used by semaphores and blocking primitives in general */
#define EE_BLOCKED    4

/* used to know if a task has some space allocated on its stack */
#define EE_WASSTACKED 8

/*************************************************************************
 Kernel Types
 *************************************************************************/

/* priority type, used for system ceiling and preemption level */
#ifndef EE_TYPEPRIO
#define EE_TYPEPRIO EE_UREG
#endif

/* status type */
#ifndef EE_TYPESTATUS
#define EE_TYPESTATUS EE_UREG
#endif

/* relative deadline type */
#ifndef EE_TYPERELDLINE
#define EE_TYPERELDLINE EE_TIME
#endif

/* absolute deadline type */
#ifndef EE_TYPEABSDLINE
#define EE_TYPEABSDLINE EE_TIME
#endif

/* capacity type */
#ifndef EE_TYPECAPACITY
#define EE_TYPECAPACITY EE_STIME
//#define EE_TYPECONTRACT EE_SREG	//trial
#endif

/* pending activation type */
#ifndef EE_TYPENACT
#define EE_TYPENACT EE_UREG
#endif

/* mutex ID type */
#ifndef EE_MUTEX
#define EE_MUTEX EE_UREG
#endif


/*************************************************************************
 Kernel Variables
 *************************************************************************/

/* ROM */
extern const EE_TYPERELDLINE EE_th_prlevel[];        /* task preemption level */
//extern const EE_TYPECAPACITY EE_th_budget[];         /* IRIS mean execution time */
//extern const EE_TYPERELDLINE EE_th_period[];         /* IRIS replenishment period */
extern const EE_TYPEPRIO     EE_mutex_ceiling[];     /* mutex ceiling */

extern EE_TYPECAPACITY EE_th_budget[];         /* IRIS mean execution time */
extern EE_TYPERELDLINE EE_th_period[];         /* IRIS replenishment period */

typedef struct 
{
  EE_TYPECAPACITY capacity;
  EE_TYPERELDLINE period;
  EE_TYPERELDLINE inv_proc_util;
}EE_TYPECONTRACT;

	//const struct contracts EE_contracts[];
    //const EE_TYPECONTRACT EE_contracts[EE_MAX_CONTRACT] = {
extern const EE_TYPECONTRACT EE_contracts[];
	
/* This vector contains the inverse processor utilization of each task 
   if the budget and the period are power of 2, it contains the logarithm of the
   ratio in order to speed up the multiplication */
extern EE_TYPERELDLINE EE_inv_proc_util[];     /* inverse processor utilization */

/* RAM */
extern EE_TYPECAPACITY EE_th_budget_avail[];	 /* available budget (initvalue: 0) */
extern EE_TYPEABSDLINE EE_th_absdline[];           /* task absolute deadline (initvalue: 0) */

extern EE_TYPESTATUS   EE_th_status[];	         /* thread status (initvalue: EE_READY) */
extern EE_TYPENACT     EE_th_nact[];		 /* pending activations (initvalue: 0) */
extern EE_TID          EE_th_next[];		 /* next task in queue (initvalue: EE_NIL) */
extern EE_TYPEPRIO     EE_mutex_oldceiling[];	 /* old mutex ceiling (initvalue: none) */
extern EE_UREG         EE_th_lockedcounter[];	 /* number of mutexes locked (initvalue: 0) */
/* EE_mutex_lockedcounter is used to know if a task have to be put in the ready or 
   in the stacked queue */

extern EE_UREG         EE_th_active[];             /* task is active ? (initvalue: 0) */
/* a task is set to not active whenever its deadline goes too much in
   the past. usually, it is an user interrupt that calls
   EE_iris_deadlinecheck */
   
#ifdef __SEM_FRSH__
#include "../syncobj/inc/ee_sem.h"
extern EE_TID          EE_th_nextsem[];	 /* next task in the sem wait queue (initvalue: EE_NIL) */
extern SemRefType      EE_th_semrefs[];    /* Task reference to the used semaphore */
extern EE_TIME         EE_th_timeouts[];   /* Task semaphore timeouts */
extern char            EE_th_timedout[];   /* used to check if timedout*/
#endif

/* system ceiling (initvalue: 0) */
extern EE_TYPEPRIO EE_sys_ceiling;

/* The first task into the ready queue -> ready means that the task
   has been activated without never running or that it has been
   preempted by another task, in both cases without currently locking
   any resource 
   (initvalue: EE_NIL)
*/
extern EE_TID EE_rqfirst;

/* The first stacked task -> stacked means a preempted task that owns a mutex 
   (initvalue: EE_NIL)
*/
extern EE_TID EE_stkfirst;

/* The first task in the recharging queue
*/
extern EE_TID EE_rcgfirst;

/* The running task 
   (initvalue: EE_NIL)
*/
extern EE_TID EE_exec;

/* a temporary value that stores the timer read that was done before
   executing a task. That value is useful for capacity accounting 
   (initvalue: none)
*/
extern EE_TIME EE_last_time;

/* This variable is used to check whether a the schedule procedure 
 * at the end of an ISR should be executed or not
*/
extern int EE_served;

#endif


