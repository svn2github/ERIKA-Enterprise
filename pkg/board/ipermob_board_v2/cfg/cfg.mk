ifeq ($(findstring __IPERMOB_BOARD_V2__,$(EEOPT)) , __IPERMOB_BOARD_V2__)

#ifeq ($(findstring __USE_BUTTONS__,$(EEOPT)) , __USE_BUTTONS__)
#EE_SRCS += pkg/board/ipermob_mb_pic32/src/ee_board.c
#endif



#ifeq ($(findstring USE_HV7131GP,$(EEOPT)) , USE_HV7131GP)
#EE_SRCS += pkg/board/ipermob_mb_pic32/src/ee_ethernet_enc28j60.c
#endif


endif # __IPERMOB_BOARD_V2__
