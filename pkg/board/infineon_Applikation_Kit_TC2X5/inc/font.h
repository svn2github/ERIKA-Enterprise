/*
 * font.h
 *
 *  Created on: Jan 30, 2014
 *      Author: Fusseneg
 */

#ifndef __INCLUDE_APPKIT_TC2X5_BOARD_FONT_H__
#define __INCLUDE_APPKIT_TC2X5_BOARD_FONT_H__

typedef struct font {

	int xsize;
	int ysize;
	int bytes_per_line;
	char * font_bitmap;

} TFont;


// Fonts
extern const TFont FONT_STANDARD;
extern const TFont FONT_CONSOLAS_LARGE;
extern const TFont FONT_CONSOLAS_SMALL;

#endif /* __INCLUDE_APPKIT_TC2X5_BOARD_FONT_H__ */
