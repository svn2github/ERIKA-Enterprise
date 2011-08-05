/* ###*B*###
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
 * ###*E*### */
 
 /**
    @file   ee_board.h
    @brief  easylab board header file.
        
    Header file taht contains board's API declaration, and defines 
    for remap mcu drivers on board layout.
        
    @author Errico Guidieri
    @date   2011
  */
 
#ifndef __INCLUDE_EASYLAB_BOARD_H__
#define __INCLUDE_EASYLAB_BOARD_H__

/******************************* 
Include device header
********************************/
#include "mcu/microchip_dspic/inc/ee_mcu.h"

#ifdef __USE_UART__
/** configure UART1_RX driver pin **/
#define EE_Board_Uart1_Rx EE_PIN_RP10
/** configure UART1_TX driver pin **/
#define EE_Board_Uart1_Tx EE_PIN_RP11
#endif /* __USE_UART__ */

#ifdef __USE_LEDS__
void EE_leds_init(void);

#ifdef __dsPIC33FJ64MC802__
/** @brief Enable all LEDS **/
__INLINE__ void EE_leds_enable(void){
    /* Abilitazione LED pins regA */
    LATAbits.LATA3 = 1;
    LATAbits.LATA4 = 1;

    /* Abilitazione LED pins regB */
    LATBbits.LATB4  = 1;
    LATBbits.LATB5  = 1;
    LATBbits.LATB6  = 1;
    LATBbits.LATB7  = 1;
    LATBbits.LATB12 = 1;
    LATBbits.LATB13 = 1;

    /* system LED (the one on microstick) */
    LATBbits.LATB15 = 1;
}

/** @brief Disable all LEDS **/
__INLINE__ void EE_leds_disable(void){
    /* Disabilitazione LED pins regA */
    LATAbits.LATA3 = 0;
    LATAbits.LATA4 = 0;

    /* Disabilitazione LED pins regB */
    LATBbits.LATB4  = 0;
    LATBbits.LATB5  = 0;
    LATBbits.LATB6  = 0;
    LATBbits.LATB7  = 0;
    LATBbits.LATB12 = 0;
    LATBbits.LATB13 = 0;
    
    /* system LED (the one on microstick) */
    LATBbits.LATB15 = 0;
}

/** @brief Enable system led (the one on microstick) **/
static inline void EE_sys_led_on(void){
    LATBbits.LATB15 = 1;
}

/** @brief Disable system led (the one on microstick) **/
__INLINE__ void EE_sys_led_off(void){
    LATBbits.LATB15 = 0;
}

/** @brief Toogle system led (the one on microstick) **/
__INLINE__ void EE_sys_led_toggle(void){
    LATBbits.LATB15 = ~LATBbits.LATB15;
}


/** @brief Enable led1 **/
static inline void EE_led1_on(void){
    LATBbits.LATB12 = 1;
}

/** @brief Disable led 1 **/
__INLINE__ void EE_led1_off(void){
    LATBbits.LATB12 = 0;
}

/** @brief Toogle led 1 **/
__INLINE__ void EE_led1_toggle(void){
    LATBbits.LATB12 = ~LATBbits.LATB12;
}

/** @brief Enable led 2 **/
__INLINE__ void EE_led2_on(void){
    LATBbits.LATB13 = 1;
}

/** @brief Disable led 2 **/
__INLINE__ void EE_led2_off(void){
    LATBbits.LATB13 = 0;
}

/** @brief Toggle led 2 **/
__INLINE__ void EE_led2_toggle(void){
    LATBbits.LATB13 = ~LATBbits.LATB13;
}

/** @brief Enable led 3 */
__INLINE__ void EE_led3_on(void){
    LATBbits.LATB7 = 1;
}

/** @brief Disable led 3 **/
__INLINE__ void EE_led3_off(void){
    LATBbits.LATB7 = 0;
}

/** @brief Toggle led 3 **/
__INLINE__ void EE_led3_toggle(void){
    LATBbits.LATB7 = ~LATBbits.LATB7;
}

/** @brief Enable led 4 **/
__INLINE__ void EE_led4_on(void){
    LATBbits.LATB6 = 1;
}

/** @brief Disable led 4 **/
__INLINE__ void EE_led4_off(void){
    LATBbits.LATB6 = 0;
}

/** @brief Toggle led 4 **/
__INLINE__ void EE_led4_toggle(void){
    LATBbits.LATB6 = ~LATBbits.LATB6;
}

/** @brief Enable led 7 **/
__INLINE__ void EE_led7_on(void){
    LATAbits.LATA3 = 1;
}

/** @brief Disable led 7 **/
__INLINE__ void EE_led7_off(void){
    LATAbits.LATA3 = 0;
}

/** @brief Toggle led 7 **/
__INLINE__ void EE_led7_toggle(void){
    LATAbits.LATA3 = ~LATAbits.LATA3;
}

/** @brief Enable led 8 */
__INLINE__ void EE_led8_on(void){
    LATBbits.LATB4 = 1;
}

/** @brief Disable led 8 **/
__INLINE__ void EE_led8_off(void){
    LATBbits.LATB4 = 0;
}

/** @brief Toggle led 8 **/
__INLINE__ void EE_led8_toggle(void){
    LATBbits.LATB4 = ~LATBbits.LATB4;
}

/** @brief Enable led 9 **/
__INLINE__ void EE_led9_on(void){
    LATAbits.LATA4 = 1;
}

/** @brief Disable led 9 **/
__INLINE__ void EE_led9_off(void){
    LATAbits.LATA4 = 0;
}

/** @brief Toogle led 9 **/
__INLINE__ void EE_led9_toggle(void){
    LATAbits.LATA4 = ~LATAbits.LATA4;
}

/** @brief Enable led 10 **/
__INLINE__ void EE_led10_on(void){
    LATBbits.LATB5 = 1;
}

/** @brief Disable led 10 **/
__INLINE__ void EE_led10_off(void){
    LATBbits.LATB5 = 0;
}

/** @brief Toggle led 10 **/
__INLINE__ void EE_led10_toggle(void){
    LATBbits.LATB5 = ~LATBbits.LATB5;
}
#endif /* __dsPIC33FJ64MC802__ */
#endif /* __USE_LEDS__ */

#ifdef __USE_DIO__
#ifdef __dsPIC33FJ64MC802__
/* TODO */
#endif /*__dsPIC33FJ64MC802__ */
#endif /*__USE_DIO__ */

#ifdef __USE_BUZZER__

/**
    @brief Start the buzzer
    
    Start the buzzer. These Buzzer API use Timer2 of dspic mcu.
    
    @param freq (EE_UINT16): output square wave frequency, that drive the buzzer (Hz)
**/
void EE_buzzer_start(EE_UINT16 freq);

/** 
    @brief Togle the status of the GPIO pin that driver the buzzer 
        (used as callback for the 
**/
void EE_buzzer_toggle(void);

/**
    @brief Stop the buzzer

    @param half_period (EE_UINT16): toggle output time value (=half period)
**/
void EE_buzzer_stop(void);

#endif /* __USE_BUZZER__ */

#ifdef __USE_ADC__

/** 
    Remap ADC channels IDs on right pins 
    @{
**/
#define EE_ADC_AN1   EE_ADC_PIN0
#define EE_ADC_AN2   EE_ADC_PIN1
#define EE_ADC_AN3   EE_ADC_PIN4
#define EE_ADC_AN4   EE_ADC_PIN5
/** @} */

#include "mcu/microchip_dspic/inc/ee_adc.h"

/** @brief Initialize ADC driver.
    
    @param adc_ch_id (EE_AdcChId): channel's ID to initialize
    @param volt_ref (EE_Adc_VoltageRef): a voltage reference pair enum values
    @param bit_res (EE_Adc_BitResolution): desired ADc bit resolution
    
    @return 0 if no errors happend. 
        Otherwise appropriate error value (negative value).
**/
__INLINE__ EE_INT8 EE_easylab_adc_init_ch(EE_AdcChId adc_ch_id, EE_Adc_VoltageRef volt_ref, 
    EE_Adc_BitResolution bit_res)
{
    return EE_adc_init_ch(EE_ADC_1, adc_ch_id, volt_ref, bit_res);
}

/**
    @brief Get channel value as uint 
    
    @param adc_ch_id (EE_AdcChId): channel's ID to acquire.
    @param value  (EE_UINT16 *): return value pointer.
    
    @return 0 if no errors happend. 
        Otherwise appropriate error value (negative value).
**/
__INLINE__ EE_INT8 EE_easylab_adc_get_ch_uint(EE_AdcChId adc_ch_id, EE_UINT16 * value ){
    return EE_adc_get_ch_uint(EE_ADC_1, adc_ch_id, value);
}

/** 
    @brief Start ADC sampling 
    
    @return 0 if no errors happend. 
        Otherwise appropriate error value (negative value).

 **/
__INLINE__ EE_INT8 EE_easylab_adc_start ( ) {
    return EE_adc_start(EE_ADC_1);
}

/** 
    @brief Stop ADC sampling 
    
    @return 0 if no errors happend. 
        Otherwise appropriate error value (negative value).

 **/
__INLINE__ EE_INT8 EE_easylab_adc_stop (void){
    return EE_adc_stop(EE_ADC_1);
}


#endif /*__USE_ADC__ */

#ifdef __USE_PWM__

/** 
    Easylab Pins define for PWM
    @{    
**/
#define EE_EASYLAB_PWM1     1
#define EE_EASYLAB_PWM2     2  
#define EE_EASYLAB_PWM3     3
#define EE_EASYLAB_PWM4     4
/* if you want activate PWM over both pins 1 e 2 you should use these pin's ID */
#define EE_EASYLAB_PWM12    5
/* if you want activate PWM over both pins 3 e 4 you should use these pin's ID */
#define EE_EASYLAB_PWM34    6
/** @} **/

#include "mcu/microchip_dspic/inc/ee_pwm.h"

/** 
    Easylab PWM API error codes 
    @{
 **/
#define EE_EASYLAB_PWM_ERROR_INVALID_PIN_ID     -1
/** @} **/

/**
    @brief Initialize PWM pin

    @param pwm_pin (EE_UINT8): Pin's Id where start a PWM
    @param pwm_freq (EE_UINT32): pwm frequency

    @return an error value (negative integer) if someting happened
**/
EE_INT16 EE_easylab_pwm_init(EE_UINT8 pwm_pin, EE_UINT32 pwm_freq);

/**
    @brief Close a PWM pin.
    
    @param pwm_ch (EE_UINT8): pwm pin's Id.
    
    @return an error value (negative integer) if someting happened
**/
EE_INT16 EE_easylab_pwm_close(EE_UINT8 pwm_pin);

/**
    @brief Set PWM pin duty cicle and if, this value is not 0, start it.
    
    @param pwm_pin (EE_UINT8): pwm pin's Id.
    @param pwm_freq (EE_UINT32): pwm duty cycle [0, 100]
    
    @return an error value (negative integer) if someting happened
**/
EE_INT16 EE_easylab_pwm_set_duty(EE_UINT8 pwm_pin, EE_UINT16 duty);

#endif /* __USE_PWM__ */

#endif /*__INCLUDE_EASYLAB_BOARD_H__ */
