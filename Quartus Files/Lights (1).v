module Lights (CLOCK_50,CLOCK2_50, SW, KEY, LEDR, LEDG, HEX0, HEX1, HEX2, HEX3,
                HEX4, HEX5, HEX6,HEX7, DRAM_ADDR, DRAM_BA,DRAM_CAS_N, DRAM_RAS_N,DRAM_CLK,
					 DRAM_CKE, DRAM_CS_N,DRAM_WE_N, DRAM_DQM, DRAM_DQ,	SD_CLK,SD_CMD,
					 SD_DAT, VGA_CLK, VGA_BLANK_N, VGA_HS, VGA_VS, VGA_SYNC_N, VGA_B,
					 VGA_R, VGA_G, I2C_SCLK, I2C_SDAT,SRAM_ADDR,
	SRAM_DQ,
	SRAM_CE_N,
	SRAM_WE_N,
	SRAM_OE_N,
	SRAM_UB_N,
	SRAM_LB_N
                );
    input wire CLOCK_50;
	 input wire CLOCK2_50;
    input wire [17:0] SW;
    input wire [3:0] KEY;
    output wire [17:0] LEDR;
    output wire [7:0] LEDG;
    output wire [6:0] HEX0;
    output wire [6:0] HEX1;
    output wire [6:0] HEX2;
    output wire [6:0] HEX3;
    output wire [6:0] HEX4;
    output wire [6:0] HEX5;
    output wire [6:0] HEX6;
	 output wire [6:0] HEX7;
    output [12:0] DRAM_ADDR;
	 output [1:0] DRAM_BA;
	 output DRAM_CAS_N, DRAM_RAS_N,DRAM_CLK;
	 output DRAM_CKE, DRAM_CS_N,DRAM_WE_N;
	 output [3:0] DRAM_DQM;
	 inout [31:0] DRAM_DQ;
	 output	SD_CLK;
	inout		SD_CMD;
	inout			[ 3: 0]  SD_DAT;
	output [7:0] VGA_B, VGA_G,VGA_R;	
	output VGA_CLK, VGA_BLANK_N, VGA_HS, VGA_VS, VGA_SYNC_N;
	output I2C_SCLK;
	inout	I2C_SDAT;
	
	// SRAM
output		[19: 0]	SRAM_ADDR;
inout			[15: 0]	SRAM_DQ;
output					SRAM_CE_N;
output					SRAM_WE_N;
output					SRAM_OE_N;
output					SRAM_UB_N;
output					SRAM_LB_N;
	 
projectSystemQsys NiosII(
		.av_config_SDAT(I2C_SDAT),             //            av_config.SDAT
		.av_config_SCLK(I2C_SCLK),   
		.system_pll_ref_clk_clk(CLOCK_50),            //         clk.clk
		.green_leds_export(LEDG),  //  green_leds.export
		.red_leds_export(LEDR),
		.keys_export(KEY[3:1]),
		.system_pll_ref_reset_reset(1'b0),      //       reset.reset_n
		.seven_seg_0_export(HEX0), // seven_seg_0.export
		.seven_seg_1_export(HEX1), // seven_seg_1.export
		.seven_seg_2_export(HEX2), // seven_seg_2.export
		.seven_seg_3_export(HEX3), // seven_seg_3.export
		.seven_seg_4_export(HEX4), // seven_seg_4.export
		.seven_seg_5_export(HEX5), // seven_seg_5.export
		.seven_seg_6_export(HEX6), // seven_seg_6.export
		.seven_seg_7_export(HEX7),
		.switches_export(SW),     //    switches.export
	.sdram_clk_clk(DRAM_CLK),
   .sdram_addr									(DRAM_ADDR),
	.sdram_ba									(DRAM_BA),
	.sdram_cas_n								(DRAM_CAS_N),
	.sdram_cke									(DRAM_CKE),
	.sdram_cs_n									(DRAM_CS_N),
	.sdram_dq									(DRAM_DQ),
	.sdram_dqm									(DRAM_DQM),
	.sdram_ras_n								(DRAM_RAS_N),
	.sdram_we_n									(DRAM_WE_N),
		.sd_card_b_SD_cmd(SD_CMD),   //     sd_card.b_SD_cmd
		.sd_card_b_SD_dat(SD_DAT[0]),   //            .b_SD_dat
		.sd_card_b_SD_dat3(SD_DAT[3]),  //            .b_SD_dat3
		.sd_card_o_SD_clock(SD_CLK),
		.vga_CLK(VGA_CLK),   // vga_controller.CLK
		.vga_HS(VGA_HS),    //               .HS
		.vga_VS(VGA_VS),    //               .VS
		.vga_BLANK(VGA_BLANK_N), //               .BLANK
		.vga_SYNC(VGA_SYNC_N),  //               .SYNC
		.vga_R(VGA_R),     //               .R
		.vga_G(VGA_G),     //               .G
		.vga_B(VGA_B),      //               .B
		.vga_pll_ref_clk_clk(CLOCK2_50),        //      vga_pll_ref_clk.clk
		.vga_pll_ref_reset_reset(1'b0),
			.sram_DQ(SRAM_DQ),
	.sram_ADDR(SRAM_ADDR),
	.sram_LB_N(SRAM_LB_N),
	.sram_UB_N(SRAM_UB_N),
	.sram_CE_N(SRAM_CE_N),
	.sram_OE_N(SRAM_OE_N),
	.sram_WE_N(SRAM_WE_N)

	);

	
	endmodule 