/*
 * sim.h
 *
 *  Created on: Dec 8, 2018
 *      Author: joey
 */

#ifndef INCLUDE_SIM_H_
#define INCLUDE_SIM_H_
#include <string>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
#define prefix_path string("/home/joey/courses/ece385/final_project/python_sim/")

class Sim {
public:
	static fstream software_done_file, hardware_done_file, sprite_x_file, sprite_y_file, sprite_width_file, sprite_height_file, scancode_file, sprite_address_file, sprite_id_file, sprite_flip_mode_file;
	static void initSim();
};

#endif /* INCLUDE_SIM_H_ */
