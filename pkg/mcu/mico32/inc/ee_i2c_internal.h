#ifndef __EE_I2C_INTERNAL_H__
#define __EE_I2C_INTERNAL_H__

#ifdef __USE_I2C__

#include <eecfg.h>
#include "mcu/mico32/inc/ee_internal.h"
#include "OpenCoresI2CMaster.h"

/*************************************************************************
 I2C
 *************************************************************************/

/*
	I2C structure:
		
	typedef struct {
		int err;						// last error condition
		int mode;						// i2c operating mode (polling, isr, ...)
		int ir;							// flag to discriminate interrupt source (rx or tx)
    	OCI2CMDev_t* base;				// controller base address
    	int irqf;						// irq flag
    	EE_ISR_callback rxcbk;			// rx callback
    	EE_ISR_callback txcbk;			// tx callback
    	EE_buffer rxbuf;				// rx buffer used in isr mode
    	EE_buffer txbuf;				// tx buffer used in isr mode
	} EE_i2c_st;
*/

typedef struct {
	int err;						
	int txie;						
	int mode;						
	int ir;							
    OCI2CMDev_t* base;				
    int irqf;						
    EE_ISR_callback rxcbk;			
    EE_ISR_callback txcbk;			
    EE_buffer rxbuf;				
    EE_buffer txbuf;				
} EE_i2c_st;

/* Internal functions */
int EE_hal_i2c_config(EE_i2c_st* i2csp, int baudrate, int setttings);									//1
int EE_hal_i2c_set_ISR_mode(EE_i2c_st* i2csp, int mode);												//2
int EE_hal_i2c_set_rx_callback(EE_i2c_st* i2csp, EE_ISR_callback isr_rx_callback);						//3
int EE_hal_i2c_set_tx_callback(EE_i2c_st* i2csp, EE_ISR_callback isr_tx_callback);						//4
int EE_hal_i2c_write_byte(EE_i2c_st* i2csp, int address, char data);									//5
int EE_hal_i2c_read_byte(EE_i2c_st* i2csp, int address, char *adddata);									//6
int EE_hal_i2c_read_buffer(EE_i2c_st* i2csp, int address, char *vet, int len);							//7
int EE_hal_i2c_write_buffer(EE_i2c_st* i2csp, int address, char *vet, int len);							//8
int EE_hal_i2c_enable_IRQ(EE_i2c_st* i2csp);															//9
int EE_hal_i2c_disable_IRQ(EE_i2c_st* i2csp);															//10
int EE_hal_i2c_disable(EE_i2c_st* i2csp);																//11
int EE_hal_i2c_enable(EE_i2c_st* i2csp);																//12
int EE_hal_i2c_start(EE_i2c_st* i2csp);																	//13
int EE_hal_i2c_stop(EE_i2c_st* i2csp);																	//14	
void EE_i2c_common_handler(int level);																	//handler

/* Macro utils */
#define cat3(a, b, c)  a ## b ## c
#define cat2(a, b) a ## b

/* Macro for the structure name generation */
#define EE_I2C_ST_NAME(lc) cat3(ee_, lc, _st)

/* Macro for vectors (buffers) name generation */
#define EE_I2C_VETRX_NAME(lc) cat3(ee_, lc, _isr_rxvet)
#define EE_I2C_VETTX_NAME(lc) cat3(ee_, lc, _isr_txvet)

/* Macro for Structure declaration */
#define DECLARE_STRUCT_I2C(uc, lc) \
  extern EE_i2c_st EE_I2C_ST_NAME(lc);

/* Macro for vectors (buffers) definition */  
#define DEFINE_VET_I2C(uc, lc) \
char EE_I2C_VETRX_NAME(lc)[EE_I2C_BUFSIZE]; \
char EE_I2C_VETTX_NAME(lc)[EE_I2C_BUFSIZE];  

/* Macro for structure definition */
#define DEFINE_STRUCT_I2C(uc, lc) \
EE_i2c_st cat3(ee_, lc, _st) = { \
	.err=EE_I2C_OK, .mode= EE_I2C_POLLING, .base= (OCI2CMDev_t* )cat2(uc, _BASE_ADDRESS),\
	.irqf= cat2(uc, _IRQ), .rxcbk= EE_OCI2CMDev_t_NULL_CBK, .txcbk= EE_OCI2CMDev_t_NULL_CBK,\
	.rxbuf.data= EE_OCI2CMDev_t_VETRX_NAME(lc),.txbuf.data= EE_OCI2CMDev_t_VETTX_NAME(lc)};

/* Macros for User functions (API) */  
#define DECLARE_FUNC_I2C(uc, lc) \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _config)(int baudrate,int settings){ \
	return EE_hal_i2c_config(& EE_I2C_ST_NAME(lc), baudrate, settings); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _set_ISR_mode)(int mode){ \
	return EE_hal_i2c_set_ISR_mode(& EE_I2C_ST_NAME(lc), mode); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _set_rx_callback)(EE_ISR_callback rxcbk){ \
	return EE_hal_i2c_set_rx_callback(& EE_I2C_ST_NAME(lc), rxcbk); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _set_tx_callback)(EE_ISR_callback txcbk){ \
	return EE_hal_i2c_set_tx_callback(& EE_I2C_ST_NAME(lc), txcbk); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _write_byte)(int address, char data){ \
	return EE_hal_i2c_write_byte(& EE_I2C_ST_NAME(lc), address, data); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _read_byte)(int address, char *adddata){ \
	return EE_hal_i2c_read_byte(& EE_I2C_ST_NAME(lc), address, adddata); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _write_buffer)(int address, char *vet, int len){ \
	return EE_hal_i2c_write_buffer(& EE_I2C_ST_NAME(lc), address, vet, len); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _read_buffer)(int address, char *vet, int len){ \
	return EE_hal_i2c_read_buffer(& EE_I2C_ST_NAME(lc), address, vet, len); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _enable_IRQ)(void){ \
	return EE_hal_i2c_enable_IRQ(& EE_I2C_ST_NAME(lc)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _disable_IRQ)(void){ \
	return EE_hal_i2c_disable_IRQ(& EE_I2C_ST_NAME(lc)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _disable)(void){ \
	return EE_hal_i2c_disable(& EE_I2C_ST_NAME(lc)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _enable)(void){ \
	return EE_hal_i2c_enable(& EE_I2C_ST_NAME(lc)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _stop)(void){ \
	return EE_hal_i2c_stop(& EE_I2C_ST_NAME(lc)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _start)(void){ \
	return EE_hal_i2c_start(& EE_I2C_ST_NAME(lc)); }

/* User functions (API): */  
#ifdef EE_I2C1_NAME_UC
DECLARE_STRUCT_I2C(EE_I2C1_NAME_UC, EE_I2C1_NAME_LC)
DECLARE_FUNC_I2C(EE_I2C1_NAME_UC, EE_I2C1_NAME_LC)
#endif	

#ifdef EE_I2C2_NAME_UC
DECLARE_STRUCT_I2C(EE_I2C2_NAME_UC, EE_I2C2_NAME_LC)
DECLARE_FUNC_I2C(EE_I2C2_NAME_UC, EE_I2C2_NAME_LC)
#endif	

/* Return the I2C structure for the componente associated with the given IRQ
 * level */
__DECLARE_INLINE__ EE_i2c_st *EE_get_i2c_st_from_level(int level);


#ifndef EE_I2C_NAME2_UC
/* If there is only one component of this kind, no test is done */
__INLINE__ EE_i2c_st * __ALWAYS_INLINE__ EE_get_i2c_st_from_level(int level)
{
    return & EE_I2C_ST_NAME(EE_I2C_NAME1_LC);
}
#else /* #ifndef EE_I2C_NAME2_UC */
__INLINE__ EE_i2c_st * __ALWAYS_INLINE__ EE_get_i2c_st_from_level(int level)
{
    if (level == EE_I2C_IRQ_NAME(EE_I2C_NAME1_UC))
        return & EE_I2C_ST_NAME(EE_I2C_NAME1_LC);
    else
        return & EE_I2C_ST_NAME(EE_I2C_NAME2_LC);
}
#endif /* #ifndef EE_I2C_NAME2_UC */

#endif // #ifdef __USE_I2C__

#endif //__EE_I2C_INTERNAL_H__
