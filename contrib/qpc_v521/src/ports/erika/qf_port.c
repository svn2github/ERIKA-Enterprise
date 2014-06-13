/*****************************************************************************
* Product:  QF/C port to POSIX/P-threads, GNU
* Last Updated for Version: 5.2.1
* Date of the Last Update:  Jan 06, 2014
*
*                    Q u a n t u m     L e a P s
*                    ---------------------------
*                    innovating embedded systems
*
* Copyright (C) 2002-2014 Quantum Leaps, LLC. All rights reserved.
*
* This program is open source software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Alternatively, this program may be distributed and modified under the
* terms of Quantum Leaps commercial licenses, which expressly supersede
* the GNU General Public License and are specifically designed for
* licensees interested in retaining the proprietary status of their code.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
* Contact information:
* Quantum Leaps Web sites: http://www.quantum-leaps.com
*                          http://www.state-machine.com
* e-mail:                  info@quantum-leaps.com
*****************************************************************************/
#include "qf_pkg.h"
#include "qassert.h"

#include "eecfg.h"

Q_DEFINE_THIS_MODULE("qf_port")

/* Global objects ----------------------------------------------------------*/

QActive *pdata[QF_MAX_ACTIVE];

static TaskType NextTaskID = 0;


/*..........................................................................*/
void QF_init(void) {
	/* Nothing to do. Erika does not require special initialization steps. */
}
/*..........................................................................*/
int_t QF_run(void) {

	QF_onStartup();
	
	StartOS(OSDEFAULTAPPMODE);
	
	Q_ERROR();            /* The Erika kernel should never returns to the caller 
    						from StartOS(). */
    
    return (int_t)0;      /* return success */
}

/*..........................................................................*/
void QF_stop(void) {
	/* stop the loop in QF_run() */
}
/*..........................................................................*/
void task_function(void *pdata) { /* routine called by each task. */
  
	while (((QActive *)pdata)->thread != (uint8_t)0) {
        QEvt const *e = QActive_get_((QActive *)pdata);
        QMSM_DISPATCH((QMsm *)pdata, e);         /* dispatch to the AO's SM */
        QF_gc(e);    /* check if the event is garbage, and collect it if so */
    }

    QF_remove_((QActive *)pdata);  /* remove this object from the framework */
    
    TerminateTask();        /* Terminate Erika task */
}
/*..........................................................................*/
void QActive_start_(QActive *me, uint_t prio,
                    QEvt const *qSto[], uint_t qLen,
                    void *stkSto, uint_t stkSize,
                    QEvt const *ie)
{

    Q_REQUIRE(stkSto == (void *)0);  /* Erika tasks allocate stack internally */

    QEQueue_init(&me->eQueue, qSto, qLen);
   
    me->prio = (uint8_t)prio;
    QF_add_(me);                     /* make QF aware of this active object */
    QMSM_INIT(&me->super, ie);            /* execute the initial transition */
    QS_FLUSH(); /* flush the trace buffer to the host */
    
	me->osObject = QFEvent;
 
	/*
	 * Object priority must by lower than the maximum value allowed by Erika RTOS.
	 * Note: the maximum priority number depends on the CPU register size.
	 */
	if (me->prio > sizeof(EE_TYPEPRIO)* 8)
		Q_ERROR();
	/* 
	 * Priority of AO must match the priority of next available task. 
     */	
    if ((0x1 << (me->prio -1)) & EE_th_ready_prio[NextTaskID]) {
    	
    	me->thread = NextTaskID + 1;
    	
    	pdata[NextTaskID++] = me;
    	
    } else {

    	Q_ERROR();
    }
    
    
   
}

/*..........................................................................*/
void QActive_stop(QActive *me) {
    me->thread = (uint8_t)0;                /* stop the QActive thread loop */
}


