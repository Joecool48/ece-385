`define FRAME_CURRENT 0
`define FRAME_UPDATE 1
module frame_controller (input logic Clk, Reset, VGA_CLK,
								 input logic [9:0] DrawX, DrawY,
								 output logic [7:0] VGA_R, VGA_G, VGA_B,
								 input active,
								 output logic [17:0] fb_addr,
								 input logic [7:0] fb_data_out
								 );
	enum logic [3:0] {WAIT, GET_ROW, WRITE_PIXEL, DONE} curr_state, next_state; 
	logic [7:0] curr_pix;
	logic [7:0] curr_data;
	logic [7:0] pix_num;
	logic [1:0] counter;
	Color_Mapper color_mapper (.encoded_color(curr_pix), .red(VGA_R), .green(VGA_G), .blue(VGA_B));
	//pixel_mux pix_mux (.pixel_buf(curr_data), .pixel_select(pix_num), .pixel(curr_pix));
	
	always_ff @ (posedge Clk) begin
		counter <= counter + 1;
		case (curr_state)
			WAIT: begin
				fb_addr <= 18'b0;
				pix_num <= 8'b0;
				curr_data <= 8'b0;
			end
			GET_ROW: begin
				// Get the current row
				curr_data <= fb_data_out;
				fb_addr <= fb_addr + 1;
			end
			WRITE_PIXEL: begin
				// See other always_ff for checking for posedge DrawX
				if (counter == 2'b0) begin
					pix_num <= pix_num + 1;
				end
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
				if (counter == 2'b0) begin
					next_state = GET_ROW;
				end
			end
			DONE: begin
				if (~active) begin
					next_state = WAIT;
				end
			end
		endcase
	end
	// Update the pixel number every DrawX clock cycle
	always_ff @ (posedge Clk) begin
		curr_state <= next_state;
	end
endmodule	