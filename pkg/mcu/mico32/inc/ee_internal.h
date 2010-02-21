/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
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

#include "mcu/mico32/inc/ee_mcu.h"

#ifndef __INCLUDE_MCUMICO32_INTERNAL_H__
#define __INCLUDE_MCUMICO32_INTERNAL_H__


/*************************************************************************
 Timers
 *************************************************************************/

/*
 * FRSH
 */

#if defined(__FRSH__)

/* This function set the capacity timer to raise in t ticks. */
void EE_hal_set_budget_timer(EE_STIME t);

__INLINE__ void __ALWAYS_INLINE__ EE_hal_stop_budget_timer(void)
{
  // TODO!!!
}

#endif  /* __FRSH__ */


/* Return the Timer structure for the componente associated with the given IRQ
 * level */
__DECLARE_INLINE__ EE_timer_st *EE_get_timer_st_from_level(int level);


#ifndef EE_TIMER_NAME2_UC
/* If there is only one component of this kind, no test is done */
__INLINE__ EE_timer_st * __ALWAYS_INLINE__ EE_get_timer_st_from_level(int level)
{
    return EE_TIMER_ST_NAME(EE_TIMER_NAME1_LC);
}
#else /* #ifndef EE_TIMER_NAME2_UC */
__INLINE__ EE_timer_st * __ALWAYS_INLINE__ EE_get_timer_st_from_level(int level)
{
    switch (level) {
    default:
        return EE_TIMER_ST_NAME(EE_TIMER_NAME1_LC);
#ifdef EE_TIMER_NAME2_UC
    case EE_TIMER_IRQ_NAME(EE_TIMER_NAME2_UC):
        return EE_TIMER_ST_NAME(EE_TIMER_NAME2_LC);
#endif
#ifdef EE_TIMER_NAME3_UC
    case EE_TIMER_IRQ_NAME(EE_TIMER_NAME3_UC):
        return EE_TIMER_ST_NAME(EE_TIMER_NAME3_LC);
#endif
#ifdef EE_TIMER_NAME4_UC
    case EE_TIMER_IRQ_NAME(EE_TIMER_NAME4_UC):
        return EE_TIMER_ST_NAME(EE_TIMER_NAME4_LC);
#endif
    }
}
#endif /* #ifndef EE_TIMER_NAME2_UC */



/*************************************************************************
 Uart
 *************************************************************************/

/* Return the Uart structure for the componente associated with the given IRQ
 * level */
__DECLARE_INLINE__ EE_uart_st *EE_get_uart_st_from_level(int level);


#ifndef EE_UART_NAME2_UC
/* If there is only one component of this kind, no test is done */
__INLINE__ EE_uart_st * __ALWAYS_INLINE__ EE_get_uart_st_from_level(int level)
{
    return EE_UART_ST_NAME(EE_UART_NAME1_LC);
}
#else /* #ifndef EE_UART_NAME2_UC */
__INLINE__ EE_uart_st * __ALWAYS_INLINE__ EE_get_uart_st_from_level(int level)
{
    if (level == EE_UART_IRQ_NAME(EE_UART_NAME1_UC))
        return EE_UART_ST_NAME(EE_UART_NAME1_LC);
    else
        return EE_UART_ST_NAME(EE_UART_NAME2_LC);
}
#endif /* #ifndef EE_UART_NAME2_UC */



/*************************************************************************
 I2C
 *************************************************************************/

/* Return the I2C structure for the componente associated with the given IRQ
 * level */
__DECLARE_INLINE__ EE_i2c_st *EE_get_i2c_st_from_level(int level);


#ifndef EE_I2C_NAME2_UC
/* If there is only one component of this kind, no test is done */
__INLINE__ EE_i2c_st * __ALWAYS_INLINE__ EE_get_i2c_st_from_level(int level)
{
    return EE_I2C_ST_NAME(EE_I2C_NAME1_LC);
}
#else /* #ifndef EE_I2C_NAME2_UC */
__INLINE__ EE_i2c_st * __ALWAYS_INLINE__ EE_get_i2c_st_from_level(int level)
{
    if (level == EE_I2C_IRQ_NAME(EE_I2C_NAME1_UC))
        return EE_I2C_ST_NAME(EE_I2C_NAME1_LC);
    else
        return EE_I2C_ST_NAME(EE_I2C_NAME2_LC);
}
#endif /* #ifndef EE_I2C_NAME2_UC */


#endif /* __INCLUDE_MCUMICO32_INTERNAL_H__ */
