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
 
/** 
* @file     spi_flash_generic.h
* @brief    SPI flash driver. Generic functions.
* @author   Bernardo Dal Seno
* @author   Dario Di Stefano
* @date     2010
*/ 

#ifndef SPI_FLASH_GENERIC_H
#define SPI_FLASH_GENERIC_H

#ifdef __LM32__
#include "spi_flash_mico32.h"
#endif

/* ========================= SPI interface ========================= */

/* Flash generic SPI commands */

void short_spi_write(unsigned ctrl_base, EE_UINT32 data, EE_UREG len);
void long_spi_write(unsigned ctrl_base, EE_UINT32 data1, EE_UINT32 data2, EE_UREG len);

__INLINE__ void __ALWAYS_INLINE__ spi_write(unsigned ctrl_base, const void *data, unsigned len)
{
    const EE_UINT8 *buf = data;
    EE_UINT32 data1, data2;
    unsigned l;
    data1 = buf[0];
    for (l = 1; l < len && l < 4; ++l)
        data1 = (data1 << 8) | buf[l];
    if (len > 4) {
        data2 = buf[4];
        for (l = 5; l < len && l < 8; ++l)
            data2 = (data2 << 8) | buf[l];
        long_spi_write(ctrl_base, data1, data2, len);
    } else {
        short_spi_write(ctrl_base, data1, len);
    }
}


/* ========================= Flash commands ========================= */

extern const EE_UINT8 cmd_e_w_sr[1];  // = { SPI_FLASH_CMD_EN_WR_SR };
extern const EE_UINT8 cmd_w_en[1];    // = { SPI_FLASH_CMD_WRITE_EN };
extern const EE_UINT8 cmd_w_dis[1];   // = { SPI_FLASH_CMD_WRITE_DIS };
extern const EE_UINT8 cmd_ch_erase[1];// = { SPI_FLASH_CMD_CHIP_ERASE };

__INLINE__ int __ALWAYS_INLINE__ spi_flash_is_busy(EE_UINT8 status)
{
    return (status & SPI_FLASH_BUSY_MASK) ? 1 : 0;
}


__INLINE__ int __ALWAYS_INLINE__ spi_flash_is_protected(EE_UINT8 status)
{
    return (status & SPI_FLASH_BP_MASK) ? 1 : 0;
}


__INLINE__ EE_UINT8 __ALWAYS_INLINE__ spi_flash_unprotected_status(EE_UINT8 status)
{
    return status & ~(SPI_FLASH_BP_MASK|SPI_FLASH_BPL_MASK);
}


__INLINE__ EE_UINT8 __ALWAYS_INLINE__ spi_flash_get_status_reg(unsigned ctrl_base)
{
    return SPI_CMD_STATUS_READ(ctrl_base);
}


__INLINE__ void __ALWAYS_INLINE__ spi_flash_wait_until_ready(unsigned ctrl_base)
{
    EE_UINT8 s;
    //debug_set_leds(STATE_LEDS_WAITING_FLASH);
    do {
        s = spi_flash_get_status_reg(ctrl_base);
    } while(spi_flash_is_busy(s));
}


__INLINE__ void __ALWAYS_INLINE__ spi_flash_write_status(unsigned ctrl_base, EE_UINT8 status)
{
    EE_UINT8 cmd_wr_sr[2] = { SPI_FLASH_CMD_WR_SR };
    cmd_wr_sr[1] = status;
    spi_write(ctrl_base, cmd_wr_sr, sizeof(cmd_wr_sr));
}

__INLINE__ void __ALWAYS_INLINE__ spi_flash_maybe_unprotect(unsigned ctrl_base)
{
    EE_UINT8 sr = spi_flash_get_status_reg(ctrl_base);
    if (spi_flash_is_protected(sr)) {
        spi_write(ctrl_base, cmd_e_w_sr, sizeof(cmd_e_w_sr));
        spi_flash_write_status(ctrl_base, spi_flash_unprotected_status(sr));
    }
}


__INLINE__ void __ALWAYS_INLINE__ spi_flash_write_enable(unsigned ctrl_base)
{
    spi_flash_maybe_unprotect(ctrl_base);
    spi_write(ctrl_base, cmd_w_en, sizeof(cmd_w_en));
}


__INLINE__ void __ALWAYS_INLINE__ spi_flash_write_disable(unsigned ctrl_base)
{
    spi_write(ctrl_base, cmd_w_dis, sizeof(cmd_w_dis));
}


#ifndef spi_flash_write_buffer
//#warning "spi_flash_write_buffer VOID DEFINED!"
__INLINE__ void __ALWAYS_INLINE__ spi_flash_write_buffer(unsigned ctrl_base, EE_UINT32 addr,
    const void *data, EE_UREG len)
{
}
#define spi_flash_write_buffer generic_spi_flash_write_buffer
#else
//#warning "spi_flash_write_buffer DEFINED!"
void spi_flash_write_buffer(unsigned ctrl_base, EE_UINT32 addr,
    const void *data, EE_UREG len);
#endif


__INLINE__ void __ALWAYS_INLINE__ spi_flash_erase_chip(unsigned ctrl_base)
{
    spi_flash_write_enable(ctrl_base);
    //debug_set_leds(STATE_LEDS_ERASING_CHIP);
    spi_write(ctrl_base, cmd_ch_erase, sizeof(cmd_ch_erase));
    spi_flash_wait_until_ready(ctrl_base);
}

#endif /* SPI_FLASH_GENERIC_H */
