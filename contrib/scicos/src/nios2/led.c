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


static int led_status=0;
static int leds[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

static void init(scicos_block *block)
{
}

static void inout(scicos_block *block)
{
	int i = block->ipar[0];
	
	if ( (i<0) || (i>7) )
		return;

	alt_irq_context c;
	c = alt_irq_disable_all();

	if(block->inptr[0][0]>0.5)
		led_status |= leds[i];
	else
		led_status &= ~leds[i];

	IOWR_ALTERA_AVALON_PIO_DATA(LED_PIO_BASE, led_status);
	alt_irq_enable_all(c);
}

static void end(scicos_block *block)
{
}

void rt_led(scicos_block *block,int flag)
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
