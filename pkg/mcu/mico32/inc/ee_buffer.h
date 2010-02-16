/** 
* ee_buffer.h
*/

#ifndef __INCLUDE_EEMCUMICO32_BUFFER_H__
#define __INCLUDE_EEMCUMICO32_BUFFER_H__

#include "ee.h"							// to refer Erika Enterprise.

typedef struct {
    EE_INT16 g;							// get index: points to the first packet to be extracted
	EE_INT16 p;							// put index: points to the next empty location
	EE_INT16 counter;					// counter: to make difference between full queue and empty queue...
	EE_INT16 msg_size;					// size of a single message
	EE_INT16 buf_size;					// size of the buffer (vector of messages)
	EE_INT8 *data;						// buffer data (messages) vector
} EE_buffer;


/*************************************************** 
* Symbols and macros definition
****************************************************/
#define EE_BUF_OK			(0x00)
#define EE_BUF_ERR_SIZE 	(0xE1)
#define EE_BUF_ERR_FULL 	(0xE2)
#define EE_BUF_ERR_EMPTY 	(0xE3)
#define EE_BUF_ERR_NULL 	(0xE4)

#define buf(i,j) buf->data[(i) * buf->msg_size + (j)]


/*************************************************** 
* Functions declarations
****************************************************/
EE_UINT8 EE_buffer_init(EE_buffer *buf, EE_INT16 msgsize, EE_INT16 bufsize, EE_INT8 *vet);	// vet must be: char vet[msgsize*bufsize]
EE_UINT8 EE_buffer_putmsg(EE_buffer *buf, EE_INT8* msg);
EE_UINT8 EE_buffer_getmsg(EE_buffer *buf, EE_INT8* msg);
EE_UINT8 EE_buffer_isempty(EE_buffer *buf);
EE_UINT8 EE_buffer_isfull(EE_buffer *buf);

#endif // __INCLUDE_EEMCUMICO32_BUFFER_H__
