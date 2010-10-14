#!/bin/sh
for d in `ls -d */*/Debug`; do echo $d; cd $d; make clean; cd ../../..; done