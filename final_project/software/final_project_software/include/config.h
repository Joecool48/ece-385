/*
 * config.h
 *
 *  Created on: Nov 28, 2018
 *      Author: joey
 */

#ifndef INCLUDE_CONFIG_H_
#define INCLUDE_CONFIG_H_

#include <stdint.h>
#include "../include/colliders.h"

using namespace std;
/*
 * TODO
 * Add real address offset here
 */
const uint32_t ADDRESS_OFFSET = 0x30000000; // Place where the memory is initialized in SDRAM


const uint16_t SCREEN_WIDTH = 480; // Screen height and width in pixels
const uint16_t SCREEN_HEIGHT = 360;

const uint16_t FRAMES_PER_SECOND = 60;

enum class Key {KEY_LEFT, KEY_RIGHT, KEY_JUMP, KEY_CROUCH, KEY_FIREBALL, NO_KEY, KEY_PAUSE};

const float GRAVITY_STRENGTH = .2;
const float TERMINAL_VELOCITY = 100;

// Returns how much to offset rect1 first param


const uint8_t NO_FLIP = 0; // Hardcoded for player
const uint8_t FLIP_HORIZONTAL = 1;
const uint8_t FLIP_VERTICAL = 2;


#endif /* INCLUDE_CONFIG_H_ */
