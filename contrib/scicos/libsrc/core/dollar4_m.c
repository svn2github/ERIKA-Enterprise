/* ###*B*###
 * Copyright (C) Roberto Bucher (SUPSI- Lugano)
 *               Simone Mannori (Scilab / INRIA / DIGITEO)
 *
 * Copyright (C) METALAU Project (INRIA)
 * ###*E*### */
 
 
#include "scicos_block4.h"
//#include <memory.h>
#include <string.h>

//* DerivativeState    0
//* OutputUpdate       1
//* StateUpdate        2
//* OutputEventTiming  3
//* Initialization     4
//* Ending             5

typedef struct
{         int s;
} dol_struct ;

void dollar4_m(scicos_block *block,int flag)
{
  /* c     Copyright INRIA
     
  Scicos block simulator
  Ouputs delayed input */


  int m,n;
  double *y,*u,*oz;
  dol_struct *ptr;
  m=GetInPortRows(block,1);
  n=GetInPortCols(block,1);
  u=GetRealInPortPtrs(block,1);
  y=GetRealOutPortPtrs(block,1);
  oz=GetRealOzPtrs(block,1);

  if (flag==Initialization)
    {
		*(block->work)=(dol_struct*) scicos_malloc(sizeof(dol_struct));
        ptr=*(block->work);
   /*	ptr->s=(int) scicos_malloc(sizeof(int));*/
        ptr->s=GetSizeOfOz(block,1);
	 }
  if (flag ==OutputUpdate || flag ==6)
      {ptr=*(block->work);
       memcpy(y,oz,m*n*(ptr->s));}
  if (flag == StateUpdate)
      {ptr=*(block->work);
       memcpy(oz,u,m*n*ptr->s);}
  if (flag == Ending)
      {ptr=*(block->work);
       if(ptr!=NULL) {
          scicos_free(ptr);
       }
      }

}
