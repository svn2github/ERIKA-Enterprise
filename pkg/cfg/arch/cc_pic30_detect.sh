#!/bin/bash

# This script is used to print out information about the positioning of the
# Microchip PIC30 compiler, to avoid that the compilation will fail due to
# a wrongly specified compiler installation directory

# usage:
# cc_pic30_detect.sh ASM dirname
# cc_pic30_detect.sh GCC dirname

if test -d "$2"; then
    cygpath `cygpath -ms "$2"`
    exit
fi

if [ $1 = "ASM" ]; then
    printf "Looking for the MPLAB ASM30 directory...\n" 1>&2

    if test -d "${PROGRAMFILES}\Microchip\MPLAB ASM30 Suite"; then
	printf "...Using ${PROGRAMFILES}\\Microchip\\MPLAB ASM30 Suite\n" 1>&2
	cygpath `cygpath -ms "${PROGRAMFILES}\Microchip\MPLAB ASM30 Suite"`
	exit
    fi

    if test -d "c:\Program Files\Microchip\MPLAB ASM30 Suite"; then
	printf "...Using c:\\Program Files\\Microchip\\MPLAB ASM30 Suite\n" 1>&2
	cygpath `cygpath -ms "c:\Program Files\Microchip\MPLAB ASM30 Suite"`
	exit
    fi

    if test -d "c:\Programmi\Microchip\MPLAB ASM30 Suite"; then
	printf "...Using c:\\Programmi\\Microchip\\MPLAB ASM30 Suite\n" 1>&2
	cygpath `cygpath -ms "c:\Programmi\Microchip\MPLAB ASM30 Suite"`
	exit
    fi

fi

if [ $1 = "GCC" ]; then
    printf "Looking for the MPLAB C30 directory...\n" 1>&2

    if test -d "${PROGRAMFILES}\Microchip\MPLAB C30 Suite"; then
	printf "...Using ${PROGRAMFILES}\\Microchip\\MPLAB C30 Suite\n" 1>&2
	cygpath `cygpath -ms "${PROGRAMFILES}\Microchip\MPLAB C30 Suite"`
	exit
    fi

    if test -d "${PROGRAMFILES}\Microchip\mplabc30\v3.25"; then
	printf "...Using ${PROGRAMFILES}\\Microchip\\mplabc30\\v3.25\n" 1>&2
	cygpath `cygpath -ms "${PROGRAMFILES}\Microchip\mplabc30\v3.25"`
	exit
    fi

    if test -d "${PROGRAMFILES}\Microchip\mplabc30\v3.30"; then
	printf "...Using ${PROGRAMFILES}\\Microchip\\mplabc30\\v3.30\n" 1>&2
	cygpath `cygpath -ms "${PROGRAMFILES}\Microchip\mplabc30\v3.30"`
	exit
    fi

    if test -d "${PROGRAMFILES}\Microchip\mplabc30\v3.31"; then
	printf "...Using ${PROGRAMFILES}\\Microchip\\mplabc30\\v3.31\n" 1>&2
	cygpath `cygpath -ms "${PROGRAMFILES}\Microchip\mplabc30\v3.31"`
	exit
    fi

    if test -d "c:\Program Files\Microchip\MPLAB C30"; then
	printf "...Using c:\\Program Files\\Microchip\\MPLAB C30\n" 1>&2
	cygpath `cygpath -ms "c:\Program Files\Microchip\MPLAB C30"`
	exit
    fi

    if test -d "c:\Programmi\Microchip\MPLAB C30"; then
	printf "...Using c:\\Programmi\\Microchip\\MPLAB C30\n" 1>&2
	cygpath `cygpath -ms "c:\Programmi\Microchip\MPLAB C30"`
	exit
    fi

fi;

