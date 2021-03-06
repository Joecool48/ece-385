// synthesis VERILOG_INPUT_VERSION SYSTEMVERILOG_2005
// 480 X 360
module mario_cv_game (
							input  logic             CLOCK_50,
							input  logic      [3:0]  KEY,          //bit 0 is set up as Reset
							input logic				  SYS_CLK, // Clock for everything in the system

							// VGA Interface 
							output logic [7:0] VGA_R, VGA_G, VGA_B, //VGA Blue
							output logic VGA_CLK,      //VGA Clock
											 VGA_SYNC_N,   //VGA Sync signal
                                  VGA_BLANK_N,  //VGA Blank signal
                                  VGA_VS,       //VGA virtical sync signal
                                  VGA_HS,       //VGA horizontal sync signal
											 
							// CY7C67200 Interface
							input logic  [1:0]  OTG_INT,      //CY7C67200 Interrupt
							inout  wire  [15:0] OTG_DATA,     //CY7C67200 Data bus 16 Bits
							output logic [1:0]  OTG_ADDR,     //CY7C67200 Address 2 Bits
							output logic 		  OTG_CS_N,     //CY7C67200 Chip Select
													  OTG_RD_N,     //CY7C67200 Read
													  OTG_WR_N,     //CY7C67200 Write
													  OTG_RST_N,    //CY7C67200 Reset											 
							
							// SDRAM Interface for Nios II Software
							output logic [12:0] DRAM_ADDR,    //SDRAM Address 13 Bits
							inout  wire  [31:0] DRAM_DQ,      //SDRAM Data 32 Bits
							output logic [1:0]  DRAM_BA,      //SDRAM Bank Address 2 Bits
							output logic [3:0]  DRAM_DQM,     //SDRAM Data Mast 4 Bits
							output logic        DRAM_RAS_N,   //SDRAM Row Address Strobe
													  DRAM_CAS_N,   //SDRAM Column Address Strobe
													  DRAM_CKE,     //SDRAM Clock Enable
													  DRAM_WE_N,    //SDRAM Write Enable
													  DRAM_CS_N,    //SDRAM Chip Select
													  DRAM_CLK, //SDRAM Clock
							
							//Hexs
							output logic [6:0] HEX0, HEX1, HEX2, HEX3, HEX4, HEX5, HEX6, HEX7
							
							//Testbench signals
//							input logic [31:0] S_A,
//							input logic [15:0] S_X, S_Y, S_H, S_W, S_I,
//							input logic [7:0] S_R
);
							// Reset assignments high and low
							logic Reset;
							assign Reset = KEY[0];
							logic t1, t2;
							logic [9:0] DrawX, DrawY;

							// Set it to 0 to make the bus burst
							logic avalon_control_fixed_location;  // avalon_control.fixed_location
							assign avalon_control_fixed_location = 1'b0;							
							
							// Avalon bus arbitrates to allow us to access sprite data
							logic avalon_control_go;              //               .go
							logic avalon_control_done;            //               .done
							logic avalon_control_early_done;      //               .early_done
							logic frame_end;

							//Read from SDRAM
							logic [31:0] avalon_control_read_base;       //               .read_base
							logic [31:0] avalon_control_read_length;     //               .read_length
							logic [7:0] avalon_user_buffer_output_data; //               .buffer_output_data
							logic avalon_user_data_available;     //               .data_available
							logic avalon_user_read_buffer;        //    avalon_user.read_buffer
							
							//Write to SDRAM
							logic [31:0] avalon_control_write_base;      
							logic [31:0] avalon_control_write_length;
							logic [15:0] avalon_user_buffer_input_data;
							logic avalon_user_buffer_full;
							logic avalon_user_write_buffer;
							
							// 800 pixels per line (including front/back porch
							// 525 lines per frame (including front/back porch)
							parameter [9:0] H_TOTAL = 10'd800;
							parameter [9:0] V_TOTAL = 10'd525;
							
							//Sprite PIOs
							logic [15:0] sprite_id, 
											 sprite_id_pio_export, 
											 sprite_id_test;
							logic [15:0] sprite_x, sprite_y,
											 sprite_x_pio_export, sprite_y_pio_export,
											 sprite_x_test, sprite_y_test;
							logic [31:0] sprite_address, 
											 sprite_address_pio_export,
											 sprite_address_test;
							logic [15:0] sprite_width, sprite_height,
											 sprite_width_pio_export, sprite_height_pio_export,
											 sprite_width_test, sprite_height_test;			 
							logic [7:0]  sprite_rotate, 
											 sprite_rotate_pio_export,
											 sprite_rotate_test;
							logic [7:0]  hardware_done_pio_export;
							
							always_ff @ (posedge SYS_CLK) begin
								if (DrawY > 10'd795) hardware_done_pio_export <= 8'd1;
								else hardware_done_pio_export <= 0;
							end
//							assign sprite_x_test = S_X;
//							assign sprite_y_test = S_Y;
//							assign sprite_height_test = S_H;
//							assign sprite_width_test = S_W;
//							assign sprite_address_test = S_A;
//							assign sprite_id_test = S_I;
//							assign sprite_rotate_test = S_R;

//							assign sprite_x_test = 16'd30;
//							assign sprite_y_test = 16'd30;
//							assign sprite_height_test = 16'd50;
//							assign sprite_width_test = 16'd50;
//							assign sprite_address_test = 32'd0;
//							assign sprite_id_test = 16'd1;
//							assign sprite_rotate_test = 0;
							logic key3, key2;
							assign key3 = KEY[3];
							assign key2 = KEY[2];

							logic [31:0] frame_count;
							logic  count_start;
							enum logic [3:0] {FWAIT, BACK, FDONE} frame_state, next_frame_state; 
							always_ff @ (posedge SYS_CLK) begin
								case (frame_state)
									FWAIT: begin
										count_start <= 0;
									end
									BACK: begin
										count_start <= 1'b1;
									end
									FDONE:
										count_start <= 0;
								endcase
								if (count_start) begin
									frame_count <= frame_count + 32'd1;
								end
								else frame_count <= 0;
								frame_state <= next_frame_state;
							end
							logic [8:0] f_count;
							always_ff @ (posedge SYS_CLK) begin
								if (~Reset) begin
									sprite_x_test <= 0;
									sprite_y_test <= 0;
									sprite_height_test <= 16'd224;	//h*w = the nb of 4-hex-words
									sprite_width_test <= 16'd480;
									sprite_address_test <= 32'd10000000; //double the address of the control panel
									sprite_rotate_test <= 0;
									sprite_id_test <= 16'd1;
								end
								else if (~key2 && f_count < 8'd1) begin
									sprite_x_test <= 16'd0;
									sprite_y_test <= 16'd0;
									sprite_height_test <= 16'd224;	//h*w = the nb of 4-hex-words
									sprite_width_test <= 16'd480;
									sprite_address_test <= 32'd10000000; //double the address of the control panel
									sprite_rotate_test <= 8'd0;
									sprite_id_test <= sprite_id_test + 16'd1;
									f_count <= f_count + 8'd1;
								end
								else if (~key3 && f_count < 8'd1) begin
									sprite_x_test <= 16'd180;
									sprite_y_test <= 16'd240;
									sprite_height_test <= 16'd31;	//h*w = the nb of 4-hex-words
									sprite_width_test <= 16'd31;
									sprite_address_test <= 32'd10771128; //double the address of the control panel
									sprite_rotate_test <= 0;
									sprite_id_test <= sprite_id_test + 16'd1;
									f_count <= f_count + 8'd1;
								end
								else if (key2 && key3) f_count <= 0;
							end
							always_comb begin
							   next_frame_state = frame_state;
								case(frame_state) 
									FWAIT: if(frame_end) next_frame_state = BACK;
									BACK: if(frame_count == 32'd10000) next_frame_state = FDONE;
									FDONE: next_frame_state = FWAIT;
									default: next_frame_state = FWAIT;
								endcase
							end
//							***SOC***
						
							//NIOS II, SDRAM_CTRL, PLL, MASTER_TEMPLATE, OTG, PIOs
//							final_project nios_system (
//											 .*,
//											 .clk_clk(CLOCK_50),
//											 .reset_reset_n(Reset), 
//											 .sdram_wire_addr(DRAM_ADDR),    //  sdram_wire.addr
//											 .sdram_wire_ba(DRAM_BA),      	//  .ba
//											 .sdram_wire_cas_n(DRAM_CAS_N),    //  .cas_n
//											 .sdram_wire_cke(DRAM_CKE),     	//  .cke
//											 .sdram_wire_cs_n(DRAM_CS_N),      //  .cs_n
//											 .sdram_wire_dq(DRAM_DQ),      	//  .dq
//											 .sdram_wire_dqm(DRAM_DQM),     	//  .dqm
//											 .sdram_wire_ras_n(DRAM_RAS_N),    //  .ras_n
//											 .sdram_wire_we_n(DRAM_WE_N),      //  .we_n
//											 .sdram_clk_clk(DRAM_CLK),			//  clock out to SDRAM from other PLL port
//											 .sys_clk_clk(SYS_CLK)			// Clock for system
//											 // Also imports all the sprite PIO information
//							);
							
//							***FRAME BUFFERS***
							
							// Module instantiated to keep track of frame number based on VS input
							logic frame_num;
							frame_number f_num (.Clk(SYS_CLK), .*);

							// Frame buffer init
							logic [17:0] fb_curr_addr, fb_update_addr;
							logic [7:0] fb_curr_data_out, fb_update_data_out;
							
							// Frame buffer stats for reader (frame_controller)
							logic [17:0] read_fb_addr;
							logic [7:0] fb_data_out;
							logic read_active;
							
							// Frame buffer stats for writer (sprite_controller)
							logic [17:0] write_fb_addr;
							logic [7:0] fb_data_in;
							logic write_fb_write_en;
							logic write_active;
							logic [31:0] count, count2;
							assign fb_data_out = (frame_num == 1) ? fb_curr_data_out : fb_update_data_out;
							assign fb_curr_addr = (frame_num == 1) ? read_fb_addr : write_fb_addr;
							assign fb_update_addr = (frame_num == 0) ? read_fb_addr : write_fb_addr;
									
							// Inferred on chip memory for frame buffers 480 * 360
							RAM_param fb_curr (	.clk(SYS_CLK),
														.wren(~frame_num & write_fb_write_en),
														.address(fb_curr_addr),
														.data(fb_data_in),
														.q(fb_curr_data_out)
							);
							
							// Inferred on chip memory for frame buffers 480 * 360
							RAM_param fb_update (.clk(SYS_CLK),
														.wren(frame_num & write_fb_write_en),
														.address(fb_update_addr),
														.data(fb_data_in),
														.q(fb_update_data_out)
							);
							
//							***FB => VGA***
							
							// VGA controller current position
							VGA_controller vga_controller (	.*, .Clk(SYS_CLK), 
																		.VGA_CLK(VGA_CLK)
							);
							
							// Frame controller that writes to the FPGA from the selected frame buffer
							frame_controller f_ctl (	.*, .Clk(SYS_CLK),
																.fb_addr(read_fb_addr),
																.read_fb_data_out(fb_data_out),
																.active(read_active),
																.red(VGA_R), 
																.green(VGA_G), 
																.blue(VGA_B)
							);
							
							// TODO:
							//		Figure out a way to signal the controller to start reading without using always_ff and VGA_CLK. This wont work
							always_ff @ (posedge VGA_CLK) begin
								if ((DrawX == H_TOTAL - 1) && (DrawY == V_TOTAL - 1)) read_active <= 1'b1;
								else read_active <= 1'b0;
							end							always_ff @ (posedge SYS_CLK or negedge Reset) begin
								if (~Reset) frame_end <= 0;
								else if((DrawX == H_TOTAL - 1) && (DrawY == V_TOTAL - 1)) frame_end <= 1'd1;
								else frame_end <= 0;
							end
//							*** SDRAM => FB ***
							logic [31:0] test_addr;
							logic [7:0] test_data;
							logic [3:0] test_state;
							assign test_data = fb_data_in;
							assign test_addr = write_fb_addr;
							// Sprite controller for writing sprites to the frame buffer that is currently selected
							logic draw_sprite, done_draw;	// Tells the write buffer whether to draw a new sprite
							
							sprite_controller s_ctl (	.*, .Clk(SYS_CLK), .Reset(Reset),
																.fb_addr(write_fb_addr),
																.fb_data_in(fb_data_in), 
																.fb_write_en(write_fb_write_en), // Signal a write to the current frame buffer
																.draw_sprite(draw_sprite),
																.done_draw(done_draw),
																.state(test_state)
							);

//							logic [3:0] hex_6;
//							logic [15:0] hex_9;
//							memory_reader m_test (.*, .Clk(SYS_CLK), .Start(~KEY[3]), .mem_addr(test_addr), .mem_data(test_data), .state(test_state));
//							memory_writer m_test (.*, .Clk(SYS_CLK), .Start(~KEY[3]), .mem_addr(test_addr), .mem_data(test_data), .state(test_state));
							
							// FIFO's to queue any new sprites/backgrounds to be drawn
							logic fifo_re, fifo_we;
							logic fifo_full, fifo_empty;
							logic [6:0] full, empty;
							assign fifo_full = full[0];
							assign fifo_empty = empty[0];
							
							sprite_fifo #(.FIFO_DEPTH(128), .BUS_WIDTH(16)) sprite_id_fifo (.Clk(SYS_CLK), 
																												.Reset(Reset), 
																												.data_in(sprite_id_test), 
																												.re(fifo_re), 
																												.we(fifo_we),
																												.f(full[0]),
																												.e(empty[0]),
																												.data_out(sprite_id));
																												
							sprite_fifo #(.FIFO_DEPTH(128), .BUS_WIDTH(16)) sprite_x_fifo (.Clk(SYS_CLK), 
																												.Reset(Reset), 
																												.data_in(sprite_x_test), 
																												.re(fifo_re), 
																												.we(fifo_we),
																												.f(full[1]),
																												.e(empty[1]),
																												.data_out(sprite_x));
														
														
							sprite_fifo #(.FIFO_DEPTH(128), .BUS_WIDTH(16)) sprite_y_fifo (.Clk(SYS_CLK), 
																												.Reset(Reset), 
																												.data_in(sprite_y_test), 
																												.re(fifo_re), 
																												.we(fifo_we),
																												.f(full[2]),
																												.e(empty[2]),
																												.data_out(sprite_y));
														
														
							sprite_fifo #(.FIFO_DEPTH(128), .BUS_WIDTH(16)) sprite_width_fifo (.Clk(SYS_CLK),
																												.Reset(Reset), 
																												.data_in(sprite_width_test), 
																												.re(fifo_re), 
																												.we(fifo_we),
																												.f(full[3]),
																												.e(empty[3]),
																												.data_out(sprite_width));
																												
							sprite_fifo #(.FIFO_DEPTH(128), .BUS_WIDTH(16)) sprite_height_fifo (.Clk(SYS_CLK),
																												.Reset(Reset), 
																												.data_in(sprite_height_test), 
																												.re(fifo_re), 
																												.we(fifo_we),
																												.f(full[4]),
																												.e(empty[4]),
																												.data_out(sprite_height));
							
							sprite_fifo #(.FIFO_DEPTH(128), .BUS_WIDTH(32)) sprite_address_fifo (.Clk(SYS_CLK),
																												.Reset(Reset), 
																												.data_in(sprite_address_test), 
																												.re(fifo_re), 
																												.we(fifo_we),
																												.f(full[5]),
																												.e(empty[5]),
																												.data_out(sprite_address));
							
							sprite_fifo #(.FIFO_DEPTH(128), .BUS_WIDTH(8)) sprite_rotate_fifo (.Clk(SYS_CLK), 
																												.Reset(Reset), 
																												.data_in(sprite_rotate_pio_export), 
																												.re(fifo_re), 
																												.we(fifo_we), 
																												.f(full[6]),
																												.e(empty[6]), 
																												.data_out(sprite_rotate));
																							
							
							
							// For controlling the reading and writing to the fifo queues
							enum logic [3:0] {WAIT, READ, WRITE, DONE} fifo_curr_state, fifo_next_state;
							logic [15:0] last_sprite_id;
							logic [1:0] rd_counter, wr_counter;
							logic test_read, test_write;
							assign test_read = ~KEY[1];
							assign test_write = ~KEY[2];
							
							// System to manage the _sprite, done_draw, read_active, and fifo_re/fifo_we signals
							always_ff @ (posedge SYS_CLK) begin
								case (fifo_curr_state)
									WAIT: begin
										if(~Reset) begin 
											last_sprite_id <= 0;
										end
										if (last_sprite_id != sprite_id_test && !fifo_full) begin
											last_sprite_id  <= sprite_id_test;
											fifo_we <= 1'b1;
										end
										else if (done_draw && !fifo_empty) begin 
											fifo_re <= 1'b1;
											draw_sprite <= 1'b1;
										end
										else begin
											fifo_we <= 1'b0;
											fifo_re <= 1'b0;
											draw_sprite <= 1'b0;
										end
									end
									READ: begin
										//rd_counter <= rd_counter + 2'd1;
										fifo_re <= 1'b1;
										draw_sprite <= 1'b1;
									end
									WRITE: begin
										//wr_counter <= wr_counter + 2'd1;
										fifo_we <= 1'b1;
									end
									DONE: begin
										fifo_re = 1'b0;
										fifo_we = 1'b0;
										draw_sprite <= 1'b0;
									end
								endcase
							end
							always_comb begin
								fifo_next_state = fifo_curr_state;
								case (fifo_curr_state)
									WAIT: begin
										if (last_sprite_id != sprite_id_test && !fifo_full) fifo_next_state = WRITE;
										else if (done_draw && !fifo_empty) fifo_next_state = READ; 
									end
									READ: fifo_next_state = DONE;
									WRITE: fifo_next_state = DONE;
									DONE: fifo_next_state = WAIT;
									default: fifo_next_state = WAIT;
								endcase
							end
							always_ff @ (posedge SYS_CLK) begin
								fifo_curr_state <= fifo_next_state;
							end
							logic [7:0] t_count;
							//HEX DRIVERS
							logic [6:0] hex0_comb, hex1_comb, hex2_comb, hex3_comb, hex4_comb, hex5_comb, hex6_comb, hex7_comb;
							logic [15:0] pix_x_test, pix_y_test;
							always_ff @(posedge SYS_CLK) begin       
									HEX0 <= hex0_comb;	
									HEX1 <= hex1_comb;	
									HEX2 <= hex2_comb;	
									HEX3 <= hex3_comb;	
									HEX4 <= hex4_comb;	
									HEX5 <= hex5_comb;
									HEX6 <= hex6_comb;	
									HEX7 <= hex7_comb;
							 end
							 
							 HexDriver hex0_inst
							 (
								  .In0(avalon_user_buffer_output_data[3:0]),
								  .Out0(hex0_comb)
							 );
							 
							 HexDriver hex1_inst
							 (
								  .In0(avalon_user_buffer_output_data[7:4]),
								  .Out0(hex1_comb)
							 );
							 
							 HexDriver hex2_inst
							 (
								  .In0(test_state[3:0]),
								  .Out0(hex2_comb)
							 );
							 
							 HexDriver hex3_inst
							 (
								  .In0(t_count[3:0]),
								  .Out0(hex3_comb)
							 );
							 
							HexDriver hex4_inst
							 (
								  .In0(t_count[7:4]),
								  .Out0(hex4_comb)
							 );
							 
							 HexDriver hex5_inst
							 (
								  .In0(avalon_user_read_buffer),
								  .Out0(hex5_comb)
							 );
							 
							HexDriver hex6_inst
							 (
								  .In0(avalon_control_done),
								  .Out0(hex6_comb)
							 );
							 
							 HexDriver hex7_inst
							 (
								  .In0(avalon_user_data_available),
								  .Out0(hex7_comb)
							 );
//							 logic SYS_CLK;
//							logic [31:0] clk_counter;
//							always_ff @ (posedge CLOCK_50 or negedge Reset) begin
//								if (~Reset) begin 
//									SYS_CLK <= 0;
//									clk_counter <= 0;
//								end
//								else begin
//									if(clk_counter == 32'h0989680) begin
//										clk_counter <= 0;
//										SYS_CLK <= ~SYS_CLK;
//									end
//									else clk_counter <= clk_counter + 32'd1;
//								end
//							end
endmodule
