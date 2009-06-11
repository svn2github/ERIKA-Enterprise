/* ###*B*###
 * Copyright (C) Roberto Bucher (SUPSI- Lugano)
 *               Simone Mannori (Scilab / INRIA / DIGITEO)
 *
 * Copyright (C) METALAU Project (INRIA)
 * ###*E*### */
 
 
//** 9 Feb 2008 : Revision notes by Simone Mannori 

#include <machine.h>
#include <scicos_block4.h>

#include <ee.h>

/* Encoder bit allocation 
QEA	RB4
QEB	RB5
*/

static void init(scicos_block *block)
{
	EE_encoder_init(); //** encoder initialization 
}

static void inout(scicos_block *block)
{
	float data = 0.0     ;
	int int_data_enc = 0 ; 
	float * y = block->outptr[0];
	
	//** the encoder return a float value coded in signed pulse units
	//** this means that the dspic register MUST be read as "int" 
	//** in order to keep the signed comp. 2' bynary rapresentation.
	//** the scaling to degree/radian/centesimal/mm will be done 
	//** in a later release.

	int_data_enc = EE_encoder_get_ticks();
	data = (float) (int_data_enc) ; 
	y[0] = data; //** pass the variable to Scicos 
}

static void end(scicos_block *block)
{
}

void flex_daughter_encoder(scicos_block *block,int flag)
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
