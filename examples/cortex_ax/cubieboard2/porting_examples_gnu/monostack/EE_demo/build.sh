#!/bin/bash
#export RTDRUID_ECLIPSE_HOME=/home/bruno/gea_kern/imx6/rt_druid/eclipse/
export RTDRUID_ECLIPSE_HOME=/home/bruno/gea_kern/imx6/rt_druid_new5/RT-Druid
export CORTEX_AX_GCCDIR=/home/bruno/gea_kern/z/gcc-4.4.4-glibc-2.11.1-multilib-1.0/arm-fsl-linux-gnueabi

#make FAKE_DRUID=1 $@
make $@
