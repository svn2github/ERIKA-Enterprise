/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2006-2010  Evidence Srl
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
	@file flex_serial_send.c
	@brief www.scicos.org, www.scicoslab.org
	@author Roberto Bucher, SUPSI- Lugano
	@author Simone Mannori, ScicosLab developer
	@date 2006-2010
*/
 
#include <machine.h>
#include <scicos_block4.h>

#include <ee.h>
#include "mcu/microchip_dspic/inc/ee_uart.h"

/* TODO: the initialization check should be done among the send and receive 
         blocks, so that a global variable is required for all of them
*/
static EE_UINT8 serial_initialized = 0;

void flex_serial_send(scicos_block *block,int flag)
{
	EE_UINT8 serial_port = block->ipar[0];
	EE_UINT32 baudrate = block->rpar[0];
	float * u = block->inptr[0];

	if ((serial_port < 1) || (serial_port > 2))
	  return;
	if ((baudrate != 9600) && (baudrate != 19200) && (baudrate != 57600) && (baudrate != 115200))
		return;

	switch(flag) {
		case OutputUpdate:	/* set output */
			EE_uart_write_byte(serial_port-1,(EE_UINT8)u[0]);
			break;

		case StateUpdate:	/* get input */
			break;
		
		case Initialization:	/* initialisation */
			if (serial_initialized)
				break;
			EE_uart_init(serial_port-1,baudrate,EE_UART_BIT8_NO|EE_UART_BIT_STOP_1|EE_UART_CTRL_SIMPLE,0);
			serial_initialized = 1;
			break;
		
		case Ending:	/* ending */
			EE_uart_close(serial_port-1);
			break;
	}
}
 
