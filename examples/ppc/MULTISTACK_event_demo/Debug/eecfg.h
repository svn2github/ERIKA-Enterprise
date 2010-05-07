

//////////////////////////////////////////////////////////////////////////////
//  
//   Common defines ( CPU 0 )
//  
/////////////////////////////////////////////////////////////////////////////

    // TASK definition
    #define EE_MAX_TASK 2
    #define Task1 0
    #define Task2 1

    // MUTEX definition
    #define EE_MAX_RESOURCE 1
    #define RES_SCHEDULER 0

    // EVENT definition
    #define TimerEvent 0x1
    #define ButtonEvent 0x2

    // ALARM definition
    #define EE_MAX_ALARM 2
    #define AlarmTask1 0
    #define AlarmTask2 1

    // COUNTER definition
    #define EE_MAX_COUNTER 1
    #define Counter1 0

    // APPMODE definition
    #define EE_MAX_APPMODE 1

    // CPUs
    #define EE_MAX_CPU 1
    #define EE_CURRENTCPU 0

