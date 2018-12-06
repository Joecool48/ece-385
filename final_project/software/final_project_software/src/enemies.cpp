/*
 * enemies.cpp
 *
 *  Created on: Nov 29, 2018
 *      Author: joey
 */
#include "enemies.h"


void Turtle::animatorSetup() {
	Sprite turtle_up(x, y, 16, 32, ADDRESS_OFFSET + 759584);
	Sprite turtle_walk_1(x, y, 16, 32, ADDRESS_OFFSET + 761632);
	Sprite turtle_walk_2(x, y, 16, 32, ADDRESS_OFFSET + 760096);
	Sprite turtle_shell_frame_1(x, y, 16, 32, ADDRESS_OFFSET + 760608);
	state_mode_to_frames_map[WALKING][NORMAL_MODE].push_back(turtle_walk_1);
	state_mode_to_frames_map[WALKING][NORMAL_MODE].push_back(turtle_walk_2);
	state_mode_to_frames_map[SHELL][NORMAL_MODE].push_back(turtle_shell_frame_1);
	state_mode_to_frames_map[SHELL_MOVING][NORMAL_MODE].push_back(turtle_shell_frame_1);
	state_mode_to_frames_map[GET_UP][NORMAL_MODE].push_back(turtle_up);
}

void Gumba::animatorSetup() {
	Sprite walking_1(x, y, 16, 32, 762656);
	Sprite walking_2(x, y, 16, 32, 761120);
	state_mode_to_frames_map[WALKING][NORMAL_MODE].push_back(walking_1);
	state_mode_to_frames_map[WALKING][NORMAL_MODE].push_back(walking_2);
}
/*
 * TODO
 * Implement Gumba state machine
 */
void Gumba::update() {

}

/*
 * TODO
 * Implement Turtle state machine
 */
void Turtle::update() {

}
