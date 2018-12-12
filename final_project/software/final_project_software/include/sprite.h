/*
 * sprite.h
 *
 *  Created on: Dec 1, 2018
 *      Author: joey
 */

#ifndef INCLUDE_SPRITE_H_
#define INCLUDE_SPRITE_H_
#include "../include/config.h"

// Class for each spriteframe
class Sprite {
public:
	Sprite();
	Sprite(int16_t width, int16_t height, uint32_t address);
	void drawSprite(int16_t xx, int16_t yy, uint8_t flip_mode, bool isVis);
	static volatile int16_t * const SPRITE_X_PIO;
	static volatile int16_t * const SPRITE_Y_PIO;
	static volatile int16_t * const SPRITE_WIDTH_PIO;
	static volatile int16_t * const SPRITE_HEIGHT_PIO;
	static volatile int16_t * const SPRITE_ID_PIO;
	static volatile uint32_t * const SPRITE_ADDRESS_PIO;
	static volatile uint8_t * const SPRITE_FLIP_MODE_PIO;
	static volatile uint8_t * const HARDWARE_DONE;
	static int16_t sprite_x, sprite_y, sprite_width, sprite_height, sprite_id;
	static uint32_t sprite_address;
	static uint8_t sprite_flip_mode;
	static uint8_t hardware_done, software_done;
	//// Sprite PIO Start Addresses
	//volatile uint32_t * const SPRITE_X_PIO = (uint32_t*) 0x01000890;
	//volatile uint32_t * const SPRITE_Y_PIO = (uint32_t*) 0x01000880;
	//volatile uint32_t * const SPRITE_WIDTH_PIO = (uint32_t*) 0x010008b0;
	//volatile uint32_t * const SPRITE_HEIGHT_PIO = (uint32_t*) 0x010008a0;
	//volatile uint32_t * const SPRITE_ID_PIO = (uint32_t*) 0x010008d0;
	//volatile uint32_t * const SPRITE_ADDRESS_PIO = (uint32_t*) 0x010008c0;
	//volatile uint32_t * const SPRITE_FLIP_MODE_PIO = (uint32_t*) 0x01000870;
	//
	//// TODO Add real hardware and software done addresses
	//volatile uint32_t * const HARDWARE_DONE = (uint32_t*) 0x1321313;
	//volatile uint32_t * const SOFTWARE_DONE = (uint32_t*) 0x1321313;
	uint32_t start_address;
	uint16_t width, height;
};



#endif /* INCLUDE_SPRITE_H_ */
