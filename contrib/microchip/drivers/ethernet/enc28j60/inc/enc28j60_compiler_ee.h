/*
  Name: enc28j60_compiler_ee.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: ENC28J60 driver header file for EE compiler settings.
*/

#ifndef __enc28j60_compiler_ee_h__
#define __enc28j60_compiler_ee_h__

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

// TODO: Create EE_UINT64?
#ifndef UINT64_T
#define UINT64_T
typedef unsigned long long uint64_t;	/**< Unsigned 64 bit intgerer. */
#endif

#ifndef INT8_T
#define INT8_T
typedef EE_INT8 int8_t;		/**< Unsigned 8 bit intgerer. */
#endif

#ifndef INT16_T
#define INT16_T
typedef EE_INT16 int16_t;	/**< Unsigned 16 bit intgerer. */
#endif

// TODO: Create EE_INT64?
#ifndef INT64_T
#define INT64_T
typedef signed long long int64_t;	/**< Unsigned 64 bit intgerer. */
#endif
/**  @} */

#ifndef COMPILER_INLINE 
#define COMPILER_INLINE __INLINE__
#endif

#ifndef COMPILER_ISR
#define COMPILER_ISR(func) ISR2(func)
#endif

/** T Y P E S   D E F I N I T I O N S **************************************/
// #include "GenericTypeDefs.h", not allowed...

/* BOOL, BYTE, WORD, DWORD */
typedef enum _BOOL { FALSE = 0, TRUE } BOOL;	// Undefined size
typedef uint8_t		BYTE;						// 8-bit unsigned
typedef uint16_t	WORD;						// 16-bit unsigned
typedef uint32_t	DWORD;						// 32-bit unsigned

/* BYTE_VAL */
#ifdef BIG_ENDIAN
typedef union _BYTE_VAL
{
    BYTE Val;
    struct
    {
        unsigned char b7:1;
        unsigned char b6:1;
        unsigned char b5:1;
        unsigned char b4:1;
        unsigned char b3:1;
        unsigned char b2:1;
        unsigned char b1:1;
        unsigned char b0:1;
    } bits;
} BYTE_VAL;
#else
typedef union _BYTE_VAL
{
    BYTE Val;
    struct
    {
        unsigned char b0:1;
        unsigned char b1:1;
        unsigned char b2:1;
        unsigned char b3:1;
        unsigned char b4:1;
        unsigned char b5:1;
        unsigned char b6:1;
        unsigned char b7:1;
    } bits;
} BYTE_VAL, BYTE_BITS;
#endif

/* WORD_VAL */
#ifdef BIG_ENDIAN
typedef union _WORD_VAL
{
    WORD Val;
    BYTE v[2];
    struct
    {
        BYTE HB;
        BYTE LB;
    } byte;
    struct
    {
        unsigned char b15:1;
        unsigned char b14:1;
        unsigned char b13:1;
        unsigned char b12:1;
        unsigned char b11:1;
        unsigned char b10:1;
        unsigned char b9:1;
        unsigned char b8:1;
        unsigned char b7:1;
        unsigned char b6:1;
        unsigned char b5:1;
        unsigned char b4:1;
        unsigned char b3:1;
        unsigned char b2:1;
        unsigned char b1:1;
        unsigned char b0:1;
    } bits;
} WORD_VAL;
#else
typedef union _WORD_VAL
{
    WORD Val;
    BYTE v[2];
    struct
    {
        BYTE LB;
        BYTE HB;
    } byte;
    struct
    {
        unsigned char b0:1;
        unsigned char b1:1;
        unsigned char b2:1;
        unsigned char b3:1;
        unsigned char b4:1;
        unsigned char b5:1;
        unsigned char b6:1;
        unsigned char b7:1;
        unsigned char b8:1;
        unsigned char b9:1;
        unsigned char b10:1;
        unsigned char b11:1;
        unsigned char b12:1;
        unsigned char b13:1;
        unsigned char b14:1;
        unsigned char b15:1;
    } bits;
} WORD_VAL, WORD_BITS;
#endif

/* DWORD_VAL */
#ifdef BIG_ENDIAN
typedef union _DWORD_VAL
{
    DWORD Val;
	WORD w[2];
    BYTE v[4];
    struct
    {
        WORD HW;
        WORD LW;
    } word;
    struct
    {
		BYTE MB;
		BYTE UB;
		BYTE HB;
		BYTE LB;
    } byte;
    struct
    {
        WORD_VAL high;
        WORD_VAL low;
    }wordUnion;
    struct
    {
        unsigned char b31:1;
        unsigned char b30:1;
        unsigned char b29:1;
        unsigned char b28:1;
        unsigned char b27:1;
        unsigned char b26:1;
        unsigned char b25:1;
        unsigned char b24:1;
        unsigned char b23:1;
        unsigned char b22:1;
        unsigned char b21:1;
        unsigned char b20:1;
        unsigned char b19:1;
        unsigned char b18:1;
        unsigned char b17:1;
        unsigned char b16:1;
        unsigned char b15:1;
        unsigned char b14:1;
        unsigned char b13:1;
        unsigned char b12:1;
        unsigned char b11:1;
        unsigned char b10:1;
        unsigned char b9:1;
        unsigned char b8:1;
        unsigned char b7:1;
        unsigned char b6:1;
        unsigned char b5:1;
        unsigned char b4:1;
        unsigned char b3:1;
        unsigned char b2:1;
        unsigned char b1:1;
        unsigned char b0:1;
    } bits;
} DWORD_VAL;
#else
typedef union _DWORD_VAL
{
    DWORD Val;
	WORD w[2];
    BYTE v[4];
    struct
    {
        WORD LW;
        WORD HW;
    } word;
    struct
    {
        BYTE LB;
        BYTE HB;
        BYTE UB;
        BYTE MB;
    } byte;
    struct
    {
        WORD_VAL low;
        WORD_VAL high;
    }wordUnion;
    struct
    {
        unsigned char b0:1;
        unsigned char b1:1;
        unsigned char b2:1;
        unsigned char b3:1;
        unsigned char b4:1;
        unsigned char b5:1;
        unsigned char b6:1;
        unsigned char b7:1;
        unsigned char b8:1;
        unsigned char b9:1;
        unsigned char b10:1;
        unsigned char b11:1;
        unsigned char b12:1;
        unsigned char b13:1;
        unsigned char b14:1;
        unsigned char b15:1;
        unsigned char b16:1;
        unsigned char b17:1;
        unsigned char b18:1;
        unsigned char b19:1;
        unsigned char b20:1;
        unsigned char b21:1;
        unsigned char b22:1;
        unsigned char b23:1;
        unsigned char b24:1;
        unsigned char b25:1;
        unsigned char b26:1;
        unsigned char b27:1;
        unsigned char b28:1;
        unsigned char b29:1;
        unsigned char b30:1;
        unsigned char b31:1;
    } bits;
} DWORD_VAL;
#endif

#endif /* Header Protection */
