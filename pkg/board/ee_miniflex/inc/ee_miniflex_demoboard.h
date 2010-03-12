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


#ifndef __INCLUDE_EE_MINIFLEX_DEMOBOARD_H__
#define __INCLUDE_EE_MINIFLEX_DEMOBOARD_H__

#ifdef __USE_DEMOBOARD__

/* /\************************************************************************* */
/*  Includes needed by PicDemZ wirelessmodule (GF) */
/*  *************************************************************************\/ */

#if defined (__USE_PICDEMZ_WITH_INT4__) || (__USE_PICDEMZ_WITH_CN20INT__)

#include "radio_spi.h"

#endif


/* /\************************************************************************* */
/*  LEDs */
/*  *************************************************************************\/ */

#ifdef __USE_LEDS__

#define EE_demoboard_leds_init() EE_daughter_leds_init()

__INLINE__ void __ALWAYS_INLINE__ EE_daughter_leds_init(void) {
	/* set LEDs drive state low */
	LATF  &= 0xFFF0;
	LATD  &= 0xF0FF;

	/* set LEDs pin as output */
	TRISF &= 0xFFF0;
	TRISD &= 0xF0FF;
}

__INLINE__ void __ALWAYS_INLINE__ EE_leds( EE_UINT8 data ) {
	LATF &= 0xFFF0;
	LATD &= 0xF0FF;

	LATF |= (data & 0x0F);
	LATD |= (data & 0xF0) << 4;
}

__INLINE__ void __ALWAYS_INLINE__ EE_led_0_on(void)   { LATFbits.LATF0  = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_0_off(void)  { LATFbits.LATF0  = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_1_on(void)   { LATFbits.LATF1  = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_1_off(void)  { LATFbits.LATF1  = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_2_on(void)   { LATFbits.LATF2  = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_2_off(void)  { LATFbits.LATF2  = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_3_on(void)   { LATFbits.LATF3  = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_3_off(void)  { LATFbits.LATF3  = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_4_on(void)   { LATDbits.LATD8  = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_4_off(void)  { LATDbits.LATD8  = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_5_on(void)   { LATDbits.LATD9  = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_5_off(void)  { LATDbits.LATD9  = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_6_on(void)   { LATDbits.LATD10 = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_6_off(void)  { LATDbits.LATD10 = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_7_on(void)   { LATDbits.LATD11 = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_7_off(void)  { LATDbits.LATD11 = 0; }

__INLINE__ void __ALWAYS_INLINE__ EE_leds_on(void)   { LATD  |= 0x0F00; LATF  |= 0x000F; }
__INLINE__ void __ALWAYS_INLINE__ EE_leds_off(void)  { LATD  &= 0xF0FF; LATF  &= 0xFFF0; }

#endif

/* /\************************************************************************* */
/*  Buttons */
/*  *************************************************************************\/ */

#ifdef __USE_BUTTONS__

extern void (*EE_button_callback)(void);

union  cn_st{
	EE_UINT8 status;
	struct a_bits
	{
		EE_UINT8 s1: 1;
		EE_UINT8 s2: 1;
		EE_UINT8 s3: 1;
		EE_UINT8 s4: 1;
	}bits;
};

extern EE_UINT8 EE_button_mask;
extern union cn_st cn_st_old;

__INLINE__ void __ALWAYS_INLINE__ EE_buttons_init( void(*isr_callback)(void), EE_UINT8 mask ) {
	/* set BUTTON pins as inputs */
	TRISDbits.TRISD4  = 1;
	TRISDbits.TRISD5  = 1;
	TRISDbits.TRISD6  = 1;
	TRISDbits.TRISD15 = 1;

	/* Enable Interrupt */
	if (isr_callback != NULL) {
		if (mask & 0x01) {
			CNEN1bits.CN13IE = 1;	// S1/RD4
			//cn_st_old.bits.s1 = PORTDbits.RD4;
		}
		if (mask & 0x02) {
			CNEN1bits.CN14IE = 1;	// S2/RD5
			//cn_st_old.bits.s2 = PORTDbits.RD5;
		}
		if (mask & 0x04) {
			CNEN1bits.CN15IE = 1;	// S3/RD6
			//cn_st_old.bits.s3 = PORTDbits.RD6;
		}
		if (mask & 0x08) {
			CNEN2bits.CN21IE = 1;	// S4/RD15
			//cn_st_old.bits.s4 = PORTDbits.RD15;
		}
		IFS1bits.CNIF = 0;
		IEC1bits.CNIE = 1;
	}

	/* Save callback */
	EE_button_callback = isr_callback;
}

__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_button_get_S1( void ) {
	if (PORTDbits.RD4)
		return 0;
	else
		return 1;
}
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_button_get_S2( void ) {
	if (PORTDbits.RD5)
		return 0;
	else
		return 1;
}
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_button_get_S3( void ) {
	if (PORTDbits.RD6)
		return 0;
	else
		return 1;
}
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_button_get_S4( void ) {
	if (PORTDbits.RD15)
		return 0;
	else
		return 1;
}

/******************************************************************************/
/*                  Common APIs for Model Based Suite                         */
/******************************************************************************/

/* TODO:
   1- Write APIs doc
   2- Do we need pre-condition check on the orther of calls? i.e. the init MUST
      be done before any call to control and read.
   3- Do we want to keep this "safe" version of the API that checking all 
      the function params? We can have a "faster" version with no check. We can
      choose at compilation time with defines.
*/
#if 0
enum {
	EE_BUTTON_MODE = 0,
	EE_BUTTON_ATTRIBUTES
};

enum {
	EE_BUTTON_RAW = 0,
	EE_BUTTON_LATCHED,
	EE_BUTTON_DEBOUNCED,
	EE_BUTTON_MODE_VALUES
};

enum {
	EE_BUTTON_ERR_UNIMPLEMENTED = 1,
	EE_BUTTON_ERR_BAD_ID,
};

__INLINE__ EE_INT8  EE_button_init(EE_UINT8 id, void(*callback)(void)) 
{
	/* TODO: provide logic for callback registration for each button */
	if (id > 4)
		return -EE_BUTTON_ERR_BAD_ID;
	if (callback != NULL)
		return -EE_BUTTON_ERR_UNIMPLEMENTED;
	EE_buttons_init(NULL, 0);
	return 1;
}

__INLINE__ EE_INT8 EE_button_control(EE_UINT8 id, EE_UINT8 attribute, 
				     EE_UINT8 value) 
{
	/* TODO: provide parsing of attributes */
	if (id > 4)
		return -EE_BUTTON_ERR_BAD_ID;
	switch (attribute) {
	case EE_BUTTON_MODE :
		if (value != EE_BUTTON_RAW)
			return -EE_BUTTON_ERR_UNIMPLEMENTED;
		break;
	default:
		return -EE_BUTTON_ERR_UNIMPLEMENTED;
	}
	return 1;
}

__INLINE__ EE_INT8 EE_button_read(EE_UINT8 id, EE_UINT8 *value) 
{
	switch (id) {
	case 0 :
		*value = EE_button_get_S1();
		break;
	case 1 :
		*value = EE_button_get_S2();
		break;
	case 2 :
		*value = EE_button_get_S3();
		break;
	case 3 :
		*value = EE_button_get_S4();
		break;
	default :
		return -EE_BUTTON_ERR_BAD_ID;
	}
	return 1;
}

enum {
	EE_LED_ERR_UNIMPLEMENTED = 1,
	EE_LED_ERR_BAD_ID,
	EE_LED_ERR_BAD_VALUE,
};

__INLINE__ EE_INT8  EE_led_init(EE_UINT8 id) 
{
	if (id > 4)
	switch (id) {
	case 0 :
		TRISFbits.TRISF0 = 0;
		break;
	case 1 :
		TRISFbits.TRISF1 = 0;
		break;
	case 2 :
		TRISFbits.TRISF2 = 0;
		break;
	case 3 :
		TRISFbits.TRISF3 = 0;
		break;
	case 4 :
		TRISDbits.TRISD8 = 0;
		break;
	case 5 :
		TRISDbits.TRISD9 = 0;
		break;
	case 6 :
		TRISDbits.TRISD10 = 0;
		break;
	case 7 :
		TRISDbits.TRISD11 = 0;
		break;
	default :
		return -EE_LED_ERR_BAD_ID;
	}
	return 1;
}

__INLINE__ EE_INT8  EE_led_write(EE_UINT8 id, EE_UINT8 value) 
{
	if (value > 1)
		return -EE_LED_ERR_BAD_VALUE;
	switch (id) {
	case 0 :
		LATFbits.LATF0 = value;
		break;
	case 1 :
		LATFbits.LATF1 = value;
		break;
	case 2 :
		LATFbits.LATF2 = value;
		break;
	case 3 :
		LATFbits.LATF3 = value;
		break;
	case 4 :
		LATDbits.LATD8 = value;
		break;
	case 5 :
		LATDbits.LATD9 = value;
		break;
	case 6 :
		LATDbits.LATD10 = value;
		break;
	case 7 :
		LATDbits.LATD11 = value;
		break;
	default :
		return -EE_LED_ERR_BAD_ID;
	}
	return 1;
}
#endif
#endif

//Start GF
/* /\************************************************************************* */
/*  PICDEM Z RF*/
/*  *************************************************************************\/ */

#if defined (__USE_PICDEMZ_WITH_INT4__) || (__USE_PICDEMZ_WITH_CN20INT__)

extern void (*EE_picdemz_callback)(void);

__INLINE__ void __ALWAYS_INLINE__ EE_picdemz_init( void(*isr_callback)(void)) {


	/* set the pins that control the radio module */
	TRISGbits.TRISG0 = 0; //PHY_RESETn_TRIS = 0;
	LATGbits.LATG0 = 0; //PHY_RESETn = 0; Reset the radio
	TRISGbits.TRISG9 = 0; // PHY_CS_TRIS = 0;
	LATGbits.LATG9 = 1; //PHY_CS = 1;
	TRISGbits.TRISG12 = 0; //PHY_WAKE_TRIS = 0;
	LATGbits.LATG12 = 1; //PHY_WAKE = 1;

	/* Initialize the spi peripheral */
	dsPIC33F_radio_spi_init(1); /* Initialize SPI2 */

#ifdef __USE_PICDEMZ_WITH_INT4__
		/* initialize INT4 interrupt */
	IFS3bits.INT4IF = 0; //RFIF = 0;
	IEC3bits.INT4IE = 1; //RFIE = 1;
#else
	/* initialize CN20 interrupt */
	CNEN2bits.CN20IE =1; //RFIEC20 = 1; INT on CN20
	IFS1bits.CNIF = 0; //RFIF = 0;
	IEC1bits.CNIE = 1; //RFIE = 1;
	TRISDbits.TRISD14 = 1; // set CN20 pin as input
#endif
	/* link the callback */
	EE_picdemz_callback = isr_callback;

}

#endif
//End GF

/* /\************************************************************************* */
/*  LCD */
/*  *************************************************************************\/ */

#ifdef __USE_LCD__
/*
   For Explorer 16 board, here are the data and control signal definitions
   RS -> RB10
   E   -> RB9
   RW -> N.C.
   DATA -> RA0 - RA7
*/

/* /\* Control signal data pins *\/ */
#define  EE_LCD_RS		LATBbits.LATB10	// LCD RS signal
#define  EE_LCD_E		LATBbits.LATB9	// LCD Enable signal
// fra
#define  EE_LCD_VLCD		LATBbits.LATB8	// LCD Voltage control
#define  EE_LCD_BRIGHTNESS	LATBbits.LATB11	// LCD Brightness control

/* /\* Control signal pin direction *\/ */
#define  EE_LCD_RS_TRIS		TRISBbits.TRISB10
#define  EE_LCD_E_TRIS		TRISBbits.TRISB9
// fra
#define  EE_LCD_VLCD_TRIS	TRISBbits.TRISB8
#define  EE_LCD_BRIGHTNESS_TRIS	TRISBbits.TRISB11

/* /\* Data signals and pin direction *\/ */
#define  EE_LCD_DATA		LATA           // Port for LCD data
#define  EE_LCD_DATAPORT	PORTA
#define  EE_LCD_TRISDATA	TRISA          // I/O setup for data Port

// fra
#define Fcy  40000000
#define Delay200uS_count  (Fcy * 0.0002) / 1080
#define Delay500uS_count  (Fcy * 0.0005) / 1080
#define Delay_1mS_Cnt	  (Fcy * 0.001) / 2950
#define Delay_2mS_Cnt	  (Fcy * 0.002) / 2950
#define Delay_5mS_Cnt	  (Fcy * 0.005) / 2950
#define Delay_20mS_Cnt	  (Fcy * 0.020) / 2950
#define Delay_1S_Cnt	  (Fcy * 1) / 2950

void Delay( unsigned int delay_count );
void Delay_Us( unsigned int delayUs_count );

/* /\* Send an impulse on the enable line.  *\/ */
__INLINE__ void __ALWAYS_INLINE__ EE_lcd_pulse_enable( void )
{
	EE_LCD_E = 1;
	Nop();
	Nop();
	Nop();
	EE_LCD_E = 0;
}

/* /\* Send a command to the lcd.  *\/ */
__INLINE__ void __ALWAYS_INLINE__ EE_lcd_command( EE_UINT8 cmd )
{
	EE_LCD_DATA &= 0xFF00;
	EE_LCD_DATA |= cmd;
	EE_LCD_RS = 0;  // fra
	EE_lcd_pulse_enable();
	Delay_Us( Delay200uS_count );
}

/* /\* Switch on or off the back illumination  *\/ */
__INLINE__ void __ALWAYS_INLINE__ EE_lcd_brightness( EE_UINT8 btns_status )
{
	EE_LCD_BRIGHTNESS = btns_status & 1;
}

/* /\* Switch on or off the display  *\/ */
__INLINE__ void __ALWAYS_INLINE__ EE_lcd_switch( EE_UINT8 lcd_status )
{
	EE_LCD_VLCD = lcd_status & 1;
}

/* /\* Initialize the display.  *\/ */
__INLINE__ void __ALWAYS_INLINE__ EE_lcd_init(void) {
	// 15mS delay after Vdd reaches nnVdc before proceeding with LCD initialization
	// not alwEE_LCD_VLCDays required and is based on system Vdd rise rate
	// Todo!!!
	EE_LCD_VLCD_TRIS	= 0;
	EE_LCD_BRIGHTNESS_TRIS	= 0;
	EE_LCD_VLCD       = 1;
	EE_LCD_BRIGHTNESS = 1;

	/* Use pin as digital IO */
 	AD1PCFGLbits.PCFG9  = 0;
 	AD1PCFGLbits.PCFG10 = 0;

	/* Initial values */
	EE_LCD_DATA &= 0xFF00;
	EE_LCD_RS   = 0;
	EE_LCD_E    = 0;

	/* Set pins direction */
	EE_LCD_TRISDATA &= 0xFF00;
	EE_LCD_RS_TRIS  = 0;
	EE_LCD_E_TRIS   = 0;
	Delay( Delay_20mS_Cnt );

	// Init - Step 1
	EE_LCD_DATA &= 0xFF00;
	EE_LCD_DATA |= 0x0038;
	EE_lcd_pulse_enable();
	Delay_Us( Delay500uS_count );

	// Init - Step 2
	EE_LCD_DATA &= 0xFF00;
	EE_LCD_DATA |= 0x0038;
	EE_lcd_pulse_enable();
	Delay_Us( Delay200uS_count );

	// Init - Step 3
	EE_LCD_DATA &= 0xFF00;
	EE_LCD_DATA |= 0x0038;
	EE_lcd_pulse_enable();
	Delay_Us( Delay200uS_count );

	EE_lcd_command( 0x38 );	// Function set
	EE_lcd_command( 0x0C );	// Display on/off control, cursor blink off (0x0C)
	EE_lcd_command( 0x06 );	// Entry mode set (0x06)
}

/* /\* Send a data.  *\/ */
__INLINE__ void __ALWAYS_INLINE__ EE_lcd_putc( unsigned char data )
{
	EE_LCD_RS = 1;
	EE_LCD_DATA &= 0xFF00;
	EE_LCD_DATA |= data;
	EE_lcd_pulse_enable();
	EE_LCD_RS = 0;
	Delay_Us( Delay200uS_count );
}

/* /\* Send a string to the display.  *\/ */
__INLINE__ void __ALWAYS_INLINE__ EE_lcd_puts( char *buf )
{
	EE_UINT8 i = 0;

	while (buf[i] != '\0')
		EE_lcd_putc(buf[i++]);
}

/* /\* Check if the display is busy.  *\/ */
__INLINE__ unsigned char __ALWAYS_INLINE__ EE_lcd_busy( void )
{
	EE_INT8 buf;

	EE_LCD_TRISDATA |= 0x00FF;
	EE_LCD_RS = 1;
	EE_lcd_pulse_enable();
	//Delay_Us( Delay200uS_count );
	buf = EE_LCD_DATAPORT & 0x00FF;
	EE_LCD_RS = 0;
	EE_LCD_TRISDATA &= 0xFF00;
	return ( (buf & 0x80) ? 1 : 0 );
}

__INLINE__ void __ALWAYS_INLINE__ EE_lcd_clear (void)		{ EE_lcd_command( 0x01 ); }

__INLINE__ void __ALWAYS_INLINE__ EE_lcd_home  (void)		{ EE_lcd_command( 0x02 ); }
__INLINE__ void __ALWAYS_INLINE__ EE_lcd_line2 (void)		{ EE_lcd_command( 0xC0 ); }

__INLINE__ void __ALWAYS_INLINE__ EE_lcd_curs_right (void)	{ EE_lcd_command( 0x14 ); }
__INLINE__ void __ALWAYS_INLINE__ EE_lcd_curs_left (void)	{ EE_lcd_command( 0x10 ); }
__INLINE__ void __ALWAYS_INLINE__ EE_lcd_shift (void)		{ EE_lcd_command( 0x1C ); }

__INLINE__ void __ALWAYS_INLINE__ EE_lcd_goto (EE_UINT8 posx, EE_UINT8 posy)
{
	EE_UINT8 tmp_pos;

	tmp_pos  = posy ? 0xC0 : 0x80;
	tmp_pos += 0x0F & posx;
	EE_lcd_command( tmp_pos );
}

#endif


/* /\************************************************************************* */
/*  Analog inputs */
/*  *************************************************************************\/ */

#if defined(__USE_ANALOG_SENSORS__) || defined(__USE_TRIMMER__) || defined(__USE_ACCELEROMETER__) || defined(__USE_ADC__)

#define AVDD 3.3
#define VREF 3.3

extern EE_UINT8 EE_adc_init;

__INLINE__ void __ALWAYS_INLINE__ EE_analog_init( void )
{
	/* Check if the ADC is initialized */
	if (EE_adc_init != 0) return;

	/* turn off ADC module */
	AD1CON1bits.ADON = 0;

	/* set ALL configuration bits as ADC input */
 	AD1PCFGLbits.PCFG12 = 0;         // Temp Sensor -> AN12/RB12
 	AD1PCFGLbits.PCFG13 = 0;         // Light Sensor -> AN13/RB13
 	AD1PCFGLbits.PCFG15 = 0;         // Trimmer        -> AN15/RB15
 	AD1PCFGHbits.PCFG16 = 0;         // Accelerometer X Axis -> AN16/RC1
 	AD1PCFGHbits.PCFG17 = 0;         // Accelerometer Y Axis -> AN17/RC2
 	AD1PCFGHbits.PCFG18 = 0;         // Accelerometer Z Axis -> AN18/RC3
 	AD1PCFGHbits.PCFG19 = 0;         // ADC Aux 1    -> AN19/RC4
 	AD1PCFGHbits.PCFG20 = 0;         // ADC Aux 2    -> AN20/RE8
 	AD1PCFGHbits.PCFG21 = 0;         // ADC Aux 3    -> AN21/RE9

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
	AD1CON1bits.ADON = 1;

	/* set ADC as configured */
	EE_adc_init = 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_analog_close( void )
{
	/* turn off ADC module */
	AD1CON1bits.ADON = 0;

	/* set ADC as unconfigured */
	EE_adc_init = 0;
}

#endif

/* ADC Aux Input */
#ifdef __USE_ADC__
__INLINE__ void __ALWAYS_INLINE__ EE_adcin_init( void ) { EE_analog_init(); }

__INLINE__ float __ALWAYS_INLINE__ EE_adcin_get_volt( EE_UINT8 channel )
{
	float adcdata;

	switch (channel) {
		case 1: // Set AN19 - RC4 as input channel
			AD1CHS0 = 19;
			break;
		case 2: // Set AN20 - RE8 as input channel
			AD1CHS0 = 20;
			break;
		case 3: // Set AN21 - RE9 as input channel
			AD1CHS0 = 21;
			break;
		default: // Set to channel 1 as default
			AD1CHS0 = 19;
			break;
	}

	/* Start conversion */
	AD1CON1bits.SAMP = 1;

	/* Wait till the EOC */
	while(!IFS0bits.AD1IF);

	/* reset ADC interrupt flag */
	IFS0bits.AD1IF = 0;

	/* Acquire data */
	adcdata = ADC1BUF0;

	/* Return conversion */
	return (adcdata * VREF) / 4096;
}
#endif

/* Trimmer Input */
#ifdef __USE_TRIMMER__
__INLINE__ void __ALWAYS_INLINE__ EE_trimmer_init( void ) { EE_analog_init(); }

__INLINE__ float __ALWAYS_INLINE__ EE_trimmer_get_volt( void )
{
	float adcdata;

	// Set AN15 - RB15 as input channel
	AD1CHS0 = 15;

	/* Start conversion */
	AD1CON1bits.SAMP = 1;

	/* Wait till the EOC */
	while(!IFS0bits.AD1IF);

	/* reset ADC interrupt flag */
	IFS0bits.AD1IF = 0;

	/* Acquire data */
	adcdata = ADC1BUF0;

	/* Return conversion */
	return (adcdata * VREF) / 4096;
}
#endif

/* Sensors Input */
#ifdef __USE_ANALOG_SENSORS__

// Thermal constants for the Voltage-Temperature conversion (fra)
#define THERM_A 0.0004132
#define THERM_B 0.000320135

__INLINE__ void __ALWAYS_INLINE__ EE_analogsensors_init( void ) { EE_analog_init(); }

__INLINE__ float __ALWAYS_INLINE__ EE_analog_get_temperature( void )
{
	float adcdata;

	// Set AN12 - RB12 as input channel
	AD1CHS0 = 12;

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

	r_therm = 1 / (4096.0/adcdata - 1.0);

	// T_K = 1.0 / (THERM_A + THERM_B * log(r_therm));
	T_K = 1.0 / (THERM_A + THERM_B * ((r_therm-1) + 9.8) );
	T_C = T_K - 273.15;

	/* Return conversion */
	return T_C;
}

__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_analog_get_light( void )
{
	EE_UINT32 adcdata;

	// Set AN13 - RB13 as input channel
	AD1CHS0 = 13;

	/* Start conversion */
	AD1CON1bits.SAMP = 1;

	/* Wait till the EOC */
	while(!IFS0bits.AD1IF);

	/* reset ADC interrupt flag */
	IFS0bits.AD1IF = 0;

	/* Acquire data */
	adcdata = ADC1BUF0;

	/* Convert the acquired data */
	adcdata = 200 - ( adcdata * 0.116 ); // lux

	/* Return conversion */
	return adcdata;
}
#endif

/* Accelerometer Input */
#ifdef __USE_ACCELEROMETER__

#define	EE_ACCEL_G_ZERO		1.65
#define	EE_ACCEL_G_SCALE_1_5	0.8
#define	EE_ACCEL_G_SCALE_2	0.6
#define	EE_ACCEL_G_SCALE_4	0.3
#define	EE_ACCEL_G_SCALE_6	0.2

extern EE_UINT8 EE_accelerometer_g;

__INLINE__ void __ALWAYS_INLINE__ EE_accelerometer_init( void )
{
	EE_analog_init();

	// Set output pins for g-select and sleep options
	TRISDbits.TRISD3  = 0;
	TRISGbits.TRISG15 = 0;   // GS1
	TRISCbits.TRISC13 = 0;   // GS2

	// Set g-selet to 6g
	LATGbits.LATG15 = 1;
	LATCbits.LATC13 = 1;
	EE_accelerometer_g = 3;

	// Disable Sleep mode
	LATDbits.LATD3 = 1;
}

__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_eccelerometer_getglevel( void ) { return EE_accelerometer_g; }

__INLINE__ void __ALWAYS_INLINE__ EE_eccelerometer_setglevel( EE_UINT8 level)
{
	if (level <= 0) {
		EE_accelerometer_g = 0;
		LATGbits.LATG15 = 0;
	  LATCbits.LATC13 = 0;
	} else if (level == 1) {
		EE_accelerometer_g = 1;
		LATGbits.LATG15 = 1;
    LATCbits.LATC13 = 0;
	} else if (level == 2) {
		EE_accelerometer_g = 2;
  	LATGbits.LATG15 = 0;
  	LATCbits.LATC13 = 1;
	} else {
		EE_accelerometer_g = 3;
  	LATGbits.LATG15 = 1;
  	LATCbits.LATC13 = 1;
	}
}

__INLINE__ void __ALWAYS_INLINE__ EE_accelerometer_sleep( void )  { LATDbits.LATD3 = 0; }

__INLINE__ void __ALWAYS_INLINE__ EE_accelerometer_wakeup( void ) { LATDbits.LATD3 = 1; }

__INLINE__ float __ALWAYS_INLINE__ EE_accelerometer_getx( void )
{
	float adcdata;

	// Set AN16 - RB16 as input channel
	AD1CHS0 = 16;

	/* Start conversion */
	AD1CON1bits.SAMP = 1;

	/* Wait till the EOC */
	while(!IFS0bits.AD1IF);

	/* reset ADC interrupt flag */
	IFS0bits.AD1IF = 0;

	/* Acquire data and convert to volts */
	adcdata = ((ADC1BUF0 * 3.3) / 4096);

	/* Return conversion */
	adcdata -= EE_ACCEL_G_ZERO;
	switch (EE_accelerometer_g) {
		case 0:
			adcdata /= EE_ACCEL_G_SCALE_1_5;
			break;
		case 1:
			adcdata /= EE_ACCEL_G_SCALE_2;
			break;
		case 2:
			adcdata /= EE_ACCEL_G_SCALE_4;
			break;
		case 3:
			adcdata /= EE_ACCEL_G_SCALE_6;
			break;
	}

	return adcdata;
}

__INLINE__ float __ALWAYS_INLINE__ EE_accelerometer_gety( void )
{
	float adcdata;

	// Set AN17 - RB17 as input channel
	AD1CHS0 = 17;

	/* Start conversion */
	AD1CON1bits.SAMP = 1;

	/* Wait till the EOC */
	while(!IFS0bits.AD1IF);

	/* reset ADC interrupt flag */
	IFS0bits.AD1IF = 0;

	/* Acquire data and convert to volts */
	adcdata = (ADC1BUF0 * 3.3) / 4096;

	/* Return conversion */
	adcdata -= EE_ACCEL_G_ZERO;
	switch (EE_accelerometer_g) {
		case 0:
			adcdata /= EE_ACCEL_G_SCALE_1_5;
			break;
		case 1:
			adcdata /= EE_ACCEL_G_SCALE_2;
			break;
		case 2:
			adcdata /= EE_ACCEL_G_SCALE_4;
			break;
		case 3:
			adcdata /= EE_ACCEL_G_SCALE_6;
			break;
	}
	return adcdata;
}

__INLINE__ float __ALWAYS_INLINE__ EE_accelerometer_getz( void )
{
	float adcdata;

	// Set AN18 - RB18 as input channel
	AD1CHS0 = 18;

	/* Start conversion */
	AD1CON1bits.SAMP = 1;

	/* Wait till the EOC */
	while(!IFS0bits.AD1IF);

	/* reset ADC interrupt flag */
	IFS0bits.AD1IF = 0;

	/* Acquire data and convert to volts */
	adcdata = (ADC1BUF0 * 3.3) / 4096;

	/* Return conversion */
	adcdata -= EE_ACCEL_G_ZERO;
	switch (EE_accelerometer_g) {
		case 0:
			adcdata /= EE_ACCEL_G_SCALE_1_5;
			break;
		case 1:
			adcdata /= EE_ACCEL_G_SCALE_2;
			break;
		case 2:
			adcdata /= EE_ACCEL_G_SCALE_4;
			break;
		case 3:
			adcdata /= EE_ACCEL_G_SCALE_6;
			break;
	}
	return adcdata; // TODO!!!
}

#endif

/* /\************************************************************************* */
/*  Buzzer */
/*  *************************************************************************\/ */

#ifdef __USE_BUZZER__

extern EE_UINT16 buzzer_freq;
extern EE_UINT16 buzzer_ticks;
extern EE_UINT16 count;


__INLINE__ void __ALWAYS_INLINE__ EE_buzzer_init( void )
{
  count=0;

  // Initialize Output Compare Module
  OC1CONbits.OCM = 0b000; // Disable Output Compare Module
  OC1R = 300; // Write the duty cycle for the first PWM pulse
  OC1RS = 1250; // Write the duty cycle for the second PWM pulse
  OC1CONbits.OCTSEL = 1; // Select Timer 3 as output compare time base
  OC1R = 1250; // Load the Compare Register Value
  OC1CONbits.OCM = 0b110; // Select the Output Compare mode
  // Initialize and enable Timer3
  T3CONbits.TON = 0; // Disable Timer
  T3CONbits.TCS = 0; // Select internal instruction cycle clock
  T3CONbits.TGATE = 0; // Disable Gated Timer mode
  //T2CONbits.TCKPS = 0b00; // Select 1:1 Prescaler
  	T3CONbits.TCKPS = 1;
  TMR3 = 0x00; // Clear timer register
  PR3 = 2500; // Load the period value
  IPC2bits.T3IP = 0x01; // Set Timer 3 Interrupt Priority Level
  IFS0bits.T3IF = 0; // Clear Timer 3 Interrupt Flag
  IEC0bits.T3IE = 0; // Disable Timer 3 interrupt
  T3CONbits.TON = 0; //
}

__INLINE__ void __ALWAYS_INLINE__ EE_buzzer_set_freq( EE_UINT16 new_freq )
{
  buzzer_freq  = new_freq;
  if ((new_freq > 100) && (new_freq < 48000)) {

    buzzer_freq  = 5000000ul / buzzer_freq;
    buzzer_ticks = buzzer_freq >> 1;

    OC1R = buzzer_ticks;
    OC1RS = buzzer_ticks;
    PR3 = buzzer_freq;
    if(!T3CONbits.TON)
      T3CONbits.TON = 1; // Start Timer
  }
  else T3CONbits.TON = 0; // Start Timer
}

__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_buzzer_get_freq( void ) {
	return buzzer_freq;
}

__INLINE__ void __ALWAYS_INLINE__ EE_buzzer_mute( void ) {
	/* Stop Timer3 */
	T3CONbits.TON = 0;
}

__INLINE__ void __ALWAYS_INLINE__ EE_buzzer_unmute( void ) {
	/* Clear contents of the timer register */
	TMR3 = 0;

	/* Start Timer3 */
	T3CONbits.TON = 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_buzzer_close( void ) {
	/* Stop Timer4 */
	T3CONbits.TON = 0;

	/* Disable Timer4 interrupts */
	IEC0bits.T3IE = 0;
}

#endif

/* /\************************************************************************* */
/*  PWM Output */
/*  *************************************************************************\/ */

#ifdef __USE_PWM__

#define EE_PWM_PORT1 1
#define EE_PWM_PORT2 2

#define EE_PWM_ZERO_DUTY 1500

extern EE_UINT8 t_pre_scaler;

void EE_pwm_init(EE_UINT8 chan, unsigned long int pwm_period, unsigned long int init_pw);

//__INLINE__ void __ALWAYS_INLINE__ EE_pwm_set_duty_f( EE_UINT8 chan , float duty )
//{
//	/* The computed duty cycle*/
//	float duty_out ;
//
//	/* Get period from Timer2 period register PR2 */
//	EE_UINT16 period = PR2;
//
//	if (duty <= 0.0)
//		duty_out = 0; //** for negative values assume zero
//	else if(duty >= 1.0)
//		duty_out = 1; //** for exessive values assume one
//	else
//		duty_out = duty; //** for the correct values ...
//
//	// Computer register valure
//	switch (chan) {
//		case EE_PWM_PORT1:
//			OC8RS = duty_out * (period+1);
//			break;
//		case EE_PWM_PORT2:
//			OC7RS = duty_out * (period+1);
//			break;
//	}
//}

void EE_pwm_set_duty_f( EE_UINT8 chan , float duty );

__INLINE__ void __ALWAYS_INLINE__ EE_pwm_set_duty(EE_UINT8 chan, unsigned long int duty)
{
  duty = ( (duty * 40) >> t_pre_scaler ) - 1;  /* Compute the Current PulseWidth  to set */

	if(	duty > PR2) return;

  switch(chan)
  {
    case EE_PWM_PORT1:
			OC8RS = (unsigned int)duty; /* Load OCRS: current pwm duty cycle */
    	break;
    case EE_PWM_PORT2:
			OC3RS = (unsigned int)duty; /* Load OCRS: current pwm duty cycle */
    	break;
  }

  return;
}

__INLINE__ void __ALWAYS_INLINE__ EE_pwm_close( EE_UINT8 chan )
{
	switch (chan) {
		case EE_PWM_PORT1:	/** Close PWM1 **/
			OC8RS  = 0;
			OC8CON = 0;
			break;

		case EE_PWM_PORT2: /** Close PWM2 **/
			OC3RS  = 0;
			OC3CON = 0;
			break;
	}
}

#endif // __USE_PWM__

/* /\************************************************************************* */
/*  DAC */
/*  *************************************************************************\/ */

#ifdef __USE_DAC__

#define EE_DAC_I2C_KCLOCK		100

#define EE_DAC_GENERAL_CALL_RESET	0x06
#define EE_DAC_GENERAL_CALL_WAKEUP	0x09

#define EE_DAC_PD_NORMAL		0x00
#define EE_DAC_PD_1K			0x01
#define EE_DAC_PD_100K			0x10
#define EE_DAC_PD_500K			0x11

#define EE_DAC_SAVE_EEPROM		0x00
#define EE_DAC_NOSAVE_EEPROM		0x02

__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_dac_general_call( EE_UINT8 second )
{
	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

	// Transmit a Start condition
	I2C1CONbits.SEN = 1;		// initiate Start on SDA and SCL pins

	// Wait till Start sequence is completed
	while(I2C1CONbits.SEN);

	// Write Slave address and set master for transmission  (R/W bit should be 0)
	I2C1TRN = 0x00;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -1;

	// Wait till address is transmitted
	while(I2C1STATbits.TBF);

	// Test for ACK condition received
	while(I2C1STATbits.ACKSTAT);

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

	// Write command
	I2C1TRN = 0x06;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -1;

	// Wait till address is transmitted
	while(I2C1STATbits.TBF);

	// Test for ACK condition received
	while(I2C1STATbits.ACKSTAT);

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

	// send STOP condition
	I2C1CONbits.PEN = 1;	/* initiate Stop on SDA and SCL pins */

	// Wait till Stop sequence is completed
	while(I2C1CONbits.PEN);

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

	return 0;
}

__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_dac_fast_write( EE_UINT16 data, EE_UINT8 port, EE_UINT8 power)
{
	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

	// Transmit a Start condition
	I2C1CONbits.SEN = 1;		// initiate Start on SDA and SCL pins

	// Wait till Start sequence is completed
	while(I2C1CONbits.SEN);

	// Write address
	I2C1TRN = 0xC0 + ( port*2 & 0x02 );
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -1;

	// Wait till address is transmitted
	while(I2C1STATbits.TBF);

	// Test for ACK condition received
	while(I2C1STATbits.ACKSTAT);

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

	// Write first byte
	I2C1TRN = ((data / 256) & 0x0F) + (power << 4);
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -1;

	// Wait till data is transmitted
	while(I2C1STATbits.TBF);

	// Test for ACK condition received
	while(I2C1STATbits.ACKSTAT);

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

	// Write second byte
	I2C1TRN = data % 256;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -1;

	// Wait till data is transmitted
	while(I2C1STATbits.TBF);

	// Test for ACK condition received
	while(I2C1STATbits.ACKSTAT);

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

	// send STOP condition
	I2C1CONbits.PEN = 1;	/* initiate Stop on SDA and SCL pins */

	// Wait till Stop sequence is completed
	while(I2C1CONbits.PEN);

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

	return 0;
}

__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_dac_write( EE_UINT16 data, EE_UINT8 port, EE_UINT8 power, EE_UINT8 save)
{
	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

	// Transmit a Start condition
	I2C1CONbits.SEN = 1;		// initiate Start on SDA and SCL pins

	// Wait till Start sequence is completed
	while(I2C1CONbits.SEN);

	// Write address
	I2C1TRN = 0xC0 + ( port*2 & 0x02 );
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -1;

	// Wait till address is transmitted
	while(I2C1STATbits.TBF);

	// Test for ACK condition received
	while(I2C1STATbits.ACKSTAT);

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

	// Write first byte
	I2C1TRN = 0x40 + ( save & 0x20 ) + power*2;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -1;

	// Wait till data is transmitted
	while(I2C1STATbits.TBF);

	// Test for ACK condition received
	while(I2C1STATbits.ACKSTAT);

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

	// Write second byte
	I2C1TRN = data / 16;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -1;

	// Wait till address is transmitted
	while(I2C1STATbits.TBF);

	// Test for ACK condition received
	while(I2C1STATbits.ACKSTAT);

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

	// Write third byte
	I2C1TRN = (data % 16) << 4;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -1;

	// Wait till address is transmitted
	while(I2C1STATbits.TBF);

	// Test for ACK condition received
	while(I2C1STATbits.ACKSTAT);

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

	// send STOP condition
	I2C1CONbits.PEN = 1;	/* initiate Stop on SDA and SCL pins */

	// Wait till Stop sequence is completed
	while(I2C1CONbits.PEN);

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

	return 0;
}

__INLINE__ void __ALWAYS_INLINE__ EE_dac_init( void )
{
	/* Configre SCL/SDA pin as open-drain */
	ODCGbits.ODCG2 = 1;
	ODCGbits.ODCG3 = 1;

	/* Clear Address and mask */
	I2C1ADD = 0;
	I2C1MSK = 0;

	/* Set baudrate */
	I2C1BRG = (40000ul / EE_DAC_I2C_KCLOCK) - 37;	// With Fcy = 40MHz !!!
	//I2C1BRG = 363;

	/* Configure I2C port */
	I2C1CON = 0;
	I2C1CONbits.ACKDT  = 1;
	I2C1CONbits.DISSLW = 1;

	/* Start I2C port */
	I2C1CONbits.I2CEN = 1;

	EE_dac_general_call(EE_DAC_GENERAL_CALL_RESET);
}

#endif

/* /\************************************************************************* */
/*  Motor PWM - TODO!!! */
/*  *************************************************************************\/ */

#ifdef __USE_PWM_MOTOR__

__INLINE__ void __ALWAYS_INLINE__ EE_motor_init( void ) {

}

#endif

/* /\************************************************************************* */
/*  Encoder */
/*  *************************************************************************\/ */

#ifdef __USE_ENCODER__

#define QEI_TICK_PER_REV	500
#define	QEI_MAX_CNT_PER_REV	0xffff

__INLINE__ void __ALWAYS_INLINE__ EE_encoder_init( void )
{
	/* set encoder bits as digital input */
 	AD1PCFGLbits.PCFG3 = 1;
 	AD1PCFGLbits.PCFG4 = 1;
 	AD1PCFGLbits.PCFG5 = 1;
 	AD2PCFGLbits.PCFG3 = 1;
 	AD2PCFGLbits.PCFG4 = 1;
 	AD2PCFGLbits.PCFG5 = 1;

	// Disable QEI Module
	QEICONbits.QEIM = 0;

	// Clear any count errors
	QEICONbits.CNTERR = 0;

	// Count error interrupts disabled
	DFLTCONbits.CEID = 1;

	// Reset position counter
	POSCNT = 0;

	// Set bound value
	MAXCNT = QEI_MAX_CNT_PER_REV;

	// X4 mode with position counter reset by MAXCNT
	QEICONbits.QEIM = 7;
}

__INLINE__ void __ALWAYS_INLINE__ EE_encoder_close( void )
{
	// Disable QEI Module
	QEICONbits.QEIM = 0;
}

__INLINE__ EE_INT16 __ALWAYS_INLINE__ EE_encoder_get_ticks( void )
{
	return ((EE_INT16)POSCNT);
}

//__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_encoder_get_position( void )
__INLINE__ float __ALWAYS_INLINE__ EE_encoder_get_position( void )
{
	EE_INT16 POSCNTcopy = 0;

	POSCNTcopy = (int)POSCNT;

	if (POSCNTcopy < 0)
		POSCNTcopy = -POSCNTcopy;

	//AngPos[1] = AngPos[0];
	//AngPos[0] = (unsigned int)(((unsigned long)POSCNTcopy * 2048)/125);
	// 0 <= POSCNT <= 1999 to 0 <= AngPos <= 32752

	//return (unsigned int)(((unsigned long)POSCNTcopy * 2048)/125);
	return (float)(((unsigned long)POSCNTcopy*500)/360);
}

#endif


/* ************************************************************************* */

/* ************************************************************************* */

#endif

#endif
