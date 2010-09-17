#include "color_model_conversion.h"
#include <stdlib.h>

#define RGB_A	3

#define FLOAT2INT	1024
#define R  ((int)(1.371F * FLOAT2INT))
#define G1 ((int)(0.698F * FLOAT2INT))
#define G2 ((int)(0.336F * FLOAT2INT))
#define B  ((int)(1.732F * FLOAT2INT))


void my_free(unsigned char* ptr_free){
	free(ptr_free);
}

static inline UChar_t color_model_conversion_saturate(int col)
{
	if (col < 0)
		return 0;
	else if (col > 255)
		return 255;
	else
		return col;
}

static inline void color_model_conversion_yuv2rgb_single(UChar_t rgb[RGB_A*2], UChar_t y1,UChar_t y2,UChar_t cr, UChar_t cb)
{
	int r, g, b;
	
	r = R * ((int)cr - 128); // red
	g = -1 * (G1 * ((int)cr - 128) + G2 * ((int)cb - 128)); // green
	b = B * ((int)cb - 128); // blue
	
	r /= FLOAT2INT;
	g /= FLOAT2INT;
	b /= FLOAT2INT;
	
	rgb[0] = color_model_conversion_saturate(r+y1);
	rgb[1] = color_model_conversion_saturate(g+y1);
	rgb[2] = color_model_conversion_saturate(b+y1);
	if(RGB_A == 4)
		rgb[3] = 255; // alpha channel
		
	rgb[RGB_A] = color_model_conversion_saturate(r+y2);
	rgb[RGB_A+1] = color_model_conversion_saturate(g+y2);
	rgb[RGB_A+2] = color_model_conversion_saturate(b+y2);
	if(RGB_A == 4)
		rgb[RGB_A+3] = 255; // alpha channel	
}


/** Convert an image from YUV 4:2:2 to rgb.
 *
 * The returned array contains r,g,b triples and must be freed with delete[].
 */
UChar_t* color_model_conversion_yuv2rgb(const UChar_t yuvimage[],
	unsigned image_length)
{
	unsigned k;
	UChar_t *rgbimage = malloc(image_length/2*RGB_A);
	for (k = 0; k < image_length/2; k += 2) {
		UChar_t y1, y2, cr, cb;
		y1 = yuvimage[k*2];
		cb = yuvimage[k*2+1];
		y2 = yuvimage[(k+1)*2];
		cr = yuvimage[(k+1)*2+1];
		color_model_conversion_yuv2rgb_single(&rgbimage[k*RGB_A], y1,y2, cr, cb);
		//color_model_conversion_yuv2rgb_single(&rgbimage[(k+1)*RGB_A], y2, cr, cb);
	}
	return rgbimage;
}