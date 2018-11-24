module sprite_controller (input logic Clk, Reset,
							output logic [17:0] fb_addr,
							output logic [7:0] fb_data_in, 
							input logic [7:0] fb_data_out,
							output logic fb_write, // Signal a write to the current frame buffer
							input logic [15:0] sprite_id,
							input logic [15:0] sprite_x,
							input logic [15:0] sprite_y,
							input logic [15:0] sprite_width,
							input logic [15:0] sprite_height,
							input logic [31:0] sprite_address,
							input logic draw_sprite, // signal to begin drawing sprite
							output logic done_draw, // signal to indicate sprite has been drawn
							output logic [31:0] avalon_control_read_base,       //               .read_base
							output logic [31:0] avalon_control_read_length,     //               .read_length
							output logic avalon_control_go,             //               .go
							input logic avalon_control_done,            //               .done
							input logic avalon_control_early_done,      //               .early_done
							output logic avalon_user_read_buffer,        //    avalon_user.read_buffer
							input logic [7:0] avalon_user_buffer_output_data, //               .buffer_output_data
							input logic avalon_user_data_available
);
	logic pix;
	assign pix = ((360 * sprite_x) + sprite_y);
	
	enum logic [5:0] {WAIT, LOAD_NEW_SPRITE, FETCH_AVALON_MEM, FETCH_FB_ROW, FETCH_FB_ROW_2, DONE} curr_state, next_state;
	always_ff @ (posedge Clk) begin
		avalon_user_read_buffer <= 1'b0;
		avalon_control_go <= 1'b0;
		fb_write <= 1'b0;
		done_draw <= 1'b0;
		case (curr_state)
			LOAD_NEW_SPRITE: begin
//				sprite_address <= s_address;
//				sprite_width <= s_width;
//				sprite_height <= s_height;
//				sprite_x <= s_x;
//				sprite_y <= s_y;
				fb_data_in <= 8'b0;
				fb_addr <= 18'b0;
				fb_write <= 1'b0;
				done_draw <= 1'b0;
			end
			FETCH_AVALON_MEM: begin	
				avalon_control_read_base <= sprite_address;
				avalon_control_read_length <= sprite_width * sprite_height; // Read all the pixels one at a time in bursts
				avalon_control_go <= 1'b1; // Begin fetching data from avalon bus (sprite data)
				fb_addr <= pix;
			end
			FETCH_FB_ROW: begin
				if (avalon_user_buffer_output_data != 8'b0) begin
					fb_data_in <= avalon_user_buffer_output_data;
					fb_write <= 1'b1;
				end
			end
			FETCH_FB_ROW_2: begin
				fb_addr <= fb_addr + 32'd1;
			end
			
			DONE: begin
				done_draw <= 1'b1;
			end
		endcase
	end
	
	
	always_comb begin
	next_state = curr_state;
		case (curr_state) 
			WAIT: begin
				if (draw_sprite) next_state = LOAD_NEW_SPRITE;
			end
			LOAD_NEW_SPRITE: begin
				next_state = FETCH_AVALON_MEM;
			end
			FETCH_AVALON_MEM: begin
				// Once data has been gotten
				if (avalon_control_done) next_state = FETCH_FB_ROW;
			end
			FETCH_FB_ROW: begin
				if (fb_addr == sprite_address + (sprite_width * sprite_height)) next_state = DONE;
				if (avalon_user_data_available) next_state = FETCH_FB_ROW_2;
			end
			FETCH_FB_ROW_2: begin
				next_state = FETCH_FB_ROW;
			end
			DONE: begin
				if (!draw_sprite) next_state = WAIT;
			end
			default: begin
				next_state = WAIT;
			end
		endcase
	end	
	
	
	
	
	
	always_ff @ (posedge Clk) begin
		curr_state <= next_state;
	end
	
endmodule
