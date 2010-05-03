/*
  Name: ee_gpio.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: GPIO library functions header file.
*/


#ifndef __INCLUDE_EEMCUMICO32_GPIO_H__
#define __INCLUDE_EEMCUMICO32_GPIO_H__

#ifdef __USE_GPIO__

#include "cpu/mico32/inc/ee_internal.h"
#include "mcu/mico32/inc/ee_internal.h"
#include <cpu/mico32/inc/ee_irq.h>
#include <MicoGPIO.h>

/*************************************************************************
 GPIO
*************************************************************************/
/* Generic Macros */
#define EE_GPIO_OK                              (0x00) 
#define EE_GPIO_FAILURE                         (-1)
/* Macro for Structure declaration */
#define DECLARE_STRUCT_GPIO(uc, lc)             \
extern EE_gpio_st EE_ST_NAME(lc);
/* Macro for structure definition */
#define DEFINE_STRUCT_GPIO(uc, lc)                      \
EE_gpio_st cat3(ee_, lc, _st) = {                       \
    .base = (MicoGPIO_t* )cat2(uc, _BASE_ADDRESS),      \
    .irqf = cat2(uc, _IRQ),                             \
    .cbk = EE_NULL_CBK,                                 \
    .flag = 0};

/* GPIO structure */
typedef struct {
    /** Pins that caused the latest interrupt; this mask is valid only in
     * the callback */
    unsigned int flag;
    /** Controller base address */
    MicoGPIO_t* base;
    /** IRQ number to register the handler */
    int irqf;
    /** Interrupt callback */
    EE_ISR_callback cbk;
    /** Copy of the data register.  Used for GPIO configured as both input and
     * output */
    unsigned int data_copy;
} EE_gpio_st;

/* Macros for User functions (API) */  
#define DECLARE_FUNC_GPIO(uc, lc)                                       \
__INLINE__ unsigned int __ALWAYS_INLINE__ cat3(EE_, lc, _read_data)(void){ \
    return EE_hal_gpio_read_data((MicoGPIO_t*)EE_BASE_ADD(uc)); }       \
 __INLINE__ unsigned int __ALWAYS_INLINE__ cat3(EE_, lc, _read_data_out)(void){ \
     if (cat2(uc, _BOTH_INPUT_AND_OUTPUT))                              \
         return EE_hal_gpio_bothio_read_data_out(&EE_ST_NAME(lc));      \
     else                                                               \
         return EE_hal_gpio_read_data_out((MicoGPIO_t*)EE_BASE_ADD(uc)); } \
 __INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _write_data)(unsigned int val){ \
     if (cat2(uc, _BOTH_INPUT_AND_OUTPUT))                              \
         EE_hal_gpio_bothio_write_data((MicoGPIO_t*)EE_BASE_ADD(uc), val, &EE_ST_NAME(lc)); \
     else                                                               \
         EE_hal_gpio_write_data((MicoGPIO_t*)EE_BASE_ADD(uc), val); }   \
 __INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _write_bit_data)(unsigned int val, unsigned char numbit){ \
     if (cat2(uc, _BOTH_INPUT_AND_OUTPUT))                              \
         EE_hal_gpio_bothio_write_bit_data((MicoGPIO_t*)EE_BASE_ADD(uc), val, numbit, &EE_ST_NAME(lc)); \
     else                                                               \
         EE_hal_gpio_write_bit_data((MicoGPIO_t*)EE_BASE_ADD(uc), val, numbit); } \
 __INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _write_mask_data)(unsigned int val, unsigned int mask){ \
     if (cat2(uc, _BOTH_INPUT_AND_OUTPUT))                              \
         EE_hal_gpio_bothio_write_mask_data((MicoGPIO_t*)EE_BASE_ADD(uc), val, mask, &EE_ST_NAME(lc)); \
     else                                                               \
         EE_hal_gpio_write_mask_data((MicoGPIO_t*)EE_BASE_ADD(uc), val, mask); } \
 __INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _read_tristate)(void){  \
     return EE_hal_gpio_read_tristate((MicoGPIO_t*)EE_BASE_ADD(uc)); }  \
 __INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _write_tristate)(unsigned int val){ \
     EE_hal_gpio_write_tristate((MicoGPIO_t*)EE_BASE_ADD(uc), val); }   \
 __INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _write_bit_tristate)(unsigned int val, unsigned char numbit){ \
     EE_hal_gpio_write_bit_tristate((MicoGPIO_t*)EE_BASE_ADD(uc), val, numbit); } \
 __INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _write_mask_tristate)(unsigned int val, unsigned int mask){ \
     EE_hal_gpio_write_mask_tristate((MicoGPIO_t*)EE_BASE_ADD(uc), val, mask); } \
 __INLINE__ unsigned int __ALWAYS_INLINE__ cat3(EE_, lc, _read_irqMask)(void){ \
     return EE_hal_gpio_read_irqMask((MicoGPIO_t*)EE_BASE_ADD(uc)); }   \
 __INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _write_irqMask)(unsigned int val){ \
     EE_hal_gpio_write_irqMask((MicoGPIO_t*)EE_BASE_ADD(uc), val); }    \
 __INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _write_bit_irqMask)(unsigned int val, unsigned char numbit){ \
     EE_hal_gpio_write_bit_irqMask((MicoGPIO_t*)EE_BASE_ADD(uc), val, numbit); } \
 __INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _write_mask_irqMask)(unsigned int val, unsigned int mask){ \
     EE_hal_gpio_write_mask_irqMask((MicoGPIO_t*)EE_BASE_ADD(uc), val, mask); } \
 __INLINE__ unsigned int __ALWAYS_INLINE__ cat3(EE_, lc, _read_edgeCapture)(void){ \
     return EE_hal_gpio_read_edgeCapture((MicoGPIO_t*)EE_BASE_ADD(uc)); } \
 __INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _write_edgeCapture)(unsigned int val){ \
     EE_hal_gpio_write_edgeCapture((MicoGPIO_t*)EE_BASE_ADD(uc), val); } \
 __INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _write_bit_edgeCapture)(unsigned int val, unsigned char numbit){ \
     EE_hal_gpio_write_bit_edgeCapture((MicoGPIO_t*)EE_BASE_ADD(uc), val, numbit); } \
 __INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _write_mask_edgeCapture)(unsigned int val, unsigned int mask){ \
     EE_hal_gpio_write_mask_edgeCapture((MicoGPIO_t*)EE_BASE_ADD(uc), val, mask); } \
 __INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _enable_IRQ)(unsigned int ch){ \
     EE_hal_gpio_enable_IRQ(& EE_ST_NAME(lc), cat2(uc, _IRQ_MODE), ch); } \
 __INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _disable_IRQ)(void){   \
     EE_hal_gpio_disable_IRQ(& EE_ST_NAME(lc)); }                       \
 __INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _set_IRQ_callback)(EE_ISR_callback cbk){ \
     EE_hal_gpio_set_IRQ_callback(& EE_ST_NAME(lc), cbk); }

void EE_gpio_common_handler(int level);

__INLINE__ unsigned int __ALWAYS_INLINE__ EE_hal_gpio_read_data(MicoGPIO_t* base)
{
    return base->data;
}
 
__INLINE__ unsigned int __ALWAYS_INLINE__ EE_hal_gpio_read_data_out(MicoGPIO_t* base)
{
    return base->data;
}
 
__INLINE__ unsigned int __ALWAYS_INLINE__ EE_hal_gpio_bothio_read_data_out(EE_gpio_st *gpio_sp)
{
    return gpio_sp->data_copy;
}
 
__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_write_data(MicoGPIO_t *base, unsigned int val)
{
    base->data = val;
} 

__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_bothio_write_data_internal(MicoGPIO_t *base, unsigned int val, EE_gpio_st *gpio_sp)
{
    gpio_sp->data_copy = val;
    base->data = val;
} 

__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_bothio_write_data(MicoGPIO_t *base, unsigned int val, EE_gpio_st *gpio_sp)
{
    EE_FREG irqstat;

    irqstat = EE_mico32_disableIRQ();
    EE_hal_gpio_bothio_write_data_internal(base, val, gpio_sp);
    if (EE_mico32_are_IRQs_enabled(irqstat))
        EE_mico32_enableIRQ();
} 

__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_write_bit_data(MicoGPIO_t *base, unsigned int val, unsigned char numbit)
{
    unsigned int mask = (1 << numbit);
    unsigned int data;
    EE_FREG irqstat;

    irqstat = EE_mico32_disableIRQ();
    data = EE_hal_gpio_read_data_out(base);
    if(val)
        EE_hal_gpio_write_data(base, data | mask);
    else
        EE_hal_gpio_write_data(base, data & (~mask));
    if (EE_mico32_are_IRQs_enabled(irqstat))
        EE_mico32_enableIRQ();
} 
                
__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_bothio_write_bit_data(
    MicoGPIO_t *base, unsigned int val, unsigned char numbit,
    EE_gpio_st *gpio_sp)
{
    unsigned int mask = (1 << numbit);
    unsigned int data;
    EE_FREG irqstat;

    irqstat = EE_mico32_disableIRQ();
    data = EE_hal_gpio_bothio_read_data_out(gpio_sp);
    if(val)
        EE_hal_gpio_bothio_write_data_internal(base, data | mask, gpio_sp);
    else
        EE_hal_gpio_bothio_write_data_internal(base, data & (~mask), gpio_sp);
    if (EE_mico32_are_IRQs_enabled(irqstat))
        EE_mico32_enableIRQ();
} 
                
__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_write_mask_data(MicoGPIO_t* base,
    unsigned int val, unsigned int mask)
{ 
    unsigned int data;
    EE_FREG irqstat;

    irqstat = EE_mico32_disableIRQ();
    data = EE_hal_gpio_read_data_out(base);
    EE_hal_gpio_write_data(base, (data & (~mask)) | (val & mask));
    if (EE_mico32_are_IRQs_enabled(irqstat))
        EE_mico32_enableIRQ();
}
        
__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_bothio_write_mask_data(
    MicoGPIO_t* base, unsigned int val, unsigned int mask, EE_gpio_st *gpio_sp)
{ 
    unsigned int data;
    EE_FREG irqstat;

    irqstat = EE_mico32_disableIRQ();
    data = EE_hal_gpio_bothio_read_data_out(gpio_sp);
    EE_hal_gpio_bothio_write_data_internal(base,
        (data & (~mask)) | (val & mask), gpio_sp);
    if (EE_mico32_are_IRQs_enabled(irqstat))
        EE_mico32_enableIRQ();
}
        
__INLINE__ unsigned int __ALWAYS_INLINE__ EE_hal_gpio_read_tristate(
    MicoGPIO_t* base)
{ 
    return base->tristate;
} 
        
__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_write_tristate(MicoGPIO_t* base,
    unsigned int val)
{ 
    base->tristate = val;
} 
        
__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_write_bit_tristate(MicoGPIO_t* base, unsigned int val, unsigned char numbit)
{ 
    unsigned int mask = (1 << numbit);
    unsigned int tristate;
    EE_FREG irqstat;
        
    irqstat = EE_mico32_disableIRQ();
        tristate = base->tristate;
    if(val)
        base->tristate = tristate | mask;
    else
        base->tristate = tristate & (~mask);
    if (EE_mico32_are_IRQs_enabled(irqstat))
        EE_mico32_enableIRQ();
} 
        
__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_write_mask_tristate(MicoGPIO_t* base, unsigned int val, unsigned int mask)
{ 
    unsigned int tristate;
    EE_FREG irqstat;
        
    irqstat = EE_mico32_disableIRQ();
    tristate = base->tristate;
    base->tristate = (tristate & (~mask)) | (val & mask);
    if (EE_mico32_are_IRQs_enabled(irqstat))
        EE_mico32_enableIRQ();
} 
        
__INLINE__ unsigned int __ALWAYS_INLINE__ EE_hal_gpio_read_irqMask(MicoGPIO_t* base)
{ 
    return base->irqMask;
} 
        
__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_write_irqMask(MicoGPIO_t* base, unsigned int val)
{ 
    base->irqMask = val;
}       
        
__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_write_bit_irqMask(MicoGPIO_t* base, unsigned int val, unsigned char numbit)
{ 
    unsigned int mask = (1 << numbit);
    unsigned int irqMask = base->irqMask;
    
    if(val)
        base->irqMask = irqMask | mask;
    else
        base->irqMask = irqMask & (~mask);
} 
        
__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_write_mask_irqMask(MicoGPIO_t* base, unsigned int val, unsigned int mask)
{ 
    unsigned int irqMask = base->irqMask;
        
    base->irqMask = (irqMask & (~mask)) | (val & mask);
} 
        
 __INLINE__ unsigned int __ALWAYS_INLINE__ EE_hal_gpio_read_edgeCapture(MicoGPIO_t* base)
{ 
    return base->edgeCapture;
} 

__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_write_edgeCapture(MicoGPIO_t* base, unsigned int val)
{ 
    base->edgeCapture = val;
} 
__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_write_bit_edgeCapture(MicoGPIO_t* base, unsigned int val, unsigned char numbit)
{ 
    unsigned int mask = (1 << numbit);
    unsigned int edgeCapture = base->edgeCapture;
        
    if(val)
        base->edgeCapture = edgeCapture | mask;
    else
        base->edgeCapture = edgeCapture & (~mask);
} 

__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_write_mask_edgeCapture(MicoGPIO_t *base, unsigned int val, unsigned int mask)
{ 
    unsigned int edgeCapture = base->edgeCapture;
        
    base->edgeCapture = (edgeCapture & (~mask)) | (val & mask);
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_enable_IRQ(EE_gpio_st *gpio_sp, int irq_mode, unsigned int ch)
{
    if(ch!=0 && irq_mode!=0) {
        EE_mico32_register_ISR(gpio_sp->irqf, EE_gpio_common_handler);   
        mico32_enable_irq(gpio_sp->irqf);
    } else {
        mico32_disable_irq(gpio_sp->irqf);
    }
    EE_hal_gpio_write_irqMask(gpio_sp->base, ch);
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_disable_IRQ(EE_gpio_st *gpio_sp)
{
    mico32_disable_irq(gpio_sp->irqf);
    EE_hal_gpio_write_irqMask(gpio_sp->base, 0);
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_set_IRQ_callback(EE_gpio_st* gpio_sp, EE_ISR_callback cbk)
{
    gpio_sp->cbk = cbk;
}


#ifdef EE_GPIO1_NAME_UC
DECLARE_STRUCT_GPIO(EE_GPIO1_NAME_UC, EE_GPIO1_NAME_LC)
DECLARE_FUNC_GPIO(EE_GPIO1_NAME_UC, EE_GPIO1_NAME_LC)
#endif

#ifdef EE_GPIO2_NAME_UC
DECLARE_STRUCT_GPIO(EE_GPIO2_NAME_UC, EE_GPIO2_NAME_LC)
DECLARE_FUNC_GPIO(EE_GPIO2_NAME_UC, EE_GPIO2_NAME_LC)
#endif

#ifdef EE_GPIO3_NAME_UC
DECLARE_STRUCT_GPIO(EE_GPIO3_NAME_UC, EE_GPIO3_NAME_LC)
DECLARE_FUNC_GPIO(EE_GPIO3_NAME_UC, EE_GPIO3_NAME_LC)
#endif

#ifdef EE_GPIO4_NAME_UC
DECLARE_STRUCT_GPIO(EE_GPIO4_NAME_UC, EE_GPIO4_NAME_LC)
DECLARE_FUNC_GPIO(EE_GPIO4_NAME_UC, EE_GPIO4_NAME_LC)
#endif

/* Return the GPIO structure for the componente associated with the given IRQ
 * level */
__DECLARE_INLINE__ EE_gpio_st *EE_get_gpio_st_from_level(int level);
#ifndef EE_GPIO2_NAME_UC
/* If there is only one component of this kind, no test is done */
__INLINE__ EE_gpio_st * __ALWAYS_INLINE__ EE_get_gpio_st_from_level(int level)
{
    return & EE_ST_NAME(EE_GPIO1_NAME_LC);
}
#elif ! defined(EE_GPIO3_NAME_UC)
__INLINE__ EE_gpio_st * __ALWAYS_INLINE__ EE_get_gpio_st_from_level(int level)
{
    if (level == EE_IRQ_NAME(EE_GPIO1_NAME_UC))
        return & EE_ST_NAME(EE_GPIO1_NAME_LC);
    else
        return & EE_ST_NAME(EE_GPIO2_NAME_LC);
}
#elif ! defined(EE_GPIO4_NAME_UC)
__INLINE__ EE_gpio_st * __ALWAYS_INLINE__ EE_get_gpio_st_from_level(int level)
{
    if (level == EE_IRQ_NAME(EE_GPIO1_NAME_UC))
        return & EE_ST_NAME(EE_GPIO1_NAME_LC);
    else if(level == EE_IRQ_NAME(EE_GPIO2_NAME_UC))
        return & EE_ST_NAME(EE_GPIO2_NAME_LC);
    else
        return & EE_ST_NAME(EE_GPIO3_NAME_LC);
}
#else // #ifndef EE_GPIO4_NAME_UC
__INLINE__ EE_gpio_st * __ALWAYS_INLINE__ EE_get_gpio_st_from_level(int level)
{
    if (level == EE_IRQ_NAME(EE_GPIO1_NAME_UC))
        return & EE_ST_NAME(EE_GPIO1_NAME_LC);
    else if(level == EE_IRQ_NAME(EE_GPIO2_NAME_UC))
        return & EE_ST_NAME(EE_GPIO2_NAME_LC);
    else if(level == EE_IRQ_NAME(EE_GPIO3_NAME_UC))
        return & EE_ST_NAME(EE_GPIO3_NAME_LC);
    else
        return & EE_ST_NAME(EE_GPIO4_NAME_LC);
}
#endif /* #ifndef EE_GPIO_NAME2_UC */

#endif // #ifdef __USE_GPIO__

#endif //__INCLUDE_EEMCUMICO32_GPIO_H__
