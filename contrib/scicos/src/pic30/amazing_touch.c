
// 07-06-2009 Francesco Prosperi - Retis Lab - SSSA

#include <ee.h>
#include "touch.h"
#include <machine.h>
#include <scicos_block4.h>

#define ASCII_X	88
#define ASCII_Y	89

static void init(scicos_block *block)
{
	EE_UINT8 axis = block->ipar[0];

	if(axis != ASCII_X && axis != ASCII_Y) 
		return;

	#if (defined __USE_LEDS__) && (defined __USE_MOTIONBOARD__)
	EE_daughter_leds_init();
	#endif
	}
}

static void in(scicos_block *block)
{
	EE_UINT8 axis = block->ipar[0];
	EE_INT16 data;

	float *y = block->outptr[0];

	if(axis != ASCII_X && axis != ASCII_Y) 
		return;
		
	touch_poll_s_position_s(axis-ASCII_X),&data);

	y[0] = (float)data;
}

void amazing_touch(scicos_block *block,int flag)
{
	switch (flag) {
		case OutputUpdate:
			break;
		case StateUpdate:
			in(block);
			break;
		case Initialization:
			init(block);
			break;
		case Ending:
			break;
	}
}
