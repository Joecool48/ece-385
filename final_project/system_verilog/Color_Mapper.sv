module Color_Mapper (input logic [7:0] encoded_color, output logic [7:0] red, green, blue);
	
	always_comb begin
		case (encoded_color)
			// List each pixel decoding into its color
			default begin
				red = 8'dx;
				green = 8'dx;
				blue = 8'dx;
			end
		endcase
	end
endmodule
	
