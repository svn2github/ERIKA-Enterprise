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

/* NTC bit allocation: AN12-RB12 */

static void init(scicos_block *block)
{
	EE_analogsensors_init();
}

static void inout(scicos_block *block)
{
	float adcdata;
	float * y = block->outptr[0];
	
	//** Returns the temparature in Celsius degree 
	//** using plain vanilla floating point representation 
	adcdata = EE_analog_get_temperature();

	y[0] = adcdata;
}

static void end(scicos_block *block)
{
}

void flex_daughter_therm(scicos_block *block,int flag)
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
