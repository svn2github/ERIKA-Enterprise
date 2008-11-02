/* ###*B*###
 * Copyright (C) Roberto Bucher (SUPSI- Lugano)
 *               Simone Mannori (Scilab / INRIA / DIGITEO)
 *
 * Copyright (C) METALAU Project (INRIA)
 * ###*E*### */
 
 
#include "scicos_block.h"
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

void  absolute_value(scicos_block *block,int flag)
{
  int i,j;
  if (flag==1){
    if( block->ng>0){
      for(i=0;i<block->insz[0];++i){
	if (get_phase_simulation()==1) {
	  if (block->inptr[0][i]<0){
	    j=2;
	  } else{
	    j=1;
	  }
	}else {
	  j=block->mode[i];
	}
	if (j==1){
	  block->outptr[0][i]=block->inptr[0][i];
	} else{
	  block->outptr[0][i]=-block->inptr[0][i];
	}
      }
    }else{
      for(i=0;i<block->insz[0];++i){
	if (block->inptr[0][i]<0){
	  block->outptr[0][i]=-block->inptr[0][i];
	}else{
	  block->outptr[0][i]=block->inptr[0][i];
	}
      }
    }
  }else if (flag==9){
    for(i=0;i<block->insz[0];++i){
      block->g[i]=block->inptr[0][i];
      if (get_phase_simulation()==1) {
	if(block->g[i]<0){
	  block->mode[i]=2;
	}else{
	  block->mode[i]=1;
	}
      }
    }
  }
}
