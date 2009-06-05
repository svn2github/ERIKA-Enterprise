/* ###*B*###
 * Copyright (C) Roberto Bucher (SUPSI- Lugano)
 *               Simone Mannori (Scilab / INRIA / DIGITEO)
 *
 * Copyright (C) METALAU Project (INRIA)
 * ###*E*### */
 
 
//** 9 Feb 2008 : Revision notes by Simone Mannori 
//**

//*** da rivedere 

#include <machine.h>
#include <scicos_block4.h>

#include <ee.h>

/* Dac bit allocation:
SCL	RG2
SDA	RG3
*/

static void init(scicos_block *block)
{
	EE_dac_init();
}

static void inout(scicos_block *block)
{
	/* Get the PWM number [1,2]     */
	int pin = block->ipar[0];

	/* Get duty cycle from Scicos block */
	float * duty = block->inptr[0];
	
	if ((pin < 1) || (pin > 2))
		return; //** refuse not supported PWM

	//** non ci siamo : questi sono dei veri dac che producono VOLT, quindi 
	//** l'ingresso DEVE essere interpretato in VOLT e i VOLT devono essere 
	//** VOLT VERI e non noccioline ......
	EE_dac_fast_write( (unsigned int)(duty[0]*4095), pin-1, 0 );
}

static void end(scicos_block *block)
{
	/* Get the PWM number [1,2]     */
	int pin = block->ipar[0];

	if ((pin < 1) || (pin > 2))
		return; //** refuse not supported PWM

	EE_dac_fast_write( 0, pin-1, 0 );
}

void flex_dmb_dac(scicos_block *block,int flag)
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
