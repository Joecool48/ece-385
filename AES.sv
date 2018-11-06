/************************************************************************
AES Decryption Core Logic

Dong Kai Wang, Fall 2017

For use with ECE 385 Experiment 9
University of Illinois ECE Department
************************************************************************/

module AES (
	input	 logic CLK,
	input  logic RESET,
	input  logic AES_START,
	output logic AES_DONE,
	input  logic [127:0] AES_KEY,
	input  logic [127:0] AES_MSG_ENC,
	output logic [127:0] AES_MSG_DEC
);
	parameter [4:0] COUNTER_START = 9;
	enum logic [5:0] {START, KEY_EXPANSION, ADD_ROUND_KEY_INIT, INV_SHIFT_ROWS_LOOP, INV_SHIFT_ROWS_LOOP_WAIT, INV_SUB_BYTES_LOOP, INV_SUB_BYTES_LOOP_WAIT, INV_ADD_ROUND_KEY_LOOP, INV_MIX_COLUMNS_LOOP_0, INV_MIX_COLUMNS_LOOP_WAIT_0, INV_MIX_COLUMNS_LOOP_1, INV_MIX_COLUMNS_LOOP_WAIT_1, INV_MIX_COLUMNS_LOOP_2, INV_MIX_COLUMNS_LOOP_WAIT_2, INV_MIX_COLUMNS_LOOP_3, INV_MIX_COLUMNS_LOOP_WAIT_3, DONE} current_state, next_state;//INV_SHIFT_ROWS_WAIT, INV_SUB_BYTES_WAIT, INV_ADD_ROUND_KEY, DONE} current_state, next_state;
	logic [1407:0] key_expansion_out;
	logic [4:0] loop_counter;
	logic [1:0] mix_col_counter;
	logic [127:0] inv_shift_rows_data_in, inv_shift_rows_data_out;
	logic [31:0] inv_mix_columns_in, inv_mix_columns_out;
	logic [7:0] inv_sub_bytes_in [15:0], inv_sub_bytes_out [15:0];
	logic [127:0] state;
	
	KeyExpansion key_exp (.clk(CLK), .CipherKey(AES_KEY), .KeySchedule(key_expansion_out));
	InvShiftRows inv_shift_rows (.data_in(inv_shift_rows_data_in), .data_out(inv_shift_rows_data_out));
	InvMixColumns inv_mix_columns (.in(inv_mix_columns_in), .out(inv_mix_columns_out));
	InvSubBytes sub0 (.clk(CLK), .in(inv_sub_bytes_in[0]), .out(inv_sub_bytes_out[0]));
	InvSubBytes sub1 (.clk(CLK), .in(inv_sub_bytes_in[1]), .out(inv_sub_bytes_out[1]));
	InvSubBytes sub2 (.clk(CLK), .in(inv_sub_bytes_in[2]), .out(inv_sub_bytes_out[2]));
	InvSubBytes sub3 (.clk(CLK), .in(inv_sub_bytes_in[3]), .out(inv_sub_bytes_out[3]));
	InvSubBytes sub4 (.clk(CLK), .in(inv_sub_bytes_in[4]), .out(inv_sub_bytes_out[4]));
	InvSubBytes sub5 (.clk(CLK), .in(inv_sub_bytes_in[5]), .out(inv_sub_bytes_out[5]));
	InvSubBytes sub6 (.clk(CLK), .in(inv_sub_bytes_in[6]), .out(inv_sub_bytes_out[6]));
	InvSubBytes sub7 (.clk(CLK), .in(inv_sub_bytes_in[7]), .out(inv_sub_bytes_out[7]));
	InvSubBytes sub8 (.clk(CLK), .in(inv_sub_bytes_in[8]), .out(inv_sub_bytes_out[8]));
	InvSubBytes sub9 (.clk(CLK), .in(inv_sub_bytes_in[9]), .out(inv_sub_bytes_out[9]));
	InvSubBytes sub10 (.clk(CLK), .in(inv_sub_bytes_in[10]), .out(inv_sub_bytes_out[10]));
	InvSubBytes sub11 (.clk(CLK), .in(inv_sub_bytes_in[11]), .out(inv_sub_bytes_out[11]));
	InvSubBytes sub12 (.clk(CLK), .in(inv_sub_bytes_in[12]), .out(inv_sub_bytes_out[12]));
	InvSubBytes sub13 (.clk(CLK), .in(inv_sub_bytes_in[13]), .out(inv_sub_bytes_out[13]));
	InvSubBytes sub14 (.clk(CLK), .in(inv_sub_bytes_in[14]), .out(inv_sub_bytes_out[14]));
	InvSubBytes sub15 (.clk(CLK), .in(inv_sub_bytes_in[15]), .out(inv_sub_bytes_out[15]));
	
	always_comb begin
//		if (RESET) begin	
//			AES_MSG_DEC = 128'b0;
//			loop_counter = COUNTER_START;
//			current_state = START;
//			next_state = START;
//		end
		unique case (current_state)
			START: begin
				if (AES_START) next_state = KEY_EXPANSION;
				else next_state = START;
			end
			KEY_EXPANSION: begin
				next_state = ADD_ROUND_KEY_INIT;
			end
			ADD_ROUND_KEY_INIT: begin
				next_state = INV_SHIFT_ROWS_LOOP;
				loop_counter = COUNTER_START;
			end
			INV_SHIFT_ROWS_LOOP: begin
				next_state = INV_SHIFT_ROWS_LOOP_WAIT;
			end
			INV_SHIFT_ROWS_LOOP_WAIT: begin
				next_state = INV_SUB_BYTES_LOOP;
			end
			INV_SUB_BYTES_LOOP: begin	
				next_state = INV_SUB_BYTES_LOOP_WAIT;
			end
			INV_SUB_BYTES_LOOP_WAIT: begin
				next_state = INV_ADD_ROUND_KEY_LOOP;
			end
			INV_ADD_ROUND_KEY_LOOP: begin
				if (loop_counter <= 0)
					next_state = DONE;
				else 
					next_state = INV_MIX_COLUMNS_LOOP_0;
			end
			INV_MIX_COLUMNS_LOOP_0: begin
				next_state = INV_MIX_COLUMNS_LOOP_WAIT_0;
			end
			INV_MIX_COLUMNS_LOOP_WAIT_0: begin
				next_state = INV_MIX_COLUMNS_LOOP_1;
			end
			INV_MIX_COLUMNS_LOOP_1: begin
				next_state = INV_MIX_COLUMNS_LOOP_WAIT_1;
			end
			INV_MIX_COLUMNS_LOOP_WAIT_1: begin
				next_state = INV_MIX_COLUMNS_LOOP_2;
			end
			INV_MIX_COLUMNS_LOOP_2: begin
				next_state = INV_MIX_COLUMNS_LOOP_WAIT_2;
			end
			INV_MIX_COLUMNS_LOOP_WAIT_2: begin
				next_state = INV_MIX_COLUMNS_LOOP_3;
			end
			INV_MIX_COLUMNS_LOOP_3: begin
				next_state = INV_MIX_COLUMNS_LOOP_WAIT_3;
			end
			INV_MIX_COLUMNS_LOOP_WAIT_3: begin
				next_state = INV_SHIFT_ROWS_LOOP;
				loop_counter--;
			end
			DONE: begin
				if (~AES_START) begin
					next_state = START;
				end
				else begin
					next_state = DONE;
				end
			end
		endcase
		
		case (current_state)
			START: begin
				state = AES_MSG_ENC;
			end
			ADD_ROUND_KEY_INIT: begin 
				state = state ^ key_expansion_out[127:0];
			end
			INV_SHIFT_ROWS_LOOP: begin
				inv_shift_rows_data_in = state;
			end
			INV_SHIFT_ROWS_LOOP_WAIT: begin
				state = inv_shift_rows_data_out;
			end
			INV_SUB_BYTES_LOOP: begin
//				for(int i = 0; i<16; i++) begin
//					inv_sub_bytes_in[i] <= state[8*i+7:8*i];
//				end
				{inv_sub_bytes_in[0], 
				 inv_sub_bytes_in[1],
				 inv_sub_bytes_in[2],
				 inv_sub_bytes_in[3],
				 inv_sub_bytes_in[4],
				 inv_sub_bytes_in[5],
				 inv_sub_bytes_in[6],
				 inv_sub_bytes_in[7],
				 inv_sub_bytes_in[8],
				 inv_sub_bytes_in[9],
				 inv_sub_bytes_in[10],
				 inv_sub_bytes_in[11],
				 inv_sub_bytes_in[12],
				 inv_sub_bytes_in[13],
				 inv_sub_bytes_in[14],
				 inv_sub_bytes_in[15]}= state[127:0];
			end
			INV_SUB_BYTES_LOOP_WAIT: begin	
//				for(int i = 0; i<16; i++) begin
//					state[8*i+7:8*i] <= inv_sub_bytes_out[i];
//				end
				state[127:0] = {inv_sub_bytes_in[0], 
									 inv_sub_bytes_in[1],
									 inv_sub_bytes_in[2],
									 inv_sub_bytes_in[3],
									 inv_sub_bytes_in[4],
									 inv_sub_bytes_in[5],
									 inv_sub_bytes_in[6],
									 inv_sub_bytes_in[7],
									 inv_sub_bytes_in[8],
									 inv_sub_bytes_in[9],
									 inv_sub_bytes_in[10],
									 inv_sub_bytes_in[11],
									 inv_sub_bytes_in[12],
									 inv_sub_bytes_in[13],
									 inv_sub_bytes_in[14],
									 inv_sub_bytes_in[15]};
			end
			INV_MIX_COLUMNS_LOOP_0: begin
				inv_mix_columns_in = state[31:0];
			end
			INV_MIX_COLUMNS_LOOP_WAIT_0: begin
				state[31:0] = inv_mix_columns_out;
			end
			INV_MIX_COLUMNS_LOOP_1: begin
				inv_mix_columns_in = state[63:32];
			end
			INV_MIX_COLUMNS_LOOP_WAIT_1: begin
				state[63:32] = inv_mix_columns_out;
			end
			INV_MIX_COLUMNS_LOOP_2: begin
				inv_mix_columns_in = state[95:64];
			end
			INV_MIX_COLUMNS_LOOP_WAIT_2: begin
				state[95:64] = inv_mix_columns_out;
			end
			INV_MIX_COLUMNS_LOOP_3: begin
				inv_mix_columns_in = state[127:96];
			end
			INV_MIX_COLUMNS_LOOP_WAIT_3: begin
				state[127:96] = inv_mix_columns_out;
			end
			DONE: begin
				AES_DONE = 1'b1;
				AES_MSG_DEC = state;
			end
		endcase	
	end
	
	
	always_ff begin
		current_state <= next_state;
	end
				
	
	
endmodule
