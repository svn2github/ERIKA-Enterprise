#
# distrib.in: rules to create the include file structure
#

# These rules extends the files that are exported by a binary distribution.
# For that reason, we include the distrib.mk file of the binary distribution
# here; moreover, all the dependencies are :: rule

include config/distrib_bin.mk

distrib_opt_base:: \
		ee_$(DIST)/pkg \
		ee_$(DIST)/pkg/ee_internal.h
	@echo Base files up2date.

#
#
# CPU
#
#


distrib_opt___AVR5__:: \
		ee_$(DIST)/pkg/cpu/avr5/cfg \
		ee_$(DIST)/pkg/cpu/avr5/cfg/cfg.mk \
		ee_$(DIST)/pkg/cpu/avr5/inc \
		ee_$(DIST)/pkg/cpu/avr5/inc/ee_internal.h \
		ee_$(DIST)/pkg/cpu/avr5/src \
		ee_$(DIST)/pkg/cpu/avr5/src/ee_hal.S \
		ee_$(DIST)/pkg/cpu/avr5/src/stackManage.S \
		ee_$(DIST)/pkg/cpu/avr5/src/ee_osek.S \
		ee_$(DIST)/pkg/mcu/atmel_atmega128/cfg \
		ee_$(DIST)/pkg/mcu/atmel_atmega128/cfg/cfg.mk \
		ee_$(DIST)/pkg/mcu/atmel_atmega128/inc \
		ee_$(DIST)/pkg/mcu/atmel_atmega128/inc/ee_internal.h \
		ee_$(DIST)/pkg/mcu/atmel_atmega128/inc/ee_irqstub.S \
		ee_$(DIST)/pkg/mcu/atmel_atmega128/inc/ee_spi.h \
		ee_$(DIST)/pkg/mcu/atmel_atmega128/inc/ee_uart.h \
		ee_$(DIST)/pkg/mcu/atmel_atmega128/src \
		ee_$(DIST)/pkg/mcu/atmel_atmega128/src/ee_ic.c \
		ee_$(DIST)/pkg/mcu/atmel_atmega128/src/ee_external_int.S \
		ee_$(DIST)/pkg/mcu/atmel_atmega128/src/ee_timer.S \
		ee_$(DIST)/pkg/mcu/atmel_atmega128/src/ee_uart_opt.S \
		ee_$(DIST)/pkg/mcu/atmel_atmega128/src/ee_uartApi.c \
		ee_$(DIST)/pkg/mcu/atmel_atmega128/src/ee_spi.c \
		ee_$(DIST)/pkg/mcu/atmel_atmega128/src/ee_uart.c \
		ee_$(DIST)/pkg/mcu/atmel_atmega1281/cfg \
		ee_$(DIST)/pkg/mcu/atmel_atmega1281/cfg/cfg.mk \
		ee_$(DIST)/pkg/mcu/atmel_atmega1281/inc \
		ee_$(DIST)/pkg/mcu/atmel_atmega1281/inc/ee_internal.h \
		ee_$(DIST)/pkg/mcu/atmel_atmega1281/inc/ee_irqstub.S \
		ee_$(DIST)/pkg/mcu/atmel_atmega1281/inc/ee_spi.h \
		ee_$(DIST)/pkg/mcu/atmel_atmega1281/inc/ee_uart.h \
		ee_$(DIST)/pkg/mcu/atmel_atmega1281/src \
		ee_$(DIST)/pkg/mcu/atmel_atmega1281/src/ee_ic.c \
		ee_$(DIST)/pkg/mcu/atmel_atmega1281/src/ee_external_int.S \
		ee_$(DIST)/pkg/mcu/atmel_atmega1281/src/ee_timer.S \
		ee_$(DIST)/pkg/mcu/atmel_atmega1281/src/ee_uart_opt.S \
		ee_$(DIST)/pkg/mcu/atmel_atmega1281/src/ee_uartApi.c \
		ee_$(DIST)/pkg/mcu/atmel_atmega1281/src/ee_spi.c \
		ee_$(DIST)/pkg/mcu/atmel_atmega1281/src/ee_uart.c \
		ee_$(DIST)/pkg/board/xbow_mib5x0/cfg \
		ee_$(DIST)/pkg/board/xbow_mib5x0/cfg/cfg.mk \
		ee_$(DIST)/pkg/board/xbow_mib5x0/inc \
		ee_$(DIST)/pkg/board/xbow_mib5x0/inc/ee_internal.h \
		ee_$(DIST)/pkg/board/xbow_mib5x0/src \
		ee_$(DIST)/pkg/board/xbow_mib5x0/src/ee_board.c \
		ee_$(DIST)/pkg/board/xbow_mib5x0/src/ee_led.S \
		ee_$(DIST)/pkg/board/atmel_stk500/cfg \
		ee_$(DIST)/pkg/board/atmel_stk500/cfg/cfg.mk \
		ee_$(DIST)/pkg/board/atmel_stk500/inc \
		ee_$(DIST)/pkg/board/atmel_stk500/inc/ee_internal.h \
		ee_$(DIST)/pkg/board/atmel_stk500/src \
		ee_$(DIST)/pkg/board/atmel_stk500/src/ee_board.c \
		ee_$(DIST)/pkg/board/atmel_stk500/src/ee_led.S
	@echo OPT __AVR5__ up2date.


distrib_opt___ARM7GNU__:: \
		ee_$(DIST)/pkg/cpu/arm7tdmi/cfg \
		ee_$(DIST)/pkg/cpu/arm7tdmi/cfg/cfg.mk \
		ee_$(DIST)/pkg/cpu/arm7tdmi/inc \
		ee_$(DIST)/pkg/cpu/arm7tdmi/inc/ee_internal.h \
		ee_$(DIST)/pkg/cpu/arm7tdmi/src \
		ee_$(DIST)/pkg/cpu/arm7tdmi/src/ee_hal.S \
		ee_$(DIST)/pkg/cpu/arm7tdmi/src/ee_hal_c.c \
		ee_$(DIST)/pkg/cpu/arm7tdmi/src/ee_hal_thumb.S \
		ee_$(DIST)/pkg/cpu/arm7tdmi/src/ee_oo.S \
		ee_$(DIST)/pkg/cpu/arm7tdmi/src/ee_hal_ads.S \
		ee_$(DIST)/pkg/cpu/arm7tdmi/src/ee_hal_thumb_ads.S \
		ee_$(DIST)/pkg/cpu/arm7tdmi/src/ee_oo_ads.S
	@echo OPT __ARM7GNU__ up2date.

# This includes also the Nios II MCU
distrib_opt___NIOS2__:: \
		ee_$(DIST)/pkg/cpu/nios2/cfg \
		ee_$(DIST)/pkg/cpu/nios2/cfg/component.mk \
		ee_$(DIST)/pkg/cpu/nios2/inc \
		ee_$(DIST)/pkg/cpu/nios2/inc/ee_internal.h \
		ee_$(DIST)/pkg/cpu/nios2/src \
		ee_$(DIST)/pkg/cpu/nios2/src/ee_hal.S \
		ee_$(DIST)/pkg/cpu/nios2/src/ee_oo.S \
		ee_$(DIST)/pkg/cpu/nios2/src/ee_start.c \
		ee_$(DIST)/pkg/mcu/altera_nios2/inc \
		ee_$(DIST)/pkg/mcu/altera_nios2/inc/ee_internal.h \
		ee_$(DIST)/pkg/mcu/altera_nios2/src \
		ee_$(DIST)/pkg/mcu/altera_nios2/src/ee_nios2_timers.c \
		$(distrib_files_NIOS2)
	@echo OPT __NIOS2__ up2date.









distrib_opt___MPC5XX__:: \
		ee_$(DIST)/pkg/cpu/mpc5xx \
		ee_$(DIST)/pkg/cpu/mpc5xx/cfg \
		ee_$(DIST)/pkg/cpu/mpc5xx/cfg/cfg.mk \
		ee_$(DIST)/pkg/cpu/mpc5xx/inc \
		ee_$(DIST)/pkg/cpu/mpc5xx/inc/ee_internal.h \
		ee_$(DIST)/pkg/cpu/mpc5xx/src \
		ee_$(DIST)/pkg/cpu/mpc5xx/src/ee_hal.S \
		ee_$(DIST)/pkg/cpu/mpc5xx/src/ee_irqvect.S
	@echo OPT __MPC5XX__ up2date.


# This should be splitted in CPU, MCU, BOARD!!!
distrib_opt___PIC30__:: \
		ee_$(DIST)/pkg/cpu/pic30/cfg \
		ee_$(DIST)/pkg/cpu/pic30/cfg/cfg.mk \
		ee_$(DIST)/pkg/cpu/pic30/inc \
		ee_$(DIST)/pkg/cpu/pic30/inc/ee_internal.h \
		ee_$(DIST)/pkg/cpu/pic30/src \
		ee_$(DIST)/pkg/cpu/pic30/src/ee_hal.S \
		ee_$(DIST)/pkg/cpu/pic30/src/ee_hal_c.c \
		ee_$(DIST)/pkg/cpu/pic30/src/ee_oo.S \
		ee_$(DIST)/pkg/mcu/microchip_dspic/cfg \
		ee_$(DIST)/pkg/mcu/microchip_dspic/cfg/cfg.mk \
		ee_$(DIST)/pkg/mcu/microchip_dspic/inc \
		ee_$(DIST)/pkg/mcu/microchip_dspic/inc/ee_internal.h \
		ee_$(DIST)/pkg/mcu/microchip_dspic/inc/ee_uart.h \
		ee_$(DIST)/pkg/mcu/microchip_dspic/inc/ee_spi.h \
		ee_$(DIST)/pkg/mcu/microchip_dspic/src \
		ee_$(DIST)/pkg/mcu/microchip_dspic/src/ee_pic30frsh.c \
		ee_$(DIST)/pkg/mcu/microchip_dspic/src/ee_uart.c \
		ee_$(DIST)/pkg/mcu/microchip_dspic/src/ee_spi.c \
		ee_$(DIST)/pkg/board/ee_flex/cfg \
		ee_$(DIST)/pkg/board/ee_flex/cfg/cfg.mk \
		ee_$(DIST)/pkg/board/ee_flex/inc \
		ee_$(DIST)/pkg/board/ee_flex/inc/ee_internal.h \
		ee_$(DIST)/pkg/board/ee_flex/src \
		ee_$(DIST)/pkg/board/ee_flex/src/ee_board.c \
		ee_$(DIST)/pkg/board/microchip_explorer16/cfg \
		ee_$(DIST)/pkg/board/microchip_explorer16/cfg/cfg.mk \
		ee_$(DIST)/pkg/board/microchip_explorer16/inc \
		ee_$(DIST)/pkg/board/microchip_explorer16/inc/ee_internal.h \
		ee_$(DIST)/pkg/board/microchip_explorer16/src \
		ee_$(DIST)/pkg/board/microchip_explorer16/src/ee_board.c \
		ee_$(DIST)/pkg/board/microchip_dspicdem11plus/cfg \
		ee_$(DIST)/pkg/board/microchip_dspicdem11plus/cfg/cfg.mk \
		ee_$(DIST)/pkg/board/microchip_dspicdem11plus/inc \
		ee_$(DIST)/pkg/board/microchip_dspicdem11plus/inc/ee_internal.h \
		ee_$(DIST)/pkg/board/microchip_dspicdem11plus/src \
		ee_$(DIST)/pkg/board/microchip_dspicdem11plus/src/ee_board.c
	@echo OPT __PIC30__ up2date.


#
#
# MCU
#
#





distrib_opt___SAMSUNG_KS32C50100__:: \
		ee_$(DIST)/pkg/mcu/samsung_ks32c50100 \
		ee_$(DIST)/pkg/mcu/samsung_ks32c50100/cfg \
		ee_$(DIST)/pkg/mcu/samsung_ks32c50100/cfg/cfg.mk \
		ee_$(DIST)/pkg/mcu/samsung_ks32c50100/inc \
		ee_$(DIST)/pkg/mcu/samsung_ks32c50100/inc/ee_internal.h \
		ee_$(DIST)/pkg/mcu/samsung_ks32c50100/inc/ee_ic_fiqstub.S \
		ee_$(DIST)/pkg/mcu/samsung_ks32c50100/src \
		ee_$(DIST)/pkg/mcu/samsung_ks32c50100/src/ee_ic.c \
		ee_$(DIST)/pkg/mcu/samsung_ks32c50100/src/ee_ic_exc_handlers.S \
		ee_$(DIST)/pkg/mcu/samsung_ks32c50100/src/ee_irqvect.S \
		ee_$(DIST)/pkg/mcu/samsung_ks32c50100/src/ee_start.S
	@echo OPT __SAMSUNG_KS32C50100__ up2date.

distrib_opt___unibo_mparm__:: \
		ee_$(DIST)/pkg/mcu/unibo_mparm \
		ee_$(DIST)/pkg/mcu/unibo_mparm/cfg \
		ee_$(DIST)/pkg/mcu/unibo_mparm/cfg/cfg.mk \
		ee_$(DIST)/pkg/mcu/unibo_mparm/inc \
		ee_$(DIST)/pkg/mcu/unibo_mparm/inc/ee_internal.h \
		ee_$(DIST)/pkg/mcu/unibo_mparm/inc/ee_ic_fiqstub.S \
		ee_$(DIST)/pkg/mcu/unibo_mparm/src \
		ee_$(DIST)/pkg/mcu/unibo_mparm/src/ee_ic.c \
		ee_$(DIST)/pkg/mcu/unibo_mparm/src/ee_ic_exc_handlers.S \
		ee_$(DIST)/pkg/mcu/unibo_mparm/src/ee_irqvect.S \
		ee_$(DIST)/pkg/mcu/unibo_mparm/src/ee_start.S \
		ee_$(DIST)/pkg/board/unibo_mparm \
		ee_$(DIST)/pkg/board/unibo_mparm/cfg \
		ee_$(DIST)/pkg/board/unibo_mparm/cfg/cfg.mk \
		ee_$(DIST)/pkg/board/unibo_mparm/inc \
		ee_$(DIST)/pkg/board/unibo_mparm/inc/ee_internal.h \
		ee_$(DIST)/pkg/board/unibo_mparm/src \
		ee_$(DIST)/pkg/board/unibo_mparm/src/ee_board.c \
		ee_$(DIST)/pkg/board/unibo_mparm/debug \
		ee_$(DIST)/pkg/board/unibo_mparm/debug/swarm.tpl
	@echo OPT __unibo_mparm__ up2date.

distrib_opt___ST_STA2051__:: \
		ee_$(DIST)/pkg/mcu/st_sta2051 \
		ee_$(DIST)/pkg/mcu/st_sta2051/cfg \
		ee_$(DIST)/pkg/mcu/st_sta2051/cfg/cfg.mk \
		ee_$(DIST)/pkg/mcu/st_sta2051/inc \
		ee_$(DIST)/pkg/mcu/st_sta2051/inc/ee_ic.h \
		ee_$(DIST)/pkg/mcu/st_sta2051/inc/ee_ic_fiqstub.S \
		ee_$(DIST)/pkg/mcu/st_sta2051/inc/ee_ic_irqstub.S \
		ee_$(DIST)/pkg/mcu/st_sta2051/inc/ee_ic_fiqstub_ads.S \
		ee_$(DIST)/pkg/mcu/st_sta2051/inc/ee_ic_irqstub_ads.S \
		ee_$(DIST)/pkg/mcu/st_sta2051/inc/ee_internal.h \
		ee_$(DIST)/pkg/mcu/st_sta2051/inc/ee_mcu.h \
		ee_$(DIST)/pkg/mcu/st_sta2051/inc/ee_mcuregs.h \
		ee_$(DIST)/pkg/mcu/st_sta2051/src \
		ee_$(DIST)/pkg/mcu/st_sta2051/src/ee_irqvect.S \
		ee_$(DIST)/pkg/mcu/st_sta2051/src/ee_start.S \
		ee_$(DIST)/pkg/mcu/st_sta2051/src/ee_irqvect_ads.S \
		ee_$(DIST)/pkg/mcu/st_sta2051/src/ee_start_ads.S
	@echo OPT __ST_STA2051__ up2date.


#
#
# BOARD
#
#



distrib_opt___EVALUATOR7T_EXAMPLES__:: \
	ee_$(DIST)/examples/arm7_evaluator7t/fp \
	ee_$(DIST)/examples/arm7_evaluator7t/fp/template.xml \
	ee_$(DIST)/examples/arm7_evaluator7t/fp/code.c \
	ee_$(DIST)/examples/arm7_evaluator7t/fp/conf.oil \
	ee_$(DIST)/examples/arm7_evaluator7t/fp/thumb.c

#distrib_files_EVALUATOR7T_EXAMPLES += \
#	ee_$(DIST)/examples/arm7_evaluator7t/edf \
#	ee_$(DIST)/examples/arm7_evaluator7t/edf/cfg_e7t.h \
#	ee_$(DIST)/examples/arm7_evaluator7t/edf/code.c \
#	ee_$(DIST)/examples/arm7_evaluator7t/edf/code.h \
#	ee_$(DIST)/examples/arm7_evaluator7t/edf/eecfg.h \
#	ee_$(DIST)/examples/arm7_evaluator7t/edf/initdrvs.c \
#	ee_$(DIST)/examples/arm7_evaluator7t/edf/inithal.c \
#	ee_$(DIST)/examples/arm7_evaluator7t/edf/initkern.c \
#	ee_$(DIST)/examples/arm7_evaluator7t/edf/makefile \
#	ee_$(DIST)/examples/arm7_evaluator7t/edf/thumb.c \
#	ee_$(DIST)/examples/arm7_evaluator7t/edf/timer.c

distrib_opt___EVALUATOR7T__:: \
		ee_$(DIST)/pkg/board/arm_evaluator7t \
		ee_$(DIST)/pkg/board/arm_evaluator7t/cfg \
		ee_$(DIST)/pkg/board/arm_evaluator7t/cfg/cfg.mk \
		ee_$(DIST)/pkg/board/arm_evaluator7t/inc \
		ee_$(DIST)/pkg/board/arm_evaluator7t/inc/ee_internal.h \
		ee_$(DIST)/pkg/board/arm_evaluator7t/src \
		ee_$(DIST)/pkg/board/arm_evaluator7t/src/ee_board.c \
		$(distrib_files_EVALUATOR7T)
	@echo OPT __EVALUATOR7T__ up2date.


distrib_opt___MPC566EVB__:: \
		ee_$(DIST)/pkg/board/axiom_mpc566evb/cfg \
		ee_$(DIST)/pkg/board/axiom_mpc566evb/cfg/cfg.mk \
		ee_$(DIST)/pkg/board/axiom_mpc566evb/inc \
		ee_$(DIST)/pkg/board/axiom_mpc566evb/inc/ee_internal.h \
		ee_$(DIST)/pkg/board/axiom_mpc566evb/src \
		ee_$(DIST)/pkg/board/axiom_mpc566evb/src/ee_board.c \
		ee_$(DIST)/pkg/board/axiom_mpc566evb/src/ee_start.S
	@echo OPT __MPC566EVB__ up2date.



#
#
# KERNEL
#
#

distrib_opt___OO_BCC1__ distrib_opt___OO_BCC2__ \
distrib_opt___OO_ECC1__ distrib_opt___OO_ECC2__:: distrib_opt_base \
		ee_$(DIST)/pkg/kernel/oo \
		ee_$(DIST)/pkg/kernel/oo/cfg \
		ee_$(DIST)/pkg/kernel/oo/cfg/cfg.mk \
		ee_$(DIST)/pkg/kernel/oo/inc \
		ee_$(DIST)/pkg/kernel/oo/inc/ee_internal.h \
		ee_$(DIST)/pkg/kernel/oo/src \
		ee_$(DIST)/pkg/kernel/oo/src/ee_activate.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_alcancel.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_alget.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_algetbase.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_alsetabs.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_alsetrel.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_altick.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_chaintas.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_disableallinterrupts.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_enableallinterrupts.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_evclear.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_evget.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_evset.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_evwait.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_force_schedule.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_getactiveapplicationmode.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_gettaskid.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_gettaskstate.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_irqendin.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_lockres.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_lookup.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_resumeallinterrupts.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_resumeosinterrupts.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_rq_exchg.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_rq_first.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_rq_inser.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_schedule.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_sempost.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_semtrywait.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_semwait.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_shtdown.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_startos.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_suspendallinterrupts.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_suspendosinterrupts.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_terminat.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_thendin.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_tstub.c \
		ee_$(DIST)/pkg/kernel/oo/src/ee_ulockres.c
	@echo OPT __OO_*__ up2date.


distrib_opt___ASSERT__:: \
		ee_$(DIST)/pkg/test/assert/cfg \
		ee_$(DIST)/pkg/test/assert/cfg/cfg.mk \
		ee_$(DIST)/pkg/test/assert/src \
		ee_$(DIST)/pkg/test/assert/src/ee_assert.c
	@echo OPT __ASSERT__ up2date.

distrib_opt___CBS__:: \
		ee_$(DIST)/pkg/kernel/cbs/cfg \
		ee_$(DIST)/pkg/kernel/cbs/cfg/cfg.mk \
		ee_$(DIST)/pkg/kernel/cbs/inc \
		ee_$(DIST)/pkg/kernel/cbs/inc/ee_internal.h \
		ee_$(DIST)/pkg/kernel/cbs/src \
		ee_$(DIST)/pkg/kernel/cbs/src/ee_cap.c \
		ee_$(DIST)/pkg/kernel/cbs/src/ee_dlcheck.c \
		ee_$(DIST)/pkg/kernel/cbs/src/ee_gettime.c \
		ee_$(DIST)/pkg/kernel/cbs/src/ee_irq_sc.c \
		ee_$(DIST)/pkg/kernel/cbs/src/ee_mutex.c \
		ee_$(DIST)/pkg/kernel/cbs/src/ee_rq_inser.c \
		ee_$(DIST)/pkg/kernel/cbs/src/ee_schedule.c \
		ee_$(DIST)/pkg/kernel/cbs/src/ee_thact.c \
		ee_$(DIST)/pkg/kernel/cbs/src/ee_thendin.c
	@echo OPT __CBS__ up2date.


distrib_opt___FP__:: \
		ee_$(DIST)/pkg/kernel/fp/cfg \
		ee_$(DIST)/pkg/kernel/fp/cfg/cfg.mk \
		ee_$(DIST)/pkg/kernel/fp/inc \
		ee_$(DIST)/pkg/kernel/fp/inc/ee_internal.h \
		ee_$(DIST)/pkg/kernel/fp/src \
		ee_$(DIST)/pkg/kernel/fp/src/ee_irqsc.c \
		ee_$(DIST)/pkg/kernel/fp/src/ee_mutex.c \
		ee_$(DIST)/pkg/kernel/fp/src/ee_rqexchg.c \
		ee_$(DIST)/pkg/kernel/fp/src/ee_rqinsert.c \
		ee_$(DIST)/pkg/kernel/fp/src/ee_schedule.c \
		ee_$(DIST)/pkg/kernel/fp/src/ee_thact.c \
		ee_$(DIST)/pkg/kernel/fp/src/ee_thendin.c
	@echo OPT __FP__ up2date.

distrib_opt___EDF__:: \
		ee_$(DIST)/pkg/kernel/edf/cfg \
		ee_$(DIST)/pkg/kernel/edf/cfg/cfg.mk \
		ee_$(DIST)/pkg/kernel/edf/inc \
		ee_$(DIST)/pkg/kernel/edf/inc/ee_internal.h \
		ee_$(DIST)/pkg/kernel/edf/src \
		ee_$(DIST)/pkg/kernel/edf/src/ee_gettime.c \
		ee_$(DIST)/pkg/kernel/edf/src/ee_irqsc.c \
		ee_$(DIST)/pkg/kernel/edf/src/ee_mutex.c \
		ee_$(DIST)/pkg/kernel/edf/src/ee_rqexchg.c \
		ee_$(DIST)/pkg/kernel/edf/src/ee_rqinsert.c \
		ee_$(DIST)/pkg/kernel/edf/src/ee_schedule.c \
		ee_$(DIST)/pkg/kernel/edf/src/ee_thact.c \
		ee_$(DIST)/pkg/kernel/edf/src/ee_thendin.c
	@echo OPT __EDF__ up2date.

distrib_opt___ALARMS__:: \
		ee_$(DIST)/pkg/kernel/alarms/cfg \
		ee_$(DIST)/pkg/kernel/alarms/cfg/cfg.mk \
		ee_$(DIST)/pkg/kernel/alarms/src \
		ee_$(DIST)/pkg/kernel/alarms/src/ee_alcancel.c \
		ee_$(DIST)/pkg/kernel/alarms/src/ee_alget.c \
		ee_$(DIST)/pkg/kernel/alarms/src/ee_alsetabs.c \
		ee_$(DIST)/pkg/kernel/alarms/src/ee_alsetrel.c \
		ee_$(DIST)/pkg/kernel/alarms/src/ee_altick.c
	@echo OPT __ALARMS__ up2date.

distrib_opt___SEM__:: \
		ee_$(DIST)/pkg/kernel/sem/cfg \
		ee_$(DIST)/pkg/kernel/sem/cfg/cfg.mk \
		ee_$(DIST)/pkg/kernel/sem/src \
		ee_$(DIST)/pkg/kernel/sem/src/ee_sgetvalue.c \
		ee_$(DIST)/pkg/kernel/sem/src/ee_spost.c \
		ee_$(DIST)/pkg/kernel/sem/src/ee_strywait.c \
		ee_$(DIST)/pkg/kernel/sem/src/ee_swait.c
	@echo OPT __SEM__ up2date.

distrib_opt___RN__:: \
		ee_$(DIST)/pkg/kernel/rn/cfg \
		ee_$(DIST)/pkg/kernel/rn/cfg/cfg.mk \
		ee_$(DIST)/pkg/kernel/rn/inc \
		ee_$(DIST)/pkg/kernel/rn/inc/ee_rn_internal.h \
		ee_$(DIST)/pkg/kernel/rn/src \
		ee_$(DIST)/pkg/kernel/rn/src/ee_rn.c \
		ee_$(DIST)/pkg/kernel/rn/src/ee_rnsend.c
	@echo OPT __RN__ up2date.

distrib_opt___FRSH__:: \
		ee_$(DIST)/pkg/kernel/frsh/cfg \
		ee_$(DIST)/pkg/kernel/frsh/cfg/cfg.mk \
		ee_$(DIST)/pkg/kernel/frsh/inc \
		ee_$(DIST)/pkg/kernel/frsh/inc/ee_internal.h \
		ee_$(DIST)/pkg/kernel/frsh/src \
		ee_$(DIST)/pkg/kernel/frsh/src/ee_cap.c \
		ee_$(DIST)/pkg/kernel/frsh/src/ee_dlcheck.c \
		ee_$(DIST)/pkg/kernel/frsh/src/ee_end_budget.c \
		ee_$(DIST)/pkg/kernel/frsh/src/ee_end_recharging.c \
		ee_$(DIST)/pkg/kernel/frsh/src/ee_frsh_bind.c \
		ee_$(DIST)/pkg/kernel/frsh/src/ee_frsh_bind_utils.c \
		ee_$(DIST)/pkg/kernel/frsh/src/ee_frsh_contracts.c \
		ee_$(DIST)/pkg/kernel/frsh/src/ee_frsh_getcontract.c \
		ee_$(DIST)/pkg/kernel/frsh/src/ee_frsh_getvresid.c \
		ee_$(DIST)/pkg/kernel/frsh/src/ee_frsh_init.c \
		ee_$(DIST)/pkg/kernel/frsh/src/ee_frsh_strerror.c \
		ee_$(DIST)/pkg/kernel/frsh/src/ee_frsh_syncobj_signal.c \
		ee_$(DIST)/pkg/kernel/frsh/src/ee_frsh_syncobj_timedwait.c \
		ee_$(DIST)/pkg/kernel/frsh/src/ee_frsh_syncobj_wait.c \
		ee_$(DIST)/pkg/kernel/frsh/src/ee_frsh_syncobj_wait_utils.c \
		ee_$(DIST)/pkg/kernel/frsh/src/ee_frsh_syncobj_waittimeout.c \
		ee_$(DIST)/pkg/kernel/frsh/src/ee_frsh_timers.c \
		ee_$(DIST)/pkg/kernel/frsh/src/ee_frsh_unbind.c \
		ee_$(DIST)/pkg/kernel/frsh/src/ee_gettime.c \
		ee_$(DIST)/pkg/kernel/frsh/src/ee_irq_sc.c \
		ee_$(DIST)/pkg/kernel/frsh/src/ee_mutex.c \
		ee_$(DIST)/pkg/kernel/frsh/src/ee_rcg_inser.c \
		ee_$(DIST)/pkg/kernel/frsh/src/ee_rq_extract.c \
		ee_$(DIST)/pkg/kernel/frsh/src/ee_rq_inser.c \
		ee_$(DIST)/pkg/kernel/frsh/src/ee_schedule.c \
		ee_$(DIST)/pkg/kernel/frsh/src/ee_thact.c \
		ee_$(DIST)/pkg/kernel/frsh/src/ee_thendin.c
	@echo OPT __FRSH__ up2date.


#
#
# COM
#
#

distrib_opt___CABS__:: \
		ee_$(DIST)/pkg/com/cabs/cfg \
		ee_$(DIST)/pkg/com/cabs/cfg/cfg.mk \
		ee_$(DIST)/pkg/com/cabs/src \
		ee_$(DIST)/pkg/com/cabs/src/ee_cabs.c
	@echo OPT __CABS__ up2date.



#
#
# CONTRIB
#
#

distrib_opt___ATMEL802154__:: \
		ee_$(DIST)/contrib \
		ee_$(DIST)/contrib/readme.txt \
		ee_$(DIST)/contrib/atmel802_15_4 \
		ee_$(DIST)/contrib/atmel802_15_4/cfg \
		ee_$(DIST)/contrib/atmel802_15_4/cfg/cfg.mk \
		ee_$(DIST)/contrib/atmel802_15_4/cfg/libcfg.mk \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/bios \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/bios/bios.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/bios/board_rdk230.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/bios/crc16.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/bios/hif_rf230.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/bios/queue.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/bios/timer.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/bios/timer_m128.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/inc \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/inc/avrtypes.h \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/inc/bios.h \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/inc/board.h \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/inc/board_def_rdk230.h \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/inc/cmdif.h \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/inc/data_structures.h \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/inc/mac.h \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/inc/mcu_types.h \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/inc/msg_const.h \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/inc/msg_types.h \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/inc/phy230_registermap.h \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/inc/phy.h \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/inc/project.h \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/inc/rf230.h \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/inc/timer_const.h \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/inc/version.h \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/mac \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/mac/associate.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/mac/beacon.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/mac/buffer.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/mac/csma_ca.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/mac/data_ind.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/mac/data_req.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/mac/disassociate.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/mac/mcps_data.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/mac/misc.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/mac/orphan.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/mac/pib.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/mac/plme_conf.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/mac/poll.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/mac/process_ack_frame.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/mac/process_beacon_frame.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/mac/rx_enable.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/mac/scan.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/mac/start.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/mac/sync.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/mac/tx_coord_realignment_command.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/api_mac.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/callback_wrapper.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/cmdif.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/dispatcher.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/usr_hal_radio_irq.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/usr_mcps_data_conf.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/usr_mcps_data_ind.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/usr_mcps_purge_conf.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/usr_mlme_associate_conf.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/usr_mlme_associate_ind.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/usr_mlme_beacon_notify_ind.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/usr_mlme_comm_status_ind.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/usr_mlme_disassociate_conf.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/usr_mlme_disassociate_ind.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/usr_mlme_get_conf.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/usr_mlme_gts_conf.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/usr_mlme_gts_ind.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/usr_mlme_orphan_ind.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/usr_mlme_poll_conf.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/usr_mlme_reset_conf.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/usr_mlme_rx_enable_conf.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/usr_mlme_scan_conf.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/usr_mlme_set_conf.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/usr_mlme_start_conf.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/usr_mlme_sync_loss_ind.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/usr_pd_data_conf.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/usr_pd_data_ind.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/usr_plme_cca_conf.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/usr_plme_ed_conf.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/usr_plme_get_conf.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/usr_plme_set_conf.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/usr_plme_set_trx_state_conf.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/misc/usr_timer_trigger.c \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/phy \
		ee_$(DIST)/contrib/atmel802_15_4/libsrc/phy/phy230.c \
		ee_$(DIST)/contrib/atmel802_15_4/inc \
		ee_$(DIST)/contrib/atmel802_15_4/inc/def.h \
		ee_$(DIST)/contrib/atmel802_15_4/inc/ee_confMac.h \
		ee_$(DIST)/contrib/atmel802_15_4/inc/ieee_const.h \
		ee_$(DIST)/contrib/atmel802_15_4/inc/wpan_defines.h \
		ee_$(DIST)/contrib/atmel802_15_4/inc/wpan_mac.h

distrib_opt___CONTRIB__:: \
		ee_$(DIST)/contrib \
		ee_$(DIST)/contrib/readme.txt \
		ee_$(DIST)/contrib/console \
		ee_$(DIST)/contrib/console/doxyconf \
		ee_$(DIST)/contrib/console/cfg \
		ee_$(DIST)/contrib/console/cfg/cfg.mk \
		ee_$(DIST)/contrib/console/cfg/libcfg.mk \
		ee_$(DIST)/contrib/console/inc \
		ee_$(DIST)/contrib/console/inc/conq.h \
		ee_$(DIST)/contrib/console/inc/console.h \
		ee_$(DIST)/contrib/console/inc/console_serial.h \
		ee_$(DIST)/contrib/console/inc/hal \
		ee_$(DIST)/contrib/console/inc/hal/arch.h \
		ee_$(DIST)/contrib/console/inc/hal/compiler.h \
		ee_$(DIST)/contrib/console/inc/hal/pic30.h \
		ee_$(DIST)/contrib/console/inc/hal/avr5.h \
		ee_$(DIST)/contrib/console/src \
		ee_$(DIST)/contrib/console/src/conq.c \
		ee_$(DIST)/contrib/console/src/console.c \
		ee_$(DIST)/contrib/console/src/console_serial.c \
		ee_$(DIST)/contrib/console/src/hal \
		ee_$(DIST)/contrib/console/src/hal/pic30.c \
		ee_$(DIST)/contrib/console/src/hal/avr5.c \
		ee_$(DIST)/contrib/memory \
		ee_$(DIST)/contrib/memory/doxyconf \
		ee_$(DIST)/contrib/memory/cfg \
		ee_$(DIST)/contrib/memory/cfg/libcfg.mk \
		ee_$(DIST)/contrib/memory/inc \
		ee_$(DIST)/contrib/memory/inc/cqueue.h \
		ee_$(DIST)/contrib/memory/inc/arch \
		ee_$(DIST)/contrib/memory/inc/arch/mem_compiler.h \
		ee_$(DIST)/contrib/memory/inc/arch/mem_compiler_ee.h \
		ee_$(DIST)/contrib/memory/inc/arch/mem_compiler_c30.h \
		ee_$(DIST)/contrib/memory/libsrc \
		ee_$(DIST)/contrib/memory/libsrc/cqueue.c

distrib_opt___DRIVERS__:: \
		ee_$(DIST)/contrib/drivers \
		ee_$(DIST)/contrib/drivers/cfg \
		ee_$(DIST)/contrib/drivers/cfg/contrib.mk \
		ee_$(DIST)/contrib/drivers/radio \
		ee_$(DIST)/contrib/drivers/radio/cc2420 \
		ee_$(DIST)/contrib/drivers/radio/cc2420/doxyconf \
		ee_$(DIST)/contrib/drivers/radio/cc2420/cfg \
		ee_$(DIST)/contrib/drivers/radio/cc2420/cfg/cfg.mk \
		ee_$(DIST)/contrib/drivers/radio/cc2420/cfg/libcfg.mk \
		ee_$(DIST)/contrib/drivers/radio/cc2420/inc \
		ee_$(DIST)/contrib/drivers/radio/cc2420/inc/cc2420.h \
		ee_$(DIST)/contrib/drivers/radio/cc2420/inc/cc2420_compiler.h \
		ee_$(DIST)/contrib/drivers/radio/cc2420/inc/cc2420_compiler_c30.h \
		ee_$(DIST)/contrib/drivers/radio/cc2420/inc/cc2420_compiler_ee.h \
		ee_$(DIST)/contrib/drivers/radio/cc2420/inc/cc2420_hal.h \
		ee_$(DIST)/contrib/drivers/radio/cc2420/inc/cc2420_hal_ee.h \
		ee_$(DIST)/contrib/drivers/radio/cc2420/src \
		ee_$(DIST)/contrib/drivers/radio/cc2420/src/cc2420.c \
		ee_$(DIST)/contrib/drivers/radio/cc2420/src/cc2420_hal_ee.c

distrib_opt___OPENZB__:: \
		ee_$(DIST)/contrib/network \
		ee_$(DIST)/contrib/network/cfg \
		ee_$(DIST)/contrib/network/cfg/contrib.mk \
		ee_$(DIST)/contrib/network/openzb \
		ee_$(DIST)/contrib/network/openzb/doxyconf \
		ee_$(DIST)/contrib/network/openzb/cfg \
		ee_$(DIST)/contrib/network/openzb/cfg/cfg.mk \
		ee_$(DIST)/contrib/network/openzb/cfg/libcfg.mk \
		ee_$(DIST)/contrib/network/openzb/inc \
		ee_$(DIST)/contrib/network/openzb/inc/ieee802154.h \
		ee_$(DIST)/contrib/network/openzb/inc/openzb.h \
		ee_$(DIST)/contrib/network/openzb/inc/hal \
		ee_$(DIST)/contrib/network/openzb/inc/hal/ozb_compiler.h \
		ee_$(DIST)/contrib/network/openzb/inc/hal/ozb_compiler_c30.h \
		ee_$(DIST)/contrib/network/openzb/inc/hal/ozb_compiler_ee.h \
		ee_$(DIST)/contrib/network/openzb/inc/hal/ozb_radio.h \
		ee_$(DIST)/contrib/network/openzb/inc/hal/ozb_radio_cc2420.h \
		ee_$(DIST)/contrib/network/openzb/inc/hal/ozb_rand.h \
		ee_$(DIST)/contrib/network/openzb/inc/hal/ozb_timer.h \
		ee_$(DIST)/contrib/network/openzb/inc/hal/ozb_timer_dspic30.h \
		ee_$(DIST)/contrib/network/openzb/inc/kal \
		ee_$(DIST)/contrib/network/openzb/inc/kal/ozb_kal.h \
		ee_$(DIST)/contrib/network/openzb/inc/kal/ozb_kal_erika.h \
		ee_$(DIST)/contrib/network/openzb/inc/mac \
		ee_$(DIST)/contrib/network/openzb/inc/mac/ozb_mac.h \
		ee_$(DIST)/contrib/network/openzb/inc/mac/ozb_mac_const.h \
		ee_$(DIST)/contrib/network/openzb/inc/mac/ozb_mac_internal.h \
		ee_$(DIST)/contrib/network/openzb/inc/mac/ozb_mac_mcps.h \
		ee_$(DIST)/contrib/network/openzb/inc/mac/ozb_mac_mlme.h \
		ee_$(DIST)/contrib/network/openzb/inc/mac/ozb_mac_mutexes.h \
		ee_$(DIST)/contrib/network/openzb/inc/mac/ozb_mac_types.h \
		ee_$(DIST)/contrib/network/openzb/inc/net \
		ee_$(DIST)/contrib/network/openzb/inc/net/ozb_net.h \
		ee_$(DIST)/contrib/network/openzb/inc/net/ozb_net_internal.h \
		ee_$(DIST)/contrib/network/openzb/inc/phy \
		ee_$(DIST)/contrib/network/openzb/inc/phy/ozb_phy.h \
		ee_$(DIST)/contrib/network/openzb/inc/phy/ozb_phy_const.h \
		ee_$(DIST)/contrib/network/openzb/inc/phy/ozb_phy_internal.h \
		ee_$(DIST)/contrib/network/openzb/inc/phy/ozb_phy_pd.h \
		ee_$(DIST)/contrib/network/openzb/inc/phy/ozb_phy_plme.h \
		ee_$(DIST)/contrib/network/openzb/inc/phy/ozb_phy_types.h \
		ee_$(DIST)/contrib/network/openzb/inc/util \
		ee_$(DIST)/contrib/network/openzb/inc/util/ozb_debug.h \
		ee_$(DIST)/contrib/network/openzb/inc/util/ozb_memory.h \
		ee_$(DIST)/contrib/network/openzb/src \
		ee_$(DIST)/contrib/network/openzb/src/hal \
		ee_$(DIST)/contrib/network/openzb/src/hal/ozb_radio_cc2420.c \
		ee_$(DIST)/contrib/network/openzb/src/hal/ozb_timer_dspic30.c \
		ee_$(DIST)/contrib/network/openzb/src/kal \
		ee_$(DIST)/contrib/network/openzb/src/kal/ozb_kal_erika.c \
		ee_$(DIST)/contrib/network/openzb/src/mac \
		ee_$(DIST)/contrib/network/openzb/src/mac/ozb_mac.c \
		ee_$(DIST)/contrib/network/openzb/src/mac/ozb_mac_gts.c \
		ee_$(DIST)/contrib/network/openzb/src/mac/ozb_mac_mcps.c \
		ee_$(DIST)/contrib/network/openzb/src/mac/ozb_mac_mlme.c \
		ee_$(DIST)/contrib/network/openzb/src/mac/ozb_mac_superframe.c \
		ee_$(DIST)/contrib/network/openzb/src/net \
		ee_$(DIST)/contrib/network/openzb/src/net/ozb_net_mac_events.c \
		ee_$(DIST)/contrib/network/openzb/src/phy \
		ee_$(DIST)/contrib/network/openzb/src/phy/ozb_phy.c \
		ee_$(DIST)/contrib/network/openzb/src/util \
		ee_$(DIST)/contrib/network/openzb/src/util/ozb_debug.c

distrib_opt___MIWIP2P__:: \
		ee_$(DIST)/contrib/MiWiP2P \
		ee_$(DIST)/contrib/MiWiP2P/cfg \
		ee_$(DIST)/contrib/MiWiP2P/cfg/cfg.mk \
		ee_$(DIST)/contrib/MiWiP2P/cfg/libcfg.mk \
		ee_$(DIST)/contrib/MiWiP2P/inc \
		ee_$(DIST)/contrib/MiWiP2P/inc/compiler.h \
		ee_$(DIST)/contrib/MiWiP2P/inc/GenericTypeDefs.h \
		ee_$(DIST)/contrib/MiWiP2P/inc/MRF24J40.h \
		ee_$(DIST)/contrib/MiWiP2P/inc/P2P.h \
		ee_$(DIST)/contrib/MiWiP2P/inc/radio_spi.h \
		ee_$(DIST)/contrib/MiWiP2P/inc/SymbolTime.h \
		ee_$(DIST)/contrib/MiWiP2P/libsrc \
		ee_$(DIST)/contrib/MiWiP2P/libsrc/P2P.c \
		ee_$(DIST)/contrib/MiWiP2P/libsrc/radio_spi.c \
		ee_$(DIST)/contrib/MiWiP2P/libsrc/serv_funct.c \
		ee_$(DIST)/contrib/MiWiP2P/libsrc/SymbolTime.c

distrib_opt___SCICOS__:: \
		ee_$(DIST)/contrib/scicos \
		ee_$(DIST)/contrib/scicos/readme.txt \
		ee_$(DIST)/contrib/scicos/cfg \
		ee_$(DIST)/contrib/scicos/cfg/cfg.mk \
		ee_$(DIST)/contrib/scicos/cfg/libcfg.mk \
		ee_$(DIST)/contrib/scicos/libsrc \
		ee_$(DIST)/contrib/scicos/libsrc/core \
		ee_$(DIST)/contrib/scicos/libsrc/core/absolute_value.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/backlash.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/bit_clear_16.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/bit_clear_32.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/bit_clear_8.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/bit_set_16.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/bit_set_32.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/bit_set_8.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/canimxy.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/cmscope.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/convert.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/counter.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/cscope.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/cscopexy.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/cscopxy.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/csslti4.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/cstblk4.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/cstblk4_m.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/deadband.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/delay4.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/delay4_i16.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/delay4_i32.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/delay4_i8.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/delay4_ui16.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/delay4_ui32.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/delay4_ui8.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/deriv.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/dmmul.h \
		ee_$(DIST)/contrib/scicos/libsrc/core/dmmul.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/dmmul1.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/dollar4.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/dollar4_m.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/dsslti4.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/evaluate_expr.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/expblk_m.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_16_LH.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_16_LSB.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_16_MSB0.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_16_MSB1.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_16_RB0.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_16_RB1.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_16_UH0.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_16_UH1.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_32_LH.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_32_LSB.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_32_MSB0.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_32_MSB1.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_32_RB0.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_32_RB1.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_32_UH0.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_32_UH1.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_8_LH.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_8_LSB.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_8_MSB0.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_8_MSB1.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_8_RB0.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_8_RB1.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_8_UH0.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_8_UH1.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_u16_MSB1.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_u16_RB1.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_u16_UH1.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_u32_MSB1.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_u32_RB1.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_u32_UH1.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_u8_MSB1.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_u8_RB1.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extract_bit_u8_UH1.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/extractor.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/gainblk.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/gainblk_i16e.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/gainblk_i16n.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/gainblk_i16s.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/gainblk_i32e.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/gainblk_i32n.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/gainblk_i32s.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/gainblk_i8e.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/gainblk_i8n.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/gainblk_i8s.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/gainblk_ui16e.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/gainblk_ui16n.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/gainblk_ui16s.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/gainblk_ui32e.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/gainblk_ui32n.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/gainblk_ui32s.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/gainblk_ui8e.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/gainblk_ui8n.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/gainblk_ui8s.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/get_phase_simulation.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/hystheresis.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/integral_func.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/integralz_func.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/invblk4.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/logic.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/machine.h \
		ee_$(DIST)/contrib/scicos/libsrc/core/matmul2_m.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/matmul_i16e.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/matmul_i16n.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/matmul_i16s.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/matmul_i32e.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/matmul_i32n.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/matmul_i32s.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/matmul_i8e.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/matmul_i8n.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/matmul_i8s.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/matmul_m.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/matmul_ui16e.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/matmul_ui16n.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/matmul_ui16s.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/matmul_ui32e.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/matmul_ui32n.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/matmul_ui32s.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/matmul_ui8e.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/matmul_ui8n.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/matmul_ui8s.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/minmax.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/modulo_count.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/mswitch.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/multiplex.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/plusblk.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/prod.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/product.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/ratelimiter.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/removed \
		ee_$(DIST)/contrib/scicos/libsrc/core/removed/readf4.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/removed/realtime.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/samphold4_m.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/satur.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/scalar2vector.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/sci_mem_alloc.h \
		ee_$(DIST)/contrib/scicos/libsrc/core/scicos_block.h \
		ee_$(DIST)/contrib/scicos/libsrc/core/scicos_block4.h \
		ee_$(DIST)/contrib/scicos/libsrc/core/scicos_free.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/scicos_malloc.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/scicos_USB.h \
		ee_$(DIST)/contrib/scicos/libsrc/core/sciprint.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/set_block_error.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/shift_16_LA.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/shift_16_LC.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/shift_16_RA.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/shift_16_RC.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/shift_32_LA.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/shift_32_LC.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/shift_32_RA.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/shift_32_RC.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/shift_8_LA.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/shift_8_LC.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/shift_8_RA.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/shift_8_RC.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/shift_u16_RA.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/shift_u32_RA.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/shift_u8_RA.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/signum.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/summation.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/summation_i16e.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/summation_i16n.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/summation_i16s.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/summation_i32e.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/summation_i32n.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/summation_i32s.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/summation_i8e.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/summation_i8n.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/summation_i8s.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/summation_ui16e.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/summation_ui16n.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/summation_ui16s.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/summation_ui32e.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/summation_ui32n.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/summation_ui32s.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/summation_ui8e.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/summation_ui8n.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/summation_ui8s.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/summation_z.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/switch2_m.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/switchn.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/time_delay.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/variable_delay.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/ScilabLib \
		ee_$(DIST)/contrib/scicos/libsrc/core/ScilabLib/dmmul.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/ScilabLib/dmmul1.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/ScilabLib/get_phase_simulation.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/ScilabLib/scicos_free.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/ScilabLib/scicos_malloc.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/ScilabLib/sciprint.c \
		ee_$(DIST)/contrib/scicos/libsrc/core/ScilabLib/set_block_error.c \
		ee_$(DIST)/contrib/scicos/libsrc/rt \
		ee_$(DIST)/contrib/scicos/libsrc/rt/rt_randm.c \
		ee_$(DIST)/contrib/scicos/libsrc/rt/rt_sinus.c \
		ee_$(DIST)/contrib/scicos/libsrc/rt/rt_square.c \
		ee_$(DIST)/contrib/scicos/libsrc/rt/rt_step.c \
		ee_$(DIST)/contrib/scicos/readme.txt \
		ee_$(DIST)/contrib/scicos/src \
		ee_$(DIST)/contrib/scicos/src/pic30 \
		ee_$(DIST)/contrib/scicos/src/pic30/communication \
		ee_$(DIST)/contrib/scicos/src/pic30/communication/flex_serial_receive.c \
		ee_$(DIST)/contrib/scicos/src/pic30/communication/flex_serial_send.c \
		ee_$(DIST)/contrib/scicos/src/pic30/communication/flex_usb_receive.c \
		ee_$(DIST)/contrib/scicos/src/pic30/communication/flex_usb_send.c \
		ee_$(DIST)/contrib/scicos/src/pic30/communication/flex_zigbee_receive.c \
		ee_$(DIST)/contrib/scicos/src/pic30/communication/flex_zigbee_send.c \
		ee_$(DIST)/contrib/scicos/src/pic30/flex_adc.c \
		ee_$(DIST)/contrib/scicos/src/pic30/flex_adcin.c \
		ee_$(DIST)/contrib/scicos/src/pic30/flex_buzzer.c \
		ee_$(DIST)/contrib/scicos/src/pic30/flex_debug.c \
		ee_$(DIST)/contrib/scicos/src/pic30/flex_gpin.c \
		ee_$(DIST)/contrib/scicos/src/pic30/flex_gpout.c \
		ee_$(DIST)/contrib/scicos/src/pic30/flex_lcd.c \
		ee_$(DIST)/contrib/scicos/src/pic30/flex_led.c \
		ee_$(DIST)/contrib/scicos/src/pic30/flex_pwm.c \
		ee_$(DIST)/contrib/scicos/src/pic30/flex_dmb_adc.c \
		ee_$(DIST)/contrib/scicos/src/pic30/flex_dmb_button.c \
		ee_$(DIST)/contrib/scicos/src/pic30/flex_dmb_buzzer.c \
		ee_$(DIST)/contrib/scicos/src/pic30/flex_dmb_dac.c \
		ee_$(DIST)/contrib/scicos/src/pic30/flex_dmb_encoder.c \
		ee_$(DIST)/contrib/scicos/src/pic30/flex_dmb_gpin.c \
		ee_$(DIST)/contrib/scicos/src/pic30/flex_dmb_gpout.c \
		ee_$(DIST)/contrib/scicos/src/pic30/flex_dmb_inertial.c \
		ee_$(DIST)/contrib/scicos/src/pic30/flex_dmb_lcd.c \
		ee_$(DIST)/contrib/scicos/src/pic30/flex_dmb_ldr.c \
		ee_$(DIST)/contrib/scicos/src/pic30/flex_dmb_leds.c \
		ee_$(DIST)/contrib/scicos/src/pic30/flex_dmb_ntc.c \
		ee_$(DIST)/contrib/scicos/src/pic30/flex_dmb_potin.c \
		ee_$(DIST)/contrib/scicos/src/pic30/flex_dmb_pwm.c \

#		ee_$(DIST)/contrib/scicos/src/nios2 \
#		ee_$(DIST)/contrib/scicos/src/nios2/button.c \
#		ee_$(DIST)/contrib/scicos/src/nios2/led.c \
#		ee_$(DIST)/contrib/scicos/src/nios2/sevenseg.c \


distrib_opt___LIB_IEEE802154__:: \
		ee_$(DIST)/contrib/ieee802154/cfg \
		ee_$(DIST)/contrib/ieee802154/libsrc/common \
		ee_$(DIST)/contrib/ieee802154/libsrc/ieee802154alarms \
		ee_$(DIST)/contrib/ieee802154/libsrc/hal \
		ee_$(DIST)/contrib/ieee802154/libsrc/phy \
		ee_$(DIST)/contrib/ieee802154/libsrc/mac \
		ee_$(DIST)/contrib/ieee802154/libsrc/nwl \
		ee_$(DIST)/contrib/ieee802154/cfg/cfg.mk \
		ee_$(DIST)/contrib/ieee802154/cfg/libcfg.mk \
		ee_$(DIST)/contrib/ieee802154/libsrc/phy/PD_DATA.c \
		ee_$(DIST)/contrib/ieee802154/libsrc/phy/PLME_CCA.c \
		ee_$(DIST)/contrib/ieee802154/libsrc/phy/PLME_ED.c \
		ee_$(DIST)/contrib/ieee802154/libsrc/phy/PLME_GET.c \
		ee_$(DIST)/contrib/ieee802154/libsrc/phy/PLME_SET.c \
		ee_$(DIST)/contrib/ieee802154/libsrc/phy/PLME_SET_TRX_STATE.c \
		ee_$(DIST)/contrib/ieee802154/libsrc/phy/Phy.c \
		ee_$(DIST)/contrib/ieee802154/libsrc/mac/Mac.c \
		ee_$(DIST)/contrib/ieee802154/libsrc/mac/MLME_START.c \
		ee_$(DIST)/contrib/ieee802154/libsrc/mac/MLME_GET.c \
		ee_$(DIST)/contrib/ieee802154/libsrc/mac/MLME_SET.c \
		ee_$(DIST)/contrib/ieee802154/libsrc/mac/MLME_ASSOCIATE.c \
		ee_$(DIST)/contrib/ieee802154/libsrc/mac/MCPS_DATA.c \
		ee_$(DIST)/contrib/ieee802154/libsrc/mac/mac_func.c \
		ee_$(DIST)/contrib/ieee802154/libsrc/nwl/Nwl.c \
		ee_$(DIST)/contrib/ieee802154/libsrc/ieee802154alarms/ieee802154alarms.c \
		ee_$(DIST)/contrib/ieee802154/libsrc/hal/hal_cc2420.c \
		ee_$(DIST)/contrib/ieee802154/libsrc/hal/hal_interrupts.c \
		ee_$(DIST)/contrib/ieee802154/libsrc/common/cc2420.c \
		ee_$(DIST)/contrib/ieee802154/libsrc/common/console.c \
		ee_$(DIST)/contrib/ieee802154/libsrc/common/ee_radio_spi.c \
		ee_$(DIST)/contrib/ieee802154/libsrc/common/eeuart.c \
		ee_$(DIST)/contrib/ieee802154/libsrc/common/netbuff.c \
		ee_$(DIST)/contrib/ieee802154/libsrc/common/queue.c 

#
#
# AVR5 EXAMPLES
#
#

distrib_opt___AVR5_EXAMPLES__:: \
		ee_$(DIST)/examples/avr5/avr5_blink \
		ee_$(DIST)/examples/avr5/avr5_blink/template.xml \
		ee_$(DIST)/examples/avr5/avr5_blink/code.c \
		ee_$(DIST)/examples/avr5/avr5_blink/conf.oil \
		\
		ee_$(DIST)/examples/avr5/avr5_blink1 \
		ee_$(DIST)/examples/avr5/avr5_blink1/template.xml \
		ee_$(DIST)/examples/avr5/avr5_blink1/code.c \
		ee_$(DIST)/examples/avr5/avr5_blink1/conf.oil \
		\
		ee_$(DIST)/examples/avr5/avr5_serial \
		ee_$(DIST)/examples/avr5/avr5_serial/template.xml \
		ee_$(DIST)/examples/avr5/avr5_serial/code.c \
		ee_$(DIST)/examples/avr5/avr5_serial/conf.oil \
		\
		ee_$(DIST)/examples/avr5/avr5_console \
		ee_$(DIST)/examples/avr5/avr5_console/template.xml \
		ee_$(DIST)/examples/avr5/avr5_console/code.c \
		ee_$(DIST)/examples/avr5/avr5_console/conf.oil




#
#
# PIC30 EXAMPLES
#
#

distrib_opt___PIC30_EXAMPLES__:: \
		ee_$(DIST)/examples/pic30/pic30_ant \
		ee_$(DIST)/examples/pic30/pic30_ant/build.xml \
		ee_$(DIST)/examples/pic30/pic30_ant/code.c \
		ee_$(DIST)/examples/pic30/pic30_ant/compile.bat \
		ee_$(DIST)/examples/pic30/pic30_ant/conf.oil \
		ee_$(DIST)/examples/pic30/pic30_ant/template.xml \
		\
		ee_$(DIST)/examples/pic30/pic30_dspicdem11_base \
		ee_$(DIST)/examples/pic30/pic30_dspicdem11_base/code.c \
		ee_$(DIST)/examples/pic30/pic30_dspicdem11_base/conf.oil \
		ee_$(DIST)/examples/pic30/pic30_dspicdem11_base/template.xml \
		\
		ee_$(DIST)/examples/pic30/pic30_Embedded_World_2007 \
		ee_$(DIST)/examples/pic30/pic30_Embedded_World_2007/code.c \
		ee_$(DIST)/examples/pic30/pic30_Embedded_World_2007/conf.oil \
		ee_$(DIST)/examples/pic30/pic30_Embedded_World_2007/sensors.c \
		ee_$(DIST)/examples/pic30/pic30_Embedded_World_2007/sensors.h \
		ee_$(DIST)/examples/pic30/pic30_Embedded_World_2007/template.xml \
		ee_$(DIST)/examples/pic30/pic30_Embedded_World_2007/EW07.sch \
		ee_$(DIST)/examples/pic30/pic30_Embedded_World_2007/EW07.brd \
		ee_$(DIST)/examples/pic30/pic30_Embedded_World_2007/photo.jpg \
		ee_$(DIST)/examples/pic30/pic30_Embedded_World_2007/readme.txt \
		\
		ee_$(DIST)/examples/pic30/pic30_empty \
		ee_$(DIST)/examples/pic30/pic30_empty/code.c \
		ee_$(DIST)/examples/pic30/pic30_empty/conf.oil \
		ee_$(DIST)/examples/pic30/pic30_empty/template.xml \
		\
		ee_$(DIST)/examples/pic30/pic30_explorer16_base \
		ee_$(DIST)/examples/pic30/pic30_explorer16_base/code.c \
		ee_$(DIST)/examples/pic30/pic30_explorer16_base/conf.oil \
		ee_$(DIST)/examples/pic30/pic30_explorer16_base/template.xml \
		\
		ee_$(DIST)/examples/pic30/pic30_explorer16_resource_lcd \
		ee_$(DIST)/examples/pic30/pic30_explorer16_resource_lcd/code.c \
		ee_$(DIST)/examples/pic30/pic30_explorer16_resource_lcd/conf.oil \
		ee_$(DIST)/examples/pic30/pic30_explorer16_resource_lcd/template.xml \
		ee_$(DIST)/examples/pic30/pic30_explorer16_resource_lcd/readme.txt \
		\
		ee_$(DIST)/examples/pic30/pic30_Firmware_February \
		ee_$(DIST)/examples/pic30/pic30_Firmware_February/code.c \
		ee_$(DIST)/examples/pic30/pic30_Firmware_February/conf.oil \
		ee_$(DIST)/examples/pic30/pic30_Firmware_February/template.xml \
		ee_$(DIST)/examples/pic30/pic30_Firmware_February/readme.txt \
		\
		ee_$(DIST)/examples/pic30/pic30_libs \
		ee_$(DIST)/examples/pic30/pic30_libs/conf.oil \
		ee_$(DIST)/examples/pic30/pic30_libs/template.xml \
		\
		ee_$(DIST)/examples/pic30/pic30_sem \
		ee_$(DIST)/examples/pic30/pic30_sem/code.c \
		ee_$(DIST)/examples/pic30/pic30_sem/conf.oil \
		ee_$(DIST)/examples/pic30/pic30_sem/template.xml \
		ee_$(DIST)/examples/pic30/pic30_sem/readme.txt \
		\
		ee_$(DIST)/examples/pic30/pic30_res_scheduler \
		ee_$(DIST)/examples/pic30/pic30_res_scheduler/code.c \
		ee_$(DIST)/examples/pic30/pic30_res_scheduler/conf.oil \
		ee_$(DIST)/examples/pic30/pic30_res_scheduler/template.xml \
		ee_$(DIST)/examples/pic30/pic30_res_scheduler/readme.txt \
		\
		ee_$(DIST)/examples/pic30/pic30_scicos \
		ee_$(DIST)/examples/pic30/pic30_scicos/dspic_main.c \
		ee_$(DIST)/examples/pic30/pic30_scicos/template.xml \
		ee_$(DIST)/examples/pic30/pic30_scicos/conf_scicos.oil \
		\
		ee_$(DIST)/examples/pic30/pic30_scicos_openzb_coordinator \
		ee_$(DIST)/examples/pic30/pic30_scicos_openzb_coordinator/dspic_main.c \
		ee_$(DIST)/examples/pic30/pic30_scicos_openzb_coordinator/types.h \
		ee_$(DIST)/examples/pic30/pic30_scicos_openzb_coordinator/template.xml \
#		ee_$(DIST)/examples/pic30/pic30_scicos_openzb_coordinator/scicos_openZB.h \
		ee_$(DIST)/examples/pic30/pic30_scicos_openzb_coordinator/conf_scicos.oil \
		\
		ee_$(DIST)/examples/pic30/pic30_scicos_openzb_device \
		ee_$(DIST)/examples/pic30/pic30_scicos_openzb_device/dspic_main.c \
		ee_$(DIST)/examples/pic30/pic30_scicos_openzb_device/types.h \
		ee_$(DIST)/examples/pic30/pic30_scicos_openzb_device/template.xml \
#		ee_$(DIST)/examples/pic30/pic30_scicos_openzb_device/scicos_openZB.h \
		ee_$(DIST)/examples/pic30/pic30_scicos_openzb_device/conf_scicos.oil \
		\
		ee_$(DIST)/examples/pic30/pic30_openzb_demo \
		ee_$(DIST)/examples/pic30/pic30_openzb_demo/code.c \
		ee_$(DIST)/examples/pic30/pic30_openzb_demo/types.h \
		ee_$(DIST)/examples/pic30/pic30_openzb_demo/template.xml \
		ee_$(DIST)/examples/pic30/pic30_openzb_demo/conf.oil \
		\
		ee_$(DIST)/examples/pic30/pic30_serial \
		ee_$(DIST)/examples/pic30/pic30_serial/template.xml \
		ee_$(DIST)/examples/pic30/pic30_serial/code.c \
		ee_$(DIST)/examples/pic30/pic30_serial/conf.oil \
		ee_$(DIST)/examples/pic30/pic30_serial/eeuart.c \
		ee_$(DIST)/examples/pic30/pic30_serial/eeuart.h \
		\
		ee_$(DIST)/examples/pic30/pic30_edf_periodic \
		ee_$(DIST)/examples/pic30/pic30_edf_periodic/code.c \
		ee_$(DIST)/examples/pic30/pic30_edf_periodic/conf.oil \
		ee_$(DIST)/examples/pic30/pic30_edf_periodic/template.xml \
		ee_$(DIST)/examples/pic30/pic30_edf_periodic/readme.txt \
		\
		ee_$(DIST)/examples/pic30/pic30_DemoBoard_base \
		ee_$(DIST)/examples/pic30/pic30_DemoBoard_base/code.c \
		ee_$(DIST)/examples/pic30/pic30_DemoBoard_base/conf.oil \
		ee_$(DIST)/examples/pic30/pic30_DemoBoard_base/template.xml \
		\
		ee_$(DIST)/examples/pic30/pic30_DemoBoard_console \
		ee_$(DIST)/examples/pic30/pic30_DemoBoard_console/code.c \
		ee_$(DIST)/examples/pic30/pic30_DemoBoard_console/conf.oil \
		ee_$(DIST)/examples/pic30/pic30_DemoBoard_console/template.xml \
		\
		ee_$(DIST)/examples/pic30/pic30_oo_task \
		ee_$(DIST)/examples/pic30/pic30_oo_task/code.c \
		ee_$(DIST)/examples/pic30/pic30_oo_task/conf.oil \
		ee_$(DIST)/examples/pic30/pic30_oo_task/template.xml \
		\
		ee_$(DIST)/examples/pic30/pic30_oo_resource \
		ee_$(DIST)/examples/pic30/pic30_oo_resource/code.c \
		ee_$(DIST)/examples/pic30/pic30_oo_resource/conf.oil \
		ee_$(DIST)/examples/pic30/pic30_oo_resource/template.xml \
		\
		ee_$(DIST)/examples/pic30/pic30_oo_event \
		ee_$(DIST)/examples/pic30/pic30_oo_event/code.c \
		ee_$(DIST)/examples/pic30/pic30_oo_event/conf.oil \
		ee_$(DIST)/examples/pic30/pic30_oo_event/template.xml \
		\
		ee_$(DIST)/examples/pic30/pic30_miwip2p \
		ee_$(DIST)/examples/pic30/pic30_miwip2p/code.c \
		ee_$(DIST)/examples/pic30/pic30_miwip2p/conf.oil \
		ee_$(DIST)/examples/pic30/pic30_miwip2p/P2PDefs.h \
		ee_$(DIST)/examples/pic30/pic30_miwip2p/template.xml \
		\
		ee_$(DIST)/examples/pic30/pic30_frsh_coverage \
		ee_$(DIST)/examples/pic30/pic30_frsh_coverage/code.c \
		ee_$(DIST)/examples/pic30/pic30_frsh_coverage/conf.oil \
		ee_$(DIST)/examples/pic30/pic30_frsh_coverage/template.xml \


#
#
# Evaluator 7T EXAMPLES
#
#


ifeq ($(findstring __EVALUATOR7T__,$(ALLOPTIONS)) , __EVALUATOR7T__)
ifeq ($(findstring __OO_,$(ALLOPTIONS)) , __OO_)

#distrib_opt___EVALUATOR7T__:: \
#		ee_$(DIST)/examples/arm_evaluator7t/oil_task \
#		ee_$(DIST)/examples/arm_evaluator7t/oil_task/code.c \
#		ee_$(DIST)/examples/arm_evaluator7t/oil_task/conf.oil \
#		ee_$(DIST)/examples/arm_evaluator7t/oil_task/template.xml \
#		ee_$(DIST)/examples/arm_evaluator7t/oil_resource \
#		ee_$(DIST)/examples/arm_evaluator7t/oil_resource/code.c \
#		ee_$(DIST)/examples/arm_evaluator7t/oil_resource/conf.oil \
#		ee_$(DIST)/examples/arm_evaluator7t/oil_resource/template.xml \
#		ee_$(DIST)/examples/arm_evaluator7t/oil_event \
#		ee_$(DIST)/examples/arm_evaluator7t/oil_event/conf.oil \
#		ee_$(DIST)/examples/arm_evaluator7t/oil_event/conf.orti \
#		ee_$(DIST)/examples/arm_evaluator7t/oil_event/orti.c \
#		ee_$(DIST)/examples/arm_evaluator7t/oil_event/orti.cmm \
#		ee_$(DIST)/examples/arm_evaluator7t/oil_event/ortiperf.men \
#		ee_$(DIST)/examples/arm_evaluator7t/oil_event/template.xml \
#		ee_$(DIST)/examples/arm_evaluator7t/oil_event/code.c
#	@echo OPT Examples __EVALUATOR7T__ up2date.
endif
endif




#
#
# NIOS2 EXAMPLES
#
#

# Nios 2 demo_2cpu (tutorial in the ERIKA Enterprise reference manual)
distrib_opt___NIOS2_EXAMPLES__:: \
		ee_$(DIST)/examples/nios2/demo_2cpu \
		ee_$(DIST)/examples/nios2/demo_2cpu/conf.oil \
		ee_$(DIST)/examples/nios2/demo_2cpu/cpu0_main.c \
		ee_$(DIST)/examples/nios2/demo_2cpu/cpu1_main.c \
		ee_$(DIST)/examples/nios2/demo_2cpu/readme.txt \
		ee_$(DIST)/examples/nios2/demo_2cpu/resourcedata.c \
		ee_$(DIST)/examples/nios2/demo_2cpu/resourcedata.h \
		ee_$(DIST)/examples/nios2/demo_2cpu/shareddata.h \
		ee_$(DIST)/examples/nios2/demo_2cpu/shareddata.c \
		ee_$(DIST)/examples/nios2/demo_2cpu/task0.c \
		ee_$(DIST)/examples/nios2/demo_2cpu/task1.c \
		ee_$(DIST)/examples/nios2/demo_2cpu/task2.c \
		ee_$(DIST)/examples/nios2/demo_2cpu/template.xml
	@echo OPT Examples __NIOS2_EXAMPLES__ up2date - demo_2cpu

# Nios 2 demo_fifo (tutorial in the literature page)
distrib_opt___NIOS2_EXAMPLES__:: \
		ee_$(DIST)/examples/nios2/demo_fifo \
		ee_$(DIST)/examples/nios2/demo_fifo/buttonreadtask.c \
		ee_$(DIST)/examples/nios2/demo_fifo/conf.oil \
		ee_$(DIST)/examples/nios2/demo_fifo/cpu0_main.c \
		ee_$(DIST)/examples/nios2/demo_fifo/cpu1_main.c \
		ee_$(DIST)/examples/nios2/demo_fifo/fifo.c \
		ee_$(DIST)/examples/nios2/demo_fifo/fifo.h \
		ee_$(DIST)/examples/nios2/demo_fifo/myfifo.h \
		ee_$(DIST)/examples/nios2/demo_fifo/readtask.c \
		ee_$(DIST)/examples/nios2/demo_fifo/writetask.c \
		ee_$(DIST)/examples/nios2/demo_fifo/template.xml
	@echo OPT Examples __NIOS2_EXAMPLES__ up2date - demo_fifo

# Nios 2 demo_lwip (tutorial in the literature page)
#distrib_opt___NIOS2_EXAMPLES__:: \
#		ee_$(DIST)/examples/nios2/demo_lwip \
#		ee_$(DIST)/examples/nios2/demo_lwip/altera_avalon_lan91c111.c \
#		ee_$(DIST)/examples/nios2/demo_lwip/conf.oil \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwipopts.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip_web_server.c \
#		ee_$(DIST)/examples/nios2/demo_lwip/mac_addr.c \
#		ee_$(DIST)/examples/nios2/demo_lwip/ReadMe.txt \
#		ee_$(DIST)/examples/nios2/demo_lwip/apps \
#		ee_$(DIST)/examples/nios2/demo_lwip/apps/echo.c \
#		ee_$(DIST)/examples/nios2/demo_lwip/apps/echo.c.unix \
#		ee_$(DIST)/examples/nios2/demo_lwip/apps/echo.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/apps/fs.c \
#		ee_$(DIST)/examples/nios2/demo_lwip/apps/fs.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/apps/fs.zip \
#		ee_$(DIST)/examples/nios2/demo_lwip/apps/fsdata.c \
#		ee_$(DIST)/examples/nios2/demo_lwip/apps/fsdata.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/apps/httpd.c \
#		ee_$(DIST)/examples/nios2/demo_lwip/apps/httpd.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/apps/makefsdata \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1 \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/CHANGELOG \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/COPYING \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/doc \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/doc/contrib.txt \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/doc/rawapi.txt \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/doc/savannah.txt \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/doc/sys_arch.txt \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/FILES \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/README \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/core \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/core/dhcp.c \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/core/inet.c \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/core/ipv4 \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/core/ipv4/icmp.c \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/core/ipv4/ip.c \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/core/ipv4/ip_addr.c \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/core/ipv4/ip_frag.c \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/core/mem.c \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/core/memp.c \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/core/netif.c \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/core/pbuf.c \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/core/raw.c \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/core/stats.c \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/core/sys.c \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/core/tcp.c \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/core/tcp_in.c \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/core/tcp_out.c \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/core/udp.c \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/FILES \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/ipv4 \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/ipv4/lwip \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/ipv4/lwip/icmp.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/ipv4/lwip/inet.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/ipv4/lwip/ip.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/ipv4/lwip/ip_addr.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/ipv4/lwip/ip_frag.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/lwip \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/lwip/api.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/lwip/api_msg.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/lwip/arch.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/lwip/debug.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/lwip/def.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/lwip/dhcp.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/lwip/err.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/lwip/mem.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/lwip/memp.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/lwip/netif.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/lwip/opt.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/lwip/pbuf.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/lwip/raw.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/lwip/sio.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/lwip/snmp.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/lwip/sockets.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/lwip/stats.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/lwip/sys.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/lwip/tcp.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/lwip/tcpip.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/lwip/udp.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/netif \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/netif/etharp.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/netif/loopif.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/include/netif/slipif.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/netif \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/netif/etharp.c \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/netif/ethernetif.c.template \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/netif/FILES \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip-0.7.1/src/netif/loopif.c \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip4hal \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip4hal/include \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip4hal/include/arch \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip4hal/include/arch/cc.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip4hal/include/arch/cpu.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip4hal/include/arch/init.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip4hal/include/arch/lib.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip4hal/include/arch/perf.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip4hal/include/netif \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip4hal/include/netif/lan91c111if.h \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip4hal/lib.c \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip4hal/lwip_init.c \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip4hal/netif \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip4hal/netif/lan91c111if.c \
#		ee_$(DIST)/examples/nios2/demo_lwip/lwip4hal/perf.c
#	@echo OPT Examples __NIOS2_EXAMPLES__ up2date. \(demo_lwip\)

# Nios 2 demo_fifo (tutorial in the literature page)
distrib_opt___NIOS2_EXAMPLES__:: \
		ee_$(DIST)/examples/nios2/api_tutorial/task \
		ee_$(DIST)/examples/nios2/api_tutorial/task/code.c \
		ee_$(DIST)/examples/nios2/api_tutorial/task/conf.oil \
		ee_$(DIST)/examples/nios2/api_tutorial/task/template.xml \
		ee_$(DIST)/examples/nios2/api_tutorial/resource \
		ee_$(DIST)/examples/nios2/api_tutorial/resource/code.c \
		ee_$(DIST)/examples/nios2/api_tutorial/resource/conf.oil \
		ee_$(DIST)/examples/nios2/api_tutorial/resource/template.xml \
		ee_$(DIST)/examples/nios2/api_tutorial/event \
		ee_$(DIST)/examples/nios2/api_tutorial/event/code.c \
		ee_$(DIST)/examples/nios2/api_tutorial/event/conf.oil \
		ee_$(DIST)/examples/nios2/api_tutorial/event/template.xml
	@echo OPT Examples __NIOS2_EXAMPLES__ up2date - demo_api_examples
