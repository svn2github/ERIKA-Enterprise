
/* ###*B*###
 * 
 * Copyright (C) Francesco Prosperi (SSSA - Pisa)
 *
 * ###*E*### */

#include <ee.h>
#include <amazing.h>
#include <machine.h>
#include <scicos_block4.h>

void check_reset(scicos_block *block)
{
	float *u = block->inptr[0];
	
	if(u[0] >= 0.5)
		amazing_reset_body();
}

void amazing_reset(scicos_block *block,int flag)
{
	switch (flag) {
		case OutputUpdate:
			check_reset(block);
			break;
		case StateUpdate:
			break;
		case Initialization:
			break;
		case Ending:
			break;
	}
}
