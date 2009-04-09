#ifndef __ozb_osal_erika_h__
#define __ozb_osal_erika_h__

#include <ee.h>


HAL_INLINE int8_t ozb_osal_erika_set_body(void(*src)(void), void(**dst)(void)) 
{
	*dst = src;
	return 1;
}

HAL_INLINE int8_t ozb_osal_erika_set_activation(TaskType tid, AlarmType aid, 
						uint16_t offset,
						uint16_t period) 
{
	if (offset == 0 && period == 0)
		ActivateTask(tid);
	else
		SetRelAlarm(aid, offset, period);
	return 1;
}

HAL_INLINE int8_t ozb_osal_erika_cancel_activation(AlarmType aid) 
{
	CancelAlarm(aid);
	return 1;
}

HAL_INLINE int8_t ozb_osal_init(void) 
{
	return 1;
}

#define OZB_OSAL_TASK(task_id, priority)			\
static void (*OZB_EE_TBODY_##task_id)(void) = 0;		\
TASK(OZB_EE_TASK_##task_id)					\
{ 								\
	if (OZB_EE_TBODY_##task_id != 0)			\
		OZB_EE_TBODY_##task_id();			\
}


#define ozb_osal_set_body(task_id, task_body) 		 	\
ozb_osal_erika_set_body(task_body, &(OZB_EE_TBODY_##task_id))	\


#define ozb_osal_set_activation(task_id, offset, period)	\
ozb_osal_erika_set_activation(OZB_EE_TASK_##task_id, 		\
			      OZB_EE_ALARM_##task_id,		\
			      offset, period)			\


#define ozb_osal_cancel_activation(task_id)			\
ozb_osal_erika_cancel_activation(OZB_EE_ALARM_##task_id)	\

#endif /* Header Protection */
