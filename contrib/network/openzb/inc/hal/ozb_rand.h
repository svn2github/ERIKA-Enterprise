#ifndef __ozb_rand_h__
#define __ozb_rand_h__

#include <hal/ozb_compiler.h>

#ifdef __ERIKA__	/* Erika */
#include <ee.h>
/* TODO: this is FAKE!!!, what can we do in future??? */
#include <stdlib.h>
HAL_INLINE void ozb_rand_init(void) 
{
}

HAL_INLINE uint8_t ozb_rand_8bit(void)
{
	return (rand() % 0xFF);
}

#elif defined __C30__ 	/* Microchip C30 */
#include <stdlib.h>
HAL_INLINE void ozb_rand_init(void) 
{
}

HAL_INLINE uint8_t ozb_rand_8bit(void)
{
	return (rand() % 0xFF);
}

#else			/* No random generator */
#error "OZB_HAL ERROR: random number generator not specified"

#endif	/* End Compiler Selection */

#endif /* Header Protection */
