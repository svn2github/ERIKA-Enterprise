/** 
* @file lwip_debug.c
* @brief Debug Module Implementation
* @author Christian Nastasi, Dario Di Stefano
* @version 0.1
* @date 2009-06-22
*/

#include <util/lwip_debug.h>
#include <string.h>

#ifdef LWIP_DEBUG
/* TODO: chris: shall waste memory for this check variable or not? */
static uint8_t debug_initialized = 0; 
#endif

int8_t lwip_debug_init(void)
{
	#ifdef LWIP_DEBUG
	debug_initialized = 0;
	console_descriptor_t *des = NULL;
	#ifdef LWIP_DEBUG_SERIAL 
	des = console_serial_config(LWIP_DEBUG_SERIAL_PORT, 
								LWIP_DEBUG_SERIAL_BAUDRATE,
								LWIP_DEBUG_SERIAL_OPT);
	#endif
	if (des == NULL)
		return -1;
	if (console_init(LWIP_DEBUG_CONSOLE, des) < 0)
		return -1;
	debug_initialized = 1;
	return console_open(LWIP_DEBUG_CONSOLE);
	#else
	return 1;
	#endif /* LWIP_DEBUG */
}

int8_t lwip_debug_write(char *msg, uint16_t len) 
{
	#ifdef LWIP_DEBUG
	if (debug_initialized)
		return console_write(LWIP_DEBUG_CONSOLE, (const uint8_t *)msg, len);
	return -1;
	#else
	return 0;
	#endif /* LWIP_DEBUG */
}

s8_t lwip_debug_printf(const char* format, ...)
{
	#define MAXCHARS 128
	char str[MAXCHARS];
	
	va_list args;
	va_start( args, format );
	vsnprintf(str, MAXCHARS, format, args);
	va_end( args );
	return lwip_debug_write(str, strlen(str));
}

#ifdef DO_CASE_STRCPY 	
#undef DO_CASE_STRCPY 	
#endif

#define DO_CASE_STRCPY(x, out) 	\
case x:				\
strcpy((out), #x);		\
break;				\


