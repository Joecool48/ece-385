// Keeps track of the frame number based on VGA_VS
module frame_number (input logic VGA_VS, input logic Clk, input logic Reset, output logic frame_num);
	always_ff @ (negedge VGA_VS or negedge Reset) begin
		if (~Reset) frame_num <= 1'b0;
		else frame_num <= ~frame_num;
	end
endmodule	