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
* @file ucv_morph.h
* @brief uCV Library morph APIs file.
* @author Christian Nastasi
* @author Claudio Salvadori
* @version 0.1
* @date 2010-02-09
*/

/* SVN: $Id$
 *
 * $Log$
 */
#ifndef __ucv_morph_h__
#define __ucv_morph_h__

#include "ucv_types.h"
/** 
* @name Mathematical Morphology Functions
*
* @{ */
/** 
* @brief Binary Negation
*
* Negate a binary image, the images MUST be of type \ref UCV_BW_BIN.\n
* If <c> dst == NULL </c> the output shall be written on src, otherwise on dst.
*
* @param[in,out] src Reference to the source image.
* @param[out]	 dst Reference to the destination image.
* 
* @return \todo
*/
int8_t ucv_mm_negate(ucv_image_t *src, ucv_image_t *dst);

/** 
* @brief Morphological Erosion
*
* Perform Binary Erosion
* 
* @param bw A \ref UCV_BW_BIN image to process
* @param window A ROI to reduce elaboration
* @param buffer The memory space to store a temporary \ref UCV_BW_BIN image data
*/

/** 
* @brief Morphological Erosion
* 
* Perform binary erosion, the images MUST be of type \ref UCV_BW_BIN.\n
* If \p roi is \c NULL the ROI is the whole image.\n
* 
* \b IMPORTANT: The \p src and \p dst image references MUST point to different
* images to properly perfom this operation.
*
* @param[in]	src Reference to the source image.
* @param[out]	dst Reference to the destination image.
* @param[in] 	roi Reference to a ROI.
* 
* @return \todo
*/
int8_t ucv_mm_erode(ucv_image_t *src, ucv_image_t *dst, ucv_roi_t *roi);

/** 
* @brief Morphological Dilation
*
* Perform Binary Dilation
* 
* @param bw A \ref UCV_BW_BIN image to process
* @param window A ROI to reduce elaboration
* @param buffer The memory space to store a temporary \ref UCV_BW_BIN image data
*/

/** 
* @brief Morphological Dilation
* 
* Perform binary dilation, the images MUST be of type \ref UCV_BW_BIN.\n
* If \p roi is \c NULL the ROI is the whole image.\n
* 
* \b IMPORTANT: The \p src and \p dst image references MUST point to different
* images to properly perfom this operation.
*
* @param[in]	src Reference to the source image.
* @param[out]	dst Reference to the destination image.
* @param[in] 	roi Reference to a ROI.
* 
* @return \todo
*/
int8_t ucv_mm_dilate(ucv_image_t *src, ucv_image_t *dst, ucv_roi_t *roi);

/** 
* @brief Morphological Opening 
*
* Perform Binary Opening.\n
* @param bw A \ref UCV_BW_BIN image to process
* @param window A ROI to reduce elaboration
* @param buffer The memory space to store a temporary \ref UCV_BW_BIN image data
*/

/** 
* @brief Morphological Opening
* 
* Perform binary Opening, the images MUST be of type \ref UCV_BW_BIN.\n
* Logically this can be considered as a \ref ucv_mm_erode followed by a 
* \ref ucv_mm_dilate, but this function performs optimizations.\n
* If \p roi is \c NULL the ROI is the whole image.\n
* 
* \b IMPORTANT: The \p src and \p dst image references MUST point to different
* images to properly perfom this operation.
*
* @param[in]	src Reference to the source image.
* @param[out]	dst Reference to the destination image.
* @param[in] 	roi Reference to a ROI.
* 
* @return \todo
*/
int8_t ucv_mm_open(ucv_image_t *src, ucv_image_t *dst, ucv_roi_t *roi);

/** 
* @brief Boundary Extraction.
* 
* @param bw A \ref UCV_BW_BIN image to process
* @param window A ROI to reduce elaboration
* @param buffer 
*/

/** 
* @brief Morphological Boundary Extraction
* 
* Extract boundaries on binary images, 
* the images MUST be of type \ref UCV_BW_BIN.\n
* \todo Say more about this function.
* If \p roi is \c NULL the ROI is the whole image.\n
* 
* \b IMPORTANT: The \p src and \p dst image references MUST point to different
* images to properly perfom this operation.
*
* @param[in]	src Reference to the source image.
* @param[out]	dst Reference to the destination image.
* @param[in] 	roi Reference to a ROI.
* 
* @return \todo 
*/
int8_t ucv_mm_boundary(ucv_image_t *src, ucv_image_t *dst, ucv_roi_t *roi);
/**  @} */

#endif /* __ucv_morph_h__*/
