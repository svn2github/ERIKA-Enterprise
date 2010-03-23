/** 
* @file hv7131gp_compiler_ee.h
* @brief Erika Enterprise Compiler support for HV7131GP.
* @author Marco Ghibaudi
* @date 2010-03-19
*
* Using the Erika Enterprise abstraction for the compiler.
*/

#ifndef __hv7131gp_compiler_ee_h__
#define __hv7131gp_compiler_ee_h__

#include <ee.h>
#include "p32xxxx.h"
/** 
* @name Basic type representations.
* @{ */

typedef enum {
	TRUE 		= 0x00,	/**< True */
	FALSE		= 0x01, /**< False */
} Boolean;


#ifndef uint32_t	/**< 32 bits unsigned data type */
#define uint32_t unsigned int 	
#endif

#ifndef int32_t		/**< 32 bits data type */
#define int32_t int				
#endif

#ifndef uint16_t	/**< 16 bits unsigned data type */
#define uint16_t unsigned short int 	
#endif

#ifndef int16_t		/**< 16 bits data type */
#define int16_t short int 		
#endif

#ifndef uint8_t		/**< 8 bits unsigned data type */
#define uint8_t unsigned char		
#endif

#ifndef int8_t		/**< 8 bits data type */
#define int8_t char		
#endif

/**  @} */




#ifndef COMPILER_INLINE 
#define COMPILER_INLINE __INLINE__
#endif

#ifndef COMPILER_ISR
#define COMPILER_ISR(func) ISR2(func)
#endif

#endif /* Header Protection */
