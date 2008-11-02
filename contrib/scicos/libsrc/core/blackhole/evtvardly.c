/* ###*B*###
 * Copyright (C) Roberto Bucher (SUPSI- Lugano)
 *               Simone Mannori (Scilab / INRIA / DIGITEO)
 *
 * Copyright (C) METALAU Project (INRIA)
 * ###*E*### */
 
 
#include "scicos_block.h"
#include <math.h>

void evtvardly(scicos_block *block,int flag)
{ 
  if (flag==3){
    block->evout[0]=block->inptr[0][0];
  }
}

