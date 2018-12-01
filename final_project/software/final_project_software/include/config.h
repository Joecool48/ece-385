/*
 * config.h
 *
 *  Created on: Nov 28, 2018
 *      Author: joey
 */

#ifndef INCLUDE_CONFIG_H_
#define INCLUDE_CONFIG_H_

const uint16_t SCREEN_WIDTH = 480; // Screen height and width in pixels
const uint16_t SCREEN_HEIGHT = 360;


/*
 * TODO:
 * 	CHANGE THESE ADDRESSES TO REFLECT THE ACTUAL MEMORY ADDRESSES
 */
// Sprite PIO Start Addresses
volatile uint16_t * SPRITE_X_PIO = 0x12345678;
volatile uint16_t * SPRITE_Y_PIO = 0x12345678;
volatile uint16_t * SPRITE_WIDTH_PIO = 0x12345678;
volatile uint16_t * SPRITE_HEIGHT_PIO = 0x12345678;
volatile uint16_t * SPRITE_ID_PIO = 0x12345678;
volatile uint32_t * SPRITE_ADDRESS_PIO = 0x12345678;

#endif /* INCLUDE_CONFIG_H_ */
