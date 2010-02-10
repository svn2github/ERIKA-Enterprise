/* SVN: $Id$
 *
 * $Log$
 */
#include "ucv_core.h"

/******************************************************************************/
/*                       Private Local Functions                              */
/******************************************************************************/
static int8_t bw_centroid(ucv_image_t* bw, ucv_coord_t* x, ucv_coord_t* y, 
			  ucv_roi_t *roi)
{
	ucv_coord_t x_i, x_f, y_i, y_f;
	uint32_t i, j;
	uint16_t area = 0;
	uint32_t sx = 0;	
	uint32_t sy = 0;	
	UCV_BIT_INIT(bw_word, mask, bw->image);

	/* TODO: check margins of images? */
	/*TODO: Check the roi limit? */
	if (roi) {
		ucv_roi_get(roi, &x_i, &y_i, &x_f, &y_f);
	} else {
		x_i = 0; 
		y_i = 0; 
		x_f = bw->width; 
		y_f = bw->height;
	}
	for (i = y_i; i < y_f; i++) {
		if (roi) 
			UCV_BIT_GOTO(bw_word, mask, bw->image, 
				     UCV_POS(i, x_i, UCV_IMAGE_WIDTH(*bw)));
		for (j = x_i; j < x_f; j++) {
			/* If pixel == 1 add to centroid sum */
			if (UCV_BIT_GET(bw_word, mask)) {	
				area++;
				sx += j;
				sy += i;
			}
			UCV_BIT_NEXT(bw_word, mask);
		}
	}
	/* Calculate the centroid */
	if(area > 0){
		*x = (ucv_coord_t) (sx / area);
		*y = (ucv_coord_t) (sy / area);
		return 1;
	}
	return UCV_ERR_FAILURE;
}

/******************************************************************************/
/*                       Public Global Functions                              */
/******************************************************************************/
int8_t ucv_centroid(ucv_image_t *im, ucv_coord_t *x, ucv_coord_t *y, 
		    ucv_roi_t *roi)
{
	if (im->type != UCV_BW_BIN)
		return -UCV_ERR_BAD_IMAGE_TYPE; 
	return bw_centroid(im, x, y, roi);
}

COMPILER_INLINE int8_t binarize_from_gray(ucv_image_t *src, ucv_image_t *dst,
					  uint8_t bin_type, 
					  uint8_t th1, uint8_t th2)
{
	uint8_t *max;
	uint8_t *p;
	UCV_BIT_INIT(bw_word, mask, NULL);
	
	#define _BIN_GRAY_ITERATIONS(body)	\
	for (; p < max; p++) {			\
		body;				\
	}				
	
	#define _BIN_GRAY2BW(cond)		\
	if (cond)				\
		UCV_BIT_SET(bw_word, mask);	\
	else					\
		UCV_BIT_CLR(bw_word, mask);	\
	UCV_BIT_NEXT(bw_word, mask);		
	
	#define _BIN_GRAY2GRAY(cond)	\
	if (cond)			\
		*p = 255;		\
	else				\
		*p = 0;			
	
	#define _BIN_DO_GRAY_CASES(cond)			\
	if (dst != NULL ) {					\
		UCV_BIT_GOTO(bw_word, mask, dst->image, 0);	\
		_BIN_GRAY_ITERATIONS(_BIN_GRAY2BW(cond)); 	\
	} else {						\
		_BIN_GRAY_ITERATIONS(_BIN_GRAY2GRAY(cond)); 	\
	}							

	/* TODO: check margins of images? */
	max = src->image + (((uint32_t) src->width) * ((uint32_t) src->height));
	p = src->image;
	switch (bin_type) {
	case UCV_BINARIZE_GRAY_LVALUE :
		_BIN_DO_GRAY_CASES(*p < th1);
	case UCV_BINARIZE_GRAY_GVALUE :
		_BIN_DO_GRAY_CASES(*p > th1);
	case UCV_BINARIZE_GRAY_IN_INTERVAL : 
		_BIN_DO_GRAY_CASES((*p > th1) && (*p < th2));
	case UCV_BINARIZE_GRAY_OUT_INTERVAL :
		_BIN_DO_GRAY_CASES((*p < th1) || (*p > th2));
	} 
	return 1;
}

int8_t ucv_binarize(ucv_image_t *src, ucv_image_t *dst, uint8_t bin_type,
		    void *threshold)
{
	if (src->type != UCV_GRAY_8U)
		return -UCV_ERR_BAD_IMAGE_TYPE; 
	if (bin_type <= UCV_BINARIZE_GRAY_GVALUE) 
		return binarize_from_gray(src, dst, bin_type, 
					  ((uint8_t *)threshold)[0], 0);
	else if (bin_type <= UCV_BINARIZE_GRAY_OUT_INTERVAL) 
		return binarize_from_gray(src, dst, bin_type, 
					  ((uint8_t *)threshold)[0],
					  ((uint8_t *)threshold)[1]);
	return -UCV_ERR_UNIMPLEMENTED;
	
}
