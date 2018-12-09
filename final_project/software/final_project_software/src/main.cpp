
#include <stdio.h>
#include "../include/background.h"
#include "../include/init.h"
#include "../include/config.h"
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <ostream>
#include <istream>
#include "../include/keyboard.h"
#include "../include/sim.h"
#include <unistd.h>
using namespace std;

string strip_newline(string str) {
	if (str.length() <= 1) return "";
	return str.substr(str.length() - 1);
}

int main ()
{
//	volatile uint32_t * const SPRITE_X_PIO = (uint32_t*) &Sprite::sprite_x;
//	volatile uint32_t * const SPRITE_Y_PIO = (uint32_t*) &Sprite::sprite_y;
//	volatile uint32_t * const SPRITE_WIDTH_PIO = (uint32_t*) &Sprite::sprite_width;
//	volatile uint32_t * const SPRITE_HEIGHT_PIO = (uint32_t*) &Sprite::sprite_height;
//	volatile uint32_t * const SPRITE_ID_PIO = (uint32_t*) &Sprite::sprite_id;
//	volatile uint32_t * const SPRITE_ADDRESS_PIO = (uint32_t*) &Sprite::sprite_address;
//	volatile uint32_t * const SPRITE_FLIP_MODE_PIO = (uint32_t*) &Sprite::sprite_flip_mode;
//	volatile uint32_t * const HARDWARE_DONE = (uint32_t*) &Sprite::hardware_done;
//	volatile uint32_t * const SOFTWARE_DONE = (uint32_t*) &Sprite::software_done;
//	volatile uint32_t * const SCANCODE_PIO = (uint32_t*) &Keyboard::scancode;
	Background * background = new Background ();
	Player * player = new Player(30, 30); // Make a player at 30, 30
	background->setPlayer(player); // Each contains the other
	player->setBackground(background);
	setBackgroundObjectWorld1(background); // Add the world 1 object colliders
	Keyboard::initKeyboard(); // Startup the keyboard
	Fireflower * fireflower = new Fireflower(30, 150);
	background->items[fireflower->collider.collider_id] = fireflower;
	string line;
	while (true) {
		Sim::scancode_file.seekg(0, ios_base::beg);
		Sim::scancode_file >> line;
		std::cout << "Line " << line << std::endl;
		std::cout << "Scancode:" << unsigned(atoi((line == "" ? "0" : line).c_str())) << std::endl;

		*Keyboard::SCANCODE_PIO = unsigned(atoi((line == "" ? "0" : line).c_str()));
		Keyboard::updateKeys();
		std::cout << "Before update background" << std::endl;
		background->updateBackground(); // Function that does everything in the game.
		std::cout << "After  backgroundUpdate" << std::endl;
		// Wait for hardware, and signal that you're done
		*Sprite::SOFTWARE_DONE = 1;
		Sim::software_done_file.seekp(0, ios_base::beg);
		Sim::software_done_file << 1 << std::flush;
		Sim::hardware_done_file.seekg(0, ios_base::beg);
		getline(Sim::hardware_done_file, line);
		//line = strip_newline(line);
		*Sprite::HARDWARE_DONE = atoi(line.c_str());
		while (!(*Sprite::HARDWARE_DONE)) { // Should update at 60ish fps
			std::cout << "Before" << std::endl;
			Sim::hardware_done_file.seekg(0, ios_base::beg);
			Sim::hardware_done_file >> line;
			*Sprite::HARDWARE_DONE = atoi(line.c_str());
			std::cout << "Line 2" << line << std::endl;
			usleep(500000);
		}
		*Sprite::SOFTWARE_DONE = 0;
		Sim::software_done_file.seekp(0, ios_base::beg);
		Sim::software_done_file << 0 << std::flush;
		usleep(500000);
		cout << std::endl;
	}
	return 0;
}
