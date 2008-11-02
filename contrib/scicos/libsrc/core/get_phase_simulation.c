/* ###*B*###
 * Copyright (C) Roberto Bucher (SUPSI- Lugano)
 *               Simone Mannori (Scilab / INRIA / DIGITEO)
 *
 * Copyright (C) METALAU Project (INRIA)
 * ###*E*### */
 
 
/**
     dummy function for code generation 
*/

//** WARNING: this function is an emulation used for
//**          the fxed step solver used by the code 
//**          genenerator for continuous systems

 //** the original function return back
 //** a code to the computational function
 //** "1" is the defalt value used for the fixed
 //** sep solver

#include "scicos_block4.h"

int get_phase_simulation()
{
   return (1);
}
