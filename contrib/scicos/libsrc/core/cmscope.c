/* ###*B*###
 * Copyright (C) Roberto Bucher (SUPSI- Lugano)
 *               Simone Mannori (Scilab / INRIA / DIGITEO)
 *
 * Copyright (C) METALAU Project (INRIA)
 * ###*E*### */
 
 
/**
     dummy function for code generation 
*/

#include "scicos_block4.h"

void cmscope(scicos_block * block,int flag)
{

  switch(flag) 
  {
    case Initialization:
      {
	    //** nothing to do 
	break;
      }
    case StateUpdate:
      {
        //** nothing to do 
	  }
	break;

    case Ending:
      {
        //** nothing to do 
      }
    break;
  }
}
