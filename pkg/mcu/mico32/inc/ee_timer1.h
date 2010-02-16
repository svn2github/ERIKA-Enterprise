/** 
* ee_timer.h
*/

#ifndef __INCLUDE_EEMCUMICO32_TIMER1_H__
#define __INCLUDE_EEMCUMICO32_TIMER1_H__



/*********************************************************************
     *                                                    
     * Timer Device Register-map                         
     *                                                    
**********************************************************************/
//	typedef struct st_MicoTimer
//	{
//        volatile unsigned int Status;
//        volatile unsigned int Control;
//        volatile unsigned int Period;
//        volatile unsigned int Snapshot;
//	}MicoTimer_t;


/*************************************************** 
* Symbols and macros definition
****************************************************/
// ...

/*************************************************** 
* Functions declarations
****************************************************/
void EE_timer1_handler(void);


#endif // __INCLUDE_EEMCUMICO32_TIMER1_H__
