/*
 * sim.cpp
 *
 *  Created on: Dec 8, 2018
 *      Author: joey
 */

#include "../include/sim.h"


fstream Sim::software_done_file(prefix_path + "SOFTWARE_DONE"), Sim::hardware_done_file(prefix_path + "HARDWARE_DONE"), Sim::sprite_x_file(prefix_path + "SPRITE_X_PIO"), Sim::sprite_y_file(prefix_path + "SPRITE_Y_PIO"), Sim::sprite_width_file(prefix_path + "SPRITE_WIDTH_PIO"), Sim::sprite_height_file(prefix_path + "SPRITE_HEIGHT_PIO"), Sim::scancode_file(prefix_path + "SCANCODE_PIO"), Sim::sprite_address_file(prefix_path + "SPRITE_ADDRESS_PIO"), Sim::sprite_id_file(prefix_path + "SPRITE_ID_PIO"), Sim::sprite_flip_mode_file(prefix_path + "SPRITE_FLIP_MODE_PIO");

void Sim::initSim() {
//	software_done_file.open(prefix_path + "SOFTWARE_DONE", ios::trunc);
//	hardware_done_file.open(prefix_path + "HARDWARE_DONE", ios::trunc);
//	sprite_x_file.open(prefix_path + "SPRITE_X_PIO", ios::trunc);
//	sprite_y_file.open(prefix_path + "SPRITE_Y_PIO", ios::trunc);
//	sprite_width_file.open(prefix_path + "SPRITE_WIDTH_PIO", ios::trunc);
//	sprite_height_file.open(prefix_path + "SPRITE_HEIGHT_PIO", ios::trunc);
//	sprite_id_file.open(prefix_path + "SPRITE_ID_PIO", ios::trunc);
//	sprite_flip_mode_file.open(prefix_path + "SPRITE_FLIP_MODE_PIO", ios::trunc);
//	scancode_file.open(prefix_path + "SCANCODE_PIO", ios::trunc);
//	sprite_address_file.open(prefix_path + "SPRITE_ADDRESS_PIO", ios::trunc);
}
