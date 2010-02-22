#ifndef __ucv_compiler_h__
#define __ucv_compiler_h__

/* Start Compiler Selection section */
#if 	defined __ERIKA__		/* Erika Abstract Compiler */
#include <arch/ucv_compiler_ee.h>
#elif	defined __EDAQ__		/* eDAQ Abstract Compiler */
#include <arch/ucv_compiler_edaq.h>
#else			/* No compiler */
#error "uCV LIBRARY ERROR: compiler type not specified"
#endif	
/* End Compiler Selection */

#endif /* Header Protection */
