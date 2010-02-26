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

int EE_buffer_init(EE_buffer *buf, int msgsize, int bufsize, EE_UINT8 *vet)
{
	unsigned int intst;
  
	intst = EE_mico32_disableIRQ();				//EE_hal_disableIRQ();
	buf->g = 0;
  	buf->p = 0;
  	buf->counter = 0;
  	buf->msg_size = msgsize;
  	buf->buf_size = bufsize;
  	buf->data = vet;
	if (EE_mico32_are_IRQs_enabled(intst))		//EE_hal_enableIRQ();
        EE_mico32_enableIRQ();
        
  	// All done!!!
  	return EE_BUF_OK;	  	
}

int EE_buffer_isempty(EE_buffer *buf)
{
	int retvalue;
	unsigned int intst;
	
	intst = EE_mico32_disableIRQ();				//EE_hal_disableIRQ();
	if((buf->g == buf->p) && (buf->counter==0))
		retvalue = 1;
	else
		retvalue = 0; 	
	if (EE_mico32_are_IRQs_enabled(intst))		//EE_hal_enableIRQ();
        EE_mico32_enableIRQ();
	
	return retvalue;	
}


int EE_buffer_isfull(EE_buffer *buf)
{
	int retvalue;
	unsigned int intst;
	
	intst = EE_mico32_disableIRQ();				//EE_hal_disableIRQ();
	if((buf->g == buf->p) && (buf->counter==buf->buf_size))
		retvalue = 1;
	else
		retvalue = 0;
	if (EE_mico32_are_IRQs_enabled(intst))		//EE_hal_enableIRQ();
        EE_mico32_enableIRQ();
		
	return retvalue;	
}

int EE_buffer_putmsg(EE_buffer *buf, EE_UINT8* msg)
{
	int retvalue;
	int i=0;
	unsigned int intst;
	
	if(msg==NULL)
		return EE_BUF_ERR_NULL;
	
	intst = EE_mico32_disableIRQ();				//EE_hal_disableIRQ();
	if((buf->g == buf->p) && (buf->counter==buf->buf_size))
		retvalue = EE_BUF_ERR_FULL;
	else
	{ 	
		for(i=0;i<(buf->msg_size);i++)	
    		buf(buf->p,i) = msg[i];				//buf->data[buf->p][i] = msg[i];
    	buf->p++;
    	if(buf->p == buf->buf_size)
    		buf->p = 0;							//buf->p = (buf->p % (buf->buf_size));
    	buf->counter++;
    	retvalue = EE_BUF_OK;
	}
    if (EE_mico32_are_IRQs_enabled(intst))		//EE_hal_enableIRQ();
        EE_mico32_enableIRQ();
    
  	return retvalue;
}

int EE_buffer_getmsg(EE_buffer *buf, EE_UINT8* msg)
{
	int retvalue;
	int i=0;
	unsigned int intst;
	
	if(msg==NULL)
		return EE_BUF_ERR_NULL;
	
	intst = EE_mico32_disableIRQ();				//EE_hal_disableIRQ();
	if((buf->g == buf->p) && (buf->counter==0)) 
		retvalue = EE_BUF_ERR_EMPTY; 
	else
	{	
  		for(i=0;i<(buf->msg_size);i++)	
    		msg[i] = buf(buf->g,i);				//buf->data[buf->g][i];
  		buf->g++;
  		if(buf->g == buf->buf_size)
  			buf->g = 0;							//buf->g = (buf->g % (buf->buf_size));
  		buf->counter--;
  		retvalue = EE_BUF_OK;
	}
  	if (EE_mico32_are_IRQs_enabled(intst))		//EE_hal_enableIRQ();
        EE_mico32_enableIRQ();
  	
  	return retvalue;
}

