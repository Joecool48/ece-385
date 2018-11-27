module testbench();
	timeunit 1ns;
	timeprecision 1ps;
	logic        CLOCK_50;
	logic        [3:0]  KEY;          //bit 0 is set up as Reset
	logic				  SYS_CLK; // Clock for everything in the system
	// VGA Interface 
	logic [7:0]  VGA_R,        //VGA Red
					VGA_G,        //VGA Green
					VGA_B;    //VGA Blue
	logic        VGA_CLK,      //VGA Clock
					VGA_SYNC_N,   //VGA Sync signal
					VGA_BLANK_N,  //VGA Blank signal
					VGA_VS,       //VGA virtical sync signal
					VGA_HS;       //VGA horizontal sync signal
	// CY7C67200 Interface
	wire  [15:0] OTG_DATA;     //CY7C67200 Data bus 16 Bits
	logic [1:0]  OTG_ADDR;     //CY7C67200 Address 2 Bits
	logic        OTG_CS_N,   //CY7C67200 Chip Select
					OTG_RD_N,     //CY7C67200 Read
					OTG_WR_N,     //CY7C67200 Write
					OTG_RST_N;    //CY7C67200 Reset
	logic [1:0]            OTG_INT;      //CY7C67200 Interrupt
	// SDRAM Interface for Nios II Software
	logic [12:0] DRAM_ADDR;    //SDRAM Address 13 Bits
	wire  [31:0] DRAM_DQ;      //SDRAM Data 32 Bits
	logic [1:0]  DRAM_BA;      //SDRAM Bank Address 2 Bits
	logic [3:0]  DRAM_DQM;     //SDRAM Data Mast 4 Bits
	logic        DRAM_RAS_N,   //SDRAM Row Address Strobe
					DRAM_CAS_N,   //SDRAM Column Address Strobe
					DRAM_CKE,     //SDRAM Clock Enable
					DRAM_WE_N,    //SDRAM Write Enable
					DRAM_CS_N,    //SDRAM Chip Select
					DRAM_CLK; //SDRAM Clock
	logic[9:0] DrawX;
	logic[9:0] DrawY;
	logic Reset;
	
	mario_cv_game mario_game (.*);
	assign DrawX = mario_game.vga_controller.DrawX;
	assign DrawY = mario_game.vga_controller.DrawY;
	assign Reset = mario_game.vga_controller.Reset;
	
	initial begin
		CLOCK_50 = 1'b0;
	end
	always begin
		#10 CLOCK_50 = ~CLOCK_50;
	end
	
	initial begin : TEST_VGA
			KEY = 4'b0000;
			#5 KEY = 4'b1111;
	end

endmodule
