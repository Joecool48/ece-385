/*
 * keyboard.cpp
 *
 *  Created on: Dec 7, 2018
 *      Author: joey
 */

#include "../include/keyboard.h"
#include <iostream>
// Methods to sim a keyboard

/*
 * Left KEY_A
 * UP 0x9e
 * DOWN 0x1e
 *
 * CROUCH KEY_S
 * UP 0x9f
 * DOWN 0x1f
 *
 * Right KEY_D
 * UP 0xa0
 * DOWN 0x20
 *
 * JUMP KEY_W
 * UP 0x91
 * DOWN 0x11
 *
 * FIREBALL KEY_SPACE
 * UP 0xb9
 * DOWN 0x39
 *
 * PAUSE KEY_ESC
 * UP 0x81
 * DOWN 0x01
 */
// Init static vars
map<uint8_t, Key> Keyboard::keys;
//map<uint8_t, Key> Keyboard::key_ups;
//map<uint8_t, Key> Keyboard::key_downs;

//uint16_t Keyboard::scancode = 0;

volatile uint16_t * const Keyboard::SCANCODE_PIO ((uint16_t*) 0x8001010);

uint8_t Keyboard::getScanCode() {
	return (*Keyboard::SCANCODE_PIO & 0xff); // Just get first 8 bits
}

void Keyboard::initKeyboard() {
//	key_ups[0x9e] = Key::KEY_LEFT;
//	key_ups[0x9f] = Key::KEY_CROUCH;
//	key_ups[0xa0] = Key::KEY_RIGHT;
//	key_ups[0x91] = Key::KEY_JUMP;
//	key_ups[0xb9] = Key::KEY_FIREBALL;
//	key_ups[0x81] = Key::KEY_PAUSE;
//	key_downs[0x1e] = Key::KEY_LEFT;
//	key_downs[0x1f] = Key::KEY_CROUCH;
//	key_downs[0x20] = Key::KEY_RIGHT;
//	key_downs[0x11] = Key::KEY_JUMP;
//	key_downs[0x39] = Key::KEY_FIREBALL;
//	key_downs[0x01] = Key::KEY_PAUSE;
	keys[7] = Key::KEY_RIGHT;
	keys[4] = Key::KEY_LEFT;
	keys[26] = Key::KEY_JUMP;
	keys[44] = Key::KEY_FIREBALL;
	keys[22] = Key::KEY_CROUCH;
	keys[41] = Key::KEY_PAUSE;
}

void Keyboard::updateKeys() {
	std::cout << "scancode = " << unsigned(getScanCode()) << std::endl;
//	if (key_ups.find(getScanCode()) != key_ups.end()) {
//		Key k = key_ups[getScanCode()];
//		keys.erase(k);
//	}
//	else if (key_downs.find(getScanCode()) != key_downs.end()) {
//		Key k = key_downs[getScanCode()];
//		keys.insert(k);
//	}
}
bool Keyboard::key_jump(bool keyboardEnable) {
	// return (keys.find(Key::KEY_JUMP) != keys.end()) && keyboardEnable;
	return keys[getScanCode()] == Key::KEY_JUMP && keyboardEnable;
}
bool Keyboard::key_left(bool keyboardEnable) {
	//return (keys.find(Key::KEY_LEFT) != keys.end()) && keyboardEnable;
	return keys[getScanCode()] == Key::KEY_LEFT && keyboardEnable;
}
bool Keyboard::key_right(bool keyboardEnable) {
	//return (keys.find(Key::KEY_RIGHT) != keys.end()) && keyboardEnable;
	return keys[getScanCode()] == Key::KEY_RIGHT && keyboardEnable;
}
bool Keyboard::key_crouch(bool keyboardEnable) {
	//return (keys.find(Key::KEY_CROUCH) != keys.end()) && keyboardEnable;
	return keys[getScanCode()] == Key::KEY_CROUCH && keyboardEnable;
}
bool Keyboard::key_fireball(bool keyboardEnable) {
	//return (keys.find(Key::KEY_FIREBALL) != keys.end()) && keyboardEnable;
	return keys[getScanCode()] == Key::KEY_FIREBALL && keyboardEnable;
}
bool Keyboard::key_pause() {
	//return (keys.find(Key::KEY_PAUSE) != keys.end()); // Shouldnt need to be check for enabling
	return keys[getScanCode] == Key::KEY_PAUSE;
}
bool Keyboard::keys_pressed() {
	return getScanCode() != 0;
}
