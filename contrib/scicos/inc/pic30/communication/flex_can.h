/*
 * flex_can.h
 *
 *  Created on: 17/nov/2009
 *      Author: Dario Di Stefano
 */

#ifndef CAN_TASK_H_
#define CAN_TASK_H_

#define EE_CAN_BUF_SIZE 64
#define SCICOS_CAN_CHANNELS 16
#define SIZE_OF_ELEMENT 4
#define u(i,j) ((double *)block->inptr[i])[j]
#define y(i,j) ((double *)block->outptr[i])[j]

#define CAN_PKT_LEN 8
#define CAN_BUF_SIZE 20

void print_string(char *str);

typedef char CAN_message[CAN_PKT_LEN];
typedef struct {
    int g;			// get index: points to the first packet to be extracted
	int p;			// put index: points to the next empty location
	int counter;	// counter: to make difference between full queue and empty queue...
	CAN_message data[CAN_BUF_SIZE];
} CAN_buffer;

extern EE_UINT8 scicosCAN1_rx_buffer[CAN_PKT_LEN];	// buffer for CAN reception
extern EE_UINT8 scicosCAN1_tx_buffer[CAN_PKT_LEN];	// buffer for CAN transmission
extern CAN_buffer CAN1_rx_buffer;
extern CAN_buffer CAN1_tx_buffer;

void CAN_Buffer_Init(CAN_buffer *buf, int dim);
int CAN_Buffer_Putmsg(CAN_buffer *buf, EE_UINT8* msg, int dim);
int CAN_Buffer_Getmsg(CAN_buffer *buf, EE_UINT8* msg, int dim);
void CAN_Buffer_Close(CAN_buffer *buf);
int CAN_Buffer_Isempty(CAN_buffer *buf);
int CAN_Buffer_Isfull(CAN_buffer *buf, int dim);


extern EE_UINT8 ee_ecan1_initialized;
void EE_eCAN1_cbk(int flag);
void EE_eCAN1_init(void);
void EE_eCAN1_send(EE_UINT8 *data, int len, int id);

#endif /* CAN_TASK_H_ */
