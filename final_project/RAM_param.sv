module RAM_param (input logic clk,
						input logic [7:0] data,
						input	logic [17:0] address,
						input	logic wren,
						output logic [7:0] q
);
	
	logic[7:0] mem [172800];
	
	always_ff @ (posedge clk) begin
		if (wren)
			mem[address] <= data;
		else
			q <= mem[address];
	end
endmodule
