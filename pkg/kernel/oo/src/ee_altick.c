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
 * Author: 2002 Paolo Gai
 * CVS: $Id: ee_altick.c,v 1.5 2006/06/08 20:40:42 pj Exp $
 */

#include "ee_internal.h"

#ifndef __PRIVATE_COUNTER_TICK__
void EE_oo_alarm_insert(AlarmType AlarmID, TickType increment)
{
  register AlarmType current, previous;
  
#ifdef __OO_ORTI_ALARMTIME__
  EE_ORTI_alarmtime[AlarmID] = increment + 
    EE_counter_RAM[EE_alarm_ROM[AlarmID].c].value;
#endif

  current = EE_counter_RAM[EE_alarm_ROM[AlarmID].c].first;

  if (current == -1) {
    /* the alarm becomes the first into the delta queue */
    EE_counter_RAM[EE_alarm_ROM[AlarmID].c].first = AlarmID;
  } else if (EE_alarm_RAM[current].delta > increment) {
    EE_counter_RAM[EE_alarm_ROM[AlarmID].c].first = AlarmID;
    EE_alarm_RAM[current].delta -= increment;
  }
  else {
    /* the alarm is not the first into the delta queue */

    /* follow the delta chain until I reach the right place */
    do {
      increment -= EE_alarm_RAM[current].delta;
      previous = current;
      current = EE_alarm_RAM[current].next;
    } while(current != -1 && EE_alarm_RAM[current].delta <= increment);

    /* insert the alarm between previous and current */
    if (current != -1)
      EE_alarm_RAM[current].delta -= increment;
    EE_alarm_RAM[previous].next = AlarmID;
  }

  EE_alarm_RAM[AlarmID].delta = increment;
  EE_alarm_RAM[AlarmID].next = current;
}


void EE_oo_counter_tick(CounterType c)
{
  register AlarmType current;
  register TaskType TaskID;
#if defined(__OO_ECC1__) || defined(__OO_ECC2__)
  register EventMaskType Mask;
#endif
  register EE_FREG flag;

#ifdef __OO_ORTI_SERVICETRACE__
  EE_ORTI_servicetrace = EE_SERVICETRACE_COUNTERTICK+1;
#endif

  flag = EE_hal_begin_nested_primitive();
  
  /* increment the counter value */
  EE_counter_RAM[c].value++;

  /* if there are queued alarms */
  if (EE_counter_RAM[c].first != -1) {
    /* decrement first queued alarm delta */
    EE_alarm_RAM[EE_counter_RAM[c].first].delta--;

    /* execute all the alarms with counter 0 */
    current = EE_counter_RAM[c].first;
    while (!EE_alarm_RAM[current].delta) {
      /* execute it */
      switch (EE_alarm_ROM[current].action) {



      case  EE_ALARM_ACTION_TASK:
	/* activate the task; NOTE: no preemption at all... 
	   This code was directly copied from ActivateTask */

	TaskID = EE_alarm_ROM[current].TaskID;

#ifdef __RN_TASK__
	if (TaskID & EE_REMOTE_TID) {
	  register EE_TYPERN_PARAM par;
	  par.pending = 1;
	  /* forward the request to another CPU whether the thread do
	     not become to the current CPU */
	  EE_rn_send(TaskID & ~EE_REMOTE_TID, EE_RN_TASK, par );
	  break;
	}
#endif

#ifdef __OO_EXTENDED_STATUS__    
	/* check if the task Id is valid */
	if (TaskID < 0 || TaskID >= EE_MAX_TASK) {
#ifdef __OO_ORTI_LASTERROR__
	  EE_ORTI_lasterror = E_OS_ID;
#endif
	  
#ifdef __OO_HAS_ERRORHOOK__
	  if (!EE_ErrorHook_nested_flag) {
#ifndef __OO_ERRORHOOK_NOMACROS__
	    EE_oo_ErrorHook_ServiceID = OSServiceId_CounterTick;
	    EE_oo_ErrorHook_data.CounterTick_prm.AlarmID = current;
	    EE_oo_ErrorHook_data.CounterTick_prm.TaskID = TaskID;
	    EE_oo_ErrorHook_data.CounterTick_prm.action =
	      EE_alarm_ROM[current].action;
#endif
	    EE_ErrorHook_nested_flag = 1;
	    ErrorHook(E_OS_ID);
	    EE_ErrorHook_nested_flag = 0;
	  }
#endif
	  break;
	}
#endif
	
	/* check for pending activations */
	if (EE_th_rnact[TaskID] == 0) {
#ifdef __OO_ORTI_LASTERROR__
	  EE_ORTI_lasterror = E_OS_LIMIT;
#endif
	  
#ifdef __OO_HAS_ERRORHOOK__
	  if (!EE_ErrorHook_nested_flag) {
#ifndef __OO_ERRORHOOK_NOMACROS__
   	    EE_oo_ErrorHook_ServiceID = OSServiceId_CounterTick;
	    EE_oo_ErrorHook_data.CounterTick_prm.AlarmID = current;
	    EE_oo_ErrorHook_data.CounterTick_prm.TaskID = TaskID;
	    EE_oo_ErrorHook_data.CounterTick_prm.action =
	      EE_alarm_ROM[current].action;
#endif
	    EE_ErrorHook_nested_flag = 1;
	    ErrorHook(E_OS_LIMIT);
	    EE_ErrorHook_nested_flag = 0;
	  }
#endif
	  break;
	} 


	EE_th_rnact[TaskID]--;
	
#if defined(__OO_BCC2__) || defined(__OO_ECC2__)
	if (EE_th_status[TaskID] == SUSPENDED) {
	  EE_th_status[TaskID] = READY;
#ifdef __OO_ECC2__
	  /* When an extended task is transferred from suspended state
	     into ready state all its events are cleared*/
	  EE_th_event_active[TaskID] = 0;
#endif
	}
#else
	EE_th_status[TaskID] = READY;
#ifdef __OO_ECC1__
	EE_th_event_active[TaskID] = 0;
#endif
#endif
  
	/* insert the task in the ready queue */
	EE_rq_insert(TaskID);

  	break;




#if defined(__OO_ECC1__) || defined(__OO_ECC2__)
      case EE_ALARM_ACTION_EVENT:
	/* set an event for a task... NOTE: no preemption at all... 
	   This code was directly copied from SetEvent */
	
	TaskID = EE_alarm_ROM[current].TaskID;
	Mask = EE_alarm_ROM[current].Mask;

#ifdef __RN_EVENT__
	if (TaskID & EE_REMOTE_TID) {
	  register EE_TYPERN_PARAM par;
	  par.ev = Mask;
	  /* forward the request to another CPU whether the thread do
	     not become to the current CPU */
	  EE_rn_send(TaskID & ~EE_REMOTE_TID, EE_RN_EVENT, par );

	  break;
	}
#endif
	

#ifdef __OO_EXTENDED_STATUS__    
	/* check if the task Id is valid */
	if (TaskID < 0 || TaskID >= EE_MAX_TASK) {
#ifdef __OO_ORTI_LASTERROR__
	  EE_ORTI_lasterror = E_OS_ID;
#endif
	  
#ifdef __OO_HAS_ERRORHOOK__
	  if (!EE_ErrorHook_nested_flag) {  
#ifndef __OO_ERRORHOOK_NOMACROS__
            EE_oo_ErrorHook_ServiceID = OSServiceId_CounterTick;
	    EE_oo_ErrorHook_data.CounterTick_prm.AlarmID = current;
	    EE_oo_ErrorHook_data.CounterTick_prm.TaskID = TaskID;
	    EE_oo_ErrorHook_data.CounterTick_prm.Mask = Mask;
	    EE_oo_ErrorHook_data.CounterTick_prm.action =
	      EE_alarm_ROM[current].action;
#endif
	    EE_ErrorHook_nested_flag = 1;
	    ErrorHook(E_OS_ID);
	    EE_ErrorHook_nested_flag = 0;
	  }
#endif
	  break;
	}
	


	if (!EE_th_is_extended[TaskID]) {
#ifdef __OO_ORTI_LASTERROR__
	  EE_ORTI_lasterror = E_OS_ACCESS;
#endif

#ifdef __OO_HAS_ERRORHOOK__
	  if (!EE_ErrorHook_nested_flag) {
#ifndef __OO_ERRORHOOK_NOMACROS__
            EE_oo_ErrorHook_ServiceID = OSServiceId_CounterTick;
	    EE_oo_ErrorHook_data.CounterTick_prm.AlarmID = current;
	    EE_oo_ErrorHook_data.CounterTick_prm.TaskID = TaskID;
	    EE_oo_ErrorHook_data.CounterTick_prm.Mask = Mask;
	    EE_oo_ErrorHook_data.CounterTick_prm.action =
	      EE_alarm_ROM[current].action;
#endif
	    EE_ErrorHook_nested_flag = 1;
	    ErrorHook(E_OS_ACCESS);
	    EE_ErrorHook_nested_flag = 0;
	  }
#endif
	  
	  break;
	}
#endif

	if (EE_th_status[TaskID] == SUSPENDED) {
#ifdef __OO_ORTI_LASTERROR__
	  EE_ORTI_lasterror = E_OS_STATE;
#endif
	  
#ifdef __OO_HAS_ERRORHOOK__
	  if (!EE_ErrorHook_nested_flag) {
#ifndef __OO_ERRORHOOK_NOMACROS__
            EE_oo_ErrorHook_ServiceID = OSServiceId_CounterTick;
	    EE_oo_ErrorHook_data.CounterTick_prm.AlarmID = current;
	    EE_oo_ErrorHook_data.CounterTick_prm.TaskID = TaskID;
	    EE_oo_ErrorHook_data.CounterTick_prm.Mask = Mask;
	    EE_oo_ErrorHook_data.CounterTick_prm.action =
	      EE_alarm_ROM[current].action;
#endif
	    EE_ErrorHook_nested_flag = 1;
	    ErrorHook(E_OS_STATE);
	    EE_ErrorHook_nested_flag = 0;
	  }
#endif
	  break;
	}
	

	/* set the event mask */
	EE_th_event_active[TaskID] |= Mask;
	
	/* check if the task was waiting for an event we just set
	 *
	 * WARNING:
	 * the test with status==WAITING is FUNDAMENTAL to avoid double
	 * insertion of the task in the ready queue!!! Example, when I call
	 * two times the same setevent... the first time the task must go in
	 * the ready queue, the second time NOT!!!
	 */
	if (EE_th_event_waitmask[TaskID] & Mask &&
	    EE_th_status[TaskID] == WAITING) {
	  /* if yes, the task must go back into the READY state */
	  EE_th_status[TaskID] = READY;
	  /* insert the task in the ready queue */
	  EE_rq_insert(TaskID);
	}  

	break;
#endif



      
      case EE_ALARM_ACTION_CALLBACK:
	((void (*)(void))EE_alarm_ROM[current].f)();
	break;
      };
      
      /* remove the current entry */
      EE_counter_RAM[c].first = EE_alarm_RAM[current].next;

      /* the alarm is cyclic? */
      if (EE_alarm_RAM[current].cycle) {
	/* enqueue it again 
	   note: this can modify EE_counter_RAM[c].first!!! see (*)
	*/
	EE_oo_alarm_insert(current,EE_alarm_RAM[current].cycle);
      } else {
	/* alarm no more used! */
	EE_alarm_RAM[current].used = 0;
      }
      /* (*) here we need EE_counter_RAM[c].first again... */
      current = EE_counter_RAM[c].first;
      if (current == -1) break;
    }
  }    

  EE_hal_end_nested_primitive(flag);
}
#endif
