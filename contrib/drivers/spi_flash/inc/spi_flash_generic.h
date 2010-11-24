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

/* ========================= Flash commands ========================= */

/**
 * Function to write up to 4 bytes.
 */
__INLINE__ void __ALWAYS_INLINE__ spi_short_write(unsigned id, EE_UINT32 data, EE_UREG len)
{
    hal_spi_short_write(id, data, len);
}

/**
 * Function to write up to 8 bytes.
 */
__INLINE__ void __ALWAYS_INLINE__ spi_long_write(unsigned id, EE_UINT32 data1, EE_UINT32 data2, EE_UREG len)
{
    hal_spi_long_write(id, data1, data2, len);
}

/**
 * Function to write an array of bytes.
 */
__INLINE__ void __ALWAYS_INLINE__ spi_write(unsigned id, const void *data, unsigned len)
{
    hal_spi_write(id, data, len);
}

/**
 * Function to read the busy bit of the status register of the SPI-Flash memory
 */
__INLINE__ int __ALWAYS_INLINE__ spi_flash_is_busy(EE_UINT8 status)
{
    return (status & SPI_FLASH_BUSY_MASK) ? 1 : 0;
}

/**
 * Function to read the protection bit of the status register of the SPI-Flash memory
 */
__INLINE__ int __ALWAYS_INLINE__ spi_flash_is_protected(EE_UINT8 status)
{
    return (status & SPI_FLASH_BP_MASK) ? 1 : 0;
}

/**
 * Function to return the unprotected status of the SPI-Flash memory
 */
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ spi_flash_unprotected_status(EE_UINT8 status)
{
    return status & ~(SPI_FLASH_BP_MASK|SPI_FLASH_BPL_MASK);
}

/**
 * Function to get the status register of the SPI-Flash memory
 */
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ spi_flash_get_status_reg(unsigned id)
{
    return SPI_CMD_STATUS_READ(id);
}

/**
 * Function to wait until SPI-Flash memory is ready
 */
__INLINE__ void __ALWAYS_INLINE__ spi_flash_wait_until_ready(unsigned id)
{
    EE_UINT8 s;
    do {
        s = spi_flash_get_status_reg(id);
    } while(spi_flash_is_busy(s));
}

/**
 * Function to write the status register of the SPI-Flash memory
 */
__INLINE__ void __ALWAYS_INLINE__ spi_flash_write_status(unsigned id, EE_UINT8 status)
{
    EE_UINT32 len = sizeof(cmd_wr_sr);
    cmd_wr_sr[len-1] = status;
    spi_write(id, cmd_wr_sr, len);
}

/**
 * Function to change the status register of the SPI-Flash memory
 * to unprotected
 */
__INLINE__ void __ALWAYS_INLINE__ spi_flash_maybe_unprotect(unsigned id)
{
    EE_UINT8 sr = spi_flash_get_status_reg(id);
    if (spi_flash_is_protected(sr)) {
        spi_write(id, cmd_e_w_sr, sizeof(cmd_e_w_sr));
        spi_flash_write_status(id, spi_flash_unprotected_status(sr));
    }
}

/**
 * Function to enable write
 */
__INLINE__ void __ALWAYS_INLINE__ spi_flash_write_enable(unsigned id)
{
    spi_flash_maybe_unprotect(id);
    spi_write(id, cmd_w_en, sizeof(cmd_w_en));
}

/**
 * Function to disable write
 */
__INLINE__ void __ALWAYS_INLINE__ spi_flash_write_disable(unsigned id)
{
    spi_write(id, cmd_w_dis, sizeof(cmd_w_dis));
}

/**
 * Function to erase chip (all bytes to 0xFF)
 */
__INLINE__ void __ALWAYS_INLINE__ spi_flash_erase_chip(unsigned id)
{
    spi_flash_write_enable(id);
    spi_write(id, cmd_ch_erase, sizeof(cmd_ch_erase));
    spi_flash_wait_until_ready(id);
}

/**
 * Function to erase a sector (4 KB)
 */
__INLINE__ void __ALWAYS_INLINE__ spi_flash_erase_sector(unsigned id, EE_UINT32 addr)
{
    spi_flash_write_enable(id);
    hal_spi_flash_erase_sector(id, addr);
    spi_flash_wait_until_ready(id);
}

/**
 * Function to erase a block (32 KB)
 */
__INLINE__ void __ALWAYS_INLINE__ spi_flash_erase_block(unsigned id, EE_UINT32 addr)
{
    spi_flash_write_enable(id);
    hal_spi_flash_block_sector(id, addr);
    spi_flash_wait_until_ready(id);
}

#ifndef spi_flash_write_buffer
#error "SPI-Flash error: spi_flash_write_buffer not defined!"
#else
void spi_flash_write_buffer(unsigned id, EE_UINT32 addr,
    const void *data, EE_UREG len);
#endif




#endif /* SPI_FLASH_GENERIC_H */
