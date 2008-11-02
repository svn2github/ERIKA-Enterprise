/* ###*B*###
 * Copyright (C) Roberto Bucher (SUPSI- Lugano)
 *               Simone Mannori (Scilab / INRIA / DIGITEO)
 *
 * Copyright (C) METALAU Project (INRIA)
 * ###*E*### */
 
 
#include <altera_avalon_pio_regs.h>
#include <system.h>

#include <machine.h>
#include <scicos_block.h>

#include <ee.h>

static void init(scicos_block *block)
{
}

static void inout(scicos_block *block)
{
	int button = block->ipar[0];

	if ( (button < 1) || (button > 4) )
		return;

	volatile int pressed = IORD_ALTERA_AVALON_PIO_DATA(BUTTON_PIO_BASE);

	if(!(pressed & (0x01 << (button-1))))
		block->outptr[0][0] = 1;
	else
		block->outptr[0][0] = 0;
}

static void end(scicos_block *block)
{
}

void rt_button(scicos_block *block,int flag)
{
	switch (flag) {
		case 1:	/* set output */
			inout(block);
			break;
		case 2:	/* get input */
			inout(block);
			break;
		case 4:	/* initialisation */
			init(block);
			break;
		case 5:	/* ending */
			end(block);
			break;
	}
}
