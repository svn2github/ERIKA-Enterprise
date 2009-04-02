# This is the makefile-included file that contains the specifications
# of all the binary images that have to be created for a given
# distribution

# here is a template for all the entries of this file

# DISTRIBUTION_NAME = LIBCONFi ...
# DISTRIBUTION_NAME_varname = value
# LIBCONFi = __EEOPT_OPTj__ ...


# -------------------------------------------------------------------

# this variable is used in the "help" rule
ALL_DISTRIBUTIONS += MPC5
ALL_DISTRIBUTIONS += COBRA_ICD30_ALL
ALL_DISTRIBUTIONS += NIOS2_ALL NIOS2_TEST NIOS2_FROMBINDIST

#ALL_DISTRIBUTIONS += E7T_ALL E7T_TESTCASE
#ALL_DISTRIBUTIONS += PIC30_ALL PIC30_TESTCASE
#ALL_DISTRIBUTIONS += AVR5_ALL AVR5_TESTCASE
ALL_DISTRIBUTIONS += EEFLEX EE3ARCH EE3ARCHD


# -------------------------------------------------------------------
# -------------------------------------------------------------------
# -------------------------------------------------------------------
# -------------------------------------------------------------------

# Nios2 distributions

NIOS2_ALL = NIOS2_ALL_FP NIOS2_ALL_OO NIOS2_ALL_EXAMP NIOS2_ALL_TESTCASE

NIOS2_ALL_FP = __NIOS2__ __FP__ __ALLOW_NESTED_IRQ__ __MONO__ __RN__ __MSRP__ __ALARMS__ __SEM__
NIOS2_ALL_OO = __NIOS2__ __OO_BCC1__ __ALLOW_NESTED_IRQ__ __MONO__ __RN__ __MSRP__
NIOS2_ALL_EXAMP = __NIOS2_EXAMPLES__
NIOS2_ALL_TESTCASE = __ASSERT__


NIOS2_TEST = $(NIOS2_ALL) NIOS2_TEST_FRSH

NIOS2_TEST_FRSH = __NIOS2__ __FRSH__ __ALLOW_NESTED_IRQ__ __MONO__ __RN__ __MSRP__


# this is called hardcoded by the binary distribution scripts when
# generating a binary distribution for NIOS2. This is needed because
# the scripts for NIOS2 must stay into the nios2 directory, so the
# binary distribution generator first generates a source distribution
# that then is used to compile the binary distribution

NIOS2_FROMBINDIST = NIOS2_FROMBINDIST_THEDIST

NIOS2_FROMBINDIST_THEDIST = __NIOS2__ __OO_BCC1__ __ALLOW_NESTED_IRQ__ __MONO__ __RN__ __MSRP__ __ASSERT__

# -------------------------------------------------------------------
# -------------------------------------------------------------------
# -------------------------------------------------------------------
# -------------------------------------------------------------------

MPC5 = MPC5_SOURCE

MPC5_SOURCE = __FP__ __MPC566EVB__ __MPC5XX__

# -------------------------------------------------------------------
# -------------------------------------------------------------------

# Cobra Automotive Spa
# source code distribution for the STA2051 Vespucci

COBRA_ICD30_ALL = COBRA_ICD30_ALL_OO

COBRA_ICD30_ALL_OO = __ARM7GNU__ __ST_STA2051__ __COBRA_ICD30__ __OO_BCC1__ __FP__



# -------------------------------------------------------------------
# -------------------------------------------------------------------

E7T_ALL = E7T_ALL_OO

E7T_ALL_OO = __OO_BCC1__ __FP__ __EVALUATOR7T__ __SAMSUNG_KS32C50100__ __ARM7GNU__

# -------------------------------------------------------------------

E7T_TESTCASE = E7T_TESTCASE_OO

E7T_TESTCASE_OO = __OO_BCC1__ __ASSERT__ __EVALUATOR7T__ __SAMSUNG_KS32C50100__ __ARM7GNU__

# -------------------------------------------------------------------

# same as E7T_ALL!!!
E7T_FROMBINDIST = E7T_ALL_OO

# -------------------------------------------------------------------
# -------------------------------------------------------------------

AVR5_EE = AVR5_EE_OO

AVR5_EE_OO = __AVR5__ __OO_BCC1__ __FP__

# -------------------------------------------------------------------

AVR5_TESTCASE = AVR5_TESTCASE_OO

AVR5_TESTCASE_OO = __AVR5__ __OO_BCC1__ __ASSERT__

# -------------------------------------------------------------------

# same as AVR5_ALL!!!
AVR5_FROMBINDIST = AVR5_ALL_OO


# -------------------------------------------------------------------
# -------------------------------------------------------------------

PIC30_EE = PIC30_EE_OO

PIC30_EE_OO = __PIC30__ __OO_BCC1__ __FP__

# -------------------------------------------------------------------

PIC30_TESTCASE = PIC30_TESTCASE_OO

PIC30_TESTCASE_OO = __PIC30__ __OO_BCC1__ __ASSERT__

# -------------------------------------------------------------------

# same as PIC30_ALL!!!
PIC30_FROMBINDIST = PIC30_ALL_OO


# -------------------------------------------------------------------
# -------------------------------------------------------------------

# EE versions

EE_KERNEL = __FP__ __EDF__ __OO_BCC1__ __ALARMS__ __SEM__

EE_LIBS = __LIB_IEEE802154__


EE_PIC30 = __PIC30__ __PIC30_EXAMPLES__

EE_AVR5 = __AVR5__ __AVR5_EXAMPLES__

EE_ARM7 = __ARM7GNU__ __SAMSUNG_KS32C50100__ __EVALUATOR7T__

EE_ARM7_DEV = __ARM7GNU__ __SAMSUNG_KS32C50100__ __EVALUATOR7T__ __unibo_mparm__


EEFLEX = EE_KERNEL EE_LIBS EE_PIC30

EE3ARCH = EE_KERNEL EE_LIBS EE_PIC30 EE_AVR5 EE_ARM7

EE3ARCHD = EE_KERNEL EE_LIBS EE_PIC30 EE_AVR5 EE_ARM7_DEV

# -------------------------------------------------------------------
# OLD, to be removed!
# -------------------------------------------------------------------

# EE, for the commercial distribution
#EE = EE_ALL EE_OPENZB
#EE_ALL = __PIC30__ __FP__ __EDF__ __PIC30_EXAMPLES__ __OO_BCC1__  __FRSH__ __SEM_FRSH__ __ALARMS__ __SEM__
#EE_OPENZB = __LIB_IEEE802154__
#EE_ALL = __AVR5__ __PIC30__ __FP__ __EDF__ __AVR5_EXAMPLES__ __PIC30_EXAMPLES__ __OO_BCC1__  __ALARMS__ __SEM__

# EE FLEX, for the Flex CDROM
#EEFLEX = EEFLEX_ALL
#EEFLEX_ALL = __PIC30__ __FP__ __OO_BCC1__ __EDF__ __PIC30_EXAMPLES__ __ALARMS__ __SEM__ __LIB_IEEE802154__
# EE AVR5, by now, for downloading
#EEAVR5 = EEAVR5_ALL
#EEAVR5_ALL = __AVR5__ __FP__ __EDF__ __AVR5_EXAMPLES__ __ALARMS__ __SEM__
