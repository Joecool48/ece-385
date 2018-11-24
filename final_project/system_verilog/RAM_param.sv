//// Quartus Prime SystemVerilog Template
//// 
//// Mixed-width RAM with separate read and write addresses and data widths
//// that are controlled by the parameters RW and WW.	 RW and WW must specify a
//// read/write ratio supported by the memory blocks in your target device.
//// Otherwise, Quartus Prime will not infer a RAM.
//
//module RAM_param
//	#(parameter int
//		WORDS = 172800,
//		RW = 8,
//		WW = 8)
//(
//	input we, 
//	input clk,
//	input [$clog2((RW < WW) ? WORDS : (WORDS * RW)/WW) - 1 : 0] waddr, 
//	input [WW-1:0] wdata, 
//	input [$clog2((RW < WW) ? (WORDS * WW)/RW : WORDS) - 1 : 0] raddr, 
//	output logic [RW-1:0] q
//);
//   initial begin
//		$display("Initializing RAM");
//		$readmemh("scripts/mem_file.hex", ram, 0, 512);
//	end
//	// Use a multi-dimensional packed array to model the different read/write
//	// width
//	localparam int R = (RW < WW) ? WW/RW : RW/WW;
//	localparam int B = (RW < WW) ? RW: WW;
//
//	logic [R-1:0][B-1:0] ram[0:WORDS-1];
//
//	generate if(RW < WW) begin
//		// Smaller read?
//		always_ff@(posedge clk)
//		begin
//			if(we) ram[waddr] <= wdata;
//			q <= ram[raddr / R][raddr % R];
//		end
//	end
//	else begin 
//		// Smaller write?
//		always_ff@(posedge clk)
//		begin
//			if(we) ram[waddr / R][waddr % R] <= wdata;
//			q <= ram[raddr];
//		end
//	end 
//	endgenerate
//   
//endmodule : RAM_param 
