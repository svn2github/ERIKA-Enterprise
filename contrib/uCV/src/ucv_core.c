/* SVN: $Id$
 *
 * $Log$
 */
#include "ucv_core.h"
#include "ucv_opt.h"

/******************************************************************************/
/*                       Private Local Functions                              */
/******************************************************************************/
static int8_t bw_centroid(const ucv_image_t *bw, ucv_coord_t *x, ucv_coord_t *y,
			  ucv_roi_t *roi)
{
	ucv_coord_t x_i, x_f, y_i, y_f;
	uint32_t i, j;
	uint16_t area = 0;
	uint32_t sx = 0;	
	uint32_t sy = 0;	
	UCV_BIT_INIT(bw_word, mask, bw->image);

	/* TODO: check margins of images? */
	/* TODO: Check the roi limit? */
	if (roi) {
		ucv_roi_get(roi, &x_i, &y_i, &x_f, &y_f);
	} else {
		x_i = 0; 
		y_i = 0; 
		x_f = bw->width; 
		y_f = bw->height;
	}
	/* TODO: Use loop unrolling to be faster? */
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

#define _BINARIZE_GRAY2BIN_SCHELETON(cond)				\
	ucv_word_t sw, dw, dm;						\
	ucv_word_t *s;							\
	ucv_word_t *d;							\
	uint8_t v;							\
	UCV_WORD_UNROLL_INIT();						\
	const ucv_word_t *s_end = (ucv_word_t *) src->image + 		\
			UCV_LOOP_UNROLL_8_ROUNDS( 			\
			    UCV_GRAY_8U_WSIZE(src->width, src->height));\
	const ucv_word_t *s_actual_end = (ucv_word_t *) src->image + 	\
			    UCV_GRAY_8U_WSIZE(src->width, src->height); \
									\
	s = (ucv_word_t *) src->image;					\
	d = (ucv_word_t *) dst->image;					\
	UCV_LOOP_UNROLL_8_DO_ALL(s != s_end, s_actual_end - s,		\
		dw = 0;							\
		dm = UCV_BIT_START_MASK;				\
		,							\
		sw = *(s++);						\
		UCV_WORD_UNROLL(					\
			v = UCV_WORD_UNROLL_TARGET(sw);			\
			if (cond)					\
				dw |= dm;				\
			dm >>= 1;					\
		);							\
		,							\
		*(d++) = dw;						\
	);

	//while (s != s_end) {						\
		dw = 0;							\
		dm = UCV_BIT_START_MASK;				\
		UCV_LOOP_UNROLL_8(					\
			sw = *(s++);					\
			UCV_WORD_UNROLL(				\
				v = UCV_WORD_UNROLL_TARGET(sw);		\
				if (cond)				\
					dw |= dm;			\
				dm >>= 1;				\
			);						\
		);							\
		*(d++) = dw;						\
	}								\
	if (s != s_actual_end)	{					\
		dw = 0;							\
		dm = UCV_BIT_START_MASK;				\
		UCV_LOOP_UNROLL_8_DO_RESIDUALS(s_actual_end - s,	\
			sw = *(s++);					\
			UCV_WORD_UNROLL(				\
				v = UCV_WORD_UNROLL_TARGET(sw);		\
				if (cond)				\
					dw |= dm;			\
				dm >>= 1;				\
			);						\
		);							\
		*d = dw;						\
	}\

static void binarize_gray2bin_gval(const ucv_image_t *src, 
				   ucv_image_t *dst, uint8_t th1)
{
	_BINARIZE_GRAY2BIN_SCHELETON(v > th1);
}

static void binarize_gray2bin_lval(const ucv_image_t *src, 
				   ucv_image_t *dst, uint8_t th1)
{
	_BINARIZE_GRAY2BIN_SCHELETON(v < th1);
}

static void binarize_gray2bin_in(const ucv_image_t *src, 
				 ucv_image_t *dst, uint8_t th1, uint8_t th2)
{
	_BINARIZE_GRAY2BIN_SCHELETON(v > th1 && v < th2);
}

static void binarize_gray2bin_out(const ucv_image_t *src, 
				  ucv_image_t *dst, uint8_t th1, uint8_t th2)
{
	_BINARIZE_GRAY2BIN_SCHELETON(v < th1 || v > th2);
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

int8_t ucv_binarize(ucv_image_t *src, ucv_image_t *dst, uint8_t bin_type,
		    void *thr)
{
	uint8_t *max;
	uint8_t *p;

	/* TODO: provide solution for gray2gray similar to the gray2bin one */
	#define _BIN_GRAY_ITERATIONS(body)	\
	for (; p < max; p++) {			\
		body;				\
	}				
	
	#define _BIN_GRAY2GRAY(cond)	\
	if (cond)			\
		*p = 255;		\
	else				\
		*p = 0;			
	
	if (src->type != UCV_GRAY_8U)
		return -UCV_ERR_BAD_IMAGE_TYPE; 
	/* TODO: check margins of images? */
	max = src->image + (((uint32_t) src->width) * ((uint32_t) src->height));
	p = src->image;
	switch (bin_type) {
	case UCV_BINARIZE_GRAY_LVALUE :
		if (dst != NULL) 
			binarize_gray2bin_lval(src, dst, *((uint8_t *) thr));
		else {
		_BIN_GRAY_ITERATIONS(_BIN_GRAY2GRAY(*p < *((uint8_t *) thr)));
		}
		break;
	case UCV_BINARIZE_GRAY_GVALUE :
		if (dst != NULL) 
			binarize_gray2bin_gval(src, dst, *((uint8_t *) thr));
		else {
		_BIN_GRAY_ITERATIONS(_BIN_GRAY2GRAY(*p > *((uint8_t *) thr)));
		}
		break;
	case UCV_BINARIZE_GRAY_IN_INTERVAL : 
		if (dst != NULL) 
			binarize_gray2bin_in(src, dst, ((uint8_t*)thr)[0],
					     ((uint8_t*)thr)[1]);
		else {
		_BIN_GRAY_ITERATIONS(_BIN_GRAY2GRAY(
				 		  (*p > ((uint8_t*)thr)[0]) && 
						  (*p < ((uint8_t*)thr)[1])));
		}
		break;
	case UCV_BINARIZE_GRAY_OUT_INTERVAL :
		if (dst != NULL) 
			binarize_gray2bin_out(src, dst, ((uint8_t*)thr)[0],
					      ((uint8_t*)thr)[1]);
		else {
		_BIN_GRAY_ITERATIONS(_BIN_GRAY2GRAY(
				 		  (*p < ((uint8_t*)thr)[0]) || 
						  (*p > ((uint8_t*)thr)[1])));
		}
		break;
	default:
		return -UCV_ERR_UNIMPLEMENTED;
	} 
	return 1;
}


