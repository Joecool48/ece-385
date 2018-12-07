/*
 * config.h
 *
 *  Created on: Nov 28, 2018
 *      Author: joey
 */

#ifndef INCLUDE_CONFIG_H_
#define INCLUDE_CONFIG_H_
/*
 * TODO
 * Add real address offset here
 */
const uint32_t ADDRESS_OFFSET = 0x312313; // Place where the memory is initialized in SDRAM


const uint16_t SCREEN_WIDTH = 480; // Screen height and width in pixels
const uint16_t SCREEN_HEIGHT = 360;

const uint16_t FRAMES_PER_SECOND = 60;

enum class Key {KEY_LEFT, KEY_RIGHT, KEY_JUMP, KEY_CROUCH, KEY_FIREBALL, NO_KEY, KEY_PAUSE};
enum class Collider_Type {DUMMY_COLLIDER_TYPE,
						GUMBA,
						FIREBALL,
						FIREFLOWER,
						MUSHROOM,
						TURTLE,
						TURTLE_SHELL,
						PLATFORM_UNBREAKABLE,
						ITEM_BLOCK,
						PLAYER
						}; // List all the possible objects on the screen. The background tells another object when it collides, and what it should do
inline bool cantGoThrough (Collider_Type type) {
	return type == Collider_Type::PLATFORM_UNBREAKABLE || type == Collider_Type::ITEM_BLOCK;
}
// GUMBA, TURTLE, and TURTLE_SHELL are considered enemies
inline bool isEnemy (Collider_Type type) {
	return type == Collider_Type::GUMBA || type == Collider_Type::TURTLE || type == Collider_Type::TURTLE_SHELL;
}
const float GRAVITY_STRENGTH = .2;
const float TERMINAL_VELOCITY = 100;
// Returns how much to offset rect1 first param
void resolve (Rect_Collider & rect1, Rect_Collider & rect2) {
	rect1.collide_x += overlapX(rect1, rect2);
	rect1.collide_y += overlapY(rect1, rect2);
}
int16_t overlapX (const Rect_Collider & rect1, const Rect_Collider & rect2) {
	int16_t dist1 = 0, dist2 = 0;
	dist1 = rect2.collide_x + rect2.collide_width - rect1.collide_x;
	if (dist1 > 0) return dist1;
	dist2 = rect1.collide_x + rect1.collide_width - rect2.collide_x;
	if (dist2 > 0) return -dist2;
	return 0;

}
// Returns how much to offset rect1 first param
int16_t overlapY (const Rect_Collider & rect1, const Rect_Collider & rect2) {
	int16_t dist1 = 0, dist2 = 0;
	dist1 = rect1.collide_y + rect1.collide_height - rect2.collide_y;
	if (dist1 > 0) return -dist1;
	dist2 = rect2.collide_y + rect2.collide_height - rect1.collide_y;
	if (dist2 > 0) return dist2;
	return 0;
}
bool pause_animation = false;
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
