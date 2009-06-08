/* ###*B*###
 * Copyright (C) Roberto Bucher (SUPSI- Lugano)
 *               Simone Mannori (Scilab / INRIA / DIGITEO)
 *
 * Copyright (C) METALAU Project (INRIA)
 * ###*E*### */
 
 
#include <machine.h>
#include <scicos_block4.h>

#include <ee.h>
#include "mcu/microchip_dspic/inc/ee_uart.h"

/* TODO: the initialization check should be done among the send and receive 
         blocks, so that a global variable is required for all of them
*/
static EE_UINT8 serial_initialized = 0;

void flex_serial_receive(scicos_block *block,int flag)
{
	EE_UINT8 serial_port= block->ipar[0];
	EE_UINT32 baudrate = block->rpar[0];
	EE_UINT8 serial_data;

  float *y = block->outptr[0];

	if ((serial_port < 1) || (serial_port > 2))
		return;
	if ((baudrate != 9600) && (baudrate != 19200) && (baudrate != 57600) && (baudrate != 115200))
		return;

	switch (flag) {

		case OutputUpdate:
      break;

    case StateUpdate: 
			EE_uart_read_byte(serial_port-1,&serial_data);
			y[0] = (float)serial_data;
			break;
		
		case 4:	/* initialisation */
			if (serial_initialized)
				break;
			EE_uart_init(serial_port-1,baudrate,EE_UART_BIT8_NO|EE_UART_BIT_STOP_1|EE_UART_CTRL_SIMPLE,0);
			serial_initialized = 1;
			break;
		
		case 5:	/* ending */
			EE_uart_close(serial_port-1);
			break;
	}
}
 
