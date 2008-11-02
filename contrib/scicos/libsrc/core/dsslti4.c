/* ###*B*###
 * Copyright (C) Roberto Bucher (SUPSI- Lugano)
 *               Simone Mannori (Scilab / INRIA / DIGITEO)
 *
 * Copyright (C) METALAU Project (INRIA)
 * ###*E*### */
 
 
//#include <memory.h>
#include <string.h>
#include "scicos_block.h"
#include "sci_mem_alloc.h"  /* malloc */
#include "machine.h"
#include "dmmul.h"

#define DerivativeState    0
#define OutputUpdate       1
#define StateUpdate        2
#define OutputEventTiming  3
#define Initialization     4
#define Ending             5

void dsslti4(scicos_block *block,int flag)
{
  /* Copyright INRIA
     
  Scicos block simulator
  discrete state space linear system simulator
  rpar(1:nx*nx)=A
  rpar(nx*nx+1:nx*nx+nx*nu)=B
  rpar(nx*nx+nx*nu+1:nx*nx+nx*nu+nx*ny)=C */
  
  int un = 1,lb,lc,ld ;
  int nz = block->nz  ;
  double* z    = block->z    ;
  double* rpar = block->rpar ;
  double* y    = block->outptr[0] ;
  double* u    = block->inptr[0]  ;
  int*    outsz = block->outsz ;
  int*    insz  = block->insz  ;
  double *w ;
  
  lb = nz * nz ;
  
  if (flag==OutputUpdate || flag ==6)
    {
     /* y=c*x+d*u */
     lc = lb+nz*insz[0]  ;
     ld = lc+nz*outsz[0] ;
     if (nz==0)
	 {
       dmmul (&rpar[ld],outsz,u,insz,y,outsz,outsz,insz,&un) ;
     }
	 else
	 {
       dmmul (&rpar[lc],outsz,z,&nz,y,outsz,outsz,&nz,&un)   ;
       dmmul1(&rpar[ld],outsz,u,insz,y,outsz,outsz,insz,&un) ;
     }
  }
  else if (flag==StateUpdate){
    /* x+=a*x+b*u */
    if (nz!=0){
      w =*block->work;
      memcpy(w,z,nz*sizeof(double)); //** standard C library function 
      dmmul(&rpar[0],&nz,w,&nz,z,&nz,&nz,&nz,&un);
      dmmul1(&rpar[lb],&nz,u,insz,z,&nz,&nz,insz,&un);
    }
  }
  else if (flag==Initialization)
  {/* the workspace for temp storage
		      */
    if ( (*block->work=scicos_malloc(sizeof(double)*nz) )== NULL )
	{
      set_block_error(-16);
      return;
    }
  }
  else if (flag==Ending){
    scicos_free(*block->work);
  }
}


