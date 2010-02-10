#ifndef __ucv_compiler_h__
#define __ucv_compiler_h__

/* Start Compiler Selection section */
#ifdef __ERIKA__	/* Erika Abstract Compiler */
#include <ee.h>
#include <arch/ucv_compiler_ee.h>
#else			/* No compiler */
#error "uCV LIBRARY ERROR: compiler type not specified"
#endif	
/* End Compiler Selection */

#endif /* Header Protection */
