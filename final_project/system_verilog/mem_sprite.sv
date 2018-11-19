//// Gets the current 32 bit row of pixels at the specified location
//module mem_sprite (	
//							input logic avalon_control_fixed_location,  // avalon_control.fixed_location
//							input logic [31:0] avalon_control_read_base,       //               .read_base
//							input logic [31:0] avalon_control_read_length,     //               .read_length
//							input logic avalon_control_go,              //               .go
//							input logic avalon_control_done,            //               .done
//							input logic avalon_control_early_done,      //               .early_done
//							input logic avalon_user_read_buffer,      //    avalon_user.read_buffer
//							input logic [31:0] avalon_user_buffer_output_data, //               .buffer_output_data
//							input logic avalon_user_data_available,     //               .data_available)
//							
//);