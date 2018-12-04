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

enum class Key {KEY_LEFT, KEY_RIGHT, KEY_JUMP, KEY_CROUCH, KEY_FIREBALL, NO_KEY, KEY_PAUSE};
enum class Collider_Id {DUMMY_COLLIDER_ID,
						GUMBA,
						FIREBALL,
						FIREFLOWER,
						MUSHROOM,
						TURTLE,
						TURTLE_SHELL,
						PLATFORM_BREAKABLE,
						PLATFORM_UNBREAKABLE,
						COIN_BLOCK,
						ITEM_BLOCK
						}; // List all the possible objects on the screen. The background tells another object when it collides, and what it should do
inline bool cantGoThrough (Collider_Id id) {
	return id == Collider_Id::PLATFORM_BREAKABLE || id == Collider_Id::PLATFORM_UNBREAKABLE || id == Collider_Id::COIN_BLOCK || id == Collider_Id::ITEM_BLOCK;
}
const float GRAVITY_STRENGTH = 3;
const float TERMINAL_VELOCITY = 100;
const uint16_t FRAMES_PER_SECOND = 60;

bool pause_animation =false;
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
