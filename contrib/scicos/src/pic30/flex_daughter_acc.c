/* ###*B*###
 * Copyright (C) Roberto Bucher (SUPSI- Lugano)
 *               Simone Mannori (Scilab / INRIA / DIGITEO)
 *
 * Copyright (C) METALAU Project (INRIA)
 * ###*E*### */
 
 
//** 9 Feb 2008 : Revision notes by Simone Mannori 
//**

#include <machine.h>
#include <scicos_block4.h>

#include <ee.h>

/* Accelerometer bit allocation:
X axis:	AN16-RC1 
Y axis:	AN17-RC2 
Z axis:	AN18-RC3 
G Select1:	RF12
G Select2:	RF13
Sleep:	RD3
*/

static void init(scicos_block *block)
{
	EE_accelerometer_init();
}

static void inout(scicos_block *block)
{
	float adcdata;
	float * y = block->outptr[0];
	
	int axis = block->ipar[0];

	if ( (axis < 1) || (axis > 3) )
		return; //** return if outside the allowed range

	switch (axis) {
		case 1:
			adcdata = EE_accelerometer_getx();
			y[0] = adcdata;
			break;
		case 2:
			adcdata = EE_accelerometer_gety();
			y[0] = adcdata;
			break;
		case 3:
			adcdata = EE_accelerometer_getz();
			y[0] = adcdata;
	}
}

static void end(scicos_block *block)
{
}

void flex_daughter_acc(scicos_block *block,int flag)
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
