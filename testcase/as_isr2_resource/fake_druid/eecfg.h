#ifndef __EECFG_H__
#define __EECFG_H__


#define RTDRUID_CONFIGURATOR_NUMBER 1276



/***************************************************************************
 *
 * Common defines ( CPU 0 )
 *
 **************************************************************************/

    /* TASK definition */
    #define EE_MAX_TASK 1
    #define Task1 0

    /* MUTEX definition */
    #define EE_MAX_RESOURCE 3U
    #define Resource1 0U
    #define ResourceA 1U
    #define ResourceB 2U

    /* ALARM definition */
    #define EE_MAX_ALARM 0

    /* COUNTER definition */
    #define EE_MAX_COUNTER 0

    /* APPMODE definition */
    #define EE_MAX_APPMODE 0U

    /* CPUs */
    #define EE_MAX_CPU 1
    #define EE_CURRENTCPU 0

    /* ISR2 */
    #define EE_MAX_ISR2_WITH_RESOURCES 2
    #define EE_ISR2_MAX_LEVEL 0x3U

#ifndef __DISABLE_EEOPT_DEFINES__


/***************************************************************************
 *
 * User options
 *
 **************************************************************************/
#define __ASSERT__
#define __E200ZX_EXECUTE_FROM_RAM__


/***************************************************************************
 *
 * Automatic options
 *
 **************************************************************************/
#define __RTD_LINUX__
#define __PPCE200ZX__
#define __MPC5674F__
#define __PPCE200Z7__
#define __DIAB__
#define __OO_ECC1__
#define __OO_HAS_ERRORHOOK__
#define __MULTI__
#define __OO_NO_ALARMS__
#define __OO_NO_EVENTS__
#define __ALLOW_NESTED_IRQ__
#define __OO_ISR2_RESOURCES__
#define __OO_STARTOS_OLD__

#define EE_ISR_DYNAMIC_TABLE

#endif

    /* System stack size */
    #define EE_SYS_STACK_SIZE     2048

#endif

