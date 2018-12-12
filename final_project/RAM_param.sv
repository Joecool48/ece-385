module RAM_param (input logic clk,
						input logic [7:0] data,
						input	logic [17:0] address,
						input	logic wren,
						output logic [7:0] q
);
	
	logic[7:0] mem [172800];
	
	always_ff @ (posedge clk) begin
		if (wren && address < 18'd172800) begin
			if(address < 18'd100000 && address > 18'd90000) mem[address] <= 8'd4;
			else mem[address] <= data;
		end
		else
			q <= mem[address];
		
	end
endmodule
