/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation, 
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/**
 * @brief Definitions of (some) ISO types
 *
 * @author  Bernardo  Dal Seno
 *
 * Copyright (C) 2011 Evidence srl
 */

#ifndef __INCLUDE_CPU_COMMON_EE_STDINT_H__
#define __INCLUDE_CPU_COMMON_EE_STDINT_H__

#if (defined(__PIC32__) && defined(__GNUC__))
/* When supported, include stdint.h to avoid conflicting definitions of
 * exact-size types. */
#include <stdint.h>

#else
/* No stdint.h.  Define types through educated guesses */

#include <limits.h>

/** 
* @name Basic type representations.
* @{ */

#if SCHAR_MAX == 127
#ifndef UINT8_T
#define UINT8_T
typedef unsigned char uint8_t;	/**< Unsigned 8 bit integer. */
#endif

#ifndef INT8_T
#define INT8_T
typedef signed char int8_t;		/**< Signed 8 bit integer. */
#endif
#else
#error Unable to define a 8-bit types
#endif

#if INT_MAX == 32767 /* 16-bit architecture */
#define __EE_INT16 int
#define __EE_UINT16 unsigned int
#define __EE_INT32 long
#define __EE_UINT32 unsigned long
#elif (INT_MAX == 2147483647) && (SHRT_MAX == 32767) /* 32-bit architecture */
#define __EE_INT16 short
#define __EE_UINT16 unsigned short
#define __EE_INT32 int
#define __EE_UINT32 unsigned int
#else /* Unknown architecture */
#error Unknown/unsupported architecture
#endif


#ifndef UINT16_T
#define UINT16_T
typedef __EE_UINT16 uint16_t;	/**< Unsigned 16 bit integer. */
#endif

#ifndef UINT32_T
#define UINT32_T
typedef __EE_UINT32 uint32_t;	/**< Unsigned 32 bit integer. */
#endif

#ifndef INT16_T
#define INT16_T
typedef __EE_INT16 int16_t;	/**< Signed 16 bit integer. */
#endif

#ifndef INT32_T
#define INT32_T
typedef __EE_INT32 int32_t;	/**< Signed 32 bit integer. */
#endif

/* Some real guesswork is needed here, as 64-bit types are not standard */
#ifndef __EE_STDINT_SKIP_64BIT__

#ifndef UINT64_T
#ifdef ULLONG_MAX
#warning ULLONG_MAX
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
#error "No known way to define a signed 64-bit type"
#endif
#endif /* ifndef INT64_T */

#endif /* __EE_STDINT_SKIP_64BIT__ */

#endif /* No <stdint.h> */

/**  @} */

#endif /* __INCLUDE_CPU_COMMON_EE_STDINT_H__ */