#include "ee.h"

#include "./define.h"
#include "./variable.h"

//-----------------------------------------------------------------------------
// Utility functions on ring buffers
//-----------------------------------------------------------------------------
unsigned char IsBufferEmpty(RingBuf * pBuf)
{
	unsigned char	result;

	if (pBuf->count == 0)
		result = DPS_TRUE;
	else
		result = DPS_FALSE;

	return result;
}

unsigned char IsBufferFull(RingBuf * pBuf)
{
	unsigned char	result;

	if (pBuf->count == pBuf->size)
		result = DPS_TRUE;
	else
		result = DPS_FALSE;

	return result;
}

int	CountBuffer(RingBuf * pBuf)
{
	return pBuf->count;
}

void PushBuffer(RingBuf * pBuf, unsigned char byte)
{
	pBuf->buffer[pBuf->head] = byte;
	pBuf->head++;
	if (pBuf->head == pBuf->size)
		pBuf->head = 0;
	pBuf->count++;
}

unsigned char PopBuffer(RingBuf * pBuf)
{
	unsigned char	data;
	//assert(pBuf->count > 0);
	data = pBuf->buffer[pBuf->tail];
	pBuf->tail++;
	if (pBuf->tail == pBuf->size)
		pBuf->tail = 0;
	pBuf->count--;

	return data;
}

unsigned char TopBuffer(RingBuf * pBuf)
{
	unsigned char	data;
	//assert(pBuf->count > 0);
	data = pBuf->buffer[pBuf->tail];

	return data;
}

//-----------------------------------------------------------------------------
// Utility functions on LED
//	Only one YELLOW LED is available for application.
//	3 GREEN LEDs are dedicated to Power status.
//-----------------------------------------------------------------------------
unsigned char	statusYellowLED = LED_OFF;
void	TurnOnYellowLED()
{
	statusYellowLED = LED_OFF;
	LATBbits.LATB14 = statusYellowLED;
}

void	TurnOffYellowLED()
{
	statusYellowLED = LED_ON;
	LATBbits.LATB14 = statusYellowLED;
}

void	ToggleYellowLED()
{
	statusYellowLED ^= 0x01;		//toggle status
	LATBbits.LATB14 = statusYellowLED;
}
