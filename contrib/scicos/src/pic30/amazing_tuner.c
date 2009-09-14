/* ###*B*###
 * 
 * Copyright (C) Francesco Prosperi (SSSA - Pisa)
 *
 * ###*E*### */

#include <ee.h>
#include <amazing.h>
#include <machine.h>
#include <scicos_block4.h>

static void init(scicos_block *block)
{
	int res_x = block->ipar[0];
	int res_y = block->ipar[1];

	amazing_tuner_body((EE_UINT16)res_x,(EE_UINT16)res_y);
}

void amazing_tuner(scicos_block *block,int flag)
{
	switch (flag) {
		case OutputUpdate:
			break;
		case StateUpdate:
			break;
		case Initialization:
			init(block);
			break;
		case Ending:
			break;
	}
}
