#include "mcu/microchip_pic32/inc/ee_oc.h"
#include "mcu/microchip_pic32/inc/ee_timer.h"
/* Include a file with the registers from Microchip C32 distribution */
#ifdef __PIC32_INCLUDE_REGS__
#include "ee_pic32regs.h"
#endif


#ifdef __USE_EE_OC_1__
__INLINE__ void __ALWAYS_INLINE__ oc1_init(void)
{
	TRISDbits.TRISD0 = 0;
	IEC0bits.OC1IE = 0;
	IFS0bits.OC1IF = 0;						
	OC1CON = 0x00;			
}


__INLINE__ EE_INT8 __ALWAYS_INLINE__ oc1_setup(EE_UINT16 configuration, 
				    	    EE_UINT16 period, EE_UINT8 prescale)
{
	OC1CON = (EE_UREG)configuration;
	T2CONbits.T32 = 0;

	if(configuration && EE_OC_TIMER_3){
		
		if(configuration & EE_OC_TIMER_32_BITS)
			return -EE_OC_ERR_BAD_TIMER_CONF;
		
		if(EE_timer_hard_init(EE_TIMER_3, period, prescale) != 
		   				EE_TIMER_NO_ERRORS)		
			return -EE_OC_ERR_TIMER_INIT;
					
		return EE_TIMER_NO_ERRORS;
	}else{
		if(configuration && EE_OC_TIMER_32_BITS)
			return -EE_OC_ERR_UNIMPLEMENTED; 
		return -EE_OC_ERR_UNIMPLEMENTED;
	}			
}

__INLINE__ EE_INT8 __ALWAYS_INLINE__ oc1_advanced_setup(EE_UINT32 dreg, 
						EE_UINT32 sdreg, EE_UINT8 mode)
{
	//TODO: gestire il parametro mode.
	OC1R  = (EE_UREG)dreg;	
	OC1RS = (EE_UREG)sdreg;
	
	return EE_OC_NO_ERRORS;		
}

__INLINE__ void __ALWAYS_INLINE__ oc1_start(void)
{
	EE_timer_start(EE_TIMER_3);	
	OC1CONbits.ON = 1;	
}

__INLINE__ void __ALWAYS_INLINE__ oc1_stop(void)
{
	OC1CONbits.ON = 0;
	EE_timer_stop(EE_TIMER_3);	
		
}
#endif 

EE_INT8 EE_oc_init(EE_UINT8 id)
{
#ifdef __USE_EE_OC_1__
	oc1_init();
#else	
	switch (id) {
	case EE_OC_1 :
		oc1_init();
		break;
	case EE_OC_2 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	case EE_OC_3 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	case EE_OC_4 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	case EE_OC_5 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	case EE_OC_N :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	default:
		return -EE_TIMER_ERR_BAD_TIMER_ID;
		break;
	}
#endif 
	return EE_TIMER_NO_ERRORS;
}

EE_INT8 EE_oc_setup(EE_UINT8 id, EE_UINT16 configuration, EE_UINT16 period, 
							      EE_UINT8 prescale)
{
#ifdef __USE_EE_OC_1__
	return oc1_setup(configuration, period, prescale);
#else
	switch (id) {
	case EE_OC_1 :
		return oc1_setup(configuration, period, prescale);
		break;
	
	case EE_OC_2 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	case EE_OC_3 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	case EE_OC_4 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	case EE_OC_5 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	case EE_OC_N :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	default:
		return -EE_TIMER_ERR_BAD_TIMER_ID;
		break;
	}
#endif
	return EE_TIMER_NO_ERRORS;
}

EE_INT8 EE_oc_set_callback(EE_UINT8 id, void (*f)(void))
{
	return -EE_OC_ERR_UNIMPLEMENTED;
}

EE_INT8 EE_oc_advanced_setup(EE_UINT8 id, EE_UINT32 dreg, EE_UINT32 sdreg, 
								EE_UINT8 mode)
{
#ifdef __USE_EE_OC_1__
	return oc1_advanced_setup(dreg, sdreg, mode);
#else
	switch (id) {
	case EE_OC_1 :
		return oc1_advanced_setup(dreg, sdreg, mode);
		break;
	
	case EE_OC_2 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	case EE_OC_3 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	case EE_OC_4 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	case EE_OC_5 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	case EE_OC_N :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	default:
		return -EE_TIMER_ERR_BAD_TIMER_ID;
		break;
	}
#endif
	return EE_TIMER_NO_ERRORS;
}

EE_INT8 EE_oc_start(EE_UINT8 id)
{	

#ifdef __USE_EE_OC_1__
	oc1_start();
#else
	switch (id) {
	case EE_OC_1 :
		oc1_start();
		break;
	case EE_OC_2 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	case EE_OC_3 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	case EE_OC_4 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	case EE_OC_5 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	case EE_OC_N :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	default:
		return -EE_TIMER_ERR_BAD_TIMER_ID;
		break;
	}
#endif
	return EE_TIMER_NO_ERRORS;
}

EE_INT8 EE_oc_stop(EE_UINT8 id)
{
#ifdef __USE_EE_OC_1__
	oc1_stop();
#else
	switch (id) {
	case EE_OC_1 :
		oc1_stop();
		break;
	case EE_OC_2 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	case EE_OC_3 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	case EE_OC_4 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	case EE_OC_5 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	case EE_OC_N :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	default:
		return -EE_TIMER_ERR_BAD_TIMER_ID;
		break;
	}
#endif 
	return EE_TIMER_NO_ERRORS;
}

