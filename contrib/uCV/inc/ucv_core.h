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
* @file ucv_core.h
* @brief uCV Library core APIs file.
* @author Christian Nastasi
* @author Claudio Salvadori
* @version 0.1
* @date 2010-02-09
*/

/* SVN: $Id$
 *
 * $Log$
 */
#ifndef __ucv_core_h__
#define __ucv_core_h__

#include "ucv_types.h"
/** 
* @name Image Basic Functions
* @{ */

#define UCV_BW_BIN_DEFINE(image_name, w, h)				\
ucv_word_t image_name##_data_storage[UCV_BW_BIN_SIZE(w, h)];	\
ucv_image_t image_name = {						\
	.image = (uint8_t*) image_name##_data_storage,			\
	.width = w,							\
	.height = h,							\
	.type = UCV_BW_BIN,						\
}									\

/** 
* @brief Initialize a \ref ucv_image_t image.
*
* This function does not allocate memory, but just initialize the 
* \ref ucv_image_t data structure with proper values.
* See \ref ucv_image_type_t for the size requirement of the \p buff parameter.
*
* @param[out]	 im	Reference to the image to initialize.
* @param[in]	 width	Image width.
* @param[in]	 height Image height.
* @param[in]	 type	Image type, see \ref ucv_image_type_t.
* @param[in]	 buff	Reference to a memory space used to store image bytes.
* 
* @return 
*/
COMPILER_INLINE void ucv_image_create(ucv_image_t *im, ucv_coord_t width, 
				      ucv_coord_t height, uint8_t type,
				      uint8_t *buff)
{
	im->width = width;
	im->height = height;
	im->type = type;
	im->image = buff;
}

/** 
* @brief Set the ROI 
*
* @param[out] 	roi Reference to the ROI box to set.
* @param[in] 	tlx Top Left X coordinate.
* @param[in] 	tly Top Left Y coordinate.
* @param[in] 	brx Bottom Right X coordinate.
* @param[in] 	bry Bottom Right Y coordinate.
*/
COMPILER_INLINE void ucv_roi_set(ucv_roi_t *roi, ucv_coord_t tlx, 
				 ucv_coord_t tly, ucv_coord_t brx, 
				 ucv_coord_t bry)	
{
	roi->tl_x = tlx;
	roi->tl_y = tly;
	roi->br_x = brx;
	roi->br_y = bry;
}

/** 
* @brief Set the ROI 
*
* @param[in] 	roi Reference to the ROI box to set.
* @param[out] 	tlx Top Left X coordinate.
* @param[out] 	tly Top Left Y coordinate.
* @param[out] 	brx Bottom Right X coordinate.
* @param[out] 	bry Bottom Right Y coordinate.
*/
COMPILER_INLINE void ucv_roi_get(ucv_roi_t *roi, ucv_coord_t *tlx, 
				 ucv_coord_t *tly, ucv_coord_t *brx, 
				 ucv_coord_t *bry)	
{
	*tlx = roi->tl_x;
	*tly = roi->tl_y;
	*brx = roi->br_x;
	*bry = roi->br_y;
}

/** 
* @brief Set a squared ROI in a specific hook position 
*
* \b IMPORTANT: the coherency of the parameters MUST be checked by the callee.
*
* The square might be truncated if the ROI attempts to exceed the image margins.
* 
* @param[out]	roi	Reference to the ROI box to set.
* @param[in] 	x_hook 	X coordinate to for the square center.
* @param[in] 	y_hook  Y coordinate to for the square center.
* @param[in] 	size	Length of the square side (should be odd).
* @param[in] 	image_w Image width margin.	
* @param[in] 	image_h Image height margin.	
*/
COMPILER_INLINE void ucv_roi_square(ucv_roi_t *roi, ucv_coord_t x_hook, 
				    ucv_coord_t y_hook, ucv_coord_t size, 
				    ucv_coord_t image_w, ucv_coord_t image_h)
{
	size >>= 1;	/* Half-Size */
	roi->tl_x = (x_hook > size) ? x_hook - size : 0;
	roi->tl_y = (y_hook > size) ? y_hook - size : 0;
	roi->br_x = (x_hook < image_w) - size ?  x_hook + size : image_w - 1;
	roi->br_y = (y_hook < image_h) - size ?  y_hook + size : image_h - 1;
}

/** 
* @brief B/W Image Centroid
* 
*
* @param bw A \ref UCV_BW_BIN image to be processed
* @param x The result X coordinate for the centroid
* @param y The result Y coordinate for the centroid
* @param window The ROI window to limit the elaboration, \c NULL means do not use any ROI
* @param min_area Min area in pixel to compute the centroid, \ref UCV_MIN_OBJECT_AREA could be used
*
* @return \ref UCV_SUCCESS on success, \ref UCV_FAILURE on failure
*/

/** 
* @brief B/W Image Centroid
* 
* Calculates the centroid for the foreground(W) in the B/W image.\n
* If \p roi is \c NULL the ROI is the whole image.\n
* On failure x, y and area are unchanged.
* 
* \todo Extension of centroid to gray-scale image (should be center of mass).
* 
* @param[in] 	im	Reference to source the image.
* @param[out]	x	Reference to store the X coordiante of the centroid.
* @param[out]	y	Reference to store the Y coordiante of the centroid.
* @param[in]	roi	Reference to a ROI.
* 
* @return 	\todo
*/
int8_t ucv_centroid(ucv_image_t *im, ucv_coord_t *x, ucv_coord_t *y, 
		    ucv_roi_t *roi);

enum {
	UCV_BINARIZE_GRAY_LVALUE = 0,	/**<Gray-Level less than value.*/
	UCV_BINARIZE_GRAY_GVALUE, 	/**<Gray-Level greather than value.*/
	UCV_BINARIZE_GRAY_IN_INTERVAL, 	/**<Gray-Level in interval values.*/
	UCV_BINARIZE_GRAY_OUT_INTERVAL,	/**<Gray-Level out of interval values.*/
} ucv_binarize_types_t ;

/** 
* @brief Image binarization with threshold
*
* Perform image binarization according to specific thresholding method. 
* See binarization \ref ucv_binarize_types_t for a list of valid binarization
* mechanisms.\n
* The output can be either \p src or \p dst. Specifically:
* - if <c> dst != NULL </c> the output is written to \p dst that MUST be a valid
*   reference to a \ref UCV_BW_BIN image.
* - if <c> dst == NULL </c> the output is written to \p src accordingly to the
*   image type.
*   \todo Say more about the way the output is written in \p src.
* 
* @param[in,out] src	Reference to source the image.
* @param[out] 	 dst	Reference to destination \ref UCV_BW_BIN the image.
* @param[in]	 bin_type	Type of thresholding to use for binarization.
* @param[in]	 threshold	Reference to a valid threshold with respect to
*				to \p threshold_type.
*
* @return	\todo
*/
int8_t ucv_binarize(ucv_image_t *src, ucv_image_t *dst, uint8_t bin_type,
		    void *threshold);
/**  @} */

#endif /* __ucv_core_h__*/
