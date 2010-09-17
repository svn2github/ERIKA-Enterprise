/*
Copyright (C) 2010 - Bernardo  Dal Seno
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

/**
 *\file color_model_conversion.h
 *\author Bernardo  Dal Seno
 *\brief  Functions to convert colors
 */
 
#ifndef COLOR_MODEL_CONVERSION_H
#define COLOR_MODEL_CONVERSION_H

typedef unsigned char UChar_t;

UChar_t* color_model_conversion_yuv2rgb(const UChar_t yuvimage[],unsigned image_length);
void my_free(unsigned char* ptr_free);

#endif