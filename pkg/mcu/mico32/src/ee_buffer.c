/** 
* @file ee_timer.c
*/

#include "mcu/mico32/inc/ee_buffer.h"
//#include "ee_internal.h"

/******************************************************************************/
/*                             Utility Macros                                 */
/******************************************************************************/
// ...

/******************************************************************************/
/*                       Private Local Variables                              */
/******************************************************************************/

/******************************************************************************/
/*                       Private Local Functions                              */
/******************************************************************************/
// ...

/******************************************************************************/
/*                              ISRs                                          */
/******************************************************************************/


/******************************************************************************/
/*                       Public Global Functions                              */
/******************************************************************************/

/******************************************************************************/
/*                             Buffer Management                              */
/******************************************************************************/

//typedef struct {
//  EE_INT16 g;							// get index: points to the first packet to be extracted
//	EE_INT16 p;							// put index: points to the next empty location
//	EE_INT16 counter;					// counter: to make difference between full queue and empty queue...
//	EE_INT16 msg_size;					// size of a single message
//	EE_INT16 buf_size;					// size of the buffer (vector of messages)
//	EE_INT8 *data;						// buffer data (messages) vector
//} ee_buffer;

EE_UINT8 EE_buffer_init(EE_buffer *buf, EE_INT16 msgsize, EE_INT16 bufsize, EE_INT8 *vet)
{
  	if((msgsize < 0) || (bufsize < 0))	
  		return EE_BUF_ERR_SIZE;

	EE_hal_disableIRQ();
	buf->g = 0;
  	buf->p = 0;
  	buf->counter = 0;
  	buf->msg_size = msgsize;
  	buf->buf_size = bufsize;
  	buf->data = vet;
	EE_hal_enableIRQ();
		
  	// All done!!!
  	return EE_BUF_OK;	  	
}

EE_UINT8 EE_buffer_isempty(EE_buffer *buf)
{
	EE_UINT8 retvalue;
	
	EE_hal_disableIRQ();
	if((buf->g == buf->p) && (buf->counter==0))
		retvalue = 1;
	else
		retvalue = 0; 	
	EE_hal_enableIRQ();	
	
	return retvalue;	
}


EE_UINT8 EE_buffer_isfull(EE_buffer *buf)
{
	EE_UINT8 retvalue;
	
	EE_hal_disableIRQ();
	if((buf->g == buf->p) && (buf->counter==buf->buf_size))
		retvalue = 1;
	else
		retvalue = 0;
	EE_hal_enableIRQ();	
		
	return retvalue;	
}

EE_UINT8 EE_buffer_putmsg(EE_buffer *buf, EE_INT8* msg)
{
	int i=0;
	
	if(msg==NULL)
		return EE_BUF_ERR_NULL;
	
	EE_hal_disableIRQ();
	if((buf->g == buf->p) && (buf->counter==buf->buf_size))	
	{
		EE_hal_enableIRQ();	
		return EE_BUF_ERR_FULL; 	
	}
	for(i=0;i<(buf->msg_size);i++)	
    	buf(buf->p,i) = msg[i];					//buf->data[buf->p][i] = msg[i];
    buf->p++;
    buf->p = (buf->p % (buf->buf_size));
    buf->counter++;
    EE_hal_enableIRQ();	
    
    // All done!!!
  	return EE_BUF_OK;
}

EE_UINT8 EE_buffer_getmsg(EE_buffer *buf, EE_INT8* msg)
{
	int i=0;
	
	if(msg==NULL)
		return EE_BUF_ERR_NULL;
	
	EE_hal_disableIRQ();
	if((buf->g == buf->p) && (buf->counter==0)) 
	{
		EE_hal_enableIRQ();	
		return EE_BUF_ERR_EMPTY; 	
	}
  	for(i=0;i<(buf->msg_size);i++)	
    	msg[i] = buf(buf->g,i);					//buf->data[buf->g][i];
  	buf->g++;
  	buf->g = (buf->g % (buf->buf_size));
  	buf->counter--;
  	EE_hal_enableIRQ();	
  	
  	// All done!!!
  	return EE_BUF_OK;
}

