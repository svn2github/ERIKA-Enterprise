#ifndef __TOUCH_HAL_EE_H__
#define __TOUCH_HAL_EE_H__

#if defined __MICROCHIP_DSPIC30__

#ifndef __USE_LCD__

#define Fcy  40000000
#define Delay200uS_count  (Fcy * 0.0002) / 1080
#define Delay500uS_count  (Fcy * 0.0005) / 1080
#define Delay_1mS_Cnt	  (Fcy * 0.001) / 2950
#define Delay_2mS_Cnt	  (Fcy * 0.002) / 2950
#define Delay_5mS_Cnt	  (Fcy * 0.005) / 2950
#define Delay_20mS_Cnt	  (Fcy * 0.020) / 2950
#define Delay_1S_Cnt	  (Fcy * 1) / 2950

#endif // __USE_LCD__

#if !defined(__FOUR_WIRES__) && !defined(__FIVE_WIRES__)
#error "Choose one between FOUR WIRES and FIVE WIRES technologies."
#endif

#if defined(__FOUR_WIRES__) && defined(__FIVE_WIRES__)
#error "Choose only ONE between FOUR WIRES and FIVE WIRES technologies."
#endif

#ifdef __FOUR_WIRES__

/****************************************************************************
  4-wires
****************************************************************************/

// ADC Settings
#ifndef ADC_TO_USE
#define ADC_TO_USE						1
#endif

#if ADC_TO_USE!=1 && ADC_TO_USE!=2
#error dsPIC33 has only two ADCs.Please change ADC_TO_USE macro.
#endif

#if ADC_TO_USE==1

#define ADC_ONOFF							AD1CON1bits.ADON
#define ADC_SAMP							AD1CON1bits.SAMP
#define ADC_ASAM							AD1CON1bits.ASAM
#define ADC_FORM							AD1CON1bits.FORM
#define ADC_SSRC							AD1CON1bits.SSRC
#define ADC_AD12B							AD1CON1bits.AD12B
#define ADC_CON2							AD1CON2
#define ADC_SAMC							AD1CON3bits.SAMC
#define ADC_ADRC							AD1CON3bits.ADRC
#define ADC_ADCS							AD1CON3bits.ADCS
#define ADC_CONVERSION_DONE		AD1CON1bits.DONE
#define ADC_SELECTED_PIN 			AD1CHS0
#define ADC_RESULT_BUFFER			ADC1BUF0
#define ADC_INTERRUPT_FLAG		IFS0bits.AD1IF
#define ADC_INTERRUPT_ENABLE	IEC0bits.AD1IE
#define ADC_INTERRUPT_NAME		_ADC1Interrupt
#define EE_TOUCH_BOTTOM_AD		AD1PCFGLbits.PCFG15
#define EE_TOUCH_RIGHT_AD			AD1PCFGLbits.PCFG9

#else

#define ADC_ONOFF							AD2CON1bits.ADON
#define ADC_SAMP							AD2CON1bits.SAMP
#define ADC_ASAM							AD2CON1bits.ASAM
#define ADC_FORM							AD2CON1bits.FORM
#define ADC_SSRC							AD2CON1bits.SSRC
#define ADC_AD12B							AD2CON1bits.AD12B
#define ADC_CON2							AD2CON2
#define ADC_SAMC							AD2CON3bits.SAMC
#define ADC_ADRC							AD2CON3bits.ADRC
#define ADC_ADCS							AD2CON3bits.ADCS
#define ADC_CONVERSION_DONE		AD2CON1bits.DONE
#define ADC_SELECTED_PIN 			AD2CHS0
#define ADC_RESULT_BUFFER			ADC2BUF0
#define ADC_INTERRUPT_FLAG		IFS1bits.AD2IF
#define ADC_INTERRUPT_ENABLE	IEC1bits.AD2IE
#define ADC_INTERRUPT_NAME		_ADC2Interrupt
#define EE_TOUCH_BOTTOM_AD		AD2PCFGLbits.PCFG15
#define EE_TOUCH_RIGHT_AD			AD2PCFGLbits.PCFG9

#endif

#define ADC_TURN_ON						SETBIT(ADC_ONOFF)
#define ADC_TURN_OFF					CLEARBIT(ADC_ONOFF)
#define ADC_CONVERSION_RESET	CLEARBIT(ADC_CONVERSION_DONE)
#define ADC_CONVERSION_START  CLEARBIT(ADC_SAMP)

#define EE_TOUCH_BOTTOM_TRIS	TRISBbits.TRISB15
#define EE_TOUCH_RIGHT_TRIS		TRISBbits.TRISB9

#define EE_TOUCH_EN_A					LATEbits.LATE1
#define EE_TOUCH_EN_B					LATEbits.LATE2
#define EE_TOUCH_EN_C					LATEbits.LATE3

#define EE_TOUCH_EN_A_TRIS 		TRISEbits.TRISE1
#define EE_TOUCH_EN_B_TRIS		TRISEbits.TRISE2
#define EE_TOUCH_EN_C_TRIS		TRISEbits.TRISE3

#define CLEARBIT(BIT)					(BIT = 0)
#define SETBIT(BIT)						(BIT = 1)
#define TOGGLEBIT(BIT) 				(BIT ^= 1)

// ADC reading pins
#define STANDBY_PIN						9		// Pin Change & Low_Level_Readings & X-Coordinate Reading
#define ADC_X									15
#define ADC_Y									9	

// I/O States
#define STANDBY_CONFIGURATION	(SETBIT(EE_TOUCH_EN_A), SETBIT(EE_TOUCH_EN_B), CLEARBIT(EE_TOUCH_EN_C))
#define X_POS_CONFIGURATION		(CLEARBIT(EE_TOUCH_EN_A), SETBIT(EE_TOUCH_EN_B), SETBIT(EE_TOUCH_EN_C))
#define Y_POS_CONFIGURATION		(SETBIT(EE_TOUCH_EN_A), CLEARBIT(EE_TOUCH_EN_B), CLEARBIT(EE_TOUCH_EN_C))

#endif // __FOUR_WIRES__

#ifdef __FIVE_WIRES__
#error There_s no support for five wires device ^_^ Enjoy.
#endif // __FIVE_WIRES__

#endif // __MICROCHIP_DSPIC30__

#endif // __touch_hal_ee_h__
