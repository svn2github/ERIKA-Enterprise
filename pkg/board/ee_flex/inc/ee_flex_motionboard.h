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


#ifndef __INCLUDE_EE_FLEX_MOTIONBOARD_H__
#define __INCLUDE_EE_FLEX_MOTIONBOARD_H__

#ifdef __USE_MOTIONBOARD__


/* /\************************************************************************* */
/*  LEDs */
/*  *************************************************************************\/ */

#ifdef __USE_LEDS__

__INLINE__ void __ALWAYS_INLINE__ EE_demoboard_leds_init(void) {
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
/*  PWM Output */
/*  *************************************************************************\/ */

#ifdef __USE_PWM_OUT__

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
			OC7RS = (unsigned int)duty; /* Load OCRS: current pwm duty cycle */
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
			OC7RS  = 0;
			OC7CON = 0;
			break;
	}
}

#endif // __USE_PWM_OUT__


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
/* USB Communication - TODO!!! */
/* ************************************************************************* */

#if defined __USE_USB__
void EE_usb_init(void);
EE_INT16 EE_usb_write(EE_UINT8 *buf, EE_UINT16 len);
EE_INT16 EE_usb_read(EE_UINT8 *buf, EE_UINT16 len);
#endif

/* ************************************************************************* */

/* ************************************************************************* */

#endif

#endif
