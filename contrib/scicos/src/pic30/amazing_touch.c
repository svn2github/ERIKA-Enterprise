
// 07-06-2009 Francesco Prosperi - Retis Lab - SSSA

#include <ee.h>
#include "touch.h"
#include "mcu/microchip_dspic/inc/ee_uart.h"
#include <machine.h>
#include <scicos_block4.h>

#define ASCII_X	88
#define ASCII_Y	89

static unsigned char serial_initialized = 0;

void init(scicos_block *block)
{
	if(!serial_initialized)
	{	
		EE_uart_init(EE_UART_PORT_2,115200,EE_UART_BIT8_NO|EE_UART_BIT_STOP_1|EE_UART_CTRL_SIMPLE,0);
		serial_initialized = 1;
	}
}

void out(scicos_block *block)
{
/*	EE_UINT8 axis = block->ipar[0];
	EE_INT16 data;

	float *y = block->outptr[0];

	if(axis != ASCII_X && axis != ASCII_Y) 
		return;
	if(axis == ASCII_X) touch_poll_s_position(TOUCH_X_AXIS,&data);
	else touch_poll_s_position(TOUCH_Y_AXIS,&data);

	y[0] = (float)data; */

	EE_UINT8 axis = block->ipar[0];
	EE_UINT16 data;

	float *y = block->outptr[0];

	if(axis != ASCII_X && axis != ASCII_Y) 
		for(;;);
	if(axis == ASCII_X){
		touch_poll_u_position(TOUCH_X_AXIS,&data);
		EE_uart_write_byte(EE_UART_PORT_2,'<');
	} else {
		touch_poll_u_position(TOUCH_Y_AXIS,&data);
	}

	EE_uart_write_byte(EE_UART_PORT_2,(EE_UINT8)data);

	if(axis == ASCII_Y){
		EE_uart_write_byte(EE_UART_PORT_2,'>');
	}	

	y[0] = (float)data; 
}

void amazing_touch(scicos_block *block,int flag)
{
	switch (flag) {
		case OutputUpdate:
			out(block);
			break;
		case StateUpdate:
			break;
		case Initialization:
			init(block);
			break;
		case Ending:
			break;
	}
}
