module sprite_fifo #(parameter BUS_WIDTH, parameter FIFO_DEPTH)
(
    input logic Clk,
    input logic Reset,
    input logic [BUS_WIDTH-1:0] data_in,
    input logic re,
    input logic we,
    output logic e,
    output logic f,
    output logic [BUS_WIDTH-1:0] data_out
);
logic [BUS_WIDTH - 1:0] buff_mem [FIFO_DEPTH];
logic [FIFO_DEPTH - 1:0] rd_ptr, wr_ptr;
logic [FIFO_DEPTH - 1:0] status;

assign e = (status == 0);
assign f = (status == {(FIFO_DEPTH){1'd1}});
 
always@(posedge Clk or negedge Reset)
begin
    if(~Reset)
    begin
        data_out <= 0;
		  for (int i = 0; i < FIFO_DEPTH; i = i + 1) begin
			buff_mem[i] = {(BUS_WIDTH){1'd0}};
        end
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
        if( re && !e )
        begin
            data_out <= buff_mem[rd_ptr];
            status[rd_ptr] <= 1'b0;
				if(rd_ptr == FIFO_DEPTH-1) rd_ptr <= 0;
				else rd_ptr <= rd_ptr + {{(BUS_WIDTH-1){1'b0}}, 1'b1};
        end
        else if( we && !f )
        begin
            buff_mem[wr_ptr] <= data_in;
            status[wr_ptr] <= 1'b1;
				if(wr_ptr == FIFO_DEPTH-1) wr_ptr <= 0;
				else wr_ptr <= wr_ptr + {{(BUS_WIDTH-1){1'b0}}, 1'b1};
        end
    end
end

 
endmodule
