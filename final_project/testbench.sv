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
					
	logic [6:0] HEX0, HEX1, HEX2, HEX3, HEX4, HEX5, HEX6, HEX7;	

//	logic [31:0] S_A;
//	logic [15:0] S_X, S_Y, S_H, S_W, S_I;
//	logic [7:0] S_R;
	
	logic [15:0] sprite_id;
	logic [15:0] sprite_x, sprite_y;
	logic [31:0] sprite_address;
	logic [15:0] sprite_width, sprite_height;
	
	logic [1:0] fifo_curr_state;
	logic done_draw, draw_sprite;
	logic [15:0] last_sprite_id;
	logic fifo_full, fifo_empty;
					
	logic[9:0] DrawX;
	logic[9:0] DrawY;
	logic[1:0] State;
	logic[7:0] Pix;
	logic[1:0] Count;
	logic[17:0] Addr; 
	
	logic frame_num;
	logic [17:0] fb_curr_addr, fb_update_addr;
	logic [7:0] fb_curr_data_out, fb_update_data_out; 
	logic [17:0] read_fb_addr;
	logic read_active;
	logic [17:0] write_fb_addr;
	logic [7:0] fb_data_in;
	logic [7:0] fb_data_out;
	logic [17:0] fb_addr;
	logic [7:0] curr_d, curr_q, updated_d, updated_q;
	logic [17:0] curr_addr, updated_addr;
	logic curr_wren, updated_wren;
	
	logic [2:0] curr_state;
	logic [17:0] pix;
	logic [15:0] pix_x, pix_y;
	logic [15:0] pix_w, pix_h;
	logic [15:0] x_count, y_count;
	
	logic [31:0] test;
	mario_cv_game mario_game (.*);
	
	assign sprite_id = mario_game.sprite_id;
	assign sprite_x = mario_game.sprite_x;
	assign sprite_y = mario_game.sprite_y;
	assign sprite_address = mario_game.sprite_address;
	assign sprite_width = mario_game.sprite_width;
	assign sprite_height = mario_game.sprite_height;
	
	assign fifo_curr_state = mario_game.fifo_curr_state;
	assign done_draw = mario_game.done_draw;
	assign draw_sprite = mario_game.draw_sprite;
	assign last_sprite_id = mario_game.last_sprite_id;
	assign fifo_full = mario_game.fifo_full;
	assign fifo_empty = mario_game.fifo_empty;
	
	assign DrawX = mario_game.f_ctl.DrawX;
	assign DrawY = mario_game.f_ctl.DrawY;
	assign State = mario_game.f_ctl.curr_state;
	assign Pix = mario_game.f_ctl.curr_pix;
	assign Count = mario_game.f_ctl.counter;
	assign Addr = mario_game.f_ctl.fb_addr;
	assign read_active = mario_game.f_ctl.active;
	assign frame_num = mario_game.frame_num;	
	
	assign fb_curr_addr = mario_game.fb_curr_addr;
	assign fb_update_addr = mario_game.fb_update_addr;
	assign read_fb_addr = mario_game.read_fb_addr;
	assign write_fb_addr = mario_game.write_fb_addr;
	
	assign fb_data_out = mario_game.fb_data_out;
	assign fb_curr_data_out = mario_game.fb_curr_data_out;
	assign fb_update_data_out = mario_game.fb_update_data_out;
	
	assign fb_data_in = mario_game.fb_data_in;
	
	assign curr_d = mario_game.fb_curr.data;
	assign curr_q = mario_game.fb_curr.q;
	assign curr_addr = mario_game.fb_curr.address;
	assign curr_wren = mario_game.fb_curr.wren; 
	
	assign updated_d = mario_game.fb_update.data;
	assign updated_q = mario_game.fb_update.q;
	assign updated_addr = mario_game.fb_update.address;
	assign updated_wren = mario_game.fb_update.wren; 
	
	assign curr_state = mario_game.s_ctl.curr_state;
	assign pix = mario_game.s_ctl.pix;
	assign pix_x = mario_game.s_ctl.pix_x; 
	assign pix_y = mario_game.s_ctl.pix_y;
	assign pix_w = mario_game.s_ctl.pix_w;
	assign pix_h = mario_game.s_ctl.pix_h;
	assign x_count = mario_game.s_ctl.x_count;
	assign y_count = mario_game.s_ctl.y_count;
	
//	assign test = mario_game.s_ctl.avalon_control_read_base;
	
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
	initial begin
		KEY = 4'b1110;
		#10 KEY = 4'b1111;
		#50 KEY = 4'b1011;
		#20 KEY = 4'b1111;
//		#10 KEY = 4'b1011;
//		#10 KEY = 4'b1111;
//		#20 KEY = 4'b1101;
//		#10 KEY = 4'b1111;
//		#20 KEY = 4'b0111;
//		#20 KEY = 4'b1111;
//		#8 S_X = 0;
//		S_Y = 0;
//		S_W = 16'd480;
//		S_H = 16'd360;
//		S_ID = 16'd1;

//		S_A = 18'd1;
//		#50 S_X = 16'd120;
//		S_Y = 16'd90;
//		S_W = 16'd240;
//		S_H = 16'd180;
//		S_ID = 16'd2;
//		S_A = 18'd2;
	end
//	always @ (posedge SYS_CLK) begin
////		if(test == 18'd1) S_D = 8'd15;
////		if(test == 18'd2) S_D = 8'd240;
//		if(curr_state == 3'b001) S_AV = 1'b1;
//		if(curr_state == 3'b001) S_DO = 1'b1;
//		else S_DO = 1'b0;
//	end
endmodule
