/** 
* @file debug.h
* @brief Debug Interface
* @author Christian Nastasi, Dario Di Stefano
* @date 2009-03-22
*
* This file define the debug optional function that can be used by the stack
* declaring the build option \c lwip_DEBUG.
*
* \todo Include a dependency check in the header file inclusion that returns a 
* 	compilation error if the console library is not included in the build of
* 	the lwip one.
*
* \todo Write a more specific docs for this section that explain:
* 	- How to enable debugging (from the compiler line?);
* 	- What are the supported debug mechanisms (debug ports);
* 	- What are the port-specifc debug option (from the compiler line?).
* 	- What are the dependency with respect to other contrib dir.
*/

#ifndef __lwip_debug_h__
#define __lwip_debug_h__

#include <hal/lwip_compiler.h> 


#ifdef LWIP_DEBUG_LOG
/* FIXME: chris: now this simbol is passed by the compiled -D option, 
 * we should have something automatically declared when the required contrib 
 * lib is included in the build. */
#ifndef USE_CONSOLE
#error "LWIP_DEBUG_LOG: Console library is required for LWIP Debugging."
#endif
#include "console.h"	/* From the console contrib library. */
/* Select the specific debug mechanism (port). */
#ifdef LWIP_DEBUG_LOG_SERIAL		/* Serial Port */
/* FIXME: chris: now this simbol is passed by the compiled -D option, 
 * we should have something automatically declared when the required contrib 
 * lib is included in the build. */
#ifndef USE_CONSOLE_SERIAL	
#error "LWIP_DEBUG_LOG: Console Serial module is required for serial port."
#endif
#include "console_serial.h"  /* From the console contrib library. */
#ifndef LWIP_DEBUG_LOG_SERIAL_PORT 
#define LWIP_DEBUG_LOG_SERIAL_PORT 	CONSOLE_SERIAL_PORT_2		
#endif
#ifndef LWIP_DEBUG_LOG_SERIAL_BAUDRATE 
#define LWIP_DEBUG_LOG_SERIAL_BAUDRATE 	115200 
#endif
#ifndef LWIP_DEBUG_LOG_SERIAL_OPT
#define LWIP_DEBUG_LOG_SERIAL_OPT \
	CONSOLE_SERIAL_FLAG_BIT8_NO | CONSOLE_SERIAL_FLAG_BIT_STOP1
#endif
#else	/* Unspecified Port */
#error "LWIP_DEBUG_LOG: unselected debug mechanism."
#endif	/* End Select Debug Port */
#endif /* LWIP_DEBUG_LOG */

/** 
* @brief Initialize the lwip debug port
* 
* @return A negative error code is return on failure, otherwise success.
*/
s8_t lwip_debug_init(void);

/** 
* @brief Write to the lwip debug port
* 
* @param[in] msg The message to write
* @param[in] len The message length
* 
* @return A negative error code is return on failure, otherwise success.
*
* @pre 	The debug port must be properly initialized with the \ref lwip_debug_init
*	function. 
*/
s8_t lwip_debug_write(u8_t *msg, u16_t len);

/** 
* @brief Print to the lwip debug port
* 
* @param[in] msg The message to write
* 
* @return A negative error code is return on failure, otherwise success.
*
* @pre 	The debug port must be properly initialized with the \ref lwip_debug_init
*	function. 
*
* \todo Write a comment to this function.
*/
s8_t lwip_debug_print(const char *msg);

COMPILER_INLINE void lwip_debug_sprint_u8(u8_t data, char *out)
{
	out[3] = '\0';
	out[2] = '0' + (data % 10);
	out[1] = '0' + ((data / 10) % 10);
	out[0] = '0' + ((data / 100) % 10);
}

COMPILER_INLINE void lwip_debug_sprint_u16(u16_t data, char *out)
{
	out[5] = '\0';
	out[4] = '0' + (data % 10);
	out[3] = '0' + ((data / 10) % 10);
	out[2] = '0' + ((data / 100) % 10);
	out[1] = '0' + ((data / 1000) % 10);
	out[0] = '0' + ((data / 10000) % 10);
}

COMPILER_INLINE void lwip_debug_sprint_u32(u32_t data, char *out)
{
	out[10] = '\0';
	out[9] = '0' + (data % 10);
	out[8] = '0' + ((data / 10) % 10);
	out[7] = '0' + ((data / 100) % 10);
	out[6] = '0' + ((data / 1000) % 10);
	out[5] = '0' + ((data / 10000) % 10);
	out[4] = '0' + ((data / 100000) % 10);
	out[3] = '0' + ((data / 1000000) % 10);
	out[2] = '0' + ((data / 10000000) % 10);
	out[1] = '0' + ((data / 100000000) % 10);
	out[0] = '0' + ((data / 1000000000) % 10);
}

COMPILER_INLINE void lwip_debug_sprint_d8(s8_t data, char *out)
{
	out[4] = '\0';
	out[3] = '0' + (data % 10);
	out[2] = '0' + ((data / 10) % 10);
	out[1] = '0' + ((data / 100) % 10);
	out[0] = data < 0 ? '-' : ' ';
}

COMPILER_INLINE void lwip_debug_sprint_d16(s16_t data, char *out)
{
	out[6] = '\0';
	out[5] = '0' + (data % 10);
	out[4] = '0' + ((data / 10) % 10);
	out[3] = '0' + ((data / 100) % 10);
	out[2] = '0' + ((data / 1000) % 10);
	out[1] = '0' + ((data / 10000) % 10);
	out[0] = data < 0 ? '-' : ' ';
}

COMPILER_INLINE void lwip_debug_sprint_d32(s32_t data, char *out)
{
	out[11] = '\0';
	out[10] = '0' + (data % 10);
	out[9] = '0' + ((data / 10) % 10);
	out[8] = '0' + ((data / 100) % 10);
	out[7] = '0' + ((data / 1000) % 10);
	out[6] = '0' + ((data / 10000) % 10);
	out[5] = '0' + ((data / 100000) % 10);
	out[4] = '0' + ((data / 1000000) % 10);
	out[3] = '0' + ((data / 10000000) % 10);
	out[2] = '0' + ((data / 100000000) % 10);
	out[1] = '0' + ((data / 1000000000) % 10);
	out[0] = data < 0 ? '-' : ' ';
}

#endif /* Header Protection */
