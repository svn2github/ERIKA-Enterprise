#!/bin/bash
export ECLIPSE_HOME=/home/bruno/usr/ee2/eclipse
export RTDRUID_ECLIPSE_HOME=/home/bruno/gea_kern/xen/rt_tux_web_CLEAN/
export CORTEX_AX_XENPV_GCCDIR=/usr/

#make FAKE_DRUID=1 $@
make $@
