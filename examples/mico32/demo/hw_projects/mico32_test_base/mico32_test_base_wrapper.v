`timescale 1 ns / 1 ns

// Define Wrapping Module
module mico32_test_base_wrapper( 
                            clk_i,reset_n
                            , sramsram_wen
                            , sramsram_data
                            , sramsram_addr
                            , sramsram_csn
                            , sramsram_be
                            , sramsram_oen
                            , SPIFlashCEJ
                            , SPIFlashSCK
                            , SPIFlashSI
                            , SPIFlashSO
                            , SPIFlashWPJ
                            , sdramsdr_DQ
                            , sdramsdr_A
                            , sdramsdr_BA
                            , sdramsdr_CKE
                            , sdramsdr_CSn
                            , sdramsdr_RASn
                            , sdramsdr_CASn
                            , sdramsdr_WEn
                            , sdramsdr_DQM
                            , sdramsdr_CLK
                            , uartSIN
                            , uartSOUT
                            , net_spiMISO_MASTER
                            , net_spiMOSI_MASTER
                            , net_spiSS_N_MASTER
                            , net_spiSCLK_MASTER
                            , camera_i2cSDA
                            , camera_i2cSCL
                            , rtc_i2cSDA
                            , rtc_i2cSCL
                            , lcd_gpioPIO_IO
                            , misc_gpioPIO_BOTH_IN
                            , misc_gpioPIO_BOTH_OUT
                            , camera_gpioPIO_BOTH_IN
                            , camera_gpioPIO_BOTH_OUT
                            , multiplexed_gpioPIO_BOTH_IN
                            , multiplexed_gpioPIO_BOTH_OUT
                            , ext_spiMISO_MASTER
                            , ext_spiMOSI_MASTER
                            , ext_spiSS_N_MASTER
                            , ext_spiSCLK_MASTER
                            , spi_flash_hold_out
                            , SPIFlash_bootCEJ
                            , SPIFlash_bootSCK
                            , SPIFlash_bootSI
                            , SPIFlash_bootSO
                            );
    
    // Inputs
    input clk_i;
    input reset_n;
    input SPIFlashSO;
    input uartSIN;
    input net_spiMISO_MASTER;
	input [2:0] misc_gpioPIO_BOTH_IN;
    input [10:0] camera_gpioPIO_BOTH_IN;
    input [0:0]  multiplexed_gpioPIO_BOTH_IN;
    input        ext_spiMISO_MASTER;
    input SPIFlash_bootSO;
    
    
    // Outputs
    output       sramsram_wen;
    output [17:0] sramsram_addr;
    output        sramsram_csn;
    output [1:0]  sramsram_be;
    output        sramsram_oen;
    output        SPIFlashCEJ;
    output        SPIFlashSCK;
    output        SPIFlashSI;
    output        SPIFlashWPJ;
    output [12:0] sdramsdr_A;
    output [1:0]  sdramsdr_BA;
    output        sdramsdr_CKE;
    output        sdramsdr_CSn;
    output        sdramsdr_RASn;
    output        sdramsdr_CASn;
    output        sdramsdr_WEn;
    output [1:0]  sdramsdr_DQM;
    output        sdramsdr_CLK;
    output        uartSOUT;
	output [3:0]  misc_gpioPIO_BOTH_OUT;
    output        net_spiMOSI_MASTER;
    output [0:0]  net_spiSS_N_MASTER;
    output        net_spiSCLK_MASTER;
    output [2:0]  camera_gpioPIO_BOTH_OUT;
    output [3:0]  multiplexed_gpioPIO_BOTH_OUT;
    output        ext_spiMOSI_MASTER;
    output [0:0]  ext_spiSS_N_MASTER;
    output        ext_spiSCLK_MASTER;
    output        SPIFlash_bootCEJ;
    output        SPIFlash_bootSCK;
    output        SPIFlash_bootSI;
    output        spi_flash_hold_out;
    
    
    // Bidirs
    inout [15:0]  sramsram_data;
    inout [15:0]  sdramsdr_DQ;
    inout         camera_i2cSDA;
    inout         camera_i2cSCL;
    inout         rtc_i2cSDA;
    inout         rtc_i2cSCL;
    inout [5:0]  lcd_gpioPIO_IO;
   
	
    wire          sram_addr_0;
    
    test_base base_platform (
                               .clk_i(clk_i), 
                               .reset_n(reset_n), 
                               .sramsram_wen(sramsram_wen), 
                               .sramsram_data(sramsram_data), 
                               .sramsram_addr({sramsram_addr[17:0],sram_addr_0}),
                               .sramsram_csn(sramsram_csn), 
                               .sramsram_be(sramsram_be), 
                               .sramsram_oen(sramsram_oen), 
                               .SPIFlashCEJ(SPIFlashCEJ), 
                               .SPIFlashSCK(SPIFlashSCK), 
                               .SPIFlashSI(SPIFlashSI), 
                               .SPIFlashSO(SPIFlashSO), 
                               .sdramsdr_DQ(sdramsdr_DQ), 
                               .sdramsdr_A(sdramsdr_A), 
                               .sdramsdr_BA(sdramsdr_BA), 
                               .sdramsdr_CKE(sdramsdr_CKE), 
                               .sdramsdr_CSn(sdramsdr_CSn), 
                               .sdramsdr_RASn(sdramsdr_RASn), 
                               .sdramsdr_CASn(sdramsdr_CASn), 
                               .sdramsdr_WEn(sdramsdr_WEn), 
                               .sdramsdr_DQM(sdramsdr_DQM), 
                               .sdramsdr_CLK(sdramsdr_CLK), 
                               .uartSIN(uartSIN), 
                               .uartSOUT(uartSOUT), 
                               .net_spiMISO_MASTER(net_spiMISO_MASTER), 
                               .net_spiMOSI_MASTER(net_spiMOSI_MASTER), 
                               .net_spiSS_N_MASTER(net_spiSS_N_MASTER), 
                               .net_spiSCLK_MASTER(net_spiSCLK_MASTER), 
                               .camera_i2cSDA(camera_i2cSDA), 
                               .camera_i2cSCL(camera_i2cSCL), 
                               .rtc_i2cSDA(rtc_i2cSDA), 
                               .rtc_i2cSCL(rtc_i2cSCL), 
                               .lcd_gpioPIO_IO(lcd_gpioPIO_IO), 
                               .misc_gpioPIO_BOTH_IN(misc_gpioPIO_BOTH_IN), 
                               .misc_gpioPIO_BOTH_OUT(misc_gpioPIO_BOTH_OUT), 
                               .camera_gpioPIO_BOTH_IN(camera_gpioPIO_BOTH_IN), 
                               .camera_gpioPIO_BOTH_OUT(camera_gpioPIO_BOTH_OUT), 
                               .multiplexed_gpioPIO_BOTH_IN(multiplexed_gpioPIO_BOTH_IN), 
                               .multiplexed_gpioPIO_BOTH_OUT(multiplexed_gpioPIO_BOTH_OUT), 
                               .ext_spiMISO_MASTER(ext_spiMISO_MASTER), 
                               .ext_spiMOSI_MASTER(ext_spiMOSI_MASTER), 
                               .ext_spiSS_N_MASTER(ext_spiSS_N_MASTER), 
                               .ext_spiSCLK_MASTER(ext_spiSCLK_MASTER),
                               .SPIFlash_bootCEJ(SPIFlash_bootCEJ), 
                               .SPIFlash_bootSCK(SPIFlash_bootSCK), 
                               .SPIFlash_bootSI(SPIFlash_bootSI), 
                               .SPIFlash_bootSO(SPIFlash_bootSO)
                               );

    // Unblock SPI Flash
    assign spi_flash_hold_out = 1'b1;
    assign SPIFlashWPJ = 1'b1;
endmodule
