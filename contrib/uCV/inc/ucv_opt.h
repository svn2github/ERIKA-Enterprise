/* Copyright (C) 
* 2010 - Christian Nastasi
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
* 
*/

/** 
* @file ucv_opt.h
* @brief uCV Library Optimization Utils file.
* @author Christian Nastasi
* @author Claudio Salvadori
* @version 0.1
* @date 2010-02-09
*/

/* SVN: $Id$
 *
 * $Log$
 */
#ifndef __ucv_opt_h__
#define __ucv_opt_h__

#include "ucv_types.h"

#if 	UCV_WORD_SIZE == 4	/* Machine Word Size = 4 -> 32bit CPU */

#define UCV_WORD_UNROLL_TARGET(s) 	(((s) >> __ucv_word_unroll) & 0xFF)	
#define UCV_WORD_UNROLL_INIT() 		register ucv_word_t __ucv_word_unroll
#ifndef UCV_WORD_BIG_ENDIAN	/* Default is LITTLE ENDIAN */
#define UCV_WORD_UNROLL(exp)	\
	__ucv_word_unroll = 0;	\
	exp;			\
	__ucv_word_unroll = 8;	\
	exp;			\
	__ucv_word_unroll = 16;	\
	exp;			\
	__ucv_word_unroll = 24;	\
	exp;				
#else 	/* if is BIG ENDIAN */
#define UCV_WORD_UNROLL(exp)	\
	__ucv_word_unroll = 24;	\
	exp;			\
	__ucv_word_unroll = 16;	\
	exp;			\
	__ucv_word_unroll = 8;	\
	exp;			\
	__ucv_word_unroll = 0;	\
	exp;				
#endif	/* Endianess Check */

#elif 	UCV_WORD_SIZE == 2	/* Machine Word Size = 2 -> 16bit CPU */

#define UCV_WORD_UNROLL_TARGET(s) 	(((s) >> __ucv_word_unroll) & 0xFF)	
#define UCV_WORD_UNROLL_INIT() 		register ucv_word_t __ucv_word_unroll
#ifndef UCV_WORD_BIG_ENDIAN	/* Default is LITTLE ENDIAN */
#define UCV_WORD_UNROLL(exp)	\
	__ucv_word_unroll = 0;	\
	exp;			\
	__ucv_word_unroll = 8;	\
	exp;			
#else 	/* if is BIG ENDIAN */
#define UCV_WORD_UNROLL(exp)	\
	__ucv_word_unroll = 8;	\
	exp;			\
	__ucv_word_unroll = 0;	\
	exp;				
#endif	/* Endianess Check */

#elif 	UCV_WORD_SIZE == 1	/* Machine Word Size = 1 -> 8bit CPU */

#define UCV_WORD_UNROLL_TARGET(s) 	(s)	
#define UCV_WORD_UNROLL_INIT() 		
#define UCV_WORD_UNROLL(exp)		exp;

#else
#error "uCV Library ERROR: wrong UCV_WORD_SIZE."
#endif	/* UCW_WORD_SIZE */

#define UCV_LOOP_UNROLL_8(exp)	\
	exp;\
	exp;\
	exp;\
	exp;\
	exp;\
	exp;\
	exp;\
	exp;\

#define UCV_LOOP_UNROLL_8_ROUNDS(count) (((count) / 8) * 8)

#define UCV_LOOP_UNROLL_8_DO_RESIDUALS(count, exp)	\
	switch ((count)) {				\
	case 7 : exp;					\
	case 6 : exp;					\
	case 5 : exp;					\
	case 4 : exp;					\
	case 3 : exp;					\
	case 2 : exp;					\
	case 1 : exp;					\
	}						\


#define UCV_LOOP_UNROLL_8_DO_ALL(cond1, res, exp_pre, exp_in, exp_post) \
	while (cond1) {							\
		exp_pre;						\
		UCV_LOOP_UNROLL_8(exp_in);				\
		exp_post;						\
	}								\
	if ((res)) {							\
		exp_pre;						\
		switch ((res)) {					\
		case 7 : exp_in;					\
		case 6 : exp_in;					\
		case 5 : exp_in;					\
		case 4 : exp_in;					\
		case 3 : exp_in;					\
		case 2 : exp_in;					\
		case 1 : exp_in;					\
		}							\
		exp_post;						\
	}								\

#define UCV_LOOP_UNROLL_16(exp)	\
	exp;\
	exp;\
	exp;\
	exp;\
	exp;\
	exp;\
	exp;\
	exp;\
	exp;\
	exp;\
	exp;\
	exp;\
	exp;\
	exp;\
	exp;\
	exp;\

#define UCV_LOOP_UNROLL_15(exp)	\
	exp;\
	exp;\
	exp;\
	exp;\
	exp;\
	exp;\
	exp;\
	exp;\
	exp;\
	exp;\
	exp;\
	exp;\
	exp;\
	exp;\
	exp;\

#endif /* __ucv_opt_h__*/
