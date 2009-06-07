// 07-06-2009 Francesco Prosperi - Retis Lab - SSSA

#include <machine.h>
#include <scicos_block4.h>

#include <ee.h>

#define ASCII_X	88
#define ASCII_Y	89

EE_UINT8 x_already_initialized = 0;
EE_UINT8 y_already_initialized = 0;
EE_UINT8 touch_initialized = 0;

static void init(scicos_block *block)
{
	EE_UINT8 axis = block->ipar[0];
	EE_UINT16 range = block->ipar[1];
	if(axis != ASCII_X && axis != ASCII_Y) 
		return;
	
	touch_set_dimension(axis-ASCII_X,range);
	
	if(axis == ASCII_X)
		x_already_initialized = 1;
	else if(axis == ASCII_Y)
		y_already_initialized = 1;
	
	if(x_already_initialized && y_already_initialized)
	{
		touch_calibrate();
		touch_start();
		touch_initialized = 1;
	}
}

static void inout(scicos_block *block)
{
	EE_UINT8 axis;
	float *y;

	if(!touch_initialized)
		return;
	
	if(axis != ASCII_X && axis != ASCII_Y) 
		return;
	
	axis = block->ipar[0];
	float *y = block->outptr[0];
	
	y[0] = (float)touch_get_position(axis-ASCII_X);
	
}

static void end(scicos_block *block)
{
}

void flex_touchin(scicos_block *block,int flag)
{
 switch (flag) {
    case OutputUpdate:  /* set output */
      inout(block);
      break;

    case StateUpdate: /* get input */
      break;

    case Initialization:  /* initialisation */
      init(block);
      break;

    case Ending:  /* ending */
      end(block);
      break;
  }
}
