#include "ee.h"


//////////////////////////////////////////////////////////////////////////////
//  
//   Kernel ( CPU 0 )
//  
/////////////////////////////////////////////////////////////////////////////
    // Definition of task's body
    DeclareTask(Task1);
    DeclareTask(Task2);

    const EE_FADDR EE_hal_thread_body[EE_MAX_TASK] = {
        (EE_FADDR)EE_oo_thread_stub,		 // thread Task1
        (EE_FADDR)EE_oo_thread_stub 		 // thread Task2

    };

    EE_UINT32 EE_terminate_data[EE_MAX_TASK];

    // ip of each thread body (ROM)
    const EE_FADDR EE_terminate_real_th_body[EE_MAX_TASK] = {
        (EE_FADDR)FuncTask1,
        (EE_FADDR)FuncTask2
    };
    // ready priority
    const EE_TYPEPRIO EE_th_ready_prio[EE_MAX_TASK] = {
        0x1,		 // thread Task1
        0x2 		 // thread Task2
    };

    const EE_TYPEPRIO EE_th_dispatch_prio[EE_MAX_TASK] = {
        0x1,		 // thread Task1
        0x2 		 // thread Task2
    };

    // thread status
    EE_TYPESTATUS EE_th_status[EE_MAX_TASK] = {
        SUSPENDED,
        SUSPENDED
    };

    // next thread
    EE_TID EE_th_next[EE_MAX_TASK] = {
        EE_NIL,
        EE_NIL
    };

    // The first stacked task
    EE_TID EE_stkfirst = EE_NIL;

    // system ceiling
    EE_TYPEPRIO EE_sys_ceiling= 0x0000;

    // The priority queues: (16 priorities maximum!)
    EE_TYPEPAIR EE_rq_queues_head[16] =
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    EE_TYPEPAIR EE_rq_queues_tail[16] =
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

    EE_UINT16 EE_rq_bitmask = 0;

    // remaining nact: init= maximum pending activations of a Task
    EE_TYPEPRIO EE_th_rnact[EE_MAX_TASK] = {
        1,		 // thread Task1
        1		 // thread Task2
    };

    EE_TYPEPRIO EE_rq_link[EE_MAX_TASK] =
        { 0, 1};

    // The pairs that are enqueued into the priority queues (2 is the total number of task activations)
    EE_TYPEPAIR EE_rq_pairs_next[] =
        { 1, -1};

    // no need to be initialized
    EE_TID EE_rq_pairs_tid[2];

    // a list of unused pairs
    EE_TYPEPAIR EE_rq_free = 0; // pointer to a free pair

    #ifndef __OO_NO_CHAINTASK__
        // The next task to be activated after a ChainTask. initvalue=all EE_NIL
        EE_TID EE_th_terminate_nextask[EE_MAX_TASK] = {
            EE_NIL,
            EE_NIL
        };
    #endif



//////////////////////////////////////////////////////////////////////////////
//  
//   Event handling
//  
/////////////////////////////////////////////////////////////////////////////
    EE_TYPEEVENTMASK EE_th_event_active[EE_MAX_TASK] =
        { 0, 0};    // thread event already active

    EE_TYPEEVENTMASK EE_th_event_waitmask[EE_MAX_TASK] =
        { 0, 0};    // thread wait mask

    EE_TYPEBOOL EE_th_waswaiting[EE_MAX_TASK] =
        { 0, 0};

    EE_TYPEPRIO EE_th_is_extended[EE_MAX_TASK] =
        { 1, 0};



//////////////////////////////////////////////////////////////////////////////
//  
//   Mutex
//  
/////////////////////////////////////////////////////////////////////////////
    // This is the last mutex that the task has locked. This array
    //    contains one entry for each task. Initvalue= all -1. at runtime,
    //    it points to the first item in the EE_resource_stack data structure.
    EE_UREG EE_th_resource_last[EE_MAX_TASK] =
        { (EE_UREG) -1, (EE_UREG) -1};

    // This array is used to store a list of resources locked by a
    //    task. there is one entry for each resource, initvalue = -1. the
    //    list of resources locked by a task is ended by -1.
    EE_UREG EE_resource_stack[EE_MAX_RESOURCE] =
        { (EE_UREG) -1};

    // Only in extended status or when using ORTI with resources; for
    //    each resource, a flag is allocated to see if the resource is locked or
    //    not.  Note that this information cannot be easily knew from the previous
    //    two data structures. initvalue=0
    EE_TYPEBOOL EE_resource_locked[EE_MAX_RESOURCE] =
        { 0};

    const EE_TYPEPRIO EE_resource_ceiling[EE_MAX_RESOURCE]= {
        0x2 		// resource RES_SCHEDULER
    };

    EE_TYPEPRIO EE_resource_oldceiling[EE_MAX_RESOURCE];



//////////////////////////////////////////////////////////////////////////////
//  
//   Counters
//  
/////////////////////////////////////////////////////////////////////////////
    const EE_oo_counter_ROM_type EE_counter_ROM[] = {
        {0xFFFF, 1, 2}         // Counter1
    };

    EE_oo_counter_RAM_type       EE_counter_RAM[EE_MAX_COUNTER] = {
        {0, -1}
    };


//////////////////////////////////////////////////////////////////////////////
//  
//   Alarms
//  
/////////////////////////////////////////////////////////////////////////////
    const EE_oo_alarm_ROM_type   EE_alarm_ROM[] = {
        {0, EE_ALARM_ACTION_EVENT   , Task1, TimerEvent, (EE_ADDR)NULL},
        {0, EE_ALARM_ACTION_TASK    , Task2, 0, (EE_ADDR)NULL}
    };

    EE_oo_alarm_RAM_type         EE_alarm_RAM[EE_MAX_ALARM];



//////////////////////////////////////////////////////////////////////////////
//  
//   AppMode
//  
/////////////////////////////////////////////////////////////////////////////
    EE_TYPEAPPMODE EE_ApplicationMode;


//////////////////////////////////////////////////////////////////////////////
//  
//   Auto Start (TASK)
//  
/////////////////////////////////////////////////////////////////////////////
    static const EE_TID EE_oo_autostart_task_mode_OSDEFAULTAPPMODE[1] = 
        { Task1 };

    const struct EE_oo_autostart_task_type EE_oo_autostart_task_data[EE_MAX_APPMODE] = {
        { 1, EE_oo_autostart_task_mode_OSDEFAULTAPPMODE}
    };


//////////////////////////////////////////////////////////////////////////////
//  
//   Auto Start (ALARM)
//  
/////////////////////////////////////////////////////////////////////////////
    static const EE_TYPEALARM EE_oo_autostart_alarm_mode_OSDEFAULTAPPMODE[1] =
        { AlarmTask1 };

    const struct EE_oo_autostart_alarm_type EE_oo_autostart_alarm_data[EE_MAX_APPMODE] = {
        { 1, EE_oo_autostart_alarm_mode_OSDEFAULTAPPMODE}
    };


//////////////////////////////////////////////////////////////////////////////
//  
//   Init alarms parameters (ALARM)
//  
/////////////////////////////////////////////////////////////////////////////

    const EE_TYPETICK EE_oo_autostart_alarm_increment[EE_MAX_ALARM] =
        {250, 1000 };

    const EE_TYPETICK EE_oo_autostart_alarm_cycle[EE_MAX_ALARM] =
        {500, 0 };


#include "ee.h"


//////////////////////////////////////////////////////////////////////////////
//  
//   Stack definition for Freescale MPC5674F, PPC E200Z7
//  
/////////////////////////////////////////////////////////////////////////////
    #define STACK_1_SIZE 256 // size = 1024 bytes 
    #define STACK_2_SIZE 128 // size = 512 bytes 

    int EE_e200z7_stack_1[STACK_1_SIZE];	/* Task 0 (Task1) */
    int EE_e200z7_stack_2[STACK_2_SIZE];	/* irq stack */
    const EE_UREG EE_std_thread_tos[EE_MAX_TASK+1] = {
        0,	 /* dummy*/
        1,	 /* Task1*/
        0 	 /* Task2*/
    };

    struct EE_TOS EE_e200z7_system_tos[2] = {
        {0},	/* Task   (dummy), Task 1 (Task2) */
        {(EE_ADDR)(&EE_e200z7_stack_1[STACK_1_SIZE -1])} 	/* Task 0 (Task1) */
    };

    EE_UREG EE_e200z7_active_tos = 0; /* dummy */

    /* stack used only by IRQ handlers */
    struct EE_TOS EE_e200z7_IRQ_tos = {
        (EE_ADDR)(&EE_e200z7_stack_2[STACK_2_SIZE - 1])
    };

