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
	@file flex_daughter_lcd.c
	@brief www.scicos.org, www.scicoslab.org
	@author Roberto Bucher, SUPSI- Lugano
	@author Simone Mannori, ScicosLab developer
	@date 2006-2010
*/ 
 
 
//** 9 Feb 2008 : Revision notes by Simone Mannori 
//**

#include <machine.h>
#include <scicos_block4.h>

#include <ee.h>
#include "stdio.h"

#define in_uint8(i,j) ((unsigned char *)block->inptr[i])[j]
#define in_float(i,j) ((float *)block->inptr[i])[j]

// defined in the dspic_main template
extern int scicos_lcd_used;
extern char ee_lcd_line1[17];
extern char ee_lcd_line2[17];

static void init(scicos_block *block) {
	scicos_lcd_used = 1;
}

void EESCI_flexdmb_lcd_float_inout(float scicos_lcd_value1, float scicos_lcd_value2) {
	EE_pic30_disableIRQ();
	sprintf(ee_lcd_line1, "%+.6E", (double)scicos_lcd_value1);
	sprintf(ee_lcd_line2, "%+.6E", (double)scicos_lcd_value2);
	EE_pic30_enableIRQ();
}


void EESCI_flexdmb_lcd_uint8_inout(unsigned char* line1, unsigned char* line2) {
	int i;
	EE_pic30_disableIRQ();
	for(i=0; i<16; i++) {
		ee_lcd_line1[i] = line1[i];
		ee_lcd_line2[i] = line2[i];
	}
	ee_lcd_line1[16] = '\0';
	ee_lcd_line2[16] = '\0';
	EE_pic30_enableIRQ();
}


static void inout(scicos_block *block) {
	int port_type = block->ipar[0];
	
	if (port_type == 1)
		EESCI_flexdmb_lcd_float_inout(in_float(0,0), in_float(1,0));
	else
		EESCI_flexdmb_lcd_uint8_inout( (unsigned char *)block->inptr[0], (unsigned char *)block->inptr[1] );
}

static void end(scicos_block *block)
{
}

void flex_daughter_lcd(scicos_block *block,int flag)
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
