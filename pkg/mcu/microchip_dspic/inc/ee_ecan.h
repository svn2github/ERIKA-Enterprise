/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation, 
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/*
 * PRELIMINARY VERSION
 * from patch sent by Tizar Rizano (UNITN)
 * Code originally written by Daniele Zadra (UNITN) and Roberto Bucher (SUPSI)
 */

#ifndef _ECAN_DEF_H
#define _ECAN_DEF_H


#ifdef __USE_CAN1__

/* DMA CODE */


/* ************************************************************************************** */

#define DMA_IRQ_INT0      (0L)
#define DMA_IRQ_IC1       (1L)
#define DMA_IRQ_IC2       (5L)
#define DMA_IRQ_OC1       (2L)
#define DMA_IRQ_OC2       (6L)
#define DMA_IRQ_TMR2      (7L)
#define DMA_IRQ_TMR3      (8L)
#define DMA_IRQ_SPI1      (10L)
#define DMA_IRQ_SPI2      (33L)
#define DMA_IRQ_UART1_RX  (11L)
#define DMA_IRQ_UART1_TX  (12L)
#define DMA_IRQ_UART2_RX  (30L)
#define DMA_IRQ_UART2_TX  (31L)
#define DMA_IRQ_ADC1      (13L)
#define DMA_IRQ_ADC2      (21L)
#define DMA_IRQ_DCI       (60L)
#define DMA_IRQ_ECAN1_RX  (34L)
#define DMA_IRQ_ECAN1_TX  (70L)
#define DMA_IRQ_ECAN2_RX  (55L)
#define DMA_IRQ_ECAN2_TX  (71L)


/* DMAxCON Configuration Bit Definitions */

#define DMA_MODULE_ON               0xFFFF /* DMA module on */
#define DMA_MODULE_OFF              0x7FFF /* DMA module off */

#define DMA_SIZE_BYTE			          0xFFFF /* DMA0 data size is byte */
#define DMA_SIZE_WORD			          0xBFFF /* DMA0 data size is word */

#define DMA_TO_PERIPHERAL		        0xFFFF	/* Direction: from DMA RAM address to peripheral*/ 
#define PERIPHERAL_TO_DMA		        0xDFFF	/* Direction: from peripheral address to DMA RAM */

#define DMA_INTERRUPT_HALF		      0xFFFF	/* interrupt when half of the data has been moved */
#define DMA_INTERRUPT_FULL		      0xEFFF	/* interrupt when all of the data has been moved */

#define DMA_WRITE_NULL			        0xFFFF	/* Null data write to peripheral in addition to DMA RAM write */
#define DMA_NORMAL			            0xF7FF	/* Normal operation */

#define DMA_PERIPHERAL_INDIRECT	    0xFF2F	/* Peripheral indirect addressing mode */
#define DMA_REGISTER			          0xFF1F	/* Register indirect without post increment */
#define DMA_REGISTER_POST_INCREMENT	0xFF0F	/* Register indirect with post incremenent */

#define DMA_ONE_SHOT_PING_PONG		  0xFFFF	/* One-Shot Mode,   Ping-Pong enabled */
#define DMA_CONTINUOUS_PING_PONG	  0xFFF2	/* Continuous Mode, Ping-Pong enabled */
#define DMA_ONE_SHOT			          0xFFF1	/* One-shot Mode,   Ping-Pong disabled */
#define DMA_CONTINUOUS			        0xFFF0	/* Continuous Mode, Ping-Pong disabled */

/* ************************************************************************************** */

typedef struct
{
  unsigned int	Config;			        /* DMAxCON */
  unsigned int	PeripheralIRQ;			/* DMAxIRQ */
  unsigned int	FirstBufferStart;		/* DMAxSTA */
  unsigned int	SecondBufferStart;	/* DMAxSTB */	
  unsigned int	FSRAddress;			    /* DMAxPAD */
  unsigned int	NumbersOfTransfer;	/* DMAxCNT */
}_s_DMA;

/* ************************************************************************************** */

#define EnableDMAInt(channel,prio) _DMA##channel##IF = 0;\
                                _DMA##channel##IE = 1;\
                                _DMA##channel##IP = prio;

#define DisableDMAInt(channel,prio) _DMA##channel##IF = 0;\
                                _DMA##channel##IE = 0;

#define ClearDmaIF(channel) _DMA##channel##IF = 0    

#define EnableDmaChannel(channel)  DMA##channel##CONbits.CHEN = 1
#define DisableDmaChannel(channel)  DMA##channel##CONbits.CHEN = 0

#define DmaInterrupt(channel) _DMA##channel##Interrupt(void)                            
/* ************************************************************************************** */

//__INLINE__ unsigned int __ALWAYS_INLINE__ InitDma( unsigned char Channel, _s_DMA *StrPtr);

extern unsigned int DMAIntFlag;

extern void *_DMA_BASE;

/* ************************************************************************************** */
                                   

/* ------------------------- */












/* byte / word addressing structures */

typedef union
{
  unsigned int w;
  struct
  {
    unsigned char lo;
    unsigned char hi;
  } b;
} u_wb;

typedef union
{
  EE_UINT32 lng;
  struct
  {
    EE_UINT16 lw;
    EE_UINT16 hw;
  } w;
}u_lw;



/******************************************************************/

//#define BITRATE   125000      /* CAN baudrate */

/******************************************************************/

#define ECAN1 0
#define ECAN2 1

/******************************************************************/

#define USE_MASK0   0
#define USE_MASK1   1
#define USE_MASK2   2
#define USE_NOMASK  3

/******************************************************************/


#define USE_AS_TRANSMIT (1U)
#define USE_AS_RECEIVE  (0U)

/******************************************************************/


#define STANDARD 0
#define EXTENDED 1


#define MASK0  0x00000000			//Value of mask 0
#define MASK0MODE  STANDARD

#define MASK1  0xFFFFFFFF			//Value of mask 1
#define MASK1MODE  STANDARD

#define MASK2  0xFFFFFFFF			//Value of mask 2
#define MASK2MODE  STANDARD



#define FILTER0 	 0x00000222
#define FILTER0MASK  USE_MASK0
#define FILTER0MODE  STANDARD

// #define FILTER1 	 0x00000333    //Value of filter n
// #define FILTER1MASK  USE_MASK0		  //Mask associated to filter n
// #define FILTER1MODE  STANDARD

// #define FILTER2 	 0x00000355
// #define FILTER2MASK  USE_MASK0
// #define FILTER2MODE  STANDARD

// #define FILTER3 	 0x00000000
// #define FILTER3MASK  USE_MASK0
// #define FILTER3MODE  STANDARD

// #define FILTER4 	 0x00000000		
// #define FILTER4MASK  USE_MASK0
// #define FILTER4MODE  STANDARD

// #define FILTER5 	 0x00000000
// #define FILTER5MASK  USE_MASK0
// #define FILTER5MODE  STANDARD


//Filter 6-14 NOT IMPLEMENTED

// #define FILTER6 	 0x00000000
// #define FILTER6MASK  MASK0
// #define FILTER6MODE  STANDARD

// #define FILTER7 	 0x00000000
// #define FILTER7MASK  MASK0
// #define FILTER7MODE  STANDARD

// #define FILTER8 	 0x00000000
// #define FILTER8MASK  MASK0
// #define FILTER8MODE  STANDARD

// #define FILTER9 	 0x00000000
// #define FILTER9MASK  MASK0
// #define FILTER9MODE  STANDARD

// #define FILTER10 	 0x00000000
// #define FILTER10MASK MASK0
// #define FILTER10MODE  STANDARD

// #define FILTER11 	 0x00000000
// #define FILTER11MASK MASK0
// #define FILTER11MODE  STANDARD

// #define FILTER12 	 0x00000000
// #define FILTER12MASK MASK0
// #define FILTER12MODE  STANDARD

// #define FILTER13 	 0x00000000
// #define FILTER13MASK MASK0
// #define FILTER13MODE  STANDARD

// #define FILTER14 	 0x00000000
// #define FILTER14MASK MASK0
// #define FILTER14MODE  STANDARD

// #define FILTER15 	 0x00000000
// #define FILTER15MASK MASK0
// #define FILTER15MODE  STANDARD 




/* structure represents the datas stored in DMAbuffer for receive and transmit */

/*
  sid :     - - - 10 9 8 7 6 5 4 3 2 1 0 SRR IDE
  eidh:     - - - - 17 16 15 14 13 12 11 10 9 8 7 6
  eidl_dlc: 5 4 3 2 1 0 RTR - - - - - DLC:4 
*/

typedef struct
{
  EE_UINT16 sid;       /* standard identifier 10:0,SRR, TXIDE */
  EE_UINT16 eidh;
  EE_UINT16 eidl_dlc;  /* extended identifier 17:0, DLC */
  EE_UINT8  data[8];
  EE_UINT16 config;    /* TXABT,TXLARB,TXERR,TXREQ,TXPRI 1:0 */
}_t_ecan;

/* defines for available DMA irqs */

#define kDMA_IRQ_INT0      (0L)
#define kDMA_IRQ_IC1       (1L)
#define kDMA_IRQ_IC2       (5L)
#define kDMA_IRQ_OC1       (2L)
#define kDMA_IRQ_OC2       (6L)
#define kDMA_IRQ_TMR2      (7L)
#define kDMA_IRQ_TMT3      (8L)
#define kDMA_IRQ_SPI1      (10L)
#define kDMA_IRQ_SPI2      (33L)
#define kDMA_IRQ_UART1_RX  (11L)
#define kDMA_IRQ_UART1_TX  (12L)
#define kDMA_IRQ_UART2_RX  (30L)
#define kDMA_IRQ_UART2_TX  (31L)
#define kDMA_IRQ_ADC1      (13L)
#define kDMA_IRQ_ADC2      (21L)
#define kDMA_IRQ_DCI       (60L)
#define kDMA_IRQ_ECAN1_RX  (34L)
#define kDMA_IRQ_ECAN1_TX  (70L)
#define kDMA_IRQ_ECAN2_RX  (55L)
#define kDMA_IRQ_ECAN2_TX  (71L)

//#define kDMA_BASE_ADDR  0x7800




//extern void ecan1Init(void);
//extern void ecan1ClkInit(void);

void EE_ecan_ReadMessage(EE_UINT16 bufptr,
			 EE_UINT32 *identifier,
			 EE_UINT8  *len,
			 EE_UINT8  *dptr);

void EE_ecan_WriteMessage(EE_UINT16 bufptr,
			  EE_UINT32 identifier,
			  EE_UINT8  len,
			  EE_UINT8  type,
			  EE_UINT8  *dptr);

void EE_ecan_SetFilter(EE_UINT8  module,
		       EE_UINT8  nr,
		       EE_UINT8  type,
		       EE_UINT32 id);

void EE_ecan_SetMask(EE_UINT8  module,
		     EE_UINT8  nr,
		     EE_UINT8  type,
		     EE_UINT32 id);

EE_UINT16 EE_ecan_GetFilterHit(EE_UINT16 bufptr);

/******************************************************************/



#define FCY       40000000    /* system clock */
#define BITRATE   125000      /* CAN baudrate */


//#define FCY       40000000    /* system clock */
// #define FCY       40000000    /* system clock */
// #define BITRATE   125000      /* CAN baudrate */

extern _t_ecan CanBuf[8];
extern EE_UINT8 can1_dma_flag;
extern EE_UINT8 can1_clk_flag;
extern EE_INT8 (*RxCan1IsrFunction)(EE_UINT8 data);


/* ***************************************************************************************** */

#define _ECAN1TX_DMACONFIG   DMA_MODULE_ON & DMA_SIZE_WORD & DMA_TO_PERIPHERAL & DMA_INTERRUPT_FULL & \
                              DMA_NORMAL & DMA_PERIPHERAL_INDIRECT & DMA_CONTINUOUS
#define _ECAN1RX_DMACONFIG   DMA_MODULE_ON & DMA_SIZE_WORD & PERIPHERAL_TO_DMA & DMA_INTERRUPT_FULL & \
                              DMA_NORMAL & DMA_PERIPHERAL_INDIRECT & DMA_CONTINUOUS
                       
/* ************************************************************************************** */

#define _DMA0SETUP = {  _ECAN1TX_DMACONFIG, DMA_IRQ_ECAN1_TX,(unsigned int)&CanBuf[0],0, (EE_UINT16)&C1TXD, 8};
                        
#define _DMA1SETUP = {  _ECAN1RX_DMACONFIG,\
                        DMA_IRQ_ECAN1_RX,\
                        (unsigned int)&CanBuf,\
                        0,\
                        (EE_UINT16)&C1RXD,\
                        8};

/* ************************************************************************************** */



__INLINE__ unsigned int __ALWAYS_INLINE__ InitDma( unsigned char Channel, _s_DMA *StrPtr)
{ 
  _s_DMA *DmaPtr;
  unsigned int temp;
  
  temp = (unsigned int)&DMA0CON;
  temp += __builtin_muluu(Channel,12L);
  
  //  temp = (unsigned int*)&DMA0CON + __builtin_muluu(Channel,12L);
  
  DmaPtr = (_s_DMA*)temp;

  temp = StrPtr -> Config;
  
  DmaPtr -> Config = 0;                     /* make sure that channel is disabled before initialisation */ 
  
  DmaPtr -> PeripheralIRQ = StrPtr -> PeripheralIRQ;
  DmaPtr -> FirstBufferStart = StrPtr -> FirstBufferStart - (unsigned int)&_DMA_BASE;
  DmaPtr -> SecondBufferStart = StrPtr -> SecondBufferStart - (unsigned int)&_DMA_BASE;
  DmaPtr -> FSRAddress = StrPtr -> FSRAddress;
  DmaPtr -> NumbersOfTransfer = (StrPtr -> NumbersOfTransfer) - 1;
  
  DmaPtr -> Config = StrPtr -> Config;
	
  return 1;  
}



__INLINE__ void __ALWAYS_INLINE__ EE_Can_Dma_Init(void){
  if (can1_dma_flag==0){
	
    const _s_DMA DmaCan1Tx _DMA0SETUP;
    const _s_DMA DmaCan1Rx _DMA1SETUP;
	
	
    /* DMA0 configuration */
    /* Direction: Read from DMA RAM and write to peripheral address 0x442 (C1TXD register)  */
    /* AMODE: Peripheral Indirect addressing */
    /* MODE: Continuous, Ping-Pong Disabled */
    /* IRQ: Ecan1 transmission */
    /* DMA RAM Memory Starts at dma_tx_buffer location for channel 0 */
    /* ***************************************************************************************** */

    InitDma(0,(_s_DMA*)&DmaCan1Tx);              /* initialize DMA0 supporting CAN1 TX */

    /* ***************************************************************************************** */
    /* DMA3 configuration   */
    /* Direction: Read from peripheral address 0x440 (C1RXD) and write to DMA RAM */
    /* AMODE: Peripheral Indirect addressing*/
    /* MODE: Continuous, Ping-Pong Disabled*/
    /* IRQ: Ecan1 Reception*/
    /* DMA Memory starts at dma_rcv_buffer location for channel 3*/
    /* ***************************************************************************************** */

    InitDma(1,(_s_DMA*)&DmaCan1Rx);  
    /* initialize DMA0 supporting CAN1 RX */
 
    EnableDMAInt(1,4);
    can1_dma_flag=1;
  }

}






__INLINE__ void __ALWAYS_INLINE__ EE_Ecan1_Clk_Init() 
{   if (can1_clk_flag==0){

  C1CTRL1bits.REQOP = 0x04;
  while(C1CTRL1bits.OPMODE != 0x04);              /* wait until module switched over to configuration mode */ 
	
  C1CTRL1bits.CANCKS = 1; 					//fcan clock is FCY
  C1CFG1 = (((FCY/16)/BITRATE)-1) & 0x003F;  
  C1CFG2 = 0x0290;                        
  C1INTF = 0;
  _C1IF = _C1TXIF = _C1RXIF = 0;
  C1INTE = 0x00FF;     
  _C1IE = _C1TXIE = _C1RXIE = 1;
	
  C1FCTRLbits.DMABS = 2;                      /* 8 - DMA buffers alocated in DMA RAM */
  C1FCTRLbits.FSA = 31;    
	
	
  C1CTRL1bits.REQOP = 0;                          /* request normal operation mode */
  while(C1CTRL1bits.OPMODE != 0);                 /* wait until switched back */
  can1_clk_flag=1;
}

}


//// Ecan1 Init
//// Buffer Size: 32 buffers (0-31)
//// FIFO Start: Buffer 31
//// Transmit Buffer: Buffer 0
//// Receive Buffer: Buffer 1


__INLINE__ void __ALWAYS_INLINE__ EE_Ecan1_RxInit(EE_INT8 (*RxCanFunctionCallBack)(EE_UINT8 data))
{	   
  C1CTRL1bits.REQOP = 0x04;
  while(C1CTRL1bits.OPMODE != 0x04);              /* wait until module switched over to configuration mode */ 

  	
  	 	
  C1CTRL2 = 0;
  C1CTRL1bits.WIN = 1;    /* access to Acceptance Filter Registers	*/
	
#ifdef MASK0
  EE_ecan_SetMask(ECAN1,0,MASK0MODE,(EE_UINT32)MASK0); /* setup mask0  */
#endif
	
#ifdef MASK1
  EE_ecan_SetMask(ECAN1,1,MASK1MODE,(EE_UINT32)MASK1); /* setup mask1  */
#endif
	
#ifdef MASK2
  EE_ecan_SetMask(ECAN1,2,MASK2MODE,(EE_UINT32)MASK2); /* setup mask02 */
#endif
	
		                         	
	  	
#ifdef FILTER0
  EE_ecan_SetFilter(ECAN1,0,FILTER0MODE,(EE_UINT32)FILTER0);
  C1BUFPNT1bits.F0BP = 0x02;		/* buffer2 used when filter0 hit */
#endif
#ifdef FILTER1
  EE_ecan_SetFilter(ECAN1,1,FILTER1MODE,(EE_UINT32)FILTER1);
  C1BUFPNT1bits.F1BP = 0x03;		/* buffer3 used when filter1 hit */
#endif
#ifdef FILTER2
  EE_ecan_SetFilter(ECAN1,2,FILTER2MODE,(EE_UINT32)FILTER2);
  C1BUFPNT1bits.F2BP = 0x04;		/* buffer4 used when filter2 hit */
#endif
#ifdef FILTER3
  EE_ecan_SetFilter(ECAN1,3,FILTER3MODE,(EE_UINT32)FILTER3);
  C1BUFPNT1bits.F3BP = 0x05;		/* buffer5 used when filter3 hit */
#endif
#ifdef FILTER4
  EE_ecan_SetFilter(ECAN1,4,FILTER4MODE,(EE_UINT32)FILTER4);
  C1BUFPNT2bits.F4BP = 0x06;		
#endif
#ifdef FILTER5
  EE_ecan_SetFilter(ECAN1,5,FILTER5MODE,(EE_UINT32)FILTER5);
  C1BUFPNT2bits.F5BP = 0x07;		
#endif
#ifdef FILTER6
  EE_ecan_SetFilter(ECAN1,6,FILTER6MODE,(EE_UINT32)FILTER6);
  C1BUFPNT2bits.F6BP = 0x07;	
#endif
#ifdef FILTER7
  EE_ecan_SetFilter(ECAN1,7,FILTER7MODE,(EE_UINT32)FILTER7);
  C1BUFPNT2bits.F7BP = 0x07;		
#endif
#ifdef FILTER8
  EE_ecan_SetFilter(ECAN1,8,FILTER8MODE,(EE_UINT32)FILTER8);
  C1BUFPNT3bits.F7BP = 0x07;		
#endif
#ifdef FILTER9
  EE_ecan_SetFilter(ECAN1,9,FILTER9MODE,(EE_UINT32)FILTER9);
  C1BUFPNT3bits.F9BP = 0x07;		
#endif
#ifdef FILTER10
  EE_ecan_SetFilter(ECAN1,10,FILTER10MODE,(EE_UINT32)FILTER10);
  C1BUFPNT3bits.F10BP = 0x07;		
#endif
#ifdef FILTER11
  EE_ecan_SetFilter(ECAN1,11,FILTER11MODE,(EE_UINT32)FILTER11);
  C1BUFPN3bits.F11BP = 0x07;		
#endif
#ifdef FILTER12
  EE_ecan_SetFilter(ECAN1,12,FILTER12MODE,(EE_UINT32)FILTER12);
  C1BUFPNT4bits.F12BP = 0x07;		
#endif
#ifdef FILTER13
  EE_ecan_SetFilter(ECAN1,13,FILTER13MODE,(EE_UINT32)FILTER13);
  C1BUFPNT4bits.F13BP = 0x07;		
#endif
#ifdef FILTER14
  EE_ecan_SetFilter(ECAN1,14,FILTER14MODE,(EE_UINT32)FILTER14);
  C1BUFPNT4bits.F14BP = 0x07;		
#endif
#ifdef FILTER15
  EE_ecan_SetFilter(ECAN1,15,FILTER15MODE,(EE_UINT32)FILTER15);
  C1BUFPNT4bits.F15BP = 0x07;		
#endif
		                          
    
	
  C1CTRL1bits.WIN = 0;
  C1CTRL2 = 7;
  /* FIFO starts from TX/RX buffer 31 */
  C1FEN1 = 0;
	
	
#ifdef FILTER0
  C1FEN1bits.FLTEN0 = 1;
  C1FMSKSEL1bits.F0MSK = FILTER0MASK; 	
#endif
	
#ifdef FILTER1
  C1FEN1bits.FLTEN1 = 1;
  C1FMSKSEL1bits.F1MSK = FILTER1MASK; 
			
#endif
	
#ifdef FILTER2
  C1FEN1bits.FLTEN2 = 1;
  C1FMSKSEL1bits.F2MSK = FILTER2MASK; 
		
#endif
	
#ifdef FILTER3
  C1FEN1bits.FLTEN3 = 1;
  C1FMSKSEL1bits.F3MSK = FILTER3MASK;
#endif
	
#ifdef FILTER4
  C1FEN1bits.FLTEN4 = 1;
  C1FMSKSEL1bits.F4MSK = FILTER4MASK; 
		
#endif
	
#ifdef FILTER5
  C1FEN1bits.FLTEN5 = 1;
  C1FMSKSEL1bits.F5MSK = FILTER5MASK; 
			
#endif
#ifdef FILTER6
  C1FEN1bits.FLTEN6 = 1;
  C1FMSKSEL1bits.F6MSK = FILTER6MASK; 
			
#endif
	
#ifdef FILTER7
  C1FEN1bits.FLTEN7 = 1;
  C1FMSKSEL1bits.F7MSK = FILTER7MASK; 
	
#endif
	
#ifdef FILTER8
  C1FEN1bits.FLTEN8 = 1;
  C1FMSKSEL1bits.F8MSK = FILTER8MASK; 
			
#endif
#ifdef FILTER9
  C1FEN1bits.FLTEN9 = 1;
  C1FMSKSEL1bits.F9MSK = FILTER9MASK; 
#endif
#ifdef FILTER10
  C1FEN1bits.FLTEN10 = 1;
  C1FMSKSEL1bits.F10MSK = FILTER10MASK; 
			
#endif
#ifdef FILTER11
  C1FEN1bits.FLTEN11 = 1;
  C1FMSKSEL1bits.F11MSK = FILTER11MASK; 
			
#endif
#ifdef FILTER12
  C1FEN1bits.FLTEN12 = 1;
  C1FMSKSEL1bits.F12MSK = FILTER12MASK; 
			
#endif
#ifdef FILTER13
  C1FEN1bits.FLTEN13 = 1;
  C1FMSKSEL1bits.F13MSK = FILTER13MASK; 
			
#endif
#ifdef FILTER14
  C1FEN1bits.FLTEN14 = 1;
  C1FMSKSEL1bits.F14MSK = FILTER14MASK; 
			
#endif
#ifdef FILTER15
  C1FEN1bits.FLTEN15 = 1;
  C1FMSKSEL1bits.F15MSK = FILTER15MASK; 
			
#endif
	
	
	
	
	
  C1TR01CONbits.TXEN0 = USE_AS_TRANSMIT;          /* buffer0 is a transmit buffer */
  C1TR01CONbits.TXEN1 = USE_AS_TRANSMIT;          /* buffer1 is a transmit buffer */
  C1TR23CONbits.TXEN2 = 0;		                /* buffer2 is a receive buffer  */
  C1TR23CONbits.TXEN3 = 0;		                /* buffer3 is a receive buffer  */
  C1TR45CONbits.TXEN4 = 0;		                /* buffer4 is a receive buffer  */
  C1TR45CONbits.TXEN5 = 0;		                /* buffer5 is a receive buffer  */
  C1TR67CONbits.TXEN6 = 0;		                /* buffer6 is a receive buffer  */
  C1TR67CONbits.TXEN7 = 0;		                /* buffer7 is a receive buffer  */
	
  //C1TR01CONbits.TX0PRI = 3;	                    /* priority	for buffer0 is high */
  //C1TR01CONbits.TX1PRI = 2; 	                    /* priority	for buffer1 is medium */
	
  C1CTRL2 = 0;                                    /* reset DeviceNet support */
  	
  C1CTRL1bits.REQOP = 0;                          /* request normal operation mode */
  while(C1CTRL1bits.OPMODE != 0);                 /* wait until switched back */
	
  RxCan1IsrFunction=RxCanFunctionCallBack;        //Settings callback function
  ////delay = C1CTRL2;
	
}

__INLINE__ void __ALWAYS_INLINE__ EE_Ecan1_TxInit(void)
{
  C1CTRL1bits.REQOP = 0x04;
  while(C1CTRL1bits.OPMODE != 0x04);              /* wait until module switched over to configuration mode */ 
		
  C1TR01CONbits.TXEN0 = USE_AS_TRANSMIT;          /* buffer0 is a transmit buffer */
  C1TR01CONbits.TXEN1 = USE_AS_TRANSMIT;          /* buffer1 is a transmit buffer */
  C1TR01CONbits.TX0PRI = 3;	                    /* priority	for buffer0 is high */
  C1TR01CONbits.TX1PRI = 2; 	                    /* priority	for buffer1 is medium */
		
  C1CTRL1bits.REQOP = 0;                          /* request normal operation mode */
  while(C1CTRL1bits.OPMODE != 0);                 /* wait until switched back */
}

#endif //__USE_CAN1__


/* ************************************************************************* */





#endif
