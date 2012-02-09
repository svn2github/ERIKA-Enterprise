/** 
* @file iedf_debug.h
* @brief Debug Interfaceiedf
* @author Gianluca Franchino 2012
* @author Gianluca Franchino 2011 
*
* This file define the debug optional function that can be used by the stack
* declaring the build option \c IEDF_DEBUG.
*
*/
#ifndef __iedf_debug_h__
#define __iedf_debug_h__

#include <hal/iedf_compiler.h> 


#ifdef IEDF_DEBUG_LOG
#ifndef USE_CONSOLE
#error "IEDF_DEBUG_LOG: Console library is required for RI-EDF Debugging."
#endif

#include "console.h"	/* From the console contrib library. */

/* Select the specific debug mechanism (port). */
#ifdef IEDF_DEBUG_LOG_SERIAL		/* Serial Port */

#ifndef USE_CONSOLE_SERIAL	
#error "IEDF_DEBUG_LOG: Console Serial module is required for serial port."
#endif
#include "console_serial.h"  /* From the console contrib library. */
#ifndef IEDF_DEBUG_LOG_SERIAL_PORT 
#define IEDF_DEBUG_LOG_SERIAL_PORT 	CONSOLE_SERIAL_PORT_2		
#endif
#ifndef IEDF_DEBUG_LOG_SERIAL_BAUDRATE 
#define IEDF_DEBUG_LOG_SERIAL_BAUDRATE 	115200 
#endif
#ifndef IEDF_DEBUG_LOG_SERIAL_OPT
//#define IEDF_DEBUG_LOG_SERIAL_OPT 0x06
#define IEDF_DEBUG_LOG_SERIAL_OPT \
	CONSOLE_SERIAL_FLAG_BIT8_NO | CONSOLE_SERIAL_FLAG_BIT_STOP1

#endif

#else	/* Unspecified Port */
#error "IEDF_DEBUG_LOG: unselected debug mechanism."

#endif	/* End Select Debug Port */

#endif /* IEDF_DEBUG_LOG */

/** 
* @brief Initialize the uWireless debug port
* 
* @return A negative error code is return on failure, otherwise success.
*/
int8_t iedf_debug_init(void);


enum iedf_debug_tim_clock_id_t {
	IEDF_DEBUG_TIME_CLOCK_BI = 0,
	IEDF_DEBUG_TIME_CLOCK_DEVEL ,
	IEDF_DEBUG_TIME_CLOCK_NUMBER,
};

#define IEDF_DEBUG_STAT_STRLEN 	26	/**<head(3)+tail(3) + (DAQ_TIME_STRLEN *
					     IEDF_DEBUG_TIME_CLOCK_NUMBER) */

struct iedf_debug_stat_t {
	#ifdef IEDF_DEBUG_TIME
	struct daq_time_t time_clock[IEDF_DEBUG_TIME_CLOCK_NUMBER];
	#endif /* IEDF_DEBUG_TIME */
};

extern struct iedf_debug_stat_t iedf_debug_stats;

COMPILER_INLINE int8_t iedf_debug_time_start(uint8_t ck_id) 
{
	#ifdef UWL_DEBUG_TIME
	return daq_time_start(ck_id);
	#else
	return 0;
	#endif
}

COMPILER_INLINE uint8_t iedf_debug_time_get(uint8_t ck_id) 
{
	#ifdef UWL_DEBUG_TIME
	return daq_time_get(ck_id, iedf_debug_stats.time_clock + ck_id);
	#else
	return 0;
	#endif
}


COMPILER_INLINE void iedf_debug_stat2str(uint8_t *out) 
{
	#ifdef UWL_DEBUG
	#ifdef UWL_DEBUG_TIME
	uint8_t i;
	#endif

	/* TODO: the escape mechanism must be done!!! */
	*(out++) = 0x3C;	/* HEADER */
	#ifdef UWL_DEBUG_TIME
	for (i = 0; i < UWL_DEBUG_TIME_CLOCK_NUMBER; i++, out+=DAQ_TIME_STRLEN) 
		daq_time_2str(iedf_debug_stats.time_clock + i, out);
	#endif /* UWL_DEBUG_TIME */
	*(out++) = 0x3E;	/* TRAILER */
	#endif /* UWL_DEBUG */
}

COMPILER_INLINE uint32_t iedf_debug_time_get_us(uint8_t ck_id) 
{
	#ifdef UWL_DEBUG_TIME
	daq_time_get(ck_id, iedf_debug_stats.time_clock + ck_id);
	return daq_time_2us(iedf_debug_stats.time_clock + ck_id);
	#else
	return 0;
	#endif
}

/** 
* @brief Write to the uWireless debug port
* 
* @param[in] msg The message to write
* @param[in] len The message length
* 
* @return A negative error code is return on failure, otherwise success.
*
* @pre 	The debug port must be properly initialized with the \ref iedf_debug_init
*	function. 
*/
int8_t iedf_debug_write(uint8_t *msg, uint16_t len);

/** 
* @brief Print to the uWireless debug port
* 
* @param[in] msg The message to write
* 
* @return A negative error code is return on failure, otherwise success.
*
* @pre 	The debug port must be properly initialized with the \ref iedf_debug_init
*	function. 
*
* \todo Write a comment to this function.
*/
int8_t iedf_debug_print(const char *msg);


COMPILER_INLINE void iedf_debug_sprint_u8(uint8_t data, char *out)
{
	out[3] = '\0';
	out[2] = '0' + (data % 10);
	out[1] = '0' + ((data / 10) % 10);
	out[0] = '0' + ((data / 100) % 10);
}

COMPILER_INLINE void iedf_debug_sprint_u16(uint16_t data, char *out)
{
	out[5] = '\0';
	out[4] = '0' + (data % 10);
	out[3] = '0' + ((data / 10) % 10);
	out[2] = '0' + ((data / 100) % 10);
	out[1] = '0' + ((data / 1000) % 10);
	out[0] = '0' + ((data / 10000) % 10);
}

COMPILER_INLINE void iedf_debug_sprint_u32(uint32_t data, char *out)
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

COMPILER_INLINE void iedf_debug_sprint_d8(int8_t data, char *out)
{
	out[4] = '\0';
	out[3] = '0' + (data % 10);
	out[2] = '0' + ((data / 10) % 10);
	out[1] = '0' + ((data / 100) % 10);
	out[0] = data < 0 ? '-' : ' ';
}

COMPILER_INLINE void iedf_debug_sprint_d16(int16_t data, char *out)
{
	out[6] = '\0';
	out[5] = '0' + (data % 10);
	out[4] = '0' + ((data / 10) % 10);
	out[3] = '0' + ((data / 100) % 10);
	out[2] = '0' + ((data / 1000) % 10);
	out[1] = '0' + ((data / 10000) % 10);
	out[0] = data < 0 ? '-' : ' ';
}

COMPILER_INLINE void iedf_debug_sprint_d32(int32_t data, char *out)
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
