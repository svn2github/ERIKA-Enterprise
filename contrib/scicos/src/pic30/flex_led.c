/* ###*B*###
 * Copyright (C) Roberto Bucher (SUPSI- Lugano)
 *               Simone Mannori (Scilab / INRIA / DIGITEO)
 *
 * Copyright (C) METALAU Project (INRIA)
 * ###*E*### */
 
 
#include <machine.h>
#include <scicos_block4.h>

#include <ee.h>

static void init(scicos_block *block)
{
	EE_leds_init();
}

static void inout(scicos_block *block)
{
  float * u = block->inptr[0];
	if (u[0] > 0.5)
		EE_led_sys_on(); 
	else
		EE_led_sys_off(); 
}

static void end(scicos_block *block)
{
}

void flex_led(scicos_block *block,int flag)
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
