
#include "ee.h"

/***************************************************************************
 *
 * Stack definition for PIC 30
 *
 **************************************************************************/
    #define STACK_1_SIZE 128 // size = 256 bytes 
    #define STACK_2_SIZE 128 // size = 256 bytes 
    #define STACK_3_SIZE 128 // size = 256 bytes 

    int EE_s12xs_stack_1[STACK_1_SIZE];	/* Task 0 (Task1) */
    int EE_s12xs_stack_2[STACK_2_SIZE];	/* Task 1 (Task2) */
    int EE_s12xs_stack_3[STACK_3_SIZE];	/* irq stack */

    EE_UREG EE_s12xs_thread_tos[EE_MAX_TASK+1] = {
        0,	 /* dummy*/
        1,	 /* Task1*/
        2 	 /* Task2*/
    };

    struct EE_TOS EE_s12xs_system_tos[3] = {
        {0},	/* Task   (dummy) */
        {(EE_DADD)(&EE_s12xs_stack_1[STACK_1_SIZE-1])},	/* Task 0 (Task1) */
        {(EE_DADD)(&EE_s12xs_stack_2[STACK_2_SIZE-1])} 	/* Task 1 (Task2) */
    };

    EE_UREG EE_s12xs_active_tos = 0; /* dummy */

    /* stack used only by IRQ handlers */
    struct EE_TOS EE_s12xs_IRQ_tos = {
        (EE_DADD)(&EE_s12xs_stack_3[STACK_3_SIZE-1])
    };

    //extern int _SPLIM_init;
//    const struct EE_TOS EE_s12xs_system_splim[3] = {
//        {(EE_ADDR)(EE_UREG)&_SPLIM_init},
//        {(EE_ADDR)(&EE_s12xs_stack_1[STACK_1_SIZE - 4])},
//        {(EE_ADDR)(&EE_s12xs_stack_2[STACK_2_SIZE - 4])}
//    };
//    const struct EE_TOS EE_s12xs_IRQ_splim = {
//        (EE_ADDR)(&EE_s12xs_stack_3[STACK_3_SIZE - 4])
//    };
#include "ee.h"


/***************************************************************************
 *
 * Kernel ( CPU 0 )
 *
 **************************************************************************/
    /* Definition of task's body */
    DeclareTask(Task1);
    DeclareTask(Task2);

    const EE_ADDR EE_hal_thread_body[EE_MAX_TASK] = {
        (EE_ADDR)EE_oo_thread_stub,		 /* thread Task1 */
        (EE_ADDR)EE_oo_thread_stub 		 /* thread Task2 */

    };

    EE_UINT16 EE_terminate_data[EE_MAX_TASK];

    /* ip of each thread body (ROM) */
    const EE_ADDR EE_terminate_real_th_body[EE_MAX_TASK] = {
        (EE_ADDR)FuncTask1,
        (EE_ADDR)FuncTask2
    };
    /* ready priority */
    const EE_TYPEPRIO EE_th_ready_prio[EE_MAX_TASK] = {
        0x1,		 /* thread Task1 */
        0x2 		 /* thread Task2 */
    };

    const EE_TYPEPRIO EE_th_dispatch_prio[EE_MAX_TASK] = {
        0x1,		 /* thread Task1 */
        0x2 		 /* thread Task2 */
    };

    /* thread status */
    EE_TYPESTATUS EE_th_status[EE_MAX_TASK] = {
        SUSPENDED,
        SUSPENDED
    };

    /* next thread */
    EE_TID EE_th_next[EE_MAX_TASK] = {
        EE_NIL,
        EE_NIL
    };

    /* The first stacked task */
    EE_TID EE_stkfirst = EE_NIL;

    /* system ceiling */
    EE_TYPEPRIO EE_sys_ceiling= 0x0000;

    /* remaining nact: init= maximum pending activations of a Task */
    /* MUST BE 1 for BCC1 and ECC1 */
    EE_TYPENACT   EE_th_rnact[EE_MAX_TASK] =
        { 1, 1};

    /* First task in the ready queue (initvalue = EE_NIL) */
    EE_TID EE_rq_first  = EE_NIL;

    #ifndef __OO_NO_CHAINTASK__
        /* The next task to be activated after a ChainTask. initvalue=all EE_NIL */
        EE_TID EE_th_terminate_nextask[EE_MAX_TASK] = {
            EE_NIL,
            EE_NIL
        };
    #endif



/***************************************************************************
 *
 * Event handling
 *
 **************************************************************************/
    EE_TYPEEVENTMASK EE_th_event_active[EE_MAX_TASK] =
        { 0, 0};    /* thread event already active */

    EE_TYPEEVENTMASK EE_th_event_waitmask[EE_MAX_TASK] =
        { 0, 0};    /* thread wait mask */

    EE_TYPEBOOL EE_th_waswaiting[EE_MAX_TASK] =
        { 0, 0};

    EE_TYPEPRIO EE_th_is_extended[EE_MAX_TASK] =
        { 0, 0};



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
   // const EE_oo_counter_ROM_type EE_counter_ROM[] = {
//     };
//
//    EE_oo_counter_RAM_type       EE_counter_RAM[EE_MAX_COUNTER] = {
//    };


/***************************************************************************
 *
 * Alarms
 *
 **************************************************************************/
    //const EE_oo_alarm_ROM_type   EE_alarm_ROM[] = {
//
//    };
//
//    EE_oo_alarm_RAM_type         EE_alarm_RAM[EE_MAX_ALARM];



/***************************************************************************
 *
 * AppMode
 *
 **************************************************************************/
    EE_TYPEAPPMODE EE_ApplicationMode;


/***************************************************************************
 *
 * Auto Start (TASK)
 *
 **************************************************************************/
    static const EE_TID EE_oo_autostart_task_mode_OSDEFAULTAPPMODE[1] = 
        { Task2 };

    const struct EE_oo_autostart_task_type EE_oo_autostart_task_data[EE_MAX_APPMODE] = {
        { 1, EE_oo_autostart_task_mode_OSDEFAULTAPPMODE}
    };
