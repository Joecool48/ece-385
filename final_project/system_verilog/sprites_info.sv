module sprites_info (input logic [31:0] sprite_id, output logic [31:0] sprite_address, sprite_width, sprite_height);
	
	
	always_comb begin
		// List every sprites id along with its respective address, width, and height here
		case (sprite_id) 
			default begin
				sprite_address = 32'bx;
				sprite_width = 32'bx;
				sprite_height = 32'bx;
			end
		endcase
	end

endmodule

