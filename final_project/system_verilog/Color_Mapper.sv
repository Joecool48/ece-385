// If it is 0, then we simply dont put that pixel in the frame buffer. Zero should never appear here (0 is not black, just encoded alpha. 1 is black)
module Color_Mapper (input logic [7:0] encoded_color, output logic [7:0] red, green, blue);
/*
0xff    0xff    0xff    1
0x69    0x0     0x2d    2
0x0     0x0     0x0     3
0x92    0x27    0x8f    4
0xb1    0x34    0x25    5
0xf7    0xd6    0xa4    6
0x3a    0x84    0x0     7
0x0     0x42    0x4a    8
0x0     0x7b    0x8c    9
0x63    0x63    0x63    10
0xad    0xad    0xad    11
0x6a    0x6b    0x4     12
0xe3    0x9d    0x25    13
0xb5    0x31    0x21    14
0xe6    0x9c    0x21    15
0x9c    0x4a    0x0     16
0xff    0xce    0xc5    17
0xb5    0xef    0xef    18
0x99    0x4b    0xc     19
0xa6    0xa6    0xa6    20
0x10    0x32    0x39    21
0x56    0x56    0x56    22
0xff    0xc8    0xb8    23
0xae    0xea    0xe9    24
0xd7    0x8d    0x22    25
0x1e    0x84    0x0     26
0x9c    0x25    0x20    27
0xae    0xae    0xae    28
0xff    0xce    0xc6    29
0x69    0x69    0x69    30
0xe7    0x9c    0x21    31
0x10    0x94    0x0     32
0x6b    0x8c    0xff    33
0x0     0x0     0x0     34
0xe7    0x5a    0x10    35
0xf7    0xd6    0xb5    36
0xff    0xff    0xff    37
0x0     0xad    0x0     38
0x0     0x8c    0x8c    39
0x0     0xff    0xff    40
0xfe    0xfe    0xfe    41
0xff    0xa5    0x42    42
0xbd    0xff    0x18    43
0x0     0x7b    0x0     44
0x39    0xbd    0xff    45
else							x
Num colors is:  45
*/
	always_comb begin
		case (encoded_color)
			// List each pixel decoding into its color
        8'd1: begin
            red = 8'd255;
            green = 8'd255;
            blue = 8'd255;
        end
        8'd2: begin
            red = 8'd105;
            green = 8'd0;
            blue = 8'd45;
        end
        8'd3: begin
            red = 8'd0;
            green = 8'd0;
            blue = 8'd0;
        end
        8'd4: begin
            red = 8'd146;
            green = 8'd39;
            blue = 8'd143;
        end
        8'd5: begin
            red = 8'd177;
            green = 8'd52;
            blue = 8'd37;
        end
        8'd6: begin
            red = 8'd247;
            green = 8'd214;
            blue = 8'd164;
        end
        8'd7: begin
            red = 8'd58;
            green = 8'd132;
            blue = 8'd0;
        end
        8'd8: begin
            red = 8'd0;
            green = 8'd66;
            blue = 8'd74;
        end
        8'd9: begin
            red = 8'd0;
            green = 8'd123;
            blue = 8'd140;
        end
        8'd10: begin
            red = 8'd99;
            green = 8'd99;
            blue = 8'd99;
        end
        8'd11: begin
            red = 8'd173;
            green = 8'd173;
            blue = 8'd173;
        end
        8'd12: begin
            red = 8'd106;
            green = 8'd107;
            blue = 8'd4;
        end
        8'd13: begin
            red = 8'd227;
            green = 8'd157;
            blue = 8'd37;
        end
        8'd14: begin
            red = 8'd181;
            green = 8'd49;
            blue = 8'd33;
        end
        8'd15: begin
            red = 8'd230;
            green = 8'd156;
            blue = 8'd33;
        end
        8'd16: begin
            red = 8'd156;
            green = 8'd74;
            blue = 8'd0;
        end
        8'd17: begin
            red = 8'd255;
            green = 8'd206;
            blue = 8'd197;
        end
        8'd18: begin
            red = 8'd181;
            green = 8'd239;
            blue = 8'd239;
        end
        8'd19: begin
            red = 8'd153;
            green = 8'd75;
            blue = 8'd12;
        end
        8'd20: begin
            red = 8'd166;
            green = 8'd166;
            blue = 8'd166;
        end
        8'd21: begin
            red = 8'd16;
            green = 8'd50;
            blue = 8'd57;
        end
        8'd22: begin
            red = 8'd86;
            green = 8'd86;
            blue = 8'd86;
        end
        8'd23: begin
            red = 8'd255;
            green = 8'd200;
            blue = 8'd184;
        end
        8'd24: begin
            red = 8'd174;
            green = 8'd234;
            blue = 8'd233;
        end
        8'd25: begin
            red = 8'd215;
            green = 8'd141;
            blue = 8'd34;
        end
        8'd26: begin
            red = 8'd30;
            green = 8'd132;
            blue = 8'd0;
        end
        8'd27: begin
            red = 8'd156;
            green = 8'd37;
            blue = 8'd32;
        end
        8'd28: begin
            red = 8'd174;
            green = 8'd174;
            blue = 8'd174;
        end
        8'd29: begin
            red = 8'd255;
            green = 8'd206;
            blue = 8'd198;
        end
        8'd30: begin
            red = 8'd105;
            green = 8'd105;
            blue = 8'd105;
        end
        8'd31: begin
            red = 8'd231;
            green = 8'd156;
            blue = 8'd33;
        end
        8'd32: begin
            red = 8'd16;
            green = 8'd148;
            blue = 8'd0;
        end
        8'd33: begin
            red = 8'd107;
            green = 8'd140;
            blue = 8'd255;
        end
        8'd34: begin
            red = 8'd231;
            green = 8'd90;
            blue = 8'd16;
        end
        8'd35: begin
            red = 8'd247;
            green = 8'd214;
            blue = 8'd181;
        end
        8'd36: begin
            red = 8'd0;
            green = 8'd173;
            blue = 8'd0;
        end
        8'd37: begin
            red = 8'd189;
            green = 8'd255;
            blue = 8'd24;
        end
        8'd38: begin
            red = 8'd255;
            green = 8'd165;
            blue = 8'd66;
        end
        8'd39: begin
            red = 8'd254;
            green = 8'd254;
            blue = 8'd254;
        end
        8'd40: begin
            red = 8'd57;
            green = 8'd189;
            blue = 8'd255;
        end

			default begin
				red = 8'dx;
				green = 8'dx;
				blue = 8'dx;
			end
		endcase
	end
endmodule
	
