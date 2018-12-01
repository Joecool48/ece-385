/*
 * keyboard.h
 *
 *  Created on: Nov 28, 2018
 *      Author: joey
 */

#ifndef INCLUDE_KEYBOARD_H_
#define INCLUDE_KEYBOARD_H_

#include <unordered_map>



class Keyboard {
	enum class key {};
	void init_keyboard();
	int getScanCode();
	int decodeKey(int scanCode);
	key getInputKey();
};



#endif /* INCLUDE_KEYBOARD_H_ */
