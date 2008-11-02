/* ###*B*###
 * Copyright (C) Roberto Bucher (SUPSI- Lugano)
 *               Simone Mannori (Scilab / INRIA / DIGITEO)
 *
 * Copyright (C) METALAU Project (INRIA)
 * ###*E*### */
 
 
#include "scicos_block.h"
#include "sci_mem_alloc.h"

#ifndef NULL
	#define NULL 0
#endif
#define SCICOS_FREE(x) if (x  != NULL) FREE((char *) x);

void scicos_free(void *p)
{
  SCICOS_FREE(p);
}
