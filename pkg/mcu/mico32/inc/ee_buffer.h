/** 
* ee_buffer.h
*/

#ifndef __INCLUDE_EEMCUMICO32_BUFFER_H__
#define __INCLUDE_EEMCUMICO32_BUFFER_H__

#include "cpu/mico32/inc/ee_internal.h"

typedef struct {
    int g;							// get index: points to the first packet to be extracted
	int p;							// put index: points to the next empty location
	int counter;					// counter: to make difference between full queue and empty queue...
	int msg_size;					// size of a single message
	int buf_size;					// size of the buffer (vector of messages)
	char *data;						// buffer vector (dimension: msg_size * buf_size)
} EE_buffer;


/*************************************************** 
* Symbols and macros definition
****************************************************/
#define EE_BUF_OK			(0x00)
#define EE_BUF_ERR_SIZE 	(-1)
#define EE_BUF_ERR_FULL 	(-2)
#define EE_BUF_ERR_EMPTY 	(-3)
#define EE_BUF_ERR_NULL 	(-4)

//#define EE_NO_BUF_INIT 		(0xC0)
//#define EE_RX_BUF_INIT 		(0xC1)
//#define EE_TX_BUF_INIT 		(0xC2)
//#define EE_RXTX_BUF_INIT 		(0xC3)

#define EE_NULL_BUF			((EE_buffer *)0)

#define buf(i,j) buf->data[(i) * buf->msg_size + (j)]


/*************************************************** 
* Functions declarations
****************************************************/
/*
	int EE_buffer_init(EE_buffer *buf, int msgsize, int bufsize, char *vet);
		This function is used to initialize a buffer. 
		Arguments:
			- EE_buffer *buf: buffer pointer
			- int msgsize: size of a message
			- int bufsize: size of the buffer   
			- char *vet: vector used for buffering (vector size: msgsize*bufsize)
		Actions: 
			- reset counters and indexes (this function works with interrupts disabled...)
		Return values:
			- the function return the result: EE_BUF_OK if no errors found
*/
int EE_buffer_init(EE_buffer *buf, int msgsize, int bufsize, char *vet);	// vet must be: char vet[msgsize*bufsize]


/*
	int EE_buffer_putmsg(EE_buffer *buf, char* msg);
		This function puts a new message in the buffer.
		Arguments:
			- EE_buffer *buf: buffer pointer
			- char *msg: address of first location of the message to be loaded 
		Actions: 
			- puts a message in the buffer if there is a free location (this function works with interrupts disabled...)
		Return values:
			- the function return the result: EE_BUF_OK if no errors found
											  EE_BUF_ERR_FULL if buffer is full	
*/
int EE_buffer_putmsg(EE_buffer *buf, char* msg);


/*
	int EE_buffer_getmsg(EE_buffer *buf, char* msg);
		This function extracts a message from the buffer.
		Arguments:
			- EE_buffer *buf: buffer pointer
			- char *msg: address of first location of the message to be written with the extracted message 
		Actions: 
			- extracts a message from the buffer if buffer is not empty (this function works with interrupts disabled...)
		Return values:
			- the function return the result: EE_BUF_OK if no errors found
											  EE_BUF_ERR_EMPTY if buffer is empty	
*/
int EE_buffer_getmsg(EE_buffer *buf, char* msg);

/*
	int EE_buffer_isempty(EE_buffer *buf);
		This function can be used to check if the buffer is empty.
		Arguments:
			- EE_buffer *buf: buffer pointer
		Actions: 
			- this function checks the counter of the buffer (this function works with interrupts disabled...)
		Return values:
			- the function return the result: 1 if buffer is empty
											  0 if buffer is not empty	
*/
int EE_buffer_isempty(EE_buffer *buf);

/*
	int EE_buffer_isfull(EE_buffer *buf);
		This function can be used to check if the buffer is full.
		Arguments:
			- EE_buffer *buf: buffer pointer
		Actions: 
			- this function compare the counter of the buffer with the max size (this function works with interrupts disabled...)
		Return values:
			- the function return the result: 1 if buffer is full
											  0 if buffer is not full	
*/
int EE_buffer_isfull(EE_buffer *buf);

#endif // __INCLUDE_EEMCUMICO32_BUFFER_H__
