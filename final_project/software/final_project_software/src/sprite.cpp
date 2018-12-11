/*
 * sprite.cpp
 *
 *  Created on: Dec 1, 2018
 *      Author: joey
 */
#include "../include/sprite.h"
#include <iostream>
#include <string>
#include "../include/sim.h"
using namespace std;

/* TODO: Make function warn when it is drawing out of range
 * Draws a sprite at a specified location by placing it in memory
 */
void Sprite::drawSprite(int16_t xx, int16_t yy, uint8_t flip_mode, bool isVis) {
	if (isVis) {
		std::cout << "Sprite x " << xx << std::endl;
		std::cout << "Sprite y " << yy << std::endl;
		std::cout << "Sprite width " << width << std::endl;
		std::cout << "Sprite height " << height << std::endl;
		std::cout << "Sprite address " << start_address << std::endl;
		//std::cout << "Sprite ID " << sprite_id << std::endl;
		*SPRITE_X_PIO = static_cast<uint16_t>(xx);
//		Sim::sprite_x_file.seekp(0, ios_base::beg);
//		Sim::sprite_x_file << xx << std::flush;
		*SPRITE_Y_PIO = static_cast<uint16_t>(yy);
//		Sim::sprite_y_file.seekp(0, ios_base::beg);
//		Sim::sprite_y_file << yy << std::flush;
		*SPRITE_ADDRESS_PIO = start_address;
//		Sim::sprite_address_file.seekp(0, ios_base::beg);
//		Sim::sprite_address_file << start_address << std::flush;
		*SPRITE_WIDTH_PIO = width;
//		Sim::sprite_width_file.seekp(0, ios_base::beg);
//		Sim::sprite_width_file << width << std::flush;
		*SPRITE_HEIGHT_PIO = height;
//		Sim::sprite_height_file.seekp(0, ios_base::beg);
//		Sim::sprite_height_file << height << std::flush;
		*SPRITE_FLIP_MODE_PIO = flip_mode;
//		Sim::sprite_flip_mode_file.seekp(0, ios_base::beg);
//		Sim::sprite_flip_mode_file << flip_mode << std::flush;
		*SPRITE_ID_PIO = (*SPRITE_ID_PIO) + 1;
//		Sim::sprite_id_file.seekp(0, ios_base::beg);
//		Sim::sprite_id_file << *SPRITE_ID_PIO << std::flush;
	}
	else {
		std::cout << "Sprite at " << xx << ", " << yy << " is not visible" << std::endl;
	}
}
Sprite::Sprite() {
	width = 0;
	height = 0;
	start_address = 0;
}

Sprite::Sprite(int16_t width, int16_t height, uint32_t address) {
	this->width = width;
	this->height = height;
	this->start_address = address;
}

//int16_t Sprite::sprite_x = 0, Sprite::sprite_y = 0, Sprite::sprite_width = 0, Sprite::sprite_height = 0, Sprite::sprite_id = 0;
//uint32_t Sprite::sprite_address = 0;
//uint8_t Sprite::sprite_flip_mode = 0;
//uint8_t Sprite::hardware_done = 0, Sprite::software_done = 0;

volatile int16_t * const Sprite::SPRITE_X_PIO((int16_t*) 0x8001110);
volatile int16_t * const Sprite::SPRITE_Y_PIO((int16_t*) 0x8001100);
volatile int16_t * const Sprite::SPRITE_WIDTH_PIO = ((int16_t*) 0x8001130);
volatile int16_t * const Sprite::SPRITE_HEIGHT_PIO ((int16_t*) 0x8001120);
volatile int16_t * const Sprite::SPRITE_ID_PIO((int16_t*) 0x8001150);
volatile uint32_t * const Sprite::SPRITE_ADDRESS_PIO((uint32_t*) 0x8001140);
volatile uint8_t * const Sprite::SPRITE_FLIP_MODE_PIO((uint8_t*) 0x80010f0);
volatile uint8_t * const Sprite::HARDWARE_DONE((uint8_t*) 0x8001000); // Add real addresses of the done signal

