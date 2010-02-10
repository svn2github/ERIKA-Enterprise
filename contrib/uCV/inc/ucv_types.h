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
* @file ucv_types.h
* @brief Types definitions and helper macros for the uCV library.
* @author Christian Nastasi
* @author Claudio Salvadori
* @version 0.1
* @date 2010-02-09
*/

/* SVN: $Id$
 *
 * $Log$
 */
#ifndef __ucv_types_h__
#define __ucv_types_h__

#include <arch/ucv_compiler.h>

/**
* @name Basic data representation
* @{ */
typedef uint16_t ucv_coord_t;	/**< Image Coordinate Type. */
typedef ureg_t ucv_word_t;	/**< Word of the size of a machine register.*/
#define UCV_BIT_START_MASK	(~(((ucv_word_t)-1) >> 1)) 
#define UCV_POS(i, j, w) (((i) * (w)) + (j))
/**  @} */

/**
* @name Macro for Bit Array Addressing
* @{ */
/**
* @brief Initialize bit array access params
*
* \b IMPORTANT: this macro declares two variables named \p word and \p mask.
*  Use it in the variables definition section.
*
* @param byte Name for the current word pointer.
* @param mask Name for the bit mask to access the single bit; 
*	      initialized to 128 (binary 10000000).
* @param init The word pointer to initialize the \p word.
*/
#define UCV_BIT_INIT(word, mask, init)	\
ucv_word_t mask = UCV_BIT_START_MASK;	\
ucv_word_t *word = (ucv_word_t*)(init);	\

/**
* @brief Go to Next Bit
*
* Rotate right (shift) the mask bit and increase the current word pointer.
*
* @param word The current word pointer.
* @param mask The bit mask.
*/
#define UCV_BIT_NEXT(word, mask)		\
do {						\
	(mask) >>= 1;				\
	if(!(mask)) {				\
		(mask) = UCV_BIT_START_MASK;	\
		(word)++;			\
	}					\
} while (0)					\

/**
* @brief Go to Previous Bit
*
* Rotate left (shift) the mask bit and decrease for the current word pointer.
*
* @param word The current word pointer.
* @param mask The bit mask.
*/
#define UCV_BIT_PREV(word, mask)\
do {				\
	(mask) <<= 1;		\
	if(!(mask)) {		\
		(mask) = 1;	\
		(word)--;	\
	}			\
} while (0)			\

/**
* @brief Go to the specific Bit Position
*
* @param word The current word pointer.
* @param mask The bit mask.
* @param im The start word pointer.
* @param pos The required 0-based bit position in the bit array (0 to N-1).
*/
#define UCV_BIT_GOTO(word, mask, im, pos)				\
do {									\
	(word) = ((ucv_word_t*)(im)) + 					\
		 (((uint32_t)(pos)) >> (3 * sizeof(ucv_word_t)));	\
	(mask) = UCV_BIT_START_MASK;					\
	(mask) >>= (pos) % (8 * sizeof(ucv_word_t));			\
} while (0)								\


/**
* @brief Get the current bit value
*
* @param word The current word pointer.
* @param mask The bit mask.
*
*/
#define UCV_BIT_GET(word, mask)	((*(word)) & (mask))

/**
* @brief Set to 1 the current bit value
*
* @param word The current word pointer.
* @param mask The bit mask.
*
*/
#define UCV_BIT_SET(word, mask)	((*(word)) |= (mask))

/**
* @brief Reset to 0 the current bit value
*
* @param word The current word pointer.
* @param mask The bit mask.
*
*/
#define UCV_BIT_CLR(word, mask)	((*(word)) &= (~(mask)))
/**  @} */

/**
* @brief Exit status codes, returned has negative values
*/
enum {
	UCV_ERR_FAILURE = 1,	/*!< General Error code. */
	UCV_ERR_BAD_IMAGE_TYPE,	/*!< Invalid image type. */
	UCV_ERR_UNIMPLEMENTED,	/*!< Functionality not implemented. */
};

/**
* @brief Image types
*
* - \ref UCV_GRAY_8U is an unsigned 8-bit single channel image with pixel range
*   [0 255]; the required space is \f$ width \times height \f$ bytes; \n
* - \ref UCV_RGB_24U see \ref Mv_Rgb;
*   the required space is \f$ width \times height \times 3 \f$ bytes; \n
* - \ref UCV_RGB_16U see \ref Mv_Rgb16;
*   the required space is \f$ width \times height \times 2 \f$ bytes; \n
* - \ref UCV_BW_BIN is a binary 1-bit single channel image with values 
*   0=background, 1=foreground; the required space is 
*   \f$ \lceil(width \times height)/(8 \times sizeof(ucv\_word\_t)\rceil \f$ 
*   bytes due to bit array usage.\n
*
* See the corresponding utility macros that calculate the required space.
*/
enum {
	UCV_GRAY_8U = 0,/**< 8-bit Gray Scale Image */
	UCV_RGB_24U,	/**< RGB 24-bit Color Image */
	UCV_RGB_16U,	/**< RGB 16-bit Color Image */
	UCV_BW_BIN	/**< B/W Image */
} ucv_image_type_t;

/**
* @name Byte sizes for Image Types
* @{ */
#define UCV_GRAY_8U_SIZE(w, h)	\
	((w) * (h))		\
	/**< Get the \ref UCV_GRAY_8U image size in byte */
#define UCV_RGB_24U_SIZE(w, h)	\
	((w) * (h) * 3)		\
	/**< Get the \ref UCV_RGB_24U image size in byte */
#define UCV_RGB_16U_SIZE(w, h)	\
	((w) * (h) * 2)		\
	/**< Get the \ref UCV_RGB_16U image size in byte */
#define UCV_BW_BIN_SIZE(w, h)					\
	(((((w) * (h)) - 1) / (8 * sizeof(ucv_word_t))) + 1)	\
	/**< Get the \ref UCV_BW_BIN image size in byte */
/**  @} */

/**
* @brief Image data type
*/
typedef struct {
	uint8_t *image;		/**< Image data pointer */
	uint8_t type;		/**< Image type */
	ucv_coord_t width;	/**< Image width */
	ucv_coord_t height;	/**< Image height */
} ucv_image_t;

/**
* @name Image properties retrieval
*\todo Write documentation for these macros.
* @{ */
#define UCV_IMAGE_DATA(im) 	((im).image)
#define UCV_IMAGE_TYPE(im) 	((im).type)
#define UCV_IMAGE_WIDTH(im) 	((im).width)
#define UCV_IMAGE_HEIGHT(im) 	((im).height)
/* @} */

/**
* @brief The ROI data type
*/
typedef struct {
	ucv_coord_t tl_x;	/**< Top-Left X ucv_coord_t */
	ucv_coord_t tl_y;	/**< Top-Left Y ucv_coord_t */
	ucv_coord_t br_x;	/**< Bottom-Right X ucv_coord_t */
	ucv_coord_t br_y;	/**< Bottom-Right Y ucv_coord_t */
} ucv_roi_t;

#endif /* __ucv_types_h__ */
