/*
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation, 
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 */

/*
 * Author: 2011 Errico Guidieri
 * CVS: $Id: dspic_main.c,v 1.10 2008/06/19 08:58:09 francesco Exp $
 */

#define XNAME(x,y)  x##y
#define NAME(x,y)   XNAME(x,y)

#include "ee.h"
#include "mcu/microchip_dspic/inc/ee_utils.h"
#include "mcu/microchip_dspic/inc/ee_timer.h"

/* Oscillator selectione register set on internal Fast RC oscillator. */
_FOSCSEL(FNOSC_FRC);
/* Oscillator configuration register set with clock switch enabled & clock monitoring disabled (FCKSM_CSECMD),
 * OSC2 pin as GPIO (OSCIOFNC_ON) and
 * primary oscillator disabled (not external oscillator/clock source in the board) */
_FOSC(FCKSM_CSECMD & OSCIOFNC_ON & POSCMD_NONE);
/* Watchdog Timer disabled */
_FWDT(FWDTEN_OFF);
/* Disable Code Protection */
_FGS(GCP_OFF);

/* simple time */
static double scicos_time;
static int dspic_time;
static double t;
static double actTime;

extern int NAME(MODELNAME,_init)(void);
extern double NAME(MODELNAME,_get_tsamp)(void);
extern int NAME(MODELNAME,_isr)(double);
extern int NAME(MODELNAME,_end)(void);

double get_scicos_time()
{
    return(actTime);
}


static void timer1_callback(void){
    CounterTick(sciCounter);
}

TASK(rt_sci)
{
    actTime = t;
    NAME(MODELNAME,_isr)(actTime);
    t += scicos_time;
}

int main(void)
{
    /* Set the system clock frequency to 80 Mhz (means microcontroller instructions frequency 40 MIPS) */
    EE_set_system_clock(80000000UL);
    
    /* Set timer1 callback to increment counter */
    EE_timer_set_callback(EE_TIMER_1, timer1_callback);
    /* reset the counter */
    EE_timer_soft_init(EE_TIMER_1, 1000U);
    EE_timer_start(EE_TIMER_1);

    NAME(MODELNAME,_init)(); 
    
    /* simulation time */
    t  = 0.0;

    scicos_time = NAME(MODELNAME,_get_tsamp)();
    dspic_time = (int) (1000 * scicos_time);
    
    SetRelAlarm(AlarmSci, dspic_time, dspic_time);

    /* Forever loop: background activities (if any) should go here */
    for (;;);
    
    return 0;
}
