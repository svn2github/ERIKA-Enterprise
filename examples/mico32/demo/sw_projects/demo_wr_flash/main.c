/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2010  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation, 
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */
 
/** 
    @file      main.c
    @brief     SPI Flash demo.
               User can use this demo to learn how to write to and read from SST25LF0X0A SPI flash
               mounted on the XP2 camera board.
               The demo requires a RS232 serial connection with user PC (115200 bps,8N1 configuration).
    @author    Dario Di Stefano
    @date      2010
*/


/* Use Erika */
#include <ee.h>
/* Platform configuration */
#include <system_conf.h>
/* Erika Mico32 interrupts */
#include <cpu/mico32/inc/ee_irq.h>
/* SPI flash library */
#include "ee_spi_flash.h"
/* Other libraries */
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

/* A printf-like function */
void myprintf(const char *format, ...)
{
#define MAXCHARS 128
	const char printf_trunc[] = "..[TRUNCATED]..\n";
	char str[MAXCHARS];
	int len;
	va_list args;
	va_start(args, format);
	len = vsnprintf(str, MAXCHARS, format, args);
	va_end(args);
	if (len > MAXCHARS - 1) {
		/* vsnptintf() returns the number of characters needed */
		EE_uart_send_buffer(str, MAXCHARS - 1 );
		EE_uart_send_buffer(printf_trunc, sizeof(printf_trunc) - 1);
	} else {
		EE_uart_send_buffer(str, len);
	}
}

/*
 * MAIN TASK
 */
int main(void)
{	
	/* Uart configuration */
	EE_uart_config(115200, EE_UART_BIT8_NO | EE_UART_BIT_STOP_1);
	EE_uart_set_ISR_mode(EE_UART_POLLING | EE_UART_RXTX_BLOCK);  
	
	/* Flash test */
	#define BUF_SIZE 10
	EE_UINT32 buff[BUF_SIZE] = {0xABCDEF01,0xABCDEF02,0xABCDEF03,0xABCDEF04,
		                        0xABCDEF05,0xABCDEF06,0xABCDEF07,0xABCDEF08,
		                        0xABCDEF09,0xABCDEF0A};
	spi_flash_erase_chip(spi_flash_SPIFlash.control_base);
    spi_flash_write_buffer(spi_flash_SPIFlash.control_base, spi_flash_SPIFlash.memory_base, buff, BUF_SIZE*4);
    
 	/* Test results */
    int i;
    const EE_UINT32 *flash_mem = (const EE_UINT32 *)(spi_flash_SPIFlash.memory_base);
    for(i=0; i<BUF_SIZE; i++)
    	myprintf("flash_mem[%d]:%x\n", i, flash_mem[i]);
    
    /* Background activities */
    while(1)
    	;
    return 0;
}



