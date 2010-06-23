/*
  Name: test9.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: LWIP tcp test.
*/

#ifndef __TEST9_H__
#define __TEST9_H__

/* RT-Kernel */
#include <ee.h>

/* Macros used in the application code */
#define LWIP_ON
#define PRINT_ON

#define turn_on_led() 				EE_misc_gpio_write_bit_data(1,EE_DL3_BIT)
#define turn_off_led() 				EE_misc_gpio_write_bit_data(0,EE_DL3_BIT)
/* Size of the expected payload */
#define TCP_PAYLOAD_PKT_SIZE 		4

/* Functions used in the application code */
void system_timer_callback(void);
void print_pbuf(const char *name, struct pbuf *p);
void print_array(const char *name, BYTE* vet, int len);
void print_time_results(void);
void myprintf(const char *format, ...);
void tsprintf(const char* format, ...);
void do_something(struct pbuf *p);

#endif //__TEST9_H__
