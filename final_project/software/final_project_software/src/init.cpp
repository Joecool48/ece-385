/*
 * init.cpp
 *
 *  Created on: Dec 3, 2018
 *      Author: joey
 */
#include "init.h"
/*
 * TODO
 * Get all the background objects from the world1 like
 * Pipes, ground, coin clocks, and other things.
 * Some blocks should spawn coins, mushrooms, and or fireflowers
 */
void setBackgroundObjectWorld1(Background * b) {
	// Set the start address and width of background sprite
	if (b == nullptr) {
		std::cout << "You tried to init a nullptr" << std::endl;
	}
	b->x = 0;
	b->y = 0;
	b->width = 3391;
	b->height = 224;
	b->start_address = ADDRESS_OFFSET; // Background is at 0x0

}



