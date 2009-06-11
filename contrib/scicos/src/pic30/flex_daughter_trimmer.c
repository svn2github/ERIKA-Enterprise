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

/* Trimmer bit allocation: AN15-RB15 */

static void init(scicos_block *block)
{
	EE_trimmer_init();
}

static void inout(scicos_block *block)
{
	float adcdata;
	float * y = block->outptr[0];
	
	adcdata = EE_trimmer_get_volt();

	y[0] = adcdata;
}

static void end(scicos_block *block)
{
}

void flex_daughter_trimmer(scicos_block *block,int flag)
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
