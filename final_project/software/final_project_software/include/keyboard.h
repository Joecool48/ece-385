/*
 * keyboard.h
 *
 *  Created on: Nov 28, 2018
 *      Author: joey
 */

#ifndef INCLUDE_KEYBOARD_H_
#define INCLUDE_KEYBOARD_H_



/*TODO
 * Implement keyboard class
 *
 */
class Keyboard {
	void init_keyboard();
	int getScanCode();
	int decodeKey(int scanCode);
	Key getInputKey(); // Should return NO_KEY if no key is pressed
	bool key_jump();
	bool key_left();
	bool key_right();
	bool key_crouch();
	bool key_fireball();
	bool multipleKeysPressed(); // Returns true if mult keys pressed
};



#endif /* INCLUDE_KEYBOARD_H_ */
