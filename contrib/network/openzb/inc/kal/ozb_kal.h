#ifndef __ozb_kal_h__
#define __ozb_kal_h__

#include <hal/ozb_compiler.h>

/* chris: is it necesary to have this include in here? maybe the 
	  implementation details specific of the particular kal can be 
	  hidden in the ozb_kal_erika.c? 
	  If we need some particular macros (or inline) specific for the
	  particular kal then we need to use something like this!
*/
/* Start OS selection */
#ifdef __ERIKA__
#include <kal/ozb_kal_erika.h>	/* Erika Enterprise */

#else					/* No KAL */
#error "OZB_KAL ERROR: OS or equivalent abstraction not specified"
#endif

#endif /* Header Protection */
