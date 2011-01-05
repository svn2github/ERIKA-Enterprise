/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
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
 * Z7 register mappings.
 * Author: 2010 Fabio Checconi
 */

#ifndef __EE_REGS_H__
#define __EE_REGS_H__

#define SPRG_XER	1
#define SPRG_LR		8
#define SPRG_CTR	9
#define SPRG_SRR0	26
#define SPRG_SRR1	27

#define SPRG_IVOR_BASE	400
#define SPRG_IVPR	63

#define SPRG_DEC	22
#define SPRG_DECAR	54
#define SPRG_TBL_W	284
#define SPRG_TBH_W	285
#define SPRG_TCR	340
#define SPRG_TSR	336

#define SPRG_HID0	1008

#define TCR_DIE		26
#define TCR_ARE		22

#define TSR_DIS		27

#define HID0_TBEN	14

#endif
