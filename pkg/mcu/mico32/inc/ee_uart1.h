/** 
* ee_uart.h
*/

#ifndef __INCLUDE_EEMCUMICO32_UART1_H__
#define __INCLUDE_EEMCUMICO32_UART1_H__

#include "mcu/mico32/inc/ee_uart.h"


/****************************************************************
     *                                                  
     * UART Device Register-map                          
     *                                                   
*****************************************************************/
//    typedef struct st_MicoUart{
//        volatile unsigned int rxtx;
//        volatile unsigned int ier;
//        volatile unsigned int iir;
//        volatile unsigned int lcr;
//        volatile unsigned int mcr;
//        volatile unsigned int lsr;
//        volatile unsigned int msr;
//        volatile unsigned int div;
//    }MicoUart_t;


/*************************************************** 
* Symbols and macros definition
****************************************************/
// ...

/*************************************************** 
* Functions declarations
****************************************************/
void EE_uart1_handler(void);


#endif // __INCLUDE_EEMCUMICO32_UART1_H__
