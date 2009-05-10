#ifndef __ozb_kal_erika_h__
#define __ozb_kal_erika_h__

#include <ee.h>
#include <hal/ozb_compiler.h>
#include <hal/ozb_timer.h>

void ozb_kal_external_timer_action(void);

/* tick_duration is expressed in microseconds */
COMPILER_INLINE 
int8_t ozb_kal_erika_init(uint32_t tick_duration) 
{
	/* TODO: make use of this information to properly configure the
		 duration of the tick of the timer connected to the the
		 Counter fot the KAL tasks! */
	/* TODO: Fix all this hard-coding!!*/
	if (tick_duration != 0) {
		#ifdef OZB_HAL_EXTERNAL_TIMER
		/* TODO: call a user callback where the user can be notified 
			 about the kal tick_duration */
		#else
		if (ozb_timer_init(tick_duration, 40000) < 0)
			return -1;
		ozb_timer_set_isr_callback(ozb_kal_external_timer_action);
		ozb_timer_start();
		#endif
	}
	return 1;
}

COMPILER_INLINE 
int8_t ozb_kal_erika_set_body(void (*src)(void), void (**dst)(void)) 
{
	*dst = src;
	return 1;
}

COMPILER_INLINE 
int8_t ozb_kal_erika_set_activation(TaskType tid, AlarmType aid, 
				     uint32_t offset,
				     uint32_t period) 
{
	if (offset == 0 && period == 0)
		ActivateTask(tid);
	else
		SetRelAlarm(aid, offset, period);
	return 1;
}

COMPILER_INLINE 
int8_t ozb_kal_erika_cancel_activation(AlarmType aid) 
{
	CancelAlarm(aid);
	return 1;
}

 
COMPILER_INLINE 
int8_t ozb_kal_erika_mutex_wait(ResourceType res) 
{
	GetResource(res);
	return 1;
}

COMPILER_INLINE 
int8_t ozb_kal_erika_mutex_signal(ResourceType res) 
{
	ReleaseResource(res);
	return 1;
}

#define OZB_KAL_TASK_ASYNC(task_id, priority)			\
static void (*OZB_EE_TBODY_##task_id)(void) = 0;		\
TASK(OZB_EE_TASK_##task_id)					\
{ 								\
	if (OZB_EE_TBODY_##task_id != 0)			\
		OZB_EE_TBODY_##task_id();			\
}

#define OZB_KAL_TASK(task_id, priority)				\
static void (*OZB_EE_TBODY_##task_id)(void) = 0;		\
TASK(OZB_EE_TASK_##task_id)					\
{ 								\
	if (OZB_EE_TBODY_##task_id != 0)			\
		OZB_EE_TBODY_##task_id();			\
}

#define OZB_KAL_MUTEX(mutex_id, task_id)			\

#define ozb_kal_init(tick_duration) 				\
ozb_kal_erika_init(tick_duration)				\

#define ozb_kal_set_body(task_id, task_body) 		 	\
ozb_kal_erika_set_body(task_body, &(OZB_EE_TBODY_##task_id))	\


#define ozb_kal_set_activation(task_id, offset, period)		\
ozb_kal_erika_set_activation(OZB_EE_TASK_##task_id, 		\
			      OZB_EE_ALARM_##task_id,		\
			      offset, period)			\

#define ozb_kal_activate(task_id)				\
ActivateTask(OZB_EE_TASK_##task_id)				\

#define ozb_kal_cancel_activation(task_id)			\
ozb_kal_erika_cancel_activation(OZB_EE_ALARM_##task_id)		\


#define ozb_kal_mutex_wait(mutex_id)				\
ozb_kal_erika_mutex_wait(OZB_EE_RESOURCE_##mutex_id)		\


#define ozb_kal_mutex_signal(mutex_id)				\
ozb_kal_erika_mutex_signal(OZB_EE_RESOURCE_##mutex_id)		\


#endif /* Header Protection */
