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


#ifndef __INCLUDE_EE_MINIFLEX_BOARD_H__
#define __INCLUDE_EE_MINIFLEX_BOARD_H__

#include "mcu/microchip_dspic/inc/ee_mcu.h"

/* /\************************************************************************* */
/*  Sys_Clock */
/*  *************************************************************************\/ */

#ifndef	EE_SYS_CLOCK
#define	EE_SYS_CLOCK	16000000ul
#endif

/* /\************************************************************************* */
/*  LEDs */
/*  *************************************************************************\/ */

#ifdef __USE_LEDS__

__INLINE__ void __ALWAYS_INLINE__ EE_leds_init(void) {
	/* set LED (LEDSYS/RA10) drive state low */
	LATAbits.LATA10 = 0;
	/* set LED pin (LEDSYS/RA10) as output */
	TRISAbits.TRISA10 = 0;
}

__INLINE__ void __ALWAYS_INLINE__ EE_led_sys_on(void)	{ LATAbits.LATA10  = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_sys_off(void)	{ LATAbits.LATA10  = 0; }

__INLINE__ void __ALWAYS_INLINE__ EE_led_on(void)		{ LATAbits.LATA10  = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_off(void)		{ LATAbits.LATA10  = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_toggle(void)	{ LATAbits.LATA10 += 1; }

#endif


/* /\************************************************************************* */
/*  Analog inputs */
/*  *************************************************************************\/ */

#if defined(__USE_ANALOG_IN__)

#define AVDD 3.3

extern EE_UINT8 EE_adc_init;

__INLINE__ void __ALWAYS_INLINE__ EE_analog_init( void )
{
	/* Check if the ADC is initialized */
	if (EE_adc_init != 0) return;

	/* turn off ADC module */
	AD1CON1bits.ADON = 0;

	/* Set control register 1 */
	/* 12-bit, unsigned integer format, autosampling */
	AD1CON1 = 0x04E0;

	/* Set control register 2 */
	/* Vref = AVcc/AVdd, Scan Inputs */
	AD1CON2 = 0x0000;

	/* Set Samples and bit conversion time */
	/* AS = 31 Tad, Tad = 64 Tcy = 1.6us  */
	AD1CON3 = 0x1F3F; //** Last PATCH xxx

	/* disable channel scanning here */
	AD1CSSL = 0x0000;

	/* reset ADC interrupt flag */
	IFS0bits.AD1IF = 0;

	/* disable ADC interrupts */
	IEC0bits.AD1IE = 0;

	/* turn on ADC module */
	//AD1CON1bits.ADON = 1;

	/* set ADC as configured */
	EE_adc_init = 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_analog_stop( void )
{
	/* enable external voltage reference */
	
	/* set 3V3M drive state high */
	LATAbits.LATA1 = 1;
	/* set 3V3M pin as output */
	TRISAbits.TRISA1 = 0;
	
	/* turn off ADC module */
	AD1CON1bits.ADON = 0;
}

__INLINE__ void __ALWAYS_INLINE__ EE_analog_start( void )
{
	/* turn on ADC module */
	AD1CON1bits.ADON = 1;

	/* set 3V3M drive state low */
	LATAbits.LATA1 = 0;
}
#endif

/* ************************************************************************* */

/* Battery Monitor Input */
#ifdef __USE_BATTERY_MONITOR__

// TODO!!! - Tune!
#define VREF 3.3 // Battery Voltage acquired as 0x03FF

__INLINE__ void __ALWAYS_INLINE__ EE_battery_monitor_init( void )
{
	/* set configuration bit as ADC input */
 	AD1PCFGbits.PCFG4 = 0; // Battery Monitor -> AN4/RB2

	/* Configure ADC */
	EE_analog_init();

	/* turn on ADC module */
	EE_analog_start();
}

__INLINE__ float __ALWAYS_INLINE__ EE_battery_monitor_get( void )
{
	float adcdata;
	
	/* Set AN4 - RB2 as input channel */
	AD1CHS = 4;

	/* Start conversion */
	AD1CON1bits.SAMP = 1;

	/* Wait till the EOC */
	while(!IFS0bits.AD1IF);

	/* reset ADC interrupt flag */
	IFS0bits.AD1IF = 0;

	/* Acquire data */
	adcdata = ADC1BUF0;

	/* Return conversion */
	return (adcdata * VREF) / 1024;
}
#endif

/* ************************************************************************* */

/* Temperature Input */
#ifdef __USE_TEMPERATURE__

// Thermal constants for the Voltage-Temperature conversion (fra)
#define THERM_A 0.0004132
#define THERM_B 0.000320135

__INLINE__ void __ALWAYS_INLINE__ EE_temperature_init( void )
{
	/* set configuration bit as ADC input */
 	AD1PCFGbits.PCFG5 = 0; // Temperature Sensor -> AN5/RB3

	/* Configure ADC */
	EE_analog_init();

	/* turn on ADC module */
	EE_analog_start();
}

__INLINE__ float __ALWAYS_INLINE__ EE_temperature_get( void )
{
	float adcdata;

	// Set AN5 - RB3 as input channel
	AD1CHS = 5;

	/* Start conversion */
	AD1CON1bits.SAMP = 1;

	/* Wait till the EOC */
	while(!IFS0bits.AD1IF);

	/* reset ADC interrupt flag */
	IFS0bits.AD1IF = 0;

	/* Acquire data */
	adcdata = ADC1BUF0;

	// Conversion (fra)
	float r_therm, T_K, T_C;

	r_therm = 1 / (1024.0/adcdata - 1.0);

	// T_K = 1.0 / (THERM_A + THERM_B * log(r_therm));
	T_K = 1.0 / (THERM_A + THERM_B * ((r_therm-1) + 9.8) );
	T_C = T_K - 273.15;

	/* Return conversion */
	return T_C;
}
#endif



/* /\************************************************************************* */
/* Check if the Flex DemoBoard has been selected */
/* /\************************************************************************* */

#ifdef __USE_DEMOBOARD__
#include "board/ee_miniflex/inc/ee_miniflex_demoboard.h"
#endif // __USE_DEMOBOARD__

/* ************************************************************************* */
#endif
