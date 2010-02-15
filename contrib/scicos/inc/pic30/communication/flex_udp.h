/*
 * mtcpip_tcp_server.h
 *
 *  Created on: 17/nov/2009
 *      Author: Daniele Alessandrelli
 */

#ifndef ETH_TASK_H_
#define ETH_TASK_H_

#include "TCPIP_Stack/TCPIP.h"

#define SCICOS_UDP_CHANNELS 15
#define REMOTE_PORT_NULL 0 
#define UDP_PKG_LEN 60
#define UDP_BUF_SIZE 10

extern volatile unsigned long int UDP_flex_port;		// FLEX SERVER PORT NUMBER
extern volatile unsigned long int UDP_pc_port;			// PC SERVER PORT NUMBER
extern volatile unsigned char UDP_is_initialized;		// udp initialization flag
extern NODE_INFO UDP_remote;

extern BYTE scicosUDP_rx_buffer[UDP_PKG_LEN];	// buffer for UDP reception
extern BYTE scicosUDP_tx_buffer[UDP_PKG_LEN];	// buffer for UDP transmission

typedef char UDP_message[UDP_PKG_LEN];
typedef struct {
    int g;			// get index: points to the first packet to be extracted
	int p;			// put index: points to the next empty location
	int counter;	// counter: to make difference between full queue and empty queue...
	UDP_message data[UDP_BUF_SIZE];
} UDP_buffer;

extern UDP_buffer UDP_rx_buffer;
extern UDP_buffer UDP_tx_buffer;
void UDP_Buffer_Init(UDP_buffer *buf, int dim);
int UDP_Buffer_Putmsg(UDP_buffer *buf, BYTE* msg, int dim);
int UDP_Buffer_Getmsg(UDP_buffer *buf, BYTE* msg, int dim);
void UDP_Buffer_Close(UDP_buffer *buf);
int UDP_Buffer_Isempty(UDP_buffer *buf);
int UDP_Buffer_Isfull(UDP_buffer *buf, int dim);

/*
TASKs
*/
DeclareTask(UDP_TASK);

#endif /* ETH_TASK_H_ */
