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

#include <hal/ozb_compiler.h> 
#include <phy/ozb_phy_types.h>
#include <mac/ozb_mac_types.h>

#ifdef OZB_DEBUG_TIME
/* FIXME: chris: now this simbol is passed by the compiled -D option, 
 * we should have something automatically declared when the required contrib 
 * lib is included in the build. */
#ifndef USE_DAQ_TIME
#error "OZB_DEBUG_TIME: DAQ Time library is required for OpenZB Debugging."
#endif

#include "daq_time.h"	/* From the daq_time contrib library. */
#define OZB_DEBUG_TIME_CLOCK_ID	0

#endif /* OZB_DEBUG_TIME */


#ifdef OZB_DEBUG_LOG
/* FIXME: chris: now this simbol is passed by the compiled -D option, 
 * we should have something automatically declared when the required contrib 
 * lib is included in the build. */
#ifndef USE_CONSOLE
#error "OZB_DEBUG_LOG: Console library is required for OpenZB Debugging."
#endif

#include "console.h"	/* From the console contrib library. */

/* Select the specific debug mechanism (port). */
#ifdef OZB_DEBUG_LOG_SERIAL		/* Serial Port */
/* FIXME: chris: now this simbol is passed by the compiled -D option, 
 * we should have something automatically declared when the required contrib 
 * lib is included in the build. */
#ifndef USE_CONSOLE_SERIAL	
#error "OZB_DEBUG_LOG: Console Serial module is required for serial port."
#endif
#include "console_serial.h"  /* From the console contrib library. */
#ifndef OZB_DEBUG_LOG_SERIAL_PORT 
#define OZB_DEBUG_LOG_SERIAL_PORT 	CONSOLE_SERIAL_PORT_2		
#endif
#ifndef OZB_DEBUG_LOG_SERIAL_BAUDRATE 
#define OZB_DEBUG_LOG_SERIAL_BAUDRATE 	115200 
#endif
#ifndef OZB_DEBUG_LOG_SERIAL_OPT
#define OZB_DEBUG_LOG_SERIAL_OPT 0x06
/*#define OZB_DEBUG_LOG_SERIAL_OPT \
	CONSOLE_SERIAL_FLAG_BIT8_NO | CONSOLE_SERIAL_FLAG_BIT_STOP1*/

#endif

#else	/* Unspecified Port */
#error "OZB_DEBUG_LOG: unselected debug mechanism."

#endif	/* End Select Debug Port */

#endif /* OZB_DEBUG_LOG */

/** 
* @brief Initialize the OpenZB debug port
* 
* @return A negative error code is return on failure, otherwise success.
*/
int8_t ozb_debug_init(void);


enum ozb_debug_tim_clock_id_t {
	OZB_DEBUG_TIME_CLOCK_BI = 0,
	OZB_DEBUG_TIME_CLOCK_DEVEL ,
	OZB_DEBUG_TIME_CLOCK_NUMBER,
};

#define OZB_DEBUG_STAT_STRLEN 	26	/**<head(3)+tail(3) + (DAQ_TIME_STRLEN *
					     OZB_DEBUG_TIME_CLOCK_NUMBER) */

struct ozb_debug_stat_t {
	#ifdef OZB_DEBUG_TIME
	struct daq_time_t time_clock[OZB_DEBUG_TIME_CLOCK_NUMBER];
	#endif /* OZB_DEBUG_TIME */
};

extern struct ozb_debug_stat_t ozb_debug_stats;

COMPILER_INLINE int8_t ozb_debug_time_start(uint8_t ck_id) 
{
	#ifdef OZB_DEBUG_TIME
	return daq_time_start(ck_id);
	#else
	return 0;
	#endif
}

COMPILER_INLINE uint8_t ozb_debug_time_get(uint8_t ck_id) 
{
	#ifdef OZB_DEBUG_TIME
	return daq_time_get(ck_id, ozb_debug_stats.time_clock + ck_id);
	#else
	return 0;
	#endif
}


COMPILER_INLINE void ozb_debug_stat2str(uint8_t *out) 
{
	#ifdef OZB_DEBUG
	#ifdef OZB_DEBUG_TIME
	uint8_t i;
	#endif

	/* TODO: the escape mechanism must be done!!! */
	*(out++) = 0x3C;	/* HEADER */
	#ifdef OZB_DEBUG_TIME
	for (i = 0; i < OZB_DEBUG_TIME_CLOCK_NUMBER; i++, out+=DAQ_TIME_STRLEN) 
		daq_time_2str(ozb_debug_stats.time_clock + i, out);
	#endif /* OZB_DEBUG_TIME */
	*(out++) = 0x3E;	/* TRAILER */
	#endif /* OZB_DEBUG */
}

COMPILER_INLINE uint32_t ozb_debug_time_get_us(uint8_t ck_id) 
{
	#ifdef OZB_DEBUG_TIME
	daq_time_get(ck_id, ozb_debug_stats.time_clock + ck_id);
	return daq_time_2us(ozb_debug_stats.time_clock + ck_id);
	#else
	return 0;
	#endif
}

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

void ozb_debug_sprint_phycode(enum ozb_phy_code_t c, char *out); 
void ozb_debug_sprint_maccode(enum ozb_mac_code_t c, char *out);

COMPILER_INLINE void ozb_debug_sprint_u8(uint8_t data, char *out)
{
	out[3] = '\0';
	out[2] = '0' + (data % 10);
	out[1] = '0' + ((data / 10) % 10);
	out[0] = '0' + ((data / 100) % 10);
}

COMPILER_INLINE void ozb_debug_sprint_u16(uint16_t data, char *out)
{
	out[5] = '\0';
	out[4] = '0' + (data % 10);
	out[3] = '0' + ((data / 10) % 10);
	out[2] = '0' + ((data / 100) % 10);
	out[1] = '0' + ((data / 1000) % 10);
	out[0] = '0' + ((data / 10000) % 10);
}

COMPILER_INLINE void ozb_debug_sprint_u32(uint32_t data, char *out)
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

COMPILER_INLINE void ozb_debug_sprint_d8(int8_t data, char *out)
{
	out[4] = '\0';
	out[3] = '0' + (data % 10);
	out[2] = '0' + ((data / 10) % 10);
	out[1] = '0' + ((data / 100) % 10);
	out[0] = data < 0 ? '-' : ' ';
}

COMPILER_INLINE void ozb_debug_sprint_d16(int16_t data, char *out)
{
	out[6] = '\0';
	out[5] = '0' + (data % 10);
	out[4] = '0' + ((data / 10) % 10);
	out[3] = '0' + ((data / 100) % 10);
	out[2] = '0' + ((data / 1000) % 10);
	out[1] = '0' + ((data / 10000) % 10);
	out[0] = data < 0 ? '-' : ' ';
}

COMPILER_INLINE void ozb_debug_sprint_d32(int32_t data, char *out)
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
