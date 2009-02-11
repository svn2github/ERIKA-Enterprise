/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
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
 * ###*E*### */

/*
 * Author: 2001-2002 Alessandro Colantonio, 2002- Paolo Gai
 * CVS: $Id: ee_board.h,v 1.4 2006/04/08 21:07:19 pj Exp $
 */

#ifndef __INCLUDE_UNIBO_MPARM_BOARD_H__
#define __INCLUDE_UNIBO_MPARM_BOARD_H__

#include "mcu/unibo_mparm/inc/ee_mcu.h"


// TODO: Change According to MPARM!!!

/*************************************************************************
 Button
 *************************************************************************/

/* the button is connected to EXT0 */

#ifdef __BUTTON_USED__

/* Initialize the EXT0 interrupt source (button)  */
__INLINE__ void __ALWAYS_INLINE__ EE_button_init(void)
{
    *IOPCON |= IO_ENABLE_EXT0;
    *IOPCON |= IO_ACTIVE_HIGH_EXT0;
    *IOPCON |= IO_RISING_EDGE_EXT0;
}

#endif


/*************************************************************************
 LEDs
 *************************************************************************/

#ifdef __LEDS_USED__

/* On Evaluator7T, the LEDs are connected through IO Port 
 * LED1 is Green, LED2 is Red, LED3 is Yellow, LED4 is Green */

__INLINE__ void __ALWAYS_INLINE__ EE_led_4_on(void) {*IOPDATA |= 16;}
__INLINE__ void __ALWAYS_INLINE__ EE_led_3_on(void) {*IOPDATA |= 32;}
__INLINE__ void __ALWAYS_INLINE__ EE_led_2_on(void) {*IOPDATA |= 64;}
__INLINE__ void __ALWAYS_INLINE__ EE_led_1_on(void) {*IOPDATA |= 128;}

__INLINE__ void __ALWAYS_INLINE__ EE_led_4_off(void) {*IOPDATA &= ~16;}
__INLINE__ void __ALWAYS_INLINE__ EE_led_3_off(void) {*IOPDATA &= ~32;}
__INLINE__ void __ALWAYS_INLINE__ EE_led_2_off(void) {*IOPDATA &= ~64;}
__INLINE__ void __ALWAYS_INLINE__ EE_led_1_off(void) {*IOPDATA &= ~128;}

__INLINE__ void __ALWAYS_INLINE__ EE_leds_init(void) {*IOPDATA &= ~(128+64+32+16);}

#endif /* __LEDS_USED__ */

// ------------------------------------------------------------------------------------------------------------------------------------------------
/*************************************************************************
**************************************************************************
 Memory-mapped support functions
*************************************************************************
*************************************************************************/


/*************************************************************************
Print
 *************************************************************************/
/* pr - Allows printing debug info even without support from an OS */
__INLINE__ void __ALWAYS_INLINE__ EE_print(char *msg, unsigned long int value, unsigned long int mode)
{
	/* Initialize message, value */
	*(unsigned long int *)ee_pr_string_ptr = (unsigned long int)msg;
	*(unsigned long int *)ee_pr_value_ptr = value;
	/* Set mode and print */
	*(unsigned long int *)ee_pr_mode_ptr = mode;
}


/*************************************************************************
Info
 *************************************************************************/
 
/* get_proc_id - Allows getting the processor's ID (from 1 onwards) */
__INLINE__ unsigned int __ALWAYS_INLINE__ EE_get_proc_id()
{
	char *ptr = (char *)(SIMSUPPORT_BASE + GET_CPU_ID_ADDRESS);
	return (*(unsigned long int *)ptr);
}

/* get_proc_num - Allows getting the number of processors in the platform */
__INLINE__ unsigned int __ALWAYS_INLINE__ EE_get_proc_num()
{
	char *ptr = (char *)(SIMSUPPORT_BASE + GET_CPU_CNT_ADDRESS);
	return (*(unsigned long int *)ptr);
}


/*************************************************************************
Simulation Support
 *************************************************************************/

/* end_boot - Marks the end of the bootstrap stage */
__INLINE__ void __ALWAYS_INLINE__ EE_end_boot()
{
	char *ptr = (char *)(SIMSUPPORT_BASE + ENDBOOT_ADDRESS);
	*ptr = 1;
}

/* stop_simulation - Exits the simulation (when all processors will be done) */
__INLINE__ void __ALWAYS_INLINE__ EE_stop_simulation()
{
	char *ptr = (char *)(SIMSUPPORT_BASE + SHUTDOWN_ADDRESS);
	*ptr = 1;
}


/*************************************************************************
Statistics
 *************************************************************************/

/* dump_metric - Does an instant dump of simulation statistics */
__INLINE__ void __ALWAYS_INLINE__ EE_dump_metric()
{
	char *ptr = (char *)(SIMSUPPORT_BASE + DUMP_ADDRESS);
	*ptr = 1;
}

/* dump_light_metric - Does an instant light dump of simulation statistics */
__INLINE__ void __ALWAYS_INLINE__ EE_dump_light_metric()
{
	char *ptr = (char *)(SIMSUPPORT_BASE + DUMP_LIGHT_ADDRESS);
	*ptr = 1;
}

/* clear_metric - Resets simulation statistics */
__INLINE__ void __ALWAYS_INLINE__ EE_clear_metric()
{
	char *ptr = (char *)(SIMSUPPORT_BASE + CLEAR_ADDRESS);
	*ptr = 1;
}

/*************************************************************************
Environment
 *************************************************************************/

/* get_argc - Allows getting the argc command line parameter */
__INLINE__ unsigned int __ALWAYS_INLINE__ EE_get_argc()
{
	char *ptr = (char *)(SIMSUPPORT_BASE + GET_ARGC_ADDRESS);
	return (*(unsigned long int *)ptr);
}

/* get_argv - Allows getting the argv command line parameter */
__INLINE__ char __ALWAYS_INLINE__ **EE_get_argv()
{
	char **ptr = (char **)(SIMSUPPORT_BASE + GET_ARGV_ADDRESS);
	return (ptr);
}

/* get_envp - Allows getting the environment */
__INLINE__ char __ALWAYS_INLINE__ **EE_get_envp()
{
	char **ptr = (char **)(SIMSUPPORT_BASE + GET_ENVP_ADDRESS);
	return (ptr);
}

/*************************************************************************
Time Info
 *************************************************************************/

/* get_time - Allows getting the current simulation time */
__INLINE__ unsigned long long int __ALWAYS_INLINE__ EE_get_time()
{
	unsigned long long int time;
  
	*time_stop_ptr = 1;
	time = (((unsigned long long int)(*(unsigned long int *)time_high_ptr)) << 32) + *(unsigned long int *)time_low_ptr;
	*time_rel_ptr = 1;
  
	return (time);
}

/* get_cycle - Allows getting the current simulation cycle */
__INLINE__ unsigned long long int __ALWAYS_INLINE__ EE_get_cycle()
{
	unsigned long long int cycle;
  
	*cycle_stop_ptr = 1;
	cycle = (((unsigned long long int)(*(unsigned long int *)cycle_high_ptr)) << 32) + *(unsigned long int *)cycle_low_ptr;
	*cycle_rel_ptr = 1;
  
	return (cycle);
}

/*************************************************************************
Frequency scaling functions
 *************************************************************************/

/* scale_this_core_frequency - Scales the frequency of the core on which the application is running */
__INLINE__ void __ALWAYS_INLINE__ EE_scale_this_core_frequency(unsigned short int divider)
{
	freqdevice[get_proc_id() - 1] = divider;
}

/* scale_device_frequency - Scales the frequency of any device in the system */
__INLINE__ void __ALWAYS_INLINE__ EE_scale_device_frequency(unsigned short int divider, int ID)
{
	freqdevice[ID] = divider;
}

/* get_this_core_frequency - Gets the frequency divider of the core on which the application is running */
__INLINE__ unsigned short int __ALWAYS_INLINE__ EE_get_this_core_frequency()
{
	return (freqdevice[get_proc_id() - 1]);
}

/* get_device_frequency - Gets the frequency divider of any device in the system */
__INLINE__ unsigned short int __ALWAYS_INLINE__ EE_get_device_frequency(int ID)
{
	return (freqdevice[ID]);
}