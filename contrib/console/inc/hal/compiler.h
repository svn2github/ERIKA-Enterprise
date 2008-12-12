#ifndef __compiler_h__
#define __compiler_h__
/** 
* @file compiler.h
* @brief Compiler definitions.
* @author Marinoni Mauro, Nastasi Christian
* @date 2008-11-03
*/

/** 
* @name Basic type representations.
* @{ */
typedef unsigned char uint8_t;		/**< Unsigned 8 bit intgerer. */
typedef unsigned short int uint16_t;	/**< Unsigned 16 bit intgerer. */
typedef unsigned long int uint32_t;	/**< Unsigned 32 bit intgerer. */
/**  @} */

#define COMPILER_INLINE	static inline	/**< Compiler inlining keywords. */

#endif	/* __compiler_h__ */
