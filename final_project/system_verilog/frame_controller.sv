module frame_controller (input logic Clk, Reset,
								 input logic [9:0] DrawX, DrawY,
								 output logic [7:0] red, green, blue,
								 input active,
								 output logic [17:0] fb_addr,
								 input logic [7:0] read_fb_data_out
								 );
	enum logic [1:0] {WAIT, GET_ROW, WRITE_PIXEL, DONE} curr_state, next_state; 
	logic [7:0] curr_pix;
	logic [1:0] counter;
	Color_Mapper color_mapper (.encoded_color(curr_pix), .*);	//.* <=> r, g, b
	
	always_ff @ (posedge Clk) begin
		counter <= counter + 2'd1;
		case (curr_state)
			WAIT: begin
				if (~Reset) begin
					fb_addr <= 18'b0;
					curr_pix <= 8'b0;
					counter <= 2'd0;
				end
				else begin
					fb_addr <= 18'b0;
					curr_pix <= 8'b0;
					counter <= 2'd0;
				end
			end
			GET_ROW: begin
				// Get the current row
				curr_pix <= (DrawX < 10'd480 && DrawY < 10'd360) ? read_fb_data_out : 8'd50;
				fb_addr <= (DrawX < 10'd480 && DrawY < 10'd360) ? fb_addr + 18'd1 : fb_addr;
				
			end
			WRITE_PIXEL: begin
//				if (counter == 2'd3) begin
//					fb_addr <= fb_addr + 18'd1;
//				end
			end
			DONE: begin
				
			end
		endcase
	end

	always_comb begin
		next_state = curr_state;
		case (curr_state)
			WAIT: begin
				if (active) next_state = GET_ROW;
			end
			GET_ROW: begin
				// Get the current row
				if (fb_addr == 18'd172800) next_state = DONE;
				else next_state = WRITE_PIXEL;
			end
			WRITE_PIXEL: begin
				if (counter == 2'd3) begin
					next_state = GET_ROW;
				end
			end
			DONE: begin
				if (~active) begin
					next_state = WAIT;
				end
			end
			default: begin
				next_state = WAIT;
			end 
		endcase
	end
	// Update the pixel number every DrawX clock cycle
	always_ff @ (posedge Clk) begin
		curr_state <= next_state;
	end
endmodule	