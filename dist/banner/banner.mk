# banner.mk
# ---------

# this file is included by the makefile of the binary distributions

# This file specifies the banners that have to be used for particulars extensions

# Include direcory list with licenses
include ../banner/dirs.mk

# Altera Demo
ALL_BANNERS += ALTERA_DEMO
ALTERA_DEMO.h = altera_demo_c.txt
ALTERA_DEMO.c = altera_demo_c.txt
ALTERA_DEMO.S = altera_demo_c.txt
ALTERA_DEMO.mk = altera_demo_mk.txt
ALTERA_DEMO.oil = altera_demo_c.txt

# Altera Full
ALL_BANNERS += ALTERA_FULL
ALTERA_FULL.h = altera_full_c.txt
ALTERA_FULL.c = altera_full_c.txt
ALTERA_FULL.S = altera_full_c.txt
ALTERA_FULL.mk = altera_full_mk.txt
ALTERA_FULL.oil = altera_full_c.txt

# PIC30 University
ALL_BANNERS += PIC30_UNIV
PIC30_UNIV.h = pic30_university_full_c.txt
PIC30_UNIV.c = pic30_university_full_c.txt
PIC30_UNIV.S = pic30_university_full_c.txt
PIC30_UNIV.mk = pic30_university_full_mk.txt
PIC30_UNIV.oil = pic30_university_full_c.txt

# PIC30 Demo
ALL_BANNERS += PIC30_DEMO
PIC30_DEMO.h = pic30_demo_c.txt
PIC30_DEMO.c = pic30_demo_c.txt
PIC30_DEMO.S = pic30_demo_c.txt
PIC30_DEMO.mk = pic30_demo_mk.txt
PIC30_DEMO.oil = pic30_demo_c.txt

# AVR5 University
ALL_BANNERS += AVR5_UNIV
AVR5_UNIV.h = avr5_university_full_c.txt
AVR5_UNIV.c = avr5_university_full_c.txt
AVR5_UNIV.S = avr5_university_full_c.txt
AVR5_UNIV.mk = avr5_university_full_mk.txt
AVR5_UNIV.oil = avr5_university_full_c.txt

# AVR5 Demo
ALL_BANNERS += AVR5_DEMO
AVR5_DEMO.h = avr5_demo_c.txt
AVR5_DEMO.c = avr5_demo_c.txt
AVR5_DEMO.S = avr5_demo_c.txt
AVR5_DEMO.mk = avr5_demo_mk.txt
AVR5_DEMO.oil = avr5_demo_c.txt


# EE Basic
ALL_BANNERS += EEBASIC
EEBASIC.h = gpl_eebasic_c.txt
EEBASIC.c = gpl_eebasic_c.txt
EEBASIC.S = gpl_eebasic_c.txt
EEBASIC.mk = gpl_eebasic_mk.txt
EEBASIC.oil = gpl_eebasic_c.txt

# EE
ALL_BANNERS += EECOMMERCIAL
EECOMMERCIAL.h = commercial_ee_c.txt
EECOMMERCIAL.c = commercial_ee_c.txt
EECOMMERCIAL.S = commercial_ee_c.txt
EECOMMERCIAL.mk = commercial_ee_mk.txt
EECOMMERCIAL.oil = commercial_ee_c.txt

# EE GPL
ALL_BANNERS += EEGPL
EEGPL.h = gpl_eebasic_c.txt
EEGPL.c = gpl_eebasic_c.txt
EEGPL.S = gpl_eebasic_c.txt
EEGPL.mk = gpl_eebasic_mk.txt
EEGPL.oil = gpl_eebasic_c.txt

# EE GPL with linking exception
ALL_BANNERS += EEGPLEXC
EEGPLEXC.h = gplexc_c.txt
EEGPLEXC.c = gplexc_c.txt
EEGPLEXC.S = gplexc_c.txt
EEGPLEXC.mk = gplexc_mk.txt
EEGPLEXC.oil = gplexc_c.txt

# Scilab/Scicos codegen
ALL_BANNERS += SCILAB_CODEGEN
SCILAB_CODEGEN.h = scilab_codegen_c.txt
SCILAB_CODEGEN.c = scilab_codegen_c.txt
SCILAB_CODEGEN.S = scilab_codegen_c.txt
SCILAB_CODEGEN.mk = scilab_codegen_mk.txt
SCILAB_CODEGEN.oil = scilab_codegen_c.txt

