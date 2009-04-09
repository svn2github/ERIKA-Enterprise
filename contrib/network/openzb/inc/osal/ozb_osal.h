#ifndef __ozb_osal_h__
#define __ozb_osal_h__

#include <hal/ozb_compiler.h>

/* chris: is it necesary to have this include in here? maybe the 
	  implementation details specific of the particular osal can be 
	  hidden in the ozb_osal_erika.c? 
	  If we need some particular macros (or inline) specific for the
	  particular osal then we need to use something like this!
*/
/* Start OS selection */
#ifdef __ERIKA__
#include <osal/ozb_osal_erika.h>	/* Erika Enterprise */

#else					/* No OSAL */
#error "OZB_OSAL ERROR: OS or equivalent abstraction not specified"
#endif

#endif /* Header Protection */
