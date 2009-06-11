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

/* ADCIN bit allocation 

Scicos	Function	dsPIC	Flex Connectors
Pin=1	 ADCIN1	RC4	CON8.P9	
Pin=2	 ADCIN2	RE8	CON8.P18	
Pin=3	 ADCIN3	RE9	CON8.P20	
*/

static void init(scicos_block *block)
{
	EE_adcin_init();
}

static void inout(scicos_block *block)
{
	float adcdata;
	float * y = block->outptr[0];
	
	int pin = block->ipar[0];

	if ( (pin < 1) || (pin > 3) ) { //** only the first three ADC channels are supported
		y[0] = -1.0 ;  
		return;
	}

	adcdata = EE_adcin_get_volt(pin);
	y[0] = adcdata ; 
}

static void end(scicos_block *block)
{
}

void flex_daughter_adc(scicos_block *block,int flag)
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
