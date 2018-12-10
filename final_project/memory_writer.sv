module memory_writer (input logic Clk, Reset, Start,
							output logic [17:0] mem_addr,
							output logic [15:0] mem_data, 
							input logic [15:0] sprite_width,
							input logic [15:0] sprite_height,
							input logic [31:0] sprite_address,
							output logic avalon_control_go,             //               .go
							input logic avalon_control_done,            //               .done
							input logic avalon_control_early_done,      //               .early_done
							
							output logic [31:0] avalon_control_write_base,
							output logic [31:0] avalon_control_write_length,
							output [15:0] avalon_user_buffer_input_data,
							input logic avalon_user_buffer_full,
							output logic avalon_user_write_buffer,
							
							output logic [3:0] state
);
	
	reg [15:0] memory [2500]; //set to nb of 4-hex-words						
	initial begin
	   $readmemh("scripts/test3.hex", memory);
	end
	logic [15:0] mem_in;
	assign mem_data = mem_in;
	assign state ={1'b0, {curr_state}};
	enum logic [2:0] {WAIT, FETCH_AVALON_MEM, FETCH_MEM, PAUSE, FETCH_MEM2, DONE, DONE2} curr_state, next_state;
	logic test, clear;
	always_ff @ (posedge Clk) begin
		curr_state <= next_state;
		case(curr_state)
			WAIT: begin
				mem_addr <= 0;
				avalon_control_go <= 0;
				avalon_user_write_buffer <= 0;	
				mem_in <= 0;
			end
			FETCH_AVALON_MEM: begin
				avalon_control_go <= 1'b1;
				avalon_control_write_base <= sprite_address;					
				avalon_control_write_length <= sprite_width * sprite_height;
			end
			FETCH_MEM: begin
				avalon_control_go <= 0;
				avalon_user_write_buffer <= 0;	
				mem_in <= memory[mem_addr];
			end
			PAUSE: begin
				test <= 1'd1;
			end
			FETCH_MEM2: begin
				test <= 0;
				mem_addr <= mem_addr + 18'b1;
				avalon_user_buffer_input_data <= mem_in;		//Write
				avalon_user_write_buffer <= 1'b1;
			end
			DONE: begin

			end
			DONE2: begin
			
			end
		endcase
	end
	always_comb begin
		next_state = curr_state;
		case(curr_state)
			WAIT: if(Start) next_state = FETCH_AVALON_MEM;
			FETCH_AVALON_MEM: if(avalon_control_done) next_state = FETCH_MEM;
			FETCH_MEM: begin
				if (mem_addr == 32'd2500) next_state = DONE2;
				else if (!avalon_user_buffer_full) next_state = PAUSE;
			end
			PAUSE: if(clear) next_state = FETCH_MEM2;
			FETCH_MEM2: next_state = FETCH_MEM;	
			DONE: next_state = FETCH_MEM;
			DONE2: next_state = DONE2;
			default: next_state = WAIT;
		endcase
		if(~Reset) next_state = WAIT;
	end
	logic [31:0] clk_counter;
	always_ff @ (posedge Clk or negedge Reset) begin
		if (~Reset) begin 
			clk_counter <= 0;
			clear <= 0;
		end
		else if (test) begin
			if(clk_counter == 32'h05F5E10) begin
				clear <= 1'd1;
				clk_counter <= 0;
			end
			else clk_counter <= clk_counter + 32'd1;
		end
		else clear <= 0;
	end
endmodule
