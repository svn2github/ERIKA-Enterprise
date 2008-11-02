/* ###*B*###
 * Copyright (C) Roberto Bucher (SUPSI- Lugano)
 *               Simone Mannori (Scilab / INRIA / DIGITEO)
 *
 * Copyright (C) METALAU Project (INRIA)
 * ###*E*### */
 
 
#include <machine.h>
#include <scicos_block4.h>

#include <ee.h>
#include <stdio.h>

// this is to temporarily support the prototyping demo board
// to be moved into the Flex board directory.
#ifdef BOARD_DEMO_PROTOTYPE
#include "lcd-protocol.h"
#endif

/*
* Output syntax: n:smmmmmmmmEsaa
* where:	n is the input number (0/1);
*	s is the signum (-/+);
*	mmmmmmmm is the mantissa (max 8 chars);
*	aaa is the exponent (max 3 chars).
*/
static char lcd_buf[17];

static void write_buf(float data)
{
	/* Conversion routine */
	//** WARNING: 
	//**          Two lines = 7.5 ms !
	//** To DO: find a faster sprintf()
	sprintf(lcd_buf,"%+.6E ",(double)data);
}

static void init(scicos_block *block)
{
	/* Init LCD */
	EE_lcd_init();
	
	/* Clean LCD */
	EE_lcd_clear();
}

static void inout(scicos_block *block)
{
	//** WARNING: This routine is extremely SLOOOOW 
	//**          Two lines = 7.5 ms !
	
	float *u1 = block->inptr[0];
	float *u2 = block->inptr[1];

	/* Clear screen */
	//EE_lcd_clear();

	/* Write 1st value on LCD */
	EE_lcd_puts("1:");
	write_buf(u1[0]);
	EE_lcd_puts(lcd_buf);
	
	/* Move to second line */
	EE_lcd_line2();
	
	/* Write 2nd value on LCD */
	EE_lcd_puts("2:");
	write_buf(u2[0]);
	EE_lcd_puts(lcd_buf);	

	/* Reset position for the next iteration */
	EE_lcd_home();
}

static void end(scicos_block *block)
{
}

void rt_lcd(scicos_block *block,int flag)
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
