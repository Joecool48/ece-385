/*
 * sprite.cpp
 *
 *  Created on: Dec 1, 2018
 *      Author: joey
 */
#include "sprite.h"

/* TODO: Make function warn when it is drawing out of range
 * Draws a sprite at a specified location by placing it in memory
 */

void Sprite::drawSprite() {
	if (isVisible) {
		*SPRITE_X_PIO = (uint16_t) x;
		*SPRITE_Y_PIO = (uint16_t) y;
		*SPRITE_ADDRESS_PIO = start_address;
		*SPRITE_WIDTH_PIO = width;
		*SPRITE_HEIGHT_PIO = height;
		*SPRITE_ID_PIO = ++(*SPRITE_ID_PIO);
	}
}

Image::Image (uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t address) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->start_address = address;
}

Sprite::Sprite(float x, float y, uint16_t width, uint16_t height, uint32_t address) : Image (x, y, width, height, address) {
	isVisible = false;
	isFlipped = false; // Variable for if the sprite is flipped. Also used in player for walking left
}
