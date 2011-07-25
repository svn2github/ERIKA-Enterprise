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
#include "ee.h"
#include "mcu/microchip_dspic/inc/ee_adc.h"

#ifdef __dsPIC33FJ64MC802__

#ifdef _PCFG16 /* AD1PCFGMbits: PORT Configuration Register High. AD1PCFGMbits.PCFG16 */
static void EE_adc_init_driver_high()
{
    if(!driver_initialized){
        /* Is better leave those pins as analog input so digital In buffer is turned-off
           and it doesn't consume power */
        /*
        AD1PCFGLbits.PCFG6 = 1;
        AD1PCFGLbits.PCFG7 = 1;
        AD1PCFGLbits.PCFG8 = 1;
        AD1PCFGLbits.PCFG9 = 1;
        */
        /* TODO: Add support for Port High PINs 
        (AD1PCFGM: PORT Configuration Register High) */
    }
}

static EE_AdcErr EE_adc_init_high_port( EE_AdcChId adc_ch_id )
{
    /* TODO: Add support for Port High PINs (AD1PCFGM: PORT Configuration Register High) */
    return EE_ADC_ERR_NO;
}

static EE_AdcErr EE_sdc_get_high_port ( EE_AdcId adc_ch_id )
{
    EE_AdcErr error = EE_ADC_ERR_NO;
    switch ( adc_ch_id ){
        case EE_ADC1_PIN6:
            AD1PCFGLbits.PCFG6 = 0;
        break;
        case EE_ADC1_PIN7:
            AD1PCFGLbits.PCFG7 = 0;
        break;
        case EE_ADC1_PIN8:
            AD1PCFGLbits.PCFG8 = 0;
        break;
        case EE_ADC1_PIN9:
            AD1PCFGLbits.PCFG9 = 0;
        break;
        /* TODO: Add support for Port High PINs (AD1PCFGM: PORT Configuration Register High) */
        default:
            error = EE_ADC_ERR_CHID_INVALID;
    }
    return error;
}

#else
static EE_AdcErr EE_adc_init_high_port( EE_AdcChId adc_ch_id )
{
    return EE_ADC_ERR_CHID_INVALID;
}

static EE_AdcErr EE_sdc_get_high_port ( EE_AdcChId adc_ch_id )
{
    return EE_ADC_ERR_CHID_INVALID;
}

#define EE_adc_init_driver_high()
#endif /* _PCFG16 */

static EE_UINT8 driver_initialized = 0;

enum EE_Adc_SampleFormats {
    EE_ADC_UINT  = 0x0,
    EE_ADC_INT   = 0x1,
    EE_ADC_UFRAC = 0x2,
    EE_ADC_FRAC  = 0x3
};

static void EE_adc_set_sample_format(enum EE_Adc_SampleFormats format)
{
    AD1CON1bits.FORM = format;
}

static void EE_adc_int_driver()
{
    /* AD1PCFGLbits are initialized as Analog Input in POR (Power on Reset).
       I put them as digital input here. */
    if(!driver_initialized){
        /* Is better leave those pins as analog input so digital In buffer is turned-off
           and it doesn't consume power */
        /*
        AD1PCFGLbits.PCFG0 = 1;
        AD1PCFGLbits.PCFG1 = 1;
        AD1PCFGLbits.PCFG2 = 1;
        AD1PCFGLbits.PCFG3 = 1;
        AD1PCFGLbits.PCFG4 = 1;
        AD1PCFGLbits.PCFG5 = 1;
        */
        EE_adc_init_driver_high();
        driver_initialized  = 1;
    }
}

static EE_INT16 EE_adc1_init_ch_internal ( EE_AdcChId adc_ch_id, EE_Adc_VoltageRef volt_ref,
    EE_Adc_BitResolution bit_res )
{
    /* initialize driver */
    EE_adc_int_driver();
    /* turn off ADC module */
    AD1CON1bits.ADON = 0;
    EE_INT16 error = EE_ADC_ERR_NO;
    switch( adc_ch_id ) {
        case EE_ADC_PIN0:
            AD1PCFGLbits.PCFG0 = 0;
        break;
        case EE_ADC_PIN1:
            AD1PCFGLbits.PCFG1 = 0;
        break;
        case EE_ADC_PIN2:
            AD1PCFGLbits.PCFG2 = 0;
        break;
        case EE_ADC_PIN3:
            AD1PCFGLbits.PCFG3 = 0;
        break;
        case EE_ADC_PIN4:
            AD1PCFGLbits.PCFG4 = 0;
        break;
        case EE_ADC_PIN5:
            AD1PCFGLbits.PCFG5 = 0;
        break;
        default:
            error = EE_adc_init_high_port( adc_ch_id );
    }
    if(!error){
            /* Set control register 2 */
            /* Vref = AVcc/AVdd, Scan Inputs */
            AD1CON2bits.VCFG = volt_ref;
            /* Set bit resolution for ADC (10 or 12 bits) */
            AD1CON1bits.AD12B = bit_res;
            /*  Sample Clock Source Select bits 
                111 => Internal counter ends sampling and starts conversion (autosampling)
                Other configuration not supported because they depends on other periphereal
                (GP Timers, PWM, external pins)
            */
            AD1CON1bits.SSRC = 0x7;

            /* Input scan not supported by default */
            AD1CON2bits.CSCNA = 0; /* Input scan enable bit */
            AD1CSSL = 0x0000;  /* Channel selection register for input scan [none]*/
            
            /*  1 => Sampling begins immediately after last conversion. SAMP bit is auto-set
                0 => Sampling begins when SAMP bit is set 
                We want trigger convertion with a function call so we put this at 0.
            */
            AD1CON1bits.ASAM = 0; /* ADC Sample Auto-Start bit */
            
            /* 
              1 => ADC internal RC clock
              0 => Clock derived from system clock */
            AD1CON3bits.ADRC = 0; /* ADC Conversion Clock Source bit */
            /* AST = value (e.g. 31) * Tad Tad: ADC clock period [if ARDC = 0 
               then periphereal clock]) used only if SSRC if autosampling is choose */
            AD1CON3bits.SAMC = 31; /* Auto Sample Time (AST) bits */
            /* 0011 1111 => TAD = (ADCS<7:0> + 1) · TCY = 64 · TCY 
               Not used if ADRC were = 1 */
            AD1CON3bits.ADCS = 0x003F; /* ADC Conversion Clock Select bits */
            
            /* reset ADC interrupt flag */
            IFS0bits.AD1IF = 0;
            /* disable ADC interrupts */
            IEC0bits.AD1IE = 0;
    } else {
        /* Unitialize driver */
        driver_initialized = 0;
    }
    return error;
}

static EE_INT16 EE_adc2_init_ch_internal ( EE_AdcChId adc_ch_id, EE_Adc_VoltageRef volt_ref,
    EE_Adc_BitResolution bit_res )
{
    /* To Be implemented */
    return EE_ADC_ERR_CHID_INVALID;
}

EE_AdcErr EE_adc_init_ch( EE_Adc_Coverter_Id adc_id, EE_AdcChId adc_ch_id, 
    EE_Adc_VoltageRef volt_ref, EE_Adc_BitResolution bit_res )
{
    EE_AdcErr error;
    switch( adc_id ){
        case EE_ADC_1:
            error = EE_adc1_init_ch_internal( adc_ch_id, volt_ref, bit_res );
        break;
        case EE_ADC_2:
            error = EE_adc2_init_ch_internal( adc_ch_id, volt_ref, bit_res );
        break;
        default:
            error = EE_ADC_ERR_CHID_INVALID;
    }
    return error;
}

static EE_AdcErr EE_adc1_start_internal ( void )
{
    EE_INT16 error = EE_ADC_ERR_NO;
    /* turn on ADC module */
    if(driver_initialized)
        AD1CON1bits.ADON = 1;
    else
        error = EE_ADC_ERR_DRIVER_UNINT;
    return error;
}

static EE_AdcErr EE_adc2_start_internal( void )
{
    /* To Be implemented */
    return EE_ADC_ERR_CHID_INVALID;
}

EE_AdcErr EE_adc_start( EE_Adc_Coverter_Id adc_id ){
    EE_AdcErr error;
    switch( adc_id ){
        case EE_ADC_1:
            error = EE_adc1_start_internal( );
        break;
        case EE_ADC_2:
            error = EE_adc2_start_internal( );
        break;
        default:
            error = EE_ADC_ERR_CHID_INVALID;
    }
    return error;
}

static EE_AdcErr EE_adc1_stop_internal( void )
{
    /* turn off ADC module */
    AD1CON1bits.ADON = 0;
    return EE_ADC_ERR_NO;
}

static EE_AdcErr EE_adc2_stop_internal( void )
{
    /* To Be implemented */
    return EE_ADC_ERR_CHID_INVALID;
}

EE_AdcErr EE_adc_stop( EE_Adc_Coverter_Id adc_id ){
    EE_AdcErr error;
    switch( adc_id ){
        case EE_ADC_1:
            error = EE_adc1_stop_internal( );
        break;
        case EE_ADC_2:
            error = EE_adc2_stop_internal( );
        break;
        default:
            error = EE_ADC_ERR_CHID_INVALID;
    }
    return error;
}

static EE_AdcErr EE_adc1_get_ch_uint_internal( EE_AdcChId adc_ch_id, EE_UINT16 * value)
{
    EE_AdcErr error = EE_ADC_ERR_NO;
    if(!driver_initialized) {
        error = EE_ADC_ERR_DRIVER_UNINT; 
    } else {
        /* Set the data format to acquire as UINT (10 -12 bit) */
        EE_adc_set_sample_format(EE_ADC_UINT);
        /* Select channel to acquire */
        switch (adc_ch_id) {
            case EE_ADC_PIN0:
                if(AD1PCFGLbits.PCFG0){
                    error = EE_ADC_ERR_CHID_INVALID;
                    break;
                }
                AD1CHS0bits.CH0SA = 0;
            break;
            case EE_ADC_PIN1: 
                if(AD1PCFGLbits.PCFG1) {
                    error = EE_ADC_ERR_CHID_INVALID;
                    break;
                }
                AD1CHS0bits.CH0SA = 1;
            break;
            case EE_ADC_PIN4: 
                if(AD1PCFGLbits.PCFG4) {
                    error = EE_ADC_ERR_CHID_INVALID;
                    break;
                }
                AD1CHS0bits.CH0SA = 4;
            break;
            case EE_ADC_PIN5:
                if(AD1PCFGLbits.PCFG5){
                    error = EE_ADC_ERR_CHID_INVALID;
                    break;
                }
                AD1CHS0bits.CH0SA = 5;
            break;
            default:
                error = EE_sdc_get_high_port ( adc_ch_id );
        }
        if(!error){
            /* Start conversion (reset DONE pin too) */
            AD1CON1bits.SAMP = 1;
            while(!AD1CON1bits.DONE){
                /* Wait till the EOC */
            }
            /* Stop conversion */
            AD1CON1bits.SAMP = 0;
            /* Acquire data */
            *value =  ADC1BUF0;
        }
    }
    return error;
}

static EE_AdcErr EE_adc2_get_ch_uint_internal( EE_AdcChId adc_ch_id, EE_UINT16 * value ){
    /* TO Be implemented */
    return EE_ADC_ERR_CHID_INVALID;
}

EE_AdcErr EE_adc_get_ch_uint( EE_Adc_Coverter_Id adc_id, EE_AdcChId adc_ch_id, EE_UINT16 * value ){
    EE_AdcErr error;
    switch( adc_id ){
        case EE_ADC_1:
            error = EE_adc1_get_ch_uint_internal( adc_ch_id, value );
        break;
        case EE_ADC_2:
            error = EE_adc2_get_ch_uint_internal( adc_ch_id, value );
        break;
        default:
            error = EE_ADC_ERR_CHID_INVALID;
    }
    return error;
}

#endif /*__dsPIC33FJ64MC802__ */


