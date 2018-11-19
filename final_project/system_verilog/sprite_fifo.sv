module sprite_fifo #(parameter BUS_WIDTH, parameter FIFO_DEPTH)
(
    input logic Clk,
    input logic Reset,
    input logic [BUS_WIDTH-1:0] data_in,
    input logic re,
    input logic we,
    output logic empty,
    output logic full,
    output logic [BUS_WIDTH-1:0] data_out
);
logic [BUS_WIDTH - 1:0] buff_mem [FIFO_DEPTH - 1:0];
logic [BUS_WIDTH - 1:0] rd_ptr, wr_ptr;
logic [BUS_WIDTH - 1:0] status;

always@(data_out)
begin
    assign empty = (status == 0);
    assign full = (status == {(FIFO_DEPTH){1'b1}});
end
 
always@(posedge Clk or posedge Reset)
begin
    if(Reset)
    begin
        data_out <= 0;
        buff_mem <= 0;
        status <= 0;
        rd_ptr <= 0;
        wr_ptr <= 0;
    end
    else
    begin
        data_out <= data_out;
        buff_mem[wr_ptr] <= buff_mem[wr_ptr];
        rd_ptr <= rd_ptr;
        wr_ptr <= wr_ptr;
        if( re && !empty )
        begin
            data_out <= buff_mem[rd_ptr][BUS_WIDTH-1:0];
            status[rd_ptr] <= 1'b0;
            rd_ptr <= rd_ptr + 1;
        end
        else if( we && !full )
        begin
            buff_mem[wr_ptr] <= data_in;
            status[wr_ptr] <= 1'b1;
            wr_ptr <= wr_ptr + 1;
        end
    end
end
 
 
endmodule
