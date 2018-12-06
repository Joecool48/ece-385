// Keeps track of the frame number based on VGA_VS
module frame_number (input logic VGA_VS, input logic Clk, input logic Reset, output logic frame_num);
	logic frame_reg, prev_VS;
	assign frame_num = frame_reg;
	always_ff @ (posedge Clk or negedge Reset) begin
		prev_VS <= ~VGA_VS;
		if (~Reset) frame_reg <= 1'b0;
		else if (VGA_VS == 1'b0 && prev_VS == 1'b0) frame_reg <= ~frame_reg;
	end
	
endmodule	