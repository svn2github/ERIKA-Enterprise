#!/bin/bash
#export RTDRUID_ECLIPSE_HOME=/home/bruno/gea_kern/imx6/rt_druid/eclipse/
export RTDRUID_ECLIPSE_HOME=/home/ava/heavy/tirocinio/source/linux_plus_erika/imx6-linerika-erika/rtdruid/bin
export CORTEX_AX_XENPV_GCCDIR=/usr/

#make FAKE_DRUID=1 $@
make $@
