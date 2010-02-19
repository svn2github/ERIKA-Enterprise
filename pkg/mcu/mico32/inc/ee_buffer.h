/** 
* ee_buffer.h
*/

#ifndef __INCLUDE_EEMCUMICO32_BUFFER_H__
#define __INCLUDE_EEMCUMICO32_BUFFER_H__

#include "ee.h"						// to refer Erika Enterprise.

typedef struct {
    int g;							// get index: points to the first packet to be extracted
	int p;							// put index: points to the next empty location
	int counter;					// counter: to make difference between full queue and empty queue...
	int msg_size;					// size of a single message
	int buf_size;					// size of the buffer (vector of messages)
	char *data;						// buffer data (messages) vector
} EE_buffer;


/*************************************************** 
* Symbols and macros definition
****************************************************/
#define EE_BUF_OK			(0x00)
#define EE_BUF_ERR_SIZE 	(-1)
#define EE_BUF_ERR_FULL 	(-2)
#define EE_BUF_ERR_EMPTY 	(-3)
#define EE_BUF_ERR_NULL 	(-4)

#define buf(i,j) buf->data[(i) * buf->msg_size + (j)]


/*************************************************** 
* Functions declarations
****************************************************/
int EE_buffer_init(EE_buffer *buf, int msgsize, int bufsize, char *vet);	// vet must be: char vet[msgsize*bufsize]
int EE_buffer_putmsg(EE_buffer *buf, char* msg);
int EE_buffer_getmsg(EE_buffer *buf, char* msg);
int EE_buffer_isempty(EE_buffer *buf);
int EE_buffer_isfull(EE_buffer *buf);

#endif // __INCLUDE_EEMCUMICO32_BUFFER_H__
