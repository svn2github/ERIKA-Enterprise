/**
 * @brief Definitions of (some) ISO types
 *
 * @author  Bernardo  Dal Seno
 *
 * Copyright (C) 2010 Evidence srl
 *
 * Derived from  contrib/drivers/camera/hv7131gp/inc/hv7131gp_compiler_ee.h
 */

#ifndef __INCLUDE_CONTRIB_MISC_EE_STDINT_H__
#define __INCLUDE_CONTRIB_MISC_EE_STDINT_H__

#include <ee.h>

#if defined(__PIC32__) && defined(__GNUC__)
/* When supported, include stdint.h to avoid conflicting definitions of
 * exact-size types. */
#include <stdint.h>
#else

/** 
* @name Basic type representations.
* @{ */

#ifndef UINT8_T
#define UINT8_T
typedef EE_UINT8 uint8_t;	/**< Unsigned 8 bit integer. */
#endif

#ifndef UINT16_T
#define UINT16_T
typedef EE_UINT16 uint16_t;	/**< Unsigned 16 bit integer. */
#endif

#ifndef UINT32_T
#define UINT32_T
typedef EE_UINT32 uint32_t;	/**< Unsigned 32 bit integer. */
#endif

#ifndef INT8_T
#define INT8_T
typedef EE_INT8 int8_t;		/**< Signed 8 bit integer. */
#endif

#ifndef INT16_T
#define INT16_T
typedef EE_INT16 int16_t;	/**< Signed 16 bit integer. */
#endif

#ifndef INT32_T
#define INT32_T
typedef EE_INT32 int32_t;	/**< Signed 32 bit integer. */
#endif

/* Some guesswork is needed here, as 64-bit types are not standard */
#include <limits.h>

#ifndef UINT64_T
#ifdef ULLONG_MAX
#if ULLONG_MAX != 4294967295UL
#define UINT64_T
typedef unsigned long long uint64_t;	/**< Unsigned 64 bit integer. */
#endif
#endif /* ULLONG_MAX */
#if ! defined(UINT64_T) && defined(__LONG_LONG_MAX__)
/* Gcc built-in macro __LONG_LONG_MAX__ is only signed */
#if __LONG_LONG_MAX__ != 2147483647L
#define UINT64_T
typedef unsigned long long uint64_t;	/**< Unsigned 64 bit integer. */
#endif
#endif /*  __LONG_LONG_MAX__ */
#ifndef UINT64_T
#error "No known way to define an unsigned 64-bit type"
#endif
#endif /* ifndef UINT64_T */

#ifndef INT64_T
#ifdef LLONG_MAX
#if LLONG_MAX != 4294967295UL
#define INT64_T
typedef long long int64_t;	/**< Unsigned 64 bit integer. */
#endif
#endif /* ULLONG_MAX */
#if ! defined(INT64_T) && defined(__LONG_LONG_MAX__)
#if __LONG_LONG_MAX__ != 2147483647L
#define INT64_T
typedef long long int64_t;	/**< Unsigned 64 bit integer. */
#endif
#endif /*  __LONG_LONG_MAX__ */
#ifndef UINT64_T
#error "No known way to define an unsigned 64-bit type"
#endif
#endif /* ifndef INT64_T */

#endif /* No <stdint.h> */

/**  @} */

#endif /* __INCLUDE_CONTRIB_MISC_EE_STDINT_H__ */
