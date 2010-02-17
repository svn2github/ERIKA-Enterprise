/* SVN: $Id$
 *
 * $Log$
 */
#include "ucv_morph.h"
#include "ucv_opt.h"

/******************************************************************************/
/*                       Private Local Functions                              */
/******************************************************************************/
void fast_dilate_se3(const ucv_image_t *src, ucv_image_t *dst, 
//static void fast_dilate_se3(const ucv_image_t *src, ucv_image_t *dst, 
			    uint8_t mask)
{
	/*
	The idea is the following:
	
	mask = [s1 s2 s3 s4 s5 s6 s7 s8]
	
	pixl = [p1 p2 p3 p4 p5 p6 p7 p8]
                || || ||
	se_u = [s1 s2 s3 0 0 0 ...]
	se_c = [s4 1  s5 0 0 0 ...]
	se_d = [s6 s7 s8 0 0 0 ...]

	*/
	#define NW (UCV_WORD_SIZE * 8)
	#define NW_2 (NW / 2)
	#define NB (8)
	register ucv_word_t r_u, r_c, r_d;
	register ucv_word_t r_u_next, r_c_next, r_d_next;
	const ucv_word_t se_u = ((ucv_word_t) mask & 0xE0) << (NW - NB); 
	const ucv_word_t se_c = (((ucv_word_t) mask & 0x10) << (NW - NB + 3)) |
	                        (((ucv_word_t) mask & 0x40) << (NW - NB)) | 
	                        (((ucv_word_t) mask & 0x08) << (NW - NB + 2)); 
	const ucv_word_t se_d = ((ucv_word_t) mask & 0x07) << (NW - NB + 5); 
	uint32_t i, k;
	ucv_word_t *d;
	ucv_word_t dw, dm;

	/* TODO: fare la prima riga! */

#define UCV_BIT_GET_WPTR(im, pos)					\
	(((ucv_word_t*)(im)) +						\
		 (((uint32_t)(pos)) / (8 * sizeof(ucv_word_t))))	\

	i = 0;

	d = UCV_BIT_GET_WPTR(dst->image, dst->width);
	r_u = *(UCV_BIT_GET_WPTR(src->image, 0) + i);
	r_c = *(UCV_BIT_GET_WPTR(src->image, src->width) + i);
	r_d = *(UCV_BIT_GET_WPTR(src->image, 2 * src->width) + i);

	dw = 0;	
	dm = UCV_BIT_START_MASK;

	/* 1st Boundary condition: start of the first coloumn */
	if (((se_u << 1) & r_u) | ((se_c << 1) & r_c) | ((se_d << 1) & r_d))
		dw |= dm;
	dm >>= 1;

	k = ((uint32_t)src->width * (src->height - 2)) / NW;
	while (k--) {
		/* Load the _next words */
		i++; 
		r_u_next = *(UCV_BIT_GET_WPTR(src->image, 0) + i);
		r_c_next = *(UCV_BIT_GET_WPTR(src->image, src->width) + i);
		r_d_next = *(UCV_BIT_GET_WPTR(src->image, 2 * src->width) + i);
//		#if NW_2 == 16
		UCV_LOOP_UNROLL_16(
//		#endif
			//if ((se_u & r_u) || (se_c & r_c) || (se_d & r_d))
			//	dw |= dm;
			if ((se_u & r_u) | (se_c & r_c) | (se_d & r_d))
				dw |= dm;
			dm >>= 1;
			r_u <<= 1;
			r_c <<= 1;
			r_d <<= 1;
		);
		/* Destination is at 17th pixel, source is at 16th pixels */
		/* Swap the first NW_2 bits from the _next words 
		   to the processing ones */
		r_u |= (r_u_next >> NW_2);
		r_c |= (r_c_next >> NW_2);
		r_d |= (r_d_next >> NW_2);
//		#if NW_2 == 16
		UCV_LOOP_UNROLL_15(
//		#endif
			//if ((se_u & r_u) || (se_c & r_c) || (se_d & r_d))
			if ((se_u & r_u) | (se_c & r_c) | (se_d & r_d))
				dw |= dm;
			dm >>= 1;
			r_u <<= 1;
			r_c <<= 1;
			r_d <<= 1;
		);
		/* Destination is at 32th pixel, store result.
		   Source is at 31th pixel. */
		*(d++) = dw;
		dw = 0;	
		dm = UCV_BIT_START_MASK;
		/* Consume the 32th pixel from source and 
		   use it for the new 1st (32+1) destination pixel. */
		//if ((se_u & r_u) || (se_c & r_c) || (se_d & r_d))
		if ((se_u & r_u) | (se_c & r_c) | (se_d & r_d))
			dw |= dm;
		dm >>= 1;
		r_u <<= 1;
		r_c <<= 1;
		r_d <<= 1;
		/* Swap the last NW_2 bits from the _next words 
		   to the processing ones */
		r_u |= (r_u_next & 0x0000FFFF);
		r_c |= (r_c_next & 0x0000FFFF);
		r_d |= (r_d_next & 0x0000FFFF);
	}
}

void fast_erode_se3(const ucv_image_t *src, ucv_image_t *dst, 
//static void fast_dilate_se3(const ucv_image_t *src, ucv_image_t *dst, 
			    uint8_t mask)
{
	/*
	The idea is the following:
	
	mask = [s1 s2 s3 s4 s5 s6 s7 s8]
	
	pixl = [p1 p2 p3 p4 p5 p6 p7 p8]
                || || ||
	se_u = [s1 s2 s3 0 0 0 ...]
	se_c = [s4 1  s5 0 0 0 ...]
	se_d = [s6 s7 s8 0 0 0 ...]

	*/
	#define NW (UCV_WORD_SIZE * 8)
	#define NW_2 (NW / 2)
	#define NB (8)
	register ucv_word_t r_u, r_c, r_d;
	register ucv_word_t r_u_next, r_c_next, r_d_next;
	const ucv_word_t se_u = ((ucv_word_t) mask & 0xE0) << (NW - NB); 
	const ucv_word_t se_c = (((ucv_word_t) mask & 0x10) << (NW - NB + 3)) |
	                        (((ucv_word_t) mask & 0x40) << (NW - NB)) | 
	                        (((ucv_word_t) mask & 0x08) << (NW - NB + 2)); 
	const ucv_word_t se_d = ((ucv_word_t) mask & 0x07) << (NW - NB + 5); 
	uint32_t i, k;
	ucv_word_t *d;
	ucv_word_t dw, dm;

	/* TODO: fare la prima riga! */

#define UCV_BIT_GET_WPTR(im, pos)					\
	(((ucv_word_t*)(im)) +						\
		 (((uint32_t)(pos)) / (8 * sizeof(ucv_word_t))))	\

	i = 0;

	d = UCV_BIT_GET_WPTR(dst->image, dst->width);
	r_u = *(UCV_BIT_GET_WPTR(src->image, 0) + i);
	r_c = *(UCV_BIT_GET_WPTR(src->image, src->width) + i);
	r_d = *(UCV_BIT_GET_WPTR(src->image, 2 * src->width) + i);

	dw = 0;	
	dm = UCV_BIT_START_MASK;

	/* 1st Boundary condition: start of the first coloumn */
	#define CON(a, b) (((a) & (b)) ^ (a))
	if (!(CON(se_u << 1, r_u) | CON(se_c << 1, r_c) | CON(se_d << 1, r_d)))
		dw |= dm;
	dm >>= 1;

	k = ((uint32_t)src->width * (src->height - 2)) / NW;
	while (k--) {
		/* Load the _next words */
		i++; 
		r_u_next = *(UCV_BIT_GET_WPTR(src->image, 0) + i);
		r_c_next = *(UCV_BIT_GET_WPTR(src->image, src->width) + i);
		r_d_next = *(UCV_BIT_GET_WPTR(src->image, 2 * src->width) + i);
//		#if NW_2 == 16
		UCV_LOOP_UNROLL_16(
//		#endif
			//if ((se_u & r_u) || (se_c & r_c) || (se_d & r_d))
			//	dw |= dm;
			if (!(CON(se_u, r_u) | CON(se_c, r_c) | CON(se_d, r_d)))
				dw |= dm;
			dm >>= 1;
			r_u <<= 1;
			r_c <<= 1;
			r_d <<= 1;
		);
		/* Destination is at 17th pixel, source is at 16th pixels */
		/* Swap the first NW_2 bits from the _next words 
		   to the processing ones */
		r_u |= (r_u_next >> NW_2);
		r_c |= (r_c_next >> NW_2);
		r_d |= (r_d_next >> NW_2);
//		#if NW_2 == 16
		UCV_LOOP_UNROLL_15(
//		#endif
			//if ((se_u & r_u) || (se_c & r_c) || (se_d & r_d))
			if (!(CON(se_u, r_u) | CON(se_c, r_c) | CON(se_d, r_d)))
				dw |= dm;
			dm >>= 1;
			r_u <<= 1;
			r_c <<= 1;
			r_d <<= 1;
		);
		/* Destination is at 32th pixel, store result.
		   Source is at 31th pixel. */
		*(d++) = dw;
		dw = 0;	
		dm = UCV_BIT_START_MASK;
		/* Consume the 32th pixel from source and 
		   use it for the new 1st (32+1) destination pixel. */
		//if ((se_u & r_u) || (se_c & r_c) || (se_d & r_d))
		if (!(CON(se_u, r_u) | CON(se_c, r_c) | CON(se_d, r_d)))
			dw |= dm;
		dm >>= 1;
		r_u <<= 1;
		r_c <<= 1;
		r_d <<= 1;
		/* Swap the last NW_2 bits from the _next words 
		   to the processing ones */
		r_u |= (r_u_next & 0x0000FFFF);
		r_c |= (r_c_next & 0x0000FFFF);
		r_d |= (r_d_next & 0x0000FFFF);
	}
}


/******************************************************************************/
/*                       Public Global Functions                              */
/******************************************************************************/
int8_t ucv_mm_negate(ucv_image_t *src, ucv_image_t *dst)
{
//	ucv_word_t *s;
//	ucv_word_t *max;
//	ucv_word_t *d;
//
//	/* TODO: check margins of images? */
//	s = (ucv_word_t*) src->image;
//	max = s + UCV_BW_BIN_SIZE(src->width, src->height);
//	if (dst != NULL) 
//		for (d = (ucv_word_t*) dst->image; s < max; d++, s++) 
//			*d = ~(*s);
//		
//	else 
//		for (; s < max; s++) 
//			*s = ~(*s);

	ucv_word_t *s;
	ucv_word_t *d;
	const ucv_word_t words = UCV_BW_BIN_SIZE(src->width, src->height);
	const ucv_word_t *end1 = (ucv_word_t *) src->image + 
				 UCV_LOOP_UNROLL_8_ROUNDS(words);
	const ucv_word_t *end2 = (ucv_word_t *) src->image + words;

	/* TODO: check margins of images? */
	s = (ucv_word_t*) src->image;
	if (dst != NULL) {
		d = (ucv_word_t*) dst->image;
		UCV_LOOP_UNROLL_8_DO_ALL(s != end1, end2 - s,
			,
			*(d++) = ~(*(s++));
			,
		);
	} else {
		UCV_LOOP_UNROLL_8_DO_ALL(s != end1, end2 - s,
			,
			*(s) = ~(*s);
			s++;
			,
		);
	}
	return 1;
}

int8_t ucv_mm_dilate(const ucv_image_t *src, ucv_image_t *dst, ucv_mask_t *se,
		     ucv_roi_t *roi)
{
	if (roi != NULL)
		return -UCV_ERR_UNIMPLEMENTED;
	/* TODO: this code is just for test, make the right one!*/
	fast_dilate_se3(src, dst, 0xFF);
	return 1;
}

int8_t ucv_mm_erode(const ucv_image_t *src, ucv_image_t *dst, ucv_mask_t *se,
		    ucv_roi_t *roi)
{
	if (roi != NULL)
		return -UCV_ERR_UNIMPLEMENTED;
	/* TODO: this code is just for test, make the right one!*/
	fast_erode_se3(src, dst, 0xFF);
	return 1;
}


#if 0
void mv_Image_erosion(ucv_image_t *bw, ucv_roi_t *window, Mv_int8u* buffer)
{
	ucv_coord_t i,j;
	ucv_coord_t Xi=1, Xf=(bw->width)-1, Yi=1, Yf=(bw->height)-1;
	UCV_BIT_INIT(b,m,NULL);
	UCV_BIT_INIT(b1,m1,NULL);
	UCV_BIT_INIT(b2,m2,NULL);
	UCV_BIT_INIT(b3,m3,NULL);
	UCV_BIT_INIT(b4,m4,NULL);
	#ifdef UCV_MORPH_8_CONNECTED
	UCV_BIT_INIT(b5,m5,NULL);
	UCV_BIT_INIT(b6,m6,NULL);
	UCV_BIT_INIT(b7,m7,NULL);
	UCV_BIT_INIT(b8,m8,NULL);
	#endif

	memcpy(buffer, bw->image, UCV_BW_BIN_SIZE(bw->width, bw->height));

	if(window){
		if(window->tl_x > 0) Xi=window->tl_x;
		if(window->tl_y > 0) Yi=window->tl_y;
		if(window->br_x < bw->width) Xf=window->br_x;
		if(window->br_y < bw->height) Yf=window->br_y;
	}

	/* Operation from buffer to bw->image */

	for(i=Yi; i<Yf; i++){
		UCV_BIT_GOTO(b, m, bw->image, (int)(i*bw->width)+Xi);
		UCV_BIT_GOTO(b1,m1,buffer, (int)((i-1)*bw->width)+Xi);
		UCV_BIT_GOTO(b2,m2,buffer, (int)(i*bw->width)+Xi+1);
		UCV_BIT_GOTO(b3,m3,buffer, (int)((i+1)*bw->width)+Xi);
		UCV_BIT_GOTO(b4,m4,buffer, (int)(i*bw->width)+Xi-1);
		#ifdef UCV_MORPH_8_CONNECTED
		UCV_BIT_GOTO(b5,m5,buffer, (int)((i-1)*bw->width)+Xi+1);
		UCV_BIT_GOTO(b6,m6,buffer, (int)((i+1)*bw->width)+Xi+1);
		UCV_BIT_GOTO(b7,m7,buffer, (int)((i+1)*bw->width)+Xi-1);
		UCV_BIT_GOTO(b8,m8,buffer, (int)((i-1)*bw->width)+Xi-1);
		#endif

		for(j=Xi; j<Xf; j++) {
			if(UCV_BIT_GET(b1,m1) && UCV_BIT_GET(b2,m2) && UCV_BIT_GET(b3,m3) && UCV_BIT_GET(b4,m4)
			#ifdef UCV_MORPH_8_CONNECTED
			   && UCV_BIT_GET(b5,m5) && UCV_BIT_GET(b6,m6) && UCV_BIT_GET(b7,m7) && UCV_BIT_GET(b8,m8)
			#endif
			){
				UCV_BIT_SET(b,m);
			}
			else{
				UCV_BIT_CLR(b,m);
			}

			UCV_BIT_NEXT(b,m);
			UCV_BIT_NEXT(b1,m1);
			UCV_BIT_NEXT(b2,m2);
			UCV_BIT_NEXT(b3,m3);
			UCV_BIT_NEXT(b4,m4);
			#ifdef UCV_MORPH_8_CONNECTED
			UCV_BIT_NEXT(b5,m5);
			UCV_BIT_NEXT(b6,m6);
			UCV_BIT_NEXT(b7,m7);
			UCV_BIT_NEXT(b8,m8);
			#endif
		}
	}
}


void mv_Image_dilation(ucv_image_t *bw, ucv_roi_t *window, Mv_int8u* buffer)
{
	ucv_coord_t i,j;
	ucv_coord_t Xi=1, Xf=(bw->width)-1, Yi=1, Yf=(bw->height)-1;
	UCV_BIT_INIT(b,m,NULL);
	UCV_BIT_INIT(b1,m1,NULL);
	UCV_BIT_INIT(b2,m2,NULL);
	UCV_BIT_INIT(b3,m3,NULL);
	UCV_BIT_INIT(b4,m4,NULL);
	#ifdef UCV_MORPH_8_CONNECTED
	UCV_BIT_INIT(b5,m5,NULL);
	UCV_BIT_INIT(b6,m6,NULL);
	UCV_BIT_INIT(b7,m7,NULL);
	UCV_BIT_INIT(b8,m8,NULL);
	#endif

	memcpy(buffer, bw->image, UCV_BW_BIN_SIZE(bw->width, bw->height));

	if(window){
		if(window->tl_x > 0) Xi=window->tl_x;
		if(window->tl_y > 0) Yi=window->tl_y;
		if(window->br_x < bw->width) Xf=window->br_x;
		if(window->br_y < bw->height) Yf=window->br_y;
	}

	/* Operation from buffer to bw->image */

	for(i=Yi; i<Yf; i++){
		UCV_BIT_GOTO(b, m, bw->image, (int)(i*bw->width)+Xi);
		UCV_BIT_GOTO(b1,m1,buffer, (int)((i-1)*bw->width)+Xi);
		UCV_BIT_GOTO(b2,m2,buffer, (int)(i*bw->width)+Xi+1);
		UCV_BIT_GOTO(b3,m3,buffer, (int)((i+1)*bw->width)+Xi);
		UCV_BIT_GOTO(b4,m4,buffer, (int)(i*bw->width)+Xi-1);
		#ifdef UCV_MORPH_8_CONNECTED
		UCV_BIT_GOTO(b5,m5,buffer, (int)((i-1)*bw->width)+Xi+1);
		UCV_BIT_GOTO(b6,m6,buffer, (int)((i+1)*bw->width)+Xi+1);
		UCV_BIT_GOTO(b7,m7,buffer, (int)((i+1)*bw->width)+Xi-1);
		UCV_BIT_GOTO(b8,m8,buffer, (int)((i-1)*bw->width)+Xi-1);
		#endif

		for(j=Xi; j<Xf; j++) {
			if(UCV_BIT_GET(b1,m1) || UCV_BIT_GET(b2,m2) || UCV_BIT_GET(b3,m3) || UCV_BIT_GET(b4,m4)
			#ifdef UCV_MORPH_8_CONNECTED
			   || UCV_BIT_GET(b5,m5) || UCV_BIT_GET(b6,m6) || UCV_BIT_GET(b7,m7) || UCV_BIT_GET(b8,m8)
			#endif
			){
				UCV_BIT_SET(b,m);
			}
			else{
				UCV_BIT_CLR(b,m);
			}

			UCV_BIT_NEXT(b,m);
			UCV_BIT_NEXT(b1,m1);
			UCV_BIT_NEXT(b2,m2);
			UCV_BIT_NEXT(b3,m3);
			UCV_BIT_NEXT(b4,m4);
			#ifdef UCV_MORPH_8_CONNECTED
			UCV_BIT_NEXT(b5,m5);
			UCV_BIT_NEXT(b6,m6);
			UCV_BIT_NEXT(b7,m7);
			UCV_BIT_NEXT(b8,m8);
			#endif
		}
	}
}

void mv_Image_open(ucv_image_t *bw, ucv_roi_t *window, Mv_int8u* buffer)
{

	ucv_coord_t i,j;
	ucv_coord_t Xi=1, Xf=(bw->width)-1, Yi=1, Yf=(bw->height)-1;
	UCV_BIT_INIT(b,m,NULL);
	UCV_BIT_INIT(b1,m1,NULL);
	UCV_BIT_INIT(b2,m2,NULL);
	UCV_BIT_INIT(b3,m3,NULL);
	UCV_BIT_INIT(b4,m4,NULL);
	#ifdef UCV_MORPH_8_CONNECTED
	UCV_BIT_INIT(b5,m5,NULL);
	UCV_BIT_INIT(b6,m6,NULL);
	UCV_BIT_INIT(b7,m7,NULL);
	UCV_BIT_INIT(b8,m8,NULL);
	#endif

	if(window){
		if(window->tl_x > 0) Xi=window->tl_x;
		if(window->tl_y > 0) Yi=window->tl_y;
		if(window->br_x < bw->width) Xf=window->br_x;
		if(window->br_y < bw->height) Yf=window->br_y;
	}

	/* Operation from bw->image to buffer */

	for(i=Yi; i<Yf; i++){
		UCV_BIT_GOTO(b, m, buffer, (int)(i*bw->width)+Xi);
		UCV_BIT_GOTO(b1,m1,bw->image, (int)((i-1)*bw->width)+Xi);
		UCV_BIT_GOTO(b2,m2,bw->image, (int)(i*bw->width)+Xi+1);
		UCV_BIT_GOTO(b3,m3,bw->image, (int)((i+1)*bw->width)+Xi);
		UCV_BIT_GOTO(b4,m4,bw->image, (int)(i*bw->width)+Xi-1);
		#ifdef UCV_MORPH_8_CONNECTED
		UCV_BIT_GOTO(b5,m5,bw->image, (int)((i-1)*bw->width)+Xi+1);
		UCV_BIT_GOTO(b6,m6,bw->image, (int)((i+1)*bw->width)+Xi+1);
		UCV_BIT_GOTO(b7,m7,bw->image, (int)((i+1)*bw->width)+Xi-1);
		UCV_BIT_GOTO(b8,m8,bw->image, (int)((i-1)*bw->width)+Xi-1);
		#endif

		for(j=Xi; j<Xf; j++) {
			if(UCV_BIT_GET(b1,m1) && UCV_BIT_GET(b2,m2) && UCV_BIT_GET(b3,m3) && UCV_BIT_GET(b4,m4)
			#ifdef UCV_MORPH_8_CONNECTED
			   && UCV_BIT_GET(b5,m5) && UCV_BIT_GET(b6,m6) && UCV_BIT_GET(b7,m7) && UCV_BIT_GET(b8,m8)
			#endif
			){
				UCV_BIT_SET(b,m);
			}
			else{
				UCV_BIT_CLR(b,m);
			}

			UCV_BIT_NEXT(b,m);
			UCV_BIT_NEXT(b1,m1);
			UCV_BIT_NEXT(b2,m2);
			UCV_BIT_NEXT(b3,m3);
			UCV_BIT_NEXT(b4,m4);
			#ifdef UCV_MORPH_8_CONNECTED
			UCV_BIT_NEXT(b5,m5);
			UCV_BIT_NEXT(b6,m6);
			UCV_BIT_NEXT(b7,m7);
			UCV_BIT_NEXT(b8,m8);
			#endif
		}
	}

	/* Operation from buffer to bw->image */

	for(i=Yi; i<Yf; i++){
		UCV_BIT_GOTO(b, m, bw->image, (int)(i*bw->width)+Xi);
		UCV_BIT_GOTO(b1,m1,buffer, (int)((i-1)*bw->width)+Xi);
		UCV_BIT_GOTO(b2,m2,buffer, (int)(i*bw->width)+Xi+1);
		UCV_BIT_GOTO(b3,m3,buffer, (int)((i+1)*bw->width)+Xi);
		UCV_BIT_GOTO(b4,m4,buffer, (int)(i*bw->width)+Xi-1);
		#ifdef UCV_MORPH_8_CONNECTED
		UCV_BIT_GOTO(b5,m5,buffer, (int)((i-1)*bw->width)+Xi+1);
		UCV_BIT_GOTO(b6,m6,buffer, (int)((i+1)*bw->width)+Xi+1);
		UCV_BIT_GOTO(b7,m7,buffer, (int)((i+1)*bw->width)+Xi-1);
		UCV_BIT_GOTO(b8,m8,buffer, (int)((i-1)*bw->width)+Xi-1);
		#endif
		for(j=Xi; j<Xf; j++) {
			if(UCV_BIT_GET(b1,m1) || UCV_BIT_GET(b2,m2) || UCV_BIT_GET(b3,m3) || UCV_BIT_GET(b4,m4)
			#ifdef UCV_MORPH_8_CONNECTED
			   || UCV_BIT_GET(b5,m5) || UCV_BIT_GET(b6,m6) || UCV_BIT_GET(b7,m7) || UCV_BIT_GET(b8,m8)
			#endif
			){
				UCV_BIT_SET(b,m);
			}
			else{
				UCV_BIT_CLR(b,m);
			}

			UCV_BIT_NEXT(b,m);
			UCV_BIT_NEXT(b1,m1);
			UCV_BIT_NEXT(b2,m2);
			UCV_BIT_NEXT(b3,m3);
			UCV_BIT_NEXT(b4,m4);
			#ifdef UCV_MORPH_8_CONNECTED
			UCV_BIT_NEXT(b5,m5);
			UCV_BIT_NEXT(b6,m6);
			UCV_BIT_NEXT(b7,m7);
			UCV_BIT_NEXT(b8,m8);
			#endif
		}
	}
}

void mv_Image_boundary(ucv_image_t *bw, ucv_roi_t *window, Mv_int8u* buffer)
{
	ucv_coord_t i,j;
	Mv_int16u *diff1, *diff2;
	ucv_coord_t Xi=1, Xf=(bw->width)-1, Yi=1, Yf=(bw->height)-1;
	UCV_BIT_INIT(b,m,NULL);
	UCV_BIT_INIT(b1,m1,NULL);
	UCV_BIT_INIT(b2,m2,NULL);
	UCV_BIT_INIT(b3,m3,NULL);
	UCV_BIT_INIT(b4,m4,NULL);
	#ifdef UCV_MORPH_8_CONNECTED
	UCV_BIT_INIT(b5,m5,NULL);
	UCV_BIT_INIT(b6,m6,NULL);
	UCV_BIT_INIT(b7,m7,NULL);
	UCV_BIT_INIT(b8,m8,NULL);
	#endif

	memset(buffer, 0, UCV_BW_BIN_SIZE(bw->width, bw->height));

	if(window){
		if(window->tl_x > 0) Xi=window->tl_x;
		if(window->tl_y > 0) Yi=window->tl_y;
		if(window->br_x < bw->width) Xf=window->br_x;
		if(window->br_y < bw->height) Yf=window->br_y;
	}

	/* Erosion : from bw->image to buffer */

	for(i=Yi; i<Yf; i++){
		UCV_BIT_GOTO(b, m, buffer, (int)(i*bw->width)+Xi);
		UCV_BIT_GOTO(b1,m1,bw->image, (int)((i-1)*bw->width)+Xi);
		UCV_BIT_GOTO(b2,m2,bw->image, (int)(i*bw->width)+Xi+1);
		UCV_BIT_GOTO(b3,m3,bw->image, (int)((i+1)*bw->width)+Xi);
		UCV_BIT_GOTO(b4,m4,bw->image, (int)(i*bw->width)+Xi-1);
		#ifdef UCV_MORPH_8_CONNECTED
		UCV_BIT_GOTO(b5,m5,bw->image, (int)((i-1)*bw->width)+Xi+1);
		UCV_BIT_GOTO(b6,m6,bw->image, (int)((i+1)*bw->width)+Xi+1);
		UCV_BIT_GOTO(b7,m7,bw->image, (int)((i+1)*bw->width)+Xi-1);
		UCV_BIT_GOTO(b8,m8,bw->image, (int)((i-1)*bw->width)+Xi-1);
		#endif

		for(j=Xi; j<Xf; j++) {
			if(UCV_BIT_GET(b1,m1) && UCV_BIT_GET(b2,m2) && UCV_BIT_GET(b3,m3) && UCV_BIT_GET(b4,m4)
			#ifdef UCV_MORPH_8_CONNECTED
			   && UCV_BIT_GET(b5,m5) && UCV_BIT_GET(b6,m6) && UCV_BIT_GET(b7,m7) && UCV_BIT_GET(b8,m8)
			#endif
			){
				UCV_BIT_SET(b,m);
			}
			else{
				UCV_BIT_CLR(b,m);
			}

			UCV_BIT_NEXT(b,m);
			UCV_BIT_NEXT(b1,m1);
			UCV_BIT_NEXT(b2,m2);
			UCV_BIT_NEXT(b3,m3);
			UCV_BIT_NEXT(b4,m4);
			#ifdef UCV_MORPH_8_CONNECTED
			UCV_BIT_NEXT(b5,m5);
			UCV_BIT_NEXT(b6,m6);
			UCV_BIT_NEXT(b7,m7);
			UCV_BIT_NEXT(b8,m8);
			#endif
		}
	}

	/* Logic Difference: bw->image = bw->image - buffer */

	/* NOTE:
	 * 1- operation on 16-bit unsigned int
	 * 2- operation performed on the whole image
	 * 3- TODO dspPIC: dsp may be used here!
	*/

	diff1 = (Mv_int16u*) bw->image;
	diff2 = (Mv_int16u*) buffer;
	for(i=0; i< UCV_BW_BIN_SIZE(bw->width, bw->height)/2; i++){
		*diff1 &= ~(*diff2);
		diff1++;
		diff2++;
	}
	if(UCV_BW_BIN_SIZE(bw->width, bw->height)%2 == 1) /* if the amount of byte is not a multiple of 16-bit...*/
		*((Mv_int8u*)(diff1)) &= ~(*((Mv_int8u*)(diff2)));
}
#endif
