/**
 * \file ledctl.c
 * \copyright Copyright (c) 2013 Infineon Technologies AG. All rights reserved.
 *
 *
 * 1.0
 * 2014-05-20
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 */
// TriBoard-TC275A/C

#include "board/infineon_Applikation_Kit_TC2X5/inc/ee_board.h"

/* LEDs: P33.6 .. P33.13 */

#define LEDCTL_LED_COUNT	8
#define LEDCTL_LED_FIRST	6

int LEDCTL_Init(void)
{
	volatile unsigned int ui;
	P33_OMR.U = (0x0FF << LEDCTL_LED_FIRST);
	ui = (P33_IOCR4.U & 0x0FFFF) | 0x80800000;
	P33_IOCR4.U = ui;
	P33_IOCR8.U = 0x80808080;
	ui = (P33_IOCR12.U & 0xFFFF0000) | 0x00008080;
	P33_IOCR12.U = ui;

	return LEDCTL_LED_COUNT;
}

void LEDCTL_Cleanup(void)
{
}

int  LEDCTL_GetCount(void)
{
	return LEDCTL_LED_COUNT;
}

void LEDCTL_On(int Index)
{
	unsigned int uiMask = (1 << (Index + LEDCTL_LED_FIRST + 16));
	P33_OMR.U = uiMask;
}

void LEDCTL_Off(int Index)
{
	unsigned int uiMask = (1 << (Index + LEDCTL_LED_FIRST));
	P33_OMR.U = uiMask;
}

int  LEDCTL_Status(int Index)
{
	unsigned int uiMask = (1 << (Index + LEDCTL_LED_FIRST));
	return ((P33_OUT.U & uiMask) ? 1 : 0);
}

void LEDCTL_Toggle(int Index)
{
	unsigned int uiMask = (1 << (Index + LEDCTL_LED_FIRST));
	P33_OUT.U ^= uiMask;
}

void LEDCTL_Out(unsigned int uiValue)
{
	P33_OUT.U = ~(uiValue << LEDCTL_LED_FIRST);
}
