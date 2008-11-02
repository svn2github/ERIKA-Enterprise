/* ###*B*###
 * Copyright (C) Roberto Bucher (SUPSI- Lugano)
 *               Simone Mannori (Scilab / INRIA / DIGITEO)
 *
 * Copyright (C) METALAU Project (INRIA)
 * ###*E*### */
 
 
#include "scicos_block.h"
#include <stdio.h>

//* DerivativeState    0
//* OutputUpdate       1
//* StateUpdate        2
//* OutputEventTiming  3
//* Initialization     4
//* Ending             5
//* 
//* ReInitialization   6
//* ModeZeroCrossing   9

void invblk4(scicos_block *block,int flag)
{
  /* Copyright INRIA
     
  Scicos block simulator
  Outputs the inverse of the input */
  
  int i;
  double ww;
  if (flag == 6){
    for(i=0;i< block->insz[0];i++){
      ww=block->inptr[0][i];
      if (ww != 0.0)
	block->outptr[0][i]=1.0/ww;
    }
  }
  if (flag == 1){
    for(i=0;i< block->insz[0];i++){
      ww=block->inptr[0][i];
      if (ww != 0.0)
	block->outptr[0][i]=1.0/ww;
      else{
	set_block_error(-2);
	return;
      }
    }
  } 
}
