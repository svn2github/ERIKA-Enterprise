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

static void init(scicos_block *block)
{
	unsigned int serial_port = block->ipar[0];
	unsigned int baudrate = block->ipar[1];
	
	if ((serial_port < 1) || (serial_port > 2))
	  return;
	if ((baudrate != 9600) || (baudrate != 19200) || (baudrate != 57600) || (baudrate != 115200))
		return;
	
	EE_uart_init(serial_port-1,baudrate,EE_UART_BIT8_NO|EE_UART_BIT_STOP_1|EE_UART_CTRL_SIMPLE,0);

}

static void inout(scicos_block *block)
{
  float * y = block->outptr[0];
	EE_UINT8 serial_data;

	unsigned int serial_port= block->ipar[0];
	unsigned int baudrate = block->ipar[1];
	
	if ((serial_port < 1) || (serial_port > 2))
		return;
	if ((baudrate != 9600) || (baudrate != 19200) || (baudrate != 57600) || (baudrate != 115200))
		return;
	
	EE_uart_read_byte(serial_port-1,&serial_data);
	y[0] = (float)serial_data;

}

static void end(scicos_block *block)
{
	unsigned int serial_port= block->ipar[0];
	unsigned int baudrate = block->ipar[1];
	
	if ((serial_port < 1) || (serial_port > 8))
		return;

	EE_uart_close(serial_port-1);


}

void flex_serial_send(scicos_block *block,int flag)
{
	switch (flag) {
		case 1:	/* set output */
			inout(block);
			break;

		case 2:	/* get input */
			inout(block);
			break;
		
		case 4:	/* initialisation */
			init(block);
			break;
		
		case 5:	/* ending */
	        end(block);
			break;
	}
}
 
