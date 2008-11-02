/* ###*B*###
 * Copyright (C) Roberto Bucher (SUPSI- Lugano)
 *               Simone Mannori (Scilab / INRIA / DIGITEO)
 *
 * Copyright (C) METALAU Project (INRIA)
 * ###*E*### */
 
 
#include "machine.h"
#include "scicos_block4.h"

#include <math.h>

static void init(scicos_block *block)
{
  double * y = block->outptr[0];
  y[0]=0.0;
}

static void inout(scicos_block *block)
{
  double w,pi=3.1415927;
  double * y = block->outptr[0];
  double t = get_scicos_time();

   if (t<block->rpar[4]) y[0]=0.0;
   else {
     w=fmod(2*pi*block->rpar[1]*(t-block->rpar[4])-block->rpar[2],(2*pi));
     y[0]=block->rpar[0]*sin(w)+block->rpar[3];
   }
}

static void end(scicos_block *block)
{
  double * y = block->outptr[0];
  y[0]=0.0;
}



void rt_sinus(scicos_block *block,int flag)
{
  if (flag==1){          /* set output */
    inout(block);
  }
  else if (flag==5){     /* termination */ 
    end(block);
  }
  else if (flag ==4){    /* initialisation */
    init(block);
  }
}


