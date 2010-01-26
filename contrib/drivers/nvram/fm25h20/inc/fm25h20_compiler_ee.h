/** 
* @file fm25h20_compiler_ee.h
* @brief Erika Enterprise Compiler support for FM25H20.
* @author Christian Nastasi
* @author Marco Ghibaudi 
* @date 2010-01-25
*
* Using the Erika Enterprise abstraction for the compiler.
*/

#ifndef __fm25h20_compiler_ee_h__
#define __fm25h20_compiler_ee_h__

#include <ee.h>
/** 
* @name Basic type representations.
* @{ */
#ifndef UINT8_T
#define UINT8_T
typedef EE_UINT8 uint8_t;	/**< Unsigned 8 bit intgerer. */
#endif

#ifndef UINT16_T
#define UINT16_T
typedef EE_UINT16 uint16_t;	/**< Unsigned 16 bit intgerer. */
#endif

#ifndef UINT32_T
#define UINT32_T
typedef EE_UINT32 uint32_t;	/**< Unsigned 32 bit intgerer. */
#endif

#ifndef INT8_T
#define INT8_T
typedef EE_INT8 int8_t;		/**< Unsigned 8 bit intgerer. */
#endif

#ifndef INT16_T
#define INT16_T
typedef EE_INT16 int16_t;	/**< Unsigned 16 bit intgerer. */
#endif
/**  @} */

#ifndef COMPILER_INLINE 
#define COMPILER_INLINE __INLINE__
#endif

#endif /* Header Protection */
