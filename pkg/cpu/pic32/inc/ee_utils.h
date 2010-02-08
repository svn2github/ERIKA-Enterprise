#ifndef __INCLUDE_PIC32_EE_UTILS_H__
#define __INCLUDE_PIC32_EE_UTILS_H__

#include "cpu/pic32/inc/ee_compiler.h"
#include "ee_pic32regs.h"

__INLINE__ void __ALWAYS_INLINE__ EE_system_init(void)
{
	EE_UREG r;

	DDPCONbits.JTAGEN = 0;  // disable JTAG port
        /* chris: TODO: understanding the meaning of this */
        asm volatile("mfc0   %0,$13" : "=r"(r));
        r |= 0x00800000; 	// set the CP0 cause IV bit high
        asm volatile("mtc0   %0,$13" : "+r"(r));
        INTCONSET = _INTCON_MVEC_MASK;
	ASM_EN_INT; 		// Enable IRQ
}

#endif  /* __INCLUDE_PIC32_EE_UTILS_H__ */
