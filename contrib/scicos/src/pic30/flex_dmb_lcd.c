/* ###*B*###
 * Copyright (C) Roberto Bucher (SUPSI- Lugano)
 *               Simone Mannori (Scilab / INRIA / DIGITEO)
 *
 * Copyright (C) METALAU Project (INRIA)
 * ###*E*### */
 
 
//** 9 Feb 2008 : Revision notes by Simone Mannori 
//**

#include <machine.h>
#include <scicos_block4.h>

#include <ee.h>

// defined in the dspic_main template
extern float scicos_lcd_value1;
extern float scicos_lcd_value2;
extern int scicos_lcd_used;

static void init(scicos_block *block)
{
	scicos_lcd_used = 1;
}
signed char stop=0;
static void inout(scicos_block *block)
{
	EE_pic30_disableIRQ();
	stop=1;
	scicos_lcd_value1 = *(float *)block->inptr[0];
	scicos_lcd_value2 = *(float *)block->inptr[1];
	EE_pic30_enableIRQ();
}

static void end(scicos_block *block)
{
}

void flex_dmb_lcd(scicos_block *block,int flag)
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
