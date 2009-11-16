#include "ee.h"

/***************************************************************************
 *
 * Kernel ( CPU 0 )
 *
 **************************************************************************/
//    /* Definition of task's body */
    DeclareTask(TASK_SEND);
    DeclareTask(TASK_RECEIVE);

    const EE_ADDR EE_hal_thread_body[EE_MAX_TASK] = {
        (EE_ADDR)FuncTASK_SEND,		 	/* thread TASK_SEND */
        (EE_ADDR)FuncTASK_RECEIVE		/* thread TASK_RECEIVE */
    };

//    /* ready priority */
    const EE_TYPEPRIO EE_th_ready_prio[EE_MAX_TASK] = {
        0x1,		/* thread TASK_SEND */
        0X2			/* thread TASK_RECEIVE */
    };

//    /* dispatch priority */
    const EE_TYPEPRIO EE_th_dispatch_prio[EE_MAX_TASK] = {
        0x1,		/* thread TASK_SEND */
        0X2			/* thread TASK_RECEIVE */
    };

//    /* thread status */
    #if defined(__MULTI__) || defined(__WITH_STATUS__)
        EE_TYPESTATUS EE_th_status[EE_MAX_TASK] = {
            EE_READY,
            EE_READY
        };
    #endif

//    /* next thread */
    EE_TID EE_th_next[EE_MAX_TASK] = {
        EE_NIL,
        EE_NIL
    };

    EE_TYPEPRIO EE_th_nact[EE_MAX_TASK];
//    /* The first stacked task */
    EE_TID EE_stkfirst = EE_NIL;

//    /* The first task into the ready queue */
    EE_TID EE_rqfirst  = EE_NIL;

//    /* system ceiling */
    EE_TYPEPRIO EE_sys_ceiling= 0x0000;



/***************************************************************************
 *
 * Mutex
 *
 **************************************************************************/
    const EE_TYPEPRIO EE_resource_ceiling[EE_MAX_RESOURCE]= {
        0x2 		 /* resource RES_SCHEDULER */
    };

    EE_TYPEPRIO EE_resource_oldceiling[EE_MAX_RESOURCE];



/***************************************************************************
 *
 * Counters
 *
 **************************************************************************/
    EE_counter_RAM_type       EE_counter_RAM[EE_MAX_COUNTER] = {
        {0, -1}        /*DUMMY_COUNTER*/
    };



/***************************************************************************
 *
 * Alarms
 *
 **************************************************************************/
    const EE_alarm_ROM_type   EE_alarm_ROM[] = {
        {0, EE_ALARM_ACTION_TASK    , TASK_SEND, NULL}
    };

    EE_alarm_RAM_type         EE_alarm_RAM[EE_MAX_ALARM];

