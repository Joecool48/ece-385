// Fetch row of 256 15 times per row
module sprite_controller (input logic Clk, Reset,
							output logic [17:0] fb_addr,
							output logic [7:0] fb_data_in, 
							input logic [7:0] fb_data_out,
							input logic fb_write, // Signal a write to the current frame buffer
							input logic [31:0] sprite_id,
							input logic [31:0] sprite_x,
							input logic [31:0] sprite_y,
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
	logic [31:0] sprite_address, sprite_width, sprite_height;
	logic [31:0] address_reg, width_reg, height_reg, x_reg, y_reg;
	// Gets info about sprite based on id
	sprites_info sprite_inf (.*);
	
	assign pix = ((480 * y_reg) + x_reg);
	
	enum [5:0] {WAIT, LOAD_NEW_SPRITE, FETCH_AVALON_MEM, FETCH_FB_ROW, WRITE_PIXEL, DONE} curr_state, next_state;
	always_ff @ (posedge Clk) begin
		avalon_user_read_buffer <= 1'b0;
		avalon_control_go <= 1'b0;
		fb_write <= 1'b0;
		done_draw <= 1'b0;
		case (curr_state)
			LOAD_NEW_SPRITE: begin
				address_reg <= sprite_address;
				width_reg <= sprite_width;
				height_reg <= sprite_height;
				x_reg <= sprite_x;
				y_reg <= sprite_y;
				fb_data_in <= 8'b0;
				fb_addr <= 18'b0;
				fb_write <= 1'b0;
				done_draw <= 1'b0;
				data_buf <= 8'b0;
			end
			FETCH_AVALON_MEM: begin	
				avalon_control_base <= address_reg;
				avalog_control_read_length <= sprite_width * sprite_height; // Read all the pixels one at a time in bursts
				avalon_control_go <= 1'b1; // Begin fetching data from avalon bus (sprite data)
				fb_addr <= address_row;
			end
			FETCH_FB_ROW: begin
				fb_data_in <= avalon_user_buffer_output_data;
				fb_write <= 1'b1;
			end
			FETCH_FB_ROW_2: begin
				fb_addr <= fb_addr + 1;
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
				if (fb_addr == sprite_address + (width_reg * height_reg)) next_state = DONE;
				if (avalon_user_data_available) next_state = FETCH_FB_ROW_2;
			end
			FETCH_FB_ROW_2: begin
				next_state = FETCH_FB_ROW;
			end
			DONE: begin
				if (!draw_sprite) next_state = WAIT;
			end
		endcase
	end	
	
	
	
	
	
	always_ff @ (posedge Clk) begin
		next_state <= curr_state;
	end
	