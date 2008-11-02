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
 * CVS: $Id: ee_dlcheck.c,v 1.1 2008/04/23 11:36:01 francesco Exp $
 */

#include "ee_internal.h"

#ifndef __PRIVATE_DEADLINECHECK__
/* il controllo periodico delle deadlines deve essere fatto con una
   periodicita' di almeno 1/4 del tempo di vita del timer */
void EE_iris_deadlinecheck(EE_TID maxtask, EE_TIME tmp_time)
{
  register EE_UREG t;

  for (t=0; t<maxtask; t++) {
    if (EE_th_active[t] && (EE_STIME)(tmp_time - EE_th_absdline[t]) > (EE_TIMER_LIFETIME>>2)) {
      if (EE_th_nact[t])
	/* hmmm... probably there is something strange here... a ready
	   thread with  number of activations  > 0 should  never drift
	   away! */
	for (;;);
      else
	EE_th_active[t]=0;
	
    }
  }
}
#endif
