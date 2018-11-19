module RAM_param #(parameter DATA_WIDTH, parameter ADDRESS_SPACE) (input logic clk, write, 
					   input logic [ADDRESS_SPACE - 1: 0] addr, input logic [DATA_WIDTH - 1: 0] data_in, output logic [DATA_WIDTH - 1: 0] data_out);

// Start module here!
logic [DATA_WIDTH - 1:0] reg_array [2**ADDRESS_SPACE - 1:0];

integer i;
initial begin
    for( i = 0; i < 2 ** ADDRESS_SPACE; i = i + 1 ) begin
        reg_array[i] <= 0;
    end
end

always_ff @ (posedge clk) begin
    if( write == 1'b1 )
        reg_array[addr] <= data_in;
    data_out <= reg_array[addr];
end
endmodule  
