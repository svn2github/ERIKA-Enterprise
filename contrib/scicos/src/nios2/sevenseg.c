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
	unsigned int hex = block->inptr[0][0];

	static alt_u8 segments[16] = {  0x81, 0xCF, 0x92, 0x86, 0xCC, 0xA4, 0xA0, 0x8F, 0x80, 0x84, /* 0-9 */
					0x88, 0xE0, 0xF2, 0xC2, 0xB0, 0xB8 };                       /* a-f */

	unsigned int data = segments[(int)hex & 15] | (segments[((int)hex >> 4) & 15] << 8);

	IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_PIO_BASE, data);
}

static void end(scicos_block *block)
{
}

void rt_sevenseg(scicos_block *block,int flag)
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
			ending(block);
			break;
	}
}
