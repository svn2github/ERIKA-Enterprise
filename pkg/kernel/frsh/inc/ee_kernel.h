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
 * CVS: $Id: ee_kernel.h,v 1.4 2008/07/16 09:46:12 francesco Exp $
 */

#include "kernel/frsh/inc/ee_common.h"

#ifndef __INCLUDE_FRSH_KERN_H__
#define __INCLUDE_FRSH_KERN_H__

/* This macros are used to define a task */
#define DeclareTask(t) void Func##t(void)
#define TASK(t) void Func##t(void)

/*************************************************************************
 System functions
 *************************************************************************/

#ifndef __PRIVATE_FRSH_INIT__
int EE_frsh_init(void);
#endif

#ifndef __PRIVATE_SYS_GETTIME__
#ifdef __TIME_SUPPORT__
EE_TIME EE_frsh_sys_gettime(void);
#endif
#endif


/*************************************************************************
 Primitives
 *************************************************************************/

#ifndef __PRIVATE_THREAD_ACTIVATE__
/* This primitive activates a thread once and then execute the
   preemption test */
void EE_frsh_thread_activate(EE_TID t);
#endif



/* mutexes are called using symbolic names as parameters. using MUTEX
   values different from these constants give an unspecified behavior. 
   Mutex constants are contained into structs.ini */

#ifndef __PRIVATE_MUTEX_LOCK__
/* This primitive implements a SRP mutex lock */
void EE_frsh_mutex_lock(EE_MUTEX m);
#endif

#ifndef __PRIVATE_MUTEX_UNLOCK__
/* This primitive implements a SRP mutex unlock */
void EE_frsh_mutex_unlock(EE_MUTEX m);
#endif

#endif


