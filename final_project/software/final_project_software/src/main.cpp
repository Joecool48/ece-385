
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
#include "../include/enemies.h"
//extern "C" {
//#include "../include/efsl/efs.h"
//#include "../include/efsl/ls.h"
//}
//#include <system.h>
using namespace std;

string strip_newline(string str) {
	if (str.length() <= 1) return "";
	return str.substr(str.length() - 1);
}
//char toDec(char hex) {
//	if (hex >= 'a' && hex <= 'f') {
//		return hex - 'a' + 10;
//	}
//	else if (hex >= 'A' && hex <= 'F') {
//		return hex - 'A' + 10;
//	}
//	else {
//		return hex - '0';
//	}
//}
//void init_sdcard() {
//	char * address = (char *) ADDRESS_OFFSET;
//	if (!alt_up_sd_card_is_Present()) {
//		printf("No SD card available to read\n");
//		return;
//	}
//	if (!alt_up_sd_card_is_FAT16()) {
//		printf("Cannot read card. Not FAT16\n");
//		return;
//	}
//	char filename[] = "test.hex";
//	short fd = alt_up_sd_card_fopen(filename, false);
//	if (fd < 0) {
//		printf("SD card error. Could not be opened\n");
//		return;
//	}
//	char curr_char;
//	char curr_char2;
//	do {
//		curr_char = alt_up_sd_card_read(fd);
//		curr_char2 = alt_up_sd_card_read(fd);
//		*address = (toDec(curr_char) * 16) + toDec(curr_char2);
//		address += 1;
//		curr_char = alt_up_sd_card_read(fd);
//		curr_char2 = alt_up_sd_card_read(fd);
//		*address = (toDec(curr_char) * 16) + toDec(curr_char2);
//		address += 1;
//		curr_char = alt_up_sd_card_read(fd); // Get the space at the hex format after every 4 ascii chars
//		address += 1;
//
//	} while(curr_char >= 0);
//	if (curr_char != -1) {
//		printf("Reading SD card failed\n");
//		return;
//	}
//}

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
	//init_sdcard(); // Initialize the sd card memory
	Background * background = new Background ();
	Player * player = new Player(30, 30); // Make a player at 30, 30
	background->setPlayer(player); // Each contains the other
	player->setBackground(background);
	setBackgroundObjectWorld1(background); // Add the world 1 object colliders
	Keyboard::initKeyboard(); // Startup the keyboard
	string line;

	Turtle * turt = new Turtle(100, 100, background);
	background->enemies[turt->collider.collider_id] = turt;
	std::cout << "Before loop" << std::endl;
	while (true) {
		Sim::scancode_file.seekg(0, ios_base::beg);
		Sim::scancode_file >> line;
		std::cout << "Scancode:" << unsigned(atoi((line == "" ? "0" : line).c_str())) << std::endl;

		*Keyboard::SCANCODE_PIO = unsigned(atoi((line == "" ? "0" : line).c_str()));
		Keyboard::updateKeys();
		background->updateBackground(); // Function that does everything in the game.
		// Wait for hardware, and signal that you're done
		usleep(500000);
//		Sim::software_done_file.seekp(0, ios_base::beg);
//		Sim::software_done_file << 1 << std::flush;
//		Sim::hardware_done_file.seekg(0, ios_base::beg);
//		getline(Sim::hardware_done_file, line);
		//line = strip_newline(line);
		//*Sprite::HARDWARE_DONE = atoi(line.c_str());
		//while (!(*Sprite::HARDWARE_DONE)) { // Should update at 60ish fps
		//	std::cout << "Waiting for hardware" << std::endl;
//		//	Sim::hardware_done_file.seekg(0, ios_base::beg);
//		//	Sim::hardware_done_file >> line;
//		//	*Sprite::HARDWARE_DONE = atoi(line.c_str());
		//}
//		Sim::software_done_file.seekp(0, ios_base::beg);
//		Sim::software_done_file << 0 << std::flush;
		cout << std::endl;
	}

	return 0;
}
