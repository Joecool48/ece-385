module read_frame_mux (input frame_num, 
							  input logic [17:0] fb_curr_addr, fb_update_addr,
							  input logic [7:0] fb_curr_data_out, fb_update_data_out,
							  output logic [17:0] fb_addr,
							  output logic [7:0] fb_data_out
);
	assign fb_curr_addr = (frame_num == 0) ? fb_curr_addr : fb_update_addr;
	assign fb_data_out = (frame_num == 0) ? fb_curr_data_out : fb_update_data_out;

endmodule
