module sprite_controller (input logic Clk, Reset,
							output logic [17:0] fb_addr,
							output logic [7:0] fb_data_in, 
							output logic fb_write_en, // Signal a write to the current frame buffer
							input logic [15:0] sprite_id,
							input logic [15:0] sprite_x,
							input logic [15:0] sprite_y,
							input logic [15:0] sprite_width,
							input logic [15:0] sprite_height,
							input logic [31:0] sprite_address,
							input logic [7:0] sprite_rotate,
							input logic draw_sprite, // signal to begin drawing sprite
							output logic done_draw, // signal to indicate sprite has been drawn
							output logic [31:0] avalon_control_read_base,       //               .read_base
							output logic [31:0] avalon_control_read_length,     //               .read_length
							output logic avalon_control_go,             //               .go
							input logic avalon_control_done,            //               .done
							input logic avalon_control_early_done,      //               .early_done
							output logic avalon_user_read_buffer,        //    avalon_user.read_buffer
							input logic [7:0] avalon_user_buffer_output_data,  //               .buffer_output_data
							input logic avalon_user_data_available,
							output logic [3:0] state
);
//	logic avalon_control_done, avalon_user_data_available;
	logic [17:0] pix;
	logic [15:0] pix_x, pix_y;
	logic [15:0] pix_w, pix_h;
	logic [15:0] x_count, y_count;
	assign state = curr_state;
//	logic [1:0] pix_rot;
//	if(pix_rot == 2'b00) assign pix = (((pix_x + x_count) * 18'd360) + (pix_y + y_count));
//	else if(pix_rot == 2'b01) assign pix = (((pix_x + pix_w - x_count) * 18'd360) + (pix_y + y_count));
//	else if(pix_rot == 2'b10) assign pix = (((pix_x + pix_w - x_count) * 18'd360) + (pix_y + pix_h - y_count));
	assign pix = (((pix_x + x_count) * 18'd480) + (pix_y + y_count));
	enum logic [2:0] {WAIT, LOAD_NEW_SPRITE, FETCH_AVALON_MEM, FETCH_FB_ROW, PAUSE, FETCH_FB_ROW_2, DONE} curr_state, next_state;
	always_ff @ (posedge Clk) begin
		case (curr_state)
			WAIT: begin
				if (~Reset) begin
					done_draw <= 1'b1;
					fb_addr <= 18'b0;
					fb_data_in <= 8'b0;
					fb_write_en <= 1'b0;
					avalon_control_read_base <= 32'b0;
					avalon_control_read_length <= 32'b0;
					avalon_control_go <= 1'b0;
					avalon_user_read_buffer <= 1'b0;
					pix_h <= 0;
					pix_w <= 0;
//					pix_rot <= 0;
				end
				pix_x <= 0;
				pix_y <= 0;
				x_count <= 0;
				y_count <= 0;
			end
			LOAD_NEW_SPRITE: begin
				fb_data_in <= 8'b0;
				fb_addr <= 18'b0;
				fb_write_en <= 1'b0;
				done_draw <= 1'b0;
				pix_x <= sprite_x;
				pix_y <= sprite_y;
				pix_h <= sprite_height;
				pix_w <= sprite_width;
//				avalon_user_data_available <= 1'b1;
//				avalon_control_done <= 1'b0;
//				pix_rot <= sprite_rotate;
			end
			FETCH_AVALON_MEM: begin	
				avalon_control_read_base <= sprite_address;
				avalon_control_read_length <= sprite_width * sprite_height; // Read all the pixels one at a time in bursts
				avalon_control_go <= 1'b1; // Begin fetching data from avalon bus (sprite data)
//				avalon_control_done <= 1'b1;
			end
			FETCH_FB_ROW: begin
				if (y_count == pix_h - 16'd1) begin
					y_count <= 0;
					x_count <= x_count + 16'd1;
				end
				else y_count <= y_count + 16'd1;
				avalon_control_go <= 0;
				avalon_user_read_buffer <= 1'b0;
			end
//			PAUSE: begin
//				test <= 1'b1;
//			end
			FETCH_FB_ROW_2: begin
				fb_addr <= pix;
//				test <= 1'b0;
//				avalon_user_read_buffer <= 1'b1;
//				if (sprite_address == 32'd3) begin
//					fb_data_in <= 8'd25; //avalon_user_buffer_output_data
//					fb_write_en <= 1'b1;
//				end
//				else if (sprite_address == 32'd7) begin
//					fb_data_in <= 8'd11;
//					fb_write_en <= 1'b1;
//				end
//				if (avalon_user_buffer_output_data != 8'b0) begin
//					fb_data_in <= avalon_user_buffer_output_data;
//					fb_write_en <= 1'b1;
//				end
				fb_data_in <= avalon_user_buffer_output_data;
				fb_write_en <= 1'b1;
			end
			DONE: begin
				done_draw <= 1'b1;
				fb_write_en <= 1'b0;
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
				next_state = FETCH_FB_ROW;
			end
			FETCH_FB_ROW: begin
				if ((y_count == pix_h - 16'd1 && x_count == pix_w - 16'd1) || avalon_control_done) next_state = DONE;
				else if (avalon_user_data_available) next_state = FETCH_FB_ROW_2;
			end
			PAUSE: begin
				if(clear) next_state = FETCH_FB_ROW_2;
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
		if (~Reset) next_state = WAIT;
	end	
	
	always_ff @ (posedge Clk) begin
		curr_state <= next_state;
	end
	
	logic [31:0] clk_counter;
	logic test, clear;
	always_ff @ (posedge Clk or negedge Reset) begin
		if (~Reset) begin 
			clk_counter <= 0;
			clear <= 0;
		end
		else if (test) begin
			if(clk_counter == 32'h05F5E10) begin
				clear <= 1'd1;
				clk_counter <= 0;
			end
			else clk_counter <= clk_counter + 32'd1;
		end
		else clear <= 0;
	end
	
endmodule
