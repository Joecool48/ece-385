// synthesis VERILOG_INPUT_VERSION SYSTEMVERILOG_2005
// 480 X 360
module mario_cv_game (
							input  logic             CLOCK_50,
							input  logic      [3:0]  KEY,          //bit 0 is set up as Reset
							output logic				  SYS_CLK, // Clock for everything in the system
							// VGA Interface 
							output logic [7:0]  VGA_R,        //VGA Red
											VGA_G,        //VGA Green
                                 VGA_B,        //VGA Blue
							output logic        VGA_CLK,      //VGA Clock
                                 VGA_SYNC_N,   //VGA Sync signal
                                 VGA_BLANK_N,  //VGA Blank signal
                                 VGA_VS,       //VGA virtical sync signal
                                 VGA_HS,       //VGA horizontal sync signal
							// CY7C67200 Interface
							inout  wire  [15:0] OTG_DATA,     //CY7C67200 Data bus 16 Bits
							output logic [1:0]  OTG_ADDR,     //CY7C67200 Address 2 Bits
							output logic        OTG_CS_N,     //CY7C67200 Chip Select
                                 OTG_RD_N,     //CY7C67200 Read
                                 OTG_WR_N,     //CY7C67200 Write
                                 OTG_RST_N,    //CY7C67200 Reset
							input logic  [1:0]  OTG_INT,      //CY7C67200 Interrupt
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
											DRAM_CLK //SDRAM Clock
							);
							// 800 pixels per line (including front/back porch
							// 525 lines per frame (including front/back porch)
							parameter [9:0] H_TOTAL = 10'd800;
							parameter [9:0] V_TOTAL = 10'd525;
							
							// Reset assignments high and low
							logic Reset;
							assign Reset = KEY[0];
							
							// Set it to 0 to make the bus burst
							logic avalon_control_fixed_location;  // avalon_control.fixed_location
							assign avalon_control_fixed_location = 1'b0;
							
							
							// Avalon bus arbitrates to allow us to access sprite data
							logic [31:0] avalon_control_read_base;       //               .read_base
							logic [31:0] avalon_control_read_length;     //               .read_length
							logic avalon_control_go;              //               .go
							logic avalon_control_done;            //               .done
							logic avalon_control_early_done;      //               .early_done
							logic avalon_user_read_buffer;        //    avalon_user.read_buffer
							logic [7:0] avalon_user_buffer_output_data; //               .buffer_output_data
							logic avalon_user_data_available;     //               .data_available
							
							
							
							logic [15:0] sprite_id, sprite_id_pio_export;
							logic [15:0] sprite_x, sprite_y, sprite_x_pio_export, sprite_y_pio_export;
							logic [31:0] sprite_address, sprite_address_pio_export;
							logic [15:0] sprite_width, sprite_height, sprite_width_pio_export, sprite_height_pio_export;
							
							logic [5:0] empty;
							logic [5:0] full;
							
							// FIFO's to queue any new sprites/backgrounds to be drawn
							logic fifo_re, fifo_we;
							logic fifo_full, fifo_empty;
							assign fifo_full = full[0];
							assign fifo_empty = empty[0];
							sprite_fifo #(.FIFO_DEPTH(128), .BUS_WIDTH(16)) sprite_id_fifo (.Clk(SYS_CLK), 
																												.Reset(Reset), 
																												.data_in(sprite_id_pio_export), 
																												.re(fifo_re), 
																												.we(fifo_we),
																												.f(full[0]),
																												.e(empty[0]),
																												.data_out(sprite_id));
																												
							sprite_fifo #(.FIFO_DEPTH(128), .BUS_WIDTH(16)) sprite_x_fifo (.Clk(SYS_CLK), 
																												.Reset(Reset), 
																												.data_in(sprite_x_pio_export), 
																												.re(fifo_re), 
																												.we(fifo_we),
																												.f(full[1]),
																												.e(empty[1]),
																												.data_out(sprite_x));
														
														
							sprite_fifo #(.FIFO_DEPTH(128), .BUS_WIDTH(16)) sprite_y_fifo (.Clk(SYS_CLK), 
																												.Reset(Reset), 
																												.data_in(sprite_y_pio_export), 
																												.re(fifo_re), 
																												.we(fifo_we),
																												.f(full[2]),
																												.e(empty[2]),
																												.data_out(sprite_y));
														
														
							sprite_fifo #(.FIFO_DEPTH(128), .BUS_WIDTH(16)) sprite_width_fifo (.Clk(SYS_CLK),
																												.Reset(Reset), 
																												.data_in(sprite_width_pio_export), 
																												.re(fifo_re), 
																												.we(fifo_we),
																												.f(full[3]),
																												.e(empty[3]),
																												.data_out(sprite_width));
																												
							sprite_fifo #(.FIFO_DEPTH(128), .BUS_WIDTH(16)) sprite_height_fifo (.Clk(SYS_CLK),
																												.Reset(Reset), 
																												.data_in(sprite_height_pio_export), 
																												.re(fifo_re), 
																												.we(fifo_we),
																												.f(full[4]),
																												.e(empty[4]),
																												.data_out(sprite_height));
							
							sprite_fifo #(.FIFO_DEPTH(128), .BUS_WIDTH(32)) sprite_address_fifo (.Clk(SYS_CLK),
																												.Reset(Reset), 
																												.data_in(sprite_address_pio_export), 
																												.re(fifo_re), 
																												.we(fifo_we),
																												.f(full[5]),
																												.e(empty[5]),
																												.data_out(sprite_address));
							

							
							// VGA controller current position
							logic [9:0] DrawX, DrawY;
							
							// Frame buffer init
							logic fb_curr_write, fb_update_write;
							logic [17:0] fb_curr_addr, fb_update_addr;
							logic [7:0] fb_curr_data_in, fb_curr_data_out, fb_update_data_in, fb_update_data_out;
							
							// Frame buffer stats for reader
							logic [17:0] read_fb_addr;
							logic [7:0] read_fb_data_out;
							logic frame_num;
							logic read_active;
							// Module to select the read frame for frame controller
							read_frame_mux frame_read_mux (.fb_addr(read_fb_addr), .fb_data_out(read_fb_data_out), .*);
							
							// Frame buffer stats for writer
							logic [17:0] write_fb_addr;
							logic [7:0] write_fb_data_out;
							logic [7:0] write_fb_data_in;
							logic write_fb_write_en;
							logic write_active;
							
							// Module to select the frame for writing sprite data to
							write_frame_mux frame_write_mux (.*, .fb_addr(write_fb_addr), .fb_data_out(write_fb_data_out), .fb_data_in(write_fb_data_in), .fb_write(write_fb_write_en));
							
							// Tells the write buffer whether to draw a new sprite
							logic draw_sprite, done_draw;
							
							final_project nios_system (
											 .*,
											 .clk_clk(CLOCK_50),
											 .reset_reset_n(KEY[0]), 
											 .sdram_wire_addr(DRAM_ADDR),    //  sdram_wire.addr
											 .sdram_wire_ba(DRAM_BA),      	//  .ba
											 .sdram_wire_cas_n(DRAM_CAS_N),    //  .cas_n
											 .sdram_wire_cke(DRAM_CKE),     	//  .cke
											 .sdram_wire_cs_n(DRAM_CS_N),      //  .cs_n
											 .sdram_wire_dq(DRAM_DQ),      	//  .dq
											 .sdram_wire_dqm(DRAM_DQM),     	//  .dqm
											 .sdram_wire_ras_n(DRAM_RAS_N),    //  .ras_n
											 .sdram_wire_we_n(DRAM_WE_N),      //  .we_n
											 .sdram_clk_clk(DRAM_CLK),			//  clock out to SDRAM from other PLL port
											 .sys_clk_clk(SYS_CLK)			// Clock for system
											 // Also imports all the sprite PIO information
							);

							// Module instantiated to keep track of frame number based on VS input
							frame_number f_num (.Clk(SYS_CLK), .*);
							
							VGA_controller vga_controller (.Clk(CLOCK_50), .*);

							// Inferred on chip memory for frame buffers 480 * 360
							RAM_param fb_curr (
																	.clock(SYS_CLK),
																	.wren(fb_curr_write), 
																	.address(fb_curr_addr),
																	.data(fb_curr_data_in), 
																	.q(fb_curr_data_out)
							);
							// Inferred on chip memory for frame buffers 480 * 360
							RAM_param fb_update  (
																	.clock(SYS_CLK),
																	.wren(fb_update_write), 
																	.address(fb_update_addr),
																	.data(fb_update_data_in), 
																	.q(fb_update_data_out)
							);
							
							// Frame controller that writes to the FPGA from the selected frame buffer
							frame_controller f_ctl (.*, .Clk(SYS_CLK), .fb_addr(read_fb_addr), .read_fb_data_out(read_fb_data_out), .active(read_active));
							
							// Sprite controller for writing sprites to the frame buffer that is currently selected
							sprite_controller s_ctl (.*, .Clk(SYS_CLK), .Reset(Reset), // .* for all avalon fabric signals
							.fb_addr(write_fb_addr),
							.fb_data_in(write_fb_data_in), 
							.fb_data_out(write_fb_data_out),
							.fb_write(write_fb_write_en), // Signal a write to the current frame buffer
							.draw_sprite(draw_sprite),
							.done_draw(done_draw)
							);
							// For controlling the reading and writing to the fifo queues
							enum logic [3:0] {WAIT, READ, READ1, READ2, READ3, WRITE, WRITE1, WRITE2, WRITE3, DONE} fifo_curr_state, fifo_next_state;
							logic [15:0] last_sprite_id;
							// System to manage the draw_sprite, done_draw, read_active, and fifo_re/fifo_we signals
							
							// TODO:
							//		Figure out a way to signal the controller to start reading without using always_ff and VGA_CLK. This wont work
							always_ff @ (posedge VGA_CLK) begin
								if ((DrawX == H_TOTAL - 1) && (DrawY == V_TOTAL - 1)) read_active <= 1'b1;
								else read_active <= 1'b0;
							end
//							always_ff @ (posedge SYS_CLK) begin								
//								fifo_we <= 1'b0;
//								fifo_re <= 1'b0;
//								draw_sprite <= 1'b0;
//								if (last_sprite_id != sprite_id && !fifo_full) begin
//									last_sprite_id <= sprite_id;
//									fifo_we <= 1'b1;
//								end
//								if (done_draw && !fifo_empty) begin
//									fifo_re <= 1'b1;
//									draw_sprite <= 1'b1;
//									
//								end
//							end
							always_comb begin
								fifo_next_state = fifo_curr_state;
								case (fifo_curr_state)
									WAIT: begin
										if (last_sprite_id != sprite_id_pio_export) fifo_next_state = WRITE;
										else if (done_draw && !fifo_empty) fifo_next_state = READ;
									end
									READ: fifo_next_state = READ1;
									READ1: fifo_next_state = READ2;
									READ2: fifo_next_state = READ3;
									READ3: fifo_next_state = DONE;
									WRITE: fifo_next_state = WRITE1;
									WRITE1: fifo_next_state = WRITE2;
									WRITE2: fifo_next_state = WRITE3;
									WRITE3: fifo_next_state = DONE;
									DONE: fifo_next_state = WAIT;
									default: fifo_next_state = WAIT;
								endcase
									
							end
							// Make sure done_draw is set low in a couple cycles after it is set high
							always_ff @ (posedge SYS_CLK) begin
								case (fifo_curr_state)
									WAIT: begin
										if (last_sprite_id != sprite_id_pio_export) begin
											last_sprite_id  <= sprite_id_pio_export;
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
									READ: fifo_re <= 1'b1;
									READ1: fifo_re <= 1'b1;
									READ2: fifo_re <= 1'b1;
									READ3: fifo_re <= 1'b1;
									WRITE: begin
										fifo_we <= 1'b1;
										draw_sprite <= 1'b1;
									end
									WRITE1: begin
										fifo_we <= 1'b1;
										draw_sprite <= 1'b1;
									end
									WRITE2: begin
										fifo_we <= 1'b1;
										draw_sprite <= 1'b1;
									end
									WRITE3: begin
										fifo_we <= 1'b1;
										draw_sprite <= 1'b1;
									end
									DONE: begin
										fifo_re = 1'b0;
										fifo_we = 1'b0;
										draw_sprite <= 1'b0;
									end
								endcase
							end
							always_ff @ (posedge SYS_CLK) begin
								fifo_curr_state <= fifo_next_state;
							end
endmodule
