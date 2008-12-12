#ifndef __pic30_c__
#define __pic30_c__
/** 
* @file pic30.c
* @brief PIC30 Hardware Abstraction Layer implementation.
* @author Marinoni Mauro, Nastasi Christian
* @date 2008-11-03
*/

#ifdef __PIC30__
#ifdef USE_CONSOLE

#include "hal/pic30.h"

/* ************************************************************************** */
/*                           HAL Functions Definition                         */
/* ************************************************************************** */
#ifdef USE_CONSOLE_SERIAL
int console_serial_hal_open(uint8_t port, uint32_t baudrate, uint16_t flags)
{
	switch (port) {
	case 0:
		EE_UART1_Init(baudrate, flags, TX_INT_SINGLE & RX_INT_SINGLE);
		return 0;
	case 1:
		EE_UART2_Init(baudrate, flags, TX_INT_SINGLE & RX_INT_SINGLE);
		return 0;
	}
	return -1;
}

int console_serial_hal_close(uint8_t port)
{
	/*
	switch (port) {
	case 0:
		return 0;
	case 1:
		return 0;
	}
	*/
	return -1;
}

int console_serial_hal_write(uint8_t port, uint8_t *mesg, uint16_t length)
{
	int i;
	
	switch (port) {
	case 0:
		/* TODO!!! - Buffer management in interrupt mode */
		for (i=0; i<length; i++)
			EE_UART1_Send(mesg[i]);
		return 0;
	case 1:
		/* TODO!!! - Buffer management in interrupt mode*/
		for (i=0; i<length; i++)
			EE_UART2_Send(mesg[i]);
		return 0;
	}
	return -1;
}

int console_serial_hal_read(uint8_t port, uint8_t *mesg, uint16_t length, 
								uint16_t *read)
{
	int i;
	
	switch (port) {
	case 0:
		/* TODO!!! - Buffer management in interrupt mode */
		for(i=0; i<length; i++)
			EE_UART1_Receive(mesg+i);
		return 0;
	case 1:
		/* TODO!!! - Buffer management in interrupt mode */
		for(i=0; i<length; i++)
			EE_UART2_Receive(mesg+i);
		return 0;
	}
	return -1;
}
#endif /* USE_CONSOLE_SERIAL */

#endif /* USE_CONSOLE */
#endif /* __PIC30__ */
#endif /* __pic30_c__ */
