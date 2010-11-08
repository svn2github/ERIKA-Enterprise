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


/******************************************************************************/
/*                                    Leds                                    */
/******************************************************************************/
#ifdef __USE_LEDS__

__INLINE__ void __ALWAYS_INLINE__ EE_daughter_leds_init(void) 
{
	/* set LEDs drive state low */
	LATDbits.LATD0 = 0;
	LATDbits.LATD2 = 0;
	/* set LEDs pin as output */
	TRISDbits.TRISD0 = 0;
	TRISDbits.TRISD2 = 0;
}
__INLINE__ void __ALWAYS_INLINE__ EE_led_0_on(void)   
{ 
	LATDbits.LATD0 = 1;
}
__INLINE__ void __ALWAYS_INLINE__ EE_led_0_off(void)  
{ 
	LATDbits.LATD0 = 0;
}
__INLINE__ void __ALWAYS_INLINE__ EE_led_1_on(void)   
{ 
	LATDbits.LATD2 = 1;
}
__INLINE__ void __ALWAYS_INLINE__ EE_led_1_off(void)  
{ 
	LATDbits.LATD2 = 0;
}
__INLINE__ void __ALWAYS_INLINE__ EE_leds_on(void)   
{ 
	LATDbits.LATD0 = 1;
	LATDbits.LATD2 = 1;
}
__INLINE__ void __ALWAYS_INLINE__ EE_leds_off(void)  
{ 
	LATDbits.LATD0 = 0;
	LATDbits.LATD2 = 0;
}

#endif

/******************************************************************************/
/*                                   Buttons                                  */
/*Author: Gianluca Franchino                                                  */
/******************************************************************************/
#ifdef __USE_BUTTONS__

extern void (*EE_buttonS1_callback)(void);
extern void (*EE_buttonS2_callback)(void);

__INLINE__ void __ALWAYS_INLINE__ EE_button_S1_init(void(*isr_callback)(void))
{

	/* set BUTTON pins as inputs */
	TRISDbits.TRISD11  = 1;

	/* enable Input capture on falling edge */
	IC4CON = 0x2;

	/* Enable Interrupt */
	if (isr_callback != NULL) {
		IEC2bits.IC4IE = 1;
		IFS2bits.IC4IF = 0;
		/* Save callback */
		EE_buttonS1_callback = isr_callback;
	}
}

__INLINE__ void __ALWAYS_INLINE__ EE_button_S2_init(void(*isr_callback)(void))
{

	/* set BUTTON pins as inputs */
	TRISDbits.TRISD9  = 1;

	/* enable Input capture on falling edge */
	IC2CON = 0x2;

	/* Enable Interrupt */
	if (isr_callback != NULL) {
		IEC0bits.IC2IE = 1;
		IFS0bits.IC2IF = 0;
		/* Save callback */
		EE_buttonS2_callback = isr_callback;
	}
}

__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_button_get_S1(void)
{
	return !(PORTDbits.RD11);
}
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_button_get_S2(void)
{
	return !(PORTDbits.RD9);
}

__INLINE__ void __ALWAYS_INLINE__ EE_buttons_init( void(*isr_callback1)(void), void(*isr_callback2)(void) )
{
	EE_button_S1_init(isr_callback1);
	EE_button_S2_init(isr_callback2);
}

#endif

/******************************************************************************/
/*                                   Switch                                   */
/******************************************************************************/
#ifdef __USE_SWITCH__

__INLINE__ void __ALWAYS_INLINE__ EE_switch_init(void) 
{
	/* set SWITCH pins as inputs */
	TRISEbits.TRISE7  = 1;
	TRISEbits.TRISE6  = 1;
	TRISEbits.TRISE5  = 1;
	TRISGbits.TRISG13 = 1;
	TRISAbits.TRISA7  = 1;
	TRISGbits.TRISG14 = 1;
	TRISDbits.TRISD4  = 1;
	TRISDbits.TRISD1  = 1;
}

__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_switch_1_get(void) 
{
	return !(PORTEbits.RE7);
}
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_switch_2_get(void) 
{
	return !(PORTEbits.RE6);
}
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_switch_3_get(void) 
{
	return !(PORTEbits.RE5);
}
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_switch_4_get(void) 
{
	return !(PORTGbits.RG13);
}
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_switch_5_get(void) 
{
	return !(PORTAbits.RA7);
}
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_switch_6_get(void) 
{
	return !(PORTGbits.RG14);
}
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_switch_7_get(void) 
{
	return !(PORTDbits.RD4);
}
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_switch_8_get(void) 
{
	return !(PORTDbits.RD1);
}

__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_switch_get_all(void) 
{

	return !(((EE_UINT8) PORTEbits.RE7      ) |
		((EE_UINT8) PORTEbits.RE6  << 1 ) |
		((EE_UINT8) PORTEbits.RE5  << 2 ) |
		((EE_UINT8) PORTGbits.RG13 << 3 ) |
		((EE_UINT8) PORTAbits.RA7  << 4 ) |
		((EE_UINT8) PORTGbits.RG14 << 5 ) |
		((EE_UINT8) PORTDbits.RD4  << 6 ) |
		((EE_UINT8) PORTDbits.RD1  << 7 ));
}
#endif /* __USE_SWITCH__ */




/******************************************************************************/
/*                                   PWM Out                                  */
/******************************************************************************/
#ifdef __USE_PWM__

#define EE_PWM_PORT1 1
#define EE_PWM_PORT2 2

#define EE_PWM_ZERO_DUTY 1500

extern EE_UINT8 t_pre_scaler;

void EE_pwm_init(EE_UINT8 chan, EE_UINT32 pwm_period, EE_UINT32 init_pw);

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

void EE_pwm_set_duty_f(EE_UINT8 chan , float duty);

__INLINE__ void __ALWAYS_INLINE__ EE_pwm_set_duty(EE_UINT8 chan, EE_UINT32 duty)
{
	/* Compute the Current PulseWidth  to set */
	duty = ( (duty * 40) >> t_pre_scaler ) - 1;  
	if (duty > PR2) 
		return;
	duty = PR2 - duty;    // board-dependent inversion.
	switch(chan) {
	case EE_PWM_PORT1:
		OC8RS = (EE_UINT16)duty; /* Load OCRS: current pwm duty cycle */
		break;
	case EE_PWM_PORT2:
		OC7RS = (EE_UINT16)duty; /* Load OCRS: current pwm duty cycle */
	  	break;
	}
	return;
}

__INLINE__ void __ALWAYS_INLINE__ EE_pwm_close(EE_UINT8 chan)
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

#endif // __USE_PWM__

/******************************************************************************/
/*                                   DC-Motor PWM Out                         */
/******************************************************************************/
#ifdef __USE_DCM_PWM__

/* PWM */
#define EE_DCM_PORT1 			1
#define EE_DCM_PORT2 			2
#define EE_DCM_EN_M1_TRIS		TRISDbits.TRISD7
#define EE_DCM_EN_M1			LATDbits.LATD7
#define EE_DCM_EN_M2_TRIS		TRISDbits.TRISD6
#define EE_DCM_EN_M2			LATDbits.LATD6
#define EE_DCM_DIR_POS			1
#define EE_DCM_DIR_NEG			-1

int EE_dcm_pwm_init(EE_UINT8 chan, EE_UINT32 pwm_freq, EE_UINT16 init_duty, EE_INT8 dir);
void EE_dcm_pwm_set_duty(EE_UINT8 chan, EE_UINT32 duty);
void EE_dcm_pwm_set_direction(EE_UINT8 chan, EE_INT8 dir);
void EE_dcm_pwm_close(void);
void EE_dcm_pwm_enable_chan(EE_UINT8 chan);
void EE_dcm_pwm_disable_chan(EE_UINT8 chan);

#endif // __USE_DCM_PWM__

/******************************************************************************/
/*                                   Encoder                                  */
/******************************************************************************/
#ifdef __USE_ENCODER__

#define EE_ENCODER_HW 		0
#define EE_ENCODER_SW 		1
#define EE_ENCODER_SW_PINA	PORTDbits.RD8                       // IC1
#define EE_ENCODER_SW_PINB	PORTBbits.RB11                      // digital input
#define QEI_TICK_PER_REV	500
#define	QEI_MAX_CNT_PER_REV	0xffff
#define	SWENC_MAX_CNT_PER_REV	0xffff

extern EE_INT16 ee_encsw_poscnts;
extern EE_INT16 ee_encsw_swapped;
extern EE_INT16 ee_encsw_maxcnt;

__INLINE__ void __ALWAYS_INLINE__ EE_encoder_SW_init(EE_UINT8 swap_on_off, EE_UINT8 irq_on_off)
{
	if(swap_on_off)
		ee_encsw_swapped = 1;
	else
		ee_encsw_swapped = 0;
	ee_encsw_maxcnt = SWENC_MAX_CNT_PER_REV;
	
	/** 
		Set encoder RB11 pin as digital. Used for channel A.
	*/
	AD1PCFGLbits.PCFG11 = 1; 
 	AD2PCFGLbits.PCFG11 = 1; 
	TRISBbits.TRISB11 = 1; 		/*PIN CHA */
	
	/** 
		Motion board encoder sw driver 
		uses IC1 to raise interrupts. Used for channel B.  
	*/
 	TRISDbits.TRISD8 = 1;  		/*PIN CHB */
 	
	/** 
		Reset position counter
	*/
	ee_encsw_poscnts = 0;
	
	/**
		Initialize Capture Module
		ICSIDL: Input Capture Module Stop in Idle Control bit
		1 = Input capture module will halt in CPU Idle mode
		0 = Input capture module will continue to operate in CPU Idle mode
	*/
	IC1CONbits.ICSIDL = 0;

	/**
		ICTMR: Input Capture Timer Select bits
		1 = TMR2 contents are captured on capture event
		0 = TMR3 contents are captured on capture event
	*/
	IC1CONbits.ICTMR= 1;

	/**
		ICI<1:0>: Select Number of Captures per Interrupt bits
		11 = Interrupt on every fourth capture event
		10 = Interrupt on every third capture event
		01 = Interrupt on every second capture event
		00 = Interrupt on every capture event
	*/
	IC1CONbits.ICI= 0;  

	/**
		ICM<2:0>: Input Capture Mode Select bits
		111 = Input Capture functions as interrupt pin only, when device is in Sleep or Idle mode
				(Rising edge detect only, all other control bits are not applicable.)
		110 = Unused (module disabled)
		101 = Capture mode, every 16th rising edge
		100 = Capture mode, every 4th rising edge
		011 = Capture mode, every rising edge
		010 = Capture mode, every falling edge
		001 = Capture mode, every edge (rising and falling)
				(ICI<1:0> does not control interrupt generation for this mode.)
		000 = Input capture module turned off
	*/
	IC1CONbits.ICM = 0b001;   

	/** 
		Enable Capture Interrupt
	*/
	IPC0bits.IC1IP = 6;      // Setup IC1 interrupt priority level 
	IFS0bits.IC1IF = 0;      // Clear IC1 Interrupt Status Flag
	IEC0bits.IC1IE = irq_on_off;      // Enable IC1 interrupt
}

__INLINE__ void __ALWAYS_INLINE__ EE_encoder_SW_close(void)
{
	// Turn off the IC1 module
	IC1CONbits.ICM = 0;
	// Disable Capture Interrupt
	IEC0bits.IC1IE = 0;      // Enable IC1 interrupt
	IFS0bits.IC1IF = 0;      // Clear IC1 Interrupt Status Flag
}

__INLINE__ EE_INT16 __ALWAYS_INLINE__ EE_encoder_SW_get_ticks(void)
{
	return ee_encsw_poscnts;
}

__INLINE__ float __ALWAYS_INLINE__ EE_encoder_SW_get_position(float sw_gain)
{
	return (float)EE_encoder_SW_get_ticks() * sw_gain;
}

__INLINE__ void __ALWAYS_INLINE__ EE_encoder_init(EE_UINT8 swap_on_off, EE_UINT8 irq_on_off)
{
	/* Default value */
	QEICON = 0;
	
	/* set encoder bits as digital input */
 	AD1PCFGLbits.PCFG3 = 1;
 	AD1PCFGLbits.PCFG4 = 1;
 	AD1PCFGLbits.PCFG5 = 1;
 	AD2PCFGLbits.PCFG3 = 1;
 	AD2PCFGLbits.PCFG4 = 1;
 	AD2PCFGLbits.PCFG5 = 1;

	// Swap channels
	QEICONbits.SWPAB = swap_on_off;
	// Count error interrupts disabled
	DFLTCONbits.CEID = 1;
	// Interrupts
		// Interrupts
	IPC14bits.QEIIP = 5;
	IFS3bits.QEIIF = 0;
	IEC3bits.QEIIE = irq_on_off;
	// Reset position counter
	POSCNT = 0;
	// Set bound value
	MAXCNT = QEI_MAX_CNT_PER_REV;
	// X4 mode with position counter reset by MAXCNT
	QEICONbits.QEIM = 7;
}

__INLINE__ void __ALWAYS_INLINE__ EE_encoder_close(void)
{
	// Disable QEI Module
	QEICONbits.QEIM = 0;
}

__INLINE__ EE_INT16 __ALWAYS_INLINE__ EE_encoder_get_ticks(void)
{
	return ((EE_INT16)POSCNT);
}

__INLINE__ float __ALWAYS_INLINE__ EE_encoder_get_position(float hw_gain)
{
	return (float)EE_encoder_get_ticks() * hw_gain; 
}

__INLINE__ void __ALWAYS_INLINE__ EE_encoder_set_IRQ(EE_UINT8 irq_on_off)
{
	IEC3bits.QEIIE = irq_on_off;
}

extern void (*QEI_cbk)(void);
__INLINE__ void __ALWAYS_INLINE__ EE_encoder_set_ISR_callback(void (*qei_cbk)(void))
{
	QEI_cbk = qei_cbk;
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
