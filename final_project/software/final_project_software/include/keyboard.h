/*
 * keyboard.h
 *
 *  Created on: Nov 28, 2018
 *      Author: joey
 */

#ifndef INCLUDE_KEYBOARD_H_
#define INCLUDE_KEYBOARD_H_
#include "../include/config.h"
#include <map>
#include <set>
using namespace std;
/*TODO
 * Implement keyboard class
 *
 */
class Keyboard {
public:
	static uint8_t getScanCode();
	static void initKeyboard(); // Init keyboard map
	static void updateKeys(); // Should return NO_KEY if no key is pressed
	static bool key_jump(bool keyboardEnable);
	static bool key_left(bool keyboardEnable);
	static bool key_right(bool keyboardEnable);
	static bool key_crouch(bool keyboardEnable);
	static bool key_fireball(bool keyboardEnable);
	static bool key_pause();
	static bool keys_pressed();
	static volatile uint16_t * const SCANCODE_PIO;
	//volatile uint32_t * const SCANCODE_PIO = (uint32_t*) 0x3132313;
//	static uint8_t scancode;
//	static set<Key> keys;
//	static map<uint8_t, Key> key_ups;
//	static map<uint8_t, Key> key_downs;
	static map<uint8_t, Key> keys;
};



#endif /* INCLUDE_KEYBOARD_H_ */
