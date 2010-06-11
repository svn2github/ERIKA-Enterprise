/** 
* @file lwip_debug.c
* @brief Debug Module Implementation
* @author Christian Nastasi, Dario Di Stefano
* @version 0.1
* @date 2009-06-22
*/

#include <util/lwip_debug.h>
#include <string.h>

#ifdef LWIP_DEBUG_LOG
/* TODO: chris: shall waste memory for this check variable or not? */
static uint8_t debug_initialized = 0; 
#endif

#define LWIP_DEBUG_LOG_CONSOLE 0

int8_t lwip_debug_init(void)
{
	#ifdef LWIP_DEBUG_LOG
	debug_initialized = 0;
	console_descriptor_t *des = NULL;
	#ifdef LWIP_DEBUG_LOG_SERIAL 
	des = console_serial_config(LWIP_DEBUG_LOG_SERIAL_PORT, 
								LWIP_DEBUG_LOG_SERIAL_BAUDRATE,
								LWIP_DEBUG_LOG_SERIAL_OPT);
	#endif
	if (des == NULL)
		return -1;
	if (console_init(LWIP_DEBUG_LOG_CONSOLE, des) < 0)
		return -1;
	debug_initialized = 1;
	return console_open(LWIP_DEBUG_LOG_CONSOLE);
	#else
	return 1;
	#endif /* LWIP_DEBUG_LOG */
}

int8_t lwip_debug_write(uint8_t *msg, uint16_t len) 
{
	#ifdef LWIP_DEBUG_LOG
	if (debug_initialized)
		return console_write(LWIP_DEBUG_LOG_CONSOLE, msg, len);
	return -1;
	#else
	return 0;
	#endif /* LWIP_DEBUG_LOG */
}

int8_t lwip_debug_print(const char *msg) 
{
	#ifdef LWIP_DEBUG_LOG_HAS_PRINT
	int8_t retv = 0;
	const char *m = "\n\rLWIP_DEBUG_LOG: ";

	if (debug_initialized) {
		retv = console_write(LWIP_DEBUG_LOG_CONSOLE, (uint8_t *) m, 
				     strlen(m));
		if (retv < 0)
			return retv;
		return console_write(LWIP_DEBUG_LOG_CONSOLE, (uint8_t *) msg, 
				     strlen(msg));
	}
	return -1;
	#else
	return 1;
	#endif /* LWIP_DEBUG_LOG_HAS_PRINT */
}

#ifdef DO_CASE_STRCPY 	
#undef DO_CASE_STRCPY 	
#endif

#define DO_CASE_STRCPY(x, out) 	\
case x:				\
strcpy((out), #x);		\
break;				\


