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
* @file     spi_flash_mico32.c
* @brief    SPI flash driver. Mico32 functions.
* @author   Bernardo Dal Seno
* @author   Dario Di Stefano
* @date     2010
*/ 

#include <ee.h>
#include "ee_spi_flash.h"

void short_spi_write(unsigned ctrl_base, EE_UINT32 data, EE_UREG len)
{
    struct spi_flash_cmd * const cmd_ctrl =
        (struct spi_flash_cmd *)(ctrl_base + 0x40);
    cmd_ctrl->cmd0 = data << (8 * (4 - len));
    cmd_ctrl->cmd_len = len;
    cmd_ctrl->ret_len = 0;
    cmd_ctrl->do_cmd = 1;
}

void long_spi_write(unsigned ctrl_base, EE_UINT32 data1, EE_UINT32 data2, EE_UREG len)
{
    struct spi_flash_cmd * const cmd_ctrl =
        (struct spi_flash_cmd *)(ctrl_base + 0x40);
    cmd_ctrl->cmd0 = data2;
    cmd_ctrl->cmd1 = data1;
    cmd_ctrl->cmd_len = len;
    cmd_ctrl->ret_len = 0;
    cmd_ctrl->do_cmd = 1;
}




