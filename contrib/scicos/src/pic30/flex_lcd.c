/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2006-2010  Simone Mannori, Roberto Bucher
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation, 
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/** 
	@file flex_lcd.c
	@brief www.scicos.org, www.scicoslab.org
	@author Roberto Bucher, SUPSI- Lugano
	@author Simone Mannori, ScicosLab developer
	@date 2006-2010
*/ 
 
 
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

void flex_lcd(scicos_block *block,int flag)
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
