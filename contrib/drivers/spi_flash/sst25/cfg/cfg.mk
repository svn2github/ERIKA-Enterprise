## Author: 2010 Dario Di Stefano

## Check the SPIFLASH library selection
ifeq ($(findstring __LIB_SPIFLASH__,$(LIB_OPT)),__LIB_SPIFLASH__)

##
## Application files
##

ifeq ($(findstring __USE_SST25__,$(EEOPT)) , __USE_SST25__)
EE_SRCS += contrib/drivers/spi_flash/sst25/src/sst25_generic.c
endif

ifeq ($(findstring __USE_SST25LF0X0A__,$(EEOPT)) , __USE_SST25LF0X0A__)
EE_SRCS += contrib/drivers/spi_flash/sst25/src/sst25lf0x0a.c
endif

ifeq ($(findstring __USE_SST25VF016B__,$(EEOPT)) , __USE_SST25VF016B__)
EE_SRCS += contrib/drivers/spi_flash/sst25/src/sst25vf016b.c
endif

endif
