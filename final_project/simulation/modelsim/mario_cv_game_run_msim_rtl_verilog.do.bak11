transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -sv -work work +incdir+C:/Users/yeda_/Documents/ECE_385/ece-385/final_project/system_verilog {C:/Users/yeda_/Documents/ECE_385/ece-385/final_project/system_verilog/VGA_controller.sv}
vlog -sv -work work +incdir+C:/Users/yeda_/Documents/ECE_385/ece-385/final_project/system_verilog {C:/Users/yeda_/Documents/ECE_385/ece-385/final_project/system_verilog/sprite_controller.sv}
vlog -sv -work work +incdir+C:/Users/yeda_/Documents/ECE_385/ece-385/final_project/system_verilog {C:/Users/yeda_/Documents/ECE_385/ece-385/final_project/system_verilog/frame_number.sv}
vlog -sv -work work +incdir+C:/Users/yeda_/Documents/ECE_385/ece-385/final_project/system_verilog {C:/Users/yeda_/Documents/ECE_385/ece-385/final_project/system_verilog/Color_Mapper.sv}
vlog -sv -work work +incdir+C:/Users/yeda_/Documents/ECE_385/ece-385/final_project {C:/Users/yeda_/Documents/ECE_385/ece-385/final_project/RAM_param.sv}
vlog -sv -work work +incdir+C:/Users/yeda_/Documents/ECE_385/ece-385/final_project {C:/Users/yeda_/Documents/ECE_385/ece-385/final_project/HexDriver.sv}
vlog -sv -work work +incdir+C:/Users/yeda_/Documents/ECE_385/ece-385/final_project/system_verilog {C:/Users/yeda_/Documents/ECE_385/ece-385/final_project/system_verilog/sprite_fifo.sv}
vlog -sv -work work +incdir+C:/Users/yeda_/Documents/ECE_385/ece-385/final_project/system_verilog {C:/Users/yeda_/Documents/ECE_385/ece-385/final_project/system_verilog/frame_controller.sv}
vlog -sv -work work +incdir+C:/Users/yeda_/Documents/ECE_385/ece-385/final_project/system_verilog {C:/Users/yeda_/Documents/ECE_385/ece-385/final_project/system_verilog/mario_cv_game.sv}
vlib final_project
vmap final_project final_project

vlog -sv -work work +incdir+C:/Users/yeda_/Documents/ECE_385/ece-385/final_project {C:/Users/yeda_/Documents/ECE_385/ece-385/final_project/testbench.sv}

vsim -t 1ps -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cycloneive_ver -L rtl_work -L work -L final_project -voptargs="+acc"  testbench

add wave *
view structure
view signals
run 20 ms
