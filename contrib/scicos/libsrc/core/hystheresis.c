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

void  hystheresis(scicos_block *block,int flag)
{
  if (flag==1)
  {
    if (get_phase_simulation()==1||block->ng==0) {
      if (*block->inptr[0]>=block->rpar[0]){
	     block->outptr[0][0]=block->rpar[2];
      }
	  else if (*block->inptr[0]<=block->rpar[1]){
	     block->outptr[0][0]=block->rpar[3];
      }
	  else if ((block->outptr[0][0]!=block->rpar[3])&&(block->outptr[0][0]!=block->rpar[2])){
	     block->outptr[0][0]=block->rpar[3];
	/* Handling situations where all zero-crossings are
	   suppressed in discrete models. In this case, initial state
	   is initialised to OFF*/
      }
    }
   else {
    /* compatibility with Simulink: when input value is located
	   between two margines the OFF state is selected. Initial
	   Mode is OFF (mode==0) */
    if (block->mode[0]==2){
	  block->outptr[0][0]=block->rpar[2];
      }
	else {
	  block->outptr[0][0]=block->rpar[3];
    }

   }

  //* ModeZeroCrossing   9
  } else if (flag==9){
      block->g[0]=*block->inptr[0]-(block->rpar[0]);
      block->g[1]=*block->inptr[0]-(block->rpar[1]);
      if (get_phase_simulation()==1) {
         if (block->g[0]>=0){
	       block->mode[0] = 2;
         }
		 else if (block->g[1]<=0){
	       block->mode[0]=1;
         }
      }
  }

}//** .. end 
