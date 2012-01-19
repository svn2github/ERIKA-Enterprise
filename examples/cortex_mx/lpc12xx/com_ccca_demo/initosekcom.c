/*
 * Author: 2012 Gianluca Franchino
 */

//#include "com/osek/cominit.h"
#include "com/com/inc/ee_cominit.h"
/* Modes definition
 */
COMApplicationModeType EE_com_validmodes[EE_COM_N_MODE] = {EE_COM_MODE_A};

/* Message definition 
 */
/* Reception
 */
EE_TID task_to_call = Task1;
//extern void callback(void); /*GF: dovremmo usare EE_COM_DECLARE_CALL_BACK(callback);*/
//EE_COM_DEFINE_INTERNAL_UNQUEUED_MESSAGE(RECEIVER1,32,F_Always,NULL,EE_COM_T_OK,&task_to_call,RECEIVER2);

EE_COM_DECLARE_CALL_BACK(callback);

EE_COM_DEFINE_INTERNAL_UNQUEUED_MESSAGE(RECEIVER1, 32, F_Always, NULL, 
										EE_COM_T_OK,Task1, RECEIVER2);
EE_COM_DEFINE_INTERNAL_UNQUEUED_MESSAGE(RECEIVER2, 32, F_Always, NULL, 
										EE_COM_CB_OK, (void*)callback, 
										EE_COM_NULL);
/* Transmission
 */
EE_COM_DEFINE_INTERNAL_MESSAGE(ABS,32,RECEIVER1);


/* Other config
 */
struct EE_com_msg_RAM_TYPE * EE_com_msg_RAM[EE_COM_N_MSG] = {
  EE_com_msg_RAM(ABS),
  EE_com_msg_RAM(RECEIVER1),
  EE_com_msg_RAM(RECEIVER2)
};

const struct EE_com_msg_ROM_TYPE * EE_com_msg_ROM[EE_COM_N_MSG] = {
  EE_com_msg_ROM(ABS),
  EE_com_msg_ROM(RECEIVER1),
  EE_com_msg_ROM(RECEIVER2)
};
