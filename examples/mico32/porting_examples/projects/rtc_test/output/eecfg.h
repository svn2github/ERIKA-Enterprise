

//////////////////////////////////////////////////////////////////////////////
//  
//   Common defines ( CPU 0 )
//  
/////////////////////////////////////////////////////////////////////////////

    // TASK definition
    #define EE_MAX_TASK 1
    #define Task1 0

    // MUTEX definition
    #define EE_MAX_RESOURCE 0

    // ALARM definition
    #define EE_MAX_ALARM 1
    #define task1_alarm 0

    // COUNTER definition
    #define EE_MAX_COUNTER 1
    #define system_counter 0

    // APPMODE definition
    #define EE_MAX_APPMODE 0

    // CPUs
    #define EE_MAX_CPU 1
    #define EE_CURRENTCPU 0
    
    // Druid
    #define EE_UART1_NAME_UC UART
	#define EE_UART1_NAME_LC uart
	#define EE_I2C1_NAME_UC I2C
	#define EE_I2C1_NAME_LC i2c
	#define EE_TIMER1_NAME_UC SYSTEM_TIMER
	#define EE_TIMER1_NAME_LC system_timer
	#define EE_TIMER2_NAME_UC TIMER
	#define EE_TIMER2_NAME_LC timer
