///* ###*B*###
// * ERIKA Enterprise - a tiny RTOS for small microcontrollers
// *
// * Copyright (C) 2002-2008  Evidence Srl
// *
// * This file is part of ERIKA Enterprise.
// *
// * ERIKA Enterprise is free software; you can redistribute it
// * and/or modify it under the terms of the GNU General Public License
// * version 2 as published by the Free Software Foundation, 
// * (with a special exception described below).
// *
// * Linking this code statically or dynamically with other modules is
// * making a combined work based on this code.  Thus, the terms and
// * conditions of the GNU General Public License cover the whole
// * combination.
// *
// * As a special exception, the copyright holders of this library give you
// * permission to link this code with independent modules to produce an
// * executable, regardless of the license terms of these independent
// * modules, and to copy and distribute the resulting executable under
// * terms of your choice, provided that you also meet, for each linked
// * independent module, the terms and conditions of the license of that
// * module.  An independent module is a module which is not derived from
// * or based on this library.  If you modify this code, you may extend
// * this exception to your version of the code, but you are not
// * obligated to do so.  If you do not wish to do so, delete this
// * exception statement from your version.
// *
// * ERIKA Enterprise is distributed in the hope that it will be
// * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// * GNU General Public License version 2 for more details.
// *
// * You should have received a copy of the GNU General Public License
// * version 2 along with ERIKA Enterprise; if not, write to the
// * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
// * Boston, MA 02110-1301 USA.
// * ###*E*### */
//
///*
// * Author: Dario Di Stefano
// */
//
///* This file MUST contain only #defines, because it is also included
//   by the .S files */
//
///*
// * Compiler dependent interface
// */

#ifndef EE_CPU_COMPILER_H
#define EE_CPU_COMPILER_H
  
///*************************************************************************
// HAL Types
// *************************************************************************/

typedef unsigned char EE_BIT;
typedef unsigned char EE_UINT8;
typedef unsigned int EE_UINT16;
typedef unsigned long EE_UINT32;
typedef signed char EE_INT8;
typedef signed int EE_INT16;
typedef signed long EE_INT32;

typedef EE_UINT16 EE_UREG;
typedef EE_INT16  EE_SREG;
typedef EE_UINT16 EE_FREG;

// Thread IDs
typedef EE_UINT32 EE_TID;

// Addresses (that have the same size of a pointer)
typedef @far void *EE_ADDR;		// N.B. 16-bit for @near pointer and 32-bit for @far pointer
typedef EE_UINT16 *EE_DADD;		// N.B. for data pointer you can use only 16 bit 
#define EE_FADDR EE_ADDR
/* Callbacks with no parameters nor return value */
typedef @far void (*EE_VOID_CALLBACK)(void);

#ifndef NULL     // invalid pointer
#define NULL 0 
#endif

#ifdef __CODEWARRIOR__
 #ifdef __EMBEDDED_CPP_SUPPORT__
  #define INLINE_KEYWORD inline
 #else
  #define INLINE_KEYWORD
 #endif
#else // CODEWARRIOR
 #define INLINE_KEYWORD @inline
#endif

#ifdef __NO_INLINE__
 #define __INLINE__ static
#else
 #define __INLINE__ static INLINE_KEYWORD
#endif

#define __ALWAYS_INLINE__ 

#define NORETURN  //__attribute__ ((noreturn))


#ifdef __CODEWARRIOR__

// save CCR register (I bit)
 __INLINE__ EE_FREG __ALWAYS_INLINE__ EE_READ_CCR()
 {
     EE_FREG rvar;
     __asm tfr ccr,b;
     __asm std rvar;
     return rvar;
 }
 
 // save the stack pointer
 __INLINE__ EE_DADD __ALWAYS_INLINE__ EE_READ_SP()
 {
     EE_DADD tos;
     __asm tfr SP,d;
     __asm addd #5;
     __asm std tos;
     return tos;
 }
 
 // change the stack pointer
 #define EE_WRITE_SP(tos) __asm ldd tos; __asm tfr d,SP;
 
 // write CCRH register
 #define EE_WRITE_CCRH(rvar)    do {\
  EE_UINT16 var = rvar;\
  __asm ldd var; __asm tfr a,CCRH;\
  }while(0)
  
 // Macro for interrupts disabling
 #define ASM_DIS_INT __asm sei
  
 // Macro for interrupts enabling  
 #define ASM_EN_INT  __asm cli

#else // COSMIC

 #define EE_READ_CCR()      _asm("tfr ccr,b\n")                  // save CCR register (I bit)
 #define EE_READ_SP()       (EE_DADD)(_asm("tfr  s, d"))         // save the stack pointer
 #define EE_WRITE_SP(var)   _asm("tfr d, s", var)                // change the stack pointer
 #define EE_WRITE_CCRH(var) _asm("tfr a,ccrh\n", var)            // write CCRH register
 #define ASM_DIS_INT        _asm("sei")                          // Macro for interrupts disabling
 #define ASM_EN_INT         _asm("cli")                          // Macro for interrupts enabling  
  
#endif

#endif // EE_CPU_COMPILER_H

