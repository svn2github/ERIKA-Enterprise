/* ###*B*###
 * Copyright (C) Roberto Bucher (SUPSI- Lugano)
 *               Simone Mannori (Scilab / INRIA / DIGITEO)
 *
 * Copyright (C) METALAU Project (INRIA)
 * ###*E*### */
 
 

#include "sci_mem_alloc.h"  /* malloc */

#include "scicos_block.h"

void * scicos_malloc(size_t size)
{
  return MALLOC(size);
}

