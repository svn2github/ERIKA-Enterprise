/* SVN: $Id$
 *
 * $Log$
 */
#include "ucv_morph.h"

/***************************** 
 * Neighbourhood convention  *
 *                           *
 *         b8 b1 b5          *           
 *         b4 -- b2          *
 *         b7 b3 b6          *
 *                           *
 *****************************/

/******************************************************************************/
/*                       Private Local Functions                              */
/******************************************************************************/

/******************************************************************************/
/*                       Public Global Functions                              */
/******************************************************************************/
int8_t ucv_mm_negate(ucv_image_t *src, ucv_image_t *dst)
{
	ucv_word_t *s;
	ucv_word_t *max;
	ucv_word_t *d;

	/* TODO: check margins of images? */
	s = (ucv_word_t*) src->image;
	max = s + UCV_BW_BIN_SIZE(src->width, src->height);
	if (dst != NULL) 
		for (d = (ucv_word_t*) dst->image; s < max; d++, s++) 
			*d = ~(*s);
	else 
		for (; s < max; s++) 
			*s = ~(*s);
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
