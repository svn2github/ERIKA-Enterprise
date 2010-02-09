/* ###*B*###
 * 
 * Copyright (C) Francesco Prosperi (SSSA - Pisa)
 *
 * ###*E*### */

#include <ee.h>
#include <amazing.h>
#include <machine.h>
#include <scicos_block4.h>

void amazing_ground(scicos_block *block,int flag)
{
	switch (flag) {
		case OutputUpdate:
			break;
		case StateUpdate:
			break;
		case Initialization:
			break;
		case Ending:
			break;
	}
}
