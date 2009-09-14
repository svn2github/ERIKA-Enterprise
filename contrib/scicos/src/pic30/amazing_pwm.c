
/* ###*B*###
 * 
 * Copyright (C) Francesco Prosperi (SSSA - Pisa)
 *
 * ###*E*### */
 
#include <ee.h>
#include <machine.h>
#include <scicos_block4.h>

static void init(scicos_block *block)
{
#ifndef __AMAZING_TUNER__
	EE_pwm_init( EE_PWM_PORT1 , 20000 , 0 );
	EE_pwm_init( EE_PWM_PORT2 , 20000 , 0 );
#endif // __AMAZING_TUNER__
}
 
static void inout(scicos_block *block)
{
	/* Get angle(degree) from Scicos block */
	float *x_angle = block->inptr[0];
	float *y_angle = block->inptr[1];
	unsigned int pwm_step = 10; // us
	unsigned int pwm_bias = 1500; // us
	
	EE_pwm_set_duty( EE_PWM_PORT1 , (*x_angle)*pwm_step+pwm_bias );
	EE_pwm_set_duty( EE_PWM_PORT2 , (*y_angle)*pwm_step+pwm_bias );
}

static void end(scicos_block *block)
{
	EE_pwm_close(EE_PWM_PORT1);
	EE_pwm_close(EE_PWM_PORT2);
}

void amazing_pwm(scicos_block *block,int flag)
{
	switch (flag) {
		case OutputUpdate:
			inout(block);
			break;
    		case StateUpdate:
			break;
		case Initialization:
			init(block);
			break;
		case Ending:
			end(block);
			break;
	}
}

