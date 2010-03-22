/*
* ee_spi.h
*/

#ifndef __INCLUDE_EEMCUMICO32_SPI_H__
#define __INCLUDE_EEMCUMICO32_SPI_H__

#ifdef __USE_SPI__

#include "mcu/mico32/inc/ee_spi_internal.h"

///****************************
//	 * SPI Register Structure
//	 ****************************/
//	typedef struct st_MicoSPI{
//        volatile unsigned int rx;
//        volatile unsigned int tx;
//        volatile unsigned int status;
//        volatile unsigned int control;
//        volatile unsigned int sSelect;
//	}MicoSPI_t;

#endif //#ifdef __USE_SPI__

#endif // __INCLUDE_EEMCUMICO32_SPI_H__


/*************************************************** 
* Notes
****************************************************/
// Interrupt works only byte-by-byte data transfers...
//	The interface defines 3 transmission speeds:
//	- Normal: 100Kbps
//	- Fast: 400Kbps
//	- High speed: 3.5Mbps
//	Only 100Kbps and 400Kbps modes are supported directly. For High speed special IOs
//	are needed. If these IOs are available and used, then High speed is also supported.






//#ifndef MICOSPI_HEADER_FILE_
//#define MICOSPI_HEADER_FILE_
//#include "DDStructs.h"
//
//
//#ifdef __cplusplus
//extern "C"
//{
//#endif /* __cplusplus */
//
///**********************************************************
// * DATA TYPES, MACROS, CONSTANTS etc.                     *
// **********************************************************/
//#define MICOSPI_ERR_SLAVE_DEVICE       (1)
//#define MICOSPI_ERR_WOULD_BLOCK        (2)
//#define MICOSPI_ERR_INVALID_PARAMETER  (3)
//
//typedef void(*MicoSPIDataHandler_t)(void);
//
//
//
///**********************************************************
// * FUNCTIONS                                              *
// **********************************************************/
//    void MicoSPIInit(MicoSPICtx_t *ctx);
//    unsigned int MicoSPISetSlaveEnable(MicoSPICtx_t *ctx, unsigned int mask);
//    unsigned int MicoSPIGetSlaveEnable(MicoSPICtx_t *ctx, unsigned int *pMask);
//	unsigned int MicoSPIIsTxDone(MicoSPICtx_t *ctx);
//    unsigned int MicoSPITxData(MicoSPICtx_t *ctx, unsigned int data, unsigned int bBlock);
//    unsigned int MicoSPIRxData(MicoSPICtx_t *ctx, unsigned int *pData, unsigned int bBlock);
//    unsigned int MicoSPIEnableTxIntr(MicoSPICtx_t *ctx, MicoSPIDataHandler_t handler);
//    void MicoSPIDisableTxIntr(MicoSPICtx_t *ctx);
//    unsigned int MicoSPIEnableRxIntr(MicoSPICtx_t *ctx, MicoSPIDataHandler_t handler);
//    void MicoSPIDisableRxIntr(MicoSPICtx_t *ctx);
//
//
//
//#ifdef __cplusplus
//}
//#endif /* __cplusplus */
//
//
//#endif /* MICOUART_HEADER_FILE_ */
//
