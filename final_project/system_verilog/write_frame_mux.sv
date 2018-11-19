module write_frame_mux (input frame_num, 
							  input logic [17:0] fb_curr_addr, fb_update_addr,
							  input logic [7:0] fb_curr_data_out, fb_update_data_out,
							  input logic [7:0] fb_curr_data_in, fb_curr_data_out,
							  input logic fb_curr_write, fb_update_write,
							  output logic [17:0] fb_addr,
							  output logic [7:0] fb_data_out,
							  output logic [7:0] fb_data_in,
							  output logic fb_write
);
	assign fb_addr = (frame_num == 1) ? fb_curr_addr : fb_update_addr;
	assign fb_data_out = (frame_num == 1) ? fb_curr_data_out : fb_update_data_out;
	assign fb_data_in = (frame_num == 1) ? fb_curr_data_in : fb_update_data_in;
	assign fb_write = (frame_num == 1) ? fb_curr_write : fb_update_write;
endmodule
