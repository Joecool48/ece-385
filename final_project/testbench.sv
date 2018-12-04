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
	logic[1:0] State;
	logic[7:0] Pix;
	logic[1:0] Count;
	logic[17:0] Addr; 
	logic frame_num;
	logic[7:0] fb_data_out;
	logic[17:0] fb_addr;
	logic[7:0] ram_d, ram_q;
	logic[17:0] ram_raddr, ram_waddr;
	logic ram_ren;
	
	mario_cv_game mario_game (.*);
	
	assign DrawX = mario_game.f_ctl.DrawX;
	assign DrawY = mario_game.f_ctl.DrawY;
	assign State = mario_game.f_ctl.curr_state;
	assign Pix = mario_game.f_ctl.curr_pix;
	assign Count = mario_game.f_ctl.counter;
	assign Addr = mario_game.f_ctl.fb_addr;
	assign frame_num = mario_game.frame_read_mux.frame_num;
	assign fb_data_out = mario_game.frame_read_mux.fb_data_out;
	assign fb_addr = mario_game.frame_read_mux.fb_addr;
	assign ram_d = mario_game.fb_curr.data;
	assign ram_q = mario_game.fb_curr.q;
	assign ram_raddr = mario_game.fb_curr.rdaddress;
	assign ram_waddr = mario_game.fb_curr.wraddress;
	assign ram_ren = mario_game.fb_curr.rden; 
	
	initial begin
		CLOCK_50 = 1'b0;
		SYS_CLK = 1'b0;
	end
	always begin
		#10 CLOCK_50 = ~CLOCK_50;
	end
	always begin
		#5 SYS_CLK = ~SYS_CLK;
	end
	initial begin : TEST_VGA
			KEY = 4'b0000;
			#10 KEY = 4'b1111;
	end

endmodule
