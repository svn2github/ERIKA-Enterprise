/** 
* @file debug.h
* @brief 
* @author Christian Nastasi
* @date 2009-03-22
*
* This file define the debug optional function that can be used by the stack
* declaring the build option \c OZB_DEBUG.
*
* \todo Include a dependency check in the header file inclusion that returns a 
* 	compilation error if the console library is not included in the build of
* 	the ozb one.
*
* \todo Write a more specific docs for this section that explain:
* 	- How to enable debugging (from the compiler line?);
* 	- What are the supported debug mechanisms (debug ports);
* 	- What are the port-specifc debug option (from the compiler line?).
* 	- What are the dependency with respect to other contrib dir.
*/
#ifndef __ozb_debug_h__
#define __ozb_debug_h__

#ifdef OZB_DEBUG

/* FIXME: chris: now this simbol is passed by the compiled -D option, 
 * we should have something automatically declared when the required contrib 
 * lib is included in the build. */
#ifndef USE_CONSOLE
#error "OZB_DEBUG: Console library is required for OpenZB Debugging."
#endif

#include <hal/ozb_compiler.h> 
#include "console.h"	/* From the console contrib library. */


/* Select the specific debug mechanism (port). */
#ifdef OZB_DEBUG_SERIAL		/* Serial Port */
/* FIXME: chris: now this simbol is passed by the compiled -D option, 
 * we should have something automatically declared when the required contrib 
 * lib is included in the build. */
#ifndef USE_CONSOLE_SERIAL	
#error "OZB_DEBUG: Console Serial module is required for serial port."
#endif
#include "console_serial.h"  /* From the console contrib library. */
#ifndef OZB_DEBUG_SERIAL_PORT 
#define OZB_DEBUG_SERIAL_PORT 	CONSOLE_SERIAL_PORT_2		
#endif
#ifndef OZB_DEBUG_SERIAL_BAUDRATE 
#define OZB_DEBUG_SERIAL_BAUDRATE 115200 
#endif
#ifndef OZB_DEBUG_SERIAL_OPT
#define OZB_DEBUG_SERIAL_OPT \
	CONSOLE_SERIAL_FLAG_BIT8_NO | CONSOLE_SERIAL_FLAG_BIT_STOP1 
#endif

#else	/* Unspecified Port */
#error "OZB_DEBUG: unselected debug mechanism."

#endif	/* End Select Debug Port */

#include <phy/ozb_phy_types.h>

/** 
* @brief Initialize the OpenZB debug port
* 
* @return A negative error code is return on failure, otherwise success.
*/
int8_t ozb_debug_init(void);

/** 
* @brief Write to the OpenZB debug port
* 
* @param[in] msg The message to write
* @param[in] len The message length
* 
* @return A negative error code is return on failure, otherwise success.
*
* @pre 	The debug port must be properly initialized with the \ref ozb_debug_init
*	function. 
*/
int8_t ozb_debug_write(uint8_t *msg, uint16_t len);

/** 
* @brief Print to the OpenZB debug port
* 
* @param[in] msg The message to write
* 
* @return A negative error code is return on failure, otherwise success.
*
* @pre 	The debug port must be properly initialized with the \ref ozb_debug_init
*	function. 
*
* \todo Write a comment to this function.
*/
int8_t ozb_debug_print(const char *msg);

void ozb_debug_print_phycode(enum ozb_phy_code_t c, char *out); 

HAL_INLINE void ozb_debug_sprint_uint8(uint8_t data, char *out)
{
	out[3] = '\0';
	out[2] = '0' + (data % 10);
	out[1] = '0' + ((data / 10) % 10);
	out[0] = '0' + ((data / 100) % 10);
}

HAL_INLINE void ozb_debug_print_uint16(uint16_t data, char *out)
{
	out[5] = '\0';
	out[4] = '0' + (data % 10);
	out[3] = '0' + ((data / 10) % 10);
	out[2] = '0' + ((data / 100) % 10);
	out[1] = '0' + ((data / 1000) % 10);
	out[0] = '0' + ((data / 10000) % 10);
}

HAL_INLINE void ozb_debug_print_uint32(uint32_t data, char *out)
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

HAL_INLINE void ozb_debug_print_int8(int8_t data, char *out)
{
	out[4] = '\0';
	out[3] = '0' + (data % 10);
	out[2] = '0' + ((data / 10) % 10);
	out[1] = '0' + ((data / 100) % 10);
	out[0] = data < 0 ? '-' : ' ';
}

HAL_INLINE void ozb_debug_print_int16(int16_t data, char *out)
{
	out[6] = '\0';
	out[5] = '0' + (data % 10);
	out[4] = '0' + ((data / 10) % 10);
	out[3] = '0' + ((data / 100) % 10);
	out[2] = '0' + ((data / 1000) % 10);
	out[1] = '0' + ((data / 10000) % 10);
	out[0] = data < 0 ? '-' : ' ';
}

HAL_INLINE void ozb_debug_print_int32(int32_t data, char *out)
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
#endif /* OSB_DEBUF */

#endif /* Header Protection */
