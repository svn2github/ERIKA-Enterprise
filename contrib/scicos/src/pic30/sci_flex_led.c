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
		case 1:	/* set output */
		case 2:	/* get input */
			inout(block);
			break;
		case 5:	/* ending */
			end(block);
			break;
		case 4:	/* initialisation */
			init(block);
			break;
	}
}
