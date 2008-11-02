/* ###*B*###
 * Copyright (C) Roberto Bucher (SUPSI- Lugano)
 *               Simone Mannori (Scilab / INRIA / DIGITEO)
 *
 * Copyright (C) METALAU Project (INRIA)
 * ###*E*### */
 
 
#include <stdlib.h> /* for rand()*/

#include "machine.h"
#include "scicos_block4.h"

static void init(scicos_block *block)
{
  double * y = block->outptr[0]   ;
  double   seed = block->rpar[1]  ; // Seed

  srand ( (int)seed ); // randomize the generator   

  y[0]=0.0;
}

static void inout(scicos_block *block)
{
  double * y = block->outptr[0]; //Output 
  double   A = block->rpar[0]  ; //Amplitute 

  //** one random integer [0 RAND_MAX]
  y[0] = A * ( (double)rand() / (double)RAND_MAX  ) ; 
}

static void end(scicos_block *block)
{
  double * y = block->outptr[0];
  y[0]=0.0;
}




//** This block produce a pseudo random output 

void rt_randm(scicos_block *block,int flag)
{
  if (flag==OutputUpdate){          /* set output */
    inout(block);
  }
  else if (flag==Ending){      /* termination */ 
    end(block);
  }
  else if (flag ==Initialization){    /* initialisation */
    init(block);
  }
}


