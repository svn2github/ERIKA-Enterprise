/*
 * flex_can.h
 *
 *  Created on: 16/07/2010
 *      Author: Dario Di Stefano
 */

#ifndef CAN_SCICOS_H_
#define CAN_SCICOS_H_

#define EE_CAN_BUF_SIZE 64
#define SCICOS_CAN_CHANNELS 16
#define SIZE_OF_ELEMENT 4
#define u(i,j) ((double *)block->inptr[i])[j]
#define y(i,j) ((double *)block->outptr[i])[j]

#define CAN_PKT_LEN 8
#define CAN_BUF_SIZE 20

#ifndef CAN_DEBUG
#define can_debug_print_string(a)
#define can_debug_print_val(a,b)
#else
void can_debug_print_string(char *str);
void can_debug_print_val(char *str, int val);
#endif

/* CAN scicos types */
typedef char CAN_message[CAN_PKT_LEN];
typedef struct {
    int g;			// get index: points to the first packet to be extracted
	int p;			// put index: points to the next empty location
	int counter;	// counter: to make difference between full queue and empty queue...
	CAN_message data[CAN_BUF_SIZE];
} CAN_buffer;

/* Global variables used in the CAN scicos code */
/* buffer */
extern EE_UINT8 scicosCAN1_rx_buffer[CAN_PKT_LEN];	// buffer for CAN reception
extern EE_UINT8 scicosCAN1_tx_buffer[CAN_PKT_LEN];	// buffer for CAN transmission
extern CAN_buffer CAN1_rx_buffer;
extern CAN_buffer CAN1_tx_buffer;
/* tx */
extern EE_UINT8 ecan1_tx_initialized;
extern EE_UINT32 ecan1_tx_id;     /* contain the id for can messages */
extern EE_UINT8 ecan1_tx_len;
extern EE_UINT8 ecan_tx_canid;
extern EE_UINT8 ecan1_tx_div;
extern void (*EE_eCAN1_tx_cbk) (void);
/* rx */
extern EE_UINT8 ecan1_rx_initialized;
extern void (*EE_eCAN1_rx_cbk) (void);
extern EE_UINT8 ecan_rx_canid;
extern ee_ecan_mID rx_ecan1message1;//RX message for id=1
extern ee_ecan_mID rx_ecan1message2;//RX message for id=2
extern ee_ecan_mID rx_ecan1message3;//RX message for id=3
extern ee_ecan_mID rx_ecan1message4;//RX message for id=99
extern EE_UINT32 ecan1_rx_id;     /* contain the id for can messages */
extern EE_UINT8 ecan1_rx_len;
extern EE_UINT8 ecan1_rx_div;

/* CAN buffer library  */
void CAN_Buffer_Init(CAN_buffer *buf);
int CAN_Buffer_Putmsg(CAN_buffer *buf, EE_UINT8* msg, int dim);
int CAN_Buffer_Getmsg(CAN_buffer *buf, EE_UINT8* msg, int dim);
void CAN_Buffer_Close(CAN_buffer *buf);
int CAN_Buffer_Isempty(CAN_buffer *buf);
int CAN_Buffer_Isfull(CAN_buffer *buf, int dim);
int CAN_Buffer_count(CAN_buffer *buf);

/* CAN scicos blocks library */
void EE_eCAN1_cbk(int flag);
void EE_eCAN1_init(void);
void EE_eCAN1_send(EE_UINT8 *data, int len, int id);
void EE_eCAN1_tx_service(void);
void EE_eCAN1_rx_service(void);

#endif /* CAN_SCICOS_H_ */