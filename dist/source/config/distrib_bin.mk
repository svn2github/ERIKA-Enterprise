#
# distrib.in: rules to create the include file structure
#

#
# SubMakefile for Step 2 - Creation of the distribution directory


ALLOPTIONS= $(sort $(foreach c, $($(DIST)), $($(c))))
DISTRIB_ALLOPTIONS= $(addprefix distrib_opt_, $(ALLOPTIONS))

.PHONY: $(DISTRIB_ALLOPTIONS) distrib_opt_base

make_distribdir: $(DISTRIB_ALLOPTIONS) distrib_opt_base
	@echo Distribution directories created.

distrib_opt_%:
	@echo ...OPT $* is not linked to any file!

#
# dependencies that create directories
#

# these dependencies are used in step 2 to create the include tree and
# in step 3 to create the lib tree


# here is the main directory, the other dependencies are into dirdep.tmp
ee_$(DIST):
	@echo mkdir ee_$(DIST)
	@if (test ! -e ee_$(DIST)); then mkdir ee_$(DIST); cp -a ../../CVS ee_$(DIST); fi

ee_$(DIST)/lib: ee_$(DIST)
	@echo mkdir ee_$(DIST)/lib
	@if (test ! -e ee_$(DIST)/lib); then mkdir ee_$(DIST)/lib; fi

ifdef DIST
include dirdep.tmp

# to be rewritten in a better way...
dirdep.tmp:
	@echo DIRDEP.TMP
# to remove potential generated dependencies on the directory we are creating for the distribution
	@make --no-print-directory -C . clean DIST=
	find ../.. -type d -printf "%P\n" | grep -v CVS | grep -v svn | gawk '{ sub(/^..\/..\//, ""); print}' | gawk '{ print "ee_$$(DIST)/" $$0 ": \n\tmkdir -p ee_$$(DIST)/" $$0 ";" }' >> dirdep.tmp
#	@for x in `find ../.. -type d -printf "%P\n" | grep -v CVS | gawk '{ sub(/^..\/..\//, ""); print}'` ; do echo $${x} | gawk '{ print "ee_$$(DIST)/" $$0 ": \n\tmkdir -p ee_$$(DIST)/" $$0 ";" }' >> dirdep.tmp; done
#	@for x in `find ../.. -type d -printf "%P\n" | grep -v CVS | grep -v oldexamples | grep -v testcase | gawk '{ sub(/^..\/..\//, ""); print}'` ; do echo $${x} | gawk '{ print "ee_$$(DIST)/" $$0 ": \n\tmkdir -p ee_$$(DIST)/" $$0 ";" }' >> dirdep.tmp; done
endif




# In the case that a symbol is used in more than one architecture
# (e.g., JANUS used both in ARM7GNU and ARM7ADS, do the following: 
#
# - remove the dependencies that depends on ARM7GNU and ARM7ADS, and leave
#   only the common ones in the distrib_opt___JANUS__ inside the makefile
#
# - then, before the line
#   @echo OPT __JANUS__ up2date
#   check if the variable ALLOPTIONS have the ARM7GNU symbol. if yes, do
#   a make -C on a rule that contains the dependency files that are
#   particular for it.
# - Do the same for ARM7ADS.
#
# note that the file listed in these files are nonly useful for the
# binary distributions.  source distributions also include other
# files, listed in ../../source/config/distrib.mk

distrib_opt_base:: \
		ee_$(DIST)/pkg/cfg \
		ee_$(DIST)/pkg/ee.h \
		ee_$(DIST)/pkg/ee_opt.h \
		ee_$(DIST)/pkg/ee_api.h \
		ee_$(DIST)/pkg/cfg/cfg.mk \
		ee_$(DIST)/pkg/cfg/compiler.mk \
		ee_$(DIST)/pkg/cfg/dir.mk \
		ee_$(DIST)/pkg/cfg/rules.mk \
		ee_$(DIST)/pkg/cfg/verbose.mk
	@echo Base files up2date.

#
#
# CPU
#
#


distrib_opt___AVR5__:: \
		ee_$(DIST)/pkg/cfg/arch \
		ee_$(DIST)/pkg/cfg/arch/cc_avr5gnu.mk \
		ee_$(DIST)/pkg/cfg/arch/rules_atmel_stk500.mk \
		ee_$(DIST)/pkg/cfg/arch/rules_xbow_mib5x0.mk \
		ee_$(DIST)/pkg/cfg/arch/rules_xbow_mib510.mk \
		ee_$(DIST)/pkg/cpu/avr5 \
		ee_$(DIST)/pkg/cpu/avr5/inc \
		ee_$(DIST)/pkg/cpu/avr5/inc/ee_compiler.h \
		ee_$(DIST)/pkg/cpu/avr5/inc/ee_cpu.h \
		ee_$(DIST)/pkg/mcu/atmel_atmega128 \
		ee_$(DIST)/pkg/mcu/atmel_atmega128/inc \
		ee_$(DIST)/pkg/mcu/atmel_atmega128/inc/ee_mcu.h \
		ee_$(DIST)/pkg/mcu/atmel_atmega128/inc/ee_mcuregs.h \
		ee_$(DIST)/pkg/mcu/atmel_atmega128/inc/ee_ic.h \
		ee_$(DIST)/pkg/mcu/atmel_atmega128/inc/ee_avr5def.S  \
		ee_$(DIST)/pkg/mcu/atmel_atmega1281 \
		ee_$(DIST)/pkg/mcu/atmel_atmega1281/inc \
		ee_$(DIST)/pkg/mcu/atmel_atmega1281/inc/ee_mcu.h \
		ee_$(DIST)/pkg/mcu/atmel_atmega1281/inc/ee_mcuregs.h \
		ee_$(DIST)/pkg/mcu/atmel_atmega1281/inc/ee_ic.h \
		ee_$(DIST)/pkg/mcu/atmel_atmega1281/inc/ee_avr5def.S  \
		ee_$(DIST)/pkg/board/atmel_stk500/inc \
		ee_$(DIST)/pkg/board/atmel_stk500/inc/ee_board.h \
		ee_$(DIST)/pkg/board/xbow_mib5x0/inc \
		ee_$(DIST)/pkg/board/xbow_mib5x0/inc/ee_board.h 
	@echo OPT __AVR5__ up2date.





distrib_opt___ARM7GNU__:: \
		ee_$(DIST)/pkg/cfg/arch \
		ee_$(DIST)/pkg/cfg/arch/cc_arm7gnu.mk \
		ee_$(DIST)/pkg/cfg/arch/cc_arm7ads.mk \
		ee_$(DIST)/pkg/cfg/arch/rules_arm_evaluator7t.mk \
		ee_$(DIST)/pkg/cpu/arm7tdmi/inc \
		ee_$(DIST)/pkg/cpu/arm7tdmi/inc/ee_arm7defs.h \
		ee_$(DIST)/pkg/cpu/arm7tdmi/inc/ee_compiler.h \
		ee_$(DIST)/pkg/cpu/arm7tdmi/inc/ee_cpu.h
	@echo OPT __ARM7GNU__ up2date.

distrib_opt___NIOS2__:: \
		ee_$(DIST)/pkg/cpu/nios2/bin \
		ee_$(DIST)/pkg/cpu/nios2/bin/mymake_cygwin.bat \
		ee_$(DIST)/pkg/cpu/nios2/build \
		ee_$(DIST)/pkg/cpu/nios2/build/app.mk \
		ee_$(DIST)/pkg/cpu/nios2/build/app_rules.mk \
		ee_$(DIST)/pkg/cpu/nios2/build/chac_rules.mk \
		ee_$(DIST)/pkg/cpu/nios2/build/common.mk \
		ee_$(DIST)/pkg/cpu/nios2/build/ee_common.mk \
		ee_$(DIST)/pkg/cpu/nios2/build/ee_firstcpu.mk \
		ee_$(DIST)/pkg/cpu/nios2/build/ee_global.mk \
		ee_$(DIST)/pkg/cpu/nios2/build/ee_othercpu.mk \
		ee_$(DIST)/pkg/cpu/nios2/build/ee_t32.mk \
		ee_$(DIST)/pkg/cpu/nios2/build/gnu_rules.mk \
		ee_$(DIST)/pkg/cpu/nios2/build/gtf_rules.mk \
		ee_$(DIST)/pkg/cpu/nios2/build/lib.mk \
		ee_$(DIST)/pkg/cpu/nios2/build/lib_rules.mk \
		ee_$(DIST)/pkg/cpu/nios2/build/system.mk \
		ee_$(DIST)/pkg/cpu/nios2/build/system_rules.mk \
		ee_$(DIST)/pkg/cpu/nios2/inc \
		ee_$(DIST)/pkg/cpu/nios2/inc/ee_cpu.h \
		ee_$(DIST)/pkg/cpu/nios2/inc/ee_compiler.h \
		ee_$(DIST)/pkg/cpu/nios2/debug/lauterbach/t32 \
		ee_$(DIST)/pkg/cpu/nios2/debug/lauterbach/t32/debug_nojam.cmm \
		ee_$(DIST)/pkg/cpu/nios2/debug/lauterbach/t32/go.cmm \
		ee_$(DIST)/pkg/cpu/nios2/debug/lauterbach/t32/jam.cmm \
		ee_$(DIST)/pkg/cpu/nios2/debug/lauterbach/t32/load.cmm \
		ee_$(DIST)/pkg/cpu/nios2/debug/lauterbach/t32/windows.cmm \
		ee_$(DIST)/pkg/cpu/nios2/debug/lauterbach/t32/windowsreset.cmm \
		ee_$(DIST)/pkg/mcu/altera_nios2/inc \
		ee_$(DIST)/pkg/mcu/altera_nios2/inc/ee_mcu.h
	@echo OPT __NIOS2__ up2date.

distrib_opt___MPC5XX__:: \
		ee_$(DIST)/pkg/cpu/mpc5xx \
		ee_$(DIST)/pkg/cpu/mpc5xx/inc \
		ee_$(DIST)/pkg/cpu/mpc5xx/inc/ee_compiler.h \
		ee_$(DIST)/pkg/cpu/mpc5xx/inc/ee_cpu.h \
		ee_$(DIST)/pkg/cpu/mpc5xx/inc/ee_opt.h
	@echo OPT __MPC5XX__ up2date.

distrib_opt___PIC30__:: \
		ee_$(DIST)/pkg/cfg/arch \
		ee_$(DIST)/pkg/cfg/arch/cc_pic30.mk \
		ee_$(DIST)/pkg/cfg/arch/rules_microchip_pic30.mk \
		ee_$(DIST)/pkg/cfg/arch/rules_microchip_pic30_mplab_dirs.txt \
		ee_$(DIST)/pkg/cfg/arch/rules_microchip_pic30_mplab_files.txt \
		ee_$(DIST)/pkg/cpu/pic30 \
		ee_$(DIST)/pkg/cpu/pic30/inc \
		ee_$(DIST)/pkg/cpu/pic30/inc/ee_compiler.h \
		ee_$(DIST)/pkg/cpu/pic30/inc/ee_cpu.h \
		ee_$(DIST)/pkg/cpu/pic30/inc/ee_irqstub.h \
		ee_$(DIST)/pkg/mcu/microchip_dspic/inc \
		ee_$(DIST)/pkg/mcu/microchip_dspic/inc/ee_mcu.h \
		ee_$(DIST)/pkg/mcu/microchip_dspic/inc/ee_mcuregs.h \
		ee_$(DIST)/pkg/board/ee_flex/inc \
		ee_$(DIST)/pkg/board/ee_flex/inc/ee_board.h \
		ee_$(DIST)/pkg/board/microchip_explorer16/inc \
		ee_$(DIST)/pkg/board/microchip_explorer16/inc/ee_board.h \
		ee_$(DIST)/pkg/board/microchip_dspicdem11plus/inc \
		ee_$(DIST)/pkg/board/microchip_dspicdem11plus/inc/ee_board.h
	@echo OPT __PIC30__ up2date.

#		ee_$(DIST)/pkg/board/evidence_bee/inc/ee_board.h \
#		ee_$(DIST)/pkg/board/microchip_dspicdem11plus/inc \
#		ee_$(DIST)/pkg/board/microchip_dspicdem11plus/inc/ee_board.h




#
#
# MCU
#
#



distrib_opt___SAMSUNG_KS32C50100__:: \
		ee_$(DIST)/pkg/mcu/samsung_ks32c50100 \
		ee_$(DIST)/pkg/mcu/samsung_ks32c50100/inc \
		ee_$(DIST)/pkg/mcu/samsung_ks32c50100/inc/ee_mcu.h \
		ee_$(DIST)/pkg/mcu/samsung_ks32c50100/inc/ee_mcuregs.h \
		ee_$(DIST)/pkg/mcu/samsung_ks32c50100/inc/ee_ic.h
	@echo OPT __SAMSUNG_KS32C50100__ up2date.


distrib_opt___unibo_mparm__:: \
		ee_$(DIST)/pkg/mcu/unibo_mparm \
		ee_$(DIST)/pkg/mcu/unibo_mparm/inc \
		ee_$(DIST)/pkg/mcu/unibo_mparm/inc/ee_mcu.h \
		ee_$(DIST)/pkg/mcu/unibo_mparm/inc/ee_mcuregs.h \
		ee_$(DIST)/pkg/mcu/unibo_mparm/inc/ee_ic.h
	@echo OPT __unibo_mparm__ up2date.


distrib_opt___ST_STA2051__:: \
		ee_$(DIST)/pkg/mcu/st_sta2051 \
		ee_$(DIST)/pkg/mcu/st_sta2051/inc \
		ee_$(DIST)/pkg/mcu/st_sta2051/inc/ee_mcu.h \
		ee_$(DIST)/pkg/mcu/st_sta2051/inc/ee_mcuregs.h \
		ee_$(DIST)/pkg/mcu/st_sta2051/inc/ee_ic.h
	@echo OPT __ST_STA2051__ up2date.



#
#
# BOARD
#
#




distrib_opt___XBOW_MIB5X0__:: \
		ee_$(DIST)/pkg/cfg/arch \
		ee_$(DIST)/pkg/cfg/arch/rules_xbow_mib5x0.mk \
		ee_$(DIST)/pkg/board/xbow_mib5x0/inc \
		ee_$(DIST)/pkg/board/xbow_mib5x0/inc/ee_board.h
	@echo OPT __XBOW_MIB5X0__ up2date.






distrib_opt___EVALUATOR7T__:: \
		ee_$(DIST)/pkg/cfg/arch \
		ee_$(DIST)/pkg/cfg/arch/rules_arm_evaluator7t.mk \
		ee_$(DIST)/pkg/board/arm_evaluator7t \
		ee_$(DIST)/pkg/board/arm_evaluator7t/cfg \
		ee_$(DIST)/pkg/board/arm_evaluator7t/cfg/loc_gnu.ld \
		ee_$(DIST)/pkg/board/arm_evaluator7t/debug \
		ee_$(DIST)/pkg/board/arm_evaluator7t/debug/lauterbach \
		ee_$(DIST)/pkg/board/arm_evaluator7t/debug/lauterbach/t32 \
		ee_$(DIST)/pkg/board/arm_evaluator7t/debug/lauterbach/t32/evaluator7t.per \
		ee_$(DIST)/pkg/board/arm_evaluator7t/debug/lauterbach/t32/startup.cmm \
		ee_$(DIST)/pkg/board/arm_evaluator7t/debug/lauterbach/t32/windows.cmm \
		ee_$(DIST)/pkg/board/arm_evaluator7t/debug/lauterbach/t32.cmm \
		ee_$(DIST)/pkg/board/arm_evaluator7t/inc \
		ee_$(DIST)/pkg/board/arm_evaluator7t/inc/ee_board.h
	@echo OPT __EVALUATOR7T__ up2date.


distrib_opt___unibo_mparm__:: \
		ee_$(DIST)/pkg/cfg/arch \
		ee_$(DIST)/pkg/cfg/arch/rules_unibo_mparm.mk \
		ee_$(DIST)/pkg/board/unibo_mparm \
		ee_$(DIST)/pkg/board/unibo_mparm/cfg \
		ee_$(DIST)/pkg/board/unibo_mparm/cfg/loc_gnu.ld \
		ee_$(DIST)/pkg/board/unibo_mparm/debug \
		ee_$(DIST)/pkg/board/unibo_mparm/inc \
		ee_$(DIST)/pkg/board/unibo_mparm/inc/ee_board.h
	@echo OPT __unibo_mparm__ up2date.


distrib_opt___MPC566EVB__:: \
		ee_$(DIST)/pkg/cfg/arch \
		ee_$(DIST)/pkg/cfg/arch/rules_axiom_mpc566evb.mk \
		ee_$(DIST)/pkg/board/axiom_mpc566evb \
		ee_$(DIST)/pkg/board/axiom_mpc566evb/cfg \
		ee_$(DIST)/pkg/board/axiom_mpc566evb/cfg/loc_gnu.ld \
		ee_$(DIST)/pkg/board/axiom_mpc566evb/debug \
		ee_$(DIST)/pkg/board/axiom_mpc566evb/debug/lauterbach \
		ee_$(DIST)/pkg/board/axiom_mpc566evb/debug/lauterbach/t32.cmm \
		ee_$(DIST)/pkg/board/axiom_mpc566evb/inc \
		ee_$(DIST)/pkg/board/axiom_mpc566evb/inc/ee_board.h \
		ee_$(DIST)/pkg/board/axiom_mpc566evb/inc/ee_micro.h
	@echo OPT __MPC566EVB__ up2date.




#
#
# KERNEL
#
#

distrib_opt___OO_BCC1__ distrib_opt___OO_BCC2__ \
distrib_opt___OO_ECC1__ distrib_opt___OO_ECC2__:: distrib_opt_base \
		ee_$(DIST)/pkg/kernel/oo/inc \
		ee_$(DIST)/pkg/kernel/oo/inc/ee_common.h \
		ee_$(DIST)/pkg/kernel/oo/inc/ee_inline.h \
		ee_$(DIST)/pkg/kernel/oo/inc/ee_intfunc.h \
		ee_$(DIST)/pkg/kernel/oo/inc/ee_kernel.h \
		ee_$(DIST)/pkg/kernel/oo/inc/ee_api.h
	@echo OPT __OO_*__ up2date.



distrib_opt___ASSERT__:: \
		ee_$(DIST)/pkg/test/assert/inc \
		ee_$(DIST)/pkg/test/assert/inc/ee_assert.h
	@echo OPT __ASSERT__ up2date.

distrib_opt___CBS__:: \
		ee_$(DIST)/pkg/kernel/cbs/inc \
		ee_$(DIST)/pkg/kernel/cbs/inc/ee_common.h \
		ee_$(DIST)/pkg/kernel/cbs/inc/ee_kernel.h \
		ee_$(DIST)/pkg/kernel/cbs/inc/ee_api.h
	@echo OPT __CBS__ up2date.


distrib_opt___FP__:: \
		ee_$(DIST)/pkg/kernel/fp/inc \
		ee_$(DIST)/pkg/kernel/fp/inc/ee_common.h \
		ee_$(DIST)/pkg/kernel/fp/inc/ee_kernel.h \
		ee_$(DIST)/pkg/kernel/fp/inc/ee_api.h
	@echo OPT __FP__ up2date.

distrib_opt___EDF__:: \
		ee_$(DIST)/pkg/kernel/edf/inc \
		ee_$(DIST)/pkg/kernel/edf/inc/ee_api.h \
		ee_$(DIST)/pkg/kernel/edf/inc/ee_common.h \
		ee_$(DIST)/pkg/kernel/edf/inc/ee_kernel.h
	@echo OPT __EDF__ up2date.

distrib_opt___ALARMS__:: \
		ee_$(DIST)/pkg/kernel/alarms/inc \
		ee_$(DIST)/pkg/kernel/alarms/inc/ee_alarms.h \
		ee_$(DIST)/pkg/kernel/alarms/inc/ee_api.h
	@echo OPT __ALARMS__ up2date.

distrib_opt___SEM__:: \
		ee_$(DIST)/pkg/kernel/sem/inc \
		ee_$(DIST)/pkg/kernel/sem/inc/ee_sem.h \
		ee_$(DIST)/pkg/kernel/sem/inc/ee_api.h
	@echo OPT __SEM__ up2date.

distrib_opt___RN__:: \
		ee_$(DIST)/pkg/kernel/rn/inc \
		ee_$(DIST)/pkg/kernel/rn/inc/ee_rn.h
	@echo OPT __RN__ up2date.

distrib_opt___FRSH__:: \
		ee_$(DIST)/pkg/kernel/frsh \
		ee_$(DIST)/pkg/kernel/frsh/README.txt \
		ee_$(DIST)/pkg/kernel/frsh/inc \
		ee_$(DIST)/pkg/kernel/frsh/inc/ee_common.h \
		ee_$(DIST)/pkg/kernel/frsh/inc/ee_kernel.h \
		ee_$(DIST)/pkg/kernel/frsh/inc/ee_api.h \
		ee_$(DIST)/pkg/kernel/frsh/inc/frsh_types.h \
		ee_$(DIST)/pkg/kernel/frsh/frsh_include \
		ee_$(DIST)/pkg/kernel/frsh/frsh_include/frsh_configuration_parameters.h \
		ee_$(DIST)/pkg/kernel/frsh/frsh_include/frsh_core_types.h \
		ee_$(DIST)/pkg/kernel/frsh/frsh_include/frsh_error.h \
		ee_$(DIST)/pkg/kernel/frsh/frsh_include/frsh_time_types.h \
		ee_$(DIST)/pkg/kernel/frsh/frsh_include/readme.txt
	@echo OPT __FRSH__ up2date.


#
#
# COM
#
#

distrib_opt___CABS__:: \
		ee_$(DIST)/pkg/com/cabs/inc \
		ee_$(DIST)/pkg/com/cabs/inc/ee_cabs.h
	@echo OPT __CABS__ up2date.

#
#
# CONTRIB
#
#

distrib_opt___LIB_IEEE802154__:: \
		ee_$(DIST)/contrib/ieee802154/inc/common \
		ee_$(DIST)/contrib/ieee802154/inc/ieee802154alarms \
		ee_$(DIST)/contrib/ieee802154/inc/hal \
		ee_$(DIST)/contrib/ieee802154/inc/phy \
		ee_$(DIST)/contrib/ieee802154/inc/mac \
		ee_$(DIST)/contrib/ieee802154/inc/nwl \
		ee_$(DIST)/contrib/ieee802154/inc/frame_format.h \
		ee_$(DIST)/contrib/ieee802154/inc/common/Compiler.h \
		ee_$(DIST)/contrib/ieee802154/inc/common/cc2420.h \
		ee_$(DIST)/contrib/ieee802154/inc/common/console.h \
		ee_$(DIST)/contrib/ieee802154/inc/common/ee_radio_spi.h \
		ee_$(DIST)/contrib/ieee802154/inc/common/eeuart.h \
		ee_$(DIST)/contrib/ieee802154/inc/common/generic.h \
		ee_$(DIST)/contrib/ieee802154/inc/common/hal.h \
		ee_$(DIST)/contrib/ieee802154/inc/common/netbuff.h \
		ee_$(DIST)/contrib/ieee802154/inc/common/queue.h \
		ee_$(DIST)/contrib/ieee802154/inc/common/sralloc.h \
		ee_$(DIST)/contrib/ieee802154/inc/hal/hal_cc2420.h \
		ee_$(DIST)/contrib/ieee802154/inc/hal/hal_defines.h \
		ee_$(DIST)/contrib/ieee802154/inc/hal/hal_interrupts.h \
		ee_$(DIST)/contrib/ieee802154/inc/ieee802154alarms/ieee802154alarms.h \
		ee_$(DIST)/contrib/ieee802154/inc/mac/MCPS_DATA.h \
		ee_$(DIST)/contrib/ieee802154/inc/mac/MCPS_PURGE.h \
		ee_$(DIST)/contrib/ieee802154/inc/mac/MLME_ASSOCIATE.h \
		ee_$(DIST)/contrib/ieee802154/inc/mac/MLME_BEACON_NOTIFY.h \
		ee_$(DIST)/contrib/ieee802154/inc/mac/MLME_COMM_STATUS.h \
		ee_$(DIST)/contrib/ieee802154/inc/mac/MLME_DISASSOCIATE.h \
		ee_$(DIST)/contrib/ieee802154/inc/mac/MLME_GET.h \
		ee_$(DIST)/contrib/ieee802154/inc/mac/MLME_GTS.h \
		ee_$(DIST)/contrib/ieee802154/inc/mac/MLME_ORPHAN.h \
		ee_$(DIST)/contrib/ieee802154/inc/mac/MLME_POLL.h \
		ee_$(DIST)/contrib/ieee802154/inc/mac/MLME_RESET.h \
		ee_$(DIST)/contrib/ieee802154/inc/mac/MLME_RX_ENABLE.h \
		ee_$(DIST)/contrib/ieee802154/inc/mac/MLME_SCAN.h \
		ee_$(DIST)/contrib/ieee802154/inc/mac/MLME_SET.h \
		ee_$(DIST)/contrib/ieee802154/inc/mac/MLME_START.h \
		ee_$(DIST)/contrib/ieee802154/inc/mac/MLME_SYNC.h \
		ee_$(DIST)/contrib/ieee802154/inc/mac/MLME_SYNC_LOSS.h \
		ee_$(DIST)/contrib/ieee802154/inc/mac/Mac.h \
		ee_$(DIST)/contrib/ieee802154/inc/mac/gts_mechanism.h \
		ee_$(DIST)/contrib/ieee802154/inc/mac/mac_const.h \
		ee_$(DIST)/contrib/ieee802154/inc/mac/mac_enumerations.h \
		ee_$(DIST)/contrib/ieee802154/inc/mac/mac_func.h \
		ee_$(DIST)/contrib/ieee802154/inc/nwl/Nwl.h \
		ee_$(DIST)/contrib/ieee802154/inc/phy/PD_DATA.h \
		ee_$(DIST)/contrib/ieee802154/inc/phy/PLME_CCA.h \
		ee_$(DIST)/contrib/ieee802154/inc/phy/PLME_ED.h \
		ee_$(DIST)/contrib/ieee802154/inc/phy/PLME_GET.h \
		ee_$(DIST)/contrib/ieee802154/inc/phy/PLME_SET.h \
		ee_$(DIST)/contrib/ieee802154/inc/phy/PLME_SET_TRX_STATE.h \
		ee_$(DIST)/contrib/ieee802154/inc/phy/phy.h \
		ee_$(DIST)/contrib/ieee802154/inc/phy/phy_const.h \
		ee_$(DIST)/contrib/ieee802154/inc/phy/phy_enumerations.h
	@echo OPT __LIB_IEEE802154__ up2date.


#
# Generic rules
#

ee_$(DIST)/%: ../../%
	@echo FILE $*
ifdef BANNER
	@if test -f ../banner/$($($(subst /,_,$(dir $*))banner)$(suffix $*)); then \
		cat ../banner/$($($(subst /,_,$(dir $*))banner)$(suffix $*)) ../../$* > ee_$(DIST)/$*; \
	else \
		cp ../../$* ee_$(DIST)/$*; \
	fi
else
	@cp ../../$* ee_$(DIST)/$*
endif


# erika_$(DIST)/config/%: \
# 			template/config/%
# 	@echo FILE $*
# 	@cp template/config/$* erika_$(DIST)/config/$*
