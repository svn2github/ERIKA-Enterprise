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

static void init(scicos_block *block)
{
	EE_buzzer_init();
}

static void inout(scicos_block *block)
{
	/* Get duty cycle from Scicos block */
	float * freq = block->inptr[0];
	
	//** Set the frequency in Hz 
	EE_buzzer_set_freq( freq[0] ); 
}

static void end(scicos_block *block)
{
	EE_buzzer_close();
}

void flex_dmb_buzzer(scicos_block *block,int flag)
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
