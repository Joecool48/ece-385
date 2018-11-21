module RAM_param #(parameter DATA_WIDTH, parameter ADDRESSES) (input logic clk, write, 
					   input logic [$clog2(ADDRESSES) - 1: 0] addr, input logic [DATA_WIDTH - 1: 0] data_in, output logic [DATA_WIDTH - 1: 0] data_out);

logic [DATA_WIDTH - 1:0] reg_array [ADDRESSES - 1:0];

always_ff @ (posedge clk) begin
    if( write == 1'b1 )
        reg_array[addr] <= data_in;
    data_out <= reg_array[addr];
end
endmodule  
