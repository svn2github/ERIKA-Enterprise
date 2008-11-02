/* ###*B*###
 * Copyright (C) Roberto Bucher (SUPSI- Lugano)
 *               Simone Mannori (Scilab / INRIA / DIGITEO)
 *
 * Copyright (C) METALAU Project (INRIA)
 * ###*E*### */
 
 
#include "scicos_block.h"
#include <math.h>

void scalar2vector(scicos_block *block,int flag)
{
  int i;
  if(flag==1){
    for(i=0;i<block->outsz[0];++i){
      block->outptr[0][i]=block->inptr[0][0];
    }
  }
}
