module pixel_mux (input logic [7:0] pixel_buf, input logic [7:0] pixel_select, output logic [7:0] pixel);
	
	always_comb begin
		case (pixel_select) 
			for (int i = 0; i < 63; i = i + 1) begin
				i: pixel = pixel_buf[8 * i + 7: 8 * i];
			end
		endcase
	end	
	
endmodule 