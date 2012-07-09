/*
 * Author: Gianluca Franchino 2011
 */
#ifndef __BM_ERIKA_CONFIG_H__
#define __BM_ERIKA_CONFIG_H__

#include "ee.h"
//#include "ee_internal.h"
//#include "cpu/common/inc/ee_irqstub.h"

#ifndef __TIMING_TEST_H__
#include "cpu/cortex_mx/inc/ee_irq.h"
#endif

#include "cpu/common/inc/ee_stdint.h"

#define activate_task(task) ActivateTask(task)

#ifdef __FP__
#define terminate_task()	((void)0)
#else
#define terminate_task() TerminateTask()
#endif	

#ifndef ANALISYS_RES_DIM
#define ANALISYS_RES_DIM 9 
#endif

#ifndef TIMINGTEST_NUM_RECORDS
#define TIMINGTEST_NUM_RECORDS 50
#endif


#ifndef BM_MAX_LOOPS
#define BM_MAX_LOOPS  TIMINGTEST_NUM_RECORDS
#endif


static volatile unsigned int bm_loops = 0;
#ifdef __FP__
volatile EE_UINT8 bm_end = 0;
#endif

NORETURN __INLINE__ void bm_rtos_init(void)
{

	/*Initialize some Erika stuffs*/
	EE_system_init();
	
#ifdef __FP__
	activate_task(BM_task);
#else
	/*
	 * Note: StartOs will active BM_task if we
	 * set AUTOSTART=TRUE in the oil file.
	 */
	StartOS(OSDEFAULTAPPMODE);
#endif

#ifdef __FP__  
	for (;;) {  
	/* Background activities, if any, go here... */
		if (bm_loops == BM_MAX_LOOPS)
			bm_end = 1;
	}
#endif	
}


#endif /*__BM_ERIKA_CONFIG_H__*/

