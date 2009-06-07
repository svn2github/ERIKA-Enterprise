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
#define ADC_TURN_ON					AD1CON1bits.ADON = 1
#define ADC_TURN_OFF				AD1CON1bits.ADON = 0
#define START_CONVERSION         	AD1CON1bits.SAMP = 0
#define CONVERSION_DONE				AD1CON1bits.DONE
#define CONVERSION_RESET			AD1CON1bits.DONE = 0

#if !defined(__USE_TOUCH_STANDARD__) && !defined(__USE_TOUCH_ALTERNATE__)
#error "Choose one between TOUCH_STANDARD or TOUCH_ALTERNATE."
#endif

#if defined(__USE_TOUCH_STANDARD__) && defined(__USE_TOUCH__ALTERNATE__)
#error "Choose only ONE between TOUCH_STANDARD or TOUCH_ALTERNATE."
#endif

#ifdef __USE_TOUCH_ALTERNATE__

// I/O
#define TOUCHSCREEN_INPUT		PORTB
#define TOUCHSCREEN_OUTPUT		LATB
#define TOUCHSCREEN_DDR			TRISB

#define FAKE_PULL_UP_OUTPUT		LATD
#define FAKE_PULL_UP_DDR		TRISD

// Bit Definitions

#define EE_T_TOP	11			// RB11
#define EE_T_LEFT	10			// RB10
#define EE_T_BOTTOM	4			// RB4
#define EE_T_RIGHT	5			// RB5

#define EE_T_FAKE_PULL_UP		8

// ADC reading pins
#define STANDBY_PIN	EE_T_BOTTOM            // Pin Change & Low_Level_Readings & X-Coordinate Reading
#define ADC_X		STANDBY_PIN
#define ADC_Y		EE_T_RIGHT
#define ADC_Z1		ADC_Y
#define ADC_Z2		EE_T_TOP

#define ClearBit(ADRESS,BIT)	(ADRESS&=~(1<<BIT)) // LAT##ADRESS##bits.LAT##ADRESS##BIT = 0
#define SetBit(ADRESS,BIT)		(ADRESS|=(1<<BIT))
#define TestBit(ADRESS,BIT)		((ADRESS&(1<<BIT)))
#define ToggleBit(ADRESS, BIT) 	((ADRESS)^=(1<<(BIT)))

#define Pin_Gnd(LLL)			(SetBit(AD1PCFGL,LLL),ClearBit(TOUCHSCREEN_DDR,LLL),ClearBit(TOUCHSCREEN_OUTPUT,LLL))
#define Pin_Vdd(LLL)			(SetBit(AD1PCFGL,LLL),ClearBit(TOUCHSCREEN_DDR,LLL),SetBit(TOUCHSCREEN_OUTPUT,LLL))
#define Pin_Hi_Z(LLL)			(ClearBit(AD1PCFGL,LLL),SetBit(TOUCHSCREEN_DDR,LLL))
#define Pin_Pullup(LLL)			(SetBit(AD1PCFGL,LLL),SetBit(TOUCHSCREEN_DDR,LLL))

// I/O States
#define STANDBY_CONFIGURATION		(Pin_Gnd(EE_T_LEFT),	Pin_Hi_Z(EE_T_RIGHT), 	Pin_Hi_Z(EE_T_TOP),	Pin_Hi_Z(EE_T_BOTTOM))
#define X_POS_CONFIGURATION			(Pin_Gnd(EE_T_LEFT),	Pin_Vdd(EE_T_RIGHT),	Pin_Hi_Z(EE_T_TOP),	Pin_Hi_Z(EE_T_BOTTOM))
#define Y_POS_CONFIGURATION			(Pin_Hi_Z(EE_T_LEFT),	Pin_Hi_Z(EE_T_RIGHT),	Pin_Gnd(EE_T_TOP),	Pin_Vdd(EE_T_BOTTOM))
#define HI_Z_CONFIGURATION			(Pin_Hi_Z(EE_T_LEFT),	Pin_Hi_Z(EE_T_RIGHT),	Pin_Hi_Z(EE_T_TOP),	Pin_Hi_Z(EE_T_BOTTOM))
#define Z1_Z2_CONFIGURATION			(Pin_Gnd(EE_T_LEFT),	Pin_Hi_Z(EE_T_RIGHT),	Pin_Hi_Z(EE_T_TOP),	Pin_Vdd(EE_T_BOTTOM))

#endif // __USE_TOUCH_ALTERNATE__

#ifdef __USE_TOUCH_STANDARD__ // failure

#define EE_TOUCH_BOTTOM_AD		AD1PCFGLbits.PCFG15
#define EE_TOUCH_RIGHT_AD		AD1PCFGLbits.PCFG9

#define EE_TOUCH_BOTTOM_TRIS	TRISBbits.TRISB15
#define EE_TOUCH_RIGHT_TRIS		TRISBbits.TRISB9

#define EE_TOUCH_EN_A			LATEbits.LATE1
#define EE_TOUCH_EN_B			LATEbits.LATE2
#define EE_TOUCH_EN_C			LATEbits.LATE3

#define EE_TOUCH_EN_A_TRIS 		TRISEbits.TRISE1
#define EE_TOUCH_EN_B_TRIS		TRISEbits.TRISE2
#define EE_TOUCH_EN_C_TRIS		TRISEbits.TRISE3

#define clear_bit(BIT)			(BIT = 0)
#define set_bit(BIT)			(BIT = 1)
#define toggle_bit(BIT) 		(BIT ^= 1)

// ADC reading pins
#define STANDBY_PIN				9		// Pin Change & Low_Level_Readings & X-Coordinate Reading
#define ADC_X					15
#define ADC_Y					9

// I/O States
#define STANDBY_CONFIGURATION	(set_bit(EE_TOUCH_EN_A), set_bit(EE_TOUCH_EN_B), clear_bit(EE_TOUCH_EN_C))
#define X_POS_CONFIGURATION		(clear_bit(EE_TOUCH_EN_A), clear_bit(EE_TOUCH_EN_B), clear_bit(EE_TOUCH_EN_C))
#define Y_POS_CONFIGURATION		(set_bit(EE_TOUCH_EN_A), clear_bit(EE_TOUCH_EN_B), clear_bit(EE_TOUCH_EN_C))

#endif // __USE_TOUCH_STANDARD__

#endif // __FOUR_WIRES__

#ifdef __FIVE_WIRES__
#error "There_s no support for five wires device ^_^ Enjoy."
#endif // __FIVE_WIRES__

#endif // __MICROCHIP_DSPIC30__

#endif // __touch_hal_ee_h__
