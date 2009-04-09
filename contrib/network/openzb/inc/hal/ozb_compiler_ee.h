/** 
* @file ozb_compiler_ee.h
* @brief Erika Enterprise Compiler support for OpenZB.
* @author Christian Nastasi
* @date 2009-03-22
*
* Using the Erika Enterprise abstraction for the compiler.
*/
#ifndef __ozb_compiler_ee_h__
#define __ozb_compiler_ee_h__

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

#ifndef INT32_T
#define INT32_T
typedef EE_INT32 int32_t;	/**< Unsigned 32 bit intgerer. */
#endif
/**  @} */

#ifndef HAL_INLINE 
#define HAL_INLINE __INLINE__
#endif

#endif /* Header Protection */
