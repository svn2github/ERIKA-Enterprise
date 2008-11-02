/* ###*B*###
 * Copyright (C) Roberto Bucher (SUPSI- Lugano)
 *               Simone Mannori (Scilab / INRIA / DIGITEO)
 *
 * Copyright (C) METALAU Project (INRIA)
 * ###*E*### */
 
 
#include "scicos_block4.h"
//#include "memory.h"
#include <string.h>

void samphold4_m(scicos_block *block,int flag)
{
  /* c     Copyright INRIA
     
  Scicos block simulator
  returns sample and hold  of the input */
  
if ((flag ==1)) {
  void *u,*y;
  int m,n,sz;
  m=GetInPortRows(block,1);
  n=GetInPortCols(block,1);
  u=GetInPortPtrs(block,1);
  y=GetOutPortPtrs(block,1);
  sz=GetSizeOfOut(block,1);
  memcpy(y,u,m*n*sz);
  }
}
