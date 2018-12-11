
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
	sprite_address_pio_export,
	sprite_height_pio_export,
	sprite_id_pio_export,
	sprite_rotate_pio_export,
	sprite_width_pio_export,
	sprite_x_pio_export,
	sprite_y_pio_export,
	sys_clk_clk,
	keycode_pio_export_export,
	otg_data_pio_export_in_port,
	otg_data_pio_export_out_port,
	otg_cs_pio_export_export,
	otg_read_pio_export_export,
	otg_write_pio_export_export,
	otg_address_pio_export_export);	

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
	output	[12:0]	sdram_wire_addr;
	output	[1:0]	sdram_wire_ba;
	output		sdram_wire_cas_n;
	output		sdram_wire_cke;
	output		sdram_wire_cs_n;
	inout	[31:0]	sdram_wire_dq;
	output	[3:0]	sdram_wire_dqm;
	output		sdram_wire_ras_n;
	output		sdram_wire_we_n;
	output	[31:0]	sprite_address_pio_export;
	output	[15:0]	sprite_height_pio_export;
	output	[15:0]	sprite_id_pio_export;
	output	[7:0]	sprite_rotate_pio_export;
	output	[15:0]	sprite_width_pio_export;
	output	[15:0]	sprite_x_pio_export;
	output	[15:0]	sprite_y_pio_export;
	output		sys_clk_clk;
	input	[15:0]	keycode_pio_export_export;
	input	[15:0]	otg_data_pio_export_in_port;
	output	[15:0]	otg_data_pio_export_out_port;
	output	[7:0]	otg_cs_pio_export_export;
	output	[7:0]	otg_read_pio_export_export;
	output	[7:0]	otg_write_pio_export_export;
	output	[7:0]	otg_address_pio_export_export;
endmodule
