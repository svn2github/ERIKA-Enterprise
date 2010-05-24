/** 
* @file uwl_mac_marshalling.h
* @brief Marshalling process for storage and transmission
* @author Dario Di Stefano
* @version 0.1
* @date 2009-06-22
*/
#ifndef __uwl_mac_marshalling_h__
#define __uwl_mac_marshalling_h__

#include <kal/uwl_kal.h>

#ifdef __LM32__
#ifndef BIG_ENDIAN
#define BIG_ENDIAN
#endif
#endif

#ifdef BIG_ENDIAN

/* Host to net function (BIG_ENDIAN case) */
COMPILER_INLINE void hton(uint8_t* dst, uint8_t* src, int len)
{
	int i;
	
	for(i=0; i<len; i++)
		dst[i] = src[len-1-i];
	
	return;
}

#else // LITTLE_ENDIAN

/* Host to net function (LITTLE_ENDIAN case) */
COMPILER_INLINE void hton(uint8_t* dst, uint8_t* src, int len)
{
	int i;
	
	for(i=0; i<len; i++)
		dst[i] = src[i];
	
	return;
}

#endif

/* Net to host macro */
#define ntoh(dst, src, len) 			hton( (dst), (src), (len) )

#endif /* Header Protection */
