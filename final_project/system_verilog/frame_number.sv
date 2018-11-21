// Keeps track of the frame number based on VGA_VS
module frame_number (input logic VGA_VS, input logic Clk, output logic frame_num);
	logic frame_reg;
	assign frame_num = frame_reg;
	always_ff @ (posedge Clk) begin
		if (~VGA_VS) frame_reg <= ~frame_reg;
	end
	
endmodule	