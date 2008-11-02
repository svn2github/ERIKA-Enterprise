/* ###*B*###
 * Copyright (C) Roberto Bucher (SUPSI- Lugano)
 *               Simone Mannori (Scilab / INRIA / DIGITEO)
 *
 * Copyright (C) METALAU Project (INRIA)
 * ###*E*### */
 
 
#include "machine.h"
#include "scicos_block4.h"

static void init(scicos_block *block)
{
  double * y = block->outptr[0];
  y[0]=0.0;
}

static void inout(scicos_block *block)
{
  double t = get_scicos_time();
  double * y = block->outptr[0];
  double v;

  if (t<block->rpar[4]) y[0]=0.0;
  else {
    v=(t-block->rpar[4])/block->rpar[1];
    v=(v - (int) v) * block->rpar[1];
    if(v < block->rpar[2]) y[0]=block->rpar[3]+block->rpar[0];
    else                   y[0]=block->rpar[3];
  }
}

static void end(scicos_block *block)
{
  double * y = block->outptr[0];
  y[0]=0.0;
}



void rt_square(scicos_block *block,int flag)
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


