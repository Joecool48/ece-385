// synthesis VERILOG_INPUT_VERSION SYSTEMVERILOG_2005
// 480 X 360
module mario_cv_game (
							input               CLOCK_50,
							input        [3:0]  KEY,          //bit 0 is set up as Reset
							output				  SYS_CLK, // Clock for everything in the system
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
							input               OTG_INT,      //CY7C67200 Interrupt
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
							
							// Set it to 0 to make the bus burst
							logic avalon_control_fixed_location;  // avalon_control.fixed_location
							assign avalon_control_fixed_location = 1'b0;
							
							logic [31:0] avalon_control_read_base;       //               .read_base
							logic [31:0] avalon_control_read_length;     //               .read_length
							logic avalon_control_go;              //               .go
							logic avalon_control_done;            //               .done
							logic avalon_control_early_done;      //               .early_done
							logic avalon_user_read_buffer;        //    avalon_user.read_buffer
							logic [7:0] avalon_user_buffer_output_data; //               .buffer_output_data
							logic avalon_user_data_available;     //               .data_available
							
							
							
							
							// Reset assignments high and low
							assign Reset = KEY[0];
							assign Reset_h = ~Reset;
							
							// VGA controller current position
							logic [9:0] DrawX, DrawY;
							
							// Frame buffer init
							logic fb_current_write, fb_update_write;
							logic [17:0] fb_curr_addr, fb_update_addr;
							logic [7:0] fb_curr_data_in, fb_curr_data_out, fb_update_data_in, fb_update_data_out;
							
							
							logic [17:0] read_fb_addr;
							logic [7:0] read_fb_data_out;
							logic frame_num;
							logic read_active;
							// Module to select the read frame for frame controller
							read_frame_mux frame_read_mux (.fb_addr(read_fb_addr), .fb_data_out(read_fb_data_out), .*);
							
							
							logic [17:0] write_fb_addr;
							logic [7:0] write_fb_data_out;
							logic [7:0] write_fb_data_in;
							logic write_fb_write_en;
							logic write_active;
							
							// Module to select the frame for writing sprite data to
							write_frame_mux frame_write_mux (.*, .fb_addr(write_fb_addr), .fb_data_out(write_fb_data_out), .fb_data_in(write_fb_data_in), .fb_write(write_fb_write_en));
							
							
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
											 .sys_clk_clk(SYS_CLK)				// Clock for system
							);
							
							// Module instantiated to keep track of frame number based on VS input
							frame_number f_num (.*);
							
							VGA_controller vga_controller (.Clk(CLOCK_50), .*);
							
							// Inferred on chip memory for frame buffers
							// Get 128 pixels per line which is 1 /5 of a 640 length line of pixels
							RAM_param #(.DATA_WIDTH(8), .ADDRESS_SPACE(18)) fb_curr (
																	.clk(SYS_CLK),
																	.write(fb_current_write), 
																	.addr(fb_curr_addr),
																	.data_in(fb_curr_data_in), 
																	.data_out(fb_curr_data_out)
							);
							// Inferred on chip memory for frame buffers
							// Get 128 pixels per line which is 1 /5 of a 640 length line of pixels
							RAM_param #(.DATA_WIDTH(8), .ADDRESS_SPACE(18)) fb_update  (
																	.clk(SYS_CLK),
																	.write(fb_update_write), 
																	.addr(fb_update_addr),
																	.data_in(fb_update_data_in), 
																	.data_out(fb_update_data_out)
							);
							// Frame controller that writes to the FPGA from the selected frame buffer
							frame_controller f_ctl (.*, .Clk(SYS_CLK), .fb_addr(read_fb_addr), .fb_data_out(read_fb_data_out), .active(read_active));
							
							// Sprite controller for writing sprites to the frame buffer that is currently selected
							sprite_controller s_ctl (.*, .Clk(SYS_CLK), .Reset(Reset), // .* for all avalon fabric signals
							.fb_addr(write_fb_addr),
							.fb_data_in(write_fb_data_in), 
							.fb_data_out(write_fb_data_out),
							.fb_write(write_fb_write_en), // Signal a write to the current frame buffer
							.sprite_id(), // NEED CONTROL HERE
							.sprite_x(), // NEED CONTROL HERE
							.sprite_y(), // NEED CONTROL HERE
							.draw_sprite(),  // NEED CONTROL HERE
							.done_draw(), // NEED CONTROL HERE
							);
endmodule
