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
		case 1:	/* set output */
		case 2:	/* get input */
			EE_uart_read_byte(serial_port-1,&serial_data);
			y[0] = (float)serial_data;
			break;
		
		case 4:	/* initialisation */
			EE_uart_init(serial_port-1,baudrate,EE_UART_BIT8_NO|EE_UART_BIT_STOP_1|EE_UART_CTRL_SIMPLE,0);
			break;
		
		case 5:	/* ending */
			EE_uart_close(serial_port-1);
			break;
	}
}
 
