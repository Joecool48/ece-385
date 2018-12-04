/*
 * sprite.h
 *
 *  Created on: Dec 1, 2018
 *      Author: joey
 */

#ifndef INCLUDE_SPRITE_H_
#define INCLUDE_SPRITE_H_

// Class to store information about a image. Will be copied from this to create other sprites.
class Image {
public:
	float x;
	float y;
	uint16_t width;
	uint16_t height;
	uint32_t start_address;
	Image::Image (uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t address);
	virtual ~Image () = 0;
};

// Class for each spriteframe
class Sprite : public Image {
public:
	bool isVisible;
	bool isFlipped;
	Sprite();
	Sprite(float x, float y, uint16_t width, uint16_t height, uint32_t address);
	void drawSprite();
};
// Sprite with no image. Just to keep track of its collisions and movement
class Background_Sprite {
public:
	uint16_t x;
	uint16_t y;
	uint16_t width;
	uint16_t height;
};



#endif /* INCLUDE_SPRITE_H_ */
