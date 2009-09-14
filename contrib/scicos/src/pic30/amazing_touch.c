
// 07-06-2009 Francesco Prosperi - Retis Lab - SSSA

#include <ee.h>
#include "touch.h"
#include "mcu/microchip_dspic/inc/ee_uart.h"
#include <machine.h>
#include <scicos_block4.h>

#define ASCII_X	88
#define ASCII_Y	89

static void out(scicos_block *block)
{
	EE_UINT8 axis = block->ipar[0];
	EE_UINT16 data;

	float *y = block->outptr[0];

	if(axis != ASCII_X && axis != ASCII_Y) 
		return;
	if(axis == ASCII_X){
		touch_poll_u_position(TOUCH_X_AXIS,&data);
	} else {
		touch_poll_u_position(TOUCH_Y_AXIS,&data);
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
			break;
		case Ending:
			break;
	}
}
