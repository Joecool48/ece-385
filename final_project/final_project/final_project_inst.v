	final_project u0 (
		.avalon_control_fixed_location  (<connected-to-avalon_control_fixed_location>),  //     avalon_control.fixed_location
		.avalon_control_read_base       (<connected-to-avalon_control_read_base>),       //                   .read_base
		.avalon_control_read_length     (<connected-to-avalon_control_read_length>),     //                   .read_length
		.avalon_control_go              (<connected-to-avalon_control_go>),              //                   .go
		.avalon_control_done            (<connected-to-avalon_control_done>),            //                   .done
		.avalon_control_early_done      (<connected-to-avalon_control_early_done>),      //                   .early_done
		.avalon_user_read_buffer        (<connected-to-avalon_user_read_buffer>),        //        avalon_user.read_buffer
		.avalon_user_buffer_output_data (<connected-to-avalon_user_buffer_output_data>), //                   .buffer_output_data
		.avalon_user_data_available     (<connected-to-avalon_user_data_available>),     //                   .data_available
		.clk_clk                        (<connected-to-clk_clk>),                        //                clk.clk
		.reset_reset_n                  (<connected-to-reset_reset_n>),                  //              reset.reset_n
		.sdram_clk_clk                  (<connected-to-sdram_clk_clk>),                  //          sdram_clk.clk
		.sdram_wire_addr                (<connected-to-sdram_wire_addr>),                //         sdram_wire.addr
		.sdram_wire_ba                  (<connected-to-sdram_wire_ba>),                  //                   .ba
		.sdram_wire_cas_n               (<connected-to-sdram_wire_cas_n>),               //                   .cas_n
		.sdram_wire_cke                 (<connected-to-sdram_wire_cke>),                 //                   .cke
		.sdram_wire_cs_n                (<connected-to-sdram_wire_cs_n>),                //                   .cs_n
		.sdram_wire_dq                  (<connected-to-sdram_wire_dq>),                  //                   .dq
		.sdram_wire_dqm                 (<connected-to-sdram_wire_dqm>),                 //                   .dqm
		.sdram_wire_ras_n               (<connected-to-sdram_wire_ras_n>),               //                   .ras_n
		.sdram_wire_we_n                (<connected-to-sdram_wire_we_n>),                //                   .we_n
		.sprite_address_pio_export      (<connected-to-sprite_address_pio_export>),      // sprite_address_pio.export
		.sprite_height_pio_export       (<connected-to-sprite_height_pio_export>),       //  sprite_height_pio.export
		.sprite_id_pio_export           (<connected-to-sprite_id_pio_export>),           //      sprite_id_pio.export
		.sprite_width_pio_export        (<connected-to-sprite_width_pio_export>),        //   sprite_width_pio.export
		.sprite_x_pio_export            (<connected-to-sprite_x_pio_export>),            //       sprite_x_pio.export
		.sprite_y_pio_export            (<connected-to-sprite_y_pio_export>),            //       sprite_y_pio.export
		.sys_clk_clk                    (<connected-to-sys_clk_clk>),                    //            sys_clk.clk
		.sdcard_wire_DAT3               (<connected-to-sdcard_wire_DAT3>),               //        sdcard_wire.DAT3
		.sdcard_wire_DAT                (<connected-to-sdcard_wire_DAT>),                //                   .DAT
		.sdcard_wire_CMD                (<connected-to-sdcard_wire_CMD>),                //                   .CMD
		.sdcard_wire_CLK                (<connected-to-sdcard_wire_CLK>)                 //                   .CLK
	);

