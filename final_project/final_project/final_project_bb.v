
module final_project (
	avalon_control_fixed_location,
	avalon_control_read_base,
	avalon_control_read_length,
	avalon_control_go,
	avalon_control_done,
	avalon_control_early_done,
	avalon_user_read_buffer,
	avalon_user_buffer_output_data,
	avalon_user_data_available,
	clk_clk,
	reset_reset_n,
	sdram_clk_clk,
	sdram_wire_addr,
	sdram_wire_ba,
	sdram_wire_cas_n,
	sdram_wire_cke,
	sdram_wire_cs_n,
	sdram_wire_dq,
	sdram_wire_dqm,
	sdram_wire_ras_n,
	sdram_wire_we_n,
	sys_clk_clk);	

	input		avalon_control_fixed_location;
	input	[31:0]	avalon_control_read_base;
	input	[31:0]	avalon_control_read_length;
	input		avalon_control_go;
	output		avalon_control_done;
	output		avalon_control_early_done;
	input		avalon_user_read_buffer;
	output	[7:0]	avalon_user_buffer_output_data;
	output		avalon_user_data_available;
	input		clk_clk;
	input		reset_reset_n;
	output		sdram_clk_clk;
	output	[11:0]	sdram_wire_addr;
	output	[1:0]	sdram_wire_ba;
	output		sdram_wire_cas_n;
	output		sdram_wire_cke;
	output		sdram_wire_cs_n;
	inout	[31:0]	sdram_wire_dq;
	output	[3:0]	sdram_wire_dqm;
	output		sdram_wire_ras_n;
	output		sdram_wire_we_n;
	output		sys_clk_clk;
endmodule
