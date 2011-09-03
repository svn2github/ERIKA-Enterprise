/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
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
 * Author: 2011  Bernardo  Dal Seno
 *         2010  Fabio Checconi
 */

#include <ee_internal.h>

EE_STACK_T EE_STACK_ATTRIB EE_e200zx_sys_stack[EE_STACK_WLEN(EE_SYS_STACK_SIZE)];


/*
 * MMU setup
 *
 * MMU is normally initialized by BAM.  A different configuration can be
 * programmed with EE_e200zx_mmu_setup().
 */

#ifdef __EE_USE_MMU__

#define MMU_MAS0	624
#define MMU_MAS1	625
#define MMU_MAS2	626
#define MMU_MAS3	627


#ifdef __DCC__

__asm volatile void mmu_write_mas(int mas, unsigned long val)
{
% reg val; con mas;
!
	mtspr	mas, val
}

__asm volatile void mmu_write_sync(void)
{
!
	tlbwe
	msync
}

#else /* if __DCC__ */

#define mmu_write_mas(mas, val) asm volatile ("mtspr	(" \
	EE_PREPROC_STRING(mas) "), %0" : : "r"(val))

__INLINE__ void __ALWAYS_INLINE__ mmu_write_sync(void)
{
	asm volatile ("tlbwe	\n\t"
		"msync");
}

#endif /* else if __DCC__ */


void EE_e200zx_mmu_setup(const EE_MMU_ENTRY_T *entries, unsigned count)
{
	unsigned i;

	for (i = 0U; i < count; i++) {
		mmu_write_mas(MMU_MAS0, EE_E200ZX_MMU_TLBSEL1 | (i << 16));
		mmu_write_mas(MMU_MAS1, entries[i].mas1);
		mmu_write_mas(MMU_MAS2, entries[i].mas2);
		mmu_write_mas(MMU_MAS3, entries[i].mas3);
		mmu_write_sync();
	}
}

#endif /* __EE_USE_MMU__ */
