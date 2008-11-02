/* ###*B*###
 * Copyright (C) Roberto Bucher (SUPSI- Lugano)
 *               Simone Mannori (Scilab / INRIA / DIGITEO)
 *
 * Copyright (C) METALAU Project (INRIA)
 * ###*E*### */
 
 
#include "scicos_block4.h"
#include "machine.h"
#include <math.h>

//* DerivativeState    0
//* OutputUpdate       1
//* StateUpdate        2
//* OutputEventTiming  3
//* Initialization     4
//* Ending             5
//* 
//* ReInitialization   6
//* ModeZeroCrossing   9

void expblk_m(scicos_block *block,int flag)
{
  double *u;
  double *y;
  double *rpar;
  int nu,mu,i;

  mu=GetInPortRows(block,1);
  nu=GetInPortCols(block,1);
  u=GetRealInPortPtrs(block,1);
  y=GetRealOutPortPtrs(block,1);
  rpar=GetRparPtrs(block);
  if ((flag==1)|(flag>=4)) {
  for(i=0;i<mu*nu;i++) y[i]=exp(log(*rpar)*u[i]);
  }
}
