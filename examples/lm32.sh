#!/bin/sh

# This script sets-up LatticeMico32 System environment.

#~ if [ "${NEW_INSTALL_PATH:-notset}" != "notset" ]; then
  #~ ispleverPath=$NEW_INSTALL_PATH
  #~ if [ -d $ispleverPath/micosystem ]; then
    #~ micoPath=$ispleverPath/micosystem
  #~ else
    #~ if [ "${NEW_LM32_INSTALL_PATH:-notset}" != "notset" ]; then
      #~ micoPath=$NEW_LM32_INSTALL_PATH
    #~ else
      #~ micoPath=/usr/local/diamond/1.3/micosystem
    #~ fi
  #~ fi
#~ else
  #~ if [ "${NEW_LM32_INSTALL_PATH:-notset}" != "notset" ]; then
    #~ micoPath=$NEW_LM32_INSTALL_PATH
  #~ else
    #~ micoPath=/usr/local/diamond/1.3/micosystem
  #~ fi
  #~ ispleverPath=$micoPath/../
#~ fi

if [ "${LM32_PATH:-notset}" != "notset" ]; then
  micoPath=$LM32_PATH
else
  micoPath=/usr/local/diamond/1.3/micosystem
fi

#~ if [ -d $ispleverPath/ispvmsystem ]; then
  #~ ispvmPath=$ispleverPath/ispvmsystem
#~ else
  #~ if [ "${ISPVM_DIR:-notset}" != "notset" ]; then
    #~ if [ -d $ISPVM_DIR ]; then
      #~ ispvmPath = $ISPVM_DIR
    #~ else
      #~ /bin/echo "Please enter the ispVM system path."
      #~ read ispvmPath
    #~ fi
  #~ else
      #~ /bin/echo "Please enter the ispVM system path."
      #~ read ispvmPath
  #~ fi
#~ fi

################################################################
# update environment
################################################################

PATH=$micoPath/gtools/bin:$micoPath/jre/bin:$PATH
#~ PATH=$ispvmPath:$PATH
export PATH

MOZILLA_FIVE_HOME=$micoPath/mozilla-seamonkey-1.0.1
export MOZILLA_FIVE_HOME

if [ "${LD_LIBRARY_PATH:-notset}" != "notset" ]; then
  LD_LIBRARY_PATH=$micoPath/gtools/bin:$micoPath/gtools/lib:$LD_LIBRARY_PATH
  #~ LD_LIBRARY_PATH=$ispvmPath/lib:$LD_LIBRARY_PATH
  LD_LIBRARY_PATH=${MOZILLA_FIVE_HOME}:$LD_LIBRARY_PATH
  #~ LD_LIBRARY_PATH=$ispleverPath/ispfpga/bin/lin:$LD_LIBRARY_PATH
else
  LD_LIBRARY_PATH=$micoPath/gtools/bin:$micoPath/gtools/lib
  #~ LD_LIBRARY_PATH=$ispvmPath/lib:$LD_LIBRARY_PATH
  LD_LIBRARY_PATH=${MOZILLA_FIVE_HOME}:$LD_LIBRARY_PATH
  #~ LD_LIBRARY_PATH=$ispleverPath/ispfpga/bin/lin:$LD_LIBRARY_PATH
fi
export LD_LIBRARY_PATH

if [ "${PERL5LIB:-notset}" != "notset" ]; then
  PERL5LIB=$micoPath/utilities/perlscript:$PERL5LIB
else
  PERL5LIB=$micoPath/utilities/perlscript
fi
export PERL5LIB

#~ ISPVM_DIR=$ispvmPath
#~ export ISPVM_DIR

if [ "${LD_ASSUME_KERNEL:-notset}" != "notset" ]; then
  unset LD_ASSUME_KERNEL
fi
